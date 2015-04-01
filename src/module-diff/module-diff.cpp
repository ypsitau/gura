//=============================================================================
// Gura module: diff
//=============================================================================
#include "stdafx.h"

Gura_BeginModuleBody(diff)

//-----------------------------------------------------------------------------
// HunkLine
//-----------------------------------------------------------------------------
String HunkLine::TextizeUnifiedRange() const
{
	String str;
	char buff[80];
	::sprintf(buff, "-%lu", linenoOrg);
	str += buff;
	if (nLinesOrg != 1) {
		::sprintf(buff, ",%lu", nLinesOrg);
		str += buff;
	}
	::sprintf(buff, " +%lu", linenoNew);
	str += buff;
	if (nLinesNew != 1) {
		::sprintf(buff, ",%lu", nLinesNew);
		str += buff;
	}
	return str;
}

HunkLine::Format HunkLine::SymbolToFormat(Signal sig, const Symbol *pSymbol)
{
	if (pSymbol->IsIdentical(Gura_UserSymbol(normal))) {
		return FORMAT_Normal;
	} else if (pSymbol->IsIdentical(Gura_UserSymbol(context))) {
		return FORMAT_Context;
	} else if (pSymbol->IsIdentical(Gura_UserSymbol(unified))) {
		return FORMAT_Unified;
	} else {		
		sig.SetError(ERR_ValueError, "invalid symbol for the format");
		return FORMAT_None;
	}
}

//-----------------------------------------------------------------------------
// DiffLine
//-----------------------------------------------------------------------------
void DiffLine::FeedString(SequenceLine &seq, const char *src)
{
	String str;
	for (const char *p = src; *p != '\0'; p++) {
		char ch = *p;
		if (ch == '\n') {
			seq.push_back(str);
			str.clear();
		} else {
			str += ch;
		}
	}
	if (!str.empty()) seq.push_back(str);
}

bool DiffLine::FeedStream(Signal sig, SequenceLine &seq, Stream &src)
{
	bool includeEOLFlag = false;
	for (;;) {
		String str;
		if (!src.ReadLine(sig, str, includeEOLFlag)) break;
		seq.push_back(str);
	}
	return !sig.IsSignalled();
}

bool DiffLine::FeedIterator(Environment &env, Signal sig,
							  SequenceLine &seq, Iterator *pIterator)
{
	Value value;
	while (pIterator->Next(env, sig, value)) {
		seq.push_back(value.ToString());
	}
	return !sig.IsSignalled();
}

void DiffLine::FeedList(SequenceLine &seq, const ValueList &valList)
{
	foreach_const (ValueList, pValue, valList) {
		seq.push_back(pValue->ToString());
	}
}

String DiffLine::TextizeUnifiedEdit(const DiffLine::Edit &edit)
{
	String str;
	str += GetEditMark(edit);
	str += edit.first;
	return str;
}

bool DiffLine::PrintEdit(Signal sig, SimpleStream &stream, const DiffLine::Edit &edit)
{
	stream.Println(sig, TextizeUnifiedEdit(edit).c_str());
	return !sig.IsSignalled();
}

//-----------------------------------------------------------------------------
// ResultLine
//-----------------------------------------------------------------------------
void ResultLine::Compose()
{
	_diffLine.init();
	_diffLine.onHuge();
	_diffLine.compose();
}

bool ResultLine::PrintEdit(Signal sig, SimpleStream &stream, size_t idxEdit)
{
	const DiffLine::Edit &edit = _diffLine.GetEditList()[idxEdit];
	return DiffLine::PrintEdit(sig, stream, edit);
}

bool ResultLine::PrintEdits(Signal sig, SimpleStream &stream) const
{
	foreach_const (DiffLine::EditList, pEdit, _diffLine.GetEditList()) {
		if (!DiffLine::PrintEdit(sig, stream, *pEdit)) return false;
	}
	return true;
}

