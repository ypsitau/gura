//----------------------------------------------------------------------------
// wxColourDialog
//----------------------------------------------------------------------------
#ifndef __CLASS_WX_COLOURDIALOG_H__
#define __CLASS_WX_COLOURDIALOG_H__
#include <wx/colordlg.h>

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Class declaration for wxColourDialog
//----------------------------------------------------------------------------
Gura_DeclareUserClass(wx_ColourDialog);

//----------------------------------------------------------------------------
// Object declaration for wxColourDialog
//----------------------------------------------------------------------------
class Object_wx_ColourDialog : public Object_wx_Dialog {
public:
	Gura_DeclareObjectAccessor(wx_ColourDialog)
public:
	inline Object_wx_ColourDialog(wxColourDialog *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object_wx_Dialog(Gura_UserClass(wx_ColourDialog), pEntity, pObserver, ownerFlag) {}
	inline Object_wx_ColourDialog(Class *pClass, wxColourDialog *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object_wx_Dialog(pClass, pEntity, pObserver, ownerFlag) {}
	virtual ~Object_wx_ColourDialog();
	virtual Object *Clone() const;
	virtual String ToString(bool exprFlag);
	inline wxColourDialog *GetEntity() {
		return static_cast<wxColourDialog *>(_pEntity);
	}
	inline wxColourDialog *ReleaseEntity() {
		wxColourDialog *pEntity = GetEntity();
		InvalidateEntity();
		return pEntity;
	}
	inline bool IsInvalid(Environment &env) const {
		if (_pEntity != nullptr) return false;
		SetError_InvalidWxObject(env, "wxColourDialog");
		return true;
	}
};

Gura_EndModuleScope(wx)

#endif
