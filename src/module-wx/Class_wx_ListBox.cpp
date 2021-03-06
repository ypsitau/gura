//----------------------------------------------------------------------------
// wxListBox
// extracted from listbox.tex
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Class derivation
//----------------------------------------------------------------------------
class wx_ListBox: public wxListBox, public GuraObjectObserver {
private:
	//Gura::Signal *_pSig;
	Object_wx_ListBox *_pObj;
public:
	inline wx_ListBox() : wxListBox(), _pObj(nullptr) {}
	//inline wx_ListBox(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, int n, const wxString choices[], long style, const wxValidator& validator, const wxString& name) : wxListBox(parent, id, pos, size, n, choices[], style, validator, name), _pObj(nullptr) {}
	inline wx_ListBox(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, const wxArrayString& choices, long style, const wxValidator& validator, const wxString& name) : wxListBox(parent, id, pos, size, choices, style, validator, name), _pObj(nullptr) {}
	~wx_ListBox();
	inline void AssocWithGura(Object_wx_ListBox *pObj) {
		_pObj = pObj;
	}
	// virtual function of GuraObjectObserver
	virtual void GuraObjectDeleted();
};

wx_ListBox::~wx_ListBox()
{
	if (_pObj != nullptr) _pObj->InvalidateEntity();
}

void wx_ListBox::GuraObjectDeleted()
{
	_pObj = nullptr;
}

//----------------------------------------------------------------------------
// Gura interfaces for wxListBox
//----------------------------------------------------------------------------
Gura_DeclareFunction(ListBoxEmpty)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	SetClassToConstruct(Gura_UserClass(wx_ListBox));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(ListBoxEmpty)
{
	Signal &sig = env.GetSignal();
	if (!CheckWxReady(sig)) return Value::Nil;
	wx_ListBox *pEntity = new wx_ListBox();
	Object_wx_ListBox *pObj = Object_wx_ListBox::GetObjectThis(arg);
	if (pObj == nullptr) {
		pObj = new Object_wx_ListBox(pEntity, pEntity, OwnerFalse);
		pEntity->AssocWithGura(pObj);
		return ReturnValue(env, arg, Value(pObj));
	}
	pObj->SetEntity(pEntity, pEntity, OwnerFalse);
	pEntity->AssocWithGura(pObj);
	return ReturnValue(env, arg, arg.GetValueThis());
}

