//----------------------------------------------------------------------------
// wxFileOutputStream
//----------------------------------------------------------------------------
#ifndef __CLASS_WX_FILEOUTPUTSTREAM_H__
#define __CLASS_WX_FILEOUTPUTSTREAM_H__
#include <wx/wfstream.h>

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Class declaration for wxFileOutputStream
//----------------------------------------------------------------------------
Gura_DeclareUserClass(wx_FileOutputStream);

//----------------------------------------------------------------------------
// Object declaration for wxFileOutputStream
//----------------------------------------------------------------------------
class Object_wx_FileOutputStream : public Object_wx_OutputStream {
public:
	Gura_DeclareObjectAccessor(wx_FileOutputStream)
public:
	inline Object_wx_FileOutputStream(wxFileOutputStream *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object_wx_OutputStream(Gura_UserClass(wx_FileOutputStream), pEntity, pObserver, ownerFlag) {}
	inline Object_wx_FileOutputStream(Class *pClass, wxFileOutputStream *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object_wx_OutputStream(pClass, pEntity, pObserver, ownerFlag) {}
	virtual ~Object_wx_FileOutputStream();
	virtual Object *Clone() const;
	virtual String ToString(bool exprFlag);
	inline wxFileOutputStream *GetEntity() {
		return static_cast<wxFileOutputStream *>(_pEntity);
	}
	inline wxFileOutputStream *ReleaseEntity() {
		wxFileOutputStream *pEntity = GetEntity();
		InvalidateEntity();
		return pEntity;
	}
	inline bool IsInvalid(Environment &env) const {
		if (_pEntity != nullptr) return false;
		SetError_InvalidWxObject(env, "wxFileOutputStream");
		return true;
	}
};

Gura_EndModuleScope(wx)

#endif
