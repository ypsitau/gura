//----------------------------------------------------------------------------
// wxVariant
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Gura interfaces for wxVariant
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Object implementation for wxVariant
//----------------------------------------------------------------------------
Object_wx_Variant::~Object_wx_Variant()
{
}

Object *Object_wx_Variant::Clone() const
{
	return nullptr;
}

String Object_wx_Variant::ToString(bool exprFlag)
{
	String rtn("<wx.Variant:");
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
Gura_DeclareFunctionAlias(__Variant, "Variant")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	SetClassToConstruct(Gura_UserClass(wx_Variant));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(__Variant)
{
	//wxVariant();
	return Value::Nil;
}

Gura_DeclareFunctionAlias(__Variant_1, "Variant_1")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "data", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "name", VTYPE_number, OCCUR_Once);
	SetClassToConstruct(Gura_UserClass(wx_Variant));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(__Variant_1)
{
	//int data = arg.GetNumber(0)
	//int name = arg.GetNumber(1)
	//wxVariant();
	return Value::Nil;
}

Gura_DeclareFunctionAlias(__Variant_2, "Variant_2")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "variant", VTYPE_number, OCCUR_Once);
	SetClassToConstruct(Gura_UserClass(wx_Variant));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(__Variant_2)
{
	//int variant = arg.GetNumber(0)
	//wxVariant();
	return Value::Nil;
}

Gura_DeclareFunctionAlias(__Variant_3, "Variant_3")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "any", VTYPE_number, OCCUR_Once);
	SetClassToConstruct(Gura_UserClass(wx_Variant));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(__Variant_3)
{
	//int any = arg.GetNumber(0)
	//wxVariant();
	return Value::Nil;
}

Gura_DeclareFunctionAlias(__Variant_4, "Variant_4")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "value", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "name", VTYPE_number, OCCUR_Once);
	SetClassToConstruct(Gura_UserClass(wx_Variant));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(__Variant_4)
{
	//int value = arg.GetNumber(0)
	//int name = arg.GetNumber(1)
	//wxVariant();
	return Value::Nil;
}

Gura_DeclareFunctionAlias(__Variant_5, "Variant_5")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "value", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "name", VTYPE_number, OCCUR_Once);
	SetClassToConstruct(Gura_UserClass(wx_Variant));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(__Variant_5)
{
	//int value = arg.GetNumber(0)
	//int name = arg.GetNumber(1)
	//wxVariant();
	return Value::Nil;
}

Gura_DeclareFunctionAlias(__Variant_6, "Variant_6")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "value", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "name", VTYPE_number, OCCUR_Once);
	SetClassToConstruct(Gura_UserClass(wx_Variant));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(__Variant_6)
{
	//int value = arg.GetNumber(0)
	//int name = arg.GetNumber(1)
	//wxVariant();
	return Value::Nil;
}

Gura_DeclareFunctionAlias(__Variant_7, "Variant_7")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "value", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "name", VTYPE_number, OCCUR_Once);
	SetClassToConstruct(Gura_UserClass(wx_Variant));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(__Variant_7)
{
	//int value = arg.GetNumber(0)
	//int name = arg.GetNumber(1)
	//wxVariant();
	return Value::Nil;
}

Gura_DeclareFunctionAlias(__Variant_8, "Variant_8")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "value", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "name", VTYPE_number, OCCUR_Once);
	SetClassToConstruct(Gura_UserClass(wx_Variant));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(__Variant_8)
{
	//int value = arg.GetNumber(0)
	//int name = arg.GetNumber(1)
	//wxVariant();
	return Value::Nil;
}

Gura_DeclareFunctionAlias(__Variant_9, "Variant_9")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "value", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "name", VTYPE_number, OCCUR_Once);
	SetClassToConstruct(Gura_UserClass(wx_Variant));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(__Variant_9)
{
	//int value = arg.GetNumber(0)
	//int name = arg.GetNumber(1)
	//wxVariant();
	return Value::Nil;
}

