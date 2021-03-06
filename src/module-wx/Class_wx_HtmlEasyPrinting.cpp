//----------------------------------------------------------------------------
// wxHtmlEasyPrinting
// extracted from hteasypr.tex
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Class derivation
//----------------------------------------------------------------------------
class wx_HtmlEasyPrinting: public wxHtmlEasyPrinting, public GuraObjectObserver {
private:
	//Gura::Signal *_pSig;
	Object_wx_HtmlEasyPrinting *_pObj;
public:
	inline wx_HtmlEasyPrinting(const wxString& name, wxWindow* parentWindow) : wxHtmlEasyPrinting(name, parentWindow), _pObj(nullptr) {}
	~wx_HtmlEasyPrinting();
	inline void AssocWithGura(Object_wx_HtmlEasyPrinting *pObj) {
		_pObj = pObj;
	}
	// virtual function of GuraObjectObserver
	virtual void GuraObjectDeleted();
};

wx_HtmlEasyPrinting::~wx_HtmlEasyPrinting()
{
	if (_pObj != nullptr) _pObj->InvalidateEntity();
}

void wx_HtmlEasyPrinting::GuraObjectDeleted()
{
	_pObj = nullptr;
}

//----------------------------------------------------------------------------
// Gura interfaces for wxHtmlEasyPrinting
//----------------------------------------------------------------------------
Gura_DeclareFunction(HtmlEasyPrinting)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	SetClassToConstruct(Gura_UserClass(wx_HtmlEasyPrinting));
	DeclareArg(env, "name", VTYPE_string, OCCUR_ZeroOrOnce);
	DeclareArg(env, "parentWindow", VTYPE_wx_Window, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(HtmlEasyPrinting)
{
	Signal &sig = env.GetSignal();
	if (!CheckWxReady(sig)) return Value::Nil;
	wxString name = wxT("Printing");
	if (arg.IsValid(0)) name = wxString::FromUTF8(arg.GetString(0));
	wxWindow *parentWindow = (wxWindow *)(nullptr);
	if (arg.IsValid(1)) parentWindow = Object_wx_Window::GetObject(arg, 1)->GetEntity();
	wx_HtmlEasyPrinting *pEntity = new wx_HtmlEasyPrinting(name, parentWindow);
	Object_wx_HtmlEasyPrinting *pObj = Object_wx_HtmlEasyPrinting::GetObjectThis(arg);
	if (pObj == nullptr) {
		pObj = new Object_wx_HtmlEasyPrinting(pEntity, pEntity, OwnerFalse);
		pEntity->AssocWithGura(pObj);
		return ReturnValue(env, arg, Value(pObj));
	}
	pObj->SetEntity(pEntity, pEntity, OwnerFalse);
	pEntity->AssocWithGura(pObj);
	return ReturnValue(env, arg, arg.GetValueThis());
}

Gura_DeclareMethod(wx_HtmlEasyPrinting, GetParentWindow)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_HtmlEasyPrinting, GetParentWindow)
{
	Signal &sig = env.GetSignal();
	Object_wx_HtmlEasyPrinting *pThis = Object_wx_HtmlEasyPrinting::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxWindow *rtn = (wxWindow *)pThis->GetEntity()->GetParentWindow();
	return ReturnValue(env, arg, Value(new Object_wx_Window(rtn, nullptr, OwnerFalse)));
}

Gura_DeclareMethod(wx_HtmlEasyPrinting, GetPrintData)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_HtmlEasyPrinting, GetPrintData)
{
	Signal &sig = env.GetSignal();
	Object_wx_HtmlEasyPrinting *pThis = Object_wx_HtmlEasyPrinting::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxPrintData *rtn = (wxPrintData *)pThis->GetEntity()->GetPrintData();
	return ReturnValue(env, arg, Value(new Object_wx_PrintData(rtn, nullptr, OwnerFalse)));
}

