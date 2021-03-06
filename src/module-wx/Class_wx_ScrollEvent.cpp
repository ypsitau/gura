//----------------------------------------------------------------------------
// wxScrollEvent
// extracted from scrolevt.tex
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Class derivation
//----------------------------------------------------------------------------
class wx_ScrollEvent: public wxScrollEvent, public GuraObjectObserver {
private:
	//Gura::Signal *_pSig;
	Object_wx_ScrollEvent *_pObj;
public:
	inline wx_ScrollEvent(WXTYPE commandType, int id, int pos, int orientation) : wxScrollEvent(commandType, id, pos, orientation), _pObj(nullptr) {}
	~wx_ScrollEvent();
	inline void AssocWithGura(Object_wx_ScrollEvent *pObj) {
		_pObj = pObj;
	}
	// virtual function of GuraObjectObserver
	virtual void GuraObjectDeleted();
};

wx_ScrollEvent::~wx_ScrollEvent()
{
	if (_pObj != nullptr) _pObj->InvalidateEntity();
}

void wx_ScrollEvent::GuraObjectDeleted()
{
	_pObj = nullptr;
}

//----------------------------------------------------------------------------
// Gura interfaces for wxScrollEvent
//----------------------------------------------------------------------------
Gura_DeclareFunction(ScrollEvent)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	SetClassToConstruct(Gura_UserClass(wx_ScrollEvent));
	DeclareArg(env, "commandType", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareArg(env, "id", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareArg(env, "pos", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareArg(env, "orientation", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(ScrollEvent)
{
	Signal &sig = env.GetSignal();
	if (!CheckWxReady(sig)) return Value::Nil;
	WXTYPE commandType = 0;
	if (arg.IsValid(0)) commandType = static_cast<WXTYPE>(arg.GetInt(0));
	int id = 0;
	if (arg.IsValid(1)) id = arg.GetInt(1);
	int pos = 0;
	if (arg.IsValid(2)) pos = arg.GetInt(2);
	int orientation = 0;
	if (arg.IsValid(3)) orientation = arg.GetInt(3);
	wx_ScrollEvent *pEntity = new wx_ScrollEvent(commandType, id, pos, orientation);
	Object_wx_ScrollEvent *pObj = Object_wx_ScrollEvent::GetObjectThis(arg);
	if (pObj == nullptr) {
		pObj = new Object_wx_ScrollEvent(pEntity, pEntity, OwnerFalse);
		pEntity->AssocWithGura(pObj);
		return ReturnValue(env, arg, Value(pObj));
	}
	pObj->SetEntity(pEntity, pEntity, OwnerFalse);
	pEntity->AssocWithGura(pObj);
	return ReturnValue(env, arg, arg.GetValueThis());
}

Gura_DeclareMethod(wx_ScrollEvent, GetOrientation)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_ScrollEvent, GetOrientation)
{
	Signal &sig = env.GetSignal();
	Object_wx_ScrollEvent *pThis = Object_wx_ScrollEvent::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	int rtn = pThis->GetEntity()->GetOrientation();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_ScrollEvent, GetPosition)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_ScrollEvent, GetPosition)
{
	Signal &sig = env.GetSignal();
	Object_wx_ScrollEvent *pThis = Object_wx_ScrollEvent::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	int rtn = pThis->GetEntity()->GetPosition();
	return ReturnValue(env, arg, Value(rtn));
}

//----------------------------------------------------------------------------
// Object implementation for wxScrollEvent
//----------------------------------------------------------------------------
Object_wx_ScrollEvent::~Object_wx_ScrollEvent()
{
}

Object *Object_wx_ScrollEvent::Clone() const
{
	return nullptr;
}

String Object_wx_ScrollEvent::ToString(bool exprFlag)
{
	String rtn("<wx.ScrollEvent:");
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
// Class implementation for wxScrollEvent
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_ScrollEvent)
{
	Gura_AssignFunction(ScrollEvent);
	Gura_AssignMethod(wx_ScrollEvent, GetOrientation);
	Gura_AssignMethod(wx_ScrollEvent, GetPosition);
}

Gura_ImplementDescendantCreator(wx_ScrollEvent)
{
	return new Object_wx_ScrollEvent((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
