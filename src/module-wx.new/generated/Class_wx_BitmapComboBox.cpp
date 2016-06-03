//----------------------------------------------------------------------------
// wxBitmapComboBox
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Gura interfaces for wxBitmapComboBox
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Object implementation for wxBitmapComboBox
//----------------------------------------------------------------------------
Object_wx_BitmapComboBox::~Object_wx_BitmapComboBox()
{
}

Object *Object_wx_BitmapComboBox::Clone() const
{
	return nullptr;
}

String Object_wx_BitmapComboBox::ToString(bool exprFlag)
{
	String rtn("<wx.BitmapComboBox:");
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
Gura_DeclareFunctionAlias(__BitmapComboBox, "BitmapComboBox")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	SetClassToConstruct(Gura_UserClass(wx_BitmapComboBox));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(__BitmapComboBox)
{
	//wxBitmapComboBox();
	return Value::Nil;
}

Gura_DeclareFunctionAlias(__BitmapComboBox_1, "BitmapComboBox_1")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "parent", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "id", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "value", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "pos", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "size", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "n", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "choices", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "style", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "validator", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "name", VTYPE_number, OCCUR_Once);
	SetClassToConstruct(Gura_UserClass(wx_BitmapComboBox));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(__BitmapComboBox_1)
{
	//int parent = arg.GetNumber(0)
	//int id = arg.GetNumber(1)
	//int value = arg.GetNumber(2)
	//int pos = arg.GetNumber(3)
	//int size = arg.GetNumber(4)
	//int n = arg.GetNumber(5)
	//int choices = arg.GetNumber(6)
	//int style = arg.GetNumber(7)
	//int validator = arg.GetNumber(8)
	//int name = arg.GetNumber(9)
	//wxBitmapComboBox();
	return Value::Nil;
}

