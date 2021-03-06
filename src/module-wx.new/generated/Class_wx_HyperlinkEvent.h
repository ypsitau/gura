//----------------------------------------------------------------------------
// wxHyperlinkEvent
//----------------------------------------------------------------------------
#ifndef __CLASS_WX_HYPERLINKEVENT_H__
#define __CLASS_WX_HYPERLINKEVENT_H__
#include <wx/hyperlink.h>

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Class declaration for wxHyperlinkEvent
//----------------------------------------------------------------------------
Gura_DeclareUserClass(wx_HyperlinkEvent);

//----------------------------------------------------------------------------
// Object declaration for wxHyperlinkEvent
//----------------------------------------------------------------------------
class Object_wx_HyperlinkEvent : public Object_wx_CommandEvent {
public:
	Gura_DeclareObjectAccessor(wx_HyperlinkEvent)
public:
	inline Object_wx_HyperlinkEvent(wxHyperlinkEvent *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object_wx_CommandEvent(Gura_UserClass(wx_HyperlinkEvent), pEntity, pObserver, ownerFlag) {}
	inline Object_wx_HyperlinkEvent(Class *pClass, wxHyperlinkEvent *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object_wx_CommandEvent(pClass, pEntity, pObserver, ownerFlag) {}
	virtual ~Object_wx_HyperlinkEvent();
	virtual Object *Clone() const;
	virtual String ToString(bool exprFlag);
	inline wxHyperlinkEvent *GetEntity() {
		return static_cast<wxHyperlinkEvent *>(_pEntity);
	}
	inline wxHyperlinkEvent *ReleaseEntity() {
		wxHyperlinkEvent *pEntity = GetEntity();
		InvalidateEntity();
		return pEntity;
	}
	inline bool IsInvalid(Environment &env) const {
		if (_pEntity != nullptr) return false;
		SetError_InvalidWxObject(env, "wxHyperlinkEvent");
		return true;
	}
};

Gura_EndModuleScope(wx)

#endif
