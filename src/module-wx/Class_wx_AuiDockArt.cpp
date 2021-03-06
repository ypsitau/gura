//----------------------------------------------------------------------------
// wxAuiDockArt
// extracted from auidockart.tex
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

Gura_DeclarePrivUserSymbol(DrawBackground);
Gura_DeclarePrivUserSymbol(DrawBorder);
Gura_DeclarePrivUserSymbol(DrawCaption);
Gura_DeclarePrivUserSymbol(DrawGripper);
Gura_DeclarePrivUserSymbol(DrawPaneButton);
Gura_DeclarePrivUserSymbol(DrawSash);
Gura_DeclarePrivUserSymbol(GetColor);
Gura_DeclarePrivUserSymbol(GetColour);
Gura_DeclarePrivUserSymbol(GetFont);
Gura_DeclarePrivUserSymbol(GetMetric);
Gura_DeclarePrivUserSymbol(SetColor);
Gura_DeclarePrivUserSymbol(SetColour);
Gura_DeclarePrivUserSymbol(SetFont);
Gura_DeclarePrivUserSymbol(SetMetric);

//----------------------------------------------------------------------------
// Class derivation
//----------------------------------------------------------------------------
class wx_AuiDockArt: public wxAuiDockArt, public GuraObjectObserver {
private:
	//Gura::Signal *_pSig;
	Object_wx_AuiDockArt *_pObj;
public:
	//inline wx_AuiDockArt() : wxAuiDockArt(), _pObj(nullptr) {}
	//virtual void DrawBackground(wxDC& dc, wxWindow* window, int orientation, const wxRect& rect);
	//virtual void DrawBorder(wxDC& dc, wxWindow* window, const wxRect& rect, wxAuiPaneInfo& pane);
	//virtual void DrawCaption(wxDC& dc, wxWindow* window, const wxString& text, const wxRect& rect, wxAuiPaneInfo& pane);
	//virtual void DrawGripper(wxDC& dc, wxWindow* window, const wxRect& rect, wxAuiPaneInfo& pane);
	//virtual void DrawPaneButton(wxDC& dc, wxWindow* window, int button, int button_state, const wxRect& rect, wxAuiPaneInfo& pane);
	//virtual void DrawSash(wxDC& dc, wxWindow* window, int orientation, const wxRect& rect);
	//virtual wxColour GetColor(int id);
	//virtual wxColour GetColour(int id);
	//virtual wxFont GetFont(int id);
	//virtual int GetMetric(int id);
	//virtual void SetColor(int id, const wxColour& color);
	//virtual void SetColour(int id, const wxColor& colour);
	//virtual void SetFont(int id, const wxFont& font);
	//virtual void SetMetric(int id, int new_val);
	~wx_AuiDockArt();
	inline void AssocWithGura(Object_wx_AuiDockArt *pObj) {
		_pObj = pObj;
	}
	// virtual function of GuraObjectObserver
	virtual void GuraObjectDeleted();
};

wx_AuiDockArt::~wx_AuiDockArt()
{
	if (_pObj != nullptr) _pObj->InvalidateEntity();
}

void wx_AuiDockArt::GuraObjectDeleted()
{
	_pObj = nullptr;
}

//----------------------------------------------------------------------------
// Gura interfaces for wxAuiDockArt
//----------------------------------------------------------------------------
Gura_DeclareFunction(AuiDockArtEmpty)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
#if 0
	SetClassToConstruct(Gura_UserClass(wx_AuiDockArt));
	DeclareBlock(OCCUR_ZeroOrOnce);
#endif
}

Gura_ImplementFunction(AuiDockArtEmpty)
{
	Signal &sig = env.GetSignal();
	if (!CheckWxReady(sig)) return Value::Nil;
#if 0
	wx_AuiDockArt *pEntity = new wx_AuiDockArt();
	Object_wx_AuiDockArt *pObj = Object_wx_AuiDockArt::GetObjectThis(arg);
	if (pObj == nullptr) {
		pObj = new Object_wx_AuiDockArt(pEntity, pEntity, OwnerFalse);
		pEntity->AssocWithGura(pObj);
		return ReturnValue(env, arg, Value(pObj));
	}
	pObj->SetEntity(pEntity, pEntity, OwnerFalse);
	pEntity->AssocWithGura(pObj);
	return ReturnValue(env, arg, arg.GetValueThis());
#endif
	SetError_NotImplemented(sig);
	return Value::Nil;
}

