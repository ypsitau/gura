//
// Object_error
//

#include "stdafx.h"

namespace Gura {

//-----------------------------------------------------------------------------
// Object_error
//-----------------------------------------------------------------------------
Object_error::Object_error(const Object_error &obj) : Object(obj), _err(obj._err)
{
}

Object *Object_error::Clone() const
{
	return new Object_error(*this);
}

bool Object_error::DoDirProp(Environment &env, Signal sig, SymbolSet &symbols)
{
	if (!Object::DoDirProp(env, sig, symbols)) return false;
	symbols.insert(Gura_Symbol(text));
	symbols.insert(Gura_Symbol(trace));
	return true;
}

Value Object_error::DoGetProp(Environment &env, Signal sig, const Symbol *pSymbol,
						const SymbolSet &attrs, bool &evaluatedFlag)
{
	evaluatedFlag = true;
	if (pSymbol->IsIdentical(Gura_Symbol(text))) {
		bool lineInfoFlag = attrs.IsSet(Gura_Symbol(lineno));
		return Value(env, _err.MakeText(lineInfoFlag));
	} else if (pSymbol->IsIdentical(Gura_Symbol(trace))) {
		Value value;
		ValueList &valList = value.InitAsList(env);
		AutoPtr<ExprOwner> pExprOwner(new ExprOwner());
		_err.GetExprCauseOwner().ExtractTrace(*pExprOwner);
		foreach_const (ExprOwner, ppExpr, *pExprOwner) {
			const Expr *pExpr = *ppExpr;
			valList.push_back(Value(new Object_expr(env, pExpr->Reference())));
		}
		return value;
	}
	evaluatedFlag = false;
	return Value::Null;
}

String Object_error::ToString(Signal sig, bool exprFlag)
{
	String rtn;
	rtn += "<error:";
	rtn += _err.GetTypeName();
	rtn += ">";
	return rtn;
}

//-----------------------------------------------------------------------------
// Gura interfaces for Object_error
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Classs implementation
//-----------------------------------------------------------------------------
Class_error::Class_error(Environment *pEnvOuter) : Class(pEnvOuter, VTYPE_error)
{
}

void Class_error::Prepare(Environment &env)
{
}

Object *Class_error::CreateDescendant(Environment &env, Signal sig, Class *pClass)
{
	GURA_ERROREND(env, "this function must not be called");
	return NULL;
}

}
