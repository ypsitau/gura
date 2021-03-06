//----------------------------------------------------------------------------
// wxQueryLayoutInfoEvent
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Gura interfaces for wxQueryLayoutInfoEvent
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Object implementation for wxQueryLayoutInfoEvent
//----------------------------------------------------------------------------
Object_wx_QueryLayoutInfoEvent::~Object_wx_QueryLayoutInfoEvent()
{
}

Object *Object_wx_QueryLayoutInfoEvent::Clone() const
{
	return nullptr;
}

String Object_wx_QueryLayoutInfoEvent::ToString(bool exprFlag)
{
	String rtn("<wx.QueryLayoutInfoEvent:");
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
Gura_DeclareFunctionAlias(__QueryLayoutInfoEvent, "QueryLayoutInfoEvent")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "id", VTYPE_number, OCCUR_Once);
	SetClassToConstruct(Gura_UserClass(wx_QueryLayoutInfoEvent));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(__QueryLayoutInfoEvent)
{
	//wxWindowID id = arg.GetNumber(0)
	//wxQueryLayoutInfoEvent(id);
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Method implementation
//----------------------------------------------------------------------------
Gura_DeclareMethodAlias(wx_QueryLayoutInfoEvent, __GetAlignment, "GetAlignment")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_QueryLayoutInfoEvent, __GetAlignment)
{
	Object_wx_QueryLayoutInfoEvent *pThis = Object_wx_QueryLayoutInfoEvent::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxLayoutAlignment _rtn = pThis->GetEntity()->GetAlignment();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_QueryLayoutInfoEvent, __GetFlags, "GetFlags")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_QueryLayoutInfoEvent, __GetFlags)
{
	Object_wx_QueryLayoutInfoEvent *pThis = Object_wx_QueryLayoutInfoEvent::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int _rtn = pThis->GetEntity()->GetFlags();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_QueryLayoutInfoEvent, __GetOrientation, "GetOrientation")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_QueryLayoutInfoEvent, __GetOrientation)
{
	Object_wx_QueryLayoutInfoEvent *pThis = Object_wx_QueryLayoutInfoEvent::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxLayoutOrientation _rtn = pThis->GetEntity()->GetOrientation();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_QueryLayoutInfoEvent, __GetRequestedLength, "GetRequestedLength")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_QueryLayoutInfoEvent, __GetRequestedLength)
{
	Object_wx_QueryLayoutInfoEvent *pThis = Object_wx_QueryLayoutInfoEvent::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int _rtn = pThis->GetEntity()->GetRequestedLength();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_QueryLayoutInfoEvent, __GetSize, "GetSize")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_QueryLayoutInfoEvent, __GetSize)
{
	Object_wx_QueryLayoutInfoEvent *pThis = Object_wx_QueryLayoutInfoEvent::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxSize _rtn = pThis->GetEntity()->GetSize();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_QueryLayoutInfoEvent, __SetAlignment, "SetAlignment")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "alignment", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_QueryLayoutInfoEvent, __SetAlignment)
{
	Object_wx_QueryLayoutInfoEvent *pThis = Object_wx_QueryLayoutInfoEvent::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxLayoutAlignment alignment = arg.GetNumber(0)
	//pThis->GetEntity()->SetAlignment(alignment);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_QueryLayoutInfoEvent, __SetFlags, "SetFlags")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "flags", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_QueryLayoutInfoEvent, __SetFlags)
{
	Object_wx_QueryLayoutInfoEvent *pThis = Object_wx_QueryLayoutInfoEvent::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int flags = arg.GetNumber(0)
	//pThis->GetEntity()->SetFlags(flags);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_QueryLayoutInfoEvent, __SetOrientation, "SetOrientation")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "orientation", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_QueryLayoutInfoEvent, __SetOrientation)
{
	Object_wx_QueryLayoutInfoEvent *pThis = Object_wx_QueryLayoutInfoEvent::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxLayoutOrientation orientation = arg.GetNumber(0)
	//pThis->GetEntity()->SetOrientation(orientation);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_QueryLayoutInfoEvent, __SetRequestedLength, "SetRequestedLength")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "length", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_QueryLayoutInfoEvent, __SetRequestedLength)
{
	Object_wx_QueryLayoutInfoEvent *pThis = Object_wx_QueryLayoutInfoEvent::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int length = arg.GetNumber(0)
	//pThis->GetEntity()->SetRequestedLength(length);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_QueryLayoutInfoEvent, __SetSize, "SetSize")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "size", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_QueryLayoutInfoEvent, __SetSize)
{
	Object_wx_QueryLayoutInfoEvent *pThis = Object_wx_QueryLayoutInfoEvent::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxSize& size = arg.GetNumber(0)
	//pThis->GetEntity()->SetSize(size);
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Class implementation for wxQueryLayoutInfoEvent
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_QueryLayoutInfoEvent)
{
	// Constructor assignment
	Gura_AssignFunction(__QueryLayoutInfoEvent);
	// Method assignment
	Gura_AssignMethod(wx_QueryLayoutInfoEvent, __GetAlignment);
	Gura_AssignMethod(wx_QueryLayoutInfoEvent, __GetFlags);
	Gura_AssignMethod(wx_QueryLayoutInfoEvent, __GetOrientation);
	Gura_AssignMethod(wx_QueryLayoutInfoEvent, __GetRequestedLength);
	Gura_AssignMethod(wx_QueryLayoutInfoEvent, __GetSize);
	Gura_AssignMethod(wx_QueryLayoutInfoEvent, __SetAlignment);
	Gura_AssignMethod(wx_QueryLayoutInfoEvent, __SetFlags);
	Gura_AssignMethod(wx_QueryLayoutInfoEvent, __SetOrientation);
	Gura_AssignMethod(wx_QueryLayoutInfoEvent, __SetRequestedLength);
	Gura_AssignMethod(wx_QueryLayoutInfoEvent, __SetSize);
}

Gura_ImplementDescendantCreator(wx_QueryLayoutInfoEvent)
{
	return new Object_wx_QueryLayoutInfoEvent((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
