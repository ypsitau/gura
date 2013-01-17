//----------------------------------------------------------------------------
// wxMDIParentFrame
// extracted from mdi.tex
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModule(wx)

Gura_DeclarePrivUserSymbol(GetClientSize);
Gura_DeclarePrivUserSymbol(GetToolBar);
Gura_DeclarePrivUserSymbol(OnCreateClient);
Gura_DeclarePrivUserSymbol(SetToolBar);

//----------------------------------------------------------------------------
// Class derivation
//----------------------------------------------------------------------------
class wx_MDIParentFrame: public wxMDIParentFrame, public GuraObjectObserver {
private:
	Gura::Signal _sig;
	Object_wx_MDIParentFrame *_pObj;
public:
	inline wx_MDIParentFrame() : wxMDIParentFrame(), _sig(NULL), _pObj(NULL) {}
	inline wx_MDIParentFrame(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style, const wxString& name) : wxMDIParentFrame(parent, id, title, pos, size, style, name), _sig(NULL), _pObj(NULL) {}
	//virtual void GetClientSize(int* width, int* height);
	//virtual wxWindow* GetToolBar();
	//virtual wxMDIClientWindow* OnCreateClient();
	//virtual void SetToolBar(wxWindow* toolbar);
	~wx_MDIParentFrame();
	inline void AssocWithGura(Gura::Signal &sig, Object_wx_MDIParentFrame *pObj) {
		_sig = sig, _pObj = pObj;
	}
	// virtual function of GuraObjectObserver
	virtual void GuraObjectDeleted();
};

wx_MDIParentFrame::~wx_MDIParentFrame()
{
	if (_pObj != NULL) _pObj->InvalidateEntity();
}

void wx_MDIParentFrame::GuraObjectDeleted()
{
	_pObj = NULL;
}

//----------------------------------------------------------------------------
// Gura interfaces for wxMDIParentFrame
//----------------------------------------------------------------------------
Gura_DeclareFunction(MDIParentFrameEmpty)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	SetClassToConstruct(Gura_UserClass(wx_MDIParentFrame));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(MDIParentFrameEmpty)
{
	wx_MDIParentFrame *pEntity = new wx_MDIParentFrame();
	Object_wx_MDIParentFrame *pObj = Object_wx_MDIParentFrame::GetSelfObj(args);
	if (pObj == NULL) {
		pObj = new Object_wx_MDIParentFrame(pEntity, pEntity, OwnerFalse);
		pEntity->AssocWithGura(sig, pObj);
		return ReturnValue(env, sig, args, Value(pObj));
	}
	pObj->SetEntity(pEntity, pEntity, OwnerFalse);
	pEntity->AssocWithGura(sig, pObj);
	return ReturnValue(env, sig, args, args.GetSelf());
}

