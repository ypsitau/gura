//----------------------------------------------------------------------------
// wxGridCellTextEditor
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Gura interfaces for wxGridCellTextEditor
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Object implementation for wxGridCellTextEditor
//----------------------------------------------------------------------------
Object_wx_GridCellTextEditor::~Object_wx_GridCellTextEditor()
{
}

Object *Object_wx_GridCellTextEditor::Clone() const
{
	return nullptr;
}

String Object_wx_GridCellTextEditor::ToString(bool exprFlag)
{
	String rtn("<wx.GridCellTextEditor:");
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
Gura_DeclareFunctionAlias(__GridCellTextEditor, "GridCellTextEditor")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "maxChars", VTYPE_number, OCCUR_Once);
	SetClassToConstruct(Gura_UserClass(wx_GridCellTextEditor));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(__GridCellTextEditor)
{
	//size_t maxChars = arg.GetNumber(0)
	//explicit _rtn = wxGridCellTextEditor(maxChars);
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Method implementation
//----------------------------------------------------------------------------
Gura_DeclareMethodAlias(wx_GridCellTextEditor, __SetParameters, "SetParameters")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "params", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_GridCellTextEditor, __SetParameters)
{
	Object_wx_GridCellTextEditor *pThis = Object_wx_GridCellTextEditor::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxString& params = arg.GetNumber(0)
	//pThis->GetEntity()->SetParameters(params);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_GridCellTextEditor, __SetValidator, "SetValidator")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "validator", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_GridCellTextEditor, __SetValidator)
{
	Object_wx_GridCellTextEditor *pThis = Object_wx_GridCellTextEditor::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxValidator& validator = arg.GetNumber(0)
	//pThis->GetEntity()->SetValidator(validator);
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Class implementation for wxGridCellTextEditor
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_GridCellTextEditor)
{
	// Constructor assignment
	Gura_AssignFunction(__GridCellTextEditor);
	// Method assignment
	Gura_AssignMethod(wx_GridCellTextEditor, __SetParameters);
	Gura_AssignMethod(wx_GridCellTextEditor, __SetValidator);
}

Gura_ImplementDescendantCreator(wx_GridCellTextEditor)
{
	return new Object_wx_GridCellTextEditor((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
