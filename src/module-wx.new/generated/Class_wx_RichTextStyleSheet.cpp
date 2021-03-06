//----------------------------------------------------------------------------
// wxRichTextStyleSheet
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Gura interfaces for wxRichTextStyleSheet
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Object implementation for wxRichTextStyleSheet
//----------------------------------------------------------------------------
Object_wx_RichTextStyleSheet::~Object_wx_RichTextStyleSheet()
{
}

Object *Object_wx_RichTextStyleSheet::Clone() const
{
	return nullptr;
}

String Object_wx_RichTextStyleSheet::ToString(bool exprFlag)
{
	String rtn("<wx.RichTextStyleSheet:");
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
Gura_DeclareFunctionAlias(__RichTextStyleSheet, "RichTextStyleSheet")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	SetClassToConstruct(Gura_UserClass(wx_RichTextStyleSheet));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(__RichTextStyleSheet)
{
	//wxRichTextStyleSheet();
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Method implementation
//----------------------------------------------------------------------------
Gura_DeclareMethodAlias(wx_RichTextStyleSheet, __AddCharacterStyle, "AddCharacterStyle")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "def", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_RichTextStyleSheet, __AddCharacterStyle)
{
	Object_wx_RichTextStyleSheet *pThis = Object_wx_RichTextStyleSheet::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxRichTextCharacterStyleDefinition* def = arg.GetNumber(0)
	//bool _rtn = pThis->GetEntity()->AddCharacterStyle(def);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RichTextStyleSheet, __AddListStyle, "AddListStyle")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "def", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_RichTextStyleSheet, __AddListStyle)
{
	Object_wx_RichTextStyleSheet *pThis = Object_wx_RichTextStyleSheet::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxRichTextListStyleDefinition* def = arg.GetNumber(0)
	//bool _rtn = pThis->GetEntity()->AddListStyle(def);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RichTextStyleSheet, __AddParagraphStyle, "AddParagraphStyle")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "def", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_RichTextStyleSheet, __AddParagraphStyle)
{
	Object_wx_RichTextStyleSheet *pThis = Object_wx_RichTextStyleSheet::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxRichTextParagraphStyleDefinition* def = arg.GetNumber(0)
	//bool _rtn = pThis->GetEntity()->AddParagraphStyle(def);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RichTextStyleSheet, __AddStyle, "AddStyle")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "def", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_RichTextStyleSheet, __AddStyle)
{
	Object_wx_RichTextStyleSheet *pThis = Object_wx_RichTextStyleSheet::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxRichTextStyleDefinition* def = arg.GetNumber(0)
	//bool _rtn = pThis->GetEntity()->AddStyle(def);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RichTextStyleSheet, __DeleteStyles, "DeleteStyles")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_RichTextStyleSheet, __DeleteStyles)
{
	Object_wx_RichTextStyleSheet *pThis = Object_wx_RichTextStyleSheet::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->DeleteStyles();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RichTextStyleSheet, __FindCharacterStyle, "FindCharacterStyle")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "name", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "recurse", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_RichTextStyleSheet, __FindCharacterStyle)
{
	Object_wx_RichTextStyleSheet *pThis = Object_wx_RichTextStyleSheet::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxString& name = arg.GetNumber(0)
	//bool recurse = arg.GetNumber(1)
	//wxRichTextCharacterStyleDefinition* _rtn = pThis->GetEntity()->FindCharacterStyle(name, recurse);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RichTextStyleSheet, __FindListStyle, "FindListStyle")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "name", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "recurse", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_RichTextStyleSheet, __FindListStyle)
{
	Object_wx_RichTextStyleSheet *pThis = Object_wx_RichTextStyleSheet::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxString& name = arg.GetNumber(0)
	//bool recurse = arg.GetNumber(1)
	//wxRichTextListStyleDefinition* _rtn = pThis->GetEntity()->FindListStyle(name, recurse);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RichTextStyleSheet, __FindParagraphStyle, "FindParagraphStyle")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "name", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "recurse", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_RichTextStyleSheet, __FindParagraphStyle)
{
	Object_wx_RichTextStyleSheet *pThis = Object_wx_RichTextStyleSheet::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxString& name = arg.GetNumber(0)
	//bool recurse = arg.GetNumber(1)
	//wxRichTextParagraphStyleDefinition* _rtn = pThis->GetEntity()->FindParagraphStyle(name, recurse);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RichTextStyleSheet, __FindStyle, "FindStyle")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "name", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_RichTextStyleSheet, __FindStyle)
{
	Object_wx_RichTextStyleSheet *pThis = Object_wx_RichTextStyleSheet::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxString& name = arg.GetNumber(0)
	//wxRichTextStyleDefinition* _rtn = pThis->GetEntity()->FindStyle(name);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RichTextStyleSheet, __GetCharacterStyle, "GetCharacterStyle")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "n", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_RichTextStyleSheet, __GetCharacterStyle)
{
	Object_wx_RichTextStyleSheet *pThis = Object_wx_RichTextStyleSheet::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//size_t n = arg.GetNumber(0)
	//wxRichTextCharacterStyleDefinition* _rtn = pThis->GetEntity()->GetCharacterStyle(n);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RichTextStyleSheet, __GetCharacterStyleCount, "GetCharacterStyleCount")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_RichTextStyleSheet, __GetCharacterStyleCount)
{
	Object_wx_RichTextStyleSheet *pThis = Object_wx_RichTextStyleSheet::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//size_t _rtn = pThis->GetEntity()->GetCharacterStyleCount();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RichTextStyleSheet, __GetDescription, "GetDescription")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_RichTextStyleSheet, __GetDescription)
{
	Object_wx_RichTextStyleSheet *pThis = Object_wx_RichTextStyleSheet::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxString& _rtn = pThis->GetEntity()->GetDescription();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RichTextStyleSheet, __GetListStyle, "GetListStyle")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "n", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_RichTextStyleSheet, __GetListStyle)
{
	Object_wx_RichTextStyleSheet *pThis = Object_wx_RichTextStyleSheet::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//size_t n = arg.GetNumber(0)
	//wxRichTextListStyleDefinition* _rtn = pThis->GetEntity()->GetListStyle(n);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RichTextStyleSheet, __GetListStyleCount, "GetListStyleCount")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_RichTextStyleSheet, __GetListStyleCount)
{
	Object_wx_RichTextStyleSheet *pThis = Object_wx_RichTextStyleSheet::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//size_t _rtn = pThis->GetEntity()->GetListStyleCount();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RichTextStyleSheet, __GetName, "GetName")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_RichTextStyleSheet, __GetName)
{
	Object_wx_RichTextStyleSheet *pThis = Object_wx_RichTextStyleSheet::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxString& _rtn = pThis->GetEntity()->GetName();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RichTextStyleSheet, __GetParagraphStyle, "GetParagraphStyle")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "n", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_RichTextStyleSheet, __GetParagraphStyle)
{
	Object_wx_RichTextStyleSheet *pThis = Object_wx_RichTextStyleSheet::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//size_t n = arg.GetNumber(0)
	//wxRichTextParagraphStyleDefinition* _rtn = pThis->GetEntity()->GetParagraphStyle(n);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RichTextStyleSheet, __GetParagraphStyleCount, "GetParagraphStyleCount")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_RichTextStyleSheet, __GetParagraphStyleCount)
{
	Object_wx_RichTextStyleSheet *pThis = Object_wx_RichTextStyleSheet::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//size_t _rtn = pThis->GetEntity()->GetParagraphStyleCount();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RichTextStyleSheet, __RemoveCharacterStyle, "RemoveCharacterStyle")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "def", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "deleteStyle", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_RichTextStyleSheet, __RemoveCharacterStyle)
{
	Object_wx_RichTextStyleSheet *pThis = Object_wx_RichTextStyleSheet::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxRichTextStyleDefinition* def = arg.GetNumber(0)
	//bool deleteStyle = arg.GetNumber(1)
	//bool _rtn = pThis->GetEntity()->RemoveCharacterStyle(def, deleteStyle);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RichTextStyleSheet, __RemoveListStyle, "RemoveListStyle")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "def", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "deleteStyle", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_RichTextStyleSheet, __RemoveListStyle)
{
	Object_wx_RichTextStyleSheet *pThis = Object_wx_RichTextStyleSheet::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxRichTextStyleDefinition* def = arg.GetNumber(0)
	//bool deleteStyle = arg.GetNumber(1)
	//bool _rtn = pThis->GetEntity()->RemoveListStyle(def, deleteStyle);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RichTextStyleSheet, __RemoveParagraphStyle, "RemoveParagraphStyle")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "def", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "deleteStyle", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_RichTextStyleSheet, __RemoveParagraphStyle)
{
	Object_wx_RichTextStyleSheet *pThis = Object_wx_RichTextStyleSheet::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxRichTextStyleDefinition* def = arg.GetNumber(0)
	//bool deleteStyle = arg.GetNumber(1)
	//bool _rtn = pThis->GetEntity()->RemoveParagraphStyle(def, deleteStyle);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RichTextStyleSheet, __RemoveStyle, "RemoveStyle")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "def", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "deleteStyle", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_RichTextStyleSheet, __RemoveStyle)
{
	Object_wx_RichTextStyleSheet *pThis = Object_wx_RichTextStyleSheet::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxRichTextStyleDefinition* def = arg.GetNumber(0)
	//bool deleteStyle = arg.GetNumber(1)
	//bool _rtn = pThis->GetEntity()->RemoveStyle(def, deleteStyle);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RichTextStyleSheet, __SetDescription, "SetDescription")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "descr", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_RichTextStyleSheet, __SetDescription)
{
	Object_wx_RichTextStyleSheet *pThis = Object_wx_RichTextStyleSheet::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxString& descr = arg.GetNumber(0)
	//pThis->GetEntity()->SetDescription(descr);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RichTextStyleSheet, __SetName, "SetName")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "name", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_RichTextStyleSheet, __SetName)
{
	Object_wx_RichTextStyleSheet *pThis = Object_wx_RichTextStyleSheet::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxString& name = arg.GetNumber(0)
	//pThis->GetEntity()->SetName(name);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RichTextStyleSheet, __GetProperties, "GetProperties")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_RichTextStyleSheet, __GetProperties)
{
	Object_wx_RichTextStyleSheet *pThis = Object_wx_RichTextStyleSheet::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxRichTextProperties& _rtn = pThis->GetEntity()->GetProperties();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RichTextStyleSheet, __GetProperties_1, "GetProperties_1")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_RichTextStyleSheet, __GetProperties_1)
{
	Object_wx_RichTextStyleSheet *pThis = Object_wx_RichTextStyleSheet::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxRichTextProperties& _rtn = pThis->GetEntity()->GetProperties();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RichTextStyleSheet, __SetProperties, "SetProperties")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "props", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_RichTextStyleSheet, __SetProperties)
{
	Object_wx_RichTextStyleSheet *pThis = Object_wx_RichTextStyleSheet::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxRichTextProperties& props = arg.GetNumber(0)
	//pThis->GetEntity()->SetProperties(props);
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Class implementation for wxRichTextStyleSheet
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_RichTextStyleSheet)
{
	// Constructor assignment
	Gura_AssignFunction(__RichTextStyleSheet);
	// Method assignment
	Gura_AssignMethod(wx_RichTextStyleSheet, __AddCharacterStyle);
	Gura_AssignMethod(wx_RichTextStyleSheet, __AddListStyle);
	Gura_AssignMethod(wx_RichTextStyleSheet, __AddParagraphStyle);
	Gura_AssignMethod(wx_RichTextStyleSheet, __AddStyle);
	Gura_AssignMethod(wx_RichTextStyleSheet, __DeleteStyles);
	Gura_AssignMethod(wx_RichTextStyleSheet, __FindCharacterStyle);
	Gura_AssignMethod(wx_RichTextStyleSheet, __FindListStyle);
	Gura_AssignMethod(wx_RichTextStyleSheet, __FindParagraphStyle);
	Gura_AssignMethod(wx_RichTextStyleSheet, __FindStyle);
	Gura_AssignMethod(wx_RichTextStyleSheet, __GetCharacterStyle);
	Gura_AssignMethod(wx_RichTextStyleSheet, __GetCharacterStyleCount);
	Gura_AssignMethod(wx_RichTextStyleSheet, __GetDescription);
	Gura_AssignMethod(wx_RichTextStyleSheet, __GetListStyle);
	Gura_AssignMethod(wx_RichTextStyleSheet, __GetListStyleCount);
	Gura_AssignMethod(wx_RichTextStyleSheet, __GetName);
	Gura_AssignMethod(wx_RichTextStyleSheet, __GetParagraphStyle);
	Gura_AssignMethod(wx_RichTextStyleSheet, __GetParagraphStyleCount);
	Gura_AssignMethod(wx_RichTextStyleSheet, __RemoveCharacterStyle);
	Gura_AssignMethod(wx_RichTextStyleSheet, __RemoveListStyle);
	Gura_AssignMethod(wx_RichTextStyleSheet, __RemoveParagraphStyle);
	Gura_AssignMethod(wx_RichTextStyleSheet, __RemoveStyle);
	Gura_AssignMethod(wx_RichTextStyleSheet, __SetDescription);
	Gura_AssignMethod(wx_RichTextStyleSheet, __SetName);
	Gura_AssignMethod(wx_RichTextStyleSheet, __GetProperties);
	Gura_AssignMethod(wx_RichTextStyleSheet, __GetProperties_1);
	Gura_AssignMethod(wx_RichTextStyleSheet, __SetProperties);
}

Gura_ImplementDescendantCreator(wx_RichTextStyleSheet)
{
	return new Object_wx_RichTextStyleSheet((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