Gura_DeclareFunctionAlias(__BitmapComboBox_2, "BitmapComboBox_2")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "parent", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "id", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "value", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "pos", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "size", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "choices", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "style", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "validator", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "name", VTYPE_number, OCCUR_Once);
	SetClassToConstruct(Gura_UserClass(wx_BitmapComboBox));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(__BitmapComboBox_2)
{
	//int parent = arg.GetNumber(0)
	//int id = arg.GetNumber(1)
	//int value = arg.GetNumber(2)
	//int pos = arg.GetNumber(3)
	//int size = arg.GetNumber(4)
	//int choices = arg.GetNumber(5)
	//int style = arg.GetNumber(6)
	//int validator = arg.GetNumber(7)
	//int name = arg.GetNumber(8)
	//wxBitmapComboBox();
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Method implementation
//----------------------------------------------------------------------------
Gura_DeclareMethodAlias(wx_BitmapComboBox, __Append, "Append")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "item", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "bitmap", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_BitmapComboBox, __Append)
{
	Object_wx_BitmapComboBox *pThis = Object_wx_BitmapComboBox::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int item = arg.GetNumber(0)
	//int bitmap = arg.GetNumber(1)
	//pThis->GetEntity()->Append();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_BitmapComboBox, __Append_1, "Append_1")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "item", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "bitmap", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "clientData", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_BitmapComboBox, __Append_1)
{
	Object_wx_BitmapComboBox *pThis = Object_wx_BitmapComboBox::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int item = arg.GetNumber(0)
	//int bitmap = arg.GetNumber(1)
	//int clientData = arg.GetNumber(2)
	//pThis->GetEntity()->Append();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_BitmapComboBox, __Append_2, "Append_2")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "item", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "bitmap", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "clientData", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_BitmapComboBox, __Append_2)
{
	Object_wx_BitmapComboBox *pThis = Object_wx_BitmapComboBox::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int item = arg.GetNumber(0)
	//int bitmap = arg.GetNumber(1)
	//int clientData = arg.GetNumber(2)
	//pThis->GetEntity()->Append();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_BitmapComboBox, __Create, "Create")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "parent", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "id", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "value", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "pos", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "size", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "n", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "choices", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "style", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "validator", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "name", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_BitmapComboBox, __Create)
{
	Object_wx_BitmapComboBox *pThis = Object_wx_BitmapComboBox::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int parent = arg.GetNumber(0)
	//int id = arg.GetNumber(1)
	//int value = arg.GetNumber(2)
	//int pos = arg.GetNumber(3)
	//int size = arg.GetNumber(4)
	//int n = arg.GetNumber(5)
	//int choices = arg.GetNumber(6)
	//int style = arg.GetNumber(7)
	//int validator = arg.GetNumber(8)
	//int name = arg.GetNumber(9)
	//pThis->GetEntity()->Create();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_BitmapComboBox, __Create_1, "Create_1")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
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

Gura_ImplementMethod(wx_BitmapComboBox, __Create_1)
{
	Object_wx_BitmapComboBox *pThis = Object_wx_BitmapComboBox::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int parent = arg.GetNumber(0)
	//int id = arg.GetNumber(1)
	//int value = arg.GetNumber(2)
	//int pos = arg.GetNumber(3)
	//int size = arg.GetNumber(4)
	//int choices = arg.GetNumber(5)
	//int style = arg.GetNumber(6)
	//int validator = arg.GetNumber(7)
	//int name = arg.GetNumber(8)
	//pThis->GetEntity()->Create();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_BitmapComboBox, __GetBitmapSize, "GetBitmapSize")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_BitmapComboBox, __GetBitmapSize)
{
	Object_wx_BitmapComboBox *pThis = Object_wx_BitmapComboBox::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->GetBitmapSize();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_BitmapComboBox, __GetItemBitmap, "GetItemBitmap")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "n", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_BitmapComboBox, __GetItemBitmap)
{
	Object_wx_BitmapComboBox *pThis = Object_wx_BitmapComboBox::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int n = arg.GetNumber(0)
	//pThis->GetEntity()->GetItemBitmap();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_BitmapComboBox, __Insert, "Insert")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "item", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "bitmap", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "pos", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_BitmapComboBox, __Insert)
{
	Object_wx_BitmapComboBox *pThis = Object_wx_BitmapComboBox::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int item = arg.GetNumber(0)
	//int bitmap = arg.GetNumber(1)
	//int pos = arg.GetNumber(2)
	//pThis->GetEntity()->Insert();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_BitmapComboBox, __Insert_1, "Insert_1")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "item", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "bitmap", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "pos", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "clientData", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_BitmapComboBox, __Insert_1)
{
	Object_wx_BitmapComboBox *pThis = Object_wx_BitmapComboBox::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int item = arg.GetNumber(0)
	//int bitmap = arg.GetNumber(1)
	//int pos = arg.GetNumber(2)
	//int clientData = arg.GetNumber(3)
	//pThis->GetEntity()->Insert();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_BitmapComboBox, __Insert_2, "Insert_2")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "item", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "bitmap", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "pos", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "clientData", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_BitmapComboBox, __Insert_2)
{
	Object_wx_BitmapComboBox *pThis = Object_wx_BitmapComboBox::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int item = arg.GetNumber(0)
	//int bitmap = arg.GetNumber(1)
	//int pos = arg.GetNumber(2)
	//int clientData = arg.GetNumber(3)
	//pThis->GetEntity()->Insert();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_BitmapComboBox, __SetItemBitmap, "SetItemBitmap")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "n", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "bitmap", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_BitmapComboBox, __SetItemBitmap)
{
	Object_wx_BitmapComboBox *pThis = Object_wx_BitmapComboBox::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int n = arg.GetNumber(0)
	//int bitmap = arg.GetNumber(1)
	//pThis->GetEntity()->SetItemBitmap();
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Class implementation for wxBitmapComboBox
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_BitmapComboBox)
{
	// Constructor assignment
	Gura_AssignFunction(__BitmapComboBox);
	Gura_AssignFunction(__BitmapComboBox_1);
	Gura_AssignFunction(__BitmapComboBox_2);
	// Method assignment
	Gura_AssignMethod(wx_BitmapComboBox, __Append);
	Gura_AssignMethod(wx_BitmapComboBox, __Append_1);
	Gura_AssignMethod(wx_BitmapComboBox, __Append_2);
	Gura_AssignMethod(wx_BitmapComboBox, __Create);
	Gura_AssignMethod(wx_BitmapComboBox, __Create_1);
	Gura_AssignMethod(wx_BitmapComboBox, __GetBitmapSize);
	Gura_AssignMethod(wx_BitmapComboBox, __GetItemBitmap);
	Gura_AssignMethod(wx_BitmapComboBox, __Insert);
	Gura_AssignMethod(wx_BitmapComboBox, __Insert_1);
	Gura_AssignMethod(wx_BitmapComboBox, __Insert_2);
	Gura_AssignMethod(wx_BitmapComboBox, __SetItemBitmap);
}

Gura_ImplementDescendantCreator(wx_BitmapComboBox)
{
	return new Object_wx_BitmapComboBox((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
