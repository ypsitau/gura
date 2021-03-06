//----------------------------------------------------------------------------
// wxControlWithItems
//----------------------------------------------------------------------------
#ifndef __CLASS_WX_CONTROLWITHITEMS_H__
#define __CLASS_WX_CONTROLWITHITEMS_H__
#include <wx/ctrlsub.h>

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Class declaration for wxControlWithItems
//----------------------------------------------------------------------------
Gura_DeclareUserClass(wx_ControlWithItems);

//----------------------------------------------------------------------------
// Object declaration for wxControlWithItems
//----------------------------------------------------------------------------
class Object_wx_ControlWithItems : public Object_wx_Control {
public:
	Gura_DeclareObjectAccessor(wx_ControlWithItems)
public:
	inline Object_wx_ControlWithItems(wxControlWithItems *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object_wx_Control(Gura_UserClass(wx_ControlWithItems), pEntity, pObserver, ownerFlag) {}
	inline Object_wx_ControlWithItems(Class *pClass, wxControlWithItems *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object_wx_Control(pClass, pEntity, pObserver, ownerFlag) {}
	virtual ~Object_wx_ControlWithItems();
	virtual Object *Clone() const;
	virtual String ToString(bool exprFlag);
	inline wxControlWithItems *GetEntity() {
		return static_cast<wxControlWithItems *>(_pEntity);
	}
	inline wxControlWithItems *ReleaseEntity() {
		wxControlWithItems *pEntity = GetEntity();
		InvalidateEntity();
		return pEntity;
	}
	inline bool IsInvalid(Environment &env) const {
		if (_pEntity != nullptr) return false;
		SetError_InvalidWxObject(env, "wxControlWithItems");
		return true;
	}
};

Gura_EndModuleScope(wx)

#endif
