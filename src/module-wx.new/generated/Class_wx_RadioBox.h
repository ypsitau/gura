//----------------------------------------------------------------------------
// wxRadioBox
//----------------------------------------------------------------------------
#ifndef __CLASS_WX_RADIOBOX_H__
#define __CLASS_WX_RADIOBOX_H__
#include <wx/radiobox.h>

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Class declaration for wxRadioBox
//----------------------------------------------------------------------------
Gura_DeclareUserClass(wx_RadioBox);

//----------------------------------------------------------------------------
// Object declaration for wxRadioBox
//----------------------------------------------------------------------------
class Object_wx_RadioBox : public Object_wx_Control {
public:
	Gura_DeclareObjectAccessor(wx_RadioBox)
public:
	inline Object_wx_RadioBox(wxRadioBox *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object_wx_Control(Gura_UserClass(wx_RadioBox), pEntity, pObserver, ownerFlag) {}
	inline Object_wx_RadioBox(Class *pClass, wxRadioBox *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object_wx_Control(pClass, pEntity, pObserver, ownerFlag) {}
	virtual ~Object_wx_RadioBox();
	virtual Object *Clone() const;
	virtual String ToString(bool exprFlag);
	inline wxRadioBox *GetEntity() {
		return static_cast<wxRadioBox *>(_pEntity);
	}
	inline wxRadioBox *ReleaseEntity() {
		wxRadioBox *pEntity = GetEntity();
		InvalidateEntity();
		return pEntity;
	}
	inline bool IsInvalid(Environment &env) const {
		if (_pEntity != nullptr) return false;
		SetError_InvalidWxObject(env, "wxRadioBox");
		return true;
	}
};

Gura_EndModuleScope(wx)

#endif
