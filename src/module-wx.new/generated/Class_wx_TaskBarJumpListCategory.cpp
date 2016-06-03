//----------------------------------------------------------------------------
// wxTaskBarJumpListCategory
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Gura interfaces for wxTaskBarJumpListCategory
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Object implementation for wxTaskBarJumpListCategory
//----------------------------------------------------------------------------
Object_wx_TaskBarJumpListCategory::~Object_wx_TaskBarJumpListCategory()
{
}

Object *Object_wx_TaskBarJumpListCategory::Clone() const
{
	return nullptr;
}

String Object_wx_TaskBarJumpListCategory::ToString(bool exprFlag)
{
	String rtn("<wx.TaskBarJumpListCategory:");
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
Gura_DeclareMethodAlias(wx_TaskBarJumpListCategory, __wxTaskBarJumpListCategory, "wxTaskBarJumpListCategory")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "parent", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "title", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_TaskBarJumpListCategory, __wxTaskBarJumpListCategory)
{
	Object_wx_TaskBarJumpListCategory *pThis = Object_wx_TaskBarJumpListCategory::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int parent = arg.GetNumber(0)
	//int title = arg.GetNumber(1)
	//pThis->GetEntity()->wxTaskBarJumpListCategory();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_TaskBarJumpListCategory, __Append, "Append")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "item", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_TaskBarJumpListCategory, __Append)
{
	Object_wx_TaskBarJumpListCategory *pThis = Object_wx_TaskBarJumpListCategory::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int item = arg.GetNumber(0)
	//pThis->GetEntity()->Append();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_TaskBarJumpListCategory, __Delete, "Delete")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "item", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_TaskBarJumpListCategory, __Delete)
{
	Object_wx_TaskBarJumpListCategory *pThis = Object_wx_TaskBarJumpListCategory::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int item = arg.GetNumber(0)
	//pThis->GetEntity()->Delete();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_TaskBarJumpListCategory, __Remove, "Remove")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "item", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_TaskBarJumpListCategory, __Remove)
{
	Object_wx_TaskBarJumpListCategory *pThis = Object_wx_TaskBarJumpListCategory::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int item = arg.GetNumber(0)
	//pThis->GetEntity()->Remove();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_TaskBarJumpListCategory, __FindItemByPosition, "FindItemByPosition")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "pos", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_TaskBarJumpListCategory, __FindItemByPosition)
{
	Object_wx_TaskBarJumpListCategory *pThis = Object_wx_TaskBarJumpListCategory::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int pos = arg.GetNumber(0)
	//pThis->GetEntity()->FindItemByPosition();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_TaskBarJumpListCategory, __Insert, "Insert")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "pos", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "item", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_TaskBarJumpListCategory, __Insert)
{
	Object_wx_TaskBarJumpListCategory *pThis = Object_wx_TaskBarJumpListCategory::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int pos = arg.GetNumber(0)
	//int item = arg.GetNumber(1)
	//pThis->GetEntity()->Insert();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_TaskBarJumpListCategory, __Prepend, "Prepend")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "item", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_TaskBarJumpListCategory, __Prepend)
{
	Object_wx_TaskBarJumpListCategory *pThis = Object_wx_TaskBarJumpListCategory::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int item = arg.GetNumber(0)
	//pThis->GetEntity()->Prepend();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_TaskBarJumpListCategory, __SetTitle, "SetTitle")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "title", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_TaskBarJumpListCategory, __SetTitle)
{
	Object_wx_TaskBarJumpListCategory *pThis = Object_wx_TaskBarJumpListCategory::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int title = arg.GetNumber(0)
	//pThis->GetEntity()->SetTitle();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_TaskBarJumpListCategory, __GetTitle, "GetTitle")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_TaskBarJumpListCategory, __GetTitle)
{
	Object_wx_TaskBarJumpListCategory *pThis = Object_wx_TaskBarJumpListCategory::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->GetTitle();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_TaskBarJumpListCategory, __GetItems, "GetItems")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_TaskBarJumpListCategory, __GetItems)
{
	Object_wx_TaskBarJumpListCategory *pThis = Object_wx_TaskBarJumpListCategory::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->GetItems();
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Class implementation for wxTaskBarJumpListCategory
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_TaskBarJumpListCategory)
{
	Gura_AssignMethod(wx_TaskBarJumpListCategory, __wxTaskBarJumpListCategory);
	Gura_AssignMethod(wx_TaskBarJumpListCategory, __Append);
	Gura_AssignMethod(wx_TaskBarJumpListCategory, __Delete);
	Gura_AssignMethod(wx_TaskBarJumpListCategory, __Remove);
	Gura_AssignMethod(wx_TaskBarJumpListCategory, __FindItemByPosition);
	Gura_AssignMethod(wx_TaskBarJumpListCategory, __Insert);
	Gura_AssignMethod(wx_TaskBarJumpListCategory, __Prepend);
	Gura_AssignMethod(wx_TaskBarJumpListCategory, __SetTitle);
	Gura_AssignMethod(wx_TaskBarJumpListCategory, __GetTitle);
	Gura_AssignMethod(wx_TaskBarJumpListCategory, __GetItems);
}

Gura_ImplementDescendantCreator(wx_TaskBarJumpListCategory)
{
	return new Object_wx_TaskBarJumpListCategory((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
