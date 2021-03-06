//----------------------------------------------------------------------------
// wxPrinterDC
//----------------------------------------------------------------------------
#ifndef __CLASS_WX_PRINTERDC_H__
#define __CLASS_WX_PRINTERDC_H__
#include <wx/dcprint.h>

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Class declaration for wxPrinterDC
//----------------------------------------------------------------------------
Gura_DeclareUserClass(wx_PrinterDC);

//----------------------------------------------------------------------------
// Object declaration for wxPrinterDC
//----------------------------------------------------------------------------
class Object_wx_PrinterDC : public Object_wx_DC {
public:
	Gura_DeclareObjectAccessor(wx_PrinterDC)
public:
	inline Object_wx_PrinterDC(wxPrinterDC *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object_wx_DC(Gura_UserClass(wx_PrinterDC), pEntity, pObserver, ownerFlag) {}
	inline Object_wx_PrinterDC(Class *pClass, wxPrinterDC *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object_wx_DC(pClass, pEntity, pObserver, ownerFlag) {}
	virtual ~Object_wx_PrinterDC();
	virtual Object *Clone() const;
	virtual String ToString(bool exprFlag);
	inline wxPrinterDC *GetEntity() {
		return static_cast<wxPrinterDC *>(_pEntity);
	}
	inline wxPrinterDC *ReleaseEntity() {
		wxPrinterDC *pEntity = GetEntity();
		InvalidateEntity();
		return pEntity;
	}
	inline bool IsInvalid(Environment &env) const {
		if (_pEntity != nullptr) return false;
		SetError_InvalidWxObject(env, "wxPrinterDC");
		return true;
	}
};

Gura_EndModuleScope(wx)

#endif
