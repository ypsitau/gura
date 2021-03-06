//----------------------------------------------------------------------------
// wxFrame
// extracted from frame.tex
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

Gura_DeclarePrivUserSymbol(CreateStatusBar);
Gura_DeclarePrivUserSymbol(CreateToolBar);
Gura_DeclarePrivUserSymbol(OnCreateStatusBar);
Gura_DeclarePrivUserSymbol(OnCreateToolBar);
Gura_DeclarePrivUserSymbol(SetStatusText);
Gura_DeclarePrivUserSymbol(SetStatusWidths);

//----------------------------------------------------------------------------
// Class derivation
//----------------------------------------------------------------------------
class wx_Frame: public wxFrame, public GuraObjectObserver {
private:
	//Gura::Signal *_pSig;
	Object_wx_Frame *_pObj;
public:
	inline wx_Frame() : wxFrame(), _pObj(nullptr) {}
	inline wx_Frame(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style, const wxString& name) : wxFrame(parent, id, title, pos, size, style, name), _pObj(nullptr) {}
	//virtual wxStatusBar* CreateStatusBar(int number, long style, wxWindowID id, const wxString& name);
	//virtual wxToolBar* CreateToolBar(long style, wxWindowID id, const wxString& name);
	//virtual wxStatusBar* OnCreateStatusBar(int number, long style, wxWindowID id, const wxString& name);
	//virtual wxToolBar* OnCreateToolBar(long style, wxWindowID id, const wxString& name);
	//virtual void SetStatusText(const wxString& text, int number);
	//virtual void SetStatusWidths(int n, int * widths);
	~wx_Frame();
	inline void AssocWithGura(Object_wx_Frame *pObj) {
		_pObj = pObj;
	}
	// virtual function of GuraObjectObserver
	virtual void GuraObjectDeleted();
public:
	// reveal private or protected member functions to public
	void _PositionMenuBar() { wxFrame::PositionMenuBar(); }
	void _DetachMenuBar() { wxFrame::DetachMenuBar(); }
	void _AttachMenuBar(wxMenuBar *menubar) { wxFrame::AttachMenuBar(menubar); }
	void _PositionStatusBar() { wxFrame::PositionStatusBar(); }
	void _PositionToolBar() { wxFrame::PositionToolBar(); }
};

wx_Frame::~wx_Frame()
{
	if (_pObj != nullptr) _pObj->InvalidateEntity();
}

void wx_Frame::GuraObjectDeleted()
{
	_pObj = nullptr;
}

//----------------------------------------------------------------------------
// Gura interfaces for wxFrame
//----------------------------------------------------------------------------
Gura_DeclareFunction(FrameEmpty)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	SetClassToConstruct(Gura_UserClass(wx_Frame));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(FrameEmpty)
{
	Signal &sig = env.GetSignal();
	if (!CheckWxReady(sig)) return Value::Nil;
	wx_Frame *pEntity = new wx_Frame();
	Object_wx_Frame *pObj = Object_wx_Frame::GetObjectThis(arg);
	if (pObj == nullptr) {
		pObj = new Object_wx_Frame(pEntity, pEntity, OwnerFalse);
		pEntity->AssocWithGura(pObj);
		return ReturnValue(env, arg, Value(pObj));
	}
	pObj->SetEntity(pEntity, pEntity, OwnerFalse);
	pEntity->AssocWithGura(pObj);
	return ReturnValue(env, arg, arg.GetValueThis());
}

