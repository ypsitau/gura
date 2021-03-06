//----------------------------------------------------------------------------
// wxAnimation
// extracted from animation.tex
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Class derivation
//----------------------------------------------------------------------------
class wx_Animation: public wxAnimation, public GuraObjectObserver {
private:
	//Gura::Signal *_pSig;
	Object_wx_Animation *_pObj;
public:
	inline wx_Animation() : wxAnimation(), _pObj(nullptr) {}
	inline wx_Animation(const wxAnimation& anim) : wxAnimation(anim), _pObj(nullptr) {}
	inline wx_Animation(const wxString& name, wxAnimationType type) : wxAnimation(name, type), _pObj(nullptr) {}
	~wx_Animation();
	inline void AssocWithGura(Object_wx_Animation *pObj) {
		_pObj = pObj;
	}
	// virtual function of GuraObjectObserver
	virtual void GuraObjectDeleted();
};

wx_Animation::~wx_Animation()
{
	if (_pObj != nullptr) _pObj->InvalidateEntity();
}

void wx_Animation::GuraObjectDeleted()
{
	_pObj = nullptr;
}

//----------------------------------------------------------------------------
// Gura interfaces for wxAnimation
//----------------------------------------------------------------------------
Gura_DeclareFunction(AnimationEmpty)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	SetClassToConstruct(Gura_UserClass(wx_Animation));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(AnimationEmpty)
{
	Signal &sig = env.GetSignal();
	if (!CheckWxReady(sig)) return Value::Nil;
	wx_Animation *pEntity = new wx_Animation();
	Object_wx_Animation *pObj = Object_wx_Animation::GetObjectThis(arg);
	if (pObj == nullptr) {
		pObj = new Object_wx_Animation(pEntity, pEntity, OwnerFalse);
		pEntity->AssocWithGura(pObj);
		return ReturnValue(env, arg, Value(pObj));
	}
	pObj->SetEntity(pEntity, pEntity, OwnerFalse);
	pEntity->AssocWithGura(pObj);
	return ReturnValue(env, arg, arg.GetValueThis());
}

Gura_DeclareFunction(Animation)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	SetClassToConstruct(Gura_UserClass(wx_Animation));
	DeclareArg(env, "anim", VTYPE_wx_Animation, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(Animation)
{
	Signal &sig = env.GetSignal();
	if (!CheckWxReady(sig)) return Value::Nil;
	wxAnimation *anim = Object_wx_Animation::GetObject(arg, 0)->GetEntity();
	wx_Animation *pEntity = new wx_Animation(*anim);
	Object_wx_Animation *pObj = Object_wx_Animation::GetObjectThis(arg);
	if (pObj == nullptr) {
		pObj = new Object_wx_Animation(pEntity, pEntity, OwnerFalse);
		pEntity->AssocWithGura(pObj);
		return ReturnValue(env, arg, Value(pObj));
	}
	pObj->SetEntity(pEntity, pEntity, OwnerFalse);
	pEntity->AssocWithGura(pObj);
	return ReturnValue(env, arg, arg.GetValueThis());
}

Gura_DeclareFunction(Animation_1)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	SetClassToConstruct(Gura_UserClass(wx_Animation));
	DeclareArg(env, "name", VTYPE_string, OCCUR_Once);
	DeclareArg(env, "type", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(Animation_1)
{
	Signal &sig = env.GetSignal();
	if (!CheckWxReady(sig)) return Value::Nil;
	wxString name = wxString::FromUTF8(arg.GetString(0));
	wxAnimationType type = wxANIMATION_TYPE_ANY;
	if (arg.IsValid(1)) type = static_cast<wxAnimationType>(arg.GetInt(1));
	wx_Animation *pEntity = new wx_Animation(name, type);
	Object_wx_Animation *pObj = Object_wx_Animation::GetObjectThis(arg);
	if (pObj == nullptr) {
		pObj = new Object_wx_Animation(pEntity, pEntity, OwnerFalse);
		pEntity->AssocWithGura(pObj);
		return ReturnValue(env, arg, Value(pObj));
	}
	pObj->SetEntity(pEntity, pEntity, OwnerFalse);
	pEntity->AssocWithGura(pObj);
	return ReturnValue(env, arg, arg.GetValueThis());
}

Gura_DeclareMethod(wx_Animation, GetDelay)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "i", VTYPE_number, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_Animation, GetDelay)
{
	Signal &sig = env.GetSignal();
	Object_wx_Animation *pThis = Object_wx_Animation::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	unsigned i = arg.GetInt(0);
	int rtn = pThis->GetEntity()->GetDelay(i);
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_Animation, GetFrameCount)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_Animation, GetFrameCount)
{
	Signal &sig = env.GetSignal();
	Object_wx_Animation *pThis = Object_wx_Animation::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	unsigned rtn = pThis->GetEntity()->GetFrameCount();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_Animation, GetFrame)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "i", VTYPE_number, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_Animation, GetFrame)
{
	Signal &sig = env.GetSignal();
	Object_wx_Animation *pThis = Object_wx_Animation::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	unsigned i = arg.GetInt(0);
	wxImage rtn = pThis->GetEntity()->GetFrame(i);
	return ReturnValue(env, arg, Value(new Object_wx_Image(new wxImage(rtn), nullptr, OwnerTrue)));
}

