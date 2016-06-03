//----------------------------------------------------------------------------
// wxPropertyGridEvent
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Gura interfaces for wxPropertyGridEvent
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Object implementation for wxPropertyGridEvent
//----------------------------------------------------------------------------
Object_wx_PropertyGridEvent::~Object_wx_PropertyGridEvent()
{
}

Object *Object_wx_PropertyGridEvent::Clone() const
{
	return nullptr;
}

String Object_wx_PropertyGridEvent::ToString(bool exprFlag)
{
	String rtn("<wx.PropertyGridEvent:");
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
Gura_DeclareMethodAlias(wx_PropertyGridEvent, __wxPropertyGridEvent, "wxPropertyGridEvent")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "commandType", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "id", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_PropertyGridEvent, __wxPropertyGridEvent)
{
	Object_wx_PropertyGridEvent *pThis = Object_wx_PropertyGridEvent::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int commandType = arg.GetNumber(0)
	//int id = arg.GetNumber(1)
	//pThis->GetEntity()->wxPropertyGridEvent();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_PropertyGridEvent, __wxPropertyGridEvent_1, "wxPropertyGridEvent_1")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "event", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_PropertyGridEvent, __wxPropertyGridEvent_1)
{
	Object_wx_PropertyGridEvent *pThis = Object_wx_PropertyGridEvent::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int event = arg.GetNumber(0)
	//pThis->GetEntity()->wxPropertyGridEvent();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_PropertyGridEvent, __CanVeto, "CanVeto")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_PropertyGridEvent, __CanVeto)
{
	Object_wx_PropertyGridEvent *pThis = Object_wx_PropertyGridEvent::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->CanVeto();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_PropertyGridEvent, __GetColumn, "GetColumn")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_PropertyGridEvent, __GetColumn)
{
	Object_wx_PropertyGridEvent *pThis = Object_wx_PropertyGridEvent::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->GetColumn();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_PropertyGridEvent, __GetMainParent, "GetMainParent")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_PropertyGridEvent, __GetMainParent)
{
	Object_wx_PropertyGridEvent *pThis = Object_wx_PropertyGridEvent::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->GetMainParent();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_PropertyGridEvent, __GetProperty, "GetProperty")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_PropertyGridEvent, __GetProperty)
{
	Object_wx_PropertyGridEvent *pThis = Object_wx_PropertyGridEvent::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->GetProperty();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_PropertyGridEvent, __GetValidationFailureBehavior, "GetValidationFailureBehavior")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_PropertyGridEvent, __GetValidationFailureBehavior)
{
	Object_wx_PropertyGridEvent *pThis = Object_wx_PropertyGridEvent::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->GetValidationFailureBehavior();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_PropertyGridEvent, __GetPropertyName, "GetPropertyName")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_PropertyGridEvent, __GetPropertyName)
{
	Object_wx_PropertyGridEvent *pThis = Object_wx_PropertyGridEvent::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->GetPropertyName();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_PropertyGridEvent, __GetPropertyValue, "GetPropertyValue")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_PropertyGridEvent, __GetPropertyValue)
{
	Object_wx_PropertyGridEvent *pThis = Object_wx_PropertyGridEvent::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->GetPropertyValue();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_PropertyGridEvent, __SetCanVeto, "SetCanVeto")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "canVeto", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_PropertyGridEvent, __SetCanVeto)
{
	Object_wx_PropertyGridEvent *pThis = Object_wx_PropertyGridEvent::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int canVeto = arg.GetNumber(0)
	//pThis->GetEntity()->SetCanVeto();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_PropertyGridEvent, __SetProperty, "SetProperty")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "p", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_PropertyGridEvent, __SetProperty)
{
	Object_wx_PropertyGridEvent *pThis = Object_wx_PropertyGridEvent::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int p = arg.GetNumber(0)
	//pThis->GetEntity()->SetProperty();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_PropertyGridEvent, __SetValidationFailureBehavior, "SetValidationFailureBehavior")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "flags", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_PropertyGridEvent, __SetValidationFailureBehavior)
{
	Object_wx_PropertyGridEvent *pThis = Object_wx_PropertyGridEvent::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int flags = arg.GetNumber(0)
	//pThis->GetEntity()->SetValidationFailureBehavior();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_PropertyGridEvent, __SetValidationFailureMessage, "SetValidationFailureMessage")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "message", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_PropertyGridEvent, __SetValidationFailureMessage)
{
	Object_wx_PropertyGridEvent *pThis = Object_wx_PropertyGridEvent::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int message = arg.GetNumber(0)
	//pThis->GetEntity()->SetValidationFailureMessage();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_PropertyGridEvent, __Veto, "Veto")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "veto", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_PropertyGridEvent, __Veto)
{
	Object_wx_PropertyGridEvent *pThis = Object_wx_PropertyGridEvent::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int veto = arg.GetNumber(0)
	//pThis->GetEntity()->Veto();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_PropertyGridEvent, __WasVetoed, "WasVetoed")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_PropertyGridEvent, __WasVetoed)
{
	Object_wx_PropertyGridEvent *pThis = Object_wx_PropertyGridEvent::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->WasVetoed();
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Class implementation for wxPropertyGridEvent
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_PropertyGridEvent)
{
	Gura_AssignMethod(wx_PropertyGridEvent, __wxPropertyGridEvent);
	Gura_AssignMethod(wx_PropertyGridEvent, __wxPropertyGridEvent_1);
	Gura_AssignMethod(wx_PropertyGridEvent, __CanVeto);
	Gura_AssignMethod(wx_PropertyGridEvent, __GetColumn);
	Gura_AssignMethod(wx_PropertyGridEvent, __GetMainParent);
	Gura_AssignMethod(wx_PropertyGridEvent, __GetProperty);
	Gura_AssignMethod(wx_PropertyGridEvent, __GetValidationFailureBehavior);
	Gura_AssignMethod(wx_PropertyGridEvent, __GetPropertyName);
	Gura_AssignMethod(wx_PropertyGridEvent, __GetPropertyValue);
	Gura_AssignMethod(wx_PropertyGridEvent, __SetCanVeto);
	Gura_AssignMethod(wx_PropertyGridEvent, __SetProperty);
	Gura_AssignMethod(wx_PropertyGridEvent, __SetValidationFailureBehavior);
	Gura_AssignMethod(wx_PropertyGridEvent, __SetValidationFailureMessage);
	Gura_AssignMethod(wx_PropertyGridEvent, __Veto);
	Gura_AssignMethod(wx_PropertyGridEvent, __WasVetoed);
}

Gura_ImplementDescendantCreator(wx_PropertyGridEvent)
{
	return new Object_wx_PropertyGridEvent((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
