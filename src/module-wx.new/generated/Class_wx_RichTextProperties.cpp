//----------------------------------------------------------------------------
// wxRichTextProperties
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Gura interfaces for wxRichTextProperties
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Object implementation for wxRichTextProperties
//----------------------------------------------------------------------------
Object_wx_RichTextProperties::~Object_wx_RichTextProperties()
{
}

Object *Object_wx_RichTextProperties::Clone() const
{
	return nullptr;
}

String Object_wx_RichTextProperties::ToString(bool exprFlag)
{
	String rtn("<wx.RichTextProperties:");
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
Gura_DeclareFunctionAlias(__RichTextProperties, "RichTextProperties")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	SetClassToConstruct(Gura_UserClass(wx_RichTextProperties));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(__RichTextProperties)
{
	//wxRichTextProperties();
	return Value::Nil;
}

Gura_DeclareFunctionAlias(__RichTextProperties_1, "RichTextProperties_1")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "props", VTYPE_number, OCCUR_Once);
	SetClassToConstruct(Gura_UserClass(wx_RichTextProperties));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(__RichTextProperties_1)
{
	//int props = arg.GetNumber(0)
	//wxRichTextProperties();
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Method implementation
//----------------------------------------------------------------------------
Gura_DeclareMethodAlias(wx_RichTextProperties, __Copy, "Copy")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "props", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_RichTextProperties, __Copy)
{
	Object_wx_RichTextProperties *pThis = Object_wx_RichTextProperties::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int props = arg.GetNumber(0)
	//pThis->GetEntity()->Copy();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RichTextProperties, __Clear, "Clear")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_RichTextProperties, __Clear)
{
	Object_wx_RichTextProperties *pThis = Object_wx_RichTextProperties::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->Clear();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RichTextProperties, __GetProperties, "GetProperties")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_RichTextProperties, __GetProperties)
{
	Object_wx_RichTextProperties *pThis = Object_wx_RichTextProperties::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->GetProperties();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RichTextProperties, __GetProperties_1, "GetProperties_1")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_RichTextProperties, __GetProperties_1)
{
	Object_wx_RichTextProperties *pThis = Object_wx_RichTextProperties::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->GetProperties();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RichTextProperties, __SetProperties, "SetProperties")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "props", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_RichTextProperties, __SetProperties)
{
	Object_wx_RichTextProperties *pThis = Object_wx_RichTextProperties::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int props = arg.GetNumber(0)
	//pThis->GetEntity()->SetProperties();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RichTextProperties, __GetPropertyNames, "GetPropertyNames")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_RichTextProperties, __GetPropertyNames)
{
	Object_wx_RichTextProperties *pThis = Object_wx_RichTextProperties::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->GetPropertyNames();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RichTextProperties, __GetCount, "GetCount")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_RichTextProperties, __GetCount)
{
	Object_wx_RichTextProperties *pThis = Object_wx_RichTextProperties::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->GetCount();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RichTextProperties, __HasProperty, "HasProperty")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "name", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_RichTextProperties, __HasProperty)
{
	Object_wx_RichTextProperties *pThis = Object_wx_RichTextProperties::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int name = arg.GetNumber(0)
	//pThis->GetEntity()->HasProperty();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RichTextProperties, __Find, "Find")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "name", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_RichTextProperties, __Find)
{
	Object_wx_RichTextProperties *pThis = Object_wx_RichTextProperties::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int name = arg.GetNumber(0)
	//pThis->GetEntity()->Find();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RichTextProperties, __Remove, "Remove")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "name", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_RichTextProperties, __Remove)
{
	Object_wx_RichTextProperties *pThis = Object_wx_RichTextProperties::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int name = arg.GetNumber(0)
	//pThis->GetEntity()->Remove();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RichTextProperties, __GetProperty, "GetProperty")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "name", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_RichTextProperties, __GetProperty)
{
	Object_wx_RichTextProperties *pThis = Object_wx_RichTextProperties::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int name = arg.GetNumber(0)
	//pThis->GetEntity()->GetProperty();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RichTextProperties, __FindOrCreateProperty, "FindOrCreateProperty")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "name", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_RichTextProperties, __FindOrCreateProperty)
{
	Object_wx_RichTextProperties *pThis = Object_wx_RichTextProperties::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int name = arg.GetNumber(0)
	//pThis->GetEntity()->FindOrCreateProperty();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RichTextProperties, __GetPropertyString, "GetPropertyString")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "name", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_RichTextProperties, __GetPropertyString)
{
	Object_wx_RichTextProperties *pThis = Object_wx_RichTextProperties::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int name = arg.GetNumber(0)
	//pThis->GetEntity()->GetPropertyString();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RichTextProperties, __GetPropertyLong, "GetPropertyLong")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "name", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_RichTextProperties, __GetPropertyLong)
{
	Object_wx_RichTextProperties *pThis = Object_wx_RichTextProperties::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int name = arg.GetNumber(0)
	//pThis->GetEntity()->GetPropertyLong();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RichTextProperties, __GetPropertyBool, "GetPropertyBool")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "name", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_RichTextProperties, __GetPropertyBool)
{
	Object_wx_RichTextProperties *pThis = Object_wx_RichTextProperties::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int name = arg.GetNumber(0)
	//pThis->GetEntity()->GetPropertyBool();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RichTextProperties, __GetPropertyDouble, "GetPropertyDouble")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "name", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_RichTextProperties, __GetPropertyDouble)
{
	Object_wx_RichTextProperties *pThis = Object_wx_RichTextProperties::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int name = arg.GetNumber(0)
	//pThis->GetEntity()->GetPropertyDouble();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RichTextProperties, __SetProperty, "SetProperty")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "variant", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_RichTextProperties, __SetProperty)
{
	Object_wx_RichTextProperties *pThis = Object_wx_RichTextProperties::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int variant = arg.GetNumber(0)
	//pThis->GetEntity()->SetProperty();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RichTextProperties, __SetProperty_1, "SetProperty_1")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "name", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "variant", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_RichTextProperties, __SetProperty_1)
{
	Object_wx_RichTextProperties *pThis = Object_wx_RichTextProperties::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int name = arg.GetNumber(0)
	//int variant = arg.GetNumber(1)
	//pThis->GetEntity()->SetProperty();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RichTextProperties, __SetProperty_2, "SetProperty_2")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "name", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "value", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_RichTextProperties, __SetProperty_2)
{
	Object_wx_RichTextProperties *pThis = Object_wx_RichTextProperties::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int name = arg.GetNumber(0)
	//int value = arg.GetNumber(1)
	//pThis->GetEntity()->SetProperty();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RichTextProperties, __SetProperty_3, "SetProperty_3")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "name", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "value", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_RichTextProperties, __SetProperty_3)
{
	Object_wx_RichTextProperties *pThis = Object_wx_RichTextProperties::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int name = arg.GetNumber(0)
	//int value = arg.GetNumber(1)
	//pThis->GetEntity()->SetProperty();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RichTextProperties, __SetProperty_4, "SetProperty_4")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "name", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "value", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_RichTextProperties, __SetProperty_4)
{
	Object_wx_RichTextProperties *pThis = Object_wx_RichTextProperties::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int name = arg.GetNumber(0)
	//int value = arg.GetNumber(1)
	//pThis->GetEntity()->SetProperty();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RichTextProperties, __SetProperty_5, "SetProperty_5")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "name", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "value", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_RichTextProperties, __SetProperty_5)
{
	Object_wx_RichTextProperties *pThis = Object_wx_RichTextProperties::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int name = arg.GetNumber(0)
	//int value = arg.GetNumber(1)
	//pThis->GetEntity()->SetProperty();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RichTextProperties, __SetProperty_6, "SetProperty_6")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "name", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "value", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_RichTextProperties, __SetProperty_6)
{
	Object_wx_RichTextProperties *pThis = Object_wx_RichTextProperties::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int name = arg.GetNumber(0)
	//int value = arg.GetNumber(1)
	//pThis->GetEntity()->SetProperty();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RichTextProperties, __RemoveProperties, "RemoveProperties")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "properties", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_RichTextProperties, __RemoveProperties)
{
	Object_wx_RichTextProperties *pThis = Object_wx_RichTextProperties::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int properties = arg.GetNumber(0)
	//pThis->GetEntity()->RemoveProperties();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RichTextProperties, __MergeProperties, "MergeProperties")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "properties", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_RichTextProperties, __MergeProperties)
{
	Object_wx_RichTextProperties *pThis = Object_wx_RichTextProperties::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int properties = arg.GetNumber(0)
	//pThis->GetEntity()->MergeProperties();
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Class implementation for wxRichTextProperties
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_RichTextProperties)
{
	// Constructor assignment
	Gura_AssignFunction(__RichTextProperties);
	Gura_AssignFunction(__RichTextProperties_1);
	// Method assignment
	Gura_AssignMethod(wx_RichTextProperties, __Copy);
	Gura_AssignMethod(wx_RichTextProperties, __Clear);
	Gura_AssignMethod(wx_RichTextProperties, __GetProperties);
	Gura_AssignMethod(wx_RichTextProperties, __GetProperties_1);
	Gura_AssignMethod(wx_RichTextProperties, __SetProperties);
	Gura_AssignMethod(wx_RichTextProperties, __GetPropertyNames);
	Gura_AssignMethod(wx_RichTextProperties, __GetCount);
	Gura_AssignMethod(wx_RichTextProperties, __HasProperty);
	Gura_AssignMethod(wx_RichTextProperties, __Find);
	Gura_AssignMethod(wx_RichTextProperties, __Remove);
	Gura_AssignMethod(wx_RichTextProperties, __GetProperty);
	Gura_AssignMethod(wx_RichTextProperties, __FindOrCreateProperty);
	Gura_AssignMethod(wx_RichTextProperties, __GetPropertyString);
	Gura_AssignMethod(wx_RichTextProperties, __GetPropertyLong);
	Gura_AssignMethod(wx_RichTextProperties, __GetPropertyBool);
	Gura_AssignMethod(wx_RichTextProperties, __GetPropertyDouble);
	Gura_AssignMethod(wx_RichTextProperties, __SetProperty);
	Gura_AssignMethod(wx_RichTextProperties, __SetProperty_1);
	Gura_AssignMethod(wx_RichTextProperties, __SetProperty_2);
	Gura_AssignMethod(wx_RichTextProperties, __SetProperty_3);
	Gura_AssignMethod(wx_RichTextProperties, __SetProperty_4);
	Gura_AssignMethod(wx_RichTextProperties, __SetProperty_5);
	Gura_AssignMethod(wx_RichTextProperties, __SetProperty_6);
	Gura_AssignMethod(wx_RichTextProperties, __RemoveProperties);
	Gura_AssignMethod(wx_RichTextProperties, __MergeProperties);
}

Gura_ImplementDescendantCreator(wx_RichTextProperties)
{
	return new Object_wx_RichTextProperties((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