bool ResultLine::PrintHunkLine(Signal sig, SimpleStream &stream,
					   HunkLine::Format format, const HunkLine &hunkLine) const
{
	const DiffLine::EditList &edits = _diffLine.GetEditList();
	DiffLine::EditList::const_iterator pEdit = edits.begin() + hunkLine.idxEditBegin;
	DiffLine::EditList::const_iterator pEditEnd = edits.begin() + hunkLine.idxEditEnd;
	stream.Printf(sig, "@@ %s @@\n", hunkLine.TextizeUnifiedRange().c_str());
	for ( ; pEdit != pEditEnd; pEdit++) {
		if (!DiffLine::PrintEdit(sig, stream, *pEdit)) return false;
	}
	return true;
}

bool ResultLine::PrintHunkLines(Signal sig, SimpleStream &stream,
						HunkLine::Format format, size_t nLinesCommon) const
{
	size_t idxEdit = 0;
	HunkLine hunkLine;
	while (NextHunkLine(&idxEdit, nLinesCommon, &hunkLine)) {
		if (!PrintHunkLine(sig, stream, format, hunkLine)) return false;
	}
	return true;
}

bool ResultLine::NextHunkLine(size_t *pIdxEdit, size_t nLinesCommon, HunkLine *pHunkLine) const
{
	::memset(pHunkLine, 0x00, sizeof(HunkLine));
	size_t idxEdit = *pIdxEdit;
	size_t idxEditTop = idxEdit;
	size_t nEdits = CountEdits();
	if (idxEdit >= nEdits) return false;
	size_t nLines = 0;
	for ( ; idxEdit < nEdits; idxEdit++) {
		const DiffLine::Edit &edit = GetEdit(idxEdit);
		if (edit.second.type == dtl::SES_COMMON) continue;
		pHunkLine->idxEditBegin = (idxEdit > idxEditTop + nLinesCommon)?
			idxEdit - nLinesCommon : idxEditTop;
		idxEdit++;
		for ( ; idxEdit < nEdits; idxEdit++) {
			const DiffLine::Edit &edit = GetEdit(idxEdit);
			if (edit.second.type == dtl::SES_COMMON) {
				nLines++;
				if (nLines >= nLinesCommon * 2) {
					idxEdit = idxEdit + 1 - nLinesCommon;
					break;
				}
			} else {
				nLines = 0;
			}
		}
		*pIdxEdit = idxEdit;
		pHunkLine->idxEditEnd = idxEdit;
		for (size_t idxEdit = pHunkLine->idxEditBegin; idxEdit < pHunkLine->idxEditEnd; idxEdit++) {
			const DiffLine::Edit &edit = GetEdit(idxEdit);
			if (edit.second.beforeIdx > 0) {
				pHunkLine->linenoOrg = edit.second.beforeIdx;
				break;
			}
		}
		for (size_t idxEdit = pHunkLine->idxEditBegin; idxEdit < pHunkLine->idxEditEnd; idxEdit++) {
			const DiffLine::Edit &edit = GetEdit(idxEdit);
			if (edit.second.afterIdx > 0) {
				pHunkLine->linenoNew = edit.second.afterIdx;
				break;
			}
		}
		do {
			const DiffLine::Edit &edit = GetEdit(pHunkLine->idxEditBegin);
			if (pHunkLine->linenoOrg == 0 && pHunkLine->idxEditBegin > 0) {
				const DiffLine::Edit &edit = GetEdit(pHunkLine->idxEditBegin - 1);
				pHunkLine->linenoOrg = edit.second.beforeIdx;
			}
			if (pHunkLine->linenoNew == 0 && pHunkLine->idxEditBegin > 0) {
				const DiffLine::Edit &edit = GetEdit(pHunkLine->idxEditBegin - 1);
				pHunkLine->linenoNew = edit.second.afterIdx;
			}
		} while (0);
		for (size_t idxEdit = pHunkLine->idxEditBegin; idxEdit < pHunkLine->idxEditEnd; idxEdit++) {
			const DiffLine::Edit &edit = GetEdit(idxEdit);
			if (edit.second.type != dtl::SES_ADD) pHunkLine->nLinesOrg++;
			if (edit.second.type != dtl::SES_DELETE) pHunkLine->nLinesNew++;
		}
		return true;
	}
	*pIdxEdit = idxEdit;
	return false;
}

