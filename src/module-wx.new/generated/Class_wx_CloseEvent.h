//----------------------------------------------------------------------------
// wxCloseEvent
//----------------------------------------------------------------------------
#ifndef __CLASS_WX_CLOSEEVENT_H__
#define __CLASS_WX_CLOSEEVENT_H__
#include <wx/event.h>

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Class declaration for wxCloseEvent
//----------------------------------------------------------------------------
Gura_DeclareUserClass(wx_CloseEvent);

//----------------------------------------------------------------------------
// Object declaration for wxCloseEvent
//----------------------------------------------------------------------------
class Object_wx_CloseEvent : public Object_wx_Event {
public:
	Gura_DeclareObjectAccessor(wx_CloseEvent)
public:
	inline Object_wx_CloseEvent(wxCloseEvent *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object_wx_Event(Gura_UserClass(wx_CloseEvent), pEntity, pObserver, ownerFlag) {}
	inline Object_wx_CloseEvent(Class *pClass, wxCloseEvent *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object_wx_Event(pClass, pEntity, pObserver, ownerFlag) {}
	virtual ~Object_wx_CloseEvent();
	virtual Object *Clone() const;
	virtual String ToString(bool exprFlag);
	inline wxCloseEvent *GetEntity() {
		return static_cast<wxCloseEvent *>(_pEntity);
	}
	inline wxCloseEvent *ReleaseEntity() {
		wxCloseEvent *pEntity = GetEntity();
		InvalidateEntity();
		return pEntity;
	}
	inline bool IsInvalid(Environment &env) const {
		if (_pEntity != nullptr) return false;
		SetError_InvalidWxObject(env, "wxCloseEvent");
		return true;
	}
};

Gura_EndModuleScope(wx)

#endif
