//----------------------------------------------------------------------------
// wxRichTextStyleSheet
//----------------------------------------------------------------------------
#ifndef __CLASS_WX_RICHTEXTSTYLESHEET_H__
#define __CLASS_WX_RICHTEXTSTYLESHEET_H__
#include <wx/richtext/richtextstyles.h>

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Class declaration for wxRichTextStyleSheet
//----------------------------------------------------------------------------
Gura_DeclareUserClass(wx_RichTextStyleSheet);

//----------------------------------------------------------------------------
// Object declaration for wxRichTextStyleSheet
//----------------------------------------------------------------------------
class Object_wx_RichTextStyleSheet : public Object_wx_Object {
public:
	Gura_DeclareObjectAccessor(wx_RichTextStyleSheet)
public:
	inline Object_wx_RichTextStyleSheet(wxRichTextStyleSheet *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object_wx_Object(Gura_UserClass(wx_RichTextStyleSheet), pEntity, pObserver, ownerFlag) {}
	inline Object_wx_RichTextStyleSheet(Class *pClass, wxRichTextStyleSheet *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object_wx_Object(pClass, pEntity, pObserver, ownerFlag) {}
	virtual ~Object_wx_RichTextStyleSheet();
	virtual Object *Clone() const;
	virtual String ToString(bool exprFlag);
	inline wxRichTextStyleSheet *GetEntity() {
		return static_cast<wxRichTextStyleSheet *>(_pEntity);
	}
	inline wxRichTextStyleSheet *ReleaseEntity() {
		wxRichTextStyleSheet *pEntity = GetEntity();
		InvalidateEntity();
		return pEntity;
	}
	inline bool IsInvalid(Environment &env) const {
		if (_pEntity != nullptr) return false;
		SetError_InvalidWxObject(env, "wxRichTextStyleSheet");
		return true;
	}
};

Gura_EndModuleScope(wx)

#endif
