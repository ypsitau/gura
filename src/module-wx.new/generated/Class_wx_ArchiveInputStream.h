//----------------------------------------------------------------------------
// wxArchiveInputStream
//----------------------------------------------------------------------------
#ifndef __CLASS_WX_ARCHIVEINPUTSTREAM_H__
#define __CLASS_WX_ARCHIVEINPUTSTREAM_H__
#include <wx/archive.h>

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Class declaration for wxArchiveInputStream
//----------------------------------------------------------------------------
Gura_DeclareUserClass(wx_ArchiveInputStream);

//----------------------------------------------------------------------------
// Object declaration for wxArchiveInputStream
//----------------------------------------------------------------------------
class Object_wx_ArchiveInputStream : public Object_wx_FilterInputStream {
public:
	Gura_DeclareObjectAccessor(wx_ArchiveInputStream)
public:
	inline Object_wx_ArchiveInputStream(wxArchiveInputStream *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object_wx_FilterInputStream(Gura_UserClass(wx_ArchiveInputStream), pEntity, pObserver, ownerFlag) {}
	inline Object_wx_ArchiveInputStream(Class *pClass, wxArchiveInputStream *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object_wx_FilterInputStream(pClass, pEntity, pObserver, ownerFlag) {}
	virtual ~Object_wx_ArchiveInputStream();
	virtual Object *Clone() const;
	virtual String ToString(bool exprFlag);
	inline wxArchiveInputStream *GetEntity() {
		return static_cast<wxArchiveInputStream *>(_pEntity);
	}
	inline wxArchiveInputStream *ReleaseEntity() {
		wxArchiveInputStream *pEntity = GetEntity();
		InvalidateEntity();
		return pEntity;
	}
	inline bool IsInvalid(Environment &env) const {
		if (_pEntity != nullptr) return false;
		SetError_InvalidWxObject(env, "wxArchiveInputStream");
		return true;
	}
};

Gura_EndModuleScope(wx)

#endif
