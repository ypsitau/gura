//----------------------------------------------------------------------------
// wxVarHVScrollHelper
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Gura interfaces for wxVarHVScrollHelper
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Object implementation for wxVarHVScrollHelper
//----------------------------------------------------------------------------
Object_wx_VarHVScrollHelper::~Object_wx_VarHVScrollHelper()
{
}

Object *Object_wx_VarHVScrollHelper::Clone() const
{
	return nullptr;
}

String Object_wx_VarHVScrollHelper::ToString(bool exprFlag)
{
	String rtn("<wx.VarHVScrollHelper:");
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
Gura_DeclareFunctionAlias(__VarHVScrollHelper, "VarHVScrollHelper")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "winToScroll", VTYPE_number, OCCUR_Once);
	SetClassToConstruct(Gura_UserClass(wx_VarHVScrollHelper));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(__VarHVScrollHelper)
{
	//wxWindow* winToScroll = arg.GetNumber(0)
	//wxVarHVScrollHelper(winToScroll);
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Method implementation
//----------------------------------------------------------------------------
Gura_DeclareMethodAlias(wx_VarHVScrollHelper, __EnablePhysicalScrolling, "EnablePhysicalScrolling")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "vscrolling", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "hscrolling", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_VarHVScrollHelper, __EnablePhysicalScrolling)
{
	Object_wx_VarHVScrollHelper *pThis = Object_wx_VarHVScrollHelper::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//bool vscrolling = arg.GetNumber(0)
	//bool hscrolling = arg.GetNumber(1)
	//pThis->GetEntity()->EnablePhysicalScrolling(vscrolling, hscrolling);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_VarHVScrollHelper, __GetRowColumnCount, "GetRowColumnCount")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_VarHVScrollHelper, __GetRowColumnCount)
{
	Object_wx_VarHVScrollHelper *pThis = Object_wx_VarHVScrollHelper::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxSize _rtn = pThis->GetEntity()->GetRowColumnCount();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_VarHVScrollHelper, __GetVisibleBegin, "GetVisibleBegin")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_VarHVScrollHelper, __GetVisibleBegin)
{
	Object_wx_VarHVScrollHelper *pThis = Object_wx_VarHVScrollHelper::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxPosition _rtn = pThis->GetEntity()->GetVisibleBegin();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_VarHVScrollHelper, __GetVisibleEnd, "GetVisibleEnd")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_VarHVScrollHelper, __GetVisibleEnd)
{
	Object_wx_VarHVScrollHelper *pThis = Object_wx_VarHVScrollHelper::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxPosition _rtn = pThis->GetEntity()->GetVisibleEnd();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_VarHVScrollHelper, __IsVisible, "IsVisible")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "row", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "column", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_VarHVScrollHelper, __IsVisible)
{
	Object_wx_VarHVScrollHelper *pThis = Object_wx_VarHVScrollHelper::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//size_t row = arg.GetNumber(0)
	//size_t column = arg.GetNumber(1)
	//bool _rtn = pThis->GetEntity()->IsVisible(row, column);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_VarHVScrollHelper, __IsVisible_1, "IsVisible_1")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "pos", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_VarHVScrollHelper, __IsVisible_1)
{
	Object_wx_VarHVScrollHelper *pThis = Object_wx_VarHVScrollHelper::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxPosition& pos = arg.GetNumber(0)
	//bool _rtn = pThis->GetEntity()->IsVisible(pos);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_VarHVScrollHelper, __RefreshRowColumn, "RefreshRowColumn")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "row", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "column", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_VarHVScrollHelper, __RefreshRowColumn)
{
	Object_wx_VarHVScrollHelper *pThis = Object_wx_VarHVScrollHelper::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//size_t row = arg.GetNumber(0)
	//size_t column = arg.GetNumber(1)
	//pThis->GetEntity()->RefreshRowColumn(row, column);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_VarHVScrollHelper, __RefreshRowColumn_1, "RefreshRowColumn_1")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "pos", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_VarHVScrollHelper, __RefreshRowColumn_1)
{
	Object_wx_VarHVScrollHelper *pThis = Object_wx_VarHVScrollHelper::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxPosition& pos = arg.GetNumber(0)
	//pThis->GetEntity()->RefreshRowColumn(pos);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_VarHVScrollHelper, __RefreshRowsColumns, "RefreshRowsColumns")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "fromRow", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "toRow", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "fromColumn", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "toColumn", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_VarHVScrollHelper, __RefreshRowsColumns)
{
	Object_wx_VarHVScrollHelper *pThis = Object_wx_VarHVScrollHelper::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//size_t fromRow = arg.GetNumber(0)
	//size_t toRow = arg.GetNumber(1)
	//size_t fromColumn = arg.GetNumber(2)
	//size_t toColumn = arg.GetNumber(3)
	//pThis->GetEntity()->RefreshRowsColumns(fromRow, toRow, fromColumn, toColumn);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_VarHVScrollHelper, __RefreshRowsColumns_1, "RefreshRowsColumns_1")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "from", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "to", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_VarHVScrollHelper, __RefreshRowsColumns_1)
{
	Object_wx_VarHVScrollHelper *pThis = Object_wx_VarHVScrollHelper::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxPosition& from = arg.GetNumber(0)
	//const wxPosition& to = arg.GetNumber(1)
	//pThis->GetEntity()->RefreshRowsColumns(from, to);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_VarHVScrollHelper, __ScrollToRowColumn, "ScrollToRowColumn")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "row", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "column", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_VarHVScrollHelper, __ScrollToRowColumn)
{
	Object_wx_VarHVScrollHelper *pThis = Object_wx_VarHVScrollHelper::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//size_t row = arg.GetNumber(0)
	//size_t column = arg.GetNumber(1)
	//bool _rtn = pThis->GetEntity()->ScrollToRowColumn(row, column);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_VarHVScrollHelper, __ScrollToRowColumn_1, "ScrollToRowColumn_1")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "pos", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_VarHVScrollHelper, __ScrollToRowColumn_1)
{
	Object_wx_VarHVScrollHelper *pThis = Object_wx_VarHVScrollHelper::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxPosition& pos = arg.GetNumber(0)
	//bool _rtn = pThis->GetEntity()->ScrollToRowColumn(pos);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_VarHVScrollHelper, __SetRowColumnCount, "SetRowColumnCount")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "rowCount", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "columnCount", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_VarHVScrollHelper, __SetRowColumnCount)
{
	Object_wx_VarHVScrollHelper *pThis = Object_wx_VarHVScrollHelper::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//size_t rowCount = arg.GetNumber(0)
	//size_t columnCount = arg.GetNumber(1)
	//pThis->GetEntity()->SetRowColumnCount(rowCount, columnCount);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_VarHVScrollHelper, __VirtualHitTest, "VirtualHitTest")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "x", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "y", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_VarHVScrollHelper, __VirtualHitTest)
{
	Object_wx_VarHVScrollHelper *pThis = Object_wx_VarHVScrollHelper::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxCoord x = arg.GetNumber(0)
	//wxCoord y = arg.GetNumber(1)
	//wxPosition _rtn = pThis->GetEntity()->VirtualHitTest(x, y);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_VarHVScrollHelper, __VirtualHitTest_1, "VirtualHitTest_1")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "pos", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_VarHVScrollHelper, __VirtualHitTest_1)
{
	Object_wx_VarHVScrollHelper *pThis = Object_wx_VarHVScrollHelper::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxPoint& pos = arg.GetNumber(0)
	//wxPosition _rtn = pThis->GetEntity()->VirtualHitTest(pos);
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Class implementation for wxVarHVScrollHelper
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_VarHVScrollHelper)
{
	// Constructor assignment
	Gura_AssignFunction(__VarHVScrollHelper);
	// Method assignment
	Gura_AssignMethod(wx_VarHVScrollHelper, __EnablePhysicalScrolling);
	Gura_AssignMethod(wx_VarHVScrollHelper, __GetRowColumnCount);
	Gura_AssignMethod(wx_VarHVScrollHelper, __GetVisibleBegin);
	Gura_AssignMethod(wx_VarHVScrollHelper, __GetVisibleEnd);
	Gura_AssignMethod(wx_VarHVScrollHelper, __IsVisible);
	Gura_AssignMethod(wx_VarHVScrollHelper, __IsVisible_1);
	Gura_AssignMethod(wx_VarHVScrollHelper, __RefreshRowColumn);
	Gura_AssignMethod(wx_VarHVScrollHelper, __RefreshRowColumn_1);
	Gura_AssignMethod(wx_VarHVScrollHelper, __RefreshRowsColumns);
	Gura_AssignMethod(wx_VarHVScrollHelper, __RefreshRowsColumns_1);
	Gura_AssignMethod(wx_VarHVScrollHelper, __ScrollToRowColumn);
	Gura_AssignMethod(wx_VarHVScrollHelper, __ScrollToRowColumn_1);
	Gura_AssignMethod(wx_VarHVScrollHelper, __SetRowColumnCount);
	Gura_AssignMethod(wx_VarHVScrollHelper, __VirtualHitTest);
	Gura_AssignMethod(wx_VarHVScrollHelper, __VirtualHitTest_1);
}

Gura_ImplementDescendantCreator(wx_VarHVScrollHelper)
{
	return new Object_wx_VarHVScrollHelper((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
