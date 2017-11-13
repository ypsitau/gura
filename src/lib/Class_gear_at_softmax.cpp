//=============================================================================
// Gura class: gear@softmax
//=============================================================================
#include "stdafx.h"

namespace Gura {

static const char *helpDoc_en = R"**(
)**";

//-----------------------------------------------------------------------------
// Gear_Softmax
//-----------------------------------------------------------------------------
Gear_Softmax::GearFuncTable Gear_Softmax::gearFuncTable = {{nullptr}};

bool Gear_Softmax::Apply(Signal &sig, AutoPtr<Array> &pArrayRtn, const Array *pArray) const
{
	GearFuncT gearFunc = gearFuncTable.funcs[pArray->GetElemType()];
	if (gearFunc == nullptr) {
		sig.SetError(ERR_TypeError, "can't apply softmax gear on array@%s",
					 pArray->GetElemTypeName());
		return nullptr;
	}
	return (*gearFunc)(sig, pArrayRtn, pArray, this);
}

String Gear_Softmax::ToString() const
{
	return "softmax";
}

//-----------------------------------------------------------------------------
// Object_gear_at_softmax
//-----------------------------------------------------------------------------
Object_gear_at_softmax::Object_gear_at_softmax(Environment &env, Gear_Softmax *pGear) :
	Object_gear(env.LookupClass(VTYPE_gear_at_softmax), pGear)
{
}

Object *Object_gear_at_softmax::Clone() const
{
	return nullptr;
}
	
//-----------------------------------------------------------------------------
// Implementation of functions
//-----------------------------------------------------------------------------
// gear@softmax(axis?:number):map {block?}
Gura_DeclareFunctionAlias(gear_at_softmax, "gear@softmax")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "axis", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
	SetClassToConstruct(env.LookupClass(VTYPE_gear_at_softmax));
	AddHelp(
		Gura_Symbol(en),
		"Creates a `gear@softmax` instance.\n");
}

Gura_ImplementFunction(gear_at_softmax)
{
	size_t axis = arg.IsValid(0)? arg.GetSizeT(0) : static_cast<size_t>(-1);
	Object_gear_at_softmax *pObj = new Object_gear_at_softmax(env, new Gear_Softmax(axis));
	return ReturnValue(env, arg, Value(pObj));
}

//-----------------------------------------------------------------------------
// Implementation of properties
//-----------------------------------------------------------------------------
// gear@softmax#axis
Gura_DeclareProperty_R(gear_at_softmax, axis)
{
	SetPropAttr(VTYPE_number, FLAG_Nil);
	AddHelp(
		Gura_Symbol(en),
		"");
}

Gura_ImplementPropertyGetter(gear_at_softmax, axis)
{
	const Gear_Softmax *pGear = Object_gear_at_softmax::GetObject(valueThis)->GetGear();
	size_t axis = pGear->GetAxis();
	return (axis == static_cast<size_t>(-1))? Value::Nil : Value(axis);
}

//-----------------------------------------------------------------------------
// Implementation of class
//-----------------------------------------------------------------------------
Class_gear_at_softmax::Class_gear_at_softmax(Environment *pEnvOuter) :
	ClassFundamental(pEnvOuter, VTYPE_gear_at_softmax)
{
}

void Class_gear_at_softmax::DoPrepare(Environment &env)
{
	// Assignment of function
	Gura_AssignFunction(gear_at_softmax);
	// Assignment of properties
	Gura_AssignProperty(gear_at_softmax, axis);
	// Assignment of value
	// help document
	AddHelpTemplate(env, Gura_Symbol(en), helpDoc_en);
}

Object *Class_gear_at_softmax::CreateDescendant(Environment &env, Class *pClass)
{
	return nullptr;
}

}
