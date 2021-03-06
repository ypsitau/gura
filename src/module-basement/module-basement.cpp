﻿//-----------------------------------------------------------------------------
// Gura module: basement
//-----------------------------------------------------------------------------
#include "stdafx.h"
#include <gura.h>

Gura_BeginModuleBody(basement)

#define REPEATER_HELP \
"It returns the last evaluated value in the block as its own result,\n" \
"but, if one of `:list`, `:xlist`, `:set`, `:xset` or `:iter` is specified,\n" \
"it returns a list or evaluated value or an iterator. The rule is as follows:\n" \
"\n" \
"- `:list` .. returns a list of result values\n" \
"- `:xlist` .. returns a list of result values eliminating `nil`\n" \
"- `:set` .. returns a list of unique values of results\n" \
"- `:xset` .. returns a list of unique values of results eliminating `nil`\n" \
"- `:iter` .. returns an iterator that executes the block\n" \
"- `:xiter` .. returns an iterator that executes the block, skipping `nil`\n"

//-----------------------------------------------------------------------------
// Formatting and Printing of Text
//-----------------------------------------------------------------------------
// format(format, value*):map
Gura_DeclareFunction(format)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "format", VTYPE_string);
	DeclareArg(env, "values", VTYPE_any, OCCUR_ZeroOrMore);
	AddHelp(
		Gura_Symbol(en),
		"Converts `values` into string depending on formatter specifications\n"
		"in `format` and returns the result in string.\n"
		"For a detail information about formatter specications,\n"
		"refer to the document of `printf()` function.");
}

Gura_ImplementFunction(format)
{
	Signal &sig = env.GetSignal();
	return Value(Formatter::FormatValueList(sig, arg.GetString(0), arg.GetList(1)));
}

// print(value*):map:void
Gura_DeclareFunction(print)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "values", VTYPE_any, OCCUR_ZeroOrMore);
	AddHelp(
		Gura_Symbol(en),
		"Prints out `values` to standard output."
	);
}

Gura_ImplementFunction(print)
{
	Signal &sig = env.GetSignal();
	Stream *pConsole = env.GetConsole();
	if (pConsole == nullptr) return Value::Nil;
	foreach_const (ValueList, pValue, arg.GetList(0)) {
		pConsole->Print(sig, pValue->ToString(false).c_str());
		if (sig.IsSignalled()) break;
	}
	return Value::Nil;
}

// printf(format, values*):map:void
Gura_DeclareFunction(printf)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "format", VTYPE_string);
	DeclareArg(env, "values", VTYPE_any, OCCUR_ZeroOrMore);
	AddHelp(
		Gura_Symbol(en),
		"Prints out `values` to standard output according to formatter specifiers in `format`.\n"
		"The format specifier has a format of `%[flags][width][.precision]specifier`.\n"
		"\n"
		"The `specifier` takes one of the following characters:\n"
		"\n"
		"- `d`, `i` .. decimal integer number with a sign mark\n"
		"- `u` .. decimal integer number wihout a sign mark\n"
		"- `b` .. binary integer number without a sign mark\n"
		"- `o` .. octal integer number without a sign mark\n"
		"- `x` .. hexadecimal integer number in lower character without a sign mark\n"
		"- `X` .. hexadecimal integer number in upper character without a sign mark\n"
		"- `e` .. floating number in exponential form\n"
		"- `E` .. floating number in exponential form (in upper character)\n"
		"- `f` .. floating number in decimal form\n"
		"- `F` .. floating number in decimal form (in upper character)\n"
		"- `g` .. better form between `e` and `f`\n"
		"- `G` .. better form between `E` and `F`\n"
		"- `s` .. string\n"
		"- `c` .. character\n"
		"\n"
		"The `flags` takes one of the following characters.\n"
		"\n"
		"- `+` .. Appends a character \"`+`\" before a positive number.\n"
		"- `-` .. Adjust a string to left.\n"
		"- `[SPC]` .. Appends a space character before a positive number.\n"
		"- `#` .. Appends a prefix before a numbers \"`0b`\" for a binary,\n"
		"         \"`0`\" for an octal and \"`0x`\" for a hexadecimal number.\n"
		"- `0` .. Fills lacking columns with \"`0`\" instead of space characters.`\n"
		"\n"
		"The `width` is a decimal number that specifies a minimum character.\n"
		"If the width of the corresponding field is less than this number,\n"
		"the lacking part will be filled with space characters or \"`0`\".\n"
		"If the width is equal to or more than this number, there's nothing to be processed.\n"
		"If an asterisk character \"`*`\" is specified for `width`,\n"
		"the minimum character width will be retrieved from the argument list.\n"
		"\n"
		"The `width` it a character width that appears on a console,\n"
		"and it takes into account each character width based on the specification\n"
		"of East Asian Width. This means that a kanji-character occupies two characters in width.\n"
		"\n"
		"The `precision` is a decimal number and has different effects depending on `specifier`.\n"
		"\n"
		"For specifiers that formats integer numbers, it specifies a minimum character width\n"
		"and fills `0` for the lacking column.\n"
		"Format specifiers \"`%03d`\" and \"`%.3d`\" have the same effect.\n"
		"When it works in combination with `width`,\n"
		"`precision` fills `0` in the lacking space before `width` does padding.\n"
		"An example is shown below:\n"
		"\n"
		"    printf('%5.3d', 23) .. prints \"  023\"\n"
		"\n"
		"For specifiers `e`, `f` and `g`, it specifies a digit number after a decimal point.\n"
		"Examples are shown below:\n"
		"\n"
		"    printf('%.3f', 1 / 3) .. prints \"0.333\"\n"
		"    printf('%.5f', 1 / 3) .. prints \"0.33333\"\n"
		"\n"
		"It has no effect with other specifiers.\n");
}

Gura_ImplementFunction(printf)
{
	Signal &sig = env.GetSignal();
	Stream *pConsole = env.GetConsole();
	if (pConsole == nullptr) return Value::Nil;
	pConsole->PrintFmt(sig, arg.GetString(0), arg.GetList(1));
	return Value::Nil;
}

// println(value*):map:void
Gura_DeclareFunction(println)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "values", VTYPE_any, OCCUR_ZeroOrMore);
	AddHelp(
		Gura_Symbol(en),
		"Prints out `values` and an end-of-line character to the standard output.\n");
}

Gura_ImplementFunction(println)
{
	Signal &sig = env.GetSignal();
	Stream *pConsole = env.GetConsole();
	if (pConsole == nullptr) return Value::Nil;
	foreach_const (ValueList, pValue, arg.GetList(0)) {
		pConsole->Print(sig, pValue->ToString(false).c_str());
		if (sig.IsSignalled()) break;
	}
	pConsole->Print(sig, "\n");
	return Value::Nil;
}

//-----------------------------------------------------------------------------
// Repetition
//-----------------------------------------------------------------------------
// cross (`expr+) {block}
Gura_DeclareFunction(cross)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "expr", VTYPE_quote, OCCUR_OnceOrMore);
	DeclareBlock(OCCUR_Once);
	AddHelp(
		Gura_Symbol(en),
		"Executes the `block` while evaluating all the combinations of results from `expr`\n"
		"that has format \"`var in iteratable`\".\n"
		"You can specify one or more such `expr`s as arguments and\n"
		"they are counted up from the one on the right side to the left.\n"
		"\n"
		"Iterators and lists are the most typical iteratables, but even any objects that\n"
		"are cable of generating iterators can be specified as such.\n"
		"\n"
		REPEATER_HELP
		"\n"
		"Block parameter format is `|idx:number, i0:number, i1:number, ..|`\n"
		"where `idx` indicates an index of the whole loop\n"
		"and each of `i0`, `i1` .. indicates an index of each corresponding iterable.\n"
		"\n"
		"Example:\n"
		"\n"
		"    cross (ch in ['A', 'B', 'C'], i in 1..4) {\n"
		"        printf('%s-%d ', ch, i)\n"
		"    }\n"
		"    // prints \"A-1 A-2 A-3 A-4 B-1 B-2 B-3 B-4 C-1 C-2 C-3 C-4 \"\n");
}

Gura_ImplementFunction(cross)
{
	AutoPtr<Environment> pEnvBlock(env.Derive(ENVTYPE_block));
	const Function *pFuncBlock = arg.GetBlockFunc(*pEnvBlock, GetSymbolForBlock());
	if (pFuncBlock == nullptr) return Value::Nil;
	bool skipInvalidFlag = arg.IsResultXList() || arg.IsResultXSet() || arg.IsResultXIterator();
	bool genIterFlag = arg.IsResultIterator() || arg.IsResultXIterator();
	Iterator *pIterator = new Iterator_cross(pEnvBlock->Reference(), Function::Reference(pFuncBlock),
				skipInvalidFlag, genIterFlag, arg.GetList(0));
	return ReturnIterator(env, arg, pIterator);
}

// for (`expr+) {block}
Gura_DeclareFunctionAlias(for_, "for")
{
	DeclareArg(env, "expr", VTYPE_quote, OCCUR_OnceOrMore);
	DeclareBlock(OCCUR_Once);
	AddHelp(
		Gura_Symbol(en),
		"Executes the `block` while evaulating iteration command `expr` that has a format\n"
		"\"`var in iteratable`\".\n"
		"For `var`, an identifier or a list of identifiers is specified.\n"
		"For `iterable`, you can spedify iterators and lists as well as any objects\n"
		"that are cable of generating iterators.\n"
		"\n"
		"You can specify one or more `expr` in the argument list.\n"
		"In such a case, it continues to repeat until the shortest iterable among them\n"
		"reaches at its end.\n"
		"\n"
		REPEATER_HELP
		"\n"
		"Block parameter format is `|idx:number|` where `idx` indicates an index of the loop.\n"
		"\n"
		"Example:\n"
		"\n"
		"    for (ch in ['A', 'B', 'C'], i in 1..4) {\n"
		"        printf('%s-%d ', ch, i)\n"
		"    }\n"
		"    // prints \"A-1 B-2 C-3\"\n");
}

Gura_ImplementFunction(for_)
{
	AutoPtr<Environment> pEnvBlock(env.Derive(ENVTYPE_block));
	const Function *pFuncBlock = arg.GetBlockFunc(*pEnvBlock, GetSymbolForBlock());
	if (pFuncBlock == nullptr) return Value::Nil;
	bool skipInvalidFlag = arg.IsResultXList() || arg.IsResultXSet() || arg.IsResultXIterator();
	bool genIterFlag = arg.IsResultIterator() || arg.IsResultXIterator();
	Iterator *pIterator = new Iterator_for(pEnvBlock->Reference(), Function::Reference(pFuncBlock),
				skipInvalidFlag, genIterFlag, arg.GetList(0));
	return ReturnIterator(env, arg, pIterator);
}

// repeat (n?:number) {block}
Gura_DeclareFunction(repeat)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "n", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_Once);
	AddHelp(
		Gura_Symbol(en),
		"Executes the block for `n` times. If `n` is omitted, it repeats the block\n"
		"execution forever.\n"
		"\n"
		REPEATER_HELP
		"\n"
		"Block parameter format is `|idx:number|` where `idx` indicates an index of the loop.\n");
}

