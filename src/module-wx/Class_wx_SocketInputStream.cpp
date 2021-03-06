//----------------------------------------------------------------------------
// wxSocketInputStream
// extracted from strmsock.tex
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Class derivation
//----------------------------------------------------------------------------
class wx_SocketInputStream: public wxSocketInputStream, public GuraObjectObserver {
private:
	//Gura::Signal *_pSig;
	Object_wx_SocketInputStream *_pObj;
public:
	inline wx_SocketInputStream(wxSocketBase& s) : wxSocketInputStream(s), _pObj(nullptr) {}
	~wx_SocketInputStream();
	inline void AssocWithGura(Object_wx_SocketInputStream *pObj) {
		_pObj = pObj;
	}
	// virtual function of GuraObjectObserver
	virtual void GuraObjectDeleted();
};

wx_SocketInputStream::~wx_SocketInputStream()
{
	if (_pObj != nullptr) _pObj->InvalidateEntity();
}

void wx_SocketInputStream::GuraObjectDeleted()
{
	_pObj = nullptr;
}

//----------------------------------------------------------------------------
// Gura interfaces for wxSocketInputStream
//----------------------------------------------------------------------------
Gura_DeclareFunction(SocketInputStream)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	SetClassToConstruct(Gura_UserClass(wx_SocketInputStream));
	DeclareArg(env, "s", VTYPE_wx_SocketBase, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(SocketInputStream)
{
	Signal &sig = env.GetSignal();
	if (!CheckWxReady(sig)) return Value::Nil;
	wxSocketBase *s = Object_wx_SocketBase::GetObject(arg, 0)->GetEntity();
	wx_SocketInputStream *pEntity = new wx_SocketInputStream(*s);
	Object_wx_SocketInputStream *pObj = Object_wx_SocketInputStream::GetObjectThis(arg);
	if (pObj == nullptr) {
		pObj = new Object_wx_SocketInputStream(pEntity, pEntity, OwnerFalse);
		pEntity->AssocWithGura(pObj);
		return ReturnValue(env, arg, Value(pObj));
	}
	pObj->SetEntity(pEntity, pEntity, OwnerFalse);
	pEntity->AssocWithGura(pObj);
	return ReturnValue(env, arg, arg.GetValueThis());
}

//----------------------------------------------------------------------------
// Object implementation for wxSocketInputStream
//----------------------------------------------------------------------------
Object_wx_SocketInputStream::~Object_wx_SocketInputStream()
{
}

Object *Object_wx_SocketInputStream::Clone() const
{
	return nullptr;
}

String Object_wx_SocketInputStream::ToString(bool exprFlag)
{
	String rtn("<wx.SocketInputStream:");
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
// Class implementation for wxSocketInputStream
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_SocketInputStream)
{
	Gura_AssignFunction(SocketInputStream);
}

Gura_ImplementDescendantCreator(wx_SocketInputStream)
{
	return new Object_wx_SocketInputStream((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
