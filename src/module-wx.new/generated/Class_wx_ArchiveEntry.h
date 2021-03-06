//----------------------------------------------------------------------------
// wxArchiveEntry
//----------------------------------------------------------------------------
#ifndef __CLASS_WX_ARCHIVEENTRY_H__
#define __CLASS_WX_ARCHIVEENTRY_H__
#include <wx/archive.h>

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Class declaration for wxArchiveEntry
//----------------------------------------------------------------------------
Gura_DeclareUserClass(wx_ArchiveEntry);

//----------------------------------------------------------------------------
// Object declaration for wxArchiveEntry
//----------------------------------------------------------------------------
class Object_wx_ArchiveEntry : public Object_wx_Object {
public:
	Gura_DeclareObjectAccessor(wx_ArchiveEntry)
public:
	inline Object_wx_ArchiveEntry(wxArchiveEntry *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object_wx_Object(Gura_UserClass(wx_ArchiveEntry), pEntity, pObserver, ownerFlag) {}
	inline Object_wx_ArchiveEntry(Class *pClass, wxArchiveEntry *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object_wx_Object(pClass, pEntity, pObserver, ownerFlag) {}
	virtual ~Object_wx_ArchiveEntry();
	virtual Object *Clone() const;
	virtual String ToString(bool exprFlag);
	inline wxArchiveEntry *GetEntity() {
		return static_cast<wxArchiveEntry *>(_pEntity);
	}
	inline wxArchiveEntry *ReleaseEntity() {
		wxArchiveEntry *pEntity = GetEntity();
		InvalidateEntity();
		return pEntity;
	}
	inline bool IsInvalid(Environment &env) const {
		if (_pEntity != nullptr) return false;
		SetError_InvalidWxObject(env, "wxArchiveEntry");
		return true;
	}
};

Gura_EndModuleScope(wx)

#endif
