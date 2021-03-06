//----------------------------------------------------------------------------
// wxCollapsiblePane
// extracted from collpane.tex
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Class derivation
//----------------------------------------------------------------------------
class wx_CollapsiblePane: public wxCollapsiblePane, public GuraObjectObserver {
private:
	//Gura::Signal *_pSig;
	Object_wx_CollapsiblePane *_pObj;
public:
	inline wx_CollapsiblePane(wxWindow * parent, wxWindowID id, const wxString& label, const wxPoint& pos, const wxSize& size, long style, const wxValidator& validator, const wxString& name) : wxCollapsiblePane(parent, id, label, pos, size, style, validator, name), _pObj(nullptr) {}
	~wx_CollapsiblePane();
	inline void AssocWithGura(Object_wx_CollapsiblePane *pObj) {
		_pObj = pObj;
	}
	// virtual function of GuraObjectObserver
	virtual void GuraObjectDeleted();
};

wx_CollapsiblePane::~wx_CollapsiblePane()
{
	if (_pObj != nullptr) _pObj->InvalidateEntity();
}

void wx_CollapsiblePane::GuraObjectDeleted()
{
	_pObj = nullptr;
}

//----------------------------------------------------------------------------
// Gura interfaces for wxCollapsiblePane
//----------------------------------------------------------------------------
Gura_DeclareFunction(CollapsiblePane)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	SetClassToConstruct(Gura_UserClass(wx_CollapsiblePane));
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

Gura_ImplementFunction(CollapsiblePane)
{
	Signal &sig = env.GetSignal();
	if (!CheckWxReady(sig)) return Value::Nil;
	wxWindow *parent = Object_wx_Window::GetObject(arg, 0)->GetEntity();
	wxWindowID id = static_cast<wxWindowID>(arg.GetInt(1));
	wxString label = wxString::FromUTF8(arg.GetString(2));
	wxPoint *pos = (wxPoint *)(&wxDefaultPosition);
	if (arg.IsValid(3)) pos = Object_wx_Point::GetObject(arg, 3)->GetEntity();
	wxSize *size = (wxSize *)(&wxDefaultSize);
	if (arg.IsValid(4)) size = Object_wx_Size::GetObject(arg, 4)->GetEntity();
	long style = wxCP_DEFAULT_STYLE;
	if (arg.IsValid(5)) style = arg.GetLong(5);
	wxValidator *validator = (wxValidator *)(&wxDefaultValidator);
	if (arg.IsValid(6)) validator = Object_wx_Validator::GetObject(arg, 6)->GetEntity();
	wxString name = wxT("collapsiblePane");
	if (arg.IsValid(7)) name = wxString::FromUTF8(arg.GetString(7));
	wx_CollapsiblePane *pEntity = new wx_CollapsiblePane(parent, id, label, *pos, *size, style, *validator, name);
	Object_wx_CollapsiblePane *pObj = Object_wx_CollapsiblePane::GetObjectThis(arg);
	if (pObj == nullptr) {
		pObj = new Object_wx_CollapsiblePane(pEntity, pEntity, OwnerFalse);
		pEntity->AssocWithGura(pObj);
		return ReturnValue(env, arg, Value(pObj));
	}
	pObj->SetEntity(pEntity, pEntity, OwnerFalse);
	pEntity->AssocWithGura(pObj);
	return ReturnValue(env, arg, arg.GetValueThis());
}

Gura_DeclareMethod(wx_CollapsiblePane, Create)
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

