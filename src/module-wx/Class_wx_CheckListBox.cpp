//----------------------------------------------------------------------------
// wxCheckListBox
// extracted from checklst.tex
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Class derivation
//----------------------------------------------------------------------------
class wx_CheckListBox: public wxCheckListBox, public GuraObjectObserver {
private:
	//Gura::Signal *_pSig;
	Object_wx_CheckListBox *_pObj;
public:
	inline wx_CheckListBox() : wxCheckListBox(), _pObj(nullptr) {}
	//inline wx_CheckListBox(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, int n, const wxString choices[], long style, const wxValidator& validator, const wxString& name) : wxCheckListBox(parent, id, pos, size, n, choices[], style, validator, name), _pObj(nullptr) {}
	inline wx_CheckListBox(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, const wxArrayString& choices, long style, const wxValidator& validator, const wxString& name) : wxCheckListBox(parent, id, pos, size, choices, style, validator, name), _pObj(nullptr) {}
	~wx_CheckListBox();
	inline void AssocWithGura(Object_wx_CheckListBox *pObj) {
		_pObj = pObj;
	}
	// virtual function of GuraObjectObserver
	virtual void GuraObjectDeleted();
};

wx_CheckListBox::~wx_CheckListBox()
{
	if (_pObj != nullptr) _pObj->InvalidateEntity();
}

void wx_CheckListBox::GuraObjectDeleted()
{
	_pObj = nullptr;
}

//----------------------------------------------------------------------------
// Gura interfaces for wxCheckListBox
//----------------------------------------------------------------------------
Gura_DeclareFunction(CheckListBoxEmpty)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	SetClassToConstruct(Gura_UserClass(wx_CheckListBox));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(CheckListBoxEmpty)
{
	Signal &sig = env.GetSignal();
	if (!CheckWxReady(sig)) return Value::Nil;
	wx_CheckListBox *pEntity = new wx_CheckListBox();
	Object_wx_CheckListBox *pObj = Object_wx_CheckListBox::GetObjectThis(arg);
	if (pObj == nullptr) {
		pObj = new Object_wx_CheckListBox(pEntity, pEntity, OwnerFalse);
		pEntity->AssocWithGura(pObj);
		return ReturnValue(env, arg, Value(pObj));
	}
	pObj->SetEntity(pEntity, pEntity, OwnerFalse);
	pEntity->AssocWithGura(pObj);
	return ReturnValue(env, arg, arg.GetValueThis());
}

Gura_DeclareFunction(CheckListBox)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	SetClassToConstruct(Gura_UserClass(wx_CheckListBox));
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

Gura_ImplementFunction(CheckListBox)
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
	wx_CheckListBox *pEntity = new wx_CheckListBox(parent, id, *pos, *size, *choices, style, *validator, name);
	Object_wx_CheckListBox *pObj = Object_wx_CheckListBox::GetObjectThis(arg);
	if (pObj == nullptr) {
		pObj = new Object_wx_CheckListBox(pEntity, pEntity, OwnerFalse);
		pEntity->AssocWithGura(pObj);
		return ReturnValue(env, arg, Value(pObj));
	}
	pObj->SetEntity(pEntity, pEntity, OwnerFalse);
	pEntity->AssocWithGura(pObj);
	return ReturnValue(env, arg, arg.GetValueThis());
}

Gura_DeclareMethod(wx_CheckListBox, Check)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "item", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "check", VTYPE_boolean, OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_CheckListBox, Check)
{
	Signal &sig = env.GetSignal();
	Object_wx_CheckListBox *pThis = Object_wx_CheckListBox::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	int item = arg.GetInt(0);
	bool check = true;
	if (arg.IsValid(1)) check = arg.GetBoolean(1);
	pThis->GetEntity()->Check(item, check);
	return Value::Nil;
}

Gura_DeclareMethod(wx_CheckListBox, IsChecked)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "item", VTYPE_number, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_CheckListBox, IsChecked)
{
	Signal &sig = env.GetSignal();
	Object_wx_CheckListBox *pThis = Object_wx_CheckListBox::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	unsigned item = arg.GetInt(0);
	bool rtn = pThis->GetEntity()->IsChecked(item);
	return ReturnValue(env, arg, Value(rtn));
}

//----------------------------------------------------------------------------
// Object implementation for wxCheckListBox
//----------------------------------------------------------------------------
Object_wx_CheckListBox::~Object_wx_CheckListBox()
{
}

Object *Object_wx_CheckListBox::Clone() const
{
	return nullptr;
}

String Object_wx_CheckListBox::ToString(bool exprFlag)
{
	String rtn("<wx.CheckListBox:");
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
// Class implementation for wxCheckListBox
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_CheckListBox)
{
	//Gura_AssignWxStringValue(CheckListBoxNameStr);
	Gura_AssignFunction(CheckListBoxEmpty);
	Gura_AssignFunction(CheckListBox);
	Gura_AssignMethod(wx_CheckListBox, Check);
	Gura_AssignMethod(wx_CheckListBox, IsChecked);
}

Gura_ImplementDescendantCreator(wx_CheckListBox)
{
	return new Object_wx_CheckListBox((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