Gura_DeclareFunction(ListBox)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	SetClassToConstruct(Gura_UserClass(wx_ListBox));
	DeclareArg(env, "parent", VTYPE_wx_Window, OCCUR_Once);
	DeclareArg(env, "id", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "pos", VTYPE_wx_Point, OCCUR_ZeroOrOnce);
	DeclareArg(env, "size", VTYPE_wx_Size, OCCUR_ZeroOrOnce);
	DeclareArg(env, "choices", VTYPE_string, OCCUR_ZeroOrOnce, FLAG_ListVar);
	DeclareArg(env, "style", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareArg(env, "validator", VTYPE_wx_Validator, OCCUR_ZeroOrOnce);
	DeclareArg(env, "name", VTYPE_string, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(ListBox)
{
	Signal &sig = env.GetSignal();
	if (!CheckWxReady(sig)) return Value::Nil;
	wxWindow *parent = Object_wx_Window::GetObject(arg, 0)->GetEntity();
	wxWindowID id = static_cast<wxWindowID>(arg.GetInt(1));
	wxPoint *pos = (wxPoint *)(&wxDefaultPosition);
	if (arg.IsValid(2)) pos = Object_wx_Point::GetObject(arg, 2)->GetEntity();
	wxSize *size = (wxSize *)(&wxDefaultSize);
	if (arg.IsValid(3)) size = Object_wx_Size::GetObject(arg, 3)->GetEntity();
	std::unique_ptr<wxArrayString> choices;
	if (arg.IsValid(4)) {
		choices.reset(CreateArrayString(arg.GetList(4)));
	} else {
		choices.reset(new wxArrayString());
	}
	long style = 0;
	if (arg.IsValid(5)) style = arg.GetLong(5);
	wxValidator *validator = (wxValidator *)(&wxDefaultValidator);
	if (arg.IsValid(6)) validator = Object_wx_Validator::GetObject(arg, 6)->GetEntity();
	wxString name = wxT("listBox");
	if (arg.IsValid(7)) name = wxString::FromUTF8(arg.GetString(7));
	wx_ListBox *pEntity = new wx_ListBox(parent, id, *pos, *size, *choices, style, *validator, name);
	Object_wx_ListBox *pObj = Object_wx_ListBox::GetObjectThis(arg);
	if (pObj == nullptr) {
		pObj = new Object_wx_ListBox(pEntity, pEntity, OwnerFalse);
		pEntity->AssocWithGura(pObj);
		return ReturnValue(env, arg, Value(pObj));
	}
	pObj->SetEntity(pEntity, pEntity, OwnerFalse);
	pEntity->AssocWithGura(pObj);
	return ReturnValue(env, arg, arg.GetValueThis());
}

Gura_DeclareMethod(wx_ListBox, Create)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "parent", VTYPE_wx_Window, OCCUR_Once);
	DeclareArg(env, "id", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "pos", VTYPE_wx_Point, OCCUR_ZeroOrOnce);
	DeclareArg(env, "size", VTYPE_wx_Size, OCCUR_ZeroOrOnce);
	DeclareArg(env, "choices", VTYPE_string, OCCUR_ZeroOrOnce, FLAG_ListVar);
	DeclareArg(env, "style", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareArg(env, "validator", VTYPE_wx_Validator, OCCUR_ZeroOrOnce);
	DeclareArg(env, "name", VTYPE_string, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_ListBox, Create)
{
	Signal &sig = env.GetSignal();
	Object_wx_ListBox *pThis = Object_wx_ListBox::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxWindow *parent = Object_wx_Window::GetObject(arg, 0)->GetEntity();
	wxWindowID id = static_cast<wxWindowID>(arg.GetInt(1));
	wxPoint *pos = (wxPoint *)(&wxDefaultPosition);
	if (arg.IsValid(2)) pos = Object_wx_Point::GetObject(arg, 2)->GetEntity();
	wxSize *size = (wxSize *)(&wxDefaultSize);
	if (arg.IsValid(3)) size = Object_wx_Size::GetObject(arg, 3)->GetEntity();
	std::unique_ptr<wxArrayString> choices;
	if (arg.IsValid(4)) {
		choices.reset(CreateArrayString(arg.GetList(4)));
	} else {
		choices.reset(new wxArrayString());
	}
	long style = 0;
	if (arg.IsValid(5)) style = arg.GetLong(5);
	wxValidator *validator = (wxValidator *)(&wxDefaultValidator);
	if (arg.IsValid(6)) validator = Object_wx_Validator::GetObject(arg, 6)->GetEntity();
	wxString name = wxT("listBox");
	if (arg.IsValid(7)) name = wxString::FromUTF8(arg.GetString(7));
	bool rtn = pThis->GetEntity()->Create(parent, id, *pos, *size, *choices, style, *validator, name);
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_ListBox, Deselect)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "n", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_ListBox, Deselect)
{
	Signal &sig = env.GetSignal();
	Object_wx_ListBox *pThis = Object_wx_ListBox::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	int n = arg.GetInt(0);
	pThis->GetEntity()->Deselect(n);
	return Value::Nil;
}

Gura_DeclareMethod(wx_ListBox, GetSelections)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_ListBox, GetSelections)
{
	Signal &sig = env.GetSignal();
	Object_wx_ListBox *pThis = Object_wx_ListBox::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxArrayInt selections;
	int rtn = pThis->GetEntity()->GetSelections(selections);
	return ReturnValue(env, arg, ArrayIntToValue(env, selections));
}