Gura_DeclareMethod(wx_Animation, GetSize)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_Animation, GetSize)
{
	Signal &sig = env.GetSignal();
	Object_wx_Animation *pThis = Object_wx_Animation::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxSize rtn = pThis->GetEntity()->GetSize();
	return ReturnValue(env, arg, Value(new Object_wx_Size(new wxSize(rtn), nullptr, OwnerTrue)));
}

Gura_DeclareMethod(wx_Animation, IsOk)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_Animation, IsOk)
{
	Signal &sig = env.GetSignal();
	Object_wx_Animation *pThis = Object_wx_Animation::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	bool rtn = pThis->GetEntity()->IsOk();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_Animation, Load)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "stream", VTYPE_wx_InputStream, OCCUR_Once);
	DeclareArg(env, "type", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_Animation, Load)
{
	Signal &sig = env.GetSignal();
	Object_wx_Animation *pThis = Object_wx_Animation::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxInputStream *stream = Object_wx_InputStream::GetObject(arg, 0)->GetEntity();
	wxAnimationType type = wxANIMATION_TYPE_ANY;
	if (arg.IsValid(1)) type = static_cast<wxAnimationType>(arg.GetInt(1));
	bool rtn = pThis->GetEntity()->Load(*stream, type);
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_Animation, LoadFile)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "name", VTYPE_string, OCCUR_Once);
	DeclareArg(env, "type", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_Animation, LoadFile)
{
	Signal &sig = env.GetSignal();
	Object_wx_Animation *pThis = Object_wx_Animation::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxString name = wxString::FromUTF8(arg.GetString(0));
	wxAnimationType type = wxANIMATION_TYPE_ANY;
	if (arg.IsValid(1)) type = static_cast<wxAnimationType>(arg.GetInt(1));
	bool rtn = pThis->GetEntity()->LoadFile(name, type);
	return ReturnValue(env, arg, Value(rtn));
}

//----------------------------------------------------------------------------
// Object implementation for wxAnimation
//----------------------------------------------------------------------------
Object_wx_Animation::~Object_wx_Animation()
{
}

Object *Object_wx_Animation::Clone() const
{
	return nullptr;
}

String Object_wx_Animation::ToString(bool exprFlag)
{
	String rtn("<wx.Animation:");
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
// Class implementation for wxAnimation
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_Animation)
{
	Gura_AssignFunction(AnimationEmpty);
	Gura_AssignFunction(Animation);
	Gura_AssignFunction(Animation_1);
	Gura_AssignMethod(wx_Animation, GetDelay);
	Gura_AssignMethod(wx_Animation, GetFrameCount);
	Gura_AssignMethod(wx_Animation, GetFrame);
	Gura_AssignMethod(wx_Animation, GetSize);
	Gura_AssignMethod(wx_Animation, IsOk);
	Gura_AssignMethod(wx_Animation, Load);
	Gura_AssignMethod(wx_Animation, LoadFile);
}

Gura_ImplementDescendantCreator(wx_Animation)
{
	return new Object_wx_Animation((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
