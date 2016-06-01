//----------------------------------------------------------------------------
// wxMsgCatalog
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Gura interfaces for wxMsgCatalog
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Object implementation for wxMsgCatalog
//----------------------------------------------------------------------------
Object_wx_MsgCatalog::~Object_wx_MsgCatalog()
{
}

Object *Object_wx_MsgCatalog::Clone() const
{
	return nullptr;
}

String Object_wx_MsgCatalog::ToString(bool exprFlag)
{
	String rtn("<wx.MsgCatalog:");
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
Gura_DeclareMethod(wx_MsgCatalog, CreateFromFile)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "filename", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "domain", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_MsgCatalog, CreateFromFile)
{
	Signal &sig = env.GetSignal();
	Object_wx_MsgCatalog *pThis = Object_wx_MsgCatalog::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	//int filename = arg.GetNumber(0)
	//int domain = arg.GetNumber(1)
	//pThis->GetEntity()->CreateFromFile();
	return Value::Nil;
}

Gura_DeclareMethod(wx_MsgCatalog, CreateFromData)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "data", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "domain", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_MsgCatalog, CreateFromData)
{
	Signal &sig = env.GetSignal();
	Object_wx_MsgCatalog *pThis = Object_wx_MsgCatalog::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	//int data = arg.GetNumber(0)
	//int domain = arg.GetNumber(1)
	//pThis->GetEntity()->CreateFromData();
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Class implementation for wxMsgCatalog
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_MsgCatalog)
{
	Gura_AssignMethod(wx_MsgCatalog, CreateFromFile);
	Gura_AssignMethod(wx_MsgCatalog, CreateFromData);
}

Gura_ImplementDescendantCreator(wx_MsgCatalog)
{
	return new Object_wx_MsgCatalog((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
