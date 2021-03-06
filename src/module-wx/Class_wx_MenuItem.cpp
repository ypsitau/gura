//----------------------------------------------------------------------------
// wxMenuItem
// extracted from menuitem.tex
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Class derivation
//----------------------------------------------------------------------------
class wx_MenuItem: public wxMenuItem, public GuraObjectObserver {
private:
	//Gura::Signal *_pSig;
	Object_wx_MenuItem *_pObj;
public:
	inline wx_MenuItem(wxMenu* parentMenu, int id, const wxString& text, const wxString& helpString, wxItemKind kind, wxMenu* subMenu) : wxMenuItem(parentMenu, id, text, helpString, kind, subMenu), _pObj(nullptr) {}
	~wx_MenuItem();
	inline void AssocWithGura(Object_wx_MenuItem *pObj) {
		_pObj = pObj;
	}
	// virtual function of GuraObjectObserver
	virtual void GuraObjectDeleted();
};

wx_MenuItem::~wx_MenuItem()
{
	if (_pObj != nullptr) _pObj->InvalidateEntity();
}

void wx_MenuItem::GuraObjectDeleted()
{
	_pObj = nullptr;
}

//----------------------------------------------------------------------------
// Gura interfaces for wxMenuItem
//----------------------------------------------------------------------------
Gura_DeclareFunction(MenuItem)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	SetClassToConstruct(Gura_UserClass(wx_MenuItem));
	DeclareArg(env, "parentMenu", VTYPE_wx_Menu, OCCUR_ZeroOrOnce);
	DeclareArg(env, "id", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareArg(env, "text", VTYPE_string, OCCUR_ZeroOrOnce);
	DeclareArg(env, "helpString", VTYPE_string, OCCUR_ZeroOrOnce);
	DeclareArg(env, "kind", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareArg(env, "subMenu", VTYPE_wx_Menu, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(MenuItem)
{
	Signal &sig = env.GetSignal();
	if (!CheckWxReady(sig)) return Value::Nil;
	wxMenu *parentMenu = (wxMenu *)(nullptr);
	if (arg.IsValid(0)) parentMenu = Object_wx_Menu::GetObject(arg, 0)->GetEntity();
	int id = wxID_SEPARATOR;
	if (arg.IsValid(1)) id = arg.GetInt(1);
	wxString text = wxT("");
	if (arg.IsValid(2)) text = wxString::FromUTF8(arg.GetString(2));
	wxString helpString = wxT("");
	if (arg.IsValid(3)) helpString = wxString::FromUTF8(arg.GetString(3));
	wxItemKind kind = wxITEM_NORMAL;
	if (arg.IsValid(4)) kind = static_cast<wxItemKind>(arg.GetInt(4));
	wxMenu *subMenu = (wxMenu *)(nullptr);
	if (arg.IsValid(5)) subMenu = Object_wx_Menu::GetObject(arg, 5)->GetEntity();
	wx_MenuItem *pEntity = new wx_MenuItem(parentMenu, id, text, helpString, kind, subMenu);
	Object_wx_MenuItem *pObj = Object_wx_MenuItem::GetObjectThis(arg);
	if (pObj == nullptr) {
		pObj = new Object_wx_MenuItem(pEntity, pEntity, OwnerFalse);
		pEntity->AssocWithGura(pObj);
		return ReturnValue(env, arg, Value(pObj));
	}
	pObj->SetEntity(pEntity, pEntity, OwnerFalse);
	pEntity->AssocWithGura(pObj);
	return ReturnValue(env, arg, arg.GetValueThis());
}

Gura_DeclareMethod(wx_MenuItem, Check)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "check", VTYPE_boolean, OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_MenuItem, Check)
{
	Signal &sig = env.GetSignal();
	Object_wx_MenuItem *pThis = Object_wx_MenuItem::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	bool check = true;
	if (arg.IsValid(0)) check = arg.GetBoolean(0);
	pThis->GetEntity()->Check(check);
	return Value::Nil;
}

Gura_DeclareMethod(wx_MenuItem, Enable)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "enable", VTYPE_boolean, OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_MenuItem, Enable)
{
	Signal &sig = env.GetSignal();
	Object_wx_MenuItem *pThis = Object_wx_MenuItem::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	bool enable = true;
	if (arg.IsValid(0)) enable = arg.GetBoolean(0);
	pThis->GetEntity()->Enable(enable);
	return Value::Nil;
}

Gura_DeclareMethod(wx_MenuItem, GetAccel)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_MenuItem, GetAccel)
{
	Signal &sig = env.GetSignal();
	Object_wx_MenuItem *pThis = Object_wx_MenuItem::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxAcceleratorEntry *rtn = pThis->GetEntity()->GetAccel();
	Value value;
	if (rtn != nullptr) value = Value(new Object_wx_AcceleratorEntry(rtn, nullptr, OwnerFalse));
	return ReturnValue(env, arg, value);
}

