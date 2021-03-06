//----------------------------------------------------------------------------
// wxGridCellNumberRenderer
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Gura interfaces for wxGridCellNumberRenderer
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Object implementation for wxGridCellNumberRenderer
//----------------------------------------------------------------------------
Object_wx_GridCellNumberRenderer::~Object_wx_GridCellNumberRenderer()
{
}

Object *Object_wx_GridCellNumberRenderer::Clone() const
{
	return nullptr;
}

String Object_wx_GridCellNumberRenderer::ToString(bool exprFlag)
{
	String rtn("<wx.GridCellNumberRenderer:");
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
Gura_DeclareFunctionAlias(__GridCellNumberRenderer, "GridCellNumberRenderer")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	SetClassToConstruct(Gura_UserClass(wx_GridCellNumberRenderer));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(__GridCellNumberRenderer)
{
	//wxGridCellNumberRenderer();
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Class implementation for wxGridCellNumberRenderer
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_GridCellNumberRenderer)
{
	// Constructor assignment
	Gura_AssignFunction(__GridCellNumberRenderer);
}

Gura_ImplementDescendantCreator(wx_GridCellNumberRenderer)
{
	return new Object_wx_GridCellNumberRenderer((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
