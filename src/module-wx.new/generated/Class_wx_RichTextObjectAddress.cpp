//----------------------------------------------------------------------------
// wxRichTextObjectAddress
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Gura interfaces for wxRichTextObjectAddress
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Object implementation for wxRichTextObjectAddress
//----------------------------------------------------------------------------
Object_wx_RichTextObjectAddress::~Object_wx_RichTextObjectAddress()
{
}

Object *Object_wx_RichTextObjectAddress::Clone() const
{
	return nullptr;
}

String Object_wx_RichTextObjectAddress::ToString(bool exprFlag)
{
	String rtn("<wx.RichTextObjectAddress:");
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
Gura_DeclareFunctionAlias(__RichTextObjectAddress, "RichTextObjectAddress")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "topLevelContainer", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "obj", VTYPE_number, OCCUR_Once);
	SetClassToConstruct(Gura_UserClass(wx_RichTextObjectAddress));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(__RichTextObjectAddress)
{
	//wxRichTextParagraphLayoutBox* topLevelContainer = arg.GetNumber(0)
	//wxRichTextObject* obj = arg.GetNumber(1)
	//wxRichTextObjectAddress(topLevelContainer, obj);
	return Value::Nil;
}

Gura_DeclareFunctionAlias(__RichTextObjectAddress_1, "RichTextObjectAddress_1")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	SetClassToConstruct(Gura_UserClass(wx_RichTextObjectAddress));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(__RichTextObjectAddress_1)
{
	//wxRichTextObjectAddress();
	return Value::Nil;
}

Gura_DeclareFunctionAlias(__RichTextObjectAddress_2, "RichTextObjectAddress_2")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "address", VTYPE_number, OCCUR_Once);
	SetClassToConstruct(Gura_UserClass(wx_RichTextObjectAddress));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(__RichTextObjectAddress_2)
{
	//const wxRichTextObjectAddress& address = arg.GetNumber(0)
	//wxRichTextObjectAddress(address);
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Method implementation
//----------------------------------------------------------------------------
Gura_DeclareMethodAlias(wx_RichTextObjectAddress, __Init, "Init")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_RichTextObjectAddress, __Init)
{
	Object_wx_RichTextObjectAddress *pThis = Object_wx_RichTextObjectAddress::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->Init();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RichTextObjectAddress, __Copy, "Copy")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "address", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_RichTextObjectAddress, __Copy)
{
	Object_wx_RichTextObjectAddress *pThis = Object_wx_RichTextObjectAddress::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxRichTextObjectAddress& address = arg.GetNumber(0)
	//pThis->GetEntity()->Copy(address);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RichTextObjectAddress, __GetObject, "GetObject")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "topLevelContainer", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_RichTextObjectAddress, __GetObject)
{
	Object_wx_RichTextObjectAddress *pThis = Object_wx_RichTextObjectAddress::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxRichTextParagraphLayoutBox* topLevelContainer = arg.GetNumber(0)
	//wxRichTextObject* _rtn = pThis->GetEntity()->GetObject(topLevelContainer);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RichTextObjectAddress, __Create, "Create")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "topLevelContainer", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "obj", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_RichTextObjectAddress, __Create)
{
	Object_wx_RichTextObjectAddress *pThis = Object_wx_RichTextObjectAddress::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxRichTextParagraphLayoutBox* topLevelContainer = arg.GetNumber(0)
	//wxRichTextObject* obj = arg.GetNumber(1)
	//bool _rtn = pThis->GetEntity()->Create(topLevelContainer, obj);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RichTextObjectAddress, __GetAddress, "GetAddress")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_RichTextObjectAddress, __GetAddress)
{
	Object_wx_RichTextObjectAddress *pThis = Object_wx_RichTextObjectAddress::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxArrayInt& _rtn = pThis->GetEntity()->GetAddress();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RichTextObjectAddress, __GetAddress_1, "GetAddress_1")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_RichTextObjectAddress, __GetAddress_1)
{
	Object_wx_RichTextObjectAddress *pThis = Object_wx_RichTextObjectAddress::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxArrayInt& _rtn = pThis->GetEntity()->GetAddress();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RichTextObjectAddress, __SetAddress, "SetAddress")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "address", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_RichTextObjectAddress, __SetAddress)
{
	Object_wx_RichTextObjectAddress *pThis = Object_wx_RichTextObjectAddress::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxArrayInt& address = arg.GetNumber(0)
	//pThis->GetEntity()->SetAddress(address);
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Class implementation for wxRichTextObjectAddress
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_RichTextObjectAddress)
{
	// Constructor assignment
	Gura_AssignFunction(__RichTextObjectAddress);
	Gura_AssignFunction(__RichTextObjectAddress_1);
	Gura_AssignFunction(__RichTextObjectAddress_2);
	// Method assignment
	Gura_AssignMethod(wx_RichTextObjectAddress, __Init);
	Gura_AssignMethod(wx_RichTextObjectAddress, __Copy);
	Gura_AssignMethod(wx_RichTextObjectAddress, __GetObject);
	Gura_AssignMethod(wx_RichTextObjectAddress, __Create);
	Gura_AssignMethod(wx_RichTextObjectAddress, __GetAddress);
	Gura_AssignMethod(wx_RichTextObjectAddress, __GetAddress_1);
	Gura_AssignMethod(wx_RichTextObjectAddress, __SetAddress);
}

Gura_ImplementDescendantCreator(wx_RichTextObjectAddress)
{
	return new Object_wx_RichTextObjectAddress((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
