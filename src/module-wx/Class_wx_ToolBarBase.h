//----------------------------------------------------------------------------
// wxToolBarBase
// (automatically generated)
//----------------------------------------------------------------------------
#ifndef __CLASS_WX_TOOLBARBASE_H__
#define __CLASS_WX_TOOLBARBASE_H__

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Class declaration for wxToolBarBase
//----------------------------------------------------------------------------
Gura_DeclareUserClass(wx_ToolBarBase);

//----------------------------------------------------------------------------
// Object declaration for wxToolBarBase
//----------------------------------------------------------------------------
class Object_wx_ToolBarBase : public Object_wx_Control {
public:
	Gura_DeclareObjectAccessor(wx_ToolBarBase)
public:
	inline Object_wx_ToolBarBase(wxToolBarBase *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object_wx_Control(Gura_UserClass(wx_ToolBarBase), pEntity, pObserver, ownerFlag) {}
	inline Object_wx_ToolBarBase(Class *pClass, wxToolBarBase *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object_wx_Control(pClass, pEntity, pObserver, ownerFlag) {}
	virtual ~Object_wx_ToolBarBase();
	virtual Object *Clone() const;
	virtual String ToString(bool exprFlag);
	inline wxToolBarBase *GetEntity() {
		return dynamic_cast<wxToolBarBase *>(_pEntity);
	}
	inline wxToolBarBase *ReleaseEntity() {
		wxToolBarBase *pEntity = GetEntity();
		InvalidateEntity();
		return pEntity;
	}
	inline bool IsInvalid(Signal &sig) const {
		if (_pEntity != nullptr) return false;
		SetError_InvalidWxObject(sig, "wxToolBarBase");
		return true;
	}
};

Gura_EndModuleScope(wx)

#endif
