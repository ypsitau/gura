//----------------------------------------------------------------------------
// wxAcceleratorEntry
//----------------------------------------------------------------------------
#ifndef __CLASS_WX_ACCELERATORENTRY_H__
#define __CLASS_WX_ACCELERATORENTRY_H__
#include <wx/accel.h>

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Class declaration for wxAcceleratorEntry
//----------------------------------------------------------------------------
Gura_DeclareUserClass(wx_AcceleratorEntry);

//----------------------------------------------------------------------------
// Object declaration for wxAcceleratorEntry
//----------------------------------------------------------------------------
class Object_wx_AcceleratorEntry : public Object {
protected:
	wxAcceleratorEntry *_pEntity;
	GuraObjectObserver *_pObserver;
	bool _ownerFlag;
public:
	Gura_DeclareObjectAccessor(wx_AcceleratorEntry)
public:
	inline Object_wx_AcceleratorEntry(wxAcceleratorEntry *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object(Gura_UserClass(wx_AboutDialogInfo)),
				_pEntity(pEntity), _pObserver(pObserver), _ownerFlag(ownerFlag) {}
	inline Object_wx_AcceleratorEntry(Class *pClass, wxAcceleratorEntry *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object(pClass),
				_pEntity(pEntity), _pObserver(pObserver), _ownerFlag(ownerFlag) {}
	virtual ~Object_wx_AcceleratorEntry();
	virtual Object *Clone() const;
	virtual String ToString(bool exprFlag);
	inline void SetEntity(wxAcceleratorEntry *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) {
		if (_ownerFlag) delete _pEntity;
		_pEntity = pEntity;
		_pObserver = pObserver;
		_ownerFlag = ownerFlag;
	}
	inline void InvalidateEntity() { _pEntity = nullptr, _pObserver = nullptr, _ownerFlag = false; }
	inline wxAcceleratorEntry *GetEntity() {
		return static_cast<wxAcceleratorEntry *>(_pEntity);
	}
	inline wxAcceleratorEntry *ReleaseEntity() {
		wxAcceleratorEntry *pEntity = GetEntity();
		InvalidateEntity();
		return pEntity;
	}
	inline void NotifyGuraObjectDeleted() {
		if (_pObserver != nullptr) _pObserver->GuraObjectDeleted();
	}
	inline bool IsInvalid(Environment &env) const {
		if (_pEntity != nullptr) return false;
		SetError_InvalidWxObject(env, "wxAcceleratorEntry");
		return true;
	}
};

Gura_EndModuleScope(wx)

#endif
