//----------------------------------------------------------------------------
// wxSearchCtrl
// extracted from srchctrl.tex
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

Gura_DeclarePrivUserSymbol(SetMenu);
Gura_DeclarePrivUserSymbol(GetMenu);
Gura_DeclarePrivUserSymbol(ShowSearchButton);
Gura_DeclarePrivUserSymbol(IsSearchButtonVisible);
Gura_DeclarePrivUserSymbol(ShowCancelButton);
Gura_DeclarePrivUserSymbol(IsCancelButtonVisible);

//----------------------------------------------------------------------------
// Class derivation
//----------------------------------------------------------------------------
class wx_SearchCtrl: public wxSearchCtrl, public GuraObjectObserver {
private:
	//Gura::Signal *_pSig;
	Object_wx_SearchCtrl *_pObj;
public:
	inline wx_SearchCtrl() : wxSearchCtrl(), _pObj(nullptr) {}
	inline wx_SearchCtrl(wxWindow* parent, wxWindowID id, const wxString& value, const wxPoint& pos, const wxSize& size, long style, const wxValidator& validator, const wxString& name) : wxSearchCtrl(parent, id, value, pos, size, style, validator, name), _pObj(nullptr) {}
	//virtual void SetMenu(wxMenu* menu);
	//virtual wxMenu* GetMenu();
	//virtual void ShowSearchButton(bool show);
	//virtual bool IsSearchButtonVisible();
	//virtual void ShowCancelButton(bool show);
	//virtual bool IsCancelButtonVisible();
	~wx_SearchCtrl();
	inline void AssocWithGura(Object_wx_SearchCtrl *pObj) {
		_pObj = pObj;
	}
	// virtual function of GuraObjectObserver
	virtual void GuraObjectDeleted();
};

wx_SearchCtrl::~wx_SearchCtrl()
{
	if (_pObj != nullptr) _pObj->InvalidateEntity();
}

void wx_SearchCtrl::GuraObjectDeleted()
{
	_pObj = nullptr;
}

//----------------------------------------------------------------------------
// Gura interfaces for wxSearchCtrl
//----------------------------------------------------------------------------
Gura_DeclareFunction(SearchCtrlEmpty)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	SetClassToConstruct(Gura_UserClass(wx_SearchCtrl));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(SearchCtrlEmpty)
{
	Signal &sig = env.GetSignal();
	if (!CheckWxReady(sig)) return Value::Nil;
	wx_SearchCtrl *pEntity = new wx_SearchCtrl();
	Object_wx_SearchCtrl *pObj = Object_wx_SearchCtrl::GetObjectThis(arg);
	if (pObj == nullptr) {
		pObj = new Object_wx_SearchCtrl(pEntity, pEntity, OwnerFalse);
		pEntity->AssocWithGura(pObj);
		return ReturnValue(env, arg, Value(pObj));
	}
	pObj->SetEntity(pEntity, pEntity, OwnerFalse);
	pEntity->AssocWithGura(pObj);
	return ReturnValue(env, arg, arg.GetValueThis());
}

Gura_DeclareFunction(SearchCtrl)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	SetClassToConstruct(Gura_UserClass(wx_SearchCtrl));
	DeclareArg(env, "parent", VTYPE_wx_Window, OCCUR_Once);
	DeclareArg(env, "id", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "value", VTYPE_string, OCCUR_ZeroOrOnce);
	DeclareArg(env, "pos", VTYPE_wx_Point, OCCUR_ZeroOrOnce);
	DeclareArg(env, "size", VTYPE_wx_Size, OCCUR_ZeroOrOnce);
	DeclareArg(env, "style", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareArg(env, "validator", VTYPE_wx_Validator, OCCUR_ZeroOrOnce);
	DeclareArg(env, "name", VTYPE_string, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(SearchCtrl)
{
	Signal &sig = env.GetSignal();
	if (!CheckWxReady(sig)) return Value::Nil;
	wxWindow *parent = Object_wx_Window::GetObject(arg, 0)->GetEntity();
	wxWindowID id = static_cast<wxWindowID>(arg.GetInt(1));
	wxString value = wxT("");
	if (arg.IsValid(2)) value = wxString::FromUTF8(arg.GetString(2));
	wxPoint *pos = (wxPoint *)(&wxDefaultPosition);
	if (arg.IsValid(3)) pos = Object_wx_Point::GetObject(arg, 3)->GetEntity();
	wxSize *size = (wxSize *)(&wxDefaultSize);
	if (arg.IsValid(4)) size = Object_wx_Size::GetObject(arg, 4)->GetEntity();
	long style = 0;
	if (arg.IsValid(5)) style = arg.GetLong(5);
	wxValidator *validator = (wxValidator *)(&wxDefaultValidator);
	if (arg.IsValid(6)) validator = Object_wx_Validator::GetObject(arg, 6)->GetEntity();
	wxString name = wxSearchCtrlNameStr;
	if (arg.IsValid(7)) name = wxString::FromUTF8(arg.GetString(7));
	wx_SearchCtrl *pEntity = new wx_SearchCtrl(parent, id, value, *pos, *size, style, *validator, name);
	Object_wx_SearchCtrl *pObj = Object_wx_SearchCtrl::GetObjectThis(arg);
	if (pObj == nullptr) {
		pObj = new Object_wx_SearchCtrl(pEntity, pEntity, OwnerFalse);
		pEntity->AssocWithGura(pObj);
		return ReturnValue(env, arg, Value(pObj));
	}
	pObj->SetEntity(pEntity, pEntity, OwnerFalse);
	pEntity->AssocWithGura(pObj);
	return ReturnValue(env, arg, arg.GetValueThis());
}

Gura_DeclareMethod(wx_SearchCtrl, SetMenu)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "menu", VTYPE_wx_Menu, OCCUR_Once);
}

