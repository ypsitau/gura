//----------------------------------------------------------------------------
// wxCustomDataObject
// extracted from custdobj.tex
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

Gura_DeclarePrivUserSymbol(Alloc);
Gura_DeclarePrivUserSymbol(Free);
Gura_DeclarePrivUserSymbol(GetSize);
Gura_DeclarePrivUserSymbol(GetData);
Gura_DeclarePrivUserSymbol(SetData);
Gura_DeclarePrivUserSymbol(TakeData);

//----------------------------------------------------------------------------
// Class derivation
//----------------------------------------------------------------------------
class wx_CustomDataObject: public wxCustomDataObject, public GuraObjectObserver {
private:
	//Gura::Signal *_pSig;
	Object_wx_CustomDataObject *_pObj;
public:
	inline wx_CustomDataObject(const wxDataFormat& format) : wxCustomDataObject(format), _pObj(nullptr) {}
	//virtual void * Alloc(size_t size);
	//virtual void Free();
	//virtual size_t GetSize();
	//virtual void * GetData();
	//virtual void SetData(size_t size, const void *data);
	//virtual void TakeData(size_t size, const void *data);
	~wx_CustomDataObject();
	inline void AssocWithGura(Object_wx_CustomDataObject *pObj) {
		_pObj = pObj;
	}
	// virtual function of GuraObjectObserver
	virtual void GuraObjectDeleted();
};

wx_CustomDataObject::~wx_CustomDataObject()
{
	if (_pObj != nullptr) _pObj->InvalidateEntity();
}

void wx_CustomDataObject::GuraObjectDeleted()
{
	_pObj = nullptr;
}

//----------------------------------------------------------------------------
// Gura interfaces for wxCustomDataObject
//----------------------------------------------------------------------------
Gura_DeclareFunction(CustomDataObject)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	SetClassToConstruct(Gura_UserClass(wx_CustomDataObject));
	DeclareArg(env, "format", VTYPE_wx_DataFormat, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(CustomDataObject)
{
	Signal &sig = env.GetSignal();
	if (!CheckWxReady(sig)) return Value::Nil;
	wxDataFormat *format = (wxDataFormat *)(&wxFormatInvalid);
	if (arg.IsValid(0)) format = Object_wx_DataFormat::GetObject(arg, 0)->GetEntity();
	wx_CustomDataObject *pEntity = new wx_CustomDataObject(*format);
	Object_wx_CustomDataObject *pObj = Object_wx_CustomDataObject::GetObjectThis(arg);
	if (pObj == nullptr) {
		pObj = new Object_wx_CustomDataObject(pEntity, pEntity, OwnerFalse);
		pEntity->AssocWithGura(pObj);
		return ReturnValue(env, arg, Value(pObj));
	}
	pObj->SetEntity(pEntity, pEntity, OwnerFalse);
	pEntity->AssocWithGura(pObj);
	return ReturnValue(env, arg, arg.GetValueThis());
}

Gura_DeclareMethod(wx_CustomDataObject, Alloc)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "size", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_CustomDataObject, Alloc)
{
	Signal &sig = env.GetSignal();
	Object_wx_CustomDataObject *pThis = Object_wx_CustomDataObject::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	size_t size = arg.GetSizeT(0);
	pThis->GetEntity()->Alloc(size);
	return Value::Nil;
}

Gura_DeclareMethod(wx_CustomDataObject, Free)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_CustomDataObject, Free)
{
	Signal &sig = env.GetSignal();
	Object_wx_CustomDataObject *pThis = Object_wx_CustomDataObject::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	pThis->GetEntity()->Free();
	return Value::Nil;
}

Gura_DeclareMethod(wx_CustomDataObject, GetSize)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_CustomDataObject, GetSize)
{
	Signal &sig = env.GetSignal();
	Object_wx_CustomDataObject *pThis = Object_wx_CustomDataObject::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	size_t rtn = pThis->GetEntity()->GetSize();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_CustomDataObject, GetData)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_CustomDataObject, GetData)
{
	Signal &sig = env.GetSignal();
	Object_wx_CustomDataObject *pThis = Object_wx_CustomDataObject::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	pThis->GetEntity()->GetData();
	return Value::Nil;
}

Gura_DeclareMethod(wx_CustomDataObject, SetData)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
#if 0
	DeclareArg(env, "size", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "*data", VTYPE_number, OCCUR_Once);
#endif
}

Gura_ImplementMethod(wx_CustomDataObject, SetData)
{
	Signal &sig = env.GetSignal();
#if 0
	Object_wx_CustomDataObject *pThis = Object_wx_CustomDataObject::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	size_t size = arg.GetSizeT(0);
	int *data = arg.GetInt(1);
	pThis->GetEntity()->SetData(size, *data);
	return Value::Nil;
#endif
	SetError_NotImplemented(sig);
	return Value::Nil;
}

Gura_DeclareMethod(wx_CustomDataObject, TakeData)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
#if 0
	DeclareArg(env, "size", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "*data", VTYPE_number, OCCUR_Once);
#endif
}

Gura_ImplementMethod(wx_CustomDataObject, TakeData)
{
	Signal &sig = env.GetSignal();
#if 0
	Object_wx_CustomDataObject *pThis = Object_wx_CustomDataObject::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	size_t size = arg.GetSizeT(0);
	int *data = arg.GetInt(1);
	pThis->GetEntity()->TakeData(size, *data);
	return Value::Nil;
#endif
	SetError_NotImplemented(sig);
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Object implementation for wxCustomDataObject
//----------------------------------------------------------------------------
Object_wx_CustomDataObject::~Object_wx_CustomDataObject()
{
}

Object *Object_wx_CustomDataObject::Clone() const
{
	return nullptr;
}

String Object_wx_CustomDataObject::ToString(bool exprFlag)
{
	String rtn("<wx.CustomDataObject:");
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
// Class implementation for wxCustomDataObject
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_CustomDataObject)
{
	Gura_RealizeUserSymbol(Alloc);
	Gura_RealizeUserSymbol(Free);
	Gura_RealizeUserSymbol(GetSize);
	Gura_RealizeUserSymbol(GetData);
	Gura_RealizeUserSymbol(SetData);
	Gura_RealizeUserSymbol(TakeData);
	Gura_AssignFunction(CustomDataObject);
	Gura_AssignMethod(wx_CustomDataObject, Alloc);
	Gura_AssignMethod(wx_CustomDataObject, Free);
	Gura_AssignMethod(wx_CustomDataObject, GetSize);
	Gura_AssignMethod(wx_CustomDataObject, GetData);
	Gura_AssignMethod(wx_CustomDataObject, SetData);
	Gura_AssignMethod(wx_CustomDataObject, TakeData);
}

Gura_ImplementDescendantCreator(wx_CustomDataObject)
{
	return new Object_wx_CustomDataObject((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
