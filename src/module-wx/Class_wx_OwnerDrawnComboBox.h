//----------------------------------------------------------------------------
// wxOwnerDrawnComboBox
// extracted from odcbox.tex
//----------------------------------------------------------------------------
#ifndef __CLASS_WX_OWNERDRAWNCOMBOBOX_H__
#define __CLASS_WX_OWNERDRAWNCOMBOBOX_H__

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Class declaration for wxOwnerDrawnComboBox
//----------------------------------------------------------------------------
Gura_DeclareUserClass(wx_OwnerDrawnComboBox);

//----------------------------------------------------------------------------
// Object declaration for wxOwnerDrawnComboBox
//----------------------------------------------------------------------------
class Object_wx_OwnerDrawnComboBox : public Object_wx_ComboCtrl {
public:
	Gura_DeclareObjectAccessor(wx_OwnerDrawnComboBox)
public:
	inline Object_wx_OwnerDrawnComboBox(wxOwnerDrawnComboBox *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object_wx_ComboCtrl(Gura_UserClass(wx_OwnerDrawnComboBox), pEntity, pObserver, ownerFlag) {}
	inline Object_wx_OwnerDrawnComboBox(Class *pClass, wxOwnerDrawnComboBox *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object_wx_ComboCtrl(pClass, pEntity, pObserver, ownerFlag) {}
	virtual ~Object_wx_OwnerDrawnComboBox();
	virtual Object *Clone() const;
	virtual String ToString(bool exprFlag);
	inline wxOwnerDrawnComboBox *GetEntity() {
		return dynamic_cast<wxOwnerDrawnComboBox *>(_pEntity);
	}
	inline wxOwnerDrawnComboBox *ReleaseEntity() {
		wxOwnerDrawnComboBox *pEntity = GetEntity();
		InvalidateEntity();
		return pEntity;
	}
	inline bool IsInvalid(Signal &sig) const {
		if (_pEntity != nullptr) return false;
		SetError_InvalidWxObject(sig, "wxOwnerDrawnComboBox");
		return true;
	}
};

Gura_EndModuleScope(wx)

#endif