Gura_ImplementMethod(wx_SearchCtrl, SetMenu)
{
	Signal &sig = env.GetSignal();
	Object_wx_SearchCtrl *pThis = Object_wx_SearchCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxMenu *menu = Object_wx_Menu::GetObject(arg, 0)->GetEntity();
	pThis->GetEntity()->SetMenu(menu);
	return Value::Nil;
}

Gura_DeclareMethod(wx_SearchCtrl, GetMenu)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_SearchCtrl, GetMenu)
{
	Signal &sig = env.GetSignal();
	Object_wx_SearchCtrl *pThis = Object_wx_SearchCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxMenu *rtn = (wxMenu *)pThis->GetEntity()->GetMenu();
	return ReturnValue(env, arg, Value(new Object_wx_Menu(rtn, nullptr, OwnerFalse)));
}

Gura_DeclareMethod(wx_SearchCtrl, ShowSearchButton)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "show", VTYPE_boolean, OCCUR_Once);
}

Gura_ImplementMethod(wx_SearchCtrl, ShowSearchButton)
{
	Signal &sig = env.GetSignal();
	Object_wx_SearchCtrl *pThis = Object_wx_SearchCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	bool show = arg.GetBoolean(0);
	pThis->GetEntity()->ShowSearchButton(show);
	return Value::Nil;
}

Gura_DeclareMethod(wx_SearchCtrl, IsSearchButtonVisible)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_SearchCtrl, IsSearchButtonVisible)
{
	Signal &sig = env.GetSignal();
	Object_wx_SearchCtrl *pThis = Object_wx_SearchCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	bool rtn = pThis->GetEntity()->IsSearchButtonVisible();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_SearchCtrl, ShowCancelButton)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "show", VTYPE_boolean, OCCUR_Once);
}

Gura_ImplementMethod(wx_SearchCtrl, ShowCancelButton)
{
	Signal &sig = env.GetSignal();
	Object_wx_SearchCtrl *pThis = Object_wx_SearchCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	bool show = arg.GetBoolean(0);
	pThis->GetEntity()->ShowCancelButton(show);
	return Value::Nil;
}

Gura_DeclareMethod(wx_SearchCtrl, IsCancelButtonVisible)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_SearchCtrl, IsCancelButtonVisible)
{
	Signal &sig = env.GetSignal();
	Object_wx_SearchCtrl *pThis = Object_wx_SearchCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	bool rtn = pThis->GetEntity()->IsCancelButtonVisible();
	return ReturnValue(env, arg, Value(rtn));
}

//----------------------------------------------------------------------------
// Object implementation for wxSearchCtrl
//----------------------------------------------------------------------------
Object_wx_SearchCtrl::~Object_wx_SearchCtrl()
{
}

Object *Object_wx_SearchCtrl::Clone() const
{
	return nullptr;
}

String Object_wx_SearchCtrl::ToString(bool exprFlag)
{
	String rtn("<wx.SearchCtrl:");
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
// Class implementation for wxSearchCtrl
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_SearchCtrl)
{
	Gura_RealizeUserSymbol(SetMenu);
	Gura_RealizeUserSymbol(GetMenu);
	Gura_RealizeUserSymbol(ShowSearchButton);
	Gura_RealizeUserSymbol(IsSearchButtonVisible);
	Gura_RealizeUserSymbol(ShowCancelButton);
	Gura_RealizeUserSymbol(IsCancelButtonVisible);
	Gura_AssignWxStringValue(SearchCtrlNameStr);
	Gura_AssignFunction(SearchCtrlEmpty);
	Gura_AssignFunction(SearchCtrl);
	Gura_AssignMethod(wx_SearchCtrl, SetMenu);
	Gura_AssignMethod(wx_SearchCtrl, GetMenu);
	Gura_AssignMethod(wx_SearchCtrl, ShowSearchButton);
	Gura_AssignMethod(wx_SearchCtrl, IsSearchButtonVisible);
	Gura_AssignMethod(wx_SearchCtrl, ShowCancelButton);
	Gura_AssignMethod(wx_SearchCtrl, IsCancelButtonVisible);
}

Gura_ImplementDescendantCreator(wx_SearchCtrl)
{
	return new Object_wx_SearchCtrl((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
