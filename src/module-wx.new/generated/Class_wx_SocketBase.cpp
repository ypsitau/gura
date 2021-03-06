//----------------------------------------------------------------------------
// wxSocketBase
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Gura interfaces for wxSocketBase
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Object implementation for wxSocketBase
//----------------------------------------------------------------------------
Object_wx_SocketBase::~Object_wx_SocketBase()
{
}

Object *Object_wx_SocketBase::Clone() const
{
	return nullptr;
}

String Object_wx_SocketBase::ToString(bool exprFlag)
{
	String rtn("<wx.SocketBase:");
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
Gura_DeclareFunctionAlias(__SocketBase, "SocketBase")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	SetClassToConstruct(Gura_UserClass(wx_SocketBase));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(__SocketBase)
{
	//wxSocketBase();
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Method implementation
//----------------------------------------------------------------------------
Gura_DeclareMethodAlias(wx_SocketBase, __Destroy, "Destroy")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_SocketBase, __Destroy)
{
	Object_wx_SocketBase *pThis = Object_wx_SocketBase::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//bool _rtn = pThis->GetEntity()->Destroy();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_SocketBase, __Initialize, "Initialize")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_SocketBase, __Initialize)
{
	Object_wx_SocketBase *pThis = Object_wx_SocketBase::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//bool _rtn = pThis->GetEntity()->Initialize();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_SocketBase, __Shutdown, "Shutdown")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_SocketBase, __Shutdown)
{
	Object_wx_SocketBase *pThis = Object_wx_SocketBase::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->Shutdown();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_SocketBase, __Error, "Error")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_SocketBase, __Error)
{
	Object_wx_SocketBase *pThis = Object_wx_SocketBase::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//bool _rtn = pThis->GetEntity()->Error();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_SocketBase, __GetLocal, "GetLocal")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "addr", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_SocketBase, __GetLocal)
{
	Object_wx_SocketBase *pThis = Object_wx_SocketBase::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxSockAddress& addr = arg.GetNumber(0)
	//bool _rtn = pThis->GetEntity()->GetLocal(addr);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_SocketBase, __GetPeer, "GetPeer")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "addr", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_SocketBase, __GetPeer)
{
	Object_wx_SocketBase *pThis = Object_wx_SocketBase::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxSockAddress& addr = arg.GetNumber(0)
	//bool _rtn = pThis->GetEntity()->GetPeer(addr);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_SocketBase, __GetTimeout, "GetTimeout")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_SocketBase, __GetTimeout)
{
	Object_wx_SocketBase *pThis = Object_wx_SocketBase::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//long _rtn = pThis->GetEntity()->GetTimeout();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_SocketBase, __IsConnected, "IsConnected")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_SocketBase, __IsConnected)
{
	Object_wx_SocketBase *pThis = Object_wx_SocketBase::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//bool _rtn = pThis->GetEntity()->IsConnected();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_SocketBase, __IsData, "IsData")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_SocketBase, __IsData)
{
	Object_wx_SocketBase *pThis = Object_wx_SocketBase::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//bool _rtn = pThis->GetEntity()->IsData();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_SocketBase, __IsDisconnected, "IsDisconnected")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_SocketBase, __IsDisconnected)
{
	Object_wx_SocketBase *pThis = Object_wx_SocketBase::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//bool _rtn = pThis->GetEntity()->IsDisconnected();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_SocketBase, __IsOk, "IsOk")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_SocketBase, __IsOk)
{
	Object_wx_SocketBase *pThis = Object_wx_SocketBase::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//bool _rtn = pThis->GetEntity()->IsOk();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_SocketBase, __LastCount, "LastCount")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_SocketBase, __LastCount)
{
	Object_wx_SocketBase *pThis = Object_wx_SocketBase::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxUint32 _rtn = pThis->GetEntity()->LastCount();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_SocketBase, __LastReadCount, "LastReadCount")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_SocketBase, __LastReadCount)
{
	Object_wx_SocketBase *pThis = Object_wx_SocketBase::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxUint32 _rtn = pThis->GetEntity()->LastReadCount();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_SocketBase, __LastWriteCount, "LastWriteCount")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_SocketBase, __LastWriteCount)
{
	Object_wx_SocketBase *pThis = Object_wx_SocketBase::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxUint32 _rtn = pThis->GetEntity()->LastWriteCount();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_SocketBase, __LastError, "LastError")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_SocketBase, __LastError)
{
	Object_wx_SocketBase *pThis = Object_wx_SocketBase::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxSocketError _rtn = pThis->GetEntity()->LastError();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_SocketBase, __RestoreState, "RestoreState")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_SocketBase, __RestoreState)
{
	Object_wx_SocketBase *pThis = Object_wx_SocketBase::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->RestoreState();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_SocketBase, __SaveState, "SaveState")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_SocketBase, __SaveState)
{
	Object_wx_SocketBase *pThis = Object_wx_SocketBase::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->SaveState();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_SocketBase, __Close, "Close")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_SocketBase, __Close)
{
	Object_wx_SocketBase *pThis = Object_wx_SocketBase::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//bool _rtn = pThis->GetEntity()->Close();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_SocketBase, __ShutdownOutput, "ShutdownOutput")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_SocketBase, __ShutdownOutput)
{
	Object_wx_SocketBase *pThis = Object_wx_SocketBase::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->ShutdownOutput();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_SocketBase, __Discard, "Discard")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_SocketBase, __Discard)
{
	Object_wx_SocketBase *pThis = Object_wx_SocketBase::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxSocketBase& _rtn = pThis->GetEntity()->Discard();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_SocketBase, __GetFlags, "GetFlags")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_SocketBase, __GetFlags)
{
	Object_wx_SocketBase *pThis = Object_wx_SocketBase::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxSocketFlags _rtn = pThis->GetEntity()->GetFlags();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_SocketBase, __InterruptWait, "InterruptWait")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_SocketBase, __InterruptWait)
{
	Object_wx_SocketBase *pThis = Object_wx_SocketBase::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->InterruptWait();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_SocketBase, __Peek, "Peek")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "buffer", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "nbytes", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_SocketBase, __Peek)
{
	Object_wx_SocketBase *pThis = Object_wx_SocketBase::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//void* buffer = arg.GetNumber(0)
	//wxUint32 nbytes = arg.GetNumber(1)
	//wxSocketBase& _rtn = pThis->GetEntity()->Peek(buffer, nbytes);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_SocketBase, __Read, "Read")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "buffer", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "nbytes", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_SocketBase, __Read)
{
	Object_wx_SocketBase *pThis = Object_wx_SocketBase::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//void* buffer = arg.GetNumber(0)
	//wxUint32 nbytes = arg.GetNumber(1)
	//wxSocketBase& _rtn = pThis->GetEntity()->Read(buffer, nbytes);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_SocketBase, __ReadMsg, "ReadMsg")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "buffer", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "nbytes", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_SocketBase, __ReadMsg)
{
	Object_wx_SocketBase *pThis = Object_wx_SocketBase::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//void* buffer = arg.GetNumber(0)
	//wxUint32 nbytes = arg.GetNumber(1)
	//wxSocketBase& _rtn = pThis->GetEntity()->ReadMsg(buffer, nbytes);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_SocketBase, __SetFlags, "SetFlags")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "flags", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_SocketBase, __SetFlags)
{
	Object_wx_SocketBase *pThis = Object_wx_SocketBase::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxSocketFlags flags = arg.GetNumber(0)
	//pThis->GetEntity()->SetFlags(flags);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_SocketBase, __SetLocal, "SetLocal")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "local", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_SocketBase, __SetLocal)
{
	Object_wx_SocketBase *pThis = Object_wx_SocketBase::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxIPV4address& local = arg.GetNumber(0)
	//bool _rtn = pThis->GetEntity()->SetLocal(local);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_SocketBase, __SetTimeout, "SetTimeout")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "seconds", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_SocketBase, __SetTimeout)
{
	Object_wx_SocketBase *pThis = Object_wx_SocketBase::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//long seconds = arg.GetNumber(0)
	//pThis->GetEntity()->SetTimeout(seconds);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_SocketBase, __Unread, "Unread")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "buffer", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "nbytes", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_SocketBase, __Unread)
{
	Object_wx_SocketBase *pThis = Object_wx_SocketBase::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const void* buffer = arg.GetNumber(0)
	//wxUint32 nbytes = arg.GetNumber(1)
	//wxSocketBase& _rtn = pThis->GetEntity()->Unread(buffer, nbytes);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_SocketBase, __Wait, "Wait")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "seconds", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "millisecond", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_SocketBase, __Wait)
{
	Object_wx_SocketBase *pThis = Object_wx_SocketBase::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//long seconds = arg.GetNumber(0)
	//long millisecond = arg.GetNumber(1)
	//bool _rtn = pThis->GetEntity()->Wait(seconds, millisecond);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_SocketBase, __WaitForLost, "WaitForLost")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "seconds", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "millisecond", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_SocketBase, __WaitForLost)
{
	Object_wx_SocketBase *pThis = Object_wx_SocketBase::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//long seconds = arg.GetNumber(0)
	//long millisecond = arg.GetNumber(1)
	//bool _rtn = pThis->GetEntity()->WaitForLost(seconds, millisecond);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_SocketBase, __WaitForRead, "WaitForRead")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "seconds", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "millisecond", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_SocketBase, __WaitForRead)
{
	Object_wx_SocketBase *pThis = Object_wx_SocketBase::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//long seconds = arg.GetNumber(0)
	//long millisecond = arg.GetNumber(1)
	//bool _rtn = pThis->GetEntity()->WaitForRead(seconds, millisecond);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_SocketBase, __WaitForWrite, "WaitForWrite")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "seconds", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "millisecond", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_SocketBase, __WaitForWrite)
{
	Object_wx_SocketBase *pThis = Object_wx_SocketBase::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//long seconds = arg.GetNumber(0)
	//long millisecond = arg.GetNumber(1)
	//bool _rtn = pThis->GetEntity()->WaitForWrite(seconds, millisecond);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_SocketBase, __Write, "Write")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "buffer", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "nbytes", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_SocketBase, __Write)
{
	Object_wx_SocketBase *pThis = Object_wx_SocketBase::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const void* buffer = arg.GetNumber(0)
	//wxUint32 nbytes = arg.GetNumber(1)
	//wxSocketBase& _rtn = pThis->GetEntity()->Write(buffer, nbytes);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_SocketBase, __WriteMsg, "WriteMsg")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "buffer", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "nbytes", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_SocketBase, __WriteMsg)
{
	Object_wx_SocketBase *pThis = Object_wx_SocketBase::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const void* buffer = arg.GetNumber(0)
	//wxUint32 nbytes = arg.GetNumber(1)
	//wxSocketBase& _rtn = pThis->GetEntity()->WriteMsg(buffer, nbytes);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_SocketBase, __GetClientData, "GetClientData")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_SocketBase, __GetClientData)
{
	Object_wx_SocketBase *pThis = Object_wx_SocketBase::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//void* _rtn = pThis->GetEntity()->GetClientData();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_SocketBase, __Notify, "Notify")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "notify", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_SocketBase, __Notify)
{
	Object_wx_SocketBase *pThis = Object_wx_SocketBase::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//bool notify = arg.GetNumber(0)
	//pThis->GetEntity()->Notify(notify);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_SocketBase, __SetClientData, "SetClientData")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "data", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_SocketBase, __SetClientData)
{
	Object_wx_SocketBase *pThis = Object_wx_SocketBase::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//void* data = arg.GetNumber(0)
	//pThis->GetEntity()->SetClientData(data);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_SocketBase, __SetEventHandler, "SetEventHandler")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "handler", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "id", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_SocketBase, __SetEventHandler)
{
	Object_wx_SocketBase *pThis = Object_wx_SocketBase::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxEvtHandler& handler = arg.GetNumber(0)
	//int id = arg.GetNumber(1)
	//pThis->GetEntity()->SetEventHandler(handler, id);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_SocketBase, __SetNotify, "SetNotify")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "flags", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_SocketBase, __SetNotify)
{
	Object_wx_SocketBase *pThis = Object_wx_SocketBase::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxSocketEventFlags flags = arg.GetNumber(0)
	//pThis->GetEntity()->SetNotify(flags);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_SocketBase, __GetSocket, "GetSocket")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_SocketBase, __GetSocket)
{
	Object_wx_SocketBase *pThis = Object_wx_SocketBase::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxSOCKET_T _rtn = pThis->GetEntity()->GetSocket();
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Class implementation for wxSocketBase
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_SocketBase)
{
	// Constructor assignment
	Gura_AssignFunction(__SocketBase);
	// Method assignment
	Gura_AssignMethod(wx_SocketBase, __Destroy);
	Gura_AssignMethod(wx_SocketBase, __Initialize);
	Gura_AssignMethod(wx_SocketBase, __Shutdown);
	Gura_AssignMethod(wx_SocketBase, __Error);
	Gura_AssignMethod(wx_SocketBase, __GetLocal);
	Gura_AssignMethod(wx_SocketBase, __GetPeer);
	Gura_AssignMethod(wx_SocketBase, __GetTimeout);
	Gura_AssignMethod(wx_SocketBase, __IsConnected);
	Gura_AssignMethod(wx_SocketBase, __IsData);
	Gura_AssignMethod(wx_SocketBase, __IsDisconnected);
	Gura_AssignMethod(wx_SocketBase, __IsOk);
	Gura_AssignMethod(wx_SocketBase, __LastCount);
	Gura_AssignMethod(wx_SocketBase, __LastReadCount);
	Gura_AssignMethod(wx_SocketBase, __LastWriteCount);
	Gura_AssignMethod(wx_SocketBase, __LastError);
	Gura_AssignMethod(wx_SocketBase, __RestoreState);
	Gura_AssignMethod(wx_SocketBase, __SaveState);
	Gura_AssignMethod(wx_SocketBase, __Close);
	Gura_AssignMethod(wx_SocketBase, __ShutdownOutput);
	Gura_AssignMethod(wx_SocketBase, __Discard);
	Gura_AssignMethod(wx_SocketBase, __GetFlags);
	Gura_AssignMethod(wx_SocketBase, __InterruptWait);
	Gura_AssignMethod(wx_SocketBase, __Peek);
	Gura_AssignMethod(wx_SocketBase, __Read);
	Gura_AssignMethod(wx_SocketBase, __ReadMsg);
	Gura_AssignMethod(wx_SocketBase, __SetFlags);
	Gura_AssignMethod(wx_SocketBase, __SetLocal);
	Gura_AssignMethod(wx_SocketBase, __SetTimeout);
	Gura_AssignMethod(wx_SocketBase, __Unread);
	Gura_AssignMethod(wx_SocketBase, __Wait);
	Gura_AssignMethod(wx_SocketBase, __WaitForLost);
	Gura_AssignMethod(wx_SocketBase, __WaitForRead);
	Gura_AssignMethod(wx_SocketBase, __WaitForWrite);
	Gura_AssignMethod(wx_SocketBase, __Write);
	Gura_AssignMethod(wx_SocketBase, __WriteMsg);
	Gura_AssignMethod(wx_SocketBase, __GetClientData);
	Gura_AssignMethod(wx_SocketBase, __Notify);
	Gura_AssignMethod(wx_SocketBase, __SetClientData);
	Gura_AssignMethod(wx_SocketBase, __SetEventHandler);
	Gura_AssignMethod(wx_SocketBase, __SetNotify);
	Gura_AssignMethod(wx_SocketBase, __GetSocket);
}

Gura_ImplementDescendantCreator(wx_SocketBase)
{
	return new Object_wx_SocketBase((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