Gura_DeclareFunctionAlias(__Variant_10, "Variant_10")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "value", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "name", VTYPE_number, OCCUR_Once);
	SetClassToConstruct(Gura_UserClass(wx_Variant));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(__Variant_10)
{
	//int value = arg.GetNumber(0)
	//int name = arg.GetNumber(1)
	//wxVariant();
	return Value::Nil;
}

Gura_DeclareFunctionAlias(__Variant_11, "Variant_11")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "value", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "name", VTYPE_number, OCCUR_Once);
	SetClassToConstruct(Gura_UserClass(wx_Variant));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(__Variant_11)
{
	//int value = arg.GetNumber(0)
	//int name = arg.GetNumber(1)
	//wxVariant();
	return Value::Nil;
}

Gura_DeclareFunctionAlias(__Variant_12, "Variant_12")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "value", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "name", VTYPE_number, OCCUR_Once);
	SetClassToConstruct(Gura_UserClass(wx_Variant));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(__Variant_12)
{
	//int value = arg.GetNumber(0)
	//int name = arg.GetNumber(1)
	//wxVariant();
	return Value::Nil;
}

Gura_DeclareFunctionAlias(__Variant_13, "Variant_13")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "value", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "name", VTYPE_number, OCCUR_Once);
	SetClassToConstruct(Gura_UserClass(wx_Variant));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(__Variant_13)
{
	//int value = arg.GetNumber(0)
	//int name = arg.GetNumber(1)
	//wxVariant();
	return Value::Nil;
}

Gura_DeclareFunctionAlias(__Variant_14, "Variant_14")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "value", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "name", VTYPE_number, OCCUR_Once);
	SetClassToConstruct(Gura_UserClass(wx_Variant));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(__Variant_14)
{
	//int value = arg.GetNumber(0)
	//int name = arg.GetNumber(1)
	//wxVariant();
	return Value::Nil;
}

Gura_DeclareFunctionAlias(__Variant_15, "Variant_15")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "val", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "name", VTYPE_number, OCCUR_Once);
	SetClassToConstruct(Gura_UserClass(wx_Variant));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(__Variant_15)
{
	//int val = arg.GetNumber(0)
	//int name = arg.GetNumber(1)
	//wxVariant();
	return Value::Nil;
}

