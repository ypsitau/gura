//----------------------------------------------------------------------------
// wxFileName
//----------------------------------------------------------------------------
#ifndef __CLASS_WX_FILENAME_H__
#define __CLASS_WX_FILENAME_H__
#include <wx/filename.h>

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Class declaration for wxFileName
//----------------------------------------------------------------------------
Gura_DeclareUserClass(wx_FileName);

//----------------------------------------------------------------------------
// Object declaration for wxFileName
//----------------------------------------------------------------------------
class Object_wx_FileName : public Object {
protected:
	wxFileName *_pEntity;
	GuraObjectObserver *_pObserver;
	bool _ownerFlag;
public:
	Gura_DeclareObjectAccessor(wx_FileName)
public:
	inline Object_wx_FileName(wxFileName *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object(Gura_UserClass(wx_AboutDialogInfo)),
				_pEntity(pEntity), _pObserver(pObserver), _ownerFlag(ownerFlag) {}
	inline Object_wx_FileName(Class *pClass, wxFileName *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object(pClass),
				_pEntity(pEntity), _pObserver(pObserver), _ownerFlag(ownerFlag) {}
	virtual ~Object_wx_FileName();
	virtual Object *Clone() const;
	virtual String ToString(bool exprFlag);
	inline void SetEntity(wxFileName *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) {
		if (_ownerFlag) delete _pEntity;
		_pEntity = pEntity;
		_pObserver = pObserver;
		_ownerFlag = ownerFlag;
	}
	inline void InvalidateEntity() { _pEntity = nullptr, _pObserver = nullptr, _ownerFlag = false; }
	inline wxFileName *GetEntity() {
		return static_cast<wxFileName *>(_pEntity);
	}
	inline wxFileName *ReleaseEntity() {
		wxFileName *pEntity = GetEntity();
		InvalidateEntity();
		return pEntity;
	}
	inline void NotifyGuraObjectDeleted() {
		if (_pObserver != nullptr) _pObserver->GuraObjectDeleted();
	}
	inline bool IsInvalid(Environment &env) const {
		if (_pEntity != nullptr) return false;
		SetError_InvalidWxObject(env, "wxFileName");
		return true;
	}
};

Gura_EndModuleScope(wx)

#endif