Gura_DeclareFunction(Frame)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	SetClassToConstruct(Gura_UserClass(wx_Frame));
	DeclareArg(env, "parent", VTYPE_wx_Window, OCCUR_Once, FLAG_Nil);
	DeclareArg(env, "id", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "title", VTYPE_string, OCCUR_Once);
	DeclareArg(env, "pos", VTYPE_wx_Point, OCCUR_ZeroOrOnce);
	DeclareArg(env, "size", VTYPE_wx_Size, OCCUR_ZeroOrOnce);
	DeclareArg(env, "style", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareArg(env, "name", VTYPE_string, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(Frame)
{
	Signal &sig = env.GetSignal();
	if (!CheckWxReady(sig)) return Value::Nil;
	wxWindow *parent = arg.IsValid(0)?
			Object_wx_Window::GetObject(arg, 0)->GetEntity() : nullptr;
	wxWindowID id = static_cast<wxWindowID>(arg.GetInt(1));
	wxString title = wxString::FromUTF8(arg.GetString(2));
	wxPoint *pos = (wxPoint *)(&wxDefaultPosition);
	if (arg.IsValid(3)) pos = Object_wx_Point::GetObject(arg, 3)->GetEntity();
	wxSize *size = (wxSize *)(&wxDefaultSize);
	if (arg.IsValid(4)) size = Object_wx_Size::GetObject(arg, 4)->GetEntity();
	long style = wxDEFAULT_FRAME_STYLE;
	if (arg.IsValid(5)) style = arg.GetLong(5);
	wxString name = wxT("frame");
	if (arg.IsValid(6)) name = wxString::FromUTF8(arg.GetString(6));
	wx_Frame *pEntity = new wx_Frame(parent, id, title, *pos, *size, style, name);
	Object_wx_Frame *pObj = Object_wx_Frame::GetObjectThis(arg);
	if (pObj == nullptr) {
		pObj = new Object_wx_Frame(pEntity, pEntity, OwnerFalse);
		pEntity->AssocWithGura(pObj);
		return ReturnValue(env, arg, Value(pObj));
	}
	pObj->SetEntity(pEntity, pEntity, OwnerFalse);
	pEntity->AssocWithGura(pObj);
	return ReturnValue(env, arg, arg.GetValueThis());
}

Gura_DeclareMethod(wx_Frame, Centre)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "direction", VTYPE_number, OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_Frame, Centre)
{
	Signal &sig = env.GetSignal();
	Object_wx_Frame *pThis = Object_wx_Frame::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	int direction = wxBOTH;
	if (arg.IsValid(0)) direction = arg.GetInt(0);
	pThis->GetEntity()->Centre(direction);
	return Value::Nil;
}

Gura_DeclareMethod(wx_Frame, Create)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "parent", VTYPE_wx_Window, OCCUR_Once, FLAG_Nil);
	DeclareArg(env, "id", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "title", VTYPE_string, OCCUR_Once);
	DeclareArg(env, "pos", VTYPE_wx_Point, OCCUR_ZeroOrOnce);
	DeclareArg(env, "size", VTYPE_wx_Size, OCCUR_ZeroOrOnce);
	DeclareArg(env, "style", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareArg(env, "name", VTYPE_string, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_Frame, Create)
{
	Signal &sig = env.GetSignal();
	Object_wx_Frame *pThis = Object_wx_Frame::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxWindow *parent = arg.IsValid(0)?
			Object_wx_Window::GetObject(arg, 0)->GetEntity() : nullptr;
	wxWindowID id = static_cast<wxWindowID>(arg.GetInt(1));
	wxString title = wxString::FromUTF8(arg.GetString(2));
	wxPoint *pos = (wxPoint *)(&wxDefaultPosition);
	if (arg.IsValid(3)) pos = Object_wx_Point::GetObject(arg, 3)->GetEntity();
	wxSize *size = (wxSize *)(&wxDefaultSize);
	if (arg.IsValid(4)) size = Object_wx_Size::GetObject(arg, 4)->GetEntity();
	long style = wxDEFAULT_FRAME_STYLE;
	if (arg.IsValid(5)) style = arg.GetLong(5);
	wxString name = wxT("frame");
	if (arg.IsValid(6)) name = wxString::FromUTF8(arg.GetString(6));
	bool rtn = pThis->GetEntity()->Create(parent, id, title, *pos, *size, style, name);
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_Frame, CreateStatusBar)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "number", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareArg(env, "style", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareArg(env, "id", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareArg(env, "name", VTYPE_string, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_Frame, CreateStatusBar)
{
	Signal &sig = env.GetSignal();
	Object_wx_Frame *pThis = Object_wx_Frame::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	int number = 1;
	if (arg.IsValid(0)) number = arg.GetInt(0);
	long style = wxST_SIZEGRIP | wxFULL_REPAINT_ON_RESIZE;
	if (arg.IsValid(1)) style = arg.GetLong(1);
	wxWindowID id = 0;
	if (arg.IsValid(2)) id = static_cast<wxWindowID>(arg.GetInt(2));
	wxString name = wxT("statusBar");
	if (arg.IsValid(3)) name = wxString::FromUTF8(arg.GetString(3));
	wxStatusBar *rtn = (wxStatusBar *)pThis->GetEntity()->CreateStatusBar(number, style, id, name);
	return ReturnValue(env, arg, Value(new Object_wx_StatusBar(rtn, nullptr, OwnerFalse)));
}

Gura_DeclareMethod(wx_Frame, CreateToolBar)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "style", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareArg(env, "id", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareArg(env, "name", VTYPE_string, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_Frame, CreateToolBar)
{
	Signal &sig = env.GetSignal();
	Object_wx_Frame *pThis = Object_wx_Frame::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	long style = wxNO_BORDER | wxTB_HORIZONTAL;
	if (arg.IsValid(0)) style = arg.GetLong(0);
	wxWindowID id = -1;
	if (arg.IsValid(1)) id = static_cast<wxWindowID>(arg.GetInt(1));
	wxString name = wxT("toolBar");
	if (arg.IsValid(2)) name = wxString::FromUTF8(arg.GetString(2));
	wxToolBar *rtn = (wxToolBar *)pThis->GetEntity()->CreateToolBar(style, id, name);
	return ReturnValue(env, arg, Value(new Object_wx_ToolBar(rtn, nullptr, OwnerFalse)));
}

Gura_DeclareMethod(wx_Frame, GetClientAreaOrigin)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_Frame, GetClientAreaOrigin)
{
	Signal &sig = env.GetSignal();
	Object_wx_Frame *pThis = Object_wx_Frame::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxPoint rtn = pThis->GetEntity()->GetClientAreaOrigin();
	return ReturnValue(env, arg, Value(new Object_wx_Point(new wxPoint(rtn), nullptr, OwnerTrue)));
}

Gura_DeclareMethod(wx_Frame, GetMenuBar)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_Frame, GetMenuBar)
{
	Signal &sig = env.GetSignal();
	Object_wx_Frame *pThis = Object_wx_Frame::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxMenuBar *rtn = (wxMenuBar *)pThis->GetEntity()->GetMenuBar();
	Value value;
	if (rtn != nullptr) {
		value = Value(new Object_wx_MenuBar(rtn, nullptr, OwnerFalse));
	}
	return ReturnValue(env, arg, value);
}

Gura_DeclareMethod(wx_Frame, GetStatusBar)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_Frame, GetStatusBar)
{
	Signal &sig = env.GetSignal();
	Object_wx_Frame *pThis = Object_wx_Frame::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxStatusBar *rtn = (wxStatusBar *)pThis->GetEntity()->GetStatusBar();
	Value value;
	if (rtn != nullptr) {
		value = Value(new Object_wx_StatusBar(rtn, nullptr, OwnerFalse));
	}
	return ReturnValue(env, arg, value);
}

Gura_DeclareMethod(wx_Frame, GetStatusBarPane)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_Frame, GetStatusBarPane)
{
	Signal &sig = env.GetSignal();
	Object_wx_Frame *pThis = Object_wx_Frame::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	int rtn = pThis->GetEntity()->GetStatusBarPane();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_Frame, GetToolBar)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_Frame, GetToolBar)
{
	Signal &sig = env.GetSignal();
	Object_wx_Frame *pThis = Object_wx_Frame::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxToolBar *rtn = (wxToolBar *)pThis->GetEntity()->GetToolBar();
	Value value;
	if (rtn != nullptr) {
		value = Value(new Object_wx_ToolBar(rtn, nullptr, OwnerFalse));
	}
	return ReturnValue(env, arg, value);
}

