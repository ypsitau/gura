//----------------------------------------------------------------------------
// wxFileDirPickerEvent
//----------------------------------------------------------------------------
#ifndef __CLASS_WX_FILEDIRPICKEREVENT_H__
#define __CLASS_WX_FILEDIRPICKEREVENT_H__
#include <wx/filepicker.h>

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Class declaration for wxFileDirPickerEvent
//----------------------------------------------------------------------------
Gura_DeclareUserClass(wx_FileDirPickerEvent);

//----------------------------------------------------------------------------
// Object declaration for wxFileDirPickerEvent
//----------------------------------------------------------------------------
class Object_wx_FileDirPickerEvent : public Object_wx_CommandEvent {
public:
	Gura_DeclareObjectAccessor(wx_FileDirPickerEvent)
public:
	inline Object_wx_FileDirPickerEvent(wxFileDirPickerEvent *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object_wx_CommandEvent(Gura_UserClass(wx_FileDirPickerEvent), pEntity, pObserver, ownerFlag) {}
	inline Object_wx_FileDirPickerEvent(Class *pClass, wxFileDirPickerEvent *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object_wx_CommandEvent(pClass, pEntity, pObserver, ownerFlag) {}
	virtual ~Object_wx_FileDirPickerEvent();
	virtual Object *Clone() const;
	virtual String ToString(bool exprFlag);
	inline wxFileDirPickerEvent *GetEntity() {
		return static_cast<wxFileDirPickerEvent *>(_pEntity);
	}
	inline wxFileDirPickerEvent *ReleaseEntity() {
		wxFileDirPickerEvent *pEntity = GetEntity();
		InvalidateEntity();
		return pEntity;
	}
	inline bool IsInvalid(Environment &env) const {
		if (_pEntity != nullptr) return false;
		SetError_InvalidWxObject(env, "wxFileDirPickerEvent");
		return true;
	}
};

Gura_EndModuleScope(wx)

#endif
