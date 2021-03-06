//----------------------------------------------------------------------------
// wxComboBox
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Gura interfaces for wxComboBox
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Object implementation for wxComboBox
//----------------------------------------------------------------------------
Object_wx_ComboBox::~Object_wx_ComboBox()
{
}

Object *Object_wx_ComboBox::Clone() const
{
	return nullptr;
}

String Object_wx_ComboBox::ToString(bool exprFlag)
{
	String rtn("<wx.ComboBox:");
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
Gura_DeclareFunctionAlias(__ComboBox, "ComboBox")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	SetClassToConstruct(Gura_UserClass(wx_ComboBox));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(__ComboBox)
{
	//wxComboBox();
	return Value::Nil;
}

Gura_DeclareFunctionAlias(__ComboBox_1, "ComboBox_1")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "parent", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "id", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "value", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "pos", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "size", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "n", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "_arg6", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "style", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "validator", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "name", VTYPE_number, OCCUR_Once);
	SetClassToConstruct(Gura_UserClass(wx_ComboBox));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(__ComboBox_1)
{
	//wxWindow* parent = arg.GetNumber(0)
	//wxWindowID id = arg.GetNumber(1)
	//const wxString& value = arg.GetNumber(2)
	//const wxPoint& pos = arg.GetNumber(3)
	//const wxSize& size = arg.GetNumber(4)
	//int n = arg.GetNumber(5)
	//const wxString choices[] _arg6 = arg.GetNumber(6)
	//long style = arg.GetNumber(7)
	//const wxValidator& validator = arg.GetNumber(8)
	//const wxString& name = arg.GetNumber(9)
	//wxComboBox(parent, id, value, pos, size, n, _arg6, style, validator, name);
	return Value::Nil;
}

