#include "stdafx.h"

Gura_BeginModuleScope(ceres)

//-----------------------------------------------------------------------------
// Object_NumericDiffCostFunction implementation
//-----------------------------------------------------------------------------
Object_NumericDiffCostFunction::Object_NumericDiffCostFunction(Class *pClass) :
								Object_CostFunction(pClass)
{
}

String Object_NumericDiffCostFunction::ToString(bool exprFlag)
{
	String str = "<ceres.NumericDiffCostFunction";
	if (_pCostFunction == nullptr) str += ":invalid";
	str += ">";
	return str;
}

//-----------------------------------------------------------------------------
// Implementation of properties
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Implementation of function
//-----------------------------------------------------------------------------
// ceres.NumericDiffCostFunction(method:number, numResiduals:number, parameterBlockSizes+:number) {block?}
Gura_DeclareFunction(NumericDiffCostFunction)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "method", VTYPE_number);
	DeclareArg(env, "numResiduals", VTYPE_number);
	DeclareArg(env, "parameterBlockSizes", VTYPE_number, OCCUR_OnceOrMore);
	DeclareBlock(OCCUR_ZeroOrOnce);
	SetClassToConstruct(Gura_UserClass(NumericDiffCostFunction));
	AddHelp(
		Gura_Symbol(en),
		"");

}

Gura_ImplementFunction(NumericDiffCostFunction)
{
	Object_NumericDiffCostFunction *pObj = Object_NumericDiffCostFunction::GetObjectThis(arg);
	if (pObj == nullptr) {
		env.SetError(ERR_ValueError, "pure class can not be instantiated");
		return Value::Nil;
	}
	std::unique_ptr<NumericDiffCostFunctorCustom> pCostFunctor(new NumericDiffCostFunctorCustom(pObj->Reference()));
	ceres::NumericDiffMethodType method = static_cast<ceres::NumericDiffMethodType>(arg.GetInt(0));
	std::unique_ptr<ceres::DynamicCostFunction> pCostFunction;
	if (method == ceres::CENTRAL) {
		pCostFunction.reset(
			new ceres::DynamicNumericDiffCostFunction<NumericDiffCostFunctorCustom, ceres::CENTRAL>(
				pCostFunctor.release()));
	} else if (method == ceres::FORWARD) {
		pCostFunction.reset(
			new ceres::DynamicNumericDiffCostFunction<NumericDiffCostFunctorCustom, ceres::FORWARD>(
				pCostFunctor.release()));
	} else if (method == ceres::RIDDERS) {
		pCostFunction.reset(
			new ceres::DynamicNumericDiffCostFunction<NumericDiffCostFunctorCustom, ceres::RIDDERS>(
				pCostFunctor.release()));
	} else {
		env.SetError(ERR_ValueError, "invalid value for method");
		return Value::Nil;
	}
	pCostFunction->SetNumResiduals(arg.GetInt(1));
	foreach_const (ValueList, pValue, arg.GetList(2)) {
		pCostFunction->AddParameterBlock(pValue->GetInt());
	}
	pObj->SetCostFunction(pCostFunction.release());
	return ReturnValue(env, arg, arg.GetValueThis());
}

//-----------------------------------------------------------------------------
// Implementation of class ceres.NumericDiffCostFunction
//-----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(NumericDiffCostFunction)
{
	// Assignment of properties
	// Assignment of function
	Gura_AssignFunction(NumericDiffCostFunction);
}

Gura_ImplementDescendantCreator(NumericDiffCostFunction)
{
	return new Object_NumericDiffCostFunction((pClass == nullptr)? this : pClass);
}

Gura_EndModuleScope(ceres)