Gura_DeclareMethod(wx_MenuItem, GetBackgroundColour)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_MenuItem, GetBackgroundColour)
{
	Signal &sig = env.GetSignal();
#if defined(__WXMSW__)
	Object_wx_MenuItem *pThis = Object_wx_MenuItem::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxColour &rtn = pThis->GetEntity()->GetBackgroundColour();
	return ReturnValue(env, arg, Value(new Object_wx_Colour(new wxColour(rtn), nullptr, OwnerTrue)));
#else
	SetError_MSWOnly(sig);
	return Value::Nil;
#endif	
}

Gura_DeclareMethod(wx_MenuItem, GetBitmap)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "checked", VTYPE_boolean, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_MenuItem, GetBitmap)
{
	Signal &sig = env.GetSignal();
#if defined(__WXMSW__)
	Object_wx_MenuItem *pThis = Object_wx_MenuItem::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	bool checked = true;
	if (arg.IsValid(0)) checked = arg.GetBoolean(0);
	const wxBitmap &rtn = pThis->GetEntity()->GetBitmap(checked);
	return ReturnValue(env, arg, Value(new Object_wx_Bitmap(new wxBitmap(rtn), nullptr, OwnerTrue)));
#else
	SetError_MSWOnly(sig);
	return Value::Nil;
#endif	
}

Gura_DeclareMethod(wx_MenuItem, GetFont)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_MenuItem, GetFont)
{
	Signal &sig = env.GetSignal();
#if defined(__WXMSW__)
	Object_wx_MenuItem *pThis = Object_wx_MenuItem::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxFont &rtn = pThis->GetEntity()->GetFont();
	return ReturnValue(env, arg, Value(new Object_wx_Font(new wxFont(rtn), nullptr, OwnerTrue)));
#else
	SetError_MSWOnly(sig);
	return Value::Nil;
#endif	
}

Gura_DeclareMethod(wx_MenuItem, GetHelp)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_MenuItem, GetHelp)
{
	Signal &sig = env.GetSignal();
	Object_wx_MenuItem *pThis = Object_wx_MenuItem::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxString rtn = pThis->GetEntity()->GetHelp();
	return ReturnValue(env, arg, Value(static_cast<const char *>(rtn.ToUTF8())));
}

Gura_DeclareMethod(wx_MenuItem, GetId)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_MenuItem, GetId)
{
	Signal &sig = env.GetSignal();
	Object_wx_MenuItem *pThis = Object_wx_MenuItem::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	int rtn = pThis->GetEntity()->GetId();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_MenuItem, GetItemLabel)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_MenuItem, GetItemLabel)
{
	Signal &sig = env.GetSignal();
	Object_wx_MenuItem *pThis = Object_wx_MenuItem::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxString rtn = pThis->GetEntity()->GetItemLabel();
	return ReturnValue(env, arg, Value(static_cast<const char *>(rtn.ToUTF8())));
}

Gura_DeclareMethod(wx_MenuItem, GetItemLabelText)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_MenuItem, GetItemLabelText)
{
	Signal &sig = env.GetSignal();
	Object_wx_MenuItem *pThis = Object_wx_MenuItem::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxString rtn = pThis->GetEntity()->GetItemLabelText();
	return ReturnValue(env, arg, Value(static_cast<const char *>(rtn.ToUTF8())));
}

