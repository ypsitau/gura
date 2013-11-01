//----------------------------------------------------------------------------
// wxMultiChoiceDialog
// extracted from mltchdlg.tex
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Class derivation
//----------------------------------------------------------------------------
class wx_MultiChoiceDialog: public wxMultiChoiceDialog, public GuraObjectObserver {
private:
	Gura::Signal _sig;
	Object_wx_MultiChoiceDialog *_pObj;
public:
	//inline wx_MultiChoiceDialog(wxWindow* parent, const wxString& message, const wxString& caption, int n, const wxString* choices, long style, const wxPoint& pos) : wxMultiChoiceDialog(parent, message, caption, n, choices, style, pos), _sig(NULL), _pObj(NULL) {}
	inline wx_MultiChoiceDialog(wxWindow* parent, const wxString& message, const wxString& caption, const wxArrayString& choices, long style, const wxPoint& pos) : wxMultiChoiceDialog(parent, message, caption, choices, style, pos), _sig(NULL), _pObj(NULL) {}
	~wx_MultiChoiceDialog();
	inline void AssocWithGura(Gura::Signal &sig, Object_wx_MultiChoiceDialog *pObj) {
		_sig = sig, _pObj = pObj;
	}
	// virtual function of GuraObjectObserver
	virtual void GuraObjectDeleted();
};

wx_MultiChoiceDialog::~wx_MultiChoiceDialog()
{
	if (_pObj != NULL) _pObj->InvalidateEntity();
}

void wx_MultiChoiceDialog::GuraObjectDeleted()
{
	_pObj = NULL;
}