Gura_DeclareMethod(wx_Frame, OnCreateStatusBar)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "number", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "style", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "id", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "name", VTYPE_string, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_Frame, OnCreateStatusBar)
{
	Signal &sig = env.GetSignal();
	Object_wx_Frame *pThis = Object_wx_Frame::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	int number = arg.GetInt(0);
	long style = arg.GetLong(1);
	wxWindowID id = static_cast<wxWindowID>(arg.GetInt(2));
	wxString name = wxString::FromUTF8(arg.GetString(3));
	wxStatusBar *rtn = (wxStatusBar *)pThis->GetEntity()->OnCreateStatusBar(number, style, id, name);
	return ReturnValue(env, arg, Value(new Object_wx_StatusBar(rtn, nullptr, OwnerFalse)));
}

Gura_DeclareMethod(wx_Frame, OnCreateToolBar)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "style", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "id", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "name", VTYPE_string, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_Frame, OnCreateToolBar)
{
	Signal &sig = env.GetSignal();
	Object_wx_Frame *pThis = Object_wx_Frame::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	long style = arg.GetLong(0);
	wxWindowID id = static_cast<wxWindowID>(arg.GetInt(1));
	wxString name = wxString::FromUTF8(arg.GetString(2));
	wxToolBar *rtn = (wxToolBar *)pThis->GetEntity()->OnCreateToolBar(style, id, name);
	return ReturnValue(env, arg, Value(new Object_wx_ToolBar(rtn, nullptr, OwnerFalse)));
}

