//----------------------------------------------------------------------------
// wxRichTextFormattingDialog
//----------------------------------------------------------------------------
#ifndef __CLASS_WX_RICHTEXTFORMATTINGDIALOG_H__
#define __CLASS_WX_RICHTEXTFORMATTINGDIALOG_H__
#include <wx/richtext/richtextformatdlg.h>

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Class declaration for wxRichTextFormattingDialog
//----------------------------------------------------------------------------
Gura_DeclareUserClass(wx_RichTextFormattingDialog);

//----------------------------------------------------------------------------
// Object declaration for wxRichTextFormattingDialog
//----------------------------------------------------------------------------
class Object_wx_RichTextFormattingDialog : public Object_wx_PropertySheetDialog {
public:
	Gura_DeclareObjectAccessor(wx_RichTextFormattingDialog)
public:
	inline Object_wx_RichTextFormattingDialog(wxRichTextFormattingDialog *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object_wx_PropertySheetDialog(Gura_UserClass(wx_RichTextFormattingDialog), pEntity, pObserver, ownerFlag) {}
	inline Object_wx_RichTextFormattingDialog(Class *pClass, wxRichTextFormattingDialog *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object_wx_PropertySheetDialog(pClass, pEntity, pObserver, ownerFlag) {}
	virtual ~Object_wx_RichTextFormattingDialog();
	virtual Object *Clone() const;
	virtual String ToString(bool exprFlag);
	inline wxRichTextFormattingDialog *GetEntity() {
		return static_cast<wxRichTextFormattingDialog *>(_pEntity);
	}
	inline wxRichTextFormattingDialog *ReleaseEntity() {
		wxRichTextFormattingDialog *pEntity = GetEntity();
		InvalidateEntity();
		return pEntity;
	}
	inline bool IsInvalid(Environment &env) const {
		if (_pEntity != nullptr) return false;
		SetError_InvalidWxObject(env, "wxRichTextFormattingDialog");
		return true;
	}
};

Gura_EndModuleScope(wx)

#endif
