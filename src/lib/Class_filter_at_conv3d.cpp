//=============================================================================
// Gura class: filter@conv3d
//=============================================================================
#include "stdafx.h"

namespace Gura {

static const char *helpDoc_en = R"**(
)**";

//-----------------------------------------------------------------------------
// Filter_Conv3d
//-----------------------------------------------------------------------------
Filter_Conv3d::FilterFuncTable Filter_Conv3d::filterFuncTable = {{{nullptr}}};

bool Filter_Conv3d::Apply(Signal &sig, AutoPtr<Array> &pArrayRtn, const Array *pArray) const
{
	FilterFuncT filterFunc = filterFuncTable.funcs[pArray->GetElemType()][Array::ETYPE_None];
	if (filterFunc == nullptr) {
		sig.SetError(ERR_TypeError, "can't apply 3-dimension convolution filter on array@%s",
					 pArray->GetElemTypeName());
		return nullptr;
	}
	return (*filterFunc)(sig, pArrayRtn, pArray, this);
}

String Filter_Conv3d::ToString() const
{
	return "conv3d";
}

//-----------------------------------------------------------------------------
// Object_filter_at_conv3d
//-----------------------------------------------------------------------------
Object_filter_at_conv3d::Object_filter_at_conv3d(Environment &env, Filter_Conv3d *pFilter) :
	Object_filter(env.LookupClass(VTYPE_filter_at_conv3d), pFilter)
{
}

Object *Object_filter_at_conv3d::Clone() const
{
	return nullptr;
}
	
//-----------------------------------------------------------------------------
// Implementation of functions
//-----------------------------------------------------------------------------
// filter@conv3d():map {block?}
Gura_DeclareFunctionAlias(filter_at_conv3d, "filter@conv3d")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareBlock(OCCUR_ZeroOrOnce);
	SetClassToConstruct(env.LookupClass(VTYPE_filter_at_conv3d));
	AddHelp(
		Gura_Symbol(en),
		"Creates a `filter@conv3d` instance.\n");
}

Gura_ImplementFunction(filter_at_conv3d)
{
	Object_filter_at_conv3d *pObj = new Object_filter_at_conv3d(env, new Filter_Conv3d());
	return ReturnValue(env, arg, Value(pObj));
}

//-----------------------------------------------------------------------------
// Implementation of class
//-----------------------------------------------------------------------------
Class_filter_at_conv3d::Class_filter_at_conv3d(Environment *pEnvOuter) :
	ClassFundamental(pEnvOuter, VTYPE_filter_at_conv3d)
{
}

void Class_filter_at_conv3d::DoPrepare(Environment &env)
{
	// Assignment of function
	Gura_AssignFunction(filter_at_conv3d);
	// help document
	AddHelpTemplate(env, Gura_Symbol(en), helpDoc_en);
}

Object *Class_filter_at_conv3d::CreateDescendant(Environment &env, Class *pClass)
{
	return nullptr;
}

}