Gura_DeclareMethod(wx_Frame, ProcessCommand)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "id", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Frame, ProcessCommand)
{
	Signal &sig = env.GetSignal();
	Object_wx_Frame *pThis = Object_wx_Frame::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	int id = arg.GetInt(0);
	pThis->GetEntity()->ProcessCommand(id);
	return Value::Nil;
}

Gura_DeclareMethod(wx_Frame, SendSizeEvent)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_Frame, SendSizeEvent)
{
	Signal &sig = env.GetSignal();
	Object_wx_Frame *pThis = Object_wx_Frame::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	pThis->GetEntity()->SendSizeEvent();
	return Value::Nil;
}

Gura_DeclareMethod(wx_Frame, SetMenuBar)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "menuBar", VTYPE_wx_MenuBar, OCCUR_Once);
}

Gura_ImplementMethod(wx_Frame, SetMenuBar)
{
	Signal &sig = env.GetSignal();
	Object_wx_Frame *pThis = Object_wx_Frame::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxMenuBar *menuBar = Object_wx_MenuBar::GetObject(arg, 0)->GetEntity();
	pThis->GetEntity()->SetMenuBar(menuBar);
	return Value::Nil;
}

Gura_DeclareMethod(wx_Frame, SetStatusBar)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "statusBar", VTYPE_wx_StatusBar, OCCUR_Once, FLAG_Nil);
}

Gura_ImplementMethod(wx_Frame, SetStatusBar)
{
	Signal &sig = env.GetSignal();
	Object_wx_Frame *pThis = Object_wx_Frame::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxStatusBar *statusBar = arg.IsValid(0)?
			Object_wx_StatusBar::GetObject(arg, 0)->GetEntity() : nullptr;
	pThis->GetEntity()->SetStatusBar(statusBar);
	return Value::Nil;
}

Gura_DeclareMethod(wx_Frame, SetStatusBarPane)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "n", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Frame, SetStatusBarPane)
{
	Signal &sig = env.GetSignal();
	Object_wx_Frame *pThis = Object_wx_Frame::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	int n = arg.GetInt(0);
	pThis->GetEntity()->SetStatusBarPane(n);
	return Value::Nil;
}

Gura_DeclareMethod(wx_Frame, SetStatusText)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "text", VTYPE_string, OCCUR_Once);
	DeclareArg(env, "number", VTYPE_number, OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_Frame, SetStatusText)
{
	Signal &sig = env.GetSignal();
	Object_wx_Frame *pThis = Object_wx_Frame::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxString text = wxString::FromUTF8(arg.GetString(0));
	int number = 0;
	if (arg.IsValid(1)) number = arg.GetInt(1);
	pThis->GetEntity()->SetStatusText(text, number);
	return Value::Nil;
}

Gura_DeclareMethod(wx_Frame, SetStatusWidths)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "widths", VTYPE_number, OCCUR_Once, FLAG_ListVar);
}

Gura_ImplementMethod(wx_Frame, SetStatusWidths)
{
	Signal &sig = env.GetSignal();
	Object_wx_Frame *pThis = Object_wx_Frame::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	CArrayOfInt widths(arg.GetList(0));
	pThis->GetEntity()->SetStatusWidths(widths.Count(), widths.Data());
	return Value::Nil;
}

Gura_DeclareMethod(wx_Frame, SetToolBar)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "toolBar", VTYPE_wx_ToolBar, OCCUR_Once);
}

Gura_ImplementMethod(wx_Frame, SetToolBar)
{
	Signal &sig = env.GetSignal();
	Object_wx_Frame *pThis = Object_wx_Frame::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxToolBar *toolBar = Object_wx_ToolBar::GetObject(arg, 0)->GetEntity();
	pThis->GetEntity()->SetToolBar(toolBar);
	return Value::Nil;
}

Gura_DeclareMethod(wx_Frame, PositionMenuBar)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_Frame, PositionMenuBar)
{
	Signal &sig = env.GetSignal();
	Object_wx_Frame *pThis = Object_wx_Frame::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	dynamic_cast<wx_Frame *>(pThis->GetEntity())->_PositionMenuBar();
	return Value::Nil;
}

