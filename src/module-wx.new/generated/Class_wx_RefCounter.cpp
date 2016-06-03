//----------------------------------------------------------------------------
// wxRefCounter
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Gura interfaces for wxRefCounter
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Object implementation for wxRefCounter
//----------------------------------------------------------------------------
Object_wx_RefCounter::~Object_wx_RefCounter()
{
}

Object *Object_wx_RefCounter::Clone() const
{
	return nullptr;
}

String Object_wx_RefCounter::ToString(bool exprFlag)
{
	String rtn("<wx.RefCounter:");
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
Gura_DeclareMethodAlias(wx_RefCounter, __wxRefCounter, "wxRefCounter")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_RefCounter, __wxRefCounter)
{
	Object_wx_RefCounter *pThis = Object_wx_RefCounter::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->wxRefCounter();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RefCounter, __DecRef, "DecRef")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_RefCounter, __DecRef)
{
	Object_wx_RefCounter *pThis = Object_wx_RefCounter::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->DecRef();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RefCounter, __GetRefCount, "GetRefCount")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_RefCounter, __GetRefCount)
{
	Object_wx_RefCounter *pThis = Object_wx_RefCounter::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->GetRefCount();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RefCounter, __IncRef, "IncRef")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_RefCounter, __IncRef)
{
	Object_wx_RefCounter *pThis = Object_wx_RefCounter::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->IncRef();
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Class implementation for wxRefCounter
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_RefCounter)
{
	Gura_AssignMethod(wx_RefCounter, __wxRefCounter);
	Gura_AssignMethod(wx_RefCounter, __DecRef);
	Gura_AssignMethod(wx_RefCounter, __GetRefCount);
	Gura_AssignMethod(wx_RefCounter, __IncRef);
}

Gura_ImplementDescendantCreator(wx_RefCounter)
{
	return new Object_wx_RefCounter((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
