//----------------------------------------------------------------------------
// wxMenu
//----------------------------------------------------------------------------
#ifndef __CLASS_WX_MENU_H__
#define __CLASS_WX_MENU_H__
#include <wx/menu.h>

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Class declaration for wxMenu
//----------------------------------------------------------------------------
Gura_DeclareUserClass(wx_Menu);

//----------------------------------------------------------------------------
// Object declaration for wxMenu
//----------------------------------------------------------------------------
class Object_wx_Menu : public Object_wx_EvtHandler {
public:
	Gura_DeclareObjectAccessor(wx_Menu)
public:
	inline Object_wx_Menu(wxMenu *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object_wx_EvtHandler(Gura_UserClass(wx_Menu), pEntity, pObserver, ownerFlag) {}
	inline Object_wx_Menu(Class *pClass, wxMenu *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object_wx_EvtHandler(pClass, pEntity, pObserver, ownerFlag) {}
	virtual ~Object_wx_Menu();
	virtual Object *Clone() const;
	virtual String ToString(bool exprFlag);
	inline wxMenu *GetEntity() {
		return static_cast<wxMenu *>(_pEntity);
	}
	inline wxMenu *ReleaseEntity() {
		wxMenu *pEntity = GetEntity();
		InvalidateEntity();
		return pEntity;
	}
	inline bool IsInvalid(Environment &env) const {
		if (_pEntity != nullptr) return false;
		SetError_InvalidWxObject(env, "wxMenu");
		return true;
	}
};

Gura_EndModuleScope(wx)

#endif
