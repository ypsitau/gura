//=============================================================================
// Parser.cpp
//=============================================================================
#include "stdafx.h"

Gura_BeginModuleScope(doxygen)

//-----------------------------------------------------------------------------
// Parser
//-----------------------------------------------------------------------------
Parser::Parser(const Aliases *pAliases, Parser *pParserParent) :
	_pAliases(pAliases), _pParserParent(pParserParent), _stat(STAT_Init),
	_pushbackLevel(0), _chAhead('\0'), _chPrev('\0'), _pElemOwner(new ElemOwner())
{
}

void Parser::SetCommandSpecial(const CommandFormat *pCmdFmt)
{
	_pElemCmdCur.reset(new Elem_Command(pCmdFmt));
	_stat = STAT_CommandSpecial;
}

void Parser::SetCommandCustom(const String &cmdName)
{
	_cmdName = cmdName;
	_stat = STAT_CommandCustom;
}

bool Parser::FeedChar(Environment &env, char ch)
{
	BeginPushbackRegion(ch);
	//::printf("%p ch=%c, stat=%d\n", this, ch, _stat);
	switch (_stat) {
	case STAT_Init: {
		if (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\0') {
			// nothing to do
		} else {
			Pushback(ch);
			_str.clear();
			_stat = STAT_String;
		}
		break;
	}
	case STAT_String: {
		if (ch == '\0') {
			FlushElemString(_str.c_str());
			_str.clear();
		} else if (IsCommandMark(ch)) {
			FlushElemString(_str.c_str());
			_str.clear();
			_cmdName.clear();
			_stat = STAT_AcceptCommandInString;
		} else {
			_str += ch;
		}
		break;
	}
	case STAT_AcceptCommandInString: {
		if (IsCommandEnd(_cmdName, ch)) {
			if (_cmdName.empty()) {
				env.SetError(ERR_SyntaxError, "command name is not specified");
				return false;
			}
			const CommandFormat *pCmdFmt = CommandFormat::Lookup(_cmdName.c_str());
			if (pCmdFmt == nullptr) {
				// custom command
				_stat = STAT_CommandCustom;
			} else {
				// special command
				_stat = STAT_CommandSpecial;
				_pElemCmdCur.reset(new Elem_Command(pCmdFmt));
			}
			Pushback(ch);
		} else {
			_cmdName += ch;
		}
		break;
	}
	case STAT_AcceptCommandInArgLine:
	case STAT_AcceptCommandInArgPara: {
		if (_pParserChild.get() != nullptr) {
			if (!_pParserChild->FeedChar(env, ch)) return false;
			if (_pParserChild->IsComplete()) {
				AutoPtr<Elem_Composite> pElemResult(
					new Elem_Composite(_pParserChild->GetElemOwner().Reference()));
				_pElemArg->GetElemOwner().push_back(pElemResult->ReduceContent()->Reference());
				_pParserChild.reset();
				_stat = (_stat == STAT_AcceptCommandInArgLine)? STAT_ArgLine : STAT_ArgPara;
			}
		} else if (IsCommandEnd(_cmdName, ch)) {
			if (_cmdName.empty()) {
				env.SetError(ERR_SyntaxError, "command name is not specified");
				return false;
			}
			const CommandFormat *pCmdFmt = CommandFormat::Lookup(_cmdName.c_str());
			if (pCmdFmt == nullptr) {
				// custom command
				_pParserChild.reset(new Parser(_pAliases, this));
				_pParserChild->SetCommandCustom(_cmdName.c_str());
				Pushback(ch);
			} else if (pCmdFmt->IsSectionIndicator()) {
				if (_stat == STAT_AcceptCommandInArgLine ||
					_stat == STAT_AcceptCommandInArgCustom) {
					env.SetError(ERR_SyntaxError,
								 "section indicator can not appear in line argument");
					return false;
				}
				// finish the previous command
				if (!_strArg.empty()) {
					_pElemArg->GetElemOwner().push_back(new Elem_String(_strArg));
					_strArg.clear();
				}
				_pElemCmdCur->GetElemArgs().push_back(_pElemArg->ReduceContent()->Reference());
				FlushElemCommand(_pElemCmdCur.release());
				// special command (section indicator)
				_pElemCmdCur.reset(new Elem_Command(pCmdFmt));
				Pushback(ch);
				_stat = STAT_CommandSpecial;
			} else {
				// special command (not section indicator)
				_pParserChild.reset(new Parser(_pAliases, this));
				_pParserChild->SetCommandSpecial(pCmdFmt);
			}
		} else {
			_cmdName += ch;
		}
		break;
	}
	case STAT_AcceptCommandInArgCustom: {
		if (_pParserChild.get() != nullptr) {
			if (!_pParserChild->FeedChar(env, ch)) return false;
			if (_pParserChild->IsComplete()) {
				_strArg += _pParserChild->GetString();
				_pParserChild.reset();
				_stat = STAT_ArgCustom;
			}
		} else if (IsCommandEnd(_cmdName, ch)) {
			if (_cmdName.empty()) {
				env.SetError(ERR_SyntaxError, "command name is not specified");
				return false;
			}
			const CommandFormat *pCmdFmt = CommandFormat::Lookup(_cmdName.c_str());
			if (pCmdFmt == nullptr) {
				// custom command
				_pParserChild.reset(new Parser(_pAliases, this));
				_pParserChild->SetCommandCustom(_cmdName);
				Pushback(ch);
			} else {
				// special command
				_strArg += _chAhead;
				_strArg += _cmdName;
				_stat = STAT_ArgCustom;
			}
		} else {
			_cmdName += ch;
		}
		break;
	}
	case STAT_CommandSpecial: {
		Pushback(ch);
		_strArg.clear();
		_stat = STAT_NextArg;
		break;
	}
	case STAT_NextArg: {
		const ElemOwner &elemArgs = _pElemCmdCur->GetElemArgs();
		const CommandFormat::ArgOwner &argOwner = _pElemCmdCur->GetCommandFormat()->GetArgOwner();
		size_t iArg = elemArgs.size();
		if (iArg < argOwner.size()) {
			Pushback(ch);
			_stat = STAT_BranchArg;
		} else {
			FlushElemCommand(_pElemCmdCur.release());
			Pushback(ch);
			_str.clear();
			_stat = IsTopLevel()? STAT_String : STAT_Complete;
		}
		break;
	}
	case STAT_BranchArg: {
		const ElemOwner &elemArgs = _pElemCmdCur->GetElemArgs();
		const CommandFormat::ArgOwner &argOwner = _pElemCmdCur->GetCommandFormat()->GetArgOwner();
		size_t iArg = elemArgs.size();
		const CommandFormat::Arg *pArg = argOwner[iArg];
		if (ch == ' ' || ch == '\t') {
			// nothing to do
		} else if (pArg->IsWord() || pArg->IsWordOpt()) {
			if (ch == '\n' || ch == '\0' || IsCommandMark(ch)) {
				if (pArg->IsWord()) {
					env.SetError(ERR_SyntaxError, "argument %s doesn't exist", pArg->GetName());
					return false;
				}
				Pushback(ch);
				_pElemCmdCur->GetElemArgs().push_back(new Elem_Empty());
				_stat = STAT_NextArg;
			} else if (ch == '"') {
				_strArg.clear();
				_stat = STAT_ArgWordQuote;
			} else {
				_strArg.clear();
				Pushback(ch);
				_stat = STAT_ArgWord;
			}
		} else if (pArg->IsBracket()) {
			if (ch == '[') {
				_strArg.clear();
				_stat = STAT_ArgBracket;
			} else { // including '\0'
				Pushback(ch);
				_pElemCmdCur->GetElemArgs().push_back(new Elem_Empty());
				_stat = STAT_NextArg;
			}
		} else if (pArg->IsLine() || pArg->IsLineOpt()) {
			_pElemArg.reset(new Elem_Composite());
			Pushback(ch);
			_strArg.clear();
			_stat = STAT_ArgLine;
		} else if (pArg->IsQuote() || pArg->IsQuoteOpt()) {
			if (ch == '"') {
				_strArg.clear();
				_stat = STAT_ArgQuote;
			} else { // including '\0'
				if (pArg->IsQuote()) {
					env.SetError(ERR_SyntaxError, "quoted string is expected");
					return false;
				}
				Pushback(ch);
				if (_chPrev == ' ' || _chPrev == '\t') Pushback(_chPrev);
				_pElemCmdCur->GetElemArgs().push_back(new Elem_Empty());
				_stat = STAT_NextArg;
			}
		} else if (pArg->IsBrace() || pArg->IsBraceOpt()) {
			if (ch == '{') {
				_strArg.clear();
				_stat = STAT_ArgBrace;
			} else { // include '\0'
				if (pArg->IsBrace()) {
					env.SetError(ERR_SyntaxError, "braced string is expected");
					return false;
				}
				Pushback(ch);
				_pElemCmdCur->GetElemArgs().push_back(new Elem_Empty());
				_stat = STAT_NextArg;
			}
		} else if (pArg->IsPara()) {
			_pElemArg.reset(new Elem_Composite());
			Pushback(ch);
			_strArg.clear();
			_stat = STAT_ArgPara;
		}
		break;
	}
	case STAT_ArgWord: {
		if (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\0' || IsCommandMark(ch)) {
			Pushback(ch);
			_pElemCmdCur->GetElemArgs().push_back(new Elem_String(_strArg));
			_strArg.clear();
			_stat = STAT_NextArg;
		} else if (ch == '.' || ch == ',' || ch == ';' || ch == '?' || ch == '!') {
			_chAhead = ch;
			_stat = STAT_ArgWord_Punctuation;
		} else {
			_strArg += ch;
		}
		break;
	}
	case STAT_ArgWord_Punctuation: {
		if (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\0' || IsCommandMark(ch)) {
			Pushback(ch);
			Pushback(_chAhead);
			_pElemCmdCur->GetElemArgs().push_back(new Elem_String(_strArg));
			_strArg.clear();
			_stat = STAT_NextArg;
		} else {
			Pushback(ch);
			_strArg += _chAhead;
			_stat = STAT_ArgWord;
		}
		break;
	}
	case STAT_ArgWordQuote: {
		if (ch == '\n' || ch == '\0') {
			Pushback(ch);
			_pElemCmdCur->GetElemArgs().push_back(new Elem_String(_strArg));
			_strArg.clear();
			_stat = STAT_NextArg;
		} else if (ch == '"') {
			_pElemCmdCur->GetElemArgs().push_back(new Elem_String(_strArg));
			_strArg.clear();
			_stat = STAT_NextArg;
		} else {
			_strArg += ch;
		}
		break;
	}
	case STAT_ArgBracket: {
		if (ch == '\n' || ch == '\0' || IsCommandMark(ch)) {
			env.SetError(ERR_SyntaxError, "unmatched brakcet mark");
			return false;
		} else if (ch == ']') {
			_pElemCmdCur->GetElemArgs().push_back(new Elem_String(_strArg));
			_strArg.clear();
			_stat = STAT_NextArg;
		} else {
			_strArg += ch;
		}
		break;
	}
	case STAT_ArgLine: {
		if (ch == '\n' || ch == '\0') {
			if (ch == '\0') Pushback(ch);
			String str = Strip(_strArg.c_str());
			if (!str.empty()) {
				_pElemArg->GetElemOwner().push_back(new Elem_String(str));
			}
			_strArg.clear();
			_pElemCmdCur->GetElemArgs().push_back(_pElemArg->ReduceContent()->Reference());
			_stat = STAT_NextArg;
		} else if (IsCommandMark(ch)) {
			String str = Strip(_strArg.c_str());
			if (!str.empty()) {
				_pElemArg->GetElemOwner().push_back(new Elem_String(str));
			}
			_strArg.clear();
			_cmdName.clear();
			_stat = STAT_AcceptCommandInArgLine;
		} else {
			_strArg += ch;
		}
		break;
	}
	case STAT_ArgQuote: {
		if (ch == '\n' || ch == '\0') {
			env.SetError(ERR_SyntaxError, "quoted string doesn't end correctly");
			return false;
		} else if (ch == '"') {
			_pElemCmdCur->GetElemArgs().push_back(new Elem_String(_strArg));
			_strArg.clear();
			_stat = STAT_NextArg;
		} else {
			_strArg += ch;
		}
		break;
	}
	case STAT_ArgBrace: {
		if (ch == '\n' || ch == '\0') {
			env.SetError(ERR_SyntaxError, "braced string doesn't end correctly");
			return false;
		} else if (ch == '}') {
			_pElemCmdCur->GetElemArgs().push_back(new Elem_String(_strArg));
			_strArg.clear();
			_stat = STAT_NextArg;
		} else {
			_strArg += ch;
		}
		break;
	}
	case STAT_ArgPara: {
		if (ch == '\n') {
			_strArg += ch;
			_strAhead.clear();
			_stat = STAT_ArgParaNewline;
		} else if (ch == '\0') {
			Pushback(ch);
			if (!_strArg.empty()) {
				_pElemArg->GetElemOwner().push_back(new Elem_String(_strArg));
				_strArg.clear();
			}
			_pElemCmdCur->GetElemArgs().push_back(_pElemArg->ReduceContent()->Reference());
			_stat = STAT_NextArg;
		} else if (IsCommandMark(ch)) {
			if (!_strArg.empty()) {
				_pElemArg->GetElemOwner().push_back(new Elem_String(_strArg));
				_strArg.clear();
			}
			_cmdName.clear();
			_stat = STAT_AcceptCommandInArgPara;
		} else {
			_strArg += ch;
		}
		break;
	}
	case STAT_ArgParaNewline: {
		if (ch == '\n') {
			// detected a blank line
			if (!_strArg.empty()) {
				_pElemArg->GetElemOwner().push_back(new Elem_String(_strArg));
				_strArg.clear();
			}
			_pElemCmdCur->GetElemArgs().push_back(_pElemArg->ReduceContent()->Reference());
			_stat = STAT_NextArg;
		} else if (ch == ' ' || ch == '\t') {
			_strAhead += ch;
		} else { // including '\0'
			_strArg += _strAhead;
			Pushback(ch);
			_stat = STAT_ArgPara;
		}
		break;
	}
	case STAT_CommandCustom: {
		if (ch == '{') {
			_strArg.clear();
			_stat = STAT_ArgCustom;
		} else {
			_strArg.clear();
			String rtn = EvaluateCustomCommand(env);
			if (env.IsSignalled()) return false;
			Pushback(ch);
			_strArgs.clear();
			_str.clear();
			_stat = STAT_String;
			foreach (String, p, rtn) {
				if (!FeedChar(env, *p)) return false;
			}
			if (!IsTopLevel()) _stat = STAT_Complete;
		}
		break;
	}
	case STAT_ArgCustom: {
		if (ch == '}') {
			_strArgs.push_back(_strArg);
			String rtn = EvaluateCustomCommand(env);
			if (env.IsSignalled()) return false;
			_strArgs.clear();
			_strArg.clear();
			_str.clear();
			_stat = STAT_String;
			foreach (String, p, rtn) {
				if (!FeedChar(env, *p)) return false;
			}
			if (!IsTopLevel()) _stat = STAT_Complete;
		} else if (ch == ',') {
			_strArgs.push_back(_strArg);
			_strArg.clear();
		} else if (ch == '\\') {
			_stat = STAT_ArgCustom_Backslash;
		} else if (IsCommandMark(ch)) {
			_cmdName.clear();
			_chAhead = ch;
			_stat = STAT_AcceptCommandInArgCustom;
		} else if (ch == '\0') {
			// nothing to do
		} else {
			_strArg += ch;
		}
		break;
	}
	case STAT_ArgCustom_Backslash: {
		if (ch == '\0') {
			Pushback(ch);
			_stat = STAT_ArgCustom;
		} else if (ch == ',') {
			_strArg += ch;
			_stat = STAT_ArgCustom;
		} else {
			Pushback(ch);
			_cmdName.clear();
			_chAhead = '\\';
			_stat = STAT_AcceptCommandInArgCustom;
		}
		break;
	}
	case STAT_Complete: {
		break;
	}
	}
	EndPushbackRegion();
	if (IsTopLevel() && ch == '\0') _stat = STAT_Init;
	_chPrev = ch;
	return true;
}

