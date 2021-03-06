//----------------------------------------------------------------------------
// wxGridCellTextEditor
//----------------------------------------------------------------------------
#ifndef __CLASS_WX_GRIDCELLTEXTEDITOR_H__
#define __CLASS_WX_GRIDCELLTEXTEDITOR_H__
#include <wx/grid.h>

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Class declaration for wxGridCellTextEditor
//----------------------------------------------------------------------------
Gura_DeclareUserClass(wx_GridCellTextEditor);

//----------------------------------------------------------------------------
// Object declaration for wxGridCellTextEditor
//----------------------------------------------------------------------------
class Object_wx_GridCellTextEditor : public Object_wx_GridCellEditor {
public:
	Gura_DeclareObjectAccessor(wx_GridCellTextEditor)
public:
	inline Object_wx_GridCellTextEditor(wxGridCellTextEditor *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object_wx_GridCellEditor(Gura_UserClass(wx_GridCellTextEditor), pEntity, pObserver, ownerFlag) {}
	inline Object_wx_GridCellTextEditor(Class *pClass, wxGridCellTextEditor *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object_wx_GridCellEditor(pClass, pEntity, pObserver, ownerFlag) {}
	virtual ~Object_wx_GridCellTextEditor();
	virtual Object *Clone() const;
	virtual String ToString(bool exprFlag);
	inline wxGridCellTextEditor *GetEntity() {
		return static_cast<wxGridCellTextEditor *>(_pEntity);
	}
	inline wxGridCellTextEditor *ReleaseEntity() {
		wxGridCellTextEditor *pEntity = GetEntity();
		InvalidateEntity();
		return pEntity;
	}
	inline bool IsInvalid(Environment &env) const {
		if (_pEntity != nullptr) return false;
		SetError_InvalidWxObject(env, "wxGridCellTextEditor");
		return true;
	}
};

Gura_EndModuleScope(wx)

#endif