Gura_DeclareMethod(wx_AuiDockArt, DrawBackground)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "dc", VTYPE_wx_DC, OCCUR_Once);
	DeclareArg(env, "window", VTYPE_wx_Window, OCCUR_Once);
	DeclareArg(env, "orientation", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "rect", VTYPE_wx_Rect, OCCUR_Once);
}

Gura_ImplementMethod(wx_AuiDockArt, DrawBackground)
{
	Signal &sig = env.GetSignal();
	Object_wx_AuiDockArt *pThis = Object_wx_AuiDockArt::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxDC *dc = Object_wx_DC::GetObject(arg, 0)->GetEntity();
	wxWindow *window = Object_wx_Window::GetObject(arg, 1)->GetEntity();
	int orientation = arg.GetInt(2);
	wxRect *rect = Object_wx_Rect::GetObject(arg, 3)->GetEntity();
	pThis->GetEntity()->DrawBackground(*dc, window, orientation, *rect);
	return Value::Nil;
}

Gura_DeclareMethod(wx_AuiDockArt, DrawBorder)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "dc", VTYPE_wx_DC, OCCUR_Once);
	DeclareArg(env, "window", VTYPE_wx_Window, OCCUR_Once);
	DeclareArg(env, "rect", VTYPE_wx_Rect, OCCUR_Once);
	DeclareArg(env, "pane", VTYPE_wx_AuiPaneInfo, OCCUR_Once);
}

Gura_ImplementMethod(wx_AuiDockArt, DrawBorder)
{
	Signal &sig = env.GetSignal();
	Object_wx_AuiDockArt *pThis = Object_wx_AuiDockArt::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxDC *dc = Object_wx_DC::GetObject(arg, 0)->GetEntity();
	wxWindow *window = Object_wx_Window::GetObject(arg, 1)->GetEntity();
	wxRect *rect = Object_wx_Rect::GetObject(arg, 2)->GetEntity();
	wxAuiPaneInfo *pane = Object_wx_AuiPaneInfo::GetObject(arg, 3)->GetEntity();
	pThis->GetEntity()->DrawBorder(*dc, window, *rect, *pane);
	return Value::Nil;
}

Gura_DeclareMethod(wx_AuiDockArt, DrawCaption)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "dc", VTYPE_wx_DC, OCCUR_Once);
	DeclareArg(env, "window", VTYPE_wx_Window, OCCUR_Once);
	DeclareArg(env, "text", VTYPE_string, OCCUR_Once);
	DeclareArg(env, "rect", VTYPE_wx_Rect, OCCUR_Once);
	DeclareArg(env, "pane", VTYPE_wx_AuiPaneInfo, OCCUR_Once);
}

Gura_ImplementMethod(wx_AuiDockArt, DrawCaption)
{
	Signal &sig = env.GetSignal();
	Object_wx_AuiDockArt *pThis = Object_wx_AuiDockArt::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxDC *dc = Object_wx_DC::GetObject(arg, 0)->GetEntity();
	wxWindow *window = Object_wx_Window::GetObject(arg, 1)->GetEntity();
	wxString text = wxString::FromUTF8(arg.GetString(2));
	wxRect *rect = Object_wx_Rect::GetObject(arg, 3)->GetEntity();
	wxAuiPaneInfo *pane = Object_wx_AuiPaneInfo::GetObject(arg, 4)->GetEntity();
	pThis->GetEntity()->DrawCaption(*dc, window, text, *rect, *pane);
	return Value::Nil;
}

Gura_DeclareMethod(wx_AuiDockArt, DrawGripper)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "dc", VTYPE_wx_DC, OCCUR_Once);
	DeclareArg(env, "window", VTYPE_wx_Window, OCCUR_Once);
	DeclareArg(env, "rect", VTYPE_wx_Rect, OCCUR_Once);
	DeclareArg(env, "pane", VTYPE_wx_AuiPaneInfo, OCCUR_Once);
}

Gura_ImplementMethod(wx_AuiDockArt, DrawGripper)
{
	Signal &sig = env.GetSignal();
	Object_wx_AuiDockArt *pThis = Object_wx_AuiDockArt::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxDC *dc = Object_wx_DC::GetObject(arg, 0)->GetEntity();
	wxWindow *window = Object_wx_Window::GetObject(arg, 1)->GetEntity();
	wxRect *rect = Object_wx_Rect::GetObject(arg, 2)->GetEntity();
	wxAuiPaneInfo *pane = Object_wx_AuiPaneInfo::GetObject(arg, 3)->GetEntity();
	pThis->GetEntity()->DrawGripper(*dc, window, *rect, *pane);
	return Value::Nil;
}

