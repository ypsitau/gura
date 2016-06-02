//----------------------------------------------------------------------------
// wxWeakRef<T>
//----------------------------------------------------------------------------
#ifndef __CLASS_WX_WEAKREF<T>_H__
#define __CLASS_WX_WEAKREF<T>_H__
#include <wx/weakref.h>

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Class declaration for wxWeakRef<T>
//----------------------------------------------------------------------------
Gura_DeclareUserClass(wx_WeakRef<T>);

//----------------------------------------------------------------------------
// Object declaration for wxWeakRef<T>
//----------------------------------------------------------------------------
class Object_wx_WeakRef<T> : public Object {
protected:
	wxWeakRef<T> *_pEntity;
	GuraObjectObserver *_pObserver;
	bool _ownerFlag;
public:
	Gura_DeclareObjectAccessor(wx_WeakRef<T>)
public:
	inline Object_wx_WeakRef<T>(wxWeakRef<T> *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object(Gura_UserClass(wx_AboutDialogInfo)),
				_pEntity(pEntity), _pObserver(pObserver), _ownerFlag(ownerFlag) {}
	inline Object_wx_WeakRef<T>(Class *pClass, wxWeakRef<T> *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object(pClass),
				_pEntity(pEntity), _pObserver(pObserver), _ownerFlag(ownerFlag) {}
	virtual ~Object_wx_WeakRef<T>();
	virtual Object *Clone() const;
	virtual String ToString(bool exprFlag);
	inline void SetEntity(wxWeakRef<T> *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) {
		if (_ownerFlag) delete _pEntity;
		_pEntity = pEntity;
		_pObserver = pObserver;
		_ownerFlag = ownerFlag;
	}
	inline void InvalidateEntity() { _pEntity = nullptr, _pObserver = nullptr, _ownerFlag = false; }
	inline wxWeakRef<T> *GetEntity() {
		return static_cast<wxWeakRef<T> *>(_pEntity);
	}
	inline wxWeakRef<T> *ReleaseEntity() {
		wxWeakRef<T> *pEntity = GetEntity();
		InvalidateEntity();
		return pEntity;
	}
	inline void NotifyGuraObjectDeleted() {
		if (_pObserver != nullptr) _pObserver->GuraObjectDeleted();
	}
	inline bool IsInvalid(Environment &env) const {
		if (_pEntity != nullptr) return false;
		SetError_InvalidWxObject(env, "wxWeakRef<T>");
		return true;
	}
};

Gura_EndModuleScope(wx)

#endif
