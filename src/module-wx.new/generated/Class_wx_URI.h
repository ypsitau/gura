//----------------------------------------------------------------------------
// wxURI
//----------------------------------------------------------------------------
#ifndef __CLASS_WX_URI_H__
#define __CLASS_WX_URI_H__
#include <wx/uri.h>

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Class declaration for wxURI
//----------------------------------------------------------------------------
Gura_DeclareUserClass(wx_URI);

//----------------------------------------------------------------------------
// Object declaration for wxURI
//----------------------------------------------------------------------------
class Object_wx_URI : public Object_wx_Object {
public:
	Gura_DeclareObjectAccessor(wx_URI)
public:
	inline Object_wx_URI(wxURI *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object_wx_Object(Gura_UserClass(wx_URI), pEntity, pObserver, ownerFlag) {}
	inline Object_wx_URI(Class *pClass, wxURI *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object_wx_Object(pClass, pEntity, pObserver, ownerFlag) {}
	virtual ~Object_wx_URI();
	virtual Object *Clone() const;
	virtual String ToString(bool exprFlag);
	inline wxURI *GetEntity() {
		return static_cast<wxURI *>(_pEntity);
	}
	inline wxURI *ReleaseEntity() {
		wxURI *pEntity = GetEntity();
		InvalidateEntity();
		return pEntity;
	}
	inline bool IsInvalid(Environment &env) const {
		if (_pEntity != nullptr) return false;
		SetError_InvalidWxObject(env, "wxURI");
		return true;
	}
};

Gura_EndModuleScope(wx)

#endif
