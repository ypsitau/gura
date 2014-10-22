//=============================================================================
// Gura class: function
//=============================================================================
#include "stdafx.h"

namespace Gura {

//-----------------------------------------------------------------------------
// Object_function
//-----------------------------------------------------------------------------
bool Object_function::IsFunction() const { return true; }

Object_function::~Object_function()
{
}

bool Object_function::DoDirProp(Environment &env, Signal sig, SymbolSet &symbols)
{
	Class *pClass = GetFunction()->GetClassToConstruct();
	if (pClass != NULL) return pClass->DoDirProp(env, sig, symbols);
	if (!Object::DoDirProp(env, sig, symbols)) return false;
	symbols.insert(Gura_Symbol(decls));
	symbols.insert(Gura_Symbol(expr));
	symbols.insert(Gura_Symbol(format));
	symbols.insert(Gura_Symbol(fullname));
	symbols.insert(Gura_Symbol(name));
	symbols.insert(Gura_Symbol(symbol));
	return true;
}

Value Object_function::DoGetProp(Environment &env, Signal sig, const Symbol *pSymbol,
							const SymbolSet &attrs, bool &evaluatedFlag)
{
	evaluatedFlag = true;
	if (pSymbol->IsIdentical(Gura_Symbol(decls))) {
		Iterator *pIterator = new Iterator_declaration(GetFunction()->GetDeclOwner().Reference());
		return Value(new Object_iterator(env, pIterator));
	} else if (pSymbol->IsIdentical(Gura_Symbol(expr))) {
		if (!GetFunction()->IsCustom()) return Value::Null;
		const FunctionCustom *pFuncCustom =
						dynamic_cast<const FunctionCustom *>(GetFunction());
		return Value(new Object_expr(env, Expr::Reference(pFuncCustom->GetExprBody())));
	} else if (pSymbol->IsIdentical(Gura_Symbol(format))) {
		String str = MakePrefix(sig);
		if (sig.IsSignalled()) return Value::Null;
		str += _pFunc->ToString();
		return Value(str);
	} else if (pSymbol->IsIdentical(Gura_Symbol(fullname))) {
		String fullName = GetFullName(sig);
		if (sig.IsSignalled()) return Value::Null;
		return Value(fullName);
	} else if (pSymbol->IsIdentical(Gura_Symbol(name))) {
		return Value(GetName());
	} else if (pSymbol->IsIdentical(Gura_Symbol(symbol))) {
		return Value(GetFunction()->GetSymbol());
	}
	evaluatedFlag = false;
	return Value::Null;
}

Value Object_function::DoSetProp(Environment &env, Signal sig, const Symbol *pSymbol, const Value &value,
							const SymbolSet &attrs, bool &evaluatedFlag)
{
	evaluatedFlag = true;
	if (pSymbol->IsIdentical(Gura_Symbol(symbol)) ||
						pSymbol->IsIdentical(Gura_Symbol(name))) {
		if (value.Is_symbol()) {
			GetFunction()->SetSymbol(value.GetSymbol());
		} else if (value.Is_string()) {
			GetFunction()->SetSymbol(Symbol::Add(value.GetString()));
		} else {
			sig.SetError(ERR_TypeError, "symbol or string must be specified");
			return Value::Null;
		}
		return value;
	} else if (pSymbol->IsIdentical(Gura_Symbol(expr))) {
		if (!GetFunction()->IsCustom()) {
			sig.SetError(ERR_TypeError, "not a custom function");
			return Value::Null;
		}
		if (!value.Is_expr()) {
			sig.SetError(ERR_TypeError, "expr must be specified");
			return Value::Null;
		}
		FunctionCustom *pFuncCustom = dynamic_cast<FunctionCustom *>(GetFunction());
		pFuncCustom->SetExprBody(Expr::Reference(value.GetExpr()));
		return value;
	}
	return DoGetProp(env, sig, pSymbol, attrs, evaluatedFlag);
}

bool Object_function::IsLeader() const
{
	return _pFunc->GetLeaderFlag();
}

bool Object_function::IsTrailer() const
{
	return _pFunc->GetTrailerFlag();
}

bool Object_function::IsFinalizer() const
{
	return _pFunc->GetFinalizerFlag();
}

bool Object_function::IsEndMarker() const
{
	return _pFunc->GetEndMarkerFlag();
}

OccurPattern Object_function::GetBlockOccurPattern() const
{
	return _pFunc->GetBlockOccurPattern();
}

Value Object_function::DoCall(Environment &env, Signal sig, Args &args)
{
	if (args.GetThis().IsInvalid() ||
					(args.GetThis().IsModule() && _valueThis.IsValid())) {
		args.SetThis(_valueThis);
	}
	return _pFunc->Call(env, sig, args);
}

Value Object_function::Eval(Environment &env, Signal sig, ValueList &valListArg) const
{
	_pFunc->GetDeclOwner().Compensate(env, sig, valListArg);
	if (sig.IsSignalled()) return Value::Null;
	AutoPtr<Args> pArgs(new Args());
	pArgs->SetThis(_valueThis);
	pArgs->SetValueListArg(valListArg);
	return _pFunc->Eval(env, sig, *pArgs);
}

Object *Object_function::Clone() const
{
	return new Object_function(*this);
}

String Object_function::GetFullName(Signal sig)
{
	String str = MakePrefix(sig);
	if (sig.IsSignalled()) return String("");
	str += _pFunc->GetName();
	return str;
}

String Object_function::ToString(bool exprFlag)
{
	Signal sig;
	String str = MakePrefix(sig);
	if (sig.IsSignalled()) return String("");
	str += _pFunc->ToString();
	return str;
}

void Object_function::GatherFollower(Environment::Frame *pFrame, EnvironmentSet &envSet)
{
	if (_cntRef == 1) {
		_pFunc->GatherFollower(pFrame, envSet);
	}
}

String Object_function::MakePrefix(Signal sig) const
{
	String str;
	if (_valueThis.IsInvalid()) return str;
	if (_valueThis.IsPrimitive()) {
		const Environment &env = *this;
		const Class *pClass = env.LookupClass(_valueThis.GetValueType());
		if (pClass != NULL) {
			str += pClass->GetName();
			str += "#";
			return str;
		}
	}
	const Fundamental *pFund = _valueThis.ExtractFundamental(sig);
	if (sig.IsSignalled()) return str;
	if (pFund->IsModule()) {
		str += dynamic_cast<const Module *>(pFund)->GetName();
		str += ".";
	} else if (pFund->IsClass()) {
		const Class *pClass = dynamic_cast<const Class *>(pFund);
		str += pClass->GetName();
		str += (_pFunc->GetType() == FUNCTYPE_Instance)? "#" : ".";
	} else if (pFund->IsObject()) {
		const Object *pObject = dynamic_cast<const Object *>(pFund);
		const Class *pClass = pObject->GetClass();
		str += pClass->GetName();
		str += "#";
	}
	return str;
}

//-----------------------------------------------------------------------------
// Implementation of functions
//-----------------------------------------------------------------------------
// function(`args*) {block}
Gura_DeclareFunction(function)
{
	DeclareArg(env, "args", VTYPE_quote, OCCUR_ZeroOrMore);
	SetClassToConstruct(env.LookupClass(VTYPE_function));
	DeclareBlock(OCCUR_Once);
}

Gura_ImplementFunction(function)
{
	const Expr_Block *pExprBlock = args.GetBlock(env, sig);
	if (sig.IsSignalled()) return Value::Null;
	const ExprOwner *pExprOwnerParam = pExprBlock->GetExprOwnerParam();
	ExprOwner *pExprOwnerArg = NULL;
	if (pExprOwnerParam == NULL) {
		pExprOwnerArg = new ExprOwner();
		foreach_const (ValueList, pValue, args.GetList(0)) {
			pExprOwnerArg->push_back(pValue->GetExpr()->Reference());
		}
		if (pExprOwnerArg->empty()) {
			pExprBlock->GatherSimpleLambdaArgs(*pExprOwnerArg);
		}
	} else if (!args.GetList(0).empty()) {
		sig.SetError(ERR_SyntaxError, "argument list conflicts with block parameter.");
		return Value::Null;
	} else {
		pExprOwnerArg = pExprOwnerParam->Reference();
	}
	AutoPtr<FunctionCustom> pFunc(new FunctionCustom(env,
			Gura_Symbol(_anonymous_), Expr::Reference(pExprBlock), FUNCTYPE_Function));
	AutoPtr<Args> pArgsSub(new Args());
	pArgsSub->SetExprOwnerArg(pExprOwnerArg);
	pArgsSub->SetAttrs(args.GetAttrs());
	if (!pFunc->CustomDeclare(env, sig, SymbolSet::Null, *pArgsSub)) return Value::Null;
	return Value(new Object_function(env, pFunc.release()));
}

//-----------------------------------------------------------------------------
// Implementation of methods
//-----------------------------------------------------------------------------
// function#addhelp(lang:symbol, format:string, help:string):map
Gura_DeclareMethod(function, addhelp)
{
	SetMode(RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "lang", VTYPE_symbol);
	DeclareArg(env, "format", VTYPE_string);
	DeclareArg(env, "help", VTYPE_string);
}

Gura_ImplementMethod(function, addhelp)
{
	Object_function *pThis = Object_function::GetThisObj(args);
	pThis->GetFunction()->AddHelp(args.GetSymbol(0), args.GetString(1), args.GetString(2));
	return Value::Null;
}

// function#mathdiff(var?:symbol)
Gura_DeclareMethod(function, mathdiff)
{
	SetMode(RSLTMODE_Reduce, FLAG_None);
	DeclareArg(env, "var", VTYPE_symbol, OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(function, mathdiff)
{
	Object_function *pThis = Object_function::GetThisObj(args);
	const Function *pFunc = pThis->GetFunction();
	const DeclarationOwner &declOwner = pFunc->GetDeclOwner();
	const Symbol *pSymbol = NULL;
	if (args.Is_symbol(0)) {
		pSymbol = args.GetSymbol(0);
	} else if (declOwner.empty()) {
		sig.SetError(ERR_ValueError, "variable symbol must be specified");
		return Value::Null;
	} else {
		pSymbol = declOwner.front()->GetSymbol();
	}
	AutoPtr<Expr> pExprArg(new Expr_Identifier(pSymbol));
	AutoPtr<Expr> pExprDiff(pFunc->MathDiff(env, sig, pExprArg.get(), pSymbol));
	if (sig.IsSignalled()) return Value::Null;
	AutoPtr<FunctionCustom> pFuncDiff(new FunctionCustom(env,
			Gura_Symbol(_anonymous_), pExprDiff.release(), FUNCTYPE_Function));
	pFuncDiff->CopyDeclare(*pFunc);
	return Value(new Object_function(env, pFuncDiff.release()));
}

// function#gethelp(lang?:symbol):map
Gura_DeclareMethod(function, gethelp)
{
	SetMode(RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "lang", VTYPE_symbol, OCCUR_ZeroOrOnce);
	AddHelp(Gura_Symbol(en), Help::FMT_markdown,
	"Gets a help object of the specified function object.\n"
	"`lang` is a symbol that indicates a language in which the help is written.\n"
	"If help doesn't exist, it returns nil.\n"
	);
}

Gura_ImplementMethod(function, gethelp)
{
	Object_function *pThis = Object_function::GetThisObj(args);
	const Symbol *pSymbol = args.Is_symbol(0)? args.GetSymbol(0) : NULL;
	const Help *pHelp = pThis->GetFunction()->GetHelp(pSymbol);
	if (pHelp == NULL) return Value::Null;
	return Value(new Object_help(env, pHelp->Reference()));
}

// function#help(lang?:symbol):map:void
Gura_DeclareMethod(function, help)
{
	SetMode(RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "lang", VTYPE_symbol, OCCUR_ZeroOrOnce);
	AddHelp(Gura_Symbol(en), Help::FMT_markdown,
	"Print a help message for the specified function object.\n"
	"`lang` is a symbol that indicates a language in which the help is written.\n"
	"If help message doesn't exist, it only prints the function's format.\n"
	);
}

Gura_ImplementMethod(function, help)
{
	Object_function *pThis = Object_function::GetThisObj(args);
	const Symbol *pSymbol = args.Is_symbol(0)? args.GetSymbol(0) : NULL;
	HelpPresenter::Present(env, sig, pThis->ToString(true).c_str(),
									pThis->GetFunction()->GetHelp(pSymbol));
	return Value::Null;
}

//-----------------------------------------------------------------------------
// Implementation of class
//-----------------------------------------------------------------------------
Class_function::Class_function(Environment *pEnvOuter) : Class(pEnvOuter, VTYPE_function)
{
}

void Class_function::Prepare(Environment &env)
{
	Gura_AssignFunction(function);
	Gura_AssignFunctionEx(function, "&");
	Gura_AssignMethod(function, addhelp);
	Gura_AssignMethod(function, mathdiff);
	Gura_AssignMethod(function, gethelp);
	Gura_AssignMethod(function, help);
}

bool Class_function::CastFrom(Environment &env, Signal sig, Value &value, const Declaration *pDecl)
{
	if (value.Is_expr()) {
		Expr_Block *pExprBlock = value.GetExpr()->ToExprBlock();
		AutoPtr<FunctionCustom> pFunc(FunctionCustom::CreateBlockFunc(env, sig,
						Gura_Symbol(_anonymous_), pExprBlock, FUNCTYPE_Function));
		if (sig.IsSignalled()) return false;
		value = Value(new Object_function(env, pFunc.release()));
		return true;
	}
	return false;
}

bool Class_function::Serialize(Environment &env, Signal sig, Stream &stream, const Value &value) const
{
	return false;
}

bool Class_function::Deserialize(Environment &env, Signal sig, Stream &stream, Value &value) const
{
	return false;
}

Object *Class_function::CreateDescendant(Environment &env, Signal sig, Class *pClass)
{
	GURA_ERROREND(env, "this function must not be called");
	return NULL;
}

}
