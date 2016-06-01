//----------------------------------------------------------------------------
// wxVariantDataCurrency
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Gura interfaces for wxVariantDataCurrency
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Object implementation for wxVariantDataCurrency
//----------------------------------------------------------------------------
Object_wx_VariantDataCurrency::~Object_wx_VariantDataCurrency()
{
}

Object *Object_wx_VariantDataCurrency::Clone() const
{
	return nullptr;
}

String Object_wx_VariantDataCurrency::ToString(bool exprFlag)
{
	String rtn("<wx.VariantDataCurrency:");
	if (GetEntity() == nullptr) {
		rtn += "invalid>";
	} else {
		char buff[64];
		::sprintf(buff, "%p>", GetEntity());
		rtn += buff;
	}
	return rtn;
}

//----------------------------------------------------------------------------
// Method implementation
//----------------------------------------------------------------------------
Gura_DeclareMethod(wx_VariantDataCurrency, wxVariantDataCurrency)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_VariantDataCurrency, wxVariantDataCurrency)
{
	Signal &sig = env.GetSignal();
	Object_wx_VariantDataCurrency *pThis = Object_wx_VariantDataCurrency::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	//pThis->GetEntity()->wxVariantDataCurrency();
	return Value::Nil;
}

Gura_DeclareMethod(wx_VariantDataCurrency, wxVariantDataCurrency_1)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "value", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_VariantDataCurrency, wxVariantDataCurrency_1)
{
	Signal &sig = env.GetSignal();
	Object_wx_VariantDataCurrency *pThis = Object_wx_VariantDataCurrency::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	//int value = arg.GetNumber(0)
	//pThis->GetEntity()->wxVariantDataCurrency();
	return Value::Nil;
}

Gura_DeclareMethod(wx_VariantDataCurrency, GetValue)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_VariantDataCurrency, GetValue)
{
	Signal &sig = env.GetSignal();
	Object_wx_VariantDataCurrency *pThis = Object_wx_VariantDataCurrency::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	//pThis->GetEntity()->GetValue();
	return Value::Nil;
}

Gura_DeclareMethod(wx_VariantDataCurrency, SetValue)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "value", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_VariantDataCurrency, SetValue)
{
	Signal &sig = env.GetSignal();
	Object_wx_VariantDataCurrency *pThis = Object_wx_VariantDataCurrency::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	//int value = arg.GetNumber(0)
	//pThis->GetEntity()->SetValue();
	return Value::Nil;
}

Gura_DeclareMethod(wx_VariantDataCurrency, Eq)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "data", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_VariantDataCurrency, Eq)
{
	Signal &sig = env.GetSignal();
	Object_wx_VariantDataCurrency *pThis = Object_wx_VariantDataCurrency::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	//int data = arg.GetNumber(0)
	//pThis->GetEntity()->Eq();
	return Value::Nil;
}

Gura_DeclareMethod(wx_VariantDataCurrency, Write)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "str", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_VariantDataCurrency, Write)
{
	Signal &sig = env.GetSignal();
	Object_wx_VariantDataCurrency *pThis = Object_wx_VariantDataCurrency::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	//int str = arg.GetNumber(0)
	//pThis->GetEntity()->Write();
	return Value::Nil;
}

Gura_DeclareMethod(wx_VariantDataCurrency, Clone)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_VariantDataCurrency, Clone)
{
	Signal &sig = env.GetSignal();
	Object_wx_VariantDataCurrency *pThis = Object_wx_VariantDataCurrency::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	//pThis->GetEntity()->Clone();
	return Value::Nil;
}

Gura_DeclareMethod(wx_VariantDataCurrency, GetType)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_VariantDataCurrency, GetType)
{
	Signal &sig = env.GetSignal();
	Object_wx_VariantDataCurrency *pThis = Object_wx_VariantDataCurrency::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	//pThis->GetEntity()->GetType();
	return Value::Nil;
}

Gura_DeclareMethod(wx_VariantDataCurrency, GetAsAny)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "any", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_VariantDataCurrency, GetAsAny)
{
	Signal &sig = env.GetSignal();
	Object_wx_VariantDataCurrency *pThis = Object_wx_VariantDataCurrency::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	//int any = arg.GetNumber(0)
	//pThis->GetEntity()->GetAsAny();
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Class implementation for wxVariantDataCurrency
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_VariantDataCurrency)
{
	Gura_AssignMethod(wx_VariantDataCurrency, wxVariantDataCurrency);
	Gura_AssignMethod(wx_VariantDataCurrency, wxVariantDataCurrency_1);
	Gura_AssignMethod(wx_VariantDataCurrency, GetValue);
	Gura_AssignMethod(wx_VariantDataCurrency, SetValue);
	Gura_AssignMethod(wx_VariantDataCurrency, Eq);
	Gura_AssignMethod(wx_VariantDataCurrency, Write);
	Gura_AssignMethod(wx_VariantDataCurrency, Clone);
	Gura_AssignMethod(wx_VariantDataCurrency, GetType);
	Gura_AssignMethod(wx_VariantDataCurrency, GetAsAny);
}

Gura_ImplementDescendantCreator(wx_VariantDataCurrency)
{
	return new Object_wx_VariantDataCurrency((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
