//----------------------------------------------------------------------------
// wxLogNull
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Gura interfaces for wxLogNull
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Object implementation for wxLogNull
//----------------------------------------------------------------------------
Object_wx_LogNull::~Object_wx_LogNull()
{
}

Object *Object_wx_LogNull::Clone() const
{
	return nullptr;
}

String Object_wx_LogNull::ToString(bool exprFlag)
{
	String rtn("<wx.LogNull:");
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
Gura_DeclareMethod(wx_LogNull, wxLogNull)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_LogNull, wxLogNull)
{
	Signal &sig = env.GetSignal();
	Object_wx_LogNull *pThis = Object_wx_LogNull::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	//pThis->GetEntity()->wxLogNull();
	return Value::Nil;
}

Gura_DeclareMethod(wx_LogNull, ~wxLogNull)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_LogNull, ~wxLogNull)
{
	Signal &sig = env.GetSignal();
	Object_wx_LogNull *pThis = Object_wx_LogNull::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	//pThis->GetEntity()->~wxLogNull();
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Class implementation for wxLogNull
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_LogNull)
{
	Gura_AssignMethod(wx_LogNull, wxLogNull);
	Gura_AssignMethod(wx_LogNull, ~wxLogNull);
}

Gura_ImplementDescendantCreator(wx_LogNull)
{
	return new Object_wx_LogNull((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
