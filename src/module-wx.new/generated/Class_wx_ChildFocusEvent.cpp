//----------------------------------------------------------------------------
// wxChildFocusEvent
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Gura interfaces for wxChildFocusEvent
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Object implementation for wxChildFocusEvent
//----------------------------------------------------------------------------
Object_wx_ChildFocusEvent::~Object_wx_ChildFocusEvent()
{
}

Object *Object_wx_ChildFocusEvent::Clone() const
{
	return nullptr;
}

String Object_wx_ChildFocusEvent::ToString(bool exprFlag)
{
	String rtn("<wx.ChildFocusEvent:");
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
Gura_DeclareFunctionAlias(__ChildFocusEvent, "ChildFocusEvent")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "win", VTYPE_number, OCCUR_Once);
	SetClassToConstruct(Gura_UserClass(wx_ChildFocusEvent));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(__ChildFocusEvent)
{
	//wxWindow* win = arg.GetNumber(0)
	//wxChildFocusEvent(win);
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Method implementation
//----------------------------------------------------------------------------
Gura_DeclareMethodAlias(wx_ChildFocusEvent, __GetWindow, "GetWindow")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_ChildFocusEvent, __GetWindow)
{
	Object_wx_ChildFocusEvent *pThis = Object_wx_ChildFocusEvent::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxWindow* _rtn = pThis->GetEntity()->GetWindow();
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Class implementation for wxChildFocusEvent
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_ChildFocusEvent)
{
	// Constructor assignment
	Gura_AssignFunction(__ChildFocusEvent);
	// Method assignment
	Gura_AssignMethod(wx_ChildFocusEvent, __GetWindow);
}

Gura_ImplementDescendantCreator(wx_ChildFocusEvent)
{
	return new Object_wx_ChildFocusEvent((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
