//----------------------------------------------------------------------------
// wxAuiDockArt
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Gura interfaces for wxAuiDockArt
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Object implementation for wxAuiDockArt
//----------------------------------------------------------------------------
Object_wx_AuiDockArt::~Object_wx_AuiDockArt()
{
}

Object *Object_wx_AuiDockArt::Clone() const
{
	return nullptr;
}

String Object_wx_AuiDockArt::ToString(bool exprFlag)
{
	String rtn("<wx.AuiDockArt:");
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
Gura_DeclareFunctionAlias(__AuiDockArt, "AuiDockArt")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	SetClassToConstruct(Gura_UserClass(wx_AuiDockArt));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(__AuiDockArt)
{
	//wxAuiDockArt();
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Method implementation
//----------------------------------------------------------------------------
Gura_DeclareMethodAlias(wx_AuiDockArt, __DrawBackground, "DrawBackground")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "dc", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "window", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "orientation", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "rect", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_AuiDockArt, __DrawBackground)
{
	Object_wx_AuiDockArt *pThis = Object_wx_AuiDockArt::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int dc = arg.GetNumber(0)
	//int window = arg.GetNumber(1)
	//int orientation = arg.GetNumber(2)
	//int rect = arg.GetNumber(3)
	//pThis->GetEntity()->DrawBackground();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_AuiDockArt, __DrawBorder, "DrawBorder")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "dc", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "window", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "rect", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "pane", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_AuiDockArt, __DrawBorder)
{
	Object_wx_AuiDockArt *pThis = Object_wx_AuiDockArt::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int dc = arg.GetNumber(0)
	//int window = arg.GetNumber(1)
	//int rect = arg.GetNumber(2)
	//int pane = arg.GetNumber(3)
	//pThis->GetEntity()->DrawBorder();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_AuiDockArt, __DrawCaption, "DrawCaption")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "dc", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "window", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "text", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "rect", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "pane", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_AuiDockArt, __DrawCaption)
{
	Object_wx_AuiDockArt *pThis = Object_wx_AuiDockArt::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int dc = arg.GetNumber(0)
	//int window = arg.GetNumber(1)
	//int text = arg.GetNumber(2)
	//int rect = arg.GetNumber(3)
	//int pane = arg.GetNumber(4)
	//pThis->GetEntity()->DrawCaption();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_AuiDockArt, __DrawGripper, "DrawGripper")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "dc", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "window", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "rect", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "pane", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_AuiDockArt, __DrawGripper)
{
	Object_wx_AuiDockArt *pThis = Object_wx_AuiDockArt::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int dc = arg.GetNumber(0)
	//int window = arg.GetNumber(1)
	//int rect = arg.GetNumber(2)
	//int pane = arg.GetNumber(3)
	//pThis->GetEntity()->DrawGripper();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_AuiDockArt, __DrawPaneButton, "DrawPaneButton")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "dc", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "window", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "button", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "button_state", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "rect", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "pane", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_AuiDockArt, __DrawPaneButton)
{
	Object_wx_AuiDockArt *pThis = Object_wx_AuiDockArt::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int dc = arg.GetNumber(0)
	//int window = arg.GetNumber(1)
	//int button = arg.GetNumber(2)
	//int button_state = arg.GetNumber(3)
	//int rect = arg.GetNumber(4)
	//int pane = arg.GetNumber(5)
	//pThis->GetEntity()->DrawPaneButton();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_AuiDockArt, __DrawSash, "DrawSash")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "dc", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "window", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "orientation", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "rect", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_AuiDockArt, __DrawSash)
{
	Object_wx_AuiDockArt *pThis = Object_wx_AuiDockArt::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int dc = arg.GetNumber(0)
	//int window = arg.GetNumber(1)
	//int orientation = arg.GetNumber(2)
	//int rect = arg.GetNumber(3)
	//pThis->GetEntity()->DrawSash();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_AuiDockArt, __GetColour, "GetColour")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "id", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_AuiDockArt, __GetColour)
{
	Object_wx_AuiDockArt *pThis = Object_wx_AuiDockArt::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int id = arg.GetNumber(0)
	//pThis->GetEntity()->GetColour();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_AuiDockArt, __GetFont, "GetFont")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "id", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_AuiDockArt, __GetFont)
{
	Object_wx_AuiDockArt *pThis = Object_wx_AuiDockArt::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int id = arg.GetNumber(0)
	//pThis->GetEntity()->GetFont();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_AuiDockArt, __GetMetric, "GetMetric")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "id", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_AuiDockArt, __GetMetric)
{
	Object_wx_AuiDockArt *pThis = Object_wx_AuiDockArt::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int id = arg.GetNumber(0)
	//pThis->GetEntity()->GetMetric();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_AuiDockArt, __SetColour, "SetColour")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "id", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "colour", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_AuiDockArt, __SetColour)
{
	Object_wx_AuiDockArt *pThis = Object_wx_AuiDockArt::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int id = arg.GetNumber(0)
	//int colour = arg.GetNumber(1)
	//pThis->GetEntity()->SetColour();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_AuiDockArt, __SetFont, "SetFont")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "id", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "font", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_AuiDockArt, __SetFont)
{
	Object_wx_AuiDockArt *pThis = Object_wx_AuiDockArt::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int id = arg.GetNumber(0)
	//int font = arg.GetNumber(1)
	//pThis->GetEntity()->SetFont();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_AuiDockArt, __SetMetric, "SetMetric")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "id", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "new_val", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_AuiDockArt, __SetMetric)
{
	Object_wx_AuiDockArt *pThis = Object_wx_AuiDockArt::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int id = arg.GetNumber(0)
	//int new_val = arg.GetNumber(1)
	//pThis->GetEntity()->SetMetric();
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Class implementation for wxAuiDockArt
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_AuiDockArt)
{
	// Constructor assignment
	Gura_AssignFunction(__AuiDockArt);
	// Method assignment
	Gura_AssignMethod(wx_AuiDockArt, __DrawBackground);
	Gura_AssignMethod(wx_AuiDockArt, __DrawBorder);
	Gura_AssignMethod(wx_AuiDockArt, __DrawCaption);
	Gura_AssignMethod(wx_AuiDockArt, __DrawGripper);
	Gura_AssignMethod(wx_AuiDockArt, __DrawPaneButton);
	Gura_AssignMethod(wx_AuiDockArt, __DrawSash);
	Gura_AssignMethod(wx_AuiDockArt, __GetColour);
	Gura_AssignMethod(wx_AuiDockArt, __GetFont);
	Gura_AssignMethod(wx_AuiDockArt, __GetMetric);
	Gura_AssignMethod(wx_AuiDockArt, __SetColour);
	Gura_AssignMethod(wx_AuiDockArt, __SetFont);
	Gura_AssignMethod(wx_AuiDockArt, __SetMetric);
}

Gura_ImplementDescendantCreator(wx_AuiDockArt)
{
	return new Object_wx_AuiDockArt((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
