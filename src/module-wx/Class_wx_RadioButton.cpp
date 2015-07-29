//----------------------------------------------------------------------------
// wxRadioButton
// extracted from radiobut.tex
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Class derivation
//----------------------------------------------------------------------------
class wx_RadioButton: public wxRadioButton, public GuraObjectObserver {
private:
	//Gura::Signal *_pSig;
	Object_wx_RadioButton *_pObj;
public:
	inline wx_RadioButton() : wxRadioButton(), _pObj(nullptr) {}
	inline wx_RadioButton(wxWindow* parent, wxWindowID id, const wxString& label, const wxPoint& pos, const wxSize& size, long style, const wxValidator& validator, const wxString& name) : wxRadioButton(parent, id, label, pos, size, style, validator, name), _pObj(nullptr) {}
	~wx_RadioButton();
	inline void AssocWithGura(Object_wx_RadioButton *pObj) {
		_pObj = pObj;
	}
	// virtual function of GuraObjectObserver
	virtual void GuraObjectDeleted();
};

wx_RadioButton::~wx_RadioButton()
{
	if (_pObj != nullptr) _pObj->InvalidateEntity();
}

void wx_RadioButton::GuraObjectDeleted()
{
	_pObj = nullptr;
}

//----------------------------------------------------------------------------
// Gura interfaces for wxRadioButton
//----------------------------------------------------------------------------
Gura_DeclareFunction(RadioButtonEmpty)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	SetClassToConstruct(Gura_UserClass(wx_RadioButton));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(RadioButtonEmpty)
{
	Signal &sig = env.GetSignal();
	if (!CheckWxReady(sig)) return Value::Null;
	wx_RadioButton *pEntity = new wx_RadioButton();
	Object_wx_RadioButton *pObj = Object_wx_RadioButton::GetThisObj(args);
	if (pObj == nullptr) {
		pObj = new Object_wx_RadioButton(pEntity, pEntity, OwnerFalse);
		pEntity->AssocWithGura(pObj);
		return ReturnValue(env, args, Value(pObj));
	}
	pObj->SetEntity(pEntity, pEntity, OwnerFalse);
	pEntity->AssocWithGura(pObj);
	return ReturnValue(env, args, args.GetThis());
}