Gura_DeclareMethod(wx_AuiDockArt, DrawPaneButton)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "dc", VTYPE_wx_DC, OCCUR_Once);
	DeclareArg(env, "window", VTYPE_wx_Window, OCCUR_Once);
	DeclareArg(env, "button", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "button_state", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "rect", VTYPE_wx_Rect, OCCUR_Once);
	DeclareArg(env, "pane", VTYPE_wx_AuiPaneInfo, OCCUR_Once);
}

Gura_ImplementMethod(wx_AuiDockArt, DrawPaneButton)
{
	Signal &sig = env.GetSignal();
	Object_wx_AuiDockArt *pThis = Object_wx_AuiDockArt::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxDC *dc = Object_wx_DC::GetObject(arg, 0)->GetEntity();
	wxWindow *window = Object_wx_Window::GetObject(arg, 1)->GetEntity();
	int button = arg.GetInt(2);
	int button_state = arg.GetInt(3);
	wxRect *rect = Object_wx_Rect::GetObject(arg, 4)->GetEntity();
	wxAuiPaneInfo *pane = Object_wx_AuiPaneInfo::GetObject(arg, 5)->GetEntity();
	pThis->GetEntity()->DrawPaneButton(*dc, window, button, button_state, *rect, *pane);
	return Value::Nil;
}

Gura_DeclareMethod(wx_AuiDockArt, DrawSash)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "dc", VTYPE_wx_DC, OCCUR_Once);
	DeclareArg(env, "window", VTYPE_wx_Window, OCCUR_Once);
	DeclareArg(env, "orientation", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "rect", VTYPE_wx_Rect, OCCUR_Once);
}

Gura_ImplementMethod(wx_AuiDockArt, DrawSash)
{
	Signal &sig = env.GetSignal();
	Object_wx_AuiDockArt *pThis = Object_wx_AuiDockArt::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxDC *dc = Object_wx_DC::GetObject(arg, 0)->GetEntity();
	wxWindow *window = Object_wx_Window::GetObject(arg, 1)->GetEntity();
	int orientation = arg.GetInt(2);
	wxRect *rect = Object_wx_Rect::GetObject(arg, 3)->GetEntity();
	pThis->GetEntity()->DrawSash(*dc, window, orientation, *rect);
	return Value::Nil;
}

Gura_DeclareMethod(wx_AuiDockArt, GetColor)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "id", VTYPE_number, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_AuiDockArt, GetColor)
{
	Signal &sig = env.GetSignal();
	Object_wx_AuiDockArt *pThis = Object_wx_AuiDockArt::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	int id = arg.GetInt(0);
	wxColour rtn = pThis->GetEntity()->GetColor(id);
	return ReturnValue(env, arg, Value(new Object_wx_Colour(new wxColour(rtn), nullptr, OwnerTrue)));
}

Gura_DeclareMethod(wx_AuiDockArt, GetColour)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "id", VTYPE_number, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_AuiDockArt, GetColour)
{
	Signal &sig = env.GetSignal();
	Object_wx_AuiDockArt *pThis = Object_wx_AuiDockArt::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	int id = arg.GetInt(0);
	wxColour rtn = pThis->GetEntity()->GetColour(id);
	return ReturnValue(env, arg, Value(new Object_wx_Colour(new wxColour(rtn), nullptr, OwnerTrue)));
}

Gura_DeclareMethod(wx_AuiDockArt, GetFont)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "id", VTYPE_number, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_AuiDockArt, GetFont)
{
	Signal &sig = env.GetSignal();
	Object_wx_AuiDockArt *pThis = Object_wx_AuiDockArt::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	int id = arg.GetInt(0);
	wxFont rtn = pThis->GetEntity()->GetFont(id);
	return ReturnValue(env, arg, Value(new Object_wx_Font(new wxFont(rtn), nullptr, OwnerTrue)));
}

Gura_DeclareMethod(wx_AuiDockArt, GetMetric)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "id", VTYPE_number, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_AuiDockArt, GetMetric)
{
	Signal &sig = env.GetSignal();
	Object_wx_AuiDockArt *pThis = Object_wx_AuiDockArt::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	int id = arg.GetInt(0);
	int rtn = pThis->GetEntity()->GetMetric(id);
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_AuiDockArt, SetColor)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "id", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "color", VTYPE_wx_Colour, OCCUR_Once);
}

