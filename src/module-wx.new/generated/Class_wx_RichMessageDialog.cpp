//----------------------------------------------------------------------------
// wxRichMessageDialog
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Gura interfaces for wxRichMessageDialog
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Object implementation for wxRichMessageDialog
//----------------------------------------------------------------------------
Object_wx_RichMessageDialog::~Object_wx_RichMessageDialog()
{
}

Object *Object_wx_RichMessageDialog::Clone() const
{
	return nullptr;
}

String Object_wx_RichMessageDialog::ToString(bool exprFlag)
{
	String rtn("<wx.RichMessageDialog:");
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
Gura_DeclareFunctionAlias(__RichMessageDialog, "RichMessageDialog")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "parent", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "message", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "caption", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "style", VTYPE_number, OCCUR_Once);
	SetClassToConstruct(Gura_UserClass(wx_RichMessageDialog));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(__RichMessageDialog)
{
	//wxWindow* parent = arg.GetNumber(0)
	//const wxString& message = arg.GetNumber(1)
	//const wxString& caption = arg.GetNumber(2)
	//long style = arg.GetNumber(3)
	//wxRichMessageDialog(parent, message, caption, style);
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Method implementation
//----------------------------------------------------------------------------
Gura_DeclareMethodAlias(wx_RichMessageDialog, __ShowCheckBox, "ShowCheckBox")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "checkBoxText", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "checked", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_RichMessageDialog, __ShowCheckBox)
{
	Object_wx_RichMessageDialog *pThis = Object_wx_RichMessageDialog::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxString& checkBoxText = arg.GetNumber(0)
	//bool checked = arg.GetNumber(1)
	//pThis->GetEntity()->ShowCheckBox(checkBoxText, checked);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RichMessageDialog, __GetCheckBoxText, "GetCheckBoxText")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_RichMessageDialog, __GetCheckBoxText)
{
	Object_wx_RichMessageDialog *pThis = Object_wx_RichMessageDialog::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxString _rtn = pThis->GetEntity()->GetCheckBoxText();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RichMessageDialog, __ShowDetailedText, "ShowDetailedText")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "detailedText", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_RichMessageDialog, __ShowDetailedText)
{
	Object_wx_RichMessageDialog *pThis = Object_wx_RichMessageDialog::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxString& detailedText = arg.GetNumber(0)
	//pThis->GetEntity()->ShowDetailedText(detailedText);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RichMessageDialog, __GetDetailedText, "GetDetailedText")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_RichMessageDialog, __GetDetailedText)
{
	Object_wx_RichMessageDialog *pThis = Object_wx_RichMessageDialog::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxString _rtn = pThis->GetEntity()->GetDetailedText();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RichMessageDialog, __IsCheckBoxChecked, "IsCheckBoxChecked")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_RichMessageDialog, __IsCheckBoxChecked)
{
	Object_wx_RichMessageDialog *pThis = Object_wx_RichMessageDialog::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//bool _rtn = pThis->GetEntity()->IsCheckBoxChecked();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RichMessageDialog, __ShowModal, "ShowModal")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_RichMessageDialog, __ShowModal)
{
	Object_wx_RichMessageDialog *pThis = Object_wx_RichMessageDialog::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int _rtn = pThis->GetEntity()->ShowModal();
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Class implementation for wxRichMessageDialog
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_RichMessageDialog)
{
	// Constructor assignment
	Gura_AssignFunction(__RichMessageDialog);
	// Method assignment
	Gura_AssignMethod(wx_RichMessageDialog, __ShowCheckBox);
	Gura_AssignMethod(wx_RichMessageDialog, __GetCheckBoxText);
	Gura_AssignMethod(wx_RichMessageDialog, __ShowDetailedText);
	Gura_AssignMethod(wx_RichMessageDialog, __GetDetailedText);
	Gura_AssignMethod(wx_RichMessageDialog, __IsCheckBoxChecked);
	Gura_AssignMethod(wx_RichMessageDialog, __ShowModal);
}

Gura_ImplementDescendantCreator(wx_RichMessageDialog)
{
	return new Object_wx_RichMessageDialog((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
