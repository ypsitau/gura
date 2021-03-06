//----------------------------------------------------------------------------
// wxShowEvent
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Gura interfaces for wxShowEvent
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Object implementation for wxShowEvent
//----------------------------------------------------------------------------
Object_wx_ShowEvent::~Object_wx_ShowEvent()
{
}

Object *Object_wx_ShowEvent::Clone() const
{
	return nullptr;
}

String Object_wx_ShowEvent::ToString(bool exprFlag)
{
	String rtn("<wx.ShowEvent:");
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
Gura_DeclareFunctionAlias(__ShowEvent, "ShowEvent")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "winid", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "show", VTYPE_number, OCCUR_Once);
	SetClassToConstruct(Gura_UserClass(wx_ShowEvent));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(__ShowEvent)
{
	//int winid = arg.GetNumber(0)
	//bool show = arg.GetNumber(1)
	//wxShowEvent(winid, show);
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Method implementation
//----------------------------------------------------------------------------
Gura_DeclareMethodAlias(wx_ShowEvent, __SetShow, "SetShow")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "show", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_ShowEvent, __SetShow)
{
	Object_wx_ShowEvent *pThis = Object_wx_ShowEvent::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//bool show = arg.GetNumber(0)
	//pThis->GetEntity()->SetShow(show);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_ShowEvent, __IsShown, "IsShown")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_ShowEvent, __IsShown)
{
	Object_wx_ShowEvent *pThis = Object_wx_ShowEvent::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//bool _rtn = pThis->GetEntity()->IsShown();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_ShowEvent, __GetShow, "GetShow")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_ShowEvent, __GetShow)
{
	Object_wx_ShowEvent *pThis = Object_wx_ShowEvent::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//bool _rtn = pThis->GetEntity()->GetShow();
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Class implementation for wxShowEvent
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_ShowEvent)
{
	// Constructor assignment
	Gura_AssignFunction(__ShowEvent);
	// Method assignment
	Gura_AssignMethod(wx_ShowEvent, __SetShow);
	Gura_AssignMethod(wx_ShowEvent, __IsShown);
	Gura_AssignMethod(wx_ShowEvent, __GetShow);
}

Gura_ImplementDescendantCreator(wx_ShowEvent)
{
	return new Object_wx_ShowEvent((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
