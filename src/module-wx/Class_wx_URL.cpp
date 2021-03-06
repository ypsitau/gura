//----------------------------------------------------------------------------
// wxURL
// extracted from url.tex
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Class derivation
//----------------------------------------------------------------------------
class wx_URL: public wxURL, public GuraObjectObserver {
private:
	//Gura::Signal *_pSig;
	Object_wx_URL *_pObj;
public:
	inline wx_URL(const wxString& url) : wxURL(url), _pObj(nullptr) {}
	~wx_URL();
	inline void AssocWithGura(Object_wx_URL *pObj) {
		_pObj = pObj;
	}
	// virtual function of GuraObjectObserver
	virtual void GuraObjectDeleted();
};

wx_URL::~wx_URL()
{
	if (_pObj != nullptr) _pObj->InvalidateEntity();
}

void wx_URL::GuraObjectDeleted()
{
	_pObj = nullptr;
}

//----------------------------------------------------------------------------
// Gura interfaces for wxURL
//----------------------------------------------------------------------------
Gura_DeclareFunction(URL)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	SetClassToConstruct(Gura_UserClass(wx_URL));
	DeclareArg(env, "url", VTYPE_string, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(URL)
{
	Signal &sig = env.GetSignal();
	if (!CheckWxReady(sig)) return Value::Nil;
	wxString url = wxEmptyString;
	if (arg.IsValid(0)) url = wxString::FromUTF8(arg.GetString(0));
	wx_URL *pEntity = new wx_URL(url);
	Object_wx_URL *pObj = Object_wx_URL::GetObjectThis(arg);
	if (pObj == nullptr) {
		pObj = new Object_wx_URL(pEntity, pEntity, OwnerFalse);
		pEntity->AssocWithGura(pObj);
		return ReturnValue(env, arg, Value(pObj));
	}
	pObj->SetEntity(pEntity, pEntity, OwnerFalse);
	pEntity->AssocWithGura(pObj);
	return ReturnValue(env, arg, arg.GetValueThis());
}

Gura_DeclareMethod(wx_URL, GetProtocol)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_URL, GetProtocol)
{
	Signal &sig = env.GetSignal();
#if 0
	Object_wx_URL *pThis = Object_wx_URL::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxProtocol &rtn = pThis->GetEntity()->GetProtocol();
	return ReturnValue(env, arg, Value(new Object_wx_Protocol(new wxProtocol(rtn), nullptr, OwnerTrue)));
#endif
	SetError_NotImplemented(sig);
	return Value::Nil;
}

Gura_DeclareMethod(wx_URL, GetError)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_URL, GetError)
{
	Signal &sig = env.GetSignal();
	Object_wx_URL *pThis = Object_wx_URL::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxURLError rtn = pThis->GetEntity()->GetError();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_URL, GetInputStream)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_URL, GetInputStream)
{
	Signal &sig = env.GetSignal();
	Object_wx_URL *pThis = Object_wx_URL::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxInputStream *rtn = (wxInputStream *)pThis->GetEntity()->GetInputStream();
	return ReturnValue(env, arg, Value(new Object_wx_InputStream(rtn, nullptr, OwnerFalse)));
}

Gura_DeclareMethod(wx_URL, IsOk)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_URL, IsOk)
{
	Signal &sig = env.GetSignal();
	Object_wx_URL *pThis = Object_wx_URL::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	bool rtn = pThis->GetEntity()->IsOk();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareClassMethod(wx_URL, SetDefaultProxy)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "url_proxy", VTYPE_string, OCCUR_Once);
}

Gura_ImplementClassMethod(wx_URL, SetDefaultProxy)
{
	Signal &sig = env.GetSignal();
	if (!CheckWxReady(sig)) return Value::Nil;
	wxString url_proxy = wxString::FromUTF8(arg.GetString(0));
	wxURL::SetDefaultProxy(url_proxy);
	return Value::Nil;
}

Gura_DeclareMethod(wx_URL, SetProxy)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "url_proxy", VTYPE_string, OCCUR_Once);
}

Gura_ImplementMethod(wx_URL, SetProxy)
{
	Signal &sig = env.GetSignal();
	Object_wx_URL *pThis = Object_wx_URL::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxString url_proxy = wxString::FromUTF8(arg.GetString(0));
	pThis->GetEntity()->SetProxy(url_proxy);
	return Value::Nil;
}

Gura_DeclareMethod(wx_URL, SetURL)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "url", VTYPE_string, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_URL, SetURL)
{
	Signal &sig = env.GetSignal();
	Object_wx_URL *pThis = Object_wx_URL::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxString url = wxString::FromUTF8(arg.GetString(0));
	wxURLError rtn = pThis->GetEntity()->SetURL(url);
	return ReturnValue(env, arg, Value(rtn));
}

//----------------------------------------------------------------------------
// Object implementation for wxURL
//----------------------------------------------------------------------------
Object_wx_URL::~Object_wx_URL()
{
}

Object *Object_wx_URL::Clone() const
{
	return nullptr;
}

String Object_wx_URL::ToString(bool exprFlag)
{
	String rtn("<wx.URL:");
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
// Class implementation for wxURL
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_URL)
{
	Gura_AssignFunction(URL);
	Gura_AssignMethod(wx_URL, GetProtocol);
	Gura_AssignMethod(wx_URL, GetError);
	Gura_AssignMethod(wx_URL, GetInputStream);
	Gura_AssignMethod(wx_URL, IsOk);
	Gura_AssignMethod(wx_URL, SetDefaultProxy);
	Gura_AssignMethod(wx_URL, SetProxy);
	Gura_AssignMethod(wx_URL, SetURL);
}

Gura_ImplementDescendantCreator(wx_URL)
{
	return new Object_wx_URL((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
