//----------------------------------------------------------------------------
// wxHeaderColumn
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Gura interfaces for wxHeaderColumn
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Object implementation for wxHeaderColumn
//----------------------------------------------------------------------------
Object_wx_HeaderColumn::~Object_wx_HeaderColumn()
{
}

Object *Object_wx_HeaderColumn::Clone() const
{
	return nullptr;
}

String Object_wx_HeaderColumn::ToString(bool exprFlag)
{
	String rtn("<wx.HeaderColumn:");
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
Gura_DeclareMethodAlias(wx_HeaderColumn, __GetTitle, "GetTitle")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_HeaderColumn, __GetTitle)
{
	Object_wx_HeaderColumn *pThis = Object_wx_HeaderColumn::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxString _rtn = pThis->GetEntity()->GetTitle();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_HeaderColumn, __GetBitmap, "GetBitmap")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_HeaderColumn, __GetBitmap)
{
	Object_wx_HeaderColumn *pThis = Object_wx_HeaderColumn::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxBitmap _rtn = pThis->GetEntity()->GetBitmap();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_HeaderColumn, __GetWidth, "GetWidth")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_HeaderColumn, __GetWidth)
{
	Object_wx_HeaderColumn *pThis = Object_wx_HeaderColumn::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int _rtn = pThis->GetEntity()->GetWidth();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_HeaderColumn, __GetMinWidth, "GetMinWidth")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_HeaderColumn, __GetMinWidth)
{
	Object_wx_HeaderColumn *pThis = Object_wx_HeaderColumn::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int _rtn = pThis->GetEntity()->GetMinWidth();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_HeaderColumn, __GetAlignment, "GetAlignment")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_HeaderColumn, __GetAlignment)
{
	Object_wx_HeaderColumn *pThis = Object_wx_HeaderColumn::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxAlignment _rtn = pThis->GetEntity()->GetAlignment();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_HeaderColumn, __GetFlags, "GetFlags")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_HeaderColumn, __GetFlags)
{
	Object_wx_HeaderColumn *pThis = Object_wx_HeaderColumn::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int _rtn = pThis->GetEntity()->GetFlags();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_HeaderColumn, __HasFlag, "HasFlag")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "flag", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_HeaderColumn, __HasFlag)
{
	Object_wx_HeaderColumn *pThis = Object_wx_HeaderColumn::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int flag = arg.GetNumber(0)
	//bool _rtn = pThis->GetEntity()->HasFlag(flag);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_HeaderColumn, __IsResizeable, "IsResizeable")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_HeaderColumn, __IsResizeable)
{
	Object_wx_HeaderColumn *pThis = Object_wx_HeaderColumn::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//bool _rtn = pThis->GetEntity()->IsResizeable();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_HeaderColumn, __IsSortable, "IsSortable")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_HeaderColumn, __IsSortable)
{
	Object_wx_HeaderColumn *pThis = Object_wx_HeaderColumn::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//bool _rtn = pThis->GetEntity()->IsSortable();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_HeaderColumn, __IsReorderable, "IsReorderable")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_HeaderColumn, __IsReorderable)
{
	Object_wx_HeaderColumn *pThis = Object_wx_HeaderColumn::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//bool _rtn = pThis->GetEntity()->IsReorderable();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_HeaderColumn, __IsHidden, "IsHidden")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_HeaderColumn, __IsHidden)
{
	Object_wx_HeaderColumn *pThis = Object_wx_HeaderColumn::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//bool _rtn = pThis->GetEntity()->IsHidden();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_HeaderColumn, __IsShown, "IsShown")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_HeaderColumn, __IsShown)
{
	Object_wx_HeaderColumn *pThis = Object_wx_HeaderColumn::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//bool _rtn = pThis->GetEntity()->IsShown();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_HeaderColumn, __IsSortKey, "IsSortKey")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_HeaderColumn, __IsSortKey)
{
	Object_wx_HeaderColumn *pThis = Object_wx_HeaderColumn::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//bool _rtn = pThis->GetEntity()->IsSortKey();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_HeaderColumn, __IsSortOrderAscending, "IsSortOrderAscending")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_HeaderColumn, __IsSortOrderAscending)
{
	Object_wx_HeaderColumn *pThis = Object_wx_HeaderColumn::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//bool _rtn = pThis->GetEntity()->IsSortOrderAscending();
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Class implementation for wxHeaderColumn
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_HeaderColumn)
{
	// Class assignment
	Gura_AssignValueEx("HeaderColumn", Reference());
	// Method assignment
	Gura_AssignMethod(wx_HeaderColumn, __GetTitle);
	Gura_AssignMethod(wx_HeaderColumn, __GetBitmap);
	Gura_AssignMethod(wx_HeaderColumn, __GetWidth);
	Gura_AssignMethod(wx_HeaderColumn, __GetMinWidth);
	Gura_AssignMethod(wx_HeaderColumn, __GetAlignment);
	Gura_AssignMethod(wx_HeaderColumn, __GetFlags);
	Gura_AssignMethod(wx_HeaderColumn, __HasFlag);
	Gura_AssignMethod(wx_HeaderColumn, __IsResizeable);
	Gura_AssignMethod(wx_HeaderColumn, __IsSortable);
	Gura_AssignMethod(wx_HeaderColumn, __IsReorderable);
	Gura_AssignMethod(wx_HeaderColumn, __IsHidden);
	Gura_AssignMethod(wx_HeaderColumn, __IsShown);
	Gura_AssignMethod(wx_HeaderColumn, __IsSortKey);
	Gura_AssignMethod(wx_HeaderColumn, __IsSortOrderAscending);
}

Gura_ImplementDescendantCreator(wx_HeaderColumn)
{
	return new Object_wx_HeaderColumn((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
