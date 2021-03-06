//----------------------------------------------------------------------------
// wxGridCellCoords
//----------------------------------------------------------------------------
#ifndef __CLASS_WX_GRIDCELLCOORDS_H__
#define __CLASS_WX_GRIDCELLCOORDS_H__
#include <wx/grid.h>

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Class declaration for wxGridCellCoords
//----------------------------------------------------------------------------
Gura_DeclareUserClass(wx_GridCellCoords);

//----------------------------------------------------------------------------
// Object declaration for wxGridCellCoords
//----------------------------------------------------------------------------
class Object_wx_GridCellCoords : public Object {
protected:
	wxGridCellCoords *_pEntity;
	GuraObjectObserver *_pObserver;
	bool _ownerFlag;
public:
	Gura_DeclareObjectAccessor(wx_GridCellCoords)
public:
	inline Object_wx_GridCellCoords(wxGridCellCoords *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object(Gura_UserClass(wx_AboutDialogInfo)),
				_pEntity(pEntity), _pObserver(pObserver), _ownerFlag(ownerFlag) {}
	inline Object_wx_GridCellCoords(Class *pClass, wxGridCellCoords *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object(pClass),
				_pEntity(pEntity), _pObserver(pObserver), _ownerFlag(ownerFlag) {}
	virtual ~Object_wx_GridCellCoords();
	virtual Object *Clone() const;
	virtual String ToString(bool exprFlag);
	inline void SetEntity(wxGridCellCoords *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) {
		if (_ownerFlag) delete _pEntity;
		_pEntity = pEntity;
		_pObserver = pObserver;
		_ownerFlag = ownerFlag;
	}
	inline void InvalidateEntity() { _pEntity = nullptr, _pObserver = nullptr, _ownerFlag = false; }
	inline wxGridCellCoords *GetEntity() {
		return static_cast<wxGridCellCoords *>(_pEntity);
	}
	inline wxGridCellCoords *ReleaseEntity() {
		wxGridCellCoords *pEntity = GetEntity();
		InvalidateEntity();
		return pEntity;
	}
	inline void NotifyGuraObjectDeleted() {
		if (_pObserver != nullptr) _pObserver->GuraObjectDeleted();
	}
	inline bool IsInvalid(Environment &env) const {
		if (_pEntity != nullptr) return false;
		SetError_InvalidWxObject(env, "wxGridCellCoords");
		return true;
	}
};

Gura_EndModuleScope(wx)

#endif
