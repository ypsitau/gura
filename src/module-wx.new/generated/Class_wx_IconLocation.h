//----------------------------------------------------------------------------
// wxIconLocation
//----------------------------------------------------------------------------
#ifndef __CLASS_WX_ICONLOCATION_H__
#define __CLASS_WX_ICONLOCATION_H__
#include <wx/iconloc.h>

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Class declaration for wxIconLocation
//----------------------------------------------------------------------------
Gura_DeclareUserClass(wx_IconLocation);

//----------------------------------------------------------------------------
// Object declaration for wxIconLocation
//----------------------------------------------------------------------------
class Object_wx_IconLocation : public Object {
protected:
	wxIconLocation *_pEntity;
	GuraObjectObserver *_pObserver;
	bool _ownerFlag;
public:
	Gura_DeclareObjectAccessor(wx_IconLocation)
public:
	inline Object_wx_IconLocation(wxIconLocation *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object(Gura_UserClass(wx_AboutDialogInfo)),
				_pEntity(pEntity), _pObserver(pObserver), _ownerFlag(ownerFlag) {}
	inline Object_wx_IconLocation(Class *pClass, wxIconLocation *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object(pClass),
				_pEntity(pEntity), _pObserver(pObserver), _ownerFlag(ownerFlag) {}
	virtual ~Object_wx_IconLocation();
	virtual Object *Clone() const;
	virtual String ToString(bool exprFlag);
	inline void SetEntity(wxIconLocation *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) {
		if (_ownerFlag) delete _pEntity;
		_pEntity = pEntity;
		_pObserver = pObserver;
		_ownerFlag = ownerFlag;
	}
	inline void InvalidateEntity() { _pEntity = nullptr, _pObserver = nullptr, _ownerFlag = false; }
	inline wxIconLocation *GetEntity() {
		return static_cast<wxIconLocation *>(_pEntity);
	}
	inline wxIconLocation *ReleaseEntity() {
		wxIconLocation *pEntity = GetEntity();
		InvalidateEntity();
		return pEntity;
	}
	inline void NotifyGuraObjectDeleted() {
		if (_pObserver != nullptr) _pObserver->GuraObjectDeleted();
	}
	inline bool IsInvalid(Environment &env) const {
		if (_pEntity != nullptr) return false;
		SetError_InvalidWxObject(env, "wxIconLocation");
		return true;
	}
};

Gura_EndModuleScope(wx)

#endif
