//----------------------------------------------------------------------------
// wxDatagramSocket
// extracted from dgramsocket.tex
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Class derivation
//----------------------------------------------------------------------------
class wx_DatagramSocket: public wxDatagramSocket, public GuraObjectObserver {
private:
	//Gura::Signal *_pSig;
	Object_wx_DatagramSocket *_pObj;
public:
	//inline wx_DatagramSocket(wxSocketFlags flags) : wxDatagramSocket(flags), _pObj(nullptr) {}
	~wx_DatagramSocket();
	inline void AssocWithGura(Object_wx_DatagramSocket *pObj) {
		_pObj = pObj;
	}
	// virtual function of GuraObjectObserver
	virtual void GuraObjectDeleted();
};

wx_DatagramSocket::~wx_DatagramSocket()
{
	if (_pObj != nullptr) _pObj->InvalidateEntity();
}

void wx_DatagramSocket::GuraObjectDeleted()
{
	_pObj = nullptr;
}

//----------------------------------------------------------------------------
// Gura interfaces for wxDatagramSocket
//----------------------------------------------------------------------------
Gura_DeclareFunction(DatagramSocket)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
#if 0
	SetClassToConstruct(Gura_UserClass(wx_DatagramSocket));
	DeclareArg(env, "flags", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
#endif
}

Gura_ImplementFunction(DatagramSocket)
{
	Signal &sig = env.GetSignal();
	if (!CheckWxReady(sig)) return Value::Nil;
#if 0
	wxSocketFlags flags = wxSOCKET_NONE;
	if (arg.IsValid(0)) flags = static_cast<wxSocketFlags>(arg.GetInt(0));
	wx_DatagramSocket *pEntity = new wx_DatagramSocket(flags);
	Object_wx_DatagramSocket *pObj = Object_wx_DatagramSocket::GetObjectThis(arg);
	if (pObj == nullptr) {
		pObj = new Object_wx_DatagramSocket(pEntity, pEntity, OwnerFalse);
		pEntity->AssocWithGura(pObj);
		return ReturnValue(env, arg, Value(pObj));
	}
	pObj->SetEntity(pEntity, pEntity, OwnerFalse);
	pEntity->AssocWithGura(pObj);
	return ReturnValue(env, arg, arg.GetValueThis());
#endif
	SetError_NotImplemented(sig);
	return Value::Nil;
}

Gura_DeclareMethod(wx_DatagramSocket, ReceiveFrom)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
#if 0
	DeclareArg(env, "address", VTYPE_wx_SockAddress, OCCUR_Once);
	DeclareArg(env, "buffer", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "nbytes", VTYPE_number, OCCUR_Once);
#endif
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_DatagramSocket, ReceiveFrom)
{
	Signal &sig = env.GetSignal();
#if 0
	Object_wx_DatagramSocket *pThis = Object_wx_DatagramSocket::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxSockAddress *address = Object_wx_SockAddress::GetObject(arg, 0)->GetEntity();
	int buffer = arg.GetInt(1);
	wxUint32 nbytes = static_cast<wxUint32>(arg.GetULong(2));
	wxDatagramSocket &rtn = pThis->GetEntity()->ReceiveFrom(*address, buffer, nbytes);
	return ReturnValue(env, arg, Value(new Object_wx_DatagramSocket(new wxDatagramSocket(rtn), nullptr, OwnerTrue)));
#endif
	SetError_NotImplemented(sig);
	return Value::Nil;
}

Gura_DeclareMethod(wx_DatagramSocket, SendTo)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
#if 0
	DeclareArg(env, "address", VTYPE_wx_SockAddress, OCCUR_Once);
	DeclareArg(env, "buffer", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "nbytes", VTYPE_number, OCCUR_Once);
#endif
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_DatagramSocket, SendTo)
{
	Signal &sig = env.GetSignal();
#if 0
	Object_wx_DatagramSocket *pThis = Object_wx_DatagramSocket::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxSockAddress *address = Object_wx_SockAddress::GetObject(arg, 0)->GetEntity();
	int buffer = arg.GetInt(1);
	wxUint32 nbytes = static_cast<wxUint32>(arg.GetULong(2));
	wxDatagramSocket &rtn = pThis->GetEntity()->SendTo(*address, buffer, nbytes);
	return ReturnValue(env, arg, Value(new Object_wx_DatagramSocket(new wxDatagramSocket(rtn), nullptr, OwnerTrue)));
#endif
	SetError_NotImplemented(sig);
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Object implementation for wxDatagramSocket
//----------------------------------------------------------------------------
Object_wx_DatagramSocket::~Object_wx_DatagramSocket()
{
}

Object *Object_wx_DatagramSocket::Clone() const
{
	return nullptr;
}

String Object_wx_DatagramSocket::ToString(bool exprFlag)
{
	String rtn("<wx.DatagramSocket:");
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
// Class implementation for wxDatagramSocket
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_DatagramSocket)
{
	Gura_AssignFunction(DatagramSocket);
	Gura_AssignMethod(wx_DatagramSocket, ReceiveFrom);
	Gura_AssignMethod(wx_DatagramSocket, SendTo);
}

Gura_ImplementDescendantCreator(wx_DatagramSocket)
{
	return new Object_wx_DatagramSocket((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