Gura_DeclareMethod(wx_Frame, DetachMenuBar)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_Frame, DetachMenuBar)
{
	Signal &sig = env.GetSignal();
	Object_wx_Frame *pThis = Object_wx_Frame::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	dynamic_cast<wx_Frame *>(pThis->GetEntity())->_DetachMenuBar();
	return Value::Nil;
}

Gura_DeclareMethod(wx_Frame, AttachMenuBar)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "menuBar", VTYPE_wx_MenuBar, OCCUR_Once);
}

Gura_ImplementMethod(wx_Frame, AttachMenuBar)
{
	Signal &sig = env.GetSignal();
	Object_wx_Frame *pThis = Object_wx_Frame::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxMenuBar *menuBar = Object_wx_MenuBar::GetObject(arg, 0)->GetEntity();
	dynamic_cast<wx_Frame *>(pThis->GetEntity())->_AttachMenuBar(menuBar);
	return Value::Nil;
}

Gura_DeclareMethod(wx_Frame, PositionStatusBar)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_Frame, PositionStatusBar)
{
	Signal &sig = env.GetSignal();
	Object_wx_Frame *pThis = Object_wx_Frame::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	dynamic_cast<wx_Frame *>(pThis->GetEntity())->_PositionStatusBar();
	return Value::Nil;
}

Gura_DeclareMethod(wx_Frame, PositionToolBar)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_Frame, PositionToolBar)
{
	Signal &sig = env.GetSignal();
	Object_wx_Frame *pThis = Object_wx_Frame::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	dynamic_cast<wx_Frame *>(pThis->GetEntity())->_PositionToolBar();
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Object implementation for wxFrame
//----------------------------------------------------------------------------
Object_wx_Frame::~Object_wx_Frame()
{
}

Object *Object_wx_Frame::Clone() const
{
	return nullptr;
}

String Object_wx_Frame::ToString(bool exprFlag)
{
	String rtn("<wx.Frame:");
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
// Class implementation for wxFrame
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_Frame)
{
	Gura_RealizeUserSymbol(CreateStatusBar);
	Gura_RealizeUserSymbol(CreateToolBar);
	Gura_RealizeUserSymbol(OnCreateStatusBar);
	Gura_RealizeUserSymbol(OnCreateToolBar);
	Gura_RealizeUserSymbol(SetStatusText);
	Gura_RealizeUserSymbol(SetStatusWidths);
	Gura_AssignFunction(FrameEmpty);
	Gura_AssignFunction(Frame);
	Gura_AssignMethod(wx_Frame, Centre);
	Gura_AssignMethod(wx_Frame, Create);
	Gura_AssignMethod(wx_Frame, CreateStatusBar);
	Gura_AssignMethod(wx_Frame, CreateToolBar);
	Gura_AssignMethod(wx_Frame, GetClientAreaOrigin);
	Gura_AssignMethod(wx_Frame, GetMenuBar);
	Gura_AssignMethod(wx_Frame, GetStatusBar);
	Gura_AssignMethod(wx_Frame, GetStatusBarPane);
	Gura_AssignMethod(wx_Frame, GetToolBar);
	Gura_AssignMethod(wx_Frame, OnCreateStatusBar);
	Gura_AssignMethod(wx_Frame, OnCreateToolBar);
	Gura_AssignMethod(wx_Frame, ProcessCommand);
	Gura_AssignMethod(wx_Frame, SendSizeEvent);
	Gura_AssignMethod(wx_Frame, SetMenuBar);
	Gura_AssignMethod(wx_Frame, SetStatusBar);
	Gura_AssignMethod(wx_Frame, SetStatusBarPane);
	Gura_AssignMethod(wx_Frame, SetStatusText);
	Gura_AssignMethod(wx_Frame, SetStatusWidths);
	Gura_AssignMethod(wx_Frame, SetToolBar);
	Gura_AssignMethod(wx_Frame, PositionMenuBar);
	Gura_AssignMethod(wx_Frame, DetachMenuBar);
	Gura_AssignMethod(wx_Frame, AttachMenuBar);
	Gura_AssignMethod(wx_Frame, PositionStatusBar);
	Gura_AssignMethod(wx_Frame, PositionToolBar);
}

Gura_ImplementDescendantCreator(wx_Frame)
{
	return new Object_wx_Frame((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
