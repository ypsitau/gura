//----------------------------------------------------------------------------
// wxMouseCaptureChangedEvent
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Gura interfaces for wxMouseCaptureChangedEvent
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Object implementation for wxMouseCaptureChangedEvent
//----------------------------------------------------------------------------
Object_wx_MouseCaptureChangedEvent::~Object_wx_MouseCaptureChangedEvent()
{
}

Object *Object_wx_MouseCaptureChangedEvent::Clone() const
{
	return nullptr;
}

String Object_wx_MouseCaptureChangedEvent::ToString(bool exprFlag)
{
	String rtn("<wx.MouseCaptureChangedEvent:");
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
Gura_DeclareFunctionAlias(__MouseCaptureChangedEvent, "MouseCaptureChangedEvent")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "windowId", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "gainedCapture", VTYPE_number, OCCUR_Once);
	SetClassToConstruct(Gura_UserClass(wx_MouseCaptureChangedEvent));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(__MouseCaptureChangedEvent)
{
	//wxWindowID windowId = arg.GetNumber(0)
	//wxWindow* gainedCapture = arg.GetNumber(1)
	//wxMouseCaptureChangedEvent(windowId, gainedCapture);
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Method implementation
//----------------------------------------------------------------------------
Gura_DeclareMethodAlias(wx_MouseCaptureChangedEvent, __GetCapturedWindow, "GetCapturedWindow")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_MouseCaptureChangedEvent, __GetCapturedWindow)
{
	Object_wx_MouseCaptureChangedEvent *pThis = Object_wx_MouseCaptureChangedEvent::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxWindow* _rtn = pThis->GetEntity()->GetCapturedWindow();
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Class implementation for wxMouseCaptureChangedEvent
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_MouseCaptureChangedEvent)
{
	// Constructor assignment
	Gura_AssignFunction(__MouseCaptureChangedEvent);
	// Method assignment
	Gura_AssignMethod(wx_MouseCaptureChangedEvent, __GetCapturedWindow);
}

Gura_ImplementDescendantCreator(wx_MouseCaptureChangedEvent)
{
	return new Object_wx_MouseCaptureChangedEvent((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
