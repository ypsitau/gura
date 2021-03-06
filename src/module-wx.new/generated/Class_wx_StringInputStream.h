//----------------------------------------------------------------------------
// wxStringInputStream
//----------------------------------------------------------------------------
#ifndef __CLASS_WX_STRINGINPUTSTREAM_H__
#define __CLASS_WX_STRINGINPUTSTREAM_H__
#include <wx/sstream.h>

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Class declaration for wxStringInputStream
//----------------------------------------------------------------------------
Gura_DeclareUserClass(wx_StringInputStream);

//----------------------------------------------------------------------------
// Object declaration for wxStringInputStream
//----------------------------------------------------------------------------
class Object_wx_StringInputStream : public Object_wx_InputStream {
public:
	Gura_DeclareObjectAccessor(wx_StringInputStream)
public:
	inline Object_wx_StringInputStream(wxStringInputStream *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object_wx_InputStream(Gura_UserClass(wx_StringInputStream), pEntity, pObserver, ownerFlag) {}
	inline Object_wx_StringInputStream(Class *pClass, wxStringInputStream *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object_wx_InputStream(pClass, pEntity, pObserver, ownerFlag) {}
	virtual ~Object_wx_StringInputStream();
	virtual Object *Clone() const;
	virtual String ToString(bool exprFlag);
	inline wxStringInputStream *GetEntity() {
		return static_cast<wxStringInputStream *>(_pEntity);
	}
	inline wxStringInputStream *ReleaseEntity() {
		wxStringInputStream *pEntity = GetEntity();
		InvalidateEntity();
		return pEntity;
	}
	inline bool IsInvalid(Environment &env) const {
		if (_pEntity != nullptr) return false;
		SetError_InvalidWxObject(env, "wxStringInputStream");
		return true;
	}
};

Gura_EndModuleScope(wx)

#endif