Gura_ImplementFunction(repeat)
{
	AutoPtr<Environment> pEnvBlock(env.Derive(ENVTYPE_block));
	const Function *pFuncBlock = arg.GetBlockFunc(*pEnvBlock, GetSymbolForBlock());
	if (pFuncBlock == nullptr) return Value::Nil;
	bool skipInvalidFlag = arg.IsResultXList() || arg.IsResultXSet() || arg.IsResultXIterator();
	bool genIterFlag = arg.IsResultIterator() || arg.IsResultXIterator();
	Iterator *pIterator = new Iterator_repeat(pEnvBlock->Reference(), Function::Reference(pFuncBlock),
			skipInvalidFlag, genIterFlag, arg.Is_number(0)? arg.GetInt(0) : -1);
	return ReturnIterator(env, arg, pIterator);
}

// while (`cond) {block}
Gura_DeclareFunctionAlias(while_, "while")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "cond", VTYPE_quote);
	DeclareBlock(OCCUR_Once);
	AddHelp(
		Gura_Symbol(en),
		"Executes the block while the evaluation result of `cond` is true.\n"
		"\n"
		REPEATER_HELP
		"\n"
		"Block parameter format is `|idx:number|` where `idx` indicates an index of the loop.\n");
}

Gura_ImplementFunction(while_)
{
	AutoPtr<Environment> pEnvBlock(env.Derive(ENVTYPE_block));
	const Function *pFuncBlock = arg.GetBlockFunc(*pEnvBlock, GetSymbolForBlock());
	if (pFuncBlock == nullptr) return Value::Nil;
	bool skipInvalidFlag = arg.IsResultXList() || arg.IsResultXSet() || arg.IsResultXIterator();
	bool genIterFlag = arg.IsResultIterator() || arg.IsResultXIterator();
	Iterator *pIterator = new Iterator_while(pEnvBlock->Reference(), Function::Reference(pFuncBlock),
			skipInvalidFlag, genIterFlag, Expr::Reference(arg.GetExpr(0)));
	return ReturnIterator(env, arg, pIterator);
}

//-----------------------------------------------------------------------------
// Value Generator
//-----------------------------------------------------------------------------
// consts(value, num?:number) {block?}
Gura_DeclareFunction(consts)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "value", VTYPE_any);
	DeclareArg(env, "num", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
	AddHelp(
		Gura_Symbol(en),
		"Creates an iterator that generates the same value specified by the argument `value`.\n"
		"\n"
		"The argument `num` specifies the number of elements to be generated.\n"
		"If omitted, it would generate the value infinitely.\n"
		"\n"
		GURA_HELPTEXT_ITERATOR_en()
		"\n"
		"Below is an example to create an iterator that returns constant values:\n"
		"\n"
		"    x = consts('hello', 10)\n"
		"    // x generates 'hello' for 10 times\n");
}

Gura_ImplementFunction(consts)
{
	Iterator *pIterator = nullptr;
	if (arg.Is_number(1)) {
		pIterator = new Iterator_ConstantN(arg.GetValue(0), arg.GetInt(1));
	} else {
		pIterator = new Iterator_Constant(arg.GetValue(0));
	}
	return ReturnIterator(env, arg, pIterator);
}

// dim(n+:number) {block?}
Gura_DeclareFunction(dim)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "n", VTYPE_number, OCCUR_OnceOrMore);
	DeclareBlock(OCCUR_ZeroOrOnce);
	AddHelp(
		Gura_Symbol(en),
		"Returns a list that contains `n` values of `nil`.\n"
		"If you pass multiple numbers for `n`, it would create a nested list.\n"
		"\n"
		"Below is an example to create a one-dimentional list:\n"
		"\n"
		"    x = dim(3)\n"
		"    // x is [nil, nil, nil]\n"
		"\n"
		"Below is an example to create a two-dimentional list:\n"
		"\n"
		"    x = dim(3, 2)\n"
		"    // x is [[nil, nil], [nil, nil], [nil, nil]]\n"
		"\n"
		"The optional `block` should return values for each element\n"
		"and takes block parameters: `|i0:number, i1:number, ..|`\n"
		"where the arguments `i0` and `i1` take indices of the loops.\n"
		"\n"
		"Below is an example to create a one-dimentional list containing a string:\n"
		"\n"
		"    x = dim(3) {'Hi'}\n"
		"    // x is ['Hi', 'Hi', 'Hi']\n"
		"\n"
		"Below is an example to create a two-dimentional list that consists of strings\n"
		"showing indices.\n"
		"\n"
		"    x = dim(3, 2) {|i, j| format('%d-%d', i, j) }\n"
		"    // x is [['0-0', '0-1'], ['1-0', '1-1'], ['2-0', '2-1']]\n");
}

bool Func_dim_Sub(Environment &env, const Function *pFuncBlock, ValueList &valListParent,
	IntList &cntList, IntList::iterator pCnt, IntList &idxList, IntList::iterator pIdx)
{
	Signal &sig = env.GetSignal();
	if (pCnt + 1 == cntList.end()) {
		if (pFuncBlock == nullptr) {
			for (*pIdx = 0; *pIdx < *pCnt; (*pIdx)++) {
				valListParent.push_back(Value::Nil);
			}
		} else {
			for (*pIdx = 0; *pIdx < *pCnt; (*pIdx)++) {
				AutoPtr<Argument> pArg(new Argument(pFuncBlock));
				foreach (IntList, pIdxWk, idxList) {
					if (!pArg->StoreValue(env, Value(*pIdxWk))) return false;
				}
				Value result = pFuncBlock->Eval(env, *pArg);
				if (sig.IsSignalled()) return false;
				valListParent.push_back(result);
			}
		}
	} else {
		for (*pIdx = 0; *pIdx < *pCnt; (*pIdx)++) {
			Value result;
			Object_list *pObjList = result.InitAsList(env);
			valListParent.push_back(result);
			if (!Func_dim_Sub(env, pFuncBlock, pObjList->GetListForModify(),
									cntList, pCnt + 1, idxList, pIdx + 1)) {
				return false;
			}
			pObjList->DetermineValueType();
		}
	}
	return true;
}

Gura_ImplementFunction(dim)
{
	AutoPtr<Environment> pEnvBlock(env.Derive(ENVTYPE_block));
	const Function *pFuncBlock = arg.GetBlockFunc(*pEnvBlock, GetSymbolForBlock());
	const ValueList &valListArg = arg.GetList(0);
	size_t nArgs = valListArg.size();
	IntList cntList, idxList;
	cntList.reserve(nArgs);
	idxList.reserve(nArgs);
	foreach_const (ValueList, pValArg, valListArg) {
		cntList.push_back(pValArg->GetInt());
		idxList.push_back(0);
	}
	Value result;
	Object_list *pObjList = result.InitAsList(env);
	if (!Func_dim_Sub(*pEnvBlock, pFuncBlock, pObjList->GetListForModify(),
						cntList, cntList.begin(), idxList, idxList.begin())) {
		return Value::Nil;
	}
	pObjList->DetermineValueType();
	return result;
}

// interval(begin:number, end:number, samples:number):map:[open,open_l,open_r] {block?}
Gura_DeclareFunction(interval)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "begin", VTYPE_number);
	DeclareArg(env, "end", VTYPE_number);
	DeclareArg(env, "samples", VTYPE_number);
	DeclareAttr(Gura_Symbol(open));
	DeclareAttr(Gura_Symbol(open_l));
	DeclareAttr(Gura_Symbol(open_r));
	DeclareBlock(OCCUR_ZeroOrOnce);
	AddHelp(
		Gura_Symbol(en),
		"Creates an iterator that generates a sequence of numbers\n"
		"by specifying the beginning and ending numbers, and the number of samples between them.\n"
		
		"\n"
		"In default, it creates a sequence that contains the beginning and ending numbers.\n"
		"Following attributes would generate the following numbers:\n"
		"\n"
		"- `:open` .. Numbers in range of `(begin, end)` that doesn't contain either `begin` or `end`.\n"
		"- `:open_l` .. Numbers in range of `(begin, end]` that doesn't contain `begin`.\n"
		"- `:open_r` .. Numbers in range of `[begin, end)` that doesn't contain `end`.\n");
}

Gura_ImplementFunction(interval)
{
	Signal &sig = env.GetSignal();
	Number numBegin = arg.GetNumber(0);
	Number numEnd = arg.GetNumber(1);
	int numSamples = arg.GetInt(2);
	if (numSamples <= 1) {
		sig.SetError(ERR_ValueError, "samples must be more than one");
		return Value::Nil;
	}
	bool openFlag = arg.IsSet(Gura_Symbol(open));
	bool openLeftFlag = arg.IsSet(Gura_Symbol(open_l));
	bool openRightFlag = arg.IsSet(Gura_Symbol(open_r));
	int iFactor = 0;
	Number numDenom = numSamples - 1;
	if (openFlag || (openLeftFlag && openRightFlag)) {
		numDenom = numSamples + 1;
		iFactor = 1;
	} else if (openLeftFlag) {
		numDenom = numSamples;
		iFactor = 1;
	} else if (openRightFlag) {
		numDenom = numSamples;
		iFactor = 0;
	}
	Iterator *pIterator =
		new Iterator_Interval(numBegin, numEnd, numSamples, numDenom, iFactor);
	return ReturnIterator(env, arg, pIterator);
}

// range(num:number, num_end?:number, step?:number):map {block?}
Gura_DeclareFunction(range)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "num",		VTYPE_number);
	DeclareArg(env, "num_end",	VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareArg(env, "step",		VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
	AddHelp(
		Gura_Symbol(en),
		"Creates an iterator that generates a sequence of integer numbers.\n"
		"\n"
		"This function can be called in three formats that generate following numbers:\n"
		"\n"
		"- `range(num)` .. Numbers between `0` and `(num - 1)`.\n"
		"- `range(num, num_end)` .. Numbers between `num` and `(num_end - 1)`.\n"
		"- `range(num, num_end, step)` .. Numbers between `num` and `(num_end - 1)`\n"
		"  incremented by `step`.\n"
		"\n"
		GURA_HELPTEXT_ITERATOR_en()
		"\n"
		"Below are examples:\n"
		"\n"
		"    x = range(10)\n"
		"    // x generates 0, 1, 2, 3, 4, 5, 6, 7, 8, 9\n"
		"    \n"
		"    x = range(3, 10)\n"
		"    // x generates 3, 4, 5, 6, 7, 8, 9\n"
		"    \n"
		"    x = range(3, 10, 2)\n"
		"    // x generates 3, 5, 7, 9\n"
		);
}

Gura_ImplementFunction(range)
{
	Signal &sig = env.GetSignal();
	AutoPtr<Iterator> pIterator;
	Number numBegin = 0.;
	Number numEnd = 0.;
	Number numStep = 1.;
	if (arg.IsInvalid(1)) {
		if (arg.IsValid(2)) {
			numBegin = arg.GetNumber(0);
			numStep = arg.GetNumber(2);
			if (numStep == 0.) {
				sig.SetError(ERR_ValueError, "step cannot be specified as zero");
				return Value::Nil;
			}
			pIterator.reset(new Iterator_SequenceInf(numBegin, numStep));
		} else {
			numEnd = arg.GetNumber(0);
			if (numBegin > numEnd) numStep = -1.;
			pIterator.reset(new Iterator_Range(numBegin, numEnd, numStep));
		}
	} else if (arg.IsInvalid(2)) {
		numBegin = arg.GetNumber(0);
		numEnd = arg.GetNumber(1);
		if (numBegin > numEnd) numStep = -1.;
		pIterator.reset(new Iterator_Range(numBegin, numEnd, numStep));
	} else {
		numBegin = arg.GetNumber(0);
		numEnd = arg.GetNumber(1);
		numStep = arg.GetNumber(2);
		if (numStep == 0.) {
			sig.SetError(ERR_ValueError, "step cannot be specified as zero");
			return Value::Nil;
		}
		if (numBegin < numEnd && numStep < 0) {
			sig.SetError(ERR_ValueError, "step value must be positive");
			return Value::Nil;
		}
		if (numBegin > numEnd && numStep > 0) {
			sig.SetError(ERR_ValueError, "step value must be negative");
			return Value::Nil;
		}
		pIterator.reset(new Iterator_Range(numBegin, numEnd, numStep));
	}
	return ReturnIterator(env, arg, pIterator.release());
}

//-----------------------------------------------------------------------------
// Flow Control
//-----------------------------------------------------------------------------
// break(value?):void:symbol_func
Gura_DeclareFunctionAlias(break_, "break")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_SymbolFunc);
	DeclareArg(env, "value", VTYPE_any, OCCUR_ZeroOrOnce);
	AddHelp(
		Gura_Symbol(en),
		"Exits from an inside of a loop that is formed with repeating functions like\n"
		"`repeat()`, `while()`, `for()` and `cross(),`\n"
		"as well as other functions generating an iterator.\n"
		"\n"
		"After this function is called,\n"
		"the current loop value would be set to `value` given in the function's argument.\n"
		"If the argument is omitted, that would be set to `nil`.\n"
		"\n"
		"However, when the loop function is called with one of the attributes,\n"
		"`:list`, `:xlist`, `:set`, `:xset`, `:iter` and `:xiter`,\n"
		"the argument value of `break()` is NOT included as an element in the list or iterator.");
}

