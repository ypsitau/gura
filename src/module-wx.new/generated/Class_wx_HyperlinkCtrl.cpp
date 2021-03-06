//----------------------------------------------------------------------------
// wxHyperlinkCtrl
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Gura interfaces for wxHyperlinkCtrl
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Object implementation for wxHyperlinkCtrl
//----------------------------------------------------------------------------
Object_wx_HyperlinkCtrl::~Object_wx_HyperlinkCtrl()
{
}

Object *Object_wx_HyperlinkCtrl::Clone() const
{
	return nullptr;
}

String Object_wx_HyperlinkCtrl::ToString(bool exprFlag)
{
	String rtn("<wx.HyperlinkCtrl:");
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
Gura_DeclareFunctionAlias(__HyperlinkCtrl, "HyperlinkCtrl")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	SetClassToConstruct(Gura_UserClass(wx_HyperlinkCtrl));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(__HyperlinkCtrl)
{
	//wxHyperlinkCtrl();
	return Value::Nil;
}

Gura_DeclareFunctionAlias(__HyperlinkCtrl_1, "HyperlinkCtrl_1")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "parent", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "id", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "label", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "url", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "pos", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "size", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "style", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "name", VTYPE_number, OCCUR_Once);
	SetClassToConstruct(Gura_UserClass(wx_HyperlinkCtrl));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(__HyperlinkCtrl_1)
{
	//wxWindow* parent = arg.GetNumber(0)
	//wxWindowID id = arg.GetNumber(1)
	//const wxString& label = arg.GetNumber(2)
	//const wxString& url = arg.GetNumber(3)
	//const wxPoint& pos = arg.GetNumber(4)
	//const wxSize& size = arg.GetNumber(5)
	//long style = arg.GetNumber(6)
	//const wxString& name = arg.GetNumber(7)
	//wxHyperlinkCtrl(parent, id, label, url, pos, size, style, name);
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Method implementation
//----------------------------------------------------------------------------
Gura_DeclareMethodAlias(wx_HyperlinkCtrl, __Create, "Create")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "parent", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "id", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "label", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "url", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "pos", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "size", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "style", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "name", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_HyperlinkCtrl, __Create)
{
	Object_wx_HyperlinkCtrl *pThis = Object_wx_HyperlinkCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxWindow* parent = arg.GetNumber(0)
	//wxWindowID id = arg.GetNumber(1)
	//const wxString& label = arg.GetNumber(2)
	//const wxString& url = arg.GetNumber(3)
	//const wxPoint& pos = arg.GetNumber(4)
	//const wxSize& size = arg.GetNumber(5)
	//long style = arg.GetNumber(6)
	//const wxString& name = arg.GetNumber(7)
	//bool _rtn = pThis->GetEntity()->Create(parent, id, label, url, pos, size, style, name);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_HyperlinkCtrl, __GetHoverColour, "GetHoverColour")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_HyperlinkCtrl, __GetHoverColour)
{
	Object_wx_HyperlinkCtrl *pThis = Object_wx_HyperlinkCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxColour _rtn = pThis->GetEntity()->GetHoverColour();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_HyperlinkCtrl, __GetNormalColour, "GetNormalColour")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_HyperlinkCtrl, __GetNormalColour)
{
	Object_wx_HyperlinkCtrl *pThis = Object_wx_HyperlinkCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxColour _rtn = pThis->GetEntity()->GetNormalColour();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_HyperlinkCtrl, __GetURL, "GetURL")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_HyperlinkCtrl, __GetURL)
{
	Object_wx_HyperlinkCtrl *pThis = Object_wx_HyperlinkCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxString _rtn = pThis->GetEntity()->GetURL();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_HyperlinkCtrl, __GetVisited, "GetVisited")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_HyperlinkCtrl, __GetVisited)
{
	Object_wx_HyperlinkCtrl *pThis = Object_wx_HyperlinkCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//bool _rtn = pThis->GetEntity()->GetVisited();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_HyperlinkCtrl, __GetVisitedColour, "GetVisitedColour")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_HyperlinkCtrl, __GetVisitedColour)
{
	Object_wx_HyperlinkCtrl *pThis = Object_wx_HyperlinkCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxColour _rtn = pThis->GetEntity()->GetVisitedColour();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_HyperlinkCtrl, __SetHoverColour, "SetHoverColour")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "colour", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_HyperlinkCtrl, __SetHoverColour)
{
	Object_wx_HyperlinkCtrl *pThis = Object_wx_HyperlinkCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxColour& colour = arg.GetNumber(0)
	//pThis->GetEntity()->SetHoverColour(colour);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_HyperlinkCtrl, __SetNormalColour, "SetNormalColour")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "colour", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_HyperlinkCtrl, __SetNormalColour)
{
	Object_wx_HyperlinkCtrl *pThis = Object_wx_HyperlinkCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxColour& colour = arg.GetNumber(0)
	//pThis->GetEntity()->SetNormalColour(colour);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_HyperlinkCtrl, __SetURL, "SetURL")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "url", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_HyperlinkCtrl, __SetURL)
{
	Object_wx_HyperlinkCtrl *pThis = Object_wx_HyperlinkCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxString& url = arg.GetNumber(0)
	//pThis->GetEntity()->SetURL(url);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_HyperlinkCtrl, __SetVisited, "SetVisited")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "visited", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_HyperlinkCtrl, __SetVisited)
{
	Object_wx_HyperlinkCtrl *pThis = Object_wx_HyperlinkCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//bool visited = arg.GetNumber(0)
	//pThis->GetEntity()->SetVisited(visited);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_HyperlinkCtrl, __SetVisitedColour, "SetVisitedColour")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "colour", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_HyperlinkCtrl, __SetVisitedColour)
{
	Object_wx_HyperlinkCtrl *pThis = Object_wx_HyperlinkCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxColour& colour = arg.GetNumber(0)
	//pThis->GetEntity()->SetVisitedColour(colour);
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Class implementation for wxHyperlinkCtrl
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_HyperlinkCtrl)
{
	// Constructor assignment
	Gura_AssignFunction(__HyperlinkCtrl);
	Gura_AssignFunction(__HyperlinkCtrl_1);
	// Method assignment
	Gura_AssignMethod(wx_HyperlinkCtrl, __Create);
	Gura_AssignMethod(wx_HyperlinkCtrl, __GetHoverColour);
	Gura_AssignMethod(wx_HyperlinkCtrl, __GetNormalColour);
	Gura_AssignMethod(wx_HyperlinkCtrl, __GetURL);
	Gura_AssignMethod(wx_HyperlinkCtrl, __GetVisited);
	Gura_AssignMethod(wx_HyperlinkCtrl, __GetVisitedColour);
	Gura_AssignMethod(wx_HyperlinkCtrl, __SetHoverColour);
	Gura_AssignMethod(wx_HyperlinkCtrl, __SetNormalColour);
	Gura_AssignMethod(wx_HyperlinkCtrl, __SetURL);
	Gura_AssignMethod(wx_HyperlinkCtrl, __SetVisited);
	Gura_AssignMethod(wx_HyperlinkCtrl, __SetVisitedColour);
}

Gura_ImplementDescendantCreator(wx_HyperlinkCtrl)
{
	return new Object_wx_HyperlinkCtrl((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
