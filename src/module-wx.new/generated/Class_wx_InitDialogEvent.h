//----------------------------------------------------------------------------
// wxInitDialogEvent
//----------------------------------------------------------------------------
#ifndef __CLASS_WX_INITDIALOGEVENT_H__
#define __CLASS_WX_INITDIALOGEVENT_H__
#include <wx/event.h>

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Class declaration for wxInitDialogEvent
//----------------------------------------------------------------------------
Gura_DeclareUserClass(wx_InitDialogEvent);

//----------------------------------------------------------------------------
// Object declaration for wxInitDialogEvent
//----------------------------------------------------------------------------
class Object_wx_InitDialogEvent : public Object_wx_Event {
public:
	Gura_DeclareObjectAccessor(wx_InitDialogEvent)
public:
	inline Object_wx_InitDialogEvent(wxInitDialogEvent *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object_wx_Event(Gura_UserClass(wx_InitDialogEvent), pEntity, pObserver, ownerFlag) {}
	inline Object_wx_InitDialogEvent(Class *pClass, wxInitDialogEvent *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object_wx_Event(pClass, pEntity, pObserver, ownerFlag) {}
	virtual ~Object_wx_InitDialogEvent();
	virtual Object *Clone() const;
	virtual String ToString(bool exprFlag);
	inline wxInitDialogEvent *GetEntity() {
		return static_cast<wxInitDialogEvent *>(_pEntity);
	}
	inline wxInitDialogEvent *ReleaseEntity() {
		wxInitDialogEvent *pEntity = GetEntity();
		InvalidateEntity();
		return pEntity;
	}
	inline bool IsInvalid(Environment &env) const {
		if (_pEntity != nullptr) return false;
		SetError_InvalidWxObject(env, "wxInitDialogEvent");
		return true;
	}
};

Gura_EndModuleScope(wx)

#endif
