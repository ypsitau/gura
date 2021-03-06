//----------------------------------------------------------------------------
// wxDialog
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Gura interfaces for wxDialog
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Object implementation for wxDialog
//----------------------------------------------------------------------------
Object_wx_Dialog::~Object_wx_Dialog()
{
}

Object *Object_wx_Dialog::Clone() const
{
	return nullptr;
}

String Object_wx_Dialog::ToString(bool exprFlag)
{
	String rtn("<wx.Dialog:");
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
Gura_DeclareFunctionAlias(__Dialog, "Dialog")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	SetClassToConstruct(Gura_UserClass(wx_Dialog));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(__Dialog)
{
	//wxDialog();
	return Value::Nil;
}

Gura_DeclareFunctionAlias(__Dialog_1, "Dialog_1")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "parent", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "id", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "title", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "pos", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "size", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "style", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "name", VTYPE_number, OCCUR_Once);
	SetClassToConstruct(Gura_UserClass(wx_Dialog));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(__Dialog_1)
{
	//wxWindow* parent = arg.GetNumber(0)
	//wxWindowID id = arg.GetNumber(1)
	//const wxString& title = arg.GetNumber(2)
	//const wxPoint& pos = arg.GetNumber(3)
	//const wxSize& size = arg.GetNumber(4)
	//long style = arg.GetNumber(5)
	//const wxString& name = arg.GetNumber(6)
	//wxDialog(parent, id, title, pos, size, style, name);
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Method implementation
//----------------------------------------------------------------------------
Gura_DeclareMethodAlias(wx_Dialog, __AddMainButtonId, "AddMainButtonId")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "id", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Dialog, __AddMainButtonId)
{
	Object_wx_Dialog *pThis = Object_wx_Dialog::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxWindowID id = arg.GetNumber(0)
	//pThis->GetEntity()->AddMainButtonId(id);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Dialog, __CanDoLayoutAdaptation, "CanDoLayoutAdaptation")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_Dialog, __CanDoLayoutAdaptation)
{
	Object_wx_Dialog *pThis = Object_wx_Dialog::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//bool _rtn = pThis->GetEntity()->CanDoLayoutAdaptation();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Dialog, __Centre, "Centre")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "direction", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Dialog, __Centre)
{
	Object_wx_Dialog *pThis = Object_wx_Dialog::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int direction = arg.GetNumber(0)
	//pThis->GetEntity()->Centre(direction);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Dialog, __Create, "Create")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "parent", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "id", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "title", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "pos", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "size", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "style", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "name", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Dialog, __Create)
{
	Object_wx_Dialog *pThis = Object_wx_Dialog::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxWindow* parent = arg.GetNumber(0)
	//wxWindowID id = arg.GetNumber(1)
	//const wxString& title = arg.GetNumber(2)
	//const wxPoint& pos = arg.GetNumber(3)
	//const wxSize& size = arg.GetNumber(4)
	//long style = arg.GetNumber(5)
	//const wxString& name = arg.GetNumber(6)
	//bool _rtn = pThis->GetEntity()->Create(parent, id, title, pos, size, style, name);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Dialog, __CreateButtonSizer, "CreateButtonSizer")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "flags", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Dialog, __CreateButtonSizer)
{
	Object_wx_Dialog *pThis = Object_wx_Dialog::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//long flags = arg.GetNumber(0)
	//wxSizer* _rtn = pThis->GetEntity()->CreateButtonSizer(flags);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Dialog, __CreateSeparatedButtonSizer, "CreateSeparatedButtonSizer")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "flags", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Dialog, __CreateSeparatedButtonSizer)
{
	Object_wx_Dialog *pThis = Object_wx_Dialog::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//long flags = arg.GetNumber(0)
	//wxSizer* _rtn = pThis->GetEntity()->CreateSeparatedButtonSizer(flags);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Dialog, __CreateSeparatedSizer, "CreateSeparatedSizer")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "sizer", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Dialog, __CreateSeparatedSizer)
{
	Object_wx_Dialog *pThis = Object_wx_Dialog::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxSizer* sizer = arg.GetNumber(0)
	//wxSizer* _rtn = pThis->GetEntity()->CreateSeparatedSizer(sizer);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Dialog, __CreateStdDialogButtonSizer, "CreateStdDialogButtonSizer")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "flags", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Dialog, __CreateStdDialogButtonSizer)
{
	Object_wx_Dialog *pThis = Object_wx_Dialog::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//long flags = arg.GetNumber(0)
	//wxStdDialogButtonSizer* _rtn = pThis->GetEntity()->CreateStdDialogButtonSizer(flags);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Dialog, __CreateTextSizer, "CreateTextSizer")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "message", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Dialog, __CreateTextSizer)
{
	Object_wx_Dialog *pThis = Object_wx_Dialog::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxString& message = arg.GetNumber(0)
	//wxSizer* _rtn = pThis->GetEntity()->CreateTextSizer(message);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Dialog, __DoLayoutAdaptation, "DoLayoutAdaptation")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_Dialog, __DoLayoutAdaptation)
{
	Object_wx_Dialog *pThis = Object_wx_Dialog::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//bool _rtn = pThis->GetEntity()->DoLayoutAdaptation();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Dialog, __EnableLayoutAdaptation, "EnableLayoutAdaptation")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "enable", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Dialog, __EnableLayoutAdaptation)
{
	Object_wx_Dialog *pThis = Object_wx_Dialog::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//bool enable = arg.GetNumber(0)
	//pThis->GetEntity()->EnableLayoutAdaptation(enable);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Dialog, __EndModal, "EndModal")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "retCode", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Dialog, __EndModal)
{
	Object_wx_Dialog *pThis = Object_wx_Dialog::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int retCode = arg.GetNumber(0)
	//pThis->GetEntity()->EndModal(retCode);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Dialog, __GetAffirmativeId, "GetAffirmativeId")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_Dialog, __GetAffirmativeId)
{
	Object_wx_Dialog *pThis = Object_wx_Dialog::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int _rtn = pThis->GetEntity()->GetAffirmativeId();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Dialog, __GetContentWindow, "GetContentWindow")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_Dialog, __GetContentWindow)
{
	Object_wx_Dialog *pThis = Object_wx_Dialog::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxWindow* _rtn = pThis->GetEntity()->GetContentWindow();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Dialog, __GetEscapeId, "GetEscapeId")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_Dialog, __GetEscapeId)
{
	Object_wx_Dialog *pThis = Object_wx_Dialog::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int _rtn = pThis->GetEntity()->GetEscapeId();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Dialog, __GetLayoutAdaptationDone, "GetLayoutAdaptationDone")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_Dialog, __GetLayoutAdaptationDone)
{
	Object_wx_Dialog *pThis = Object_wx_Dialog::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//bool _rtn = pThis->GetEntity()->GetLayoutAdaptationDone();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Dialog, __GetLayoutAdaptationLevel, "GetLayoutAdaptationLevel")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_Dialog, __GetLayoutAdaptationLevel)
{
	Object_wx_Dialog *pThis = Object_wx_Dialog::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int _rtn = pThis->GetEntity()->GetLayoutAdaptationLevel();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Dialog, __GetLayoutAdaptationMode, "GetLayoutAdaptationMode")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_Dialog, __GetLayoutAdaptationMode)
{
	Object_wx_Dialog *pThis = Object_wx_Dialog::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxDialogLayoutAdaptationMode _rtn = pThis->GetEntity()->GetLayoutAdaptationMode();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Dialog, __GetLayoutAdapter, "GetLayoutAdapter")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_Dialog, __GetLayoutAdapter)
{
	Object_wx_Dialog *pThis = Object_wx_Dialog::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxDialogLayoutAdapter* _rtn = pThis->GetEntity()->GetLayoutAdapter();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Dialog, __GetMainButtonIds, "GetMainButtonIds")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_Dialog, __GetMainButtonIds)
{
	Object_wx_Dialog *pThis = Object_wx_Dialog::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxArrayInt& _rtn = pThis->GetEntity()->GetMainButtonIds();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Dialog, __GetReturnCode, "GetReturnCode")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_Dialog, __GetReturnCode)
{
	Object_wx_Dialog *pThis = Object_wx_Dialog::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int _rtn = pThis->GetEntity()->GetReturnCode();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Dialog, __GetToolBar, "GetToolBar")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_Dialog, __GetToolBar)
{
	Object_wx_Dialog *pThis = Object_wx_Dialog::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxToolBar* _rtn = pThis->GetEntity()->GetToolBar();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Dialog, __Iconize, "Iconize")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "iconize", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Dialog, __Iconize)
{
	Object_wx_Dialog *pThis = Object_wx_Dialog::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//bool iconize = arg.GetNumber(0)
	//pThis->GetEntity()->Iconize(iconize);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Dialog, __IsIconized, "IsIconized")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_Dialog, __IsIconized)
{
	Object_wx_Dialog *pThis = Object_wx_Dialog::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//bool _rtn = pThis->GetEntity()->IsIconized();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Dialog, __IsLayoutAdaptationEnabled, "IsLayoutAdaptationEnabled")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_Dialog, __IsLayoutAdaptationEnabled)
{
	Object_wx_Dialog *pThis = Object_wx_Dialog::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//bool _rtn = pThis->GetEntity()->IsLayoutAdaptationEnabled();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Dialog, __IsMainButtonId, "IsMainButtonId")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "id", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Dialog, __IsMainButtonId)
{
	Object_wx_Dialog *pThis = Object_wx_Dialog::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxWindowID id = arg.GetNumber(0)
	//bool _rtn = pThis->GetEntity()->IsMainButtonId(id);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Dialog, __IsModal, "IsModal")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_Dialog, __IsModal)
{
	Object_wx_Dialog *pThis = Object_wx_Dialog::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//bool _rtn = pThis->GetEntity()->IsModal();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Dialog, __SetAffirmativeId, "SetAffirmativeId")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "id", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Dialog, __SetAffirmativeId)
{
	Object_wx_Dialog *pThis = Object_wx_Dialog::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int id = arg.GetNumber(0)
	//pThis->GetEntity()->SetAffirmativeId(id);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Dialog, __SetEscapeId, "SetEscapeId")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "id", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Dialog, __SetEscapeId)
{
	Object_wx_Dialog *pThis = Object_wx_Dialog::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int id = arg.GetNumber(0)
	//pThis->GetEntity()->SetEscapeId(id);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Dialog, __SetIcon, "SetIcon")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "icon", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Dialog, __SetIcon)
{
	Object_wx_Dialog *pThis = Object_wx_Dialog::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxIcon& icon = arg.GetNumber(0)
	//pThis->GetEntity()->SetIcon(icon);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Dialog, __SetIcons, "SetIcons")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "icons", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Dialog, __SetIcons)
{
	Object_wx_Dialog *pThis = Object_wx_Dialog::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxIconBundle& icons = arg.GetNumber(0)
	//pThis->GetEntity()->SetIcons(icons);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Dialog, __SetLayoutAdaptationDone, "SetLayoutAdaptationDone")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "done", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Dialog, __SetLayoutAdaptationDone)
{
	Object_wx_Dialog *pThis = Object_wx_Dialog::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//bool done = arg.GetNumber(0)
	//pThis->GetEntity()->SetLayoutAdaptationDone(done);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Dialog, __SetLayoutAdaptationLevel, "SetLayoutAdaptationLevel")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "level", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Dialog, __SetLayoutAdaptationLevel)
{
	Object_wx_Dialog *pThis = Object_wx_Dialog::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int level = arg.GetNumber(0)
	//pThis->GetEntity()->SetLayoutAdaptationLevel(level);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Dialog, __SetLayoutAdaptationMode, "SetLayoutAdaptationMode")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "mode", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Dialog, __SetLayoutAdaptationMode)
{
	Object_wx_Dialog *pThis = Object_wx_Dialog::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxDialogLayoutAdaptationMode mode = arg.GetNumber(0)
	//pThis->GetEntity()->SetLayoutAdaptationMode(mode);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Dialog, __SetLayoutAdapter, "SetLayoutAdapter")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "adapter", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Dialog, __SetLayoutAdapter)
{
	Object_wx_Dialog *pThis = Object_wx_Dialog::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxDialogLayoutAdapter* adapter = arg.GetNumber(0)
	//wxDialogLayoutAdapter* _rtn = pThis->GetEntity()->SetLayoutAdapter(adapter);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Dialog, __SetReturnCode, "SetReturnCode")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "retCode", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Dialog, __SetReturnCode)
{
	Object_wx_Dialog *pThis = Object_wx_Dialog::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int retCode = arg.GetNumber(0)
	//pThis->GetEntity()->SetReturnCode(retCode);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Dialog, __Show, "Show")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "show", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Dialog, __Show)
{
	Object_wx_Dialog *pThis = Object_wx_Dialog::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//bool show = arg.GetNumber(0)
	//bool _rtn = pThis->GetEntity()->Show(show);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Dialog, __ShowModal, "ShowModal")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_Dialog, __ShowModal)
{
	Object_wx_Dialog *pThis = Object_wx_Dialog::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int _rtn = pThis->GetEntity()->ShowModal();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Dialog, __ShowWindowModal, "ShowWindowModal")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_Dialog, __ShowWindowModal)
{
	Object_wx_Dialog *pThis = Object_wx_Dialog::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->ShowWindowModal();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Dialog, __ShowWindowModalThenDo, "ShowWindowModalThenDo")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "onEndModal", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Dialog, __ShowWindowModalThenDo)
{
	Object_wx_Dialog *pThis = Object_wx_Dialog::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const Functor& onEndModal = arg.GetNumber(0)
	//pThis->GetEntity()->ShowWindowModalThenDo(onEndModal);
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Class implementation for wxDialog
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_Dialog)
{
	// Constructor assignment
	Gura_AssignFunction(__Dialog);
	Gura_AssignFunction(__Dialog_1);
	// Method assignment
	Gura_AssignMethod(wx_Dialog, __AddMainButtonId);
	Gura_AssignMethod(wx_Dialog, __CanDoLayoutAdaptation);
	Gura_AssignMethod(wx_Dialog, __Centre);
	Gura_AssignMethod(wx_Dialog, __Create);
	Gura_AssignMethod(wx_Dialog, __CreateButtonSizer);
	Gura_AssignMethod(wx_Dialog, __CreateSeparatedButtonSizer);
	Gura_AssignMethod(wx_Dialog, __CreateSeparatedSizer);
	Gura_AssignMethod(wx_Dialog, __CreateStdDialogButtonSizer);
	Gura_AssignMethod(wx_Dialog, __CreateTextSizer);
	Gura_AssignMethod(wx_Dialog, __DoLayoutAdaptation);
	Gura_AssignMethod(wx_Dialog, __EnableLayoutAdaptation);
	Gura_AssignMethod(wx_Dialog, __EndModal);
	Gura_AssignMethod(wx_Dialog, __GetAffirmativeId);
	Gura_AssignMethod(wx_Dialog, __GetContentWindow);
	Gura_AssignMethod(wx_Dialog, __GetEscapeId);
	Gura_AssignMethod(wx_Dialog, __GetLayoutAdaptationDone);
	Gura_AssignMethod(wx_Dialog, __GetLayoutAdaptationLevel);
	Gura_AssignMethod(wx_Dialog, __GetLayoutAdaptationMode);
	Gura_AssignMethod(wx_Dialog, __GetLayoutAdapter);
	Gura_AssignMethod(wx_Dialog, __GetMainButtonIds);
	Gura_AssignMethod(wx_Dialog, __GetReturnCode);
	Gura_AssignMethod(wx_Dialog, __GetToolBar);
	Gura_AssignMethod(wx_Dialog, __Iconize);
	Gura_AssignMethod(wx_Dialog, __IsIconized);
	Gura_AssignMethod(wx_Dialog, __IsLayoutAdaptationEnabled);
	Gura_AssignMethod(wx_Dialog, __IsMainButtonId);
	Gura_AssignMethod(wx_Dialog, __IsModal);
	Gura_AssignMethod(wx_Dialog, __SetAffirmativeId);
	Gura_AssignMethod(wx_Dialog, __SetEscapeId);
	Gura_AssignMethod(wx_Dialog, __SetIcon);
	Gura_AssignMethod(wx_Dialog, __SetIcons);
	Gura_AssignMethod(wx_Dialog, __SetLayoutAdaptationDone);
	Gura_AssignMethod(wx_Dialog, __SetLayoutAdaptationLevel);
	Gura_AssignMethod(wx_Dialog, __SetLayoutAdaptationMode);
	Gura_AssignMethod(wx_Dialog, __SetLayoutAdapter);
	Gura_AssignMethod(wx_Dialog, __SetReturnCode);
	Gura_AssignMethod(wx_Dialog, __Show);
	Gura_AssignMethod(wx_Dialog, __ShowModal);
	Gura_AssignMethod(wx_Dialog, __ShowWindowModal);
	Gura_AssignMethod(wx_Dialog, __ShowWindowModalThenDo);
}

Gura_ImplementDescendantCreator(wx_Dialog)
{
	return new Object_wx_Dialog((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
