//----------------------------------------------------------------------------
// wxRibbonButtonBar
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Gura interfaces for wxRibbonButtonBar
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Object implementation for wxRibbonButtonBar
//----------------------------------------------------------------------------
Object_wx_RibbonButtonBar::~Object_wx_RibbonButtonBar()
{
}

Object *Object_wx_RibbonButtonBar::Clone() const
{
	return nullptr;
}

String Object_wx_RibbonButtonBar::ToString(bool exprFlag)
{
	String rtn("<wx.RibbonButtonBar:");
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
Gura_DeclareMethodAlias(wx_RibbonButtonBar, __wxRibbonButtonBar, "wxRibbonButtonBar")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_RibbonButtonBar, __wxRibbonButtonBar)
{
	Object_wx_RibbonButtonBar *pThis = Object_wx_RibbonButtonBar::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->wxRibbonButtonBar();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RibbonButtonBar, __wxRibbonButtonBar_1, "wxRibbonButtonBar_1")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "parent", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "id", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "pos", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "size", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "style", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_RibbonButtonBar, __wxRibbonButtonBar_1)
{
	Object_wx_RibbonButtonBar *pThis = Object_wx_RibbonButtonBar::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int parent = arg.GetNumber(0)
	//int id = arg.GetNumber(1)
	//int pos = arg.GetNumber(2)
	//int size = arg.GetNumber(3)
	//int style = arg.GetNumber(4)
	//pThis->GetEntity()->wxRibbonButtonBar();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RibbonButtonBar, __Create, "Create")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "parent", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "id", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "pos", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "size", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "style", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_RibbonButtonBar, __Create)
{
	Object_wx_RibbonButtonBar *pThis = Object_wx_RibbonButtonBar::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int parent = arg.GetNumber(0)
	//int id = arg.GetNumber(1)
	//int pos = arg.GetNumber(2)
	//int size = arg.GetNumber(3)
	//int style = arg.GetNumber(4)
	//pThis->GetEntity()->Create();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RibbonButtonBar, __AddButton, "AddButton")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "button_id", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "label", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "bitmap", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "help_string", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "kind", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_RibbonButtonBar, __AddButton)
{
	Object_wx_RibbonButtonBar *pThis = Object_wx_RibbonButtonBar::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int button_id = arg.GetNumber(0)
	//int label = arg.GetNumber(1)
	//int bitmap = arg.GetNumber(2)
	//int help_string = arg.GetNumber(3)
	//int kind = arg.GetNumber(4)
	//pThis->GetEntity()->AddButton();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RibbonButtonBar, __AddDropdownButton, "AddDropdownButton")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "button_id", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "label", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "bitmap", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "help_string", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_RibbonButtonBar, __AddDropdownButton)
{
	Object_wx_RibbonButtonBar *pThis = Object_wx_RibbonButtonBar::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int button_id = arg.GetNumber(0)
	//int label = arg.GetNumber(1)
	//int bitmap = arg.GetNumber(2)
	//int help_string = arg.GetNumber(3)
	//pThis->GetEntity()->AddDropdownButton();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RibbonButtonBar, __AddHybridButton, "AddHybridButton")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "button_id", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "label", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "bitmap", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "help_string", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_RibbonButtonBar, __AddHybridButton)
{
	Object_wx_RibbonButtonBar *pThis = Object_wx_RibbonButtonBar::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int button_id = arg.GetNumber(0)
	//int label = arg.GetNumber(1)
	//int bitmap = arg.GetNumber(2)
	//int help_string = arg.GetNumber(3)
	//pThis->GetEntity()->AddHybridButton();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RibbonButtonBar, __AddToggleButton, "AddToggleButton")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "button_id", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "label", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "bitmap", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "help_string", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_RibbonButtonBar, __AddToggleButton)
{
	Object_wx_RibbonButtonBar *pThis = Object_wx_RibbonButtonBar::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int button_id = arg.GetNumber(0)
	//int label = arg.GetNumber(1)
	//int bitmap = arg.GetNumber(2)
	//int help_string = arg.GetNumber(3)
	//pThis->GetEntity()->AddToggleButton();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RibbonButtonBar, __AddButton_1, "AddButton_1")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "button_id", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "label", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "bitmap", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "bitmap_small", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "bitmap_disabled", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "bitmap_small_disabled", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "kind", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "help_string", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_RibbonButtonBar, __AddButton_1)
{
	Object_wx_RibbonButtonBar *pThis = Object_wx_RibbonButtonBar::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int button_id = arg.GetNumber(0)
	//int label = arg.GetNumber(1)
	//int bitmap = arg.GetNumber(2)
	//int bitmap_small = arg.GetNumber(3)
	//int bitmap_disabled = arg.GetNumber(4)
	//int bitmap_small_disabled = arg.GetNumber(5)
	//int kind = arg.GetNumber(6)
	//int help_string = arg.GetNumber(7)
	//pThis->GetEntity()->AddButton();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RibbonButtonBar, __InsertButton, "InsertButton")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "pos", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "button_id", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "label", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "bitmap", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "help_string", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "kind", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_RibbonButtonBar, __InsertButton)
{
	Object_wx_RibbonButtonBar *pThis = Object_wx_RibbonButtonBar::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int pos = arg.GetNumber(0)
	//int button_id = arg.GetNumber(1)
	//int label = arg.GetNumber(2)
	//int bitmap = arg.GetNumber(3)
	//int help_string = arg.GetNumber(4)
	//int kind = arg.GetNumber(5)
	//pThis->GetEntity()->InsertButton();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RibbonButtonBar, __InsertDropdownButton, "InsertDropdownButton")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "pos", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "button_id", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "label", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "bitmap", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "help_string", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_RibbonButtonBar, __InsertDropdownButton)
{
	Object_wx_RibbonButtonBar *pThis = Object_wx_RibbonButtonBar::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int pos = arg.GetNumber(0)
	//int button_id = arg.GetNumber(1)
	//int label = arg.GetNumber(2)
	//int bitmap = arg.GetNumber(3)
	//int help_string = arg.GetNumber(4)
	//pThis->GetEntity()->InsertDropdownButton();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RibbonButtonBar, __InsertHybridButton, "InsertHybridButton")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "pos", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "button_id", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "label", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "bitmap", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "help_string", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_RibbonButtonBar, __InsertHybridButton)
{
	Object_wx_RibbonButtonBar *pThis = Object_wx_RibbonButtonBar::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int pos = arg.GetNumber(0)
	//int button_id = arg.GetNumber(1)
	//int label = arg.GetNumber(2)
	//int bitmap = arg.GetNumber(3)
	//int help_string = arg.GetNumber(4)
	//pThis->GetEntity()->InsertHybridButton();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RibbonButtonBar, __InsertToggleButton, "InsertToggleButton")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "pos", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "button_id", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "label", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "bitmap", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "help_string", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_RibbonButtonBar, __InsertToggleButton)
{
	Object_wx_RibbonButtonBar *pThis = Object_wx_RibbonButtonBar::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int pos = arg.GetNumber(0)
	//int button_id = arg.GetNumber(1)
	//int label = arg.GetNumber(2)
	//int bitmap = arg.GetNumber(3)
	//int help_string = arg.GetNumber(4)
	//pThis->GetEntity()->InsertToggleButton();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RibbonButtonBar, __InsertButton_1, "InsertButton_1")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "pos", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "button_id", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "label", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "bitmap", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "bitmap_small", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "bitmap_disabled", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "bitmap_small_disabled", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "kind", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "help_string", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_RibbonButtonBar, __InsertButton_1)
{
	Object_wx_RibbonButtonBar *pThis = Object_wx_RibbonButtonBar::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int pos = arg.GetNumber(0)
	//int button_id = arg.GetNumber(1)
	//int label = arg.GetNumber(2)
	//int bitmap = arg.GetNumber(3)
	//int bitmap_small = arg.GetNumber(4)
	//int bitmap_disabled = arg.GetNumber(5)
	//int bitmap_small_disabled = arg.GetNumber(6)
	//int kind = arg.GetNumber(7)
	//int help_string = arg.GetNumber(8)
	//pThis->GetEntity()->InsertButton();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RibbonButtonBar, __GetButtonCount, "GetButtonCount")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_RibbonButtonBar, __GetButtonCount)
{
	Object_wx_RibbonButtonBar *pThis = Object_wx_RibbonButtonBar::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->GetButtonCount();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RibbonButtonBar, __SetItemClientObject, "SetItemClientObject")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "item", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "data", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_RibbonButtonBar, __SetItemClientObject)
{
	Object_wx_RibbonButtonBar *pThis = Object_wx_RibbonButtonBar::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int item = arg.GetNumber(0)
	//int data = arg.GetNumber(1)
	//pThis->GetEntity()->SetItemClientObject();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RibbonButtonBar, __GetItemClientObject, "GetItemClientObject")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "item", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_RibbonButtonBar, __GetItemClientObject)
{
	Object_wx_RibbonButtonBar *pThis = Object_wx_RibbonButtonBar::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int item = arg.GetNumber(0)
	//pThis->GetEntity()->GetItemClientObject();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RibbonButtonBar, __SetItemClientData, "SetItemClientData")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "item", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "data", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_RibbonButtonBar, __SetItemClientData)
{
	Object_wx_RibbonButtonBar *pThis = Object_wx_RibbonButtonBar::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int item = arg.GetNumber(0)
	//int data = arg.GetNumber(1)
	//pThis->GetEntity()->SetItemClientData();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RibbonButtonBar, __GetItemClientData, "GetItemClientData")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "item", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_RibbonButtonBar, __GetItemClientData)
{
	Object_wx_RibbonButtonBar *pThis = Object_wx_RibbonButtonBar::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int item = arg.GetNumber(0)
	//pThis->GetEntity()->GetItemClientData();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RibbonButtonBar, __GetItem, "GetItem")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "n", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_RibbonButtonBar, __GetItem)
{
	Object_wx_RibbonButtonBar *pThis = Object_wx_RibbonButtonBar::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int n = arg.GetNumber(0)
	//pThis->GetEntity()->GetItem();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RibbonButtonBar, __GetItemById, "GetItemById")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "id", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_RibbonButtonBar, __GetItemById)
{
	Object_wx_RibbonButtonBar *pThis = Object_wx_RibbonButtonBar::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int id = arg.GetNumber(0)
	//pThis->GetEntity()->GetItemById();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RibbonButtonBar, __GetItemId, "GetItemId")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_RibbonButtonBar, __GetItemId)
{
	Object_wx_RibbonButtonBar *pThis = Object_wx_RibbonButtonBar::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->GetItemId();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RibbonButtonBar, __Realize, "Realize")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_RibbonButtonBar, __Realize)
{
	Object_wx_RibbonButtonBar *pThis = Object_wx_RibbonButtonBar::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->Realize();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RibbonButtonBar, __ClearButtons, "ClearButtons")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_RibbonButtonBar, __ClearButtons)
{
	Object_wx_RibbonButtonBar *pThis = Object_wx_RibbonButtonBar::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->ClearButtons();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RibbonButtonBar, __DeleteButton, "DeleteButton")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "button_id", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_RibbonButtonBar, __DeleteButton)
{
	Object_wx_RibbonButtonBar *pThis = Object_wx_RibbonButtonBar::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int button_id = arg.GetNumber(0)
	//pThis->GetEntity()->DeleteButton();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RibbonButtonBar, __EnableButton, "EnableButton")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "button_id", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "enable", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_RibbonButtonBar, __EnableButton)
{
	Object_wx_RibbonButtonBar *pThis = Object_wx_RibbonButtonBar::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int button_id = arg.GetNumber(0)
	//int enable = arg.GetNumber(1)
	//pThis->GetEntity()->EnableButton();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RibbonButtonBar, __ToggleButton, "ToggleButton")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "button_id", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "checked", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_RibbonButtonBar, __ToggleButton)
{
	Object_wx_RibbonButtonBar *pThis = Object_wx_RibbonButtonBar::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int button_id = arg.GetNumber(0)
	//int checked = arg.GetNumber(1)
	//pThis->GetEntity()->ToggleButton();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RibbonButtonBar, __GetActiveItem, "GetActiveItem")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_RibbonButtonBar, __GetActiveItem)
{
	Object_wx_RibbonButtonBar *pThis = Object_wx_RibbonButtonBar::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->GetActiveItem();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RibbonButtonBar, __GetHoveredItem, "GetHoveredItem")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_RibbonButtonBar, __GetHoveredItem)
{
	Object_wx_RibbonButtonBar *pThis = Object_wx_RibbonButtonBar::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->GetHoveredItem();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RibbonButtonBar, __SetShowToolTipsForDisabled, "SetShowToolTipsForDisabled")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "show", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_RibbonButtonBar, __SetShowToolTipsForDisabled)
{
	Object_wx_RibbonButtonBar *pThis = Object_wx_RibbonButtonBar::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int show = arg.GetNumber(0)
	//pThis->GetEntity()->SetShowToolTipsForDisabled();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RibbonButtonBar, __GetShowToolTipsForDisabled, "GetShowToolTipsForDisabled")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_RibbonButtonBar, __GetShowToolTipsForDisabled)
{
	Object_wx_RibbonButtonBar *pThis = Object_wx_RibbonButtonBar::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->GetShowToolTipsForDisabled();
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Class implementation for wxRibbonButtonBar
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_RibbonButtonBar)
{
	Gura_AssignMethod(wx_RibbonButtonBar, __wxRibbonButtonBar);
	Gura_AssignMethod(wx_RibbonButtonBar, __wxRibbonButtonBar_1);
	Gura_AssignMethod(wx_RibbonButtonBar, __Create);
	Gura_AssignMethod(wx_RibbonButtonBar, __AddButton);
	Gura_AssignMethod(wx_RibbonButtonBar, __AddDropdownButton);
	Gura_AssignMethod(wx_RibbonButtonBar, __AddHybridButton);
	Gura_AssignMethod(wx_RibbonButtonBar, __AddToggleButton);
	Gura_AssignMethod(wx_RibbonButtonBar, __AddButton_1);
	Gura_AssignMethod(wx_RibbonButtonBar, __InsertButton);
	Gura_AssignMethod(wx_RibbonButtonBar, __InsertDropdownButton);
	Gura_AssignMethod(wx_RibbonButtonBar, __InsertHybridButton);
	Gura_AssignMethod(wx_RibbonButtonBar, __InsertToggleButton);
	Gura_AssignMethod(wx_RibbonButtonBar, __InsertButton_1);
	Gura_AssignMethod(wx_RibbonButtonBar, __GetButtonCount);
	Gura_AssignMethod(wx_RibbonButtonBar, __SetItemClientObject);
	Gura_AssignMethod(wx_RibbonButtonBar, __GetItemClientObject);
	Gura_AssignMethod(wx_RibbonButtonBar, __SetItemClientData);
	Gura_AssignMethod(wx_RibbonButtonBar, __GetItemClientData);
	Gura_AssignMethod(wx_RibbonButtonBar, __GetItem);
	Gura_AssignMethod(wx_RibbonButtonBar, __GetItemById);
	Gura_AssignMethod(wx_RibbonButtonBar, __GetItemId);
	Gura_AssignMethod(wx_RibbonButtonBar, __Realize);
	Gura_AssignMethod(wx_RibbonButtonBar, __ClearButtons);
	Gura_AssignMethod(wx_RibbonButtonBar, __DeleteButton);
	Gura_AssignMethod(wx_RibbonButtonBar, __EnableButton);
	Gura_AssignMethod(wx_RibbonButtonBar, __ToggleButton);
	Gura_AssignMethod(wx_RibbonButtonBar, __GetActiveItem);
	Gura_AssignMethod(wx_RibbonButtonBar, __GetHoveredItem);
	Gura_AssignMethod(wx_RibbonButtonBar, __SetShowToolTipsForDisabled);
	Gura_AssignMethod(wx_RibbonButtonBar, __GetShowToolTipsForDisabled);
}

Gura_ImplementDescendantCreator(wx_RibbonButtonBar)
{
	return new Object_wx_RibbonButtonBar((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