//-----------------------------------------------------------------------------
// Object_result
//-----------------------------------------------------------------------------
Object *Object_result::Clone() const
{
	return NULL;
}

bool Object_result::DoDirProp(Environment &env, Signal sig, SymbolSet &symbols)
{
	if (!Object::DoDirProp(env, sig, symbols)) return false;
	symbols.insert(Gura_UserSymbol(distance));
	symbols.insert(Gura_UserSymbol(nlines_at_org));
	symbols.insert(Gura_UserSymbol(nlines_at_new));
	return true;
}

Value Object_result::DoGetProp(Environment &env, Signal sig, const Symbol *pSymbol,
								const SymbolSet &attrs, bool &evaluatedFlag)
{
	evaluatedFlag = true;
	if (pSymbol->IsIdentical(Gura_UserSymbol(distance))) {
		return Value(_pResultLine->GetEditDistance());
	} else if (pSymbol->IsIdentical(Gura_UserSymbol(nlines_at_org))) {
		return Value(_pResultLine->GetSeq(0).size());
	} else if (pSymbol->IsIdentical(Gura_UserSymbol(nlines_at_new))) {
		return Value(_pResultLine->GetSeq(1).size());
	}
	evaluatedFlag = false;
	return Value::Null;
}

String Object_result::ToString(bool exprFlag)
{
	char buff[80];
	String str;
	str += "<diff.result:";
	::sprintf(buff, "dist=%lld", _pResultLine->GetEditDistance());
	str += buff;
	str += ">";
	return str;
}

//-----------------------------------------------------------------------------
// Methods of diff.result
//-----------------------------------------------------------------------------
// diff.result#eachedit() {block?}
Gura_DeclareMethod(result, eachedit)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
	AddHelp(
		Gura_Symbol(en), Help::FMT_markdown,
		"Creates an iterator that returns `diff.edit` instance stored in the result.\n"
		"\n"
		GURA_HELPTEXT_ITERATOR_en());
}

Gura_ImplementMethod(result, eachedit)
{
	ResultLine *pResultLine = Object_result::GetThisObj(args)->GetResultLine();
	AutoPtr<IteratorEdit> pIterator(new IteratorEdit(pResultLine->Reference()));
	return ReturnIterator(env, sig, args, pIterator.release());
}

// diff.result#eachhunk(lines?:number) {block?}
Gura_DeclareMethod(result, eachhunk)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "lines", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
	AddHelp(
		Gura_Symbol(en), Help::FMT_markdown,
		"Creates an iterator that returns `diff.hunk` instance stored in the result.\n"
		"\n"
		"The argument `lines` specifies a number of common lines appended before and after\n"
		"different lines\n"
		"\n"
		GURA_HELPTEXT_ITERATOR_en());
}

Gura_ImplementMethod(result, eachhunk)
{
	ResultLine *pResultLine = Object_result::GetThisObj(args)->GetResultLine();
	size_t nLinesCommon = args.IsValid(0)? args.GetSizeT(0) : 3;
	AutoPtr<IteratorHunkLine> pIterator(new IteratorHunkLine(pResultLine->Reference(), nLinesCommon));
	return ReturnIterator(env, sig, args, pIterator.release());
}

// diff.result#render(out?:stream:w, format?:symbol, lines?:number)
Gura_DeclareMethodAlias(result, render, "render")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "out", VTYPE_stream, OCCUR_ZeroOrOnce, FLAG_Write);
	DeclareArg(env, "format", VTYPE_symbol, OCCUR_ZeroOrOnce);
	DeclareArg(env, "lines", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
	AddHelp(
		Gura_Symbol(en), Help::FMT_markdown,
		"Renders diff result to the specified stream.\n"
		"\n"
		"If the argument `out` is omitted, this method returns a string of the rendered text.\n"
		"Otherwise, it returns `nil`.\n"
		"\n"
		"The argument `format` takes one of the symbols that specifies the rendering format:\n"
		"\n"
		"- `` `normal`` .. Normal format (not supported yet).\n"
		"- `` `context`` .. Context format (not supported yet).\n"
		"- `` `unified`` .. Unified format. This is the default.\n"
		"\n"
		"The argument `lines` specifies a number of common lines appended before and after\n"
		"different lines\n");
}

