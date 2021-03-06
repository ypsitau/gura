//----------------------------------------------------------------------------
// wxHtmlCell
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Gura interfaces for wxHtmlCell
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Object implementation for wxHtmlCell
//----------------------------------------------------------------------------
Object_wx_HtmlCell::~Object_wx_HtmlCell()
{
}

Object *Object_wx_HtmlCell::Clone() const
{
	return nullptr;
}

String Object_wx_HtmlCell::ToString(bool exprFlag)
{
	String rtn("<wx.HtmlCell:");
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
Gura_DeclareFunctionAlias(__HtmlCell, "HtmlCell")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	SetClassToConstruct(Gura_UserClass(wx_HtmlCell));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(__HtmlCell)
{
	//wxHtmlCell();
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Method implementation
//----------------------------------------------------------------------------
Gura_DeclareMethodAlias(wx_HtmlCell, __AdjustPagebreak, "AdjustPagebreak")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "pagebreak", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "known_pagebreaks", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "pageHeight", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_HtmlCell, __AdjustPagebreak)
{
	Object_wx_HtmlCell *pThis = Object_wx_HtmlCell::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int* pagebreak = arg.GetNumber(0)
	//const wxArrayInt& known_pagebreaks = arg.GetNumber(1)
	//int pageHeight = arg.GetNumber(2)
	//bool _rtn = pThis->GetEntity()->AdjustPagebreak(pagebreak, known_pagebreaks, pageHeight);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_HtmlCell, __Draw, "Draw")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "dc", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "x", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "y", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "view_y1", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "view_y2", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "info", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_HtmlCell, __Draw)
{
	Object_wx_HtmlCell *pThis = Object_wx_HtmlCell::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxDC& dc = arg.GetNumber(0)
	//int x = arg.GetNumber(1)
	//int y = arg.GetNumber(2)
	//int view_y1 = arg.GetNumber(3)
	//int view_y2 = arg.GetNumber(4)
	//wxHtmlRenderingInfo& info = arg.GetNumber(5)
	//pThis->GetEntity()->Draw(dc, x, y, view_y1, view_y2, info);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_HtmlCell, __DrawInvisible, "DrawInvisible")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "dc", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "x", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "y", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "info", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_HtmlCell, __DrawInvisible)
{
	Object_wx_HtmlCell *pThis = Object_wx_HtmlCell::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxDC& dc = arg.GetNumber(0)
	//int x = arg.GetNumber(1)
	//int y = arg.GetNumber(2)
	//wxHtmlRenderingInfo& info = arg.GetNumber(3)
	//pThis->GetEntity()->DrawInvisible(dc, x, y, info);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_HtmlCell, __Find, "Find")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "condition", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "param", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_HtmlCell, __Find)
{
	Object_wx_HtmlCell *pThis = Object_wx_HtmlCell::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int condition = arg.GetNumber(0)
	//const void* param = arg.GetNumber(1)
	//const wxHtmlCell* _rtn = pThis->GetEntity()->Find(condition, param);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_HtmlCell, __GetDescent, "GetDescent")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_HtmlCell, __GetDescent)
{
	Object_wx_HtmlCell *pThis = Object_wx_HtmlCell::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int _rtn = pThis->GetEntity()->GetDescent();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_HtmlCell, __GetFirstChild, "GetFirstChild")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_HtmlCell, __GetFirstChild)
{
	Object_wx_HtmlCell *pThis = Object_wx_HtmlCell::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxHtmlCell* _rtn = pThis->GetEntity()->GetFirstChild();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_HtmlCell, __GetHeight, "GetHeight")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_HtmlCell, __GetHeight)
{
	Object_wx_HtmlCell *pThis = Object_wx_HtmlCell::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int _rtn = pThis->GetEntity()->GetHeight();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_HtmlCell, __GetId, "GetId")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_HtmlCell, __GetId)
{
	Object_wx_HtmlCell *pThis = Object_wx_HtmlCell::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxString& _rtn = pThis->GetEntity()->GetId();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_HtmlCell, __GetLink, "GetLink")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "x", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "y", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_HtmlCell, __GetLink)
{
	Object_wx_HtmlCell *pThis = Object_wx_HtmlCell::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int x = arg.GetNumber(0)
	//int y = arg.GetNumber(1)
	//wxHtmlLinkInfo* _rtn = pThis->GetEntity()->GetLink(x, y);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_HtmlCell, __GetMouseCursor, "GetMouseCursor")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "window", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_HtmlCell, __GetMouseCursor)
{
	Object_wx_HtmlCell *pThis = Object_wx_HtmlCell::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxHtmlWindowInterface* window = arg.GetNumber(0)
	//wxCursor _rtn = pThis->GetEntity()->GetMouseCursor(window);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_HtmlCell, __GetMouseCursorAt, "GetMouseCursorAt")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "window", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "rePos", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_HtmlCell, __GetMouseCursorAt)
{
	Object_wx_HtmlCell *pThis = Object_wx_HtmlCell::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxHtmlWindowInterface* window = arg.GetNumber(0)
	//const wxPoint& rePos = arg.GetNumber(1)
	//wxCursor _rtn = pThis->GetEntity()->GetMouseCursorAt(window, rePos);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_HtmlCell, __GetNext, "GetNext")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_HtmlCell, __GetNext)
{
	Object_wx_HtmlCell *pThis = Object_wx_HtmlCell::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxHtmlCell* _rtn = pThis->GetEntity()->GetNext();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_HtmlCell, __GetParent, "GetParent")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_HtmlCell, __GetParent)
{
	Object_wx_HtmlCell *pThis = Object_wx_HtmlCell::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxHtmlContainerCell* _rtn = pThis->GetEntity()->GetParent();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_HtmlCell, __GetPosX, "GetPosX")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_HtmlCell, __GetPosX)
{
	Object_wx_HtmlCell *pThis = Object_wx_HtmlCell::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int _rtn = pThis->GetEntity()->GetPosX();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_HtmlCell, __GetPosY, "GetPosY")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_HtmlCell, __GetPosY)
{
	Object_wx_HtmlCell *pThis = Object_wx_HtmlCell::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int _rtn = pThis->GetEntity()->GetPosY();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_HtmlCell, __GetWidth, "GetWidth")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_HtmlCell, __GetWidth)
{
	Object_wx_HtmlCell *pThis = Object_wx_HtmlCell::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int _rtn = pThis->GetEntity()->GetWidth();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_HtmlCell, __Layout, "Layout")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "w", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_HtmlCell, __Layout)
{
	Object_wx_HtmlCell *pThis = Object_wx_HtmlCell::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int w = arg.GetNumber(0)
	//pThis->GetEntity()->Layout(w);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_HtmlCell, __ProcessMouseClick, "ProcessMouseClick")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "window", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "pos", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "event", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_HtmlCell, __ProcessMouseClick)
{
	Object_wx_HtmlCell *pThis = Object_wx_HtmlCell::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxHtmlWindowInterface* window = arg.GetNumber(0)
	//const wxPoint& pos = arg.GetNumber(1)
	//const wxMouseEvent& event = arg.GetNumber(2)
	//bool _rtn = pThis->GetEntity()->ProcessMouseClick(window, pos, event);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_HtmlCell, __SetId, "SetId")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "id", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_HtmlCell, __SetId)
{
	Object_wx_HtmlCell *pThis = Object_wx_HtmlCell::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxString& id = arg.GetNumber(0)
	//pThis->GetEntity()->SetId(id);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_HtmlCell, __SetLink, "SetLink")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "link", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_HtmlCell, __SetLink)
{
	Object_wx_HtmlCell *pThis = Object_wx_HtmlCell::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxHtmlLinkInfo& link = arg.GetNumber(0)
	//pThis->GetEntity()->SetLink(link);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_HtmlCell, __SetNext, "SetNext")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "cell", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_HtmlCell, __SetNext)
{
	Object_wx_HtmlCell *pThis = Object_wx_HtmlCell::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxHtmlCell* cell = arg.GetNumber(0)
	//pThis->GetEntity()->SetNext(cell);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_HtmlCell, __SetParent, "SetParent")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "p", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_HtmlCell, __SetParent)
{
	Object_wx_HtmlCell *pThis = Object_wx_HtmlCell::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxHtmlContainerCell* p = arg.GetNumber(0)
	//pThis->GetEntity()->SetParent(p);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_HtmlCell, __SetPos, "SetPos")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "x", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "y", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_HtmlCell, __SetPos)
{
	Object_wx_HtmlCell *pThis = Object_wx_HtmlCell::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int x = arg.GetNumber(0)
	//int y = arg.GetNumber(1)
	//pThis->GetEntity()->SetPos(x, y);
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Class implementation for wxHtmlCell
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_HtmlCell)
{
	// Constructor assignment
	Gura_AssignFunction(__HtmlCell);
	// Method assignment
	Gura_AssignMethod(wx_HtmlCell, __AdjustPagebreak);
	Gura_AssignMethod(wx_HtmlCell, __Draw);
	Gura_AssignMethod(wx_HtmlCell, __DrawInvisible);
	Gura_AssignMethod(wx_HtmlCell, __Find);
	Gura_AssignMethod(wx_HtmlCell, __GetDescent);
	Gura_AssignMethod(wx_HtmlCell, __GetFirstChild);
	Gura_AssignMethod(wx_HtmlCell, __GetHeight);
	Gura_AssignMethod(wx_HtmlCell, __GetId);
	Gura_AssignMethod(wx_HtmlCell, __GetLink);
	Gura_AssignMethod(wx_HtmlCell, __GetMouseCursor);
	Gura_AssignMethod(wx_HtmlCell, __GetMouseCursorAt);
	Gura_AssignMethod(wx_HtmlCell, __GetNext);
	Gura_AssignMethod(wx_HtmlCell, __GetParent);
	Gura_AssignMethod(wx_HtmlCell, __GetPosX);
	Gura_AssignMethod(wx_HtmlCell, __GetPosY);
	Gura_AssignMethod(wx_HtmlCell, __GetWidth);
	Gura_AssignMethod(wx_HtmlCell, __Layout);
	Gura_AssignMethod(wx_HtmlCell, __ProcessMouseClick);
	Gura_AssignMethod(wx_HtmlCell, __SetId);
	Gura_AssignMethod(wx_HtmlCell, __SetLink);
	Gura_AssignMethod(wx_HtmlCell, __SetNext);
	Gura_AssignMethod(wx_HtmlCell, __SetParent);
	Gura_AssignMethod(wx_HtmlCell, __SetPos);
}

Gura_ImplementDescendantCreator(wx_HtmlCell)
{
	return new Object_wx_HtmlCell((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
