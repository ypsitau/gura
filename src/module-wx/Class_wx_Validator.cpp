//----------------------------------------------------------------------------
// wxValidator
// extracted from validatr.tex
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

Gura_DeclarePrivUserSymbol(Clone);
Gura_DeclarePrivUserSymbol(TransferFromWindow);
Gura_DeclarePrivUserSymbol(TransferToWindow);
Gura_DeclarePrivUserSymbol(Validate);

//----------------------------------------------------------------------------
// Class derivation
//----------------------------------------------------------------------------
class wx_Validator: public wxValidator, public GuraObjectObserver {
private:
	Gura::Signal _sig;
	Object_wx_Validator *_pObj;
public:
	inline wx_Validator() : wxValidator(), _sig(NULL), _pObj(NULL) {}
	//virtual wxObject* Clone();
	virtual bool TransferFromWindow();
	virtual bool TransferToWindow();
	//virtual bool Validate(wxWindow* parent);
	~wx_Validator();
	inline void AssocWithGura(Gura::Signal &sig, Object_wx_Validator *pObj) {
		_sig = sig, _pObj = pObj;
	}
	// virtual function of GuraObjectObserver
	virtual void GuraObjectDeleted();
};

wx_Validator::~wx_Validator()
{
	if (_pObj != NULL) _pObj->InvalidateEntity();
}

void wx_Validator::GuraObjectDeleted()
{
	_pObj = NULL;
}

bool wx_Validator::TransferFromWindow()
{
	bool evaluatedFlag;
	Value rtn = _pObj->EvalMethod(*_pObj, _sig,
		Gura_UserSymbol(TransferFromWindow), ValueList::Null, evaluatedFlag);
	if (_sig.IsSignalled()) {
		SetLogError(_sig);
		return false;
	}
	return rtn.GetBoolean();
}

bool wx_Validator::TransferToWindow()
{
	bool evaluatedFlag;
	Value rtn = _pObj->EvalMethod(*_pObj, _sig,
		Gura_UserSymbol(TransferToWindow), ValueList::Null, evaluatedFlag);
	if (_sig.IsSignalled()) {
		SetLogError(_sig);
		return false;
	}
	return rtn.GetBoolean();
}

//bool wx_Validator::Validate(wxWindow* parent);
//{
//	
//}

//----------------------------------------------------------------------------
// Gura interfaces for wxValidator
//----------------------------------------------------------------------------
Gura_DeclareFunction(Validator)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	SetClassToConstruct(Gura_UserClass(wx_Validator));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(Validator)
{
	if (!CheckWxReady(sig)) return Value::Null;
	wx_Validator *pEntity = new wx_Validator();
	Object_wx_Validator *pObj = Object_wx_Validator::GetThisObj(args);
	if (pObj == NULL) {
		pObj = new Object_wx_Validator(pEntity, pEntity, OwnerFalse);
		pEntity->AssocWithGura(sig, pObj);
		return ReturnValue(env, sig, args, Value(pObj));
	}
	pObj->SetEntity(pEntity, pEntity, OwnerFalse);
	pEntity->AssocWithGura(sig, pObj);
	return ReturnValue(env, sig, args, args.GetThis());
}

Gura_DeclareMethod(wx_Validator, Clone)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_Validator, Clone)
{
	Object_wx_Validator *pThis = Object_wx_Validator::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	wxObject *rtn = (wxObject *)pThis->GetEntity()->Clone();
	return ReturnValue(env, sig, args, Value(new Object_wx_Object(rtn, NULL, OwnerFalse)));
}

Gura_DeclareMethod(wx_Validator, GetWindow)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_Validator, GetWindow)
{
	Object_wx_Validator *pThis = Object_wx_Validator::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	wxWindow *rtn = (wxWindow *)pThis->GetEntity()->GetWindow();
	return ReturnValue(env, sig, args, Value(new Object_wx_Window(rtn, NULL, OwnerFalse)));
}

Gura_DeclareClassMethod(wx_Validator, IsSilent)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_Validator, IsSilent)
{
	bool rtn = wxValidator::IsSilent();
	return ReturnValue(env, sig, args, Value(rtn));
}


Gura_DeclareClassMethod(wx_Validator, SetBellOnError)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "doIt", VTYPE_boolean, OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_Validator, SetBellOnError)
{
	bool doIt = true;
	if (args.IsValid(0)) doIt = args.GetBoolean(0);
	wxValidator::SetBellOnError(doIt);
	return Value::Null;
}

Gura_DeclareMethod(wx_Validator, SetWindow)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "window", VTYPE_wx_Window, OCCUR_Once);
}

Gura_ImplementMethod(wx_Validator, SetWindow)
{
	Object_wx_Validator *pThis = Object_wx_Validator::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	wxWindow *window = Object_wx_Window::GetObject(args, 0)->GetEntity();
	pThis->GetEntity()->SetWindow(window);
	return Value::Null;
}

Gura_DeclareMethod(wx_Validator, TransferToWindow)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_Validator, TransferToWindow)
{
	Object_wx_Validator *pThis = Object_wx_Validator::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	bool rtn = pThis->GetEntity()->TransferToWindow();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_Validator, TransferToWindow_1)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_Validator, TransferToWindow_1)
{
	Object_wx_Validator *pThis = Object_wx_Validator::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	bool rtn = pThis->GetEntity()->TransferToWindow();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_Validator, Validate)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "parent", VTYPE_wx_Window, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_Validator, Validate)
{
	Object_wx_Validator *pThis = Object_wx_Validator::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	wxWindow *parent = Object_wx_Window::GetObject(args, 0)->GetEntity();
	bool rtn = pThis->GetEntity()->Validate(parent);
	return ReturnValue(env, sig, args, Value(rtn));
}

//----------------------------------------------------------------------------
// Object implementation for wxValidator
//----------------------------------------------------------------------------
Object_wx_Validator::~Object_wx_Validator()
{
}

Object *Object_wx_Validator::Clone() const
{
	return NULL;
}

String Object_wx_Validator::ToString(bool exprFlag)
{
	String rtn("<wx.Validator:");
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
// Class implementation for wxValidator
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_Validator)
{
	Gura_RealizeUserSymbol(Clone);
	Gura_RealizeUserSymbol(TransferFromWindow);
	Gura_RealizeUserSymbol(TransferToWindow);
	Gura_RealizeUserSymbol(Validate);
	Gura_AssignFunction(Validator);
	Gura_AssignMethod(wx_Validator, Clone);
	Gura_AssignMethod(wx_Validator, GetWindow);
	Gura_AssignMethod(wx_Validator, IsSilent);
	Gura_AssignMethod(wx_Validator, SetBellOnError);
	Gura_AssignMethod(wx_Validator, SetWindow);
	Gura_AssignMethod(wx_Validator, TransferToWindow);
	Gura_AssignMethod(wx_Validator, TransferToWindow_1);
	Gura_AssignMethod(wx_Validator, Validate);
}

Gura_ImplementDescendantCreator(wx_Validator)
{
	return new Object_wx_Validator((pClass == NULL)? this : pClass, NULL, NULL, OwnerFalse);
}

Gura_EndModuleScope(wx)
