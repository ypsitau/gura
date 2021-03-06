//----------------------------------------------------------------------------
// wxTempFileOutputStream
//----------------------------------------------------------------------------
#ifndef __CLASS_WX_TEMPFILEOUTPUTSTREAM_H__
#define __CLASS_WX_TEMPFILEOUTPUTSTREAM_H__
#include <wx/wfstream.h>

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Class declaration for wxTempFileOutputStream
//----------------------------------------------------------------------------
Gura_DeclareUserClass(wx_TempFileOutputStream);

//----------------------------------------------------------------------------
// Object declaration for wxTempFileOutputStream
//----------------------------------------------------------------------------
class Object_wx_TempFileOutputStream : public Object_wx_OutputStream {
public:
	Gura_DeclareObjectAccessor(wx_TempFileOutputStream)
public:
	inline Object_wx_TempFileOutputStream(wxTempFileOutputStream *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object_wx_OutputStream(Gura_UserClass(wx_TempFileOutputStream), pEntity, pObserver, ownerFlag) {}
	inline Object_wx_TempFileOutputStream(Class *pClass, wxTempFileOutputStream *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object_wx_OutputStream(pClass, pEntity, pObserver, ownerFlag) {}
	virtual ~Object_wx_TempFileOutputStream();
	virtual Object *Clone() const;
	virtual String ToString(bool exprFlag);
	inline wxTempFileOutputStream *GetEntity() {
		return static_cast<wxTempFileOutputStream *>(_pEntity);
	}
	inline wxTempFileOutputStream *ReleaseEntity() {
		wxTempFileOutputStream *pEntity = GetEntity();
		InvalidateEntity();
		return pEntity;
	}
	inline bool IsInvalid(Environment &env) const {
		if (_pEntity != nullptr) return false;
		SetError_InvalidWxObject(env, "wxTempFileOutputStream");
		return true;
	}
};

Gura_EndModuleScope(wx)

#endif