Gura_DeclareMethod(wx_HtmlEasyPrinting, GetPageSetupData)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_HtmlEasyPrinting, GetPageSetupData)
{
	Signal &sig = env.GetSignal();
	Object_wx_HtmlEasyPrinting *pThis = Object_wx_HtmlEasyPrinting::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxPageSetupDialogData *rtn = (wxPageSetupDialogData *)pThis->GetEntity()->GetPageSetupData();
	return ReturnValue(env, arg, Value(new Object_wx_PageSetupDialogData(rtn, nullptr, OwnerFalse)));
}

Gura_DeclareMethod(wx_HtmlEasyPrinting, PreviewFile)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "htmlfile", VTYPE_string, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_HtmlEasyPrinting, PreviewFile)
{
	Signal &sig = env.GetSignal();
	Object_wx_HtmlEasyPrinting *pThis = Object_wx_HtmlEasyPrinting::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxString htmlfile = wxString::FromUTF8(arg.GetString(0));
	bool rtn = pThis->GetEntity()->PreviewFile(htmlfile);
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_HtmlEasyPrinting, PreviewText)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "htmltext", VTYPE_string, OCCUR_Once);
	DeclareArg(env, "basepath", VTYPE_string, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_HtmlEasyPrinting, PreviewText)
{
	Signal &sig = env.GetSignal();
	Object_wx_HtmlEasyPrinting *pThis = Object_wx_HtmlEasyPrinting::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxString htmltext = wxString::FromUTF8(arg.GetString(0));
	wxString basepath = wxEmptyString;
	if (arg.IsValid(1)) basepath = wxString::FromUTF8(arg.GetString(1));
	bool rtn = pThis->GetEntity()->PreviewText(htmltext, basepath);
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_HtmlEasyPrinting, PrintFile)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "htmlfile", VTYPE_string, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_HtmlEasyPrinting, PrintFile)
{
	Signal &sig = env.GetSignal();
	Object_wx_HtmlEasyPrinting *pThis = Object_wx_HtmlEasyPrinting::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxString htmlfile = wxString::FromUTF8(arg.GetString(0));
	bool rtn = pThis->GetEntity()->PrintFile(htmlfile);
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_HtmlEasyPrinting, PrintText)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "htmltext", VTYPE_string, OCCUR_Once);
	DeclareArg(env, "basepath", VTYPE_string, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_HtmlEasyPrinting, PrintText)
{
	Signal &sig = env.GetSignal();
	Object_wx_HtmlEasyPrinting *pThis = Object_wx_HtmlEasyPrinting::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxString htmltext = wxString::FromUTF8(arg.GetString(0));
	wxString basepath = wxEmptyString;
	if (arg.IsValid(1)) basepath = wxString::FromUTF8(arg.GetString(1));
	bool rtn = pThis->GetEntity()->PrintText(htmltext, basepath);
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_HtmlEasyPrinting, PageSetup)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_HtmlEasyPrinting, PageSetup)
{
	Signal &sig = env.GetSignal();
	Object_wx_HtmlEasyPrinting *pThis = Object_wx_HtmlEasyPrinting::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	pThis->GetEntity()->PageSetup();
	return Value::Nil;
}

Gura_DeclareMethod(wx_HtmlEasyPrinting, SetFonts)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "normal_face", VTYPE_string, OCCUR_Once);
	DeclareArg(env, "fixed_face", VTYPE_string, OCCUR_Once);
	DeclareArg(env, "sizes", VTYPE_number, OCCUR_ZeroOrOnce, FLAG_ListVar);
}

Gura_ImplementMethod(wx_HtmlEasyPrinting, SetFonts)
{
	Signal &sig = env.GetSignal();
	Object_wx_HtmlEasyPrinting *pThis = Object_wx_HtmlEasyPrinting::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxString normal_face = wxString::FromUTF8(arg.GetString(0));
	wxString fixed_face = wxString::FromUTF8(arg.GetString(1));
	int *sizes = nullptr;
	int sizesBuff[7] = { 0, 0, 0, 0, 0, 0, 0 };
	if (arg.IsValid(2)) {
		if (arg.GetList(2).size() != 7) {
			sig.SetError(ERR_ValueError, "sizes must contain seven numbers");
			return Value::Nil;
		}
		size_t i = 0;
		foreach_const (ValueList, pValue, arg.GetList(2)) {
			const Value &value = *pValue;
			sizes[i++] = value.GetInt();
		}
		sizes = sizesBuff;
	}
	pThis->GetEntity()->SetFonts(normal_face, fixed_face, sizes);
	return Value::Nil;
}

