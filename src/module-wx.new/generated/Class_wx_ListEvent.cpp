//----------------------------------------------------------------------------
// wxListEvent
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Gura interfaces for wxListEvent
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Object implementation for wxListEvent
//----------------------------------------------------------------------------
Object_wx_ListEvent::~Object_wx_ListEvent()
{
}

Object *Object_wx_ListEvent::Clone() const
{
	return nullptr;
}

String Object_wx_ListEvent::ToString(bool exprFlag)
{
	String rtn("<wx.ListEvent:");
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
Gura_DeclareFunctionAlias(__ListEvent, "ListEvent")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "commandType", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "id", VTYPE_number, OCCUR_Once);
	SetClassToConstruct(Gura_UserClass(wx_ListEvent));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(__ListEvent)
{
	//wxEventType commandType = arg.GetNumber(0)
	//int id = arg.GetNumber(1)
	//wxListEvent(commandType, id);
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Method implementation
//----------------------------------------------------------------------------
Gura_DeclareMethodAlias(wx_ListEvent, __GetCacheFrom, "GetCacheFrom")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_ListEvent, __GetCacheFrom)
{
	Object_wx_ListEvent *pThis = Object_wx_ListEvent::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//long _rtn = pThis->GetEntity()->GetCacheFrom();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_ListEvent, __GetCacheTo, "GetCacheTo")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_ListEvent, __GetCacheTo)
{
	Object_wx_ListEvent *pThis = Object_wx_ListEvent::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//long _rtn = pThis->GetEntity()->GetCacheTo();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_ListEvent, __GetColumn, "GetColumn")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_ListEvent, __GetColumn)
{
	Object_wx_ListEvent *pThis = Object_wx_ListEvent::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int _rtn = pThis->GetEntity()->GetColumn();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_ListEvent, __GetData, "GetData")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_ListEvent, __GetData)
{
	Object_wx_ListEvent *pThis = Object_wx_ListEvent::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxUIntPtr _rtn = pThis->GetEntity()->GetData();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_ListEvent, __GetImage, "GetImage")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_ListEvent, __GetImage)
{
	Object_wx_ListEvent *pThis = Object_wx_ListEvent::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int _rtn = pThis->GetEntity()->GetImage();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_ListEvent, __GetIndex, "GetIndex")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_ListEvent, __GetIndex)
{
	Object_wx_ListEvent *pThis = Object_wx_ListEvent::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//long _rtn = pThis->GetEntity()->GetIndex();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_ListEvent, __GetItem, "GetItem")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_ListEvent, __GetItem)
{
	Object_wx_ListEvent *pThis = Object_wx_ListEvent::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxListItem& _rtn = pThis->GetEntity()->GetItem();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_ListEvent, __GetKeyCode, "GetKeyCode")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_ListEvent, __GetKeyCode)
{
	Object_wx_ListEvent *pThis = Object_wx_ListEvent::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int _rtn = pThis->GetEntity()->GetKeyCode();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_ListEvent, __GetLabel, "GetLabel")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_ListEvent, __GetLabel)
{
	Object_wx_ListEvent *pThis = Object_wx_ListEvent::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxString& _rtn = pThis->GetEntity()->GetLabel();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_ListEvent, __GetMask, "GetMask")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_ListEvent, __GetMask)
{
	Object_wx_ListEvent *pThis = Object_wx_ListEvent::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//long _rtn = pThis->GetEntity()->GetMask();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_ListEvent, __GetPoint, "GetPoint")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_ListEvent, __GetPoint)
{
	Object_wx_ListEvent *pThis = Object_wx_ListEvent::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxPoint _rtn = pThis->GetEntity()->GetPoint();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_ListEvent, __GetText, "GetText")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_ListEvent, __GetText)
{
	Object_wx_ListEvent *pThis = Object_wx_ListEvent::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxString& _rtn = pThis->GetEntity()->GetText();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_ListEvent, __IsEditCancelled, "IsEditCancelled")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_ListEvent, __IsEditCancelled)
{
	Object_wx_ListEvent *pThis = Object_wx_ListEvent::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//bool _rtn = pThis->GetEntity()->IsEditCancelled();
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Class implementation for wxListEvent
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_ListEvent)
{
	// Constructor assignment
	Gura_AssignFunction(__ListEvent);
	// Method assignment
	Gura_AssignMethod(wx_ListEvent, __GetCacheFrom);
	Gura_AssignMethod(wx_ListEvent, __GetCacheTo);
	Gura_AssignMethod(wx_ListEvent, __GetColumn);
	Gura_AssignMethod(wx_ListEvent, __GetData);
	Gura_AssignMethod(wx_ListEvent, __GetImage);
	Gura_AssignMethod(wx_ListEvent, __GetIndex);
	Gura_AssignMethod(wx_ListEvent, __GetItem);
	Gura_AssignMethod(wx_ListEvent, __GetKeyCode);
	Gura_AssignMethod(wx_ListEvent, __GetLabel);
	Gura_AssignMethod(wx_ListEvent, __GetMask);
	Gura_AssignMethod(wx_ListEvent, __GetPoint);
	Gura_AssignMethod(wx_ListEvent, __GetText);
	Gura_AssignMethod(wx_ListEvent, __IsEditCancelled);
}

Gura_ImplementDescendantCreator(wx_ListEvent)
{
	return new Object_wx_ListEvent((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