Gura_DeclareMethod(wx_MenuItem, GetKind)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_MenuItem, GetKind)
{
	Signal &sig = env.GetSignal();
	Object_wx_MenuItem *pThis = Object_wx_MenuItem::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxItemKind rtn = pThis->GetEntity()->GetKind();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_MenuItem, GetLabel)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_MenuItem, GetLabel)
{
	Signal &sig = env.GetSignal();
#if 0
	Object_wx_MenuItem *pThis = Object_wx_MenuItem::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxString rtn = pThis->GetEntity()->GetLabel();
	return ReturnValue(env, arg, Value(static_cast<const char *>(rtn.ToUTF8())));
#endif
	SetError_Obsolete(sig);
	return Value::Nil;
}

Gura_DeclareClassMethod(wx_MenuItem, GetLabelText)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "text", VTYPE_string, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementClassMethod(wx_MenuItem, GetLabelText)
{
	Signal &sig = env.GetSignal();
	if (!CheckWxReady(sig)) return Value::Nil;
	wxString text = wxString::FromUTF8(arg.GetString(0));
	wxString rtn = wxMenuItem::GetLabelText(text);
	return ReturnValue(env, arg, Value(static_cast<const char *>(rtn.ToUTF8())));
}

Gura_DeclareClassMethod(wx_MenuItem, GetLabelFromText)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "text", VTYPE_string, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementClassMethod(wx_MenuItem, GetLabelFromText)
{
	Signal &sig = env.GetSignal();
#if 0
	if (!CheckWxReady(sig)) return Value::Nil;
	wxString text = wxString::FromUTF8(arg.GetString(0));
	wxString rtn = wxMenuItem::GetLabelFromText(text);
	return ReturnValue(env, arg, Value(static_cast<const char *>(rtn.ToUTF8())));
#endif
	SetError_Obsolete(sig);
	return Value::Nil;
}

Gura_DeclareMethod(wx_MenuItem, GetMarginWidth)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_MenuItem, GetMarginWidth)
{
	Signal &sig = env.GetSignal();
#if defined(__WXMSW__)
	Object_wx_MenuItem *pThis = Object_wx_MenuItem::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	int rtn = pThis->GetEntity()->GetMarginWidth();
	return ReturnValue(env, arg, Value(rtn));
#else
	SetError_MSWOnly(sig);
	return Value::Nil;
#endif	
}

Gura_DeclareMethod(wx_MenuItem, GetMenu)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_MenuItem, GetMenu)
{
	Signal &sig = env.GetSignal();
	Object_wx_MenuItem *pThis = Object_wx_MenuItem::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxMenu *rtn = (wxMenu *)pThis->GetEntity()->GetMenu();
	return ReturnValue(env, arg, Value(new Object_wx_Menu(rtn, nullptr, OwnerFalse)));
}

Gura_DeclareMethod(wx_MenuItem, GetName)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_MenuItem, GetName)
{
	Signal &sig = env.GetSignal();
#if 0
	Object_wx_MenuItem *pThis = Object_wx_MenuItem::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxString rtn = pThis->GetEntity()->GetName();
	return ReturnValue(env, arg, Value(static_cast<const char *>(rtn.ToUTF8())));
#endif
	SetError_NotImplemented(sig);
	return Value::Nil;
}

Gura_DeclareMethod(wx_MenuItem, GetText)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_MenuItem, GetText)
{
	Signal &sig = env.GetSignal();
#if 0
	Object_wx_MenuItem *pThis = Object_wx_MenuItem::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxString rtn = pThis->GetEntity()->GetText();
	return ReturnValue(env, arg, Value(static_cast<const char *>(rtn.ToUTF8())));
#endif
	SetError_Obsolete(sig);
	return Value::Nil;
}

Gura_DeclareMethod(wx_MenuItem, GetSubMenu)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_MenuItem, GetSubMenu)
{
	Signal &sig = env.GetSignal();
	Object_wx_MenuItem *pThis = Object_wx_MenuItem::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxMenu *rtn = (wxMenu *)pThis->GetEntity()->GetSubMenu();
	return ReturnValue(env, arg, Value(new Object_wx_Menu(rtn, nullptr, OwnerFalse)));
}

