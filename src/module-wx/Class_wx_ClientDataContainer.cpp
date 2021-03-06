//----------------------------------------------------------------------------
// wxClientDataContainer
// extracted from clientdat.tex
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Class derivation
//----------------------------------------------------------------------------
class wx_ClientDataContainer: public wxClientDataContainer, public GuraObjectObserver {
private:
	//Gura::Signal *_pSig;
	Object_wx_ClientDataContainer *_pObj;
public:
	inline wx_ClientDataContainer() : wxClientDataContainer(), _pObj(nullptr) {}
	~wx_ClientDataContainer();
	inline void AssocWithGura(Object_wx_ClientDataContainer *pObj) {
		_pObj = pObj;
	}
	// virtual function of GuraObjectObserver
	virtual void GuraObjectDeleted();
};

wx_ClientDataContainer::~wx_ClientDataContainer()
{
	if (_pObj != nullptr) _pObj->InvalidateEntity();
}

void wx_ClientDataContainer::GuraObjectDeleted()
{
	_pObj = nullptr;
}

//----------------------------------------------------------------------------
// Gura interfaces for wxClientDataContainer
//----------------------------------------------------------------------------
Gura_DeclareFunction(ClientDataContainerEmpty)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	SetClassToConstruct(Gura_UserClass(wx_ClientDataContainer));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(ClientDataContainerEmpty)
{
	Signal &sig = env.GetSignal();
	if (!CheckWxReady(sig)) return Value::Nil;
	wx_ClientDataContainer *pEntity = new wx_ClientDataContainer();
	Object_wx_ClientDataContainer *pObj = Object_wx_ClientDataContainer::GetObjectThis(arg);
	if (pObj == nullptr) {
		pObj = new Object_wx_ClientDataContainer(pEntity, pEntity, OwnerFalse);
		pEntity->AssocWithGura(pObj);
		return ReturnValue(env, arg, Value(pObj));
	}
	pObj->SetEntity(pEntity, pEntity, OwnerFalse);
	pEntity->AssocWithGura(pObj);
	return ReturnValue(env, arg, arg.GetValueThis());
}

Gura_DeclareMethod(wx_ClientDataContainer, GetClientData)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_ClientDataContainer, GetClientData)
{
	Signal &sig = env.GetSignal();
	Object_wx_ClientDataContainer *pThis = Object_wx_ClientDataContainer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	pThis->GetEntity()->GetClientData();
	return Value::Nil;
}

Gura_DeclareMethod(wx_ClientDataContainer, GetClientObject)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_ClientDataContainer, GetClientObject)
{
	Signal &sig = env.GetSignal();
#if 0
	Object_wx_ClientDataContainer *pThis = Object_wx_ClientDataContainer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxClientData *rtn = (wxClientData *)pThis->GetEntity()->GetClientObject();
	return ReturnValue(env, arg, Value(new Object_wx_ClientData(rtn, nullptr, OwnerFalse)));
#endif
	SetError_NotImplemented(sig);
	return Value::Nil;
}

Gura_DeclareMethod(wx_ClientDataContainer, SetClientData)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
#if 0
	DeclareArg(env, "data", VTYPE_number, OCCUR_Once);
#endif
}

Gura_ImplementMethod(wx_ClientDataContainer, SetClientData)
{
	Signal &sig = env.GetSignal();
#if 0
	Object_wx_ClientDataContainer *pThis = Object_wx_ClientDataContainer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	int data = arg.GetInt(0);
	pThis->GetEntity()->SetClientData(data);
	return Value::Nil;
#endif
	SetError_NotImplemented(sig);
	return Value::Nil;
}

Gura_DeclareMethod(wx_ClientDataContainer, SetClientObject)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "data", VTYPE_wx_ClientData, OCCUR_Once);
}

Gura_ImplementMethod(wx_ClientDataContainer, SetClientObject)
{
	Signal &sig = env.GetSignal();
	Object_wx_ClientDataContainer *pThis = Object_wx_ClientDataContainer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxClientData *data = Object_wx_ClientData::GetObject(arg, 0)->GetEntity();
	pThis->GetEntity()->SetClientObject(data);
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Object implementation for wxClientDataContainer
//----------------------------------------------------------------------------
Object_wx_ClientDataContainer::~Object_wx_ClientDataContainer()
{
	if (_pEntity != nullptr) NotifyGuraObjectDeleted();
	if (_ownerFlag) delete _pEntity;
	_pEntity = nullptr;
}

Object *Object_wx_ClientDataContainer::Clone() const
{
	return nullptr;
}

String Object_wx_ClientDataContainer::ToString(bool exprFlag)
{
	String rtn("<wx.ClientDataContainer:");
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
// Class implementation for wxClientDataContainer
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_ClientDataContainer)
{
	Gura_AssignFunction(ClientDataContainerEmpty);
	Gura_AssignMethod(wx_ClientDataContainer, GetClientData);
	Gura_AssignMethod(wx_ClientDataContainer, GetClientObject);
	Gura_AssignMethod(wx_ClientDataContainer, SetClientData);
	Gura_AssignMethod(wx_ClientDataContainer, SetClientObject);
}

Gura_ImplementDescendantCreator(wx_ClientDataContainer)
{
	return new Object_wx_ClientDataContainer((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
