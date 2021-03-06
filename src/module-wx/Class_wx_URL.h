//----------------------------------------------------------------------------
// wxURL
// extracted from url.tex
//----------------------------------------------------------------------------
#ifndef __CLASS_WX_URL_H__
#define __CLASS_WX_URL_H__

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Class declaration for wxURL
//----------------------------------------------------------------------------
Gura_DeclareUserClass(wx_URL);

//----------------------------------------------------------------------------
// Object declaration for wxURL
//----------------------------------------------------------------------------
class Object_wx_URL : public Object_wx_URI {
public:
	Gura_DeclareObjectAccessor(wx_URL)
public:
	inline Object_wx_URL(wxURL *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object_wx_URI(Gura_UserClass(wx_URL), pEntity, pObserver, ownerFlag) {}
	inline Object_wx_URL(Class *pClass, wxURL *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object_wx_URI(pClass, pEntity, pObserver, ownerFlag) {}
	virtual ~Object_wx_URL();
	virtual Object *Clone() const;
	virtual String ToString(bool exprFlag);
	inline wxURL *GetEntity() {
		return dynamic_cast<wxURL *>(_pEntity);
	}
	inline wxURL *ReleaseEntity() {
		wxURL *pEntity = GetEntity();
		InvalidateEntity();
		return pEntity;
	}
	inline bool IsInvalid(Signal &sig) const {
		if (_pEntity != nullptr) return false;
		SetError_InvalidWxObject(sig, "wxURL");
		return true;
	}
};

Gura_EndModuleScope(wx)

#endif
