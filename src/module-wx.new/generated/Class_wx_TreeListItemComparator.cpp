//----------------------------------------------------------------------------
// wxTreeListItemComparator
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Gura interfaces for wxTreeListItemComparator
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Object implementation for wxTreeListItemComparator
//----------------------------------------------------------------------------
Object_wx_TreeListItemComparator::~Object_wx_TreeListItemComparator()
{
}

Object *Object_wx_TreeListItemComparator::Clone() const
{
	return nullptr;
}

String Object_wx_TreeListItemComparator::ToString(bool exprFlag)
{
	String rtn("<wx.TreeListItemComparator:");
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
Gura_DeclareFunctionAlias(__TreeListItemComparator, "TreeListItemComparator")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	SetClassToConstruct(Gura_UserClass(wx_TreeListItemComparator));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(__TreeListItemComparator)
{
	//wxTreeListItemComparator();
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Method implementation
//----------------------------------------------------------------------------
Gura_DeclareMethodAlias(wx_TreeListItemComparator, __Compare, "Compare")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "treelist", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "column", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "first", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "second", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_TreeListItemComparator, __Compare)
{
	Object_wx_TreeListItemComparator *pThis = Object_wx_TreeListItemComparator::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxTreeListCtrl* treelist = arg.GetNumber(0)
	//unsigned column = arg.GetNumber(1)
	//wxTreeListItem first = arg.GetNumber(2)
	//wxTreeListItem second = arg.GetNumber(3)
	//pThis->GetEntity()->Compare(treelist, column, first, second);
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Class implementation for wxTreeListItemComparator
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_TreeListItemComparator)
{
	// Constructor assignment
	Gura_AssignFunction(__TreeListItemComparator);
	// Method assignment
	Gura_AssignMethod(wx_TreeListItemComparator, __Compare);
}

Gura_ImplementDescendantCreator(wx_TreeListItemComparator)
{
	return new Object_wx_TreeListItemComparator((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
