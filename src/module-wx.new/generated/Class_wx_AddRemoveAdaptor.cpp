//----------------------------------------------------------------------------
// wxAddRemoveAdaptor
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Gura interfaces for wxAddRemoveAdaptor
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Object implementation for wxAddRemoveAdaptor
//----------------------------------------------------------------------------
Object_wx_AddRemoveAdaptor::~Object_wx_AddRemoveAdaptor()
{
}

Object *Object_wx_AddRemoveAdaptor::Clone() const
{
	return nullptr;
}

String Object_wx_AddRemoveAdaptor::ToString(bool exprFlag)
{
	String rtn("<wx.AddRemoveAdaptor:");
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
Gura_DeclareFunctionAlias(__AddRemoveAdaptor, "AddRemoveAdaptor")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	SetClassToConstruct(Gura_UserClass(wx_AddRemoveAdaptor));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(__AddRemoveAdaptor)
{
	//wxAddRemoveAdaptor();
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Method implementation
//----------------------------------------------------------------------------
Gura_DeclareMethodAlias(wx_AddRemoveAdaptor, __GetItemsCtrl, "GetItemsCtrl")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_AddRemoveAdaptor, __GetItemsCtrl)
{
	Object_wx_AddRemoveAdaptor *pThis = Object_wx_AddRemoveAdaptor::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxWindow* _rtn = pThis->GetEntity()->GetItemsCtrl();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_AddRemoveAdaptor, __CanAdd, "CanAdd")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_AddRemoveAdaptor, __CanAdd)
{
	Object_wx_AddRemoveAdaptor *pThis = Object_wx_AddRemoveAdaptor::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//bool _rtn = pThis->GetEntity()->CanAdd();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_AddRemoveAdaptor, __CanRemove, "CanRemove")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_AddRemoveAdaptor, __CanRemove)
{
	Object_wx_AddRemoveAdaptor *pThis = Object_wx_AddRemoveAdaptor::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//bool _rtn = pThis->GetEntity()->CanRemove();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_AddRemoveAdaptor, __OnAdd, "OnAdd")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_AddRemoveAdaptor, __OnAdd)
{
	Object_wx_AddRemoveAdaptor *pThis = Object_wx_AddRemoveAdaptor::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->OnAdd();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_AddRemoveAdaptor, __OnRemove, "OnRemove")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_AddRemoveAdaptor, __OnRemove)
{
	Object_wx_AddRemoveAdaptor *pThis = Object_wx_AddRemoveAdaptor::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->OnRemove();
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Class implementation for wxAddRemoveAdaptor
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_AddRemoveAdaptor)
{
	// Constructor assignment
	Gura_AssignFunction(__AddRemoveAdaptor);
	// Method assignment
	Gura_AssignMethod(wx_AddRemoveAdaptor, __GetItemsCtrl);
	Gura_AssignMethod(wx_AddRemoveAdaptor, __CanAdd);
	Gura_AssignMethod(wx_AddRemoveAdaptor, __CanRemove);
	Gura_AssignMethod(wx_AddRemoveAdaptor, __OnAdd);
	Gura_AssignMethod(wx_AddRemoveAdaptor, __OnRemove);
}

Gura_ImplementDescendantCreator(wx_AddRemoveAdaptor)
{
	return new Object_wx_AddRemoveAdaptor((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
