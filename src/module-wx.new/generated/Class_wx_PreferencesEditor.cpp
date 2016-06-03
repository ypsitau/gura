//----------------------------------------------------------------------------
// wxPreferencesEditor
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Gura interfaces for wxPreferencesEditor
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Object implementation for wxPreferencesEditor
//----------------------------------------------------------------------------
Object_wx_PreferencesEditor::~Object_wx_PreferencesEditor()
{
}

Object *Object_wx_PreferencesEditor::Clone() const
{
	return nullptr;
}

String Object_wx_PreferencesEditor::ToString(bool exprFlag)
{
	String rtn("<wx.PreferencesEditor:");
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
Gura_DeclareMethodAlias(wx_PreferencesEditor, __wxPreferencesEditor, "wxPreferencesEditor")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "title", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_PreferencesEditor, __wxPreferencesEditor)
{
	Object_wx_PreferencesEditor *pThis = Object_wx_PreferencesEditor::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int title = arg.GetNumber(0)
	//pThis->GetEntity()->wxPreferencesEditor();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_PreferencesEditor, __AddPage, "AddPage")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "page", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_PreferencesEditor, __AddPage)
{
	Object_wx_PreferencesEditor *pThis = Object_wx_PreferencesEditor::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int page = arg.GetNumber(0)
	//pThis->GetEntity()->AddPage();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_PreferencesEditor, __Show, "Show")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "parent", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_PreferencesEditor, __Show)
{
	Object_wx_PreferencesEditor *pThis = Object_wx_PreferencesEditor::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int parent = arg.GetNumber(0)
	//pThis->GetEntity()->Show();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_PreferencesEditor, __Dismiss, "Dismiss")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_PreferencesEditor, __Dismiss)
{
	Object_wx_PreferencesEditor *pThis = Object_wx_PreferencesEditor::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->Dismiss();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_PreferencesEditor, __ShouldApplyChangesImmediately, "ShouldApplyChangesImmediately")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_PreferencesEditor, __ShouldApplyChangesImmediately)
{
	Object_wx_PreferencesEditor *pThis = Object_wx_PreferencesEditor::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->ShouldApplyChangesImmediately();
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Class implementation for wxPreferencesEditor
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_PreferencesEditor)
{
	Gura_AssignMethod(wx_PreferencesEditor, __wxPreferencesEditor);
	Gura_AssignMethod(wx_PreferencesEditor, __AddPage);
	Gura_AssignMethod(wx_PreferencesEditor, __Show);
	Gura_AssignMethod(wx_PreferencesEditor, __Dismiss);
	Gura_AssignMethod(wx_PreferencesEditor, __ShouldApplyChangesImmediately);
}

Gura_ImplementDescendantCreator(wx_PreferencesEditor)
{
	return new Object_wx_PreferencesEditor((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
