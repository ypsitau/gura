//----------------------------------------------------------------------------
// wxDDEServer
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Gura interfaces for wxDDEServer
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Object implementation for wxDDEServer
//----------------------------------------------------------------------------
Object_wx_DDEServer::~Object_wx_DDEServer()
{
}

Object *Object_wx_DDEServer::Clone() const
{
	return nullptr;
}

String Object_wx_DDEServer::ToString(bool exprFlag)
{
	String rtn("<wx.DDEServer:");
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
Gura_DeclareMethod(wx_DDEServer, wxDDEServer)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_DDEServer, wxDDEServer)
{
	Signal &sig = env.GetSignal();
	Object_wx_DDEServer *pThis = Object_wx_DDEServer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	//pThis->GetEntity()->wxDDEServer();
	return Value::Nil;
}

Gura_DeclareMethod(wx_DDEServer, Create)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "service", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_DDEServer, Create)
{
	Signal &sig = env.GetSignal();
	Object_wx_DDEServer *pThis = Object_wx_DDEServer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	//int service = arg.GetNumber(0)
	//pThis->GetEntity()->Create();
	return Value::Nil;
}

Gura_DeclareMethod(wx_DDEServer, OnAcceptConnection)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "topic", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_DDEServer, OnAcceptConnection)
{
	Signal &sig = env.GetSignal();
	Object_wx_DDEServer *pThis = Object_wx_DDEServer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	//int topic = arg.GetNumber(0)
	//pThis->GetEntity()->OnAcceptConnection();
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Class implementation for wxDDEServer
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_DDEServer)
{
	Gura_AssignMethod(wx_DDEServer, wxDDEServer);
	Gura_AssignMethod(wx_DDEServer, Create);
	Gura_AssignMethod(wx_DDEServer, OnAcceptConnection);
}

Gura_ImplementDescendantCreator(wx_DDEServer)
{
	return new Object_wx_DDEServer((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
