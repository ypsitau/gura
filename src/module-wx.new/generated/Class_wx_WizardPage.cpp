//----------------------------------------------------------------------------
// wxWizardPage
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Gura interfaces for wxWizardPage
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Object implementation for wxWizardPage
//----------------------------------------------------------------------------
Object_wx_WizardPage::~Object_wx_WizardPage()
{
}

Object *Object_wx_WizardPage::Clone() const
{
	return nullptr;
}

String Object_wx_WizardPage::ToString(bool exprFlag)
{
	String rtn("<wx.WizardPage:");
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
Gura_DeclareFunctionAlias(__WizardPage, "WizardPage")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	SetClassToConstruct(Gura_UserClass(wx_WizardPage));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(__WizardPage)
{
	//wxWizardPage();
	return Value::Nil;
}

Gura_DeclareFunctionAlias(__WizardPage_1, "WizardPage_1")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "parent", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "bitmap", VTYPE_number, OCCUR_Once);
	SetClassToConstruct(Gura_UserClass(wx_WizardPage));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(__WizardPage_1)
{
	//wxWizard* parent = arg.GetNumber(0)
	//const wxBitmap& bitmap = arg.GetNumber(1)
	//wxWizardPage(parent, bitmap);
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Method implementation
//----------------------------------------------------------------------------
Gura_DeclareMethodAlias(wx_WizardPage, __Create, "Create")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "parent", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "bitmap", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_WizardPage, __Create)
{
	Object_wx_WizardPage *pThis = Object_wx_WizardPage::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxWizard* parent = arg.GetNumber(0)
	//const wxBitmap& bitmap = arg.GetNumber(1)
	//bool _rtn = pThis->GetEntity()->Create(parent, bitmap);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_WizardPage, __GetBitmap, "GetBitmap")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_WizardPage, __GetBitmap)
{
	Object_wx_WizardPage *pThis = Object_wx_WizardPage::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxBitmap _rtn = pThis->GetEntity()->GetBitmap();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_WizardPage, __GetNext, "GetNext")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_WizardPage, __GetNext)
{
	Object_wx_WizardPage *pThis = Object_wx_WizardPage::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxWizardPage* _rtn = pThis->GetEntity()->GetNext();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_WizardPage, __GetPrev, "GetPrev")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_WizardPage, __GetPrev)
{
	Object_wx_WizardPage *pThis = Object_wx_WizardPage::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxWizardPage* _rtn = pThis->GetEntity()->GetPrev();
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Class implementation for wxWizardPage
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_WizardPage)
{
	// Constructor assignment
	Gura_AssignFunction(__WizardPage);
	Gura_AssignFunction(__WizardPage_1);
	// Method assignment
	Gura_AssignMethod(wx_WizardPage, __Create);
	Gura_AssignMethod(wx_WizardPage, __GetBitmap);
	Gura_AssignMethod(wx_WizardPage, __GetNext);
	Gura_AssignMethod(wx_WizardPage, __GetPrev);
}

Gura_ImplementDescendantCreator(wx_WizardPage)
{
	return new Object_wx_WizardPage((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
