//----------------------------------------------------------------------------
// wxTIFFHandler
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Class derivation
//----------------------------------------------------------------------------
class wx_TIFFHandler: public wxTIFFHandler, public GuraObjectObserver {
private:
	//Gura::Signal *_pSig;
	Object_wx_TIFFHandler *_pObj;
public:
	~wx_TIFFHandler();
	inline void AssocWithGura(Object_wx_TIFFHandler *pObj) {
		_pObj = pObj;
	}
	// virtual function of GuraObjectObserver
	virtual void GuraObjectDeleted();
};

wx_TIFFHandler::~wx_TIFFHandler()
{
	if (_pObj != nullptr) _pObj->InvalidateEntity();
}

void wx_TIFFHandler::GuraObjectDeleted()
{
	_pObj = nullptr;
}

//----------------------------------------------------------------------------
// Gura interfaces for wxTIFFHandler
//----------------------------------------------------------------------------
Gura_DeclareFunction(TIFFHandler)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	SetClassToConstruct(Gura_UserClass(wx_TIFFHandler));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(TIFFHandler)
{
	Signal &sig = env.GetSignal();
	if (!CheckWxReady(sig)) return Value::Nil;
	wx_TIFFHandler *pEntity = new wx_TIFFHandler();
	Object_wx_TIFFHandler *pObj = Object_wx_TIFFHandler::GetObjectThis(arg);
	if (pObj == nullptr) {
		pObj = new Object_wx_TIFFHandler(pEntity, pEntity, OwnerFalse);
		pEntity->AssocWithGura(pObj);
		return ReturnValue(env, arg, Value(pObj));
	}
	pObj->SetEntity(pEntity, pEntity, OwnerFalse);
	pEntity->AssocWithGura(pObj);
	return ReturnValue(env, arg, arg.GetValueThis());
}

//----------------------------------------------------------------------------
// Object implementation for wxTIFFHandler
//----------------------------------------------------------------------------
Object_wx_TIFFHandler::~Object_wx_TIFFHandler()
{
	if (_pEntity != nullptr) NotifyGuraObjectDeleted();
	if (_ownerFlag) delete _pEntity;
	_pEntity = nullptr;
}

Object *Object_wx_TIFFHandler::Clone() const
{
	return nullptr;
}

String Object_wx_TIFFHandler::ToString(bool exprFlag)
{
	String rtn("<wx.TIFFHandler:");
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
// Class implementation for wxTIFFHandler
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_TIFFHandler)
{
	Gura_AssignFunction(TIFFHandler);
}

Gura_ImplementDescendantCreator(wx_TIFFHandler)
{
	return new Object_wx_TIFFHandler((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
