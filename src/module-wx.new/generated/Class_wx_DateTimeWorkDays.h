//----------------------------------------------------------------------------
// wxDateTimeWorkDays
//----------------------------------------------------------------------------
#ifndef __CLASS_WX_DATETIMEWORKDAYS_H__
#define __CLASS_WX_DATETIMEWORKDAYS_H__
#include <wx/datetime.h>

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Class declaration for wxDateTimeWorkDays
//----------------------------------------------------------------------------
Gura_DeclareUserClass(wx_DateTimeWorkDays);

//----------------------------------------------------------------------------
// Object declaration for wxDateTimeWorkDays
//----------------------------------------------------------------------------
class Object_wx_DateTimeWorkDays : public Object {
protected:
	wxDateTimeWorkDays *_pEntity;
	GuraObjectObserver *_pObserver;
	bool _ownerFlag;
public:
	Gura_DeclareObjectAccessor(wx_DateTimeWorkDays)
public:
	inline Object_wx_DateTimeWorkDays(wxDateTimeWorkDays *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object(Gura_UserClass(wx_AboutDialogInfo)),
				_pEntity(pEntity), _pObserver(pObserver), _ownerFlag(ownerFlag) {}
	inline Object_wx_DateTimeWorkDays(Class *pClass, wxDateTimeWorkDays *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object(pClass),
				_pEntity(pEntity), _pObserver(pObserver), _ownerFlag(ownerFlag) {}
	virtual ~Object_wx_DateTimeWorkDays();
	virtual Object *Clone() const;
	virtual String ToString(bool exprFlag);
	inline void SetEntity(wxDateTimeWorkDays *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) {
		if (_ownerFlag) delete _pEntity;
		_pEntity = pEntity;
		_pObserver = pObserver;
		_ownerFlag = ownerFlag;
	}
	inline void InvalidateEntity() { _pEntity = nullptr, _pObserver = nullptr, _ownerFlag = false; }
	inline wxDateTimeWorkDays *GetEntity() {
		return static_cast<wxDateTimeWorkDays *>(_pEntity);
	}
	inline wxDateTimeWorkDays *ReleaseEntity() {
		wxDateTimeWorkDays *pEntity = GetEntity();
		InvalidateEntity();
		return pEntity;
	}
	inline void NotifyGuraObjectDeleted() {
		if (_pObserver != nullptr) _pObserver->GuraObjectDeleted();
	}
	inline bool IsInvalid(Environment &env) const {
		if (_pEntity != nullptr) return false;
		SetError_InvalidWxObject(env, "wxDateTimeWorkDays");
		return true;
	}
};

Gura_EndModuleScope(wx)

#endif
