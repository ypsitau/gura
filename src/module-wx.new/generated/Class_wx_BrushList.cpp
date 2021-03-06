//----------------------------------------------------------------------------
// wxBrushList
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Gura interfaces for wxBrushList
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Object implementation for wxBrushList
//----------------------------------------------------------------------------
Object_wx_BrushList::~Object_wx_BrushList()
{
}

Object *Object_wx_BrushList::Clone() const
{
	return nullptr;
}

String Object_wx_BrushList::ToString(bool exprFlag)
{
	String rtn("<wx.BrushList:");
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
Gura_DeclareMethodAlias(wx_BrushList, __FindOrCreateBrush, "FindOrCreateBrush")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "colour", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "style", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_BrushList, __FindOrCreateBrush)
{
	Object_wx_BrushList *pThis = Object_wx_BrushList::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxColour& colour = arg.GetNumber(0)
	//wxBrushStyle style = arg.GetNumber(1)
	//wxBrush* _rtn = pThis->GetEntity()->FindOrCreateBrush(colour, style);
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Class implementation for wxBrushList
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_BrushList)
{
	// Class assignment
	Gura_AssignValueEx("BrushList", Reference());
	// Method assignment
	Gura_AssignMethod(wx_BrushList, __FindOrCreateBrush);
}

Gura_ImplementDescendantCreator(wx_BrushList)
{
	return new Object_wx_BrushList((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
