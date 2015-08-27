//----------------------------------------------------------------------------
// wxLocale
// extracted from locale.tex
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Class derivation
//----------------------------------------------------------------------------
class wx_Locale: public wxLocale, public GuraObjectObserver {
private:
	//Gura::Signal *_pSig;
	Object_wx_Locale *_pObj;
public:
	inline wx_Locale() : wxLocale(), _pObj(nullptr) {}
	inline wx_Locale(int language, int flags) : wxLocale(language, flags), _pObj(nullptr) {}
	//inline wx_Locale(const char *szName, const char *szShort, const char *szLocale, bool bLoadDefault, bool bConvertEncoding) : wxLocale(*szName, *szShort, *szLocale, bLoadDefault, bConvertEncoding), _pObj(nullptr) {}
	~wx_Locale();
	inline void AssocWithGura(Object_wx_Locale *pObj) {
		_pObj = pObj;
	}
	// virtual function of GuraObjectObserver
	virtual void GuraObjectDeleted();
};

wx_Locale::~wx_Locale()
{
	if (_pObj != nullptr) _pObj->InvalidateEntity();
}

void wx_Locale::GuraObjectDeleted()
{
	_pObj = nullptr;
}

//----------------------------------------------------------------------------
// Gura interfaces for wxLocale
//----------------------------------------------------------------------------
Gura_DeclareFunction(Locale)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	SetClassToConstruct(Gura_UserClass(wx_Locale));
	DeclareArg(env, "language", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareArg(env, "flags", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(Locale)
{
	Signal &sig = env.GetSignal();
	if (!CheckWxReady(sig)) return Value::Nil;
	wx_Locale *pEntity = nullptr;
	if (args.IsValid(0)) {
		int language = args.GetInt(0);
		int flags = wxLOCALE_LOAD_DEFAULT | wxLOCALE_CONV_ENCODING;
		if (args.IsValid(1)) flags = args.GetInt(1);
		pEntity = new wx_Locale(language, flags);
	} else {
		pEntity = new wx_Locale();
	}
	Object_wx_Locale *pObj = Object_wx_Locale::GetObjectThis(args);
	if (pObj == nullptr) {
		pObj = new Object_wx_Locale(pEntity, pEntity, OwnerFalse);
		pEntity->AssocWithGura(pObj);
		return ReturnValue(env, args, Value(pObj));
	}
	pObj->SetEntity(pEntity, pEntity, OwnerFalse);
	pEntity->AssocWithGura(pObj);
	return ReturnValue(env, args, args.GetValueThis());
}

#if 0
Gura_DeclareFunction(Locale_1)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
#if 0
	SetClassToConstruct(Gura_UserClass(wx_Locale));
	DeclareArg(env, "*szName", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "*szShort", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareArg(env, "*szLocale", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareArg(env, "bLoadDefault", VTYPE_boolean, OCCUR_ZeroOrOnce);
	DeclareArg(env, "bConvertEncoding", VTYPE_boolean, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
#endif
}

Gura_ImplementFunction(Locale_1)
{
	Signal &sig = env.GetSignal();
	if (!CheckWxReady(sig)) return Value::Nil;
#if 0
	char *szName = args.GetChar(0);
	char *szShort = nullptr;
	if (args.IsValid(1)) *szShort = args.GetChar(1);
	char *szLocale = nullptr;
	if (args.IsValid(2)) *szLocale = args.GetChar(2);
	bool bLoadDefault = true;
	if (args.IsValid(3)) bLoadDefault = args.GetBoolean(3);
	bool bConvertEncoding = false;
	if (args.IsValid(4)) bConvertEncoding = args.GetBoolean(4);
	wx_Locale *pEntity = new wx_Locale(*szName, *szShort, *szLocale, bLoadDefault, bConvertEncoding);
	Object_wx_Locale *pObj = Object_wx_Locale::GetObjectThis(args);
	if (pObj == nullptr) {
		pObj = new Object_wx_Locale(pEntity, pEntity, OwnerFalse);
		pEntity->AssocWithGura(pObj);
		return ReturnValue(env, args, Value(pObj));
	}
	pObj->SetEntity(pEntity, pEntity, OwnerFalse);
	pEntity->AssocWithGura(pObj);
	return ReturnValue(env, args, args.GetValueThis());
#endif
	SetError_NotImplemented(sig);
	return Value::Nil;
}
#endif

Gura_DeclareMethod(wx_Locale, AddCatalog)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "szDomain", VTYPE_string, OCCUR_Once);
	DeclareArg(env, "msgIdLanguage", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareArg(env, "msgIdCharset", VTYPE_string, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_Locale, AddCatalog)
{
	Signal &sig = env.GetSignal();
#if defined(__WXMSW__)
	Object_wx_Locale *pThis = Object_wx_Locale::GetObjectThis(args);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	bool rtn = false;
	if (args.IsValid(1) && args.IsValid(2)) {
		const char *szDomain = args.GetString(0);
		wxLanguage msgIdLanguage = static_cast<wxLanguage>(args.GetInt(1));
		const char *msgIdCharset = args.GetString(2);
		rtn = pThis->GetEntity()->AddCatalog(szDomain, msgIdLanguage, msgIdCharset);
	} else {
		const char *szDomain = args.GetString(0);
		rtn = pThis->GetEntity()->AddCatalog(szDomain);
	}
	return ReturnValue(env, args, Value(rtn));
#else
	SetError_MSWOnly(sig);
	return Value::Nil;
#endif	
}

Gura_DeclareClassMethod(wx_Locale, AddCatalogLookupPathPrefix)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "prefix", VTYPE_string, OCCUR_Once);
}

Gura_ImplementClassMethod(wx_Locale, AddCatalogLookupPathPrefix)
{
	Signal &sig = env.GetSignal();
	if (!CheckWxReady(sig)) return Value::Nil;
	wxString prefix = wxString::FromUTF8(args.GetString(0));
	wxLocale::AddCatalogLookupPathPrefix(prefix);
	return Value::Nil;
}

Gura_DeclareClassMethod(wx_Locale, AddLanguage)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "info", VTYPE_wx_LanguageInfo, OCCUR_Once);
}

