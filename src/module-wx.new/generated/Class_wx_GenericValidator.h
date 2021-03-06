//----------------------------------------------------------------------------
// wxGenericValidator
//----------------------------------------------------------------------------
#ifndef __CLASS_WX_GENERICVALIDATOR_H__
#define __CLASS_WX_GENERICVALIDATOR_H__
#include <wx/valgen.h>

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Class declaration for wxGenericValidator
//----------------------------------------------------------------------------
Gura_DeclareUserClass(wx_GenericValidator);

//----------------------------------------------------------------------------
// Object declaration for wxGenericValidator
//----------------------------------------------------------------------------
class Object_wx_GenericValidator : public Object_wx_Validator {
public:
	Gura_DeclareObjectAccessor(wx_GenericValidator)
public:
	inline Object_wx_GenericValidator(wxGenericValidator *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object_wx_Validator(Gura_UserClass(wx_GenericValidator), pEntity, pObserver, ownerFlag) {}
	inline Object_wx_GenericValidator(Class *pClass, wxGenericValidator *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object_wx_Validator(pClass, pEntity, pObserver, ownerFlag) {}
	virtual ~Object_wx_GenericValidator();
	virtual Object *Clone() const;
	virtual String ToString(bool exprFlag);
	inline wxGenericValidator *GetEntity() {
		return static_cast<wxGenericValidator *>(_pEntity);
	}
	inline wxGenericValidator *ReleaseEntity() {
		wxGenericValidator *pEntity = GetEntity();
		InvalidateEntity();
		return pEntity;
	}
	inline bool IsInvalid(Environment &env) const {
		if (_pEntity != nullptr) return false;
		SetError_InvalidWxObject(env, "wxGenericValidator");
		return true;
	}
};

Gura_EndModuleScope(wx)

#endif