Gura_ImplementFunction(break_)
{
	Signal &sig = env.GetSignal();
	sig.SetSignal(SIGTYPE_Break, arg.GetValue(0));
	return Value::Nil;
}

// continue(value?):void:symbol_func
Gura_DeclareFunctionAlias(continue_, "continue")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_SymbolFunc);
	DeclareArg(env, "value", VTYPE_any, OCCUR_ZeroOrOnce);
	AddHelp(
		Gura_Symbol(en),
		"Cancels the current turn of a loop and continues on to the next.\n"
		"This function can be used in a loop that is formed with repeating functions like\n"
		"`repeat()`, `while()`, `for()` and `cross()`,\n"
		"as well as other functions generating an iterator.\n"
		"\n"
		"After this function is called,\n"
		"the current loop value would be set to `value` given in the function's argument.\n"
		"If the argument is omitted, that would be set to `nil`.\n"
		"\n"
		"If the loop function is specified with one of the attributes\n"
		"`:list`, `:xlist`, `:set`, `:xset`, `:iter` and `:xiter`,\n"
		"the argument value of `continue()` is included as an element in the list or iterator.");
}

Gura_ImplementFunction(continue_)
{
	Signal &sig = env.GetSignal();
	sig.SetSignal(SIGTYPE_Continue, arg.GetValue(0));
	return Value::Nil;
}

// return(value?):void:symbol_func
Gura_DeclareFunctionAlias(return_, "return")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_SymbolFunc);
	DeclareArg(env, "value", VTYPE_any, OCCUR_ZeroOrOnce);
	AddHelp(
		Gura_Symbol(en),
		"Skips the remaining procedure of the current function\n"
		"and returns to the context that calls it.\n"
		"\n"
		"If it takes an argument, the value is treated as a result of the function.\n"
		"Otherwise, the returned value would be `nil`.");
}

Gura_ImplementFunction(return_)
{
	Signal &sig = env.GetSignal();
	sig.SetSignal(SIGTYPE_Return, arg.GetValue(0));
	return Value::Nil;
}

//-----------------------------------------------------------------------------
// Branch Sequence
//-----------------------------------------------------------------------------
// if (`cond):leader {block}
Gura_DeclareStatementAlias_CustomBegin(if_, "if")
	typedef std::pair<const Expr *, const Expr *> ExprPair;
	typedef std::vector<ExprPair> ExprPairList;
	ExprPairList _exprPairsIf;
	const Expr *_pExprElse;
	inline Expr_Statement(Expr *pExprCar, Expr_Lister *pExprLister, Expr_Block *pExprBlock) :
		Expr_Caller(pExprCar, pExprLister, pExprBlock, FLAG_Leader), _pExprElse(nullptr) {}
	inline Expr_Statement(const Expr_Statement &expr) :
		Expr_Caller(expr), _exprPairsIf(expr._exprPairsIf), _pExprElse(expr._pExprElse) {}
Gura_DeclareStatementAlias_CustomEnd(if_, "if")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Leader);
	DeclareArg(env, "cond", VTYPE_quote);
	DeclareBlock(OCCUR_Once);
	AddHelp(
		Gura_Symbol(en),
		"Specify an \"if\" block within a statement of `if-elsif-else`.\n"
		"\n"
		"If the evaluation result of `cond` is determined as true, the block would be executed,\n"
		"and its evaluation result would become the returned value of the function.\n"
		"\n"
		"Otherwise, if the function is followed by a trailer `elsif` or `else`, that would be evaluated.\n"
		"If no trailer exists, the function returns `nil` value.\n");
}

Gura_ImplementStatement(if_)
{
	AutoPtr<Environment> pEnvBlock(env.Derive(ENVTYPE_block));
#if 1
	for (const Expr_Caller *pExpr = this; pExpr != nullptr; pExpr = pExpr->GetTrailer()) {
		const Symbol *pSymbolCar = pExpr->GetSymbolCar();
		if (pSymbolCar->IsIdentical(Gura_Symbol(else_))) {
			return pExpr->GetBlock()->Exec(*pEnvBlock);
		} else { // 'if' or 'elsif'
			const Expr *pExprCond = pExpr->GetExprOwner().front();
			Value rtn = pExprCond->Exec(*pEnvBlock);
			if (env.IsSignalled()) return Value::Nil;
			if (rtn.GetBoolean()) return pExpr->GetBlock()->Exec(*pEnvBlock);
		}
	}
#else
	foreach_const (ExprPairList, pExprPairIf, _exprPairsIf) {
		const Expr *pExprCond = pExprPairIf->first;
		const Expr *pExprBlock = pExprPairIf->second;
		Value rtn = pExprCond->Exec(*pEnvBlock);
		if (env.IsSignalled()) return Value::Nil;
		if (rtn.GetBoolean()) return pExprBlock->Exec(*pEnvBlock);
	}
	if (_pExprElse != nullptr) return _pExprElse->Exec(*pEnvBlock);
#endif
	return Value::Nil;
}

Gura_ImplementStatementPreparator(if_)
{
	if (_pExprLister.IsNull() || _pExprLister->GetExprOwner().empty()) {
		env.SetError(ERR_SyntaxError, "missing condition");
		return false;
	}
	if (_pExprLister->GetExprOwner().size() > 1) {
		env.SetError(ERR_SyntaxError, "too many conditions");
		return false;
	}
	if (_pExprBlock.IsNull()) {
		env.SetError(ERR_SyntaxError, "missing block");
		return false;
	}
	_exprPairsIf.push_back(ExprPair(GetExprOwner().front(), GetBlock()));
	for (Expr_Caller *pExpr = GetTrailer(); pExpr != nullptr; pExpr = pExpr->GetTrailer()) {
		const Symbol *pSymbolCar = pExpr->GetSymbolCar();
		if (pSymbolCar->IsIdentical(Gura_Symbol(elsif))) {
			if (!pExpr->DoPrepare(env)) return false;
			_exprPairsIf.push_back(ExprPair(pExpr->GetExprOwner().front(), pExpr->GetBlock()));
		} else if (pSymbolCar->IsIdentical(Gura_Symbol(else_))) {
			if (!pExpr->DoPrepare(env)) return false;
			if (pExpr->GetTrailer() != nullptr) {
				env.SetError(ERR_SyntaxError, "trailer after else would never be evaluated");
				return false;
			}
			_pExprElse = pExpr->GetBlock();
		} else {
			env.SetError(ERR_SyntaxError, "invalid trailer for if-elsif-else statement");
			return false;
		}
	}
	return true;
}

// elsif (`cond):leader:trailer {block}
Gura_DeclareStatementAlias(elsif_, "elsif", FLAG_Leader | FLAG_Trailer)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Leader | FLAG_Trailer);
	DeclareArg(env, "cond", VTYPE_quote);
	DeclareBlock(OCCUR_Once);
	AddHelp(
		Gura_Symbol(en),
		"Specify an \"elsif\" block within a statement of `if-elsif-else`.\n"
		"\n"
		"If the evaluation result of `cond` is determined as true, the block would be executed,\n"
		"and its evaluation result would become the returned value of the function.\n"
		"\n"
		"Otherwise, if the function is followed by a trailer `elsif` or `else`, that would be evaluated.\n"
		"If no trailer exists, the function returns `nil` value.\n");
}

Gura_ImplementStatement(elsif_)
{
	// dummy
	return Value::Nil;
}

Gura_ImplementStatementPreparator(elsif_)
{
	if (_pExprLister.IsNull() || _pExprLister->GetExprOwner().empty()) {
		env.SetError(ERR_SyntaxError, "missing condition");
		return false;
	}
	if (_pExprLister->GetExprOwner().size() > 1) {
		env.SetError(ERR_SyntaxError, "too many conditions");
		return false;
	}
	if (_pExprBlock.IsNull()) {
		env.SetError(ERR_SyntaxError, "missing block");
		return false;
	}
	return true;
}

// else ():trailer {block}
Gura_DeclareStatementAlias(else_, "else", FLAG_Trailer)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Trailer);
	DeclareBlock(OCCUR_Once);
	AddHelp(
		Gura_Symbol(en),
		"Specify an \"else\" block within a statement of `if-elsif-else` or `try-catch-else-finally`.\n");
}

Gura_ImplementStatement(else_)
{
	// dummy
	return Value::Nil;
}

Gura_ImplementStatementPreparator(else_)
{
	if (!_pExprLister.IsNull() && !_pExprLister->GetExprOwner().empty()) {
		env.SetError(ERR_SyntaxError, "no arguments necessary");
		return false;
	}
	if (_pExprBlock.IsNull()) {
		env.SetError(ERR_SyntaxError, "missing block");
		return false;
	}
	return true;
}

// end (dummy*):void:symbol_func:trailer:end_marker
Gura_DeclareStatement(end, FLAG_Trailer)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_SymbolFunc | FLAG_Trailer | FLAG_EndMarker);
	DeclareArg(env, "dummy", VTYPE_any, OCCUR_ZeroOrMore);
	AddHelp(
		Gura_Symbol(en),
		"Specify an end of a sequence.\n"
		"\n"
		"This function is supposed to be used as a block terminator\n"
		"in an embedded script of a template.\n");
}

Gura_ImplementStatement(end)
{
	return Value::Nil;
}

Gura_ImplementStatementPreparator(end)
{
	return true;
}

// switch {block}
Gura_DeclareFunctionAlias(switch_, "switch")
{
	DeclareBlock(OCCUR_Once);
	AddHelp(
		Gura_Symbol(en),
		"Form a switch block that contains `case()` and `default()` function calls.\n"
		"It calls these functions sequentially and exits the execution\n"
		"when one of the conditions is evaluated as true.");
}

Gura_ImplementFunction(switch_)
{
	Signal &sig = env.GetSignal();
	AutoPtr<Environment> pEnvBlock(env.Derive(ENVTYPE_block));;
	const Expr_Block *pExprBlock = arg.GetBlockCooked(*pEnvBlock);
	if (sig.IsSignalled()) return Value::Nil;
	pExprBlock->Exec(*pEnvBlock);
	if (sig.IsSwitchDone()) {
		Value result = sig.GetValue();
		sig.ClearSignal();
		return result;
	}
	return Value::Nil;
}

