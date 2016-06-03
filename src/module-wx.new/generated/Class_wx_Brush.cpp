//----------------------------------------------------------------------------
// wxBrush
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Gura interfaces for wxBrush
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Object implementation for wxBrush
//----------------------------------------------------------------------------
Object_wx_Brush::~Object_wx_Brush()
{
}

Object *Object_wx_Brush::Clone() const
{
	return nullptr;
}

String Object_wx_Brush::ToString(bool exprFlag)
{
	String rtn("<wx.Brush:");
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
Gura_DeclareFunctionAlias(__wxBrush, "wxBrush")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	SetClassToConstruct(Gura_UserClass(wx_Brush));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(__wxBrush)
{
	//wxBrush();
	return Value::Nil;
}

Gura_DeclareFunctionAlias(__wxBrush_1, "wxBrush_1")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "colour", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "style", VTYPE_number, OCCUR_Once);
	SetClassToConstruct(Gura_UserClass(wx_Brush));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(__wxBrush_1)
{
	//int colour = arg.GetNumber(0)
	//int style = arg.GetNumber(1)
	//wxBrush();
	return Value::Nil;
}

Gura_DeclareFunctionAlias(__wxBrush_2, "wxBrush_2")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "stippleBitmap", VTYPE_number, OCCUR_Once);
	SetClassToConstruct(Gura_UserClass(wx_Brush));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(__wxBrush_2)
{
	//int stippleBitmap = arg.GetNumber(0)
	//wxBrush();
	return Value::Nil;
}

Gura_DeclareFunctionAlias(__wxBrush_3, "wxBrush_3")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "brush", VTYPE_number, OCCUR_Once);
	SetClassToConstruct(Gura_UserClass(wx_Brush));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(__wxBrush_3)
{
	//int brush = arg.GetNumber(0)
	//wxBrush();
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Method implementation
//----------------------------------------------------------------------------
Gura_DeclareMethodAlias(wx_Brush, __GetColour, "GetColour")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_Brush, __GetColour)
{
	Object_wx_Brush *pThis = Object_wx_Brush::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->GetColour();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Brush, __GetStipple, "GetStipple")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_Brush, __GetStipple)
{
	Object_wx_Brush *pThis = Object_wx_Brush::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->GetStipple();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Brush, __GetStyle, "GetStyle")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_Brush, __GetStyle)
{
	Object_wx_Brush *pThis = Object_wx_Brush::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->GetStyle();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Brush, __IsHatch, "IsHatch")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_Brush, __IsHatch)
{
	Object_wx_Brush *pThis = Object_wx_Brush::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->IsHatch();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Brush, __IsOk, "IsOk")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_Brush, __IsOk)
{
	Object_wx_Brush *pThis = Object_wx_Brush::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->IsOk();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Brush, __IsNonTransparent, "IsNonTransparent")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_Brush, __IsNonTransparent)
{
	Object_wx_Brush *pThis = Object_wx_Brush::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->IsNonTransparent();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Brush, __IsTransparent, "IsTransparent")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_Brush, __IsTransparent)
{
	Object_wx_Brush *pThis = Object_wx_Brush::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->IsTransparent();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Brush, __SetColour, "SetColour")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "colour", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Brush, __SetColour)
{
	Object_wx_Brush *pThis = Object_wx_Brush::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int colour = arg.GetNumber(0)
	//pThis->GetEntity()->SetColour();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Brush, __SetColour_1, "SetColour_1")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "red", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "green", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "blue", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Brush, __SetColour_1)
{
	Object_wx_Brush *pThis = Object_wx_Brush::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int red = arg.GetNumber(0)
	//int green = arg.GetNumber(1)
	//int blue = arg.GetNumber(2)
	//pThis->GetEntity()->SetColour();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Brush, __SetStipple, "SetStipple")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "bitmap", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Brush, __SetStipple)
{
	Object_wx_Brush *pThis = Object_wx_Brush::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int bitmap = arg.GetNumber(0)
	//pThis->GetEntity()->SetStipple();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Brush, __SetStyle, "SetStyle")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "style", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Brush, __SetStyle)
{
	Object_wx_Brush *pThis = Object_wx_Brush::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int style = arg.GetNumber(0)
	//pThis->GetEntity()->SetStyle();
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Class implementation for wxBrush
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_Brush)
{
	// Constructor assignment
	Gura_AssignFunction(__wxBrush);
	Gura_AssignFunction(__wxBrush_1);
	Gura_AssignFunction(__wxBrush_2);
	Gura_AssignFunction(__wxBrush_3);
	// Method assignment
	Gura_AssignMethod(wx_Brush, __GetColour);
	Gura_AssignMethod(wx_Brush, __GetStipple);
	Gura_AssignMethod(wx_Brush, __GetStyle);
	Gura_AssignMethod(wx_Brush, __IsHatch);
	Gura_AssignMethod(wx_Brush, __IsOk);
	Gura_AssignMethod(wx_Brush, __IsNonTransparent);
	Gura_AssignMethod(wx_Brush, __IsTransparent);
	Gura_AssignMethod(wx_Brush, __SetColour);
	Gura_AssignMethod(wx_Brush, __SetColour_1);
	Gura_AssignMethod(wx_Brush, __SetStipple);
	Gura_AssignMethod(wx_Brush, __SetStyle);
}

Gura_ImplementDescendantCreator(wx_Brush)
{
	return new Object_wx_Brush((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
