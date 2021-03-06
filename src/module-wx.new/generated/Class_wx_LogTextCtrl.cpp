//----------------------------------------------------------------------------
// wxLogTextCtrl
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Gura interfaces for wxLogTextCtrl
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Object implementation for wxLogTextCtrl
//----------------------------------------------------------------------------
Object_wx_LogTextCtrl::~Object_wx_LogTextCtrl()
{
}

Object *Object_wx_LogTextCtrl::Clone() const
{
	return nullptr;
}

String Object_wx_LogTextCtrl::ToString(bool exprFlag)
{
	String rtn("<wx.LogTextCtrl:");
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
Gura_DeclareFunctionAlias(__LogTextCtrl, "LogTextCtrl")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "pTextCtrl", VTYPE_number, OCCUR_Once);
	SetClassToConstruct(Gura_UserClass(wx_LogTextCtrl));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(__LogTextCtrl)
{
	//wxTextCtrl* pTextCtrl = arg.GetNumber(0)
	//wxLogTextCtrl(pTextCtrl);
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Class implementation for wxLogTextCtrl
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_LogTextCtrl)
{
	// Constructor assignment
	Gura_AssignFunction(__LogTextCtrl);
}

Gura_ImplementDescendantCreator(wx_LogTextCtrl)
{
	return new Object_wx_LogTextCtrl((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
