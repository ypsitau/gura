//----------------------------------------------------------------------------
// wxToolBar
// extracted from toolbar.tex
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Class derivation
//----------------------------------------------------------------------------
class wx_ToolBar: public wxToolBar, public GuraObjectObserver {
private:
	//Gura::Signal *_pSig;
	Object_wx_ToolBar *_pObj;
public:
	inline wx_ToolBar() : wxToolBar(), _pObj(nullptr) {}
	inline wx_ToolBar(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name) : wxToolBar(parent, id, pos, size, style, name), _pObj(nullptr) {}
	~wx_ToolBar();
	inline void AssocWithGura(Object_wx_ToolBar *pObj) {
		_pObj = pObj;
	}
	// virtual function of GuraObjectObserver
	virtual void GuraObjectDeleted();
};

wx_ToolBar::~wx_ToolBar()
{
	if (_pObj != nullptr) _pObj->InvalidateEntity();
}

void wx_ToolBar::GuraObjectDeleted()
{
	_pObj = nullptr;
}

//----------------------------------------------------------------------------
// Gura interfaces for wxToolBar
//----------------------------------------------------------------------------
Gura_DeclareFunction(ToolBarEmpty)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	SetClassToConstruct(Gura_UserClass(wx_ToolBar));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(ToolBarEmpty)
{
	Signal &sig = env.GetSignal();
	if (!CheckWxReady(sig)) return Value::Nil;
	wx_ToolBar *pEntity = new wx_ToolBar();
	Object_wx_ToolBar *pObj = Object_wx_ToolBar::GetObjectThis(arg);
	if (pObj == nullptr) {
		pObj = new Object_wx_ToolBar(pEntity, pEntity, OwnerFalse);
		pEntity->AssocWithGura(pObj);
		return ReturnValue(env, arg, Value(pObj));
	}
	pObj->SetEntity(pEntity, pEntity, OwnerFalse);
	pEntity->AssocWithGura(pObj);
	return ReturnValue(env, arg, arg.GetValueThis());
}

Gura_DeclareFunction(ToolBar)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	SetClassToConstruct(Gura_UserClass(wx_ToolBar));
	DeclareArg(env, "parent", VTYPE_wx_Window, OCCUR_Once);
	DeclareArg(env, "id", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "pos", VTYPE_wx_Point, OCCUR_ZeroOrOnce);
	DeclareArg(env, "size", VTYPE_wx_Size, OCCUR_ZeroOrOnce);
	DeclareArg(env, "style", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareArg(env, "name", VTYPE_string, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(ToolBar)
{
	Signal &sig = env.GetSignal();
	if (!CheckWxReady(sig)) return Value::Nil;
	wxWindow *parent = Object_wx_Window::GetObject(arg, 0)->GetEntity();
	wxWindowID id = static_cast<wxWindowID>(arg.GetInt(1));
	wxPoint *pos = (wxPoint *)(&wxDefaultPosition);
	if (arg.IsValid(2)) pos = Object_wx_Point::GetObject(arg, 2)->GetEntity();
	wxSize *size = (wxSize *)(&wxDefaultSize);
	if (arg.IsValid(3)) size = Object_wx_Size::GetObject(arg, 3)->GetEntity();
	long style = wxTB_HORIZONTAL | wxNO_BORDER;
	if (arg.IsValid(4)) style = arg.GetLong(4);
	wxString name = wxPanelNameStr;
	if (arg.IsValid(5)) name = wxString::FromUTF8(arg.GetString(5));
	wx_ToolBar *pEntity = new wx_ToolBar(parent, id, *pos, *size, style, name);
	Object_wx_ToolBar *pObj = Object_wx_ToolBar::GetObjectThis(arg);
	if (pObj == nullptr) {
		pObj = new Object_wx_ToolBar(pEntity, pEntity, OwnerFalse);
		pEntity->AssocWithGura(pObj);
		return ReturnValue(env, arg, Value(pObj));
	}
	pObj->SetEntity(pEntity, pEntity, OwnerFalse);
	pEntity->AssocWithGura(pObj);
	return ReturnValue(env, arg, arg.GetValueThis());
}

Gura_DeclareMethod(wx_ToolBar, AddControl)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "control", VTYPE_wx_Control, OCCUR_Once);
	DeclareArg(env, "label", VTYPE_string, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_ToolBar, AddControl)
{
	Signal &sig = env.GetSignal();
	Object_wx_ToolBar *pThis = Object_wx_ToolBar::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxControl *control = Object_wx_Control::GetObject(arg, 0)->GetEntity();
	wxString label = wxEmptyString;
	if (arg.IsValid(1)) label = wxString::FromUTF8(arg.GetString(1));
	bool rtn = pThis->GetEntity()->AddControl(control, label);
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_ToolBar, AddSeparator)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_ToolBar, AddSeparator)
{
	Signal &sig = env.GetSignal();
	Object_wx_ToolBar *pThis = Object_wx_ToolBar::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxToolBarToolBase *rtn = pThis->GetEntity()->AddSeparator();
	return ReturnValue(env, arg, Value(new Object_wx_ToolBarToolBase(rtn, nullptr, OwnerFalse)));
}

