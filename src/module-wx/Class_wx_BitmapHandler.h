//----------------------------------------------------------------------------
// wxBitmapHandler
// extracted from bmphand.tex
//----------------------------------------------------------------------------
#ifndef __CLASS_WX_BITMAPHANDLER_H__
#define __CLASS_WX_BITMAPHANDLER_H__

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Class declaration for wxBitmapHandler
//----------------------------------------------------------------------------
Gura_DeclareUserClass(wx_BitmapHandler);

//----------------------------------------------------------------------------
// Object declaration for wxBitmapHandler
//----------------------------------------------------------------------------
class Object_wx_BitmapHandler : public Object_wx_Object {
public:
	Gura_DeclareObjectAccessor(wx_BitmapHandler)
public:
	inline Object_wx_BitmapHandler(wxBitmapHandler *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object_wx_Object(Gura_UserClass(wx_BitmapHandler), pEntity, pObserver, ownerFlag) {}
	inline Object_wx_BitmapHandler(Class *pClass, wxBitmapHandler *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object_wx_Object(pClass, pEntity, pObserver, ownerFlag) {}
	virtual ~Object_wx_BitmapHandler();
	virtual Object *Clone() const;
	virtual String ToString(bool exprFlag);
	inline wxBitmapHandler *GetEntity() {
		return dynamic_cast<wxBitmapHandler *>(_pEntity);
	}
	inline wxBitmapHandler *ReleaseEntity() {
		wxBitmapHandler *pEntity = GetEntity();
		InvalidateEntity();
		return pEntity;
	}
	inline bool IsInvalid(Signal &sig) const {
		if (_pEntity != nullptr) return false;
		SetError_InvalidWxObject(sig, "wxBitmapHandler");
		return true;
	}
};

Gura_EndModuleScope(wx)

#endif
