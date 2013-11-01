//----------------------------------------------------------------------------
// wxStaticBitmap
// extracted from statbmp.tex
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

Gura_DeclarePrivUserSymbol(SetBitmap);
Gura_DeclarePrivUserSymbol(SetIcon);

//----------------------------------------------------------------------------
// Class derivation
//----------------------------------------------------------------------------
class wx_StaticBitmap: public wxStaticBitmap, public GuraObjectObserver {
private:
	Gura::Signal _sig;
	Object_wx_StaticBitmap *_pObj;
public:
	inline wx_StaticBitmap() : wxStaticBitmap(), _sig(NULL), _pObj(NULL) {}
	inline wx_StaticBitmap(wxWindow* parent, wxWindowID id, const wxBitmap& label, const wxPoint& pos, const wxSize& size, long style, const wxString& name) : wxStaticBitmap(parent, id, label, pos, size, style, name), _sig(NULL), _pObj(NULL) {}
	inline wx_StaticBitmap(wxWindow* parent, wxWindowID id, const wxIcon& label, const wxPoint& pos, const wxSize& size, long style, const wxString& name) : wxStaticBitmap(parent, id, label, pos, size, style, name), _sig(NULL), _pObj(NULL) {}
	//virtual void SetBitmap(const wxBitmap& label);
	//virtual void SetIcon(const wxIcon& label);
	~wx_StaticBitmap();
	inline void AssocWithGura(Gura::Signal &sig, Object_wx_StaticBitmap *pObj) {
		_sig = sig, _pObj = pObj;
	}
	// virtual function of GuraObjectObserver
	virtual void GuraObjectDeleted();
};

wx_StaticBitmap::~wx_StaticBitmap()
{
	if (_pObj != NULL) _pObj->InvalidateEntity();
}

void wx_StaticBitmap::GuraObjectDeleted()
{
	_pObj = NULL;
}

//----------------------------------------------------------------------------
// Gura interfaces for wxStaticBitmap
//----------------------------------------------------------------------------
Gura_DeclareFunction(StaticBitmapEmpty)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	SetClassToConstruct(Gura_UserClass(wx_StaticBitmap));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(StaticBitmapEmpty)
{
	if (!CheckWxReady(sig)) return Value::Null;
	wx_StaticBitmap *pEntity = new wx_StaticBitmap();
	Object_wx_StaticBitmap *pObj = Object_wx_StaticBitmap::GetThisObj(args);
	if (pObj == NULL) {
		pObj = new Object_wx_StaticBitmap(pEntity, pEntity, OwnerFalse);
		pEntity->AssocWithGura(sig, pObj);
		return ReturnValue(env, sig, args, Value(pObj));
	}
	pObj->SetEntity(pEntity, pEntity, OwnerFalse);
	pEntity->AssocWithGura(sig, pObj);
	return ReturnValue(env, sig, args, args.GetThis());
}

