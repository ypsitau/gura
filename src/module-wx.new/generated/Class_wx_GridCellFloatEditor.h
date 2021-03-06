//----------------------------------------------------------------------------
// wxGridCellFloatEditor
//----------------------------------------------------------------------------
#ifndef __CLASS_WX_GRIDCELLFLOATEDITOR_H__
#define __CLASS_WX_GRIDCELLFLOATEDITOR_H__
#include <wx/grid.h>

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Class declaration for wxGridCellFloatEditor
//----------------------------------------------------------------------------
Gura_DeclareUserClass(wx_GridCellFloatEditor);

//----------------------------------------------------------------------------
// Object declaration for wxGridCellFloatEditor
//----------------------------------------------------------------------------
class Object_wx_GridCellFloatEditor : public Object_wx_GridCellTextEditor {
public:
	Gura_DeclareObjectAccessor(wx_GridCellFloatEditor)
public:
	inline Object_wx_GridCellFloatEditor(wxGridCellFloatEditor *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object_wx_GridCellTextEditor(Gura_UserClass(wx_GridCellFloatEditor), pEntity, pObserver, ownerFlag) {}
	inline Object_wx_GridCellFloatEditor(Class *pClass, wxGridCellFloatEditor *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object_wx_GridCellTextEditor(pClass, pEntity, pObserver, ownerFlag) {}
	virtual ~Object_wx_GridCellFloatEditor();
	virtual Object *Clone() const;
	virtual String ToString(bool exprFlag);
	inline wxGridCellFloatEditor *GetEntity() {
		return static_cast<wxGridCellFloatEditor *>(_pEntity);
	}
	inline wxGridCellFloatEditor *ReleaseEntity() {
		wxGridCellFloatEditor *pEntity = GetEntity();
		InvalidateEntity();
		return pEntity;
	}
	inline bool IsInvalid(Environment &env) const {
		if (_pEntity != nullptr) return false;
		SetError_InvalidWxObject(env, "wxGridCellFloatEditor");
		return true;
	}
};

Gura_EndModuleScope(wx)

#endif
