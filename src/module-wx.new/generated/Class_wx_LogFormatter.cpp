//----------------------------------------------------------------------------
// wxLogFormatter
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Gura interfaces for wxLogFormatter
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Object implementation for wxLogFormatter
//----------------------------------------------------------------------------
Object_wx_LogFormatter::~Object_wx_LogFormatter()
{
}

Object *Object_wx_LogFormatter::Clone() const
{
	return nullptr;
}

String Object_wx_LogFormatter::ToString(bool exprFlag)
{
	String rtn("<wx.LogFormatter:");
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
// Method implementation
//----------------------------------------------------------------------------
Gura_DeclareMethodAlias(wx_LogFormatter, __wxLogFormatter, "wxLogFormatter")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_LogFormatter, __wxLogFormatter)
{
	Object_wx_LogFormatter *pThis = Object_wx_LogFormatter::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->wxLogFormatter();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_LogFormatter, __Format, "Format")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "level", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "msg", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "info", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_LogFormatter, __Format)
{
	Object_wx_LogFormatter *pThis = Object_wx_LogFormatter::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int level = arg.GetNumber(0)
	//int msg = arg.GetNumber(1)
	//int info = arg.GetNumber(2)
	//pThis->GetEntity()->Format();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_LogFormatter, __FormatTime, "FormatTime")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "time", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_LogFormatter, __FormatTime)
{
	Object_wx_LogFormatter *pThis = Object_wx_LogFormatter::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int time = arg.GetNumber(0)
	//pThis->GetEntity()->FormatTime();
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Class implementation for wxLogFormatter
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_LogFormatter)
{
	Gura_AssignMethod(wx_LogFormatter, __wxLogFormatter);
	Gura_AssignMethod(wx_LogFormatter, __Format);
	Gura_AssignMethod(wx_LogFormatter, __FormatTime);
}

Gura_ImplementDescendantCreator(wx_LogFormatter)
{
	return new Object_wx_LogFormatter((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
