//----------------------------------------------------------------------------
// wxHtmlHelpDialog
// extracted from hthlpfrm.tex
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

Gura_DeclarePrivUserSymbol(AddToolbarButtons);

//----------------------------------------------------------------------------
// Class derivation
//----------------------------------------------------------------------------
class wx_HtmlHelpDialog: public wxHtmlHelpDialog, public GuraObjectObserver {
private:
	//Gura::Signal *_pSig;
	Object_wx_HtmlHelpDialog *_pObj;
public:
	//inline wx_HtmlHelpDialog(wxHtmlHelpData* data) : wxHtmlHelpDialog(data), _pObj(nullptr) {}
	//inline wx_HtmlHelpDialog(wxWindow* parent, int wxWindowID, const wxString& title, int style, wxHtmlHelpData* data) : wxHtmlHelpDialog(parent, wxWindowID, title, style, data), _pObj(nullptr) {}
	//virtual void AddToolbarButtons(wxToolBar * toolBar, int style);
	~wx_HtmlHelpDialog();
	inline void AssocWithGura(Object_wx_HtmlHelpDialog *pObj) {
		_pObj = pObj;
	}
	// virtual function of GuraObjectObserver
	virtual void GuraObjectDeleted();
};

wx_HtmlHelpDialog::~wx_HtmlHelpDialog()
{
	if (_pObj != nullptr) _pObj->InvalidateEntity();
}

void wx_HtmlHelpDialog::GuraObjectDeleted()
{
	_pObj = nullptr;
}

//----------------------------------------------------------------------------
// Gura interfaces for wxHtmlHelpDialog
//----------------------------------------------------------------------------
Gura_DeclareFunction(HtmlHelpDialog)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
#if 0
	SetClassToConstruct(Gura_UserClass(wx_HtmlHelpDialog));
	DeclareArg(env, "data", VTYPE_wx_HtmlHelpData, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
#endif
}

Gura_ImplementFunction(HtmlHelpDialog)
{
	Signal &sig = env.GetSignal();
	if (!CheckWxReady(sig)) return Value::Null;
#if 0
	wxHtmlHelpData *data = (wxHtmlHelpData *)(nullptr);
	if (args.IsValid(0)) data = Object_wx_HtmlHelpData::GetObject(args, 0)->GetEntity();
	wx_HtmlHelpDialog *pEntity = new wx_HtmlHelpDialog(data);
	Object_wx_HtmlHelpDialog *pObj = Object_wx_HtmlHelpDialog::GetThisObj(args);
	if (pObj == nullptr) {
		pObj = new Object_wx_HtmlHelpDialog(pEntity, pEntity, OwnerFalse);
		pEntity->AssocWithGura(pObj);
		return ReturnValue(env, args, Value(pObj));
	}
	pObj->SetEntity(pEntity, pEntity, OwnerFalse);
	pEntity->AssocWithGura(pObj);
	return ReturnValue(env, args, args.GetThis());
#endif
	SetError_NotImplemented(sig);
	return Value::Null;
}