Gura_DeclareMethod(wx_HtmlEasyPrinting, SetHeader)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "header", VTYPE_string, OCCUR_Once);
	DeclareArg(env, "pg", VTYPE_number, OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_HtmlEasyPrinting, SetHeader)
{
	Signal &sig = env.GetSignal();
	Object_wx_HtmlEasyPrinting *pThis = Object_wx_HtmlEasyPrinting::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxString header = wxString::FromUTF8(arg.GetString(0));
	int pg = wxPAGE_ALL;
	if (arg.IsValid(1)) pg = arg.GetInt(1);
	pThis->GetEntity()->SetHeader(header, pg);
	return Value::Nil;
}

Gura_DeclareMethod(wx_HtmlEasyPrinting, SetFooter)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "footer", VTYPE_string, OCCUR_Once);
	DeclareArg(env, "pg", VTYPE_number, OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_HtmlEasyPrinting, SetFooter)
{
	Signal &sig = env.GetSignal();
	Object_wx_HtmlEasyPrinting *pThis = Object_wx_HtmlEasyPrinting::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxString footer = wxString::FromUTF8(arg.GetString(0));
	int pg = wxPAGE_ALL;
	if (arg.IsValid(1)) pg = arg.GetInt(1);
	pThis->GetEntity()->SetFooter(footer, pg);
	return Value::Nil;
}

Gura_DeclareMethod(wx_HtmlEasyPrinting, SetParentWindow)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "window", VTYPE_wx_Window, OCCUR_Once);
}

Gura_ImplementMethod(wx_HtmlEasyPrinting, SetParentWindow)
{
	Signal &sig = env.GetSignal();
	Object_wx_HtmlEasyPrinting *pThis = Object_wx_HtmlEasyPrinting::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxWindow *window = Object_wx_Window::GetObject(arg, 0)->GetEntity();
	pThis->GetEntity()->SetParentWindow(window);
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Object implementation for wxHtmlEasyPrinting
//----------------------------------------------------------------------------
Object_wx_HtmlEasyPrinting::~Object_wx_HtmlEasyPrinting()
{
}

Object *Object_wx_HtmlEasyPrinting::Clone() const
{
	return nullptr;
}

String Object_wx_HtmlEasyPrinting::ToString(bool exprFlag)
{
	String rtn("<wx.HtmlEasyPrinting:");
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
// Class implementation for wxHtmlEasyPrinting
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_HtmlEasyPrinting)
{
	Gura_AssignFunction(HtmlEasyPrinting);
	Gura_AssignMethod(wx_HtmlEasyPrinting, GetParentWindow);
	Gura_AssignMethod(wx_HtmlEasyPrinting, GetPrintData);
	Gura_AssignMethod(wx_HtmlEasyPrinting, GetPageSetupData);
	Gura_AssignMethod(wx_HtmlEasyPrinting, PreviewFile);
	Gura_AssignMethod(wx_HtmlEasyPrinting, PreviewText);
	Gura_AssignMethod(wx_HtmlEasyPrinting, PrintFile);
	Gura_AssignMethod(wx_HtmlEasyPrinting, PrintText);
	Gura_AssignMethod(wx_HtmlEasyPrinting, PageSetup);
	Gura_AssignMethod(wx_HtmlEasyPrinting, SetFonts);
	Gura_AssignMethod(wx_HtmlEasyPrinting, SetHeader);
	Gura_AssignMethod(wx_HtmlEasyPrinting, SetFooter);
	Gura_AssignMethod(wx_HtmlEasyPrinting, SetParentWindow);
}

Gura_ImplementDescendantCreator(wx_HtmlEasyPrinting)
{
	return new Object_wx_HtmlEasyPrinting((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