Gura_DeclareMethod(wx_ToolBar, AddStretchableSpace)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_ToolBar, AddStretchableSpace)
{
	Signal &sig = env.GetSignal();
	Object_wx_ToolBar *pThis = Object_wx_ToolBar::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxToolBarToolBase *rtn = pThis->GetEntity()->AddStretchableSpace();
	return ReturnValue(env, arg, Value(new Object_wx_ToolBarToolBase(rtn, nullptr, OwnerFalse)));
}

Gura_DeclareMethod(wx_ToolBar, AddTool_1)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "toolId", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "label", VTYPE_string, OCCUR_Once);
	DeclareArg(env, "bitmap1", VTYPE_wx_Bitmap, OCCUR_Once);
	DeclareArg(env, "shortHelpString", VTYPE_string, OCCUR_ZeroOrOnce);
	DeclareArg(env, "kind", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_ToolBar, AddTool_1)
{
	Signal &sig = env.GetSignal();
	Object_wx_ToolBar *pThis = Object_wx_ToolBar::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	int toolId = arg.GetInt(0);
	wxString label = wxString::FromUTF8(arg.GetString(1));
	wxBitmap *bitmap1 = Object_wx_Bitmap::GetObject(arg, 2)->GetEntity();
	wxString shortHelpString = wxT("");
	if (arg.IsValid(3)) shortHelpString = wxString::FromUTF8(arg.GetString(3));
	wxItemKind kind = wxITEM_NORMAL;
	if (arg.IsValid(4)) kind = static_cast<wxItemKind>(arg.GetInt(4));
	wxToolBarToolBase *rtn = (wxToolBarToolBase *)pThis->GetEntity()->AddTool(toolId, label, *bitmap1, shortHelpString, kind);
	return ReturnValue(env, arg, Value(new Object_wx_ToolBarToolBase(rtn, nullptr, OwnerFalse)));
}

Gura_DeclareMethod(wx_ToolBar, AddTool)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "toolId", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "label", VTYPE_string, OCCUR_Once);
	DeclareArg(env, "bitmap1", VTYPE_wx_Bitmap, OCCUR_Once);
	DeclareArg(env, "bitmap2", VTYPE_wx_Bitmap, OCCUR_ZeroOrOnce);
	DeclareArg(env, "kind", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareArg(env, "shortHelpString", VTYPE_string, OCCUR_ZeroOrOnce);
	DeclareArg(env, "longHelpString", VTYPE_string, OCCUR_ZeroOrOnce);
	DeclareArg(env, "clientData", VTYPE_any, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_ToolBar, AddTool)
{
	Signal &sig = env.GetSignal();
	Object_wx_ToolBar *pThis = Object_wx_ToolBar::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	int toolId = arg.GetInt(0);
	wxString label = wxString::FromUTF8(arg.GetString(1));
	wxBitmap *bitmap1 = Object_wx_Bitmap::GetObject(arg, 2)->GetEntity();
	wxBitmap *bitmap2 = (wxBitmap *)(&wxNullBitmap);
	if (arg.IsValid(3)) bitmap2 = Object_wx_Bitmap::GetObject(arg, 3)->GetEntity();
	wxItemKind kind = wxITEM_NORMAL;
	if (arg.IsValid(4)) kind = static_cast<wxItemKind>(arg.GetInt(4));
	wxString shortHelpString = wxT("");
	if (arg.IsValid(5)) shortHelpString = wxString::FromUTF8(arg.GetString(5));
	wxString longHelpString = wxT("");
	if (arg.IsValid(6)) longHelpString = wxString::FromUTF8(arg.GetString(6));
	wxObject *clientData = nullptr;
	if (arg.IsValid(7)) clientData = new ObjectWithValue(arg.GetValue(7));
	wxToolBarToolBase *rtn = (wxToolBarToolBase *)pThis->GetEntity()->AddTool(toolId, label, *bitmap1, *bitmap2, kind, shortHelpString, longHelpString, clientData);
	return ReturnValue(env, arg, Value(new Object_wx_ToolBarToolBase(rtn, nullptr, OwnerFalse)));
}

Gura_DeclareMethod(wx_ToolBar, AddTool_2)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "tool", VTYPE_wx_ToolBarToolBase, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_ToolBar, AddTool_2)
{
	Signal &sig = env.GetSignal();
	Object_wx_ToolBar *pThis = Object_wx_ToolBar::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxToolBarToolBase *tool = Object_wx_ToolBarToolBase::GetObject(arg, 0)->GetEntity();
	wxToolBarToolBase *rtn = (wxToolBarToolBase *)pThis->GetEntity()->AddTool(tool);
	return ReturnValue(env, arg, Value(new Object_wx_ToolBarToolBase(rtn, nullptr, OwnerFalse)));
}