Gura_DeclareFunction(MDIParentFrame)
{
	SetMode(RSLTMODE_Normal, FLAG_Map);
	SetClassToConstruct(Gura_UserClass(wx_MDIParentFrame));
	DeclareArg(env, "parent", VTYPE_wx_Window, OCCUR_Once, FLAG_Nil);
	DeclareArg(env, "id", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "title", VTYPE_string, OCCUR_Once);
	DeclareArg(env, "pos", VTYPE_wx_Point, OCCUR_ZeroOrOnce);
	DeclareArg(env, "size", VTYPE_wx_Size, OCCUR_ZeroOrOnce);
	DeclareArg(env, "style", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareArg(env, "name", VTYPE_string, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(MDIParentFrame)
{
	wxWindow *parent = args.IsValid(0)?
			Object_wx_Window::GetObject(args, 0)->GetEntity() : NULL;
	wxWindowID id = static_cast<wxWindowID>(args.GetInt(1));
	wxString title = wxString::FromUTF8(args.GetString(2));
	wxPoint *pos = (wxPoint *)(&wxDefaultPosition);
	if (args.IsValid(3)) pos = Object_wx_Point::GetObject(args, 3)->GetEntity();
	wxSize *size = (wxSize *)(&wxDefaultSize);
	if (args.IsValid(4)) size = Object_wx_Size::GetObject(args, 4)->GetEntity();
	long style = wxDEFAULT_FRAME_STYLE | wxVSCROLL | wxHSCROLL;
	if (args.IsValid(5)) style = args.GetLong(5);
	wxString name = wxT("frame");
	if (args.IsValid(6)) name = wxString::FromUTF8(args.GetString(6));
	wx_MDIParentFrame *pEntity = new wx_MDIParentFrame(parent, id, title, *pos, *size, style, name);
	Object_wx_MDIParentFrame *pObj = Object_wx_MDIParentFrame::GetSelfObj(args);
	if (pObj == NULL) {
		pObj = new Object_wx_MDIParentFrame(pEntity, pEntity, OwnerFalse);
		pEntity->AssocWithGura(sig, pObj);
		return ReturnValue(env, sig, args, Value(pObj));
	}
	pObj->SetEntity(pEntity, pEntity, OwnerFalse);
	pEntity->AssocWithGura(sig, pObj);
	return ReturnValue(env, sig, args, args.GetSelf());
}

Gura_DeclareMethod(wx_MDIParentFrame, ActivateNext)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_MDIParentFrame, ActivateNext)
{
	Object_wx_MDIParentFrame *pSelf = Object_wx_MDIParentFrame::GetSelfObj(args);
	if (pSelf->IsInvalid(sig)) return Value::Null;
	pSelf->GetEntity()->ActivateNext();
	return Value::Null;
}

Gura_DeclareMethod(wx_MDIParentFrame, ActivatePrevious)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_MDIParentFrame, ActivatePrevious)
{
	Object_wx_MDIParentFrame *pSelf = Object_wx_MDIParentFrame::GetSelfObj(args);
	if (pSelf->IsInvalid(sig)) return Value::Null;
	pSelf->GetEntity()->ActivatePrevious();
	return Value::Null;
}

Gura_DeclareMethod(wx_MDIParentFrame, ArrangeIcons)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_MDIParentFrame, ArrangeIcons)
{
	Object_wx_MDIParentFrame *pSelf = Object_wx_MDIParentFrame::GetSelfObj(args);
	if (pSelf->IsInvalid(sig)) return Value::Null;
	pSelf->GetEntity()->ArrangeIcons();
	return Value::Null;
}

Gura_DeclareMethod(wx_MDIParentFrame, Cascade)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_MDIParentFrame, Cascade)
{
	Object_wx_MDIParentFrame *pSelf = Object_wx_MDIParentFrame::GetSelfObj(args);
	if (pSelf->IsInvalid(sig)) return Value::Null;
	pSelf->GetEntity()->Cascade();
	return Value::Null;
}