bool Parser::FeedString(Environment &env, const char *str)
{
	for (const char *p = str; ; p++) {
		if (!FeedChar(env, *p)) return false;
		if (*p == '\0') break;
	}
	return true;
}

String Parser::EvaluateCustomCommand(Environment &env) const
{
	String rtn;
	if (_pAliases != nullptr) {
		const Alias *pAlias = _pAliases->Lookup(_cmdName.c_str(), _strArgs.size());
		if (pAlias == nullptr || !pAlias->Evaluate(env, rtn, _strArgs)) return "";
	}
	return rtn;
}

bool Parser::ContainsCommand(const char *str)
{
	for (const char *p = str; *p != '\0'; p++) {
		char ch = *p;
		if (IsCommandMark(ch)) return true;
	}
	return false;
}

void Parser::FlushElemString(const char *str)
{
	if (*str == '\0') return;
	if (!IsTopLevel()) {
		if (_pElemOwner->empty()) {
			String strMod = Strip(str, true, false);
			if (strMod.empty()) return;
			_pElemOwner->push_back(new Elem_String(strMod));
		} else {
			_pElemOwner->push_back(new Elem_String(str));
		}
	} else if (!_pElemOwner->empty() && _pElemOwner->back()->GetType() == Elem::TYPE_Composite) {
		ElemOwner &elemOwner = dynamic_cast<Elem_Composite *>(_pElemOwner->back())->GetElemOwner();
		if (elemOwner.empty()) {
			String strMod = Strip(str, true, false);
			if (strMod.empty()) return;
			elemOwner.push_back(new Elem_String(strMod));
		} else {
			elemOwner.push_back(new Elem_String(str));
		}
	} else {
		String strMod = Strip(str, true, false);
		if (strMod.empty()) return;
		Elem_Composite *pElemComposite = new Elem_Composite();
		_pElemOwner->push_back(pElemComposite);
		ElemOwner &elemOwner = pElemComposite->GetElemOwner();
		elemOwner.push_back(new Elem_String(strMod));
	}
}

void Parser::FlushElemCommand(Elem_Command *pElem)
{
	CommandFormat::CmdType cmdType = pElem->GetCommandFormat()->GetType();
	if (cmdType != CommandFormat::CMDTYPE_Visual) {
		_pElemOwner->push_back(pElem);
		return;
	}
	if (!IsTopLevel()) {
		_pElemOwner->push_back(pElem);
	} else if (!_pElemOwner->empty() && _pElemOwner->back()->GetType() == Elem::TYPE_Composite) {
		ElemOwner &elemOwner = dynamic_cast<Elem_Composite *>(_pElemOwner->back())->GetElemOwner();
		elemOwner.push_back(pElem);
	} else {
		Elem_Composite *pElemComposite = new Elem_Composite();
		_pElemOwner->push_back(pElemComposite);
		ElemOwner &elemOwner = pElemComposite->GetElemOwner();
		elemOwner.push_back(pElem);
	}
}

Gura_EndModuleScope(doxygen)