// case (`cond) {block}
Gura_DeclareFunctionAlias(case_, "case")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "cond", VTYPE_quote);
	DeclareBlock(OCCUR_Once);
	AddHelp(
		Gura_Symbol(en),
		"Specify an case block within a switch block.\n"
		"After evaluating an expr object cond, the block shall be executed\n"
		"if it has a value of true.");
}

Gura_ImplementFunction(case_)
{
	Signal &sig = env.GetSignal();
	AutoPtr<Environment> pEnvBlock(env.Derive(ENVTYPE_block));
	Value value = arg.GetExpr(0)->Exec(*pEnvBlock);
	if (value.GetBoolean()) {
		const Expr_Block *pExprBlock = arg.GetBlockCooked(*pEnvBlock);
		if (sig.IsSignalled()) return Value::Nil;
		Value result = pExprBlock->Exec(*pEnvBlock);
		if (sig.IsSignalled()) return Value::Nil;
		sig.SetSignal(SIGTYPE_SwitchDone, result);
		return result;
	}
	return Value::Nil;
}

// default {block}
Gura_DeclareFunctionAlias(default_, "default")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_Once);
	AddHelp(
		Gura_Symbol(en),
		"Specify a default block within a switch block.\n"
		"If all the preceding condition of case block are not evaluated as true,\n"
		"this block shall be executed.\n");
}

Gura_ImplementFunction(default_)
{
	Signal &sig = env.GetSignal();
	AutoPtr<Environment> pEnvBlock(env.Derive(ENVTYPE_block));
	const Expr_Block *pExprBlock = arg.GetBlockCooked(*pEnvBlock);
	if (sig.IsSignalled()) return Value::Nil;
	Value result = pExprBlock->Exec(*pEnvBlock);
	if (sig.IsSignalled()) return Value::Nil;
	sig.SetSignal(SIGTYPE_SwitchDone, result);
	return result;
}

//-----------------------------------------------------------------------------
// Exception Handling
//-----------------------------------------------------------------------------
// try ():leader {block}
Gura_DeclareStatementAlias(try_, "try", FLAG_Leader)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Leader);
	DeclareBlock(OCCUR_Once);
	AddHelp(
		Gura_Symbol(en),
		"Specify a try block of a statement of try-catch-else-finally.\n"
		"It catches signals that occur in the block and executes a corresponding\n"
		"`catch()` or `else()` function that follow after it.");
}

Gura_ImplementStatement(try_)
{
	Signal &sig = env.GetSignal();
	AutoPtr<Environment> pEnvBlock(env.Derive(ENVTYPE_block));
	Value result = GetBlock()->Exec(*pEnvBlock);
	const Expr_Caller *pExpr = GetTrailer();
	if (sig.IsError()) {
		// evaluate catch() statement
		sig.SuspendError();
		for ( ; pExpr != nullptr; pExpr = pExpr->GetTrailer()) {
			const Symbol *pSymbolCar = pExpr->GetSymbolCar();
			if (!pSymbolCar->IsIdentical(Gura_Symbol(catch_))) continue;
			bool handleFlag = true;
			if (!pExpr->GetExprOwner().empty()) {
				handleFlag = false;
				foreach_const (ExprOwner, ppExprArg, pExpr->GetExprOwner()) {
					const Expr *pExprArg = *ppExprArg;
					Value valueArg = pExprArg->Exec(*pEnvBlock);
					if (sig.IsError()) return Value::Nil;
					if (!valueArg.Is_error()) {
						sig.SetError(ERR_TypeError, "error object must be specified");
						return Value::Nil;
					}
					if (valueArg.GetErrorType() == sig.GetError().GetType()) {
						handleFlag = true;
						break;
					}
				}
			}
			if (!handleFlag) continue;
			AutoPtr<Object_error> pObj(new Object_error(env, sig.GetError()));
			sig.ClearSignal(); // clear even the suspended state
			AutoPtr<Function> pFuncBlock(
				FunctionCustom::CreateBlockFunc(
					env, Gura_Symbol(block), pExpr->GetBlock(), FUNCTYPE_Block));
			if (pFuncBlock.IsNull()) return Value::Nil;
			AutoPtr<Argument> pArgSub(new Argument(pFuncBlock.get()));
			if (!pArgSub->StoreValue(env, Value(pObj.release()))) return Value::Nil;
			result = pFuncBlock->Eval(*pEnvBlock, *pArgSub);
			break;
		}
		if (pExpr == nullptr) {
			sig.ResumeError();
			return Value::Nil;
		}
	} else {
		// evaluate else() statement
		for ( ; pExpr != nullptr; pExpr = pExpr->GetTrailer()) {
			const Symbol *pSymbolCar = pExpr->GetSymbolCar();
			if (pSymbolCar->IsIdentical(Gura_Symbol(else_))) {
				result = pExpr->GetBlock()->Exec(*pEnvBlock);
				break;
			}
		}
	}
	if (sig.IsError()) return Value::Nil;
	// evaluate finally() statement
	ULong sigType = sig.GetType();
	Value valueSig = sig.GetValue();
	sig.ClearSignal();
	for ( ; pExpr != nullptr; pExpr = pExpr->GetTrailer()) {
		const Symbol *pSymbolCar = pExpr->GetSymbolCar();
		if (pSymbolCar->IsIdentical(Gura_Symbol(finally))) {
			pExpr->GetBlock()->Exec(*pEnvBlock);
			break;
		}
	}
	sig.SetSignal(sigType, valueSig);
	return result;
}

Gura_ImplementStatementPreparator(try_)
{
	if (!_pExprLister.IsNull() && !_pExprLister->GetExprOwner().empty()) {
		env.SetError(ERR_SyntaxError, "no arguments necessary");
		return false;
	}
	if (_pExprBlock.IsNull()) {
		env.SetError(ERR_SyntaxError, "missing block");
		return false;
	}
	for (Expr_Caller *pExpr = GetTrailer(); pExpr != nullptr; pExpr = pExpr->GetTrailer()) {
		const Symbol *pSymbolCar = pExpr->GetSymbolCar();
		if (pSymbolCar->IsIdentical(Gura_Symbol(catch_))) {
			// nothing to do
		} else if (pSymbolCar->IsIdentical(Gura_Symbol(else_))) {
			// nothing to do
		} else if (pSymbolCar->IsIdentical(Gura_Symbol(finally))) {
			if (pExpr->GetTrailer() != nullptr) {
				env.SetError(ERR_SyntaxError,
							 "trailer after finally would never be evaluated");
				return false;
			}
		} else {
			env.SetError(ERR_SyntaxError, "invalid trailer for try-catch-else-finally statement");
			return false;
		}
		if (!pExpr->DoPrepare(env)) return false;
	}
	return true;
}

// catch (errors*:error):leader:trailer {block}
Gura_DeclareStatementAlias(catch_, "catch", FLAG_Leader | FLAG_Trailer)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Leader | FLAG_Trailer);
	DeclareArg(env, "errors", VTYPE_error, OCCUR_ZeroOrMore);
	DeclareBlock(OCCUR_Once);
	AddHelp(
		Gura_Symbol(en),
		"Specify an catch block of a statement of try-catch-else-finally.\n"
		"It can take multiple numbers of arguments of error objects to handle.\n"
		"If there's no error objects specified, it handles all the errors that are\n"
		"not handled in the preceding `catch()` function calls.\n"
		"Block parameter format: `|error:error|`\n"
		"`error` is an error object that contains information of the handled error.");
}

Gura_ImplementStatement(catch_)
{
	// dummy
	return Value::Nil;
}

Gura_ImplementStatementPreparator(catch_)
{
	if (_pExprBlock.IsNull()) {
		env.SetError(ERR_SyntaxError, "missing block");
		return false;
	}
	return true;
}

// finally ():trailer:finalizer {block}
Gura_DeclareStatementAlias(finally_, "finally", FLAG_Trailer)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Trailer | FLAG_Finalizer);
	DeclareBlock(OCCUR_Once);
	AddHelp(
		Gura_Symbol(en),
		"");
}

Gura_ImplementStatement(finally_)
{
	// dummy
	return Value::Nil;
}

Gura_ImplementStatementPreparator(finally_)
{
	if (!_pExprLister.IsNull() && !_pExprLister->GetExprOwner().empty()) {
		env.SetError(ERR_SyntaxError, "no arguments necessary");
		return false;
	}
	if (_pExprBlock.IsNull()) {
		env.SetError(ERR_SyntaxError, "missing block");
		return false;
	}
	return true;
}

// raise(error:error, msg:string => "error", value?)
Gura_DeclareFunction(raise)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "error", VTYPE_error);
	DeclareArg(env, "msg", VTYPE_string, OCCUR_Once, FLAG_None, 0, new Expr_Value(Value("error")));
	DeclareArg(env, "value", VTYPE_any, OCCUR_ZeroOrOnce);
	AddHelp(
		Gura_Symbol(en),
		"Raises an error signal with a specified error object, a message string and\n"
		"an additional value.");
}

Gura_ImplementFunction(raise)
{
	Signal &sig = env.GetSignal();
	sig.SetError(arg.GetErrorType(0), "%s", arg.GetString(1));
	sig.SetValue(arg.GetValue(2));
	return Value::Nil;
}

//-----------------------------------------------------------------------------
// Data Converter
//-----------------------------------------------------------------------------
// chr(code:number):map
Gura_DeclareFunction(chr)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "code", VTYPE_number);
	AddHelp(
		Gura_Symbol(en),
		"Converts a UTF-32 code into a string.\n");
}

Gura_ImplementFunction(chr)
{
	UInt32 codeUTF32 = arg.GetUInt32(0);
	String str;
	AppendUTF32(str, codeUTF32);
	return Value(str);
}

// hex(num:number, digits?:number):map:[upper]
Gura_DeclareFunction(hex)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "num", VTYPE_number);
	DeclareArg(env, "digits", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareAttr(Gura_Symbol(upper));
	AddHelp(
		Gura_Symbol(en),
		"Converts a number into a hexadecimal string.\n"
		"Argument `digits` specifies a minimum columns of the converted result\n"
		"and fills `0` in the lacking space.\n"
		"\n"
		"In default, it uses lower-case characters in its conversion,\n"
		"while it uses upper-case ones when `:upper` attribute is specified.\n");
}

Gura_ImplementFunction(hex)
{
	Signal &sig = env.GetSignal();
	int digits = arg.Is_number(1)? arg.GetInt(1) : 0;
	bool upperFlag = arg.IsSet(Gura_Symbol(upper));
	String str;
	if (digits <= 0) {
		str = Formatter::FormatValueList(sig, upperFlag? "%X" : "%x",
						ValueList(arg.GetValue(0)));
	} else {
		str = Formatter::FormatValueList(sig, upperFlag? "%0*X" : "%0*x",
						ValueList(Value(digits), arg.GetValue(0)));
	}
	if (sig.IsSignalled()) return Value::Nil;
	return Value(str);
}

// int(value):map
Gura_DeclareFunctionAlias(int_, "int")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "value", VTYPE_any);
	AddHelp(
		Gura_Symbol(en),
		"Converts a value into an integer number like below:\n"
		"\n"
		"- For a number value, it would be converted into an integer number.\n"
		"- For a compex value, its absolute number would be converted into an integer number.\n"
		"- For a string value, it would be parsed as an integer number.\n"
		"  An error occurs if it has an invalid format.\n"
		"- For other values, an error occurs.\n");
}