Gura_ImplementMethod(result, render)
{
	ResultLine *pResultLine = Object_result::GetThisObj(args)->GetResultLine();
	HunkLine::Format format = HunkLine::FORMAT_Unified;
	if (args.IsValid(1)) {
		format = HunkLine::SymbolToFormat(sig, args.GetSymbol(1));
		if (format == HunkLine::FORMAT_None) return Value::Null;
	}
	size_t nLinesCommon = args.IsValid(2)? args.GetSizeT(2) : 3;
	if (args.IsValid(0)) {
		Stream &streamOut = args.GetStream(0);
		pResultLine->PrintHunkLines(sig, streamOut, format, nLinesCommon);
		return Value::Null;
	} else {
		String strOut;
		SimpleStream_StringWriter streamOut(strOut);
		pResultLine->PrintHunkLines(sig, streamOut, format, nLinesCommon);
		return Value(strOut);
	}
}

//-----------------------------------------------------------------------------
// Class implementation for diff.result
//-----------------------------------------------------------------------------
Gura_ImplementUserClass(result)
{
	Gura_AssignValue(result, Value(Reference()));
	Gura_AssignMethod(result, eachedit);
	Gura_AssignMethod(result, eachhunk);
	Gura_AssignMethod(result, render);
}

//-----------------------------------------------------------------------------
// Object_edit
//-----------------------------------------------------------------------------
Object *Object_edit::Clone() const
{
	return NULL;
}

bool Object_edit::DoDirProp(Environment &env, Signal sig, SymbolSet &symbols)
{
	if (!Object::DoDirProp(env, sig, symbols)) return false;
	symbols.insert(Gura_UserSymbol(type));
	symbols.insert(Gura_UserSymbol(mark));
	symbols.insert(Gura_UserSymbol(lineno_at_org));
	symbols.insert(Gura_UserSymbol(lineno_at_new));
	symbols.insert(Gura_UserSymbol(source));
	symbols.insert(Gura_UserSymbol(unified));
	return true;
}

Value Object_edit::DoGetProp(Environment &env, Signal sig, const Symbol *pSymbol,
								const SymbolSet &attrs, bool &evaluatedFlag)
{
	const DiffLine::Edit &edit = _pResultLine->GetEdit(_idxEdit);
	evaluatedFlag = true;
	if (pSymbol->IsIdentical(Gura_UserSymbol(type))) {
		if (edit.second.type == dtl::SES_ADD) {
			return Value(Gura_UserSymbol(add));
		} else if (edit.second.type == dtl::SES_DELETE) {
			return Value(Gura_UserSymbol(delete));
		} else {
			return Value(Gura_UserSymbol(copy));
		}
	} else if (pSymbol->IsIdentical(Gura_UserSymbol(mark))) {
		return Value(DiffLine::GetEditMark(edit));
	} else if (pSymbol->IsIdentical(Gura_UserSymbol(lineno_at_org))) {
		return Value(edit.second.beforeIdx);
	} else if (pSymbol->IsIdentical(Gura_UserSymbol(lineno_at_new))) {
		return Value(edit.second.afterIdx);
	} else if (pSymbol->IsIdentical(Gura_UserSymbol(source))) {
		return Value(edit.first);
	} else if (pSymbol->IsIdentical(Gura_UserSymbol(unified))) {
		return Value(DiffLine::TextizeUnifiedEdit(edit));
	}
	evaluatedFlag = false;
	return Value::Null;
}

String Object_edit::ToString(bool exprFlag)
{
	const DiffLine::Edit &edit = _pResultLine->GetEdit(_idxEdit);
	String str;
	str += "<diff.edit:";
	if (edit.second.type == dtl::SES_ADD) {
		str += "add";
	} else if (edit.second.type == dtl::SES_DELETE) {
		str += "delete";
	} else {
		str += "copy";
	}
	str += ">";
	return str;
}