Gura_DeclareMethod(wx_ToolBar, AddCheckTool)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "toolId", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "label", VTYPE_string, OCCUR_Once);
	DeclareArg(env, "bitmap1", VTYPE_wx_Bitmap, OCCUR_Once);
	DeclareArg(env, "bitmap2", VTYPE_wx_Bitmap, OCCUR_Once);
	DeclareArg(env, "shortHelpString", VTYPE_string, OCCUR_ZeroOrOnce);
	DeclareArg(env, "longHelpString", VTYPE_string, OCCUR_ZeroOrOnce);
	DeclareArg(env, "clientData", VTYPE_wx_Object, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_ToolBar, AddCheckTool)
{
	Signal &sig = env.GetSignal();
	Object_wx_ToolBar *pThis = Object_wx_ToolBar::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	int toolId = arg.GetInt(0);
	wxString label = wxString::FromUTF8(arg.GetString(1));
	wxBitmap *bitmap1 = Object_wx_Bitmap::GetObject(arg, 2)->GetEntity();
	wxBitmap *bitmap2 = Object_wx_Bitmap::GetObject(arg, 3)->GetEntity();
	wxString shortHelpString = wxT("");
	if (arg.IsValid(4)) shortHelpString = wxString::FromUTF8(arg.GetString(4));
	wxString longHelpString = wxT("");
	if (arg.IsValid(5)) longHelpString = wxString::FromUTF8(arg.GetString(5));
	wxObject *clientData = nullptr;
	if (arg.IsValid(6)) clientData = new ObjectWithValue(arg.GetValue(6));
	wxToolBarToolBase *rtn = (wxToolBarToolBase *)pThis->GetEntity()->AddCheckTool(toolId, label, *bitmap1, *bitmap2, shortHelpString, longHelpString, clientData);
	return ReturnValue(env, arg, Value(new Object_wx_ToolBarToolBase(rtn, nullptr, OwnerFalse)));
}

Gura_DeclareMethod(wx_ToolBar, AddRadioTool)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "toolId", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "label", VTYPE_string, OCCUR_Once);
	DeclareArg(env, "bitmap1", VTYPE_wx_Bitmap, OCCUR_Once);
	DeclareArg(env, "bitmap2", VTYPE_wx_Bitmap, OCCUR_Once);
	DeclareArg(env, "shortHelpString", VTYPE_string, OCCUR_ZeroOrOnce);
	DeclareArg(env, "longHelpString", VTYPE_string, OCCUR_ZeroOrOnce);
	DeclareArg(env, "clientData", VTYPE_wx_Object, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_ToolBar, AddRadioTool)
{
	Signal &sig = env.GetSignal();
	Object_wx_ToolBar *pThis = Object_wx_ToolBar::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	int toolId = arg.GetInt(0);
	wxString label = wxString::FromUTF8(arg.GetString(1));
	wxBitmap *bitmap1 = Object_wx_Bitmap::GetObject(arg, 2)->GetEntity();
	wxBitmap *bitmap2 = Object_wx_Bitmap::GetObject(arg, 3)->GetEntity();
	wxString shortHelpString = wxT("");
	if (arg.IsValid(4)) shortHelpString = wxString::FromUTF8(arg.GetString(4));
	wxString longHelpString = wxT("");
	if (arg.IsValid(5)) longHelpString = wxString::FromUTF8(arg.GetString(5));
	wxObject *clientData = nullptr;
	if (arg.IsValid(6)) clientData = new ObjectWithValue(arg.GetValue(6));
	wxToolBarToolBase *rtn = (wxToolBarToolBase *)pThis->GetEntity()->AddRadioTool(toolId, label, *bitmap1, *bitmap2, shortHelpString, longHelpString, clientData);
	return ReturnValue(env, arg, Value(new Object_wx_ToolBarToolBase(rtn, nullptr, OwnerFalse)));
}

Gura_DeclareMethod(wx_ToolBar, ClearTools)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_ToolBar, ClearTools)
{
	Signal &sig = env.GetSignal();
	Object_wx_ToolBar *pThis = Object_wx_ToolBar::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	pThis->GetEntity()->ClearTools();
	return Value::Nil;
}

Gura_DeclareMethod(wx_ToolBar, DeleteTool)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "toolId", VTYPE_number, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_ToolBar, DeleteTool)
{
	Signal &sig = env.GetSignal();
	Object_wx_ToolBar *pThis = Object_wx_ToolBar::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	int toolId = arg.GetInt(0);
	bool rtn = pThis->GetEntity()->DeleteTool(toolId);
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_ToolBar, DeleteToolByPos)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "pos", VTYPE_number, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_ToolBar, DeleteToolByPos)
{
	Signal &sig = env.GetSignal();
	Object_wx_ToolBar *pThis = Object_wx_ToolBar::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	size_t pos = arg.GetSizeT(0);
	bool rtn = pThis->GetEntity()->DeleteToolByPos(pos);
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_ToolBar, EnableTool)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "toolId", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "enable", VTYPE_boolean, OCCUR_Once);
}

