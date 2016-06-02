//----------------------------------------------------------------------------
// wxAnyValueType
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Gura interfaces for wxAnyValueType
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Object implementation for wxAnyValueType
//----------------------------------------------------------------------------
Object_wx_AnyValueType::~Object_wx_AnyValueType()
{
}

Object *Object_wx_AnyValueType::Clone() const
{
	return nullptr;
}

String Object_wx_AnyValueType::ToString(bool exprFlag)
{
	String rtn("<wx.AnyValueType:");
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
Gura_DeclareMethod(wx_AnyValueType, wxAnyValueType)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_AnyValueType, wxAnyValueType)
{
	Object_wx_AnyValueType *pThis = Object_wx_AnyValueType::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->wxAnyValueType();
	return Value::Nil;
}

Gura_DeclareMethod(wx_AnyValueType, CheckType)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_AnyValueType, CheckType)
{
	Object_wx_AnyValueType *pThis = Object_wx_AnyValueType::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->CheckType();
	return Value::Nil;
}

Gura_DeclareMethod(wx_AnyValueType, ConvertValue)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "src", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "dstType", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "dst", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_AnyValueType, ConvertValue)
{
	Object_wx_AnyValueType *pThis = Object_wx_AnyValueType::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int src = arg.GetNumber(0)
	//int dstType = arg.GetNumber(1)
	//int dst = arg.GetNumber(2)
	//pThis->GetEntity()->ConvertValue();
	return Value::Nil;
}

Gura_DeclareMethod(wx_AnyValueType, CopyBuffer)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "src", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "dst", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_AnyValueType, CopyBuffer)
{
	Object_wx_AnyValueType *pThis = Object_wx_AnyValueType::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int src = arg.GetNumber(0)
	//int dst = arg.GetNumber(1)
	//pThis->GetEntity()->CopyBuffer();
	return Value::Nil;
}

Gura_DeclareMethod(wx_AnyValueType, DeleteValue)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "buf", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_AnyValueType, DeleteValue)
{
	Object_wx_AnyValueType *pThis = Object_wx_AnyValueType::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int buf = arg.GetNumber(0)
	//pThis->GetEntity()->DeleteValue();
	return Value::Nil;
}

Gura_DeclareMethod(wx_AnyValueType, IsSameType)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "otherType", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_AnyValueType, IsSameType)
{
	Object_wx_AnyValueType *pThis = Object_wx_AnyValueType::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int otherType = arg.GetNumber(0)
	//pThis->GetEntity()->IsSameType();
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Class implementation for wxAnyValueType
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_AnyValueType)
{
	Gura_AssignMethod(wx_AnyValueType, wxAnyValueType);
	Gura_AssignMethod(wx_AnyValueType, CheckType);
	Gura_AssignMethod(wx_AnyValueType, ConvertValue);
	Gura_AssignMethod(wx_AnyValueType, CopyBuffer);
	Gura_AssignMethod(wx_AnyValueType, DeleteValue);
	Gura_AssignMethod(wx_AnyValueType, IsSameType);
}

Gura_ImplementDescendantCreator(wx_AnyValueType)
{
	return new Object_wx_AnyValueType((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