//-----------------------------------------------------------------------------
// Methods of diff.edit
//-----------------------------------------------------------------------------
// diff.edit#print(out?:stream:w):void
Gura_DeclareMethod(edit, print)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "out", VTYPE_stream, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
	AddHelp(
		Gura_Symbol(en), Help::FMT_markdown,
		"Prints the content of the `diff.edit` instance to the specified stream.\n");
}

Gura_ImplementMethod(edit, print)
{
	Object_edit *pThis = Object_edit::GetThisObj(args);
	Stream &stream = args.IsValid(0)? args.GetStream(0) : *env.GetConsole();
	pThis->GetResultLine()->PrintEdit(sig, stream, pThis->GetEditIndex());
	return Value::Null;
}

//-----------------------------------------------------------------------------
// Class implementation for diff.edit
//-----------------------------------------------------------------------------
Gura_ImplementUserClass(edit)
{
	Gura_AssignValue(edit, Value(Reference()));
	Gura_AssignMethod(edit, print);
}

//-----------------------------------------------------------------------------
// Object_hunk
//-----------------------------------------------------------------------------
Object *Object_hunk::Clone() const
{
	return NULL;
}

bool Object_hunk::DoDirProp(Environment &env, Signal sig, SymbolSet &symbols)
{
	if (!Object::DoDirProp(env, sig, symbols)) return false;
	symbols.insert(Gura_UserSymbol(edits));
	symbols.insert(Gura_UserSymbol(lineno_at_org));
	symbols.insert(Gura_UserSymbol(lineno_at_new));
	symbols.insert(Gura_UserSymbol(nlines_at_org));
	symbols.insert(Gura_UserSymbol(nlines_at_new));
	return true;
}

Value Object_hunk::DoGetProp(Environment &env, Signal sig, const Symbol *pSymbol,
								const SymbolSet &attrs, bool &evaluatedFlag)
{
	evaluatedFlag = true;
	if (pSymbol->IsIdentical(Gura_UserSymbol(edits))) {
		AutoPtr<Iterator> pIterator(new IteratorEdit(_pResultLine->Reference(), _hunkLine));
		return Value(new Object_iterator(env, pIterator.release()));
	} else if (pSymbol->IsIdentical(Gura_UserSymbol(lineno_at_org))) {
		return Value(_hunkLine.linenoOrg);
	} else if (pSymbol->IsIdentical(Gura_UserSymbol(lineno_at_new))) {
		return Value(_hunkLine.linenoNew);
	} else if (pSymbol->IsIdentical(Gura_UserSymbol(nlines_at_org))) {
		return Value(_hunkLine.nLinesOrg);
	} else if (pSymbol->IsIdentical(Gura_UserSymbol(nlines_at_new))) {
		return Value(_hunkLine.nLinesNew);
	}
	evaluatedFlag = false;
	return Value::Null;
}

String Object_hunk::ToString(bool exprFlag)
{
	char buff[80];
	String str;
	str += "<diff.hunk:";
	str += _hunkLine.TextizeUnifiedRange();
	str += ">";
	return str;
}

//-----------------------------------------------------------------------------
// Methods of diff.hunk
//-----------------------------------------------------------------------------
// diff.hunk#print(out?:stream:w, format?:symbol):void
Gura_DeclareMethod(hunk, print)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "out", VTYPE_stream, OCCUR_ZeroOrOnce);
	DeclareArg(env, "format", VTYPE_symbol, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
	AddHelp(
		Gura_Symbol(en), Help::FMT_markdown,
		"Prints the content of the `diff.hunk` instance to the specified stream.\n"
		"\n"
		"The argument `format` takes one of the symbols that specifies the rendering format:\n"
		"\n"
		"- `` `normal`` .. Normal format (not supported yet).\n"
		"- `` `context`` .. Context format (not supported yet).\n"
		"- `` `unified`` .. Unified format. This is the default.\n");
}

