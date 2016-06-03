//----------------------------------------------------------------------------
// wxThreadHelper
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Gura interfaces for wxThreadHelper
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Object implementation for wxThreadHelper
//----------------------------------------------------------------------------
Object_wx_ThreadHelper::~Object_wx_ThreadHelper()
{
}

Object *Object_wx_ThreadHelper::Clone() const
{
	return nullptr;
}

String Object_wx_ThreadHelper::ToString(bool exprFlag)
{
	String rtn("<wx.ThreadHelper:");
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
Gura_DeclareFunctionAlias(__wxThreadHelper, "wxThreadHelper")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "kind", VTYPE_number, OCCUR_Once);
	SetClassToConstruct(Gura_UserClass(wx_ThreadHelper));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(__wxThreadHelper)
{
	//int kind = arg.GetNumber(0)
	//wxThreadHelper();
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Method implementation
//----------------------------------------------------------------------------
Gura_DeclareMethodAlias(wx_ThreadHelper, __Entry, "Entry")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_ThreadHelper, __Entry)
{
	Object_wx_ThreadHelper *pThis = Object_wx_ThreadHelper::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->Entry();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_ThreadHelper, __OnDelete, "OnDelete")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_ThreadHelper, __OnDelete)
{
	Object_wx_ThreadHelper *pThis = Object_wx_ThreadHelper::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->OnDelete();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_ThreadHelper, __OnKill, "OnKill")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_ThreadHelper, __OnKill)
{
	Object_wx_ThreadHelper *pThis = Object_wx_ThreadHelper::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->OnKill();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_ThreadHelper, __Create, "Create")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "stackSize", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_ThreadHelper, __Create)
{
	Object_wx_ThreadHelper *pThis = Object_wx_ThreadHelper::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int stackSize = arg.GetNumber(0)
	//pThis->GetEntity()->Create();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_ThreadHelper, __CreateThread, "CreateThread")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "kind", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "stackSize", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_ThreadHelper, __CreateThread)
{
	Object_wx_ThreadHelper *pThis = Object_wx_ThreadHelper::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int kind = arg.GetNumber(0)
	//int stackSize = arg.GetNumber(1)
	//pThis->GetEntity()->CreateThread();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_ThreadHelper, __GetThread, "GetThread")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_ThreadHelper, __GetThread)
{
	Object_wx_ThreadHelper *pThis = Object_wx_ThreadHelper::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->GetThread();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_ThreadHelper, __GetThreadKind, "GetThreadKind")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_ThreadHelper, __GetThreadKind)
{
	Object_wx_ThreadHelper *pThis = Object_wx_ThreadHelper::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->GetThreadKind();
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Class implementation for wxThreadHelper
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_ThreadHelper)
{
	// Constructor assignment
	Gura_AssignFunction(__wxThreadHelper);
	// Method assignment
	Gura_AssignMethod(wx_ThreadHelper, __Entry);
	Gura_AssignMethod(wx_ThreadHelper, __OnDelete);
	Gura_AssignMethod(wx_ThreadHelper, __OnKill);
	Gura_AssignMethod(wx_ThreadHelper, __Create);
	Gura_AssignMethod(wx_ThreadHelper, __CreateThread);
	Gura_AssignMethod(wx_ThreadHelper, __GetThread);
	Gura_AssignMethod(wx_ThreadHelper, __GetThreadKind);
}

Gura_ImplementDescendantCreator(wx_ThreadHelper)
{
	return new Object_wx_ThreadHelper((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
