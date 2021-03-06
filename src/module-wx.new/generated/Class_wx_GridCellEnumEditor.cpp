//----------------------------------------------------------------------------
// wxGridCellEnumEditor
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Gura interfaces for wxGridCellEnumEditor
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Object implementation for wxGridCellEnumEditor
//----------------------------------------------------------------------------
Object_wx_GridCellEnumEditor::~Object_wx_GridCellEnumEditor()
{
}

Object *Object_wx_GridCellEnumEditor::Clone() const
{
	return nullptr;
}

String Object_wx_GridCellEnumEditor::ToString(bool exprFlag)
{
	String rtn("<wx.GridCellEnumEditor:");
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
Gura_DeclareFunctionAlias(__GridCellEnumEditor, "GridCellEnumEditor")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "choices", VTYPE_number, OCCUR_Once);
	SetClassToConstruct(Gura_UserClass(wx_GridCellEnumEditor));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(__GridCellEnumEditor)
{
	//const wxString& choices = arg.GetNumber(0)
	//wxGridCellEnumEditor(choices);
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Class implementation for wxGridCellEnumEditor
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_GridCellEnumEditor)
{
	// Constructor assignment
	Gura_AssignFunction(__GridCellEnumEditor);
}

Gura_ImplementDescendantCreator(wx_GridCellEnumEditor)
{
	return new Object_wx_GridCellEnumEditor((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
