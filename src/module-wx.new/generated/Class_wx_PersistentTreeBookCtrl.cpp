//----------------------------------------------------------------------------
// wxPersistentTreeBookCtrl
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Gura interfaces for wxPersistentTreeBookCtrl
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Object implementation for wxPersistentTreeBookCtrl
//----------------------------------------------------------------------------
Object_wx_PersistentTreeBookCtrl::~Object_wx_PersistentTreeBookCtrl()
{
}

Object *Object_wx_PersistentTreeBookCtrl::Clone() const
{
	return nullptr;
}

String Object_wx_PersistentTreeBookCtrl::ToString(bool exprFlag)
{
	String rtn("<wx.PersistentTreeBookCtrl:");
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
Gura_DeclareMethodAlias(wx_PersistentTreeBookCtrl, __wxPersistentTreeBookCtrl, "wxPersistentTreeBookCtrl")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "book", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_PersistentTreeBookCtrl, __wxPersistentTreeBookCtrl)
{
	Object_wx_PersistentTreeBookCtrl *pThis = Object_wx_PersistentTreeBookCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int book = arg.GetNumber(0)
	//pThis->GetEntity()->wxPersistentTreeBookCtrl();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_PersistentTreeBookCtrl, __Save, "Save")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_PersistentTreeBookCtrl, __Save)
{
	Object_wx_PersistentTreeBookCtrl *pThis = Object_wx_PersistentTreeBookCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->Save();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_PersistentTreeBookCtrl, __Restore, "Restore")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_PersistentTreeBookCtrl, __Restore)
{
	Object_wx_PersistentTreeBookCtrl *pThis = Object_wx_PersistentTreeBookCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->Restore();
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Class implementation for wxPersistentTreeBookCtrl
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_PersistentTreeBookCtrl)
{
	Gura_AssignMethod(wx_PersistentTreeBookCtrl, __wxPersistentTreeBookCtrl);
	Gura_AssignMethod(wx_PersistentTreeBookCtrl, __Save);
	Gura_AssignMethod(wx_PersistentTreeBookCtrl, __Restore);
}

Gura_ImplementDescendantCreator(wx_PersistentTreeBookCtrl)
{
	return new Object_wx_PersistentTreeBookCtrl((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
