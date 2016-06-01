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
// Method implementation
//----------------------------------------------------------------------------
Gura_DeclareMethod(wx_GridCellTextEditor, wxGridCellTextEditor)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "maxChars", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_GridCellTextEditor, wxGridCellTextEditor)
{
	Signal &sig = env.GetSignal();
	Object_wx_GridCellTextEditor *pThis = Object_wx_GridCellTextEditor::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	//int maxChars = arg.GetNumber(0)
	//pThis->GetEntity()->wxGridCellTextEditor();
	return Value::Nil;
}

Gura_DeclareMethod(wx_GridCellTextEditor, SetParameters)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "params", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_GridCellTextEditor, SetParameters)
{
	Signal &sig = env.GetSignal();
	Object_wx_GridCellTextEditor *pThis = Object_wx_GridCellTextEditor::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	//int params = arg.GetNumber(0)
	//pThis->GetEntity()->SetParameters();
	return Value::Nil;
}

Gura_DeclareMethod(wx_GridCellTextEditor, SetValidator)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "validator", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_GridCellTextEditor, SetValidator)
{
	Signal &sig = env.GetSignal();
	Object_wx_GridCellTextEditor *pThis = Object_wx_GridCellTextEditor::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	//int validator = arg.GetNumber(0)
	//pThis->GetEntity()->SetValidator();
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Class implementation for wxGridCellTextEditor
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_GridCellTextEditor)
{
	Gura_AssignMethod(wx_GridCellTextEditor, wxGridCellTextEditor);
	Gura_AssignMethod(wx_GridCellTextEditor, SetParameters);
	Gura_AssignMethod(wx_GridCellTextEditor, SetValidator);
}

Gura_ImplementDescendantCreator(wx_GridCellTextEditor)
{
	return new Object_wx_GridCellTextEditor((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
