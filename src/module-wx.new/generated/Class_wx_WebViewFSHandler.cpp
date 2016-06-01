//----------------------------------------------------------------------------
// wxWebViewFSHandler
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Gura interfaces for wxWebViewFSHandler
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Object implementation for wxWebViewFSHandler
//----------------------------------------------------------------------------
Object_wx_WebViewFSHandler::~Object_wx_WebViewFSHandler()
{
}

Object *Object_wx_WebViewFSHandler::Clone() const
{
	return nullptr;
}

String Object_wx_WebViewFSHandler::ToString(bool exprFlag)
{
	String rtn("<wx.WebViewFSHandler:");
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
Gura_DeclareMethod(wx_WebViewFSHandler, wxWebViewFSHandler)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "scheme", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_WebViewFSHandler, wxWebViewFSHandler)
{
	Signal &sig = env.GetSignal();
	Object_wx_WebViewFSHandler *pThis = Object_wx_WebViewFSHandler::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	//int scheme = arg.GetNumber(0)
	//pThis->GetEntity()->wxWebViewFSHandler();
	return Value::Nil;
}

Gura_DeclareMethod(wx_WebViewFSHandler, GetFile)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "uri", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_WebViewFSHandler, GetFile)
{
	Signal &sig = env.GetSignal();
	Object_wx_WebViewFSHandler *pThis = Object_wx_WebViewFSHandler::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	//int uri = arg.GetNumber(0)
	//pThis->GetEntity()->GetFile();
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Class implementation for wxWebViewFSHandler
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_WebViewFSHandler)
{
	Gura_AssignMethod(wx_WebViewFSHandler, wxWebViewFSHandler);
	Gura_AssignMethod(wx_WebViewFSHandler, GetFile);
}

Gura_ImplementDescendantCreator(wx_WebViewFSHandler)
{
	return new Object_wx_WebViewFSHandler((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
