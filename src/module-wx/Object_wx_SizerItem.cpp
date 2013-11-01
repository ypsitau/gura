//----------------------------------------------------------------------------
// wxSizerItem
// extracted from sizeritem.tex
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Class derivation
//----------------------------------------------------------------------------
class wx_SizerItem: public wxSizerItem, public GuraObjectObserver {
private:
	Gura::Signal _sig;
	Object_wx_SizerItem *_pObj;
public:
	inline wx_SizerItem(int width, int height, int proportion, int flag, int border, wxObject* userData) : wxSizerItem(width, height, proportion, flag, border, userData), _sig(NULL), _pObj(NULL) {}
	inline wx_SizerItem(wxWindow* window, const wxSizerFlags& flags) : wxSizerItem(window, flags), _sig(NULL), _pObj(NULL) {}
	inline wx_SizerItem(wxWindow* window, int proportion, int flag, int border, wxObject* userData) : wxSizerItem(window, proportion, flag, border, userData), _sig(NULL), _pObj(NULL) {}
	inline wx_SizerItem(wxSizer* window, const wxSizerFlags& flags) : wxSizerItem(window, flags), _sig(NULL), _pObj(NULL) {}
	inline wx_SizerItem(wxSizer* sizer, int proportion, int flag, int border, wxObject* userData) : wxSizerItem(sizer, proportion, flag, border, userData), _sig(NULL), _pObj(NULL) {}
	~wx_SizerItem();
	inline void AssocWithGura(Gura::Signal &sig, Object_wx_SizerItem *pObj) {
		_sig = sig, _pObj = pObj;
	}
	// virtual function of GuraObjectObserver
	virtual void GuraObjectDeleted();
};

wx_SizerItem::~wx_SizerItem()
{
	if (_pObj != NULL) _pObj->InvalidateEntity();
}

void wx_SizerItem::GuraObjectDeleted()
{
	_pObj = NULL;
}

