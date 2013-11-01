//----------------------------------------------------------------------------
// wxIdleEvent
// extracted from idleevt.tex
//----------------------------------------------------------------------------
#ifndef __CLASS_WX_IDLEEVENT_H__
#define __CLASS_WX_IDLEEVENT_H__

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Class declaration for wxIdleEvent
//----------------------------------------------------------------------------
Gura_DeclareUserClass(wx_IdleEvent);

//----------------------------------------------------------------------------
// Object declaration for wxIdleEvent
//----------------------------------------------------------------------------
class Object_wx_IdleEvent : public Object_wx_Event {
public:
	Gura_DeclareObjectAccessor(wx_IdleEvent)
public:
	inline Object_wx_IdleEvent(wxIdleEvent *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object_wx_Event(Gura_UserClass(wx_IdleEvent), pEntity, pObserver, ownerFlag) {}
	inline Object_wx_IdleEvent(Class *pClass, wxIdleEvent *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object_wx_Event(pClass, pEntity, pObserver, ownerFlag) {}
	virtual ~Object_wx_IdleEvent();
	virtual Object *Clone() const;
	virtual String ToString(bool exprFlag);
	inline wxIdleEvent *GetEntity() {
		return dynamic_cast<wxIdleEvent *>(_pEntity);
	}
	inline wxIdleEvent *ReleaseEntity() {
		wxIdleEvent *pEntity = GetEntity();
		InvalidateEntity();
		return pEntity;
	}
	inline bool IsInvalid(Signal sig) const {
		if (_pEntity != NULL) return false;
		SetError_InvalidWxObject(sig, "wxIdleEvent");
		return true;
	}
};

Gura_EndModuleScope(wx)

#endif
