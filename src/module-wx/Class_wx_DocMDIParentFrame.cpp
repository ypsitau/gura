//----------------------------------------------------------------------------
// wxDocMDIParentFrame
// extracted from docmdipr.tex
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Class derivation
//----------------------------------------------------------------------------
class wx_DocMDIParentFrame: public wxDocMDIParentFrame, public GuraObjectObserver {
private:
	//Gura::Signal *_pSig;
	Object_wx_DocMDIParentFrame *_pObj;
public:
	inline wx_DocMDIParentFrame() : wxDocMDIParentFrame(), _pObj(nullptr) {}
	inline wx_DocMDIParentFrame(wxDocManager* manager, wxFrame * parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style, const wxString& name) : wxDocMDIParentFrame(manager, parent, id, title, pos, size, style, name), _pObj(nullptr) {}
	~wx_DocMDIParentFrame();
	inline void AssocWithGura(Object_wx_DocMDIParentFrame *pObj) {
		_pObj = pObj;
	}
	// virtual function of GuraObjectObserver
	virtual void GuraObjectDeleted();
};

wx_DocMDIParentFrame::~wx_DocMDIParentFrame()
{
	if (_pObj != nullptr) _pObj->InvalidateEntity();
}

void wx_DocMDIParentFrame::GuraObjectDeleted()
{
	_pObj = nullptr;
}

//----------------------------------------------------------------------------
// Gura interfaces for wxDocMDIParentFrame
//----------------------------------------------------------------------------
Gura_DeclareFunction(DocMDIParentFrameEmpty)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	SetClassToConstruct(Gura_UserClass(wx_DocMDIParentFrame));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(DocMDIParentFrameEmpty)
{
	Signal &sig = env.GetSignal();
	if (!CheckWxReady(sig)) return Value::Nil;
	wx_DocMDIParentFrame *pEntity = new wx_DocMDIParentFrame();
	Object_wx_DocMDIParentFrame *pObj = Object_wx_DocMDIParentFrame::GetObjectThis(arg);
	if (pObj == nullptr) {
		pObj = new Object_wx_DocMDIParentFrame(pEntity, pEntity, OwnerFalse);
		pEntity->AssocWithGura(pObj);
		return ReturnValue(env, arg, Value(pObj));
	}
	pObj->SetEntity(pEntity, pEntity, OwnerFalse);
	pEntity->AssocWithGura(pObj);
	return ReturnValue(env, arg, arg.GetValueThis());
}

