//=============================================================================
// Document.cpp
//=============================================================================
#include "stdafx.h"

Gura_BeginModuleScope(doxygen)

//-----------------------------------------------------------------------------
// Document
//-----------------------------------------------------------------------------
Document::Document() : _cntRef(1), _stat(STAT_Indent),
	_commentLineFlag(false), _regionPrev(RGN_Other), _pStructureOwner(new StructureOwner())
{
}

bool Document::ReadStream(Environment &env, SimpleStream &stream,
						  const Aliases *pAliases, bool extractedFlag)
{
	Signal &sig = env.GetSignal();
	_pParser.reset(new Parser(pAliases));
	if (extractedFlag) {
		AddStructure();
		_stat = STAT_ExIndent;
	} else {
		_stat = STAT_Indent;
	}
	for (;;) {
		int chRaw;
		if ((chRaw = stream.GetChar(sig)) < 0) chRaw = 0;
		char ch = static_cast<char>(static_cast<UChar>(chRaw));
		if (!FeedChar(env, ch)) return false;
		if (ch == '\0') break;
	}
	_sourceName = stream.GetName();
	_pParser.reset();
	return true;
}

bool Document::FeedChar(Environment &env, char ch)
{
	Gura_BeginPushbackRegion();
	//::printf("ch=%c, stat=%d\n", ch, _stat);
	switch (_stat) {
	case STAT_Indent: {
		if (ch == '\0') {
			// nothing to do
		} else if (ch == '\n') {
			_regionPrev = RGN_Other;
		} else if (ch == ' ' || ch == '\t') {
			// nothing to do
		} else if (ch == '/') {
			// parsed "/" after indentation
			_commentLineFlag = true;
			_stat = STAT_Slash;
		} else {
			_stat = STAT_Source;
			Gura_Pushback();
		}
		break;
	}
	case STAT_Source: {
		if (ch == '/') {
			// parsed "/" after some source code
			_commentLineFlag = false;
			_stat = STAT_Slash;
		} else if (ch == '\n') {
			_regionPrev = RGN_Other;
			_stat = STAT_Indent;
		} else { // including '\0'
			// nothing to do
		}
		break;
	}
	case STAT_Slash: {
		if (ch == '\0') {
			// nothing to do
		} else if (ch == '/') {
			// parsed "//"
			_stat = STAT_LineCommentBgn;
		} else if (ch == '*') {
			// parsed "/*"
			_stat = STAT_BlockCommentBgn;
		} else {
			// parsed "/."
			_commentLineFlag = false;
			Gura_Pushback();
			_stat = STAT_Source;
		}
		break;
	}
	case STAT_LineCommentBgn: {
		if (ch == '/' || ch == '!') {
			// parsed "///" or "//!"
			_stat = STAT_LineDoxygenFirstChar;
		} else { // including '\0'
			// parsed "//."
			_regionPrev = RGN_Other;
			Gura_Pushback();
			_stat = STAT_LineComment;
		}
		break;
	}
	case STAT_LineDoxygenFirstChar: {
		if (ch == '<') {
			_pParser->SetAheadFlag(!_commentLineFlag);
		} else {
			_pParser->SetAheadFlag(false);
			Gura_Pushback();
		}
		if (_regionPrev != RGN_LineDoxygen) {
			AddStructure();
		}
		_regionPrev = _commentLineFlag? RGN_LineDoxygen : RGN_LineDoxygenMixed;
		_stat = STAT_LineDoxygen;
		break;
	}
	case STAT_LineDoxygen: {
		if (ch == '\n') {
			// a line comment ends with newline.
			if (!_pParser->FeedChar(env, '\n')) return false;
			if (!_pParser->FeedChar(env, '\0')) return false;
			_stat = STAT_Indent;
		} else { // including '\0'
			if (!_pParser->FeedChar(env, ch)) return false;
		}
		break;
	}
	case STAT_LineComment: {
		if (ch == '\n') {
			// a line comment ends with newline.
			_stat = STAT_Indent;
		} else { // including '\0'
			// nothing to do
		}
		break;
	}
	case STAT_BlockCommentBgn: {
		if (ch == '\0') {
			// nothing to do
		} else if (ch == '*') {
			// parsed "/**"
			_stat = STAT_BlockCommentBgn_Asterisk;
		} else if (ch == '!') {
			// parsed "/*!"
			_stat = STAT_BlockDoxygenFirstChar;
		} else {
			// parsed "/*."
			_regionPrev = RGN_Other;
			_stat = STAT_BlockComment;
		}
		break;
	}
	case STAT_BlockCommentBgn_Asterisk: {
		if (ch == '/') {
			// parsed "/**/"
			_stat = STAT_Source;
		} else {
			// parsed "/**."
			Gura_Pushback();
			_stat = STAT_BlockDoxygenFirstChar;
		}
		break;
	}
	case STAT_BlockDoxygenFirstChar: {
		if (ch == '<') {
			_pParser->SetAheadFlag(!_commentLineFlag);
		} else {
			_pParser->SetAheadFlag(false);
			Gura_Pushback();
		}
		if (_regionPrev != RGN_LineDoxygen) {
			AddStructure();
		}
		_regionPrev = _commentLineFlag? RGN_BlockDoxygen : RGN_BlockDoxygenMixed;
		_stat = STAT_BlockDoxygen;
		break;
	}
	case STAT_BlockDoxygen: {
		if (ch == '*') {
			_stat = STAT_BlockDoxygen_Asterisk;
		} else if (ch == '\n') {
			if (!_pParser->FeedChar(env, ch)) return false;
			_stat = STAT_BlockDoxygen_Indent;
		} else { // including '\0'
			if (!_pParser->FeedChar(env, ch)) return false;
		}
		break;
	}
	case STAT_BlockDoxygen_Asterisk: {
		if (ch == '/') {
			if (!_pParser->FeedChar(env, '\0')) return false;
			_stat = STAT_Source;
		} else { // including '\0'
			if (!_pParser->FeedChar(env, '*')) return false;
			if (!_pParser->FeedChar(env, ch)) return false;
			_stat = STAT_BlockDoxygen;
		}
		break;
	}
	case STAT_BlockDoxygen_Indent: {
		if (ch == '\0') {
			if (!_pParser->FeedChar(env, ch)) return false;
		} else if (ch == '\n') {
			if (!_pParser->FeedChar(env, ch)) return false;
		} else if (ch == ' ' || ch == '\t') {
			// nothing to do
		} else if (ch == '*') {
			_stat = STAT_BlockDoxygen_IndentAsterisk;
		} else {
			Gura_Pushback();
			_stat = STAT_BlockDoxygen;
		}
		break;
	}
	case STAT_BlockDoxygen_IndentAsterisk: {
		if (ch == '/') {
			if (!_pParser->FeedChar(env, '\0')) return false;
			_stat = STAT_Source;
		} else {
			Gura_Pushback();
			_stat = STAT_BlockDoxygen_IndentAfterAsterisk;
		}
		break;
	}
	case STAT_BlockDoxygen_IndentAfterAsterisk: {
		if (ch == '\0') {
			// nothing to do
		} else if (ch == '\n') {
			if (!_pParser->FeedChar(env, ch)) return false;
			_stat = STAT_BlockDoxygen_Indent;
		} else if (ch == ' ' || ch == '\t') {
			// nothing to do
		} else {
			Gura_Pushback();
			_stat = STAT_BlockDoxygen;
		}
		break;
	}
	case STAT_BlockComment: {
		if (ch == '*') {
			_stat = STAT_BlockComment_Asterisk;
		} else { // including '\0'
			// nothing to do
		}
		break;
	}
	case STAT_BlockComment_Asterisk: {
		if (ch == '\0') {
			// nothing to do
		} else if (ch == '/') {
			_stat = STAT_Source;
		} else {
			_stat = STAT_BlockComment;
		}
		break;
	}
	case STAT_ExIndent: {
		if (ch == '\0') {
			if (!_pParser->FeedChar(env, ch)) return false;
		} else if (ch == '\n') {
			if (!_pParser->FeedChar(env, ch)) return false;
		} else if (ch == ' ' || ch == '\t') {
			// nothing to do
		} else {
			_stat = STAT_ExDoxygen;
			Gura_Pushback();
		}
		break;
	}
	case STAT_ExDoxygen: {
		if (ch == '\0') {
			if (!_pParser->FeedChar(env, ch)) return false;
		} else if (ch == '\n') {
			if (!_pParser->FeedChar(env, ch)) return false;
			_stat = STAT_ExIndent;
		} else {
			if (!_pParser->FeedChar(env, ch)) return false;
		}
		break;
	}
	}
	Gura_EndPushbackRegion();
	return true;
}

void Document::AddStructure()
{
	Structure *pStructure = new Structure();
	_pStructureOwner->push_back(pStructure);
	_pParser->SetElemOwner(pStructure->GetElemOwner().Reference());
}

Gura_EndModuleScope(doxygen)
