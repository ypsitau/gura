//----------------------------------------------------------------------------
// wxCondition
// extracted from conditn.tex
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Class derivation
//----------------------------------------------------------------------------
class wx_Condition: public wxCondition, public GuraObjectObserver {
private:
	//Gura::Signal *_pSig;
	Object_wx_Condition *_pObj;
public:
	inline wx_Condition(wxMutex& mutex) : wxCondition(mutex), _pObj(nullptr) {}
	~wx_Condition();
	inline void AssocWithGura(Object_wx_Condition *pObj) {
		_pObj = pObj;
	}
	// virtual function of GuraObjectObserver
	virtual void GuraObjectDeleted();
};

wx_Condition::~wx_Condition()
{
	if (_pObj != nullptr) _pObj->InvalidateEntity();
}

void wx_Condition::GuraObjectDeleted()
{
	_pObj = nullptr;
}

//----------------------------------------------------------------------------
// Gura interfaces for wxCondition
//----------------------------------------------------------------------------
Gura_DeclareFunction(Condition)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	SetClassToConstruct(Gura_UserClass(wx_Condition));
	DeclareArg(env, "mutex", VTYPE_wx_Mutex, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(Condition)
{
	Signal &sig = env.GetSignal();
	if (!CheckWxReady(sig)) return Value::Nil;
	wxMutex *mutex = Object_wx_Mutex::GetObject(arg, 0)->GetEntity();
	wx_Condition *pEntity = new wx_Condition(*mutex);
	Object_wx_Condition *pObj = Object_wx_Condition::GetObjectThis(arg);
	if (pObj == nullptr) {
		pObj = new Object_wx_Condition(pEntity, pEntity, OwnerFalse);
		pEntity->AssocWithGura(pObj);
		return ReturnValue(env, arg, Value(pObj));
	}
	pObj->SetEntity(pEntity, pEntity, OwnerFalse);
	pEntity->AssocWithGura(pObj);
	return ReturnValue(env, arg, arg.GetValueThis());
}

Gura_DeclareMethod(wx_Condition, Broadcast)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_Condition, Broadcast)
{
	Signal &sig = env.GetSignal();
	Object_wx_Condition *pThis = Object_wx_Condition::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	pThis->GetEntity()->Broadcast();
	return Value::Nil;
}

Gura_DeclareMethod(wx_Condition, IsOk)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_Condition, IsOk)
{
	Signal &sig = env.GetSignal();
	Object_wx_Condition *pThis = Object_wx_Condition::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	bool rtn = pThis->GetEntity()->IsOk();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_Condition, Signal)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_Condition, Signal)
{
	Signal &sig = env.GetSignal();
	Object_wx_Condition *pThis = Object_wx_Condition::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	pThis->GetEntity()->Signal();
	return Value::Nil;
}

Gura_DeclareMethod(wx_Condition, Wait)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_Condition, Wait)
{
	Signal &sig = env.GetSignal();
	Object_wx_Condition *pThis = Object_wx_Condition::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxCondError rtn = pThis->GetEntity()->Wait();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_Condition, WaitTimeout)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "milliseconds", VTYPE_number, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_Condition, WaitTimeout)
{
	Signal &sig = env.GetSignal();
	Object_wx_Condition *pThis = Object_wx_Condition::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	unsigned milliseconds = arg.GetInt(0);
	wxCondError rtn = pThis->GetEntity()->WaitTimeout(milliseconds);
	return ReturnValue(env, arg, Value(rtn));
}

//----------------------------------------------------------------------------
// Object implementation for wxCondition
//----------------------------------------------------------------------------
Object_wx_Condition::~Object_wx_Condition()
{
	if (_pEntity != nullptr) NotifyGuraObjectDeleted();
	if (_ownerFlag) delete _pEntity;
	_pEntity = nullptr;
}

Object *Object_wx_Condition::Clone() const
{
	return nullptr;
}

String Object_wx_Condition::ToString(bool exprFlag)
{
	String rtn("<wx.Condition:");
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
// Class implementation for wxCondition
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_Condition)
{
	Gura_AssignFunction(Condition);
	Gura_AssignMethod(wx_Condition, Broadcast);
	Gura_AssignMethod(wx_Condition, IsOk);
	Gura_AssignMethod(wx_Condition, Signal);
	Gura_AssignMethod(wx_Condition, Wait);
	Gura_AssignMethod(wx_Condition, WaitTimeout);
}

Gura_ImplementDescendantCreator(wx_Condition)
{
	return new Object_wx_Condition((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
