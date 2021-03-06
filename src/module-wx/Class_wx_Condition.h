//----------------------------------------------------------------------------
// wxCondition
// extracted from conditn.tex
//----------------------------------------------------------------------------
#ifndef __CLASS_WX_CONDITION_H__
#define __CLASS_WX_CONDITION_H__

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Class declaration for wxCondition
//----------------------------------------------------------------------------
Gura_DeclareUserClass(wx_Condition);

//----------------------------------------------------------------------------
// Object declaration for wxCondition
//----------------------------------------------------------------------------
class Object_wx_Condition : public Object {
protected:
	wxCondition *_pEntity;
	GuraObjectObserver *_pObserver;
	bool _ownerFlag;
public:
	Gura_DeclareObjectAccessor(wx_Condition)
public:
	inline Object_wx_Condition(wxCondition *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object(Gura_UserClass(wx_Condition)),
				_pEntity(pEntity), _pObserver(pObserver), _ownerFlag(ownerFlag) {}
	inline Object_wx_Condition(Class *pClass, wxCondition *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object(pClass), _pEntity(pEntity), _pObserver(pObserver), _ownerFlag(ownerFlag) {}
	virtual ~Object_wx_Condition();
	virtual Object *Clone() const;
	virtual String ToString(bool exprFlag);
	inline void SetEntity(wxCondition *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) {
		if (_ownerFlag) delete _pEntity;
		_pEntity = pEntity;
		_pObserver = pObserver;
		_ownerFlag = ownerFlag;
	}
	inline void InvalidateEntity() { _pEntity = nullptr, _pObserver = nullptr, _ownerFlag = false; }
	inline wxCondition *GetEntity() { return _pEntity; }
	inline wxCondition *ReleaseEntity() {
		wxCondition *pEntity = GetEntity();
		InvalidateEntity();
		return pEntity;
	}
	inline void NotifyGuraObjectDeleted() {
		if (_pObserver != nullptr) _pObserver->GuraObjectDeleted();
	}
	inline bool IsInvalid(Signal &sig) const {
		if (_pEntity != nullptr) return false;
		SetError_InvalidWxObject(sig, "wxCondition");
		return true;
	}
};

Gura_EndModuleScope(wx)

#endif
