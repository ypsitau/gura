//----------------------------------------------------------------------------
// wxKeyboardState
//----------------------------------------------------------------------------
#ifndef __CLASS_WX_KEYBOARDSTATE_H__
#define __CLASS_WX_KEYBOARDSTATE_H__
#include <wx/kbdstate.h>

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Class declaration for wxKeyboardState
//----------------------------------------------------------------------------
Gura_DeclareUserClass(wx_KeyboardState);

//----------------------------------------------------------------------------
// Object declaration for wxKeyboardState
//----------------------------------------------------------------------------
class Object_wx_KeyboardState : public Object {
protected:
	wxKeyboardState *_pEntity;
	GuraObjectObserver *_pObserver;
	bool _ownerFlag;
public:
	Gura_DeclareObjectAccessor(wx_KeyboardState)
public:
	inline Object_wx_KeyboardState(wxKeyboardState *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object(Gura_UserClass(wx_AboutDialogInfo)),
				_pEntity(pEntity), _pObserver(pObserver), _ownerFlag(ownerFlag) {}
	inline Object_wx_KeyboardState(Class *pClass, wxKeyboardState *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object(pClass),
				_pEntity(pEntity), _pObserver(pObserver), _ownerFlag(ownerFlag) {}
	virtual ~Object_wx_KeyboardState();
	virtual Object *Clone() const;
	virtual String ToString(bool exprFlag);
	inline void SetEntity(wxKeyboardState *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) {
		if (_ownerFlag) delete _pEntity;
		_pEntity = pEntity;
		_pObserver = pObserver;
		_ownerFlag = ownerFlag;
	}
	inline void InvalidateEntity() { _pEntity = nullptr, _pObserver = nullptr, _ownerFlag = false; }
	inline wxKeyboardState *GetEntity() {
		return static_cast<wxKeyboardState *>(_pEntity);
	}
	inline wxKeyboardState *ReleaseEntity() {
		wxKeyboardState *pEntity = GetEntity();
		InvalidateEntity();
		return pEntity;
	}
	inline void NotifyGuraObjectDeleted() {
		if (_pObserver != nullptr) _pObserver->GuraObjectDeleted();
	}
	inline bool IsInvalid(Environment &env) const {
		if (_pEntity != nullptr) return false;
		SetError_InvalidWxObject(env, "wxKeyboardState");
		return true;
	}
};

Gura_EndModuleScope(wx)

#endif
