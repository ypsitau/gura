//----------------------------------------------------------------------------
// wxFrame
//----------------------------------------------------------------------------
#ifndef __CLASS_WX_FRAME_H__
#define __CLASS_WX_FRAME_H__
#include <wx/frame.h>

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Class declaration for wxFrame
//----------------------------------------------------------------------------
Gura_DeclareUserClass(wx_Frame);

//----------------------------------------------------------------------------
// Object declaration for wxFrame
//----------------------------------------------------------------------------
class Object_wx_Frame : public Object_wx_TopLevelWindow {
public:
	Gura_DeclareObjectAccessor(wx_Frame)
public:
	inline Object_wx_Frame(wxFrame *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object_wx_TopLevelWindow(Gura_UserClass(wx_Frame), pEntity, pObserver, ownerFlag) {}
	inline Object_wx_Frame(Class *pClass, wxFrame *pEntity, GuraObjectObserver *pObserver, bool ownerFlag) :
				Object_wx_TopLevelWindow(pClass, pEntity, pObserver, ownerFlag) {}
	virtual ~Object_wx_Frame();
	virtual Object *Clone() const;
	virtual String ToString(bool exprFlag);
	inline wxFrame *GetEntity() {
		return static_cast<wxFrame *>(_pEntity);
	}
	inline wxFrame *ReleaseEntity() {
		wxFrame *pEntity = GetEntity();
		InvalidateEntity();
		return pEntity;
	}
	inline bool IsInvalid(Environment &env) const {
		if (_pEntity != nullptr) return false;
		SetError_InvalidWxObject(env, "wxFrame");
		return true;
	}
};

Gura_EndModuleScope(wx)

#endif
