//----------------------------------------------------------------------------
// wxGridRangeSelectEvent
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Gura interfaces for wxGridRangeSelectEvent
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Object implementation for wxGridRangeSelectEvent
//----------------------------------------------------------------------------
Object_wx_GridRangeSelectEvent::~Object_wx_GridRangeSelectEvent()
{
}

Object *Object_wx_GridRangeSelectEvent::Clone() const
{
	return nullptr;
}

String Object_wx_GridRangeSelectEvent::ToString(bool exprFlag)
{
	String rtn("<wx.GridRangeSelectEvent:");
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
Gura_DeclareFunctionAlias(__GridRangeSelectEvent, "GridRangeSelectEvent")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	SetClassToConstruct(Gura_UserClass(wx_GridRangeSelectEvent));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(__GridRangeSelectEvent)
{
	//wxGridRangeSelectEvent();
	return Value::Nil;
}

Gura_DeclareFunctionAlias(__GridRangeSelectEvent_1, "GridRangeSelectEvent_1")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "id", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "type", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "obj", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "topLeft", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "bottomRight", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "sel", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "kbd", VTYPE_number, OCCUR_Once);
	SetClassToConstruct(Gura_UserClass(wx_GridRangeSelectEvent));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(__GridRangeSelectEvent_1)
{
	//int id = arg.GetNumber(0)
	//wxEventType type = arg.GetNumber(1)
	//wxObject* obj = arg.GetNumber(2)
	//const wxGridCellCoords& topLeft = arg.GetNumber(3)
	//const wxGridCellCoords& bottomRight = arg.GetNumber(4)
	//bool sel = arg.GetNumber(5)
	//const wxKeyboardState& kbd = arg.GetNumber(6)
	//wxGridRangeSelectEvent(id, type, obj, topLeft, bottomRight, sel, kbd);
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Method implementation
//----------------------------------------------------------------------------
Gura_DeclareMethodAlias(wx_GridRangeSelectEvent, __AltDown, "AltDown")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_GridRangeSelectEvent, __AltDown)
{
	Object_wx_GridRangeSelectEvent *pThis = Object_wx_GridRangeSelectEvent::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//bool _rtn = pThis->GetEntity()->AltDown();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_GridRangeSelectEvent, __ControlDown, "ControlDown")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_GridRangeSelectEvent, __ControlDown)
{
	Object_wx_GridRangeSelectEvent *pThis = Object_wx_GridRangeSelectEvent::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//bool _rtn = pThis->GetEntity()->ControlDown();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_GridRangeSelectEvent, __GetBottomRightCoords, "GetBottomRightCoords")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_GridRangeSelectEvent, __GetBottomRightCoords)
{
	Object_wx_GridRangeSelectEvent *pThis = Object_wx_GridRangeSelectEvent::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxGridCellCoords _rtn = pThis->GetEntity()->GetBottomRightCoords();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_GridRangeSelectEvent, __GetBottomRow, "GetBottomRow")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_GridRangeSelectEvent, __GetBottomRow)
{
	Object_wx_GridRangeSelectEvent *pThis = Object_wx_GridRangeSelectEvent::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int _rtn = pThis->GetEntity()->GetBottomRow();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_GridRangeSelectEvent, __GetLeftCol, "GetLeftCol")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_GridRangeSelectEvent, __GetLeftCol)
{
	Object_wx_GridRangeSelectEvent *pThis = Object_wx_GridRangeSelectEvent::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int _rtn = pThis->GetEntity()->GetLeftCol();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_GridRangeSelectEvent, __GetRightCol, "GetRightCol")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_GridRangeSelectEvent, __GetRightCol)
{
	Object_wx_GridRangeSelectEvent *pThis = Object_wx_GridRangeSelectEvent::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int _rtn = pThis->GetEntity()->GetRightCol();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_GridRangeSelectEvent, __GetTopLeftCoords, "GetTopLeftCoords")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_GridRangeSelectEvent, __GetTopLeftCoords)
{
	Object_wx_GridRangeSelectEvent *pThis = Object_wx_GridRangeSelectEvent::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxGridCellCoords _rtn = pThis->GetEntity()->GetTopLeftCoords();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_GridRangeSelectEvent, __GetTopRow, "GetTopRow")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_GridRangeSelectEvent, __GetTopRow)
{
	Object_wx_GridRangeSelectEvent *pThis = Object_wx_GridRangeSelectEvent::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int _rtn = pThis->GetEntity()->GetTopRow();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_GridRangeSelectEvent, __MetaDown, "MetaDown")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_GridRangeSelectEvent, __MetaDown)
{
	Object_wx_GridRangeSelectEvent *pThis = Object_wx_GridRangeSelectEvent::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//bool _rtn = pThis->GetEntity()->MetaDown();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_GridRangeSelectEvent, __Selecting, "Selecting")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_GridRangeSelectEvent, __Selecting)
{
	Object_wx_GridRangeSelectEvent *pThis = Object_wx_GridRangeSelectEvent::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//bool _rtn = pThis->GetEntity()->Selecting();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_GridRangeSelectEvent, __ShiftDown, "ShiftDown")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_GridRangeSelectEvent, __ShiftDown)
{
	Object_wx_GridRangeSelectEvent *pThis = Object_wx_GridRangeSelectEvent::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//bool _rtn = pThis->GetEntity()->ShiftDown();
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Class implementation for wxGridRangeSelectEvent
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_GridRangeSelectEvent)
{
	// Constructor assignment
	Gura_AssignFunction(__GridRangeSelectEvent);
	Gura_AssignFunction(__GridRangeSelectEvent_1);
	// Method assignment
	Gura_AssignMethod(wx_GridRangeSelectEvent, __AltDown);
	Gura_AssignMethod(wx_GridRangeSelectEvent, __ControlDown);
	Gura_AssignMethod(wx_GridRangeSelectEvent, __GetBottomRightCoords);
	Gura_AssignMethod(wx_GridRangeSelectEvent, __GetBottomRow);
	Gura_AssignMethod(wx_GridRangeSelectEvent, __GetLeftCol);
	Gura_AssignMethod(wx_GridRangeSelectEvent, __GetRightCol);
	Gura_AssignMethod(wx_GridRangeSelectEvent, __GetTopLeftCoords);
	Gura_AssignMethod(wx_GridRangeSelectEvent, __GetTopRow);
	Gura_AssignMethod(wx_GridRangeSelectEvent, __MetaDown);
	Gura_AssignMethod(wx_GridRangeSelectEvent, __Selecting);
	Gura_AssignMethod(wx_GridRangeSelectEvent, __ShiftDown);
}

Gura_ImplementDescendantCreator(wx_GridRangeSelectEvent)
{
	return new Object_wx_GridRangeSelectEvent((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
