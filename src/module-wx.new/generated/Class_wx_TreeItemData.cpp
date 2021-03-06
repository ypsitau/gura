//----------------------------------------------------------------------------
// wxTreeItemData
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Gura interfaces for wxTreeItemData
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Object implementation for wxTreeItemData
//----------------------------------------------------------------------------
Object_wx_TreeItemData::~Object_wx_TreeItemData()
{
}

Object *Object_wx_TreeItemData::Clone() const
{
	return nullptr;
}

String Object_wx_TreeItemData::ToString(bool exprFlag)
{
	String rtn("<wx.TreeItemData:");
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
Gura_DeclareFunctionAlias(__TreeItemData, "TreeItemData")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	SetClassToConstruct(Gura_UserClass(wx_TreeItemData));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(__TreeItemData)
{
	//wxTreeItemData();
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Method implementation
//----------------------------------------------------------------------------
Gura_DeclareMethodAlias(wx_TreeItemData, __GetId, "GetId")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_TreeItemData, __GetId)
{
	Object_wx_TreeItemData *pThis = Object_wx_TreeItemData::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxTreeItemId& _rtn = pThis->GetEntity()->GetId();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_TreeItemData, __SetId, "SetId")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "id", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_TreeItemData, __SetId)
{
	Object_wx_TreeItemData *pThis = Object_wx_TreeItemData::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxTreeItemId& id = arg.GetNumber(0)
	//pThis->GetEntity()->SetId(id);
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Class implementation for wxTreeItemData
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_TreeItemData)
{
	// Constructor assignment
	Gura_AssignFunction(__TreeItemData);
	// Method assignment
	Gura_AssignMethod(wx_TreeItemData, __GetId);
	Gura_AssignMethod(wx_TreeItemData, __SetId);
}

Gura_ImplementDescendantCreator(wx_TreeItemData)
{
	return new Object_wx_TreeItemData((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