//----------------------------------------------------------------------------
// Gura interfaces for wxSizerItem
//----------------------------------------------------------------------------
Gura_DeclareFunction(SizerItem)
{
	SetMode(RSLTMODE_Normal, FLAG_Map);
	SetClassToConstruct(Gura_UserClass(wx_SizerItem));
	DeclareArg(env, "width", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "height", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "proportion", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "flag", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "border", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "userData", VTYPE_wx_Object, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(SizerItem)
{
	if (!CheckWxReady(sig)) return Value::Null;
	int width = args.GetInt(0);
	int height = args.GetInt(1);
	int proportion = args.GetInt(2);
	int flag = args.GetInt(3);
	int border = args.GetInt(4);
	wxObject *userData = Object_wx_Object::GetObject(args, 5)->GetEntity();
	wx_SizerItem *pEntity = new wx_SizerItem(width, height, proportion, flag, border, userData);
	Object_wx_SizerItem *pObj = Object_wx_SizerItem::GetThisObj(args);
	if (pObj == NULL) {
		pObj = new Object_wx_SizerItem(pEntity, pEntity, OwnerFalse);
		pEntity->AssocWithGura(sig, pObj);
		return ReturnValue(env, sig, args, Value(pObj));
	}
	pObj->SetEntity(pEntity, pEntity, OwnerFalse);
	pEntity->AssocWithGura(sig, pObj);
	return ReturnValue(env, sig, args, args.GetThis());
}

Gura_DeclareFunction(SizerItem_1)
{
	SetMode(RSLTMODE_Normal, FLAG_Map);
	SetClassToConstruct(Gura_UserClass(wx_SizerItem));
	DeclareArg(env, "window", VTYPE_wx_Window, OCCUR_Once);
	DeclareArg(env, "flags", VTYPE_wx_SizerFlags, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(SizerItem_1)
{
	if (!CheckWxReady(sig)) return Value::Null;
	wxWindow *window = Object_wx_Window::GetObject(args, 0)->GetEntity();
	wxSizerFlags *flags = Object_wx_SizerFlags::GetObject(args, 1)->GetEntity();
	wx_SizerItem *pEntity = new wx_SizerItem(window, *flags);
	Object_wx_SizerItem *pObj = Object_wx_SizerItem::GetThisObj(args);
	if (pObj == NULL) {
		pObj = new Object_wx_SizerItem(pEntity, pEntity, OwnerFalse);
		pEntity->AssocWithGura(sig, pObj);
		return ReturnValue(env, sig, args, Value(pObj));
	}
	pObj->SetEntity(pEntity, pEntity, OwnerFalse);
	pEntity->AssocWithGura(sig, pObj);
	return ReturnValue(env, sig, args, args.GetThis());
}

Gura_DeclareFunction(SizerItem_2)
{
	SetMode(RSLTMODE_Normal, FLAG_Map);
	SetClassToConstruct(Gura_UserClass(wx_SizerItem));
	DeclareArg(env, "window", VTYPE_wx_Window, OCCUR_Once);
	DeclareArg(env, "proportion", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "flag", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "border", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "userData", VTYPE_wx_Object, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(SizerItem_2)
{
	if (!CheckWxReady(sig)) return Value::Null;
	wxWindow *window = Object_wx_Window::GetObject(args, 0)->GetEntity();
	int proportion = args.GetInt(1);
	int flag = args.GetInt(2);
	int border = args.GetInt(3);
	wxObject *userData = Object_wx_Object::GetObject(args, 4)->GetEntity();
	wx_SizerItem *pEntity = new wx_SizerItem(window, proportion, flag, border, userData);
	Object_wx_SizerItem *pObj = Object_wx_SizerItem::GetThisObj(args);
	if (pObj == NULL) {
		pObj = new Object_wx_SizerItem(pEntity, pEntity, OwnerFalse);
		pEntity->AssocWithGura(sig, pObj);
		return ReturnValue(env, sig, args, Value(pObj));
	}
	pObj->SetEntity(pEntity, pEntity, OwnerFalse);
	pEntity->AssocWithGura(sig, pObj);
	return ReturnValue(env, sig, args, args.GetThis());
}

Gura_DeclareFunction(SizerItem_3)
{
	SetMode(RSLTMODE_Normal, FLAG_Map);
	SetClassToConstruct(Gura_UserClass(wx_SizerItem));
	DeclareArg(env, "window", VTYPE_wx_Sizer, OCCUR_Once);
	DeclareArg(env, "flags", VTYPE_wx_SizerFlags, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(SizerItem_3)
{
	if (!CheckWxReady(sig)) return Value::Null;
	wxSizer *window = Object_wx_Sizer::GetObject(args, 0)->GetEntity();
	wxSizerFlags *flags = Object_wx_SizerFlags::GetObject(args, 1)->GetEntity();
	wx_SizerItem *pEntity = new wx_SizerItem(window, *flags);
	Object_wx_SizerItem *pObj = Object_wx_SizerItem::GetThisObj(args);
	if (pObj == NULL) {
		pObj = new Object_wx_SizerItem(pEntity, pEntity, OwnerFalse);
		pEntity->AssocWithGura(sig, pObj);
		return ReturnValue(env, sig, args, Value(pObj));
	}
	pObj->SetEntity(pEntity, pEntity, OwnerFalse);
	pEntity->AssocWithGura(sig, pObj);
	return ReturnValue(env, sig, args, args.GetThis());
}

Gura_DeclareFunction(SizerItem_4)
{
	SetMode(RSLTMODE_Normal, FLAG_Map);
	SetClassToConstruct(Gura_UserClass(wx_SizerItem));
	DeclareArg(env, "sizer", VTYPE_wx_Sizer, OCCUR_Once);
	DeclareArg(env, "proportion", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "flag", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "border", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "userData", VTYPE_wx_Object, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(SizerItem_4)
{
	if (!CheckWxReady(sig)) return Value::Null;
	wxSizer *sizer = Object_wx_Sizer::GetObject(args, 0)->GetEntity();
	int proportion = args.GetInt(1);
	int flag = args.GetInt(2);
	int border = args.GetInt(3);
	wxObject *userData = Object_wx_Object::GetObject(args, 4)->GetEntity();
	wx_SizerItem *pEntity = new wx_SizerItem(sizer, proportion, flag, border, userData);
	Object_wx_SizerItem *pObj = Object_wx_SizerItem::GetThisObj(args);
	if (pObj == NULL) {
		pObj = new Object_wx_SizerItem(pEntity, pEntity, OwnerFalse);
		pEntity->AssocWithGura(sig, pObj);
		return ReturnValue(env, sig, args, Value(pObj));
	}
	pObj->SetEntity(pEntity, pEntity, OwnerFalse);
	pEntity->AssocWithGura(sig, pObj);
	return ReturnValue(env, sig, args, args.GetThis());
}

Gura_DeclareMethod(wx_SizerItem, CalcMin)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_SizerItem, CalcMin)
{
	Object_wx_SizerItem *pThis = Object_wx_SizerItem::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	wxSize rtn = pThis->GetEntity()->CalcMin();
	return ReturnValue(env, sig, args, Value(new Object_wx_Size(new wxSize(rtn), NULL, OwnerTrue)));
}

Gura_DeclareMethod(wx_SizerItem, DeleteWindows)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_SizerItem, DeleteWindows)
{
	Object_wx_SizerItem *pThis = Object_wx_SizerItem::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->DeleteWindows();
	return Value::Null;
}

Gura_DeclareMethod(wx_SizerItem, DetachSizer)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_SizerItem, DetachSizer)
{
	Object_wx_SizerItem *pThis = Object_wx_SizerItem::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->DetachSizer();
	return Value::Null;
}

Gura_DeclareMethod(wx_SizerItem, GetBorder)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_SizerItem, GetBorder)
{
	Object_wx_SizerItem *pThis = Object_wx_SizerItem::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int rtn = pThis->GetEntity()->GetBorder();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_SizerItem, GetFlag)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_SizerItem, GetFlag)
{
	Object_wx_SizerItem *pThis = Object_wx_SizerItem::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int rtn = pThis->GetEntity()->GetFlag();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_SizerItem, GetMinSize)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_SizerItem, GetMinSize)
{
	Object_wx_SizerItem *pThis = Object_wx_SizerItem::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	wxSize rtn = pThis->GetEntity()->GetMinSize();
	return ReturnValue(env, sig, args, Value(new Object_wx_Size(new wxSize(rtn), NULL, OwnerTrue)));
}

Gura_DeclareMethod(wx_SizerItem, GetPosition)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_SizerItem, GetPosition)
{
	Object_wx_SizerItem *pThis = Object_wx_SizerItem::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	wxPoint rtn = pThis->GetEntity()->GetPosition();
	return ReturnValue(env, sig, args, Value(new Object_wx_Point(new wxPoint(rtn), NULL, OwnerTrue)));
}

Gura_DeclareMethod(wx_SizerItem, GetProportion)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_SizerItem, GetProportion)
{
	Object_wx_SizerItem *pThis = Object_wx_SizerItem::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int rtn = pThis->GetEntity()->GetProportion();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_SizerItem, GetRatio)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_SizerItem, GetRatio)
{
	Object_wx_SizerItem *pThis = Object_wx_SizerItem::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	float rtn = pThis->GetEntity()->GetRatio();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_SizerItem, GetRect)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_SizerItem, GetRect)
{
	Object_wx_SizerItem *pThis = Object_wx_SizerItem::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	wxRect rtn = pThis->GetEntity()->GetRect();
	return ReturnValue(env, sig, args, Value(new Object_wx_Rect(new wxRect(rtn), NULL, OwnerTrue)));
}