Gura_DeclareFunction(DocMDIParentFrame)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	SetClassToConstruct(Gura_UserClass(wx_DocMDIParentFrame));
	DeclareArg(env, "manager", VTYPE_wx_DocManager, OCCUR_Once);
	DeclareArg(env, "parent", VTYPE_wx_Frame, OCCUR_Once);
	DeclareArg(env, "id", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "title", VTYPE_string, OCCUR_Once);
	DeclareArg(env, "pos", VTYPE_wx_Point, OCCUR_ZeroOrOnce);
	DeclareArg(env, "size", VTYPE_wx_Size, OCCUR_ZeroOrOnce);
	DeclareArg(env, "style", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareArg(env, "name", VTYPE_string, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(DocMDIParentFrame)
{
	Signal &sig = env.GetSignal();
	if (!CheckWxReady(sig)) return Value::Nil;
	wxDocManager *manager = Object_wx_DocManager::GetObject(arg, 0)->GetEntity();
	wxFrame *parent = Object_wx_Frame::GetObject(arg, 1)->GetEntity();
	wxWindowID id = static_cast<wxWindowID>(arg.GetInt(2));
	wxString title = wxString::FromUTF8(arg.GetString(3));
	wxPoint *pos = (wxPoint *)(&wxDefaultPosition);
	if (arg.IsValid(4)) pos = Object_wx_Point::GetObject(arg, 4)->GetEntity();
	wxSize *size = (wxSize *)(&wxDefaultSize);
	if (arg.IsValid(5)) size = Object_wx_Size::GetObject(arg, 5)->GetEntity();
	long style = wxDEFAULT_FRAME_STYLE;
	if (arg.IsValid(6)) style = arg.GetLong(6);
	wxString name = wxT("frame");
	if (arg.IsValid(7)) name = wxString::FromUTF8(arg.GetString(7));
	wx_DocMDIParentFrame *pEntity = new wx_DocMDIParentFrame(manager, parent, id, title, *pos, *size, style, name);
	Object_wx_DocMDIParentFrame *pObj = Object_wx_DocMDIParentFrame::GetObjectThis(arg);
	if (pObj == nullptr) {
		pObj = new Object_wx_DocMDIParentFrame(pEntity, pEntity, OwnerFalse);
		pEntity->AssocWithGura(pObj);
		return ReturnValue(env, arg, Value(pObj));
	}
	pObj->SetEntity(pEntity, pEntity, OwnerFalse);
	pEntity->AssocWithGura(pObj);
	return ReturnValue(env, arg, arg.GetValueThis());
}

Gura_DeclareMethod(wx_DocMDIParentFrame, Create)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "manager", VTYPE_wx_DocManager, OCCUR_Once);
	DeclareArg(env, "parent", VTYPE_wx_Frame, OCCUR_Once);
	DeclareArg(env, "id", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "title", VTYPE_string, OCCUR_Once);
	DeclareArg(env, "pos", VTYPE_wx_Point, OCCUR_ZeroOrOnce);
	DeclareArg(env, "size", VTYPE_wx_Size, OCCUR_ZeroOrOnce);
	DeclareArg(env, "style", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareArg(env, "name", VTYPE_string, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_DocMDIParentFrame, Create)
{
	Signal &sig = env.GetSignal();
	Object_wx_DocMDIParentFrame *pThis = Object_wx_DocMDIParentFrame::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxDocManager *manager = Object_wx_DocManager::GetObject(arg, 0)->GetEntity();
	wxFrame *parent = Object_wx_Frame::GetObject(arg, 1)->GetEntity();
	wxWindowID id = static_cast<wxWindowID>(arg.GetInt(2));
	wxString title = wxString::FromUTF8(arg.GetString(3));
	wxPoint *pos = (wxPoint *)(&wxDefaultPosition);
	if (arg.IsValid(4)) pos = Object_wx_Point::GetObject(arg, 4)->GetEntity();
	wxSize *size = (wxSize *)(&wxDefaultSize);
	if (arg.IsValid(5)) size = Object_wx_Size::GetObject(arg, 5)->GetEntity();
	long style = wxDEFAULT_FRAME_STYLE;
	if (arg.IsValid(6)) style = arg.GetLong(6);
	wxString name = wxT("frame");
	if (arg.IsValid(7)) name = wxString::FromUTF8(arg.GetString(7));
	bool rtn = pThis->GetEntity()->Create(manager, parent, id, title, *pos, *size, style, name);
	return ReturnValue(env, arg, Value(rtn));
}

#if 0
Gura_DeclareMethod(wx_DocMDIParentFrame, OnCloseWindow)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "event", VTYPE_wx_CloseEvent, OCCUR_Once);
}

Gura_ImplementMethod(wx_DocMDIParentFrame, OnCloseWindow)
{
	Signal &sig = env.GetSignal();
	Object_wx_DocMDIParentFrame *pThis = Object_wx_DocMDIParentFrame::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxCloseEvent *event = Object_wx_CloseEvent::GetObject(arg, 0)->GetEntity();
	pThis->GetEntity()->OnCloseWindow(*event);
	return Value::Nil;
}
#endif

//----------------------------------------------------------------------------
// Object implementation for wxDocMDIParentFrame
//----------------------------------------------------------------------------
Object_wx_DocMDIParentFrame::~Object_wx_DocMDIParentFrame()
{
}

Object *Object_wx_DocMDIParentFrame::Clone() const
{
	return nullptr;
}

String Object_wx_DocMDIParentFrame::ToString(bool exprFlag)
{
	String rtn("<wx.DocMDIParentFrame:");
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
// Class implementation for wxDocMDIParentFrame
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_DocMDIParentFrame)
{
	Gura_AssignFunction(DocMDIParentFrameEmpty);
	Gura_AssignFunction(DocMDIParentFrame);
	Gura_AssignMethod(wx_DocMDIParentFrame, Create);
	//Gura_AssignMethod(wx_DocMDIParentFrame, OnCloseWindow);
}

Gura_ImplementDescendantCreator(wx_DocMDIParentFrame)
{
	return new Object_wx_DocMDIParentFrame((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