Gura_ImplementMethod(wx_ToolBar, EnableTool)
{
	Signal &sig = env.GetSignal();
	Object_wx_ToolBar *pThis = Object_wx_ToolBar::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	int toolId = arg.GetInt(0);
	bool enable = arg.GetBoolean(1);
	pThis->GetEntity()->EnableTool(toolId, enable);
	return Value::Nil;
}

Gura_DeclareMethod(wx_ToolBar, FindById)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "id", VTYPE_number, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_ToolBar, FindById)
{
	Signal &sig = env.GetSignal();
	Object_wx_ToolBar *pThis = Object_wx_ToolBar::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	int id = arg.GetInt(0);
	wxToolBarToolBase *rtn = (wxToolBarToolBase *)pThis->GetEntity()->FindById(id);
	return ReturnValue(env, arg, Value(new Object_wx_ToolBarToolBase(rtn, nullptr, OwnerFalse)));
}

Gura_DeclareMethod(wx_ToolBar, FindControl)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "id", VTYPE_number, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_ToolBar, FindControl)
{
	Signal &sig = env.GetSignal();
	Object_wx_ToolBar *pThis = Object_wx_ToolBar::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	int id = arg.GetInt(0);
	wxControl *rtn = (wxControl *)pThis->GetEntity()->FindControl(id);
	return ReturnValue(env, arg, Value(new Object_wx_Control(rtn, nullptr, OwnerFalse)));
}

Gura_DeclareMethod(wx_ToolBar, FindToolForPosition)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "x", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "y", VTYPE_number, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_ToolBar, FindToolForPosition)
{
	Signal &sig = env.GetSignal();
	Object_wx_ToolBar *pThis = Object_wx_ToolBar::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxCoord x = static_cast<wxCoord>(arg.GetInt(0));
	wxCoord y = static_cast<wxCoord>(arg.GetInt(1));
	wxToolBarToolBase *rtn = (wxToolBarToolBase *)pThis->GetEntity()->FindToolForPosition(x, y);
	return ReturnValue(env, arg, Value(new Object_wx_ToolBarToolBase(rtn, nullptr, OwnerFalse)));
}

Gura_DeclareMethod(wx_ToolBar, GetToolsCount)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_ToolBar, GetToolsCount)
{
	Signal &sig = env.GetSignal();
	Object_wx_ToolBar *pThis = Object_wx_ToolBar::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	int rtn = pThis->GetEntity()->GetToolsCount();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_ToolBar, GetToolSize)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_ToolBar, GetToolSize)
{
	Signal &sig = env.GetSignal();
	Object_wx_ToolBar *pThis = Object_wx_ToolBar::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxSize rtn = pThis->GetEntity()->GetToolSize();
	return ReturnValue(env, arg, Value(new Object_wx_Size(new wxSize(rtn), nullptr, OwnerTrue)));
}

Gura_DeclareMethod(wx_ToolBar, GetToolBitmapSize)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_ToolBar, GetToolBitmapSize)
{
	Signal &sig = env.GetSignal();
	Object_wx_ToolBar *pThis = Object_wx_ToolBar::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxSize rtn = pThis->GetEntity()->GetToolBitmapSize();
	return ReturnValue(env, arg, Value(new Object_wx_Size(new wxSize(rtn), nullptr, OwnerTrue)));
}

Gura_DeclareMethod(wx_ToolBar, GetMargins)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_ToolBar, GetMargins)
{
	Signal &sig = env.GetSignal();
	Object_wx_ToolBar *pThis = Object_wx_ToolBar::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxSize rtn = pThis->GetEntity()->GetMargins();
	return ReturnValue(env, arg, Value(new Object_wx_Size(new wxSize(rtn), nullptr, OwnerTrue)));
}

Gura_DeclareMethod(wx_ToolBar, GetToolClientData)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "toolId", VTYPE_number, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_ToolBar, GetToolClientData)
{
	Signal &sig = env.GetSignal();
	Object_wx_ToolBar *pThis = Object_wx_ToolBar::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	int toolId = arg.GetInt(0);
	ObjectWithValue *rtn = wxDynamicCast(
				pThis->GetEntity()->GetToolClientData(toolId), ObjectWithValue);
	Value result;
	if (rtn != nullptr) result = rtn->GetValue();
	return ReturnValue(env, arg, result);
}

