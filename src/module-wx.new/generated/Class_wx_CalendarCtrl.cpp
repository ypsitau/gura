//----------------------------------------------------------------------------
// wxCalendarCtrl
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Gura interfaces for wxCalendarCtrl
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Object implementation for wxCalendarCtrl
//----------------------------------------------------------------------------
Object_wx_CalendarCtrl::~Object_wx_CalendarCtrl()
{
}

Object *Object_wx_CalendarCtrl::Clone() const
{
	return nullptr;
}

String Object_wx_CalendarCtrl::ToString(bool exprFlag)
{
	String rtn("<wx.CalendarCtrl:");
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
Gura_DeclareFunctionAlias(__CalendarCtrl, "CalendarCtrl")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	SetClassToConstruct(Gura_UserClass(wx_CalendarCtrl));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(__CalendarCtrl)
{
	//wxCalendarCtrl();
	return Value::Nil;
}

Gura_DeclareFunctionAlias(__CalendarCtrl_1, "CalendarCtrl_1")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "parent", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "id", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "date", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "pos", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "size", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "style", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "name", VTYPE_number, OCCUR_Once);
	SetClassToConstruct(Gura_UserClass(wx_CalendarCtrl));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(__CalendarCtrl_1)
{
	//wxWindow* parent = arg.GetNumber(0)
	//wxWindowID id = arg.GetNumber(1)
	//const wxDateTime& date = arg.GetNumber(2)
	//const wxPoint& pos = arg.GetNumber(3)
	//const wxSize& size = arg.GetNumber(4)
	//long style = arg.GetNumber(5)
	//const wxString& name = arg.GetNumber(6)
	//wxCalendarCtrl(parent, id, date, pos, size, style, name);
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Method implementation
//----------------------------------------------------------------------------
Gura_DeclareMethodAlias(wx_CalendarCtrl, __Create, "Create")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "parent", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "id", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "date", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "pos", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "size", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "style", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "name", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_CalendarCtrl, __Create)
{
	Object_wx_CalendarCtrl *pThis = Object_wx_CalendarCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxWindow* parent = arg.GetNumber(0)
	//wxWindowID id = arg.GetNumber(1)
	//const wxDateTime& date = arg.GetNumber(2)
	//const wxPoint& pos = arg.GetNumber(3)
	//const wxSize& size = arg.GetNumber(4)
	//long style = arg.GetNumber(5)
	//const wxString& name = arg.GetNumber(6)
	//bool _rtn = pThis->GetEntity()->Create(parent, id, date, pos, size, style, name);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_CalendarCtrl, __EnableHolidayDisplay, "EnableHolidayDisplay")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "display", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_CalendarCtrl, __EnableHolidayDisplay)
{
	Object_wx_CalendarCtrl *pThis = Object_wx_CalendarCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//bool display = arg.GetNumber(0)
	//pThis->GetEntity()->EnableHolidayDisplay(display);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_CalendarCtrl, __EnableMonthChange, "EnableMonthChange")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "enable", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_CalendarCtrl, __EnableMonthChange)
{
	Object_wx_CalendarCtrl *pThis = Object_wx_CalendarCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//bool enable = arg.GetNumber(0)
	//bool _rtn = pThis->GetEntity()->EnableMonthChange(enable);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_CalendarCtrl, __EnableYearChange, "EnableYearChange")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "enable", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_CalendarCtrl, __EnableYearChange)
{
	Object_wx_CalendarCtrl *pThis = Object_wx_CalendarCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//bool enable = arg.GetNumber(0)
	//pThis->GetEntity()->EnableYearChange(enable);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_CalendarCtrl, __GetAttr, "GetAttr")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "day", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_CalendarCtrl, __GetAttr)
{
	Object_wx_CalendarCtrl *pThis = Object_wx_CalendarCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//size_t day = arg.GetNumber(0)
	//wxCalendarDateAttr* _rtn = pThis->GetEntity()->GetAttr(day);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_CalendarCtrl, __GetDate, "GetDate")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_CalendarCtrl, __GetDate)
{
	Object_wx_CalendarCtrl *pThis = Object_wx_CalendarCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxDateTime _rtn = pThis->GetEntity()->GetDate();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_CalendarCtrl, __GetHeaderColourBg, "GetHeaderColourBg")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_CalendarCtrl, __GetHeaderColourBg)
{
	Object_wx_CalendarCtrl *pThis = Object_wx_CalendarCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxColour& _rtn = pThis->GetEntity()->GetHeaderColourBg();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_CalendarCtrl, __GetHeaderColourFg, "GetHeaderColourFg")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_CalendarCtrl, __GetHeaderColourFg)
{
	Object_wx_CalendarCtrl *pThis = Object_wx_CalendarCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxColour& _rtn = pThis->GetEntity()->GetHeaderColourFg();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_CalendarCtrl, __GetHighlightColourBg, "GetHighlightColourBg")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_CalendarCtrl, __GetHighlightColourBg)
{
	Object_wx_CalendarCtrl *pThis = Object_wx_CalendarCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxColour& _rtn = pThis->GetEntity()->GetHighlightColourBg();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_CalendarCtrl, __GetHighlightColourFg, "GetHighlightColourFg")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_CalendarCtrl, __GetHighlightColourFg)
{
	Object_wx_CalendarCtrl *pThis = Object_wx_CalendarCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxColour& _rtn = pThis->GetEntity()->GetHighlightColourFg();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_CalendarCtrl, __GetHolidayColourBg, "GetHolidayColourBg")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_CalendarCtrl, __GetHolidayColourBg)
{
	Object_wx_CalendarCtrl *pThis = Object_wx_CalendarCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxColour& _rtn = pThis->GetEntity()->GetHolidayColourBg();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_CalendarCtrl, __GetHolidayColourFg, "GetHolidayColourFg")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_CalendarCtrl, __GetHolidayColourFg)
{
	Object_wx_CalendarCtrl *pThis = Object_wx_CalendarCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxColour& _rtn = pThis->GetEntity()->GetHolidayColourFg();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_CalendarCtrl, __HitTest, "HitTest")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "pos", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "date", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "wd", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_CalendarCtrl, __HitTest)
{
	Object_wx_CalendarCtrl *pThis = Object_wx_CalendarCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxPoint& pos = arg.GetNumber(0)
	//wxDateTime* date = arg.GetNumber(1)
	//wxDateTime::WeekDay* wd = arg.GetNumber(2)
	//wxCalendarHitTestResult _rtn = pThis->GetEntity()->HitTest(pos, date, wd);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_CalendarCtrl, __ResetAttr, "ResetAttr")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "day", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_CalendarCtrl, __ResetAttr)
{
	Object_wx_CalendarCtrl *pThis = Object_wx_CalendarCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//size_t day = arg.GetNumber(0)
	//pThis->GetEntity()->ResetAttr(day);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_CalendarCtrl, __SetAttr, "SetAttr")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "day", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "attr", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_CalendarCtrl, __SetAttr)
{
	Object_wx_CalendarCtrl *pThis = Object_wx_CalendarCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//size_t day = arg.GetNumber(0)
	//wxCalendarDateAttr* attr = arg.GetNumber(1)
	//pThis->GetEntity()->SetAttr(day, attr);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_CalendarCtrl, __SetDate, "SetDate")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "date", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_CalendarCtrl, __SetDate)
{
	Object_wx_CalendarCtrl *pThis = Object_wx_CalendarCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxDateTime& date = arg.GetNumber(0)
	//bool _rtn = pThis->GetEntity()->SetDate(date);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_CalendarCtrl, __SetHeaderColours, "SetHeaderColours")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "colFg", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "colBg", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_CalendarCtrl, __SetHeaderColours)
{
	Object_wx_CalendarCtrl *pThis = Object_wx_CalendarCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxColour& colFg = arg.GetNumber(0)
	//const wxColour& colBg = arg.GetNumber(1)
	//pThis->GetEntity()->SetHeaderColours(colFg, colBg);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_CalendarCtrl, __SetHighlightColours, "SetHighlightColours")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "colFg", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "colBg", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_CalendarCtrl, __SetHighlightColours)
{
	Object_wx_CalendarCtrl *pThis = Object_wx_CalendarCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxColour& colFg = arg.GetNumber(0)
	//const wxColour& colBg = arg.GetNumber(1)
	//pThis->GetEntity()->SetHighlightColours(colFg, colBg);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_CalendarCtrl, __SetHoliday, "SetHoliday")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "day", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_CalendarCtrl, __SetHoliday)
{
	Object_wx_CalendarCtrl *pThis = Object_wx_CalendarCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//size_t day = arg.GetNumber(0)
	//pThis->GetEntity()->SetHoliday(day);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_CalendarCtrl, __SetHolidayColours, "SetHolidayColours")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "colFg", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "colBg", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_CalendarCtrl, __SetHolidayColours)
{
	Object_wx_CalendarCtrl *pThis = Object_wx_CalendarCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxColour& colFg = arg.GetNumber(0)
	//const wxColour& colBg = arg.GetNumber(1)
	//pThis->GetEntity()->SetHolidayColours(colFg, colBg);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_CalendarCtrl, __Mark, "Mark")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "day", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "mark", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_CalendarCtrl, __Mark)
{
	Object_wx_CalendarCtrl *pThis = Object_wx_CalendarCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//size_t day = arg.GetNumber(0)
	//bool mark = arg.GetNumber(1)
	//pThis->GetEntity()->Mark(day, mark);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_CalendarCtrl, __SetDateRange, "SetDateRange")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "lowerdate", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "upperdate", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_CalendarCtrl, __SetDateRange)
{
	Object_wx_CalendarCtrl *pThis = Object_wx_CalendarCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxDateTime& lowerdate = arg.GetNumber(0)
	//const wxDateTime& upperdate = arg.GetNumber(1)
	//bool _rtn = pThis->GetEntity()->SetDateRange(lowerdate, upperdate);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_CalendarCtrl, __GetDateRange, "GetDateRange")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "lowerdate", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "upperdate", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_CalendarCtrl, __GetDateRange)
{
	Object_wx_CalendarCtrl *pThis = Object_wx_CalendarCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxDateTime* lowerdate = arg.GetNumber(0)
	//wxDateTime* upperdate = arg.GetNumber(1)
	//bool _rtn = pThis->GetEntity()->GetDateRange(lowerdate, upperdate);
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Class implementation for wxCalendarCtrl
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_CalendarCtrl)
{
	// Constructor assignment
	Gura_AssignFunction(__CalendarCtrl);
	Gura_AssignFunction(__CalendarCtrl_1);
	// Method assignment
	Gura_AssignMethod(wx_CalendarCtrl, __Create);
	Gura_AssignMethod(wx_CalendarCtrl, __EnableHolidayDisplay);
	Gura_AssignMethod(wx_CalendarCtrl, __EnableMonthChange);
	Gura_AssignMethod(wx_CalendarCtrl, __EnableYearChange);
	Gura_AssignMethod(wx_CalendarCtrl, __GetAttr);
	Gura_AssignMethod(wx_CalendarCtrl, __GetDate);
	Gura_AssignMethod(wx_CalendarCtrl, __GetHeaderColourBg);
	Gura_AssignMethod(wx_CalendarCtrl, __GetHeaderColourFg);
	Gura_AssignMethod(wx_CalendarCtrl, __GetHighlightColourBg);
	Gura_AssignMethod(wx_CalendarCtrl, __GetHighlightColourFg);
	Gura_AssignMethod(wx_CalendarCtrl, __GetHolidayColourBg);
	Gura_AssignMethod(wx_CalendarCtrl, __GetHolidayColourFg);
	Gura_AssignMethod(wx_CalendarCtrl, __HitTest);
	Gura_AssignMethod(wx_CalendarCtrl, __ResetAttr);
	Gura_AssignMethod(wx_CalendarCtrl, __SetAttr);
	Gura_AssignMethod(wx_CalendarCtrl, __SetDate);
	Gura_AssignMethod(wx_CalendarCtrl, __SetHeaderColours);
	Gura_AssignMethod(wx_CalendarCtrl, __SetHighlightColours);
	Gura_AssignMethod(wx_CalendarCtrl, __SetHoliday);
	Gura_AssignMethod(wx_CalendarCtrl, __SetHolidayColours);
	Gura_AssignMethod(wx_CalendarCtrl, __Mark);
	Gura_AssignMethod(wx_CalendarCtrl, __SetDateRange);
	Gura_AssignMethod(wx_CalendarCtrl, __GetDateRange);
}

Gura_ImplementDescendantCreator(wx_CalendarCtrl)
{
	return new Object_wx_CalendarCtrl((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
