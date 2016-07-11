//=============================================================================
// Class_aliases.cpp
//=============================================================================
#include "stdafx.h"

Gura_BeginModuleScope(doxygen)

//-----------------------------------------------------------------------------
// Object_aliases
//-----------------------------------------------------------------------------
Object_aliases::~Object_aliases()
{
}

Object *Object_aliases::Clone() const
{
	return nullptr;
}

bool Object_aliases::DoDirProp(Environment &env, SymbolSet &symbols)
{
#if 0
	Signal &sig = GetSignal();
	if (!Object::DoDirProp(env, symbols)) return false;
	symbols.insert(Gura_UserSymbol(elem));
#endif
	return true;
}

Value Object_aliases::DoGetProp(Environment &env, const Symbol *pSymbol,
							const SymbolSet &attrs, bool &evaluatedFlag)
{
#if 0
	evaluatedFlag = true;
	if (pSymbol->IsIdentical(Gura_UserSymbol(elem))) {
		return _pElem.IsNull()? Value::Nil : Value(new Object_elem(_pElem->Reference()));
	}
	evaluatedFlag = false;
#endif
	return Value::Nil;
}

String Object_aliases::ToString(bool exprFlag)
{
	String rtn;
	rtn += "<doxygen.aliases:";
	rtn += ">";
	return rtn;
}

//----------------------------------------------------------------------------
// Constructor
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Methods
//----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Class implementation for doxygen.aliases
//-----------------------------------------------------------------------------
Gura_ImplementUserClassWithCast(aliases)
{
}

Gura_ImplementCastFrom(aliases)
{
	Gura_UserClass(configuration)->CastFrom(env, value, pDecl);
	if (value.IsType(VTYPE_configuration)) {
		const Configuration *pCfg = Object_configuration::GetObject(value)->GetConfiguration();
		AutoPtr<Aliases> pAliases(pCfg->MakeAliases(env));
		if (pAliases.IsNull()) return false;
		value = Value(new Object_aliases(pAliases.release()));
		return true;
	}
	return false;
}

Gura_ImplementCastTo(aliases)
{
	return false;
}

Gura_EndModuleScope(doxygen)
