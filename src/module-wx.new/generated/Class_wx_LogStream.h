//----------------------------------------------------------------------------
// wxLogStream
//----------------------------------------------------------------------------
#ifndef __CLASS_WX_LOGSTREAM_H__
#define __CLASS_WX_LOGSTREAM_H__
#include <wx/log.h>

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Class declaration for wxLogStream
//----------------------------------------------------------------------------
Gura_DeclareUserClass(wx_LogStream);

//----------------------------------------------------------------------------
// Object declaration for wxLogStream
//----------------------------------------------------------------------------
class Object_wx_LogStream : public Object_wx_Log {
public:
	Gura_DeclareObjectAccessor(wx_LogStream)
public:
	inline Object_wx_LogStream(wxLogStream *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object_wx_Log(Gura_UserClass(wx_LogStream), pEntity, pObserver, ownerFlag) {}
	inline Object_wx_LogStream(Class *pClass, wxLogStream *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object_wx_Log(pClass, pEntity, pObserver, ownerFlag) {}
	virtual ~Object_wx_LogStream();
	virtual Object *Clone() const;
	virtual String ToString(bool exprFlag);
	inline wxLogStream *GetEntity() {
		return static_cast<wxLogStream *>(_pEntity);
	}
	inline wxLogStream *ReleaseEntity() {
		wxLogStream *pEntity = GetEntity();
		InvalidateEntity();
		return pEntity;
	}
	inline bool IsInvalid(Environment &env) const {
		if (_pEntity != nullptr) return false;
		SetError_InvalidWxObject(env, "wxLogStream");
		return true;
	}
};

Gura_EndModuleScope(wx)

#endif
