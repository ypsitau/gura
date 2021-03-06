//----------------------------------------------------------------------------
// wxArchiveNotifier
// (automatically generated)
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Class derivation
//----------------------------------------------------------------------------
class wx_ArchiveNotifier: public wxArchiveNotifier, public GuraObjectObserver {
private:
	//Gura::Signal *_pSig;
	Object_wx_ArchiveNotifier *_pObj;
public:
	~wx_ArchiveNotifier();
	inline void AssocWithGura(Object_wx_ArchiveNotifier *pObj) {
		_pObj = pObj;
	}
	// virtual function of GuraObjectObserver
	virtual void GuraObjectDeleted();
};

wx_ArchiveNotifier::~wx_ArchiveNotifier()
{
	if (_pObj != nullptr) _pObj->InvalidateEntity();
}

void wx_ArchiveNotifier::GuraObjectDeleted()
{
	_pObj = nullptr;
}

//----------------------------------------------------------------------------
// Gura interfaces for wxArchiveNotifier
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Object implementation for wxArchiveNotifier
//----------------------------------------------------------------------------
Object_wx_ArchiveNotifier::~Object_wx_ArchiveNotifier()
{
	if (_pEntity != nullptr) NotifyGuraObjectDeleted();
	if (_ownerFlag) delete _pEntity;
	_pEntity = nullptr;
}

Object *Object_wx_ArchiveNotifier::Clone() const
{
	return nullptr;
}

String Object_wx_ArchiveNotifier::ToString(bool exprFlag)
{
	String rtn("<wx.ArchiveNotifier:");
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
// Class implementation for wxArchiveNotifier
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_ArchiveNotifier)
{
}

Gura_ImplementDescendantCreator(wx_ArchiveNotifier)
{
	return new Object_wx_ArchiveNotifier((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