Gura_DeclareMethod(wx_ToolBar, GetToolEnabled)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "toolId", VTYPE_number, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_ToolBar, GetToolEnabled)
{
	Signal &sig = env.GetSignal();
	Object_wx_ToolBar *pThis = Object_wx_ToolBar::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	int toolId = arg.GetInt(0);
	bool rtn = pThis->GetEntity()->GetToolEnabled(toolId);
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_ToolBar, GetToolLongHelp)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "toolId", VTYPE_number, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_ToolBar, GetToolLongHelp)
{
	Signal &sig = env.GetSignal();
	Object_wx_ToolBar *pThis = Object_wx_ToolBar::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	int toolId = arg.GetInt(0);
	wxString rtn = pThis->GetEntity()->GetToolLongHelp(toolId);
	return ReturnValue(env, arg, Value(static_cast<const char *>(rtn.ToUTF8())));
}

Gura_DeclareMethod(wx_ToolBar, GetToolPacking)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_ToolBar, GetToolPacking)
{
	Signal &sig = env.GetSignal();
	Object_wx_ToolBar *pThis = Object_wx_ToolBar::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	int rtn = pThis->GetEntity()->GetToolPacking();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_ToolBar, GetToolPos)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "toolId", VTYPE_number, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_ToolBar, GetToolPos)
{
	Signal &sig = env.GetSignal();
	Object_wx_ToolBar *pThis = Object_wx_ToolBar::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	int toolId = arg.GetInt(0);
	int rtn = pThis->GetEntity()->GetToolPos(toolId);
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_ToolBar, GetToolSeparation)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_ToolBar, GetToolSeparation)
{
	Signal &sig = env.GetSignal();
	Object_wx_ToolBar *pThis = Object_wx_ToolBar::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	int rtn = pThis->GetEntity()->GetToolSeparation();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_ToolBar, GetToolShortHelp)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "toolId", VTYPE_number, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_ToolBar, GetToolShortHelp)
{
	Signal &sig = env.GetSignal();
	Object_wx_ToolBar *pThis = Object_wx_ToolBar::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	int toolId = arg.GetInt(0);
	wxString rtn = pThis->GetEntity()->GetToolShortHelp(toolId);
	return ReturnValue(env, arg, Value(static_cast<const char *>(rtn.ToUTF8())));
}

Gura_DeclareMethod(wx_ToolBar, GetToolState)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "toolId", VTYPE_number, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_ToolBar, GetToolState)
{
	Signal &sig = env.GetSignal();
	Object_wx_ToolBar *pThis = Object_wx_ToolBar::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	int toolId = arg.GetInt(0);
	bool rtn = pThis->GetEntity()->GetToolState(toolId);
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_ToolBar, InsertControl)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "pos", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "control", VTYPE_wx_Control, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_ToolBar, InsertControl)
{
	Signal &sig = env.GetSignal();
	Object_wx_ToolBar *pThis = Object_wx_ToolBar::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	size_t pos = arg.GetSizeT(0);
	wxControl *control = Object_wx_Control::GetObject(arg, 1)->GetEntity();
	wxToolBarToolBase *rtn = (wxToolBarToolBase *)pThis->GetEntity()->InsertControl(pos, control);
	return ReturnValue(env, arg, Value(new Object_wx_ToolBarToolBase(rtn, nullptr, OwnerFalse)));
}

Gura_DeclareMethod(wx_ToolBar, InsertSeparator)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "pos", VTYPE_number, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_ToolBar, InsertSeparator)
{
	Signal &sig = env.GetSignal();
	Object_wx_ToolBar *pThis = Object_wx_ToolBar::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	size_t pos = arg.GetSizeT(0);
	wxToolBarToolBase *rtn = (wxToolBarToolBase *)pThis->GetEntity()->InsertSeparator(pos);
	return ReturnValue(env, arg, Value(new Object_wx_ToolBarToolBase(rtn, nullptr, OwnerFalse)));
}

