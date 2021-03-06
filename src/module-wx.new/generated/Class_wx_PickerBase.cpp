//----------------------------------------------------------------------------
// wxPickerBase
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Gura interfaces for wxPickerBase
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Object implementation for wxPickerBase
//----------------------------------------------------------------------------
Object_wx_PickerBase::~Object_wx_PickerBase()
{
}

Object *Object_wx_PickerBase::Clone() const
{
	return nullptr;
}

String Object_wx_PickerBase::ToString(bool exprFlag)
{
	String rtn("<wx.PickerBase:");
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
Gura_DeclareFunctionAlias(__PickerBase, "PickerBase")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	SetClassToConstruct(Gura_UserClass(wx_PickerBase));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(__PickerBase)
{
	//wxPickerBase();
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Method implementation
//----------------------------------------------------------------------------
Gura_DeclareMethodAlias(wx_PickerBase, __CreateBase, "CreateBase")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "parent", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "id", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "text", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "pos", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "size", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "style", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "validator", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "name", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_PickerBase, __CreateBase)
{
	Object_wx_PickerBase *pThis = Object_wx_PickerBase::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxWindow* parent = arg.GetNumber(0)
	//wxWindowID id = arg.GetNumber(1)
	//const wxString& text = arg.GetNumber(2)
	//const wxPoint& pos = arg.GetNumber(3)
	//const wxSize& size = arg.GetNumber(4)
	//long style = arg.GetNumber(5)
	//const wxValidator& validator = arg.GetNumber(6)
	//const wxString& name = arg.GetNumber(7)
	//bool _rtn = pThis->GetEntity()->CreateBase(parent, id, text, pos, size, style, validator, name);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_PickerBase, __GetInternalMargin, "GetInternalMargin")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_PickerBase, __GetInternalMargin)
{
	Object_wx_PickerBase *pThis = Object_wx_PickerBase::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int _rtn = pThis->GetEntity()->GetInternalMargin();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_PickerBase, __GetPickerCtrlProportion, "GetPickerCtrlProportion")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_PickerBase, __GetPickerCtrlProportion)
{
	Object_wx_PickerBase *pThis = Object_wx_PickerBase::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int _rtn = pThis->GetEntity()->GetPickerCtrlProportion();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_PickerBase, __GetTextCtrl, "GetTextCtrl")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_PickerBase, __GetTextCtrl)
{
	Object_wx_PickerBase *pThis = Object_wx_PickerBase::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxTextCtrl* _rtn = pThis->GetEntity()->GetTextCtrl();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_PickerBase, __GetPickerCtrl, "GetPickerCtrl")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_PickerBase, __GetPickerCtrl)
{
	Object_wx_PickerBase *pThis = Object_wx_PickerBase::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxControl* _rtn = pThis->GetEntity()->GetPickerCtrl();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_PickerBase, __GetTextCtrlProportion, "GetTextCtrlProportion")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_PickerBase, __GetTextCtrlProportion)
{
	Object_wx_PickerBase *pThis = Object_wx_PickerBase::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int _rtn = pThis->GetEntity()->GetTextCtrlProportion();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_PickerBase, __HasTextCtrl, "HasTextCtrl")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_PickerBase, __HasTextCtrl)
{
	Object_wx_PickerBase *pThis = Object_wx_PickerBase::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//bool _rtn = pThis->GetEntity()->HasTextCtrl();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_PickerBase, __IsPickerCtrlGrowable, "IsPickerCtrlGrowable")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_PickerBase, __IsPickerCtrlGrowable)
{
	Object_wx_PickerBase *pThis = Object_wx_PickerBase::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//bool _rtn = pThis->GetEntity()->IsPickerCtrlGrowable();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_PickerBase, __IsTextCtrlGrowable, "IsTextCtrlGrowable")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_PickerBase, __IsTextCtrlGrowable)
{
	Object_wx_PickerBase *pThis = Object_wx_PickerBase::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//bool _rtn = pThis->GetEntity()->IsTextCtrlGrowable();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_PickerBase, __SetInternalMargin, "SetInternalMargin")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "margin", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_PickerBase, __SetInternalMargin)
{
	Object_wx_PickerBase *pThis = Object_wx_PickerBase::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int margin = arg.GetNumber(0)
	//pThis->GetEntity()->SetInternalMargin(margin);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_PickerBase, __SetPickerCtrlGrowable, "SetPickerCtrlGrowable")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "grow", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_PickerBase, __SetPickerCtrlGrowable)
{
	Object_wx_PickerBase *pThis = Object_wx_PickerBase::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//bool grow = arg.GetNumber(0)
	//pThis->GetEntity()->SetPickerCtrlGrowable(grow);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_PickerBase, __SetPickerCtrlProportion, "SetPickerCtrlProportion")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "prop", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_PickerBase, __SetPickerCtrlProportion)
{
	Object_wx_PickerBase *pThis = Object_wx_PickerBase::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int prop = arg.GetNumber(0)
	//pThis->GetEntity()->SetPickerCtrlProportion(prop);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_PickerBase, __SetTextCtrlGrowable, "SetTextCtrlGrowable")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "grow", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_PickerBase, __SetTextCtrlGrowable)
{
	Object_wx_PickerBase *pThis = Object_wx_PickerBase::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//bool grow = arg.GetNumber(0)
	//pThis->GetEntity()->SetTextCtrlGrowable(grow);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_PickerBase, __SetTextCtrlProportion, "SetTextCtrlProportion")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "prop", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_PickerBase, __SetTextCtrlProportion)
{
	Object_wx_PickerBase *pThis = Object_wx_PickerBase::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int prop = arg.GetNumber(0)
	//pThis->GetEntity()->SetTextCtrlProportion(prop);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_PickerBase, __SetTextCtrl, "SetTextCtrl")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "text", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_PickerBase, __SetTextCtrl)
{
	Object_wx_PickerBase *pThis = Object_wx_PickerBase::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxTextCtrl* text = arg.GetNumber(0)
	//pThis->GetEntity()->SetTextCtrl(text);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_PickerBase, __SetPickerCtrl, "SetPickerCtrl")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "picker", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_PickerBase, __SetPickerCtrl)
{
	Object_wx_PickerBase *pThis = Object_wx_PickerBase::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxControl* picker = arg.GetNumber(0)
	//pThis->GetEntity()->SetPickerCtrl(picker);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_PickerBase, __UpdatePickerFromTextCtrl, "UpdatePickerFromTextCtrl")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_PickerBase, __UpdatePickerFromTextCtrl)
{
	Object_wx_PickerBase *pThis = Object_wx_PickerBase::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->UpdatePickerFromTextCtrl();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_PickerBase, __UpdateTextCtrlFromPicker, "UpdateTextCtrlFromPicker")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_PickerBase, __UpdateTextCtrlFromPicker)
{
	Object_wx_PickerBase *pThis = Object_wx_PickerBase::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->UpdateTextCtrlFromPicker();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_PickerBase, __GetTextCtrlStyle, "GetTextCtrlStyle")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "style", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_PickerBase, __GetTextCtrlStyle)
{
	Object_wx_PickerBase *pThis = Object_wx_PickerBase::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//long style = arg.GetNumber(0)
	//long _rtn = pThis->GetEntity()->GetTextCtrlStyle(style);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_PickerBase, __GetPickerStyle, "GetPickerStyle")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "style", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_PickerBase, __GetPickerStyle)
{
	Object_wx_PickerBase *pThis = Object_wx_PickerBase::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//long style = arg.GetNumber(0)
	//long _rtn = pThis->GetEntity()->GetPickerStyle(style);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_PickerBase, __PostCreation, "PostCreation")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_PickerBase, __PostCreation)
{
	Object_wx_PickerBase *pThis = Object_wx_PickerBase::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->PostCreation();
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Class implementation for wxPickerBase
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_PickerBase)
{
	// Constructor assignment
	Gura_AssignFunction(__PickerBase);
	// Method assignment
	Gura_AssignMethod(wx_PickerBase, __CreateBase);
	Gura_AssignMethod(wx_PickerBase, __GetInternalMargin);
	Gura_AssignMethod(wx_PickerBase, __GetPickerCtrlProportion);
	Gura_AssignMethod(wx_PickerBase, __GetTextCtrl);
	Gura_AssignMethod(wx_PickerBase, __GetPickerCtrl);
	Gura_AssignMethod(wx_PickerBase, __GetTextCtrlProportion);
	Gura_AssignMethod(wx_PickerBase, __HasTextCtrl);
	Gura_AssignMethod(wx_PickerBase, __IsPickerCtrlGrowable);
	Gura_AssignMethod(wx_PickerBase, __IsTextCtrlGrowable);
	Gura_AssignMethod(wx_PickerBase, __SetInternalMargin);
	Gura_AssignMethod(wx_PickerBase, __SetPickerCtrlGrowable);
	Gura_AssignMethod(wx_PickerBase, __SetPickerCtrlProportion);
	Gura_AssignMethod(wx_PickerBase, __SetTextCtrlGrowable);
	Gura_AssignMethod(wx_PickerBase, __SetTextCtrlProportion);
	Gura_AssignMethod(wx_PickerBase, __SetTextCtrl);
	Gura_AssignMethod(wx_PickerBase, __SetPickerCtrl);
	Gura_AssignMethod(wx_PickerBase, __UpdatePickerFromTextCtrl);
	Gura_AssignMethod(wx_PickerBase, __UpdateTextCtrlFromPicker);
	Gura_AssignMethod(wx_PickerBase, __GetTextCtrlStyle);
	Gura_AssignMethod(wx_PickerBase, __GetPickerStyle);
	Gura_AssignMethod(wx_PickerBase, __PostCreation);
}

Gura_ImplementDescendantCreator(wx_PickerBase)
{
	return new Object_wx_PickerBase((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
