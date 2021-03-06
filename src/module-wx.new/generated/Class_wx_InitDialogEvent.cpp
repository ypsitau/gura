//----------------------------------------------------------------------------
// wxInitDialogEvent
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Gura interfaces for wxInitDialogEvent
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Object implementation for wxInitDialogEvent
//----------------------------------------------------------------------------
Object_wx_InitDialogEvent::~Object_wx_InitDialogEvent()
{
}

Object *Object_wx_InitDialogEvent::Clone() const
{
	return nullptr;
}

String Object_wx_InitDialogEvent::ToString(bool exprFlag)
{
	String rtn("<wx.InitDialogEvent:");
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
Gura_DeclareFunctionAlias(__InitDialogEvent, "InitDialogEvent")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "id", VTYPE_number, OCCUR_Once);
	SetClassToConstruct(Gura_UserClass(wx_InitDialogEvent));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(__InitDialogEvent)
{
	//int id = arg.GetNumber(0)
	//wxInitDialogEvent(id);
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Class implementation for wxInitDialogEvent
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_InitDialogEvent)
{
	// Constructor assignment
	Gura_AssignFunction(__InitDialogEvent);
}

Gura_ImplementDescendantCreator(wx_InitDialogEvent)
{
	return new Object_wx_InitDialogEvent((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
