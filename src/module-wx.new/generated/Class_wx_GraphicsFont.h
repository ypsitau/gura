//----------------------------------------------------------------------------
// wxGraphicsFont
//----------------------------------------------------------------------------
#ifndef __CLASS_WX_GRAPHICSFONT_H__
#define __CLASS_WX_GRAPHICSFONT_H__
#include <wx/graphics.h>

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Class declaration for wxGraphicsFont
//----------------------------------------------------------------------------
Gura_DeclareUserClass(wx_GraphicsFont);

//----------------------------------------------------------------------------
// Object declaration for wxGraphicsFont
//----------------------------------------------------------------------------
class Object_wx_GraphicsFont : public Object_wx_GraphicsObject {
public:
	Gura_DeclareObjectAccessor(wx_GraphicsFont)
public:
	inline Object_wx_GraphicsFont(wxGraphicsFont *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object_wx_GraphicsObject(Gura_UserClass(wx_GraphicsFont), pEntity, pObserver, ownerFlag) {}
	inline Object_wx_GraphicsFont(Class *pClass, wxGraphicsFont *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object_wx_GraphicsObject(pClass, pEntity, pObserver, ownerFlag) {}
	virtual ~Object_wx_GraphicsFont();
	virtual Object *Clone() const;
	virtual String ToString(bool exprFlag);
	inline wxGraphicsFont *GetEntity() {
		return static_cast<wxGraphicsFont *>(_pEntity);
	}
	inline wxGraphicsFont *ReleaseEntity() {
		wxGraphicsFont *pEntity = GetEntity();
		InvalidateEntity();
		return pEntity;
	}
	inline bool IsInvalid(Environment &env) const {
		if (_pEntity != nullptr) return false;
		SetError_InvalidWxObject(env, "wxGraphicsFont");
		return true;
	}
};

Gura_EndModuleScope(wx)

#endif
