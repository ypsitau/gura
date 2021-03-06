//----------------------------------------------------------------------------
// wxHtmlHelpController
// extracted from hthelpct.tex
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

Gura_DeclarePrivUserSymbol(CreateHelpDialog);
Gura_DeclarePrivUserSymbol(CreateHelpFrame);

//----------------------------------------------------------------------------
// Class derivation
//----------------------------------------------------------------------------
class wx_HtmlHelpController: public wxHtmlHelpController, public GuraObjectObserver {
private:
	//Gura::Signal *_pSig;
	Object_wx_HtmlHelpController *_pObj;
public:
	inline wx_HtmlHelpController(int style, wxWindow* parentWindow) : wxHtmlHelpController(style, parentWindow), _pObj(nullptr) {}
	//virtual wxHtmlHelpDialog* CreateHelpDialog(wxHtmlHelpData * data);
	//virtual wxHtmlHelpFrame* CreateHelpFrame(wxHtmlHelpData * data);
	~wx_HtmlHelpController();
	inline void AssocWithGura(Object_wx_HtmlHelpController *pObj) {
		_pObj = pObj;
	}
	// virtual function of GuraObjectObserver
	virtual void GuraObjectDeleted();
};

wx_HtmlHelpController::~wx_HtmlHelpController()
{
	if (_pObj != nullptr) _pObj->InvalidateEntity();
}

void wx_HtmlHelpController::GuraObjectDeleted()
{
	_pObj = nullptr;
}

//----------------------------------------------------------------------------
// Gura interfaces for wxHtmlHelpController
//----------------------------------------------------------------------------
Gura_DeclareFunction(HtmlHelpController)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	SetClassToConstruct(Gura_UserClass(wx_HtmlHelpController));
	DeclareArg(env, "style", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareArg(env, "parentWindow", VTYPE_wx_Window, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(HtmlHelpController)
{
	Signal &sig = env.GetSignal();
	if (!CheckWxReady(sig)) return Value::Nil;
	int style = wxHF_DEFAULT_STYLE;
	if (arg.IsValid(0)) style = arg.GetInt(0);
	wxWindow *parentWindow = (wxWindow *)(nullptr);
	if (arg.IsValid(1)) parentWindow = Object_wx_Window::GetObject(arg, 1)->GetEntity();
	wx_HtmlHelpController *pEntity = new wx_HtmlHelpController(style, parentWindow);
	Object_wx_HtmlHelpController *pObj = Object_wx_HtmlHelpController::GetObjectThis(arg);
	if (pObj == nullptr) {
		pObj = new Object_wx_HtmlHelpController(pEntity, pEntity, OwnerFalse);
		pEntity->AssocWithGura(pObj);
		return ReturnValue(env, arg, Value(pObj));
	}
	pObj->SetEntity(pEntity, pEntity, OwnerFalse);
	pEntity->AssocWithGura(pObj);
	return ReturnValue(env, arg, arg.GetValueThis());
}

Gura_DeclareMethod(wx_HtmlHelpController, AddBook)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "bookFile", VTYPE_wx_FileName, OCCUR_Once);
	DeclareArg(env, "showWaitMsg", VTYPE_boolean, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_HtmlHelpController, AddBook)
{
	Signal &sig = env.GetSignal();
	Object_wx_HtmlHelpController *pThis = Object_wx_HtmlHelpController::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxFileName *bookFile = Object_wx_FileName::GetObject(arg, 0)->GetEntity();
	bool showWaitMsg = arg.GetBoolean(1);
	bool rtn = pThis->GetEntity()->AddBook(*bookFile, showWaitMsg);
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_HtmlHelpController, AddBook_1)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "bookUrl", VTYPE_string, OCCUR_Once);
	DeclareArg(env, "showWaitMsg", VTYPE_boolean, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_HtmlHelpController, AddBook_1)
{
	Signal &sig = env.GetSignal();
	Object_wx_HtmlHelpController *pThis = Object_wx_HtmlHelpController::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxString bookUrl = wxString::FromUTF8(arg.GetString(0));
	bool showWaitMsg = arg.GetBoolean(1);
	bool rtn = pThis->GetEntity()->AddBook(bookUrl, showWaitMsg);
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_HtmlHelpController, CreateHelpDialog)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
#if 0
	DeclareArg(env, "data", VTYPE_wx_HtmlHelpData, OCCUR_Once);
