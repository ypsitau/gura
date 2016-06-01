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
// Method implementation
//----------------------------------------------------------------------------
Gura_DeclareMethod(wx_HtmlCellEvent, wxHtmlCellEvent)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "commandType", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "id", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "cell", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "point", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "ev", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_HtmlCellEvent, wxHtmlCellEvent)
{
	Signal &sig = env.GetSignal();
	Object_wx_HtmlCellEvent *pThis = Object_wx_HtmlCellEvent::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	//int commandType = arg.GetNumber(0)
	//int id = arg.GetNumber(1)
	//int cell = arg.GetNumber(2)
	//int point = arg.GetNumber(3)
	//int ev = arg.GetNumber(4)
	//pThis->GetEntity()->wxHtmlCellEvent();
	return Value::Nil;
}

Gura_DeclareMethod(wx_HtmlCellEvent, GetCell)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_HtmlCellEvent, GetCell)
{
	Signal &sig = env.GetSignal();
	Object_wx_HtmlCellEvent *pThis = Object_wx_HtmlCellEvent::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	//pThis->GetEntity()->GetCell();
	return Value::Nil;
}

Gura_DeclareMethod(wx_HtmlCellEvent, GetLinkClicked)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_HtmlCellEvent, GetLinkClicked)
{
	Signal &sig = env.GetSignal();
	Object_wx_HtmlCellEvent *pThis = Object_wx_HtmlCellEvent::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	//pThis->GetEntity()->GetLinkClicked();
	return Value::Nil;
}

Gura_DeclareMethod(wx_HtmlCellEvent, GetPoint)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_HtmlCellEvent, GetPoint)
{
	Signal &sig = env.GetSignal();
	Object_wx_HtmlCellEvent *pThis = Object_wx_HtmlCellEvent::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	//pThis->GetEntity()->GetPoint();
	return Value::Nil;
}

Gura_DeclareMethod(wx_HtmlCellEvent, SetLinkClicked)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "linkclicked", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_HtmlCellEvent, SetLinkClicked)
{
	Signal &sig = env.GetSignal();
	Object_wx_HtmlCellEvent *pThis = Object_wx_HtmlCellEvent::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	//int linkclicked = arg.GetNumber(0)
	//pThis->GetEntity()->SetLinkClicked();
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Class implementation for wxHtmlCellEvent
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_HtmlCellEvent)
{
	Gura_AssignMethod(wx_HtmlCellEvent, wxHtmlCellEvent);
	Gura_AssignMethod(wx_HtmlCellEvent, GetCell);
	Gura_AssignMethod(wx_HtmlCellEvent, GetLinkClicked);
	Gura_AssignMethod(wx_HtmlCellEvent, GetPoint);
	Gura_AssignMethod(wx_HtmlCellEvent, SetLinkClicked);
}

Gura_ImplementDescendantCreator(wx_HtmlCellEvent)
{
	return new Object_wx_HtmlCellEvent((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