Gura_ImplementMethod(wx_AuiDockArt, SetColor)
{
	Signal &sig = env.GetSignal();
	Object_wx_AuiDockArt *pThis = Object_wx_AuiDockArt::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	int id = arg.GetInt(0);
	wxColour *color = Object_wx_Colour::GetObject(arg, 1)->GetEntity();
	pThis->GetEntity()->SetColor(id, *color);
	return Value::Nil;
}

Gura_DeclareMethod(wx_AuiDockArt, SetColour)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "id", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "colour", VTYPE_wx_Colour, OCCUR_Once);
}

Gura_ImplementMethod(wx_AuiDockArt, SetColour)
{
	Signal &sig = env.GetSignal();
	Object_wx_AuiDockArt *pThis = Object_wx_AuiDockArt::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	int id = arg.GetInt(0);
	wxColor *colour = Object_wx_Colour::GetObject(arg, 1)->GetEntity();
	pThis->GetEntity()->SetColour(id, *colour);
	return Value::Nil;
}

Gura_DeclareMethod(wx_AuiDockArt, SetFont)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "id", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "font", VTYPE_wx_Font, OCCUR_Once);
}

Gura_ImplementMethod(wx_AuiDockArt, SetFont)
{
	Signal &sig = env.GetSignal();
	Object_wx_AuiDockArt *pThis = Object_wx_AuiDockArt::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	int id = arg.GetInt(0);
	wxFont *font = Object_wx_Font::GetObject(arg, 1)->GetEntity();
	pThis->GetEntity()->SetFont(id, *font);
	return Value::Nil;
}

Gura_DeclareMethod(wx_AuiDockArt, SetMetric)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "id", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "new_val", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_AuiDockArt, SetMetric)
{
	Signal &sig = env.GetSignal();
	Object_wx_AuiDockArt *pThis = Object_wx_AuiDockArt::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	int id = arg.GetInt(0);
	int new_val = arg.GetInt(1);
	pThis->GetEntity()->SetMetric(id, new_val);
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Object implementation for wxAuiDockArt
//----------------------------------------------------------------------------
Object_wx_AuiDockArt::~Object_wx_AuiDockArt()
{
	if (_pEntity != nullptr) NotifyGuraObjectDeleted();
	if (_ownerFlag) delete _pEntity;
	_pEntity = nullptr;
}

Object *Object_wx_AuiDockArt::Clone() const
{
	return nullptr;
}

String Object_wx_AuiDockArt::ToString(bool exprFlag)
{
	String rtn("<wx.AuiDockArt:");
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
// Class implementation for wxAuiDockArt
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_AuiDockArt)
{
	Gura_RealizeUserSymbol(DrawBackground);
	Gura_RealizeUserSymbol(DrawBorder);
	Gura_RealizeUserSymbol(DrawCaption);
	Gura_RealizeUserSymbol(DrawGripper);
	Gura_RealizeUserSymbol(DrawPaneButton);
	Gura_RealizeUserSymbol(DrawSash);
	Gura_RealizeUserSymbol(GetColor);
	Gura_RealizeUserSymbol(GetColour);
	Gura_RealizeUserSymbol(GetFont);
	Gura_RealizeUserSymbol(GetMetric);
	Gura_RealizeUserSymbol(SetColor);
	Gura_RealizeUserSymbol(SetColour);
	Gura_RealizeUserSymbol(SetFont);
	Gura_RealizeUserSymbol(SetMetric);
	Gura_AssignFunction(AuiDockArtEmpty);
	Gura_AssignMethod(wx_AuiDockArt, DrawBackground);
	Gura_AssignMethod(wx_AuiDockArt, DrawBorder);
	Gura_AssignMethod(wx_AuiDockArt, DrawCaption);
	Gura_AssignMethod(wx_AuiDockArt, DrawGripper);
	Gura_AssignMethod(wx_AuiDockArt, DrawPaneButton);
	Gura_AssignMethod(wx_AuiDockArt, DrawSash);
	Gura_AssignMethod(wx_AuiDockArt, GetColor);
	Gura_AssignMethod(wx_AuiDockArt, GetColour);
	Gura_AssignMethod(wx_AuiDockArt, GetFont);
	Gura_AssignMethod(wx_AuiDockArt, GetMetric);
	Gura_AssignMethod(wx_AuiDockArt, SetColor);
	Gura_AssignMethod(wx_AuiDockArt, SetColour);
	Gura_AssignMethod(wx_AuiDockArt, SetFont);
	Gura_AssignMethod(wx_AuiDockArt, SetMetric);
}

Gura_ImplementDescendantCreator(wx_AuiDockArt)
{
	return new Object_wx_AuiDockArt((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
