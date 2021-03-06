//----------------------------------------------------------------------------
// wxDCFontChanger
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Gura interfaces for wxDCFontChanger
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Object implementation for wxDCFontChanger
//----------------------------------------------------------------------------
Object_wx_DCFontChanger::~Object_wx_DCFontChanger()
{
}

Object *Object_wx_DCFontChanger::Clone() const
{
	return nullptr;
}

String Object_wx_DCFontChanger::ToString(bool exprFlag)
{
	String rtn("<wx.DCFontChanger:");
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
Gura_DeclareFunctionAlias(__DCFontChanger, "DCFontChanger")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "dc", VTYPE_number, OCCUR_Once);
	SetClassToConstruct(Gura_UserClass(wx_DCFontChanger));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(__DCFontChanger)
{
	//wxDC& dc = arg.GetNumber(0)
	//wxDCFontChanger(dc);
	return Value::Nil;
}

Gura_DeclareFunctionAlias(__DCFontChanger_1, "DCFontChanger_1")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "dc", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "font", VTYPE_number, OCCUR_Once);
	SetClassToConstruct(Gura_UserClass(wx_DCFontChanger));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(__DCFontChanger_1)
{
	//wxDC& dc = arg.GetNumber(0)
	//const wxFont& font = arg.GetNumber(1)
	//wxDCFontChanger(dc, font);
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Method implementation
//----------------------------------------------------------------------------
Gura_DeclareMethodAlias(wx_DCFontChanger, __Set, "Set")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "font", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_DCFontChanger, __Set)
{
	Object_wx_DCFontChanger *pThis = Object_wx_DCFontChanger::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxFont& font = arg.GetNumber(0)
	//pThis->GetEntity()->Set(font);
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Class implementation for wxDCFontChanger
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_DCFontChanger)
{
	// Constructor assignment
	Gura_AssignFunction(__DCFontChanger);
	Gura_AssignFunction(__DCFontChanger_1);
	// Method assignment
	Gura_AssignMethod(wx_DCFontChanger, __Set);
}

Gura_ImplementDescendantCreator(wx_DCFontChanger)
{
	return new Object_wx_DCFontChanger((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
