//----------------------------------------------------------------------------
// wxContextMenuEvent
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Gura interfaces for wxContextMenuEvent
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Object implementation for wxContextMenuEvent
//----------------------------------------------------------------------------
Object_wx_ContextMenuEvent::~Object_wx_ContextMenuEvent()
{
}

Object *Object_wx_ContextMenuEvent::Clone() const
{
	return nullptr;
}

String Object_wx_ContextMenuEvent::ToString(bool exprFlag)
{
	String rtn("<wx.ContextMenuEvent:");
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
Gura_DeclareMethodAlias(wx_ContextMenuEvent, __wxContextMenuEvent, "wxContextMenuEvent")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "type", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "id", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "pos", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_ContextMenuEvent, __wxContextMenuEvent)
{
	Object_wx_ContextMenuEvent *pThis = Object_wx_ContextMenuEvent::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int type = arg.GetNumber(0)
	//int id = arg.GetNumber(1)
	//int pos = arg.GetNumber(2)
	//pThis->GetEntity()->wxContextMenuEvent();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_ContextMenuEvent, __GetPosition, "GetPosition")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_ContextMenuEvent, __GetPosition)
{
	Object_wx_ContextMenuEvent *pThis = Object_wx_ContextMenuEvent::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->GetPosition();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_ContextMenuEvent, __SetPosition, "SetPosition")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "point", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_ContextMenuEvent, __SetPosition)
{
	Object_wx_ContextMenuEvent *pThis = Object_wx_ContextMenuEvent::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int point = arg.GetNumber(0)
	//pThis->GetEntity()->SetPosition();
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Class implementation for wxContextMenuEvent
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_ContextMenuEvent)
{
	Gura_AssignMethod(wx_ContextMenuEvent, __wxContextMenuEvent);
	Gura_AssignMethod(wx_ContextMenuEvent, __GetPosition);
	Gura_AssignMethod(wx_ContextMenuEvent, __SetPosition);
}

Gura_ImplementDescendantCreator(wx_ContextMenuEvent)
{
	return new Object_wx_ContextMenuEvent((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
