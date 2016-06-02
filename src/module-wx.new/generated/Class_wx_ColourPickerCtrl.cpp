//----------------------------------------------------------------------------
// wxColourPickerCtrl
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Gura interfaces for wxColourPickerCtrl
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Object implementation for wxColourPickerCtrl
//----------------------------------------------------------------------------
Object_wx_ColourPickerCtrl::~Object_wx_ColourPickerCtrl()
{
}

Object *Object_wx_ColourPickerCtrl::Clone() const
{
	return nullptr;
}

String Object_wx_ColourPickerCtrl::ToString(bool exprFlag)
{
	String rtn("<wx.ColourPickerCtrl:");
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
Gura_DeclareMethod(wx_ColourPickerCtrl, wxColourPickerCtrl)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_ColourPickerCtrl, wxColourPickerCtrl)
{
	Object_wx_ColourPickerCtrl *pThis = Object_wx_ColourPickerCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->wxColourPickerCtrl();
	return Value::Nil;
}

Gura_DeclareMethod(wx_ColourPickerCtrl, wxColourPickerCtrl_1)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "parent", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "id", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "colour", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "pos", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "size", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "style", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "validator", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "name", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_ColourPickerCtrl, wxColourPickerCtrl_1)
{
	Object_wx_ColourPickerCtrl *pThis = Object_wx_ColourPickerCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int parent = arg.GetNumber(0)
	//int id = arg.GetNumber(1)
	//int colour = arg.GetNumber(2)
	//int pos = arg.GetNumber(3)
	//int size = arg.GetNumber(4)
	//int style = arg.GetNumber(5)
	//int validator = arg.GetNumber(6)
	//int name = arg.GetNumber(7)
	//pThis->GetEntity()->wxColourPickerCtrl();
	return Value::Nil;
}

Gura_DeclareMethod(wx_ColourPickerCtrl, Create)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "parent", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "id", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "colour", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "pos", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "size", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "style", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "validator", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "name", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_ColourPickerCtrl, Create)
{
	Object_wx_ColourPickerCtrl *pThis = Object_wx_ColourPickerCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int parent = arg.GetNumber(0)
	//int id = arg.GetNumber(1)
	//int colour = arg.GetNumber(2)
	//int pos = arg.GetNumber(3)
	//int size = arg.GetNumber(4)
	//int style = arg.GetNumber(5)
	//int validator = arg.GetNumber(6)
	//int name = arg.GetNumber(7)
	//pThis->GetEntity()->Create();
	return Value::Nil;
}

Gura_DeclareMethod(wx_ColourPickerCtrl, GetColour)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_ColourPickerCtrl, GetColour)
{
	Object_wx_ColourPickerCtrl *pThis = Object_wx_ColourPickerCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->GetColour();
	return Value::Nil;
}

Gura_DeclareMethod(wx_ColourPickerCtrl, SetColour)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "col", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_ColourPickerCtrl, SetColour)
{
	Object_wx_ColourPickerCtrl *pThis = Object_wx_ColourPickerCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int col = arg.GetNumber(0)
	//pThis->GetEntity()->SetColour();
	return Value::Nil;
}

Gura_DeclareMethod(wx_ColourPickerCtrl, SetColour_1)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "colname", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_ColourPickerCtrl, SetColour_1)
{
	Object_wx_ColourPickerCtrl *pThis = Object_wx_ColourPickerCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int colname = arg.GetNumber(0)
	//pThis->GetEntity()->SetColour();
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Class implementation for wxColourPickerCtrl
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_ColourPickerCtrl)
{
	Gura_AssignMethod(wx_ColourPickerCtrl, wxColourPickerCtrl);
	Gura_AssignMethod(wx_ColourPickerCtrl, wxColourPickerCtrl_1);
	Gura_AssignMethod(wx_ColourPickerCtrl, Create);
	Gura_AssignMethod(wx_ColourPickerCtrl, GetColour);
	Gura_AssignMethod(wx_ColourPickerCtrl, SetColour);
	Gura_AssignMethod(wx_ColourPickerCtrl, SetColour_1);
}

Gura_ImplementDescendantCreator(wx_ColourPickerCtrl)
{
	return new Object_wx_ColourPickerCtrl((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
