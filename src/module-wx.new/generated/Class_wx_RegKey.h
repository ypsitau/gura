//----------------------------------------------------------------------------
// wxRegKey
//----------------------------------------------------------------------------
#ifndef __CLASS_WX_REGKEY_H__
#define __CLASS_WX_REGKEY_H__
#include <wx/msw/registry.h>

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Class declaration for wxRegKey
//----------------------------------------------------------------------------
Gura_DeclareUserClass(wx_RegKey);

//----------------------------------------------------------------------------
// Object declaration for wxRegKey
//----------------------------------------------------------------------------
class Object_wx_RegKey : public Object {
protected:
	wxRegKey *_pEntity;
	GuraObjectObserver *_pObserver;
	bool _ownerFlag;
public:
	Gura_DeclareObjectAccessor(wx_RegKey)
public:
	inline Object_wx_RegKey(wxRegKey *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object(Gura_UserClass(wx_AboutDialogInfo)),
				_pEntity(pEntity), _pObserver(pObserver), _ownerFlag(ownerFlag) {}
	inline Object_wx_RegKey(Class *pClass, wxRegKey *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object(pClass),
				_pEntity(pEntity), _pObserver(pObserver), _ownerFlag(ownerFlag) {}
	virtual ~Object_wx_RegKey();
	virtual Object *Clone() const;
	virtual String ToString(bool exprFlag);
	inline void SetEntity(wxRegKey *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) {
		if (_ownerFlag) delete _pEntity;
		_pEntity = pEntity;
		_pObserver = pObserver;
		_ownerFlag = ownerFlag;
	}
	inline void InvalidateEntity() { _pEntity = nullptr, _pObserver = nullptr, _ownerFlag = false; }
	inline wxRegKey *GetEntity() {
		return static_cast<wxRegKey *>(_pEntity);
	}
	inline wxRegKey *ReleaseEntity() {
		wxRegKey *pEntity = GetEntity();
		InvalidateEntity();
		return pEntity;
	}
	inline void NotifyGuraObjectDeleted() {
		if (_pObserver != nullptr) _pObserver->GuraObjectDeleted();
	}
	inline bool IsInvalid(Environment &env) const {
		if (_pEntity != nullptr) return false;
		SetError_InvalidWxObject(env, "wxRegKey");
		return true;
	}
};

Gura_EndModuleScope(wx)

#endif