Gura_ImplementFunction(int_)
{
	Signal &sig = env.GetSignal();
	const Value &value = arg.GetValue(0);
	Value result;
	if (value.Is_number()) {
		result.SetNumber(value.GetLong());
	} else if (value.Is_complex()) {
		result.SetNumber(static_cast<long>(std::abs(value.GetComplex())));
	} else if (value.Is_string()) {
		bool successFlag;
		Number num = value.ToNumber(true, successFlag);
		if (!successFlag) {
			sig.SetError(ERR_ValueError, "failed to convert to a number");
			return Value::Nil;
		}
		result.SetNumber(static_cast<long>(num));
	} else if (value.IsValid()) {
		SetError_InvalidValType(sig, value);
	}
	return result;
}

// ord(str:string):map
Gura_DeclareFunction(ord)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "str", VTYPE_string);
	AddHelp(
		Gura_Symbol(en),
		"Converts the first character of a string into a number of UTF-32 code.\n"
		"If the string contains more than one characters, it simply neglects trailing ones.\n");
}

Gura_ImplementFunction(ord)
{
	const char *str = arg.GetString(0);
	UInt32 codeUTF32 = 0;
	NextUTF32(str, codeUTF32);
	return Value(codeUTF32);
}

// tonumber(value):map:[strict,raise,zero,nil]
Gura_DeclareFunction(tonumber)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "value", VTYPE_any);
	DeclareAttr(Gura_Symbol(strict));
	DeclareAttr(Gura_Symbol(raise));
	DeclareAttr(Gura_Symbol(zero));
	DeclareAttr(Gura_Symbol(nil));
	AddHelp(
		Gura_Symbol(en),
		"Converts a string value into a number by a lexical parsing.\n"
		"If the value is not a string, it first tries to convert the value into a string.\n"
		"\n"
		"If the string starts with a sequence of characters that can be parsed as a number literal,\n"
		"it's not a failure even when it contains other characters following them.\n"
		"Specifying an attribute `:strict` doesn't allow such a case and fails the process.\n"
		"\n"
		"If it fails the conversion, it would return `nil` value.\n"
		"Attributes described below are prepared to customize the behaviour in the case of a failure.\n"
		"\n"
		"- `:raise` .. raises an error\n"
		"- `:zero` .. returns zero value\n"
		"- `:nil` .. returns `nil` value (default)\n");
}

Gura_ImplementFunction(tonumber)
{
	Signal &sig = env.GetSignal();
	bool allowPartFlag = !arg.IsSet(Gura_Symbol(strict));
	bool successFlag;
	Number num = arg.GetValue(0).ToNumber(allowPartFlag, successFlag);
	if (successFlag) {
		return Value(num);
	} else if (arg.IsSet(Gura_Symbol(raise))) {
		sig.SetError(ERR_ValueError, "failed to convert to a number");
		return Value::Nil;
	} else if (arg.IsSet(Gura_Symbol(zero))) {
		return Value(0.);
	} else { // arg.IsSet(Gura_UserSymbol(nil)
		return Value::Nil;
	}
}

// tostring(value):map
Gura_DeclareFunction(tostring)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "value", VTYPE_any);
	AddHelp(
		Gura_Symbol(en),
		"Converts a value into a string.");
}

Gura_ImplementFunction(tostring)
{
	return Value(arg.GetValue(0).ToString(false));
}

// tosymbol(str:string):map
Gura_DeclareFunction(tosymbol)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "str", VTYPE_string);
	AddHelp(
		Gura_Symbol(en),
		"Converts a string into a symbol.");
}

Gura_ImplementFunction(tosymbol)
{
	return Value(Symbol::Add(arg.GetString(0)));
}

//-----------------------------------------------------------------------------
// Class Operations
//-----------------------------------------------------------------------------
// class(superclass?:class) {block?}
Gura_DeclareFunctionAlias(class_, "class")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "superclass", VTYPE_Class, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
	AddHelp(
		Gura_Symbol(en),
		"Creates a `class` that includes methods and properties\n"
		"described in the content of the `block`.\n"
		"The detail information on how to describe the block content for this function\n"
		"is written in \"Gura Language Manual\".\n"
		"\n"
		"Below is an example to create a class named `Person`:\n"
		"\n"
		"    Person = class {\n"
		"        __init__(name:string, age:number) = {\n"
		"            this.name = name\n"
		"            this.age = age\n"
		"        }\n"
		"        Print() = {\n"
		"            printf('name:%s age:%d\\n', this.name, this.age)\n"
		"        }\n"
		"    }\n"
		"    \n"
		"    person = Person('Smith', 26)\n"
		"    person.Print()\n"
		"\n"
		"If the argument `superclass`,\n"
		"which is expected to be a constructor function of a super class, is specified,\n"
		"the created class would inherit methods and properties from the specified class.\n");
}

Gura_ImplementFunction(class_)
{
	Signal &sig = env.GetSignal();
	const Expr_Block *pExprBlock = arg.GetBlockCooked(env);
	if (sig.IsSignalled()) return Value::Nil;
	Class *pClassSuper = arg.IsClass(0)? arg.GetClassItself(0) : env.LookupClass(VTYPE_object);
	ClassCustom *pClassCustom = new ClassCustom(&env, pClassSuper,
			pClassSuper->GetValueType(),
			dynamic_cast<Expr_Block *>(Expr::Reference(pExprBlock)));
	return Value(pClassCustom);
}

// classref(type+:expr):map {block?}
Gura_DeclareFunction(classref)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "type", VTYPE_expr, OCCUR_OnceOrMore);
	DeclareBlock(OCCUR_ZeroOrOnce);
	AddHelp(
		Gura_Symbol(en),
		"Looks up a class by an expression of a type name.");
}

Gura_ImplementFunction(classref)
{
	const ValueTypeInfo *pValueTypeInfo = env.LookupValueType(arg.GetList(0));
	if (pValueTypeInfo == nullptr) return Value::Nil;
	Value result(Class::Reference(pValueTypeInfo->GetClass()));
	return ReturnValue(env, arg, result);
}

// struct(`args*):nonamed:[loose] {block?}
// if :loose attribute is specified, arguments in the generated function
// will get the following modification.
// - Once attribute will be modified to ZeroOrOnce.
// - OnceOrMore attribute will be modified to ZeroOrMore
Gura_DeclareFunctionAlias(struct_, "struct")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_NoNamed);
	DeclareArg(env, "args", VTYPE_quote, OCCUR_OnceOrMore);
	DeclareBlock(OCCUR_ZeroOrOnce);
	DeclareAttr(Gura_Symbol(loose));
	AddHelp(
		Gura_Symbol(en),
		"Creates a `class` for a structure that\n"
		"contains properties specified by `args`. It can optionally take a block\n"
		"which declares methods and properties just like `class()` function does.\n"
		"\n"
		"An element in `args` is an expression that has the same format with\n"
		"one in the argument list of a function's declaration.\n"
		"Each variable name becomes a member name in the created instance.\n"
		"\n"
		"Below is an example to create a structure named `Person`:\n"
		"\n"
		"    Person = struct(name:string, age:number)\n"
		"    person = Person('Smith', 26)\n"
		"    printf('name:%s age:%d\\n', person.name, person.age)\n"
		"\n"
		"If `:loose` attribute is speicied, the generated constructor\n"
		"would take all the arguments as optional.\n"
		"Omitted variables are set to `nil`\n");
}

Gura_ImplementFunction(struct_)
{
	const Expr_Block *pExprBlock = arg.GetBlockCooked(env);
	if (env.IsSignalled()) return Value::Nil;
	Class *pClassSuper = env.LookupClass(VTYPE_Struct);
	ClassCustom *pClassCustom = new ClassCustom(&env, pClassSuper,
			pClassSuper->GetValueType(),
			dynamic_cast<Expr_Block *>(Expr::Reference(pExprBlock)));
	AutoPtr<Class_Struct::Constructor> pFunc(new Class_Struct::Constructor(env));
	pFunc->SetClassToConstruct(pClassCustom); // constructor is registered in this class
	pFunc->DeclareBlock(OCCUR_ZeroOrOnce);
	ExprList exprListArg;
	exprListArg.reserve(arg.GetList(0).size());
	foreach_const (ValueList, pValue, arg.GetList(0)) {
		exprListArg.push_back(const_cast<Expr *>(pValue->GetExpr()));
	}
	CallerInfo callerInfo(exprListArg, nullptr, arg.GetAttrsShared(), nullptr);
	callerInfo.SetFlagsToSet(arg.GetFlags() & ~FLAG_NoNamed);
	callerInfo.SetResultMode(arg.GetResultMode());
	if (!pFunc->CustomDeclare(env, callerInfo, GetAttrsOpt())) return false;
	if (arg.IsSet(Gura_Symbol(loose))) {
		pFunc->GetDeclOwner().SetAsLoose();
	}
	return Value(pClassCustom);
}

// super(obj) {block?}
Gura_DeclareFunction(super)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "obj", VTYPE_any, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
	AddHelp(
		Gura_Symbol(en),
		"Returns a reference to `obj` through which you can call methods of the super class.\n"
		"\n"
		"Example:\n"
		"\n"
		"    A = class {\n"
		"        func() = {}\n"
		"    }\n"
		"    \n"
		"    B = class(A) {\n"
		"        func() = {}\n"
		"    }\n"
		"    \n"
		"    b = B()\n"
		"    b.func()         // B#func() is called.\n"
		"    super(b).func()  // A#func() is called.\n"
		);
}

Gura_ImplementFunction(super)
{
	Value rtn(arg.GetValue(0));
	int cntSuperSkip = rtn.GetSuperSkipCount() + 1;
	if (cntSuperSkip > Value::MaxSuperSkipCount) {
		env.SetError(ERR_SystemError,
			"number of super reference is limited under %d", Value::MaxSuperSkipCount);
		return Value::Nil;
	}
	rtn.SetSuperSkipCount(cntSuperSkip);
	return ReturnValue(env, arg, rtn);
}

//-----------------------------------------------------------------------------
// Scope Operations
//-----------------------------------------------------------------------------
#if 0
// Scope problem: when a block tries to assign a variable that has been declared by extern()
// outside of it, it fails to do it.
// 
//     x = 0
//     f() = {
//         extern(x)
//         if (true) {
//             x = 3
//         }
//     }
//     println(x)  // print 0, not 3

// extern(`syms+)
Gura_DeclareFunctionAlias(extern_, "extern")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "syms", VTYPE_quote, OCCUR_OnceOrMore);
	AddHelp(
		Gura_Symbol(en),
		"Declares symbols that is supposed to access variables in outer scopes.");
}

Gura_ImplementFunction(extern_)
{
	foreach_const (ValueList, pValue, arg.GetList(0)) {
		const Expr *pExpr = pValue->GetExpr();
		if (!pExpr->IsIdentifier()) {
			env.SetError(ERR_ValueError, "identifier must be specified");
			return Value::Nil;
		}
		const Symbol *pSymbol = dynamic_cast<const Expr_Identifier *>(pExpr)->GetSymbol();
		if (env.LookupValue(pSymbol, ENVREF_Escalate) == nullptr) {
			env.SetError(ERR_ValueError, "undefined symbol '%s'", pSymbol->GetName());
		}
	}
	return Value::Nil;
}
#endif

// local(`syms+)
Gura_DeclareFunction(local)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "syms", VTYPE_quote, OCCUR_OnceOrMore);
	AddHelp(
		Gura_Symbol(en),
		"Declares symbols of variable that are supposed to be accessed locally in a block.");
}

