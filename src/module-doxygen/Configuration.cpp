//=============================================================================
// Parser.cpp
//=============================================================================
#include "stdafx.h"

Gura_BeginModuleScope(doxygen)

//-----------------------------------------------------------------------------
// Configuration
//-----------------------------------------------------------------------------
Configuration::Configuration() : _stat(STAT_Init), _appendFlag(false)
{
}

bool Configuration::FeedChar(Environment &env, char ch)
{
	Gura_BeginPushbackRegion();
	switch (_stat) {
	case STAT_Init: {
		if (ch == '\0') {
			// nothing to do
		} else if (ch == '#') {
			_stat = STAT_SkipToLineEnd;
		} else if (ch == ' ' || ch == '\t') {
			// nothing to do
		} else if (ch == '\n') {
			// nothing to do
		} else if (IsNameCharBegin(ch)) {
			_field.clear();
			_field += ch;
			_stat = STAT_Name;
		} else {
			env.SetError(ERR_SyntaxError, "invalid variable name");
			return false;
		}
		break;
	}
	case STAT_Name: {
		if (IsNameChar(ch)) {
			_field += ch;
		} else { // including '\0'
			EntryDict::iterator iter = _entryDict.find(_field);
			if (iter == _entryDict.end()) {
				_pEntry.reset(new Entry(_field));
				_entryDict[_field] = _pEntry->Reference();
			} else {
				_pEntry.reset(iter->second->Reference());
			}
			Gura_Pushback();
			_stat = STAT_Assign;
		}
		break;
	}
	case STAT_Assign: {
		if (ch == ' ' || ch == '\t') {
			// nothing to do
		} else if (ch == '=') {
			_appendFlag = false;
			_field.clear();
			_stat = STAT_ValueBegin;
		} else if (ch == '+') {
			_stat = STAT_PlusAssign;
		} else { // including '\0'
			env.SetError(ERR_SyntaxError, "assign operator is expected");
			return false;
		}
		break;
	}
	case STAT_PlusAssign: {
		if (ch == '=') {
			_appendFlag = true;
			_field.clear();
			_stat = STAT_ValueBegin;
		} else { // including '\0'
			env.SetError(ERR_SyntaxError, "invalid assign operator");
			return false;
		}
		break;
	}
	case STAT_ValueBegin: {
		if (ch == ' ' || ch == '\t') {
			// nothing to do
		} else if (ch == '\n' || ch == '\0') {
			// no value is assigned
			_stat = STAT_Init;
		} else if (ch == '"') {
			_stat = STAT_QuotedValue;
		} else {
			Gura_Pushback();
			_stat = STAT_Value;
		}
		break;
	}
	case STAT_Value: {
		if (ch == '\n' || ch == '\0' || ch == '#') {
			_pEntry->AddValue(Strip(_field.c_str()));
			_stat = (ch == '#')? STAT_SkipToLineEnd : STAT_Init;
		} else if (ch == '\\') {
			_stat = STAT_Value_Escape;
		} else {
			_field += ch;
		}
		break;
	}
	case STAT_Value_Escape: {
		if (ch == '\n' || ch == '\0') {
			_pEntry->AddValue(Strip(_field.c_str()));
			_field.clear();
			_stat = STAT_ValueBegin;
		} else {
			_field += ch;
			_stat = STAT_Value;
		}
		break;
	}
	case STAT_QuotedValue: {
		if (ch == '\n' || ch == '\0') {
			::printf("%s = %s\n", _field.c_str(), _field.c_str());
			_stat = STAT_Init;
		} else if (ch == '"') {
			_stat = STAT_QuotedValueEnd;
		} else if (ch == '\\') {
			_stat = STAT_QuotedValue_Escape;
		} else {
			_field += ch;
		}
		break;
	}
	case STAT_QuotedValueEnd: {
		if (ch == '\n' || ch == '\0') {
			_pEntry->AddValue(Strip(_field.c_str()));
			_stat = STAT_Init;
		} else if (ch == ' ' || ch == '\t') {
			// nothing to do
		} else if (ch == '"') {
			_stat = STAT_QuotedValue;
		} else {
			Gura_Pushback();
			_stat = STAT_Value;
		}
		break;
	}
	case STAT_QuotedValue_Escape: {
		if (ch == '\n' || ch == '\0') {
			_pEntry->AddValue(Strip(_field.c_str()));
			_field.clear();
			_stat = STAT_ValueBegin;
		} else {
			_field += ch;
			_stat = STAT_QuotedValue;
		}
		break;
	}
	case STAT_SkipToLineEnd: {
		if (ch == '\n' || ch == '\0') {
			_stat = STAT_Init;
		} else {
			// nothing to do
		}
		break;
	}
	}
	Gura_EndPushbackRegion();
	return true;
}

bool Configuration::ReadStream(Environment &env, Stream &stream)
{
	Signal &sig = env.GetSignal();
	for (;;) {
		int chRaw;
		if ((chRaw = stream.GetChar(sig)) < 0) chRaw = 0;
		char ch = static_cast<char>(static_cast<UChar>(chRaw));
		if (!FeedChar(env, ch)) return false;
		if (ch == '\0') break;
	}
	return true;
}

void Configuration::Print() const
{
	foreach_const (EntryDict, iter, _entryDict) {
		const Entry *pEntry = iter->second;
		const StringList &values = pEntry->GetValues();
		if (values.empty()) {
			::printf("%s = {}\n", pEntry->GetName());
		} else if (values.size() == 1) {
			::printf("%s = '%s'\n", pEntry->GetName(), values.front().c_str());
		} else {
			::printf("%s = {\n", pEntry->GetName());
			foreach_const (StringList, pValue, values) {
				::printf("  '%s'\n", pValue->c_str());
			}
			::printf("}\n");
		}
	}
}

//-----------------------------------------------------------------------------
// Configuration::Entry
//-----------------------------------------------------------------------------
Configuration::Entry::Entry(const String &name) : _cntRef(1), _name(name)
{
}

//-----------------------------------------------------------------------------
// Configuration::EntryList
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Configuration::EntryDict
//-----------------------------------------------------------------------------
Configuration::EntryDict::~EntryDict()
{
	Clear();
}

void Configuration::EntryDict::Clear()
{
	foreach (EntryDict, iter, *this) {
		Entry::Delete(iter->second);
	}
	clear();
}

Gura_EndModuleScope(doxygen)
