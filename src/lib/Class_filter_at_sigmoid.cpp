//=============================================================================
// Gura class: filter@sigmoid
//=============================================================================
#include "stdafx.h"

namespace Gura {

static const char *helpDoc_en = R"**(
)**";

//-----------------------------------------------------------------------------
// Filter_Sigmoid
//-----------------------------------------------------------------------------
Filter_Sigmoid::FilterFuncTable Filter_Sigmoid::filterFuncTable = {{nullptr}};

bool Filter_Sigmoid::Apply(Signal &sig, AutoPtr<Array> &pArrayRtn, const Array *pArray) const
{
	FilterFuncT filterFunc = filterFuncTable.funcs[pArray->GetElemType()];
	if (filterFunc == nullptr) {
		sig.SetError(ERR_TypeError, "can't apply sigmoid filter on array@%s",
					 pArray->GetElemTypeName());
		return nullptr;
	}
	return (*filterFunc)(sig, pArrayRtn, pArray, this);
}

String Filter_Sigmoid::ToString() const
{
	return "sigmoid";
}

//-----------------------------------------------------------------------------
// Object_filter_at_sigmoid
//-----------------------------------------------------------------------------
Value Object_filter_at_sigmoid::valueConst;

Object_filter_at_sigmoid::Object_filter_at_sigmoid(Environment &env, Filter_Sigmoid *pFilter) :
	Object_filter(env.LookupClass(VTYPE_filter_at_sigmoid), pFilter)
{
}

Object *Object_filter_at_sigmoid::Clone() const
{
	return nullptr;
}
	
//-----------------------------------------------------------------------------
// Implementation of functions
//-----------------------------------------------------------------------------
// filter@sigmoid() {block?}
Gura_DeclareFunctionAlias(filter_at_sigmoid, "filter@sigmoid")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
	SetClassToConstruct(env.LookupClass(VTYPE_filter_at_sigmoid));
	AddHelp(
		Gura_Symbol(en),
		"Creates a `filter@sigmoid` instance.\n");
}

Gura_ImplementFunction(filter_at_sigmoid)
{
	return ReturnValue(env, arg, Object_filter_at_sigmoid::valueConst);
}

//-----------------------------------------------------------------------------
// Implementation of class
//-----------------------------------------------------------------------------
Class_filter_at_sigmoid::Class_filter_at_sigmoid(Environment *pEnvOuter) :
	ClassFundamental(pEnvOuter, VTYPE_filter_at_sigmoid)
{
}

void Class_filter_at_sigmoid::DoPrepare(Environment &env)
{
	// Assignment of function
	Gura_AssignFunction(filter_at_sigmoid);
	// Assignment of value
	Object_filter_at_sigmoid::valueConst = Value(new Object_filter_at_sigmoid(env, new Filter_Sigmoid()));
	// help document
	AddHelpTemplate(env, Gura_Symbol(en), helpDoc_en);
}

Object *Class_filter_at_sigmoid::CreateDescendant(Environment &env, Class *pClass)
{
	return nullptr;
}

}
