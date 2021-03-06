//----------------------------------------------------------------------------
// wxLayoutConstraints
//----------------------------------------------------------------------------
#ifndef __CLASS_WX_LAYOUTCONSTRAINTS_H__
#define __CLASS_WX_LAYOUTCONSTRAINTS_H__
#include <wx/layout.h>

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Class declaration for wxLayoutConstraints
//----------------------------------------------------------------------------
Gura_DeclareUserClass(wx_LayoutConstraints);

//----------------------------------------------------------------------------
// Object declaration for wxLayoutConstraints
//----------------------------------------------------------------------------
class Object_wx_LayoutConstraints : public Object_wx_Object {
public:
	Gura_DeclareObjectAccessor(wx_LayoutConstraints)
public:
	inline Object_wx_LayoutConstraints(wxLayoutConstraints *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object_wx_Object(Gura_UserClass(wx_LayoutConstraints), pEntity, pObserver, ownerFlag) {}
	inline Object_wx_LayoutConstraints(Class *pClass, wxLayoutConstraints *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object_wx_Object(pClass, pEntity, pObserver, ownerFlag) {}
	virtual ~Object_wx_LayoutConstraints();
	virtual Object *Clone() const;
	virtual String ToString(bool exprFlag);
	inline wxLayoutConstraints *GetEntity() {
		return static_cast<wxLayoutConstraints *>(_pEntity);
	}
	inline wxLayoutConstraints *ReleaseEntity() {
		wxLayoutConstraints *pEntity = GetEntity();
		InvalidateEntity();
		return pEntity;
	}
	inline bool IsInvalid(Environment &env) const {
		if (_pEntity != nullptr) return false;
		SetError_InvalidWxObject(env, "wxLayoutConstraints");
		return true;
	}
};

Gura_EndModuleScope(wx)

#endif
