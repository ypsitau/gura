//----------------------------------------------------------------------------
// wxMouseCaptureLostEvent
// extracted from mcaptevt.tex
//----------------------------------------------------------------------------
#ifndef __CLASS_WX_MOUSECAPTURELOSTEVENT_H__
#define __CLASS_WX_MOUSECAPTURELOSTEVENT_H__

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Class declaration for wxMouseCaptureLostEvent
//----------------------------------------------------------------------------
Gura_DeclareUserClass(wx_MouseCaptureLostEvent);

//----------------------------------------------------------------------------
// Object declaration for wxMouseCaptureLostEvent
//----------------------------------------------------------------------------
class Object_wx_MouseCaptureLostEvent : public Object_wx_Event {
public:
	Gura_DeclareObjectAccessor(wx_MouseCaptureLostEvent)
public:
	inline Object_wx_MouseCaptureLostEvent(wxMouseCaptureLostEvent *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object_wx_Event(Gura_UserClass(wx_MouseCaptureLostEvent), pEntity, pObserver, ownerFlag) {}
	inline Object_wx_MouseCaptureLostEvent(Class *pClass, wxMouseCaptureLostEvent *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object_wx_Event(pClass, pEntity, pObserver, ownerFlag) {}
	virtual ~Object_wx_MouseCaptureLostEvent();
	virtual Object *Clone() const;
	virtual String ToString(bool exprFlag);
	inline wxMouseCaptureLostEvent *GetEntity() {
		return dynamic_cast<wxMouseCaptureLostEvent *>(_pEntity);
	}
	inline wxMouseCaptureLostEvent *ReleaseEntity() {
		wxMouseCaptureLostEvent *pEntity = GetEntity();
		InvalidateEntity();
		return pEntity;
	}
	inline bool IsInvalid(Signal &sig) const {
		if (_pEntity != nullptr) return false;
		SetError_InvalidWxObject(sig, "wxMouseCaptureLostEvent");
		return true;
	}
};

Gura_EndModuleScope(wx)

#endif