Gura_DeclareFunctionAlias(__Variant_16, "Variant_16")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "val", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "name", VTYPE_number, OCCUR_Once);
	SetClassToConstruct(Gura_UserClass(wx_Variant));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(__Variant_16)
{
	//int val = arg.GetNumber(0)
	//int name = arg.GetNumber(1)
	//wxVariant();
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Method implementation
//----------------------------------------------------------------------------
Gura_DeclareMethodAlias(wx_Variant, __Append, "Append")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "value", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Variant, __Append)
{
	Object_wx_Variant *pThis = Object_wx_Variant::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int value = arg.GetNumber(0)
	//pThis->GetEntity()->Append();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Variant, __Clear, "Clear")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_Variant, __Clear)
{
	Object_wx_Variant *pThis = Object_wx_Variant::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->Clear();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Variant, __ClearList, "ClearList")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_Variant, __ClearList)
{
	Object_wx_Variant *pThis = Object_wx_Variant::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->ClearList();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Variant, __Delete, "Delete")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "item", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Variant, __Delete)
{
	Object_wx_Variant *pThis = Object_wx_Variant::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int item = arg.GetNumber(0)
	//pThis->GetEntity()->Delete();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Variant, __GetCount, "GetCount")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_Variant, __GetCount)
{
	Object_wx_Variant *pThis = Object_wx_Variant::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->GetCount();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Variant, __GetList, "GetList")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_Variant, __GetList)
{
	Object_wx_Variant *pThis = Object_wx_Variant::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->GetList();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Variant, __Insert, "Insert")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "value", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Variant, __Insert)
{
	Object_wx_Variant *pThis = Object_wx_Variant::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int value = arg.GetNumber(0)
	//pThis->GetEntity()->Insert();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Variant, __NullList, "NullList")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_Variant, __NullList)
{
	Object_wx_Variant *pThis = Object_wx_Variant::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->NullList();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Variant, __Convert, "Convert")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "value", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Variant, __Convert)
{
	Object_wx_Variant *pThis = Object_wx_Variant::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int value = arg.GetNumber(0)
	//pThis->GetEntity()->Convert();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Variant, __Convert_1, "Convert_1")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "value", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Variant, __Convert_1)
{
	Object_wx_Variant *pThis = Object_wx_Variant::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int value = arg.GetNumber(0)
	//pThis->GetEntity()->Convert();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Variant, __Convert_2, "Convert_2")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "value", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Variant, __Convert_2)
{
	Object_wx_Variant *pThis = Object_wx_Variant::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int value = arg.GetNumber(0)
	//pThis->GetEntity()->Convert();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Variant, __Convert_3, "Convert_3")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "value", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Variant, __Convert_3)
{
	Object_wx_Variant *pThis = Object_wx_Variant::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int value = arg.GetNumber(0)
	//pThis->GetEntity()->Convert();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Variant, __Convert_4, "Convert_4")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "value", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Variant, __Convert_4)
{
	Object_wx_Variant *pThis = Object_wx_Variant::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int value = arg.GetNumber(0)
	//pThis->GetEntity()->Convert();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Variant, __Convert_5, "Convert_5")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "value", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Variant, __Convert_5)
{
	Object_wx_Variant *pThis = Object_wx_Variant::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int value = arg.GetNumber(0)
	//pThis->GetEntity()->Convert();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Variant, __Convert_6, "Convert_6")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "value", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Variant, __Convert_6)
{
	Object_wx_Variant *pThis = Object_wx_Variant::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int value = arg.GetNumber(0)
	//pThis->GetEntity()->Convert();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Variant, __Convert_7, "Convert_7")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "value", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Variant, __Convert_7)
{
	Object_wx_Variant *pThis = Object_wx_Variant::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int value = arg.GetNumber(0)
	//pThis->GetEntity()->Convert();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Variant, __GetAny, "GetAny")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_Variant, __GetAny)
{
	Object_wx_Variant *pThis = Object_wx_Variant::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->GetAny();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Variant, __GetArrayString, "GetArrayString")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_Variant, __GetArrayString)
{
	Object_wx_Variant *pThis = Object_wx_Variant::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->GetArrayString();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Variant, __GetBool, "GetBool")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_Variant, __GetBool)
{
	Object_wx_Variant *pThis = Object_wx_Variant::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->GetBool();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Variant, __GetChar, "GetChar")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_Variant, __GetChar)
{
	Object_wx_Variant *pThis = Object_wx_Variant::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->GetChar();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Variant, __GetData, "GetData")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_Variant, __GetData)
{
	Object_wx_Variant *pThis = Object_wx_Variant::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->GetData();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Variant, __GetDateTime, "GetDateTime")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_Variant, __GetDateTime)
{
	Object_wx_Variant *pThis = Object_wx_Variant::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->GetDateTime();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Variant, __GetDouble, "GetDouble")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_Variant, __GetDouble)
{
	Object_wx_Variant *pThis = Object_wx_Variant::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->GetDouble();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Variant, __GetLong, "GetLong")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_Variant, __GetLong)
{
	Object_wx_Variant *pThis = Object_wx_Variant::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->GetLong();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Variant, __GetLongLong, "GetLongLong")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_Variant, __GetLongLong)
{
	Object_wx_Variant *pThis = Object_wx_Variant::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->GetLongLong();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Variant, __GetName, "GetName")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_Variant, __GetName)
{
	Object_wx_Variant *pThis = Object_wx_Variant::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->GetName();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Variant, __GetString, "GetString")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_Variant, __GetString)
{
	Object_wx_Variant *pThis = Object_wx_Variant::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->GetString();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Variant, __GetType, "GetType")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_Variant, __GetType)
{
	Object_wx_Variant *pThis = Object_wx_Variant::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->GetType();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Variant, __GetULongLong, "GetULongLong")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_Variant, __GetULongLong)
{
	Object_wx_Variant *pThis = Object_wx_Variant::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->GetULongLong();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Variant, __GetVoidPtr, "GetVoidPtr")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_Variant, __GetVoidPtr)
{
	Object_wx_Variant *pThis = Object_wx_Variant::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->GetVoidPtr();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Variant, __GetWxObjectPtr, "GetWxObjectPtr")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_Variant, __GetWxObjectPtr)
{
	Object_wx_Variant *pThis = Object_wx_Variant::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->GetWxObjectPtr();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Variant, __IsNull, "IsNull")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_Variant, __IsNull)
{
	Object_wx_Variant *pThis = Object_wx_Variant::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->IsNull();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Variant, __IsType, "IsType")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "type", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Variant, __IsType)
{
	Object_wx_Variant *pThis = Object_wx_Variant::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int type = arg.GetNumber(0)
	//pThis->GetEntity()->IsType();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Variant, __IsValueKindOf, "IsValueKindOf")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "type", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Variant, __IsValueKindOf)
{
	Object_wx_Variant *pThis = Object_wx_Variant::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int type = arg.GetNumber(0)
	//pThis->GetEntity()->IsValueKindOf();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Variant, __MakeNull, "MakeNull")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_Variant, __MakeNull)
{
	Object_wx_Variant *pThis = Object_wx_Variant::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->MakeNull();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Variant, __MakeString, "MakeString")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_Variant, __MakeString)
{
	Object_wx_Variant *pThis = Object_wx_Variant::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->MakeString();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Variant, __Member, "Member")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "value", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Variant, __Member)
{
	Object_wx_Variant *pThis = Object_wx_Variant::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int value = arg.GetNumber(0)
	//pThis->GetEntity()->Member();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Variant, __SetData, "SetData")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "data", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Variant, __SetData)
{
	Object_wx_Variant *pThis = Object_wx_Variant::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int data = arg.GetNumber(0)
	//pThis->GetEntity()->SetData();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Variant, __Unshare, "Unshare")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_Variant, __Unshare)
{
	Object_wx_Variant *pThis = Object_wx_Variant::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->Unshare();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Variant, __double, "double")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_Variant, __double)
{
	Object_wx_Variant *pThis = Object_wx_Variant::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->double();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Variant, __long, "long")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_Variant, __long)
{
	Object_wx_Variant *pThis = Object_wx_Variant::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->long();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Variant, __wxLongLong, "wxLongLong")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_Variant, __wxLongLong)
{
	Object_wx_Variant *pThis = Object_wx_Variant::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->wxLongLong();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Variant, __wxULongLong, "wxULongLong")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_Variant, __wxULongLong)
{
	Object_wx_Variant *pThis = Object_wx_Variant::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->wxULongLong();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Variant, __wxChar, "wxChar")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_Variant, __wxChar)
{
	Object_wx_Variant *pThis = Object_wx_Variant::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->wxChar();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Variant, __wxDateTime, "wxDateTime")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_Variant, __wxDateTime)
{
	Object_wx_Variant *pThis = Object_wx_Variant::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->wxDateTime();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Variant, __wxString, "wxString")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_Variant, __wxString)
{
	Object_wx_Variant *pThis = Object_wx_Variant::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->wxString();
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Class implementation for wxVariant
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_Variant)
{
	// Constructor assignment
	Gura_AssignFunction(__Variant);
	Gura_AssignFunction(__Variant_1);
	Gura_AssignFunction(__Variant_2);
	Gura_AssignFunction(__Variant_3);
	Gura_AssignFunction(__Variant_4);
	Gura_AssignFunction(__Variant_5);
	Gura_AssignFunction(__Variant_6);
	Gura_AssignFunction(__Variant_7);
	Gura_AssignFunction(__Variant_8);
	Gura_AssignFunction(__Variant_9);
	Gura_AssignFunction(__Variant_10);
	Gura_AssignFunction(__Variant_11);
	Gura_AssignFunction(__Variant_12);
	Gura_AssignFunction(__Variant_13);
	Gura_AssignFunction(__Variant_14);
	Gura_AssignFunction(__Variant_15);
	Gura_AssignFunction(__Variant_16);
	// Method assignment
	Gura_AssignMethod(wx_Variant, __Append);
	Gura_AssignMethod(wx_Variant, __Clear);
	Gura_AssignMethod(wx_Variant, __ClearList);
	Gura_AssignMethod(wx_Variant, __Delete);
	Gura_AssignMethod(wx_Variant, __GetCount);
	Gura_AssignMethod(wx_Variant, __GetList);
	Gura_AssignMethod(wx_Variant, __Insert);
	Gura_AssignMethod(wx_Variant, __NullList);
	Gura_AssignMethod(wx_Variant, __Convert);
	Gura_AssignMethod(wx_Variant, __Convert_1);
	Gura_AssignMethod(wx_Variant, __Convert_2);
	Gura_AssignMethod(wx_Variant, __Convert_3);
	Gura_AssignMethod(wx_Variant, __Convert_4);
	Gura_AssignMethod(wx_Variant, __Convert_5);
	Gura_AssignMethod(wx_Variant, __Convert_6);
	Gura_AssignMethod(wx_Variant, __Convert_7);
	Gura_AssignMethod(wx_Variant, __GetAny);
	Gura_AssignMethod(wx_Variant, __GetArrayString);
	Gura_AssignMethod(wx_Variant, __GetBool);
	Gura_AssignMethod(wx_Variant, __GetChar);
	Gura_AssignMethod(wx_Variant, __GetData);
	Gura_AssignMethod(wx_Variant, __GetDateTime);
	Gura_AssignMethod(wx_Variant, __GetDouble);
	Gura_AssignMethod(wx_Variant, __GetLong);
	Gura_AssignMethod(wx_Variant, __GetLongLong);
	Gura_AssignMethod(wx_Variant, __GetName);
	Gura_AssignMethod(wx_Variant, __GetString);
	Gura_AssignMethod(wx_Variant, __GetType);
	Gura_AssignMethod(wx_Variant, __GetULongLong);
	Gura_AssignMethod(wx_Variant, __GetVoidPtr);
	Gura_AssignMethod(wx_Variant, __GetWxObjectPtr);
	Gura_AssignMethod(wx_Variant, __IsNull);
	Gura_AssignMethod(wx_Variant, __IsType);
	Gura_AssignMethod(wx_Variant, __IsValueKindOf);
	Gura_AssignMethod(wx_Variant, __MakeNull);
	Gura_AssignMethod(wx_Variant, __MakeString);
	Gura_AssignMethod(wx_Variant, __Member);
	Gura_AssignMethod(wx_Variant, __SetData);
	Gura_AssignMethod(wx_Variant, __Unshare);
	Gura_AssignMethod(wx_Variant, __double);
	Gura_AssignMethod(wx_Variant, __long);
	Gura_AssignMethod(wx_Variant, __wxLongLong);
	Gura_AssignMethod(wx_Variant, __wxULongLong);
	Gura_AssignMethod(wx_Variant, __wxChar);
	Gura_AssignMethod(wx_Variant, __wxDateTime);
	Gura_AssignMethod(wx_Variant, __wxString);
}

Gura_ImplementDescendantCreator(wx_Variant)
{
	return new Object_wx_Variant((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
