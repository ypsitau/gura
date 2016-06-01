//----------------------------------------------------------------------------
// wxUIActionSimulator
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Gura interfaces for wxUIActionSimulator
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Object implementation for wxUIActionSimulator
//----------------------------------------------------------------------------
Object_wx_UIActionSimulator::~Object_wx_UIActionSimulator()
{
}

Object *Object_wx_UIActionSimulator::Clone() const
{
	return nullptr;
}

String Object_wx_UIActionSimulator::ToString(bool exprFlag)
{
	String rtn("<wx.UIActionSimulator:");
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
Gura_DeclareMethod(wx_UIActionSimulator, wxUIActionSimulator)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_UIActionSimulator, wxUIActionSimulator)
{
	Signal &sig = env.GetSignal();
	Object_wx_UIActionSimulator *pThis = Object_wx_UIActionSimulator::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	//pThis->GetEntity()->wxUIActionSimulator();
	return Value::Nil;
}

Gura_DeclareMethod(wx_UIActionSimulator, MouseMove)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "x", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "y", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_UIActionSimulator, MouseMove)
{
	Signal &sig = env.GetSignal();
	Object_wx_UIActionSimulator *pThis = Object_wx_UIActionSimulator::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	//int x = arg.GetNumber(0)
	//int y = arg.GetNumber(1)
	//pThis->GetEntity()->MouseMove();
	return Value::Nil;
}

Gura_DeclareMethod(wx_UIActionSimulator, MouseMove_1)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "point", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_UIActionSimulator, MouseMove_1)
{
	Signal &sig = env.GetSignal();
	Object_wx_UIActionSimulator *pThis = Object_wx_UIActionSimulator::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	//int point = arg.GetNumber(0)
	//pThis->GetEntity()->MouseMove();
	return Value::Nil;
}

Gura_DeclareMethod(wx_UIActionSimulator, MouseDown)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "button", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_UIActionSimulator, MouseDown)
{
	Signal &sig = env.GetSignal();
	Object_wx_UIActionSimulator *pThis = Object_wx_UIActionSimulator::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	//int button = arg.GetNumber(0)
	//pThis->GetEntity()->MouseDown();
	return Value::Nil;
}

Gura_DeclareMethod(wx_UIActionSimulator, MouseUp)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "button", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_UIActionSimulator, MouseUp)
{
	Signal &sig = env.GetSignal();
	Object_wx_UIActionSimulator *pThis = Object_wx_UIActionSimulator::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	//int button = arg.GetNumber(0)
	//pThis->GetEntity()->MouseUp();
	return Value::Nil;
}

Gura_DeclareMethod(wx_UIActionSimulator, MouseClick)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "button", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_UIActionSimulator, MouseClick)
{
	Signal &sig = env.GetSignal();
	Object_wx_UIActionSimulator *pThis = Object_wx_UIActionSimulator::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	//int button = arg.GetNumber(0)
	//pThis->GetEntity()->MouseClick();
	return Value::Nil;
}

Gura_DeclareMethod(wx_UIActionSimulator, MouseDblClick)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "button", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_UIActionSimulator, MouseDblClick)
{
	Signal &sig = env.GetSignal();
	Object_wx_UIActionSimulator *pThis = Object_wx_UIActionSimulator::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	//int button = arg.GetNumber(0)
	//pThis->GetEntity()->MouseDblClick();
	return Value::Nil;
}

Gura_DeclareMethod(wx_UIActionSimulator, MouseDragDrop)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "x1", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "y1", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "x2", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "y2", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "button", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_UIActionSimulator, MouseDragDrop)
{
	Signal &sig = env.GetSignal();
	Object_wx_UIActionSimulator *pThis = Object_wx_UIActionSimulator::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	//int x1 = arg.GetNumber(0)
	//int y1 = arg.GetNumber(1)
	//int x2 = arg.GetNumber(2)
	//int y2 = arg.GetNumber(3)
	//int button = arg.GetNumber(4)
	//pThis->GetEntity()->MouseDragDrop();
	return Value::Nil;
}

Gura_DeclareMethod(wx_UIActionSimulator, KeyDown)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "keycode", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "modifiers", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_UIActionSimulator, KeyDown)
{
	Signal &sig = env.GetSignal();
	Object_wx_UIActionSimulator *pThis = Object_wx_UIActionSimulator::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	//int keycode = arg.GetNumber(0)
	//int modifiers = arg.GetNumber(1)
	//pThis->GetEntity()->KeyDown();
	return Value::Nil;
}

Gura_DeclareMethod(wx_UIActionSimulator, KeyUp)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "keycode", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "modifiers", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_UIActionSimulator, KeyUp)
{
	Signal &sig = env.GetSignal();
	Object_wx_UIActionSimulator *pThis = Object_wx_UIActionSimulator::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	//int keycode = arg.GetNumber(0)
	//int modifiers = arg.GetNumber(1)
	//pThis->GetEntity()->KeyUp();
	return Value::Nil;
}

Gura_DeclareMethod(wx_UIActionSimulator, Char)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "keycode", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "modifiers", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_UIActionSimulator, Char)
{
	Signal &sig = env.GetSignal();
	Object_wx_UIActionSimulator *pThis = Object_wx_UIActionSimulator::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	//int keycode = arg.GetNumber(0)
	//int modifiers = arg.GetNumber(1)
	//pThis->GetEntity()->Char();
	return Value::Nil;
}

Gura_DeclareMethod(wx_UIActionSimulator, Select)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "text", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_UIActionSimulator, Select)
{
	Signal &sig = env.GetSignal();
	Object_wx_UIActionSimulator *pThis = Object_wx_UIActionSimulator::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	//int text = arg.GetNumber(0)
	//pThis->GetEntity()->Select();
	return Value::Nil;
}

Gura_DeclareMethod(wx_UIActionSimulator, Text)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "text", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_UIActionSimulator, Text)
{
	Signal &sig = env.GetSignal();
	Object_wx_UIActionSimulator *pThis = Object_wx_UIActionSimulator::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	//int text = arg.GetNumber(0)
	//pThis->GetEntity()->Text();
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Class implementation for wxUIActionSimulator
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_UIActionSimulator)
{
	Gura_AssignMethod(wx_UIActionSimulator, wxUIActionSimulator);
	Gura_AssignMethod(wx_UIActionSimulator, MouseMove);
	Gura_AssignMethod(wx_UIActionSimulator, MouseMove_1);
	Gura_AssignMethod(wx_UIActionSimulator, MouseDown);
	Gura_AssignMethod(wx_UIActionSimulator, MouseUp);
	Gura_AssignMethod(wx_UIActionSimulator, MouseClick);
	Gura_AssignMethod(wx_UIActionSimulator, MouseDblClick);
	Gura_AssignMethod(wx_UIActionSimulator, MouseDragDrop);
	Gura_AssignMethod(wx_UIActionSimulator, KeyDown);
	Gura_AssignMethod(wx_UIActionSimulator, KeyUp);
	Gura_AssignMethod(wx_UIActionSimulator, Char);
	Gura_AssignMethod(wx_UIActionSimulator, Select);
	Gura_AssignMethod(wx_UIActionSimulator, Text);
}

Gura_ImplementDescendantCreator(wx_UIActionSimulator)
{
	return new Object_wx_UIActionSimulator((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
