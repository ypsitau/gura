//----------------------------------------------------------------------------
// wxGridCellAttrProvider
// (automatically generated)
//----------------------------------------------------------------------------
#ifndef __CLASS_WX_GRIDCELLATTRPROVIDER_H__
#define __CLASS_WX_GRIDCELLATTRPROVIDER_H__

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Class declaration for wxGridCellAttrProvider
//----------------------------------------------------------------------------
Gura_DeclareUserClass(wx_GridCellAttrProvider);

//----------------------------------------------------------------------------
// Object declaration for wxGridCellAttrProvider
//----------------------------------------------------------------------------
class Object_wx_GridCellAttrProvider : public Object {
protected:
	wxGridCellAttrProvider *_pEntity;
	GuraObjectObserver *_pObserver;
	bool _ownerFlag;
public:
	Gura_DeclareObjectAccessor(wx_GridCellAttrProvider)
public:
	inline Object_wx_GridCellAttrProvider(wxGridCellAttrProvider *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object(Gura_UserClass(wx_GridCellAttrProvider)),
				_pEntity(pEntity), _pObserver(pObserver), _ownerFlag(ownerFlag) {}
	inline Object_wx_GridCellAttrProvider(Class *pClass, wxGridCellAttrProvider *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object(pClass), _pEntity(pEntity), _pObserver(pObserver), _ownerFlag(ownerFlag) {}
	virtual ~Object_wx_GridCellAttrProvider();
	virtual Object *Clone() const;
	virtual String ToString(bool exprFlag);
	inline void SetEntity(wxGridCellAttrProvider *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) {
		if (_ownerFlag) delete _pEntity;
		_pEntity = pEntity;
		_pObserver = pObserver;
		_ownerFlag = ownerFlag;
	}
	inline void InvalidateEntity() { _pEntity = nullptr, _pObserver = nullptr, _ownerFlag = false; }
	inline wxGridCellAttrProvider *GetEntity() { return _pEntity; }
	inline wxGridCellAttrProvider *ReleaseEntity() {
		wxGridCellAttrProvider *pEntity = GetEntity();
		InvalidateEntity();
		return pEntity;
	}
	inline void NotifyGuraObjectDeleted() {
		if (_pObserver != nullptr) _pObserver->GuraObjectDeleted();
	}
	inline bool IsInvalid(Signal &sig) const {
		if (_pEntity != nullptr) return false;
		SetError_InvalidWxObject(sig, "wxGridCellAttrProvider");
		return true;
	}
};

Gura_EndModuleScope(wx)

#endif
