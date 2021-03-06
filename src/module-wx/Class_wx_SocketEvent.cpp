//----------------------------------------------------------------------------
// wxSocketEvent
// extracted from socket.tex
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Class derivation
//----------------------------------------------------------------------------
class wx_SocketEvent: public wxSocketEvent, public GuraObjectObserver {
private:
	//Gura::Signal *_pSig;
	Object_wx_SocketEvent *_pObj;
public:
	inline wx_SocketEvent(int id) : wxSocketEvent(id), _pObj(nullptr) {}
	~wx_SocketEvent();
	inline void AssocWithGura(Object_wx_SocketEvent *pObj) {
		_pObj = pObj;
	}
	// virtual function of GuraObjectObserver
	virtual void GuraObjectDeleted();
};

wx_SocketEvent::~wx_SocketEvent()
{
	if (_pObj != nullptr) _pObj->InvalidateEntity();
}

void wx_SocketEvent::GuraObjectDeleted()
{
	_pObj = nullptr;
}

//----------------------------------------------------------------------------
// Gura interfaces for wxSocketEvent
//----------------------------------------------------------------------------
Gura_DeclareFunction(SocketEvent)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	SetClassToConstruct(Gura_UserClass(wx_SocketEvent));
	DeclareArg(env, "id", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(SocketEvent)
{
	Signal &sig = env.GetSignal();
	if (!CheckWxReady(sig)) return Value::Nil;
	int id = 0;
	if (arg.IsValid(0)) id = arg.GetInt(0);
	wx_SocketEvent *pEntity = new wx_SocketEvent(id);
	Object_wx_SocketEvent *pObj = Object_wx_SocketEvent::GetObjectThis(arg);
	if (pObj == nullptr) {
		pObj = new Object_wx_SocketEvent(pEntity, pEntity, OwnerFalse);
		pEntity->AssocWithGura(pObj);
		return ReturnValue(env, arg, Value(pObj));
	}
	pObj->SetEntity(pEntity, pEntity, OwnerFalse);
	pEntity->AssocWithGura(pObj);
	return ReturnValue(env, arg, arg.GetValueThis());
}

Gura_DeclareMethod(wx_SocketEvent, GetClientData)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_SocketEvent, GetClientData)
{
	Signal &sig = env.GetSignal();
	Object_wx_SocketEvent *pThis = Object_wx_SocketEvent::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	pThis->GetEntity()->GetClientData();
	return Value::Nil;
}

Gura_DeclareMethod(wx_SocketEvent, GetSocket)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_SocketEvent, GetSocket)
{
	Signal &sig = env.GetSignal();
	Object_wx_SocketEvent *pThis = Object_wx_SocketEvent::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxSocketBase *rtn = (wxSocketBase *)pThis->GetEntity()->GetSocket();
	return ReturnValue(env, arg, Value(new Object_wx_SocketBase(rtn, nullptr, OwnerFalse)));
}

Gura_DeclareMethod(wx_SocketEvent, GetSocketEvent)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_SocketEvent, GetSocketEvent)
{
	Signal &sig = env.GetSignal();
#if 0
	Object_wx_SocketEvent *pThis = Object_wx_SocketEvent::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxSocketNotify rtn = pThis->GetEntity()->GetSocketEvent();
	return ReturnValue(env, arg, Value(new Object_wx_SocketNotify(new wxSocketNotify(rtn), nullptr, OwnerTrue)));
#endif
	SetError_NotImplemented(sig);
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Object implementation for wxSocketEvent
//----------------------------------------------------------------------------
Object_wx_SocketEvent::~Object_wx_SocketEvent()
{
}

Object *Object_wx_SocketEvent::Clone() const
{
	return nullptr;
}

String Object_wx_SocketEvent::ToString(bool exprFlag)
{
	String rtn("<wx.SocketEvent:");
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
// Class implementation for wxSocketEvent
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_SocketEvent)
{
	Gura_AssignFunction(SocketEvent);
	Gura_AssignMethod(wx_SocketEvent, GetClientData);
	Gura_AssignMethod(wx_SocketEvent, GetSocket);
	Gura_AssignMethod(wx_SocketEvent, GetSocketEvent);
}

Gura_ImplementDescendantCreator(wx_SocketEvent)
{
	return new Object_wx_SocketEvent((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