Gura_DeclareFunction(HtmlHelpDialog_1)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
#if 0
	SetClassToConstruct(Gura_UserClass(wx_HtmlHelpDialog));
	DeclareArg(env, "parent", VTYPE_wx_Window, OCCUR_Once);
	DeclareArg(env, "wxWindowID", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "title", VTYPE_string, OCCUR_ZeroOrOnce);
	DeclareArg(env, "style", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareArg(env, "data", VTYPE_wx_HtmlHelpData, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
#endif
}

Gura_ImplementFunction(HtmlHelpDialog_1)
{
	Signal &sig = env.GetSignal();
	if (!CheckWxReady(sig)) return Value::Null;
#if 0
	wxWindow *parent = Object_wx_Window::GetObject(args, 0)->GetEntity();
	int wxWindowID = args.GetInt(1);
	wxString title = wxEmptyString;
	if (args.IsValid(2)) title = wxString::FromUTF8(args.GetString(2));
	int style = wxHF_DEFAULT_STYLE;
	if (args.IsValid(3)) style = args.GetInt(3);
	wxHtmlHelpData *data = (wxHtmlHelpData *)(nullptr);
	if (args.IsValid(4)) data = Object_wx_HtmlHelpData::GetObject(args, 4)->GetEntity();
	wx_HtmlHelpDialog *pEntity = new wx_HtmlHelpDialog(parent, wxWindowID, title, style, data);
	Object_wx_HtmlHelpDialog *pObj = Object_wx_HtmlHelpDialog::GetThisObj(args);
	if (pObj == nullptr) {
		pObj = new Object_wx_HtmlHelpDialog(pEntity, pEntity, OwnerFalse);
		pEntity->AssocWithGura(pObj);
		return ReturnValue(env, args, Value(pObj));
	}
	pObj->SetEntity(pEntity, pEntity, OwnerFalse);
	pEntity->AssocWithGura(pObj);
	return ReturnValue(env, args, args.GetThis());
#endif
	SetError_NotImplemented(sig);
	return Value::Null;
}

Gura_DeclareMethod(wx_HtmlHelpDialog, AddToolbarButtons)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
#if 0
	DeclareArg(env, "toolBar", VTYPE_wx_ToolBar, OCCUR_Once);
	DeclareArg(env, "style", VTYPE_number, OCCUR_Once);
#endif
}

Gura_ImplementMethod(wx_HtmlHelpDialog, AddToolbarButtons)
{
	Signal &sig = env.GetSignal();
#if 0
	Object_wx_HtmlHelpDialog *pThis = Object_wx_HtmlHelpDialog::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	wxToolBar *toolBar = Object_wx_ToolBar::GetObject(args, 0)->GetEntity();
	int style = args.GetInt(1);
	pThis->GetEntity()->AddToolbarButtons(toolBar, style);
	return Value::Null;
#endif
	SetError_NotImplemented(sig);
	return Value::Null;
}

Gura_DeclareMethod(wx_HtmlHelpDialog, Create)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
#if 0
	DeclareArg(env, "parent", VTYPE_wx_Window, OCCUR_Once);
	DeclareArg(env, "id", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "title", VTYPE_string, OCCUR_ZeroOrOnce);
	DeclareArg(env, "style", VTYPE_number, OCCUR_ZeroOrOnce);
#endif
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_HtmlHelpDialog, Create)
{
	Signal &sig = env.GetSignal();
#if 0
	Object_wx_HtmlHelpDialog *pThis = Object_wx_HtmlHelpDialog::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	wxWindow *parent = Object_wx_Window::GetObject(args, 0)->GetEntity();
	wxWindowID id = static_cast<wxWindowID>(args.GetInt(1));
	wxString title = wxEmptyString;
	if (args.IsValid(2)) title = wxString::FromUTF8(args.GetString(2));
	int style = wxHF_DEFAULT_STYLE;
	if (args.IsValid(3)) style = args.GetInt(3);
	bool rtn = pThis->GetEntity()->Create(parent, id, title, style);
	return ReturnValue(env, args, Value(rtn));
#endif
	SetError_NotImplemented(sig);
	return Value::Null;
}

Gura_DeclareMethod(wx_HtmlHelpDialog, GetController)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_HtmlHelpDialog, GetController)
{
	Signal &sig = env.GetSignal();
	Object_wx_HtmlHelpDialog *pThis = Object_wx_HtmlHelpDialog::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	wxHtmlHelpController *rtn = (wxHtmlHelpController *)pThis->GetEntity()->GetController();
	return ReturnValue(env, args, Value(new Object_wx_HtmlHelpController(rtn, nullptr, OwnerFalse)));
}

Gura_DeclareMethod(wx_HtmlHelpDialog, ReadCustomization)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
#if 0
	DeclareArg(env, "cfg", VTYPE_wx_ConfigBase, OCCUR_Once);
	DeclareArg(env, "path", VTYPE_string, OCCUR_ZeroOrOnce);
#endif
}

Gura_ImplementMethod(wx_HtmlHelpDialog, ReadCustomization)
{
	Signal &sig = env.GetSignal();
#if 0
	Object_wx_HtmlHelpDialog *pThis = Object_wx_HtmlHelpDialog::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	wxConfigBase *cfg = Object_wx_ConfigBase::GetObject(args, 0)->GetEntity();
	wxString path = wxEmptyString;
	if (args.IsValid(1)) path = wxString::FromUTF8(args.GetString(1));
	pThis->GetEntity()->ReadCustomization(cfg, path);
	return Value::Null;
#endif
	SetError_NotImplemented(sig);
	return Value::Null;
}

