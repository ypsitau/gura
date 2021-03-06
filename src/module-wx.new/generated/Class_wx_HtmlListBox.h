//----------------------------------------------------------------------------
// wxHtmlListBox
//----------------------------------------------------------------------------
#ifndef __CLASS_WX_HTMLLISTBOX_H__
#define __CLASS_WX_HTMLLISTBOX_H__
#include <wx/htmllbox.h>

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Class declaration for wxHtmlListBox
//----------------------------------------------------------------------------
Gura_DeclareUserClass(wx_HtmlListBox);

//----------------------------------------------------------------------------
// Object declaration for wxHtmlListBox
//----------------------------------------------------------------------------
class Object_wx_HtmlListBox : public Object_wx_VListBox {
public:
	Gura_DeclareObjectAccessor(wx_HtmlListBox)
public:
	inline Object_wx_HtmlListBox(wxHtmlListBox *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object_wx_VListBox(Gura_UserClass(wx_HtmlListBox), pEntity, pObserver, ownerFlag) {}
	inline Object_wx_HtmlListBox(Class *pClass, wxHtmlListBox *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object_wx_VListBox(pClass, pEntity, pObserver, ownerFlag) {}
	virtual ~Object_wx_HtmlListBox();
	virtual Object *Clone() const;
	virtual String ToString(bool exprFlag);
	inline wxHtmlListBox *GetEntity() {
		return static_cast<wxHtmlListBox *>(_pEntity);
	}
	inline wxHtmlListBox *ReleaseEntity() {
		wxHtmlListBox *pEntity = GetEntity();
		InvalidateEntity();
		return pEntity;
	}
	inline bool IsInvalid(Environment &env) const {
		if (_pEntity != nullptr) return false;
		SetError_InvalidWxObject(env, "wxHtmlListBox");
		return true;
	}
};

Gura_EndModuleScope(wx)

#endif
