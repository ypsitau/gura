//----------------------------------------------------------------------------
// wxNotifyEvent
// extracted from notifevt.tex
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Class derivation
//----------------------------------------------------------------------------
class wx_NotifyEvent: public wxNotifyEvent, public GuraObjectObserver {
private:
	//Gura::Signal *_pSig;
	Object_wx_NotifyEvent *_pObj;
public:
	inline wx_NotifyEvent(wxEventType eventType, int id) : wxNotifyEvent(eventType, id), _pObj(nullptr) {}
	~wx_NotifyEvent();
	inline void AssocWithGura(Object_wx_NotifyEvent *pObj) {
		_pObj = pObj;
	}
	// virtual function of GuraObjectObserver
	virtual void GuraObjectDeleted();
};

wx_NotifyEvent::~wx_NotifyEvent()
{
	if (_pObj != nullptr) _pObj->InvalidateEntity();
}

void wx_NotifyEvent::GuraObjectDeleted()
{
	_pObj = nullptr;
}

//----------------------------------------------------------------------------
// Gura interfaces for wxNotifyEvent
//----------------------------------------------------------------------------
Gura_DeclareFunction(NotifyEvent)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	SetClassToConstruct(Gura_UserClass(wx_NotifyEvent));
	DeclareArg(env, "eventType", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareArg(env, "id", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(NotifyEvent)
{
	Signal &sig = env.GetSignal();
	if (!CheckWxReady(sig)) return Value::Nil;
	wxEventType eventType = wxEVT_NULL;
	if (arg.IsValid(0)) eventType = static_cast<wxEventType>(arg.GetInt(0));
	int id = 0;
	if (arg.IsValid(1)) id = arg.GetInt(1);
	wx_NotifyEvent *pEntity = new wx_NotifyEvent(eventType, id);
	Object_wx_NotifyEvent *pObj = Object_wx_NotifyEvent::GetObjectThis(arg);
	if (pObj == nullptr) {
		pObj = new Object_wx_NotifyEvent(pEntity, pEntity, OwnerFalse);
		pEntity->AssocWithGura(pObj);
		return ReturnValue(env, arg, Value(pObj));
	}
	pObj->SetEntity(pEntity, pEntity, OwnerFalse);
	pEntity->AssocWithGura(pObj);
	return ReturnValue(env, arg, arg.GetValueThis());
}

Gura_DeclareMethod(wx_NotifyEvent, Allow)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_NotifyEvent, Allow)
{
	Signal &sig = env.GetSignal();
	Object_wx_NotifyEvent *pThis = Object_wx_NotifyEvent::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	pThis->GetEntity()->Allow();
	return Value::Nil;
}

Gura_DeclareMethod(wx_NotifyEvent, IsAllowed)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_NotifyEvent, IsAllowed)
{
	Signal &sig = env.GetSignal();
	Object_wx_NotifyEvent *pThis = Object_wx_NotifyEvent::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	bool rtn = pThis->GetEntity()->IsAllowed();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_NotifyEvent, Veto)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_NotifyEvent, Veto)
{
	Signal &sig = env.GetSignal();
	Object_wx_NotifyEvent *pThis = Object_wx_NotifyEvent::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	pThis->GetEntity()->Veto();
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Object implementation for wxNotifyEvent
//----------------------------------------------------------------------------
Object_wx_NotifyEvent::~Object_wx_NotifyEvent()
{
}

Object *Object_wx_NotifyEvent::Clone() const
{
	return nullptr;
}

String Object_wx_NotifyEvent::ToString(bool exprFlag)
{
	String rtn("<wx.NotifyEvent:");
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
// Class implementation for wxNotifyEvent
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_NotifyEvent)
{
	Gura_AssignFunction(NotifyEvent);
	Gura_AssignMethod(wx_NotifyEvent, Allow);
	Gura_AssignMethod(wx_NotifyEvent, IsAllowed);
	Gura_AssignMethod(wx_NotifyEvent, Veto);
}

Gura_ImplementDescendantCreator(wx_NotifyEvent)
{
	return new Object_wx_NotifyEvent((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
