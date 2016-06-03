//----------------------------------------------------------------------------
// wxRect2DDouble
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Gura interfaces for wxRect2DDouble
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Object implementation for wxRect2DDouble
//----------------------------------------------------------------------------
Object_wx_Rect2DDouble::~Object_wx_Rect2DDouble()
{
}

Object *Object_wx_Rect2DDouble::Clone() const
{
	return nullptr;
}

String Object_wx_Rect2DDouble::ToString(bool exprFlag)
{
	String rtn("<wx.Rect2DDouble:");
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
Gura_DeclareFunctionAlias(__wxRect2DDouble, "wxRect2DDouble")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	SetClassToConstruct(Gura_UserClass(wx_Rect2DDouble));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(__wxRect2DDouble)
{
	//wxRect2DDouble();
	return Value::Nil;
}

Gura_DeclareFunctionAlias(__wxRect2DDouble_1, "wxRect2DDouble_1")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "x", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "y", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "w", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "h", VTYPE_number, OCCUR_Once);
	SetClassToConstruct(Gura_UserClass(wx_Rect2DDouble));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(__wxRect2DDouble_1)
{
	//int x = arg.GetNumber(0)
	//int y = arg.GetNumber(1)
	//int w = arg.GetNumber(2)
	//int h = arg.GetNumber(3)
	//wxRect2DDouble();
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Method implementation
//----------------------------------------------------------------------------
Gura_DeclareMethodAlias(wx_Rect2DDouble, __GetPosition, "GetPosition")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_Rect2DDouble, __GetPosition)
{
	Object_wx_Rect2DDouble *pThis = Object_wx_Rect2DDouble::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->GetPosition();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Rect2DDouble, __GetSize, "GetSize")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_Rect2DDouble, __GetSize)
{
	Object_wx_Rect2DDouble *pThis = Object_wx_Rect2DDouble::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->GetSize();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Rect2DDouble, __GetLeft, "GetLeft")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_Rect2DDouble, __GetLeft)
{
	Object_wx_Rect2DDouble *pThis = Object_wx_Rect2DDouble::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->GetLeft();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Rect2DDouble, __SetLeft, "SetLeft")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "n", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Rect2DDouble, __SetLeft)
{
	Object_wx_Rect2DDouble *pThis = Object_wx_Rect2DDouble::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int n = arg.GetNumber(0)
	//pThis->GetEntity()->SetLeft();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Rect2DDouble, __MoveLeftTo, "MoveLeftTo")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "n", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Rect2DDouble, __MoveLeftTo)
{
	Object_wx_Rect2DDouble *pThis = Object_wx_Rect2DDouble::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int n = arg.GetNumber(0)
	//pThis->GetEntity()->MoveLeftTo();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Rect2DDouble, __GetTop, "GetTop")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_Rect2DDouble, __GetTop)
{
	Object_wx_Rect2DDouble *pThis = Object_wx_Rect2DDouble::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->GetTop();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Rect2DDouble, __SetTop, "SetTop")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "n", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Rect2DDouble, __SetTop)
{
	Object_wx_Rect2DDouble *pThis = Object_wx_Rect2DDouble::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int n = arg.GetNumber(0)
	//pThis->GetEntity()->SetTop();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Rect2DDouble, __MoveTopTo, "MoveTopTo")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "n", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Rect2DDouble, __MoveTopTo)
{
	Object_wx_Rect2DDouble *pThis = Object_wx_Rect2DDouble::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int n = arg.GetNumber(0)
	//pThis->GetEntity()->MoveTopTo();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Rect2DDouble, __GetBottom, "GetBottom")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_Rect2DDouble, __GetBottom)
{
	Object_wx_Rect2DDouble *pThis = Object_wx_Rect2DDouble::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->GetBottom();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Rect2DDouble, __SetBottom, "SetBottom")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "n", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Rect2DDouble, __SetBottom)
{
	Object_wx_Rect2DDouble *pThis = Object_wx_Rect2DDouble::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int n = arg.GetNumber(0)
	//pThis->GetEntity()->SetBottom();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Rect2DDouble, __MoveBottomTo, "MoveBottomTo")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "n", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Rect2DDouble, __MoveBottomTo)
{
	Object_wx_Rect2DDouble *pThis = Object_wx_Rect2DDouble::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int n = arg.GetNumber(0)
	//pThis->GetEntity()->MoveBottomTo();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Rect2DDouble, __GetRight, "GetRight")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_Rect2DDouble, __GetRight)
{
	Object_wx_Rect2DDouble *pThis = Object_wx_Rect2DDouble::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->GetRight();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Rect2DDouble, __SetRight, "SetRight")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "n", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Rect2DDouble, __SetRight)
{
	Object_wx_Rect2DDouble *pThis = Object_wx_Rect2DDouble::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int n = arg.GetNumber(0)
	//pThis->GetEntity()->SetRight();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Rect2DDouble, __MoveRightTo, "MoveRightTo")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "n", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Rect2DDouble, __MoveRightTo)
{
	Object_wx_Rect2DDouble *pThis = Object_wx_Rect2DDouble::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int n = arg.GetNumber(0)
	//pThis->GetEntity()->MoveRightTo();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Rect2DDouble, __GetLeftTop, "GetLeftTop")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_Rect2DDouble, __GetLeftTop)
{
	Object_wx_Rect2DDouble *pThis = Object_wx_Rect2DDouble::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->GetLeftTop();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Rect2DDouble, __SetLeftTop, "SetLeftTop")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "pt", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Rect2DDouble, __SetLeftTop)
{
	Object_wx_Rect2DDouble *pThis = Object_wx_Rect2DDouble::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int pt = arg.GetNumber(0)
	//pThis->GetEntity()->SetLeftTop();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Rect2DDouble, __MoveLeftTopTo, "MoveLeftTopTo")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "pt", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Rect2DDouble, __MoveLeftTopTo)
{
	Object_wx_Rect2DDouble *pThis = Object_wx_Rect2DDouble::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int pt = arg.GetNumber(0)
	//pThis->GetEntity()->MoveLeftTopTo();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Rect2DDouble, __GetLeftBottom, "GetLeftBottom")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_Rect2DDouble, __GetLeftBottom)
{
	Object_wx_Rect2DDouble *pThis = Object_wx_Rect2DDouble::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->GetLeftBottom();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Rect2DDouble, __SetLeftBottom, "SetLeftBottom")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "pt", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Rect2DDouble, __SetLeftBottom)
{
	Object_wx_Rect2DDouble *pThis = Object_wx_Rect2DDouble::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int pt = arg.GetNumber(0)
	//pThis->GetEntity()->SetLeftBottom();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Rect2DDouble, __MoveLeftBottomTo, "MoveLeftBottomTo")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "pt", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Rect2DDouble, __MoveLeftBottomTo)
{
	Object_wx_Rect2DDouble *pThis = Object_wx_Rect2DDouble::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int pt = arg.GetNumber(0)
	//pThis->GetEntity()->MoveLeftBottomTo();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Rect2DDouble, __GetRightTop, "GetRightTop")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_Rect2DDouble, __GetRightTop)
{
	Object_wx_Rect2DDouble *pThis = Object_wx_Rect2DDouble::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->GetRightTop();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Rect2DDouble, __SetRightTop, "SetRightTop")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "pt", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Rect2DDouble, __SetRightTop)
{
	Object_wx_Rect2DDouble *pThis = Object_wx_Rect2DDouble::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int pt = arg.GetNumber(0)
	//pThis->GetEntity()->SetRightTop();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Rect2DDouble, __MoveRightTopTo, "MoveRightTopTo")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "pt", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Rect2DDouble, __MoveRightTopTo)
{
	Object_wx_Rect2DDouble *pThis = Object_wx_Rect2DDouble::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int pt = arg.GetNumber(0)
	//pThis->GetEntity()->MoveRightTopTo();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Rect2DDouble, __GetRightBottom, "GetRightBottom")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_Rect2DDouble, __GetRightBottom)
{
	Object_wx_Rect2DDouble *pThis = Object_wx_Rect2DDouble::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->GetRightBottom();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Rect2DDouble, __SetRightBottom, "SetRightBottom")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "pt", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Rect2DDouble, __SetRightBottom)
{
	Object_wx_Rect2DDouble *pThis = Object_wx_Rect2DDouble::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int pt = arg.GetNumber(0)
	//pThis->GetEntity()->SetRightBottom();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Rect2DDouble, __MoveRightBottomTo, "MoveRightBottomTo")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "pt", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Rect2DDouble, __MoveRightBottomTo)
{
	Object_wx_Rect2DDouble *pThis = Object_wx_Rect2DDouble::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int pt = arg.GetNumber(0)
	//pThis->GetEntity()->MoveRightBottomTo();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Rect2DDouble, __GetCentre, "GetCentre")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_Rect2DDouble, __GetCentre)
{
	Object_wx_Rect2DDouble *pThis = Object_wx_Rect2DDouble::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->GetCentre();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Rect2DDouble, __SetCentre, "SetCentre")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "pt", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Rect2DDouble, __SetCentre)
{
	Object_wx_Rect2DDouble *pThis = Object_wx_Rect2DDouble::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int pt = arg.GetNumber(0)
	//pThis->GetEntity()->SetCentre();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Rect2DDouble, __MoveCentreTo, "MoveCentreTo")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "pt", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Rect2DDouble, __MoveCentreTo)
{
	Object_wx_Rect2DDouble *pThis = Object_wx_Rect2DDouble::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int pt = arg.GetNumber(0)
	//pThis->GetEntity()->MoveCentreTo();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Rect2DDouble, __GetOutCode, "GetOutCode")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "pt", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Rect2DDouble, __GetOutCode)
{
	Object_wx_Rect2DDouble *pThis = Object_wx_Rect2DDouble::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int pt = arg.GetNumber(0)
	//pThis->GetEntity()->GetOutCode();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Rect2DDouble, __GetOutcode, "GetOutcode")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "pt", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Rect2DDouble, __GetOutcode)
{
	Object_wx_Rect2DDouble *pThis = Object_wx_Rect2DDouble::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int pt = arg.GetNumber(0)
	//pThis->GetEntity()->GetOutcode();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Rect2DDouble, __Contains, "Contains")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "pt", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Rect2DDouble, __Contains)
{
	Object_wx_Rect2DDouble *pThis = Object_wx_Rect2DDouble::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int pt = arg.GetNumber(0)
	//pThis->GetEntity()->Contains();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Rect2DDouble, __Contains_1, "Contains_1")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "rect", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Rect2DDouble, __Contains_1)
{
	Object_wx_Rect2DDouble *pThis = Object_wx_Rect2DDouble::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int rect = arg.GetNumber(0)
	//pThis->GetEntity()->Contains();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Rect2DDouble, __IsEmpty, "IsEmpty")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_Rect2DDouble, __IsEmpty)
{
	Object_wx_Rect2DDouble *pThis = Object_wx_Rect2DDouble::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->IsEmpty();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Rect2DDouble, __HaveEqualSize, "HaveEqualSize")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "rect", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Rect2DDouble, __HaveEqualSize)
{
	Object_wx_Rect2DDouble *pThis = Object_wx_Rect2DDouble::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int rect = arg.GetNumber(0)
	//pThis->GetEntity()->HaveEqualSize();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Rect2DDouble, __Inset, "Inset")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "x", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "y", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Rect2DDouble, __Inset)
{
	Object_wx_Rect2DDouble *pThis = Object_wx_Rect2DDouble::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int x = arg.GetNumber(0)
	//int y = arg.GetNumber(1)
	//pThis->GetEntity()->Inset();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Rect2DDouble, __Inset_1, "Inset_1")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "left", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "top", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "right", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "bottom", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Rect2DDouble, __Inset_1)
{
	Object_wx_Rect2DDouble *pThis = Object_wx_Rect2DDouble::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int left = arg.GetNumber(0)
	//int top = arg.GetNumber(1)
	//int right = arg.GetNumber(2)
	//int bottom = arg.GetNumber(3)
	//pThis->GetEntity()->Inset();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Rect2DDouble, __Offset, "Offset")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "pt", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Rect2DDouble, __Offset)
{
	Object_wx_Rect2DDouble *pThis = Object_wx_Rect2DDouble::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int pt = arg.GetNumber(0)
	//pThis->GetEntity()->Offset();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Rect2DDouble, __ConstrainTo, "ConstrainTo")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "rect", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Rect2DDouble, __ConstrainTo)
{
	Object_wx_Rect2DDouble *pThis = Object_wx_Rect2DDouble::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int rect = arg.GetNumber(0)
	//pThis->GetEntity()->ConstrainTo();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Rect2DDouble, __Interpolate, "Interpolate")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "widthfactor", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "heightfactor", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Rect2DDouble, __Interpolate)
{
	Object_wx_Rect2DDouble *pThis = Object_wx_Rect2DDouble::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int widthfactor = arg.GetNumber(0)
	//int heightfactor = arg.GetNumber(1)
	//pThis->GetEntity()->Interpolate();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Rect2DDouble, __Intersect, "Intersect")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "src1", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "src2", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "dest", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Rect2DDouble, __Intersect)
{
	Object_wx_Rect2DDouble *pThis = Object_wx_Rect2DDouble::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int src1 = arg.GetNumber(0)
	//int src2 = arg.GetNumber(1)
	//int dest = arg.GetNumber(2)
	//pThis->GetEntity()->Intersect();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Rect2DDouble, __Intersect_1, "Intersect_1")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "otherRect", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Rect2DDouble, __Intersect_1)
{
	Object_wx_Rect2DDouble *pThis = Object_wx_Rect2DDouble::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int otherRect = arg.GetNumber(0)
	//pThis->GetEntity()->Intersect();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Rect2DDouble, __CreateIntersection, "CreateIntersection")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "otherRect", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Rect2DDouble, __CreateIntersection)
{
	Object_wx_Rect2DDouble *pThis = Object_wx_Rect2DDouble::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int otherRect = arg.GetNumber(0)
	//pThis->GetEntity()->CreateIntersection();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Rect2DDouble, __Intersects, "Intersects")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "rect", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Rect2DDouble, __Intersects)
{
	Object_wx_Rect2DDouble *pThis = Object_wx_Rect2DDouble::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int rect = arg.GetNumber(0)
	//pThis->GetEntity()->Intersects();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Rect2DDouble, __Union, "Union")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "src1", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "src2", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "dest", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Rect2DDouble, __Union)
{
	Object_wx_Rect2DDouble *pThis = Object_wx_Rect2DDouble::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int src1 = arg.GetNumber(0)
	//int src2 = arg.GetNumber(1)
	//int dest = arg.GetNumber(2)
	//pThis->GetEntity()->Union();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Rect2DDouble, __Union_1, "Union_1")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "otherRect", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Rect2DDouble, __Union_1)
{
	Object_wx_Rect2DDouble *pThis = Object_wx_Rect2DDouble::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int otherRect = arg.GetNumber(0)
	//pThis->GetEntity()->Union();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Rect2DDouble, __Union_2, "Union_2")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "pt", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Rect2DDouble, __Union_2)
{
	Object_wx_Rect2DDouble *pThis = Object_wx_Rect2DDouble::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int pt = arg.GetNumber(0)
	//pThis->GetEntity()->Union();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Rect2DDouble, __CreateUnion, "CreateUnion")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "otherRect", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Rect2DDouble, __CreateUnion)
{
	Object_wx_Rect2DDouble *pThis = Object_wx_Rect2DDouble::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int otherRect = arg.GetNumber(0)
	//pThis->GetEntity()->CreateUnion();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Rect2DDouble, __Scale, "Scale")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "f", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Rect2DDouble, __Scale)
{
	Object_wx_Rect2DDouble *pThis = Object_wx_Rect2DDouble::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int f = arg.GetNumber(0)
	//pThis->GetEntity()->Scale();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Rect2DDouble, __Scale_1, "Scale_1")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "num", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "denum", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Rect2DDouble, __Scale_1)
{
	Object_wx_Rect2DDouble *pThis = Object_wx_Rect2DDouble::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int num = arg.GetNumber(0)
	//int denum = arg.GetNumber(1)
	//pThis->GetEntity()->Scale();
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Class implementation for wxRect2DDouble
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_Rect2DDouble)
{
	// Constructor assignment
	Gura_AssignFunction(__wxRect2DDouble);
	Gura_AssignFunction(__wxRect2DDouble_1);
	// Method assignment
	Gura_AssignMethod(wx_Rect2DDouble, __GetPosition);
	Gura_AssignMethod(wx_Rect2DDouble, __GetSize);
	Gura_AssignMethod(wx_Rect2DDouble, __GetLeft);
	Gura_AssignMethod(wx_Rect2DDouble, __SetLeft);
	Gura_AssignMethod(wx_Rect2DDouble, __MoveLeftTo);
	Gura_AssignMethod(wx_Rect2DDouble, __GetTop);
	Gura_AssignMethod(wx_Rect2DDouble, __SetTop);
	Gura_AssignMethod(wx_Rect2DDouble, __MoveTopTo);
	Gura_AssignMethod(wx_Rect2DDouble, __GetBottom);
	Gura_AssignMethod(wx_Rect2DDouble, __SetBottom);
	Gura_AssignMethod(wx_Rect2DDouble, __MoveBottomTo);
	Gura_AssignMethod(wx_Rect2DDouble, __GetRight);
	Gura_AssignMethod(wx_Rect2DDouble, __SetRight);
	Gura_AssignMethod(wx_Rect2DDouble, __MoveRightTo);
	Gura_AssignMethod(wx_Rect2DDouble, __GetLeftTop);
	Gura_AssignMethod(wx_Rect2DDouble, __SetLeftTop);
	Gura_AssignMethod(wx_Rect2DDouble, __MoveLeftTopTo);
	Gura_AssignMethod(wx_Rect2DDouble, __GetLeftBottom);
	Gura_AssignMethod(wx_Rect2DDouble, __SetLeftBottom);
	Gura_AssignMethod(wx_Rect2DDouble, __MoveLeftBottomTo);
	Gura_AssignMethod(wx_Rect2DDouble, __GetRightTop);
	Gura_AssignMethod(wx_Rect2DDouble, __SetRightTop);
	Gura_AssignMethod(wx_Rect2DDouble, __MoveRightTopTo);
	Gura_AssignMethod(wx_Rect2DDouble, __GetRightBottom);
	Gura_AssignMethod(wx_Rect2DDouble, __SetRightBottom);
	Gura_AssignMethod(wx_Rect2DDouble, __MoveRightBottomTo);
	Gura_AssignMethod(wx_Rect2DDouble, __GetCentre);
	Gura_AssignMethod(wx_Rect2DDouble, __SetCentre);
	Gura_AssignMethod(wx_Rect2DDouble, __MoveCentreTo);
	Gura_AssignMethod(wx_Rect2DDouble, __GetOutCode);
	Gura_AssignMethod(wx_Rect2DDouble, __GetOutcode);
	Gura_AssignMethod(wx_Rect2DDouble, __Contains);
	Gura_AssignMethod(wx_Rect2DDouble, __Contains_1);
	Gura_AssignMethod(wx_Rect2DDouble, __IsEmpty);
	Gura_AssignMethod(wx_Rect2DDouble, __HaveEqualSize);
	Gura_AssignMethod(wx_Rect2DDouble, __Inset);
	Gura_AssignMethod(wx_Rect2DDouble, __Inset_1);
	Gura_AssignMethod(wx_Rect2DDouble, __Offset);
	Gura_AssignMethod(wx_Rect2DDouble, __ConstrainTo);
	Gura_AssignMethod(wx_Rect2DDouble, __Interpolate);
	Gura_AssignMethod(wx_Rect2DDouble, __Intersect);
	Gura_AssignMethod(wx_Rect2DDouble, __Intersect_1);
	Gura_AssignMethod(wx_Rect2DDouble, __CreateIntersection);
	Gura_AssignMethod(wx_Rect2DDouble, __Intersects);
	Gura_AssignMethod(wx_Rect2DDouble, __Union);
	Gura_AssignMethod(wx_Rect2DDouble, __Union_1);
	Gura_AssignMethod(wx_Rect2DDouble, __Union_2);
	Gura_AssignMethod(wx_Rect2DDouble, __CreateUnion);
	Gura_AssignMethod(wx_Rect2DDouble, __Scale);
	Gura_AssignMethod(wx_Rect2DDouble, __Scale_1);
}

Gura_ImplementDescendantCreator(wx_Rect2DDouble)
{
	return new Object_wx_Rect2DDouble((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