Gura_DeclareMethod(wx_SizerItem, GetSize)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_SizerItem, GetSize)
{
	Object_wx_SizerItem *pThis = Object_wx_SizerItem::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	wxSize rtn = pThis->GetEntity()->GetSize();
	return ReturnValue(env, sig, args, Value(new Object_wx_Size(new wxSize(rtn), NULL, OwnerTrue)));
}

Gura_DeclareMethod(wx_SizerItem, GetSizer)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_SizerItem, GetSizer)
{
	Object_wx_SizerItem *pThis = Object_wx_SizerItem::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	wxSizer *rtn = (wxSizer *)pThis->GetEntity()->GetSizer();
	return ReturnValue(env, sig, args, Value(new Object_wx_Sizer(rtn, NULL, OwnerFalse)));
}

Gura_DeclareMethod(wx_SizerItem, GetSpacer)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_SizerItem, GetSpacer)
{
	Object_wx_SizerItem *pThis = Object_wx_SizerItem::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	const wxSize &rtn = pThis->GetEntity()->GetSpacer();
	return ReturnValue(env, sig, args, Value(new Object_wx_Size(new wxSize(rtn), NULL, OwnerTrue)));
}

Gura_DeclareMethod(wx_SizerItem, GetUserData)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_SizerItem, GetUserData)
{
	Object_wx_SizerItem *pThis = Object_wx_SizerItem::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	wxObject *rtn = (wxObject *)pThis->GetEntity()->GetUserData();
	return ReturnValue(env, sig, args, Value(new Object_wx_Object(rtn, NULL, OwnerFalse)));
}

Gura_DeclareMethod(wx_SizerItem, GetWindow)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_SizerItem, GetWindow)
{
	Object_wx_SizerItem *pThis = Object_wx_SizerItem::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	wxWindow *rtn = (wxWindow *)pThis->GetEntity()->GetWindow();
	return ReturnValue(env, sig, args, Value(new Object_wx_Window(rtn, NULL, OwnerFalse)));
}