Gura_DeclareMethod(wx_MDIParentFrame, Create)
{
	SetMode(RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "parent", VTYPE_wx_Window, OCCUR_Once, FLAG_Nil);
	DeclareArg(env, "id", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "title", VTYPE_string, OCCUR_Once);
	DeclareArg(env, "pos", VTYPE_wx_Point, OCCUR_ZeroOrOnce);
	DeclareArg(env, "size", VTYPE_wx_Size, OCCUR_ZeroOrOnce);
	DeclareArg(env, "style", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareArg(env, "name", VTYPE_string, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_MDIParentFrame, Create)
{
	Object_wx_MDIParentFrame *pSelf = Object_wx_MDIParentFrame::GetSelfObj(args);
	if (pSelf->IsInvalid(sig)) return Value::Null;
	wxWindow *parent = args.IsValid(0)?
			Object_wx_Window::GetObject(args, 0)->GetEntity() : NULL;
	wxWindowID id = static_cast<wxWindowID>(args.GetInt(1));
	wxString title = wxString::FromUTF8(args.GetString(2));
	wxPoint *pos = (wxPoint *)(&wxDefaultPosition);
	if (args.IsValid(3)) pos = Object_wx_Point::GetObject(args, 3)->GetEntity();
	wxSize *size = (wxSize *)(&wxDefaultSize);
	if (args.IsValid(4)) size = Object_wx_Size::GetObject(args, 4)->GetEntity();
	long style = wxDEFAULT_FRAME_STYLE | wxVSCROLL | wxHSCROLL;
	if (args.IsValid(5)) style = args.GetLong(5);
	wxString name = wxT("frame");
	if (args.IsValid(6)) name = wxString::FromUTF8(args.GetString(6));
	bool rtn = pSelf->GetEntity()->Create(parent, id, title, *pos, *size, style, name);
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_MDIParentFrame, GetClientSize)
{
	SetMode(RSLTMODE_Void, FLAG_Map);
#if 0
	DeclareArg(env, "width", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "height", VTYPE_number, OCCUR_Once);
#endif
}

Gura_ImplementMethod(wx_MDIParentFrame, GetClientSize)
{
#if 0
	Object_wx_MDIParentFrame *pSelf = Object_wx_MDIParentFrame::GetSelfObj(args);
	if (pSelf->IsInvalid(sig)) return Value::Null;
	int width = args.GetInt(0);
	int height = args.GetInt(1);
	pSelf->GetEntity()->GetClientSize(width, height);
	return Value::Null;
#endif
	SetError_NotImplemented(sig);
	return Value::Null;
}

Gura_DeclareMethod(wx_MDIParentFrame, GetActiveChild)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_MDIParentFrame, GetActiveChild)
{
	Object_wx_MDIParentFrame *pSelf = Object_wx_MDIParentFrame::GetSelfObj(args);
	if (pSelf->IsInvalid(sig)) return Value::Null;
	wxMDIChildFrame *rtn = (wxMDIChildFrame *)pSelf->GetEntity()->GetActiveChild();
	return ReturnValue(env, sig, args, Value(new Object_wx_MDIChildFrame(rtn, NULL, OwnerFalse)));
}

Gura_DeclareMethod(wx_MDIParentFrame, GetClientWindow)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_MDIParentFrame, GetClientWindow)
{
	Object_wx_MDIParentFrame *pSelf = Object_wx_MDIParentFrame::GetSelfObj(args);
	if (pSelf->IsInvalid(sig)) return Value::Null;
	wxMDIClientWindow *rtn = (wxMDIClientWindow *)pSelf->GetEntity()->GetClientWindow();
	return ReturnValue(env, sig, args, Value(new Object_wx_MDIClientWindow(rtn, NULL, OwnerFalse)));
}

Gura_DeclareMethod(wx_MDIParentFrame, GetToolBar)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_MDIParentFrame, GetToolBar)
{
	Object_wx_MDIParentFrame *pSelf = Object_wx_MDIParentFrame::GetSelfObj(args);
	if (pSelf->IsInvalid(sig)) return Value::Null;
	wxToolBar *rtn = (wxToolBar *)pSelf->GetEntity()->GetToolBar();
	return ReturnValue(env, sig, args, Value(new Object_wx_ToolBar(rtn, NULL, OwnerFalse)));
}

Gura_DeclareMethod(wx_MDIParentFrame, GetWindowMenu)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_MDIParentFrame, GetWindowMenu)
{
#if defined(__WXMSW__)
	Object_wx_MDIParentFrame *pSelf = Object_wx_MDIParentFrame::GetSelfObj(args);
	if (pSelf->IsInvalid(sig)) return Value::Null;
	wxMenu *rtn = (wxMenu *)pSelf->GetEntity()->GetWindowMenu();
	return ReturnValue(env, sig, args, Value(new Object_wx_Menu(rtn, NULL, OwnerFalse)));
#else
	SetError_MSWOnly(sig);
	return Value::Null;
#endif	
}

Gura_DeclareMethod(wx_MDIParentFrame, OnCreateClient)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_MDIParentFrame, OnCreateClient)
{
	Object_wx_MDIParentFrame *pSelf = Object_wx_MDIParentFrame::GetSelfObj(args);
	if (pSelf->IsInvalid(sig)) return Value::Null;
	wxMDIClientWindow *rtn = (wxMDIClientWindow *)pSelf->GetEntity()->OnCreateClient();
	return ReturnValue(env, sig, args, Value(new Object_wx_MDIClientWindow(rtn, NULL, OwnerFalse)));
}

Gura_DeclareMethod(wx_MDIParentFrame, SetToolBar)
{
	SetMode(RSLTMODE_Void, FLAG_Map);
#if 0
	DeclareArg(env, "toolbar", VTYPE_wx_Window, OCCUR_Once);
#endif
}

