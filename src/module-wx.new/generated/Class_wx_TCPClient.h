//----------------------------------------------------------------------------
// wxTCPClient
//----------------------------------------------------------------------------
#ifndef __CLASS_WX_TCPCLIENT_H__
#define __CLASS_WX_TCPCLIENT_H__
#include <wx/sckipc.h>

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Class declaration for wxTCPClient
//----------------------------------------------------------------------------
Gura_DeclareUserClass(wx_TCPClient);

//----------------------------------------------------------------------------
// Object declaration for wxTCPClient
//----------------------------------------------------------------------------
class Object_wx_TCPClient : public Object_wx_Object {
public:
	Gura_DeclareObjectAccessor(wx_TCPClient)
public:
	inline Object_wx_TCPClient(wxTCPClient *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object_wx_Object(Gura_UserClass(wx_TCPClient), pEntity, pObserver, ownerFlag) {}
	inline Object_wx_TCPClient(Class *pClass, wxTCPClient *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object_wx_Object(pClass, pEntity, pObserver, ownerFlag) {}
	virtual ~Object_wx_TCPClient();
	virtual Object *Clone() const;
	virtual String ToString(bool exprFlag);
	inline wxTCPClient *GetEntity() {
		return static_cast<wxTCPClient *>(_pEntity);
	}
	inline wxTCPClient *ReleaseEntity() {
		wxTCPClient *pEntity = GetEntity();
		InvalidateEntity();
		return pEntity;
	}
	inline bool IsInvalid(Environment &env) const {
		if (_pEntity != nullptr) return false;
		SetError_InvalidWxObject(env, "wxTCPClient");
		return true;
	}
};

Gura_EndModuleScope(wx)

#endif
