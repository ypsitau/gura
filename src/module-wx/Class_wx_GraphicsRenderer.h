//----------------------------------------------------------------------------
// wxGraphicsRenderer
// extracted from graphicsrenderer.tex
//----------------------------------------------------------------------------
#ifndef __CLASS_WX_GRAPHICSRENDERER_H__
#define __CLASS_WX_GRAPHICSRENDERER_H__

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Class declaration for wxGraphicsRenderer
//----------------------------------------------------------------------------
Gura_DeclareUserClass(wx_GraphicsRenderer);

//----------------------------------------------------------------------------
// Object declaration for wxGraphicsRenderer
//----------------------------------------------------------------------------
class Object_wx_GraphicsRenderer : public Object_wx_Object {
public:
	Gura_DeclareObjectAccessor(wx_GraphicsRenderer)
public:
	inline Object_wx_GraphicsRenderer(wxGraphicsRenderer *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object_wx_Object(Gura_UserClass(wx_GraphicsRenderer), pEntity, pObserver, ownerFlag) {}
	inline Object_wx_GraphicsRenderer(Class *pClass, wxGraphicsRenderer *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object_wx_Object(pClass, pEntity, pObserver, ownerFlag) {}
	virtual ~Object_wx_GraphicsRenderer();
	virtual Object *Clone() const;
	virtual String ToString(bool exprFlag);
	inline wxGraphicsRenderer *GetEntity() {
		return dynamic_cast<wxGraphicsRenderer *>(_pEntity);
	}
	inline wxGraphicsRenderer *ReleaseEntity() {
		wxGraphicsRenderer *pEntity = GetEntity();
		InvalidateEntity();
		return pEntity;
	}
	inline bool IsInvalid(Signal &sig) const {
		if (_pEntity != nullptr) return false;
		SetError_InvalidWxObject(sig, "wxGraphicsRenderer");
		return true;
	}
};

Gura_EndModuleScope(wx)

#endif
