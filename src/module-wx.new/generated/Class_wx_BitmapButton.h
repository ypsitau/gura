//----------------------------------------------------------------------------
// wxBitmapButton
//----------------------------------------------------------------------------
#ifndef __CLASS_WX_BITMAPBUTTON_H__
#define __CLASS_WX_BITMAPBUTTON_H__
#include <wx/bmpbuttn.h>

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Class declaration for wxBitmapButton
//----------------------------------------------------------------------------
Gura_DeclareUserClass(wx_BitmapButton);

//----------------------------------------------------------------------------
// Object declaration for wxBitmapButton
//----------------------------------------------------------------------------
class Object_wx_BitmapButton : public Object_wx_Button {
public:
	Gura_DeclareObjectAccessor(wx_BitmapButton)
public:
	inline Object_wx_BitmapButton(wxBitmapButton *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object_wx_Button(Gura_UserClass(wx_BitmapButton), pEntity, pObserver, ownerFlag) {}
	inline Object_wx_BitmapButton(Class *pClass, wxBitmapButton *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object_wx_Button(pClass, pEntity, pObserver, ownerFlag) {}
	virtual ~Object_wx_BitmapButton();
	virtual Object *Clone() const;
	virtual String ToString(bool exprFlag);
	inline wxBitmapButton *GetEntity() {
		return static_cast<wxBitmapButton *>(_pEntity);
	}
	inline wxBitmapButton *ReleaseEntity() {
		wxBitmapButton *pEntity = GetEntity();
		InvalidateEntity();
		return pEntity;
	}
	inline bool IsInvalid(Environment &env) const {
		if (_pEntity != nullptr) return false;
		SetError_InvalidWxObject(env, "wxBitmapButton");
		return true;
	}
};

Gura_EndModuleScope(wx)

#endif