Gura_ImplementMethod(hunk, print)
{
	Object_hunk *pThis = Object_hunk::GetThisObj(args);
	Stream &stream = args.IsValid(0)? args.GetStream(0) : *env.GetConsole();
	HunkLine::Format format = HunkLine::FORMAT_Unified;
	if (args.IsValid(1)) {
		format = HunkLine::SymbolToFormat(sig, args.GetSymbol(1));
		if (format == HunkLine::FORMAT_None) return Value::Null;
	}
	pThis->GetResultLine()->PrintHunkLine(sig, stream, format, pThis->GetHunkLine());
	return Value::Null;
}

//-----------------------------------------------------------------------------
// Class implementation for diff.hunk
//-----------------------------------------------------------------------------
Gura_ImplementUserClass(hunk)
{
	Gura_AssignValue(hunk, Value(Reference()));
	Gura_AssignMethod(hunk, print);
}

//-----------------------------------------------------------------------------
// IteratorEdit
//-----------------------------------------------------------------------------
IteratorEdit::IteratorEdit(ResultLine *pResultLine) :
	Iterator(false), _pResultLine(pResultLine),
	_idxEdit(0), _idxEditBegin(0), _idxEditEnd(pResultLine->CountEdits())
{
}

IteratorEdit::IteratorEdit(ResultLine *pResultLine, const HunkLine &hunkLine) :
	Iterator(false), _pResultLine(pResultLine),
	_idxEdit(hunkLine.idxEditBegin), _idxEditBegin(hunkLine.idxEditBegin), _idxEditEnd(hunkLine.idxEditEnd)
{
}

Iterator *IteratorEdit::GetSource()
{
	return NULL;
}

bool IteratorEdit::DoNext(Environment &env, Signal sig, Value &value)
{
	if (_idxEdit >= _idxEditEnd) return false;
	value = Value(new Object_edit(_pResultLine->Reference(), _idxEdit));
	_idxEdit++;
	return true;
}

String IteratorEdit::ToString() const
{
	String str;
	str += "diff.edit";
	return str;
}

void IteratorEdit::GatherFollower(Environment::Frame *pFrame, EnvironmentSet &envSet)
{
}

//-----------------------------------------------------------------------------
// IteratorHunkLine
//-----------------------------------------------------------------------------
IteratorHunkLine::IteratorHunkLine(ResultLine *pResultLine, size_t nLinesCommon) :
	Iterator(false), _pResultLine(pResultLine), _idxEdit(0), _nLinesCommon(nLinesCommon)
{
}

Iterator *IteratorHunkLine::GetSource()
{
	return NULL;
}

bool IteratorHunkLine::DoNext(Environment &env, Signal sig, Value &value)
{
	HunkLine hunkLine;
	if (_pResultLine->NextHunkLine(&_idxEdit, _nLinesCommon, &hunkLine)) {
		value = Value(new Object_hunk(_pResultLine->Reference(), hunkLine));
		return true;
	}
	return false;
}

String IteratorHunkLine::ToString() const
{
	String str;
	str += "diff.hunk";
	return str;
}

void IteratorHunkLine::GatherFollower(Environment::Frame *pFrame, EnvironmentSet &envSet)
{
}