Gura_DeclareMethod(wx_MenuItem, GetTextColour)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_MenuItem, GetTextColour)
{
	Signal &sig = env.GetSignal();
#if defined(__WXMSW__)
	Object_wx_MenuItem *pThis = Object_wx_MenuItem::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxColour &rtn = pThis->GetEntity()->GetTextColour();
	return ReturnValue(env, arg, Value(new Object_wx_Colour(new wxColour(rtn), nullptr, OwnerTrue)));
#else
	SetError_MSWOnly(sig);
	return Value::Nil;
#endif	
}

Gura_DeclareMethod(wx_MenuItem, IsCheckable)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_MenuItem, IsCheckable)
{
	Signal &sig = env.GetSignal();
	Object_wx_MenuItem *pThis = Object_wx_MenuItem::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	bool rtn = pThis->GetEntity()->IsCheckable();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_MenuItem, IsChecked)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_MenuItem, IsChecked)
{
	Signal &sig = env.GetSignal();
	Object_wx_MenuItem *pThis = Object_wx_MenuItem::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	bool rtn = pThis->GetEntity()->IsChecked();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_MenuItem, IsEnabled)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_MenuItem, IsEnabled)
{
	Signal &sig = env.GetSignal();
	Object_wx_MenuItem *pThis = Object_wx_MenuItem::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	bool rtn = pThis->GetEntity()->IsEnabled();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_MenuItem, IsSeparator)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_MenuItem, IsSeparator)
{
	Signal &sig = env.GetSignal();
	Object_wx_MenuItem *pThis = Object_wx_MenuItem::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	bool rtn = pThis->GetEntity()->IsSeparator();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_MenuItem, IsSubMenu)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_MenuItem, IsSubMenu)
{
	Signal &sig = env.GetSignal();
	Object_wx_MenuItem *pThis = Object_wx_MenuItem::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	bool rtn = pThis->GetEntity()->IsSubMenu();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_MenuItem, SetBackgroundColour)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "colour", VTYPE_wx_Colour, OCCUR_Once);
}

Gura_ImplementMethod(wx_MenuItem, SetBackgroundColour)
{
	Signal &sig = env.GetSignal();
#if defined(__WXMSW__)
	Object_wx_MenuItem *pThis = Object_wx_MenuItem::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxColour *colour = Object_wx_Colour::GetObject(arg, 0)->GetEntity();
	pThis->GetEntity()->SetBackgroundColour(*colour);
	return Value::Nil;
#else
	SetError_MSWOnly(sig);
	return Value::Nil;
#endif	
}

Gura_DeclareMethod(wx_MenuItem, SetBitmap)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "bmp", VTYPE_wx_Bitmap, OCCUR_Once);
}

Gura_ImplementMethod(wx_MenuItem, SetBitmap)
{
	Signal &sig = env.GetSignal();
	Object_wx_MenuItem *pThis = Object_wx_MenuItem::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxBitmap *bmp = Object_wx_Bitmap::GetObject(arg, 0)->GetEntity();
	pThis->GetEntity()->SetBitmap(*bmp);
	return Value::Nil;
}

Gura_DeclareMethod(wx_MenuItem, SetBitmaps)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "checked", VTYPE_wx_Bitmap, OCCUR_Once);
	DeclareArg(env, "unchecked", VTYPE_wx_Bitmap, OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_MenuItem, SetBitmaps)
{
	Signal &sig = env.GetSignal();
#if defined(__WXMSW__)
	Object_wx_MenuItem *pThis = Object_wx_MenuItem::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxBitmap *checked = Object_wx_Bitmap::GetObject(arg, 0)->GetEntity();
	wxBitmap *unchecked = (wxBitmap *)(&wxNullBitmap);
	if (arg.IsValid(1)) unchecked = Object_wx_Bitmap::GetObject(arg, 1)->GetEntity();
	pThis->GetEntity()->SetBitmaps(*checked, *unchecked);
	return Value::Nil;
#else
	SetError_MSWOnly(sig);
	return Value::Nil;
#endif	
}