#endif
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_HtmlHelpController, CreateHelpDialog)
{
	Signal &sig = env.GetSignal();
#if 0
	Object_wx_HtmlHelpController *pThis = Object_wx_HtmlHelpController::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxHtmlHelpData *data = Object_wx_HtmlHelpData::GetObject(arg, 0)->GetEntity();
	wxHtmlHelpDialog *rtn = (wxHtmlHelpDialog *)pThis->GetEntity()->CreateHelpDialog(data);
	return ReturnValue(env, arg, Value(new Object_wx_HtmlHelpDialog(rtn, nullptr, OwnerFalse)));
#endif
	SetError_NotImplemented(sig);
	return Value::Nil;
}

Gura_DeclareMethod(wx_HtmlHelpController, CreateHelpFrame)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
#if 0
	DeclareArg(env, "data", VTYPE_wx_HtmlHelpData, OCCUR_Once);
#endif
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_HtmlHelpController, CreateHelpFrame)
{
	Signal &sig = env.GetSignal();
#if 0
	Object_wx_HtmlHelpController *pThis = Object_wx_HtmlHelpController::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxHtmlHelpData *data = Object_wx_HtmlHelpData::GetObject(arg, 0)->GetEntity();
	wxHtmlHelpFrame *rtn = (wxHtmlHelpFrame *)pThis->GetEntity()->CreateHelpFrame(data);
	return ReturnValue(env, arg, Value(new Object_wx_HtmlHelpFrame(rtn, nullptr, OwnerFalse)));
#endif
	SetError_NotImplemented(sig);
	return Value::Nil;
}

Gura_DeclareMethod(wx_HtmlHelpController, Display)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "x", VTYPE_string, OCCUR_Once);
}

Gura_ImplementMethod(wx_HtmlHelpController, Display)
{
	Signal &sig = env.GetSignal();
	Object_wx_HtmlHelpController *pThis = Object_wx_HtmlHelpController::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxString x = wxString::FromUTF8(arg.GetString(0));
	pThis->GetEntity()->Display(x);
	return Value::Nil;
}

Gura_DeclareMethod(wx_HtmlHelpController, Display_1)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "id", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_HtmlHelpController, Display_1)
{
	Signal &sig = env.GetSignal();
	Object_wx_HtmlHelpController *pThis = Object_wx_HtmlHelpController::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	int id = arg.GetInt(0);
	pThis->GetEntity()->Display(id);
	return Value::Nil;
}

Gura_DeclareMethod(wx_HtmlHelpController, DisplayContents)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_HtmlHelpController, DisplayContents)
{
	Signal &sig = env.GetSignal();
	Object_wx_HtmlHelpController *pThis = Object_wx_HtmlHelpController::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	pThis->GetEntity()->DisplayContents();
	return Value::Nil;
}

Gura_DeclareMethod(wx_HtmlHelpController, DisplayIndex)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_HtmlHelpController, DisplayIndex)
{
	Signal &sig = env.GetSignal();
	Object_wx_HtmlHelpController *pThis = Object_wx_HtmlHelpController::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	pThis->GetEntity()->DisplayIndex();
	return Value::Nil;
}

Gura_DeclareMethod(wx_HtmlHelpController, KeywordSearch)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "keyword", VTYPE_string, OCCUR_Once);
	DeclareArg(env, "mode", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_HtmlHelpController, KeywordSearch)
{
	Signal &sig = env.GetSignal();
	Object_wx_HtmlHelpController *pThis = Object_wx_HtmlHelpController::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxString keyword = wxString::FromUTF8(arg.GetString(0));
	wxHelpSearchMode mode = wxHELP_SEARCH_ALL;
	if (arg.IsValid(1)) mode = static_cast<wxHelpSearchMode>(arg.GetInt(1));
	bool rtn = pThis->GetEntity()->KeywordSearch(keyword, mode);
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_HtmlHelpController, ReadCustomization)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "cfg", VTYPE_wx_ConfigBase, OCCUR_Once);
	DeclareArg(env, "path", VTYPE_string, OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_HtmlHelpController, ReadCustomization)
{
	Signal &sig = env.GetSignal();
	Object_wx_HtmlHelpController *pThis = Object_wx_HtmlHelpController::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxConfigBase *cfg = Object_wx_ConfigBase::GetObject(arg, 0)->GetEntity();
	wxString path = wxEmptyString;
	if (arg.IsValid(1)) path = wxString::FromUTF8(arg.GetString(1));
	pThis->GetEntity()->ReadCustomization(cfg, path);
	return Value::Nil;
}

