//----------------------------------------------------------------------------
// wxFindReplaceDialog
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Gura interfaces for wxFindReplaceDialog
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Object implementation for wxFindReplaceDialog
//----------------------------------------------------------------------------
Object_wx_FindReplaceDialog::~Object_wx_FindReplaceDialog()
{
}

Object *Object_wx_FindReplaceDialog::Clone() const
{
	return nullptr;
}

String Object_wx_FindReplaceDialog::ToString(bool exprFlag)
{
	String rtn("<wx.FindReplaceDialog:");
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
Gura_DeclareFunctionAlias(__FindReplaceDialog, "FindReplaceDialog")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	SetClassToConstruct(Gura_UserClass(wx_FindReplaceDialog));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(__FindReplaceDialog)
{
	//wxFindReplaceDialog();
	return Value::Nil;
}

Gura_DeclareFunctionAlias(__FindReplaceDialog_1, "FindReplaceDialog_1")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "parent", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "data", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "title", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "style", VTYPE_number, OCCUR_Once);
	SetClassToConstruct(Gura_UserClass(wx_FindReplaceDialog));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(__FindReplaceDialog_1)
{
	//wxWindow* parent = arg.GetNumber(0)
	//wxFindReplaceData* data = arg.GetNumber(1)
	//const wxString& title = arg.GetNumber(2)
	//int style = arg.GetNumber(3)
	//wxFindReplaceDialog(parent, data, title, style);
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Method implementation
//----------------------------------------------------------------------------
Gura_DeclareMethodAlias(wx_FindReplaceDialog, __Create, "Create")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "parent", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "data", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "title", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "style", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_FindReplaceDialog, __Create)
{
	Object_wx_FindReplaceDialog *pThis = Object_wx_FindReplaceDialog::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxWindow* parent = arg.GetNumber(0)
	//wxFindReplaceData* data = arg.GetNumber(1)
	//const wxString& title = arg.GetNumber(2)
	//int style = arg.GetNumber(3)
	//bool _rtn = pThis->GetEntity()->Create(parent, data, title, style);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_FindReplaceDialog, __GetData, "GetData")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_FindReplaceDialog, __GetData)
{
	Object_wx_FindReplaceDialog *pThis = Object_wx_FindReplaceDialog::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxFindReplaceData* _rtn = pThis->GetEntity()->GetData();
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Class implementation for wxFindReplaceDialog
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_FindReplaceDialog)
{
	// Constructor assignment
	Gura_AssignFunction(__FindReplaceDialog);
	Gura_AssignFunction(__FindReplaceDialog_1);
	// Method assignment
	Gura_AssignMethod(wx_FindReplaceDialog, __Create);
	Gura_AssignMethod(wx_FindReplaceDialog, __GetData);
}

Gura_ImplementDescendantCreator(wx_FindReplaceDialog)
{
	return new Object_wx_FindReplaceDialog((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
