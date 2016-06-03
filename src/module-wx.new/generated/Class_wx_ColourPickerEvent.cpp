//----------------------------------------------------------------------------
// wxColourPickerEvent
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Gura interfaces for wxColourPickerEvent
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Object implementation for wxColourPickerEvent
//----------------------------------------------------------------------------
Object_wx_ColourPickerEvent::~Object_wx_ColourPickerEvent()
{
}

Object *Object_wx_ColourPickerEvent::Clone() const
{
	return nullptr;
}

String Object_wx_ColourPickerEvent::ToString(bool exprFlag)
{
	String rtn("<wx.ColourPickerEvent:");
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
Gura_DeclareFunctionAlias(__wxColourPickerEvent, "wxColourPickerEvent")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	SetClassToConstruct(Gura_UserClass(wx_ColourPickerEvent));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(__wxColourPickerEvent)
{
	//wxColourPickerEvent();
	return Value::Nil;
}

Gura_DeclareFunctionAlias(__wxColourPickerEvent_1, "wxColourPickerEvent_1")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "generator", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "id", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "colour", VTYPE_number, OCCUR_Once);
	SetClassToConstruct(Gura_UserClass(wx_ColourPickerEvent));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(__wxColourPickerEvent_1)
{
	//int generator = arg.GetNumber(0)
	//int id = arg.GetNumber(1)
	//int colour = arg.GetNumber(2)
	//wxColourPickerEvent();
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Method implementation
//----------------------------------------------------------------------------
Gura_DeclareMethodAlias(wx_ColourPickerEvent, __GetColour, "GetColour")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_ColourPickerEvent, __GetColour)
{
	Object_wx_ColourPickerEvent *pThis = Object_wx_ColourPickerEvent::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->GetColour();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_ColourPickerEvent, __SetColour, "SetColour")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "pos", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_ColourPickerEvent, __SetColour)
{
	Object_wx_ColourPickerEvent *pThis = Object_wx_ColourPickerEvent::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int pos = arg.GetNumber(0)
	//pThis->GetEntity()->SetColour();
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Class implementation for wxColourPickerEvent
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_ColourPickerEvent)
{
	// Constructor assignment
	Gura_AssignFunction(__wxColourPickerEvent);
	Gura_AssignFunction(__wxColourPickerEvent_1);
	// Method assignment
	Gura_AssignMethod(wx_ColourPickerEvent, __GetColour);
	Gura_AssignMethod(wx_ColourPickerEvent, __SetColour);
}

Gura_ImplementDescendantCreator(wx_ColourPickerEvent)
{
	return new Object_wx_ColourPickerEvent((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
