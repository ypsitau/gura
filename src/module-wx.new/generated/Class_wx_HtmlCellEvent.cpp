//----------------------------------------------------------------------------
// wxHtmlCellEvent
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Gura interfaces for wxHtmlCellEvent
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Object implementation for wxHtmlCellEvent
//----------------------------------------------------------------------------
Object_wx_HtmlCellEvent::~Object_wx_HtmlCellEvent()
{
}

Object *Object_wx_HtmlCellEvent::Clone() const
{
	return nullptr;
}

String Object_wx_HtmlCellEvent::ToString(bool exprFlag)
{
	String rtn("<wx.HtmlCellEvent:");
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
Gura_DeclareFunctionAlias(__HtmlCellEvent, "HtmlCellEvent")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "commandType", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "id", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "cell", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "point", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "ev", VTYPE_number, OCCUR_Once);
	SetClassToConstruct(Gura_UserClass(wx_HtmlCellEvent));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(__HtmlCellEvent)
{
	//wxEventType commandType = arg.GetNumber(0)
	//int id = arg.GetNumber(1)
	//wxHtmlCell* cell = arg.GetNumber(2)
	//const wxPoint& point = arg.GetNumber(3)
	//const wxMouseEvent& ev = arg.GetNumber(4)
	//wxHtmlCellEvent(commandType, id, cell, point, ev);
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Method implementation
//----------------------------------------------------------------------------
Gura_DeclareMethodAlias(wx_HtmlCellEvent, __GetCell, "GetCell")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_HtmlCellEvent, __GetCell)
{
	Object_wx_HtmlCellEvent *pThis = Object_wx_HtmlCellEvent::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxHtmlCell* _rtn = pThis->GetEntity()->GetCell();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_HtmlCellEvent, __GetLinkClicked, "GetLinkClicked")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_HtmlCellEvent, __GetLinkClicked)
{
	Object_wx_HtmlCellEvent *pThis = Object_wx_HtmlCellEvent::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//bool _rtn = pThis->GetEntity()->GetLinkClicked();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_HtmlCellEvent, __GetPoint, "GetPoint")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_HtmlCellEvent, __GetPoint)
{
	Object_wx_HtmlCellEvent *pThis = Object_wx_HtmlCellEvent::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxPoint _rtn = pThis->GetEntity()->GetPoint();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_HtmlCellEvent, __SetLinkClicked, "SetLinkClicked")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "linkclicked", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_HtmlCellEvent, __SetLinkClicked)
{
	Object_wx_HtmlCellEvent *pThis = Object_wx_HtmlCellEvent::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//bool linkclicked = arg.GetNumber(0)
	//pThis->GetEntity()->SetLinkClicked(linkclicked);
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Class implementation for wxHtmlCellEvent
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_HtmlCellEvent)
{
	// Constructor assignment
	Gura_AssignFunction(__HtmlCellEvent);
	// Method assignment
	Gura_AssignMethod(wx_HtmlCellEvent, __GetCell);
	Gura_AssignMethod(wx_HtmlCellEvent, __GetLinkClicked);
	Gura_AssignMethod(wx_HtmlCellEvent, __GetPoint);
	Gura_AssignMethod(wx_HtmlCellEvent, __SetLinkClicked);
}

Gura_ImplementDescendantCreator(wx_HtmlCellEvent)
{
	return new Object_wx_HtmlCellEvent((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