Gura_DeclareMethod(wx_ToolBar, InsertTool)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "pos", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "toolId", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "label", VTYPE_string, OCCUR_Once);
	DeclareArg(env, "bitmap", VTYPE_wx_Bitmap, OCCUR_Once);
	DeclareArg(env, "bmpDisabled", VTYPE_wx_Bitmap, OCCUR_ZeroOrOnce);
	DeclareArg(env, "kind", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareArg(env, "shortHelp", VTYPE_string, OCCUR_ZeroOrOnce);
	DeclareArg(env, "longHelp", VTYPE_string, OCCUR_ZeroOrOnce);
	DeclareArg(env, "clientData", VTYPE_wx_Object, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_ToolBar, InsertTool)
{
	Signal &sig = env.GetSignal();
	Object_wx_ToolBar *pThis = Object_wx_ToolBar::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	size_t pos = arg.GetSizeT(0);
	int toolId = arg.GetInt(1);
	wxString label = wxString::FromUTF8(arg.GetString(2));
	wxBitmap *bitmap = Object_wx_Bitmap::GetObject(arg, 3)->GetEntity();
	wxBitmap *bmpDisabled = (wxBitmap *)(&wxNullBitmap);
	if (arg.IsValid(4)) bmpDisabled = Object_wx_Bitmap::GetObject(arg, 4)->GetEntity();
	wxItemKind kind = wxITEM_NORMAL;
	if (arg.IsValid(5)) kind = static_cast<wxItemKind>(arg.GetInt(5));
	wxString shortHelp = wxT("");
	if (arg.IsValid(6)) shortHelp = wxString::FromUTF8(arg.GetString(6));
	wxString longHelp = wxT("");
	if (arg.IsValid(7)) longHelp = wxString::FromUTF8(arg.GetString(7));
	wxObject *clientData = nullptr;
	if (arg.IsValid(8)) clientData = new ObjectWithValue(arg.GetValue(8));
	wxToolBarToolBase *rtn = (wxToolBarToolBase *)pThis->GetEntity()->InsertTool(pos, toolId, label, *bitmap, *bmpDisabled, kind, shortHelp, longHelp, clientData);
	return ReturnValue(env, arg, Value(new Object_wx_ToolBarToolBase(rtn, nullptr, OwnerFalse)));
}

Gura_DeclareMethod(wx_ToolBar, InsertTool_1)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "pos", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "tool", VTYPE_wx_ToolBarToolBase, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_ToolBar, InsertTool_1)
{
	Signal &sig = env.GetSignal();
	Object_wx_ToolBar *pThis = Object_wx_ToolBar::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	size_t pos = arg.GetSizeT(0);
	wxToolBarToolBase *tool = Object_wx_ToolBarToolBase::GetObject(arg, 1)->GetEntity();
	wxToolBarToolBase *rtn = (wxToolBarToolBase *)pThis->GetEntity()->InsertTool(pos, tool);
	return ReturnValue(env, arg, Value(new Object_wx_ToolBarToolBase(rtn, nullptr, OwnerFalse)));
}

Gura_DeclareMethod(wx_ToolBar, OnLeftClick)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "toolId", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "toggleDown", VTYPE_boolean, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_ToolBar, OnLeftClick)
{
	Signal &sig = env.GetSignal();
	Object_wx_ToolBar *pThis = Object_wx_ToolBar::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	int toolId = arg.GetInt(0);
	bool toggleDown = arg.GetBoolean(1);
	bool rtn = pThis->GetEntity()->OnLeftClick(toolId, toggleDown);
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_ToolBar, OnMouseEnter)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "toolId", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_ToolBar, OnMouseEnter)
{
	Signal &sig = env.GetSignal();
	Object_wx_ToolBar *pThis = Object_wx_ToolBar::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	int toolId = arg.GetInt(0);
	pThis->GetEntity()->OnMouseEnter(toolId);
	return Value::Nil;
}

Gura_DeclareMethod(wx_ToolBar, OnRightClick)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "toolId", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "x", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "y", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_ToolBar, OnRightClick)
{
	Signal &sig = env.GetSignal();
	Object_wx_ToolBar *pThis = Object_wx_ToolBar::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	int toolId = arg.GetInt(0);
	float x = arg.GetFloat(1);
	float y = arg.GetFloat(2);
	pThis->GetEntity()->OnRightClick(toolId, x, y);
	return Value::Nil;
}

Gura_DeclareMethod(wx_ToolBar, Realize)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_ToolBar, Realize)
{
	Signal &sig = env.GetSignal();
	Object_wx_ToolBar *pThis = Object_wx_ToolBar::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	bool rtn = pThis->GetEntity()->Realize();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_ToolBar, RemoveTool)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "id", VTYPE_number, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_ToolBar, RemoveTool)
{
	Signal &sig = env.GetSignal();
	Object_wx_ToolBar *pThis = Object_wx_ToolBar::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	int id = arg.GetInt(0);
	wxToolBarToolBase *rtn = (wxToolBarToolBase *)pThis->GetEntity()->RemoveTool(id);
	return ReturnValue(env, arg, Value(new Object_wx_ToolBarToolBase(rtn, nullptr, OwnerFalse)));
}

Gura_DeclareMethod(wx_ToolBar, SetBitmapResource)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
#if 0
	DeclareArg(env, "resourceId", VTYPE_number, OCCUR_Once);
#endif
}

Gura_ImplementMethod(wx_ToolBar, SetBitmapResource)
{
	Signal &sig = env.GetSignal();
#if 0
	Object_wx_ToolBar *pThis = Object_wx_ToolBar::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	int resourceId = arg.GetInt(0);
	pThis->GetEntity()->SetBitmapResource(resourceId);
	return Value::Nil;
#endif
	SetError_NotImplemented(sig);
	return Value::Nil;
}

Gura_DeclareMethod(wx_ToolBar, SetMargins)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "size", VTYPE_wx_Size, OCCUR_Once);
}

