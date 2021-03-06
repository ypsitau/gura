//----------------------------------------------------------------------------
// wxPostScriptDC
//----------------------------------------------------------------------------
#ifndef __CLASS_WX_POSTSCRIPTDC_H__
#define __CLASS_WX_POSTSCRIPTDC_H__
#include <wx/dcps.h>

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Class declaration for wxPostScriptDC
//----------------------------------------------------------------------------
Gura_DeclareUserClass(wx_PostScriptDC);

//----------------------------------------------------------------------------
// Object declaration for wxPostScriptDC
//----------------------------------------------------------------------------
class Object_wx_PostScriptDC : public Object_wx_DC {
public:
	Gura_DeclareObjectAccessor(wx_PostScriptDC)
public:
	inline Object_wx_PostScriptDC(wxPostScriptDC *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object_wx_DC(Gura_UserClass(wx_PostScriptDC), pEntity, pObserver, ownerFlag) {}
	inline Object_wx_PostScriptDC(Class *pClass, wxPostScriptDC *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object_wx_DC(pClass, pEntity, pObserver, ownerFlag) {}
	virtual ~Object_wx_PostScriptDC();
	virtual Object *Clone() const;
	virtual String ToString(bool exprFlag);
	inline wxPostScriptDC *GetEntity() {
		return static_cast<wxPostScriptDC *>(_pEntity);
	}
	inline wxPostScriptDC *ReleaseEntity() {
		wxPostScriptDC *pEntity = GetEntity();
		InvalidateEntity();
		return pEntity;
	}
	inline bool IsInvalid(Environment &env) const {
		if (_pEntity != nullptr) return false;
		SetError_InvalidWxObject(env, "wxPostScriptDC");
		return true;
	}
};

Gura_EndModuleScope(wx)

#endif