//----------------------------------------------------------------------------
// Gura interfaces for wxMultiChoiceDialog
//----------------------------------------------------------------------------
Gura_DeclareFunction(MultiChoiceDialog)
{
	SetMode(RSLTMODE_Normal, FLAG_Map);
#if 0
	SetClassToConstruct(Gura_UserClass(wx_MultiChoiceDialog));
	DeclareArg(env, "parent", VTYPE_wx_Window, OCCUR_Once, FLAG_Nil);
	DeclareArg(env, "message", VTYPE_string, OCCUR_Once);
	DeclareArg(env, "caption", VTYPE_string, OCCUR_Once);
	DeclareArg(env, "n", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "choices", VTYPE_string, OCCUR_Once);
	DeclareArg(env, "style", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareArg(env, "pos", VTYPE_wx_Point, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
#endif
}

Gura_ImplementFunction(MultiChoiceDialog)
{
	if (!CheckWxReady(sig)) return Value::Null;
#if 0
	wxWindow *parent = args.IsValid(0)?
			Object_wx_Window::GetObject(args, 0)->GetEntity() : NULL;
	wxString message = wxString::FromUTF8(args.GetString(1));
	wxString caption = wxString::FromUTF8(args.GetString(2));
	int n = args.GetInt(3);
	wxString choices = wxString::FromUTF8(args.GetString(4));
	long style = wxCHOICEDLG_STYLE;
	if (args.IsValid(5)) style = args.GetLong(5);
	wxPoint *pos = (wxPoint *)(&wxDefaultPosition);
	if (args.IsValid(6)) pos = Object_wx_Point::GetObject(args, 6)->GetEntity();
	wx_MultiChoiceDialog *pEntity = new wx_MultiChoiceDialog(parent, message, caption, n, choices, style, *pos);
	Object_wx_MultiChoiceDialog *pObj = Object_wx_MultiChoiceDialog::GetThisObj(args);
	if (pObj == NULL) {
		pObj = new Object_wx_MultiChoiceDialog(pEntity, pEntity, OwnerFalse);
		pEntity->AssocWithGura(sig, pObj);
		return ReturnValue(env, sig, args, Value(pObj));
	}
	pObj->SetEntity(pEntity, pEntity, OwnerFalse);
	pEntity->AssocWithGura(sig, pObj);
	return ReturnValue(env, sig, args, args.GetThis());
#endif
	SetError_NotImplemented(sig);
	return Value::Null;
}

Gura_DeclareFunction(MultiChoiceDialog_1)
{
	SetMode(RSLTMODE_Normal, FLAG_Map);
	SetClassToConstruct(Gura_UserClass(wx_MultiChoiceDialog));
	DeclareArg(env, "parent", VTYPE_wx_Window, OCCUR_Once, FLAG_Nil);
	DeclareArg(env, "message", VTYPE_string, OCCUR_Once);
	DeclareArg(env, "caption", VTYPE_string, OCCUR_Once);
	DeclareArg(env, "choices", VTYPE_string, OCCUR_Once, FLAG_List);
	DeclareArg(env, "style", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareArg(env, "pos", VTYPE_wx_Point, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(MultiChoiceDialog_1)
{
	if (!CheckWxReady(sig)) return Value::Null;
	wxWindow *parent = args.IsValid(0)?
			Object_wx_Window::GetObject(args, 0)->GetEntity() : NULL;
	wxString message = wxString::FromUTF8(args.GetString(1));
	wxString caption = wxString::FromUTF8(args.GetString(2));
	std::auto_ptr<wxArrayString> choices(CreateArrayString(args.GetList(3)));
	long style = wxCHOICEDLG_STYLE;
	if (args.IsValid(4)) style = args.GetLong(4);
	wxPoint *pos = (wxPoint *)(&wxDefaultPosition);
	if (args.IsValid(5)) pos = Object_wx_Point::GetObject(args, 5)->GetEntity();
	wx_MultiChoiceDialog *pEntity = new wx_MultiChoiceDialog(parent, message, caption, *choices, style, *pos);
	Object_wx_MultiChoiceDialog *pObj = Object_wx_MultiChoiceDialog::GetThisObj(args);
	if (pObj == NULL) {
		pObj = new Object_wx_MultiChoiceDialog(pEntity, pEntity, OwnerFalse);
		pEntity->AssocWithGura(sig, pObj);
		return ReturnValue(env, sig, args, Value(pObj));
	}
	pObj->SetEntity(pEntity, pEntity, OwnerFalse);
	pEntity->AssocWithGura(sig, pObj);
	return ReturnValue(env, sig, args, args.GetThis());
}

Gura_DeclareMethod(wx_MultiChoiceDialog, GetSelections)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_MultiChoiceDialog, GetSelections)
{
	Object_wx_MultiChoiceDialog *pThis = Object_wx_MultiChoiceDialog::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	wxArrayInt rtn = pThis->GetEntity()->GetSelections();
	return ReturnValue(env, sig, args, ArrayIntToValue(env, rtn));
}

Gura_DeclareMethod(wx_MultiChoiceDialog, SetSelections)
{
	SetMode(RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "selections", VTYPE_number, OCCUR_Once, FLAG_List);
}

Gura_ImplementMethod(wx_MultiChoiceDialog, SetSelections)
{
	Object_wx_MultiChoiceDialog *pThis = Object_wx_MultiChoiceDialog::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	std::auto_ptr<wxArrayInt> selections(CreateArrayInt(args.GetList(0)));
	pThis->GetEntity()->SetSelections(*selections);
	return Value::Null;
}

Gura_DeclareMethod(wx_MultiChoiceDialog, ShowModal)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_MultiChoiceDialog, ShowModal)
{
	Object_wx_MultiChoiceDialog *pThis = Object_wx_MultiChoiceDialog::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int rtn = pThis->GetEntity()->ShowModal();
	return ReturnValue(env, sig, args, Value(rtn));
}

//----------------------------------------------------------------------------
// Object implementation for wxMultiChoiceDialog
//----------------------------------------------------------------------------
Object_wx_MultiChoiceDialog::~Object_wx_MultiChoiceDialog()
{
}

Object *Object_wx_MultiChoiceDialog::Clone() const
{
	return NULL;
}

String Object_wx_MultiChoiceDialog::ToString(bool exprFlag)
{
	String rtn("<wx.MultiChoiceDialog:");
	if (GetEntity() == NULL) {
		rtn += "invalid>";
	} else {
		char buff[64];
		::sprintf(buff, "%p>", GetEntity());
		rtn += buff;
	}
	return rtn;
}

//----------------------------------------------------------------------------
// Class implementation for wxMultiChoiceDialog
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_MultiChoiceDialog)
{
	Gura_AssignFunction(MultiChoiceDialog);
	Gura_AssignFunction(MultiChoiceDialog_1);
	Gura_AssignMethod(wx_MultiChoiceDialog, GetSelections);
	Gura_AssignMethod(wx_MultiChoiceDialog, SetSelections);
	Gura_AssignMethod(wx_MultiChoiceDialog, ShowModal);
}

Gura_ImplementDescendantCreator(wx_MultiChoiceDialog)
{
	return new Object_wx_MultiChoiceDialog((pClass == NULL)? this : pClass, NULL, NULL, OwnerFalse);
}

Gura_EndModuleScope(wx)