Gura_ImplementClassMethod(wx_Locale, AddLanguage)
{
	Signal &sig = env.GetSignal();
	if (!CheckWxReady(sig)) return Value::Nil;
	wxLanguageInfo *info = Object_wx_LanguageInfo::GetObject(args, 0)->GetEntity();
	wxLocale::AddLanguage(*info);
	return Value::Nil;
}

Gura_DeclareClassMethod(wx_Locale, FindLanguageInfo)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "locale", VTYPE_string, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementClassMethod(wx_Locale, FindLanguageInfo)
{
	Signal &sig = env.GetSignal();
	if (!CheckWxReady(sig)) return Value::Nil;
	wxString locale = wxString::FromUTF8(args.GetString(0));
	wxLanguageInfo *rtn = (wxLanguageInfo *)wxLocale::FindLanguageInfo(locale);
	Value value;
	if (rtn != nullptr) {
		value = Value(new Object_wx_LanguageInfo(rtn, nullptr, OwnerFalse));
	}
	return ReturnValue(env, args, value);
}

Gura_DeclareMethod(wx_Locale, GetCanonicalName)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_Locale, GetCanonicalName)
{
	Signal &sig = env.GetSignal();
	Object_wx_Locale *pThis = Object_wx_Locale::GetObjectThis(args);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxString rtn = pThis->GetEntity()->GetCanonicalName();
	return ReturnValue(env, args, Value(static_cast<const char *>(rtn.ToUTF8())));
}

Gura_DeclareMethod(wx_Locale, GetLanguage)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_Locale, GetLanguage)
{
	Signal &sig = env.GetSignal();
	Object_wx_Locale *pThis = Object_wx_Locale::GetObjectThis(args);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	int rtn = pThis->GetEntity()->GetLanguage();
	return ReturnValue(env, args, Value(rtn));
}

