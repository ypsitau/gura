//----------------------------------------------------------------------------
// wxBufferedPaintDC
//----------------------------------------------------------------------------
#ifndef __CLASS_WX_BUFFEREDPAINTDC_H__
#define __CLASS_WX_BUFFEREDPAINTDC_H__
#include <wx/dcbuffer.h>

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Class declaration for wxBufferedPaintDC
//----------------------------------------------------------------------------
Gura_DeclareUserClass(wx_BufferedPaintDC);

//----------------------------------------------------------------------------
// Object declaration for wxBufferedPaintDC
//----------------------------------------------------------------------------
class Object_wx_BufferedPaintDC : public Object_wx_BufferedDC {
public:
	Gura_DeclareObjectAccessor(wx_BufferedPaintDC)
public:
	inline Object_wx_BufferedPaintDC(wxBufferedPaintDC *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object_wx_BufferedDC(Gura_UserClass(wx_BufferedPaintDC), pEntity, pObserver, ownerFlag) {}
	inline Object_wx_BufferedPaintDC(Class *pClass, wxBufferedPaintDC *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object_wx_BufferedDC(pClass, pEntity, pObserver, ownerFlag) {}
	virtual ~Object_wx_BufferedPaintDC();
	virtual Object *Clone() const;
	virtual String ToString(bool exprFlag);
	inline wxBufferedPaintDC *GetEntity() {
		return static_cast<wxBufferedPaintDC *>(_pEntity);
	}
	inline wxBufferedPaintDC *ReleaseEntity() {
		wxBufferedPaintDC *pEntity = GetEntity();
		InvalidateEntity();
		return pEntity;
	}
	inline bool IsInvalid(Environment &env) const {
		if (_pEntity != nullptr) return false;
		SetError_InvalidWxObject(env, "wxBufferedPaintDC");
		return true;
	}
};

Gura_EndModuleScope(wx)

#endif
