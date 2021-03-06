//----------------------------------------------------------------------------
// wxTarInputStream
// extracted from tarstrm.tex
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Class derivation
//----------------------------------------------------------------------------
class wx_TarInputStream: public wxTarInputStream, public GuraObjectObserver {
private:
	//Gura::Signal *_pSig;
	Object_wx_TarInputStream *_pObj;
public:
	inline wx_TarInputStream(wxInputStream& stream, wxMBConv& conv) : wxTarInputStream(stream, conv), _pObj(nullptr) {}
	inline wx_TarInputStream(wxInputStream* stream, wxMBConv& conv) : wxTarInputStream(stream, conv), _pObj(nullptr) {}
	~wx_TarInputStream();
	inline void AssocWithGura(Object_wx_TarInputStream *pObj) {
		_pObj = pObj;
	}
	// virtual function of GuraObjectObserver
	virtual void GuraObjectDeleted();
};

wx_TarInputStream::~wx_TarInputStream()
{
	if (_pObj != nullptr) _pObj->InvalidateEntity();
}

void wx_TarInputStream::GuraObjectDeleted()
{
	_pObj = nullptr;
}

//----------------------------------------------------------------------------
// Gura interfaces for wxTarInputStream
//----------------------------------------------------------------------------
Gura_DeclareFunction(TarInputStream)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	SetClassToConstruct(Gura_UserClass(wx_TarInputStream));
	DeclareArg(env, "stream", VTYPE_wx_InputStream, OCCUR_Once);
	DeclareArg(env, "conv", VTYPE_wx_MBConv, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(TarInputStream)
{
	Signal &sig = env.GetSignal();
	if (!CheckWxReady(sig)) return Value::Nil;
	wxInputStream *stream = Object_wx_InputStream::GetObject(arg, 0)->GetEntity();
	wxMBConv *conv = (wxMBConv *)(&wxConvLocal);
	if (arg.IsValid(1)) conv = Object_wx_MBConv::GetObject(arg, 1)->GetEntity();
	wx_TarInputStream *pEntity = new wx_TarInputStream(*stream, *conv);
	Object_wx_TarInputStream *pObj = Object_wx_TarInputStream::GetObjectThis(arg);
	if (pObj == nullptr) {
		pObj = new Object_wx_TarInputStream(pEntity, pEntity, OwnerFalse);
		pEntity->AssocWithGura(pObj);
		return ReturnValue(env, arg, Value(pObj));
	}
	pObj->SetEntity(pEntity, pEntity, OwnerFalse);
	pEntity->AssocWithGura(pObj);
	return ReturnValue(env, arg, arg.GetValueThis());
}

Gura_DeclareFunction(TarInputStream_1)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	SetClassToConstruct(Gura_UserClass(wx_TarInputStream));
	DeclareArg(env, "stream", VTYPE_wx_InputStream, OCCUR_Once);
	DeclareArg(env, "conv", VTYPE_wx_MBConv, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(TarInputStream_1)
{
	Signal &sig = env.GetSignal();
	if (!CheckWxReady(sig)) return Value::Nil;
	wxInputStream *stream = Object_wx_InputStream::GetObject(arg, 0)->GetEntity();
	wxMBConv *conv = (wxMBConv *)(&wxConvLocal);
	if (arg.IsValid(1)) conv = Object_wx_MBConv::GetObject(arg, 1)->GetEntity();
	wx_TarInputStream *pEntity = new wx_TarInputStream(stream, *conv);
	Object_wx_TarInputStream *pObj = Object_wx_TarInputStream::GetObjectThis(arg);
	if (pObj == nullptr) {
		pObj = new Object_wx_TarInputStream(pEntity, pEntity, OwnerFalse);
		pEntity->AssocWithGura(pObj);
		return ReturnValue(env, arg, Value(pObj));
	}
	pObj->SetEntity(pEntity, pEntity, OwnerFalse);
	pEntity->AssocWithGura(pObj);
	return ReturnValue(env, arg, arg.GetValueThis());
}

Gura_DeclareMethod(wx_TarInputStream, CloseEntry)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_TarInputStream, CloseEntry)
{
	Signal &sig = env.GetSignal();
	Object_wx_TarInputStream *pThis = Object_wx_TarInputStream::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	bool rtn = pThis->GetEntity()->CloseEntry();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_TarInputStream, GetNextEntry)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_TarInputStream, GetNextEntry)
{
	Signal &sig = env.GetSignal();
	Object_wx_TarInputStream *pThis = Object_wx_TarInputStream::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxTarEntry *rtn = (wxTarEntry *)pThis->GetEntity()->GetNextEntry();
	return ReturnValue(env, arg, Value(new Object_wx_TarEntry(rtn, nullptr, OwnerFalse)));
}

Gura_DeclareMethod(wx_TarInputStream, OpenEntry)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "entry", VTYPE_wx_TarEntry, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_TarInputStream, OpenEntry)
{
	Signal &sig = env.GetSignal();
	Object_wx_TarInputStream *pThis = Object_wx_TarInputStream::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxTarEntry *entry = Object_wx_TarEntry::GetObject(arg, 0)->GetEntity();
	bool rtn = pThis->GetEntity()->OpenEntry(*entry);
	return ReturnValue(env, arg, Value(rtn));
}

//----------------------------------------------------------------------------
// Object implementation for wxTarInputStream
//----------------------------------------------------------------------------
Object_wx_TarInputStream::~Object_wx_TarInputStream()
{
}

Object *Object_wx_TarInputStream::Clone() const
{
	return nullptr;
}

String Object_wx_TarInputStream::ToString(bool exprFlag)
{
	String rtn("<wx.TarInputStream:");
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
// Class implementation for wxTarInputStream
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_TarInputStream)
{
	Gura_AssignFunction(TarInputStream);
	Gura_AssignFunction(TarInputStream_1);
	Gura_AssignMethod(wx_TarInputStream, CloseEntry);
	Gura_AssignMethod(wx_TarInputStream, GetNextEntry);
	Gura_AssignMethod(wx_TarInputStream, OpenEntry);
}

Gura_ImplementDescendantCreator(wx_TarInputStream)
{
	return new Object_wx_TarInputStream((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
