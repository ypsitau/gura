//----------------------------------------------------------------------------
// wxSemaphore
// extracted from semaphor.tex
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Class derivation
//----------------------------------------------------------------------------
class wx_Semaphore: public wxSemaphore, public GuraObjectObserver {
private:
	//Gura::Signal *_pSig;
	Object_wx_Semaphore *_pObj;
public:
	inline wx_Semaphore(int initialcount, int maxcount) : wxSemaphore(initialcount, maxcount), _pObj(nullptr) {}
	~wx_Semaphore();
	inline void AssocWithGura(Object_wx_Semaphore *pObj) {
		_pObj = pObj;
	}
	// virtual function of GuraObjectObserver
	virtual void GuraObjectDeleted();
};

wx_Semaphore::~wx_Semaphore()
{
	if (_pObj != nullptr) _pObj->InvalidateEntity();
}

void wx_Semaphore::GuraObjectDeleted()
{
	_pObj = nullptr;
}

//----------------------------------------------------------------------------
// Gura interfaces for wxSemaphore
//----------------------------------------------------------------------------
Gura_DeclareFunction(Semaphore)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	SetClassToConstruct(Gura_UserClass(wx_Semaphore));
	DeclareArg(env, "initialcount", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareArg(env, "maxcount", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(Semaphore)
{
	Signal &sig = env.GetSignal();
	if (!CheckWxReady(sig)) return Value::Nil;
	int initialcount = 0;
	if (arg.IsValid(0)) initialcount = arg.GetInt(0);
	int maxcount = 0;
	if (arg.IsValid(1)) maxcount = arg.GetInt(1);
	wx_Semaphore *pEntity = new wx_Semaphore(initialcount, maxcount);
	Object_wx_Semaphore *pObj = Object_wx_Semaphore::GetObjectThis(arg);
	if (pObj == nullptr) {
		pObj = new Object_wx_Semaphore(pEntity, pEntity, OwnerFalse);
		pEntity->AssocWithGura(pObj);
		return ReturnValue(env, arg, Value(pObj));
	}
	pObj->SetEntity(pEntity, pEntity, OwnerFalse);
	pEntity->AssocWithGura(pObj);
	return ReturnValue(env, arg, arg.GetValueThis());
}

Gura_DeclareMethod(wx_Semaphore, Post)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_Semaphore, Post)
{
	Signal &sig = env.GetSignal();
	Object_wx_Semaphore *pThis = Object_wx_Semaphore::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxSemaError rtn = pThis->GetEntity()->Post();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_Semaphore, TryWait)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_Semaphore, TryWait)
{
	Signal &sig = env.GetSignal();
	Object_wx_Semaphore *pThis = Object_wx_Semaphore::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxSemaError rtn = pThis->GetEntity()->TryWait();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_Semaphore, Wait)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_Semaphore, Wait)
{
	Signal &sig = env.GetSignal();
	Object_wx_Semaphore *pThis = Object_wx_Semaphore::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxSemaError rtn = pThis->GetEntity()->Wait();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_Semaphore, WaitTimeout)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "timeout_millis", VTYPE_number, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_Semaphore, WaitTimeout)
{
	Signal &sig = env.GetSignal();
	Object_wx_Semaphore *pThis = Object_wx_Semaphore::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	unsigned timeout_millis = arg.GetInt(0);
	wxSemaError rtn = pThis->GetEntity()->WaitTimeout(timeout_millis);
	return ReturnValue(env, arg, Value(rtn));
}

//----------------------------------------------------------------------------
// Object implementation for wxSemaphore
//----------------------------------------------------------------------------
Object_wx_Semaphore::~Object_wx_Semaphore()
{
	if (_pEntity != nullptr) NotifyGuraObjectDeleted();
	if (_ownerFlag) delete _pEntity;
	_pEntity = nullptr;
}

Object *Object_wx_Semaphore::Clone() const
{
	return nullptr;
}

String Object_wx_Semaphore::ToString(bool exprFlag)
{
	String rtn("<wx.Semaphore:");
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
// Class implementation for wxSemaphore
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_Semaphore)
{
	Gura_AssignFunction(Semaphore);
	Gura_AssignMethod(wx_Semaphore, Post);
	Gura_AssignMethod(wx_Semaphore, TryWait);
	Gura_AssignMethod(wx_Semaphore, Wait);
	Gura_AssignMethod(wx_Semaphore, WaitTimeout);
}

Gura_ImplementDescendantCreator(wx_Semaphore)
{
	return new Object_wx_Semaphore((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
