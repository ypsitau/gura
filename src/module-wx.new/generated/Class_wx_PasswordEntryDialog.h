//----------------------------------------------------------------------------
// wxPasswordEntryDialog
//----------------------------------------------------------------------------
#ifndef __CLASS_WX_PASSWORDENTRYDIALOG_H__
#define __CLASS_WX_PASSWORDENTRYDIALOG_H__
#include <wx/textdlg.h>

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Class declaration for wxPasswordEntryDialog
//----------------------------------------------------------------------------
Gura_DeclareUserClass(wx_PasswordEntryDialog);

//----------------------------------------------------------------------------
// Object declaration for wxPasswordEntryDialog
//----------------------------------------------------------------------------
class Object_wx_PasswordEntryDialog : public Object_wx_TextEntryDialog {
public:
	Gura_DeclareObjectAccessor(wx_PasswordEntryDialog)
public:
	inline Object_wx_PasswordEntryDialog(wxPasswordEntryDialog *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object_wx_TextEntryDialog(Gura_UserClass(wx_PasswordEntryDialog), pEntity, pObserver, ownerFlag) {}
	inline Object_wx_PasswordEntryDialog(Class *pClass, wxPasswordEntryDialog *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object_wx_TextEntryDialog(pClass, pEntity, pObserver, ownerFlag) {}
	virtual ~Object_wx_PasswordEntryDialog();
	virtual Object *Clone() const;
	virtual String ToString(bool exprFlag);
	inline wxPasswordEntryDialog *GetEntity() {
		return static_cast<wxPasswordEntryDialog *>(_pEntity);
	}
	inline wxPasswordEntryDialog *ReleaseEntity() {
		wxPasswordEntryDialog *pEntity = GetEntity();
		InvalidateEntity();
		return pEntity;
	}
	inline bool IsInvalid(Environment &env) const {
		if (_pEntity != nullptr) return false;
		SetError_InvalidWxObject(env, "wxPasswordEntryDialog");
		return true;
	}
};

Gura_EndModuleScope(wx)

#endif
