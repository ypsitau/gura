//----------------------------------------------------------------------------
// wxHtmlLinkInfo
//----------------------------------------------------------------------------
#ifndef __CLASS_WX_HTMLLINKINFO_H__
#define __CLASS_WX_HTMLLINKINFO_H__
#include <wx/html/htmlcell.h>

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Class declaration for wxHtmlLinkInfo
//----------------------------------------------------------------------------
Gura_DeclareUserClass(wx_HtmlLinkInfo);

//----------------------------------------------------------------------------
// Object declaration for wxHtmlLinkInfo
//----------------------------------------------------------------------------
class Object_wx_HtmlLinkInfo : public Object_wx_Object {
public:
	Gura_DeclareObjectAccessor(wx_HtmlLinkInfo)
public:
	inline Object_wx_HtmlLinkInfo(wxHtmlLinkInfo *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object_wx_Object(Gura_UserClass(wx_HtmlLinkInfo), pEntity, pObserver, ownerFlag) {}
	inline Object_wx_HtmlLinkInfo(Class *pClass, wxHtmlLinkInfo *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object_wx_Object(pClass, pEntity, pObserver, ownerFlag) {}
	virtual ~Object_wx_HtmlLinkInfo();
	virtual Object *Clone() const;
	virtual String ToString(bool exprFlag);
	inline wxHtmlLinkInfo *GetEntity() {
		return static_cast<wxHtmlLinkInfo *>(_pEntity);
	}
	inline wxHtmlLinkInfo *ReleaseEntity() {
		wxHtmlLinkInfo *pEntity = GetEntity();
		InvalidateEntity();
		return pEntity;
	}
	inline bool IsInvalid(Environment &env) const {
		if (_pEntity != nullptr) return false;
		SetError_InvalidWxObject(env, "wxHtmlLinkInfo");
		return true;
	}
};

Gura_EndModuleScope(wx)

#endif
