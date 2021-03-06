//----------------------------------------------------------------------------
// wxLogPassThrough
// extracted from log.tex
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Class derivation
//----------------------------------------------------------------------------
class wx_LogPassThrough: public wxLogPassThrough, public GuraObjectObserver {
private:
	//Gura::Signal *_pSig;
	Object_wx_LogPassThrough *_pObj;
public:
	~wx_LogPassThrough();
	inline void AssocWithGura(Object_wx_LogPassThrough *pObj) {
		_pObj = pObj;
	}
	// virtual function of GuraObjectObserver
	virtual void GuraObjectDeleted();
};

wx_LogPassThrough::~wx_LogPassThrough()
{
	if (_pObj != nullptr) _pObj->InvalidateEntity();
}

void wx_LogPassThrough::GuraObjectDeleted()
{
	_pObj = nullptr;
}

//----------------------------------------------------------------------------
// Gura interfaces for wxLogPassThrough
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Object implementation for wxLogPassThrough
//----------------------------------------------------------------------------
Object_wx_LogPassThrough::~Object_wx_LogPassThrough()
{
}

Object *Object_wx_LogPassThrough::Clone() const
{
	return nullptr;
}

String Object_wx_LogPassThrough::ToString(bool exprFlag)
{
	String rtn("<wx.LogPassThrough:");
	if (GetEntity() == nullptr) {
		rtn += "invalid>";
	} else {
		char buff[64];
		::sprintf(buff, "%p>", GetEntity());
		rtn += buff;
	}
	return rtn;
}

//----------------------------------------------------------------------------
// Class implementation for wxLogPassThrough
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_LogPassThrough)
{
}

Gura_ImplementDescendantCreator(wx_LogPassThrough)
{
	return new Object_wx_LogPassThrough((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
