//----------------------------------------------------------------------------
// wxCollapsiblePaneEvent
//----------------------------------------------------------------------------
#ifndef __CLASS_WX_COLLAPSIBLEPANEEVENT_H__
#define __CLASS_WX_COLLAPSIBLEPANEEVENT_H__
#include <wx/collpane.h>

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Class declaration for wxCollapsiblePaneEvent
//----------------------------------------------------------------------------
Gura_DeclareUserClass(wx_CollapsiblePaneEvent);

//----------------------------------------------------------------------------
// Object declaration for wxCollapsiblePaneEvent
//----------------------------------------------------------------------------
class Object_wx_CollapsiblePaneEvent : public Object_wx_CommandEvent {
public:
	Gura_DeclareObjectAccessor(wx_CollapsiblePaneEvent)
public:
	inline Object_wx_CollapsiblePaneEvent(wxCollapsiblePaneEvent *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object_wx_CommandEvent(Gura_UserClass(wx_CollapsiblePaneEvent), pEntity, pObserver, ownerFlag) {}
	inline Object_wx_CollapsiblePaneEvent(Class *pClass, wxCollapsiblePaneEvent *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object_wx_CommandEvent(pClass, pEntity, pObserver, ownerFlag) {}
	virtual ~Object_wx_CollapsiblePaneEvent();
	virtual Object *Clone() const;
	virtual String ToString(bool exprFlag);
	inline wxCollapsiblePaneEvent *GetEntity() {
		return static_cast<wxCollapsiblePaneEvent *>(_pEntity);
	}
	inline wxCollapsiblePaneEvent *ReleaseEntity() {
		wxCollapsiblePaneEvent *pEntity = GetEntity();
		InvalidateEntity();
		return pEntity;
	}
	inline bool IsInvalid(Environment &env) const {
		if (_pEntity != nullptr) return false;
		SetError_InvalidWxObject(env, "wxCollapsiblePaneEvent");
		return true;
	}
};

Gura_EndModuleScope(wx)

#endif