Gura_ImplementMethod(wx_MDIParentFrame, SetToolBar)
{
#if 0
	Object_wx_MDIParentFrame *pSelf = Object_wx_MDIParentFrame::GetSelfObj(args);
	if (pSelf->IsInvalid(sig)) return Value::Null;
	wxWindow *toolbar = Object_wx_Window::GetObject(args, 0)->GetEntity();
	pSelf->GetEntity()->SetToolBar(toolbar);
	return Value::Null;
#endif
	SetError_NotImplemented(sig);
	return Value::Null;
}

Gura_DeclareMethod(wx_MDIParentFrame, SetWindowMenu)
{
	SetMode(RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "menu", VTYPE_wx_Menu, OCCUR_Once);
}

Gura_ImplementMethod(wx_MDIParentFrame, SetWindowMenu)
{
#if defined(__WXMSW__)
	Object_wx_MDIParentFrame *pSelf = Object_wx_MDIParentFrame::GetSelfObj(args);
	if (pSelf->IsInvalid(sig)) return Value::Null;
	wxMenu *menu = Object_wx_Menu::GetObject(args, 0)->GetEntity();
	pSelf->GetEntity()->SetWindowMenu(menu);
	return Value::Null;
#else
	SetError_MSWOnly(sig);
	return Value::Null;
#endif	
}

Gura_DeclareMethod(wx_MDIParentFrame, Tile)
{
	SetMode(RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "orient", VTYPE_number, OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_MDIParentFrame, Tile)
{
	Object_wx_MDIParentFrame *pSelf = Object_wx_MDIParentFrame::GetSelfObj(args);
	if (pSelf->IsInvalid(sig)) return Value::Null;
	wxOrientation orient = wxHORIZONTAL;
	if (args.IsValid(0)) orient = static_cast<wxOrientation>(args.GetInt(0));
	pSelf->GetEntity()->Tile(orient);
	return Value::Null;
}

//----------------------------------------------------------------------------
// Object implementation for wxMDIParentFrame
//----------------------------------------------------------------------------
Object_wx_MDIParentFrame::~Object_wx_MDIParentFrame()
{
}

Object *Object_wx_MDIParentFrame::Clone() const
{
	return NULL;
}

String Object_wx_MDIParentFrame::ToString(Signal sig, bool exprFlag)
{
	String rtn("<wx.MDIParentFrame:");
	if (GetEntity() == NULL) {
		rtn += "invalid>";
	} else {
		char buff[64];
		::sprintf(buff, "%p>", GetEntity());
		rtn += buff;
	}
	return rtn;
}

void Object_wx_MDIParentFrame::OnModuleEntry(Environment &env, Signal sig)
{
	Gura_RealizeUserSymbol(GetClientSize);
	Gura_RealizeUserSymbol(GetToolBar);
	Gura_RealizeUserSymbol(OnCreateClient);
	Gura_RealizeUserSymbol(SetToolBar);
	Gura_AssignFunction(MDIParentFrameEmpty);
	Gura_AssignFunction(MDIParentFrame);
}

//----------------------------------------------------------------------------
// Class implementation for wxMDIParentFrame
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_MDIParentFrame)
{
	Gura_AssignMethod(wx_MDIParentFrame, ActivateNext);
	Gura_AssignMethod(wx_MDIParentFrame, ActivatePrevious);
	Gura_AssignMethod(wx_MDIParentFrame, ArrangeIcons);
	Gura_AssignMethod(wx_MDIParentFrame, Cascade);
	Gura_AssignMethod(wx_MDIParentFrame, Create);
	Gura_AssignMethod(wx_MDIParentFrame, GetClientSize);
	Gura_AssignMethod(wx_MDIParentFrame, GetActiveChild);
	Gura_AssignMethod(wx_MDIParentFrame, GetClientWindow);
	Gura_AssignMethod(wx_MDIParentFrame, GetToolBar);
	Gura_AssignMethod(wx_MDIParentFrame, GetWindowMenu);
	Gura_AssignMethod(wx_MDIParentFrame, OnCreateClient);
	Gura_AssignMethod(wx_MDIParentFrame, SetToolBar);
	Gura_AssignMethod(wx_MDIParentFrame, SetWindowMenu);
	Gura_AssignMethod(wx_MDIParentFrame, Tile);
}

Gura_ImplementDescendantCreator(wx_MDIParentFrame)
{
	return new Object_wx_MDIParentFrame((pClass == NULL)? this : pClass, NULL, NULL, OwnerFalse);
}

}}
