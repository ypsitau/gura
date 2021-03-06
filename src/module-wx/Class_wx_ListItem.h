//----------------------------------------------------------------------------
// wxListItem
// extracted from listitem.tex
//----------------------------------------------------------------------------
#ifndef __CLASS_WX_LISTITEM_H__
#define __CLASS_WX_LISTITEM_H__

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Class declaration for wxListItem
//----------------------------------------------------------------------------
Gura_DeclareUserClass(wx_ListItem);

//----------------------------------------------------------------------------
// Object declaration for wxListItem
//----------------------------------------------------------------------------
class Object_wx_ListItem : public Object_wx_Object {
public:
	Gura_DeclareObjectAccessor(wx_ListItem)
public:
	inline Object_wx_ListItem(wxListItem *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object_wx_Object(Gura_UserClass(wx_ListItem), pEntity, pObserver, ownerFlag) {}
	inline Object_wx_ListItem(Class *pClass, wxListItem *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object_wx_Object(pClass, pEntity, pObserver, ownerFlag) {}
	virtual ~Object_wx_ListItem();
	virtual Object *Clone() const;
	virtual String ToString(bool exprFlag);
	inline wxListItem *GetEntity() {
		return dynamic_cast<wxListItem *>(_pEntity);
	}
	inline wxListItem *ReleaseEntity() {
		wxListItem *pEntity = GetEntity();
		InvalidateEntity();
		return pEntity;
	}
	inline bool IsInvalid(Signal &sig) const {
		if (_pEntity != nullptr) return false;
		SetError_InvalidWxObject(sig, "wxListItem");
		return true;
	}
};

Gura_EndModuleScope(wx)

#endif