Gura_DeclareFunctionAlias(__ComboBox_2, "ComboBox_2")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "parent", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "id", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "value", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "pos", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "size", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "choices", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "style", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "validator", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "name", VTYPE_number, OCCUR_Once);
	SetClassToConstruct(Gura_UserClass(wx_ComboBox));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(__ComboBox_2)
{
	//wxWindow* parent = arg.GetNumber(0)
	//wxWindowID id = arg.GetNumber(1)
	//const wxString& value = arg.GetNumber(2)
	//const wxPoint& pos = arg.GetNumber(3)
	//const wxSize& size = arg.GetNumber(4)
	//const wxArrayString& choices = arg.GetNumber(5)
	//long style = arg.GetNumber(6)
	//const wxValidator& validator = arg.GetNumber(7)
	//const wxString& name = arg.GetNumber(8)
	//wxComboBox(parent, id, value, pos, size, choices, style, validator, name);
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Method implementation
//----------------------------------------------------------------------------
Gura_DeclareMethodAlias(wx_ComboBox, __Create, "Create")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "parent", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "id", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "value", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "pos", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "size", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "n", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "_arg6", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "style", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "validator", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "name", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_ComboBox, __Create)
{
	Object_wx_ComboBox *pThis = Object_wx_ComboBox::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxWindow* parent = arg.GetNumber(0)
	//wxWindowID id = arg.GetNumber(1)
	//const wxString& value = arg.GetNumber(2)
	//const wxPoint& pos = arg.GetNumber(3)
	//const wxSize& size = arg.GetNumber(4)
	//int n = arg.GetNumber(5)
	//const wxString choices[] _arg6 = arg.GetNumber(6)
	//long style = arg.GetNumber(7)
	//const wxValidator& validator = arg.GetNumber(8)
	//const wxString& name = arg.GetNumber(9)
	//bool _rtn = pThis->GetEntity()->Create(parent, id, value, pos, size, n, _arg6, style, validator, name);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_ComboBox, __Create_1, "Create_1")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "parent", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "id", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "value", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "pos", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "size", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "choices", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "style", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "validator", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "name", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_ComboBox, __Create_1)
{
	Object_wx_ComboBox *pThis = Object_wx_ComboBox::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxWindow* parent = arg.GetNumber(0)
	//wxWindowID id = arg.GetNumber(1)
	//const wxString& value = arg.GetNumber(2)
	//const wxPoint& pos = arg.GetNumber(3)
	//const wxSize& size = arg.GetNumber(4)
	//const wxArrayString& choices = arg.GetNumber(5)
	//long style = arg.GetNumber(6)
	//const wxValidator& validator = arg.GetNumber(7)
	//const wxString& name = arg.GetNumber(8)
	//bool _rtn = pThis->GetEntity()->Create(parent, id, value, pos, size, choices, style, validator, name);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_ComboBox, __GetCurrentSelection, "GetCurrentSelection")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_ComboBox, __GetCurrentSelection)
{
	Object_wx_ComboBox *pThis = Object_wx_ComboBox::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int _rtn = pThis->GetEntity()->GetCurrentSelection();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_ComboBox, __GetInsertionPoint, "GetInsertionPoint")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_ComboBox, __GetInsertionPoint)
{
	Object_wx_ComboBox *pThis = Object_wx_ComboBox::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//long _rtn = pThis->GetEntity()->GetInsertionPoint();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_ComboBox, __IsEmpty, "IsEmpty")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_ComboBox, __IsEmpty)
{
	Object_wx_ComboBox *pThis = Object_wx_ComboBox::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//bool _rtn = pThis->GetEntity()->IsEmpty();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_ComboBox, __IsListEmpty, "IsListEmpty")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_ComboBox, __IsListEmpty)
{
	Object_wx_ComboBox *pThis = Object_wx_ComboBox::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//bool _rtn = pThis->GetEntity()->IsListEmpty();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_ComboBox, __IsTextEmpty, "IsTextEmpty")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_ComboBox, __IsTextEmpty)
{
	Object_wx_ComboBox *pThis = Object_wx_ComboBox::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//bool _rtn = pThis->GetEntity()->IsTextEmpty();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_ComboBox, __SetSelection, "SetSelection")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "from", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "to", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_ComboBox, __SetSelection)
{
	Object_wx_ComboBox *pThis = Object_wx_ComboBox::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//long from = arg.GetNumber(0)
	//long to = arg.GetNumber(1)
	//pThis->GetEntity()->SetSelection(from, to);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_ComboBox, __SetValue, "SetValue")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "text", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_ComboBox, __SetValue)
{
	Object_wx_ComboBox *pThis = Object_wx_ComboBox::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxString& text = arg.GetNumber(0)
	//pThis->GetEntity()->SetValue(text);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_ComboBox, __Popup, "Popup")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_ComboBox, __Popup)
{
	Object_wx_ComboBox *pThis = Object_wx_ComboBox::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->Popup();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_ComboBox, __Dismiss, "Dismiss")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_ComboBox, __Dismiss)
{
	Object_wx_ComboBox *pThis = Object_wx_ComboBox::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->Dismiss();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_ComboBox, __GetSelection, "GetSelection")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_ComboBox, __GetSelection)
{
	Object_wx_ComboBox *pThis = Object_wx_ComboBox::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int _rtn = pThis->GetEntity()->GetSelection();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_ComboBox, __GetSelection_1, "GetSelection_1")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "from", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "to", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_ComboBox, __GetSelection_1)
{
	Object_wx_ComboBox *pThis = Object_wx_ComboBox::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//long* from = arg.GetNumber(0)
	//long* to = arg.GetNumber(1)
	//pThis->GetEntity()->GetSelection(from, to);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_ComboBox, __SetSelection_1, "SetSelection_1")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "n", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_ComboBox, __SetSelection_1)
{
	Object_wx_ComboBox *pThis = Object_wx_ComboBox::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int n = arg.GetNumber(0)
	//pThis->GetEntity()->SetSelection(n);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_ComboBox, __FindString, "FindString")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "s", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "bCase", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_ComboBox, __FindString)
{
	Object_wx_ComboBox *pThis = Object_wx_ComboBox::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxString& s = arg.GetNumber(0)
	//bool bCase = arg.GetNumber(1)
	//int _rtn = pThis->GetEntity()->FindString(s, bCase);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_ComboBox, __GetString, "GetString")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "n", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_ComboBox, __GetString)
{
	Object_wx_ComboBox *pThis = Object_wx_ComboBox::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//unsigned int n = arg.GetNumber(0)
	//wxString _rtn = pThis->GetEntity()->GetString(n);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_ComboBox, __GetStringSelection, "GetStringSelection")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_ComboBox, __GetStringSelection)
{
	Object_wx_ComboBox *pThis = Object_wx_ComboBox::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxString _rtn = pThis->GetEntity()->GetStringSelection();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_ComboBox, __SetString, "SetString")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "n", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "text", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_ComboBox, __SetString)
{
	Object_wx_ComboBox *pThis = Object_wx_ComboBox::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//unsigned int n = arg.GetNumber(0)
	//const wxString& text = arg.GetNumber(1)
	//pThis->GetEntity()->SetString(n, text);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_ComboBox, __GetCount, "GetCount")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_ComboBox, __GetCount)
{
	Object_wx_ComboBox *pThis = Object_wx_ComboBox::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//unsigned int _rtn = pThis->GetEntity()->GetCount();
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Class implementation for wxComboBox
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_ComboBox)
{
	// Constructor assignment
	Gura_AssignFunction(__ComboBox);
	Gura_AssignFunction(__ComboBox_1);
	Gura_AssignFunction(__ComboBox_2);
	// Method assignment
	Gura_AssignMethod(wx_ComboBox, __Create);
	Gura_AssignMethod(wx_ComboBox, __Create_1);
	Gura_AssignMethod(wx_ComboBox, __GetCurrentSelection);
	Gura_AssignMethod(wx_ComboBox, __GetInsertionPoint);
	Gura_AssignMethod(wx_ComboBox, __IsEmpty);
	Gura_AssignMethod(wx_ComboBox, __IsListEmpty);
	Gura_AssignMethod(wx_ComboBox, __IsTextEmpty);
	Gura_AssignMethod(wx_ComboBox, __SetSelection);
	Gura_AssignMethod(wx_ComboBox, __SetValue);
	Gura_AssignMethod(wx_ComboBox, __Popup);
	Gura_AssignMethod(wx_ComboBox, __Dismiss);
	Gura_AssignMethod(wx_ComboBox, __GetSelection);
	Gura_AssignMethod(wx_ComboBox, __GetSelection_1);
	Gura_AssignMethod(wx_ComboBox, __SetSelection_1);
	Gura_AssignMethod(wx_ComboBox, __FindString);
	Gura_AssignMethod(wx_ComboBox, __GetString);
	Gura_AssignMethod(wx_ComboBox, __GetStringSelection);
	Gura_AssignMethod(wx_ComboBox, __SetString);
	Gura_AssignMethod(wx_ComboBox, __GetCount);
}

Gura_ImplementDescendantCreator(wx_ComboBox)
{
	return new Object_wx_ComboBox((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