Gura_DeclareClassMethod(wx_Locale, GetLanguageInfo)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "lang", VTYPE_number, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementClassMethod(wx_Locale, GetLanguageInfo)
{
	Signal &sig = env.GetSignal();
	if (!CheckWxReady(sig)) return Value::Nil;
	int lang = args.GetInt(0);
	wxLanguageInfo *rtn = (wxLanguageInfo *)wxLocale::GetLanguageInfo(lang);
	Value value;
	if (rtn != nullptr) {
		value = Value(new Object_wx_LanguageInfo(rtn, nullptr, OwnerFalse));
	}
	return ReturnValue(env, args, value);
}

Gura_DeclareClassMethod(wx_Locale, GetLanguageName)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "lang", VTYPE_number, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementClassMethod(wx_Locale, GetLanguageName)
{
	Signal &sig = env.GetSignal();
	if (!CheckWxReady(sig)) return Value::Nil;
	int lang = args.GetInt(0);
	wxString rtn = wxLocale::GetLanguageName(lang);
	return ReturnValue(env, args, Value(static_cast<const char *>(rtn.ToUTF8())));
}

Gura_DeclareMethod(wx_Locale, GetLocale)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_Locale, GetLocale)
{
	Signal &sig = env.GetSignal();
	Object_wx_Locale *pThis = Object_wx_Locale::GetObjectThis(args);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxString rtn = wxString(pThis->GetEntity()->GetLocale());
	return ReturnValue(env, args, Value(rtn.ToUTF8()));
}

Gura_DeclareMethod(wx_Locale, GetName)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_Locale, GetName)
{
	Signal &sig = env.GetSignal();
	Object_wx_Locale *pThis = Object_wx_Locale::GetObjectThis(args);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxString rtn = pThis->GetEntity()->GetName();
	return ReturnValue(env, args, Value(static_cast<const char *>(rtn.ToUTF8())));
}

Gura_DeclareMethod(wx_Locale, GetString)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
#if 0
	DeclareArg(env, "*szOrigString", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "*szDomain", VTYPE_number, OCCUR_ZeroOrOnce);
#endif
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_Locale, GetString)
{
	Signal &sig = env.GetSignal();
#if 0
	Object_wx_Locale *pThis = Object_wx_Locale::GetObjectThis(args);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	char *szOrigString = args.GetChar(0);
	char *szDomain = nullptr;
	if (args.IsValid(1)) *szDomain = args.GetChar(1);
	char rtn = pThis->GetEntity()->GetString(*szOrigString, *szDomain);
	return ReturnValue(env, args, Value(rtn));
#endif
	SetError_NotImplemented(sig);
	return Value::Nil;
}

Gura_DeclareMethod(wx_Locale, GetString_1)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
#if 0
	DeclareArg(env, "*szOrigString", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "*szOrigString2", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "n", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "*szDomain", VTYPE_number, OCCUR_ZeroOrOnce);
#endif
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_Locale, GetString_1)
{
	Signal &sig = env.GetSignal();
#if 0
	Object_wx_Locale *pThis = Object_wx_Locale::GetObjectThis(args);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	char *szOrigString = args.GetChar(0);
	char *szOrigString2 = args.GetChar(1);
	size_t n = args.GetSizeT(2);
	char *szDomain = nullptr;
	if (args.IsValid(3)) *szDomain = args.GetChar(3);
	char rtn = pThis->GetEntity()->GetString(*szOrigString, *szOrigString2, n, *szDomain);
	return ReturnValue(env, args, Value(rtn));
#endif
	SetError_NotImplemented(sig);
	return Value::Nil;
}

