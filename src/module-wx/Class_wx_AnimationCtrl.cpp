//----------------------------------------------------------------------------
// wxAnimationCtrl
// extracted from animatctrl.tex
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Class derivation
//----------------------------------------------------------------------------
class wx_AnimationCtrl: public wxAnimationCtrl, public GuraObjectObserver {
private:
	//Gura::Signal *_pSig;
	Object_wx_AnimationCtrl *_pObj;
public:
	inline wx_AnimationCtrl(wxWindow * parent, wxWindowID id, const wxAnimation& anim, const wxPoint& pos, const wxSize& size, long style, const wxString& name) : wxAnimationCtrl(parent, id, anim, pos, size, style, name), _pObj(nullptr) {}
	~wx_AnimationCtrl();
	inline void AssocWithGura(Object_wx_AnimationCtrl *pObj) {
		_pObj = pObj;
	}
	// virtual function of GuraObjectObserver
	virtual void GuraObjectDeleted();
};

wx_AnimationCtrl::~wx_AnimationCtrl()
{
	if (_pObj != nullptr) _pObj->InvalidateEntity();
}

void wx_AnimationCtrl::GuraObjectDeleted()
{
	_pObj = nullptr;
}

//----------------------------------------------------------------------------
// Gura interfaces for wxAnimationCtrl
//----------------------------------------------------------------------------
Gura_DeclareFunction(AnimationCtrl)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	SetClassToConstruct(Gura_UserClass(wx_AnimationCtrl));
	DeclareArg(env, "parent", VTYPE_wx_Window, OCCUR_Once);
	DeclareArg(env, "id", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "anim", VTYPE_wx_Animation, OCCUR_Once);
	DeclareArg(env, "pos", VTYPE_wx_Point, OCCUR_ZeroOrOnce);
	DeclareArg(env, "size", VTYPE_wx_Size, OCCUR_ZeroOrOnce);
	DeclareArg(env, "style", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareArg(env, "name", VTYPE_string, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(AnimationCtrl)
{
	Signal &sig = env.GetSignal();
	if (!CheckWxReady(sig)) return Value::Nil;
	wxWindow *parent = Object_wx_Window::GetObject(arg, 0)->GetEntity();
	wxWindowID id = static_cast<wxWindowID>(arg.GetInt(1));
	wxAnimation *anim = Object_wx_Animation::GetObject(arg, 2)->GetEntity();
	wxPoint *pos = (wxPoint *)(&wxDefaultPosition);
	if (arg.IsValid(3)) pos = Object_wx_Point::GetObject(arg, 3)->GetEntity();
	wxSize *size = (wxSize *)(&wxDefaultSize);
	if (arg.IsValid(4)) size = Object_wx_Size::GetObject(arg, 4)->GetEntity();
	long style = wxAC_DEFAULT_STYLE;
	if (arg.IsValid(5)) style = arg.GetLong(5);
	wxString name = wxT("animationctrl");
	if (arg.IsValid(6)) name = wxString::FromUTF8(arg.GetString(6));
	wx_AnimationCtrl *pEntity = new wx_AnimationCtrl(parent, id, *anim, *pos, *size, style, name);
	Object_wx_AnimationCtrl *pObj = Object_wx_AnimationCtrl::GetObjectThis(arg);
	if (pObj == nullptr) {
		pObj = new Object_wx_AnimationCtrl(pEntity, pEntity, OwnerFalse);
		pEntity->AssocWithGura(pObj);
		return ReturnValue(env, arg, Value(pObj));
	}
	pObj->SetEntity(pEntity, pEntity, OwnerFalse);
	pEntity->AssocWithGura(pObj);
	return ReturnValue(env, arg, arg.GetValueThis());
}

Gura_DeclareMethod(wx_AnimationCtrl, Create)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "parent", VTYPE_wx_Window, OCCUR_Once);
	DeclareArg(env, "id", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "anim", VTYPE_wx_Animation, OCCUR_Once);
	DeclareArg(env, "pos", VTYPE_wx_Point, OCCUR_ZeroOrOnce);
	DeclareArg(env, "size", VTYPE_wx_Size, OCCUR_ZeroOrOnce);
	DeclareArg(env, "style", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareArg(env, "name", VTYPE_string, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_AnimationCtrl, Create)
{
	Signal &sig = env.GetSignal();
	Object_wx_AnimationCtrl *pThis = Object_wx_AnimationCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxWindow *parent = Object_wx_Window::GetObject(arg, 0)->GetEntity();
	wxWindowID id = static_cast<wxWindowID>(arg.GetInt(1));
	wxAnimation *anim = Object_wx_Animation::GetObject(arg, 2)->GetEntity();
	wxPoint *pos = (wxPoint *)(&wxDefaultPosition);
	if (arg.IsValid(3)) pos = Object_wx_Point::GetObject(arg, 3)->GetEntity();
	wxSize *size = (wxSize *)(&wxDefaultSize);
	if (arg.IsValid(4)) size = Object_wx_Size::GetObject(arg, 4)->GetEntity();
	long style = wxAC_DEFAULT_STYLE;
	if (arg.IsValid(5)) style = arg.GetLong(5);
	wxString name = wxT("animationctrl");
	if (arg.IsValid(6)) name = wxString::FromUTF8(arg.GetString(6));
	bool rtn = pThis->GetEntity()->Create(parent, id, *anim, *pos, *size, style, name);
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_AnimationCtrl, GetAnimation)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_AnimationCtrl, GetAnimation)
{
	Signal &sig = env.GetSignal();
	Object_wx_AnimationCtrl *pThis = Object_wx_AnimationCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxAnimation rtn = pThis->GetEntity()->GetAnimation();
	return ReturnValue(env, arg, Value(new Object_wx_Animation(new wxAnimation(rtn), nullptr, OwnerTrue)));
}

Gura_DeclareMethod(wx_AnimationCtrl, GetInactiveBitmap)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_AnimationCtrl, GetInactiveBitmap)
{
	Signal &sig = env.GetSignal();
	Object_wx_AnimationCtrl *pThis = Object_wx_AnimationCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxBitmap rtn = pThis->GetEntity()->GetInactiveBitmap();
	return ReturnValue(env, arg, Value(new Object_wx_Bitmap(new wxBitmap(rtn), nullptr, OwnerTrue)));
}

