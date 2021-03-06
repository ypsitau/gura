//----------------------------------------------------------------------------
// wxMemoryBuffer
//----------------------------------------------------------------------------
#ifndef __CLASS_WX_MEMORYBUFFER_H__
#define __CLASS_WX_MEMORYBUFFER_H__
#include <wx/buffer.h>

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Class declaration for wxMemoryBuffer
//----------------------------------------------------------------------------
Gura_DeclareUserClass(wx_MemoryBuffer);

//----------------------------------------------------------------------------
// Object declaration for wxMemoryBuffer
//----------------------------------------------------------------------------
class Object_wx_MemoryBuffer : public Object {
protected:
	wxMemoryBuffer *_pEntity;
	GuraObjectObserver *_pObserver;
	bool _ownerFlag;
public:
	Gura_DeclareObjectAccessor(wx_MemoryBuffer)
public:
	inline Object_wx_MemoryBuffer(wxMemoryBuffer *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object(Gura_UserClass(wx_AboutDialogInfo)),
				_pEntity(pEntity), _pObserver(pObserver), _ownerFlag(ownerFlag) {}
	inline Object_wx_MemoryBuffer(Class *pClass, wxMemoryBuffer *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object(pClass),
				_pEntity(pEntity), _pObserver(pObserver), _ownerFlag(ownerFlag) {}
	virtual ~Object_wx_MemoryBuffer();
	virtual Object *Clone() const;
	virtual String ToString(bool exprFlag);
	inline void SetEntity(wxMemoryBuffer *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) {
		if (_ownerFlag) delete _pEntity;
		_pEntity = pEntity;
		_pObserver = pObserver;
		_ownerFlag = ownerFlag;
	}
	inline void InvalidateEntity() { _pEntity = nullptr, _pObserver = nullptr, _ownerFlag = false; }
	inline wxMemoryBuffer *GetEntity() {
		return static_cast<wxMemoryBuffer *>(_pEntity);
	}
	inline wxMemoryBuffer *ReleaseEntity() {
		wxMemoryBuffer *pEntity = GetEntity();
		InvalidateEntity();
		return pEntity;
	}
	inline void NotifyGuraObjectDeleted() {
		if (_pObserver != nullptr) _pObserver->GuraObjectDeleted();
	}
	inline bool IsInvalid(Environment &env) const {
		if (_pEntity != nullptr) return false;
		SetError_InvalidWxObject(env, "wxMemoryBuffer");
		return true;
	}
};

Gura_EndModuleScope(wx)

#endif
