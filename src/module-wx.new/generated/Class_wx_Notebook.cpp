//----------------------------------------------------------------------------
// wxNotebook
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Gura interfaces for wxNotebook
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Object implementation for wxNotebook
//----------------------------------------------------------------------------
Object_wx_Notebook::~Object_wx_Notebook()
{
}

Object *Object_wx_Notebook::Clone() const
{
	return nullptr;
}

String Object_wx_Notebook::ToString(bool exprFlag)
{
	String rtn("<wx.Notebook:");
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
Gura_DeclareFunctionAlias(__Notebook, "Notebook")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	SetClassToConstruct(Gura_UserClass(wx_Notebook));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(__Notebook)
{
	//wxNotebook();
	return Value::Nil;
}

Gura_DeclareFunctionAlias(__Notebook_1, "Notebook_1")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "parent", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "id", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "pos", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "size", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "style", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "name", VTYPE_number, OCCUR_Once);
	SetClassToConstruct(Gura_UserClass(wx_Notebook));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(__Notebook_1)
{
	//wxWindow* parent = arg.GetNumber(0)
	//wxWindowID id = arg.GetNumber(1)
	//const wxPoint& pos = arg.GetNumber(2)
	//const wxSize& size = arg.GetNumber(3)
	//long style = arg.GetNumber(4)
	//const wxString& name = arg.GetNumber(5)
	//wxNotebook(parent, id, pos, size, style, name);
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Method implementation
//----------------------------------------------------------------------------
Gura_DeclareMethodAlias(wx_Notebook, __Create, "Create")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "parent", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "id", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "pos", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "size", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "style", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "name", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Notebook, __Create)
{
	Object_wx_Notebook *pThis = Object_wx_Notebook::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxWindow* parent = arg.GetNumber(0)
	//wxWindowID id = arg.GetNumber(1)
	//const wxPoint& pos = arg.GetNumber(2)
	//const wxSize& size = arg.GetNumber(3)
	//long style = arg.GetNumber(4)
	//const wxString& name = arg.GetNumber(5)
	//bool _rtn = pThis->GetEntity()->Create(parent, id, pos, size, style, name);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Notebook, __GetRowCount, "GetRowCount")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_Notebook, __GetRowCount)
{
	Object_wx_Notebook *pThis = Object_wx_Notebook::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int _rtn = pThis->GetEntity()->GetRowCount();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Notebook, __GetThemeBackgroundColour, "GetThemeBackgroundColour")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_Notebook, __GetThemeBackgroundColour)
{
	Object_wx_Notebook *pThis = Object_wx_Notebook::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxColour _rtn = pThis->GetEntity()->GetThemeBackgroundColour();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Notebook, __OnSelChange, "OnSelChange")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "event", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Notebook, __OnSelChange)
{
	Object_wx_Notebook *pThis = Object_wx_Notebook::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxBookCtrlEvent& event = arg.GetNumber(0)
	//pThis->GetEntity()->OnSelChange(event);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Notebook, __SetPadding, "SetPadding")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "padding", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Notebook, __SetPadding)
{
	Object_wx_Notebook *pThis = Object_wx_Notebook::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxSize& padding = arg.GetNumber(0)
	//pThis->GetEntity()->SetPadding(padding);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Notebook, __GetPageImage, "GetPageImage")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "nPage", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Notebook, __GetPageImage)
{
	Object_wx_Notebook *pThis = Object_wx_Notebook::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//size_t nPage = arg.GetNumber(0)
	//int _rtn = pThis->GetEntity()->GetPageImage(nPage);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Notebook, __SetPageImage, "SetPageImage")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "page", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "image", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Notebook, __SetPageImage)
{
	Object_wx_Notebook *pThis = Object_wx_Notebook::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//size_t page = arg.GetNumber(0)
	//int image = arg.GetNumber(1)
	//bool _rtn = pThis->GetEntity()->SetPageImage(page, image);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Notebook, __GetPageText, "GetPageText")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "nPage", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Notebook, __GetPageText)
{
	Object_wx_Notebook *pThis = Object_wx_Notebook::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//size_t nPage = arg.GetNumber(0)
	//wxString _rtn = pThis->GetEntity()->GetPageText(nPage);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Notebook, __SetPageText, "SetPageText")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "page", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "text", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Notebook, __SetPageText)
{
	Object_wx_Notebook *pThis = Object_wx_Notebook::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//size_t page = arg.GetNumber(0)
	//const wxString& text = arg.GetNumber(1)
	//bool _rtn = pThis->GetEntity()->SetPageText(page, text);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Notebook, __GetSelection, "GetSelection")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_Notebook, __GetSelection)
{
	Object_wx_Notebook *pThis = Object_wx_Notebook::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int _rtn = pThis->GetEntity()->GetSelection();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Notebook, __SetSelection, "SetSelection")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "page", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Notebook, __SetSelection)
{
	Object_wx_Notebook *pThis = Object_wx_Notebook::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//size_t page = arg.GetNumber(0)
	//int _rtn = pThis->GetEntity()->SetSelection(page);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Notebook, __ChangeSelection, "ChangeSelection")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "page", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Notebook, __ChangeSelection)
{
	Object_wx_Notebook *pThis = Object_wx_Notebook::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//size_t page = arg.GetNumber(0)
	//int _rtn = pThis->GetEntity()->ChangeSelection(page);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Notebook, __InsertPage, "InsertPage")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "index", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "page", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "text", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "select", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "imageId", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Notebook, __InsertPage)
{
	Object_wx_Notebook *pThis = Object_wx_Notebook::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//size_t index = arg.GetNumber(0)
	//wxWindow* page = arg.GetNumber(1)
	//const wxString& text = arg.GetNumber(2)
	//bool select = arg.GetNumber(3)
	//int imageId = arg.GetNumber(4)
	//bool _rtn = pThis->GetEntity()->InsertPage(index, page, text, select, imageId);
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Class implementation for wxNotebook
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_Notebook)
{
	// Constructor assignment
	Gura_AssignFunction(__Notebook);
	Gura_AssignFunction(__Notebook_1);
	// Method assignment
	Gura_AssignMethod(wx_Notebook, __Create);
	Gura_AssignMethod(wx_Notebook, __GetRowCount);
	Gura_AssignMethod(wx_Notebook, __GetThemeBackgroundColour);
	Gura_AssignMethod(wx_Notebook, __OnSelChange);
	Gura_AssignMethod(wx_Notebook, __SetPadding);
	Gura_AssignMethod(wx_Notebook, __GetPageImage);
	Gura_AssignMethod(wx_Notebook, __SetPageImage);
	Gura_AssignMethod(wx_Notebook, __GetPageText);
	Gura_AssignMethod(wx_Notebook, __SetPageText);
	Gura_AssignMethod(wx_Notebook, __GetSelection);
	Gura_AssignMethod(wx_Notebook, __SetSelection);
	Gura_AssignMethod(wx_Notebook, __ChangeSelection);
	Gura_AssignMethod(wx_Notebook, __InsertPage);
}

Gura_ImplementDescendantCreator(wx_Notebook)
{
	return new Object_wx_Notebook((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
