//----------------------------------------------------------------------------
// wxStaticBoxSizer
// extracted from sbsizer.tex
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Class derivation
//----------------------------------------------------------------------------
class wx_StaticBoxSizer: public wxStaticBoxSizer, public GuraObjectObserver {
private:
	//Gura::Signal *_pSig;
	Object_wx_StaticBoxSizer *_pObj;
public:
	inline wx_StaticBoxSizer(wxStaticBox* box, int orient) : wxStaticBoxSizer(box, orient), _pObj(nullptr) {}
	inline wx_StaticBoxSizer(int orient, wxWindow *parent, const wxString& label) : wxStaticBoxSizer(orient, parent, label), _pObj(nullptr) {}
	~wx_StaticBoxSizer();
	inline void AssocWithGura(Object_wx_StaticBoxSizer *pObj) {
		_pObj = pObj;
	}
	// virtual function of GuraObjectObserver
	virtual void GuraObjectDeleted();
};

wx_StaticBoxSizer::~wx_StaticBoxSizer()
{
	if (_pObj != nullptr) _pObj->InvalidateEntity();
}

void wx_StaticBoxSizer::GuraObjectDeleted()
{
	_pObj = nullptr;
}

//----------------------------------------------------------------------------
// Gura interfaces for wxStaticBoxSizer
//----------------------------------------------------------------------------
Gura_DeclareFunction(StaticBoxSizer)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	SetClassToConstruct(Gura_UserClass(wx_StaticBoxSizer));
	DeclareArg(env, "box", VTYPE_wx_StaticBox, OCCUR_Once);
	DeclareArg(env, "orient", VTYPE_number, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(StaticBoxSizer)
{
	Signal &sig = env.GetSignal();
	if (!CheckWxReady(sig)) return Value::Nil;
	wxStaticBox *box = Object_wx_StaticBox::GetObject(arg, 0)->GetEntity();
	int orient = arg.GetInt(1);
	wx_StaticBoxSizer *pEntity = new wx_StaticBoxSizer(box, orient);
	Object_wx_StaticBoxSizer *pObj = Object_wx_StaticBoxSizer::GetObjectThis(arg);
	if (pObj == nullptr) {
		pObj = new Object_wx_StaticBoxSizer(pEntity, pEntity, OwnerFalse);
		pEntity->AssocWithGura(pObj);
		return ReturnValue(env, arg, Value(pObj));
	}
	pObj->SetEntity(pEntity, pEntity, OwnerFalse);
	pEntity->AssocWithGura(pObj);
	return ReturnValue(env, arg, arg.GetValueThis());
}

Gura_DeclareFunction(StaticBoxSizerAuto)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	SetClassToConstruct(Gura_UserClass(wx_StaticBoxSizer));
	DeclareArg(env, "orient", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "parent", VTYPE_wx_Window, OCCUR_Once);
	DeclareArg(env, "label", VTYPE_string, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(StaticBoxSizerAuto)
{
	Signal &sig = env.GetSignal();
	if (!CheckWxReady(sig)) return Value::Nil;
	int orient = arg.GetInt(0);
	wxWindow *parent = Object_wx_Window::GetObject(arg, 1)->GetEntity();
	wxString label = wxEmptyString;
	if (arg.IsValid(2)) label = wxString::FromUTF8(arg.GetString(2));
	wx_StaticBoxSizer *pEntity = new wx_StaticBoxSizer(orient, parent, label);
	Object_wx_StaticBoxSizer *pObj = Object_wx_StaticBoxSizer::GetObjectThis(arg);
	if (pObj == nullptr) {
		pObj = new Object_wx_StaticBoxSizer(pEntity, pEntity, OwnerFalse);
		pEntity->AssocWithGura(pObj);
		return ReturnValue(env, arg, Value(pObj));
	}
	pObj->SetEntity(pEntity, pEntity, OwnerFalse);
	pEntity->AssocWithGura(pObj);
	return ReturnValue(env, arg, arg.GetValueThis());
}

Gura_DeclareMethod(wx_StaticBoxSizer, GetStaticBox)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_StaticBoxSizer, GetStaticBox)
{
	Signal &sig = env.GetSignal();
	Object_wx_StaticBoxSizer *pThis = Object_wx_StaticBoxSizer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxStaticBox *rtn = (wxStaticBox *)pThis->GetEntity()->GetStaticBox();
	return ReturnValue(env, arg, Value(new Object_wx_StaticBox(rtn, nullptr, OwnerFalse)));
}

//----------------------------------------------------------------------------
// Object implementation for wxStaticBoxSizer
//----------------------------------------------------------------------------
Object_wx_StaticBoxSizer::~Object_wx_StaticBoxSizer()
{
}

Object *Object_wx_StaticBoxSizer::Clone() const
{
	return nullptr;
}

String Object_wx_StaticBoxSizer::ToString(bool exprFlag)
{
	String rtn("<wx.StaticBoxSizer:");
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
// Class implementation for wxStaticBoxSizer
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_StaticBoxSizer)
{
	Gura_AssignFunction(StaticBoxSizer);
	Gura_AssignFunction(StaticBoxSizerAuto);
	Gura_AssignMethod(wx_StaticBoxSizer, GetStaticBox);
}

Gura_ImplementDescendantCreator(wx_StaticBoxSizer)
{
	return new Object_wx_StaticBoxSizer((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
