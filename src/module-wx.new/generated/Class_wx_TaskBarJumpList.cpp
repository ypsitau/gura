//----------------------------------------------------------------------------
// wxTaskBarJumpList
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Gura interfaces for wxTaskBarJumpList
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Object implementation for wxTaskBarJumpList
//----------------------------------------------------------------------------
Object_wx_TaskBarJumpList::~Object_wx_TaskBarJumpList()
{
}

Object *Object_wx_TaskBarJumpList::Clone() const
{
	return nullptr;
}

String Object_wx_TaskBarJumpList::ToString(bool exprFlag)
{
	String rtn("<wx.TaskBarJumpList:");
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
Gura_DeclareFunctionAlias(__TaskBarJumpList, "TaskBarJumpList")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "appID", VTYPE_number, OCCUR_Once);
	SetClassToConstruct(Gura_UserClass(wx_TaskBarJumpList));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(__TaskBarJumpList)
{
	//const wxString& appID = arg.GetNumber(0)
	//wxTaskBarJumpList(appID);
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Method implementation
//----------------------------------------------------------------------------
Gura_DeclareMethodAlias(wx_TaskBarJumpList, __ShowRecentCategory, "ShowRecentCategory")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "shown", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_TaskBarJumpList, __ShowRecentCategory)
{
	Object_wx_TaskBarJumpList *pThis = Object_wx_TaskBarJumpList::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//bool shown = arg.GetNumber(0)
	//pThis->GetEntity()->ShowRecentCategory(shown);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_TaskBarJumpList, __HideRecentCategory, "HideRecentCategory")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_TaskBarJumpList, __HideRecentCategory)
{
	Object_wx_TaskBarJumpList *pThis = Object_wx_TaskBarJumpList::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->HideRecentCategory();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_TaskBarJumpList, __ShowFrequentCategory, "ShowFrequentCategory")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "shown", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_TaskBarJumpList, __ShowFrequentCategory)
{
	Object_wx_TaskBarJumpList *pThis = Object_wx_TaskBarJumpList::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//bool shown = arg.GetNumber(0)
	//pThis->GetEntity()->ShowFrequentCategory(shown);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_TaskBarJumpList, __HideFrequentCategory, "HideFrequentCategory")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_TaskBarJumpList, __HideFrequentCategory)
{
	Object_wx_TaskBarJumpList *pThis = Object_wx_TaskBarJumpList::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->HideFrequentCategory();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_TaskBarJumpList, __GetTasks, "GetTasks")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_TaskBarJumpList, __GetTasks)
{
	Object_wx_TaskBarJumpList *pThis = Object_wx_TaskBarJumpList::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxTaskBarJumpListCategory& _rtn = pThis->GetEntity()->GetTasks();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_TaskBarJumpList, __GetFrequentCategory, "GetFrequentCategory")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_TaskBarJumpList, __GetFrequentCategory)
{
	Object_wx_TaskBarJumpList *pThis = Object_wx_TaskBarJumpList::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxTaskBarJumpListCategory& _rtn = pThis->GetEntity()->GetFrequentCategory();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_TaskBarJumpList, __GetRecentCategory, "GetRecentCategory")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_TaskBarJumpList, __GetRecentCategory)
{
	Object_wx_TaskBarJumpList *pThis = Object_wx_TaskBarJumpList::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxTaskBarJumpListCategory& _rtn = pThis->GetEntity()->GetRecentCategory();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_TaskBarJumpList, __GetCustomCategories, "GetCustomCategories")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_TaskBarJumpList, __GetCustomCategories)
{
	Object_wx_TaskBarJumpList *pThis = Object_wx_TaskBarJumpList::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxTaskBarJumpListCategories& _rtn = pThis->GetEntity()->GetCustomCategories();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_TaskBarJumpList, __AddCustomCategory, "AddCustomCategory")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "category", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_TaskBarJumpList, __AddCustomCategory)
{
	Object_wx_TaskBarJumpList *pThis = Object_wx_TaskBarJumpList::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxTaskBarJumpListCategory* category = arg.GetNumber(0)
	//pThis->GetEntity()->AddCustomCategory(category);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_TaskBarJumpList, __RemoveCustomCategory, "RemoveCustomCategory")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "title", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_TaskBarJumpList, __RemoveCustomCategory)
{
	Object_wx_TaskBarJumpList *pThis = Object_wx_TaskBarJumpList::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxString& title = arg.GetNumber(0)
	//wxTaskBarJumpListCategory* _rtn = pThis->GetEntity()->RemoveCustomCategory(title);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_TaskBarJumpList, __DeleteCustomCategory, "DeleteCustomCategory")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "title", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_TaskBarJumpList, __DeleteCustomCategory)
{
	Object_wx_TaskBarJumpList *pThis = Object_wx_TaskBarJumpList::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxString& title = arg.GetNumber(0)
	//pThis->GetEntity()->DeleteCustomCategory(title);
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Class implementation for wxTaskBarJumpList
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_TaskBarJumpList)
{
	// Constructor assignment
	Gura_AssignFunction(__TaskBarJumpList);
	// Method assignment
	Gura_AssignMethod(wx_TaskBarJumpList, __ShowRecentCategory);
	Gura_AssignMethod(wx_TaskBarJumpList, __HideRecentCategory);
	Gura_AssignMethod(wx_TaskBarJumpList, __ShowFrequentCategory);
	Gura_AssignMethod(wx_TaskBarJumpList, __HideFrequentCategory);
	Gura_AssignMethod(wx_TaskBarJumpList, __GetTasks);
	Gura_AssignMethod(wx_TaskBarJumpList, __GetFrequentCategory);
	Gura_AssignMethod(wx_TaskBarJumpList, __GetRecentCategory);
	Gura_AssignMethod(wx_TaskBarJumpList, __GetCustomCategories);
	Gura_AssignMethod(wx_TaskBarJumpList, __AddCustomCategory);
	Gura_AssignMethod(wx_TaskBarJumpList, __RemoveCustomCategory);
	Gura_AssignMethod(wx_TaskBarJumpList, __DeleteCustomCategory);
}

Gura_ImplementDescendantCreator(wx_TaskBarJumpList)
{
	return new Object_wx_TaskBarJumpList((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
