//----------------------------------------------------------------------------
// wxTextDropTarget
// extracted from txtdrptg.tex
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

Gura_DeclarePrivUserSymbol(OnDrop);
Gura_DeclarePrivUserSymbol(OnDropText);

//----------------------------------------------------------------------------
// Class derivation
//----------------------------------------------------------------------------
class wx_TextDropTarget: public wxTextDropTarget, public GuraObjectObserver {
private:
	Gura::Signal _sig;
	Object_wx_TextDropTarget *_pObj;
public:
	//inline wx_TextDropTarget() : wxTextDropTarget(), _sig(NULL), _pObj(NULL) {}
	~wx_TextDropTarget();
	virtual bool OnDrop(wxCoord x, wxCoord y);
	virtual bool OnDropText(wxCoord x, wxCoord y, const wxString& data);
	inline void AssocWithGura(Gura::Signal &sig, Object_wx_TextDropTarget *pObj) {
		_sig = sig, _pObj = pObj;
	}
	// virtual function of GuraObjectObserver
	virtual void GuraObjectDeleted();
};

wx_TextDropTarget::~wx_TextDropTarget()
{
	if (_pObj != NULL) _pObj->InvalidateEntity();
}

void wx_TextDropTarget::GuraObjectDeleted()
{
	_pObj = NULL;
}

bool wx_TextDropTarget::OnDrop(wxCoord x, wxCoord y)
{
	const Function *pFunc = Gura_LookupWxMethod(_pObj, OnDrop);
	if (pFunc == NULL) return wxTextDropTarget::OnDrop(x, y);
	Environment &env = *_pObj;
	ValueList valList;
	valList.push_back(Value(x));
	valList.push_back(Value(y));
	Value rtn = _pObj->EvalMethod(*_pObj, _sig, pFunc, valList);
	if (!CheckMethodResult(_sig, rtn, VTYPE_boolean)) return false;
	return rtn.GetBoolean();
}

bool wx_TextDropTarget::OnDropText(wxCoord x, wxCoord y, const wxString& data)
{
	const Function *pFunc = Gura_LookupWxMethod(_pObj, OnDropText);
	if (pFunc == NULL) return false;
	Environment &env = *_pObj;
	ValueList valList;
	valList.push_back(Value(x));
	valList.push_back(Value(y));
	valList.push_back(Value(data.ToUTF8()));
	Value rtn = _pObj->EvalMethod(*_pObj, _sig, pFunc, valList);
	if (!CheckMethodResult(_sig, rtn, VTYPE_boolean)) return false;
	return rtn.GetBoolean();
}
	
//----------------------------------------------------------------------------
// Gura interfaces for wxTextDropTarget
//----------------------------------------------------------------------------
Gura_DeclareFunction(TextDropTargetEmpty)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
#if 0
	SetClassToConstruct(Gura_UserClass(wx_TextDropTarget));
	DeclareBlock(OCCUR_ZeroOrOnce);
#endif
}

Gura_ImplementFunction(TextDropTargetEmpty)
{
	if (!CheckWxReady(sig)) return Value::Null;
#if 0
	wx_TextDropTarget *pEntity = new wx_TextDropTarget();
	Object_wx_TextDropTarget *pObj = Object_wx_TextDropTarget::GetThisObj(args);
	if (pObj == NULL) {
		pObj = new Object_wx_TextDropTarget(pEntity, pEntity, OwnerFalse);
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

Gura_DeclareMethod(wx_TextDropTarget, OnDrop)
{
	SetMode(RSLTMODE_Normal, FLAG_Map);
#if 0
	DeclareArg(env, "x", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "y", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "*data", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "size", VTYPE_number, OCCUR_Once);
#endif
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_TextDropTarget, OnDrop)
{
#if 0
	Object_wx_TextDropTarget *pThis = Object_wx_TextDropTarget::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	long x = args.GetLong(0);
	long y = args.GetLong(1);
	int *data = args.GetInt(2);
	size_t size = args.GetSizeT(3);
	bool rtn = pThis->GetEntity()->OnDrop(x, y, *data, size);
	return ReturnValue(env, sig, args, Value(rtn));
#endif
	SetError_NotImplemented(sig);
	return Value::Null;
}

Gura_DeclareMethod(wx_TextDropTarget, OnDropText)
{
	SetMode(RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "x", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "y", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "data", VTYPE_string, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_TextDropTarget, OnDropText)
{
	Object_wx_TextDropTarget *pThis = Object_wx_TextDropTarget::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	wxCoord x = static_cast<wxCoord>(args.GetInt(0));
	wxCoord y = static_cast<wxCoord>(args.GetInt(1));
	wxString data = wxString::FromUTF8(args.GetString(2));
	bool rtn = pThis->GetEntity()->OnDropText(x, y, data);
	return ReturnValue(env, sig, args, Value(rtn));
}

//----------------------------------------------------------------------------
// Object implementation for wxTextDropTarget
//----------------------------------------------------------------------------
Object_wx_TextDropTarget::~Object_wx_TextDropTarget()
{
}

Object *Object_wx_TextDropTarget::Clone() const
{
	return NULL;
}

String Object_wx_TextDropTarget::ToString(bool exprFlag)
{
	String rtn("<wx.TextDropTarget:");
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
// Class implementation for wxTextDropTarget
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_TextDropTarget)
{
	Gura_RealizeUserSymbol(OnDrop);
	Gura_RealizeUserSymbol(OnDropText);
	Gura_AssignFunction(TextDropTargetEmpty);
	Gura_AssignMethod(wx_TextDropTarget, OnDrop);
	Gura_AssignMethod(wx_TextDropTarget, OnDropText);
}

Gura_ImplementDescendantCreator(wx_TextDropTarget)
{
	return new Object_wx_TextDropTarget((pClass == NULL)? this : pClass, NULL, NULL, OwnerFalse);
}

Gura_EndModuleScope(wx)