Gura_ImplementFunction(local)
{
	foreach_const (ValueList, pValue, arg.GetList(0)) {
		const Expr *pExpr = pValue->GetExpr();
		if (!pExpr->IsIdentifier()) {
			env.SetError(ERR_ValueError, "identifier must be specified");
			return Value::Nil;
		}
		const Symbol *pSymbol = dynamic_cast<const Expr_Identifier *>(pExpr)->GetSymbol();
		if (env.LookupValue(pSymbol, ENVREF_NoEscalate) == nullptr) {
			env.AssignValue(pSymbol, Value::Nil, EXTRA_Public);
		}
	}
	return Value::Nil;
}

// locals(module?:module) {block?}
Gura_DeclareFunction(locals)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "module", VTYPE_Module, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
	AddHelp(
		Gura_Symbol(en),
		"Returns an environment object that belongs to a specified module.\n"
		"If the argument `module` is omitted, it returns an `environment` object of the current scope.");
}

Gura_ImplementFunction(locals)
{
	Value value;
	if (arg.IsModule(0)) {
		value = Value(new Object_environment(*arg.GetModule(0)));
	} else {
		value = Value(new Object_environment(env));
	}
	return ReturnValue(env, arg, value);
}

// outers() {block?}
Gura_DeclareFunction(outers)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
	AddHelp(
		Gura_Symbol(en),
		"Returns an environment object that accesses to an outer scope.");
}

Gura_ImplementFunction(outers)
{
	AutoPtr<Environment> pEnvOuter(new Environment(env.GetSignal()));
	pEnvOuter->AddOuterFrame(env.GetFrameOwner());
	return ReturnValue(env, arg, Value(new Object_environment(*pEnvOuter)));
}

// public():void {block}
Gura_DeclareFunctionAlias(public_, "public")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	DeclareBlock(OCCUR_Once);
	AddHelp(
		Gura_Symbol(en),
		"Declares symbols as public ones that are accessible from outer scopes.\n"
		"\n"
		"If you want to make `foo` and `bar` accessible, call this function like below:\n"
		"\n"
		"    public { foo, bar }\n");
}

Gura_ImplementFunction(public_)
{
	SymbolSet &symbolsPublic = env.PrepareSymbolsPublic();
	const Expr_Block *pExprBlock = arg.GetBlockCooked(env);
	foreach_const (ExprOwner, ppExpr, pExprBlock->GetExprOwner()) {
		const Expr *pExpr = *ppExpr;
		if (pExpr->IsIdentifier()) {
			const Expr_Identifier *pExprIdentifier = dynamic_cast<const Expr_Identifier *>(pExpr);
			symbolsPublic.Insert(pExprIdentifier->GetSymbol());
		} else if (pExpr->IsAssign()) {
			const Expr_Assign *pExprAssign = dynamic_cast<const Expr_Assign *>(pExpr);
			if (!pExprAssign->GetLeft()->IsIdentifier()) {
				env.SetError(ERR_ValueError, "invalid element for public");
				return Value::Nil;
			}
			const Expr_Identifier *pExprIdentifier = dynamic_cast<const Expr_Identifier *>(pExprAssign->GetLeft());
			symbolsPublic.Insert(pExprIdentifier->GetSymbol());
			pExpr->Exec(env);
			if (env.IsSignalled()) return Value::Nil;
		} else {
			env.SetError(ERR_ValueError, "invalid element for public");
			return Value::Nil;
		}
	}
	return Value::Nil;
}

// scope(target?) {block}
Gura_DeclareFunction(scope)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "target", VTYPE_any, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_Once);
	AddHelp(
		Gura_Symbol(en),
		"Evaluates block with a local scope.");
}

Gura_ImplementFunction(scope)
{
	if (arg.IsInvalid(0)) {
		AutoPtr<Environment> pEnvBlock(env.Derive(ENVTYPE_local));
		const Expr_Block *pExprBlock = arg.GetBlockCooked(*pEnvBlock);
		if (env.IsSignalled()) return Value::Nil;
		return pExprBlock->Exec(*pEnvBlock);
	} else {
		Environment *pEnv = nullptr;
		if (arg.IsModule(0)) {
			pEnv = arg.GetModule(0);
		} else if (arg.IsClass(0)) {
			pEnv = arg.GetValue(0).GetClassItself();
		} else if (arg.IsType(0, VTYPE_environment)) {
			pEnv = &Object_environment::GetObject(arg, 0)->GetEnv();
		}
		if (pEnv != nullptr) {
			const Expr_Block *pExprBlock = arg.GetBlockCooked(*pEnv);
			if (env.IsSignalled()) return Value::Nil;
			return pExprBlock->Exec(*pEnv);
		}
	}
	env.SetError(ERR_ValueError, "module or environment must be specified");
	return Value::Nil;
}

//-----------------------------------------------------------------------------
// Module Operations
//-----------------------------------------------------------------------------
// module {block}
Gura_DeclareFunction(module)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_Once);
	AddHelp(
		Gura_Symbol(en),
		"Creates a module that contains functions and variables defined in the block\n"
		"and returns it as a module object. This can be used to realize a namespace.");
}

Gura_ImplementFunction(module)
{
	const Expr_Block *pExprBlock = arg.GetBlockCooked(env);
	if (env.IsSignalled()) return Value::Nil;
	Module *pModule = new Module(&env, Gura_Symbol(_anonymous_), "", nullptr, nullptr);
	pExprBlock->Exec(*pModule);
	return Value(pModule);
}

// import(`module, `alias?):[binary,overwrite,mixin_type] {block?}
Gura_DeclareFunctionAlias(import_, "import")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "module", VTYPE_quote);
	DeclareArg(env, "alias", VTYPE_quote, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
	DeclareAttr(Gura_Symbol(overwrite));
	DeclareAttr(Gura_Symbol(binary));
	DeclareAttr(Gura_Symbol(mixin_type));
	AddHelp(
		Gura_Symbol(en),
		"Imports a module and creates a variable that represents the imported module.\n"
		"It also returns a value that is a reference to the module.\n"
		"\n"
		"It searches module files in directories specified by a variable `sys.path`.\n"
		"\n"
		"There are three format to call this function like follow:\n"
		"\n"
		"- `import(foo)` .. imports `foo` module and creates a module object named `foo`\n"
		"- `import(foo, bar)` .. imports `foo` module and creates a module object named `bar`\n"
		"- `import(foo) {symbol1, symbol2, symbol3}` .. imports `foo` and\n"
		"      mixes up the module's properties `symbol1`, `symbol2` and `symbol3`\n"
		"      in the current scope.\n"
		"\n"
		"In the third format, you can specify an asterisk character\n"
		"to mixes up all the symbols defined in the module like below:\n"
		"\n"
		"    import(foo) {*}\n"
		"\n"
		"If a specified symbol conflicts with what already exists in the current scope,\n"
		"it will cause an error.\n"
		"Specifying the attribute `:overwrite` will avoid such an error\n"
		"and allow overwriting of symbols.\n"
		"\n"
		"If the argument `module` is prefixed by a minus operator like `-foo`,\n"
		"it will not create a variable that represents the imported module.\n"
		"\n"
		"If the argument `module` is prefixed by an and operator like `&foo`,\n"
		"the trailing expression will be evaluated and its result, which must be a string,\n"
		"is treated as a module name to be imported. Below is a sample to import `foo` module\n"
		"through a variable that contains that name:\n"
		"\n"
		"    var = 'foo'\n"
		"    import(&var)\n");
}

Gura_ImplementFunction(import_)
{
	SymbolSet symbolsToMixIn;
	SymbolSet *pSymbolsToMixIn = nullptr;
	if (arg.IsBlockSpecified()) {
		const Expr_Block *pExprBlock = arg.GetBlockCooked(env);
		if (env.IsSignalled()) return Value::Nil;
		foreach_const (ExprList, ppExpr, pExprBlock->GetExprOwner()) {
			if (!(*ppExpr)->IsIdentifier()) {
				env.SetError(ERR_SyntaxError,
					"wrong format for an element in import list");
				return Value::Nil;
			}
			const Expr_Identifier *pExprIdentifier =
							dynamic_cast<const Expr_Identifier *>(*ppExpr);
			symbolsToMixIn.insert(pExprIdentifier->GetSymbol());
		}
		pSymbolsToMixIn = &symbolsToMixIn;
	}
	const Symbol *pSymbolAlias = nullptr;
	if (!arg.Is_expr(1)) {
		// nothing to do
	} else if (!arg.GetExpr(1)->IsIdentifier()) {
		env.SetError(ERR_ValueError, "identifier is expected as a module name");
		return Value::Nil;
	} else {
		pSymbolAlias = dynamic_cast<const Expr_Identifier *>(arg.GetExpr(1))->GetSymbol();
	}
	bool overwriteFlag = arg.IsSet(Gura_Symbol(overwrite));
	bool binaryOnlyFlag = arg.IsSet(Gura_Symbol(binary));
	bool mixinTypeFlag = arg.IsSet(Gura_Symbol(mixin_type));
	Module *pModule = env.ImportModule(arg.GetExpr(0), pSymbolAlias, pSymbolsToMixIn,
									   overwriteFlag, binaryOnlyFlag, mixinTypeFlag);
	if (pModule == nullptr) return Value::Nil;
	return Value(Module::Reference(pModule));
}

//-----------------------------------------------------------------------------
// Value Type Information
//-----------------------------------------------------------------------------
// isdefined(`identifier)
Gura_DeclareFunction(isdefined)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "identifier", VTYPE_quote);
	AddHelp(
		Gura_Symbol(en),
		"Returns `true` if `identifier` is defined, and `false` otherwise.");
}

Gura_ImplementFunction(isdefined)
{
	Signal &sig = env.GetSignal();
	bool definedFlag = false;
	const Expr *pExpr = arg.GetExpr(0);
	if (pExpr->IsIdentifier() || pExpr->IsMember()) {
		Value result = pExpr->Exec(env);
		if (sig.IsSignalled() && !sig.IsError()) return Value::Nil;
		definedFlag = !sig.IsError() && result.IsDefined();
		sig.ClearSignal();
	} else {
		sig.SetError(ERR_ValueError, "argument must be an identifier");
		return Value::Nil;
	}
	return Value(definedFlag);
}

// istype*(value)
class Gura_Function(istype_) : public Function {
private:
	ValueType _valType;
public:
	Gura_Function(istype_)(Environment &env, const char *name, ValueType valType);
	virtual Value DoEval(Environment &env, Argument &arg) const;
};
Gura_Function(istype_)::Gura_Function(istype_)(
					Environment &env, const char *name, ValueType valType) :
	Function(env, Symbol::Add(name), FUNCTYPE_Function, FLAG_None), _valType(valType)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "value", VTYPE_any);
	char buff[1024];
	::sprintf(buff, "Returns `true` if the `value` is an instance of `%s`, and `false` otherwise.",
		ValueTypePool::GetInstance()->Lookup(_valType)->MakeFullName().c_str());
	AddHelp(
		Gura_Symbol(en),
		buff);
}

Gura_ImplementFunction(istype_)
{
	ValueType valType = arg.GetValue(0).GetValueType();
	ValueType valTypeCmp = _valType;
	if ((valType == VTYPE_number || valType == VTYPE_rational) &&
								valTypeCmp == VTYPE_complex) return Value(true);
	if (valType == VTYPE_rational && valTypeCmp == VTYPE_number) return Value(true);
	return Value(valType == valTypeCmp);
}

// istype(value, type+:expr):map
Gura_DeclareFunction(istype)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "value", VTYPE_any);
	DeclareArg(env, "type", VTYPE_expr, OCCUR_OnceOrMore);
	AddHelp(
		Gura_Symbol(en),
		"Returns `true` if `value` is of the type of `type`, and `false` otherwise.\n");
}

