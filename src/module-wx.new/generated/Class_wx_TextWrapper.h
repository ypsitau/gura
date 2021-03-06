//----------------------------------------------------------------------------
// wxTextWrapper
//----------------------------------------------------------------------------
#ifndef __CLASS_WX_TEXTWRAPPER_H__
#define __CLASS_WX_TEXTWRAPPER_H__
#include <wx/textwrapper.h>

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Class declaration for wxTextWrapper
//----------------------------------------------------------------------------
Gura_DeclareUserClass(wx_TextWrapper);

//----------------------------------------------------------------------------
// Object declaration for wxTextWrapper
//----------------------------------------------------------------------------
class Object_wx_TextWrapper : public Object {
protected:
	wxTextWrapper *_pEntity;
	GuraObjectObserver *_pObserver;
	bool _ownerFlag;
public:
	Gura_DeclareObjectAccessor(wx_TextWrapper)
public:
	inline Object_wx_TextWrapper(wxTextWrapper *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object(Gura_UserClass(wx_AboutDialogInfo)),
				_pEntity(pEntity), _pObserver(pObserver), _ownerFlag(ownerFlag) {}
	inline Object_wx_TextWrapper(Class *pClass, wxTextWrapper *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object(pClass),
				_pEntity(pEntity), _pObserver(pObserver), _ownerFlag(ownerFlag) {}
	virtual ~Object_wx_TextWrapper();
	virtual Object *Clone() const;
	virtual String ToString(bool exprFlag);
	inline void SetEntity(wxTextWrapper *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) {
		if (_ownerFlag) delete _pEntity;
		_pEntity = pEntity;
		_pObserver = pObserver;
		_ownerFlag = ownerFlag;
	}
	inline void InvalidateEntity() { _pEntity = nullptr, _pObserver = nullptr, _ownerFlag = false; }
	inline wxTextWrapper *GetEntity() {
		return static_cast<wxTextWrapper *>(_pEntity);
	}
	inline wxTextWrapper *ReleaseEntity() {
		wxTextWrapper *pEntity = GetEntity();
		InvalidateEntity();
		return pEntity;
	}
	inline void NotifyGuraObjectDeleted() {
		if (_pObserver != nullptr) _pObserver->GuraObjectDeleted();
	}
	inline bool IsInvalid(Environment &env) const {
		if (_pEntity != nullptr) return false;
		SetError_InvalidWxObject(env, "wxTextWrapper");
		return true;
	}
};

Gura_EndModuleScope(wx)

#endif
