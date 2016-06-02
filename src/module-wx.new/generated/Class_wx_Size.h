//----------------------------------------------------------------------------
// wxSize
//----------------------------------------------------------------------------
#ifndef __CLASS_WX_SIZE_H__
#define __CLASS_WX_SIZE_H__
#include <wx/gdicmn.h>

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Class declaration for wxSize
//----------------------------------------------------------------------------
Gura_DeclareUserClass(wx_Size);

//----------------------------------------------------------------------------
// Object declaration for wxSize
//----------------------------------------------------------------------------
class Object_wx_Size : public Object {
protected:
	wxSize *_pEntity;
	GuraObjectObserver *_pObserver;
	bool _ownerFlag;
public:
	Gura_DeclareObjectAccessor(wx_Size)
public:
	inline Object_wx_Size(wxSize *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object(Gura_UserClass(wx_AboutDialogInfo)),
				_pEntity(pEntity), _pObserver(pObserver), _ownerFlag(ownerFlag) {}
	inline Object_wx_Size(Class *pClass, wxSize *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object(pClass),
				_pEntity(pEntity), _pObserver(pObserver), _ownerFlag(ownerFlag) {}
	virtual ~Object_wx_Size();
	virtual Object *Clone() const;
	virtual String ToString(bool exprFlag);
	inline void SetEntity(wxSize *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) {
		if (_ownerFlag) delete _pEntity;
		_pEntity = pEntity;
		_pObserver = pObserver;
		_ownerFlag = ownerFlag;
	}
	inline void InvalidateEntity() { _pEntity = nullptr, _pObserver = nullptr, _ownerFlag = false; }
	inline wxSize *GetEntity() {
		return static_cast<wxSize *>(_pEntity);
	}
	inline wxSize *ReleaseEntity() {
		wxSize *pEntity = GetEntity();
		InvalidateEntity();
		return pEntity;
	}
	inline void NotifyGuraObjectDeleted() {
		if (_pObserver != nullptr) _pObserver->GuraObjectDeleted();
	}
	inline bool IsInvalid(Environment &env) const {
		if (_pEntity != nullptr) return false;
		SetError_InvalidWxObject(env, "wxSize");
		return true;
	}
};

Gura_EndModuleScope(wx)

#endif
