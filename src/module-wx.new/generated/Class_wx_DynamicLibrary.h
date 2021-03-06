//----------------------------------------------------------------------------
// wxDynamicLibrary
//----------------------------------------------------------------------------
#ifndef __CLASS_WX_DYNAMICLIBRARY_H__
#define __CLASS_WX_DYNAMICLIBRARY_H__
#include <wx/dynlib.h>

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Class declaration for wxDynamicLibrary
//----------------------------------------------------------------------------
Gura_DeclareUserClass(wx_DynamicLibrary);

//----------------------------------------------------------------------------
// Object declaration for wxDynamicLibrary
//----------------------------------------------------------------------------
class Object_wx_DynamicLibrary : public Object {
protected:
	wxDynamicLibrary *_pEntity;
	GuraObjectObserver *_pObserver;
	bool _ownerFlag;
public:
	Gura_DeclareObjectAccessor(wx_DynamicLibrary)
public:
	inline Object_wx_DynamicLibrary(wxDynamicLibrary *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object(Gura_UserClass(wx_AboutDialogInfo)),
				_pEntity(pEntity), _pObserver(pObserver), _ownerFlag(ownerFlag) {}
	inline Object_wx_DynamicLibrary(Class *pClass, wxDynamicLibrary *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object(pClass),
				_pEntity(pEntity), _pObserver(pObserver), _ownerFlag(ownerFlag) {}
	virtual ~Object_wx_DynamicLibrary();
	virtual Object *Clone() const;
	virtual String ToString(bool exprFlag);
	inline void SetEntity(wxDynamicLibrary *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) {
		if (_ownerFlag) delete _pEntity;
		_pEntity = pEntity;
		_pObserver = pObserver;
		_ownerFlag = ownerFlag;
	}
	inline void InvalidateEntity() { _pEntity = nullptr, _pObserver = nullptr, _ownerFlag = false; }
	inline wxDynamicLibrary *GetEntity() {
		return static_cast<wxDynamicLibrary *>(_pEntity);
	}
	inline wxDynamicLibrary *ReleaseEntity() {
		wxDynamicLibrary *pEntity = GetEntity();
		InvalidateEntity();
		return pEntity;
	}
	inline void NotifyGuraObjectDeleted() {
		if (_pObserver != nullptr) _pObserver->GuraObjectDeleted();
	}
	inline bool IsInvalid(Environment &env) const {
		if (_pEntity != nullptr) return false;
		SetError_InvalidWxObject(env, "wxDynamicLibrary");
		return true;
	}
};

Gura_EndModuleScope(wx)

#endif