Gura_DeclareMethod(wx_AnimationCtrl, IsPlaying)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_AnimationCtrl, IsPlaying)
{
	Signal &sig = env.GetSignal();
	Object_wx_AnimationCtrl *pThis = Object_wx_AnimationCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	bool rtn = pThis->GetEntity()->IsPlaying();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_AnimationCtrl, LoadFile)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "file", VTYPE_string, OCCUR_Once);
	DeclareArg(env, "animType", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_AnimationCtrl, LoadFile)
{
	Signal &sig = env.GetSignal();
	Object_wx_AnimationCtrl *pThis = Object_wx_AnimationCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxString file = wxString::FromUTF8(arg.GetString(0));
	wxAnimationType animType = wxANIMATION_TYPE_ANY;
	if (arg.IsValid(1)) animType = static_cast<wxAnimationType>(arg.GetInt(1));
	bool rtn = pThis->GetEntity()->LoadFile(file, animType);
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_AnimationCtrl, Play)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_AnimationCtrl, Play)
{
	Signal &sig = env.GetSignal();
	Object_wx_AnimationCtrl *pThis = Object_wx_AnimationCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	bool rtn = pThis->GetEntity()->Play();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_AnimationCtrl, SetAnimation)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "anim", VTYPE_wx_Animation, OCCUR_Once);
}

Gura_ImplementMethod(wx_AnimationCtrl, SetAnimation)
{
	Signal &sig = env.GetSignal();
	Object_wx_AnimationCtrl *pThis = Object_wx_AnimationCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxAnimation *anim = Object_wx_Animation::GetObject(arg, 0)->GetEntity();
	pThis->GetEntity()->SetAnimation(*anim);
	return Value::Nil;
}

Gura_DeclareMethod(wx_AnimationCtrl, SetInactiveBitmap)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "bmp", VTYPE_wx_Bitmap, OCCUR_Once);
}

Gura_ImplementMethod(wx_AnimationCtrl, SetInactiveBitmap)
{
	Signal &sig = env.GetSignal();
	Object_wx_AnimationCtrl *pThis = Object_wx_AnimationCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxBitmap *bmp = Object_wx_Bitmap::GetObject(arg, 0)->GetEntity();
	pThis->GetEntity()->SetInactiveBitmap(*bmp);
	return Value::Nil;
}

Gura_DeclareMethod(wx_AnimationCtrl, Stop)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_AnimationCtrl, Stop)
{
	Signal &sig = env.GetSignal();
	Object_wx_AnimationCtrl *pThis = Object_wx_AnimationCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	pThis->GetEntity()->Stop();
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Object implementation for wxAnimationCtrl
//----------------------------------------------------------------------------
Object_wx_AnimationCtrl::~Object_wx_AnimationCtrl()
{
}

Object *Object_wx_AnimationCtrl::Clone() const
{
	return nullptr;
}

String Object_wx_AnimationCtrl::ToString(bool exprFlag)
{
	String rtn("<wx.AnimationCtrl:");
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
// Class implementation for wxAnimationCtrl
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_AnimationCtrl)
{
	Gura_AssignFunction(AnimationCtrl);
	Gura_AssignMethod(wx_AnimationCtrl, Create);
	Gura_AssignMethod(wx_AnimationCtrl, GetAnimation);
	Gura_AssignMethod(wx_AnimationCtrl, GetInactiveBitmap);
	Gura_AssignMethod(wx_AnimationCtrl, IsPlaying);
	Gura_AssignMethod(wx_AnimationCtrl, LoadFile);
	Gura_AssignMethod(wx_AnimationCtrl, Play);
	Gura_AssignMethod(wx_AnimationCtrl, SetAnimation);
	Gura_AssignMethod(wx_AnimationCtrl, SetInactiveBitmap);
	Gura_AssignMethod(wx_AnimationCtrl, Stop);
}

Gura_ImplementDescendantCreator(wx_AnimationCtrl)
{
	return new Object_wx_AnimationCtrl((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