Gura_DeclareMethod(wx_MenuItem, SetFont)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "font", VTYPE_wx_Font, OCCUR_Once);
}

Gura_ImplementMethod(wx_MenuItem, SetFont)
{
	Signal &sig = env.GetSignal();
#if defined(__WXMSW__)
	Object_wx_MenuItem *pThis = Object_wx_MenuItem::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxFont *font = Object_wx_Font::GetObject(arg, 0)->GetEntity();
	pThis->GetEntity()->SetFont(*font);
	return Value::Nil;
#else
	SetError_MSWOnly(sig);
	return Value::Nil;
#endif	
}

Gura_DeclareMethod(wx_MenuItem, SetHelp)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "helpString", VTYPE_string, OCCUR_Once);
}

Gura_ImplementMethod(wx_MenuItem, SetHelp)
{
	Signal &sig = env.GetSignal();
	Object_wx_MenuItem *pThis = Object_wx_MenuItem::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxString helpString = wxString::FromUTF8(arg.GetString(0));
	pThis->GetEntity()->SetHelp(helpString);
	return Value::Nil;
}

Gura_DeclareMethod(wx_MenuItem, SetItemLabel)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "label", VTYPE_string, OCCUR_Once);
}

Gura_ImplementMethod(wx_MenuItem, SetItemLabel)
{
	Signal &sig = env.GetSignal();
	Object_wx_MenuItem *pThis = Object_wx_MenuItem::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxString label = wxString::FromUTF8(arg.GetString(0));
	pThis->GetEntity()->SetItemLabel(label);
	return Value::Nil;
}

Gura_DeclareMethod(wx_MenuItem, SetMarginWidth)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "width", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_MenuItem, SetMarginWidth)
{
	Signal &sig = env.GetSignal();
#if defined(__WXMSW__)
	Object_wx_MenuItem *pThis = Object_wx_MenuItem::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	int width = arg.GetInt(0);
	pThis->GetEntity()->SetMarginWidth(width);
	return Value::Nil;
#else
	SetError_MSWOnly(sig);
	return Value::Nil;
#endif	
}

Gura_DeclareMethod(wx_MenuItem, SetMenu)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "menu", VTYPE_wx_Menu, OCCUR_Once);
}

Gura_ImplementMethod(wx_MenuItem, SetMenu)
{
	Signal &sig = env.GetSignal();
	Object_wx_MenuItem *pThis = Object_wx_MenuItem::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxMenu *menu = Object_wx_Menu::GetObject(arg, 0)->GetEntity();
	pThis->GetEntity()->SetMenu(menu);
	return Value::Nil;
}

Gura_DeclareMethod(wx_MenuItem, SetSubMenu)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "menu", VTYPE_wx_Menu, OCCUR_Once);
}

Gura_ImplementMethod(wx_MenuItem, SetSubMenu)
{
	Signal &sig = env.GetSignal();
	Object_wx_MenuItem *pThis = Object_wx_MenuItem::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxMenu *menu = Object_wx_Menu::GetObject(arg, 0)->GetEntity();
	pThis->GetEntity()->SetSubMenu(menu);
	return Value::Nil;
}

Gura_DeclareMethod(wx_MenuItem, SetText)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "text", VTYPE_string, OCCUR_Once);
}

Gura_ImplementMethod(wx_MenuItem, SetText)
{
	Signal &sig = env.GetSignal();
#if 0
	Object_wx_MenuItem *pThis = Object_wx_MenuItem::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxString text = wxString::FromUTF8(arg.GetString(0));
	pThis->GetEntity()->SetText(text);
	return Value::Nil;
#endif
	SetError_Obsolete(sig);
	return Value::Nil;
}

Gura_DeclareMethod(wx_MenuItem, SetTextColour)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "colour", VTYPE_wx_Colour, OCCUR_Once);
}

