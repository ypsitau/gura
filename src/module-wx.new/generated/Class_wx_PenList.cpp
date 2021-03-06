//----------------------------------------------------------------------------
// wxPenList
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Gura interfaces for wxPenList
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Object implementation for wxPenList
//----------------------------------------------------------------------------
Object_wx_PenList::~Object_wx_PenList()
{
}

Object *Object_wx_PenList::Clone() const
{
	return nullptr;
}

String Object_wx_PenList::ToString(bool exprFlag)
{
	String rtn("<wx.PenList:");
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
Gura_DeclareFunctionAlias(__PenList, "PenList")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	SetClassToConstruct(Gura_UserClass(wx_PenList));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(__PenList)
{
	//wxPenList();
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Method implementation
//----------------------------------------------------------------------------
Gura_DeclareMethodAlias(wx_PenList, __FindOrCreatePen, "FindOrCreatePen")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "colour", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "width", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "style", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_PenList, __FindOrCreatePen)
{
	Object_wx_PenList *pThis = Object_wx_PenList::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxColour& colour = arg.GetNumber(0)
	//int width = arg.GetNumber(1)
	//wxPenStyle style = arg.GetNumber(2)
	//wxPen* _rtn = pThis->GetEntity()->FindOrCreatePen(colour, width, style);
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Class implementation for wxPenList
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_PenList)
{
	// Constructor assignment
	Gura_AssignFunction(__PenList);
	// Method assignment
	Gura_AssignMethod(wx_PenList, __FindOrCreatePen);
}

Gura_ImplementDescendantCreator(wx_PenList)
{
	return new Object_wx_PenList((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
