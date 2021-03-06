//----------------------------------------------------------------------------
// wxWebKitCtrl
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Gura interfaces for wxWebKitCtrl
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Object implementation for wxWebKitCtrl
//----------------------------------------------------------------------------
Object_wx_WebKitCtrl::~Object_wx_WebKitCtrl()
{
}

Object *Object_wx_WebKitCtrl::Clone() const
{
	return nullptr;
}

String Object_wx_WebKitCtrl::ToString(bool exprFlag)
{
	String rtn("<wx.WebKitCtrl:");
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
Gura_DeclareFunctionAlias(__WebKitCtrl, "WebKitCtrl")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	SetClassToConstruct(Gura_UserClass(wx_WebKitCtrl));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(__WebKitCtrl)
{
	//wxWebKitCtrl();
	return Value::Nil;
}

Gura_DeclareFunctionAlias(__WebKitCtrl_1, "WebKitCtrl_1")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "parent", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "winid", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "strURL", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "pos", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "size", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "style", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "validator", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "name", VTYPE_number, OCCUR_Once);
	SetClassToConstruct(Gura_UserClass(wx_WebKitCtrl));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(__WebKitCtrl_1)
{
	//wxWindow* parent = arg.GetNumber(0)
	//wxWindowID winid = arg.GetNumber(1)
	//const wxString& strURL = arg.GetNumber(2)
	//const wxPoint& pos = arg.GetNumber(3)
	//const wxSize& size = arg.GetNumber(4)
	//long style = arg.GetNumber(5)
	//const wxValidator& validator = arg.GetNumber(6)
	//const wxString& name = arg.GetNumber(7)
	//wxWebKitCtrl(parent, winid, strURL, pos, size, style, validator, name);
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Method implementation
//----------------------------------------------------------------------------
Gura_DeclareMethodAlias(wx_WebKitCtrl, __Create, "Create")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "parent", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "winid", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "strURL", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "pos", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "size", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "style", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "validator", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "name", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_WebKitCtrl, __Create)
{
	Object_wx_WebKitCtrl *pThis = Object_wx_WebKitCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxWindow* parent = arg.GetNumber(0)
	//wxWindowID winid = arg.GetNumber(1)
	//const wxString& strURL = arg.GetNumber(2)
	//const wxPoint& pos = arg.GetNumber(3)
	//const wxSize& size = arg.GetNumber(4)
	//long style = arg.GetNumber(5)
	//const wxValidator& validator = arg.GetNumber(6)
	//const wxString& name = arg.GetNumber(7)
	//bool _rtn = pThis->GetEntity()->Create(parent, winid, strURL, pos, size, style, validator, name);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_WebKitCtrl, __LoadURL, "LoadURL")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "url", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_WebKitCtrl, __LoadURL)
{
	Object_wx_WebKitCtrl *pThis = Object_wx_WebKitCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxString& url = arg.GetNumber(0)
	//pThis->GetEntity()->LoadURL(url);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_WebKitCtrl, __CanGoBack, "CanGoBack")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_WebKitCtrl, __CanGoBack)
{
	Object_wx_WebKitCtrl *pThis = Object_wx_WebKitCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//bool _rtn = pThis->GetEntity()->CanGoBack();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_WebKitCtrl, __CanGoForward, "CanGoForward")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_WebKitCtrl, __CanGoForward)
{
	Object_wx_WebKitCtrl *pThis = Object_wx_WebKitCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//bool _rtn = pThis->GetEntity()->CanGoForward();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_WebKitCtrl, __GoBack, "GoBack")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_WebKitCtrl, __GoBack)
{
	Object_wx_WebKitCtrl *pThis = Object_wx_WebKitCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//bool _rtn = pThis->GetEntity()->GoBack();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_WebKitCtrl, __GoForward, "GoForward")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_WebKitCtrl, __GoForward)
{
	Object_wx_WebKitCtrl *pThis = Object_wx_WebKitCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//bool _rtn = pThis->GetEntity()->GoForward();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_WebKitCtrl, __Reload, "Reload")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_WebKitCtrl, __Reload)
{
	Object_wx_WebKitCtrl *pThis = Object_wx_WebKitCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->Reload();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_WebKitCtrl, __Stop, "Stop")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_WebKitCtrl, __Stop)
{
	Object_wx_WebKitCtrl *pThis = Object_wx_WebKitCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->Stop();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_WebKitCtrl, __CanGetPageSource, "CanGetPageSource")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_WebKitCtrl, __CanGetPageSource)
{
	Object_wx_WebKitCtrl *pThis = Object_wx_WebKitCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//bool _rtn = pThis->GetEntity()->CanGetPageSource();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_WebKitCtrl, __GetPageSource, "GetPageSource")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_WebKitCtrl, __GetPageSource)
{
	Object_wx_WebKitCtrl *pThis = Object_wx_WebKitCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxString _rtn = pThis->GetEntity()->GetPageSource();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_WebKitCtrl, __SetPageSource, "SetPageSource")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "source", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "baseUrl", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_WebKitCtrl, __SetPageSource)
{
	Object_wx_WebKitCtrl *pThis = Object_wx_WebKitCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxString& source = arg.GetNumber(0)
	//const wxString& baseUrl = arg.GetNumber(1)
	//pThis->GetEntity()->SetPageSource(source, baseUrl);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_WebKitCtrl, __GetPageURL, "GetPageURL")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_WebKitCtrl, __GetPageURL)
{
	Object_wx_WebKitCtrl *pThis = Object_wx_WebKitCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxString _rtn = pThis->GetEntity()->GetPageURL();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_WebKitCtrl, __SetPageTitle, "SetPageTitle")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "title", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_WebKitCtrl, __SetPageTitle)
{
	Object_wx_WebKitCtrl *pThis = Object_wx_WebKitCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxString& title = arg.GetNumber(0)
	//pThis->GetEntity()->SetPageTitle(title);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_WebKitCtrl, __GetPageTitle, "GetPageTitle")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_WebKitCtrl, __GetPageTitle)
{
	Object_wx_WebKitCtrl *pThis = Object_wx_WebKitCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxString _rtn = pThis->GetEntity()->GetPageTitle();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_WebKitCtrl, __SetTitle, "SetTitle")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "title", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_WebKitCtrl, __SetTitle)
{
	Object_wx_WebKitCtrl *pThis = Object_wx_WebKitCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxString& title = arg.GetNumber(0)
	//pThis->GetEntity()->SetTitle(title);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_WebKitCtrl, __GetTitle, "GetTitle")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_WebKitCtrl, __GetTitle)
{
	Object_wx_WebKitCtrl *pThis = Object_wx_WebKitCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxString _rtn = pThis->GetEntity()->GetTitle();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_WebKitCtrl, __GetSelection, "GetSelection")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_WebKitCtrl, __GetSelection)
{
	Object_wx_WebKitCtrl *pThis = Object_wx_WebKitCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxString _rtn = pThis->GetEntity()->GetSelection();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_WebKitCtrl, __CanIncreaseTextSize, "CanIncreaseTextSize")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_WebKitCtrl, __CanIncreaseTextSize)
{
	Object_wx_WebKitCtrl *pThis = Object_wx_WebKitCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//bool _rtn = pThis->GetEntity()->CanIncreaseTextSize();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_WebKitCtrl, __IncreaseTextSize, "IncreaseTextSize")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_WebKitCtrl, __IncreaseTextSize)
{
	Object_wx_WebKitCtrl *pThis = Object_wx_WebKitCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->IncreaseTextSize();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_WebKitCtrl, __CanDecreaseTextSize, "CanDecreaseTextSize")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_WebKitCtrl, __CanDecreaseTextSize)
{
	Object_wx_WebKitCtrl *pThis = Object_wx_WebKitCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//bool _rtn = pThis->GetEntity()->CanDecreaseTextSize();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_WebKitCtrl, __DecreaseTextSize, "DecreaseTextSize")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_WebKitCtrl, __DecreaseTextSize)
{
	Object_wx_WebKitCtrl *pThis = Object_wx_WebKitCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->DecreaseTextSize();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_WebKitCtrl, __Print, "Print")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "showPrompt", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_WebKitCtrl, __Print)
{
	Object_wx_WebKitCtrl *pThis = Object_wx_WebKitCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//bool showPrompt = arg.GetNumber(0)
	//pThis->GetEntity()->Print(showPrompt);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_WebKitCtrl, __MakeEditable, "MakeEditable")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "enable", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_WebKitCtrl, __MakeEditable)
{
	Object_wx_WebKitCtrl *pThis = Object_wx_WebKitCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//bool enable = arg.GetNumber(0)
	//pThis->GetEntity()->MakeEditable(enable);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_WebKitCtrl, __IsEditable, "IsEditable")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_WebKitCtrl, __IsEditable)
{
	Object_wx_WebKitCtrl *pThis = Object_wx_WebKitCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//bool _rtn = pThis->GetEntity()->IsEditable();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_WebKitCtrl, __RunScript, "RunScript")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "javascript", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_WebKitCtrl, __RunScript)
{
	Object_wx_WebKitCtrl *pThis = Object_wx_WebKitCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxString& javascript = arg.GetNumber(0)
	//wxString _rtn = pThis->GetEntity()->RunScript(javascript);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_WebKitCtrl, __SetScrollPos, "SetScrollPos")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "pos", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_WebKitCtrl, __SetScrollPos)
{
	Object_wx_WebKitCtrl *pThis = Object_wx_WebKitCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int pos = arg.GetNumber(0)
	//pThis->GetEntity()->SetScrollPos(pos);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_WebKitCtrl, __GetScrollPos, "GetScrollPos")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_WebKitCtrl, __GetScrollPos)
{
	Object_wx_WebKitCtrl *pThis = Object_wx_WebKitCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int _rtn = pThis->GetEntity()->GetScrollPos();
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Class implementation for wxWebKitCtrl
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_WebKitCtrl)
{
	// Constructor assignment
	Gura_AssignFunction(__WebKitCtrl);
	Gura_AssignFunction(__WebKitCtrl_1);
	// Method assignment
	Gura_AssignMethod(wx_WebKitCtrl, __Create);
	Gura_AssignMethod(wx_WebKitCtrl, __LoadURL);
	Gura_AssignMethod(wx_WebKitCtrl, __CanGoBack);
	Gura_AssignMethod(wx_WebKitCtrl, __CanGoForward);
	Gura_AssignMethod(wx_WebKitCtrl, __GoBack);
	Gura_AssignMethod(wx_WebKitCtrl, __GoForward);
	Gura_AssignMethod(wx_WebKitCtrl, __Reload);
	Gura_AssignMethod(wx_WebKitCtrl, __Stop);
	Gura_AssignMethod(wx_WebKitCtrl, __CanGetPageSource);
	Gura_AssignMethod(wx_WebKitCtrl, __GetPageSource);
	Gura_AssignMethod(wx_WebKitCtrl, __SetPageSource);
	Gura_AssignMethod(wx_WebKitCtrl, __GetPageURL);
	Gura_AssignMethod(wx_WebKitCtrl, __SetPageTitle);
	Gura_AssignMethod(wx_WebKitCtrl, __GetPageTitle);
	Gura_AssignMethod(wx_WebKitCtrl, __SetTitle);
	Gura_AssignMethod(wx_WebKitCtrl, __GetTitle);
	Gura_AssignMethod(wx_WebKitCtrl, __GetSelection);
	Gura_AssignMethod(wx_WebKitCtrl, __CanIncreaseTextSize);
	Gura_AssignMethod(wx_WebKitCtrl, __IncreaseTextSize);
	Gura_AssignMethod(wx_WebKitCtrl, __CanDecreaseTextSize);
	Gura_AssignMethod(wx_WebKitCtrl, __DecreaseTextSize);
	Gura_AssignMethod(wx_WebKitCtrl, __Print);
	Gura_AssignMethod(wx_WebKitCtrl, __MakeEditable);
	Gura_AssignMethod(wx_WebKitCtrl, __IsEditable);
	Gura_AssignMethod(wx_WebKitCtrl, __RunScript);
	Gura_AssignMethod(wx_WebKitCtrl, __SetScrollPos);
	Gura_AssignMethod(wx_WebKitCtrl, __GetScrollPos);
}

Gura_ImplementDescendantCreator(wx_WebKitCtrl)
{
	return new Object_wx_WebKitCtrl((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