Gura_DeclareMethod(wx_Locale, GetHeaderValue)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "szHeader", VTYPE_string, OCCUR_Once);
	DeclareArg(env, "szDomain", VTYPE_string, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_Locale, GetHeaderValue)
{
	Signal &sig = env.GetSignal();
#if defined(__WXMSW__)
	Object_wx_Locale *pThis = Object_wx_Locale::GetObjectThis(args);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	const char *szHeader = args.GetString(0);
	const char *szDomain = nullptr;
	if (args.IsValid(1)) szDomain = args.GetString(1);
	wxString rtn = pThis->GetEntity()->GetHeaderValue(szHeader, szDomain);
	return ReturnValue(env, args, Value(static_cast<const char *>(rtn.ToUTF8())));
#else
	SetError_MSWOnly(sig);
	return Value::Nil;
#endif	
}

Gura_DeclareMethod(wx_Locale, GetSysName)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_Locale, GetSysName)
{
	Signal &sig = env.GetSignal();
	Object_wx_Locale *pThis = Object_wx_Locale::GetObjectThis(args);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxString rtn = pThis->GetEntity()->GetSysName();
	return ReturnValue(env, args, Value(static_cast<const char *>(rtn.ToUTF8())));
}

Gura_DeclareClassMethod(wx_Locale, GetSystemEncoding)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementClassMethod(wx_Locale, GetSystemEncoding)
{
	Signal &sig = env.GetSignal();
	if (!CheckWxReady(sig)) return Value::Nil;
	wxFontEncoding rtn = wxLocale::GetSystemEncoding();
	return ReturnValue(env, args, Value(rtn));
}

Gura_DeclareClassMethod(wx_Locale, GetSystemEncodingName)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementClassMethod(wx_Locale, GetSystemEncodingName)
{
	Signal &sig = env.GetSignal();
	if (!CheckWxReady(sig)) return Value::Nil;
	wxString rtn = wxLocale::GetSystemEncodingName();
	return ReturnValue(env, args, Value(static_cast<const char *>(rtn.ToUTF8())));
}

Gura_DeclareClassMethod(wx_Locale, GetSystemLanguage)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementClassMethod(wx_Locale, GetSystemLanguage)
{
	Signal &sig = env.GetSignal();
	if (!CheckWxReady(sig)) return Value::Nil;
	int rtn = wxLocale::GetSystemLanguage();
	return ReturnValue(env, args, Value(rtn));
}

Gura_DeclareMethod(wx_Locale, Init)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "language", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareArg(env, "flags", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_Locale, Init)
{
	Signal &sig = env.GetSignal();
	Object_wx_Locale *pThis = Object_wx_Locale::GetObjectThis(args);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	int language = wxLANGUAGE_DEFAULT;
	if (args.IsValid(0)) language = args.GetInt(0);
	int flags = wxLOCALE_LOAD_DEFAULT | wxLOCALE_CONV_ENCODING;
	if (args.IsValid(1)) flags = args.GetInt(1);
	bool rtn = pThis->GetEntity()->Init(language, flags);
	return ReturnValue(env, args, Value(rtn));
}

