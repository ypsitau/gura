//----------------------------------------------------------------------------
// wxSimpleHelpProvider
//----------------------------------------------------------------------------
#ifndef __CLASS_WX_SIMPLEHELPPROVIDER_H__
#define __CLASS_WX_SIMPLEHELPPROVIDER_H__
#include <wx/cshelp.h>

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Class declaration for wxSimpleHelpProvider
//----------------------------------------------------------------------------
Gura_DeclareUserClass(wx_SimpleHelpProvider);

//----------------------------------------------------------------------------
// Object declaration for wxSimpleHelpProvider
//----------------------------------------------------------------------------
class Object_wx_SimpleHelpProvider : public Object_wx_HelpProvider {
public:
	Gura_DeclareObjectAccessor(wx_SimpleHelpProvider)
public:
	inline Object_wx_SimpleHelpProvider(wxSimpleHelpProvider *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object_wx_HelpProvider(Gura_UserClass(wx_SimpleHelpProvider), pEntity, pObserver, ownerFlag) {}
	inline Object_wx_SimpleHelpProvider(Class *pClass, wxSimpleHelpProvider *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object_wx_HelpProvider(pClass, pEntity, pObserver, ownerFlag) {}
	virtual ~Object_wx_SimpleHelpProvider();
	virtual Object *Clone() const;
	virtual String ToString(bool exprFlag);
	inline wxSimpleHelpProvider *GetEntity() {
		return static_cast<wxSimpleHelpProvider *>(_pEntity);
	}
	inline wxSimpleHelpProvider *ReleaseEntity() {
		wxSimpleHelpProvider *pEntity = GetEntity();
		InvalidateEntity();
		return pEntity;
	}
	inline bool IsInvalid(Environment &env) const {
		if (_pEntity != nullptr) return false;
		SetError_InvalidWxObject(env, "wxSimpleHelpProvider");
		return true;
	}
};

Gura_EndModuleScope(wx)

#endif
