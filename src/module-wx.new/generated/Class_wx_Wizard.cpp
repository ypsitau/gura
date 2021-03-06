//----------------------------------------------------------------------------
// wxWizard
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Gura interfaces for wxWizard
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Object implementation for wxWizard
//----------------------------------------------------------------------------
Object_wx_Wizard::~Object_wx_Wizard()
{
}

Object *Object_wx_Wizard::Clone() const
{
	return nullptr;
}

String Object_wx_Wizard::ToString(bool exprFlag)
{
	String rtn("<wx.Wizard:");
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
Gura_DeclareFunctionAlias(__Wizard, "Wizard")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	SetClassToConstruct(Gura_UserClass(wx_Wizard));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(__Wizard)
{
	//wxWizard();
	return Value::Nil;
}

Gura_DeclareFunctionAlias(__Wizard_1, "Wizard_1")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "parent", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "id", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "title", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "bitmap", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "pos", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "style", VTYPE_number, OCCUR_Once);
	SetClassToConstruct(Gura_UserClass(wx_Wizard));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(__Wizard_1)
{
	//wxWindow* parent = arg.GetNumber(0)
	//int id = arg.GetNumber(1)
	//const wxString& title = arg.GetNumber(2)
	//const wxBitmap& bitmap = arg.GetNumber(3)
	//const wxPoint& pos = arg.GetNumber(4)
	//long style = arg.GetNumber(5)
	//wxWizard(parent, id, title, bitmap, pos, style);
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Method implementation
//----------------------------------------------------------------------------
Gura_DeclareMethodAlias(wx_Wizard, __Create, "Create")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "parent", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "id", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "title", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "bitmap", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "pos", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "style", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Wizard, __Create)
{
	Object_wx_Wizard *pThis = Object_wx_Wizard::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxWindow* parent = arg.GetNumber(0)
	//int id = arg.GetNumber(1)
	//const wxString& title = arg.GetNumber(2)
	//const wxBitmap& bitmap = arg.GetNumber(3)
	//const wxPoint& pos = arg.GetNumber(4)
	//long style = arg.GetNumber(5)
	//bool _rtn = pThis->GetEntity()->Create(parent, id, title, bitmap, pos, style);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Wizard, __FitToPage, "FitToPage")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "firstPage", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Wizard, __FitToPage)
{
	Object_wx_Wizard *pThis = Object_wx_Wizard::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxWizardPage* firstPage = arg.GetNumber(0)
	//pThis->GetEntity()->FitToPage(firstPage);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Wizard, __GetBitmap, "GetBitmap")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_Wizard, __GetBitmap)
{
	Object_wx_Wizard *pThis = Object_wx_Wizard::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxBitmap& _rtn = pThis->GetEntity()->GetBitmap();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Wizard, __GetBitmapBackgroundColour, "GetBitmapBackgroundColour")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_Wizard, __GetBitmapBackgroundColour)
{
	Object_wx_Wizard *pThis = Object_wx_Wizard::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxColour& _rtn = pThis->GetEntity()->GetBitmapBackgroundColour();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Wizard, __GetBitmapPlacement, "GetBitmapPlacement")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_Wizard, __GetBitmapPlacement)
{
	Object_wx_Wizard *pThis = Object_wx_Wizard::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int _rtn = pThis->GetEntity()->GetBitmapPlacement();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Wizard, __GetCurrentPage, "GetCurrentPage")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_Wizard, __GetCurrentPage)
{
	Object_wx_Wizard *pThis = Object_wx_Wizard::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxWizardPage* _rtn = pThis->GetEntity()->GetCurrentPage();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Wizard, __GetMinimumBitmapWidth, "GetMinimumBitmapWidth")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_Wizard, __GetMinimumBitmapWidth)
{
	Object_wx_Wizard *pThis = Object_wx_Wizard::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int _rtn = pThis->GetEntity()->GetMinimumBitmapWidth();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Wizard, __GetPageAreaSizer, "GetPageAreaSizer")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_Wizard, __GetPageAreaSizer)
{
	Object_wx_Wizard *pThis = Object_wx_Wizard::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxSizer* _rtn = pThis->GetEntity()->GetPageAreaSizer();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Wizard, __GetPageSize, "GetPageSize")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_Wizard, __GetPageSize)
{
	Object_wx_Wizard *pThis = Object_wx_Wizard::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxSize _rtn = pThis->GetEntity()->GetPageSize();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Wizard, __HasNextPage, "HasNextPage")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "page", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Wizard, __HasNextPage)
{
	Object_wx_Wizard *pThis = Object_wx_Wizard::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxWizardPage* page = arg.GetNumber(0)
	//bool _rtn = pThis->GetEntity()->HasNextPage(page);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Wizard, __HasPrevPage, "HasPrevPage")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "page", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Wizard, __HasPrevPage)
{
	Object_wx_Wizard *pThis = Object_wx_Wizard::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxWizardPage* page = arg.GetNumber(0)
	//bool _rtn = pThis->GetEntity()->HasPrevPage(page);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Wizard, __RunWizard, "RunWizard")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "firstPage", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Wizard, __RunWizard)
{
	Object_wx_Wizard *pThis = Object_wx_Wizard::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxWizardPage* firstPage = arg.GetNumber(0)
	//bool _rtn = pThis->GetEntity()->RunWizard(firstPage);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Wizard, __SetBitmap, "SetBitmap")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "bitmap", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Wizard, __SetBitmap)
{
	Object_wx_Wizard *pThis = Object_wx_Wizard::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxBitmap& bitmap = arg.GetNumber(0)
	//pThis->GetEntity()->SetBitmap(bitmap);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Wizard, __SetBitmapBackgroundColour, "SetBitmapBackgroundColour")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "colour", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Wizard, __SetBitmapBackgroundColour)
{
	Object_wx_Wizard *pThis = Object_wx_Wizard::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxColour& colour = arg.GetNumber(0)
	//pThis->GetEntity()->SetBitmapBackgroundColour(colour);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Wizard, __SetBitmapPlacement, "SetBitmapPlacement")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "placement", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Wizard, __SetBitmapPlacement)
{
	Object_wx_Wizard *pThis = Object_wx_Wizard::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int placement = arg.GetNumber(0)
	//pThis->GetEntity()->SetBitmapPlacement(placement);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Wizard, __SetBorder, "SetBorder")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "border", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Wizard, __SetBorder)
{
	Object_wx_Wizard *pThis = Object_wx_Wizard::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int border = arg.GetNumber(0)
	//pThis->GetEntity()->SetBorder(border);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Wizard, __SetMinimumBitmapWidth, "SetMinimumBitmapWidth")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "width", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Wizard, __SetMinimumBitmapWidth)
{
	Object_wx_Wizard *pThis = Object_wx_Wizard::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int width = arg.GetNumber(0)
	//pThis->GetEntity()->SetMinimumBitmapWidth(width);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Wizard, __SetPageSize, "SetPageSize")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "sizePage", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Wizard, __SetPageSize)
{
	Object_wx_Wizard *pThis = Object_wx_Wizard::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxSize& sizePage = arg.GetNumber(0)
	//pThis->GetEntity()->SetPageSize(sizePage);
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Class implementation for wxWizard
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_Wizard)
{
	// Constructor assignment
	Gura_AssignFunction(__Wizard);
	Gura_AssignFunction(__Wizard_1);
	// Method assignment
	Gura_AssignMethod(wx_Wizard, __Create);
	Gura_AssignMethod(wx_Wizard, __FitToPage);
	Gura_AssignMethod(wx_Wizard, __GetBitmap);
	Gura_AssignMethod(wx_Wizard, __GetBitmapBackgroundColour);
	Gura_AssignMethod(wx_Wizard, __GetBitmapPlacement);
	Gura_AssignMethod(wx_Wizard, __GetCurrentPage);
	Gura_AssignMethod(wx_Wizard, __GetMinimumBitmapWidth);
	Gura_AssignMethod(wx_Wizard, __GetPageAreaSizer);
	Gura_AssignMethod(wx_Wizard, __GetPageSize);
	Gura_AssignMethod(wx_Wizard, __HasNextPage);
	Gura_AssignMethod(wx_Wizard, __HasPrevPage);
	Gura_AssignMethod(wx_Wizard, __RunWizard);
	Gura_AssignMethod(wx_Wizard, __SetBitmap);
	Gura_AssignMethod(wx_Wizard, __SetBitmapBackgroundColour);
	Gura_AssignMethod(wx_Wizard, __SetBitmapPlacement);
	Gura_AssignMethod(wx_Wizard, __SetBorder);
	Gura_AssignMethod(wx_Wizard, __SetMinimumBitmapWidth);
	Gura_AssignMethod(wx_Wizard, __SetPageSize);
}

Gura_ImplementDescendantCreator(wx_Wizard)
{
	return new Object_wx_Wizard((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
