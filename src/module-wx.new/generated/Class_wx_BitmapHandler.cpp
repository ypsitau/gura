//----------------------------------------------------------------------------
// wxBitmapHandler
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Gura interfaces for wxBitmapHandler
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Object implementation for wxBitmapHandler
//----------------------------------------------------------------------------
Object_wx_BitmapHandler::~Object_wx_BitmapHandler()
{
}

Object *Object_wx_BitmapHandler::Clone() const
{
	return nullptr;
}

String Object_wx_BitmapHandler::ToString(bool exprFlag)
{
	String rtn("<wx.BitmapHandler:");
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
Gura_DeclareFunctionAlias(__wxBitmapHandler, "wxBitmapHandler")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	SetClassToConstruct(Gura_UserClass(wx_BitmapHandler));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(__wxBitmapHandler)
{
	//wxBitmapHandler();
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Method implementation
//----------------------------------------------------------------------------
Gura_DeclareMethodAlias(wx_BitmapHandler, __Create, "Create")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "bitmap", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "data", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "type", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "width", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "height", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "depth", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_BitmapHandler, __Create)
{
	Object_wx_BitmapHandler *pThis = Object_wx_BitmapHandler::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int bitmap = arg.GetNumber(0)
	//int data = arg.GetNumber(1)
	//int type = arg.GetNumber(2)
	//int width = arg.GetNumber(3)
	//int height = arg.GetNumber(4)
	//int depth = arg.GetNumber(5)
	//pThis->GetEntity()->Create();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_BitmapHandler, __GetExtension, "GetExtension")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_BitmapHandler, __GetExtension)
{
	Object_wx_BitmapHandler *pThis = Object_wx_BitmapHandler::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->GetExtension();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_BitmapHandler, __GetName, "GetName")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_BitmapHandler, __GetName)
{
	Object_wx_BitmapHandler *pThis = Object_wx_BitmapHandler::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->GetName();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_BitmapHandler, __GetType, "GetType")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_BitmapHandler, __GetType)
{
	Object_wx_BitmapHandler *pThis = Object_wx_BitmapHandler::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->GetType();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_BitmapHandler, __LoadFile, "LoadFile")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "bitmap", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "name", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "type", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "desiredWidth", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "desiredHeight", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_BitmapHandler, __LoadFile)
{
	Object_wx_BitmapHandler *pThis = Object_wx_BitmapHandler::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int bitmap = arg.GetNumber(0)
	//int name = arg.GetNumber(1)
	//int type = arg.GetNumber(2)
	//int desiredWidth = arg.GetNumber(3)
	//int desiredHeight = arg.GetNumber(4)
	//pThis->GetEntity()->LoadFile();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_BitmapHandler, __SaveFile, "SaveFile")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "bitmap", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "name", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "type", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "palette", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_BitmapHandler, __SaveFile)
{
	Object_wx_BitmapHandler *pThis = Object_wx_BitmapHandler::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int bitmap = arg.GetNumber(0)
	//int name = arg.GetNumber(1)
	//int type = arg.GetNumber(2)
	//int palette = arg.GetNumber(3)
	//pThis->GetEntity()->SaveFile();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_BitmapHandler, __SetExtension, "SetExtension")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "extension", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_BitmapHandler, __SetExtension)
{
	Object_wx_BitmapHandler *pThis = Object_wx_BitmapHandler::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int extension = arg.GetNumber(0)
	//pThis->GetEntity()->SetExtension();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_BitmapHandler, __SetName, "SetName")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "name", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_BitmapHandler, __SetName)
{
	Object_wx_BitmapHandler *pThis = Object_wx_BitmapHandler::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int name = arg.GetNumber(0)
	//pThis->GetEntity()->SetName();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_BitmapHandler, __SetType, "SetType")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "type", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_BitmapHandler, __SetType)
{
	Object_wx_BitmapHandler *pThis = Object_wx_BitmapHandler::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int type = arg.GetNumber(0)
	//pThis->GetEntity()->SetType();
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Class implementation for wxBitmapHandler
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_BitmapHandler)
{
	// Constructor assignment
	Gura_AssignFunction(__wxBitmapHandler);
	// Method assignment
	Gura_AssignMethod(wx_BitmapHandler, __Create);
	Gura_AssignMethod(wx_BitmapHandler, __GetExtension);
	Gura_AssignMethod(wx_BitmapHandler, __GetName);
	Gura_AssignMethod(wx_BitmapHandler, __GetType);
	Gura_AssignMethod(wx_BitmapHandler, __LoadFile);
	Gura_AssignMethod(wx_BitmapHandler, __SaveFile);
	Gura_AssignMethod(wx_BitmapHandler, __SetExtension);
	Gura_AssignMethod(wx_BitmapHandler, __SetName);
	Gura_AssignMethod(wx_BitmapHandler, __SetType);
}

Gura_ImplementDescendantCreator(wx_BitmapHandler)
{
	return new Object_wx_BitmapHandler((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