Gura_ImplementFunction(istype)
{
	const ValueTypeInfo *pValueTypeInfo = env.LookupValueType(arg.GetList(1));
	if (pValueTypeInfo == nullptr) return Value::Nil;
	ValueType valType = arg.GetValue(0).GetValueType();
	ValueType valTypeCmp = pValueTypeInfo->GetValueType();
	if ((valType == VTYPE_number || valType == VTYPE_rational) &&
								valTypeCmp == VTYPE_complex) return Value(true);
	if (valType == VTYPE_rational && valTypeCmp == VTYPE_number) return Value(true);
	return Value(valType == valTypeCmp);
}

// isinstance(value, type+:expr):map
Gura_DeclareFunction(isinstance)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "value", VTYPE_any);
	DeclareArg(env, "type", VTYPE_expr, OCCUR_OnceOrMore);
	AddHelp(
		Gura_Symbol(en),
		"Returns `true` if `value` is an instance of `type` or its descendant, and `false` otherwise.\n");
}

Gura_ImplementFunction(isinstance)
{
	const ValueTypeInfo *pValueTypeInfo = env.LookupValueType(arg.GetList(1));
	if (pValueTypeInfo == nullptr) return Value::Nil;
	return arg.GetValue(0).IsInstanceOf(pValueTypeInfo->GetValueType());
}

// typename(`value)
Gura_DeclareFunctionAlias(typename_, "typename")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "value", VTYPE_quote);
	AddHelp(
		Gura_Symbol(en),
		"Returns a type name of the value.");
}

Gura_ImplementFunction(typename_)
{
	Signal &sig = env.GetSignal();
	const Expr *pExpr = arg.GetExpr(0);
	String typeName = "unknown";
	if (pExpr->IsIdentifier() || pExpr->IsMember()) {
		Value value = pExpr->Exec(env);
		if (sig.IsSignalled() && !sig.IsError()) return Value::Nil;
		if (sig.IsError()) {
			typeName = "undefined";
		} else {
			typeName = value.MakeValueTypeName();
		}
		sig.ClearSignal();
	} else {
		Value value = pExpr->Exec(env);
		if (sig.IsSignalled()) return Value::Nil;
		typeName = value.MakeValueTypeName();
	}
	return Value(typeName);
}

// undef(`identifier+):[raise]
Gura_DeclareFunctionAlias(undef_, "undef")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "identifier", VTYPE_quote, OCCUR_OnceOrMore);
	DeclareAttr(Gura_Symbol(raise));
	AddHelp(
		Gura_Symbol(en),
		"Undefines `identifier` in the current scope.");
}

Gura_ImplementFunction(undef_)
{
	bool raiseFlag = arg.IsSet(Gura_Symbol(raise));
	foreach_const (ValueList, pValueArg, arg.GetList(0)) {
		const Expr *pExpr = pValueArg->GetExpr();
		Environment *pEnv = &env;
		const Symbol *pSymbol = nullptr;
		if (pExpr->IsIdentifier()) {
			pSymbol = dynamic_cast<const Expr_Identifier *>(pExpr)->GetSymbol();
		} else {
			SymbolList symbolList;
			//if (!Parser::ParseDottedIdentifier(pExpr, symbolList)) {
			if (!symbolList.AddFromExpr(pExpr)) {
				env.SetError(ERR_ValueError, "invalid identifier name");
				return Value::Nil;
			}
			for (SymbolList::iterator ppSymbol = symbolList.begin();
								ppSymbol + 1 != symbolList.end(); ppSymbol++) {
				Value *pValue = pEnv->LookupValue(*ppSymbol, ENVREF_NoEscalate);
				if (pValue == nullptr) {
					if (raiseFlag) {
						env.SetError(ERR_ValueError, "undefined identifier");
					}
					return Value::Nil;
				}
				if (pValue->IsModule()) {
					pEnv = pValue->GetModule();
				} else if (pValue->IsClass()) {
					pEnv = pValue->GetClassItself();
				} else if (pValue->IsObject()) {
					pEnv = pValue->GetObject();
				} else {
					env.SetError(ERR_ValueError, "invalid identifier name");
					return Value::Nil;
				}
			}
			pSymbol = symbolList.back();
		}
		if (raiseFlag && !pEnv->LookupValue(pSymbol, ENVREF_NoEscalate)) {
			env.SetError(ERR_ValueError, "undefined identifier");
			return Value::Nil;
		}
		pEnv->RemoveValue(pSymbol);
	}
	return Value::Nil;
}

//-----------------------------------------------------------------------------
// Data Processing
//-----------------------------------------------------------------------------
// choose(index:number, values+):map
Gura_DeclareFunction(choose)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "index", VTYPE_number);
	DeclareArg(env, "values", VTYPE_any, OCCUR_OnceOrMore);
	AddHelp(
		Gura_Symbol(en),
		"Picks up a value placed at `index` in the argument list `values`.\n"
		"\n"
		"Sample:\n"
		"\n"
		"    choose(0, 'apple', 'orange', 'banana') // returns 'apple'\n"
		"    choose(2, 'apple', 'orange', 'banana') // returns 'banana'\n");
}

Gura_ImplementFunction(choose)
{
	size_t index = arg.GetSizeT(0);
	const ValueList &valList = arg.GetList(1);
	if (index >= valList.size()) {
		env.SetError(ERR_IndexError, "index is out of range");
		return Value::Nil;
	}
	return valList[index];
}

// cond(flag:boolean, value1:nomap, value2:nomap?):map
Gura_DeclareFunction(cond)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "flag", VTYPE_boolean);
	DeclareArg(env, "value1", VTYPE_any, OCCUR_Once, FLAG_NoMap);
	DeclareArg(env, "value2", VTYPE_any, OCCUR_ZeroOrOnce, FLAG_NoMap);
	AddHelp(
		Gura_Symbol(en),
		"Returns `value1` if `flag` is determined as true, and `value2` otherwise.\n"
		"If the argument `value2` is omitted, it will return `nil` when `flag` is determined as false.\n"
		"\n"
		"This function behaves in a similar way with `if` function when it's called like below:\n"
		"\n"
		"    if (flag) { value1 } else { value2 }\n"
		"\n"
		"Notice that they have the following differences:\n"
		"\n"
		"- Function `cond()` always evaluates arguments `value1` and `value2`\n"
		"  no matter what `flag` value is,\n"
		"  while function `if()` doesn't evaluate `value1` expression\n"
		"  when `flag` is determined as `false`.\n"
		"- Function `cond()` works with implicit mapping,\n"
		"  which means that the argument `flag` may be a list or an iterator\n"
		"  that are to be processed with the implicit mapping.\n"
		"\n"
		"The arguments `value1` and `value2` are not processed by the implicit mapping,\n"
		"so you can specify a list or an iterator for them as selected items.\n");
}

Gura_ImplementFunction(cond)
{
	return arg.GetBoolean(0)? arg.GetValue(1) : arg.GetValue(2);
}

// conds(flag:boolean, value1, value2?):map
Gura_DeclareFunction(conds)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "flag", VTYPE_boolean);
	DeclareArg(env, "value1", VTYPE_any, OCCUR_Once);
	DeclareArg(env, "value2", VTYPE_any, OCCUR_ZeroOrOnce);
	AddHelp(
		Gura_Symbol(en),
		"Returns `value1` if `flag` is determined as true, and `value2` otherwise.\n"
		"If argument `value2` is omitted, it will return `nil` when `flag` is determined as false.\n"
		"\n"
		"This function behaves in a similar way with `if` function when it's called like below:\n"
		"\n"
		"    if (flag) { value1 } else { value2 }\n"
		"\n"
		"Notice that they have the following differences:\n"
		"\n"
		"- Function `conds()` always evaluates arguments `value1` and `value2`\n"
		"  no matter what `flag` value is,\n"
		"  while function `if()` doesn't evaluate `value1` expression\n"
		"  when `flag` is determined as false.\n"
		"- Function `conds()` works with implicit mapping,\n"
		"  which means that the arguments `flag`, `value1` and `value2` may be lists or iterators\n"
		"  that are to be processed with the implicig mapping.\n"
		"\n"
		"If you want to specify a list or an iterator for `value1` and `value2` as selected values,\n"
		"use `cond()` function instead.\n");
}

Gura_ImplementFunction(conds)
{
	return arg.GetBoolean(0)? arg.GetValue(1) : arg.GetValue(2);
}

// max(values+):map
Gura_DeclareFunction(max)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "values", VTYPE_any, OCCUR_OnceOrMore);
	AddHelp(
		Gura_Symbol(en),
		"Returns the maximum value among the given arguments.");
}

Gura_ImplementFunction(max)
{
	const ValueList &valList = arg.GetList(0);
	ValueList::const_iterator pValue = valList.begin();
	Value result = *pValue++;
	for ( ; pValue != valList.end(); pValue++) {
		int cmp = Value::Compare(env, result, *pValue);
		if (env.IsSignalled()) return Value::Nil;
		if (cmp < 0) result = *pValue;
	}
	return result;
}

// min(values+):map
Gura_DeclareFunction(min)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "values", VTYPE_any, OCCUR_OnceOrMore);
	AddHelp(
		Gura_Symbol(en),
		"Returns the minimum value among the given arguments.");
}

Gura_ImplementFunction(min)
{
	const ValueList &valList = arg.GetList(0);
	ValueList::const_iterator pValue = valList.begin();
	Value result = *pValue++;
	for ( ; pValue != valList.end(); pValue++) {
		int cmp = Value::Compare(env, result, *pValue);
		if (env.IsSignalled()) return Value::Nil;
		if (cmp > 0) result = *pValue;
	}
	return result;
}

//-----------------------------------------------------------------------------
// Random
//-----------------------------------------------------------------------------
// rand(range?:number) {block?}
Gura_DeclareFunction(rand)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "range", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
	AddHelp(
		Gura_Symbol(en),
		"Returns a random number between `0` and `(range - 1)`.\n"
		"If argument `range` is not specified, it generates random numbers in a range of [0, 1).");
}

Gura_ImplementFunction(rand)
{
	if (arg.Is_number(0)) {
		ULong num = arg.GetULong(0);
		Number result = static_cast<ULong>(Random::Uniform_CloseOpen() * num);
		return Value(result);
	}
	return ReturnValue(env, arg, Value(Random::Uniform_CloseOpen()));
}

// rand@normal(mu?:number, sigma?:number) {block?}
Gura_DeclareFunctionAlias(rand_at_normal, "rand@normal")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "mu", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareArg(env, "sigma", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
	AddHelp(
		Gura_Symbol(en),
		"Returns a normal distribution random number with a mean value of `mu` and a standard deviation of `sigma`.\n"
		"The default values for `mu` and `sigma` are `0` and `1` respectively.");
}

Gura_ImplementFunction(rand_at_normal)
{
	double mu = arg.Is_number(0)? arg.GetDouble(0) : 0;
	double sigma = arg.Is_number(1)? arg.GetDouble(1) : 1;
	return ReturnValue(env, arg, Value(mu + Random::Normal() * sigma));
}

// rands(range?:number, num?:number) {block?}
Gura_DeclareFunction(rands)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "range", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareArg(env, "num", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
	AddHelp(
		Gura_Symbol(en),
		"Creates an iterator that returns random numbers between `0` and `(range - 1)`.\n"
		"\n"
		"If argument `range` is not specified, it generates random numbers in a range of [0, 1).\n"
		"\n"
		"In default, the created iterator infinitely generates random numbers.\n"
		"The argument `num` specifies how many elements should be generated.\n"
		"\n"
		GURA_HELPTEXT_ITERATOR_en()
		"\n"
		"Below is an example to create a create that generates random numbers:\n"
		"\n"
		"    x = rands(100)\n"
		"    // x is an infinite iterator to generates random numbers between 0 and 99\n");
}