Gura_DeclareFunction(RadioButton)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	SetClassToConstruct(Gura_UserClass(wx_RadioButton));
	DeclareArg(env, "parent", VTYPE_wx_Window, OCCUR_Once);
	DeclareArg(env, "id", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "label", VTYPE_string, OCCUR_Once);
	DeclareArg(env, "pos", VTYPE_wx_Point, OCCUR_ZeroOrOnce);
	DeclareArg(env, "size", VTYPE_wx_Size, OCCUR_ZeroOrOnce);
	DeclareArg(env, "style", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareArg(env, "validator", VTYPE_wx_Validator, OCCUR_ZeroOrOnce);
	DeclareArg(env, "name", VTYPE_string, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(RadioButton)
{
	Signal &sig = env.GetSignal();
	if (!CheckWxReady(sig)) return Value::Null;
	wxWindow *parent = Object_wx_Window::GetObject(args, 0)->GetEntity();
	wxWindowID id = static_cast<wxWindowID>(args.GetInt(1));
	wxString label = wxString::FromUTF8(args.GetString(2));
	wxPoint *pos = (wxPoint *)(&wxDefaultPosition);
	if (args.IsValid(3)) pos = Object_wx_Point::GetObject(args, 3)->GetEntity();
	wxSize *size = (wxSize *)(&wxDefaultSize);
	if (args.IsValid(4)) size = Object_wx_Size::GetObject(args, 4)->GetEntity();
	long style = 0;
	if (args.IsValid(5)) style = args.GetLong(5);
	wxValidator *validator = (wxValidator *)(&wxDefaultValidator);
	if (args.IsValid(6)) validator = Object_wx_Validator::GetObject(args, 6)->GetEntity();
	wxString name = wxT("radioButton");
	if (args.IsValid(7)) name = wxString::FromUTF8(args.GetString(7));
	wx_RadioButton *pEntity = new wx_RadioButton(parent, id, label, *pos, *size, style, *validator, name);
	Object_wx_RadioButton *pObj = Object_wx_RadioButton::GetThisObj(args);
	if (pObj == nullptr) {
		pObj = new Object_wx_RadioButton(pEntity, pEntity, OwnerFalse);
		pEntity->AssocWithGura(pObj);
		return ReturnValue(env, args, Value(pObj));
	}
	pObj->SetEntity(pEntity, pEntity, OwnerFalse);
	pEntity->AssocWithGura(pObj);
	return ReturnValue(env, args, args.GetThis());
}

Gura_DeclareMethod(wx_RadioButton, Create)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "parent", VTYPE_wx_Window, OCCUR_Once);
	DeclareArg(env, "id", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "label", VTYPE_string, OCCUR_Once);
	DeclareArg(env, "pos", VTYPE_wx_Point, OCCUR_ZeroOrOnce);
	DeclareArg(env, "size", VTYPE_wx_Size, OCCUR_ZeroOrOnce);
	DeclareArg(env, "style", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareArg(env, "validator", VTYPE_wx_Validator, OCCUR_ZeroOrOnce);
	DeclareArg(env, "name", VTYPE_string, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_RadioButton, Create)
{
	Signal &sig = env.GetSignal();
	Object_wx_RadioButton *pThis = Object_wx_RadioButton::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	wxWindow *parent = Object_wx_Window::GetObject(args, 0)->GetEntity();
	wxWindowID id = static_cast<wxWindowID>(args.GetInt(1));
	wxString label = wxString::FromUTF8(args.GetString(2));
	wxPoint *pos = (wxPoint *)(&wxDefaultPosition);
	if (args.IsValid(3)) pos = Object_wx_Point::GetObject(args, 3)->GetEntity();
	wxSize *size = (wxSize *)(&wxDefaultSize);
	if (args.IsValid(4)) size = Object_wx_Size::GetObject(args, 4)->GetEntity();
	long style = 0;
	if (args.IsValid(5)) style = args.GetLong(5);
	wxValidator *validator = (wxValidator *)(&wxDefaultValidator);
	if (args.IsValid(6)) validator = Object_wx_Validator::GetObject(args, 6)->GetEntity();
	wxString name = wxT("radioButton");
	if (args.IsValid(7)) name = wxString::FromUTF8(args.GetString(7));
	bool rtn = pThis->GetEntity()->Create(parent, id, label, *pos, *size, style, *validator, name);
	return ReturnValue(env, args, Value(rtn));
}

Gura_DeclareMethod(wx_RadioButton, GetValue)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_RadioButton, GetValue)
{
	Signal &sig = env.GetSignal();
	Object_wx_RadioButton *pThis = Object_wx_RadioButton::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	bool rtn = pThis->GetEntity()->GetValue();
	return ReturnValue(env, args, Value(rtn));
}

Gura_DeclareMethod(wx_RadioButton, SetValue)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "value", VTYPE_boolean, OCCUR_Once);
}

Gura_ImplementMethod(wx_RadioButton, SetValue)
{
	Signal &sig = env.GetSignal();
	Object_wx_RadioButton *pThis = Object_wx_RadioButton::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	bool value = args.GetBoolean(0);
	pThis->GetEntity()->SetValue(value);
	return Value::Null;
}

//----------------------------------------------------------------------------
// Object implementation for wxRadioButton
//----------------------------------------------------------------------------
Object_wx_RadioButton::~Object_wx_RadioButton()
{
}

Object *Object_wx_RadioButton::Clone() const
{
	return nullptr;
}

String Object_wx_RadioButton::ToString(bool exprFlag)
{
	String rtn("<wx.RadioButton:");
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
// Class implementation for wxRadioButton
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_RadioButton)
{
	Gura_AssignWxStringValue(RadioButtonNameStr);
	Gura_AssignFunction(RadioButtonEmpty);
	Gura_AssignFunction(RadioButton);
	Gura_AssignMethod(wx_RadioButton, Create);
	Gura_AssignMethod(wx_RadioButton, GetValue);
	Gura_AssignMethod(wx_RadioButton, SetValue);
}

Gura_ImplementDescendantCreator(wx_RadioButton)
{
	return new Object_wx_RadioButton((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