Gura_DeclareMethod(wx_SizerItem, IsSizer)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_SizerItem, IsSizer)
{
	Object_wx_SizerItem *pThis = Object_wx_SizerItem::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	bool rtn = pThis->GetEntity()->IsSizer();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_SizerItem, IsShown)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_SizerItem, IsShown)
{
	Object_wx_SizerItem *pThis = Object_wx_SizerItem::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	bool rtn = pThis->GetEntity()->IsShown();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_SizerItem, IsSpacer)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_SizerItem, IsSpacer)
{
	Object_wx_SizerItem *pThis = Object_wx_SizerItem::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	bool rtn = pThis->GetEntity()->IsSpacer();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_SizerItem, IsWindow)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_SizerItem, IsWindow)
{
	Object_wx_SizerItem *pThis = Object_wx_SizerItem::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	bool rtn = pThis->GetEntity()->IsWindow();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_SizerItem, SetBorder)
{
	SetMode(RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "border", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_SizerItem, SetBorder)
{
	Object_wx_SizerItem *pThis = Object_wx_SizerItem::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int border = args.GetInt(0);
	pThis->GetEntity()->SetBorder(border);
	return Value::Null;
}

Gura_DeclareMethod(wx_SizerItem, SetDimension)
{
	SetMode(RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "pos", VTYPE_wx_Point, OCCUR_Once);
	DeclareArg(env, "size", VTYPE_wx_Size, OCCUR_Once);
}

Gura_ImplementMethod(wx_SizerItem, SetDimension)
{
	Object_wx_SizerItem *pThis = Object_wx_SizerItem::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	wxPoint *pos = Object_wx_Point::GetObject(args, 0)->GetEntity();
	wxSize *size = Object_wx_Size::GetObject(args, 1)->GetEntity();
	pThis->GetEntity()->SetDimension(*pos, *size);
	return Value::Null;
}

Gura_DeclareMethod(wx_SizerItem, SetFlag)
{
	SetMode(RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "flag", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_SizerItem, SetFlag)
{
	Object_wx_SizerItem *pThis = Object_wx_SizerItem::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int flag = args.GetInt(0);
	pThis->GetEntity()->SetFlag(flag);
	return Value::Null;
}

Gura_DeclareMethod(wx_SizerItem, SetInitSize)
{
	SetMode(RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "x", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "y", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_SizerItem, SetInitSize)
{
	Object_wx_SizerItem *pThis = Object_wx_SizerItem::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int x = args.GetInt(0);
	int y = args.GetInt(1);
	pThis->GetEntity()->SetInitSize(x, y);
	return Value::Null;
}

Gura_DeclareMethod(wx_SizerItem, SetProportion)
{
	SetMode(RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "proportion", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_SizerItem, SetProportion)
{
	Object_wx_SizerItem *pThis = Object_wx_SizerItem::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int proportion = args.GetInt(0);
	pThis->GetEntity()->SetProportion(proportion);
	return Value::Null;
}

Gura_DeclareMethod(wx_SizerItem, SetRatio)
{
	SetMode(RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "width", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "height", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_SizerItem, SetRatio)
{
	Object_wx_SizerItem *pThis = Object_wx_SizerItem::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int width = args.GetInt(0);
	int height = args.GetInt(1);
	pThis->GetEntity()->SetRatio(width, height);
	return Value::Null;
}

Gura_DeclareMethod(wx_SizerItem, SetRatio_1)
{
	SetMode(RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "size", VTYPE_wx_Size, OCCUR_Once);
}

Gura_ImplementMethod(wx_SizerItem, SetRatio_1)
{
	Object_wx_SizerItem *pThis = Object_wx_SizerItem::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	wxSize *size = Object_wx_Size::GetObject(args, 0)->GetEntity();
	pThis->GetEntity()->SetRatio(*size);
	return Value::Null;
}

Gura_DeclareMethod(wx_SizerItem, SetRatio_2)
{
	SetMode(RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "ratio", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_SizerItem, SetRatio_2)
{
	Object_wx_SizerItem *pThis = Object_wx_SizerItem::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	float ratio = args.GetFloat(0);
	pThis->GetEntity()->SetRatio(ratio);
	return Value::Null;
}

Gura_DeclareMethod(wx_SizerItem, SetSizer)
{
	SetMode(RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "sizer", VTYPE_wx_Sizer, OCCUR_Once);
}

Gura_ImplementMethod(wx_SizerItem, SetSizer)
{
	Object_wx_SizerItem *pThis = Object_wx_SizerItem::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	wxSizer *sizer = Object_wx_Sizer::GetObject(args, 0)->GetEntity();
	pThis->GetEntity()->SetSizer(sizer);
	return Value::Null;
}

Gura_DeclareMethod(wx_SizerItem, SetSpacer)
{
	SetMode(RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "size", VTYPE_wx_Size, OCCUR_Once);
}

Gura_ImplementMethod(wx_SizerItem, SetSpacer)
{
	Object_wx_SizerItem *pThis = Object_wx_SizerItem::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	wxSize *size = Object_wx_Size::GetObject(args, 0)->GetEntity();
	pThis->GetEntity()->SetSpacer(*size);
	return Value::Null;
}

Gura_DeclareMethod(wx_SizerItem, SetWindow)
{
	SetMode(RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "window", VTYPE_wx_Window, OCCUR_Once);
}

Gura_ImplementMethod(wx_SizerItem, SetWindow)
{
	Object_wx_SizerItem *pThis = Object_wx_SizerItem::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	wxWindow *window = Object_wx_Window::GetObject(args, 0)->GetEntity();
	pThis->GetEntity()->SetWindow(window);
	return Value::Null;
}

Gura_DeclareMethod(wx_SizerItem, Show)
{
	SetMode(RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "show", VTYPE_boolean, OCCUR_Once);
}

Gura_ImplementMethod(wx_SizerItem, Show)
{
	Object_wx_SizerItem *pThis = Object_wx_SizerItem::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	bool show = args.GetBoolean(0);
	pThis->GetEntity()->Show(show);
	return Value::Null;
}

//----------------------------------------------------------------------------
// Object implementation for wxSizerItem
//----------------------------------------------------------------------------
Object_wx_SizerItem::~Object_wx_SizerItem()
{
}

Object *Object_wx_SizerItem::Clone() const
{
	return NULL;
}

String Object_wx_SizerItem::ToString(bool exprFlag)
{
	String rtn("<wx.SizerItem:");
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
// Class implementation for wxSizerItem
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_SizerItem)
{
	Gura_AssignFunction(SizerItem);
	Gura_AssignFunction(SizerItem_1);
	Gura_AssignFunction(SizerItem_2);
	Gura_AssignFunction(SizerItem_3);
	Gura_AssignFunction(SizerItem_4);
	Gura_AssignMethod(wx_SizerItem, CalcMin);
	Gura_AssignMethod(wx_SizerItem, DeleteWindows);
	Gura_AssignMethod(wx_SizerItem, DetachSizer);
	Gura_AssignMethod(wx_SizerItem, GetBorder);
	Gura_AssignMethod(wx_SizerItem, GetFlag);
	Gura_AssignMethod(wx_SizerItem, GetMinSize);
	Gura_AssignMethod(wx_SizerItem, GetPosition);
	Gura_AssignMethod(wx_SizerItem, GetProportion);
	Gura_AssignMethod(wx_SizerItem, GetRatio);
	Gura_AssignMethod(wx_SizerItem, GetRect);
	Gura_AssignMethod(wx_SizerItem, GetSize);
	Gura_AssignMethod(wx_SizerItem, GetSizer);
	Gura_AssignMethod(wx_SizerItem, GetSpacer);
	Gura_AssignMethod(wx_SizerItem, GetUserData);
	Gura_AssignMethod(wx_SizerItem, GetWindow);
	Gura_AssignMethod(wx_SizerItem, IsSizer);
	Gura_AssignMethod(wx_SizerItem, IsShown);
	Gura_AssignMethod(wx_SizerItem, IsSpacer);
	Gura_AssignMethod(wx_SizerItem, IsWindow);
	Gura_AssignMethod(wx_SizerItem, SetBorder);
	Gura_AssignMethod(wx_SizerItem, SetDimension);
	Gura_AssignMethod(wx_SizerItem, SetFlag);
	Gura_AssignMethod(wx_SizerItem, SetInitSize);
	Gura_AssignMethod(wx_SizerItem, SetProportion);
	Gura_AssignMethod(wx_SizerItem, SetRatio);
	Gura_AssignMethod(wx_SizerItem, SetRatio_1);
	Gura_AssignMethod(wx_SizerItem, SetRatio_2);
	Gura_AssignMethod(wx_SizerItem, SetSizer);
	Gura_AssignMethod(wx_SizerItem, SetSpacer);
	Gura_AssignMethod(wx_SizerItem, SetWindow);
	Gura_AssignMethod(wx_SizerItem, Show);
}

Gura_ImplementDescendantCreator(wx_SizerItem)
{
	return new Object_wx_SizerItem((pClass == NULL)? this : pClass, NULL, NULL, OwnerFalse);
}

Gura_EndModuleScope(wx)
