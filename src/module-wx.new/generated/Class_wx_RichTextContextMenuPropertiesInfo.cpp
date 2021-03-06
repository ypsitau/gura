//----------------------------------------------------------------------------
// wxRichTextContextMenuPropertiesInfo
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Gura interfaces for wxRichTextContextMenuPropertiesInfo
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Object implementation for wxRichTextContextMenuPropertiesInfo
//----------------------------------------------------------------------------
Object_wx_RichTextContextMenuPropertiesInfo::~Object_wx_RichTextContextMenuPropertiesInfo()
{
}

Object *Object_wx_RichTextContextMenuPropertiesInfo::Clone() const
{
	return nullptr;
}

String Object_wx_RichTextContextMenuPropertiesInfo::ToString(bool exprFlag)
{
	String rtn("<wx.RichTextContextMenuPropertiesInfo:");
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
Gura_DeclareFunctionAlias(__RichTextContextMenuPropertiesInfo, "RichTextContextMenuPropertiesInfo")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	SetClassToConstruct(Gura_UserClass(wx_RichTextContextMenuPropertiesInfo));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(__RichTextContextMenuPropertiesInfo)
{
	//wxRichTextContextMenuPropertiesInfo();
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Method implementation
//----------------------------------------------------------------------------
Gura_DeclareMethodAlias(wx_RichTextContextMenuPropertiesInfo, __Init, "Init")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_RichTextContextMenuPropertiesInfo, __Init)
{
	Object_wx_RichTextContextMenuPropertiesInfo *pThis = Object_wx_RichTextContextMenuPropertiesInfo::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->Init();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RichTextContextMenuPropertiesInfo, __AddItem, "AddItem")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "label", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "obj", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_RichTextContextMenuPropertiesInfo, __AddItem)
{
	Object_wx_RichTextContextMenuPropertiesInfo *pThis = Object_wx_RichTextContextMenuPropertiesInfo::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxString& label = arg.GetNumber(0)
	//wxRichTextObject* obj = arg.GetNumber(1)
	//bool _rtn = pThis->GetEntity()->AddItem(label, obj);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RichTextContextMenuPropertiesInfo, __AddMenuItems, "AddMenuItems")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "menu", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "startCmd", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_RichTextContextMenuPropertiesInfo, __AddMenuItems)
{
	Object_wx_RichTextContextMenuPropertiesInfo *pThis = Object_wx_RichTextContextMenuPropertiesInfo::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxMenu* menu = arg.GetNumber(0)
	//int startCmd = arg.GetNumber(1)
	//int _rtn = pThis->GetEntity()->AddMenuItems(menu, startCmd);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RichTextContextMenuPropertiesInfo, __AddItems, "AddItems")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "ctrl", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "container", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "obj", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_RichTextContextMenuPropertiesInfo, __AddItems)
{
	Object_wx_RichTextContextMenuPropertiesInfo *pThis = Object_wx_RichTextContextMenuPropertiesInfo::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxRichTextCtrl* ctrl = arg.GetNumber(0)
	//wxRichTextObject* container = arg.GetNumber(1)
	//wxRichTextObject* obj = arg.GetNumber(2)
	//int _rtn = pThis->GetEntity()->AddItems(ctrl, container, obj);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RichTextContextMenuPropertiesInfo, __Clear, "Clear")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_RichTextContextMenuPropertiesInfo, __Clear)
{
	Object_wx_RichTextContextMenuPropertiesInfo *pThis = Object_wx_RichTextContextMenuPropertiesInfo::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->Clear();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RichTextContextMenuPropertiesInfo, __GetLabel, "GetLabel")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "n", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_RichTextContextMenuPropertiesInfo, __GetLabel)
{
	Object_wx_RichTextContextMenuPropertiesInfo *pThis = Object_wx_RichTextContextMenuPropertiesInfo::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int n = arg.GetNumber(0)
	//wxString _rtn = pThis->GetEntity()->GetLabel(n);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RichTextContextMenuPropertiesInfo, __GetObject, "GetObject")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "n", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_RichTextContextMenuPropertiesInfo, __GetObject)
{
	Object_wx_RichTextContextMenuPropertiesInfo *pThis = Object_wx_RichTextContextMenuPropertiesInfo::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int n = arg.GetNumber(0)
	//wxRichTextObject* _rtn = pThis->GetEntity()->GetObject(n);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RichTextContextMenuPropertiesInfo, __GetObjects, "GetObjects")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_RichTextContextMenuPropertiesInfo, __GetObjects)
{
	Object_wx_RichTextContextMenuPropertiesInfo *pThis = Object_wx_RichTextContextMenuPropertiesInfo::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxRichTextObjectPtrArray& _rtn = pThis->GetEntity()->GetObjects();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RichTextContextMenuPropertiesInfo, __GetObjects_1, "GetObjects_1")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_RichTextContextMenuPropertiesInfo, __GetObjects_1)
{
	Object_wx_RichTextContextMenuPropertiesInfo *pThis = Object_wx_RichTextContextMenuPropertiesInfo::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxRichTextObjectPtrArray& _rtn = pThis->GetEntity()->GetObjects();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RichTextContextMenuPropertiesInfo, __GetLabels, "GetLabels")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_RichTextContextMenuPropertiesInfo, __GetLabels)
{
	Object_wx_RichTextContextMenuPropertiesInfo *pThis = Object_wx_RichTextContextMenuPropertiesInfo::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxArrayString& _rtn = pThis->GetEntity()->GetLabels();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RichTextContextMenuPropertiesInfo, __GetLabels_1, "GetLabels_1")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_RichTextContextMenuPropertiesInfo, __GetLabels_1)
{
	Object_wx_RichTextContextMenuPropertiesInfo *pThis = Object_wx_RichTextContextMenuPropertiesInfo::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxArrayString& _rtn = pThis->GetEntity()->GetLabels();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RichTextContextMenuPropertiesInfo, __GetCount, "GetCount")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_RichTextContextMenuPropertiesInfo, __GetCount)
{
	Object_wx_RichTextContextMenuPropertiesInfo *pThis = Object_wx_RichTextContextMenuPropertiesInfo::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int _rtn = pThis->GetEntity()->GetCount();
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Class implementation for wxRichTextContextMenuPropertiesInfo
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_RichTextContextMenuPropertiesInfo)
{
	// Constructor assignment
	Gura_AssignFunction(__RichTextContextMenuPropertiesInfo);
	// Method assignment
	Gura_AssignMethod(wx_RichTextContextMenuPropertiesInfo, __Init);
	Gura_AssignMethod(wx_RichTextContextMenuPropertiesInfo, __AddItem);
	Gura_AssignMethod(wx_RichTextContextMenuPropertiesInfo, __AddMenuItems);
	Gura_AssignMethod(wx_RichTextContextMenuPropertiesInfo, __AddItems);
	Gura_AssignMethod(wx_RichTextContextMenuPropertiesInfo, __Clear);
	Gura_AssignMethod(wx_RichTextContextMenuPropertiesInfo, __GetLabel);
	Gura_AssignMethod(wx_RichTextContextMenuPropertiesInfo, __GetObject);
	Gura_AssignMethod(wx_RichTextContextMenuPropertiesInfo, __GetObjects);
	Gura_AssignMethod(wx_RichTextContextMenuPropertiesInfo, __GetObjects_1);
	Gura_AssignMethod(wx_RichTextContextMenuPropertiesInfo, __GetLabels);
	Gura_AssignMethod(wx_RichTextContextMenuPropertiesInfo, __GetLabels_1);
	Gura_AssignMethod(wx_RichTextContextMenuPropertiesInfo, __GetCount);
}

Gura_ImplementDescendantCreator(wx_RichTextContextMenuPropertiesInfo)
{
	return new Object_wx_RichTextContextMenuPropertiesInfo((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