Gura_DeclareFunction(StaticBitmap)
{
	SetMode(RSLTMODE_Normal, FLAG_Map);
	SetClassToConstruct(Gura_UserClass(wx_StaticBitmap));
	DeclareArg(env, "parent", VTYPE_wx_Window, OCCUR_Once);
	DeclareArg(env, "id", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "label", VTYPE_any, OCCUR_Once);
	DeclareArg(env, "pos", VTYPE_wx_Point, OCCUR_ZeroOrOnce);
	DeclareArg(env, "size", VTYPE_wx_Size, OCCUR_ZeroOrOnce);
	DeclareArg(env, "style", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareArg(env, "name", VTYPE_string, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(StaticBitmap)
{
	if (!CheckWxReady(sig)) return Value::Null;
	wxWindow *parent = Object_wx_Window::GetObject(args, 0)->GetEntity();
	wxWindowID id = static_cast<wxWindowID>(args.GetInt(1));
	wxPoint *pos = (wxPoint *)(&wxDefaultPosition);
	if (args.IsValid(3)) pos = Object_wx_Point::GetObject(args, 3)->GetEntity();
	wxSize *size = (wxSize *)(&wxDefaultSize);
	if (args.IsValid(4)) size = Object_wx_Size::GetObject(args, 4)->GetEntity();
	long style = 0;
	if (args.IsValid(5)) style = args.GetLong(5);
	wxString name = wxT("staticBitmap");
	if (args.IsValid(6)) name = wxString::FromUTF8(args.GetString(6));
	wx_StaticBitmap *pEntity = NULL;
	if (args.IsInstanceOf(2, VTYPE_wx_Bitmap)) {
		wxBitmap *label = Object_wx_Bitmap::GetObject(args, 2)->GetEntity();
		pEntity = new wx_StaticBitmap(parent, id, *label, *pos, *size, style, name);
	} else if (args.IsInstanceOf(2, VTYPE_wx_Icon)) {
		wxIcon *label = Object_wx_Icon::GetObject(args, 2)->GetEntity();
		pEntity = new wx_StaticBitmap(parent, id, *label, *pos, *size, style, name);
	} else {
		SetError_ArgumentTypeByIndex(sig, args, 2);
		return Value::Null;
	}
	Object_wx_StaticBitmap *pObj = Object_wx_StaticBitmap::GetThisObj(args);
	if (pObj == NULL) {
		pObj = new Object_wx_StaticBitmap(pEntity, pEntity, OwnerFalse);
		pEntity->AssocWithGura(sig, pObj);
		return ReturnValue(env, sig, args, Value(pObj));
	}
	pObj->SetEntity(pEntity, pEntity, OwnerFalse);
	pEntity->AssocWithGura(sig, pObj);
	return ReturnValue(env, sig, args, args.GetThis());
}

Gura_DeclareMethod(wx_StaticBitmap, Create)
{
	SetMode(RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "parent", VTYPE_wx_Window, OCCUR_Once);
	DeclareArg(env, "id", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "label", VTYPE_wx_Bitmap, OCCUR_Once);
	DeclareArg(env, "pos", VTYPE_wx_Point, OCCUR_ZeroOrOnce);
	DeclareArg(env, "size", VTYPE_wx_Size, OCCUR_ZeroOrOnce);
	DeclareArg(env, "style", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareArg(env, "name", VTYPE_string, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_StaticBitmap, Create)
{
	Object_wx_StaticBitmap *pThis = Object_wx_StaticBitmap::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	wxWindow *parent = Object_wx_Window::GetObject(args, 0)->GetEntity();
	wxWindowID id = static_cast<wxWindowID>(args.GetInt(1));
	wxBitmap *label = Object_wx_Bitmap::GetObject(args, 2)->GetEntity();
	wxPoint *pos = (wxPoint *)(&wxDefaultPosition);
	if (args.IsValid(3)) pos = Object_wx_Point::GetObject(args, 3)->GetEntity();
	wxSize *size = (wxSize *)(&wxDefaultSize);
	if (args.IsValid(4)) size = Object_wx_Size::GetObject(args, 4)->GetEntity();
	long style = 0;
	if (args.IsValid(5)) style = args.GetLong(5);
	wxString name = wxT("staticBitmap");
	if (args.IsValid(6)) name = wxString::FromUTF8(args.GetString(6));
	bool rtn = pThis->GetEntity()->Create(parent, id, *label, *pos, *size, style, name);
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StaticBitmap, GetBitmap)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_StaticBitmap, GetBitmap)
{
	Object_wx_StaticBitmap *pThis = Object_wx_StaticBitmap::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	wxBitmap rtn = pThis->GetEntity()->GetBitmap();
	return ReturnValue(env, sig, args, Value(new Object_wx_Bitmap(new wxBitmap(rtn), NULL, OwnerTrue)));
}

Gura_DeclareMethod(wx_StaticBitmap, GetIcon)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_StaticBitmap, GetIcon)
{
	Object_wx_StaticBitmap *pThis = Object_wx_StaticBitmap::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	wxIcon rtn = pThis->GetEntity()->GetIcon();
	return ReturnValue(env, sig, args, Value(new Object_wx_Icon(new wxIcon(rtn), NULL, OwnerTrue)));
}

Gura_DeclareMethod(wx_StaticBitmap, SetBitmap)
{
	SetMode(RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "label", VTYPE_wx_Bitmap, OCCUR_Once);
}

Gura_ImplementMethod(wx_StaticBitmap, SetBitmap)
{
	Object_wx_StaticBitmap *pThis = Object_wx_StaticBitmap::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	wxBitmap *label = Object_wx_Bitmap::GetObject(args, 0)->GetEntity();
	pThis->GetEntity()->SetBitmap(*label);
	return Value::Null;
}

Gura_DeclareMethod(wx_StaticBitmap, SetIcon)
{
	SetMode(RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "label", VTYPE_wx_Icon, OCCUR_Once);
}

Gura_ImplementMethod(wx_StaticBitmap, SetIcon)
{
	Object_wx_StaticBitmap *pThis = Object_wx_StaticBitmap::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	wxIcon *label = Object_wx_Icon::GetObject(args, 0)->GetEntity();
	pThis->GetEntity()->SetIcon(*label);
	return Value::Null;
}

//----------------------------------------------------------------------------
// Object implementation for wxStaticBitmap
//----------------------------------------------------------------------------
Object_wx_StaticBitmap::~Object_wx_StaticBitmap()
{
}

Object *Object_wx_StaticBitmap::Clone() const
{
	return NULL;
}

String Object_wx_StaticBitmap::ToString(bool exprFlag)
{
	String rtn("<wx.StaticBitmap:");
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
// Class implementation for wxStaticBitmap
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_StaticBitmap)
{
	Gura_RealizeUserSymbol(SetBitmap);
	Gura_RealizeUserSymbol(SetIcon);
	Gura_AssignFunction(StaticBitmapEmpty);
	Gura_AssignFunction(StaticBitmap);
	Gura_AssignMethod(wx_StaticBitmap, Create);
	Gura_AssignMethod(wx_StaticBitmap, GetBitmap);
	Gura_AssignMethod(wx_StaticBitmap, GetIcon);
	Gura_AssignMethod(wx_StaticBitmap, SetBitmap);
	Gura_AssignMethod(wx_StaticBitmap, SetIcon);
}

Gura_ImplementDescendantCreator(wx_StaticBitmap)
{
	return new Object_wx_StaticBitmap((pClass == NULL)? this : pClass, NULL, NULL, OwnerFalse);
}

Gura_EndModuleScope(wx)