Gura_ImplementMethod(wx_CollapsiblePane, Create)
{
	Signal &sig = env.GetSignal();
	Object_wx_CollapsiblePane *pThis = Object_wx_CollapsiblePane::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxWindow *parent = Object_wx_Window::GetObject(arg, 0)->GetEntity();
	wxWindowID id = static_cast<wxWindowID>(arg.GetInt(1));
	wxString label = wxString::FromUTF8(arg.GetString(2));
	wxPoint *pos = (wxPoint *)(&wxDefaultPosition);
	if (arg.IsValid(3)) pos = Object_wx_Point::GetObject(arg, 3)->GetEntity();
	wxSize *size = (wxSize *)(&wxDefaultSize);
	if (arg.IsValid(4)) size = Object_wx_Size::GetObject(arg, 4)->GetEntity();
	long style = wxCP_DEFAULT_STYLE;
	if (arg.IsValid(5)) style = arg.GetLong(5);
	wxValidator *validator = (wxValidator *)(&wxDefaultValidator);
	if (arg.IsValid(6)) validator = Object_wx_Validator::GetObject(arg, 6)->GetEntity();
	wxString name = wxT("collapsiblePane");
	if (arg.IsValid(7)) name = wxString::FromUTF8(arg.GetString(7));
	bool rtn = pThis->GetEntity()->Create(parent, id, label, *pos, *size, style, *validator, name);
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_CollapsiblePane, IsCollapsed)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_CollapsiblePane, IsCollapsed)
{
	Signal &sig = env.GetSignal();
	Object_wx_CollapsiblePane *pThis = Object_wx_CollapsiblePane::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	bool rtn = pThis->GetEntity()->IsCollapsed();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_CollapsiblePane, IsExpanded)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_CollapsiblePane, IsExpanded)
{
	Signal &sig = env.GetSignal();
	Object_wx_CollapsiblePane *pThis = Object_wx_CollapsiblePane::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	bool rtn = pThis->GetEntity()->IsExpanded();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_CollapsiblePane, Collapse)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "collapse", VTYPE_boolean, OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_CollapsiblePane, Collapse)
{
	Signal &sig = env.GetSignal();
	Object_wx_CollapsiblePane *pThis = Object_wx_CollapsiblePane::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	bool collapse = true;
	if (arg.IsValid(0)) collapse = arg.GetBoolean(0);
	pThis->GetEntity()->Collapse(collapse);
	return Value::Nil;
}

Gura_DeclareMethod(wx_CollapsiblePane, Expand)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_CollapsiblePane, Expand)
{
	Signal &sig = env.GetSignal();
	Object_wx_CollapsiblePane *pThis = Object_wx_CollapsiblePane::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	pThis->GetEntity()->Expand();
	return Value::Nil;
}

Gura_DeclareMethod(wx_CollapsiblePane, GetPane)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_CollapsiblePane, GetPane)
{
	Signal &sig = env.GetSignal();
	Object_wx_CollapsiblePane *pThis = Object_wx_CollapsiblePane::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxWindow *rtn = (wxWindow *)pThis->GetEntity()->GetPane();
	return ReturnValue(env, arg, Value(new Object_wx_Window(rtn, nullptr, OwnerFalse)));
}

//----------------------------------------------------------------------------
// Object implementation for wxCollapsiblePane
//----------------------------------------------------------------------------
Object_wx_CollapsiblePane::~Object_wx_CollapsiblePane()
{
}

Object *Object_wx_CollapsiblePane::Clone() const
{
	return nullptr;
}

String Object_wx_CollapsiblePane::ToString(bool exprFlag)
{
	String rtn("<wx.CollapsiblePane:");
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
// Class implementation for wxCollapsiblePane
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_CollapsiblePane)
{
	Gura_AssignFunction(CollapsiblePane);
	Gura_AssignMethod(wx_CollapsiblePane, Create);
	Gura_AssignMethod(wx_CollapsiblePane, IsCollapsed);
	Gura_AssignMethod(wx_CollapsiblePane, IsExpanded);
	Gura_AssignMethod(wx_CollapsiblePane, Collapse);
	Gura_AssignMethod(wx_CollapsiblePane, Expand);
	Gura_AssignMethod(wx_CollapsiblePane, GetPane);
}

Gura_ImplementDescendantCreator(wx_CollapsiblePane)
{
	return new Object_wx_CollapsiblePane((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