Gura_DeclareMethod(wx_ListBox, InsertItems)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "items", VTYPE_string, OCCUR_Once, FLAG_ListVar);
	DeclareArg(env, "pos", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_ListBox, InsertItems)
{
	Signal &sig = env.GetSignal();
	Object_wx_ListBox *pThis = Object_wx_ListBox::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	std::unique_ptr<wxArrayString> items(CreateArrayString(arg.GetList(0)));
	unsigned pos = arg.GetInt(1);
	pThis->GetEntity()->InsertItems(*items, pos);
	return Value::Nil;
}

Gura_DeclareMethod(wx_ListBox, HitTest)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "point", VTYPE_wx_Point, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_ListBox, HitTest)
{
	Signal &sig = env.GetSignal();
	Object_wx_ListBox *pThis = Object_wx_ListBox::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxPoint *point = Object_wx_Point::GetObject(arg, 0)->GetEntity();
	int rtn = pThis->GetEntity()->HitTest(*point);
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_ListBox, IsSelected)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "n", VTYPE_number, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_ListBox, IsSelected)
{
	Signal &sig = env.GetSignal();
	Object_wx_ListBox *pThis = Object_wx_ListBox::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	int n = arg.GetInt(0);
	bool rtn = pThis->GetEntity()->IsSelected(n);
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_ListBox, Set)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "choices", VTYPE_string, OCCUR_Once, FLAG_ListVar);
	//DeclareArg(env, "clientData", VTYPE_number, OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_ListBox, Set)
{
	Signal &sig = env.GetSignal();
	Object_wx_ListBox *pThis = Object_wx_ListBox::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	std::unique_ptr<wxArrayString> choices(CreateArrayString(arg.GetList(0)));
	void **clientData = nullptr;
	//if (arg.IsValid(1)) **clientData = arg.GetInt(1);
	pThis->GetEntity()->Set(*choices, clientData);
	return Value::Nil;
}

Gura_DeclareMethod(wx_ListBox, SetFirstItem)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "n", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_ListBox, SetFirstItem)
{
	Signal &sig = env.GetSignal();
	Object_wx_ListBox *pThis = Object_wx_ListBox::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	int n = arg.GetInt(0);
	pThis->GetEntity()->SetFirstItem(n);
	return Value::Nil;
}

Gura_DeclareMethod(wx_ListBox, SetFirstItemString)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "string", VTYPE_string, OCCUR_Once);
}

Gura_ImplementMethod(wx_ListBox, SetFirstItemString)
{
	Signal &sig = env.GetSignal();
	Object_wx_ListBox *pThis = Object_wx_ListBox::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxString string = wxString::FromUTF8(arg.GetString(0));
	pThis->GetEntity()->SetFirstItem(string);
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Object implementation for wxListBox
//----------------------------------------------------------------------------
Object_wx_ListBox::~Object_wx_ListBox()
{
}

Object *Object_wx_ListBox::Clone() const
{
	return nullptr;
}

String Object_wx_ListBox::ToString(bool exprFlag)
{
	String rtn("<wx.ListBox:");
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
// Class implementation for wxListBox
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_ListBox)
{
	Gura_AssignFunction(ListBoxEmpty);
	Gura_AssignFunction(ListBox);
	Gura_AssignMethod(wx_ListBox, Create);
	Gura_AssignMethod(wx_ListBox, Deselect);
	Gura_AssignMethod(wx_ListBox, GetSelections);
	Gura_AssignMethod(wx_ListBox, InsertItems);
	Gura_AssignMethod(wx_ListBox, HitTest);
	Gura_AssignMethod(wx_ListBox, IsSelected);
	Gura_AssignMethod(wx_ListBox, Set);
	Gura_AssignMethod(wx_ListBox, SetFirstItem);
	Gura_AssignMethod(wx_ListBox, SetFirstItemString);
}

Gura_ImplementDescendantCreator(wx_ListBox)
{
	return new Object_wx_ListBox((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
