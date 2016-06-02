//----------------------------------------------------------------------------
// wxAutoBufferedPaintDC
//----------------------------------------------------------------------------
#ifndef __CLASS_WX_AUTOBUFFEREDPAINTDC_H__
#define __CLASS_WX_AUTOBUFFEREDPAINTDC_H__
#include <wx/dcbuffer.h>

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Class declaration for wxAutoBufferedPaintDC
//----------------------------------------------------------------------------
Gura_DeclareUserClass(wx_AutoBufferedPaintDC);

//----------------------------------------------------------------------------
// Object declaration for wxAutoBufferedPaintDC
//----------------------------------------------------------------------------
class Object_wx_AutoBufferedPaintDC : public Object_wx_BufferedPaintDC {
public:
	Gura_DeclareObjectAccessor(wx_AutoBufferedPaintDC)
public:
	inline Object_wx_AutoBufferedPaintDC(wxAutoBufferedPaintDC *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object_wx_BufferedPaintDC(Gura_UserClass(wx_AutoBufferedPaintDC), pEntity, pObserver, ownerFlag) {}
	inline Object_wx_AutoBufferedPaintDC(Class *pClass, wxAutoBufferedPaintDC *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object_wx_BufferedPaintDC(pClass, pEntity, pObserver, ownerFlag) {}
	virtual ~Object_wx_AutoBufferedPaintDC();
	virtual Object *Clone() const;
	virtual String ToString(bool exprFlag);
	inline wxAutoBufferedPaintDC *GetEntity() {
		return static_cast<wxAutoBufferedPaintDC *>(_pEntity);
	}
	inline wxAutoBufferedPaintDC *ReleaseEntity() {
		wxAutoBufferedPaintDC *pEntity = GetEntity();
		InvalidateEntity();
		return pEntity;
	}
	inline bool IsInvalid(Environment &env) const {
		if (_pEntity != nullptr) return false;
		SetError_InvalidWxObject(env, "wxAutoBufferedPaintDC");
		return true;
	}
};

Gura_EndModuleScope(wx)

#endif