Gura_ImplementMethod(wx_ToolBar, SetMargins)
{
	Signal &sig = env.GetSignal();
#if defined(__WXMSW__)
	Object_wx_ToolBar *pThis = Object_wx_ToolBar::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxSize *size = Object_wx_Size::GetObject(arg, 0)->GetEntity();
	pThis->GetEntity()->SetMargins(*size);
	return Value::Nil;
#else
	SetError_MSWOnly(sig);
	return Value::Nil;
#endif	
}

Gura_DeclareMethod(wx_ToolBar, SetMargins_1)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "x", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "y", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_ToolBar, SetMargins_1)
{
	Signal &sig = env.GetSignal();
	Object_wx_ToolBar *pThis = Object_wx_ToolBar::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	int x = arg.GetInt(0);
	int y = arg.GetInt(1);
	pThis->GetEntity()->SetMargins(x, y);
	return Value::Nil;
}

Gura_DeclareMethod(wx_ToolBar, SetToolBitmapSize)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "size", VTYPE_wx_Size, OCCUR_Once);
}

Gura_ImplementMethod(wx_ToolBar, SetToolBitmapSize)
{
	Signal &sig = env.GetSignal();
	Object_wx_ToolBar *pThis = Object_wx_ToolBar::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxSize *size = Object_wx_Size::GetObject(arg, 0)->GetEntity();
	pThis->GetEntity()->SetToolBitmapSize(*size);
	return Value::Nil;
}

Gura_DeclareMethod(wx_ToolBar, SetToolClientData)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "id", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "clientData", VTYPE_any, OCCUR_Once);
}

Gura_ImplementMethod(wx_ToolBar, SetToolClientData)
{
	Signal &sig = env.GetSignal();
	Object_wx_ToolBar *pThis = Object_wx_ToolBar::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	int id = arg.GetInt(0);
	wxObject *clientData = new ObjectWithValue(arg.GetValue(1));
	pThis->GetEntity()->SetToolClientData(id, clientData);
	return Value::Nil;
}

Gura_DeclareMethod(wx_ToolBar, SetToolDisabledBitmap)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "id", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "bitmap", VTYPE_wx_Bitmap, OCCUR_Once);
}

Gura_ImplementMethod(wx_ToolBar, SetToolDisabledBitmap)
{
	Signal &sig = env.GetSignal();
	Object_wx_ToolBar *pThis = Object_wx_ToolBar::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	int id = arg.GetInt(0);
	wxBitmap *bitmap = Object_wx_Bitmap::GetObject(arg, 1)->GetEntity();
	pThis->GetEntity()->SetToolDisabledBitmap(id, *bitmap);
	return Value::Nil;
}

Gura_DeclareMethod(wx_ToolBar, SetToolLongHelp)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "toolId", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "helpString", VTYPE_string, OCCUR_Once);
}

Gura_ImplementMethod(wx_ToolBar, SetToolLongHelp)
{
	Signal &sig = env.GetSignal();
	Object_wx_ToolBar *pThis = Object_wx_ToolBar::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	int toolId = arg.GetInt(0);
	wxString helpString = wxString::FromUTF8(arg.GetString(1));
	pThis->GetEntity()->SetToolLongHelp(toolId, helpString);
	return Value::Nil;
}

Gura_DeclareMethod(wx_ToolBar, SetToolPacking)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "packing", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_ToolBar, SetToolPacking)
{
	Signal &sig = env.GetSignal();
	Object_wx_ToolBar *pThis = Object_wx_ToolBar::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	int packing = arg.GetInt(0);
	pThis->GetEntity()->SetToolPacking(packing);
	return Value::Nil;
}

Gura_DeclareMethod(wx_ToolBar, SetToolShortHelp)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "toolId", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "helpString", VTYPE_string, OCCUR_Once);
}

Gura_ImplementMethod(wx_ToolBar, SetToolShortHelp)
{
	Signal &sig = env.GetSignal();
	Object_wx_ToolBar *pThis = Object_wx_ToolBar::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	int toolId = arg.GetInt(0);
	wxString helpString = wxString::FromUTF8(arg.GetString(1));
	pThis->GetEntity()->SetToolShortHelp(toolId, helpString);
	return Value::Nil;
}

Gura_DeclareMethod(wx_ToolBar, SetToolNormalBitmap)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "id", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "bitmap", VTYPE_wx_Bitmap, OCCUR_Once);
}

Gura_ImplementMethod(wx_ToolBar, SetToolNormalBitmap)
{
	Signal &sig = env.GetSignal();
	Object_wx_ToolBar *pThis = Object_wx_ToolBar::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	int id = arg.GetInt(0);
	wxBitmap *bitmap = Object_wx_Bitmap::GetObject(arg, 1)->GetEntity();
	pThis->GetEntity()->SetToolNormalBitmap(id, *bitmap);
	return Value::Nil;
}

Gura_DeclareMethod(wx_ToolBar, SetToolSeparation)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "separation", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_ToolBar, SetToolSeparation)
{
	Signal &sig = env.GetSignal();
	Object_wx_ToolBar *pThis = Object_wx_ToolBar::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	int separation = arg.GetInt(0);
	pThis->GetEntity()->SetToolSeparation(separation);
	return Value::Nil;
}

