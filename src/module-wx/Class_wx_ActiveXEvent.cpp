//----------------------------------------------------------------------------
// wxActiveXEvent
// extracted from activexevt.tex
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Class derivation
//----------------------------------------------------------------------------
class wx_ActiveXEvent: public wxActiveXEvent, public GuraObjectObserver {
private:
	//Gura::Signal *_pSig;
	Object_wx_ActiveXEvent *_pObj;
public:
	~wx_ActiveXEvent();
	inline void AssocWithGura(Object_wx_ActiveXEvent *pObj) {
		_pObj = pObj;
	}
	// virtual function of GuraObjectObserver
	virtual void GuraObjectDeleted();
};

wx_ActiveXEvent::~wx_ActiveXEvent()
{
	if (_pObj != nullptr) _pObj->InvalidateEntity();
}

void wx_ActiveXEvent::GuraObjectDeleted()
{
	_pObj = nullptr;
}

//----------------------------------------------------------------------------
// Gura interfaces for wxActiveXEvent
//----------------------------------------------------------------------------
Gura_DeclareMethod(wx_ActiveXEvent, ParamCount)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_ActiveXEvent, ParamCount)
{
	Signal &sig = env.GetSignal();
	Object_wx_ActiveXEvent *pThis = Object_wx_ActiveXEvent::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	size_t rtn = pThis->GetEntity()->ParamCount();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_ActiveXEvent, ParamType)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "idx", VTYPE_number, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_ActiveXEvent, ParamType)
{
	Signal &sig = env.GetSignal();
	Object_wx_ActiveXEvent *pThis = Object_wx_ActiveXEvent::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	size_t idx = arg.GetSizeT(0);
	wxString rtn = pThis->GetEntity()->ParamType(idx);
	return ReturnValue(env, arg, Value(static_cast<const char *>(rtn.ToUTF8())));
}

Gura_DeclareMethod(wx_ActiveXEvent, ParamName)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "idx", VTYPE_number, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_ActiveXEvent, ParamName)
{
	Signal &sig = env.GetSignal();
	Object_wx_ActiveXEvent *pThis = Object_wx_ActiveXEvent::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	size_t idx = arg.GetSizeT(0);
	wxString rtn = pThis->GetEntity()->ParamName(idx);
	return ReturnValue(env, arg, Value(static_cast<const char *>(rtn.ToUTF8())));
}

Gura_DeclareMethod(wx_ActiveXEvent, GetDispatchId)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "idx", VTYPE_number, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_ActiveXEvent, GetDispatchId)
{
	Signal &sig = env.GetSignal();
	Object_wx_ActiveXEvent *pThis = Object_wx_ActiveXEvent::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	int idx = arg.GetInt(0);
}

//----------------------------------------------------------------------------
// Object implementation for wxActiveXEvent
//----------------------------------------------------------------------------
Object_wx_ActiveXEvent::~Object_wx_ActiveXEvent()
{
}

Object *Object_wx_ActiveXEvent::Clone() const
{
	return nullptr;
}

String Object_wx_ActiveXEvent::ToString(bool exprFlag)
{
	String rtn("<wx.ActiveXEvent:");
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
// Class implementation for wxActiveXEvent
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_ActiveXEvent)
{
	Gura_AssignMethod(wx_ActiveXEvent, ParamCount);
	Gura_AssignMethod(wx_ActiveXEvent, ParamType);
	Gura_AssignMethod(wx_ActiveXEvent, ParamName);
	Gura_AssignMethod(wx_ActiveXEvent, GetDispatchId);
}

Gura_ImplementDescendantCreator(wx_ActiveXEvent)
{
	return new Object_wx_ActiveXEvent((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
