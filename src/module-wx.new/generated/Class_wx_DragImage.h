//----------------------------------------------------------------------------
// wxDragImage
//----------------------------------------------------------------------------
#ifndef __CLASS_WX_DRAGIMAGE_H__
#define __CLASS_WX_DRAGIMAGE_H__
#include <wx/dragimag.h>

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Class declaration for wxDragImage
//----------------------------------------------------------------------------
Gura_DeclareUserClass(wx_DragImage);

//----------------------------------------------------------------------------
// Object declaration for wxDragImage
//----------------------------------------------------------------------------
class Object_wx_DragImage : public Object_wx_Object {
public:
	Gura_DeclareObjectAccessor(wx_DragImage)
public:
	inline Object_wx_DragImage(wxDragImage *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object_wx_Object(Gura_UserClass(wx_DragImage), pEntity, pObserver, ownerFlag) {}
	inline Object_wx_DragImage(Class *pClass, wxDragImage *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object_wx_Object(pClass, pEntity, pObserver, ownerFlag) {}
	virtual ~Object_wx_DragImage();
	virtual Object *Clone() const;
	virtual String ToString(bool exprFlag);
	inline wxDragImage *GetEntity() {
		return static_cast<wxDragImage *>(_pEntity);
	}
	inline wxDragImage *ReleaseEntity() {
		wxDragImage *pEntity = GetEntity();
		InvalidateEntity();
		return pEntity;
	}
	inline bool IsInvalid(Environment &env) const {
		if (_pEntity != nullptr) return false;
		SetError_InvalidWxObject(env, "wxDragImage");
		return true;
	}
};

Gura_EndModuleScope(wx)

#endif
