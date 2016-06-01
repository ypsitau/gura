//----------------------------------------------------------------------------
// wxTextCompleterSimple
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Gura interfaces for wxTextCompleterSimple
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Object implementation for wxTextCompleterSimple
//----------------------------------------------------------------------------
Object_wx_TextCompleterSimple::~Object_wx_TextCompleterSimple()
{
}

Object *Object_wx_TextCompleterSimple::Clone() const
{
	return nullptr;
}

String Object_wx_TextCompleterSimple::ToString(bool exprFlag)
{
	String rtn("<wx.TextCompleterSimple:");
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
Gura_DeclareMethod(wx_TextCompleterSimple, GetCompletions)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "prefix", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "res", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_TextCompleterSimple, GetCompletions)
{
	Signal &sig = env.GetSignal();
	Object_wx_TextCompleterSimple *pThis = Object_wx_TextCompleterSimple::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	//int prefix = arg.GetNumber(0)
	//int res = arg.GetNumber(1)
	//pThis->GetEntity()->GetCompletions();
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Class implementation for wxTextCompleterSimple
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_TextCompleterSimple)
{
	Gura_AssignMethod(wx_TextCompleterSimple, GetCompletions);
}

Gura_ImplementDescendantCreator(wx_TextCompleterSimple)
{
	return new Object_wx_TextCompleterSimple((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