Gura_DeclareMethod(wx_ToolBar, ToggleTool)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "toolId", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "toggle", VTYPE_boolean, OCCUR_Once);
}

Gura_ImplementMethod(wx_ToolBar, ToggleTool)
{
	Signal &sig = env.GetSignal();
	Object_wx_ToolBar *pThis = Object_wx_ToolBar::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	int toolId = arg.GetInt(0);
	bool toggle = arg.GetBoolean(1);
	pThis->GetEntity()->ToggleTool(toolId, toggle);
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Object implementation for wxToolBar
//----------------------------------------------------------------------------
Object_wx_ToolBar::~Object_wx_ToolBar()
{
}

Object *Object_wx_ToolBar::Clone() const
{
	return nullptr;
}

String Object_wx_ToolBar::ToString(bool exprFlag)
{
	String rtn("<wx.ToolBar:");
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
// Class implementation for wxToolBar
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_ToolBar)
{
	Gura_AssignFunction(ToolBarEmpty);
	Gura_AssignFunction(ToolBar);
	Gura_AssignMethod(wx_ToolBar, AddControl);
	Gura_AssignMethod(wx_ToolBar, AddSeparator);
	Gura_AssignMethod(wx_ToolBar, AddStretchableSpace);
	Gura_AssignMethod(wx_ToolBar, AddTool);
	Gura_AssignMethod(wx_ToolBar, AddTool_1);
	Gura_AssignMethod(wx_ToolBar, AddTool_2);
	Gura_AssignMethod(wx_ToolBar, AddCheckTool);
	Gura_AssignMethod(wx_ToolBar, AddRadioTool);
	Gura_AssignMethod(wx_ToolBar, ClearTools);
	Gura_AssignMethod(wx_ToolBar, DeleteTool);
	Gura_AssignMethod(wx_ToolBar, DeleteToolByPos);
	Gura_AssignMethod(wx_ToolBar, EnableTool);
	Gura_AssignMethod(wx_ToolBar, FindById);
	Gura_AssignMethod(wx_ToolBar, FindControl);
	Gura_AssignMethod(wx_ToolBar, FindToolForPosition);
	Gura_AssignMethod(wx_ToolBar, GetToolsCount);
	Gura_AssignMethod(wx_ToolBar, GetToolSize);
	Gura_AssignMethod(wx_ToolBar, GetToolBitmapSize);
	Gura_AssignMethod(wx_ToolBar, GetMargins);
	Gura_AssignMethod(wx_ToolBar, GetToolClientData);
	Gura_AssignMethod(wx_ToolBar, GetToolEnabled);
	Gura_AssignMethod(wx_ToolBar, GetToolLongHelp);
	Gura_AssignMethod(wx_ToolBar, GetToolPacking);
	Gura_AssignMethod(wx_ToolBar, GetToolPos);
	Gura_AssignMethod(wx_ToolBar, GetToolSeparation);
	Gura_AssignMethod(wx_ToolBar, GetToolShortHelp);
	Gura_AssignMethod(wx_ToolBar, GetToolState);
	Gura_AssignMethod(wx_ToolBar, InsertControl);
	Gura_AssignMethod(wx_ToolBar, InsertSeparator);
	Gura_AssignMethod(wx_ToolBar, InsertTool);
	Gura_AssignMethod(wx_ToolBar, InsertTool_1);
	Gura_AssignMethod(wx_ToolBar, OnLeftClick);
	Gura_AssignMethod(wx_ToolBar, OnMouseEnter);
	Gura_AssignMethod(wx_ToolBar, OnRightClick);
	Gura_AssignMethod(wx_ToolBar, Realize);
	Gura_AssignMethod(wx_ToolBar, RemoveTool);
	Gura_AssignMethod(wx_ToolBar, SetBitmapResource);
	Gura_AssignMethod(wx_ToolBar, SetMargins);
	Gura_AssignMethod(wx_ToolBar, SetMargins_1);
	Gura_AssignMethod(wx_ToolBar, SetToolBitmapSize);
	Gura_AssignMethod(wx_ToolBar, SetToolClientData);
	Gura_AssignMethod(wx_ToolBar, SetToolDisabledBitmap);
	Gura_AssignMethod(wx_ToolBar, SetToolLongHelp);
	Gura_AssignMethod(wx_ToolBar, SetToolPacking);
	Gura_AssignMethod(wx_ToolBar, SetToolShortHelp);
	Gura_AssignMethod(wx_ToolBar, SetToolNormalBitmap);
	Gura_AssignMethod(wx_ToolBar, SetToolSeparation);
	Gura_AssignMethod(wx_ToolBar, ToggleTool);
}

Gura_ImplementDescendantCreator(wx_ToolBar)
{
	return new Object_wx_ToolBar((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