//-----------------------------------------------------------------------------
// Module functions
//-----------------------------------------------------------------------------
// diff.compose(src1, src2):[icase] {block?}
Gura_DeclareFunction(compose)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "src1", VTYPE_any);
	DeclareArg(env, "src2", VTYPE_any);
	DeclareAttr(Gura_Symbol(icase));
	DeclareBlock(OCCUR_ZeroOrOnce);
	AddHelp(
		Gura_Symbol(en), Help::FMT_markdown,
		"Calculates differences between two sources of strings and returns `diff.result` instance\n"
		"that contains the difference information.\n"
		"\n"
		"You can specify a value of `string`, `stream`, `iterator` or `list`\n"
		"for the argument `src1` and `src2`.\n"
		"In the result, the content of `src1` is referred to as an \"original\" one\n"
		"and that of `src2` as a \"new\" one.\n"
		"\n"
		"Below is an example to compare between two strings:\n"
		"\n"
		"    str1 = '...'\n"
		"    str2 = '...'\n"
		"    result = diff.compose(str1, str2)\n"
		"\n"
		"Below is an example to compare between two files:\n"
		"\n"
		"    file1 = stream('file1.txt')\n"
		"    file2 = stream('file2.txt')\n"
		"    result = diff.compose(file1, file2)\n"
		"\n"
		"Below is an example to compare between two iterators:\n"
		"\n"
		"    chars1 = '...'.each()\n"
		"    chars2 = '...'.each()\n"
		"    result = diff.compose(chars1, chars2)\n"
		"\n"
		"Below is an example to compare between a file and a string:\n"
		"\n"
		"    file = stream('file.txt')\n"
		"    str = '...'\n"
		"    result = diff.compose(file, str)\n"
		"\n"
		"If attribute `:icase` is specified, it wouldn't distinguish\n"
		"upper and lower case of characters.\n");
}

Gura_ImplementFunction(compose)
{
	bool ignoreCaseFlag = args.IsSet(Gura_Symbol(icase));
	AutoPtr<ResultLine> pResultLine(new ResultLine(ignoreCaseFlag));
	for (size_t i = 0; i < 2; i++) {
		if (args.IsType(i, VTYPE_string)) {
			DiffLine::FeedString(pResultLine->GetSeq(i), args.GetString(i));
		} else if (args.IsType(i, VTYPE_stream)) {
			if (!DiffLine::FeedStream(sig, pResultLine->GetSeq(i), args.GetStream(i))) {
				return Value::Null;
			}
		} else if (args.IsType(i, VTYPE_iterator)) {
			AutoPtr<Iterator> pIterator(args.GetIterator(i)->Clone());
			if (!DiffLine::FeedIterator(env, sig, pResultLine->GetSeq(i), pIterator.get())) {
				return Value::Null;
			}				
		} else if (args.IsType(i, VTYPE_list)) {
			DiffLine::FeedList(pResultLine->GetSeq(i), args.GetList(i));
		} else {
			sig.SetError(ERR_TypeError, "difference source must be string or stream");
			return Value::Null;
		}
	}
	pResultLine->Compose();
	return ReturnValue(env, sig, args, Value(new Object_result(pResultLine.release())));
}

//-----------------------------------------------------------------------------
// Module entry
//-----------------------------------------------------------------------------
Gura_ModuleEntry()
{
	// symbol realization
	Gura_RealizeUserSymbol(add);
	Gura_RealizeUserSymbol(context);
	Gura_RealizeUserSymbol(copy);
	Gura_RealizeUserSymbol(delete);
	Gura_RealizeUserSymbol(distance);
	Gura_RealizeUserSymbol(edits);
	Gura_RealizeUserSymbolAlias(lineno_at_org, "lineno@org");
	Gura_RealizeUserSymbolAlias(lineno_at_new, "lineno@new");
	Gura_RealizeUserSymbol(mark);
	Gura_RealizeUserSymbolAlias(nlines_at_org, "nlines@org");
	Gura_RealizeUserSymbolAlias(nlines_at_new, "nlines@new");
	Gura_RealizeUserSymbol(normal);
	Gura_RealizeUserSymbol(source);
	Gura_RealizeUserSymbol(type);
	Gura_RealizeUserSymbol(unified);
	// class realization
	Gura_RealizeUserClass(result, env.LookupClass(VTYPE_object));
	Gura_RealizeUserClass(edit, env.LookupClass(VTYPE_object));
	Gura_RealizeUserClass(hunk, env.LookupClass(VTYPE_object));
	// class preparation
	Gura_PrepareUserClass(result);
	Gura_PrepareUserClass(edit);
	Gura_PrepareUserClass(hunk);
	// function assignment
	Gura_AssignFunction(compose);
	return true;
}

Gura_ModuleTerminate()
{
}

Gura_EndModuleBody(diff, diff)

Gura_RegisterModule(diff)
