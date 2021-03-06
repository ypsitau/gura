//----------------------------------------------------------------------------
// wxTextAttrDimension
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Gura interfaces for wxTextAttrDimension
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Object implementation for wxTextAttrDimension
//----------------------------------------------------------------------------
Object_wx_TextAttrDimension::~Object_wx_TextAttrDimension()
{
}

Object *Object_wx_TextAttrDimension::Clone() const
{
	return nullptr;
}

String Object_wx_TextAttrDimension::ToString(bool exprFlag)
{
	String rtn("<wx.TextAttrDimension:");
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
// Constructor implementation
//----------------------------------------------------------------------------
Gura_DeclareFunctionAlias(__TextAttrDimension, "TextAttrDimension")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	SetClassToConstruct(Gura_UserClass(wx_TextAttrDimension));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(__TextAttrDimension)
{
	//wxTextAttrDimension();
	return Value::Nil;
}

Gura_DeclareFunctionAlias(__TextAttrDimension_1, "TextAttrDimension_1")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "value", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "units", VTYPE_number, OCCUR_Once);
	SetClassToConstruct(Gura_UserClass(wx_TextAttrDimension));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(__TextAttrDimension_1)
{
	//int value = arg.GetNumber(0)
	//wxTextAttrUnits units = arg.GetNumber(1)
	//wxTextAttrDimension(value, units);
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Method implementation
//----------------------------------------------------------------------------
Gura_DeclareMethodAlias(wx_TextAttrDimension, __Reset, "Reset")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_TextAttrDimension, __Reset)
{
	Object_wx_TextAttrDimension *pThis = Object_wx_TextAttrDimension::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->Reset();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_TextAttrDimension, __EqPartial, "EqPartial")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "dim", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "weakTest", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_TextAttrDimension, __EqPartial)
{
	Object_wx_TextAttrDimension *pThis = Object_wx_TextAttrDimension::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxTextAttrDimension& dim = arg.GetNumber(0)
	//bool weakTest = arg.GetNumber(1)
	//bool _rtn = pThis->GetEntity()->EqPartial(dim, weakTest);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_TextAttrDimension, __Apply, "Apply")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "dim", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "compareWith", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_TextAttrDimension, __Apply)
{
	Object_wx_TextAttrDimension *pThis = Object_wx_TextAttrDimension::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxTextAttrDimension& dim = arg.GetNumber(0)
	//const wxTextAttrDimension* compareWith = arg.GetNumber(1)
	//bool _rtn = pThis->GetEntity()->Apply(dim, compareWith);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_TextAttrDimension, __CollectCommonAttributes, "CollectCommonAttributes")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "attr", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "clashingAttr", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "absentAttr", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_TextAttrDimension, __CollectCommonAttributes)
{
	Object_wx_TextAttrDimension *pThis = Object_wx_TextAttrDimension::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxTextAttrDimension& attr = arg.GetNumber(0)
	//wxTextAttrDimension& clashingAttr = arg.GetNumber(1)
	//wxTextAttrDimension& absentAttr = arg.GetNumber(2)
	//pThis->GetEntity()->CollectCommonAttributes(attr, clashingAttr, absentAttr);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_TextAttrDimension, __GetValue, "GetValue")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_TextAttrDimension, __GetValue)
{
	Object_wx_TextAttrDimension *pThis = Object_wx_TextAttrDimension::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int _rtn = pThis->GetEntity()->GetValue();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_TextAttrDimension, __GetValueMM, "GetValueMM")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_TextAttrDimension, __GetValueMM)
{
	Object_wx_TextAttrDimension *pThis = Object_wx_TextAttrDimension::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//float _rtn = pThis->GetEntity()->GetValueMM();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_TextAttrDimension, __SetValueMM, "SetValueMM")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "value", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_TextAttrDimension, __SetValueMM)
{
	Object_wx_TextAttrDimension *pThis = Object_wx_TextAttrDimension::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//float value = arg.GetNumber(0)
	//pThis->GetEntity()->SetValueMM(value);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_TextAttrDimension, __SetValue, "SetValue")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "value", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_TextAttrDimension, __SetValue)
{
	Object_wx_TextAttrDimension *pThis = Object_wx_TextAttrDimension::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int value = arg.GetNumber(0)
	//pThis->GetEntity()->SetValue(value);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_TextAttrDimension, __SetValue_1, "SetValue_1")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "value", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "flags", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_TextAttrDimension, __SetValue_1)
{
	Object_wx_TextAttrDimension *pThis = Object_wx_TextAttrDimension::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int value = arg.GetNumber(0)
	//wxTextAttrDimensionFlags flags = arg.GetNumber(1)
	//pThis->GetEntity()->SetValue(value, flags);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_TextAttrDimension, __SetValue_2, "SetValue_2")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "value", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "units", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_TextAttrDimension, __SetValue_2)
{
	Object_wx_TextAttrDimension *pThis = Object_wx_TextAttrDimension::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int value = arg.GetNumber(0)
	//wxTextAttrUnits units = arg.GetNumber(1)
	//pThis->GetEntity()->SetValue(value, units);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_TextAttrDimension, __SetValue_3, "SetValue_3")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "dim", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_TextAttrDimension, __SetValue_3)
{
	Object_wx_TextAttrDimension *pThis = Object_wx_TextAttrDimension::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxTextAttrDimension& dim = arg.GetNumber(0)
	//pThis->GetEntity()->SetValue(dim);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_TextAttrDimension, __GetUnits, "GetUnits")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_TextAttrDimension, __GetUnits)
{
	Object_wx_TextAttrDimension *pThis = Object_wx_TextAttrDimension::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxTextAttrUnits _rtn = pThis->GetEntity()->GetUnits();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_TextAttrDimension, __SetUnits, "SetUnits")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "units", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_TextAttrDimension, __SetUnits)
{
	Object_wx_TextAttrDimension *pThis = Object_wx_TextAttrDimension::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxTextAttrUnits units = arg.GetNumber(0)
	//pThis->GetEntity()->SetUnits(units);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_TextAttrDimension, __GetPosition, "GetPosition")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_TextAttrDimension, __GetPosition)
{
	Object_wx_TextAttrDimension *pThis = Object_wx_TextAttrDimension::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxTextBoxAttrPosition _rtn = pThis->GetEntity()->GetPosition();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_TextAttrDimension, __SetPosition, "SetPosition")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "pos", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_TextAttrDimension, __SetPosition)
{
	Object_wx_TextAttrDimension *pThis = Object_wx_TextAttrDimension::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxTextBoxAttrPosition pos = arg.GetNumber(0)
	//pThis->GetEntity()->SetPosition(pos);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_TextAttrDimension, __IsValid, "IsValid")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_TextAttrDimension, __IsValid)
{
	Object_wx_TextAttrDimension *pThis = Object_wx_TextAttrDimension::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//bool _rtn = pThis->GetEntity()->IsValid();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_TextAttrDimension, __SetValid, "SetValid")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "b", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_TextAttrDimension, __SetValid)
{
	Object_wx_TextAttrDimension *pThis = Object_wx_TextAttrDimension::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//bool b = arg.GetNumber(0)
	//pThis->GetEntity()->SetValid(b);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_TextAttrDimension, __GetFlags, "GetFlags")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_TextAttrDimension, __GetFlags)
{
	Object_wx_TextAttrDimension *pThis = Object_wx_TextAttrDimension::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxTextAttrDimensionFlags _rtn = pThis->GetEntity()->GetFlags();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_TextAttrDimension, __SetFlags, "SetFlags")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "flags", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_TextAttrDimension, __SetFlags)
{
	Object_wx_TextAttrDimension *pThis = Object_wx_TextAttrDimension::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxTextAttrDimensionFlags flags = arg.GetNumber(0)
	//pThis->GetEntity()->SetFlags(flags);
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Class implementation for wxTextAttrDimension
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_TextAttrDimension)
{
	// Constructor assignment
	Gura_AssignFunction(__TextAttrDimension);
	Gura_AssignFunction(__TextAttrDimension_1);
	// Method assignment
	Gura_AssignMethod(wx_TextAttrDimension, __Reset);
	Gura_AssignMethod(wx_TextAttrDimension, __EqPartial);
	Gura_AssignMethod(wx_TextAttrDimension, __Apply);
	Gura_AssignMethod(wx_TextAttrDimension, __CollectCommonAttributes);
	Gura_AssignMethod(wx_TextAttrDimension, __GetValue);
	Gura_AssignMethod(wx_TextAttrDimension, __GetValueMM);
	Gura_AssignMethod(wx_TextAttrDimension, __SetValueMM);
	Gura_AssignMethod(wx_TextAttrDimension, __SetValue);
	Gura_AssignMethod(wx_TextAttrDimension, __SetValue_1);
	Gura_AssignMethod(wx_TextAttrDimension, __SetValue_2);
	Gura_AssignMethod(wx_TextAttrDimension, __SetValue_3);
	Gura_AssignMethod(wx_TextAttrDimension, __GetUnits);
	Gura_AssignMethod(wx_TextAttrDimension, __SetUnits);
	Gura_AssignMethod(wx_TextAttrDimension, __GetPosition);
	Gura_AssignMethod(wx_TextAttrDimension, __SetPosition);
	Gura_AssignMethod(wx_TextAttrDimension, __IsValid);
	Gura_AssignMethod(wx_TextAttrDimension, __SetValid);
	Gura_AssignMethod(wx_TextAttrDimension, __GetFlags);
	Gura_AssignMethod(wx_TextAttrDimension, __SetFlags);
}

Gura_ImplementDescendantCreator(wx_TextAttrDimension)
{
	return new Object_wx_TextAttrDimension((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