Gura_DeclareMethod(wx_HtmlHelpController, SetTempDir)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "path", VTYPE_string, OCCUR_Once);
}

Gura_ImplementMethod(wx_HtmlHelpController, SetTempDir)
{
	Signal &sig = env.GetSignal();
	Object_wx_HtmlHelpController *pThis = Object_wx_HtmlHelpController::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxString path = wxString::FromUTF8(arg.GetString(0));
	pThis->GetEntity()->SetTempDir(path);
	return Value::Nil;
}

Gura_DeclareMethod(wx_HtmlHelpController, SetTitleFormat)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "format", VTYPE_string, OCCUR_Once);
}

Gura_ImplementMethod(wx_HtmlHelpController, SetTitleFormat)
{
	Signal &sig = env.GetSignal();
	Object_wx_HtmlHelpController *pThis = Object_wx_HtmlHelpController::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxString format = wxString::FromUTF8(arg.GetString(0));
	pThis->GetEntity()->SetTitleFormat(format);
	return Value::Nil;
}

Gura_DeclareMethod(wx_HtmlHelpController, UseConfig)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "config", VTYPE_wx_ConfigBase, OCCUR_Once);
	DeclareArg(env, "rootpath", VTYPE_string, OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_HtmlHelpController, UseConfig)
{
	Signal &sig = env.GetSignal();
	Object_wx_HtmlHelpController *pThis = Object_wx_HtmlHelpController::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxConfigBase *config = Object_wx_ConfigBase::GetObject(arg, 0)->GetEntity();
	wxString rootpath = wxEmptyString;
	if (arg.IsValid(1)) rootpath = wxString::FromUTF8(arg.GetString(1));
	pThis->GetEntity()->UseConfig(config, rootpath);
	return Value::Nil;
}

Gura_DeclareMethod(wx_HtmlHelpController, WriteCustomization)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "cfg", VTYPE_wx_ConfigBase, OCCUR_Once);
	DeclareArg(env, "path", VTYPE_string, OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_HtmlHelpController, WriteCustomization)
{
	Signal &sig = env.GetSignal();
	Object_wx_HtmlHelpController *pThis = Object_wx_HtmlHelpController::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxConfigBase *cfg = Object_wx_ConfigBase::GetObject(arg, 0)->GetEntity();
	wxString path = wxEmptyString;
	if (arg.IsValid(1)) path = wxString::FromUTF8(arg.GetString(1));
	pThis->GetEntity()->WriteCustomization(cfg, path);
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Object implementation for wxHtmlHelpController
//----------------------------------------------------------------------------
Object_wx_HtmlHelpController::~Object_wx_HtmlHelpController()
{
}

Object *Object_wx_HtmlHelpController::Clone() const
{
	return nullptr;
}

String Object_wx_HtmlHelpController::ToString(bool exprFlag)
{
	String rtn("<wx.HtmlHelpController:");
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
// Class implementation for wxHtmlHelpController
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_HtmlHelpController)
{
	Gura_RealizeUserSymbol(CreateHelpDialog);
	Gura_RealizeUserSymbol(CreateHelpFrame);
	Gura_AssignFunction(HtmlHelpController);
	Gura_AssignMethod(wx_HtmlHelpController, AddBook);
	Gura_AssignMethod(wx_HtmlHelpController, AddBook_1);
	Gura_AssignMethod(wx_HtmlHelpController, CreateHelpDialog);
	Gura_AssignMethod(wx_HtmlHelpController, CreateHelpFrame);
	Gura_AssignMethod(wx_HtmlHelpController, Display);
	Gura_AssignMethod(wx_HtmlHelpController, Display_1);
	Gura_AssignMethod(wx_HtmlHelpController, DisplayContents);
	Gura_AssignMethod(wx_HtmlHelpController, DisplayIndex);
	Gura_AssignMethod(wx_HtmlHelpController, KeywordSearch);
	Gura_AssignMethod(wx_HtmlHelpController, ReadCustomization);
	Gura_AssignMethod(wx_HtmlHelpController, SetTempDir);
	Gura_AssignMethod(wx_HtmlHelpController, SetTitleFormat);
	Gura_AssignMethod(wx_HtmlHelpController, UseConfig);
	Gura_AssignMethod(wx_HtmlHelpController, WriteCustomization);
}

Gura_ImplementDescendantCreator(wx_HtmlHelpController)
{
	return new Object_wx_HtmlHelpController((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
