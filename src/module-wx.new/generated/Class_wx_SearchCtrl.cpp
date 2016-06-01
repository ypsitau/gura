//----------------------------------------------------------------------------
// wxSearchCtrl
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Gura interfaces for wxSearchCtrl
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Object implementation for wxSearchCtrl
//----------------------------------------------------------------------------
Object_wx_SearchCtrl::~Object_wx_SearchCtrl()
{
}

Object *Object_wx_SearchCtrl::Clone() const
{
	return nullptr;
}

String Object_wx_SearchCtrl::ToString(bool exprFlag)
{
	String rtn("<wx.SearchCtrl:");
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
Gura_DeclareMethod(wx_SearchCtrl, wxSearchCtrl)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_SearchCtrl, wxSearchCtrl)
{
	Signal &sig = env.GetSignal();
	Object_wx_SearchCtrl *pThis = Object_wx_SearchCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	//pThis->GetEntity()->wxSearchCtrl();
	return Value::Nil;
}

Gura_DeclareMethod(wx_SearchCtrl, wxSearchCtrl_1)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "parent", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "id", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "value", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "pos", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "size", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "style", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "validator", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "name", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_SearchCtrl, wxSearchCtrl_1)
{
	Signal &sig = env.GetSignal();
	Object_wx_SearchCtrl *pThis = Object_wx_SearchCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	//int parent = arg.GetNumber(0)
	//int id = arg.GetNumber(1)
	//int value = arg.GetNumber(2)
	//int pos = arg.GetNumber(3)
	//int size = arg.GetNumber(4)
	//int style = arg.GetNumber(5)
	//int validator = arg.GetNumber(6)
	//int name = arg.GetNumber(7)
	//pThis->GetEntity()->wxSearchCtrl();
	return Value::Nil;
}

Gura_DeclareMethod(wx_SearchCtrl, ~wxSearchCtrl)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_SearchCtrl, ~wxSearchCtrl)
{
	Signal &sig = env.GetSignal();
	Object_wx_SearchCtrl *pThis = Object_wx_SearchCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	//pThis->GetEntity()->~wxSearchCtrl();
	return Value::Nil;
}

Gura_DeclareMethod(wx_SearchCtrl, Create)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "parent", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "id", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "value", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "pos", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "size", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "style", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "validator", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "name", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_SearchCtrl, Create)
{
	Signal &sig = env.GetSignal();
	Object_wx_SearchCtrl *pThis = Object_wx_SearchCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	//int parent = arg.GetNumber(0)
	//int id = arg.GetNumber(1)
	//int value = arg.GetNumber(2)
	//int pos = arg.GetNumber(3)
	//int size = arg.GetNumber(4)
	//int style = arg.GetNumber(5)
	//int validator = arg.GetNumber(6)
	//int name = arg.GetNumber(7)
	//pThis->GetEntity()->Create();
	return Value::Nil;
}

Gura_DeclareMethod(wx_SearchCtrl, GetMenu)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_SearchCtrl, GetMenu)
{
	Signal &sig = env.GetSignal();
	Object_wx_SearchCtrl *pThis = Object_wx_SearchCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	//pThis->GetEntity()->GetMenu();
	return Value::Nil;
}

Gura_DeclareMethod(wx_SearchCtrl, IsSearchButtonVisible)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_SearchCtrl, IsSearchButtonVisible)
{
	Signal &sig = env.GetSignal();
	Object_wx_SearchCtrl *pThis = Object_wx_SearchCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	//pThis->GetEntity()->IsSearchButtonVisible();
	return Value::Nil;
}

Gura_DeclareMethod(wx_SearchCtrl, IsCancelButtonVisible)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_SearchCtrl, IsCancelButtonVisible)
{
	Signal &sig = env.GetSignal();
	Object_wx_SearchCtrl *pThis = Object_wx_SearchCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	//pThis->GetEntity()->IsCancelButtonVisible();
	return Value::Nil;
}

Gura_DeclareMethod(wx_SearchCtrl, SetMenu)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "menu", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_SearchCtrl, SetMenu)
{
	Signal &sig = env.GetSignal();
	Object_wx_SearchCtrl *pThis = Object_wx_SearchCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	//int menu = arg.GetNumber(0)
	//pThis->GetEntity()->SetMenu();
	return Value::Nil;
}

Gura_DeclareMethod(wx_SearchCtrl, ShowCancelButton)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "show", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_SearchCtrl, ShowCancelButton)
{
	Signal &sig = env.GetSignal();
	Object_wx_SearchCtrl *pThis = Object_wx_SearchCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	//int show = arg.GetNumber(0)
	//pThis->GetEntity()->ShowCancelButton();
	return Value::Nil;
}

Gura_DeclareMethod(wx_SearchCtrl, ShowSearchButton)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "show", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_SearchCtrl, ShowSearchButton)
{
	Signal &sig = env.GetSignal();
	Object_wx_SearchCtrl *pThis = Object_wx_SearchCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	//int show = arg.GetNumber(0)
	//pThis->GetEntity()->ShowSearchButton();
	return Value::Nil;
}

Gura_DeclareMethod(wx_SearchCtrl, SetDescriptiveText)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "text", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_SearchCtrl, SetDescriptiveText)
{
	Signal &sig = env.GetSignal();
	Object_wx_SearchCtrl *pThis = Object_wx_SearchCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	//int text = arg.GetNumber(0)
	//pThis->GetEntity()->SetDescriptiveText();
	return Value::Nil;
}

Gura_DeclareMethod(wx_SearchCtrl, GetDescriptiveText)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_SearchCtrl, GetDescriptiveText)
{
	Signal &sig = env.GetSignal();
	Object_wx_SearchCtrl *pThis = Object_wx_SearchCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	//pThis->GetEntity()->GetDescriptiveText();
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Class implementation for wxSearchCtrl
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_SearchCtrl)
{
	Gura_AssignMethod(wx_SearchCtrl, wxSearchCtrl);
	Gura_AssignMethod(wx_SearchCtrl, wxSearchCtrl_1);
	Gura_AssignMethod(wx_SearchCtrl, ~wxSearchCtrl);
	Gura_AssignMethod(wx_SearchCtrl, Create);
	Gura_AssignMethod(wx_SearchCtrl, GetMenu);
	Gura_AssignMethod(wx_SearchCtrl, IsSearchButtonVisible);
	Gura_AssignMethod(wx_SearchCtrl, IsCancelButtonVisible);
	Gura_AssignMethod(wx_SearchCtrl, SetMenu);
	Gura_AssignMethod(wx_SearchCtrl, ShowCancelButton);
	Gura_AssignMethod(wx_SearchCtrl, ShowSearchButton);
	Gura_AssignMethod(wx_SearchCtrl, SetDescriptiveText);
	Gura_AssignMethod(wx_SearchCtrl, GetDescriptiveText);
}

Gura_ImplementDescendantCreator(wx_SearchCtrl)
{
	return new Object_wx_SearchCtrl((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
