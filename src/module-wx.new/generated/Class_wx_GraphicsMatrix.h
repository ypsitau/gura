//----------------------------------------------------------------------------
// wxGraphicsMatrix
//----------------------------------------------------------------------------
#ifndef __CLASS_WX_GRAPHICSMATRIX_H__
#define __CLASS_WX_GRAPHICSMATRIX_H__
#include <wx/graphics.h>

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Class declaration for wxGraphicsMatrix
//----------------------------------------------------------------------------
Gura_DeclareUserClass(wx_GraphicsMatrix);

//----------------------------------------------------------------------------
// Object declaration for wxGraphicsMatrix
//----------------------------------------------------------------------------
class Object_wx_GraphicsMatrix : public Object_wx_GraphicsObject {
public:
	Gura_DeclareObjectAccessor(wx_GraphicsMatrix)
public:
	inline Object_wx_GraphicsMatrix(wxGraphicsMatrix *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object_wx_GraphicsObject(Gura_UserClass(wx_GraphicsMatrix), pEntity, pObserver, ownerFlag) {}
	inline Object_wx_GraphicsMatrix(Class *pClass, wxGraphicsMatrix *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object_wx_GraphicsObject(pClass, pEntity, pObserver, ownerFlag) {}
	virtual ~Object_wx_GraphicsMatrix();
	virtual Object *Clone() const;
	virtual String ToString(bool exprFlag);
	inline wxGraphicsMatrix *GetEntity() {
		return static_cast<wxGraphicsMatrix *>(_pEntity);
	}
	inline wxGraphicsMatrix *ReleaseEntity() {
		wxGraphicsMatrix *pEntity = GetEntity();
		InvalidateEntity();
		return pEntity;
	}
	inline bool IsInvalid(Environment &env) const {
		if (_pEntity != nullptr) return false;
		SetError_InvalidWxObject(env, "wxGraphicsMatrix");
		return true;
	}
};

Gura_EndModuleScope(wx)

#endif