Gura_DeclareMethod(wx_HtmlHelpDialog, SetController)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
#if 0
	DeclareArg(env, "contoller", VTYPE_wx_HtmlHelpController, OCCUR_Once);
#endif
}

Gura_ImplementMethod(wx_HtmlHelpDialog, SetController)
{
	Signal &sig = env.GetSignal();
#if 0
	Object_wx_HtmlHelpDialog *pThis = Object_wx_HtmlHelpDialog::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	wxHtmlHelpController *contoller = Object_wx_HtmlHelpController::GetObject(args, 0)->GetEntity();
	pThis->GetEntity()->SetController(contoller);
	return Value::Null;
#endif
	SetError_NotImplemented(sig);
	return Value::Null;
}

Gura_DeclareMethod(wx_HtmlHelpDialog, SetTitleFormat)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
#if 0
	DeclareArg(env, "format", VTYPE_string, OCCUR_Once);
#endif
}

Gura_ImplementMethod(wx_HtmlHelpDialog, SetTitleFormat)
{
	Signal &sig = env.GetSignal();
#if 0
	Object_wx_HtmlHelpDialog *pThis = Object_wx_HtmlHelpDialog::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	wxString format = wxString::FromUTF8(args.GetString(0));
	pThis->GetEntity()->SetTitleFormat(format);
	return Value::Null;
#endif
	SetError_NotImplemented(sig);
	return Value::Null;
}

Gura_DeclareMethod(wx_HtmlHelpDialog, WriteCustomization)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
#if 0
	DeclareArg(env, "cfg", VTYPE_wx_ConfigBase, OCCUR_Once);
	DeclareArg(env, "path", VTYPE_string, OCCUR_ZeroOrOnce);
#endif
}

Gura_ImplementMethod(wx_HtmlHelpDialog, WriteCustomization)
{
	Signal &sig = env.GetSignal();
#if 0
	Object_wx_HtmlHelpDialog *pThis = Object_wx_HtmlHelpDialog::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	wxConfigBase *cfg = Object_wx_ConfigBase::GetObject(args, 0)->GetEntity();
	wxString path = wxEmptyString;
	if (args.IsValid(1)) path = wxString::FromUTF8(args.GetString(1));
	pThis->GetEntity()->WriteCustomization(cfg, path);
	return Value::Null;
#endif
	SetError_NotImplemented(sig);
	return Value::Null;
}

//----------------------------------------------------------------------------
// Object implementation for wxHtmlHelpDialog
//----------------------------------------------------------------------------
Object_wx_HtmlHelpDialog::~Object_wx_HtmlHelpDialog()
{
}

Object *Object_wx_HtmlHelpDialog::Clone() const
{
	return nullptr;
}

String Object_wx_HtmlHelpDialog::ToString(bool exprFlag)
{
	String rtn("<wx.HtmlHelpDialog:");
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
// Class implementation for wxHtmlHelpDialog
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_HtmlHelpDialog)
{
	Gura_RealizeUserSymbol(AddToolbarButtons);
	Gura_AssignFunction(HtmlHelpDialog);
	Gura_AssignFunction(HtmlHelpDialog_1);
	Gura_AssignMethod(wx_HtmlHelpDialog, AddToolbarButtons);
	Gura_AssignMethod(wx_HtmlHelpDialog, Create);
	Gura_AssignMethod(wx_HtmlHelpDialog, GetController);
	Gura_AssignMethod(wx_HtmlHelpDialog, ReadCustomization);
	Gura_AssignMethod(wx_HtmlHelpDialog, SetController);
	Gura_AssignMethod(wx_HtmlHelpDialog, SetTitleFormat);
	Gura_AssignMethod(wx_HtmlHelpDialog, WriteCustomization);
}

Gura_ImplementDescendantCreator(wx_HtmlHelpDialog)
{
	return new Object_wx_HtmlHelpDialog((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
