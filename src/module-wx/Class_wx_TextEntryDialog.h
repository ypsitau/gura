//----------------------------------------------------------------------------
// wxTextEntryDialog
// extracted from textdlg.tex
//----------------------------------------------------------------------------
#ifndef __CLASS_WX_TEXTENTRYDIALOG_H__
#define __CLASS_WX_TEXTENTRYDIALOG_H__

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Class declaration for wxTextEntryDialog
//----------------------------------------------------------------------------
Gura_DeclareUserClass(wx_TextEntryDialog);

//----------------------------------------------------------------------------
// Object declaration for wxTextEntryDialog
//----------------------------------------------------------------------------
class Object_wx_TextEntryDialog : public Object_wx_Dialog {
public:
	Gura_DeclareObjectAccessor(wx_TextEntryDialog)
public:
	inline Object_wx_TextEntryDialog(wxTextEntryDialog *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object_wx_Dialog(Gura_UserClass(wx_TextEntryDialog), pEntity, pObserver, ownerFlag) {}
	inline Object_wx_TextEntryDialog(Class *pClass, wxTextEntryDialog *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object_wx_Dialog(pClass, pEntity, pObserver, ownerFlag) {}
	virtual ~Object_wx_TextEntryDialog();
	virtual Object *Clone() const;
	virtual String ToString(bool exprFlag);
	inline wxTextEntryDialog *GetEntity() {
		return dynamic_cast<wxTextEntryDialog *>(_pEntity);
	}
	inline wxTextEntryDialog *ReleaseEntity() {
		wxTextEntryDialog *pEntity = GetEntity();
		InvalidateEntity();
		return pEntity;
	}
	inline bool IsInvalid(Signal &sig) const {
		if (_pEntity != nullptr) return false;
		SetError_InvalidWxObject(sig, "wxTextEntryDialog");
		return true;
	}
};

Gura_EndModuleScope(wx)

#endif
