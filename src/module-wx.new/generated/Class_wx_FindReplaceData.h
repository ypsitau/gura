//----------------------------------------------------------------------------
// wxFindReplaceData
//----------------------------------------------------------------------------
#ifndef __CLASS_WX_FINDREPLACEDATA_H__
#define __CLASS_WX_FINDREPLACEDATA_H__
#include <wx/fdrepdlg.h>

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Class declaration for wxFindReplaceData
//----------------------------------------------------------------------------
Gura_DeclareUserClass(wx_FindReplaceData);

//----------------------------------------------------------------------------
// Object declaration for wxFindReplaceData
//----------------------------------------------------------------------------
class Object_wx_FindReplaceData : public Object_wx_Object {
public:
	Gura_DeclareObjectAccessor(wx_FindReplaceData)
public:
	inline Object_wx_FindReplaceData(wxFindReplaceData *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object_wx_Object(Gura_UserClass(wx_FindReplaceData), pEntity, pObserver, ownerFlag) {}
	inline Object_wx_FindReplaceData(Class *pClass, wxFindReplaceData *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object_wx_Object(pClass, pEntity, pObserver, ownerFlag) {}
	virtual ~Object_wx_FindReplaceData();
	virtual Object *Clone() const;
	virtual String ToString(bool exprFlag);
	inline wxFindReplaceData *GetEntity() {
		return static_cast<wxFindReplaceData *>(_pEntity);
	}
	inline wxFindReplaceData *ReleaseEntity() {
		wxFindReplaceData *pEntity = GetEntity();
		InvalidateEntity();
		return pEntity;
	}
	inline bool IsInvalid(Environment &env) const {
		if (_pEntity != nullptr) return false;
		SetError_InvalidWxObject(env, "wxFindReplaceData");
		return true;
	}
};

Gura_EndModuleScope(wx)

#endif