Gura_ImplementFunction(rands)
{
	Iterator *pIterator = new Iterator_Rand(
				arg.Is_number(0)? arg.GetInt(0) : 0,
				arg.Is_number(1)? arg.GetInt(1) : -1);
	return ReturnIterator(env, arg, pIterator);
}

// rands@normal(mu?:number, sigma?:number, num?:number) {block?}
Gura_DeclareFunctionAlias(rands_at_normal, "rands@normal")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "mu", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareArg(env, "sigma", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareArg(env, "num", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
	AddHelp(
		Gura_Symbol(en),
		"Creates an iterator that returns normal distribution random numbers\n"
		"with a mean value of `mu` and a standard deviation of `sigma`.\n"
		"The default values for `mu` and `sigma` are `0` and `1` respectively.\n"
		"\n"
		"If argument `range` is not specified, it generates random numbers in a range of [0, 1).\n"
		"\n"
		"In default, the created iterator infinitely generates random numbers.\n"
		"The argument `num` specifies how many elements should be generated.\n"
		"\n"
		GURA_HELPTEXT_ITERATOR_en());
}

Gura_ImplementFunction(rands_at_normal)
{
	Iterator *pIterator = new Iterator_Randn(
				arg.Is_number(0)? arg.GetInt(0) : 0,
				arg.Is_number(1)? arg.GetInt(1) : 1,
				arg.Is_number(2)? arg.GetInt(2) : -1);
	return ReturnIterator(env, arg, pIterator);
}

// randseed(seed:number):void
Gura_DeclareFunction(randseed)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "seed", VTYPE_number);
	AddHelp(
		Gura_Symbol(en),
		"Initializes random seed with a specified number.");
}

Gura_ImplementFunction(randseed)
{
	Random::SetRandSeed(arg.GetULong(0));
	return Value::Nil;
}

//-----------------------------------------------------------------------------
// Property Listing
//-----------------------------------------------------------------------------
// dir(obj?):[noesc]
Gura_DeclareFunction(dir)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "obj", VTYPE_any, OCCUR_ZeroOrOnce);
	DeclareAttr(Gura_Symbol(noesc));
	//DeclareAttr(Gura_Symbol(nosort));
	AddHelp(
		Gura_Symbol(en),
		"Returns a symbol list of variables and functions\n"
		"that are assigned in the environment of `obj`.\n"
		"\n"
		"In default, when the `obj` is an instance of a class,\n"
		"it also searches symbols assigned in the class that it belongs to and its parent classes.\n"
		"Specifying attribute `:noesc` avoids that behavior.\n");
}

Gura_ImplementFunction(dir)
{
	bool escalateFlag = !arg.IsSet(Gura_Symbol(noesc));
	bool sortFlag = !arg.IsSet(Gura_Symbol(nosort));
	SymbolList symbolList;
	if (arg.IsValid(0)) {
		SymbolSet symbols;
		if (!arg.GetValue(0).DirProp(env, symbols, escalateFlag)) return Value::Nil;
		foreach_const (SymbolSet, ppSymbol, symbols) {
			const Symbol *pSymbol = *ppSymbol;
			symbolList.push_back(pSymbol);
		}
	} else {
		foreach_const (ValueExMap, iter, env.GetBottomFrame()->GetValueExMap()) {
			const Symbol *pSymbol = iter->first;
			symbolList.push_back(pSymbol);
		}
	}
	if (sortFlag) symbolList.SortByName();
	Value result;
	Object_list *pObjList = result.InitAsList(env);
	pObjList->Reserve(symbolList.size());
	foreach_const (SymbolList, ppSymbol, symbolList) {
		const Symbol *pSymbol = *ppSymbol;
		pObjList->AddFast(Value(pSymbol));
	}
	pObjList->SetValueType(VTYPE_symbol);
	return result;
}

// dirtype(obj?):[noesc]
Gura_DeclareFunction(dirtype)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "obj", VTYPE_any, OCCUR_ZeroOrOnce);
	DeclareAttr(Gura_Symbol(noesc));
	//DeclareAttr(Gura_Symbol(nosort));
	AddHelp(
		Gura_Symbol(en),
		"Returns a symbol list of value types\n"
		"that are assigned in the environment of `obj`.\n"
		"\n"
		"In default, when the `obj` is an instance of a class,\n"
		"it also searches symbols assigned in the class that it belongs to and its parent classes.\n"
		"Specifying attribute `:noesc` inhibits avoids behavior.\n");
}

Gura_ImplementFunction(dirtype)
{
	bool escalateFlag = !arg.IsSet(Gura_Symbol(noesc));
	bool sortFlag = !arg.IsSet(Gura_Symbol(nosort));
	SymbolList symbolList;
	if (arg.IsValid(0)) {
		SymbolSet symbols;
		arg.GetValue(0).DirValueType(symbols, escalateFlag);
		foreach_const (SymbolSet, ppSymbol, symbols) {
			const Symbol *pSymbol = *ppSymbol;
			symbolList.push_back(pSymbol);
		}
	} else {
		foreach_const (ValueTypeMap, iter, env.GetBottomFrame()->GetValueTypeMap()) {
			const Symbol *pSymbol = iter->first;
			symbolList.push_back(pSymbol);
		}
	}
	if (sortFlag) symbolList.SortByName();
	Value result;
	Object_list *pObjList = result.InitAsList(env);
	pObjList->Reserve(symbolList.size());
	foreach_const (SymbolList, ppSymbol, symbolList) {
		const Symbol *pSymbol = *ppSymbol;
		pObjList->AddFast(Value(pSymbol));
	}
	pObjList->SetValueType(VTYPE_symbol);
	return result;
}

//-----------------------------------------------------------------------------
// Module Entries
//-----------------------------------------------------------------------------
Gura_ModuleValidate()
{
	return Version::CheckCoreVersion(GURA_VERSION, nullptr);
}

Gura_ModuleEntry()
{
	// value assignment
	Gura_AssignValue(__name__,	Value("__main__"));
	Gura_AssignValue(nil,		Value::Nil);
	Gura_AssignValueEx("-",		Value::Nil);
	Gura_AssignValueEx("@rem",	Value::Nil); // dummy for MS-DOS batch
	Gura_AssignValueEx("true",	Value(true));
	Gura_AssignValueEx("false",	Value(false));
	Gura_AssignValueEx("*",		Value(new Object_iterator(env, new Iterator_SequenceInf(0))));
	Gura_AssignValue(root,		Value(new Object_environment(env)));
	// Formatting and Printing of Text
	Gura_AssignFunction(format);
	Gura_AssignFunction(print);
	Gura_AssignFunction(printf);
	Gura_AssignFunction(println);
	// Repetition
	Gura_AssignFunction(cross);
	Gura_AssignFunction(for_);
	Gura_AssignFunction(repeat);
	Gura_AssignFunction(while_);
	// Value Generator
	Gura_AssignFunction(consts);
	Gura_AssignFunction(dim);
	Gura_AssignFunction(interval);
	Gura_AssignFunction(range);
	// Flow Control
	Gura_AssignFunction(break_);
	Gura_AssignFunction(continue_);
	Gura_AssignFunction(return_);
	// Branch Sequence
	Gura_AssignFunction(if_);
	Gura_AssignFunction(elsif_);
	Gura_AssignFunction(else_);
	Gura_AssignFunction(end);
	Gura_AssignFunction(switch_);
	Gura_AssignFunction(case_);
	Gura_AssignFunction(default_);
	// Exception Handling
	Gura_AssignFunction(try_);
	Gura_AssignFunction(catch_);
	Gura_AssignFunction(finally_);
	Gura_AssignFunction(raise);
	// Data Converter
	Gura_AssignFunction(chr);
	Gura_AssignFunction(hex);
	Gura_AssignFunction(int_);
	Gura_AssignFunction(ord);
	Gura_AssignFunction(tonumber);
	Gura_AssignFunction(tostring);
	Gura_AssignFunction(tosymbol);
	// Class Operation
	Gura_AssignFunction(class_);
	Gura_AssignFunction(classref);
	Gura_AssignFunction(struct_);
	Gura_AssignFunction(super);
	// Scope Operation
	//Gura_AssignFunction(extern_);
	Gura_AssignFunction(local);
	Gura_AssignFunction(locals);
	Gura_AssignFunction(outers);
	Gura_AssignFunction(public_);
	Gura_AssignFunction(scope);
	// Module Operation
	Gura_AssignFunction(import_);
	Gura_AssignFunction(module);
	// Value Type Information
	Gura_AssignFunctionExx(istype_, "isbinary",		VTYPE_binary);
	Gura_AssignFunctionExx(istype_, "isboolean",	VTYPE_boolean);
	Gura_AssignFunctionExx(istype_, "isclass",		VTYPE_Class);
	Gura_AssignFunctionExx(istype_, "iscomplex",	VTYPE_complex);
	Gura_AssignFunctionExx(istype_, "isdatetime",	VTYPE_datetime);
	Gura_AssignFunctionExx(istype_, "isdict",		VTYPE_dict);
	Gura_AssignFunctionExx(istype_, "isenvironment",VTYPE_environment);
	Gura_AssignFunctionExx(istype_, "iserror",		VTYPE_error);
	Gura_AssignFunctionExx(istype_, "isexpr",		VTYPE_expr);
	Gura_AssignFunctionExx(istype_, "isfunction",	VTYPE_function);
	Gura_AssignFunctionExx(istype_, "isiterator",	VTYPE_iterator);
	Gura_AssignFunctionExx(istype_, "islist",		VTYPE_list);
	Gura_AssignFunctionExx(istype_, "ismodule",		VTYPE_Module);
	Gura_AssignFunctionExx(istype_, "isnil",		VTYPE_nil);
	Gura_AssignFunctionExx(istype_, "isnumber",		VTYPE_number);
	Gura_AssignFunctionExx(istype_, "isrational",	VTYPE_rational);
	Gura_AssignFunctionExx(istype_, "issemaphore",	VTYPE_semaphore);
	Gura_AssignFunctionExx(istype_, "isstring",		VTYPE_string);
	Gura_AssignFunctionExx(istype_, "issymbol",		VTYPE_symbol);
	Gura_AssignFunctionExx(istype_, "istimedelta",	VTYPE_timedelta);
	Gura_AssignFunctionExx(istype_, "isuri",		VTYPE_uri);
	Gura_AssignFunction(isdefined);
	Gura_AssignFunction(isinstance);
	Gura_AssignFunction(istype);
	Gura_AssignFunction(typename_);
	Gura_AssignFunction(undef_);
	// Data Processing
	Gura_AssignFunction(choose);
	Gura_AssignFunction(cond);
	Gura_AssignFunction(conds);
	Gura_AssignFunction(max);
	Gura_AssignFunction(min);
	// Random
	Gura_AssignFunction(rand);
	Gura_AssignFunction(rand_at_normal);
	Gura_AssignFunction(rands);
	Gura_AssignFunction(rands_at_normal);
	Gura_AssignFunction(randseed);
	// Property Listing
	Gura_AssignFunction(dir);
	Gura_AssignFunction(dirtype);
	return true;
}

Gura_ModuleTerminate()
{
}

Gura_EndModuleBody(basement, basement)

Gura_RegisterModule(basement)
