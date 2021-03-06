//----------------------------------------------------------------------------
// wxVarHScrollHelper
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Gura interfaces for wxVarHScrollHelper
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Object implementation for wxVarHScrollHelper
//----------------------------------------------------------------------------
Object_wx_VarHScrollHelper::~Object_wx_VarHScrollHelper()
{
}

Object *Object_wx_VarHScrollHelper::Clone() const
{
	return nullptr;
}

String Object_wx_VarHScrollHelper::ToString(bool exprFlag)
{
	String rtn("<wx.VarHScrollHelper:");
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
Gura_DeclareFunctionAlias(__VarHScrollHelper, "VarHScrollHelper")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "winToScroll", VTYPE_number, OCCUR_Once);
	SetClassToConstruct(Gura_UserClass(wx_VarHScrollHelper));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(__VarHScrollHelper)
{
	//wxWindow* winToScroll = arg.GetNumber(0)
	//wxVarHScrollHelper(winToScroll);
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Method implementation
//----------------------------------------------------------------------------
Gura_DeclareMethodAlias(wx_VarHScrollHelper, __GetColumnCount, "GetColumnCount")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_VarHScrollHelper, __GetColumnCount)
{
	Object_wx_VarHScrollHelper *pThis = Object_wx_VarHScrollHelper::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//size_t _rtn = pThis->GetEntity()->GetColumnCount();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_VarHScrollHelper, __GetVisibleColumnsBegin, "GetVisibleColumnsBegin")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_VarHScrollHelper, __GetVisibleColumnsBegin)
{
	Object_wx_VarHScrollHelper *pThis = Object_wx_VarHScrollHelper::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//size_t _rtn = pThis->GetEntity()->GetVisibleColumnsBegin();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_VarHScrollHelper, __GetVisibleColumnsEnd, "GetVisibleColumnsEnd")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_VarHScrollHelper, __GetVisibleColumnsEnd)
{
	Object_wx_VarHScrollHelper *pThis = Object_wx_VarHScrollHelper::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//size_t _rtn = pThis->GetEntity()->GetVisibleColumnsEnd();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_VarHScrollHelper, __IsColumnVisible, "IsColumnVisible")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "column", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_VarHScrollHelper, __IsColumnVisible)
{
	Object_wx_VarHScrollHelper *pThis = Object_wx_VarHScrollHelper::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//size_t column = arg.GetNumber(0)
	//bool _rtn = pThis->GetEntity()->IsColumnVisible(column);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_VarHScrollHelper, __RefreshColumn, "RefreshColumn")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "column", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_VarHScrollHelper, __RefreshColumn)
{
	Object_wx_VarHScrollHelper *pThis = Object_wx_VarHScrollHelper::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//size_t column = arg.GetNumber(0)
	//pThis->GetEntity()->RefreshColumn(column);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_VarHScrollHelper, __RefreshColumns, "RefreshColumns")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "from", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "to", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_VarHScrollHelper, __RefreshColumns)
{
	Object_wx_VarHScrollHelper *pThis = Object_wx_VarHScrollHelper::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//size_t from = arg.GetNumber(0)
	//size_t to = arg.GetNumber(1)
	//pThis->GetEntity()->RefreshColumns(from, to);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_VarHScrollHelper, __ScrollColumnPages, "ScrollColumnPages")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "pages", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_VarHScrollHelper, __ScrollColumnPages)
{
	Object_wx_VarHScrollHelper *pThis = Object_wx_VarHScrollHelper::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int pages = arg.GetNumber(0)
	//bool _rtn = pThis->GetEntity()->ScrollColumnPages(pages);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_VarHScrollHelper, __ScrollColumns, "ScrollColumns")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "columns", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_VarHScrollHelper, __ScrollColumns)
{
	Object_wx_VarHScrollHelper *pThis = Object_wx_VarHScrollHelper::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int columns = arg.GetNumber(0)
	//bool _rtn = pThis->GetEntity()->ScrollColumns(columns);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_VarHScrollHelper, __ScrollToColumn, "ScrollToColumn")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "column", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_VarHScrollHelper, __ScrollToColumn)
{
	Object_wx_VarHScrollHelper *pThis = Object_wx_VarHScrollHelper::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//size_t column = arg.GetNumber(0)
	//bool _rtn = pThis->GetEntity()->ScrollToColumn(column);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_VarHScrollHelper, __SetColumnCount, "SetColumnCount")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "columnCount", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_VarHScrollHelper, __SetColumnCount)
{
	Object_wx_VarHScrollHelper *pThis = Object_wx_VarHScrollHelper::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//size_t columnCount = arg.GetNumber(0)
	//pThis->GetEntity()->SetColumnCount(columnCount);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_VarHScrollHelper, __EstimateTotalWidth, "EstimateTotalWidth")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_VarHScrollHelper, __EstimateTotalWidth)
{
	Object_wx_VarHScrollHelper *pThis = Object_wx_VarHScrollHelper::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxCoord _rtn = pThis->GetEntity()->EstimateTotalWidth();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_VarHScrollHelper, __OnGetColumnsWidthHint, "OnGetColumnsWidthHint")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "columnMin", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "columnMax", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_VarHScrollHelper, __OnGetColumnsWidthHint)
{
	Object_wx_VarHScrollHelper *pThis = Object_wx_VarHScrollHelper::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//size_t columnMin = arg.GetNumber(0)
	//size_t columnMax = arg.GetNumber(1)
	//pThis->GetEntity()->OnGetColumnsWidthHint(columnMin, columnMax);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_VarHScrollHelper, __OnGetColumnWidth, "OnGetColumnWidth")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "column", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_VarHScrollHelper, __OnGetColumnWidth)
{
	Object_wx_VarHScrollHelper *pThis = Object_wx_VarHScrollHelper::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//size_t column = arg.GetNumber(0)
	//wxCoord _rtn = pThis->GetEntity()->OnGetColumnWidth(column);
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Class implementation for wxVarHScrollHelper
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_VarHScrollHelper)
{
	// Constructor assignment
	Gura_AssignFunction(__VarHScrollHelper);
	// Method assignment
	Gura_AssignMethod(wx_VarHScrollHelper, __GetColumnCount);
	Gura_AssignMethod(wx_VarHScrollHelper, __GetVisibleColumnsBegin);
	Gura_AssignMethod(wx_VarHScrollHelper, __GetVisibleColumnsEnd);
	Gura_AssignMethod(wx_VarHScrollHelper, __IsColumnVisible);
	Gura_AssignMethod(wx_VarHScrollHelper, __RefreshColumn);
	Gura_AssignMethod(wx_VarHScrollHelper, __RefreshColumns);
	Gura_AssignMethod(wx_VarHScrollHelper, __ScrollColumnPages);
	Gura_AssignMethod(wx_VarHScrollHelper, __ScrollColumns);
	Gura_AssignMethod(wx_VarHScrollHelper, __ScrollToColumn);
	Gura_AssignMethod(wx_VarHScrollHelper, __SetColumnCount);
	Gura_AssignMethod(wx_VarHScrollHelper, __EstimateTotalWidth);
	Gura_AssignMethod(wx_VarHScrollHelper, __OnGetColumnsWidthHint);
	Gura_AssignMethod(wx_VarHScrollHelper, __OnGetColumnWidth);
}

Gura_ImplementDescendantCreator(wx_VarHScrollHelper)
{
	return new Object_wx_VarHScrollHelper((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