Gura_DeclareMethod(wx_Locale, Init_1)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
#if 0
	DeclareArg(env, "*szName", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "*szShort", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareArg(env, "*szLocale", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareArg(env, "bLoadDefault", VTYPE_boolean, OCCUR_ZeroOrOnce);
	DeclareArg(env, "bConvertEncoding", VTYPE_boolean, OCCUR_ZeroOrOnce);
#endif
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_Locale, Init_1)
{
	Signal &sig = env.GetSignal();
#if 0
	Object_wx_Locale *pThis = Object_wx_Locale::GetObjectThis(args);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	char *szName = args.GetChar(0);
	char *szShort = nullptr;
	if (args.IsValid(1)) *szShort = args.GetChar(1);
	char *szLocale = nullptr;
	if (args.IsValid(2)) *szLocale = args.GetChar(2);
	bool bLoadDefault = true;
	if (args.IsValid(3)) bLoadDefault = args.GetBoolean(3);
	bool bConvertEncoding = false;
	if (args.IsValid(4)) bConvertEncoding = args.GetBoolean(4);
	bool rtn = pThis->GetEntity()->Init(*szName, *szShort, *szLocale, bLoadDefault, bConvertEncoding);
	return ReturnValue(env, args, Value(rtn));
#endif
	SetError_NotImplemented(sig);
	return Value::Nil;
}

Gura_DeclareClassMethod(wx_Locale, IsAvailable)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "lang", VTYPE_number, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementClassMethod(wx_Locale, IsAvailable)
{
	Signal &sig = env.GetSignal();
	if (!CheckWxReady(sig)) return Value::Nil;
	int lang = args.GetInt(0);
	bool rtn = wxLocale::IsAvailable(lang);
	return ReturnValue(env, args, Value(rtn));
}

Gura_DeclareMethod(wx_Locale, IsLoaded)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "domain", VTYPE_string, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_Locale, IsLoaded)
{
	Signal &sig = env.GetSignal();
#if defined(__WXMSW__)
	Object_wx_Locale *pThis = Object_wx_Locale::GetObjectThis(args);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	const char *domain = args.GetString(0);
	bool rtn = pThis->GetEntity()->IsLoaded(domain);
	return ReturnValue(env, args, Value(rtn));
#else
	SetError_MSWOnly(sig);
	return Value::Nil;
#endif	
}

Gura_DeclareMethod(wx_Locale, IsOk)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_Locale, IsOk)
{
	Signal &sig = env.GetSignal();
	Object_wx_Locale *pThis = Object_wx_Locale::GetObjectThis(args);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	bool rtn = pThis->GetEntity()->IsOk();
	return ReturnValue(env, args, Value(rtn));
}

//----------------------------------------------------------------------------
// Object implementation for wxLocale
//----------------------------------------------------------------------------
Object_wx_Locale::~Object_wx_Locale()
{
	if (_pEntity != nullptr) NotifyGuraObjectDeleted();
	if (_ownerFlag) delete _pEntity;
	_pEntity = nullptr;
}

Object *Object_wx_Locale::Clone() const
{
	return nullptr;
}

String Object_wx_Locale::ToString(bool exprFlag)
{
	String rtn("<wx.Locale:");
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
// Class implementation for wxLocale
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_Locale)
{
	Gura_AssignFunction(Locale);
	//Gura_AssignFunction(Locale_1);
	Gura_AssignMethod(wx_Locale, AddCatalog);
	Gura_AssignMethod(wx_Locale, AddCatalogLookupPathPrefix);
	Gura_AssignMethod(wx_Locale, AddLanguage);
	Gura_AssignMethod(wx_Locale, FindLanguageInfo);
	Gura_AssignMethod(wx_Locale, GetCanonicalName);
	Gura_AssignMethod(wx_Locale, GetLanguage);
	Gura_AssignMethod(wx_Locale, GetLanguageInfo);
	Gura_AssignMethod(wx_Locale, GetLanguageName);
	Gura_AssignMethod(wx_Locale, GetLocale);
	Gura_AssignMethod(wx_Locale, GetName);
	Gura_AssignMethod(wx_Locale, GetString);
	Gura_AssignMethod(wx_Locale, GetString_1);
	Gura_AssignMethod(wx_Locale, GetHeaderValue);
	Gura_AssignMethod(wx_Locale, GetSysName);
	Gura_AssignMethod(wx_Locale, GetSystemEncoding);
	Gura_AssignMethod(wx_Locale, GetSystemEncodingName);
	Gura_AssignMethod(wx_Locale, GetSystemLanguage);
	Gura_AssignMethod(wx_Locale, Init);
	Gura_AssignMethod(wx_Locale, Init_1);
	Gura_AssignMethod(wx_Locale, IsAvailable);
	Gura_AssignMethod(wx_Locale, IsLoaded);
	Gura_AssignMethod(wx_Locale, IsOk);
}

Gura_ImplementDescendantCreator(wx_Locale)
{
	return new Object_wx_Locale((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