Gura_ImplementMethod(wx_MenuItem, SetTextColour)
{
	Signal &sig = env.GetSignal();
#if defined(__WXMSW__)
	Object_wx_MenuItem *pThis = Object_wx_MenuItem::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxColour *colour = Object_wx_Colour::GetObject(arg, 0)->GetEntity();
	pThis->GetEntity()->SetTextColour(*colour);
	return Value::Nil;
#else
	SetError_MSWOnly(sig);
	return Value::Nil;
#endif	
}

Gura_DeclareMethod(wx_MenuItem, Toggle)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
}

Gura_ImplementMethod(wx_MenuItem, Toggle)
{
	Signal &sig = env.GetSignal();
	Object_wx_MenuItem *pThis = Object_wx_MenuItem::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxMenu *menu = Object_wx_Menu::GetObject(arg, 0)->GetEntity();
	pThis->GetEntity()->Toggle();
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Object implementation for wxMenuItem
//----------------------------------------------------------------------------
Object_wx_MenuItem::~Object_wx_MenuItem()
{
}

Object *Object_wx_MenuItem::Clone() const
{
	return nullptr;
}

String Object_wx_MenuItem::ToString(bool exprFlag)
{
	String rtn("<wx.MenuItem:");
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
// Class implementation for wxMenuItem
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_MenuItem)
{
	Gura_AssignFunction(MenuItem);
	Gura_AssignMethod(wx_MenuItem, Check);
	Gura_AssignMethod(wx_MenuItem, Enable);
	Gura_AssignMethod(wx_MenuItem, GetAccel);
	Gura_AssignMethod(wx_MenuItem, GetBackgroundColour);
	Gura_AssignMethod(wx_MenuItem, GetBitmap);
	Gura_AssignMethod(wx_MenuItem, GetFont);
	Gura_AssignMethod(wx_MenuItem, GetHelp);
	Gura_AssignMethod(wx_MenuItem, GetId);
	Gura_AssignMethod(wx_MenuItem, GetItemLabel);
	Gura_AssignMethod(wx_MenuItem, GetItemLabelText);
	Gura_AssignMethod(wx_MenuItem, GetKind);
	Gura_AssignMethod(wx_MenuItem, GetLabel);
	Gura_AssignMethod(wx_MenuItem, GetLabelText);
	Gura_AssignMethod(wx_MenuItem, GetLabelFromText);
	Gura_AssignMethod(wx_MenuItem, GetMarginWidth);
	Gura_AssignMethod(wx_MenuItem, GetMenu);
	Gura_AssignMethod(wx_MenuItem, GetName);
	Gura_AssignMethod(wx_MenuItem, GetText);
	Gura_AssignMethod(wx_MenuItem, GetSubMenu);
	Gura_AssignMethod(wx_MenuItem, GetTextColour);
	Gura_AssignMethod(wx_MenuItem, IsCheckable);
	Gura_AssignMethod(wx_MenuItem, IsChecked);
	Gura_AssignMethod(wx_MenuItem, IsEnabled);
	Gura_AssignMethod(wx_MenuItem, IsSeparator);
	Gura_AssignMethod(wx_MenuItem, IsSubMenu);
	Gura_AssignMethod(wx_MenuItem, SetBackgroundColour);
	Gura_AssignMethod(wx_MenuItem, SetBitmap);
	Gura_AssignMethod(wx_MenuItem, SetBitmaps);
	Gura_AssignMethod(wx_MenuItem, SetFont);
	Gura_AssignMethod(wx_MenuItem, SetHelp);
	Gura_AssignMethod(wx_MenuItem, SetItemLabel);
	Gura_AssignMethod(wx_MenuItem, SetMarginWidth);
	Gura_AssignMethod(wx_MenuItem, SetMenu);
	Gura_AssignMethod(wx_MenuItem, SetSubMenu);
	Gura_AssignMethod(wx_MenuItem, SetText);
	Gura_AssignMethod(wx_MenuItem, SetTextColour);
	Gura_AssignMethod(wx_MenuItem, Toggle);
}

Gura_ImplementDescendantCreator(wx_MenuItem)
{
	return new Object_wx_MenuItem((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
