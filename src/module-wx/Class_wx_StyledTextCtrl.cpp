//----------------------------------------------------------------------------
// wxStyledTextCtrl
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Class derivation
//----------------------------------------------------------------------------
class wx_StyledTextCtrl: public wxStyledTextCtrl, public GuraObjectObserver {
private:
	Gura::Signal _sig;
	Object_wx_StyledTextCtrl *_pObj;
public:
	inline wx_StyledTextCtrl() : wxStyledTextCtrl(), _sig(NULL), _pObj(NULL) {}
	inline wx_StyledTextCtrl(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name) : wxStyledTextCtrl(parent, id, pos, size, style, name), _sig(NULL), _pObj(NULL) {}
	~wx_StyledTextCtrl();
	inline void AssocWithGura(Gura::Signal &sig, Object_wx_StyledTextCtrl *pObj) {
		_sig = sig, _pObj = pObj;
	}
	// virtual function of GuraObjectObserver
	virtual void GuraObjectDeleted();
};

wx_StyledTextCtrl::~wx_StyledTextCtrl()
{
	if (_pObj != NULL) _pObj->InvalidateEntity();
}

void wx_StyledTextCtrl::GuraObjectDeleted()
{
	_pObj = NULL;
}

//----------------------------------------------------------------------------
// Implementation of functions
//----------------------------------------------------------------------------
Gura_DeclareFunction(StyledTextCtrlEmpty)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	SetClassToConstruct(Gura_UserClass(wx_StyledTextCtrl));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(StyledTextCtrlEmpty)
{
	if (!CheckWxReady(sig)) return Value::Null;
	wx_StyledTextCtrl *pEntity = new wx_StyledTextCtrl();
	Object_wx_StyledTextCtrl *pObj = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pObj == NULL) {
		pObj = new Object_wx_StyledTextCtrl(pEntity, pEntity, OwnerFalse);
		pEntity->AssocWithGura(sig, pObj);
		return ReturnValue(env, sig, args, Value(pObj));
	}
	pObj->SetEntity(pEntity, pEntity, OwnerFalse);
	pEntity->AssocWithGura(sig, pObj);
	return ReturnValue(env, sig, args, args.GetThis());
}

Gura_DeclareFunction(StyledTextCtrl)
{
	SetMode(RSLTMODE_Normal, FLAG_Map);
	SetClassToConstruct(Gura_UserClass(wx_StyledTextCtrl));
	DeclareArg(env, "parent", VTYPE_wx_Window, OCCUR_Once);
	DeclareArg(env, "id", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "pos", VTYPE_wx_Point, OCCUR_ZeroOrOnce);
	DeclareArg(env, "size", VTYPE_wx_Size, OCCUR_ZeroOrOnce);
	DeclareArg(env, "style", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareArg(env, "name", VTYPE_string, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(StyledTextCtrl)
{
	if (!CheckWxReady(sig)) return Value::Null;
	wxWindow *parent = Object_wx_Window::GetObject(args, 0)->GetEntity();
	wxWindowID id = static_cast<wxWindowID>(args.GetInt(1));
	wxPoint *pos = (wxPoint *)(&wxDefaultPosition);
	if (args.IsValid(2)) pos = Object_wx_Point::GetObject(args, 2)->GetEntity();
	wxSize *size = (wxSize *)(&wxDefaultSize);
	if (args.IsValid(3)) size = Object_wx_Size::GetObject(args, 3)->GetEntity();
	long style = 0;
	if (args.IsValid(4)) style = args.GetLong(4);
	wxString name = wxSTCNameStr;
	if (args.IsValid(5)) name = wxString::FromUTF8(args.GetString(5));
	wx_StyledTextCtrl *pEntity = new wx_StyledTextCtrl(parent, id, *pos, *size, style, name);
	Object_wx_StyledTextCtrl *pObj = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pObj == NULL) {
		pObj = new Object_wx_StyledTextCtrl(pEntity, pEntity, OwnerFalse);
		pEntity->AssocWithGura(sig, pObj);
		return ReturnValue(env, sig, args, Value(pObj));
	}
	pObj->SetEntity(pEntity, pEntity, OwnerFalse);
	pEntity->AssocWithGura(sig, pObj);
	return ReturnValue(env, sig, args, args.GetThis());
}

//----------------------------------------------------------------------------
// Object_wxStyledTextCtrl
//----------------------------------------------------------------------------
Object_wx_StyledTextCtrl::~Object_wx_StyledTextCtrl()
{
}

Object *Object_wx_StyledTextCtrl::Clone() const
{
	return NULL;
}

String Object_wx_StyledTextCtrl::ToString(bool exprFlag)
{
	String rtn("<wx.StyledTextCtrl:");
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
// Implementation of methods
//----------------------------------------------------------------------------
Gura_DeclareMethod(wx_StyledTextCtrl, Create)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "parent",	VTYPE_wx_Window, OCCUR_Once);
	DeclareArg(env, "id",		VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareArg(env, "pos",		VTYPE_wx_Point, OCCUR_ZeroOrOnce);
	DeclareArg(env, "size",		VTYPE_wx_Size, OCCUR_ZeroOrOnce);
	DeclareArg(env, "style",	VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareArg(env, "name",		VTYPE_string, OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_StyledTextCtrl, Create)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	wxWindow *parent = Object_wx_Window::GetObject(args, 0)->GetEntity();
	wxWindowID id = wxID_ANY;
	if (args.IsValid(1)) id = static_cast<wxWindowID>(args.GetInt(1));
	wxPoint *pos = (wxPoint *)(&wxDefaultPosition);
	if (args.IsValid(2)) pos = Object_wx_Point::GetObject(args, 2)->GetEntity();
	wxSize *size = (wxSize *)(&wxDefaultSize);
	if (args.IsValid(3)) size = Object_wx_Size::GetObject(args, 3)->GetEntity();
	long style = 0;
	if (args.IsValid(4)) style = args.GetLong(4);
	wxString name = wxSTCNameStr;
	if (args.IsValid(5)) name = wxString::FromUTF8(args.GetString(5));
	bool rtn = pThis->GetEntity()->Create(parent, id, *pos, *size, style, name);
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, AddText)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "text",	VTYPE_string, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, AddText)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	wxString text = wxString::FromUTF8(args.GetString(0));
	pThis->GetEntity()->AddText(text);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, AddStyledText)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "data",	VTYPE_wx_MemoryBuffer, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, AddStyledText)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	wxMemoryBuffer *data = Object_wx_MemoryBuffer::GetObject(args, 0)->GetEntity();
	pThis->GetEntity()->AddStyledText(*data);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, InsertText)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "pos",	VTYPE_number, OCCUR_Once);
	DeclareArg(env, "text",	VTYPE_string, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, InsertText)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int pos = args.GetInt(0);
	wxString text = wxString::FromUTF8(args.GetString(1));
	pThis->GetEntity()->InsertText(pos, text);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, ClearAll)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, ClearAll)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->ClearAll();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, DeleteRange)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "pos",			VTYPE_number, OCCUR_Once);
	DeclareArg(env, "deleteLength",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, DeleteRange)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int pos = args.GetInt(0);
	int deleteLength = args.GetInt(1);
	pThis->GetEntity()->DeleteRange(pos, deleteLength);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, ClearDocumentStyle)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, ClearDocumentStyle)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->ClearDocumentStyle();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetLength)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetLength)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int rtn = pThis->GetEntity()->GetLength();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetCharAt)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "pos",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetCharAt)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int pos = args.GetInt(0);
	int rtn = pThis->GetEntity()->GetCharAt(pos);
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetCurrentPos)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetCurrentPos)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int rtn = pThis->GetEntity()->GetCurrentPos();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetAnchor)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetAnchor)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int rtn = pThis->GetEntity()->GetAnchor();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetStyleAt)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "pos",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetStyleAt)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int pos = args.GetInt(0);
	int rtn = pThis->GetEntity()->GetStyleAt(pos);
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, Redo)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, Redo)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->Redo();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetUndoCollection)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "collectUndo",	VTYPE_boolean, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetUndoCollection)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	bool collectUndo = args.GetBoolean(0);
	pThis->GetEntity()->SetUndoCollection(collectUndo);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, SelectAll)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SelectAll)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->SelectAll();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetSavePoint)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetSavePoint)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->SetSavePoint();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetStyledText)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "startPos",	VTYPE_number, OCCUR_Once);
	DeclareArg(env, "endPos",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetStyledText)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int startPos = args.GetInt(0);
	int endPos = args.GetInt(1);
	wxMemoryBuffer rtn = pThis->GetEntity()->GetStyledText(startPos, endPos);
	return ReturnValue(env, sig, args, Value(new Object_wx_MemoryBuffer(new wxMemoryBuffer(rtn), NULL, OwnerTrue)));
}

Gura_DeclareMethod(wx_StyledTextCtrl, CanRedo)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, CanRedo)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	bool rtn = pThis->GetEntity()->CanRedo();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, MarkerLineFromHandle)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "handle",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, MarkerLineFromHandle)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int handle = args.GetInt(0);
	int rtn = pThis->GetEntity()->MarkerLineFromHandle(handle);
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, MarkerDeleteHandle)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "handle",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, MarkerDeleteHandle)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int handle = args.GetInt(0);
	pThis->GetEntity()->MarkerDeleteHandle(handle);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetUndoCollection)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetUndoCollection)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	bool rtn = pThis->GetEntity()->GetUndoCollection();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetViewWhiteSpace)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetViewWhiteSpace)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int rtn = pThis->GetEntity()->GetViewWhiteSpace();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetViewWhiteSpace)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "viewWS",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetViewWhiteSpace)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int viewWS = args.GetInt(0);
	pThis->GetEntity()->SetViewWhiteSpace(viewWS);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, PositionFromPoint)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "pt",	VTYPE_wx_Point, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, PositionFromPoint)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	wxPoint *pt = Object_wx_Point::GetObject(args, 0)->GetEntity();
	int rtn = pThis->GetEntity()->PositionFromPoint(*pt);
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, PositionFromPointClose)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "x",	VTYPE_number, OCCUR_Once);
	DeclareArg(env, "y",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, PositionFromPointClose)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int x = args.GetInt(0);
	int y = args.GetInt(1);
	int rtn = pThis->GetEntity()->PositionFromPointClose(x, y);
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, GotoLine)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "line",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GotoLine)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int line = args.GetInt(0);
	pThis->GetEntity()->GotoLine(line);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, GotoPos)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "pos",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GotoPos)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int pos = args.GetInt(0);
	pThis->GetEntity()->GotoPos(pos);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetAnchor)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "posAnchor",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetAnchor)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int posAnchor = args.GetInt(0);
	pThis->GetEntity()->SetAnchor(posAnchor);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetCurLine)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "linePos",	VTYPE_number, OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetCurLine)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int linePos = 0;
	wxString rtn = pThis->GetEntity()->GetCurLine(&linePos);
	return ReturnValue(env, sig, args, Value::CreateAsList(env, Value(static_cast<const char *>(rtn.ToUTF8())), Value(linePos)));
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetEndStyled)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetEndStyled)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int rtn = pThis->GetEntity()->GetEndStyled();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, ConvertEOLs)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "eolMode",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, ConvertEOLs)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int eolMode = args.GetInt(0);
	pThis->GetEntity()->ConvertEOLs(eolMode);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetEOLMode)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetEOLMode)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int rtn = pThis->GetEntity()->GetEOLMode();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetEOLMode)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "eolMode",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetEOLMode)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int eolMode = args.GetInt(0);
	pThis->GetEntity()->SetEOLMode(eolMode);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, StartStyling)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "pos",	VTYPE_number, OCCUR_Once);
	DeclareArg(env, "mask",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, StartStyling)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int pos = args.GetInt(0);
	int mask = args.GetInt(1);
	pThis->GetEntity()->StartStyling(pos, mask);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetStyling)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "length",	VTYPE_number, OCCUR_Once);
	DeclareArg(env, "style",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetStyling)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int length = args.GetInt(0);
	int style = args.GetInt(1);
	pThis->GetEntity()->SetStyling(length, style);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetBufferedDraw)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetBufferedDraw)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	bool rtn = pThis->GetEntity()->GetBufferedDraw();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetBufferedDraw)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "buffered",	VTYPE_boolean, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetBufferedDraw)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	bool buffered = args.GetBoolean(0);
	pThis->GetEntity()->SetBufferedDraw(buffered);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetTabWidth)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "tabWidth",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetTabWidth)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int tabWidth = args.GetInt(0);
	pThis->GetEntity()->SetTabWidth(tabWidth);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetTabWidth)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetTabWidth)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int rtn = pThis->GetEntity()->GetTabWidth();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetCodePage)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "codePage",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetCodePage)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int codePage = args.GetInt(0);
	pThis->GetEntity()->SetCodePage(codePage);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, MarkerDefine)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "markerNumber",	VTYPE_number, OCCUR_Once);
	DeclareArg(env, "markerSymbol",	VTYPE_number, OCCUR_Once);
	DeclareArg(env, "foreground",	VTYPE_wx_Colour, OCCUR_ZeroOrOnce);
	DeclareArg(env, "background",	VTYPE_wx_Colour, OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_StyledTextCtrl, MarkerDefine)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int markerNumber = args.GetInt(0);
	int markerSymbol = args.GetInt(1);
	wxColour *foreground = (wxColour *)(&wxNullColour);
	if (args.IsValid(2)) foreground = Object_wx_Colour::GetObject(args, 2)->GetEntity();
	wxColour *background = (wxColour *)(&wxNullColour);
	if (args.IsValid(3)) background = Object_wx_Colour::GetObject(args, 3)->GetEntity();
	pThis->GetEntity()->MarkerDefine(markerNumber, markerSymbol, *foreground, *background);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, MarkerSetForeground)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "markerNumber",	VTYPE_number, OCCUR_Once);
	DeclareArg(env, "fore",			VTYPE_wx_Colour, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, MarkerSetForeground)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int markerNumber = args.GetInt(0);
	wxColour *fore = Object_wx_Colour::GetObject(args, 1)->GetEntity();
	pThis->GetEntity()->MarkerSetForeground(markerNumber, *fore);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, MarkerSetBackground)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "markerNumber",	VTYPE_number, OCCUR_Once);
	DeclareArg(env, "back",			VTYPE_wx_Colour, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, MarkerSetBackground)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int markerNumber = args.GetInt(0);
	wxColour *back = Object_wx_Colour::GetObject(args, 1)->GetEntity();
	pThis->GetEntity()->MarkerSetBackground(markerNumber, *back);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, MarkerSetBackgroundSelected)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "markerNumber",	VTYPE_number, OCCUR_Once);
	DeclareArg(env, "back",			VTYPE_wx_Colour, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, MarkerSetBackgroundSelected)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int markerNumber = args.GetInt(0);
	wxColour *back = Object_wx_Colour::GetObject(args, 1)->GetEntity();
	pThis->GetEntity()->MarkerSetBackgroundSelected(markerNumber, *back);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, MarkerEnableHighlight)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "enabled",	VTYPE_boolean, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, MarkerEnableHighlight)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	bool enabled = args.GetBoolean(0);
	pThis->GetEntity()->MarkerEnableHighlight(enabled);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, MarkerAdd)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "line",			VTYPE_number, OCCUR_Once);
	DeclareArg(env, "markerNumber",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, MarkerAdd)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int line = args.GetInt(0);
	int markerNumber = args.GetInt(1);
	int rtn = pThis->GetEntity()->MarkerAdd(line, markerNumber);
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, MarkerDelete)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "line",			VTYPE_number, OCCUR_Once);
	DeclareArg(env, "markerNumber",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, MarkerDelete)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int line = args.GetInt(0);
	int markerNumber = args.GetInt(1);
	pThis->GetEntity()->MarkerDelete(line, markerNumber);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, MarkerDeleteAll)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "markerNumber",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, MarkerDeleteAll)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int markerNumber = args.GetInt(0);
	pThis->GetEntity()->MarkerDeleteAll(markerNumber);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, MarkerGet)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "line",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, MarkerGet)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int line = args.GetInt(0);
	int rtn = pThis->GetEntity()->MarkerGet(line);
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, MarkerNext)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "lineStart",	VTYPE_number, OCCUR_Once);
	DeclareArg(env, "markerMask",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, MarkerNext)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int lineStart = args.GetInt(0);
	int markerMask = args.GetInt(1);
	int rtn = pThis->GetEntity()->MarkerNext(lineStart, markerMask);
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, MarkerPrevious)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "lineStart",	VTYPE_number, OCCUR_Once);
	DeclareArg(env, "markerMask",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, MarkerPrevious)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int lineStart = args.GetInt(0);
	int markerMask = args.GetInt(1);
	int rtn = pThis->GetEntity()->MarkerPrevious(lineStart, markerMask);
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, MarkerDefineBitmap)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "markerNumber",	VTYPE_number, OCCUR_Once);
	DeclareArg(env, "bmp",			VTYPE_wx_Bitmap, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, MarkerDefineBitmap)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int markerNumber = args.GetInt(0);
	wxBitmap *bmp = Object_wx_Bitmap::GetObject(args, 1)->GetEntity();
	pThis->GetEntity()->MarkerDefineBitmap(markerNumber, *bmp);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, MarkerAddSet)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "line",	VTYPE_number, OCCUR_Once);
	DeclareArg(env, "set",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, MarkerAddSet)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int line = args.GetInt(0);
	int set = args.GetInt(1);
	pThis->GetEntity()->MarkerAddSet(line, set);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, MarkerSetAlpha)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "markerNumber",	VTYPE_number, OCCUR_Once);
	DeclareArg(env, "alpha",		VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, MarkerSetAlpha)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int markerNumber = args.GetInt(0);
	int alpha = args.GetInt(1);
	pThis->GetEntity()->MarkerSetAlpha(markerNumber, alpha);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetMarginType)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "margin",		VTYPE_number, OCCUR_Once);
	DeclareArg(env, "marginType",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetMarginType)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int margin = args.GetInt(0);
	int marginType = args.GetInt(1);
	pThis->GetEntity()->SetMarginType(margin, marginType);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetMarginType)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "margin",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetMarginType)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int margin = args.GetInt(0);
	int rtn = pThis->GetEntity()->GetMarginType(margin);
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetMarginWidth)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "margin",		VTYPE_number, OCCUR_Once);
	DeclareArg(env, "pixelWidth",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetMarginWidth)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int margin = args.GetInt(0);
	int pixelWidth = args.GetInt(1);
	pThis->GetEntity()->SetMarginWidth(margin, pixelWidth);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetMarginWidth)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "margin",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetMarginWidth)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int margin = args.GetInt(0);
	int rtn = pThis->GetEntity()->GetMarginWidth(margin);
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetMarginMask)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "margin",	VTYPE_number, OCCUR_Once);
	DeclareArg(env, "mask",		VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetMarginMask)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int margin = args.GetInt(0);
	int mask = args.GetInt(1);
	pThis->GetEntity()->SetMarginMask(margin, mask);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetMarginMask)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "margin",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetMarginMask)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int margin = args.GetInt(0);
	int rtn = pThis->GetEntity()->GetMarginMask(margin);
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetMarginSensitive)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "margin",		VTYPE_number, OCCUR_Once);
	DeclareArg(env, "sensitive",	VTYPE_boolean, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetMarginSensitive)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int margin = args.GetInt(0);
	bool sensitive = args.GetBoolean(1);
	pThis->GetEntity()->SetMarginSensitive(margin, sensitive);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetMarginSensitive)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "margin",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetMarginSensitive)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int margin = args.GetInt(0);
	bool rtn = pThis->GetEntity()->GetMarginSensitive(margin);
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetMarginCursor)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "margin",	VTYPE_number, OCCUR_Once);
	DeclareArg(env, "cursor",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetMarginCursor)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int margin = args.GetInt(0);
	int cursor = args.GetInt(1);
	pThis->GetEntity()->SetMarginCursor(margin, cursor);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetMarginCursor)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "margin",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetMarginCursor)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int margin = args.GetInt(0);
	int rtn = pThis->GetEntity()->GetMarginCursor(margin);
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, StyleClearAll)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, StyleClearAll)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->StyleClearAll();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, StyleSetForeground)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "style",	VTYPE_number, OCCUR_Once);
	DeclareArg(env, "fore",		VTYPE_wx_Colour, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, StyleSetForeground)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int style = args.GetInt(0);
	wxColour *fore = Object_wx_Colour::GetObject(args, 1)->GetEntity();
	pThis->GetEntity()->StyleSetForeground(style, *fore);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, StyleSetBackground)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "style",	VTYPE_number, OCCUR_Once);
	DeclareArg(env, "back",		VTYPE_wx_Colour, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, StyleSetBackground)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int style = args.GetInt(0);
	wxColour *back = Object_wx_Colour::GetObject(args, 1)->GetEntity();
	pThis->GetEntity()->StyleSetBackground(style, *back);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, StyleSetBold)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "style",	VTYPE_number, OCCUR_Once);
	DeclareArg(env, "bold",		VTYPE_boolean, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, StyleSetBold)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int style = args.GetInt(0);
	bool bold = args.GetBoolean(1);
	pThis->GetEntity()->StyleSetBold(style, bold);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, StyleSetItalic)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "style",	VTYPE_number, OCCUR_Once);
	DeclareArg(env, "italic",	VTYPE_boolean, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, StyleSetItalic)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int style = args.GetInt(0);
	bool italic = args.GetBoolean(1);
	pThis->GetEntity()->StyleSetItalic(style, italic);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, StyleSetSize)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "style",		VTYPE_number, OCCUR_Once);
	DeclareArg(env, "sizePoints",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, StyleSetSize)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int style = args.GetInt(0);
	int sizePoints = args.GetInt(1);
	pThis->GetEntity()->StyleSetSize(style, sizePoints);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, StyleSetFaceName)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "style",	VTYPE_number, OCCUR_Once);
	DeclareArg(env, "fontName",	VTYPE_string, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, StyleSetFaceName)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int style = args.GetInt(0);
	wxString fontName = wxString::FromUTF8(args.GetString(1));
	pThis->GetEntity()->StyleSetFaceName(style, fontName);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, StyleSetEOLFilled)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "style",	VTYPE_number, OCCUR_Once);
	DeclareArg(env, "filled",	VTYPE_boolean, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, StyleSetEOLFilled)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int style = args.GetInt(0);
	bool filled = args.GetBoolean(1);
	pThis->GetEntity()->StyleSetEOLFilled(style, filled);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, StyleResetDefault)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, StyleResetDefault)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->StyleResetDefault();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, StyleSetUnderline)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "style",		VTYPE_number, OCCUR_Once);
	DeclareArg(env, "underline",	VTYPE_boolean, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, StyleSetUnderline)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int style = args.GetInt(0);
	bool underline = args.GetBoolean(1);
	pThis->GetEntity()->StyleSetUnderline(style, underline);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, StyleGetForeground)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "style",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, StyleGetForeground)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int style = args.GetInt(0);
	wxColour rtn = pThis->GetEntity()->StyleGetForeground(style);
	return ReturnValue(env, sig, args, Value(new Object_wx_Colour(new wxColour(rtn), NULL, OwnerTrue)));
}

Gura_DeclareMethod(wx_StyledTextCtrl, StyleGetBackground)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "style",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, StyleGetBackground)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int style = args.GetInt(0);
	wxColour rtn = pThis->GetEntity()->StyleGetBackground(style);
	return ReturnValue(env, sig, args, Value(new Object_wx_Colour(new wxColour(rtn), NULL, OwnerTrue)));
}

Gura_DeclareMethod(wx_StyledTextCtrl, StyleGetBold)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "style",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, StyleGetBold)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int style = args.GetInt(0);
	bool rtn = pThis->GetEntity()->StyleGetBold(style);
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, StyleGetItalic)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "style",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, StyleGetItalic)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int style = args.GetInt(0);
	bool rtn = pThis->GetEntity()->StyleGetItalic(style);
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, StyleGetSize)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "style",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, StyleGetSize)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int style = args.GetInt(0);
	int rtn = pThis->GetEntity()->StyleGetSize(style);
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, StyleGetFaceName)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "style",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, StyleGetFaceName)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int style = args.GetInt(0);
	wxString rtn = pThis->GetEntity()->StyleGetFaceName(style);
	return ReturnValue(env, sig, args, Value(static_cast<const char *>(rtn.ToUTF8())));
}

Gura_DeclareMethod(wx_StyledTextCtrl, StyleGetEOLFilled)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "style",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, StyleGetEOLFilled)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int style = args.GetInt(0);
	bool rtn = pThis->GetEntity()->StyleGetEOLFilled(style);
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, StyleGetUnderline)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "style",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, StyleGetUnderline)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int style = args.GetInt(0);
	bool rtn = pThis->GetEntity()->StyleGetUnderline(style);
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, StyleGetCase)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "style",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, StyleGetCase)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int style = args.GetInt(0);
	int rtn = pThis->GetEntity()->StyleGetCase(style);
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, StyleGetCharacterSet)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "style",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, StyleGetCharacterSet)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int style = args.GetInt(0);
	int rtn = pThis->GetEntity()->StyleGetCharacterSet(style);
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, StyleGetVisible)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "style",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, StyleGetVisible)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int style = args.GetInt(0);
	bool rtn = pThis->GetEntity()->StyleGetVisible(style);
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, StyleGetChangeable)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "style",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, StyleGetChangeable)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int style = args.GetInt(0);
	bool rtn = pThis->GetEntity()->StyleGetChangeable(style);
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, StyleGetHotSpot)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "style",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, StyleGetHotSpot)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int style = args.GetInt(0);
	bool rtn = pThis->GetEntity()->StyleGetHotSpot(style);
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, StyleSetCase)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "style",		VTYPE_number, OCCUR_Once);
	DeclareArg(env, "caseForce",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, StyleSetCase)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int style = args.GetInt(0);
	int caseForce = args.GetInt(1);
	pThis->GetEntity()->StyleSetCase(style, caseForce);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, StyleSetSizeFractional)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "style",		VTYPE_number, OCCUR_Once);
	DeclareArg(env, "caseForce",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, StyleSetSizeFractional)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int style = args.GetInt(0);
	int caseForce = args.GetInt(1);
	pThis->GetEntity()->StyleSetSizeFractional(style, caseForce);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, StyleGetSizeFractional)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "style",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, StyleGetSizeFractional)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int style = args.GetInt(0);
	int rtn = pThis->GetEntity()->StyleGetSizeFractional(style);
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, StyleSetWeight)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "style",	VTYPE_number, OCCUR_Once);
	DeclareArg(env, "weight",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, StyleSetWeight)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int style = args.GetInt(0);
	int weight = args.GetInt(1);
	pThis->GetEntity()->StyleSetWeight(style, weight);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, StyleGetWeight)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "style",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, StyleGetWeight)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int style = args.GetInt(0);
	int rtn = pThis->GetEntity()->StyleGetWeight(style);
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, StyleSetHotSpot)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "style",	VTYPE_number, OCCUR_Once);
	DeclareArg(env, "hotspot",	VTYPE_boolean, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, StyleSetHotSpot)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int style = args.GetInt(0);
	bool hotspot = args.GetBoolean(1);
	pThis->GetEntity()->StyleSetHotSpot(style, hotspot);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetSelForeground)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "useSetting",	VTYPE_boolean, OCCUR_Once);
	DeclareArg(env, "fore",			VTYPE_wx_Colour, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetSelForeground)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	bool useSetting = args.GetBoolean(0);
	wxColour *fore = Object_wx_Colour::GetObject(args, 1)->GetEntity();
	pThis->GetEntity()->SetSelForeground(useSetting, *fore);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetSelBackground)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "useSetting",	VTYPE_boolean, OCCUR_Once);
	DeclareArg(env, "back",			VTYPE_wx_Colour, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetSelBackground)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	bool useSetting = args.GetBoolean(0);
	wxColour *back = Object_wx_Colour::GetObject(args, 1)->GetEntity();
	pThis->GetEntity()->SetSelBackground(useSetting, *back);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetSelAlpha)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetSelAlpha)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int rtn = pThis->GetEntity()->GetSelAlpha();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetSelAlpha)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "alpha",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetSelAlpha)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int alpha = args.GetInt(0);
	pThis->GetEntity()->SetSelAlpha(alpha);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetSelEOLFilled)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetSelEOLFilled)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	bool rtn = pThis->GetEntity()->GetSelEOLFilled();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetSelEOLFilled)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "filled",	VTYPE_boolean, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetSelEOLFilled)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	bool filled = args.GetBoolean(0);
	pThis->GetEntity()->SetSelEOLFilled(filled);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetCaretForeground)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "fore",	VTYPE_wx_Colour, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetCaretForeground)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	wxColour *fore = Object_wx_Colour::GetObject(args, 0)->GetEntity();
	pThis->GetEntity()->SetCaretForeground(*fore);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, CmdKeyAssign)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "key",			VTYPE_number, OCCUR_Once);
	DeclareArg(env, "modifiers",	VTYPE_number, OCCUR_Once);
	DeclareArg(env, "cmd",			VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, CmdKeyAssign)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int key = args.GetInt(0);
	int modifiers = args.GetInt(1);
	int cmd = args.GetInt(2);
	pThis->GetEntity()->CmdKeyAssign(key, modifiers, cmd);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, CmdKeyClear)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "key",			VTYPE_number, OCCUR_Once);
	DeclareArg(env, "modifiers",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, CmdKeyClear)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int key = args.GetInt(0);
	int modifiers = args.GetInt(1);
	pThis->GetEntity()->CmdKeyClear(key, modifiers);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, CmdKeyClearAll)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, CmdKeyClearAll)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->CmdKeyClearAll();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetStyleBytes)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "length",		VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetStyleBytes)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int length = args.GetInt(0);
	char styleBytes = 0;
	pThis->GetEntity()->SetStyleBytes(length, &styleBytes);
	return Value(styleBytes);
}

Gura_DeclareMethod(wx_StyledTextCtrl, StyleSetVisible)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "style",	VTYPE_number, OCCUR_Once);
	DeclareArg(env, "visible",	VTYPE_boolean, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, StyleSetVisible)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int style = args.GetInt(0);
	bool visible = args.GetBoolean(1);
	pThis->GetEntity()->StyleSetVisible(style, visible);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetCaretPeriod)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetCaretPeriod)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int rtn = pThis->GetEntity()->GetCaretPeriod();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetCaretPeriod)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "periodMilliseconds",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetCaretPeriod)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int periodMilliseconds = args.GetInt(0);
	pThis->GetEntity()->SetCaretPeriod(periodMilliseconds);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetWordChars)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "characters",	VTYPE_string, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetWordChars)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	wxString characters = wxString::FromUTF8(args.GetString(0));
	pThis->GetEntity()->SetWordChars(characters);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetWordChars)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetWordChars)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	wxString rtn = pThis->GetEntity()->GetWordChars();
	return ReturnValue(env, sig, args, Value(static_cast<const char *>(rtn.ToUTF8())));
}

Gura_DeclareMethod(wx_StyledTextCtrl, BeginUndoAction)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, BeginUndoAction)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->BeginUndoAction();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, EndUndoAction)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, EndUndoAction)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->EndUndoAction();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, IndicatorSetStyle)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "indic",	VTYPE_number, OCCUR_Once);
	DeclareArg(env, "style",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, IndicatorSetStyle)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int indic = args.GetInt(0);
	int style = args.GetInt(1);
	pThis->GetEntity()->IndicatorSetStyle(indic, style);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, IndicatorGetStyle)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "indic",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, IndicatorGetStyle)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int indic = args.GetInt(0);
	int rtn = pThis->GetEntity()->IndicatorGetStyle(indic);
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, IndicatorSetForeground)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "indic",	VTYPE_number, OCCUR_Once);
	DeclareArg(env, "fore",		VTYPE_wx_Colour, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, IndicatorSetForeground)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int indic = args.GetInt(0);
	wxColour *fore = Object_wx_Colour::GetObject(args, 1)->GetEntity();
	pThis->GetEntity()->IndicatorSetForeground(indic, *fore);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, IndicatorGetForeground)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "indic",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, IndicatorGetForeground)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int indic = args.GetInt(0);
	wxColour rtn = pThis->GetEntity()->IndicatorGetForeground(indic);
	return ReturnValue(env, sig, args, Value(new Object_wx_Colour(new wxColour(rtn), NULL, OwnerTrue)));
}

Gura_DeclareMethod(wx_StyledTextCtrl, IndicatorSetUnder)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "indic",	VTYPE_number, OCCUR_Once);
	DeclareArg(env, "under",	VTYPE_boolean, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, IndicatorSetUnder)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int indic = args.GetInt(0);
	bool under = args.GetBoolean(1);
	pThis->GetEntity()->IndicatorSetUnder(indic, under);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, IndicatorGetUnder)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "indic",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, IndicatorGetUnder)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int indic = args.GetInt(0);
	bool rtn = pThis->GetEntity()->IndicatorGetUnder(indic);
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetWhitespaceForeground)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "useSetting",	VTYPE_boolean, OCCUR_Once);
	DeclareArg(env, "fore",			VTYPE_wx_Colour, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetWhitespaceForeground)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	bool useSetting = args.GetBoolean(0);
	wxColour *fore = Object_wx_Colour::GetObject(args, 1)->GetEntity();
	pThis->GetEntity()->SetWhitespaceForeground(useSetting, *fore);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetWhitespaceBackground)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "useSetting",	VTYPE_boolean, OCCUR_Once);
	DeclareArg(env, "back",			VTYPE_wx_Colour, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetWhitespaceBackground)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	bool useSetting = args.GetBoolean(0);
	wxColour *back = Object_wx_Colour::GetObject(args, 1)->GetEntity();
	pThis->GetEntity()->SetWhitespaceBackground(useSetting, *back);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetWhitespaceSize)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "size",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetWhitespaceSize)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int size = args.GetInt(0);
	pThis->GetEntity()->SetWhitespaceSize(size);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetWhitespaceSize)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetWhitespaceSize)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int rtn = pThis->GetEntity()->GetWhitespaceSize();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetStyleBits)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "bits",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetStyleBits)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int bits = args.GetInt(0);
	pThis->GetEntity()->SetStyleBits(bits);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetStyleBits)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetStyleBits)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int rtn = pThis->GetEntity()->GetStyleBits();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetLineState)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "line",		VTYPE_number, OCCUR_Once);
	DeclareArg(env, "state",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetLineState)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int line = args.GetInt(0);
	int state = args.GetInt(1);
	pThis->GetEntity()->SetLineState(line, state);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetLineState)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "line",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetLineState)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int line = args.GetInt(0);
	int rtn = pThis->GetEntity()->GetLineState(line);
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetMaxLineState)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetMaxLineState)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int rtn = pThis->GetEntity()->GetMaxLineState();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetCaretLineVisible)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetCaretLineVisible)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	bool rtn = pThis->GetEntity()->GetCaretLineVisible();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetCaretLineVisible)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "show",	VTYPE_boolean, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetCaretLineVisible)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	bool show = args.GetBoolean(0);
	pThis->GetEntity()->SetCaretLineVisible(show);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetCaretLineBackground)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetCaretLineBackground)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	wxColour rtn = pThis->GetEntity()->GetCaretLineBackground();
	return ReturnValue(env, sig, args, Value(new Object_wx_Colour(new wxColour(rtn), NULL, OwnerTrue)));
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetCaretLineBackground)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "back",	VTYPE_wx_Colour, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetCaretLineBackground)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	wxColour *back = Object_wx_Colour::GetObject(args, 0)->GetEntity();
	pThis->GetEntity()->SetCaretLineBackground(*back);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, StyleSetChangeable)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "style",		VTYPE_number, OCCUR_Once);
	DeclareArg(env, "changeable",	VTYPE_boolean, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, StyleSetChangeable)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int style = args.GetInt(0);
	bool changeable = args.GetBoolean(1);
	pThis->GetEntity()->StyleSetChangeable(style, changeable);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, AutoCompShow)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "lenEntered",	VTYPE_number, OCCUR_Once);
	DeclareArg(env, "itemList",		VTYPE_string, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, AutoCompShow)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int lenEntered = args.GetInt(0);
	wxString itemList = wxString::FromUTF8(args.GetString(1));
	pThis->GetEntity()->AutoCompShow(lenEntered, itemList);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, AutoCompCancel)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, AutoCompCancel)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->AutoCompCancel();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, AutoCompActive)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, AutoCompActive)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	bool rtn = pThis->GetEntity()->AutoCompActive();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, AutoCompPosStart)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, AutoCompPosStart)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int rtn = pThis->GetEntity()->AutoCompPosStart();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, AutoCompComplete)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, AutoCompComplete)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->AutoCompComplete();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, AutoCompStops)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "characterSet",	VTYPE_string, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, AutoCompStops)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	wxString characterSet = wxString::FromUTF8(args.GetString(0));
	pThis->GetEntity()->AutoCompStops(characterSet);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, AutoCompSetSeparator)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "separatorCharacter",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, AutoCompSetSeparator)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int separatorCharacter = args.GetInt(0);
	pThis->GetEntity()->AutoCompSetSeparator(separatorCharacter);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, AutoCompGetSeparator)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, AutoCompGetSeparator)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int rtn = pThis->GetEntity()->AutoCompGetSeparator();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, AutoCompSelect)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "text",	VTYPE_string, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, AutoCompSelect)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	wxString text = wxString::FromUTF8(args.GetString(0));
	pThis->GetEntity()->AutoCompSelect(text);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, AutoCompSetCancelAtStart)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "cancel",	VTYPE_boolean, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, AutoCompSetCancelAtStart)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	bool cancel = args.GetBoolean(0);
	pThis->GetEntity()->AutoCompSetCancelAtStart(cancel);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, AutoCompGetCancelAtStart)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, AutoCompGetCancelAtStart)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	bool rtn = pThis->GetEntity()->AutoCompGetCancelAtStart();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, AutoCompSetFillUps)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "characterSet",	VTYPE_string, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, AutoCompSetFillUps)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	wxString characterSet = wxString::FromUTF8(args.GetString(0));
	pThis->GetEntity()->AutoCompSetFillUps(characterSet);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, AutoCompSetChooseSingle)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "chooseSingle",	VTYPE_boolean, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, AutoCompSetChooseSingle)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	bool chooseSingle = args.GetBoolean(0);
	pThis->GetEntity()->AutoCompSetChooseSingle(chooseSingle);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, AutoCompGetChooseSingle)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, AutoCompGetChooseSingle)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	bool rtn = pThis->GetEntity()->AutoCompGetChooseSingle();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, AutoCompSetIgnoreCase)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "ignoreCase",	VTYPE_boolean, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, AutoCompSetIgnoreCase)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	bool ignoreCase = args.GetBoolean(0);
	pThis->GetEntity()->AutoCompSetIgnoreCase(ignoreCase);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, AutoCompGetIgnoreCase)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, AutoCompGetIgnoreCase)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	bool rtn = pThis->GetEntity()->AutoCompGetIgnoreCase();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, UserListShow)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "listType",	VTYPE_number, OCCUR_Once);
	DeclareArg(env, "itemList",	VTYPE_string, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, UserListShow)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int listType = args.GetInt(0);
	wxString itemList = wxString::FromUTF8(args.GetString(1));
	pThis->GetEntity()->UserListShow(listType, itemList);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, AutoCompSetAutoHide)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "autoHide",	VTYPE_boolean, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, AutoCompSetAutoHide)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	bool autoHide = args.GetBoolean(0);
	pThis->GetEntity()->AutoCompSetAutoHide(autoHide);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, AutoCompGetAutoHide)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, AutoCompGetAutoHide)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	bool rtn = pThis->GetEntity()->AutoCompGetAutoHide();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, AutoCompSetDropRestOfWord)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "dropRestOfWord",	VTYPE_boolean, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, AutoCompSetDropRestOfWord)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	bool dropRestOfWord = args.GetBoolean(0);
	pThis->GetEntity()->AutoCompSetDropRestOfWord(dropRestOfWord);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, AutoCompGetDropRestOfWord)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, AutoCompGetDropRestOfWord)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	bool rtn = pThis->GetEntity()->AutoCompGetDropRestOfWord();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, RegisterImage)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "type",	VTYPE_number, OCCUR_Once);
	DeclareArg(env, "bmp",	VTYPE_wx_Bitmap, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, RegisterImage)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int type = args.GetInt(0);
	wxBitmap *bmp = Object_wx_Bitmap::GetObject(args, 1)->GetEntity();
	pThis->GetEntity()->RegisterImage(type, *bmp);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, ClearRegisteredImages)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, ClearRegisteredImages)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->ClearRegisteredImages();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, AutoCompGetTypeSeparator)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, AutoCompGetTypeSeparator)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int rtn = pThis->GetEntity()->AutoCompGetTypeSeparator();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, AutoCompSetTypeSeparator)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "separatorCharacter",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, AutoCompSetTypeSeparator)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int separatorCharacter = args.GetInt(0);
	pThis->GetEntity()->AutoCompSetTypeSeparator(separatorCharacter);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, AutoCompSetMaxWidth)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "characterCount",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, AutoCompSetMaxWidth)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int characterCount = args.GetInt(0);
	pThis->GetEntity()->AutoCompSetMaxWidth(characterCount);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, AutoCompGetMaxWidth)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, AutoCompGetMaxWidth)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int rtn = pThis->GetEntity()->AutoCompGetMaxWidth();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, AutoCompSetMaxHeight)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "rowCount",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, AutoCompSetMaxHeight)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int rowCount = args.GetInt(0);
	pThis->GetEntity()->AutoCompSetMaxHeight(rowCount);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, AutoCompGetMaxHeight)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, AutoCompGetMaxHeight)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int rtn = pThis->GetEntity()->AutoCompGetMaxHeight();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetIndent)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "indentSize",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetIndent)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int indentSize = args.GetInt(0);
	pThis->GetEntity()->SetIndent(indentSize);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetIndent)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetIndent)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int rtn = pThis->GetEntity()->GetIndent();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetUseTabs)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "useTabs",	VTYPE_boolean, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetUseTabs)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	bool useTabs = args.GetBoolean(0);
	pThis->GetEntity()->SetUseTabs(useTabs);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetUseTabs)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetUseTabs)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	bool rtn = pThis->GetEntity()->GetUseTabs();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetLineIndentation)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "line",			VTYPE_number, OCCUR_Once);
	DeclareArg(env, "indentSize",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetLineIndentation)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int line = args.GetInt(0);
	int indentSize = args.GetInt(1);
	pThis->GetEntity()->SetLineIndentation(line, indentSize);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetLineIndentation)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "line",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetLineIndentation)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int line = args.GetInt(0);
	int rtn = pThis->GetEntity()->GetLineIndentation(line);
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetLineIndentPosition)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "line",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetLineIndentPosition)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int line = args.GetInt(0);
	int rtn = pThis->GetEntity()->GetLineIndentPosition(line);
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetColumn)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "pos",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetColumn)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int pos = args.GetInt(0);
	int rtn = pThis->GetEntity()->GetColumn(pos);
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, CountCharacters)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "startPos",	VTYPE_number, OCCUR_Once);
	DeclareArg(env, "endPos",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, CountCharacters)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int startPos = args.GetInt(0);
	int endPos = args.GetInt(1);
	int rtn = pThis->GetEntity()->CountCharacters(startPos, endPos);
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetUseHorizontalScrollBar)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "show",	VTYPE_boolean, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetUseHorizontalScrollBar)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	bool show = args.GetBoolean(0);
	pThis->GetEntity()->SetUseHorizontalScrollBar(show);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetUseHorizontalScrollBar)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetUseHorizontalScrollBar)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	bool rtn = pThis->GetEntity()->GetUseHorizontalScrollBar();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetIndentationGuides)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "indentView",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetIndentationGuides)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int indentView = args.GetInt(0);
	pThis->GetEntity()->SetIndentationGuides(indentView);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetIndentationGuides)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetIndentationGuides)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int rtn = pThis->GetEntity()->GetIndentationGuides();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetHighlightGuide)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "column",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetHighlightGuide)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int column = args.GetInt(0);
	pThis->GetEntity()->SetHighlightGuide(column);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetHighlightGuide)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetHighlightGuide)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int rtn = pThis->GetEntity()->GetHighlightGuide();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetLineEndPosition)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "line",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetLineEndPosition)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int line = args.GetInt(0);
	int rtn = pThis->GetEntity()->GetLineEndPosition(line);
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetCodePage)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetCodePage)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int rtn = pThis->GetEntity()->GetCodePage();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetCaretForeground)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetCaretForeground)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	wxColour rtn = pThis->GetEntity()->GetCaretForeground();
	return ReturnValue(env, sig, args, Value(new Object_wx_Colour(new wxColour(rtn), NULL, OwnerTrue)));
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetReadOnly)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetReadOnly)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	bool rtn = pThis->GetEntity()->GetReadOnly();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetCurrentPos)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "pos",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetCurrentPos)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int pos = args.GetInt(0);
	pThis->GetEntity()->SetCurrentPos(pos);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetSelectionStart)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "pos",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetSelectionStart)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int pos = args.GetInt(0);
	pThis->GetEntity()->SetSelectionStart(pos);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetSelectionStart)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetSelectionStart)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int rtn = pThis->GetEntity()->GetSelectionStart();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetSelectionEnd)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "pos",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetSelectionEnd)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int pos = args.GetInt(0);
	pThis->GetEntity()->SetSelectionEnd(pos);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetSelectionEnd)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetSelectionEnd)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int rtn = pThis->GetEntity()->GetSelectionEnd();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetEmptySelection)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "pos",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetEmptySelection)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int pos = args.GetInt(0);
	pThis->GetEntity()->SetEmptySelection(pos);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetPrintMagnification)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "magnification",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetPrintMagnification)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int magnification = args.GetInt(0);
	pThis->GetEntity()->SetPrintMagnification(magnification);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetPrintMagnification)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetPrintMagnification)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int rtn = pThis->GetEntity()->GetPrintMagnification();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetPrintColourMode)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "mode",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetPrintColourMode)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int mode = args.GetInt(0);
	pThis->GetEntity()->SetPrintColourMode(mode);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetPrintColourMode)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetPrintColourMode)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int rtn = pThis->GetEntity()->GetPrintColourMode();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, FindText)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "minPos",	VTYPE_number, OCCUR_Once);
	DeclareArg(env, "maxPos",	VTYPE_number, OCCUR_Once);
	DeclareArg(env, "text",		VTYPE_string, OCCUR_Once);
	DeclareArg(env, "flags",	VTYPE_number, OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_StyledTextCtrl, FindText)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int minPos = args.GetInt(0);
	int maxPos = args.GetInt(1);
	wxString text = wxString::FromUTF8(args.GetString(2));
	int flags = 0;
	if (args.IsValid(3)) flags = args.GetInt(3);
	int rtn = pThis->GetEntity()->FindText(minPos, maxPos, text, flags);
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, FormatRange)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "doDraw",		VTYPE_boolean, OCCUR_Once);
	DeclareArg(env, "startPos",		VTYPE_number, OCCUR_Once);
	DeclareArg(env, "endPos",		VTYPE_number, OCCUR_Once);
	DeclareArg(env, "draw",			VTYPE_wx_DC, OCCUR_Once);
	DeclareArg(env, "target",		VTYPE_wx_DC, OCCUR_Once);
	DeclareArg(env, "renderRect",	VTYPE_wx_Rect, OCCUR_Once);
	DeclareArg(env, "pageRect",		VTYPE_wx_Rect, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, FormatRange)
{
#if 0
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	bool doDraw = args.GetBoolean(0);
	int startPos = args.GetInt(1);
	int endPos = args.GetInt(2);
	wxDC *draw = Object_wx_DC::GetObject(args, 3)->GetEntity();
	wxDC *target = Object_wx_DC::GetObject(args, 4)->GetEntity();
	wxRect *renderRect = Object_wx_Rect::GetObject(args, 5)->GetEntity();
	wxRect *pageRect = Object_wx_Rect::GetObject(args, 6)->GetEntity();
	int rtn = pThis->GetEntity()->FormatRange(doDraw, startPos, endPos, *draw, *target, *renderRect, *pageRect);
	return ReturnValue(env, sig, args, Value(rtn));
#endif
	SetError_NotImplemented(sig);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetFirstVisibleLine)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetFirstVisibleLine)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int rtn = pThis->GetEntity()->GetFirstVisibleLine();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetLine)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "line",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetLine)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int line = args.GetInt(0);
	wxString rtn = pThis->GetEntity()->GetLine(line);
	return ReturnValue(env, sig, args, Value(static_cast<const char *>(rtn.ToUTF8())));
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetLineCount)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetLineCount)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int rtn = pThis->GetEntity()->GetLineCount();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetMarginLeft)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "pixelWidth",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetMarginLeft)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int pixelWidth = args.GetInt(0);
	pThis->GetEntity()->SetMarginLeft(pixelWidth);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetMarginLeft)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetMarginLeft)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int rtn = pThis->GetEntity()->GetMarginLeft();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetMarginRight)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "pixelWidth",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetMarginRight)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int pixelWidth = args.GetInt(0);
	pThis->GetEntity()->SetMarginRight(pixelWidth);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetMarginRight)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetMarginRight)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int rtn = pThis->GetEntity()->GetMarginRight();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetModify)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetModify)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	bool rtn = pThis->GetEntity()->GetModify();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetSelectedText)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetSelectedText)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	wxString rtn = pThis->GetEntity()->GetSelectedText();
	return ReturnValue(env, sig, args, Value(static_cast<const char *>(rtn.ToUTF8())));
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetTextRange)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "startPos",	VTYPE_number, OCCUR_Once);
	DeclareArg(env, "endPos",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetTextRange)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int startPos = args.GetInt(0);
	int endPos = args.GetInt(1);
	wxString rtn = pThis->GetEntity()->GetTextRange(startPos, endPos);
	return ReturnValue(env, sig, args, Value(static_cast<const char *>(rtn.ToUTF8())));
}

Gura_DeclareMethod(wx_StyledTextCtrl, HideSelection)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "normal",	VTYPE_boolean, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, HideSelection)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	bool normal = args.GetBoolean(0);
	pThis->GetEntity()->HideSelection(normal);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, LineFromPosition)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "pos",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, LineFromPosition)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int pos = args.GetInt(0);
	int rtn = pThis->GetEntity()->LineFromPosition(pos);
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, PositionFromLine)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "line",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, PositionFromLine)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int line = args.GetInt(0);
	int rtn = pThis->GetEntity()->PositionFromLine(line);
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, LineScroll)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "columns",	VTYPE_number, OCCUR_Once);
	DeclareArg(env, "lines",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, LineScroll)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int columns = args.GetInt(0);
	int lines = args.GetInt(1);
	pThis->GetEntity()->LineScroll(columns, lines);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, EnsureCaretVisible)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, EnsureCaretVisible)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->EnsureCaretVisible();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, ReplaceSelection)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "text",	VTYPE_string, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, ReplaceSelection)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	wxString text = wxString::FromUTF8(args.GetString(0));
	pThis->GetEntity()->ReplaceSelection(text);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetReadOnly)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "readOnly",	VTYPE_boolean, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetReadOnly)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	bool readOnly = args.GetBoolean(0);
	pThis->GetEntity()->SetReadOnly(readOnly);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, CanPaste)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, CanPaste)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	bool rtn = pThis->GetEntity()->CanPaste();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, CanUndo)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, CanUndo)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	bool rtn = pThis->GetEntity()->CanUndo();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, EmptyUndoBuffer)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, EmptyUndoBuffer)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->EmptyUndoBuffer();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, Undo)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, Undo)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->Undo();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, Cut)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, Cut)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->Cut();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, Copy)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, Copy)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->Copy();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, Paste)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, Paste)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->Paste();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, Clear)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, Clear)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->Clear();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetText)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "text",	VTYPE_string, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetText)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	wxString text = wxString::FromUTF8(args.GetString(0));
	pThis->GetEntity()->SetText(text);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetText)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetText)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	wxString rtn = pThis->GetEntity()->GetText();
	return ReturnValue(env, sig, args, Value(static_cast<const char *>(rtn.ToUTF8())));
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetTextLength)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetTextLength)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int rtn = pThis->GetEntity()->GetTextLength();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetOvertype)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "overtype",	VTYPE_boolean, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetOvertype)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	bool overtype = args.GetBoolean(0);
	pThis->GetEntity()->SetOvertype(overtype);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetOvertype)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetOvertype)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	bool rtn = pThis->GetEntity()->GetOvertype();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetCaretWidth)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "pixelWidth",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetCaretWidth)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int pixelWidth = args.GetInt(0);
	pThis->GetEntity()->SetCaretWidth(pixelWidth);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetCaretWidth)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetCaretWidth)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int rtn = pThis->GetEntity()->GetCaretWidth();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetTargetStart)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "pos",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetTargetStart)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int pos = args.GetInt(0);
	pThis->GetEntity()->SetTargetStart(pos);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetTargetStart)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetTargetStart)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int rtn = pThis->GetEntity()->GetTargetStart();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetTargetEnd)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "pos",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetTargetEnd)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int pos = args.GetInt(0);
	pThis->GetEntity()->SetTargetEnd(pos);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetTargetEnd)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetTargetEnd)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int rtn = pThis->GetEntity()->GetTargetEnd();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, ReplaceTarget)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "text",	VTYPE_string, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, ReplaceTarget)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	wxString text = wxString::FromUTF8(args.GetString(0));
	int rtn = pThis->GetEntity()->ReplaceTarget(text);
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, ReplaceTargetRE)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "text",	VTYPE_string, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, ReplaceTargetRE)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	wxString text = wxString::FromUTF8(args.GetString(0));
	int rtn = pThis->GetEntity()->ReplaceTargetRE(text);
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, SearchInTarget)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "text",	VTYPE_string, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SearchInTarget)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	wxString text = wxString::FromUTF8(args.GetString(0));
	int rtn = pThis->GetEntity()->SearchInTarget(text);
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetSearchFlags)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "flags",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetSearchFlags)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int flags = args.GetInt(0);
	pThis->GetEntity()->SetSearchFlags(flags);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetSearchFlags)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetSearchFlags)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int rtn = pThis->GetEntity()->GetSearchFlags();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, CallTipShow)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "pos",			VTYPE_number, OCCUR_Once);
	DeclareArg(env, "definition",	VTYPE_string, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, CallTipShow)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int pos = args.GetInt(0);
	wxString definition = wxString::FromUTF8(args.GetString(1));
	pThis->GetEntity()->CallTipShow(pos, definition);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, CallTipCancel)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, CallTipCancel)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->CallTipCancel();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, CallTipActive)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, CallTipActive)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	bool rtn = pThis->GetEntity()->CallTipActive();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, CallTipPosAtStart)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, CallTipPosAtStart)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int rtn = pThis->GetEntity()->CallTipPosAtStart();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, CallTipSetHighlight)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "start",	VTYPE_number, OCCUR_Once);
	DeclareArg(env, "end",		VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, CallTipSetHighlight)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int start = args.GetInt(0);
	int end = args.GetInt(1);
	pThis->GetEntity()->CallTipSetHighlight(start, end);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, CallTipSetBackground)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "back",	VTYPE_wx_Colour, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, CallTipSetBackground)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	wxColour *back = Object_wx_Colour::GetObject(args, 0)->GetEntity();
	pThis->GetEntity()->CallTipSetBackground(*back);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, CallTipSetForeground)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "fore",	VTYPE_wx_Colour, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, CallTipSetForeground)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	wxColour *fore = Object_wx_Colour::GetObject(args, 0)->GetEntity();
	pThis->GetEntity()->CallTipSetForeground(*fore);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, CallTipSetForegroundHighlight)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "fore",	VTYPE_wx_Colour, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, CallTipSetForegroundHighlight)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	wxColour *fore = Object_wx_Colour::GetObject(args, 0)->GetEntity();
	pThis->GetEntity()->CallTipSetForegroundHighlight(*fore);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, CallTipUseStyle)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "tabSize",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, CallTipUseStyle)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int tabSize = args.GetInt(0);
	pThis->GetEntity()->CallTipUseStyle(tabSize);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, CallTipSetPosition)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "above",	VTYPE_boolean, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, CallTipSetPosition)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	bool above = args.GetBoolean(0);
	pThis->GetEntity()->CallTipSetPosition(above);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, VisibleFromDocLine)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "line",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, VisibleFromDocLine)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int line = args.GetInt(0);
	int rtn = pThis->GetEntity()->VisibleFromDocLine(line);
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, DocLineFromVisible)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "lineDisplay",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, DocLineFromVisible)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int lineDisplay = args.GetInt(0);
	int rtn = pThis->GetEntity()->DocLineFromVisible(lineDisplay);
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, WrapCount)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "line",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, WrapCount)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int line = args.GetInt(0);
	int rtn = pThis->GetEntity()->WrapCount(line);
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetFoldLevel)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "line",		VTYPE_number, OCCUR_Once);
	DeclareArg(env, "level",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetFoldLevel)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int line = args.GetInt(0);
	int level = args.GetInt(1);
	pThis->GetEntity()->SetFoldLevel(line, level);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetFoldLevel)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "line",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetFoldLevel)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int line = args.GetInt(0);
	int rtn = pThis->GetEntity()->GetFoldLevel(line);
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetLastChild)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "line",		VTYPE_number, OCCUR_Once);
	DeclareArg(env, "level",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetLastChild)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int line = args.GetInt(0);
	int level = args.GetInt(1);
	int rtn = pThis->GetEntity()->GetLastChild(line, level);
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetFoldParent)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "line",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetFoldParent)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int line = args.GetInt(0);
	int rtn = pThis->GetEntity()->GetFoldParent(line);
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, ShowLines)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "lineStart",	VTYPE_number, OCCUR_Once);
	DeclareArg(env, "lineEnd",		VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, ShowLines)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int lineStart = args.GetInt(0);
	int lineEnd = args.GetInt(1);
	pThis->GetEntity()->ShowLines(lineStart, lineEnd);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, HideLines)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "lineStart",	VTYPE_number, OCCUR_Once);
	DeclareArg(env, "lineEnd",		VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, HideLines)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int lineStart = args.GetInt(0);
	int lineEnd = args.GetInt(1);
	pThis->GetEntity()->HideLines(lineStart, lineEnd);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetLineVisible)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "line",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetLineVisible)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int line = args.GetInt(0);
	bool rtn = pThis->GetEntity()->GetLineVisible(line);
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetAllLinesVisible)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetAllLinesVisible)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	bool rtn = pThis->GetEntity()->GetAllLinesVisible();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetFoldExpanded)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "line",		VTYPE_number, OCCUR_Once);
	DeclareArg(env, "expanded",	VTYPE_boolean, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetFoldExpanded)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int line = args.GetInt(0);
	bool expanded = args.GetBoolean(1);
	pThis->GetEntity()->SetFoldExpanded(line, expanded);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetFoldExpanded)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "line",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetFoldExpanded)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int line = args.GetInt(0);
	bool rtn = pThis->GetEntity()->GetFoldExpanded(line);
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, ToggleFold)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "line",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, ToggleFold)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int line = args.GetInt(0);
	pThis->GetEntity()->ToggleFold(line);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, EnsureVisible)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "line",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, EnsureVisible)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int line = args.GetInt(0);
	pThis->GetEntity()->EnsureVisible(line);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetFoldFlags)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "flags",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetFoldFlags)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int flags = args.GetInt(0);
	pThis->GetEntity()->SetFoldFlags(flags);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, EnsureVisibleEnforcePolicy)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "line",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, EnsureVisibleEnforcePolicy)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int line = args.GetInt(0);
	pThis->GetEntity()->EnsureVisibleEnforcePolicy(line);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetTabIndents)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "tabIndents",	VTYPE_boolean, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetTabIndents)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	bool tabIndents = args.GetBoolean(0);
	pThis->GetEntity()->SetTabIndents(tabIndents);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetTabIndents)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetTabIndents)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	bool rtn = pThis->GetEntity()->GetTabIndents();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetBackSpaceUnIndents)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "bsUnIndents",	VTYPE_boolean, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetBackSpaceUnIndents)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	bool bsUnIndents = args.GetBoolean(0);
	pThis->GetEntity()->SetBackSpaceUnIndents(bsUnIndents);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetBackSpaceUnIndents)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetBackSpaceUnIndents)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	bool rtn = pThis->GetEntity()->GetBackSpaceUnIndents();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetMouseDwellTime)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "periodMilliseconds",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetMouseDwellTime)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int periodMilliseconds = args.GetInt(0);
	pThis->GetEntity()->SetMouseDwellTime(periodMilliseconds);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetMouseDwellTime)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetMouseDwellTime)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int rtn = pThis->GetEntity()->GetMouseDwellTime();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, WordStartPosition)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "pos",					VTYPE_number, OCCUR_Once);
	DeclareArg(env, "onlyWordCharacters",	VTYPE_boolean, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, WordStartPosition)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int pos = args.GetInt(0);
	bool onlyWordCharacters = args.GetBoolean(1);
	int rtn = pThis->GetEntity()->WordStartPosition(pos, onlyWordCharacters);
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, WordEndPosition)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "pos",					VTYPE_number, OCCUR_Once);
	DeclareArg(env, "onlyWordCharacters",	VTYPE_boolean, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, WordEndPosition)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int pos = args.GetInt(0);
	bool onlyWordCharacters = args.GetBoolean(1);
	int rtn = pThis->GetEntity()->WordEndPosition(pos, onlyWordCharacters);
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetWrapMode)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "mode",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetWrapMode)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int mode = args.GetInt(0);
	pThis->GetEntity()->SetWrapMode(mode);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetWrapMode)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetWrapMode)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int rtn = pThis->GetEntity()->GetWrapMode();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetWrapVisualFlags)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "wrapVisualFlags",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetWrapVisualFlags)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int wrapVisualFlags = args.GetInt(0);
	pThis->GetEntity()->SetWrapVisualFlags(wrapVisualFlags);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetWrapVisualFlags)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetWrapVisualFlags)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int rtn = pThis->GetEntity()->GetWrapVisualFlags();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetWrapVisualFlagsLocation)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "wrapVisualFlagsLocation",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetWrapVisualFlagsLocation)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int wrapVisualFlagsLocation = args.GetInt(0);
	pThis->GetEntity()->SetWrapVisualFlagsLocation(wrapVisualFlagsLocation);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetWrapVisualFlagsLocation)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetWrapVisualFlagsLocation)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int rtn = pThis->GetEntity()->GetWrapVisualFlagsLocation();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetWrapStartIndent)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "indent",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetWrapStartIndent)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int indent = args.GetInt(0);
	pThis->GetEntity()->SetWrapStartIndent(indent);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetWrapStartIndent)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetWrapStartIndent)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int rtn = pThis->GetEntity()->GetWrapStartIndent();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetWrapIndentMode)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "mode",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetWrapIndentMode)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int mode = args.GetInt(0);
	pThis->GetEntity()->SetWrapIndentMode(mode);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetWrapIndentMode)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetWrapIndentMode)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int rtn = pThis->GetEntity()->GetWrapIndentMode();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetLayoutCache)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "mode",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetLayoutCache)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int mode = args.GetInt(0);
	pThis->GetEntity()->SetLayoutCache(mode);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetLayoutCache)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetLayoutCache)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int rtn = pThis->GetEntity()->GetLayoutCache();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetScrollWidth)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "pixelWidth",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetScrollWidth)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int pixelWidth = args.GetInt(0);
	pThis->GetEntity()->SetScrollWidth(pixelWidth);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetScrollWidth)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetScrollWidth)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int rtn = pThis->GetEntity()->GetScrollWidth();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetScrollWidthTracking)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "tracking",	VTYPE_boolean, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetScrollWidthTracking)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	bool tracking = args.GetBoolean(0);
	pThis->GetEntity()->SetScrollWidthTracking(tracking);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetScrollWidthTracking)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetScrollWidthTracking)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	bool rtn = pThis->GetEntity()->GetScrollWidthTracking();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, TextWidth)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "style",	VTYPE_number, OCCUR_Once);
	DeclareArg(env, "text",		VTYPE_string, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, TextWidth)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int style = args.GetInt(0);
	wxString text = wxString::FromUTF8(args.GetString(1));
	int rtn = pThis->GetEntity()->TextWidth(style, text);
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetEndAtLastLine)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "endAtLastLine",	VTYPE_boolean, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetEndAtLastLine)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	bool endAtLastLine = args.GetBoolean(0);
	pThis->GetEntity()->SetEndAtLastLine(endAtLastLine);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetEndAtLastLine)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetEndAtLastLine)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	bool rtn = pThis->GetEntity()->GetEndAtLastLine();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, TextHeight)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "line",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, TextHeight)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int line = args.GetInt(0);
	int rtn = pThis->GetEntity()->TextHeight(line);
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetUseVerticalScrollBar)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "show",	VTYPE_boolean, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetUseVerticalScrollBar)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	bool show = args.GetBoolean(0);
	pThis->GetEntity()->SetUseVerticalScrollBar(show);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetUseVerticalScrollBar)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetUseVerticalScrollBar)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	bool rtn = pThis->GetEntity()->GetUseVerticalScrollBar();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, AppendText)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "text",	VTYPE_string, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, AppendText)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	wxString text = wxString::FromUTF8(args.GetString(0));
	pThis->GetEntity()->AppendText(text);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetTwoPhaseDraw)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetTwoPhaseDraw)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	bool rtn = pThis->GetEntity()->GetTwoPhaseDraw();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetTwoPhaseDraw)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "twoPhase",	VTYPE_boolean, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetTwoPhaseDraw)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	bool twoPhase = args.GetBoolean(0);
	pThis->GetEntity()->SetTwoPhaseDraw(twoPhase);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetFirstVisibleLine)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "lineDisplay",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetFirstVisibleLine)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int lineDisplay = args.GetInt(0);
	pThis->GetEntity()->SetFirstVisibleLine(lineDisplay);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetMultiPaste)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "multiPaste",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetMultiPaste)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int multiPaste = args.GetInt(0);
	pThis->GetEntity()->SetMultiPaste(multiPaste);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetMultiPaste)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetMultiPaste)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int rtn = pThis->GetEntity()->GetMultiPaste();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetTag)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "tagNumber",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetTag)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int tagNumber = args.GetInt(0);
	wxString rtn = pThis->GetEntity()->GetTag(tagNumber);
	return ReturnValue(env, sig, args, Value(static_cast<const char *>(rtn.ToUTF8())));
}

Gura_DeclareMethod(wx_StyledTextCtrl, TargetFromSelection)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, TargetFromSelection)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->TargetFromSelection();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, LinesJoin)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, LinesJoin)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->LinesJoin();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, LinesSplit)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "pixelWidth",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, LinesSplit)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int pixelWidth = args.GetInt(0);
	pThis->GetEntity()->LinesSplit(pixelWidth);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetFoldMarginColour)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "useSetting",	VTYPE_boolean, OCCUR_Once);
	DeclareArg(env, "back",			VTYPE_wx_Colour, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetFoldMarginColour)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	bool useSetting = args.GetBoolean(0);
	wxColour *back = Object_wx_Colour::GetObject(args, 1)->GetEntity();
	pThis->GetEntity()->SetFoldMarginColour(useSetting, *back);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetFoldMarginHiColour)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "useSetting",	VTYPE_boolean, OCCUR_Once);
	DeclareArg(env, "fore",			VTYPE_wx_Colour, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetFoldMarginHiColour)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	bool useSetting = args.GetBoolean(0);
	wxColour *fore = Object_wx_Colour::GetObject(args, 1)->GetEntity();
	pThis->GetEntity()->SetFoldMarginHiColour(useSetting, *fore);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, LineDown)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, LineDown)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->LineDown();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, LineDownExtend)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, LineDownExtend)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->LineDownExtend();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, LineUp)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, LineUp)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->LineUp();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, LineUpExtend)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, LineUpExtend)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->LineUpExtend();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, CharLeft)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, CharLeft)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->CharLeft();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, CharLeftExtend)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, CharLeftExtend)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->CharLeftExtend();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, CharRight)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, CharRight)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->CharRight();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, CharRightExtend)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, CharRightExtend)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->CharRightExtend();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, WordLeft)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, WordLeft)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->WordLeft();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, WordLeftExtend)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, WordLeftExtend)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->WordLeftExtend();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, WordRight)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, WordRight)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->WordRight();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, WordRightExtend)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, WordRightExtend)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->WordRightExtend();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, Home)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, Home)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->Home();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, HomeExtend)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, HomeExtend)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->HomeExtend();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, LineEnd)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, LineEnd)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->LineEnd();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, LineEndExtend)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, LineEndExtend)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->LineEndExtend();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, DocumentStart)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, DocumentStart)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->DocumentStart();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, DocumentStartExtend)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, DocumentStartExtend)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->DocumentStartExtend();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, DocumentEnd)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, DocumentEnd)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->DocumentEnd();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, DocumentEndExtend)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, DocumentEndExtend)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->DocumentEndExtend();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, PageUp)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, PageUp)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->PageUp();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, PageUpExtend)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, PageUpExtend)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->PageUpExtend();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, PageDown)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, PageDown)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->PageDown();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, PageDownExtend)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, PageDownExtend)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->PageDownExtend();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, EditToggleOvertype)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, EditToggleOvertype)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->EditToggleOvertype();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, Cancel)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, Cancel)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->Cancel();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, DeleteBack)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, DeleteBack)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->DeleteBack();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, Tab)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, Tab)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->Tab();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, BackTab)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, BackTab)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->BackTab();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, NewLine)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, NewLine)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->NewLine();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, FormFeed)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, FormFeed)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->FormFeed();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, VCHome)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, VCHome)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->VCHome();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, VCHomeExtend)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, VCHomeExtend)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->VCHomeExtend();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, ZoomIn)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, ZoomIn)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->ZoomIn();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, ZoomOut)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, ZoomOut)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->ZoomOut();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, DelWordLeft)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, DelWordLeft)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->DelWordLeft();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, DelWordRight)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, DelWordRight)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->DelWordRight();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, DelWordRightEnd)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, DelWordRightEnd)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->DelWordRightEnd();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, LineCut)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, LineCut)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->LineCut();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, LineDelete)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, LineDelete)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->LineDelete();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, LineTranspose)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, LineTranspose)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->LineTranspose();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, LineDuplicate)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, LineDuplicate)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->LineDuplicate();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, LowerCase)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, LowerCase)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->LowerCase();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, UpperCase)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, UpperCase)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->UpperCase();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, LineScrollDown)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, LineScrollDown)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->LineScrollDown();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, LineScrollUp)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, LineScrollUp)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->LineScrollUp();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, DeleteBackNotLine)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, DeleteBackNotLine)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->DeleteBackNotLine();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, HomeDisplay)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, HomeDisplay)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->HomeDisplay();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, HomeDisplayExtend)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, HomeDisplayExtend)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->HomeDisplayExtend();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, LineEndDisplay)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, LineEndDisplay)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->LineEndDisplay();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, LineEndDisplayExtend)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, LineEndDisplayExtend)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->LineEndDisplayExtend();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, HomeWrap)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, HomeWrap)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->HomeWrap();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, HomeWrapExtend)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, HomeWrapExtend)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->HomeWrapExtend();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, LineEndWrap)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, LineEndWrap)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->LineEndWrap();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, LineEndWrapExtend)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, LineEndWrapExtend)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->LineEndWrapExtend();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, VCHomeWrap)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, VCHomeWrap)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->VCHomeWrap();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, VCHomeWrapExtend)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, VCHomeWrapExtend)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->VCHomeWrapExtend();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, LineCopy)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, LineCopy)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->LineCopy();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, MoveCaretInsideView)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, MoveCaretInsideView)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->MoveCaretInsideView();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, LineLength)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "line",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, LineLength)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int line = args.GetInt(0);
	int rtn = pThis->GetEntity()->LineLength(line);
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, BraceHighlight)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "pos1",	VTYPE_number, OCCUR_Once);
	DeclareArg(env, "pos2",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, BraceHighlight)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int pos1 = args.GetInt(0);
	int pos2 = args.GetInt(1);
	pThis->GetEntity()->BraceHighlight(pos1, pos2);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, BraceHighlightIndicator)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "useBraceHighlightIndicator",	VTYPE_boolean, OCCUR_Once);
	DeclareArg(env, "indicator",					VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, BraceHighlightIndicator)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	bool useBraceHighlightIndicator = args.GetBoolean(0);
	int indicator = args.GetInt(1);
	pThis->GetEntity()->BraceHighlightIndicator(useBraceHighlightIndicator, indicator);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, BraceBadLight)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "pos",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, BraceBadLight)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int pos = args.GetInt(0);
	pThis->GetEntity()->BraceBadLight(pos);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, BraceBadLightIndicator)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "useBraceBadLightIndicator",	VTYPE_boolean, OCCUR_Once);
	DeclareArg(env, "indicator",					VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, BraceBadLightIndicator)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	bool useBraceBadLightIndicator = args.GetBoolean(0);
	int indicator = args.GetInt(1);
	pThis->GetEntity()->BraceBadLightIndicator(useBraceBadLightIndicator, indicator);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, BraceMatch)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "pos",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, BraceMatch)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int pos = args.GetInt(0);
	int rtn = pThis->GetEntity()->BraceMatch(pos);
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetViewEOL)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetViewEOL)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	bool rtn = pThis->GetEntity()->GetViewEOL();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetViewEOL)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "visible",	VTYPE_boolean, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetViewEOL)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	bool visible = args.GetBoolean(0);
	pThis->GetEntity()->SetViewEOL(visible);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetDocPointer)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetDocPointer)
{
#if 0
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->GetDocPointer();
#endif
	SetError_NotImplemented(sig);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetDocPointer)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "docPointer",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetDocPointer)
{
#if 0
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int docPointer = args.GetInt(0);
	pThis->GetEntity()->SetDocPointer(docPointer);
#endif
	SetError_NotImplemented(sig);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetModEventMask)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "mask",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetModEventMask)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int mask = args.GetInt(0);
	pThis->GetEntity()->SetModEventMask(mask);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetEdgeColumn)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetEdgeColumn)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int rtn = pThis->GetEntity()->GetEdgeColumn();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetEdgeColumn)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "column",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetEdgeColumn)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int column = args.GetInt(0);
	pThis->GetEntity()->SetEdgeColumn(column);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetEdgeMode)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetEdgeMode)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int rtn = pThis->GetEntity()->GetEdgeMode();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetEdgeMode)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "mode",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetEdgeMode)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int mode = args.GetInt(0);
	pThis->GetEntity()->SetEdgeMode(mode);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetEdgeColour)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetEdgeColour)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	wxColour rtn = pThis->GetEntity()->GetEdgeColour();
	return ReturnValue(env, sig, args, Value(new Object_wx_Colour(new wxColour(rtn), NULL, OwnerTrue)));
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetEdgeColour)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "edgeColour",	VTYPE_wx_Colour, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetEdgeColour)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	wxColour *edgeColour = Object_wx_Colour::GetObject(args, 0)->GetEntity();
	pThis->GetEntity()->SetEdgeColour(*edgeColour);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, SearchAnchor)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SearchAnchor)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->SearchAnchor();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, SearchNext)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "flags",	VTYPE_number, OCCUR_Once);
	DeclareArg(env, "text",		VTYPE_string, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SearchNext)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int flags = args.GetInt(0);
	wxString text = wxString::FromUTF8(args.GetString(1));
	int rtn = pThis->GetEntity()->SearchNext(flags, text);
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, SearchPrev)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "flags",	VTYPE_number, OCCUR_Once);
	DeclareArg(env, "text",		VTYPE_string, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SearchPrev)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int flags = args.GetInt(0);
	wxString text = wxString::FromUTF8(args.GetString(1));
	int rtn = pThis->GetEntity()->SearchPrev(flags, text);
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, LinesOnScreen)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, LinesOnScreen)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int rtn = pThis->GetEntity()->LinesOnScreen();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, UsePopUp)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "allowPopUp",	VTYPE_boolean, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, UsePopUp)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	bool allowPopUp = args.GetBoolean(0);
	pThis->GetEntity()->UsePopUp(allowPopUp);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, SelectionIsRectangle)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SelectionIsRectangle)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	bool rtn = pThis->GetEntity()->SelectionIsRectangle();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetZoom)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "zoom",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetZoom)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int zoom = args.GetInt(0);
	pThis->GetEntity()->SetZoom(zoom);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetZoom)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetZoom)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int rtn = pThis->GetEntity()->GetZoom();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, CreateDocument)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, CreateDocument)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->CreateDocument();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, AddRefDocument)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "docPointer",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, AddRefDocument)
{
#if 0
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int docPointer = args.GetInt(0);
	pThis->GetEntity()->AddRefDocument(docPointer);
#endif
	SetError_NotImplemented(sig);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, ReleaseDocument)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "docPointer",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, ReleaseDocument)
{
#if 0
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int docPointer = args.GetInt(0);
	pThis->GetEntity()->ReleaseDocument(docPointer);
#endif
	SetError_NotImplemented(sig);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetModEventMask)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetModEventMask)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int rtn = pThis->GetEntity()->GetModEventMask();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetSTCFocus)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "focus",	VTYPE_boolean, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetSTCFocus)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	bool focus = args.GetBoolean(0);
	pThis->GetEntity()->SetSTCFocus(focus);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetSTCFocus)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetSTCFocus)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	bool rtn = pThis->GetEntity()->GetSTCFocus();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetStatus)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "statusCode",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetStatus)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int statusCode = args.GetInt(0);
	pThis->GetEntity()->SetStatus(statusCode);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetStatus)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetStatus)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int rtn = pThis->GetEntity()->GetStatus();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetMouseDownCaptures)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "captures",	VTYPE_boolean, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetMouseDownCaptures)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	bool captures = args.GetBoolean(0);
	pThis->GetEntity()->SetMouseDownCaptures(captures);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetMouseDownCaptures)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetMouseDownCaptures)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	bool rtn = pThis->GetEntity()->GetMouseDownCaptures();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetSTCCursor)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "cursorType",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetSTCCursor)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int cursorType = args.GetInt(0);
	pThis->GetEntity()->SetSTCCursor(cursorType);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetSTCCursor)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetSTCCursor)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int rtn = pThis->GetEntity()->GetSTCCursor();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetControlCharSymbol)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "symbol",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetControlCharSymbol)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int symbol = args.GetInt(0);
	pThis->GetEntity()->SetControlCharSymbol(symbol);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetControlCharSymbol)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetControlCharSymbol)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int rtn = pThis->GetEntity()->GetControlCharSymbol();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, WordPartLeft)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, WordPartLeft)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->WordPartLeft();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, WordPartLeftExtend)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, WordPartLeftExtend)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->WordPartLeftExtend();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, WordPartRight)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, WordPartRight)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->WordPartRight();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, WordPartRightExtend)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, WordPartRightExtend)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->WordPartRightExtend();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetVisiblePolicy)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "visiblePolicy",	VTYPE_number, OCCUR_Once);
	DeclareArg(env, "visibleSlop",		VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetVisiblePolicy)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int visiblePolicy = args.GetInt(0);
	int visibleSlop = args.GetInt(1);
	pThis->GetEntity()->SetVisiblePolicy(visiblePolicy, visibleSlop);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, DelLineLeft)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, DelLineLeft)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->DelLineLeft();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, DelLineRight)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, DelLineRight)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->DelLineRight();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetXOffset)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "newOffset",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetXOffset)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int newOffset = args.GetInt(0);
	pThis->GetEntity()->SetXOffset(newOffset);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetXOffset)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetXOffset)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int rtn = pThis->GetEntity()->GetXOffset();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, ChooseCaretX)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, ChooseCaretX)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->ChooseCaretX();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetXCaretPolicy)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "caretPolicy",	VTYPE_number, OCCUR_Once);
	DeclareArg(env, "caretSlop",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetXCaretPolicy)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int caretPolicy = args.GetInt(0);
	int caretSlop = args.GetInt(1);
	pThis->GetEntity()->SetXCaretPolicy(caretPolicy, caretSlop);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetYCaretPolicy)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "caretPolicy",	VTYPE_number, OCCUR_Once);
	DeclareArg(env, "caretSlop",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetYCaretPolicy)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int caretPolicy = args.GetInt(0);
	int caretSlop = args.GetInt(1);
	pThis->GetEntity()->SetYCaretPolicy(caretPolicy, caretSlop);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetPrintWrapMode)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "mode",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetPrintWrapMode)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int mode = args.GetInt(0);
	pThis->GetEntity()->SetPrintWrapMode(mode);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetPrintWrapMode)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetPrintWrapMode)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int rtn = pThis->GetEntity()->GetPrintWrapMode();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetHotspotActiveForeground)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "useSetting",	VTYPE_boolean, OCCUR_Once);
	DeclareArg(env, "fore",			VTYPE_wx_Colour, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetHotspotActiveForeground)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	bool useSetting = args.GetBoolean(0);
	wxColour *fore = Object_wx_Colour::GetObject(args, 1)->GetEntity();
	pThis->GetEntity()->SetHotspotActiveForeground(useSetting, *fore);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetHotspotActiveForeground)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetHotspotActiveForeground)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	wxColour rtn = pThis->GetEntity()->GetHotspotActiveForeground();
	return ReturnValue(env, sig, args, Value(new Object_wx_Colour(new wxColour(rtn), NULL, OwnerTrue)));
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetHotspotActiveBackground)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "useSetting",	VTYPE_boolean, OCCUR_Once);
	DeclareArg(env, "back",			VTYPE_wx_Colour, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetHotspotActiveBackground)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	bool useSetting = args.GetBoolean(0);
	wxColour *back = Object_wx_Colour::GetObject(args, 1)->GetEntity();
	pThis->GetEntity()->SetHotspotActiveBackground(useSetting, *back);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetHotspotActiveBackground)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetHotspotActiveBackground)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	wxColour rtn = pThis->GetEntity()->GetHotspotActiveBackground();
	return ReturnValue(env, sig, args, Value(new Object_wx_Colour(new wxColour(rtn), NULL, OwnerTrue)));
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetHotspotActiveUnderline)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "underline",	VTYPE_boolean, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetHotspotActiveUnderline)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	bool underline = args.GetBoolean(0);
	pThis->GetEntity()->SetHotspotActiveUnderline(underline);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetHotspotActiveUnderline)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetHotspotActiveUnderline)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	bool rtn = pThis->GetEntity()->GetHotspotActiveUnderline();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetHotspotSingleLine)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "singleLine",	VTYPE_boolean, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetHotspotSingleLine)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	bool singleLine = args.GetBoolean(0);
	pThis->GetEntity()->SetHotspotSingleLine(singleLine);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetHotspotSingleLine)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetHotspotSingleLine)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	bool rtn = pThis->GetEntity()->GetHotspotSingleLine();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, ParaDown)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, ParaDown)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->ParaDown();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, ParaDownExtend)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, ParaDownExtend)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->ParaDownExtend();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, ParaUp)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, ParaUp)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->ParaUp();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, ParaUpExtend)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, ParaUpExtend)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->ParaUpExtend();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, PositionBefore)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "pos",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, PositionBefore)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int pos = args.GetInt(0);
	int rtn = pThis->GetEntity()->PositionBefore(pos);
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, PositionAfter)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "pos",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, PositionAfter)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int pos = args.GetInt(0);
	int rtn = pThis->GetEntity()->PositionAfter(pos);
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, CopyRange)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "start",	VTYPE_number, OCCUR_Once);
	DeclareArg(env, "end",		VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, CopyRange)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int start = args.GetInt(0);
	int end = args.GetInt(1);
	pThis->GetEntity()->CopyRange(start, end);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, CopyText)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "length",	VTYPE_number, OCCUR_Once);
	DeclareArg(env, "text",		VTYPE_string, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, CopyText)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int length = args.GetInt(0);
	wxString text = wxString::FromUTF8(args.GetString(1));
	pThis->GetEntity()->CopyText(length, text);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetSelectionMode)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "mode",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetSelectionMode)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int mode = args.GetInt(0);
	pThis->GetEntity()->SetSelectionMode(mode);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetSelectionMode)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetSelectionMode)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int rtn = pThis->GetEntity()->GetSelectionMode();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetLineSelStartPosition)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "line",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetLineSelStartPosition)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int line = args.GetInt(0);
	int rtn = pThis->GetEntity()->GetLineSelStartPosition(line);
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetLineSelEndPosition)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "line",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetLineSelEndPosition)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int line = args.GetInt(0);
	int rtn = pThis->GetEntity()->GetLineSelEndPosition(line);
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, LineDownRectExtend)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, LineDownRectExtend)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->LineDownRectExtend();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, LineUpRectExtend)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, LineUpRectExtend)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->LineUpRectExtend();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, CharLeftRectExtend)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, CharLeftRectExtend)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->CharLeftRectExtend();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, CharRightRectExtend)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, CharRightRectExtend)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->CharRightRectExtend();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, HomeRectExtend)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, HomeRectExtend)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->HomeRectExtend();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, VCHomeRectExtend)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, VCHomeRectExtend)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->VCHomeRectExtend();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, LineEndRectExtend)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, LineEndRectExtend)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->LineEndRectExtend();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, PageUpRectExtend)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, PageUpRectExtend)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->PageUpRectExtend();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, PageDownRectExtend)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, PageDownRectExtend)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->PageDownRectExtend();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, StutteredPageUp)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, StutteredPageUp)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->StutteredPageUp();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, StutteredPageUpExtend)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, StutteredPageUpExtend)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->StutteredPageUpExtend();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, StutteredPageDown)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, StutteredPageDown)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->StutteredPageDown();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, StutteredPageDownExtend)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, StutteredPageDownExtend)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->StutteredPageDownExtend();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, WordLeftEnd)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, WordLeftEnd)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->WordLeftEnd();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, WordLeftEndExtend)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, WordLeftEndExtend)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->WordLeftEndExtend();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, WordRightEnd)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, WordRightEnd)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->WordRightEnd();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, WordRightEndExtend)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, WordRightEndExtend)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->WordRightEndExtend();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetWhitespaceChars)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "characters",	VTYPE_string, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetWhitespaceChars)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	wxString characters = wxString::FromUTF8(args.GetString(0));
	pThis->GetEntity()->SetWhitespaceChars(characters);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetWhitespaceChars)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetWhitespaceChars)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	wxString rtn = pThis->GetEntity()->GetWhitespaceChars();
	return ReturnValue(env, sig, args, Value(static_cast<const char *>(rtn.ToUTF8())));
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetPunctuationChars)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "characters",	VTYPE_string, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetPunctuationChars)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	wxString characters = wxString::FromUTF8(args.GetString(0));
	pThis->GetEntity()->SetPunctuationChars(characters);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetPunctuationChars)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetPunctuationChars)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	wxString rtn = pThis->GetEntity()->GetPunctuationChars();
	return ReturnValue(env, sig, args, Value(static_cast<const char *>(rtn.ToUTF8())));
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetCharsDefault)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetCharsDefault)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->SetCharsDefault();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, AutoCompGetCurrent)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, AutoCompGetCurrent)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int rtn = pThis->GetEntity()->AutoCompGetCurrent();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, AutoCompSetCaseInsensitiveBehaviour)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "behaviour",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, AutoCompSetCaseInsensitiveBehaviour)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int behaviour = args.GetInt(0);
	pThis->GetEntity()->AutoCompSetCaseInsensitiveBehaviour(behaviour);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, AutoCompGetCaseInsensitiveBehaviour)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, AutoCompGetCaseInsensitiveBehaviour)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int rtn = pThis->GetEntity()->AutoCompGetCaseInsensitiveBehaviour();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, Allocate)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "bytes",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, Allocate)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int bytes = args.GetInt(0);
	pThis->GetEntity()->Allocate(bytes);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, FindColumn)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "line",		VTYPE_number, OCCUR_Once);
	DeclareArg(env, "column",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, FindColumn)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int line = args.GetInt(0);
	int column = args.GetInt(1);
	int rtn = pThis->GetEntity()->FindColumn(line, column);
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetCaretSticky)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetCaretSticky)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int rtn = pThis->GetEntity()->GetCaretSticky();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetCaretSticky)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "useCaretStickyBehaviour",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetCaretSticky)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int useCaretStickyBehaviour = args.GetInt(0);
	pThis->GetEntity()->SetCaretSticky(useCaretStickyBehaviour);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, ToggleCaretSticky)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, ToggleCaretSticky)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->ToggleCaretSticky();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetPasteConvertEndings)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "convert",	VTYPE_boolean, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetPasteConvertEndings)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	bool convert = args.GetBoolean(0);
	pThis->GetEntity()->SetPasteConvertEndings(convert);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetPasteConvertEndings)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetPasteConvertEndings)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	bool rtn = pThis->GetEntity()->GetPasteConvertEndings();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, SelectionDuplicate)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SelectionDuplicate)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->SelectionDuplicate();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetCaretLineBackAlpha)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "alpha",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetCaretLineBackAlpha)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int alpha = args.GetInt(0);
	pThis->GetEntity()->SetCaretLineBackAlpha(alpha);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetCaretLineBackAlpha)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetCaretLineBackAlpha)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int rtn = pThis->GetEntity()->GetCaretLineBackAlpha();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetCaretStyle)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "caretStyle",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetCaretStyle)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int caretStyle = args.GetInt(0);
	pThis->GetEntity()->SetCaretStyle(caretStyle);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetCaretStyle)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetCaretStyle)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int rtn = pThis->GetEntity()->GetCaretStyle();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetIndicatorCurrent)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "indicator",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetIndicatorCurrent)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int indicator = args.GetInt(0);
	pThis->GetEntity()->SetIndicatorCurrent(indicator);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetIndicatorCurrent)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetIndicatorCurrent)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int rtn = pThis->GetEntity()->GetIndicatorCurrent();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetIndicatorValue)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "value",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetIndicatorValue)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int value = args.GetInt(0);
	pThis->GetEntity()->SetIndicatorValue(value);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetIndicatorValue)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetIndicatorValue)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int rtn = pThis->GetEntity()->GetIndicatorValue();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, IndicatorFillRange)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "position",		VTYPE_number, OCCUR_Once);
	DeclareArg(env, "fillLength",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, IndicatorFillRange)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int position = args.GetInt(0);
	int fillLength = args.GetInt(1);
	pThis->GetEntity()->IndicatorFillRange(position, fillLength);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, IndicatorClearRange)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "position",		VTYPE_number, OCCUR_Once);
	DeclareArg(env, "clearLength",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, IndicatorClearRange)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int position = args.GetInt(0);
	int clearLength = args.GetInt(1);
	pThis->GetEntity()->IndicatorClearRange(position, clearLength);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, IndicatorAllOnFor)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "position",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, IndicatorAllOnFor)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int position = args.GetInt(0);
	int rtn = pThis->GetEntity()->IndicatorAllOnFor(position);
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, IndicatorValueAt)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "indicator",	VTYPE_number, OCCUR_Once);
	DeclareArg(env, "position",		VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, IndicatorValueAt)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int indicator = args.GetInt(0);
	int position = args.GetInt(1);
	int rtn = pThis->GetEntity()->IndicatorValueAt(indicator, position);
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, IndicatorStart)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "indicator",	VTYPE_number, OCCUR_Once);
	DeclareArg(env, "position",		VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, IndicatorStart)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int indicator = args.GetInt(0);
	int position = args.GetInt(1);
	int rtn = pThis->GetEntity()->IndicatorStart(indicator, position);
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, IndicatorEnd)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "indicator",	VTYPE_number, OCCUR_Once);
	DeclareArg(env, "position",		VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, IndicatorEnd)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int indicator = args.GetInt(0);
	int position = args.GetInt(1);
	int rtn = pThis->GetEntity()->IndicatorEnd(indicator, position);
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetPositionCacheSize)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "size",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetPositionCacheSize)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int size = args.GetInt(0);
	pThis->GetEntity()->SetPositionCacheSize(size);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetPositionCacheSize)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetPositionCacheSize)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int rtn = pThis->GetEntity()->GetPositionCacheSize();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, CopyAllowLine)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, CopyAllowLine)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->CopyAllowLine();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetCharacterPointer)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetCharacterPointer)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	const char *rtn = pThis->GetEntity()->GetCharacterPointer();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetRangePointer)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "position",		VTYPE_number, OCCUR_Once);
	DeclareArg(env, "rangeLength",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetRangePointer)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int position = args.GetInt(0);
	int rangeLength = args.GetInt(1);
	const char *rtn = pThis->GetEntity()->GetRangePointer(position, rangeLength);
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetGapPosition)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetGapPosition)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int rtn = pThis->GetEntity()->GetGapPosition();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetKeysUnicode)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "keysUnicode",	VTYPE_boolean, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetKeysUnicode)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	bool keysUnicode = args.GetBoolean(0);
	pThis->GetEntity()->SetKeysUnicode(keysUnicode);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetKeysUnicode)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetKeysUnicode)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	bool rtn = pThis->GetEntity()->GetKeysUnicode();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, IndicatorSetAlpha)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "indicator",	VTYPE_number, OCCUR_Once);
	DeclareArg(env, "alpha",		VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, IndicatorSetAlpha)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int indicator = args.GetInt(0);
	int alpha = args.GetInt(1);
	pThis->GetEntity()->IndicatorSetAlpha(indicator, alpha);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, IndicatorGetAlpha)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "indicator",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, IndicatorGetAlpha)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int indicator = args.GetInt(0);
	int rtn = pThis->GetEntity()->IndicatorGetAlpha(indicator);
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, IndicatorSetOutlineAlpha)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "indicator",	VTYPE_number, OCCUR_Once);
	DeclareArg(env, "alpha",		VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, IndicatorSetOutlineAlpha)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int indicator = args.GetInt(0);
	int alpha = args.GetInt(1);
	pThis->GetEntity()->IndicatorSetOutlineAlpha(indicator, alpha);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, IndicatorGetOutlineAlpha)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "indicator",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, IndicatorGetOutlineAlpha)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int indicator = args.GetInt(0);
	int rtn = pThis->GetEntity()->IndicatorGetOutlineAlpha(indicator);
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetExtraAscent)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "extraAscent",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetExtraAscent)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int extraAscent = args.GetInt(0);
	pThis->GetEntity()->SetExtraAscent(extraAscent);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetExtraAscent)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetExtraAscent)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int rtn = pThis->GetEntity()->GetExtraAscent();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetExtraDescent)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "extraDescent",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetExtraDescent)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int extraDescent = args.GetInt(0);
	pThis->GetEntity()->SetExtraDescent(extraDescent);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetExtraDescent)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetExtraDescent)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int rtn = pThis->GetEntity()->GetExtraDescent();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetMarkerSymbolDefined)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "markerNumber",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetMarkerSymbolDefined)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int markerNumber = args.GetInt(0);
	int rtn = pThis->GetEntity()->GetMarkerSymbolDefined(markerNumber);
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, MarginSetText)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "line",	VTYPE_number, OCCUR_Once);
	DeclareArg(env, "text",	VTYPE_string, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, MarginSetText)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int line = args.GetInt(0);
	wxString text = wxString::FromUTF8(args.GetString(1));
	pThis->GetEntity()->MarginSetText(line, text);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, MarginGetText)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "line",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, MarginGetText)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int line = args.GetInt(0);
	wxString rtn = pThis->GetEntity()->MarginGetText(line);
	return ReturnValue(env, sig, args, Value(static_cast<const char *>(rtn.ToUTF8())));
}

Gura_DeclareMethod(wx_StyledTextCtrl, MarginSetStyle)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "line",		VTYPE_number, OCCUR_Once);
	DeclareArg(env, "style",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, MarginSetStyle)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int line = args.GetInt(0);
	int style = args.GetInt(1);
	pThis->GetEntity()->MarginSetStyle(line, style);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, MarginGetStyle)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "line",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, MarginGetStyle)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int line = args.GetInt(0);
	int rtn = pThis->GetEntity()->MarginGetStyle(line);
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, MarginSetStyles)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "line",		VTYPE_number, OCCUR_Once);
	DeclareArg(env, "styles",	VTYPE_string, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, MarginSetStyles)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int line = args.GetInt(0);
	wxString styles = wxString::FromUTF8(args.GetString(1));
	pThis->GetEntity()->MarginSetStyles(line, styles);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, MarginGetStyles)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "line",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, MarginGetStyles)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int line = args.GetInt(0);
	wxString rtn = pThis->GetEntity()->MarginGetStyles(line);
	return ReturnValue(env, sig, args, Value(static_cast<const char *>(rtn.ToUTF8())));
}

Gura_DeclareMethod(wx_StyledTextCtrl, MarginTextClearAll)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, MarginTextClearAll)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->MarginTextClearAll();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, MarginSetStyleOffset)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "style",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, MarginSetStyleOffset)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int style = args.GetInt(0);
	pThis->GetEntity()->MarginSetStyleOffset(style);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, MarginGetStyleOffset)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, MarginGetStyleOffset)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int rtn = pThis->GetEntity()->MarginGetStyleOffset();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetMarginOptions)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "marginOptions",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetMarginOptions)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int marginOptions = args.GetInt(0);
	pThis->GetEntity()->SetMarginOptions(marginOptions);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetMarginOptions)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetMarginOptions)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int rtn = pThis->GetEntity()->GetMarginOptions();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, AnnotationSetText)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "line",	VTYPE_number, OCCUR_Once);
	DeclareArg(env, "text",	VTYPE_string, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, AnnotationSetText)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int line = args.GetInt(0);
	wxString text = wxString::FromUTF8(args.GetString(1));
	pThis->GetEntity()->AnnotationSetText(line, text);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, AnnotationGetText)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "line",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, AnnotationGetText)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int line = args.GetInt(0);
	wxString rtn = pThis->GetEntity()->AnnotationGetText(line);
	return ReturnValue(env, sig, args, Value(static_cast<const char *>(rtn.ToUTF8())));
}

Gura_DeclareMethod(wx_StyledTextCtrl, AnnotationSetStyle)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "line",		VTYPE_number, OCCUR_Once);
	DeclareArg(env, "style",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, AnnotationSetStyle)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int line = args.GetInt(0);
	int style = args.GetInt(1);
	pThis->GetEntity()->AnnotationSetStyle(line, style);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, AnnotationGetStyle)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "line",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, AnnotationGetStyle)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int line = args.GetInt(0);
	int rtn = pThis->GetEntity()->AnnotationGetStyle(line);
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, AnnotationSetStyles)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "line",		VTYPE_number, OCCUR_Once);
	DeclareArg(env, "styles",	VTYPE_string, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, AnnotationSetStyles)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int line = args.GetInt(0);
	wxString styles = wxString::FromUTF8(args.GetString(1));
	pThis->GetEntity()->AnnotationSetStyles(line, styles);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, AnnotationGetStyles)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "line",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, AnnotationGetStyles)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int line = args.GetInt(0);
	wxString rtn = pThis->GetEntity()->AnnotationGetStyles(line);
	return ReturnValue(env, sig, args, Value(static_cast<const char *>(rtn.ToUTF8())));
}

Gura_DeclareMethod(wx_StyledTextCtrl, AnnotationGetLines)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "line",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, AnnotationGetLines)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int line = args.GetInt(0);
	int rtn = pThis->GetEntity()->AnnotationGetLines(line);
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, AnnotationClearAll)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, AnnotationClearAll)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->AnnotationClearAll();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, AnnotationSetVisible)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "visible",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, AnnotationSetVisible)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int visible = args.GetInt(0);
	pThis->GetEntity()->AnnotationSetVisible(visible);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, AnnotationGetVisible)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, AnnotationGetVisible)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int rtn = pThis->GetEntity()->AnnotationGetVisible();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, AnnotationSetStyleOffset)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "style",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, AnnotationSetStyleOffset)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int style = args.GetInt(0);
	pThis->GetEntity()->AnnotationSetStyleOffset(style);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, AnnotationGetStyleOffset)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, AnnotationGetStyleOffset)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int rtn = pThis->GetEntity()->AnnotationGetStyleOffset();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, AddUndoAction)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "token",	VTYPE_number, OCCUR_Once);
	DeclareArg(env, "flags",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, AddUndoAction)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int token = args.GetInt(0);
	int flags = args.GetInt(1);
	pThis->GetEntity()->AddUndoAction(token, flags);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, CharPositionFromPoint)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "x",	VTYPE_number, OCCUR_Once);
	DeclareArg(env, "y",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, CharPositionFromPoint)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int x = args.GetInt(0);
	int y = args.GetInt(1);
	int rtn = pThis->GetEntity()->CharPositionFromPoint(x, y);
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, CharPositionFromPointClose)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "x",	VTYPE_number, OCCUR_Once);
	DeclareArg(env, "y",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, CharPositionFromPointClose)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int x = args.GetInt(0);
	int y = args.GetInt(1);
	int rtn = pThis->GetEntity()->CharPositionFromPointClose(x, y);
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetMultipleSelection)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "multipleSelection",	VTYPE_boolean, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetMultipleSelection)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	bool multipleSelection = args.GetBoolean(0);
	pThis->GetEntity()->SetMultipleSelection(multipleSelection);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetMultipleSelection)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetMultipleSelection)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	bool rtn = pThis->GetEntity()->GetMultipleSelection();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetAdditionalSelectionTyping)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "additionalSelectionTyping",	VTYPE_boolean, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetAdditionalSelectionTyping)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	bool additionalSelectionTyping = args.GetBoolean(0);
	pThis->GetEntity()->SetAdditionalSelectionTyping(additionalSelectionTyping);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetAdditionalSelectionTyping)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetAdditionalSelectionTyping)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	bool rtn = pThis->GetEntity()->GetAdditionalSelectionTyping();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetAdditionalCaretsBlink)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "additionalCaretsBlink",	VTYPE_boolean, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetAdditionalCaretsBlink)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	bool additionalCaretsBlink = args.GetBoolean(0);
	pThis->GetEntity()->SetAdditionalCaretsBlink(additionalCaretsBlink);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetAdditionalCaretsBlink)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetAdditionalCaretsBlink)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	bool rtn = pThis->GetEntity()->GetAdditionalCaretsBlink();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetAdditionalCaretsVisible)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "additionalCaretsBlink",	VTYPE_boolean, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetAdditionalCaretsVisible)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	bool additionalCaretsBlink = args.GetBoolean(0);
	pThis->GetEntity()->SetAdditionalCaretsVisible(additionalCaretsBlink);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetAdditionalCaretsVisible)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetAdditionalCaretsVisible)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	bool rtn = pThis->GetEntity()->GetAdditionalCaretsVisible();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetSelections)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetSelections)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int rtn = pThis->GetEntity()->GetSelections();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, ClearSelections)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, ClearSelections)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->ClearSelections();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, AddSelection)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "caret",	VTYPE_number, OCCUR_Once);
	DeclareArg(env, "anchor",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, AddSelection)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int caret = args.GetInt(0);
	int anchor = args.GetInt(1);
	int rtn = pThis->GetEntity()->AddSelection(caret, anchor);
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetMainSelection)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "selection",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetMainSelection)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int selection = args.GetInt(0);
	pThis->GetEntity()->SetMainSelection(selection);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetMainSelection)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetMainSelection)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int rtn = pThis->GetEntity()->GetMainSelection();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetSelectionNCaret)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "selection",	VTYPE_number, OCCUR_Once);
	DeclareArg(env, "pos",			VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetSelectionNCaret)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int selection = args.GetInt(0);
	int pos = args.GetInt(1);
	pThis->GetEntity()->SetSelectionNCaret(selection, pos);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetSelectionNCaret)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "selection",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetSelectionNCaret)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int selection = args.GetInt(0);
	int rtn = pThis->GetEntity()->GetSelectionNCaret(selection);
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetSelectionNAnchor)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "selection",	VTYPE_number, OCCUR_Once);
	DeclareArg(env, "posAnchor",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetSelectionNAnchor)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int selection = args.GetInt(0);
	int posAnchor = args.GetInt(1);
	pThis->GetEntity()->SetSelectionNAnchor(selection, posAnchor);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetSelectionNAnchor)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "selection",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetSelectionNAnchor)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int selection = args.GetInt(0);
	int rtn = pThis->GetEntity()->GetSelectionNAnchor(selection);
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetSelectionNCaretVirtualSpace)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "selection",	VTYPE_number, OCCUR_Once);
	DeclareArg(env, "space",		VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetSelectionNCaretVirtualSpace)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int selection = args.GetInt(0);
	int space = args.GetInt(1);
	pThis->GetEntity()->SetSelectionNCaretVirtualSpace(selection, space);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetSelectionNCaretVirtualSpace)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "selection",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetSelectionNCaretVirtualSpace)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int selection = args.GetInt(0);
	int rtn = pThis->GetEntity()->GetSelectionNCaretVirtualSpace(selection);
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetSelectionNAnchorVirtualSpace)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "selection",	VTYPE_number, OCCUR_Once);
	DeclareArg(env, "space",		VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetSelectionNAnchorVirtualSpace)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int selection = args.GetInt(0);
	int space = args.GetInt(1);
	pThis->GetEntity()->SetSelectionNAnchorVirtualSpace(selection, space);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetSelectionNAnchorVirtualSpace)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "selection",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetSelectionNAnchorVirtualSpace)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int selection = args.GetInt(0);
	int rtn = pThis->GetEntity()->GetSelectionNAnchorVirtualSpace(selection);
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetSelectionNStart)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "selection",	VTYPE_number, OCCUR_Once);
	DeclareArg(env, "pos",			VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetSelectionNStart)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int selection = args.GetInt(0);
	int pos = args.GetInt(1);
	pThis->GetEntity()->SetSelectionNStart(selection, pos);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetSelectionNStart)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "selection",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetSelectionNStart)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int selection = args.GetInt(0);
	int rtn = pThis->GetEntity()->GetSelectionNStart(selection);
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetSelectionNEnd)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "selection",	VTYPE_number, OCCUR_Once);
	DeclareArg(env, "pos",			VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetSelectionNEnd)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int selection = args.GetInt(0);
	int pos = args.GetInt(1);
	pThis->GetEntity()->SetSelectionNEnd(selection, pos);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetSelectionNEnd)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "selection",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetSelectionNEnd)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int selection = args.GetInt(0);
	int rtn = pThis->GetEntity()->GetSelectionNEnd(selection);
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetRectangularSelectionCaret)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "pos",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetRectangularSelectionCaret)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int pos = args.GetInt(0);
	pThis->GetEntity()->SetRectangularSelectionCaret(pos);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetRectangularSelectionCaret)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetRectangularSelectionCaret)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int rtn = pThis->GetEntity()->GetRectangularSelectionCaret();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetRectangularSelectionAnchor)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "posAnchor",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetRectangularSelectionAnchor)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int posAnchor = args.GetInt(0);
	pThis->GetEntity()->SetRectangularSelectionAnchor(posAnchor);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetRectangularSelectionAnchor)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetRectangularSelectionAnchor)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int rtn = pThis->GetEntity()->GetRectangularSelectionAnchor();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetRectangularSelectionCaretVirtualSpace)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "space",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetRectangularSelectionCaretVirtualSpace)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int space = args.GetInt(0);
	pThis->GetEntity()->SetRectangularSelectionCaretVirtualSpace(space);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetRectangularSelectionCaretVirtualSpace)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetRectangularSelectionCaretVirtualSpace)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int rtn = pThis->GetEntity()->GetRectangularSelectionCaretVirtualSpace();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetRectangularSelectionAnchorVirtualSpace)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "space",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetRectangularSelectionAnchorVirtualSpace)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int space = args.GetInt(0);
	pThis->GetEntity()->SetRectangularSelectionAnchorVirtualSpace(space);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetRectangularSelectionAnchorVirtualSpace)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetRectangularSelectionAnchorVirtualSpace)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int rtn = pThis->GetEntity()->GetRectangularSelectionAnchorVirtualSpace();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetVirtualSpaceOptions)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "virtualSpaceOptions",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetVirtualSpaceOptions)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int virtualSpaceOptions = args.GetInt(0);
	pThis->GetEntity()->SetVirtualSpaceOptions(virtualSpaceOptions);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetVirtualSpaceOptions)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetVirtualSpaceOptions)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int rtn = pThis->GetEntity()->GetVirtualSpaceOptions();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetRectangularSelectionModifier)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "modifier",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetRectangularSelectionModifier)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int modifier = args.GetInt(0);
	pThis->GetEntity()->SetRectangularSelectionModifier(modifier);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetRectangularSelectionModifier)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetRectangularSelectionModifier)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int rtn = pThis->GetEntity()->GetRectangularSelectionModifier();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetAdditionalSelForeground)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "fore",	VTYPE_wx_Colour, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetAdditionalSelForeground)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	wxColour *fore = Object_wx_Colour::GetObject(args, 0)->GetEntity();
	pThis->GetEntity()->SetAdditionalSelForeground(*fore);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetAdditionalSelBackground)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "back",	VTYPE_wx_Colour, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetAdditionalSelBackground)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	wxColour *back = Object_wx_Colour::GetObject(args, 0)->GetEntity();
	pThis->GetEntity()->SetAdditionalSelBackground(*back);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetAdditionalSelAlpha)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "alpha",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetAdditionalSelAlpha)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int alpha = args.GetInt(0);
	pThis->GetEntity()->SetAdditionalSelAlpha(alpha);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetAdditionalSelAlpha)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetAdditionalSelAlpha)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int rtn = pThis->GetEntity()->GetAdditionalSelAlpha();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetAdditionalCaretForeground)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "fore",	VTYPE_wx_Colour, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetAdditionalCaretForeground)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	wxColour *fore = Object_wx_Colour::GetObject(args, 0)->GetEntity();
	pThis->GetEntity()->SetAdditionalCaretForeground(*fore);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetAdditionalCaretForeground)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetAdditionalCaretForeground)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	wxColour rtn = pThis->GetEntity()->GetAdditionalCaretForeground();
	return ReturnValue(env, sig, args, Value(new Object_wx_Colour(new wxColour(rtn), NULL, OwnerTrue)));
}

Gura_DeclareMethod(wx_StyledTextCtrl, RotateSelection)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, RotateSelection)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->RotateSelection();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, SwapMainAnchorCaret)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SwapMainAnchorCaret)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->SwapMainAnchorCaret();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, ChangeLexerState)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "start",	VTYPE_number, OCCUR_Once);
	DeclareArg(env, "end",		VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, ChangeLexerState)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int start = args.GetInt(0);
	int end = args.GetInt(1);
	int rtn = pThis->GetEntity()->ChangeLexerState(start, end);
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, ContractedFoldNext)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "lineStart",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, ContractedFoldNext)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int lineStart = args.GetInt(0);
	int rtn = pThis->GetEntity()->ContractedFoldNext(lineStart);
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, VerticalCentreCaret)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, VerticalCentreCaret)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->VerticalCentreCaret();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, MoveSelectedLinesUp)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, MoveSelectedLinesUp)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->MoveSelectedLinesUp();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, MoveSelectedLinesDown)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, MoveSelectedLinesDown)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->MoveSelectedLinesDown();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetIdentifier)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "identifier",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetIdentifier)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int identifier = args.GetInt(0);
	pThis->GetEntity()->SetIdentifier(identifier);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetIdentifier)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetIdentifier)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int rtn = pThis->GetEntity()->GetIdentifier();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, RGBAImageSetWidth)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "width",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, RGBAImageSetWidth)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int width = args.GetInt(0);
	pThis->GetEntity()->RGBAImageSetWidth(width);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, RGBAImageSetHeight)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "height",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, RGBAImageSetHeight)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int height = args.GetInt(0);
	pThis->GetEntity()->RGBAImageSetHeight(height);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, MarkerDefineRGBAImage)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "markerNumber",	VTYPE_number, OCCUR_Once);
	DeclareArg(env, "pixels",		VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, MarkerDefineRGBAImage)
{
#if 0
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int markerNumber = args.GetInt(0);
	unsigned char pixels = args.GetUChar(1);
	pThis->GetEntity()->MarkerDefineRGBAImage(markerNumber, pixels);
#endif
	SetError_NotImplemented(sig);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, RegisterRGBAImage)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "type",		VTYPE_number, OCCUR_Once);
	DeclareArg(env, "pixels",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, RegisterRGBAImage)
{
#if 0
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int type = args.GetInt(0);
	unsigned char pixels = args.GetUChar(1);
	pThis->GetEntity()->RegisterRGBAImage(type, pixels);
#endif
	SetError_NotImplemented(sig);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, ScrollToStart)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, ScrollToStart)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->ScrollToStart();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, ScrollToEnd)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, ScrollToEnd)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->ScrollToEnd();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetTechnology)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "technology",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetTechnology)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int technology = args.GetInt(0);
	pThis->GetEntity()->SetTechnology(technology);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetTechnology)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetTechnology)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int rtn = pThis->GetEntity()->GetTechnology();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, CreateLoader)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "bytes",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, CreateLoader)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int bytes = args.GetInt(0);
	pThis->GetEntity()->CreateLoader(bytes);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, StartRecord)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, StartRecord)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->StartRecord();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, StopRecord)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, StopRecord)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->StopRecord();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetLexer)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "lexer",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetLexer)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int lexer = args.GetInt(0);
	pThis->GetEntity()->SetLexer(lexer);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetLexer)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetLexer)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int rtn = pThis->GetEntity()->GetLexer();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, Colourise)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "start",	VTYPE_number, OCCUR_Once);
	DeclareArg(env, "end",		VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, Colourise)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int start = args.GetInt(0);
	int end = args.GetInt(1);
	pThis->GetEntity()->Colourise(start, end);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetProperty)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "key",		VTYPE_string, OCCUR_Once);
	DeclareArg(env, "value",	VTYPE_string, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetProperty)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	wxString key = wxString::FromUTF8(args.GetString(0));
	wxString value = wxString::FromUTF8(args.GetString(1));
	pThis->GetEntity()->SetProperty(key, value);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetKeyWords)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "keywordSet",	VTYPE_number, OCCUR_Once);
	DeclareArg(env, "keyWords",		VTYPE_string, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetKeyWords)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int keywordSet = args.GetInt(0);
	wxString keyWords = wxString::FromUTF8(args.GetString(1));
	pThis->GetEntity()->SetKeyWords(keywordSet, keyWords);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetLexerLanguage)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "language",	VTYPE_string, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetLexerLanguage)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	wxString language = wxString::FromUTF8(args.GetString(0));
	pThis->GetEntity()->SetLexerLanguage(language);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetProperty)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "key",	VTYPE_string, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetProperty)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	wxString key = wxString::FromUTF8(args.GetString(0));
	wxString rtn = pThis->GetEntity()->GetProperty(key);
	return ReturnValue(env, sig, args, Value(static_cast<const char *>(rtn.ToUTF8())));
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetPropertyExpanded)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "key",	VTYPE_string, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetPropertyExpanded)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	wxString key = wxString::FromUTF8(args.GetString(0));
	wxString rtn = pThis->GetEntity()->GetPropertyExpanded(key);
	return ReturnValue(env, sig, args, Value(static_cast<const char *>(rtn.ToUTF8())));
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetPropertyInt)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "key",	VTYPE_string, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetPropertyInt)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	wxString key = wxString::FromUTF8(args.GetString(0));
	int rtn = pThis->GetEntity()->GetPropertyInt(key);
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetStyleBitsNeeded)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetStyleBitsNeeded)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int rtn = pThis->GetEntity()->GetStyleBitsNeeded();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, PrivateLexerCall)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "operation",	VTYPE_number, OCCUR_Once);
	DeclareArg(env, "pointer",		VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, PrivateLexerCall)
{
#if 0
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int operation = args.GetInt(0);
	int pointer = args.GetInt(1);
	pThis->GetEntity()->PrivateLexerCall(operation, pointer);
#endif
	SetError_NotImplemented(sig);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, PropertyNames)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, PropertyNames)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	wxString rtn = pThis->GetEntity()->PropertyNames();
	return ReturnValue(env, sig, args, Value(static_cast<const char *>(rtn.ToUTF8())));
}

Gura_DeclareMethod(wx_StyledTextCtrl, PropertyType)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "name",	VTYPE_string, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, PropertyType)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	wxString name = wxString::FromUTF8(args.GetString(0));
	int rtn = pThis->GetEntity()->PropertyType(name);
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, DescribeProperty)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "name",	VTYPE_string, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, DescribeProperty)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	wxString name = wxString::FromUTF8(args.GetString(0));
	wxString rtn = pThis->GetEntity()->DescribeProperty(name);
	return ReturnValue(env, sig, args, Value(static_cast<const char *>(rtn.ToUTF8())));
}

Gura_DeclareMethod(wx_StyledTextCtrl, DescribeKeyWordSets)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, DescribeKeyWordSets)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	wxString rtn = pThis->GetEntity()->DescribeKeyWordSets();
	return ReturnValue(env, sig, args, Value(static_cast<const char *>(rtn.ToUTF8())));
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetCurrentLine)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetCurrentLine)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int rtn = pThis->GetEntity()->GetCurrentLine();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, StyleSetSpec)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "styleNum",	VTYPE_number, OCCUR_Once);
	DeclareArg(env, "spec",		VTYPE_string, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, StyleSetSpec)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int styleNum = args.GetInt(0);
	wxString spec = wxString::FromUTF8(args.GetString(1));
	pThis->GetEntity()->StyleSetSpec(styleNum, spec);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, StyleGetFont)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "style",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, StyleGetFont)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int style = args.GetInt(0);
	wxFont rtn = pThis->GetEntity()->StyleGetFont(style);
	return ReturnValue(env, sig, args, Value(new Object_wx_Font(new wxFont(rtn), NULL, OwnerTrue)));
}

Gura_DeclareMethod(wx_StyledTextCtrl, StyleSetFont)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "styleNum",	VTYPE_number, OCCUR_Once);
	DeclareArg(env, "font",		VTYPE_wx_Font, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, StyleSetFont)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int styleNum = args.GetInt(0);
	wxFont *font = Object_wx_Font::GetObject(args, 1)->GetEntity();
	pThis->GetEntity()->StyleSetFont(styleNum, *font);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, StyleSetFontAttr)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "styleNum",		VTYPE_number, OCCUR_Once);
	DeclareArg(env, "size",			VTYPE_number, OCCUR_Once);
	DeclareArg(env, "faceName",		VTYPE_string, OCCUR_Once);
	DeclareArg(env, "bold",			VTYPE_boolean, OCCUR_Once);
	DeclareArg(env, "italic",		VTYPE_boolean, OCCUR_Once);
	DeclareArg(env, "underline",	VTYPE_boolean, OCCUR_Once);
	DeclareArg(env, "encoding",		VTYPE_number, OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_StyledTextCtrl, StyleSetFontAttr)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int styleNum = args.GetInt(0);
	int size = args.GetInt(1);
	wxString faceName = wxString::FromUTF8(args.GetString(2));
	bool bold = args.GetBoolean(3);
	bool italic = args.GetBoolean(4);
	bool underline = args.GetBoolean(5);
	wxFontEncoding encoding = wxFONTENCODING_DEFAULT;
	if (args.IsValid(6)) encoding = static_cast<wxFontEncoding>(args.GetInt(6));
	pThis->GetEntity()->StyleSetFontAttr(styleNum, size, faceName, bold, italic, underline, encoding);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, StyleSetCharacterSet)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "style",		VTYPE_number, OCCUR_Once);
	DeclareArg(env, "characterSet",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, StyleSetCharacterSet)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int style = args.GetInt(0);
	int characterSet = args.GetInt(1);
	pThis->GetEntity()->StyleSetCharacterSet(style, characterSet);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, StyleSetFontEncoding)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "style",	VTYPE_number, OCCUR_Once);
	DeclareArg(env, "encoding",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, StyleSetFontEncoding)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int style = args.GetInt(0);
	wxFontEncoding encoding = static_cast<wxFontEncoding>(args.GetInt(1));
	pThis->GetEntity()->StyleSetFontEncoding(style, encoding);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, CmdKeyExecute)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "cmd",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, CmdKeyExecute)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int cmd = args.GetInt(0);
	pThis->GetEntity()->CmdKeyExecute(cmd);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetMargins)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "left",		VTYPE_number, OCCUR_Once);
	DeclareArg(env, "right",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetMargins)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int left = args.GetInt(0);
	int right = args.GetInt(1);
	pThis->GetEntity()->SetMargins(left, right);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, PointFromPosition)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "pos",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, PointFromPosition)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int pos = args.GetInt(0);
	wxPoint rtn = pThis->GetEntity()->PointFromPosition(pos);
	return ReturnValue(env, sig, args, Value(new Object_wx_Point(new wxPoint(rtn), NULL, OwnerTrue)));
}

Gura_DeclareMethod(wx_StyledTextCtrl, ScrollToLine)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "line",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, ScrollToLine)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int line = args.GetInt(0);
	pThis->GetEntity()->ScrollToLine(line);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, ScrollToColumn)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "column",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, ScrollToColumn)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int column = args.GetInt(0);
	pThis->GetEntity()->ScrollToColumn(column);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, SendMsg)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "msg",	VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "wp",	VTYPE_wx_UIntPtr, OCCUR_ZeroOrOnce);
	//DeclareArg(env, "lp",	VTYPE_wx_IntPtr, OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SendMsg)
{
#if 0
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int msg = args.GetInt(0);
	wxUIntPtr *wp = (wxUIntPtr *)(&0);
	if (args.IsValid(1)) wp = Object_wx_UIntPtr::GetObject(args, 1)->GetEntity();
	wxIntPtr *lp = (wxIntPtr *)(&0);
	if (args.IsValid(2)) lp = Object_wx_IntPtr::GetObject(args, 2)->GetEntity();
	wxIntPtr rtn = pThis->GetEntity()->SendMsg(msg, *wp, *lp);
	return ReturnValue(env, sig, args, Value(new Object_wx_IntPtr(new wxIntPtr(rtn), NULL, OwnerTrue)));
#endif
	SetError_NotImplemented(sig);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetVScrollBar)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "bar",	VTYPE_wx_ScrollBar, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetVScrollBar)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	wxScrollBar *bar = Object_wx_ScrollBar::GetObject(args, 0)->GetEntity();
	pThis->GetEntity()->SetVScrollBar(bar);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetHScrollBar)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "bar",	VTYPE_wx_ScrollBar, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetHScrollBar)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	wxScrollBar *bar = Object_wx_ScrollBar::GetObject(args, 0)->GetEntity();
	pThis->GetEntity()->SetHScrollBar(bar);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetLastKeydownProcessed)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetLastKeydownProcessed)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	bool rtn = pThis->GetEntity()->GetLastKeydownProcessed();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetLastKeydownProcessed)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "val",	VTYPE_boolean, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetLastKeydownProcessed)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	bool val = args.GetBoolean(0);
	pThis->GetEntity()->SetLastKeydownProcessed(val);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, SaveFile)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "filename",	VTYPE_string, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SaveFile)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	wxString filename = wxString::FromUTF8(args.GetString(0));
	bool rtn = pThis->GetEntity()->SaveFile(filename);
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, LoadFile)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "filename",	VTYPE_string, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, LoadFile)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	wxString filename = wxString::FromUTF8(args.GetString(0));
	bool rtn = pThis->GetEntity()->LoadFile(filename);
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, DoDragOver)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "x",			VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "y",			VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "defaultRes",	VTYPE_wx_DragResult, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, DoDragOver)
{
#if 0
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	wxCoord x = static_cast<wxCoord>(args.GetInt(0));
	wxCoord y = static_cast<wxCoord>(args.GetInt(1));
	wxDragResult *defaultRes = Object_wx_DragResult::GetObject(args, 2)->GetEntity();
	wxDragResult rtn = pThis->GetEntity()->DoDragOver(x, y, *defaultRes);
	return ReturnValue(env, sig, args, Value(new Object_wx_DragResult(new wxDragResult(rtn), NULL, OwnerTrue)));
#endif
	SetError_NotImplemented(sig);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, DoDropText)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "x",	VTYPE_number, OCCUR_Once);
	DeclareArg(env, "y",	VTYPE_number, OCCUR_Once);
	DeclareArg(env, "data",	VTYPE_string, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, DoDropText)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	long x = args.GetLong(0);
	long y = args.GetLong(1);
	wxString data = wxString::FromUTF8(args.GetString(2));
	bool rtn = pThis->GetEntity()->DoDropText(x, y, data);
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, AnnotationClearLine)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "line",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, AnnotationClearLine)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int line = args.GetInt(0);
	pThis->GetEntity()->AnnotationClearLine(line);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, AddTextRaw)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "text",		VTYPE_string, OCCUR_Once);
	DeclareArg(env, "length",	VTYPE_number, OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_StyledTextCtrl, AddTextRaw)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	const char *text = args.GetString(0);
	int length = -1;
	if (args.IsValid(1)) length = args.GetInt(1);
	pThis->GetEntity()->AddTextRaw(text, length);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, InsertTextRaw)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "pos",	VTYPE_number, OCCUR_Once);
	DeclareArg(env, "text",	VTYPE_string, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, InsertTextRaw)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int pos = args.GetInt(0);
	const char *text = args.GetString(1);
	pThis->GetEntity()->InsertTextRaw(pos, text);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetCurLineRaw)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetCurLineRaw)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int linePos = 0;
	wxCharBuffer rtn = pThis->GetEntity()->GetCurLineRaw(&linePos);
	return ReturnValue(env, sig, args, Value::CreateAsList(env, Value(rtn), Value(linePos)));
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetLineRaw)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "line",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetLineRaw)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int line = args.GetInt(0);
	wxCharBuffer rtn = pThis->GetEntity()->GetLineRaw(line);
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetSelectedTextRaw)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetSelectedTextRaw)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	wxCharBuffer rtn = pThis->GetEntity()->GetSelectedTextRaw();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetTextRangeRaw)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "startPos",	VTYPE_number, OCCUR_Once);
	DeclareArg(env, "endPos",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetTextRangeRaw)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int startPos = args.GetInt(0);
	int endPos = args.GetInt(1);
	wxCharBuffer rtn = pThis->GetEntity()->GetTextRangeRaw(startPos, endPos);
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetTextRaw)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "text",	VTYPE_string, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetTextRaw)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	const char *text = args.GetString(0);
	pThis->GetEntity()->SetTextRaw(text);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetTextRaw)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetTextRaw)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	wxCharBuffer rtn = pThis->GetEntity()->GetTextRaw();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, AppendTextRaw)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "text",		VTYPE_string, OCCUR_Once);
	DeclareArg(env, "length",	VTYPE_number, OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_StyledTextCtrl, AppendTextRaw)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	const char *text = args.GetString(0);
	int length = -1;
	if (args.IsValid(1)) length = args.GetInt(1);
	pThis->GetEntity()->AppendTextRaw(text, length);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetLibraryVersionInfo)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetLibraryVersionInfo)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	wxVersionInfo rtn = pThis->GetEntity()->GetLibraryVersionInfo();
	return ReturnValue(env, sig, args, Value(new Object_wx_VersionInfo(new wxVersionInfo(rtn), NULL, OwnerTrue)));
}

Gura_DeclareMethod(wx_StyledTextCtrl, WriteText)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "text",	VTYPE_string, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, WriteText)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	wxString text = wxString::FromUTF8(args.GetString(0));
	pThis->GetEntity()->WriteText(text);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, Remove)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "from",	VTYPE_number, OCCUR_Once);
	DeclareArg(env, "to",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, Remove)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	long from = args.GetLong(0);
	long to = args.GetLong(1);
	pThis->GetEntity()->Remove(from, to);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, Replace)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "from",	VTYPE_number, OCCUR_Once);
	DeclareArg(env, "to",	VTYPE_number, OCCUR_Once);
	DeclareArg(env, "text",	VTYPE_string, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, Replace)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	long from = args.GetLong(0);
	long to = args.GetLong(1);
	wxString text = wxString::FromUTF8(args.GetString(2));
	pThis->GetEntity()->Replace(from, to, text);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetInsertionPoint)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "pos",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetInsertionPoint)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	long pos = args.GetLong(0);
	pThis->GetEntity()->SetInsertionPoint(pos);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetInsertionPoint)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetInsertionPoint)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	long rtn = pThis->GetEntity()->GetInsertionPoint();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetLastPosition)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetLastPosition)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	long rtn = pThis->GetEntity()->GetLastPosition();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetSelection)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "from",	VTYPE_number, OCCUR_Once);
	DeclareArg(env, "to",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetSelection)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	long from = args.GetLong(0);
	long to = args.GetLong(1);
	pThis->GetEntity()->SetSelection(from, to);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, SelectNone)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SelectNone)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->SelectNone();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetSelection)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "from",	VTYPE_number, OCCUR_Once);
	DeclareArg(env, "to",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetSelection)
{
#if 0
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	long from = args.GetLong(0);
	long to = args.GetLong(1);
	pThis->GetEntity()->GetSelection(from, to);
#endif
	SetError_NotImplemented(sig);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, IsEditable)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, IsEditable)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	bool rtn = pThis->GetEntity()->IsEditable();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetEditable)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "editable",	VTYPE_boolean, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetEditable)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	bool editable = args.GetBoolean(0);
	pThis->GetEntity()->SetEditable(editable);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetLineLength)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "n",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetLineLength)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	long n = args.GetLong(0);
	int rtn = pThis->GetEntity()->GetLineLength(n);
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetLineText)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "n",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetLineText)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	long n = args.GetLong(0);
	wxString rtn = pThis->GetEntity()->GetLineText(n);
	return ReturnValue(env, sig, args, Value(static_cast<const char *>(rtn.ToUTF8())));
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetNumberOfLines)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetNumberOfLines)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int rtn = pThis->GetEntity()->GetNumberOfLines();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, IsModified)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, IsModified)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	bool rtn = pThis->GetEntity()->IsModified();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, MarkDirty)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, MarkDirty)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->MarkDirty();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, DiscardEdits)
{
	SetMode(RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StyledTextCtrl, DiscardEdits)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->DiscardEdits();
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetStyle)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "start",	VTYPE_number, OCCUR_Once);
	DeclareArg(env, "end",		VTYPE_number, OCCUR_Once);
	DeclareArg(env, "style",	VTYPE_wx_TextAttr, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetStyle)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	long start = args.GetLong(0);
	long end = args.GetLong(1);
	wxTextAttr *style = Object_wx_TextAttr::GetObject(args, 2)->GetEntity();
	bool rtn = pThis->GetEntity()->SetStyle(start, end, *style);
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, GetStyle)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "position",	VTYPE_number, OCCUR_Once);
	DeclareArg(env, "style",	VTYPE_wx_TextAttr, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, GetStyle)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	long position = args.GetLong(0);
	wxTextAttr *style = Object_wx_TextAttr::GetObject(args, 1)->GetEntity();
	bool rtn = pThis->GetEntity()->GetStyle(position, *style);
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, SetDefaultStyle)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "style",	VTYPE_wx_TextAttr, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, SetDefaultStyle)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	wxTextAttr *style = Object_wx_TextAttr::GetObject(args, 0)->GetEntity();
	bool rtn = pThis->GetEntity()->SetDefaultStyle(*style);
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, XYToPosition)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "x",	VTYPE_number, OCCUR_Once);
	DeclareArg(env, "y",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, XYToPosition)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	long x = args.GetLong(0);
	long y = args.GetLong(1);
	long rtn = pThis->GetEntity()->XYToPosition(x, y);
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_StyledTextCtrl, PositionToXY)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "pos",	VTYPE_number, OCCUR_Once);
	DeclareArg(env, "x",	VTYPE_number, OCCUR_Once);
	DeclareArg(env, "y",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, PositionToXY)
{
#if 0
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	long pos = args.GetLong(0);
	long x = args.GetLong(1);
	long y = args.GetLong(2);
	bool rtn = pThis->GetEntity()->PositionToXY(pos, x, y);
	return ReturnValue(env, sig, args, Value(rtn));
#endif
	SetError_NotImplemented(sig);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, ShowPosition)
{
	SetMode(RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "pos",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, ShowPosition)
{
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	long pos = args.GetLong(0);
	pThis->GetEntity()->ShowPosition(pos);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, HitTest)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "pt",	VTYPE_wx_Point, OCCUR_Once);
	DeclareArg(env, "pos",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, HitTest)
{
#if 0
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	wxPoint *pt = Object_wx_Point::GetObject(args, 0)->GetEntity();
	long pos = args.GetLong(1);
	wxTextCtrlHitTestResult rtn = pThis->GetEntity()->HitTest(*pt, pos);
	return ReturnValue(env, sig, args, Value(new Object_wx_TextCtrlHitTestResult(new wxTextCtrlHitTestResult(rtn), NULL, OwnerTrue)));
#endif
	SetError_NotImplemented(sig);
	return Value::Null;
}

Gura_DeclareMethod(wx_StyledTextCtrl, HitTestXY)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "pt",	VTYPE_wx_Point, OCCUR_Once);
	DeclareArg(env, "col",	VTYPE_number, OCCUR_Once);
	DeclareArg(env, "row",	VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StyledTextCtrl, HitTestXY)
{
#if 0
	Object_wx_StyledTextCtrl *pThis = Object_wx_StyledTextCtrl::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	wxPoint *pt = Object_wx_Point::GetObject(args, 0)->GetEntity();
	wxTextCoord col = static_cast<wxTextCoord>(args.GetInt(1));
	wxTextCoord row = static_cast<wxTextCoord>(args.GetInt(2));
	wxTextCtrlHitTestResult rtn = pThis->GetEntity()->HitTest(*pt, col, row);
	return ReturnValue(env, sig, args, Value(new Object_wx_TextCtrlHitTestResult(new wxTextCtrlHitTestResult(rtn), NULL, OwnerTrue)));
#endif
	SetError_NotImplemented(sig);
	return Value::Null;
}

//----------------------------------------------------------------------------
// Implementation of class
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_StyledTextCtrl)
{
	// assignment of values
	Gura_AssignWxValue(STC_INVALID_POSITION);
	Gura_AssignWxValue(STC_START);
	Gura_AssignWxValue(STC_OPTIONAL_START);
	Gura_AssignWxValue(STC_LEXER_START);
	Gura_AssignWxValue(STC_WS_INVISIBLE);
	Gura_AssignWxValue(STC_WS_VISIBLEALWAYS);
	Gura_AssignWxValue(STC_WS_VISIBLEAFTERINDENT);
	Gura_AssignWxValue(STC_EOL_CRLF);
	Gura_AssignWxValue(STC_EOL_CR);
	Gura_AssignWxValue(STC_EOL_LF);
	Gura_AssignWxValue(STC_CP_UTF8);
	Gura_AssignWxValue(STC_MARKER_MAX);
	Gura_AssignWxValue(STC_MARK_CIRCLE);
	Gura_AssignWxValue(STC_MARK_ROUNDRECT);
	Gura_AssignWxValue(STC_MARK_ARROW);
	Gura_AssignWxValue(STC_MARK_SMALLRECT);
	Gura_AssignWxValue(STC_MARK_SHORTARROW);
	Gura_AssignWxValue(STC_MARK_EMPTY);
	Gura_AssignWxValue(STC_MARK_ARROWDOWN);
	Gura_AssignWxValue(STC_MARK_MINUS);
	Gura_AssignWxValue(STC_MARK_PLUS);
	Gura_AssignWxValue(STC_MARK_VLINE);
	Gura_AssignWxValue(STC_MARK_LCORNER);
	Gura_AssignWxValue(STC_MARK_TCORNER);
	Gura_AssignWxValue(STC_MARK_BOXPLUS);
	Gura_AssignWxValue(STC_MARK_BOXPLUSCONNECTED);
	Gura_AssignWxValue(STC_MARK_BOXMINUS);
	Gura_AssignWxValue(STC_MARK_BOXMINUSCONNECTED);
	Gura_AssignWxValue(STC_MARK_LCORNERCURVE);
	Gura_AssignWxValue(STC_MARK_TCORNERCURVE);
	Gura_AssignWxValue(STC_MARK_CIRCLEPLUS);
	Gura_AssignWxValue(STC_MARK_CIRCLEPLUSCONNECTED);
	Gura_AssignWxValue(STC_MARK_CIRCLEMINUS);
	Gura_AssignWxValue(STC_MARK_CIRCLEMINUSCONNECTED);
	Gura_AssignWxValue(STC_MARK_BACKGROUND);
	Gura_AssignWxValue(STC_MARK_DOTDOTDOT);
	Gura_AssignWxValue(STC_MARK_ARROWS);
	Gura_AssignWxValue(STC_MARK_PIXMAP);
	Gura_AssignWxValue(STC_MARK_FULLRECT);
	Gura_AssignWxValue(STC_MARK_LEFTRECT);
	Gura_AssignWxValue(STC_MARK_AVAILABLE);
	Gura_AssignWxValue(STC_MARK_UNDERLINE);
	Gura_AssignWxValue(STC_MARK_RGBAIMAGE);
	Gura_AssignWxValue(STC_MARK_CHARACTER);
	Gura_AssignWxValue(STC_MARKNUM_FOLDEREND);
	Gura_AssignWxValue(STC_MARKNUM_FOLDEROPENMID);
	Gura_AssignWxValue(STC_MARKNUM_FOLDERMIDTAIL);
	Gura_AssignWxValue(STC_MARKNUM_FOLDERTAIL);
	Gura_AssignWxValue(STC_MARKNUM_FOLDERSUB);
	Gura_AssignWxValue(STC_MARKNUM_FOLDER);
	Gura_AssignWxValue(STC_MARKNUM_FOLDEROPEN);
	Gura_AssignWxValue(STC_MASK_FOLDERS);
	Gura_AssignWxValue(STC_MARGIN_SYMBOL);
	Gura_AssignWxValue(STC_MARGIN_NUMBER);
	Gura_AssignWxValue(STC_MARGIN_BACK);
	Gura_AssignWxValue(STC_MARGIN_FORE);
	Gura_AssignWxValue(STC_MARGIN_TEXT);
	Gura_AssignWxValue(STC_MARGIN_RTEXT);
	Gura_AssignWxValue(STC_STYLE_DEFAULT);
	Gura_AssignWxValue(STC_STYLE_LINENUMBER);
	Gura_AssignWxValue(STC_STYLE_BRACELIGHT);
	Gura_AssignWxValue(STC_STYLE_BRACEBAD);
	Gura_AssignWxValue(STC_STYLE_CONTROLCHAR);
	Gura_AssignWxValue(STC_STYLE_INDENTGUIDE);
	Gura_AssignWxValue(STC_STYLE_CALLTIP);
	Gura_AssignWxValue(STC_STYLE_LASTPREDEFINED);
	Gura_AssignWxValue(STC_STYLE_MAX);
	Gura_AssignWxValue(STC_CHARSET_ANSI);
	Gura_AssignWxValue(STC_CHARSET_DEFAULT);
	Gura_AssignWxValue(STC_CHARSET_BALTIC);
	Gura_AssignWxValue(STC_CHARSET_CHINESEBIG5);
	Gura_AssignWxValue(STC_CHARSET_EASTEUROPE);
	Gura_AssignWxValue(STC_CHARSET_GB2312);
	Gura_AssignWxValue(STC_CHARSET_GREEK);
	Gura_AssignWxValue(STC_CHARSET_HANGUL);
	Gura_AssignWxValue(STC_CHARSET_MAC);
	Gura_AssignWxValue(STC_CHARSET_OEM);
	Gura_AssignWxValue(STC_CHARSET_RUSSIAN);
	Gura_AssignWxValue(STC_CHARSET_CYRILLIC);
	Gura_AssignWxValue(STC_CHARSET_SHIFTJIS);
	Gura_AssignWxValue(STC_CHARSET_SYMBOL);
	Gura_AssignWxValue(STC_CHARSET_TURKISH);
	Gura_AssignWxValue(STC_CHARSET_JOHAB);
	Gura_AssignWxValue(STC_CHARSET_HEBREW);
	Gura_AssignWxValue(STC_CHARSET_ARABIC);
	Gura_AssignWxValue(STC_CHARSET_VIETNAMESE);
	Gura_AssignWxValue(STC_CHARSET_THAI);
	Gura_AssignWxValue(STC_CHARSET_8859_15);
	Gura_AssignWxValue(STC_CASE_MIXED);
	Gura_AssignWxValue(STC_CASE_UPPER);
	Gura_AssignWxValue(STC_CASE_LOWER);
	Gura_AssignWxValue(STC_FONT_SIZE_MULTIPLIER);
	Gura_AssignWxValue(STC_WEIGHT_NORMAL);
	Gura_AssignWxValue(STC_WEIGHT_SEMIBOLD);
	Gura_AssignWxValue(STC_WEIGHT_BOLD);
	Gura_AssignWxValue(STC_INDIC_PLAIN);
	Gura_AssignWxValue(STC_INDIC_SQUIGGLE);
	Gura_AssignWxValue(STC_INDIC_TT);
	Gura_AssignWxValue(STC_INDIC_DIAGONAL);
	Gura_AssignWxValue(STC_INDIC_STRIKE);
	Gura_AssignWxValue(STC_INDIC_HIDDEN);
	Gura_AssignWxValue(STC_INDIC_BOX);
	Gura_AssignWxValue(STC_INDIC_ROUNDBOX);
	Gura_AssignWxValue(STC_INDIC_STRAIGHTBOX);
	Gura_AssignWxValue(STC_INDIC_DASH);
	Gura_AssignWxValue(STC_INDIC_DOTS);
	Gura_AssignWxValue(STC_INDIC_SQUIGGLELOW);
	Gura_AssignWxValue(STC_INDIC_DOTBOX);
	Gura_AssignWxValue(STC_INDIC_MAX);
	Gura_AssignWxValue(STC_INDIC_CONTAINER);
	Gura_AssignWxValue(STC_INDIC0_MASK);
	Gura_AssignWxValue(STC_INDIC1_MASK);
	Gura_AssignWxValue(STC_INDIC2_MASK);
	Gura_AssignWxValue(STC_INDICS_MASK);
	Gura_AssignWxValue(STC_IV_NONE);
	Gura_AssignWxValue(STC_IV_REAL);
	Gura_AssignWxValue(STC_IV_LOOKFORWARD);
	Gura_AssignWxValue(STC_IV_LOOKBOTH);
	Gura_AssignWxValue(STC_PRINT_NORMAL);
	Gura_AssignWxValue(STC_PRINT_INVERTLIGHT);
	Gura_AssignWxValue(STC_PRINT_BLACKONWHITE);
	Gura_AssignWxValue(STC_PRINT_COLOURONWHITE);
	Gura_AssignWxValue(STC_PRINT_COLOURONWHITEDEFAULTBG);
	Gura_AssignWxValue(STC_FIND_WHOLEWORD);
	Gura_AssignWxValue(STC_FIND_MATCHCASE);
	Gura_AssignWxValue(STC_FIND_WORDSTART);
	Gura_AssignWxValue(STC_FIND_REGEXP);
	Gura_AssignWxValue(STC_FIND_POSIX);
	Gura_AssignWxValue(STC_FOLDLEVELBASE);
	Gura_AssignWxValue(STC_FOLDLEVELWHITEFLAG);
	Gura_AssignWxValue(STC_FOLDLEVELHEADERFLAG);
	Gura_AssignWxValue(STC_FOLDLEVELNUMBERMASK);
	Gura_AssignWxValue(STC_FOLDFLAG_LINEBEFORE_EXPANDED);
	Gura_AssignWxValue(STC_FOLDFLAG_LINEBEFORE_CONTRACTED);
	Gura_AssignWxValue(STC_FOLDFLAG_LINEAFTER_EXPANDED);
	Gura_AssignWxValue(STC_FOLDFLAG_LINEAFTER_CONTRACTED);
	Gura_AssignWxValue(STC_FOLDFLAG_LEVELNUMBERS);
	Gura_AssignWxValue(STC_TIME_FOREVER);
	Gura_AssignWxValue(STC_WRAP_NONE);
	Gura_AssignWxValue(STC_WRAP_WORD);
	Gura_AssignWxValue(STC_WRAP_CHAR);
	Gura_AssignWxValue(STC_WRAPVISUALFLAG_NONE);
	Gura_AssignWxValue(STC_WRAPVISUALFLAG_END);
	Gura_AssignWxValue(STC_WRAPVISUALFLAG_START);
	Gura_AssignWxValue(STC_WRAPVISUALFLAG_MARGIN);
	Gura_AssignWxValue(STC_WRAPVISUALFLAGLOC_DEFAULT);
	Gura_AssignWxValue(STC_WRAPVISUALFLAGLOC_END_BY_TEXT);
	Gura_AssignWxValue(STC_WRAPVISUALFLAGLOC_START_BY_TEXT);
	Gura_AssignWxValue(STC_WRAPINDENT_FIXED);
	Gura_AssignWxValue(STC_WRAPINDENT_SAME);
	Gura_AssignWxValue(STC_WRAPINDENT_INDENT);
	Gura_AssignWxValue(STC_CACHE_NONE);
	Gura_AssignWxValue(STC_CACHE_CARET);
	Gura_AssignWxValue(STC_CACHE_PAGE);
	Gura_AssignWxValue(STC_CACHE_DOCUMENT);
	Gura_AssignWxValue(STC_EFF_QUALITY_MASK);
	Gura_AssignWxValue(STC_EFF_QUALITY_DEFAULT);
	Gura_AssignWxValue(STC_EFF_QUALITY_NON_ANTIALIASED);
	Gura_AssignWxValue(STC_EFF_QUALITY_ANTIALIASED);
	Gura_AssignWxValue(STC_EFF_QUALITY_LCD_OPTIMIZED);
	Gura_AssignWxValue(STC_MULTIPASTE_ONCE);
	Gura_AssignWxValue(STC_MULTIPASTE_EACH);
	Gura_AssignWxValue(STC_EDGE_NONE);
	Gura_AssignWxValue(STC_EDGE_LINE);
	Gura_AssignWxValue(STC_EDGE_BACKGROUND);
	Gura_AssignWxValue(STC_STATUS_OK);
	Gura_AssignWxValue(STC_STATUS_FAILURE);
	Gura_AssignWxValue(STC_STATUS_BADALLOC);
	Gura_AssignWxValue(STC_CURSORNORMAL);
	Gura_AssignWxValue(STC_CURSORARROW);
	Gura_AssignWxValue(STC_CURSORWAIT);
	Gura_AssignWxValue(STC_CURSORREVERSEARROW);
	Gura_AssignWxValue(STC_VISIBLE_SLOP);
	Gura_AssignWxValue(STC_VISIBLE_STRICT);
	Gura_AssignWxValue(STC_CARET_SLOP);
	Gura_AssignWxValue(STC_CARET_STRICT);
	Gura_AssignWxValue(STC_CARET_JUMPS);
	Gura_AssignWxValue(STC_CARET_EVEN);
	Gura_AssignWxValue(STC_SEL_STREAM);
	Gura_AssignWxValue(STC_SEL_RECTANGLE);
	Gura_AssignWxValue(STC_SEL_LINES);
	Gura_AssignWxValue(STC_SEL_THIN);
	Gura_AssignWxValue(STC_CASEINSENSITIVEBEHAVIOUR_RESPECTCASE);
	Gura_AssignWxValue(STC_CASEINSENSITIVEBEHAVIOUR_IGNORECASE);
	Gura_AssignWxValue(STC_CARETSTICKY_OFF);
	Gura_AssignWxValue(STC_CARETSTICKY_ON);
	Gura_AssignWxValue(STC_CARETSTICKY_WHITESPACE);
	Gura_AssignWxValue(STC_ALPHA_TRANSPARENT);
	Gura_AssignWxValue(STC_ALPHA_OPAQUE);
	Gura_AssignWxValue(STC_ALPHA_NOALPHA);
	Gura_AssignWxValue(STC_CARETSTYLE_INVISIBLE);
	Gura_AssignWxValue(STC_CARETSTYLE_LINE);
	Gura_AssignWxValue(STC_CARETSTYLE_BLOCK);
	Gura_AssignWxValue(STC_MARGINOPTION_NONE);
	Gura_AssignWxValue(STC_MARGINOPTION_SUBLINESELECT);
	Gura_AssignWxValue(STC_ANNOTATION_HIDDEN);
	Gura_AssignWxValue(STC_ANNOTATION_STANDARD);
	Gura_AssignWxValue(STC_ANNOTATION_BOXED);
	Gura_AssignWxValue(STC_UNDO_MAY_COALESCE);
	Gura_AssignWxValue(STC_SCVS_NONE);
	Gura_AssignWxValue(STC_SCVS_RECTANGULARSELECTION);
	Gura_AssignWxValue(STC_SCVS_USERACCESSIBLE);
	Gura_AssignWxValue(STC_TECHNOLOGY_DEFAULT);
	Gura_AssignWxValue(STC_TECHNOLOGY_DIRECTWRITE);
	Gura_AssignWxValue(STC_KEYWORDSET_MAX);
	Gura_AssignWxValue(STC_TYPE_BOOLEAN);
	Gura_AssignWxValue(STC_TYPE_INTEGER);
	Gura_AssignWxValue(STC_TYPE_STRING);
	Gura_AssignWxValue(STC_MOD_INSERTTEXT);
	Gura_AssignWxValue(STC_MOD_DELETETEXT);
	Gura_AssignWxValue(STC_MOD_CHANGESTYLE);
	Gura_AssignWxValue(STC_MOD_CHANGEFOLD);
	Gura_AssignWxValue(STC_PERFORMED_USER);
	Gura_AssignWxValue(STC_PERFORMED_UNDO);
	Gura_AssignWxValue(STC_PERFORMED_REDO);
	Gura_AssignWxValue(STC_MULTISTEPUNDOREDO);
	Gura_AssignWxValue(STC_LASTSTEPINUNDOREDO);
	Gura_AssignWxValue(STC_MOD_CHANGEMARKER);
	Gura_AssignWxValue(STC_MOD_BEFOREINSERT);
	Gura_AssignWxValue(STC_MOD_BEFOREDELETE);
	Gura_AssignWxValue(STC_MULTILINEUNDOREDO);
	Gura_AssignWxValue(STC_STARTACTION);
	Gura_AssignWxValue(STC_MOD_CHANGEINDICATOR);
	Gura_AssignWxValue(STC_MOD_CHANGELINESTATE);
	Gura_AssignWxValue(STC_MOD_CHANGEMARGIN);
	Gura_AssignWxValue(STC_MOD_CHANGEANNOTATION);
	Gura_AssignWxValue(STC_MOD_CONTAINER);
	Gura_AssignWxValue(STC_MOD_LEXERSTATE);
	Gura_AssignWxValue(STC_MODEVENTMASKALL);
	Gura_AssignWxValue(STC_UPDATE_CONTENT);
	Gura_AssignWxValue(STC_UPDATE_SELECTION);
	Gura_AssignWxValue(STC_UPDATE_V_SCROLL);
	Gura_AssignWxValue(STC_UPDATE_H_SCROLL);
	Gura_AssignWxValue(STC_KEY_DOWN);
	Gura_AssignWxValue(STC_KEY_UP);
	Gura_AssignWxValue(STC_KEY_LEFT);
	Gura_AssignWxValue(STC_KEY_RIGHT);
	Gura_AssignWxValue(STC_KEY_HOME);
	Gura_AssignWxValue(STC_KEY_END);
	Gura_AssignWxValue(STC_KEY_PRIOR);
	Gura_AssignWxValue(STC_KEY_NEXT);
	Gura_AssignWxValue(STC_KEY_DELETE);
	Gura_AssignWxValue(STC_KEY_INSERT);
	Gura_AssignWxValue(STC_KEY_ESCAPE);
	Gura_AssignWxValue(STC_KEY_BACK);
	Gura_AssignWxValue(STC_KEY_TAB);
	Gura_AssignWxValue(STC_KEY_RETURN);
	Gura_AssignWxValue(STC_KEY_ADD);
	Gura_AssignWxValue(STC_KEY_SUBTRACT);
	Gura_AssignWxValue(STC_KEY_DIVIDE);
	Gura_AssignWxValue(STC_KEY_WIN);
	Gura_AssignWxValue(STC_KEY_RWIN);
	Gura_AssignWxValue(STC_KEY_MENU);
	Gura_AssignWxValue(STC_SCMOD_NORM);
	Gura_AssignWxValue(STC_SCMOD_SHIFT);
	Gura_AssignWxValue(STC_SCMOD_CTRL);
	Gura_AssignWxValue(STC_SCMOD_ALT);
	Gura_AssignWxValue(STC_SCMOD_SUPER);
	Gura_AssignWxValue(STC_SCMOD_META);
	Gura_AssignWxValue(STC_LEX_CONTAINER);
	Gura_AssignWxValue(STC_LEX_NULL);
	Gura_AssignWxValue(STC_LEX_PYTHON);
	Gura_AssignWxValue(STC_LEX_CPP);
	Gura_AssignWxValue(STC_LEX_HTML);
	Gura_AssignWxValue(STC_LEX_XML);
	Gura_AssignWxValue(STC_LEX_PERL);
	Gura_AssignWxValue(STC_LEX_SQL);
	Gura_AssignWxValue(STC_LEX_VB);
	Gura_AssignWxValue(STC_LEX_PROPERTIES);
	Gura_AssignWxValue(STC_LEX_ERRORLIST);
	Gura_AssignWxValue(STC_LEX_MAKEFILE);
	Gura_AssignWxValue(STC_LEX_BATCH);
	Gura_AssignWxValue(STC_LEX_XCODE);
	Gura_AssignWxValue(STC_LEX_LATEX);
	Gura_AssignWxValue(STC_LEX_LUA);
	Gura_AssignWxValue(STC_LEX_DIFF);
	Gura_AssignWxValue(STC_LEX_CONF);
	Gura_AssignWxValue(STC_LEX_PASCAL);
	Gura_AssignWxValue(STC_LEX_AVE);
	Gura_AssignWxValue(STC_LEX_ADA);
	Gura_AssignWxValue(STC_LEX_LISP);
	Gura_AssignWxValue(STC_LEX_RUBY);
	Gura_AssignWxValue(STC_LEX_EIFFEL);
	Gura_AssignWxValue(STC_LEX_EIFFELKW);
	Gura_AssignWxValue(STC_LEX_TCL);
	Gura_AssignWxValue(STC_LEX_NNCRONTAB);
	Gura_AssignWxValue(STC_LEX_BULLANT);
	Gura_AssignWxValue(STC_LEX_VBSCRIPT);
	Gura_AssignWxValue(STC_LEX_BAAN);
	Gura_AssignWxValue(STC_LEX_MATLAB);
	Gura_AssignWxValue(STC_LEX_SCRIPTOL);
	Gura_AssignWxValue(STC_LEX_ASM);
	Gura_AssignWxValue(STC_LEX_CPPNOCASE);
	Gura_AssignWxValue(STC_LEX_FORTRAN);
	Gura_AssignWxValue(STC_LEX_F77);
	Gura_AssignWxValue(STC_LEX_CSS);
	Gura_AssignWxValue(STC_LEX_POV);
	Gura_AssignWxValue(STC_LEX_LOUT);
	Gura_AssignWxValue(STC_LEX_ESCRIPT);
	Gura_AssignWxValue(STC_LEX_PS);
	Gura_AssignWxValue(STC_LEX_NSIS);
	Gura_AssignWxValue(STC_LEX_MMIXAL);
	Gura_AssignWxValue(STC_LEX_CLW);
	Gura_AssignWxValue(STC_LEX_CLWNOCASE);
	Gura_AssignWxValue(STC_LEX_LOT);
	Gura_AssignWxValue(STC_LEX_YAML);
	Gura_AssignWxValue(STC_LEX_TEX);
	Gura_AssignWxValue(STC_LEX_METAPOST);
	Gura_AssignWxValue(STC_LEX_POWERBASIC);
	Gura_AssignWxValue(STC_LEX_FORTH);
	Gura_AssignWxValue(STC_LEX_ERLANG);
	Gura_AssignWxValue(STC_LEX_OCTAVE);
	Gura_AssignWxValue(STC_LEX_MSSQL);
	Gura_AssignWxValue(STC_LEX_VERILOG);
	Gura_AssignWxValue(STC_LEX_KIX);
	Gura_AssignWxValue(STC_LEX_GUI4CLI);
	Gura_AssignWxValue(STC_LEX_SPECMAN);
	Gura_AssignWxValue(STC_LEX_AU3);
	Gura_AssignWxValue(STC_LEX_APDL);
	Gura_AssignWxValue(STC_LEX_BASH);
	Gura_AssignWxValue(STC_LEX_ASN1);
	Gura_AssignWxValue(STC_LEX_VHDL);
	Gura_AssignWxValue(STC_LEX_CAML);
	Gura_AssignWxValue(STC_LEX_BLITZBASIC);
	Gura_AssignWxValue(STC_LEX_PUREBASIC);
	Gura_AssignWxValue(STC_LEX_HASKELL);
	Gura_AssignWxValue(STC_LEX_PHPSCRIPT);
	Gura_AssignWxValue(STC_LEX_TADS3);
	Gura_AssignWxValue(STC_LEX_REBOL);
	Gura_AssignWxValue(STC_LEX_SMALLTALK);
	Gura_AssignWxValue(STC_LEX_FLAGSHIP);
	Gura_AssignWxValue(STC_LEX_CSOUND);
	Gura_AssignWxValue(STC_LEX_FREEBASIC);
	Gura_AssignWxValue(STC_LEX_INNOSETUP);
	Gura_AssignWxValue(STC_LEX_OPAL);
	Gura_AssignWxValue(STC_LEX_SPICE);
	Gura_AssignWxValue(STC_LEX_D);
	Gura_AssignWxValue(STC_LEX_CMAKE);
	Gura_AssignWxValue(STC_LEX_GAP);
	Gura_AssignWxValue(STC_LEX_PLM);
	Gura_AssignWxValue(STC_LEX_PROGRESS);
	Gura_AssignWxValue(STC_LEX_ABAQUS);
	Gura_AssignWxValue(STC_LEX_ASYMPTOTE);
	Gura_AssignWxValue(STC_LEX_R);
	Gura_AssignWxValue(STC_LEX_MAGIK);
	Gura_AssignWxValue(STC_LEX_POWERSHELL);
	Gura_AssignWxValue(STC_LEX_MYSQL);
	Gura_AssignWxValue(STC_LEX_PO);
	Gura_AssignWxValue(STC_LEX_TAL);
	Gura_AssignWxValue(STC_LEX_COBOL);
	Gura_AssignWxValue(STC_LEX_TACL);
	Gura_AssignWxValue(STC_LEX_SORCUS);
	Gura_AssignWxValue(STC_LEX_POWERPRO);
	Gura_AssignWxValue(STC_LEX_NIMROD);
	Gura_AssignWxValue(STC_LEX_SML);
	Gura_AssignWxValue(STC_LEX_MARKDOWN);
	Gura_AssignWxValue(STC_LEX_TXT2TAGS);
	Gura_AssignWxValue(STC_LEX_A68K);
	Gura_AssignWxValue(STC_LEX_MODULA);
	Gura_AssignWxValue(STC_LEX_COFFEESCRIPT);
	Gura_AssignWxValue(STC_LEX_TCMD);
	Gura_AssignWxValue(STC_LEX_AVS);
	Gura_AssignWxValue(STC_LEX_ECL);
	Gura_AssignWxValue(STC_LEX_OSCRIPT);
	Gura_AssignWxValue(STC_LEX_VISUALPROLOG);
	Gura_AssignWxValue(STC_LEX_AUTOMATIC);
	Gura_AssignWxValue(STC_P_DEFAULT);
	Gura_AssignWxValue(STC_P_COMMENTLINE);
	Gura_AssignWxValue(STC_P_NUMBER);
	Gura_AssignWxValue(STC_P_STRING);
	Gura_AssignWxValue(STC_P_CHARACTER);
	Gura_AssignWxValue(STC_P_WORD);
	Gura_AssignWxValue(STC_P_TRIPLE);
	Gura_AssignWxValue(STC_P_TRIPLEDOUBLE);
	Gura_AssignWxValue(STC_P_CLASSNAME);
	Gura_AssignWxValue(STC_P_DEFNAME);
	Gura_AssignWxValue(STC_P_OPERATOR);
	Gura_AssignWxValue(STC_P_IDENTIFIER);
	Gura_AssignWxValue(STC_P_COMMENTBLOCK);
	Gura_AssignWxValue(STC_P_STRINGEOL);
	Gura_AssignWxValue(STC_P_WORD2);
	Gura_AssignWxValue(STC_P_DECORATOR);
	Gura_AssignWxValue(STC_C_DEFAULT);
	Gura_AssignWxValue(STC_C_COMMENT);
	Gura_AssignWxValue(STC_C_COMMENTLINE);
	Gura_AssignWxValue(STC_C_COMMENTDOC);
	Gura_AssignWxValue(STC_C_NUMBER);
	Gura_AssignWxValue(STC_C_WORD);
	Gura_AssignWxValue(STC_C_STRING);
	Gura_AssignWxValue(STC_C_CHARACTER);
	Gura_AssignWxValue(STC_C_UUID);
	Gura_AssignWxValue(STC_C_PREPROCESSOR);
	Gura_AssignWxValue(STC_C_OPERATOR);
	Gura_AssignWxValue(STC_C_IDENTIFIER);
	Gura_AssignWxValue(STC_C_STRINGEOL);
	Gura_AssignWxValue(STC_C_VERBATIM);
	Gura_AssignWxValue(STC_C_REGEX);
	Gura_AssignWxValue(STC_C_COMMENTLINEDOC);
	Gura_AssignWxValue(STC_C_WORD2);
	Gura_AssignWxValue(STC_C_COMMENTDOCKEYWORD);
	Gura_AssignWxValue(STC_C_COMMENTDOCKEYWORDERROR);
	Gura_AssignWxValue(STC_C_GLOBALCLASS);
	Gura_AssignWxValue(STC_C_STRINGRAW);
	Gura_AssignWxValue(STC_C_TRIPLEVERBATIM);
	Gura_AssignWxValue(STC_C_HASHQUOTEDSTRING);
	Gura_AssignWxValue(STC_C_PREPROCESSORCOMMENT);
	Gura_AssignWxValue(STC_D_DEFAULT);
	Gura_AssignWxValue(STC_D_COMMENT);
	Gura_AssignWxValue(STC_D_COMMENTLINE);
	Gura_AssignWxValue(STC_D_COMMENTDOC);
	Gura_AssignWxValue(STC_D_COMMENTNESTED);
	Gura_AssignWxValue(STC_D_NUMBER);
	Gura_AssignWxValue(STC_D_WORD);
	Gura_AssignWxValue(STC_D_WORD2);
	Gura_AssignWxValue(STC_D_WORD3);
	Gura_AssignWxValue(STC_D_TYPEDEF);
	Gura_AssignWxValue(STC_D_STRING);
	Gura_AssignWxValue(STC_D_STRINGEOL);
	Gura_AssignWxValue(STC_D_CHARACTER);
	Gura_AssignWxValue(STC_D_OPERATOR);
	Gura_AssignWxValue(STC_D_IDENTIFIER);
	Gura_AssignWxValue(STC_D_COMMENTLINEDOC);
	Gura_AssignWxValue(STC_D_COMMENTDOCKEYWORD);
	Gura_AssignWxValue(STC_D_COMMENTDOCKEYWORDERROR);
	Gura_AssignWxValue(STC_D_STRINGB);
	Gura_AssignWxValue(STC_D_STRINGR);
	Gura_AssignWxValue(STC_D_WORD5);
	Gura_AssignWxValue(STC_D_WORD6);
	Gura_AssignWxValue(STC_D_WORD7);
	Gura_AssignWxValue(STC_TCL_DEFAULT);
	Gura_AssignWxValue(STC_TCL_COMMENT);
	Gura_AssignWxValue(STC_TCL_COMMENTLINE);
	Gura_AssignWxValue(STC_TCL_NUMBER);
	Gura_AssignWxValue(STC_TCL_WORD_IN_QUOTE);
	Gura_AssignWxValue(STC_TCL_IN_QUOTE);
	Gura_AssignWxValue(STC_TCL_OPERATOR);
	Gura_AssignWxValue(STC_TCL_IDENTIFIER);
	Gura_AssignWxValue(STC_TCL_SUBSTITUTION);
	Gura_AssignWxValue(STC_TCL_SUB_BRACE);
	Gura_AssignWxValue(STC_TCL_MODIFIER);
	Gura_AssignWxValue(STC_TCL_EXPAND);
	Gura_AssignWxValue(STC_TCL_WORD);
	Gura_AssignWxValue(STC_TCL_WORD2);
	Gura_AssignWxValue(STC_TCL_WORD3);
	Gura_AssignWxValue(STC_TCL_WORD4);
	Gura_AssignWxValue(STC_TCL_WORD5);
	Gura_AssignWxValue(STC_TCL_WORD6);
	Gura_AssignWxValue(STC_TCL_WORD7);
	Gura_AssignWxValue(STC_TCL_WORD8);
	Gura_AssignWxValue(STC_TCL_COMMENT_BOX);
	Gura_AssignWxValue(STC_TCL_BLOCK_COMMENT);
	Gura_AssignWxValue(STC_H_DEFAULT);
	Gura_AssignWxValue(STC_H_TAG);
	Gura_AssignWxValue(STC_H_TAGUNKNOWN);
	Gura_AssignWxValue(STC_H_ATTRIBUTE);
	Gura_AssignWxValue(STC_H_ATTRIBUTEUNKNOWN);
	Gura_AssignWxValue(STC_H_NUMBER);
	Gura_AssignWxValue(STC_H_DOUBLESTRING);
	Gura_AssignWxValue(STC_H_SINGLESTRING);
	Gura_AssignWxValue(STC_H_OTHER);
	Gura_AssignWxValue(STC_H_COMMENT);
	Gura_AssignWxValue(STC_H_ENTITY);
	Gura_AssignWxValue(STC_H_TAGEND);
	Gura_AssignWxValue(STC_H_XMLSTART);
	Gura_AssignWxValue(STC_H_XMLEND);
	Gura_AssignWxValue(STC_H_SCRIPT);
	Gura_AssignWxValue(STC_H_ASP);
	Gura_AssignWxValue(STC_H_ASPAT);
	Gura_AssignWxValue(STC_H_CDATA);
	Gura_AssignWxValue(STC_H_QUESTION);
	Gura_AssignWxValue(STC_H_VALUE);
	Gura_AssignWxValue(STC_H_XCCOMMENT);
	Gura_AssignWxValue(STC_H_SGML_DEFAULT);
	Gura_AssignWxValue(STC_H_SGML_COMMAND);
	Gura_AssignWxValue(STC_H_SGML_1ST_PARAM);
	Gura_AssignWxValue(STC_H_SGML_DOUBLESTRING);
	Gura_AssignWxValue(STC_H_SGML_SIMPLESTRING);
	Gura_AssignWxValue(STC_H_SGML_ERROR);
	Gura_AssignWxValue(STC_H_SGML_SPECIAL);
	Gura_AssignWxValue(STC_H_SGML_ENTITY);
	Gura_AssignWxValue(STC_H_SGML_COMMENT);
	Gura_AssignWxValue(STC_H_SGML_1ST_PARAM_COMMENT);
	Gura_AssignWxValue(STC_H_SGML_BLOCK_DEFAULT);
	Gura_AssignWxValue(STC_HJ_START);
	Gura_AssignWxValue(STC_HJ_DEFAULT);
	Gura_AssignWxValue(STC_HJ_COMMENT);
	Gura_AssignWxValue(STC_HJ_COMMENTLINE);
	Gura_AssignWxValue(STC_HJ_COMMENTDOC);
	Gura_AssignWxValue(STC_HJ_NUMBER);
	Gura_AssignWxValue(STC_HJ_WORD);
	Gura_AssignWxValue(STC_HJ_KEYWORD);
	Gura_AssignWxValue(STC_HJ_DOUBLESTRING);
	Gura_AssignWxValue(STC_HJ_SINGLESTRING);
	Gura_AssignWxValue(STC_HJ_SYMBOLS);
	Gura_AssignWxValue(STC_HJ_STRINGEOL);
	Gura_AssignWxValue(STC_HJ_REGEX);
	Gura_AssignWxValue(STC_HJA_START);
	Gura_AssignWxValue(STC_HJA_DEFAULT);
	Gura_AssignWxValue(STC_HJA_COMMENT);
	Gura_AssignWxValue(STC_HJA_COMMENTLINE);
	Gura_AssignWxValue(STC_HJA_COMMENTDOC);
	Gura_AssignWxValue(STC_HJA_NUMBER);
	Gura_AssignWxValue(STC_HJA_WORD);
	Gura_AssignWxValue(STC_HJA_KEYWORD);
	Gura_AssignWxValue(STC_HJA_DOUBLESTRING);
	Gura_AssignWxValue(STC_HJA_SINGLESTRING);
	Gura_AssignWxValue(STC_HJA_SYMBOLS);
	Gura_AssignWxValue(STC_HJA_STRINGEOL);
	Gura_AssignWxValue(STC_HJA_REGEX);
	Gura_AssignWxValue(STC_HB_START);
	Gura_AssignWxValue(STC_HB_DEFAULT);
	Gura_AssignWxValue(STC_HB_COMMENTLINE);
	Gura_AssignWxValue(STC_HB_NUMBER);
	Gura_AssignWxValue(STC_HB_WORD);
	Gura_AssignWxValue(STC_HB_STRING);
	Gura_AssignWxValue(STC_HB_IDENTIFIER);
	Gura_AssignWxValue(STC_HB_STRINGEOL);
	Gura_AssignWxValue(STC_HBA_START);
	Gura_AssignWxValue(STC_HBA_DEFAULT);
	Gura_AssignWxValue(STC_HBA_COMMENTLINE);
	Gura_AssignWxValue(STC_HBA_NUMBER);
	Gura_AssignWxValue(STC_HBA_WORD);
	Gura_AssignWxValue(STC_HBA_STRING);
	Gura_AssignWxValue(STC_HBA_IDENTIFIER);
	Gura_AssignWxValue(STC_HBA_STRINGEOL);
	Gura_AssignWxValue(STC_HP_START);
	Gura_AssignWxValue(STC_HP_DEFAULT);
	Gura_AssignWxValue(STC_HP_COMMENTLINE);
	Gura_AssignWxValue(STC_HP_NUMBER);
	Gura_AssignWxValue(STC_HP_STRING);
	Gura_AssignWxValue(STC_HP_CHARACTER);
	Gura_AssignWxValue(STC_HP_WORD);
	Gura_AssignWxValue(STC_HP_TRIPLE);
	Gura_AssignWxValue(STC_HP_TRIPLEDOUBLE);
	Gura_AssignWxValue(STC_HP_CLASSNAME);
	Gura_AssignWxValue(STC_HP_DEFNAME);
	Gura_AssignWxValue(STC_HP_OPERATOR);
	Gura_AssignWxValue(STC_HP_IDENTIFIER);
	Gura_AssignWxValue(STC_HPHP_COMPLEX_VARIABLE);
	Gura_AssignWxValue(STC_HPA_START);
	Gura_AssignWxValue(STC_HPA_DEFAULT);
	Gura_AssignWxValue(STC_HPA_COMMENTLINE);
	Gura_AssignWxValue(STC_HPA_NUMBER);
	Gura_AssignWxValue(STC_HPA_STRING);
	Gura_AssignWxValue(STC_HPA_CHARACTER);
	Gura_AssignWxValue(STC_HPA_WORD);
	Gura_AssignWxValue(STC_HPA_TRIPLE);
	Gura_AssignWxValue(STC_HPA_TRIPLEDOUBLE);
	Gura_AssignWxValue(STC_HPA_CLASSNAME);
	Gura_AssignWxValue(STC_HPA_DEFNAME);
	Gura_AssignWxValue(STC_HPA_OPERATOR);
	Gura_AssignWxValue(STC_HPA_IDENTIFIER);
	Gura_AssignWxValue(STC_HPHP_DEFAULT);
	Gura_AssignWxValue(STC_HPHP_HSTRING);
	Gura_AssignWxValue(STC_HPHP_SIMPLESTRING);
	Gura_AssignWxValue(STC_HPHP_WORD);
	Gura_AssignWxValue(STC_HPHP_NUMBER);
	Gura_AssignWxValue(STC_HPHP_VARIABLE);
	Gura_AssignWxValue(STC_HPHP_COMMENT);
	Gura_AssignWxValue(STC_HPHP_COMMENTLINE);
	Gura_AssignWxValue(STC_HPHP_HSTRING_VARIABLE);
	Gura_AssignWxValue(STC_HPHP_OPERATOR);
	Gura_AssignWxValue(STC_PL_DEFAULT);
	Gura_AssignWxValue(STC_PL_ERROR);
	Gura_AssignWxValue(STC_PL_COMMENTLINE);
	Gura_AssignWxValue(STC_PL_POD);
	Gura_AssignWxValue(STC_PL_NUMBER);
	Gura_AssignWxValue(STC_PL_WORD);
	Gura_AssignWxValue(STC_PL_STRING);
	Gura_AssignWxValue(STC_PL_CHARACTER);
	Gura_AssignWxValue(STC_PL_PUNCTUATION);
	Gura_AssignWxValue(STC_PL_PREPROCESSOR);
	Gura_AssignWxValue(STC_PL_OPERATOR);
	Gura_AssignWxValue(STC_PL_IDENTIFIER);
	Gura_AssignWxValue(STC_PL_SCALAR);
	Gura_AssignWxValue(STC_PL_ARRAY);
	Gura_AssignWxValue(STC_PL_HASH);
	Gura_AssignWxValue(STC_PL_SYMBOLTABLE);
	Gura_AssignWxValue(STC_PL_VARIABLE_INDEXER);
	Gura_AssignWxValue(STC_PL_REGEX);
	Gura_AssignWxValue(STC_PL_REGSUBST);
	Gura_AssignWxValue(STC_PL_LONGQUOTE);
	Gura_AssignWxValue(STC_PL_BACKTICKS);
	Gura_AssignWxValue(STC_PL_DATASECTION);
	Gura_AssignWxValue(STC_PL_HERE_DELIM);
	Gura_AssignWxValue(STC_PL_HERE_Q);
	Gura_AssignWxValue(STC_PL_HERE_QQ);
	Gura_AssignWxValue(STC_PL_HERE_QX);
	Gura_AssignWxValue(STC_PL_STRING_Q);
	Gura_AssignWxValue(STC_PL_STRING_QQ);
	Gura_AssignWxValue(STC_PL_STRING_QX);
	Gura_AssignWxValue(STC_PL_STRING_QR);
	Gura_AssignWxValue(STC_PL_STRING_QW);
	Gura_AssignWxValue(STC_PL_POD_VERB);
	Gura_AssignWxValue(STC_PL_SUB_PROTOTYPE);
	Gura_AssignWxValue(STC_PL_FORMAT_IDENT);
	Gura_AssignWxValue(STC_PL_FORMAT);
	Gura_AssignWxValue(STC_PL_STRING_VAR);
	Gura_AssignWxValue(STC_PL_XLAT);
	Gura_AssignWxValue(STC_PL_REGEX_VAR);
	Gura_AssignWxValue(STC_PL_REGSUBST_VAR);
	Gura_AssignWxValue(STC_PL_BACKTICKS_VAR);
	Gura_AssignWxValue(STC_PL_HERE_QQ_VAR);
	Gura_AssignWxValue(STC_PL_HERE_QX_VAR);
	Gura_AssignWxValue(STC_PL_STRING_QQ_VAR);
	Gura_AssignWxValue(STC_PL_STRING_QX_VAR);
	Gura_AssignWxValue(STC_PL_STRING_QR_VAR);
	Gura_AssignWxValue(STC_RB_DEFAULT);
	Gura_AssignWxValue(STC_RB_ERROR);
	Gura_AssignWxValue(STC_RB_COMMENTLINE);
	Gura_AssignWxValue(STC_RB_POD);
	Gura_AssignWxValue(STC_RB_NUMBER);
	Gura_AssignWxValue(STC_RB_WORD);
	Gura_AssignWxValue(STC_RB_STRING);
	Gura_AssignWxValue(STC_RB_CHARACTER);
	Gura_AssignWxValue(STC_RB_CLASSNAME);
	Gura_AssignWxValue(STC_RB_DEFNAME);
	Gura_AssignWxValue(STC_RB_OPERATOR);
	Gura_AssignWxValue(STC_RB_IDENTIFIER);
	Gura_AssignWxValue(STC_RB_REGEX);
	Gura_AssignWxValue(STC_RB_GLOBAL);
	Gura_AssignWxValue(STC_RB_SYMBOL);
	Gura_AssignWxValue(STC_RB_MODULE_NAME);
	Gura_AssignWxValue(STC_RB_INSTANCE_VAR);
	Gura_AssignWxValue(STC_RB_CLASS_VAR);
	Gura_AssignWxValue(STC_RB_BACKTICKS);
	Gura_AssignWxValue(STC_RB_DATASECTION);
	Gura_AssignWxValue(STC_RB_HERE_DELIM);
	Gura_AssignWxValue(STC_RB_HERE_Q);
	Gura_AssignWxValue(STC_RB_HERE_QQ);
	Gura_AssignWxValue(STC_RB_HERE_QX);
	Gura_AssignWxValue(STC_RB_STRING_Q);
	Gura_AssignWxValue(STC_RB_STRING_QQ);
	Gura_AssignWxValue(STC_RB_STRING_QX);
	Gura_AssignWxValue(STC_RB_STRING_QR);
	Gura_AssignWxValue(STC_RB_STRING_QW);
	Gura_AssignWxValue(STC_RB_WORD_DEMOTED);
	Gura_AssignWxValue(STC_RB_STDIN);
	Gura_AssignWxValue(STC_RB_STDOUT);
	Gura_AssignWxValue(STC_RB_STDERR);
	Gura_AssignWxValue(STC_RB_UPPER_BOUND);
	Gura_AssignWxValue(STC_B_DEFAULT);
	Gura_AssignWxValue(STC_B_COMMENT);
	Gura_AssignWxValue(STC_B_NUMBER);
	Gura_AssignWxValue(STC_B_KEYWORD);
	Gura_AssignWxValue(STC_B_STRING);
	Gura_AssignWxValue(STC_B_PREPROCESSOR);
	Gura_AssignWxValue(STC_B_OPERATOR);
	Gura_AssignWxValue(STC_B_IDENTIFIER);
	Gura_AssignWxValue(STC_B_DATE);
	Gura_AssignWxValue(STC_B_STRINGEOL);
	Gura_AssignWxValue(STC_B_KEYWORD2);
	Gura_AssignWxValue(STC_B_KEYWORD3);
	Gura_AssignWxValue(STC_B_KEYWORD4);
	Gura_AssignWxValue(STC_B_CONSTANT);
	Gura_AssignWxValue(STC_B_ASM);
	Gura_AssignWxValue(STC_B_LABEL);
	Gura_AssignWxValue(STC_B_ERROR);
	Gura_AssignWxValue(STC_B_HEXNUMBER);
	Gura_AssignWxValue(STC_B_BINNUMBER);
	Gura_AssignWxValue(STC_PROPS_DEFAULT);
	Gura_AssignWxValue(STC_PROPS_COMMENT);
	Gura_AssignWxValue(STC_PROPS_SECTION);
	Gura_AssignWxValue(STC_PROPS_ASSIGNMENT);
	Gura_AssignWxValue(STC_PROPS_DEFVAL);
	Gura_AssignWxValue(STC_PROPS_KEY);
	Gura_AssignWxValue(STC_L_DEFAULT);
	Gura_AssignWxValue(STC_L_COMMAND);
	Gura_AssignWxValue(STC_L_TAG);
	Gura_AssignWxValue(STC_L_MATH);
	Gura_AssignWxValue(STC_L_COMMENT);
	Gura_AssignWxValue(STC_L_TAG2);
	Gura_AssignWxValue(STC_L_MATH2);
	Gura_AssignWxValue(STC_L_COMMENT2);
	Gura_AssignWxValue(STC_L_VERBATIM);
	Gura_AssignWxValue(STC_L_SHORTCMD);
	Gura_AssignWxValue(STC_L_SPECIAL);
	Gura_AssignWxValue(STC_L_CMDOPT);
	Gura_AssignWxValue(STC_L_ERROR);
	Gura_AssignWxValue(STC_LUA_DEFAULT);
	Gura_AssignWxValue(STC_LUA_COMMENT);
	Gura_AssignWxValue(STC_LUA_COMMENTLINE);
	Gura_AssignWxValue(STC_LUA_COMMENTDOC);
	Gura_AssignWxValue(STC_LUA_NUMBER);
	Gura_AssignWxValue(STC_LUA_WORD);
	Gura_AssignWxValue(STC_LUA_STRING);
	Gura_AssignWxValue(STC_LUA_CHARACTER);
	Gura_AssignWxValue(STC_LUA_LITERALSTRING);
	Gura_AssignWxValue(STC_LUA_PREPROCESSOR);
	Gura_AssignWxValue(STC_LUA_OPERATOR);
	Gura_AssignWxValue(STC_LUA_IDENTIFIER);
	Gura_AssignWxValue(STC_LUA_STRINGEOL);
	Gura_AssignWxValue(STC_LUA_WORD2);
	Gura_AssignWxValue(STC_LUA_WORD3);
	Gura_AssignWxValue(STC_LUA_WORD4);
	Gura_AssignWxValue(STC_LUA_WORD5);
	Gura_AssignWxValue(STC_LUA_WORD6);
	Gura_AssignWxValue(STC_LUA_WORD7);
	Gura_AssignWxValue(STC_LUA_WORD8);
	Gura_AssignWxValue(STC_LUA_LABEL);
	Gura_AssignWxValue(STC_ERR_DEFAULT);
	Gura_AssignWxValue(STC_ERR_PYTHON);
	Gura_AssignWxValue(STC_ERR_GCC);
	Gura_AssignWxValue(STC_ERR_MS);
	Gura_AssignWxValue(STC_ERR_CMD);
	Gura_AssignWxValue(STC_ERR_BORLAND);
	Gura_AssignWxValue(STC_ERR_PERL);
	Gura_AssignWxValue(STC_ERR_NET);
	Gura_AssignWxValue(STC_ERR_LUA);
	Gura_AssignWxValue(STC_ERR_CTAG);
	Gura_AssignWxValue(STC_ERR_DIFF_CHANGED);
	Gura_AssignWxValue(STC_ERR_DIFF_ADDITION);
	Gura_AssignWxValue(STC_ERR_DIFF_DELETION);
	Gura_AssignWxValue(STC_ERR_DIFF_MESSAGE);
	Gura_AssignWxValue(STC_ERR_PHP);
	Gura_AssignWxValue(STC_ERR_ELF);
	Gura_AssignWxValue(STC_ERR_IFC);
	Gura_AssignWxValue(STC_ERR_IFORT);
	Gura_AssignWxValue(STC_ERR_ABSF);
	Gura_AssignWxValue(STC_ERR_TIDY);
	Gura_AssignWxValue(STC_ERR_JAVA_STACK);
	Gura_AssignWxValue(STC_ERR_VALUE);
	Gura_AssignWxValue(STC_BAT_DEFAULT);
	Gura_AssignWxValue(STC_BAT_COMMENT);
	Gura_AssignWxValue(STC_BAT_WORD);
	Gura_AssignWxValue(STC_BAT_LABEL);
	Gura_AssignWxValue(STC_BAT_HIDE);
	Gura_AssignWxValue(STC_BAT_COMMAND);
	Gura_AssignWxValue(STC_BAT_IDENTIFIER);
	Gura_AssignWxValue(STC_BAT_OPERATOR);
	Gura_AssignWxValue(STC_TCMD_DEFAULT);
	Gura_AssignWxValue(STC_TCMD_COMMENT);
	Gura_AssignWxValue(STC_TCMD_WORD);
	Gura_AssignWxValue(STC_TCMD_LABEL);
	Gura_AssignWxValue(STC_TCMD_HIDE);
	Gura_AssignWxValue(STC_TCMD_COMMAND);
	Gura_AssignWxValue(STC_TCMD_IDENTIFIER);
	Gura_AssignWxValue(STC_TCMD_OPERATOR);
	Gura_AssignWxValue(STC_TCMD_ENVIRONMENT);
	Gura_AssignWxValue(STC_TCMD_EXPANSION);
	Gura_AssignWxValue(STC_TCMD_CLABEL);
	Gura_AssignWxValue(STC_MAKE_DEFAULT);
	Gura_AssignWxValue(STC_MAKE_COMMENT);
	Gura_AssignWxValue(STC_MAKE_PREPROCESSOR);
	Gura_AssignWxValue(STC_MAKE_IDENTIFIER);
	Gura_AssignWxValue(STC_MAKE_OPERATOR);
	Gura_AssignWxValue(STC_MAKE_TARGET);
	Gura_AssignWxValue(STC_MAKE_IDEOL);
	Gura_AssignWxValue(STC_DIFF_DEFAULT);
	Gura_AssignWxValue(STC_DIFF_COMMENT);
	Gura_AssignWxValue(STC_DIFF_COMMAND);
	Gura_AssignWxValue(STC_DIFF_HEADER);
	Gura_AssignWxValue(STC_DIFF_POSITION);
	Gura_AssignWxValue(STC_DIFF_DELETED);
	Gura_AssignWxValue(STC_DIFF_ADDED);
	Gura_AssignWxValue(STC_DIFF_CHANGED);
	Gura_AssignWxValue(STC_CONF_DEFAULT);
	Gura_AssignWxValue(STC_CONF_COMMENT);
	Gura_AssignWxValue(STC_CONF_NUMBER);
	Gura_AssignWxValue(STC_CONF_IDENTIFIER);
	Gura_AssignWxValue(STC_CONF_EXTENSION);
	Gura_AssignWxValue(STC_CONF_PARAMETER);
	Gura_AssignWxValue(STC_CONF_STRING);
	Gura_AssignWxValue(STC_CONF_OPERATOR);
	Gura_AssignWxValue(STC_CONF_IP);
	Gura_AssignWxValue(STC_CONF_DIRECTIVE);
	Gura_AssignWxValue(STC_AVE_DEFAULT);
	Gura_AssignWxValue(STC_AVE_COMMENT);
	Gura_AssignWxValue(STC_AVE_NUMBER);
	Gura_AssignWxValue(STC_AVE_WORD);
	Gura_AssignWxValue(STC_AVE_STRING);
	Gura_AssignWxValue(STC_AVE_ENUM);
	Gura_AssignWxValue(STC_AVE_STRINGEOL);
	Gura_AssignWxValue(STC_AVE_IDENTIFIER);
	Gura_AssignWxValue(STC_AVE_OPERATOR);
	Gura_AssignWxValue(STC_AVE_WORD1);
	Gura_AssignWxValue(STC_AVE_WORD2);
	Gura_AssignWxValue(STC_AVE_WORD3);
	Gura_AssignWxValue(STC_AVE_WORD4);
	Gura_AssignWxValue(STC_AVE_WORD5);
	Gura_AssignWxValue(STC_AVE_WORD6);
	Gura_AssignWxValue(STC_ADA_DEFAULT);
	Gura_AssignWxValue(STC_ADA_WORD);
	Gura_AssignWxValue(STC_ADA_IDENTIFIER);
	Gura_AssignWxValue(STC_ADA_NUMBER);
	Gura_AssignWxValue(STC_ADA_DELIMITER);
	Gura_AssignWxValue(STC_ADA_CHARACTER);
	Gura_AssignWxValue(STC_ADA_CHARACTEREOL);
	Gura_AssignWxValue(STC_ADA_STRING);
	Gura_AssignWxValue(STC_ADA_STRINGEOL);
	Gura_AssignWxValue(STC_ADA_LABEL);
	Gura_AssignWxValue(STC_ADA_COMMENTLINE);
	Gura_AssignWxValue(STC_ADA_ILLEGAL);
	Gura_AssignWxValue(STC_BAAN_DEFAULT);
	Gura_AssignWxValue(STC_BAAN_COMMENT);
	Gura_AssignWxValue(STC_BAAN_COMMENTDOC);
	Gura_AssignWxValue(STC_BAAN_NUMBER);
	Gura_AssignWxValue(STC_BAAN_WORD);
	Gura_AssignWxValue(STC_BAAN_STRING);
	Gura_AssignWxValue(STC_BAAN_PREPROCESSOR);
	Gura_AssignWxValue(STC_BAAN_OPERATOR);
	Gura_AssignWxValue(STC_BAAN_IDENTIFIER);
	Gura_AssignWxValue(STC_BAAN_STRINGEOL);
	Gura_AssignWxValue(STC_BAAN_WORD2);
	Gura_AssignWxValue(STC_LISP_DEFAULT);
	Gura_AssignWxValue(STC_LISP_COMMENT);
	Gura_AssignWxValue(STC_LISP_NUMBER);
	Gura_AssignWxValue(STC_LISP_KEYWORD);
	Gura_AssignWxValue(STC_LISP_KEYWORD_KW);
	Gura_AssignWxValue(STC_LISP_SYMBOL);
	Gura_AssignWxValue(STC_LISP_STRING);
	Gura_AssignWxValue(STC_LISP_STRINGEOL);
	Gura_AssignWxValue(STC_LISP_IDENTIFIER);
	Gura_AssignWxValue(STC_LISP_OPERATOR);
	Gura_AssignWxValue(STC_LISP_SPECIAL);
	Gura_AssignWxValue(STC_LISP_MULTI_COMMENT);
	Gura_AssignWxValue(STC_EIFFEL_DEFAULT);
	Gura_AssignWxValue(STC_EIFFEL_COMMENTLINE);
	Gura_AssignWxValue(STC_EIFFEL_NUMBER);
	Gura_AssignWxValue(STC_EIFFEL_WORD);
	Gura_AssignWxValue(STC_EIFFEL_STRING);
	Gura_AssignWxValue(STC_EIFFEL_CHARACTER);
	Gura_AssignWxValue(STC_EIFFEL_OPERATOR);
	Gura_AssignWxValue(STC_EIFFEL_IDENTIFIER);
	Gura_AssignWxValue(STC_EIFFEL_STRINGEOL);
	Gura_AssignWxValue(STC_NNCRONTAB_DEFAULT);
	Gura_AssignWxValue(STC_NNCRONTAB_COMMENT);
	Gura_AssignWxValue(STC_NNCRONTAB_TASK);
	Gura_AssignWxValue(STC_NNCRONTAB_SECTION);
	Gura_AssignWxValue(STC_NNCRONTAB_KEYWORD);
	Gura_AssignWxValue(STC_NNCRONTAB_MODIFIER);
	Gura_AssignWxValue(STC_NNCRONTAB_ASTERISK);
	Gura_AssignWxValue(STC_NNCRONTAB_NUMBER);
	Gura_AssignWxValue(STC_NNCRONTAB_STRING);
	Gura_AssignWxValue(STC_NNCRONTAB_ENVIRONMENT);
	Gura_AssignWxValue(STC_NNCRONTAB_IDENTIFIER);
	Gura_AssignWxValue(STC_FORTH_DEFAULT);
	Gura_AssignWxValue(STC_FORTH_COMMENT);
	Gura_AssignWxValue(STC_FORTH_COMMENT_ML);
	Gura_AssignWxValue(STC_FORTH_IDENTIFIER);
	Gura_AssignWxValue(STC_FORTH_CONTROL);
	Gura_AssignWxValue(STC_FORTH_KEYWORD);
	Gura_AssignWxValue(STC_FORTH_DEFWORD);
	Gura_AssignWxValue(STC_FORTH_PREWORD1);
	Gura_AssignWxValue(STC_FORTH_PREWORD2);
	Gura_AssignWxValue(STC_FORTH_NUMBER);
	Gura_AssignWxValue(STC_FORTH_STRING);
	Gura_AssignWxValue(STC_FORTH_LOCALE);
	Gura_AssignWxValue(STC_MATLAB_DEFAULT);
	Gura_AssignWxValue(STC_MATLAB_COMMENT);
	Gura_AssignWxValue(STC_MATLAB_COMMAND);
	Gura_AssignWxValue(STC_MATLAB_NUMBER);
	Gura_AssignWxValue(STC_MATLAB_KEYWORD);
	Gura_AssignWxValue(STC_MATLAB_STRING);
	Gura_AssignWxValue(STC_MATLAB_OPERATOR);
	Gura_AssignWxValue(STC_MATLAB_IDENTIFIER);
	Gura_AssignWxValue(STC_MATLAB_DOUBLEQUOTESTRING);
	Gura_AssignWxValue(STC_SCRIPTOL_DEFAULT);
	Gura_AssignWxValue(STC_SCRIPTOL_WHITE);
	Gura_AssignWxValue(STC_SCRIPTOL_COMMENTLINE);
	Gura_AssignWxValue(STC_SCRIPTOL_PERSISTENT);
	Gura_AssignWxValue(STC_SCRIPTOL_CSTYLE);
	Gura_AssignWxValue(STC_SCRIPTOL_COMMENTBLOCK);
	Gura_AssignWxValue(STC_SCRIPTOL_NUMBER);
	Gura_AssignWxValue(STC_SCRIPTOL_STRING);
	Gura_AssignWxValue(STC_SCRIPTOL_CHARACTER);
	Gura_AssignWxValue(STC_SCRIPTOL_STRINGEOL);
	Gura_AssignWxValue(STC_SCRIPTOL_KEYWORD);
	Gura_AssignWxValue(STC_SCRIPTOL_OPERATOR);
	Gura_AssignWxValue(STC_SCRIPTOL_IDENTIFIER);
	Gura_AssignWxValue(STC_SCRIPTOL_TRIPLE);
	Gura_AssignWxValue(STC_SCRIPTOL_CLASSNAME);
	Gura_AssignWxValue(STC_SCRIPTOL_PREPROCESSOR);
	Gura_AssignWxValue(STC_ASM_DEFAULT);
	Gura_AssignWxValue(STC_ASM_COMMENT);
	Gura_AssignWxValue(STC_ASM_NUMBER);
	Gura_AssignWxValue(STC_ASM_STRING);
	Gura_AssignWxValue(STC_ASM_OPERATOR);
	Gura_AssignWxValue(STC_ASM_IDENTIFIER);
	Gura_AssignWxValue(STC_ASM_CPUINSTRUCTION);
	Gura_AssignWxValue(STC_ASM_MATHINSTRUCTION);
	Gura_AssignWxValue(STC_ASM_REGISTER);
	Gura_AssignWxValue(STC_ASM_DIRECTIVE);
	Gura_AssignWxValue(STC_ASM_DIRECTIVEOPERAND);
	Gura_AssignWxValue(STC_ASM_COMMENTBLOCK);
	Gura_AssignWxValue(STC_ASM_CHARACTER);
	Gura_AssignWxValue(STC_ASM_STRINGEOL);
	Gura_AssignWxValue(STC_ASM_EXTINSTRUCTION);
	Gura_AssignWxValue(STC_ASM_COMMENTDIRECTIVE);
	Gura_AssignWxValue(STC_F_DEFAULT);
	Gura_AssignWxValue(STC_F_COMMENT);
	Gura_AssignWxValue(STC_F_NUMBER);
	Gura_AssignWxValue(STC_F_STRING1);
	Gura_AssignWxValue(STC_F_STRING2);
	Gura_AssignWxValue(STC_F_STRINGEOL);
	Gura_AssignWxValue(STC_F_OPERATOR);
	Gura_AssignWxValue(STC_F_IDENTIFIER);
	Gura_AssignWxValue(STC_F_WORD);
	Gura_AssignWxValue(STC_F_WORD2);
	Gura_AssignWxValue(STC_F_WORD3);
	Gura_AssignWxValue(STC_F_PREPROCESSOR);
	Gura_AssignWxValue(STC_F_OPERATOR2);
	Gura_AssignWxValue(STC_F_LABEL);
	Gura_AssignWxValue(STC_F_CONTINUATION);
	Gura_AssignWxValue(STC_CSS_DEFAULT);
	Gura_AssignWxValue(STC_CSS_TAG);
	Gura_AssignWxValue(STC_CSS_CLASS);
	Gura_AssignWxValue(STC_CSS_PSEUDOCLASS);
	Gura_AssignWxValue(STC_CSS_UNKNOWN_PSEUDOCLASS);
	Gura_AssignWxValue(STC_CSS_OPERATOR);
	Gura_AssignWxValue(STC_CSS_IDENTIFIER);
	Gura_AssignWxValue(STC_CSS_UNKNOWN_IDENTIFIER);
	Gura_AssignWxValue(STC_CSS_VALUE);
	Gura_AssignWxValue(STC_CSS_COMMENT);
	Gura_AssignWxValue(STC_CSS_ID);
	Gura_AssignWxValue(STC_CSS_IMPORTANT);
	Gura_AssignWxValue(STC_CSS_DIRECTIVE);
	Gura_AssignWxValue(STC_CSS_DOUBLESTRING);
	Gura_AssignWxValue(STC_CSS_SINGLESTRING);
	Gura_AssignWxValue(STC_CSS_IDENTIFIER2);
	Gura_AssignWxValue(STC_CSS_ATTRIBUTE);
	Gura_AssignWxValue(STC_CSS_IDENTIFIER3);
	Gura_AssignWxValue(STC_CSS_PSEUDOELEMENT);
	Gura_AssignWxValue(STC_CSS_EXTENDED_IDENTIFIER);
	Gura_AssignWxValue(STC_CSS_EXTENDED_PSEUDOCLASS);
	Gura_AssignWxValue(STC_CSS_EXTENDED_PSEUDOELEMENT);
	Gura_AssignWxValue(STC_CSS_MEDIA);
	Gura_AssignWxValue(STC_CSS_VARIABLE);
	Gura_AssignWxValue(STC_POV_DEFAULT);
	Gura_AssignWxValue(STC_POV_COMMENT);
	Gura_AssignWxValue(STC_POV_COMMENTLINE);
	Gura_AssignWxValue(STC_POV_NUMBER);
	Gura_AssignWxValue(STC_POV_OPERATOR);
	Gura_AssignWxValue(STC_POV_IDENTIFIER);
	Gura_AssignWxValue(STC_POV_STRING);
	Gura_AssignWxValue(STC_POV_STRINGEOL);
	Gura_AssignWxValue(STC_POV_DIRECTIVE);
	Gura_AssignWxValue(STC_POV_BADDIRECTIVE);
	Gura_AssignWxValue(STC_POV_WORD2);
	Gura_AssignWxValue(STC_POV_WORD3);
	Gura_AssignWxValue(STC_POV_WORD4);
	Gura_AssignWxValue(STC_POV_WORD5);
	Gura_AssignWxValue(STC_POV_WORD6);
	Gura_AssignWxValue(STC_POV_WORD7);
	Gura_AssignWxValue(STC_POV_WORD8);
	Gura_AssignWxValue(STC_LOUT_DEFAULT);
	Gura_AssignWxValue(STC_LOUT_COMMENT);
	Gura_AssignWxValue(STC_LOUT_NUMBER);
	Gura_AssignWxValue(STC_LOUT_WORD);
	Gura_AssignWxValue(STC_LOUT_WORD2);
	Gura_AssignWxValue(STC_LOUT_WORD3);
	Gura_AssignWxValue(STC_LOUT_WORD4);
	Gura_AssignWxValue(STC_LOUT_STRING);
	Gura_AssignWxValue(STC_LOUT_OPERATOR);
	Gura_AssignWxValue(STC_LOUT_IDENTIFIER);
	Gura_AssignWxValue(STC_LOUT_STRINGEOL);
	Gura_AssignWxValue(STC_ESCRIPT_DEFAULT);
	Gura_AssignWxValue(STC_ESCRIPT_COMMENT);
	Gura_AssignWxValue(STC_ESCRIPT_COMMENTLINE);
	Gura_AssignWxValue(STC_ESCRIPT_COMMENTDOC);
	Gura_AssignWxValue(STC_ESCRIPT_NUMBER);
	Gura_AssignWxValue(STC_ESCRIPT_WORD);
	Gura_AssignWxValue(STC_ESCRIPT_STRING);
	Gura_AssignWxValue(STC_ESCRIPT_OPERATOR);
	Gura_AssignWxValue(STC_ESCRIPT_IDENTIFIER);
	Gura_AssignWxValue(STC_ESCRIPT_BRACE);
	Gura_AssignWxValue(STC_ESCRIPT_WORD2);
	Gura_AssignWxValue(STC_ESCRIPT_WORD3);
	Gura_AssignWxValue(STC_PS_DEFAULT);
	Gura_AssignWxValue(STC_PS_COMMENT);
	Gura_AssignWxValue(STC_PS_DSC_COMMENT);
	Gura_AssignWxValue(STC_PS_DSC_VALUE);
	Gura_AssignWxValue(STC_PS_NUMBER);
	Gura_AssignWxValue(STC_PS_NAME);
	Gura_AssignWxValue(STC_PS_KEYWORD);
	Gura_AssignWxValue(STC_PS_LITERAL);
	Gura_AssignWxValue(STC_PS_IMMEVAL);
	Gura_AssignWxValue(STC_PS_PAREN_ARRAY);
	Gura_AssignWxValue(STC_PS_PAREN_DICT);
	Gura_AssignWxValue(STC_PS_PAREN_PROC);
	Gura_AssignWxValue(STC_PS_TEXT);
	Gura_AssignWxValue(STC_PS_HEXSTRING);
	Gura_AssignWxValue(STC_PS_BASE85STRING);
	Gura_AssignWxValue(STC_PS_BADSTRINGCHAR);
	Gura_AssignWxValue(STC_NSIS_DEFAULT);
	Gura_AssignWxValue(STC_NSIS_COMMENT);
	Gura_AssignWxValue(STC_NSIS_STRINGDQ);
	Gura_AssignWxValue(STC_NSIS_STRINGLQ);
	Gura_AssignWxValue(STC_NSIS_STRINGRQ);
	Gura_AssignWxValue(STC_NSIS_FUNCTION);
	Gura_AssignWxValue(STC_NSIS_VARIABLE);
	Gura_AssignWxValue(STC_NSIS_LABEL);
	Gura_AssignWxValue(STC_NSIS_USERDEFINED);
	Gura_AssignWxValue(STC_NSIS_SECTIONDEF);
	Gura_AssignWxValue(STC_NSIS_SUBSECTIONDEF);
	Gura_AssignWxValue(STC_NSIS_IFDEFINEDEF);
	Gura_AssignWxValue(STC_NSIS_MACRODEF);
	Gura_AssignWxValue(STC_NSIS_STRINGVAR);
	Gura_AssignWxValue(STC_NSIS_NUMBER);
	Gura_AssignWxValue(STC_NSIS_SECTIONGROUP);
	Gura_AssignWxValue(STC_NSIS_PAGEEX);
	Gura_AssignWxValue(STC_NSIS_FUNCTIONDEF);
	Gura_AssignWxValue(STC_NSIS_COMMENTBOX);
	Gura_AssignWxValue(STC_MMIXAL_LEADWS);
	Gura_AssignWxValue(STC_MMIXAL_COMMENT);
	Gura_AssignWxValue(STC_MMIXAL_LABEL);
	Gura_AssignWxValue(STC_MMIXAL_OPCODE);
	Gura_AssignWxValue(STC_MMIXAL_OPCODE_PRE);
	Gura_AssignWxValue(STC_MMIXAL_OPCODE_VALID);
	Gura_AssignWxValue(STC_MMIXAL_OPCODE_UNKNOWN);
	Gura_AssignWxValue(STC_MMIXAL_OPCODE_POST);
	Gura_AssignWxValue(STC_MMIXAL_OPERANDS);
	Gura_AssignWxValue(STC_MMIXAL_NUMBER);
	Gura_AssignWxValue(STC_MMIXAL_REF);
	Gura_AssignWxValue(STC_MMIXAL_CHAR);
	Gura_AssignWxValue(STC_MMIXAL_STRING);
	Gura_AssignWxValue(STC_MMIXAL_REGISTER);
	Gura_AssignWxValue(STC_MMIXAL_HEX);
	Gura_AssignWxValue(STC_MMIXAL_OPERATOR);
	Gura_AssignWxValue(STC_MMIXAL_SYMBOL);
	Gura_AssignWxValue(STC_MMIXAL_INCLUDE);
	Gura_AssignWxValue(STC_CLW_DEFAULT);
	Gura_AssignWxValue(STC_CLW_LABEL);
	Gura_AssignWxValue(STC_CLW_COMMENT);
	Gura_AssignWxValue(STC_CLW_STRING);
	Gura_AssignWxValue(STC_CLW_USER_IDENTIFIER);
	Gura_AssignWxValue(STC_CLW_INTEGER_CONSTANT);
	Gura_AssignWxValue(STC_CLW_REAL_CONSTANT);
	Gura_AssignWxValue(STC_CLW_PICTURE_STRING);
	Gura_AssignWxValue(STC_CLW_KEYWORD);
	Gura_AssignWxValue(STC_CLW_COMPILER_DIRECTIVE);
	Gura_AssignWxValue(STC_CLW_RUNTIME_EXPRESSIONS);
	Gura_AssignWxValue(STC_CLW_BUILTIN_PROCEDURES_FUNCTION);
	Gura_AssignWxValue(STC_CLW_STRUCTURE_DATA_TYPE);
	Gura_AssignWxValue(STC_CLW_ATTRIBUTE);
	Gura_AssignWxValue(STC_CLW_STANDARD_EQUATE);
	Gura_AssignWxValue(STC_CLW_ERROR);
	Gura_AssignWxValue(STC_CLW_DEPRECATED);
	Gura_AssignWxValue(STC_LOT_DEFAULT);
	Gura_AssignWxValue(STC_LOT_HEADER);
	Gura_AssignWxValue(STC_LOT_BREAK);
	Gura_AssignWxValue(STC_LOT_SET);
	Gura_AssignWxValue(STC_LOT_PASS);
	Gura_AssignWxValue(STC_LOT_FAIL);
	Gura_AssignWxValue(STC_LOT_ABORT);
	Gura_AssignWxValue(STC_YAML_DEFAULT);
	Gura_AssignWxValue(STC_YAML_COMMENT);
	Gura_AssignWxValue(STC_YAML_IDENTIFIER);
	Gura_AssignWxValue(STC_YAML_KEYWORD);
	Gura_AssignWxValue(STC_YAML_NUMBER);
	Gura_AssignWxValue(STC_YAML_REFERENCE);
	Gura_AssignWxValue(STC_YAML_DOCUMENT);
	Gura_AssignWxValue(STC_YAML_TEXT);
	Gura_AssignWxValue(STC_YAML_ERROR);
	Gura_AssignWxValue(STC_YAML_OPERATOR);
	Gura_AssignWxValue(STC_TEX_DEFAULT);
	Gura_AssignWxValue(STC_TEX_SPECIAL);
	Gura_AssignWxValue(STC_TEX_GROUP);
	Gura_AssignWxValue(STC_TEX_SYMBOL);
	Gura_AssignWxValue(STC_TEX_COMMAND);
	Gura_AssignWxValue(STC_TEX_TEXT);
	Gura_AssignWxValue(STC_METAPOST_DEFAULT);
	Gura_AssignWxValue(STC_METAPOST_SPECIAL);
	Gura_AssignWxValue(STC_METAPOST_GROUP);
	Gura_AssignWxValue(STC_METAPOST_SYMBOL);
	Gura_AssignWxValue(STC_METAPOST_COMMAND);
	Gura_AssignWxValue(STC_METAPOST_TEXT);
	Gura_AssignWxValue(STC_METAPOST_EXTRA);
	Gura_AssignWxValue(STC_ERLANG_DEFAULT);
	Gura_AssignWxValue(STC_ERLANG_COMMENT);
	Gura_AssignWxValue(STC_ERLANG_VARIABLE);
	Gura_AssignWxValue(STC_ERLANG_NUMBER);
	Gura_AssignWxValue(STC_ERLANG_KEYWORD);
	Gura_AssignWxValue(STC_ERLANG_STRING);
	Gura_AssignWxValue(STC_ERLANG_OPERATOR);
	Gura_AssignWxValue(STC_ERLANG_ATOM);
	Gura_AssignWxValue(STC_ERLANG_FUNCTION_NAME);
	Gura_AssignWxValue(STC_ERLANG_CHARACTER);
	Gura_AssignWxValue(STC_ERLANG_MACRO);
	Gura_AssignWxValue(STC_ERLANG_RECORD);
	Gura_AssignWxValue(STC_ERLANG_PREPROC);
	Gura_AssignWxValue(STC_ERLANG_NODE_NAME);
	Gura_AssignWxValue(STC_ERLANG_COMMENT_FUNCTION);
	Gura_AssignWxValue(STC_ERLANG_COMMENT_MODULE);
	Gura_AssignWxValue(STC_ERLANG_COMMENT_DOC);
	Gura_AssignWxValue(STC_ERLANG_COMMENT_DOC_MACRO);
	Gura_AssignWxValue(STC_ERLANG_ATOM_QUOTED);
	Gura_AssignWxValue(STC_ERLANG_MACRO_QUOTED);
	Gura_AssignWxValue(STC_ERLANG_RECORD_QUOTED);
	Gura_AssignWxValue(STC_ERLANG_NODE_NAME_QUOTED);
	Gura_AssignWxValue(STC_ERLANG_BIFS);
	Gura_AssignWxValue(STC_ERLANG_MODULES);
	Gura_AssignWxValue(STC_ERLANG_MODULES_ATT);
	Gura_AssignWxValue(STC_ERLANG_UNKNOWN);
	Gura_AssignWxValue(STC_MSSQL_DEFAULT);
	Gura_AssignWxValue(STC_MSSQL_COMMENT);
	Gura_AssignWxValue(STC_MSSQL_LINE_COMMENT);
	Gura_AssignWxValue(STC_MSSQL_NUMBER);
	Gura_AssignWxValue(STC_MSSQL_STRING);
	Gura_AssignWxValue(STC_MSSQL_OPERATOR);
	Gura_AssignWxValue(STC_MSSQL_IDENTIFIER);
	Gura_AssignWxValue(STC_MSSQL_VARIABLE);
	Gura_AssignWxValue(STC_MSSQL_COLUMN_NAME);
	Gura_AssignWxValue(STC_MSSQL_STATEMENT);
	Gura_AssignWxValue(STC_MSSQL_DATATYPE);
	Gura_AssignWxValue(STC_MSSQL_SYSTABLE);
	Gura_AssignWxValue(STC_MSSQL_GLOBAL_VARIABLE);
	Gura_AssignWxValue(STC_MSSQL_FUNCTION);
	Gura_AssignWxValue(STC_MSSQL_STORED_PROCEDURE);
	Gura_AssignWxValue(STC_MSSQL_DEFAULT_PREF_DATATYPE);
	Gura_AssignWxValue(STC_MSSQL_COLUMN_NAME_2);
	Gura_AssignWxValue(STC_V_DEFAULT);
	Gura_AssignWxValue(STC_V_COMMENT);
	Gura_AssignWxValue(STC_V_COMMENTLINE);
	Gura_AssignWxValue(STC_V_COMMENTLINEBANG);
	Gura_AssignWxValue(STC_V_NUMBER);
	Gura_AssignWxValue(STC_V_WORD);
	Gura_AssignWxValue(STC_V_STRING);
	Gura_AssignWxValue(STC_V_WORD2);
	Gura_AssignWxValue(STC_V_WORD3);
	Gura_AssignWxValue(STC_V_PREPROCESSOR);
	Gura_AssignWxValue(STC_V_OPERATOR);
	Gura_AssignWxValue(STC_V_IDENTIFIER);
	Gura_AssignWxValue(STC_V_STRINGEOL);
	Gura_AssignWxValue(STC_V_USER);
	Gura_AssignWxValue(STC_KIX_DEFAULT);
	Gura_AssignWxValue(STC_KIX_COMMENT);
	Gura_AssignWxValue(STC_KIX_STRING1);
	Gura_AssignWxValue(STC_KIX_STRING2);
	Gura_AssignWxValue(STC_KIX_NUMBER);
	Gura_AssignWxValue(STC_KIX_VAR);
	Gura_AssignWxValue(STC_KIX_MACRO);
	Gura_AssignWxValue(STC_KIX_KEYWORD);
	Gura_AssignWxValue(STC_KIX_FUNCTIONS);
	Gura_AssignWxValue(STC_KIX_OPERATOR);
	Gura_AssignWxValue(STC_KIX_IDENTIFIER);
	Gura_AssignWxValue(STC_GC_DEFAULT);
	Gura_AssignWxValue(STC_GC_COMMENTLINE);
	Gura_AssignWxValue(STC_GC_COMMENTBLOCK);
	Gura_AssignWxValue(STC_GC_GLOBAL);
	Gura_AssignWxValue(STC_GC_EVENT);
	Gura_AssignWxValue(STC_GC_ATTRIBUTE);
	Gura_AssignWxValue(STC_GC_CONTROL);
	Gura_AssignWxValue(STC_GC_COMMAND);
	Gura_AssignWxValue(STC_GC_STRING);
	Gura_AssignWxValue(STC_GC_OPERATOR);
	Gura_AssignWxValue(STC_SN_DEFAULT);
	Gura_AssignWxValue(STC_SN_CODE);
	Gura_AssignWxValue(STC_SN_COMMENTLINE);
	Gura_AssignWxValue(STC_SN_COMMENTLINEBANG);
	Gura_AssignWxValue(STC_SN_NUMBER);
	Gura_AssignWxValue(STC_SN_WORD);
	Gura_AssignWxValue(STC_SN_STRING);
	Gura_AssignWxValue(STC_SN_WORD2);
	Gura_AssignWxValue(STC_SN_WORD3);
	Gura_AssignWxValue(STC_SN_PREPROCESSOR);
	Gura_AssignWxValue(STC_SN_OPERATOR);
	Gura_AssignWxValue(STC_SN_IDENTIFIER);
	Gura_AssignWxValue(STC_SN_STRINGEOL);
	Gura_AssignWxValue(STC_SN_REGEXTAG);
	Gura_AssignWxValue(STC_SN_SIGNAL);
	Gura_AssignWxValue(STC_SN_USER);
	Gura_AssignWxValue(STC_AU3_DEFAULT);
	Gura_AssignWxValue(STC_AU3_COMMENT);
	Gura_AssignWxValue(STC_AU3_COMMENTBLOCK);
	Gura_AssignWxValue(STC_AU3_NUMBER);
	Gura_AssignWxValue(STC_AU3_FUNCTION);
	Gura_AssignWxValue(STC_AU3_KEYWORD);
	Gura_AssignWxValue(STC_AU3_MACRO);
	Gura_AssignWxValue(STC_AU3_STRING);
	Gura_AssignWxValue(STC_AU3_OPERATOR);
	Gura_AssignWxValue(STC_AU3_VARIABLE);
	Gura_AssignWxValue(STC_AU3_SENT);
	Gura_AssignWxValue(STC_AU3_PREPROCESSOR);
	Gura_AssignWxValue(STC_AU3_SPECIAL);
	Gura_AssignWxValue(STC_AU3_EXPAND);
	Gura_AssignWxValue(STC_AU3_COMOBJ);
	Gura_AssignWxValue(STC_AU3_UDF);
	Gura_AssignWxValue(STC_APDL_DEFAULT);
	Gura_AssignWxValue(STC_APDL_COMMENT);
	Gura_AssignWxValue(STC_APDL_COMMENTBLOCK);
	Gura_AssignWxValue(STC_APDL_NUMBER);
	Gura_AssignWxValue(STC_APDL_STRING);
	Gura_AssignWxValue(STC_APDL_OPERATOR);
	Gura_AssignWxValue(STC_APDL_WORD);
	Gura_AssignWxValue(STC_APDL_PROCESSOR);
	Gura_AssignWxValue(STC_APDL_COMMAND);
	Gura_AssignWxValue(STC_APDL_SLASHCOMMAND);
	Gura_AssignWxValue(STC_APDL_STARCOMMAND);
	Gura_AssignWxValue(STC_APDL_ARGUMENT);
	Gura_AssignWxValue(STC_APDL_FUNCTION);
	Gura_AssignWxValue(STC_SH_DEFAULT);
	Gura_AssignWxValue(STC_SH_ERROR);
	Gura_AssignWxValue(STC_SH_COMMENTLINE);
	Gura_AssignWxValue(STC_SH_NUMBER);
	Gura_AssignWxValue(STC_SH_WORD);
	Gura_AssignWxValue(STC_SH_STRING);
	Gura_AssignWxValue(STC_SH_CHARACTER);
	Gura_AssignWxValue(STC_SH_OPERATOR);
	Gura_AssignWxValue(STC_SH_IDENTIFIER);
	Gura_AssignWxValue(STC_SH_SCALAR);
	Gura_AssignWxValue(STC_SH_PARAM);
	Gura_AssignWxValue(STC_SH_BACKTICKS);
	Gura_AssignWxValue(STC_SH_HERE_DELIM);
	Gura_AssignWxValue(STC_SH_HERE_Q);
	Gura_AssignWxValue(STC_ASN1_DEFAULT);
	Gura_AssignWxValue(STC_ASN1_COMMENT);
	Gura_AssignWxValue(STC_ASN1_IDENTIFIER);
	Gura_AssignWxValue(STC_ASN1_STRING);
	Gura_AssignWxValue(STC_ASN1_OID);
	Gura_AssignWxValue(STC_ASN1_SCALAR);
	Gura_AssignWxValue(STC_ASN1_KEYWORD);
	Gura_AssignWxValue(STC_ASN1_ATTRIBUTE);
	Gura_AssignWxValue(STC_ASN1_DESCRIPTOR);
	Gura_AssignWxValue(STC_ASN1_TYPE);
	Gura_AssignWxValue(STC_ASN1_OPERATOR);
	Gura_AssignWxValue(STC_VHDL_DEFAULT);
	Gura_AssignWxValue(STC_VHDL_COMMENT);
	Gura_AssignWxValue(STC_VHDL_COMMENTLINEBANG);
	Gura_AssignWxValue(STC_VHDL_NUMBER);
	Gura_AssignWxValue(STC_VHDL_STRING);
	Gura_AssignWxValue(STC_VHDL_OPERATOR);
	Gura_AssignWxValue(STC_VHDL_IDENTIFIER);
	Gura_AssignWxValue(STC_VHDL_STRINGEOL);
	Gura_AssignWxValue(STC_VHDL_KEYWORD);
	Gura_AssignWxValue(STC_VHDL_STDOPERATOR);
	Gura_AssignWxValue(STC_VHDL_ATTRIBUTE);
	Gura_AssignWxValue(STC_VHDL_STDFUNCTION);
	Gura_AssignWxValue(STC_VHDL_STDPACKAGE);
	Gura_AssignWxValue(STC_VHDL_STDTYPE);
	Gura_AssignWxValue(STC_VHDL_USERWORD);
	Gura_AssignWxValue(STC_CAML_DEFAULT);
	Gura_AssignWxValue(STC_CAML_IDENTIFIER);
	Gura_AssignWxValue(STC_CAML_TAGNAME);
	Gura_AssignWxValue(STC_CAML_KEYWORD);
	Gura_AssignWxValue(STC_CAML_KEYWORD2);
	Gura_AssignWxValue(STC_CAML_KEYWORD3);
	Gura_AssignWxValue(STC_CAML_LINENUM);
	Gura_AssignWxValue(STC_CAML_OPERATOR);
	Gura_AssignWxValue(STC_CAML_NUMBER);
	Gura_AssignWxValue(STC_CAML_CHAR);
	Gura_AssignWxValue(STC_CAML_WHITE);
	Gura_AssignWxValue(STC_CAML_STRING);
	Gura_AssignWxValue(STC_CAML_COMMENT);
	Gura_AssignWxValue(STC_CAML_COMMENT1);
	Gura_AssignWxValue(STC_CAML_COMMENT2);
	Gura_AssignWxValue(STC_CAML_COMMENT3);
	Gura_AssignWxValue(STC_HA_DEFAULT);
	Gura_AssignWxValue(STC_HA_IDENTIFIER);
	Gura_AssignWxValue(STC_HA_KEYWORD);
	Gura_AssignWxValue(STC_HA_NUMBER);
	Gura_AssignWxValue(STC_HA_STRING);
	Gura_AssignWxValue(STC_HA_CHARACTER);
	Gura_AssignWxValue(STC_HA_CLASS);
	Gura_AssignWxValue(STC_HA_MODULE);
	Gura_AssignWxValue(STC_HA_CAPITAL);
	Gura_AssignWxValue(STC_HA_DATA);
	Gura_AssignWxValue(STC_HA_IMPORT);
	Gura_AssignWxValue(STC_HA_OPERATOR);
	Gura_AssignWxValue(STC_HA_INSTANCE);
	Gura_AssignWxValue(STC_HA_COMMENTLINE);
	Gura_AssignWxValue(STC_HA_COMMENTBLOCK);
	Gura_AssignWxValue(STC_HA_COMMENTBLOCK2);
	Gura_AssignWxValue(STC_HA_COMMENTBLOCK3);
	Gura_AssignWxValue(STC_T3_DEFAULT);
	Gura_AssignWxValue(STC_T3_X_DEFAULT);
	Gura_AssignWxValue(STC_T3_PREPROCESSOR);
	Gura_AssignWxValue(STC_T3_BLOCK_COMMENT);
	Gura_AssignWxValue(STC_T3_LINE_COMMENT);
	Gura_AssignWxValue(STC_T3_OPERATOR);
	Gura_AssignWxValue(STC_T3_KEYWORD);
	Gura_AssignWxValue(STC_T3_NUMBER);
	Gura_AssignWxValue(STC_T3_IDENTIFIER);
	Gura_AssignWxValue(STC_T3_S_STRING);
	Gura_AssignWxValue(STC_T3_D_STRING);
	Gura_AssignWxValue(STC_T3_X_STRING);
	Gura_AssignWxValue(STC_T3_LIB_DIRECTIVE);
	Gura_AssignWxValue(STC_T3_MSG_PARAM);
	Gura_AssignWxValue(STC_T3_HTML_TAG);
	Gura_AssignWxValue(STC_T3_HTML_DEFAULT);
	Gura_AssignWxValue(STC_T3_HTML_STRING);
	Gura_AssignWxValue(STC_T3_USER1);
	Gura_AssignWxValue(STC_T3_USER2);
	Gura_AssignWxValue(STC_T3_USER3);
	Gura_AssignWxValue(STC_T3_BRACE);
	Gura_AssignWxValue(STC_REBOL_DEFAULT);
	Gura_AssignWxValue(STC_REBOL_COMMENTLINE);
	Gura_AssignWxValue(STC_REBOL_COMMENTBLOCK);
	Gura_AssignWxValue(STC_REBOL_PREFACE);
	Gura_AssignWxValue(STC_REBOL_OPERATOR);
	Gura_AssignWxValue(STC_REBOL_CHARACTER);
	Gura_AssignWxValue(STC_REBOL_QUOTEDSTRING);
	Gura_AssignWxValue(STC_REBOL_BRACEDSTRING);
	Gura_AssignWxValue(STC_REBOL_NUMBER);
	Gura_AssignWxValue(STC_REBOL_PAIR);
	Gura_AssignWxValue(STC_REBOL_TUPLE);
	Gura_AssignWxValue(STC_REBOL_BINARY);
	Gura_AssignWxValue(STC_REBOL_MONEY);
	Gura_AssignWxValue(STC_REBOL_ISSUE);
	Gura_AssignWxValue(STC_REBOL_TAG);
	Gura_AssignWxValue(STC_REBOL_FILE);
	Gura_AssignWxValue(STC_REBOL_EMAIL);
	Gura_AssignWxValue(STC_REBOL_URL);
	Gura_AssignWxValue(STC_REBOL_DATE);
	Gura_AssignWxValue(STC_REBOL_TIME);
	Gura_AssignWxValue(STC_REBOL_IDENTIFIER);
	Gura_AssignWxValue(STC_REBOL_WORD);
	Gura_AssignWxValue(STC_REBOL_WORD2);
	Gura_AssignWxValue(STC_REBOL_WORD3);
	Gura_AssignWxValue(STC_REBOL_WORD4);
	Gura_AssignWxValue(STC_REBOL_WORD5);
	Gura_AssignWxValue(STC_REBOL_WORD6);
	Gura_AssignWxValue(STC_REBOL_WORD7);
	Gura_AssignWxValue(STC_REBOL_WORD8);
	Gura_AssignWxValue(STC_SQL_DEFAULT);
	Gura_AssignWxValue(STC_SQL_COMMENT);
	Gura_AssignWxValue(STC_SQL_COMMENTLINE);
	Gura_AssignWxValue(STC_SQL_COMMENTDOC);
	Gura_AssignWxValue(STC_SQL_NUMBER);
	Gura_AssignWxValue(STC_SQL_WORD);
	Gura_AssignWxValue(STC_SQL_STRING);
	Gura_AssignWxValue(STC_SQL_CHARACTER);
	Gura_AssignWxValue(STC_SQL_SQLPLUS);
	Gura_AssignWxValue(STC_SQL_SQLPLUS_PROMPT);
	Gura_AssignWxValue(STC_SQL_OPERATOR);
	Gura_AssignWxValue(STC_SQL_IDENTIFIER);
	Gura_AssignWxValue(STC_SQL_SQLPLUS_COMMENT);
	Gura_AssignWxValue(STC_SQL_COMMENTLINEDOC);
	Gura_AssignWxValue(STC_SQL_WORD2);
	Gura_AssignWxValue(STC_SQL_COMMENTDOCKEYWORD);
	Gura_AssignWxValue(STC_SQL_COMMENTDOCKEYWORDERROR);
	Gura_AssignWxValue(STC_SQL_USER1);
	Gura_AssignWxValue(STC_SQL_USER2);
	Gura_AssignWxValue(STC_SQL_USER3);
	Gura_AssignWxValue(STC_SQL_USER4);
	Gura_AssignWxValue(STC_SQL_QUOTEDIDENTIFIER);
	Gura_AssignWxValue(STC_ST_DEFAULT);
	Gura_AssignWxValue(STC_ST_STRING);
	Gura_AssignWxValue(STC_ST_NUMBER);
	Gura_AssignWxValue(STC_ST_COMMENT);
	Gura_AssignWxValue(STC_ST_SYMBOL);
	Gura_AssignWxValue(STC_ST_BINARY);
	Gura_AssignWxValue(STC_ST_BOOL);
	Gura_AssignWxValue(STC_ST_SELF);
	Gura_AssignWxValue(STC_ST_SUPER);
	Gura_AssignWxValue(STC_ST_NIL);
	Gura_AssignWxValue(STC_ST_GLOBAL);
	Gura_AssignWxValue(STC_ST_RETURN);
	Gura_AssignWxValue(STC_ST_SPECIAL);
	Gura_AssignWxValue(STC_ST_KWSEND);
	Gura_AssignWxValue(STC_ST_ASSIGN);
	Gura_AssignWxValue(STC_ST_CHARACTER);
	Gura_AssignWxValue(STC_ST_SPEC_SEL);
	Gura_AssignWxValue(STC_FS_DEFAULT);
	Gura_AssignWxValue(STC_FS_COMMENT);
	Gura_AssignWxValue(STC_FS_COMMENTLINE);
	Gura_AssignWxValue(STC_FS_COMMENTDOC);
	Gura_AssignWxValue(STC_FS_COMMENTLINEDOC);
	Gura_AssignWxValue(STC_FS_COMMENTDOCKEYWORD);
	Gura_AssignWxValue(STC_FS_COMMENTDOCKEYWORDERROR);
	Gura_AssignWxValue(STC_FS_KEYWORD);
	Gura_AssignWxValue(STC_FS_KEYWORD2);
	Gura_AssignWxValue(STC_FS_KEYWORD3);
	Gura_AssignWxValue(STC_FS_KEYWORD4);
	Gura_AssignWxValue(STC_FS_NUMBER);
	Gura_AssignWxValue(STC_FS_STRING);
	Gura_AssignWxValue(STC_FS_PREPROCESSOR);
	Gura_AssignWxValue(STC_FS_OPERATOR);
	Gura_AssignWxValue(STC_FS_IDENTIFIER);
	Gura_AssignWxValue(STC_FS_DATE);
	Gura_AssignWxValue(STC_FS_STRINGEOL);
	Gura_AssignWxValue(STC_FS_CONSTANT);
	Gura_AssignWxValue(STC_FS_WORDOPERATOR);
	Gura_AssignWxValue(STC_FS_DISABLEDCODE);
	Gura_AssignWxValue(STC_FS_DEFAULT_C);
	Gura_AssignWxValue(STC_FS_COMMENTDOC_C);
	Gura_AssignWxValue(STC_FS_COMMENTLINEDOC_C);
	Gura_AssignWxValue(STC_FS_KEYWORD_C);
	Gura_AssignWxValue(STC_FS_KEYWORD2_C);
	Gura_AssignWxValue(STC_FS_NUMBER_C);
	Gura_AssignWxValue(STC_FS_STRING_C);
	Gura_AssignWxValue(STC_FS_PREPROCESSOR_C);
	Gura_AssignWxValue(STC_FS_OPERATOR_C);
	Gura_AssignWxValue(STC_FS_IDENTIFIER_C);
	Gura_AssignWxValue(STC_FS_STRINGEOL_C);
	Gura_AssignWxValue(STC_CSOUND_DEFAULT);
	Gura_AssignWxValue(STC_CSOUND_COMMENT);
	Gura_AssignWxValue(STC_CSOUND_NUMBER);
	Gura_AssignWxValue(STC_CSOUND_OPERATOR);
	Gura_AssignWxValue(STC_CSOUND_INSTR);
	Gura_AssignWxValue(STC_CSOUND_IDENTIFIER);
	Gura_AssignWxValue(STC_CSOUND_OPCODE);
	Gura_AssignWxValue(STC_CSOUND_HEADERSTMT);
	Gura_AssignWxValue(STC_CSOUND_USERKEYWORD);
	Gura_AssignWxValue(STC_CSOUND_COMMENTBLOCK);
	Gura_AssignWxValue(STC_CSOUND_PARAM);
	Gura_AssignWxValue(STC_CSOUND_ARATE_VAR);
	Gura_AssignWxValue(STC_CSOUND_KRATE_VAR);
	Gura_AssignWxValue(STC_CSOUND_IRATE_VAR);
	Gura_AssignWxValue(STC_CSOUND_GLOBAL_VAR);
	Gura_AssignWxValue(STC_CSOUND_STRINGEOL);
	Gura_AssignWxValue(STC_INNO_DEFAULT);
	Gura_AssignWxValue(STC_INNO_COMMENT);
	Gura_AssignWxValue(STC_INNO_KEYWORD);
	Gura_AssignWxValue(STC_INNO_PARAMETER);
	Gura_AssignWxValue(STC_INNO_SECTION);
	Gura_AssignWxValue(STC_INNO_PREPROC);
	Gura_AssignWxValue(STC_INNO_INLINE_EXPANSION);
	Gura_AssignWxValue(STC_INNO_COMMENT_PASCAL);
	Gura_AssignWxValue(STC_INNO_KEYWORD_PASCAL);
	Gura_AssignWxValue(STC_INNO_KEYWORD_USER);
	Gura_AssignWxValue(STC_INNO_STRING_DOUBLE);
	Gura_AssignWxValue(STC_INNO_STRING_SINGLE);
	Gura_AssignWxValue(STC_INNO_IDENTIFIER);
	Gura_AssignWxValue(STC_OPAL_SPACE);
	Gura_AssignWxValue(STC_OPAL_COMMENT_BLOCK);
	Gura_AssignWxValue(STC_OPAL_COMMENT_LINE);
	Gura_AssignWxValue(STC_OPAL_INTEGER);
	Gura_AssignWxValue(STC_OPAL_KEYWORD);
	Gura_AssignWxValue(STC_OPAL_SORT);
	Gura_AssignWxValue(STC_OPAL_STRING);
	Gura_AssignWxValue(STC_OPAL_PAR);
	Gura_AssignWxValue(STC_OPAL_BOOL_CONST);
	Gura_AssignWxValue(STC_OPAL_DEFAULT);
	Gura_AssignWxValue(STC_SPICE_DEFAULT);
	Gura_AssignWxValue(STC_SPICE_IDENTIFIER);
	Gura_AssignWxValue(STC_SPICE_KEYWORD);
	Gura_AssignWxValue(STC_SPICE_KEYWORD2);
	Gura_AssignWxValue(STC_SPICE_KEYWORD3);
	Gura_AssignWxValue(STC_SPICE_NUMBER);
	Gura_AssignWxValue(STC_SPICE_DELIMITER);
	Gura_AssignWxValue(STC_SPICE_VALUE);
	Gura_AssignWxValue(STC_SPICE_COMMENTLINE);
	Gura_AssignWxValue(STC_CMAKE_DEFAULT);
	Gura_AssignWxValue(STC_CMAKE_COMMENT);
	Gura_AssignWxValue(STC_CMAKE_STRINGDQ);
	Gura_AssignWxValue(STC_CMAKE_STRINGLQ);
	Gura_AssignWxValue(STC_CMAKE_STRINGRQ);
	Gura_AssignWxValue(STC_CMAKE_COMMANDS);
	Gura_AssignWxValue(STC_CMAKE_PARAMETERS);
	Gura_AssignWxValue(STC_CMAKE_VARIABLE);
	Gura_AssignWxValue(STC_CMAKE_USERDEFINED);
	Gura_AssignWxValue(STC_CMAKE_WHILEDEF);
	Gura_AssignWxValue(STC_CMAKE_FOREACHDEF);
	Gura_AssignWxValue(STC_CMAKE_IFDEFINEDEF);
	Gura_AssignWxValue(STC_CMAKE_MACRODEF);
	Gura_AssignWxValue(STC_CMAKE_STRINGVAR);
	Gura_AssignWxValue(STC_CMAKE_NUMBER);
	Gura_AssignWxValue(STC_GAP_DEFAULT);
	Gura_AssignWxValue(STC_GAP_IDENTIFIER);
	Gura_AssignWxValue(STC_GAP_KEYWORD);
	Gura_AssignWxValue(STC_GAP_KEYWORD2);
	Gura_AssignWxValue(STC_GAP_KEYWORD3);
	Gura_AssignWxValue(STC_GAP_KEYWORD4);
	Gura_AssignWxValue(STC_GAP_STRING);
	Gura_AssignWxValue(STC_GAP_CHAR);
	Gura_AssignWxValue(STC_GAP_OPERATOR);
	Gura_AssignWxValue(STC_GAP_COMMENT);
	Gura_AssignWxValue(STC_GAP_NUMBER);
	Gura_AssignWxValue(STC_GAP_STRINGEOL);
	Gura_AssignWxValue(STC_PLM_DEFAULT);
	Gura_AssignWxValue(STC_PLM_COMMENT);
	Gura_AssignWxValue(STC_PLM_STRING);
	Gura_AssignWxValue(STC_PLM_NUMBER);
	Gura_AssignWxValue(STC_PLM_IDENTIFIER);
	Gura_AssignWxValue(STC_PLM_OPERATOR);
	Gura_AssignWxValue(STC_PLM_CONTROL);
	Gura_AssignWxValue(STC_PLM_KEYWORD);
	Gura_AssignWxValue(STC_4GL_DEFAULT);
	Gura_AssignWxValue(STC_4GL_NUMBER);
	Gura_AssignWxValue(STC_4GL_WORD);
	Gura_AssignWxValue(STC_4GL_STRING);
	Gura_AssignWxValue(STC_4GL_CHARACTER);
	Gura_AssignWxValue(STC_4GL_PREPROCESSOR);
	Gura_AssignWxValue(STC_4GL_OPERATOR);
	Gura_AssignWxValue(STC_4GL_IDENTIFIER);
	Gura_AssignWxValue(STC_4GL_BLOCK);
	Gura_AssignWxValue(STC_4GL_END);
	Gura_AssignWxValue(STC_4GL_COMMENT1);
	Gura_AssignWxValue(STC_4GL_COMMENT2);
	Gura_AssignWxValue(STC_4GL_COMMENT3);
	Gura_AssignWxValue(STC_4GL_COMMENT4);
	Gura_AssignWxValue(STC_4GL_COMMENT5);
	Gura_AssignWxValue(STC_4GL_COMMENT6);
	Gura_AssignWxValue(STC_4GL_DEFAULT_);
	Gura_AssignWxValue(STC_4GL_NUMBER_);
	Gura_AssignWxValue(STC_4GL_WORD_);
	Gura_AssignWxValue(STC_4GL_STRING_);
	Gura_AssignWxValue(STC_4GL_CHARACTER_);
	Gura_AssignWxValue(STC_4GL_PREPROCESSOR_);
	Gura_AssignWxValue(STC_4GL_OPERATOR_);
	Gura_AssignWxValue(STC_4GL_IDENTIFIER_);
	Gura_AssignWxValue(STC_4GL_BLOCK_);
	Gura_AssignWxValue(STC_4GL_END_);
	Gura_AssignWxValue(STC_4GL_COMMENT1_);
	Gura_AssignWxValue(STC_4GL_COMMENT2_);
	Gura_AssignWxValue(STC_4GL_COMMENT3_);
	Gura_AssignWxValue(STC_4GL_COMMENT4_);
	Gura_AssignWxValue(STC_4GL_COMMENT5_);
	Gura_AssignWxValue(STC_4GL_COMMENT6_);
	Gura_AssignWxValue(STC_ABAQUS_DEFAULT);
	Gura_AssignWxValue(STC_ABAQUS_COMMENT);
	Gura_AssignWxValue(STC_ABAQUS_COMMENTBLOCK);
	Gura_AssignWxValue(STC_ABAQUS_NUMBER);
	Gura_AssignWxValue(STC_ABAQUS_STRING);
	Gura_AssignWxValue(STC_ABAQUS_OPERATOR);
	Gura_AssignWxValue(STC_ABAQUS_WORD);
	Gura_AssignWxValue(STC_ABAQUS_PROCESSOR);
	Gura_AssignWxValue(STC_ABAQUS_COMMAND);
	Gura_AssignWxValue(STC_ABAQUS_SLASHCOMMAND);
	Gura_AssignWxValue(STC_ABAQUS_STARCOMMAND);
	Gura_AssignWxValue(STC_ABAQUS_ARGUMENT);
	Gura_AssignWxValue(STC_ABAQUS_FUNCTION);
	Gura_AssignWxValue(STC_ASY_DEFAULT);
	Gura_AssignWxValue(STC_ASY_COMMENT);
	Gura_AssignWxValue(STC_ASY_COMMENTLINE);
	Gura_AssignWxValue(STC_ASY_NUMBER);
	Gura_AssignWxValue(STC_ASY_WORD);
	Gura_AssignWxValue(STC_ASY_STRING);
	Gura_AssignWxValue(STC_ASY_CHARACTER);
	Gura_AssignWxValue(STC_ASY_OPERATOR);
	Gura_AssignWxValue(STC_ASY_IDENTIFIER);
	Gura_AssignWxValue(STC_ASY_STRINGEOL);
	Gura_AssignWxValue(STC_ASY_COMMENTLINEDOC);
	Gura_AssignWxValue(STC_ASY_WORD2);
	Gura_AssignWxValue(STC_R_DEFAULT);
	Gura_AssignWxValue(STC_R_COMMENT);
	Gura_AssignWxValue(STC_R_KWORD);
	Gura_AssignWxValue(STC_R_BASEKWORD);
	Gura_AssignWxValue(STC_R_OTHERKWORD);
	Gura_AssignWxValue(STC_R_NUMBER);
	Gura_AssignWxValue(STC_R_STRING);
	Gura_AssignWxValue(STC_R_STRING2);
	Gura_AssignWxValue(STC_R_OPERATOR);
	Gura_AssignWxValue(STC_R_IDENTIFIER);
	Gura_AssignWxValue(STC_R_INFIX);
	Gura_AssignWxValue(STC_R_INFIXEOL);
	Gura_AssignWxValue(STC_MAGIK_DEFAULT);
	Gura_AssignWxValue(STC_MAGIK_COMMENT);
	Gura_AssignWxValue(STC_MAGIK_HYPER_COMMENT);
	Gura_AssignWxValue(STC_MAGIK_STRING);
	Gura_AssignWxValue(STC_MAGIK_CHARACTER);
	Gura_AssignWxValue(STC_MAGIK_NUMBER);
	Gura_AssignWxValue(STC_MAGIK_IDENTIFIER);
	Gura_AssignWxValue(STC_MAGIK_OPERATOR);
	Gura_AssignWxValue(STC_MAGIK_FLOW);
	Gura_AssignWxValue(STC_MAGIK_CONTAINER);
	Gura_AssignWxValue(STC_MAGIK_BRACKET_BLOCK);
	Gura_AssignWxValue(STC_MAGIK_BRACE_BLOCK);
	Gura_AssignWxValue(STC_MAGIK_SQBRACKET_BLOCK);
	Gura_AssignWxValue(STC_MAGIK_UNKNOWN_KEYWORD);
	Gura_AssignWxValue(STC_MAGIK_KEYWORD);
	Gura_AssignWxValue(STC_MAGIK_PRAGMA);
	Gura_AssignWxValue(STC_MAGIK_SYMBOL);
	Gura_AssignWxValue(STC_POWERSHELL_DEFAULT);
	Gura_AssignWxValue(STC_POWERSHELL_COMMENT);
	Gura_AssignWxValue(STC_POWERSHELL_STRING);
	Gura_AssignWxValue(STC_POWERSHELL_CHARACTER);
	Gura_AssignWxValue(STC_POWERSHELL_NUMBER);
	Gura_AssignWxValue(STC_POWERSHELL_VARIABLE);
	Gura_AssignWxValue(STC_POWERSHELL_OPERATOR);
	Gura_AssignWxValue(STC_POWERSHELL_IDENTIFIER);
	Gura_AssignWxValue(STC_POWERSHELL_KEYWORD);
	Gura_AssignWxValue(STC_POWERSHELL_CMDLET);
	Gura_AssignWxValue(STC_POWERSHELL_ALIAS);
	Gura_AssignWxValue(STC_POWERSHELL_FUNCTION);
	Gura_AssignWxValue(STC_POWERSHELL_USER1);
	Gura_AssignWxValue(STC_POWERSHELL_COMMENTSTREAM);
	Gura_AssignWxValue(STC_MYSQL_DEFAULT);
	Gura_AssignWxValue(STC_MYSQL_COMMENT);
	Gura_AssignWxValue(STC_MYSQL_COMMENTLINE);
	Gura_AssignWxValue(STC_MYSQL_VARIABLE);
	Gura_AssignWxValue(STC_MYSQL_SYSTEMVARIABLE);
	Gura_AssignWxValue(STC_MYSQL_KNOWNSYSTEMVARIABLE);
	Gura_AssignWxValue(STC_MYSQL_NUMBER);
	Gura_AssignWxValue(STC_MYSQL_MAJORKEYWORD);
	Gura_AssignWxValue(STC_MYSQL_KEYWORD);
	Gura_AssignWxValue(STC_MYSQL_DATABASEOBJECT);
	Gura_AssignWxValue(STC_MYSQL_PROCEDUREKEYWORD);
	Gura_AssignWxValue(STC_MYSQL_STRING);
	Gura_AssignWxValue(STC_MYSQL_SQSTRING);
	Gura_AssignWxValue(STC_MYSQL_DQSTRING);
	Gura_AssignWxValue(STC_MYSQL_OPERATOR);
	Gura_AssignWxValue(STC_MYSQL_FUNCTION);
	Gura_AssignWxValue(STC_MYSQL_IDENTIFIER);
	Gura_AssignWxValue(STC_MYSQL_QUOTEDIDENTIFIER);
	Gura_AssignWxValue(STC_MYSQL_USER1);
	Gura_AssignWxValue(STC_MYSQL_USER2);
	Gura_AssignWxValue(STC_MYSQL_USER3);
	Gura_AssignWxValue(STC_MYSQL_HIDDENCOMMAND);
	Gura_AssignWxValue(STC_PO_DEFAULT);
	Gura_AssignWxValue(STC_PO_COMMENT);
	Gura_AssignWxValue(STC_PO_MSGID);
	Gura_AssignWxValue(STC_PO_MSGID_TEXT);
	Gura_AssignWxValue(STC_PO_MSGSTR);
	Gura_AssignWxValue(STC_PO_MSGSTR_TEXT);
	Gura_AssignWxValue(STC_PO_MSGCTXT);
	Gura_AssignWxValue(STC_PO_MSGCTXT_TEXT);
	Gura_AssignWxValue(STC_PO_FUZZY);
	Gura_AssignWxValue(STC_PAS_DEFAULT);
	Gura_AssignWxValue(STC_PAS_IDENTIFIER);
	Gura_AssignWxValue(STC_PAS_COMMENT);
	Gura_AssignWxValue(STC_PAS_COMMENT2);
	Gura_AssignWxValue(STC_PAS_COMMENTLINE);
	Gura_AssignWxValue(STC_PAS_PREPROCESSOR);
	Gura_AssignWxValue(STC_PAS_PREPROCESSOR2);
	Gura_AssignWxValue(STC_PAS_NUMBER);
	Gura_AssignWxValue(STC_PAS_HEXNUMBER);
	Gura_AssignWxValue(STC_PAS_WORD);
	Gura_AssignWxValue(STC_PAS_STRING);
	Gura_AssignWxValue(STC_PAS_STRINGEOL);
	Gura_AssignWxValue(STC_PAS_CHARACTER);
	Gura_AssignWxValue(STC_PAS_OPERATOR);
	Gura_AssignWxValue(STC_PAS_ASM);
	Gura_AssignWxValue(STC_SORCUS_DEFAULT);
	Gura_AssignWxValue(STC_SORCUS_COMMAND);
	Gura_AssignWxValue(STC_SORCUS_PARAMETER);
	Gura_AssignWxValue(STC_SORCUS_COMMENTLINE);
	Gura_AssignWxValue(STC_SORCUS_STRING);
	Gura_AssignWxValue(STC_SORCUS_STRINGEOL);
	Gura_AssignWxValue(STC_SORCUS_IDENTIFIER);
	Gura_AssignWxValue(STC_SORCUS_OPERATOR);
	Gura_AssignWxValue(STC_SORCUS_NUMBER);
	Gura_AssignWxValue(STC_SORCUS_CONSTANT);
	Gura_AssignWxValue(STC_POWERPRO_DEFAULT);
	Gura_AssignWxValue(STC_POWERPRO_COMMENTBLOCK);
	Gura_AssignWxValue(STC_POWERPRO_COMMENTLINE);
	Gura_AssignWxValue(STC_POWERPRO_NUMBER);
	Gura_AssignWxValue(STC_POWERPRO_WORD);
	Gura_AssignWxValue(STC_POWERPRO_WORD2);
	Gura_AssignWxValue(STC_POWERPRO_WORD3);
	Gura_AssignWxValue(STC_POWERPRO_WORD4);
	Gura_AssignWxValue(STC_POWERPRO_DOUBLEQUOTEDSTRING);
	Gura_AssignWxValue(STC_POWERPRO_SINGLEQUOTEDSTRING);
	Gura_AssignWxValue(STC_POWERPRO_LINECONTINUE);
	Gura_AssignWxValue(STC_POWERPRO_OPERATOR);
	Gura_AssignWxValue(STC_POWERPRO_IDENTIFIER);
	Gura_AssignWxValue(STC_POWERPRO_STRINGEOL);
	Gura_AssignWxValue(STC_POWERPRO_VERBATIM);
	Gura_AssignWxValue(STC_POWERPRO_ALTQUOTE);
	Gura_AssignWxValue(STC_POWERPRO_FUNCTION);
	Gura_AssignWxValue(STC_SML_DEFAULT);
	Gura_AssignWxValue(STC_SML_IDENTIFIER);
	Gura_AssignWxValue(STC_SML_TAGNAME);
	Gura_AssignWxValue(STC_SML_KEYWORD);
	Gura_AssignWxValue(STC_SML_KEYWORD2);
	Gura_AssignWxValue(STC_SML_KEYWORD3);
	Gura_AssignWxValue(STC_SML_LINENUM);
	Gura_AssignWxValue(STC_SML_OPERATOR);
	Gura_AssignWxValue(STC_SML_NUMBER);
	Gura_AssignWxValue(STC_SML_CHAR);
	Gura_AssignWxValue(STC_SML_STRING);
	Gura_AssignWxValue(STC_SML_COMMENT);
	Gura_AssignWxValue(STC_SML_COMMENT1);
	Gura_AssignWxValue(STC_SML_COMMENT2);
	Gura_AssignWxValue(STC_SML_COMMENT3);
	Gura_AssignWxValue(STC_MARKDOWN_DEFAULT);
	Gura_AssignWxValue(STC_MARKDOWN_LINE_BEGIN);
	Gura_AssignWxValue(STC_MARKDOWN_STRONG1);
	Gura_AssignWxValue(STC_MARKDOWN_STRONG2);
	Gura_AssignWxValue(STC_MARKDOWN_EM1);
	Gura_AssignWxValue(STC_MARKDOWN_EM2);
	Gura_AssignWxValue(STC_MARKDOWN_HEADER1);
	Gura_AssignWxValue(STC_MARKDOWN_HEADER2);
	Gura_AssignWxValue(STC_MARKDOWN_HEADER3);
	Gura_AssignWxValue(STC_MARKDOWN_HEADER4);
	Gura_AssignWxValue(STC_MARKDOWN_HEADER5);
	Gura_AssignWxValue(STC_MARKDOWN_HEADER6);
	Gura_AssignWxValue(STC_MARKDOWN_PRECHAR);
	Gura_AssignWxValue(STC_MARKDOWN_ULIST_ITEM);
	Gura_AssignWxValue(STC_MARKDOWN_OLIST_ITEM);
	Gura_AssignWxValue(STC_MARKDOWN_BLOCKQUOTE);
	Gura_AssignWxValue(STC_MARKDOWN_STRIKEOUT);
	Gura_AssignWxValue(STC_MARKDOWN_HRULE);
	Gura_AssignWxValue(STC_MARKDOWN_LINK);
	Gura_AssignWxValue(STC_MARKDOWN_CODE);
	Gura_AssignWxValue(STC_MARKDOWN_CODE2);
	Gura_AssignWxValue(STC_MARKDOWN_CODEBK);
	Gura_AssignWxValue(STC_TXT2TAGS_DEFAULT);
	Gura_AssignWxValue(STC_TXT2TAGS_LINE_BEGIN);
	Gura_AssignWxValue(STC_TXT2TAGS_STRONG1);
	Gura_AssignWxValue(STC_TXT2TAGS_STRONG2);
	Gura_AssignWxValue(STC_TXT2TAGS_EM1);
	Gura_AssignWxValue(STC_TXT2TAGS_EM2);
	Gura_AssignWxValue(STC_TXT2TAGS_HEADER1);
	Gura_AssignWxValue(STC_TXT2TAGS_HEADER2);
	Gura_AssignWxValue(STC_TXT2TAGS_HEADER3);
	Gura_AssignWxValue(STC_TXT2TAGS_HEADER4);
	Gura_AssignWxValue(STC_TXT2TAGS_HEADER5);
	Gura_AssignWxValue(STC_TXT2TAGS_HEADER6);
	Gura_AssignWxValue(STC_TXT2TAGS_PRECHAR);
	Gura_AssignWxValue(STC_TXT2TAGS_ULIST_ITEM);
	Gura_AssignWxValue(STC_TXT2TAGS_OLIST_ITEM);
	Gura_AssignWxValue(STC_TXT2TAGS_BLOCKQUOTE);
	Gura_AssignWxValue(STC_TXT2TAGS_STRIKEOUT);
	Gura_AssignWxValue(STC_TXT2TAGS_HRULE);
	Gura_AssignWxValue(STC_TXT2TAGS_LINK);
	Gura_AssignWxValue(STC_TXT2TAGS_CODE);
	Gura_AssignWxValue(STC_TXT2TAGS_CODE2);
	Gura_AssignWxValue(STC_TXT2TAGS_CODEBK);
	Gura_AssignWxValue(STC_TXT2TAGS_COMMENT);
	Gura_AssignWxValue(STC_TXT2TAGS_OPTION);
	Gura_AssignWxValue(STC_TXT2TAGS_PREPROC);
	Gura_AssignWxValue(STC_TXT2TAGS_POSTPROC);
	Gura_AssignWxValue(STC_A68K_DEFAULT);
	Gura_AssignWxValue(STC_A68K_COMMENT);
	Gura_AssignWxValue(STC_A68K_NUMBER_DEC);
	Gura_AssignWxValue(STC_A68K_NUMBER_BIN);
	Gura_AssignWxValue(STC_A68K_NUMBER_HEX);
	Gura_AssignWxValue(STC_A68K_STRING1);
	Gura_AssignWxValue(STC_A68K_OPERATOR);
	Gura_AssignWxValue(STC_A68K_CPUINSTRUCTION);
	Gura_AssignWxValue(STC_A68K_EXTINSTRUCTION);
	Gura_AssignWxValue(STC_A68K_REGISTER);
	Gura_AssignWxValue(STC_A68K_DIRECTIVE);
	Gura_AssignWxValue(STC_A68K_MACRO_ARG);
	Gura_AssignWxValue(STC_A68K_LABEL);
	Gura_AssignWxValue(STC_A68K_STRING2);
	Gura_AssignWxValue(STC_A68K_IDENTIFIER);
	Gura_AssignWxValue(STC_A68K_MACRO_DECLARATION);
	Gura_AssignWxValue(STC_A68K_COMMENT_WORD);
	Gura_AssignWxValue(STC_A68K_COMMENT_SPECIAL);
	Gura_AssignWxValue(STC_A68K_COMMENT_DOXYGEN);
	Gura_AssignWxValue(STC_MODULA_DEFAULT);
	Gura_AssignWxValue(STC_MODULA_COMMENT);
	Gura_AssignWxValue(STC_MODULA_DOXYCOMM);
	Gura_AssignWxValue(STC_MODULA_DOXYKEY);
	Gura_AssignWxValue(STC_MODULA_KEYWORD);
	Gura_AssignWxValue(STC_MODULA_RESERVED);
	Gura_AssignWxValue(STC_MODULA_NUMBER);
	Gura_AssignWxValue(STC_MODULA_BASENUM);
	Gura_AssignWxValue(STC_MODULA_FLOAT);
	Gura_AssignWxValue(STC_MODULA_STRING);
	Gura_AssignWxValue(STC_MODULA_STRSPEC);
	Gura_AssignWxValue(STC_MODULA_CHAR);
	Gura_AssignWxValue(STC_MODULA_CHARSPEC);
	Gura_AssignWxValue(STC_MODULA_PROC);
	Gura_AssignWxValue(STC_MODULA_PRAGMA);
	Gura_AssignWxValue(STC_MODULA_PRGKEY);
	Gura_AssignWxValue(STC_MODULA_OPERATOR);
	Gura_AssignWxValue(STC_MODULA_BADSTR);
	Gura_AssignWxValue(STC_COFFEESCRIPT_DEFAULT);
	Gura_AssignWxValue(STC_COFFEESCRIPT_COMMENT);
	Gura_AssignWxValue(STC_COFFEESCRIPT_COMMENTLINE);
	Gura_AssignWxValue(STC_COFFEESCRIPT_COMMENTDOC);
	Gura_AssignWxValue(STC_COFFEESCRIPT_NUMBER);
	Gura_AssignWxValue(STC_COFFEESCRIPT_WORD);
	Gura_AssignWxValue(STC_COFFEESCRIPT_STRING);
	Gura_AssignWxValue(STC_COFFEESCRIPT_CHARACTER);
	Gura_AssignWxValue(STC_COFFEESCRIPT_UUID);
	Gura_AssignWxValue(STC_COFFEESCRIPT_PREPROCESSOR);
	Gura_AssignWxValue(STC_COFFEESCRIPT_OPERATOR);
	Gura_AssignWxValue(STC_COFFEESCRIPT_IDENTIFIER);
	Gura_AssignWxValue(STC_COFFEESCRIPT_STRINGEOL);
	Gura_AssignWxValue(STC_COFFEESCRIPT_VERBATIM);
	Gura_AssignWxValue(STC_COFFEESCRIPT_REGEX);
	Gura_AssignWxValue(STC_COFFEESCRIPT_COMMENTLINEDOC);
	Gura_AssignWxValue(STC_COFFEESCRIPT_WORD2);
	Gura_AssignWxValue(STC_COFFEESCRIPT_COMMENTDOCKEYWORD);
	Gura_AssignWxValue(STC_COFFEESCRIPT_COMMENTDOCKEYWORDERROR);
	Gura_AssignWxValue(STC_COFFEESCRIPT_GLOBALCLASS);
	Gura_AssignWxValue(STC_COFFEESCRIPT_STRINGRAW);
	Gura_AssignWxValue(STC_COFFEESCRIPT_TRIPLEVERBATIM);
	Gura_AssignWxValue(STC_COFFEESCRIPT_HASHQUOTEDSTRING);
	Gura_AssignWxValue(STC_COFFEESCRIPT_COMMENTBLOCK);
	Gura_AssignWxValue(STC_COFFEESCRIPT_VERBOSE_REGEX);
	Gura_AssignWxValue(STC_COFFEESCRIPT_VERBOSE_REGEX_COMMENT);
	Gura_AssignWxValue(STC_AVS_DEFAULT);
	Gura_AssignWxValue(STC_AVS_COMMENTBLOCK);
	Gura_AssignWxValue(STC_AVS_COMMENTBLOCKN);
	Gura_AssignWxValue(STC_AVS_COMMENTLINE);
	Gura_AssignWxValue(STC_AVS_NUMBER);
	Gura_AssignWxValue(STC_AVS_OPERATOR);
	Gura_AssignWxValue(STC_AVS_IDENTIFIER);
	Gura_AssignWxValue(STC_AVS_STRING);
	Gura_AssignWxValue(STC_AVS_TRIPLESTRING);
	Gura_AssignWxValue(STC_AVS_KEYWORD);
	Gura_AssignWxValue(STC_AVS_FILTER);
	Gura_AssignWxValue(STC_AVS_PLUGIN);
	Gura_AssignWxValue(STC_AVS_FUNCTION);
	Gura_AssignWxValue(STC_AVS_CLIPPROP);
	Gura_AssignWxValue(STC_AVS_USERDFN);
	Gura_AssignWxValue(STC_ECL_DEFAULT);
	Gura_AssignWxValue(STC_ECL_COMMENT);
	Gura_AssignWxValue(STC_ECL_COMMENTLINE);
	Gura_AssignWxValue(STC_ECL_NUMBER);
	Gura_AssignWxValue(STC_ECL_STRING);
	Gura_AssignWxValue(STC_ECL_WORD0);
	Gura_AssignWxValue(STC_ECL_OPERATOR);
	Gura_AssignWxValue(STC_ECL_CHARACTER);
	Gura_AssignWxValue(STC_ECL_UUID);
	Gura_AssignWxValue(STC_ECL_PREPROCESSOR);
	Gura_AssignWxValue(STC_ECL_UNKNOWN);
	Gura_AssignWxValue(STC_ECL_IDENTIFIER);
	Gura_AssignWxValue(STC_ECL_STRINGEOL);
	Gura_AssignWxValue(STC_ECL_VERBATIM);
	Gura_AssignWxValue(STC_ECL_REGEX);
	Gura_AssignWxValue(STC_ECL_COMMENTLINEDOC);
	Gura_AssignWxValue(STC_ECL_WORD1);
	Gura_AssignWxValue(STC_ECL_COMMENTDOCKEYWORD);
	Gura_AssignWxValue(STC_ECL_COMMENTDOCKEYWORDERROR);
	Gura_AssignWxValue(STC_ECL_WORD2);
	Gura_AssignWxValue(STC_ECL_WORD3);
	Gura_AssignWxValue(STC_ECL_WORD4);
	Gura_AssignWxValue(STC_ECL_WORD5);
	Gura_AssignWxValue(STC_ECL_COMMENTDOC);
	Gura_AssignWxValue(STC_ECL_ADDED);
	Gura_AssignWxValue(STC_ECL_DELETED);
	Gura_AssignWxValue(STC_ECL_CHANGED);
	Gura_AssignWxValue(STC_ECL_MOVED);
	Gura_AssignWxValue(STC_OSCRIPT_DEFAULT);
	Gura_AssignWxValue(STC_OSCRIPT_LINE_COMMENT);
	Gura_AssignWxValue(STC_OSCRIPT_BLOCK_COMMENT);
	Gura_AssignWxValue(STC_OSCRIPT_DOC_COMMENT);
	Gura_AssignWxValue(STC_OSCRIPT_PREPROCESSOR);
	Gura_AssignWxValue(STC_OSCRIPT_NUMBER);
	Gura_AssignWxValue(STC_OSCRIPT_SINGLEQUOTE_STRING);
	Gura_AssignWxValue(STC_OSCRIPT_DOUBLEQUOTE_STRING);
	Gura_AssignWxValue(STC_OSCRIPT_CONSTANT);
	Gura_AssignWxValue(STC_OSCRIPT_IDENTIFIER);
	Gura_AssignWxValue(STC_OSCRIPT_GLOBAL);
	Gura_AssignWxValue(STC_OSCRIPT_KEYWORD);
	Gura_AssignWxValue(STC_OSCRIPT_OPERATOR);
	Gura_AssignWxValue(STC_OSCRIPT_LABEL);
	Gura_AssignWxValue(STC_OSCRIPT_TYPE);
	Gura_AssignWxValue(STC_OSCRIPT_FUNCTION);
	Gura_AssignWxValue(STC_OSCRIPT_OBJECT);
	Gura_AssignWxValue(STC_OSCRIPT_PROPERTY);
	Gura_AssignWxValue(STC_OSCRIPT_METHOD);
	Gura_AssignWxValue(STC_VISUALPROLOG_DEFAULT);
	Gura_AssignWxValue(STC_VISUALPROLOG_KEY_MAJOR);
	Gura_AssignWxValue(STC_VISUALPROLOG_KEY_MINOR);
	Gura_AssignWxValue(STC_VISUALPROLOG_KEY_DIRECTIVE);
	Gura_AssignWxValue(STC_VISUALPROLOG_COMMENT_BLOCK);
	Gura_AssignWxValue(STC_VISUALPROLOG_COMMENT_LINE);
	Gura_AssignWxValue(STC_VISUALPROLOG_COMMENT_KEY);
	Gura_AssignWxValue(STC_VISUALPROLOG_COMMENT_KEY_ERROR);
	Gura_AssignWxValue(STC_VISUALPROLOG_IDENTIFIER);
	Gura_AssignWxValue(STC_VISUALPROLOG_VARIABLE);
	Gura_AssignWxValue(STC_VISUALPROLOG_ANONYMOUS);
	Gura_AssignWxValue(STC_VISUALPROLOG_NUMBER);
	Gura_AssignWxValue(STC_VISUALPROLOG_OPERATOR);
	Gura_AssignWxValue(STC_VISUALPROLOG_CHARACTER);
	Gura_AssignWxValue(STC_VISUALPROLOG_CHARACTER_TOO_MANY);
	Gura_AssignWxValue(STC_VISUALPROLOG_CHARACTER_ESCAPE_ERROR);
	Gura_AssignWxValue(STC_VISUALPROLOG_STRING);
	Gura_AssignWxValue(STC_VISUALPROLOG_STRING_ESCAPE);
	Gura_AssignWxValue(STC_VISUALPROLOG_STRING_ESCAPE_ERROR);
	Gura_AssignWxValue(STC_VISUALPROLOG_STRING_EOL_OPEN);
	Gura_AssignWxValue(STC_VISUALPROLOG_STRING_VERBATIM);
	Gura_AssignWxValue(STC_VISUALPROLOG_STRING_VERBATIM_SPECIAL);
	Gura_AssignWxValue(STC_VISUALPROLOG_STRING_VERBATIM_EOL);
	Gura_AssignWxValue(STC_CMD_REDO);
	Gura_AssignWxValue(STC_CMD_SELECTALL);
	Gura_AssignWxValue(STC_CMD_UNDO);
	Gura_AssignWxValue(STC_CMD_CUT);
	Gura_AssignWxValue(STC_CMD_COPY);
	Gura_AssignWxValue(STC_CMD_PASTE);
	Gura_AssignWxValue(STC_CMD_CLEAR);
	Gura_AssignWxValue(STC_CMD_LINEDOWN);
	Gura_AssignWxValue(STC_CMD_LINEDOWNEXTEND);
	Gura_AssignWxValue(STC_CMD_LINEUP);
	Gura_AssignWxValue(STC_CMD_LINEUPEXTEND);
	Gura_AssignWxValue(STC_CMD_CHARLEFT);
	Gura_AssignWxValue(STC_CMD_CHARLEFTEXTEND);
	Gura_AssignWxValue(STC_CMD_CHARRIGHT);
	Gura_AssignWxValue(STC_CMD_CHARRIGHTEXTEND);
	Gura_AssignWxValue(STC_CMD_WORDLEFT);
	Gura_AssignWxValue(STC_CMD_WORDLEFTEXTEND);
	Gura_AssignWxValue(STC_CMD_WORDRIGHT);
	Gura_AssignWxValue(STC_CMD_WORDRIGHTEXTEND);
	Gura_AssignWxValue(STC_CMD_HOME);
	Gura_AssignWxValue(STC_CMD_HOMEEXTEND);
	Gura_AssignWxValue(STC_CMD_LINEEND);
	Gura_AssignWxValue(STC_CMD_LINEENDEXTEND);
	Gura_AssignWxValue(STC_CMD_DOCUMENTSTART);
	Gura_AssignWxValue(STC_CMD_DOCUMENTSTARTEXTEND);
	Gura_AssignWxValue(STC_CMD_DOCUMENTEND);
	Gura_AssignWxValue(STC_CMD_DOCUMENTENDEXTEND);
	Gura_AssignWxValue(STC_CMD_PAGEUP);
	Gura_AssignWxValue(STC_CMD_PAGEUPEXTEND);
	Gura_AssignWxValue(STC_CMD_PAGEDOWN);
	Gura_AssignWxValue(STC_CMD_PAGEDOWNEXTEND);
	Gura_AssignWxValue(STC_CMD_EDITTOGGLEOVERTYPE);
	Gura_AssignWxValue(STC_CMD_CANCEL);
	Gura_AssignWxValue(STC_CMD_DELETEBACK);
	Gura_AssignWxValue(STC_CMD_TAB);
	Gura_AssignWxValue(STC_CMD_BACKTAB);
	Gura_AssignWxValue(STC_CMD_NEWLINE);
	Gura_AssignWxValue(STC_CMD_FORMFEED);
	Gura_AssignWxValue(STC_CMD_VCHOME);
	Gura_AssignWxValue(STC_CMD_VCHOMEEXTEND);
	Gura_AssignWxValue(STC_CMD_ZOOMIN);
	Gura_AssignWxValue(STC_CMD_ZOOMOUT);
	Gura_AssignWxValue(STC_CMD_DELWORDLEFT);
	Gura_AssignWxValue(STC_CMD_DELWORDRIGHT);
	Gura_AssignWxValue(STC_CMD_DELWORDRIGHTEND);
	Gura_AssignWxValue(STC_CMD_LINECUT);
	Gura_AssignWxValue(STC_CMD_LINEDELETE);
	Gura_AssignWxValue(STC_CMD_LINETRANSPOSE);
	Gura_AssignWxValue(STC_CMD_LINEDUPLICATE);
	Gura_AssignWxValue(STC_CMD_LOWERCASE);
	Gura_AssignWxValue(STC_CMD_UPPERCASE);
	Gura_AssignWxValue(STC_CMD_LINESCROLLDOWN);
	Gura_AssignWxValue(STC_CMD_LINESCROLLUP);
	Gura_AssignWxValue(STC_CMD_DELETEBACKNOTLINE);
	Gura_AssignWxValue(STC_CMD_HOMEDISPLAY);
	Gura_AssignWxValue(STC_CMD_HOMEDISPLAYEXTEND);
	Gura_AssignWxValue(STC_CMD_LINEENDDISPLAY);
	Gura_AssignWxValue(STC_CMD_LINEENDDISPLAYEXTEND);
	Gura_AssignWxValue(STC_CMD_HOMEWRAP);
	Gura_AssignWxValue(STC_CMD_HOMEWRAPEXTEND);
	Gura_AssignWxValue(STC_CMD_LINEENDWRAP);
	Gura_AssignWxValue(STC_CMD_LINEENDWRAPEXTEND);
	Gura_AssignWxValue(STC_CMD_VCHOMEWRAP);
	Gura_AssignWxValue(STC_CMD_VCHOMEWRAPEXTEND);
	Gura_AssignWxValue(STC_CMD_LINECOPY);
	Gura_AssignWxValue(STC_CMD_WORDPARTLEFT);
	Gura_AssignWxValue(STC_CMD_WORDPARTLEFTEXTEND);
	Gura_AssignWxValue(STC_CMD_WORDPARTRIGHT);
	Gura_AssignWxValue(STC_CMD_WORDPARTRIGHTEXTEND);
	Gura_AssignWxValue(STC_CMD_DELLINELEFT);
	Gura_AssignWxValue(STC_CMD_DELLINERIGHT);
	Gura_AssignWxValue(STC_CMD_PARADOWN);
	Gura_AssignWxValue(STC_CMD_PARADOWNEXTEND);
	Gura_AssignWxValue(STC_CMD_PARAUP);
	Gura_AssignWxValue(STC_CMD_PARAUPEXTEND);
	Gura_AssignWxValue(STC_CMD_LINEDOWNRECTEXTEND);
	Gura_AssignWxValue(STC_CMD_LINEUPRECTEXTEND);
	Gura_AssignWxValue(STC_CMD_CHARLEFTRECTEXTEND);
	Gura_AssignWxValue(STC_CMD_CHARRIGHTRECTEXTEND);
	Gura_AssignWxValue(STC_CMD_HOMERECTEXTEND);
	Gura_AssignWxValue(STC_CMD_VCHOMERECTEXTEND);
	Gura_AssignWxValue(STC_CMD_LINEENDRECTEXTEND);
	Gura_AssignWxValue(STC_CMD_PAGEUPRECTEXTEND);
	Gura_AssignWxValue(STC_CMD_PAGEDOWNRECTEXTEND);
	Gura_AssignWxValue(STC_CMD_STUTTEREDPAGEUP);
	Gura_AssignWxValue(STC_CMD_STUTTEREDPAGEUPEXTEND);
	Gura_AssignWxValue(STC_CMD_STUTTEREDPAGEDOWN);
	Gura_AssignWxValue(STC_CMD_STUTTEREDPAGEDOWNEXTEND);
	Gura_AssignWxValue(STC_CMD_WORDLEFTEND);
	Gura_AssignWxValue(STC_CMD_WORDLEFTENDEXTEND);
	Gura_AssignWxValue(STC_CMD_WORDRIGHTEND);
	Gura_AssignWxValue(STC_CMD_WORDRIGHTENDEXTEND);
	Gura_AssignWxValue(STC_CMD_VERTICALCENTRECARET);
	Gura_AssignWxValue(STC_CMD_MOVESELECTEDLINESUP);
	Gura_AssignWxValue(STC_CMD_MOVESELECTEDLINESDOWN);
	Gura_AssignWxValue(STC_CMD_SCROLLTOSTART);
	Gura_AssignWxValue(STC_CMD_SCROLLTOEND);
	// assignment of functions
	Gura_AssignFunction(StyledTextCtrlEmpty);
	Gura_AssignFunction(StyledTextCtrl);
	// assignment of methods
	Gura_AssignMethod(wx_StyledTextCtrl, Create);
	Gura_AssignMethod(wx_StyledTextCtrl, AddText);
	Gura_AssignMethod(wx_StyledTextCtrl, AddStyledText);
	Gura_AssignMethod(wx_StyledTextCtrl, InsertText);
	Gura_AssignMethod(wx_StyledTextCtrl, ClearAll);
	Gura_AssignMethod(wx_StyledTextCtrl, DeleteRange);
	Gura_AssignMethod(wx_StyledTextCtrl, ClearDocumentStyle);
	Gura_AssignMethod(wx_StyledTextCtrl, GetLength);
	Gura_AssignMethod(wx_StyledTextCtrl, GetCharAt);
	Gura_AssignMethod(wx_StyledTextCtrl, GetCurrentPos);
	Gura_AssignMethod(wx_StyledTextCtrl, GetAnchor);
	Gura_AssignMethod(wx_StyledTextCtrl, GetStyleAt);
	Gura_AssignMethod(wx_StyledTextCtrl, Redo);
	Gura_AssignMethod(wx_StyledTextCtrl, SetUndoCollection);
	Gura_AssignMethod(wx_StyledTextCtrl, SelectAll);
	Gura_AssignMethod(wx_StyledTextCtrl, SetSavePoint);
	Gura_AssignMethod(wx_StyledTextCtrl, GetStyledText);
	Gura_AssignMethod(wx_StyledTextCtrl, CanRedo);
	Gura_AssignMethod(wx_StyledTextCtrl, MarkerLineFromHandle);
	Gura_AssignMethod(wx_StyledTextCtrl, MarkerDeleteHandle);
	Gura_AssignMethod(wx_StyledTextCtrl, GetUndoCollection);
	Gura_AssignMethod(wx_StyledTextCtrl, GetViewWhiteSpace);
	Gura_AssignMethod(wx_StyledTextCtrl, SetViewWhiteSpace);
	Gura_AssignMethod(wx_StyledTextCtrl, PositionFromPoint);
	Gura_AssignMethod(wx_StyledTextCtrl, PositionFromPointClose);
	Gura_AssignMethod(wx_StyledTextCtrl, GotoLine);
	Gura_AssignMethod(wx_StyledTextCtrl, GotoPos);
	Gura_AssignMethod(wx_StyledTextCtrl, SetAnchor);
	Gura_AssignMethod(wx_StyledTextCtrl, GetCurLine);
	Gura_AssignMethod(wx_StyledTextCtrl, GetEndStyled);
	Gura_AssignMethod(wx_StyledTextCtrl, ConvertEOLs);
	Gura_AssignMethod(wx_StyledTextCtrl, GetEOLMode);
	Gura_AssignMethod(wx_StyledTextCtrl, SetEOLMode);
	Gura_AssignMethod(wx_StyledTextCtrl, StartStyling);
	Gura_AssignMethod(wx_StyledTextCtrl, SetStyling);
	Gura_AssignMethod(wx_StyledTextCtrl, GetBufferedDraw);
	Gura_AssignMethod(wx_StyledTextCtrl, SetBufferedDraw);
	Gura_AssignMethod(wx_StyledTextCtrl, SetTabWidth);
	Gura_AssignMethod(wx_StyledTextCtrl, GetTabWidth);
	Gura_AssignMethod(wx_StyledTextCtrl, SetCodePage);
	Gura_AssignMethod(wx_StyledTextCtrl, MarkerDefine);
	Gura_AssignMethod(wx_StyledTextCtrl, MarkerSetForeground);
	Gura_AssignMethod(wx_StyledTextCtrl, MarkerSetBackground);
	Gura_AssignMethod(wx_StyledTextCtrl, MarkerSetBackgroundSelected);
	Gura_AssignMethod(wx_StyledTextCtrl, MarkerEnableHighlight);
	Gura_AssignMethod(wx_StyledTextCtrl, MarkerAdd);
	Gura_AssignMethod(wx_StyledTextCtrl, MarkerDelete);
	Gura_AssignMethod(wx_StyledTextCtrl, MarkerDeleteAll);
	Gura_AssignMethod(wx_StyledTextCtrl, MarkerGet);
	Gura_AssignMethod(wx_StyledTextCtrl, MarkerNext);
	Gura_AssignMethod(wx_StyledTextCtrl, MarkerPrevious);
	Gura_AssignMethod(wx_StyledTextCtrl, MarkerDefineBitmap);
	Gura_AssignMethod(wx_StyledTextCtrl, MarkerAddSet);
	Gura_AssignMethod(wx_StyledTextCtrl, MarkerSetAlpha);
	Gura_AssignMethod(wx_StyledTextCtrl, SetMarginType);
	Gura_AssignMethod(wx_StyledTextCtrl, GetMarginType);
	Gura_AssignMethod(wx_StyledTextCtrl, SetMarginWidth);
	Gura_AssignMethod(wx_StyledTextCtrl, GetMarginWidth);
	Gura_AssignMethod(wx_StyledTextCtrl, SetMarginMask);
	Gura_AssignMethod(wx_StyledTextCtrl, GetMarginMask);
	Gura_AssignMethod(wx_StyledTextCtrl, SetMarginSensitive);
	Gura_AssignMethod(wx_StyledTextCtrl, GetMarginSensitive);
	Gura_AssignMethod(wx_StyledTextCtrl, SetMarginCursor);
	Gura_AssignMethod(wx_StyledTextCtrl, GetMarginCursor);
	Gura_AssignMethod(wx_StyledTextCtrl, StyleClearAll);
	Gura_AssignMethod(wx_StyledTextCtrl, StyleSetForeground);
	Gura_AssignMethod(wx_StyledTextCtrl, StyleSetBackground);
	Gura_AssignMethod(wx_StyledTextCtrl, StyleSetBold);
	Gura_AssignMethod(wx_StyledTextCtrl, StyleSetItalic);
	Gura_AssignMethod(wx_StyledTextCtrl, StyleSetSize);
	Gura_AssignMethod(wx_StyledTextCtrl, StyleSetFaceName);
	Gura_AssignMethod(wx_StyledTextCtrl, StyleSetEOLFilled);
	Gura_AssignMethod(wx_StyledTextCtrl, StyleResetDefault);
	Gura_AssignMethod(wx_StyledTextCtrl, StyleSetUnderline);
	Gura_AssignMethod(wx_StyledTextCtrl, StyleGetForeground);
	Gura_AssignMethod(wx_StyledTextCtrl, StyleGetBackground);
	Gura_AssignMethod(wx_StyledTextCtrl, StyleGetBold);
	Gura_AssignMethod(wx_StyledTextCtrl, StyleGetItalic);
	Gura_AssignMethod(wx_StyledTextCtrl, StyleGetSize);
	Gura_AssignMethod(wx_StyledTextCtrl, StyleGetFaceName);
	Gura_AssignMethod(wx_StyledTextCtrl, StyleGetEOLFilled);
	Gura_AssignMethod(wx_StyledTextCtrl, StyleGetUnderline);
	Gura_AssignMethod(wx_StyledTextCtrl, StyleGetCase);
	Gura_AssignMethod(wx_StyledTextCtrl, StyleGetCharacterSet);
	Gura_AssignMethod(wx_StyledTextCtrl, StyleGetVisible);
	Gura_AssignMethod(wx_StyledTextCtrl, StyleGetChangeable);
	Gura_AssignMethod(wx_StyledTextCtrl, StyleGetHotSpot);
	Gura_AssignMethod(wx_StyledTextCtrl, StyleSetCase);
	Gura_AssignMethod(wx_StyledTextCtrl, StyleSetSizeFractional);
	Gura_AssignMethod(wx_StyledTextCtrl, StyleGetSizeFractional);
	Gura_AssignMethod(wx_StyledTextCtrl, StyleSetWeight);
	Gura_AssignMethod(wx_StyledTextCtrl, StyleGetWeight);
	Gura_AssignMethod(wx_StyledTextCtrl, StyleSetHotSpot);
	Gura_AssignMethod(wx_StyledTextCtrl, SetSelForeground);
	Gura_AssignMethod(wx_StyledTextCtrl, SetSelBackground);
	Gura_AssignMethod(wx_StyledTextCtrl, GetSelAlpha);
	Gura_AssignMethod(wx_StyledTextCtrl, SetSelAlpha);
	Gura_AssignMethod(wx_StyledTextCtrl, GetSelEOLFilled);
	Gura_AssignMethod(wx_StyledTextCtrl, SetSelEOLFilled);
	Gura_AssignMethod(wx_StyledTextCtrl, SetCaretForeground);
	Gura_AssignMethod(wx_StyledTextCtrl, CmdKeyAssign);
	Gura_AssignMethod(wx_StyledTextCtrl, CmdKeyClear);
	Gura_AssignMethod(wx_StyledTextCtrl, CmdKeyClearAll);
	Gura_AssignMethod(wx_StyledTextCtrl, SetStyleBytes);
	Gura_AssignMethod(wx_StyledTextCtrl, StyleSetVisible);
	Gura_AssignMethod(wx_StyledTextCtrl, GetCaretPeriod);
	Gura_AssignMethod(wx_StyledTextCtrl, SetCaretPeriod);
	Gura_AssignMethod(wx_StyledTextCtrl, SetWordChars);
	Gura_AssignMethod(wx_StyledTextCtrl, GetWordChars);
	Gura_AssignMethod(wx_StyledTextCtrl, BeginUndoAction);
	Gura_AssignMethod(wx_StyledTextCtrl, EndUndoAction);
	Gura_AssignMethod(wx_StyledTextCtrl, IndicatorSetStyle);
	Gura_AssignMethod(wx_StyledTextCtrl, IndicatorGetStyle);
	Gura_AssignMethod(wx_StyledTextCtrl, IndicatorSetForeground);
	Gura_AssignMethod(wx_StyledTextCtrl, IndicatorGetForeground);
	Gura_AssignMethod(wx_StyledTextCtrl, IndicatorSetUnder);
	Gura_AssignMethod(wx_StyledTextCtrl, IndicatorGetUnder);
	Gura_AssignMethod(wx_StyledTextCtrl, SetWhitespaceForeground);
	Gura_AssignMethod(wx_StyledTextCtrl, SetWhitespaceBackground);
	Gura_AssignMethod(wx_StyledTextCtrl, SetWhitespaceSize);
	Gura_AssignMethod(wx_StyledTextCtrl, GetWhitespaceSize);
	Gura_AssignMethod(wx_StyledTextCtrl, SetStyleBits);
	Gura_AssignMethod(wx_StyledTextCtrl, GetStyleBits);
	Gura_AssignMethod(wx_StyledTextCtrl, SetLineState);
	Gura_AssignMethod(wx_StyledTextCtrl, GetLineState);
	Gura_AssignMethod(wx_StyledTextCtrl, GetMaxLineState);
	Gura_AssignMethod(wx_StyledTextCtrl, GetCaretLineVisible);
	Gura_AssignMethod(wx_StyledTextCtrl, SetCaretLineVisible);
	Gura_AssignMethod(wx_StyledTextCtrl, GetCaretLineBackground);
	Gura_AssignMethod(wx_StyledTextCtrl, SetCaretLineBackground);
	Gura_AssignMethod(wx_StyledTextCtrl, StyleSetChangeable);
	Gura_AssignMethod(wx_StyledTextCtrl, AutoCompShow);
	Gura_AssignMethod(wx_StyledTextCtrl, AutoCompCancel);
	Gura_AssignMethod(wx_StyledTextCtrl, AutoCompActive);
	Gura_AssignMethod(wx_StyledTextCtrl, AutoCompPosStart);
	Gura_AssignMethod(wx_StyledTextCtrl, AutoCompComplete);
	Gura_AssignMethod(wx_StyledTextCtrl, AutoCompStops);
	Gura_AssignMethod(wx_StyledTextCtrl, AutoCompSetSeparator);
	Gura_AssignMethod(wx_StyledTextCtrl, AutoCompGetSeparator);
	Gura_AssignMethod(wx_StyledTextCtrl, AutoCompSelect);
	Gura_AssignMethod(wx_StyledTextCtrl, AutoCompSetCancelAtStart);
	Gura_AssignMethod(wx_StyledTextCtrl, AutoCompGetCancelAtStart);
	Gura_AssignMethod(wx_StyledTextCtrl, AutoCompSetFillUps);
	Gura_AssignMethod(wx_StyledTextCtrl, AutoCompSetChooseSingle);
	Gura_AssignMethod(wx_StyledTextCtrl, AutoCompGetChooseSingle);
	Gura_AssignMethod(wx_StyledTextCtrl, AutoCompSetIgnoreCase);
	Gura_AssignMethod(wx_StyledTextCtrl, AutoCompGetIgnoreCase);
	Gura_AssignMethod(wx_StyledTextCtrl, UserListShow);
	Gura_AssignMethod(wx_StyledTextCtrl, AutoCompSetAutoHide);
	Gura_AssignMethod(wx_StyledTextCtrl, AutoCompGetAutoHide);
	Gura_AssignMethod(wx_StyledTextCtrl, AutoCompSetDropRestOfWord);
	Gura_AssignMethod(wx_StyledTextCtrl, AutoCompGetDropRestOfWord);
	Gura_AssignMethod(wx_StyledTextCtrl, RegisterImage);
	Gura_AssignMethod(wx_StyledTextCtrl, ClearRegisteredImages);
	Gura_AssignMethod(wx_StyledTextCtrl, AutoCompGetTypeSeparator);
	Gura_AssignMethod(wx_StyledTextCtrl, AutoCompSetTypeSeparator);
	Gura_AssignMethod(wx_StyledTextCtrl, AutoCompSetMaxWidth);
	Gura_AssignMethod(wx_StyledTextCtrl, AutoCompGetMaxWidth);
	Gura_AssignMethod(wx_StyledTextCtrl, AutoCompSetMaxHeight);
	Gura_AssignMethod(wx_StyledTextCtrl, AutoCompGetMaxHeight);
	Gura_AssignMethod(wx_StyledTextCtrl, SetIndent);
	Gura_AssignMethod(wx_StyledTextCtrl, GetIndent);
	Gura_AssignMethod(wx_StyledTextCtrl, SetUseTabs);
	Gura_AssignMethod(wx_StyledTextCtrl, GetUseTabs);
	Gura_AssignMethod(wx_StyledTextCtrl, SetLineIndentation);
	Gura_AssignMethod(wx_StyledTextCtrl, GetLineIndentation);
	Gura_AssignMethod(wx_StyledTextCtrl, GetLineIndentPosition);
	Gura_AssignMethod(wx_StyledTextCtrl, GetColumn);
	Gura_AssignMethod(wx_StyledTextCtrl, CountCharacters);
	Gura_AssignMethod(wx_StyledTextCtrl, SetUseHorizontalScrollBar);
	Gura_AssignMethod(wx_StyledTextCtrl, GetUseHorizontalScrollBar);
	Gura_AssignMethod(wx_StyledTextCtrl, SetIndentationGuides);
	Gura_AssignMethod(wx_StyledTextCtrl, GetIndentationGuides);
	Gura_AssignMethod(wx_StyledTextCtrl, SetHighlightGuide);
	Gura_AssignMethod(wx_StyledTextCtrl, GetHighlightGuide);
	Gura_AssignMethod(wx_StyledTextCtrl, GetLineEndPosition);
	Gura_AssignMethod(wx_StyledTextCtrl, GetCodePage);
	Gura_AssignMethod(wx_StyledTextCtrl, GetCaretForeground);
	Gura_AssignMethod(wx_StyledTextCtrl, GetReadOnly);
	Gura_AssignMethod(wx_StyledTextCtrl, SetCurrentPos);
	Gura_AssignMethod(wx_StyledTextCtrl, SetSelectionStart);
	Gura_AssignMethod(wx_StyledTextCtrl, GetSelectionStart);
	Gura_AssignMethod(wx_StyledTextCtrl, SetSelectionEnd);
	Gura_AssignMethod(wx_StyledTextCtrl, GetSelectionEnd);
	Gura_AssignMethod(wx_StyledTextCtrl, SetEmptySelection);
	Gura_AssignMethod(wx_StyledTextCtrl, SetPrintMagnification);
	Gura_AssignMethod(wx_StyledTextCtrl, GetPrintMagnification);
	Gura_AssignMethod(wx_StyledTextCtrl, SetPrintColourMode);
	Gura_AssignMethod(wx_StyledTextCtrl, GetPrintColourMode);
	Gura_AssignMethod(wx_StyledTextCtrl, FindText);
	Gura_AssignMethod(wx_StyledTextCtrl, FormatRange);
	Gura_AssignMethod(wx_StyledTextCtrl, GetFirstVisibleLine);
	Gura_AssignMethod(wx_StyledTextCtrl, GetLine);
	Gura_AssignMethod(wx_StyledTextCtrl, GetLineCount);
	Gura_AssignMethod(wx_StyledTextCtrl, SetMarginLeft);
	Gura_AssignMethod(wx_StyledTextCtrl, GetMarginLeft);
	Gura_AssignMethod(wx_StyledTextCtrl, SetMarginRight);
	Gura_AssignMethod(wx_StyledTextCtrl, GetMarginRight);
	Gura_AssignMethod(wx_StyledTextCtrl, GetModify);
	Gura_AssignMethod(wx_StyledTextCtrl, GetSelectedText);
	Gura_AssignMethod(wx_StyledTextCtrl, GetTextRange);
	Gura_AssignMethod(wx_StyledTextCtrl, HideSelection);
	Gura_AssignMethod(wx_StyledTextCtrl, LineFromPosition);
	Gura_AssignMethod(wx_StyledTextCtrl, PositionFromLine);
	Gura_AssignMethod(wx_StyledTextCtrl, LineScroll);
	Gura_AssignMethod(wx_StyledTextCtrl, EnsureCaretVisible);
	Gura_AssignMethod(wx_StyledTextCtrl, ReplaceSelection);
	Gura_AssignMethod(wx_StyledTextCtrl, SetReadOnly);
	Gura_AssignMethod(wx_StyledTextCtrl, CanPaste);
	Gura_AssignMethod(wx_StyledTextCtrl, CanUndo);
	Gura_AssignMethod(wx_StyledTextCtrl, EmptyUndoBuffer);
	Gura_AssignMethod(wx_StyledTextCtrl, Undo);
	Gura_AssignMethod(wx_StyledTextCtrl, Cut);
	Gura_AssignMethod(wx_StyledTextCtrl, Copy);
	Gura_AssignMethod(wx_StyledTextCtrl, Paste);
	Gura_AssignMethod(wx_StyledTextCtrl, Clear);
	Gura_AssignMethod(wx_StyledTextCtrl, SetText);
	Gura_AssignMethod(wx_StyledTextCtrl, GetText);
	Gura_AssignMethod(wx_StyledTextCtrl, GetTextLength);
	Gura_AssignMethod(wx_StyledTextCtrl, SetOvertype);
	Gura_AssignMethod(wx_StyledTextCtrl, GetOvertype);
	Gura_AssignMethod(wx_StyledTextCtrl, SetCaretWidth);
	Gura_AssignMethod(wx_StyledTextCtrl, GetCaretWidth);
	Gura_AssignMethod(wx_StyledTextCtrl, SetTargetStart);
	Gura_AssignMethod(wx_StyledTextCtrl, GetTargetStart);
	Gura_AssignMethod(wx_StyledTextCtrl, SetTargetEnd);
	Gura_AssignMethod(wx_StyledTextCtrl, GetTargetEnd);
	Gura_AssignMethod(wx_StyledTextCtrl, ReplaceTarget);
	Gura_AssignMethod(wx_StyledTextCtrl, ReplaceTargetRE);
	Gura_AssignMethod(wx_StyledTextCtrl, SearchInTarget);
	Gura_AssignMethod(wx_StyledTextCtrl, SetSearchFlags);
	Gura_AssignMethod(wx_StyledTextCtrl, GetSearchFlags);
	Gura_AssignMethod(wx_StyledTextCtrl, CallTipShow);
	Gura_AssignMethod(wx_StyledTextCtrl, CallTipCancel);
	Gura_AssignMethod(wx_StyledTextCtrl, CallTipActive);
	Gura_AssignMethod(wx_StyledTextCtrl, CallTipPosAtStart);
	Gura_AssignMethod(wx_StyledTextCtrl, CallTipSetHighlight);
	Gura_AssignMethod(wx_StyledTextCtrl, CallTipSetBackground);
	Gura_AssignMethod(wx_StyledTextCtrl, CallTipSetForeground);
	Gura_AssignMethod(wx_StyledTextCtrl, CallTipSetForegroundHighlight);
	Gura_AssignMethod(wx_StyledTextCtrl, CallTipUseStyle);
	Gura_AssignMethod(wx_StyledTextCtrl, CallTipSetPosition);
	Gura_AssignMethod(wx_StyledTextCtrl, VisibleFromDocLine);
	Gura_AssignMethod(wx_StyledTextCtrl, DocLineFromVisible);
	Gura_AssignMethod(wx_StyledTextCtrl, WrapCount);
	Gura_AssignMethod(wx_StyledTextCtrl, SetFoldLevel);
	Gura_AssignMethod(wx_StyledTextCtrl, GetFoldLevel);
	Gura_AssignMethod(wx_StyledTextCtrl, GetLastChild);
	Gura_AssignMethod(wx_StyledTextCtrl, GetFoldParent);
	Gura_AssignMethod(wx_StyledTextCtrl, ShowLines);
	Gura_AssignMethod(wx_StyledTextCtrl, HideLines);
	Gura_AssignMethod(wx_StyledTextCtrl, GetLineVisible);
	Gura_AssignMethod(wx_StyledTextCtrl, GetAllLinesVisible);
	Gura_AssignMethod(wx_StyledTextCtrl, SetFoldExpanded);
	Gura_AssignMethod(wx_StyledTextCtrl, GetFoldExpanded);
	Gura_AssignMethod(wx_StyledTextCtrl, ToggleFold);
	Gura_AssignMethod(wx_StyledTextCtrl, EnsureVisible);
	Gura_AssignMethod(wx_StyledTextCtrl, SetFoldFlags);
	Gura_AssignMethod(wx_StyledTextCtrl, EnsureVisibleEnforcePolicy);
	Gura_AssignMethod(wx_StyledTextCtrl, SetTabIndents);
	Gura_AssignMethod(wx_StyledTextCtrl, GetTabIndents);
	Gura_AssignMethod(wx_StyledTextCtrl, SetBackSpaceUnIndents);
	Gura_AssignMethod(wx_StyledTextCtrl, GetBackSpaceUnIndents);
	Gura_AssignMethod(wx_StyledTextCtrl, SetMouseDwellTime);
	Gura_AssignMethod(wx_StyledTextCtrl, GetMouseDwellTime);
	Gura_AssignMethod(wx_StyledTextCtrl, WordStartPosition);
	Gura_AssignMethod(wx_StyledTextCtrl, WordEndPosition);
	Gura_AssignMethod(wx_StyledTextCtrl, SetWrapMode);
	Gura_AssignMethod(wx_StyledTextCtrl, GetWrapMode);
	Gura_AssignMethod(wx_StyledTextCtrl, SetWrapVisualFlags);
	Gura_AssignMethod(wx_StyledTextCtrl, GetWrapVisualFlags);
	Gura_AssignMethod(wx_StyledTextCtrl, SetWrapVisualFlagsLocation);
	Gura_AssignMethod(wx_StyledTextCtrl, GetWrapVisualFlagsLocation);
	Gura_AssignMethod(wx_StyledTextCtrl, SetWrapStartIndent);
	Gura_AssignMethod(wx_StyledTextCtrl, GetWrapStartIndent);
	Gura_AssignMethod(wx_StyledTextCtrl, SetWrapIndentMode);
	Gura_AssignMethod(wx_StyledTextCtrl, GetWrapIndentMode);
	Gura_AssignMethod(wx_StyledTextCtrl, SetLayoutCache);
	Gura_AssignMethod(wx_StyledTextCtrl, GetLayoutCache);
	Gura_AssignMethod(wx_StyledTextCtrl, SetScrollWidth);
	Gura_AssignMethod(wx_StyledTextCtrl, GetScrollWidth);
	Gura_AssignMethod(wx_StyledTextCtrl, SetScrollWidthTracking);
	Gura_AssignMethod(wx_StyledTextCtrl, GetScrollWidthTracking);
	Gura_AssignMethod(wx_StyledTextCtrl, TextWidth);
	Gura_AssignMethod(wx_StyledTextCtrl, SetEndAtLastLine);
	Gura_AssignMethod(wx_StyledTextCtrl, GetEndAtLastLine);
	Gura_AssignMethod(wx_StyledTextCtrl, TextHeight);
	Gura_AssignMethod(wx_StyledTextCtrl, SetUseVerticalScrollBar);
	Gura_AssignMethod(wx_StyledTextCtrl, GetUseVerticalScrollBar);
	Gura_AssignMethod(wx_StyledTextCtrl, AppendText);
	Gura_AssignMethod(wx_StyledTextCtrl, GetTwoPhaseDraw);
	Gura_AssignMethod(wx_StyledTextCtrl, SetTwoPhaseDraw);
	Gura_AssignMethod(wx_StyledTextCtrl, SetFirstVisibleLine);
	Gura_AssignMethod(wx_StyledTextCtrl, SetMultiPaste);
	Gura_AssignMethod(wx_StyledTextCtrl, GetMultiPaste);
	Gura_AssignMethod(wx_StyledTextCtrl, GetTag);
	Gura_AssignMethod(wx_StyledTextCtrl, TargetFromSelection);
	Gura_AssignMethod(wx_StyledTextCtrl, LinesJoin);
	Gura_AssignMethod(wx_StyledTextCtrl, LinesSplit);
	Gura_AssignMethod(wx_StyledTextCtrl, SetFoldMarginColour);
	Gura_AssignMethod(wx_StyledTextCtrl, SetFoldMarginHiColour);
	Gura_AssignMethod(wx_StyledTextCtrl, LineDown);
	Gura_AssignMethod(wx_StyledTextCtrl, LineDownExtend);
	Gura_AssignMethod(wx_StyledTextCtrl, LineUp);
	Gura_AssignMethod(wx_StyledTextCtrl, LineUpExtend);
	Gura_AssignMethod(wx_StyledTextCtrl, CharLeft);
	Gura_AssignMethod(wx_StyledTextCtrl, CharLeftExtend);
	Gura_AssignMethod(wx_StyledTextCtrl, CharRight);
	Gura_AssignMethod(wx_StyledTextCtrl, CharRightExtend);
	Gura_AssignMethod(wx_StyledTextCtrl, WordLeft);
	Gura_AssignMethod(wx_StyledTextCtrl, WordLeftExtend);
	Gura_AssignMethod(wx_StyledTextCtrl, WordRight);
	Gura_AssignMethod(wx_StyledTextCtrl, WordRightExtend);
	Gura_AssignMethod(wx_StyledTextCtrl, Home);
	Gura_AssignMethod(wx_StyledTextCtrl, HomeExtend);
	Gura_AssignMethod(wx_StyledTextCtrl, LineEnd);
	Gura_AssignMethod(wx_StyledTextCtrl, LineEndExtend);
	Gura_AssignMethod(wx_StyledTextCtrl, DocumentStart);
	Gura_AssignMethod(wx_StyledTextCtrl, DocumentStartExtend);
	Gura_AssignMethod(wx_StyledTextCtrl, DocumentEnd);
	Gura_AssignMethod(wx_StyledTextCtrl, DocumentEndExtend);
	Gura_AssignMethod(wx_StyledTextCtrl, PageUp);
	Gura_AssignMethod(wx_StyledTextCtrl, PageUpExtend);
	Gura_AssignMethod(wx_StyledTextCtrl, PageDown);
	Gura_AssignMethod(wx_StyledTextCtrl, PageDownExtend);
	Gura_AssignMethod(wx_StyledTextCtrl, EditToggleOvertype);
	Gura_AssignMethod(wx_StyledTextCtrl, Cancel);
	Gura_AssignMethod(wx_StyledTextCtrl, DeleteBack);
	Gura_AssignMethod(wx_StyledTextCtrl, Tab);
	Gura_AssignMethod(wx_StyledTextCtrl, BackTab);
	Gura_AssignMethod(wx_StyledTextCtrl, NewLine);
	Gura_AssignMethod(wx_StyledTextCtrl, FormFeed);
	Gura_AssignMethod(wx_StyledTextCtrl, VCHome);
	Gura_AssignMethod(wx_StyledTextCtrl, VCHomeExtend);
	Gura_AssignMethod(wx_StyledTextCtrl, ZoomIn);
	Gura_AssignMethod(wx_StyledTextCtrl, ZoomOut);
	Gura_AssignMethod(wx_StyledTextCtrl, DelWordLeft);
	Gura_AssignMethod(wx_StyledTextCtrl, DelWordRight);
	Gura_AssignMethod(wx_StyledTextCtrl, DelWordRightEnd);
	Gura_AssignMethod(wx_StyledTextCtrl, LineCut);
	Gura_AssignMethod(wx_StyledTextCtrl, LineDelete);
	Gura_AssignMethod(wx_StyledTextCtrl, LineTranspose);
	Gura_AssignMethod(wx_StyledTextCtrl, LineDuplicate);
	Gura_AssignMethod(wx_StyledTextCtrl, LowerCase);
	Gura_AssignMethod(wx_StyledTextCtrl, UpperCase);
	Gura_AssignMethod(wx_StyledTextCtrl, LineScrollDown);
	Gura_AssignMethod(wx_StyledTextCtrl, LineScrollUp);
	Gura_AssignMethod(wx_StyledTextCtrl, DeleteBackNotLine);
	Gura_AssignMethod(wx_StyledTextCtrl, HomeDisplay);
	Gura_AssignMethod(wx_StyledTextCtrl, HomeDisplayExtend);
	Gura_AssignMethod(wx_StyledTextCtrl, LineEndDisplay);
	Gura_AssignMethod(wx_StyledTextCtrl, LineEndDisplayExtend);
	Gura_AssignMethod(wx_StyledTextCtrl, HomeWrap);
	Gura_AssignMethod(wx_StyledTextCtrl, HomeWrapExtend);
	Gura_AssignMethod(wx_StyledTextCtrl, LineEndWrap);
	Gura_AssignMethod(wx_StyledTextCtrl, LineEndWrapExtend);
	Gura_AssignMethod(wx_StyledTextCtrl, VCHomeWrap);
	Gura_AssignMethod(wx_StyledTextCtrl, VCHomeWrapExtend);
	Gura_AssignMethod(wx_StyledTextCtrl, LineCopy);
	Gura_AssignMethod(wx_StyledTextCtrl, MoveCaretInsideView);
	Gura_AssignMethod(wx_StyledTextCtrl, LineLength);
	Gura_AssignMethod(wx_StyledTextCtrl, BraceHighlight);
	Gura_AssignMethod(wx_StyledTextCtrl, BraceHighlightIndicator);
	Gura_AssignMethod(wx_StyledTextCtrl, BraceBadLight);
	Gura_AssignMethod(wx_StyledTextCtrl, BraceBadLightIndicator);
	Gura_AssignMethod(wx_StyledTextCtrl, BraceMatch);
	Gura_AssignMethod(wx_StyledTextCtrl, GetViewEOL);
	Gura_AssignMethod(wx_StyledTextCtrl, SetViewEOL);
	Gura_AssignMethod(wx_StyledTextCtrl, GetDocPointer);
	Gura_AssignMethod(wx_StyledTextCtrl, SetDocPointer);
	Gura_AssignMethod(wx_StyledTextCtrl, SetModEventMask);
	Gura_AssignMethod(wx_StyledTextCtrl, GetEdgeColumn);
	Gura_AssignMethod(wx_StyledTextCtrl, SetEdgeColumn);
	Gura_AssignMethod(wx_StyledTextCtrl, GetEdgeMode);
	Gura_AssignMethod(wx_StyledTextCtrl, SetEdgeMode);
	Gura_AssignMethod(wx_StyledTextCtrl, GetEdgeColour);
	Gura_AssignMethod(wx_StyledTextCtrl, SetEdgeColour);
	Gura_AssignMethod(wx_StyledTextCtrl, SearchAnchor);
	Gura_AssignMethod(wx_StyledTextCtrl, SearchNext);
	Gura_AssignMethod(wx_StyledTextCtrl, SearchPrev);
	Gura_AssignMethod(wx_StyledTextCtrl, LinesOnScreen);
	Gura_AssignMethod(wx_StyledTextCtrl, UsePopUp);
	Gura_AssignMethod(wx_StyledTextCtrl, SelectionIsRectangle);
	Gura_AssignMethod(wx_StyledTextCtrl, SetZoom);
	Gura_AssignMethod(wx_StyledTextCtrl, GetZoom);
	Gura_AssignMethod(wx_StyledTextCtrl, CreateDocument);
	Gura_AssignMethod(wx_StyledTextCtrl, AddRefDocument);
	Gura_AssignMethod(wx_StyledTextCtrl, ReleaseDocument);
	Gura_AssignMethod(wx_StyledTextCtrl, GetModEventMask);
	Gura_AssignMethod(wx_StyledTextCtrl, SetSTCFocus);
	Gura_AssignMethod(wx_StyledTextCtrl, GetSTCFocus);
	Gura_AssignMethod(wx_StyledTextCtrl, SetStatus);
	Gura_AssignMethod(wx_StyledTextCtrl, GetStatus);
	Gura_AssignMethod(wx_StyledTextCtrl, SetMouseDownCaptures);
	Gura_AssignMethod(wx_StyledTextCtrl, GetMouseDownCaptures);
	Gura_AssignMethod(wx_StyledTextCtrl, SetSTCCursor);
	Gura_AssignMethod(wx_StyledTextCtrl, GetSTCCursor);
	Gura_AssignMethod(wx_StyledTextCtrl, SetControlCharSymbol);
	Gura_AssignMethod(wx_StyledTextCtrl, GetControlCharSymbol);
	Gura_AssignMethod(wx_StyledTextCtrl, WordPartLeft);
	Gura_AssignMethod(wx_StyledTextCtrl, WordPartLeftExtend);
	Gura_AssignMethod(wx_StyledTextCtrl, WordPartRight);
	Gura_AssignMethod(wx_StyledTextCtrl, WordPartRightExtend);
	Gura_AssignMethod(wx_StyledTextCtrl, SetVisiblePolicy);
	Gura_AssignMethod(wx_StyledTextCtrl, DelLineLeft);
	Gura_AssignMethod(wx_StyledTextCtrl, DelLineRight);
	Gura_AssignMethod(wx_StyledTextCtrl, SetXOffset);
	Gura_AssignMethod(wx_StyledTextCtrl, GetXOffset);
	Gura_AssignMethod(wx_StyledTextCtrl, ChooseCaretX);
	Gura_AssignMethod(wx_StyledTextCtrl, SetXCaretPolicy);
	Gura_AssignMethod(wx_StyledTextCtrl, SetYCaretPolicy);
	Gura_AssignMethod(wx_StyledTextCtrl, SetPrintWrapMode);
	Gura_AssignMethod(wx_StyledTextCtrl, GetPrintWrapMode);
	Gura_AssignMethod(wx_StyledTextCtrl, SetHotspotActiveForeground);
	Gura_AssignMethod(wx_StyledTextCtrl, GetHotspotActiveForeground);
	Gura_AssignMethod(wx_StyledTextCtrl, SetHotspotActiveBackground);
	Gura_AssignMethod(wx_StyledTextCtrl, GetHotspotActiveBackground);
	Gura_AssignMethod(wx_StyledTextCtrl, SetHotspotActiveUnderline);
	Gura_AssignMethod(wx_StyledTextCtrl, GetHotspotActiveUnderline);
	Gura_AssignMethod(wx_StyledTextCtrl, SetHotspotSingleLine);
	Gura_AssignMethod(wx_StyledTextCtrl, GetHotspotSingleLine);
	Gura_AssignMethod(wx_StyledTextCtrl, ParaDown);
	Gura_AssignMethod(wx_StyledTextCtrl, ParaDownExtend);
	Gura_AssignMethod(wx_StyledTextCtrl, ParaUp);
	Gura_AssignMethod(wx_StyledTextCtrl, ParaUpExtend);
	Gura_AssignMethod(wx_StyledTextCtrl, PositionBefore);
	Gura_AssignMethod(wx_StyledTextCtrl, PositionAfter);
	Gura_AssignMethod(wx_StyledTextCtrl, CopyRange);
	Gura_AssignMethod(wx_StyledTextCtrl, CopyText);
	Gura_AssignMethod(wx_StyledTextCtrl, SetSelectionMode);
	Gura_AssignMethod(wx_StyledTextCtrl, GetSelectionMode);
	Gura_AssignMethod(wx_StyledTextCtrl, GetLineSelStartPosition);
	Gura_AssignMethod(wx_StyledTextCtrl, GetLineSelEndPosition);
	Gura_AssignMethod(wx_StyledTextCtrl, LineDownRectExtend);
	Gura_AssignMethod(wx_StyledTextCtrl, LineUpRectExtend);
	Gura_AssignMethod(wx_StyledTextCtrl, CharLeftRectExtend);
	Gura_AssignMethod(wx_StyledTextCtrl, CharRightRectExtend);
	Gura_AssignMethod(wx_StyledTextCtrl, HomeRectExtend);
	Gura_AssignMethod(wx_StyledTextCtrl, VCHomeRectExtend);
	Gura_AssignMethod(wx_StyledTextCtrl, LineEndRectExtend);
	Gura_AssignMethod(wx_StyledTextCtrl, PageUpRectExtend);
	Gura_AssignMethod(wx_StyledTextCtrl, PageDownRectExtend);
	Gura_AssignMethod(wx_StyledTextCtrl, StutteredPageUp);
	Gura_AssignMethod(wx_StyledTextCtrl, StutteredPageUpExtend);
	Gura_AssignMethod(wx_StyledTextCtrl, StutteredPageDown);
	Gura_AssignMethod(wx_StyledTextCtrl, StutteredPageDownExtend);
	Gura_AssignMethod(wx_StyledTextCtrl, WordLeftEnd);
	Gura_AssignMethod(wx_StyledTextCtrl, WordLeftEndExtend);
	Gura_AssignMethod(wx_StyledTextCtrl, WordRightEnd);
	Gura_AssignMethod(wx_StyledTextCtrl, WordRightEndExtend);
	Gura_AssignMethod(wx_StyledTextCtrl, SetWhitespaceChars);
	Gura_AssignMethod(wx_StyledTextCtrl, GetWhitespaceChars);
	Gura_AssignMethod(wx_StyledTextCtrl, SetPunctuationChars);
	Gura_AssignMethod(wx_StyledTextCtrl, GetPunctuationChars);
	Gura_AssignMethod(wx_StyledTextCtrl, SetCharsDefault);
	Gura_AssignMethod(wx_StyledTextCtrl, AutoCompGetCurrent);
	Gura_AssignMethod(wx_StyledTextCtrl, AutoCompSetCaseInsensitiveBehaviour);
	Gura_AssignMethod(wx_StyledTextCtrl, AutoCompGetCaseInsensitiveBehaviour);
	Gura_AssignMethod(wx_StyledTextCtrl, Allocate);
	Gura_AssignMethod(wx_StyledTextCtrl, FindColumn);
	Gura_AssignMethod(wx_StyledTextCtrl, GetCaretSticky);
	Gura_AssignMethod(wx_StyledTextCtrl, SetCaretSticky);
	Gura_AssignMethod(wx_StyledTextCtrl, ToggleCaretSticky);
	Gura_AssignMethod(wx_StyledTextCtrl, SetPasteConvertEndings);
	Gura_AssignMethod(wx_StyledTextCtrl, GetPasteConvertEndings);
	Gura_AssignMethod(wx_StyledTextCtrl, SelectionDuplicate);
	Gura_AssignMethod(wx_StyledTextCtrl, SetCaretLineBackAlpha);
	Gura_AssignMethod(wx_StyledTextCtrl, GetCaretLineBackAlpha);
	Gura_AssignMethod(wx_StyledTextCtrl, SetCaretStyle);
	Gura_AssignMethod(wx_StyledTextCtrl, GetCaretStyle);
	Gura_AssignMethod(wx_StyledTextCtrl, SetIndicatorCurrent);
	Gura_AssignMethod(wx_StyledTextCtrl, GetIndicatorCurrent);
	Gura_AssignMethod(wx_StyledTextCtrl, SetIndicatorValue);
	Gura_AssignMethod(wx_StyledTextCtrl, GetIndicatorValue);
	Gura_AssignMethod(wx_StyledTextCtrl, IndicatorFillRange);
	Gura_AssignMethod(wx_StyledTextCtrl, IndicatorClearRange);
	Gura_AssignMethod(wx_StyledTextCtrl, IndicatorAllOnFor);
	Gura_AssignMethod(wx_StyledTextCtrl, IndicatorValueAt);
	Gura_AssignMethod(wx_StyledTextCtrl, IndicatorStart);
	Gura_AssignMethod(wx_StyledTextCtrl, IndicatorEnd);
	Gura_AssignMethod(wx_StyledTextCtrl, SetPositionCacheSize);
	Gura_AssignMethod(wx_StyledTextCtrl, GetPositionCacheSize);
	Gura_AssignMethod(wx_StyledTextCtrl, CopyAllowLine);
	Gura_AssignMethod(wx_StyledTextCtrl, GetCharacterPointer);
	Gura_AssignMethod(wx_StyledTextCtrl, GetRangePointer);
	Gura_AssignMethod(wx_StyledTextCtrl, GetGapPosition);
	Gura_AssignMethod(wx_StyledTextCtrl, SetKeysUnicode);
	Gura_AssignMethod(wx_StyledTextCtrl, GetKeysUnicode);
	Gura_AssignMethod(wx_StyledTextCtrl, IndicatorSetAlpha);
	Gura_AssignMethod(wx_StyledTextCtrl, IndicatorGetAlpha);
	Gura_AssignMethod(wx_StyledTextCtrl, IndicatorSetOutlineAlpha);
	Gura_AssignMethod(wx_StyledTextCtrl, IndicatorGetOutlineAlpha);
	Gura_AssignMethod(wx_StyledTextCtrl, SetExtraAscent);
	Gura_AssignMethod(wx_StyledTextCtrl, GetExtraAscent);
	Gura_AssignMethod(wx_StyledTextCtrl, SetExtraDescent);
	Gura_AssignMethod(wx_StyledTextCtrl, GetExtraDescent);
	Gura_AssignMethod(wx_StyledTextCtrl, GetMarkerSymbolDefined);
	Gura_AssignMethod(wx_StyledTextCtrl, MarginSetText);
	Gura_AssignMethod(wx_StyledTextCtrl, MarginGetText);
	Gura_AssignMethod(wx_StyledTextCtrl, MarginSetStyle);
	Gura_AssignMethod(wx_StyledTextCtrl, MarginGetStyle);
	Gura_AssignMethod(wx_StyledTextCtrl, MarginSetStyles);
	Gura_AssignMethod(wx_StyledTextCtrl, MarginGetStyles);
	Gura_AssignMethod(wx_StyledTextCtrl, MarginTextClearAll);
	Gura_AssignMethod(wx_StyledTextCtrl, MarginSetStyleOffset);
	Gura_AssignMethod(wx_StyledTextCtrl, MarginGetStyleOffset);
	Gura_AssignMethod(wx_StyledTextCtrl, SetMarginOptions);
	Gura_AssignMethod(wx_StyledTextCtrl, GetMarginOptions);
	Gura_AssignMethod(wx_StyledTextCtrl, AnnotationSetText);
	Gura_AssignMethod(wx_StyledTextCtrl, AnnotationGetText);
	Gura_AssignMethod(wx_StyledTextCtrl, AnnotationSetStyle);
	Gura_AssignMethod(wx_StyledTextCtrl, AnnotationGetStyle);
	Gura_AssignMethod(wx_StyledTextCtrl, AnnotationSetStyles);
	Gura_AssignMethod(wx_StyledTextCtrl, AnnotationGetStyles);
	Gura_AssignMethod(wx_StyledTextCtrl, AnnotationGetLines);
	Gura_AssignMethod(wx_StyledTextCtrl, AnnotationClearAll);
	Gura_AssignMethod(wx_StyledTextCtrl, AnnotationSetVisible);
	Gura_AssignMethod(wx_StyledTextCtrl, AnnotationGetVisible);
	Gura_AssignMethod(wx_StyledTextCtrl, AnnotationSetStyleOffset);
	Gura_AssignMethod(wx_StyledTextCtrl, AnnotationGetStyleOffset);
	Gura_AssignMethod(wx_StyledTextCtrl, AddUndoAction);
	Gura_AssignMethod(wx_StyledTextCtrl, CharPositionFromPoint);
	Gura_AssignMethod(wx_StyledTextCtrl, CharPositionFromPointClose);
	Gura_AssignMethod(wx_StyledTextCtrl, SetMultipleSelection);
	Gura_AssignMethod(wx_StyledTextCtrl, GetMultipleSelection);
	Gura_AssignMethod(wx_StyledTextCtrl, SetAdditionalSelectionTyping);
	Gura_AssignMethod(wx_StyledTextCtrl, GetAdditionalSelectionTyping);
	Gura_AssignMethod(wx_StyledTextCtrl, SetAdditionalCaretsBlink);
	Gura_AssignMethod(wx_StyledTextCtrl, GetAdditionalCaretsBlink);
	Gura_AssignMethod(wx_StyledTextCtrl, SetAdditionalCaretsVisible);
	Gura_AssignMethod(wx_StyledTextCtrl, GetAdditionalCaretsVisible);
	Gura_AssignMethod(wx_StyledTextCtrl, GetSelections);
	Gura_AssignMethod(wx_StyledTextCtrl, ClearSelections);
	Gura_AssignMethod(wx_StyledTextCtrl, AddSelection);
	Gura_AssignMethod(wx_StyledTextCtrl, SetMainSelection);
	Gura_AssignMethod(wx_StyledTextCtrl, GetMainSelection);
	Gura_AssignMethod(wx_StyledTextCtrl, SetSelectionNCaret);
	Gura_AssignMethod(wx_StyledTextCtrl, GetSelectionNCaret);
	Gura_AssignMethod(wx_StyledTextCtrl, SetSelectionNAnchor);
	Gura_AssignMethod(wx_StyledTextCtrl, GetSelectionNAnchor);
	Gura_AssignMethod(wx_StyledTextCtrl, SetSelectionNCaretVirtualSpace);
	Gura_AssignMethod(wx_StyledTextCtrl, GetSelectionNCaretVirtualSpace);
	Gura_AssignMethod(wx_StyledTextCtrl, SetSelectionNAnchorVirtualSpace);
	Gura_AssignMethod(wx_StyledTextCtrl, GetSelectionNAnchorVirtualSpace);
	Gura_AssignMethod(wx_StyledTextCtrl, SetSelectionNStart);
	Gura_AssignMethod(wx_StyledTextCtrl, GetSelectionNStart);
	Gura_AssignMethod(wx_StyledTextCtrl, SetSelectionNEnd);
	Gura_AssignMethod(wx_StyledTextCtrl, GetSelectionNEnd);
	Gura_AssignMethod(wx_StyledTextCtrl, SetRectangularSelectionCaret);
	Gura_AssignMethod(wx_StyledTextCtrl, GetRectangularSelectionCaret);
	Gura_AssignMethod(wx_StyledTextCtrl, SetRectangularSelectionAnchor);
	Gura_AssignMethod(wx_StyledTextCtrl, GetRectangularSelectionAnchor);
	Gura_AssignMethod(wx_StyledTextCtrl, SetRectangularSelectionCaretVirtualSpace);
	Gura_AssignMethod(wx_StyledTextCtrl, GetRectangularSelectionCaretVirtualSpace);
	Gura_AssignMethod(wx_StyledTextCtrl, SetRectangularSelectionAnchorVirtualSpace);
	Gura_AssignMethod(wx_StyledTextCtrl, GetRectangularSelectionAnchorVirtualSpace);
	Gura_AssignMethod(wx_StyledTextCtrl, SetVirtualSpaceOptions);
	Gura_AssignMethod(wx_StyledTextCtrl, GetVirtualSpaceOptions);
	Gura_AssignMethod(wx_StyledTextCtrl, SetRectangularSelectionModifier);
	Gura_AssignMethod(wx_StyledTextCtrl, GetRectangularSelectionModifier);
	Gura_AssignMethod(wx_StyledTextCtrl, SetAdditionalSelForeground);
	Gura_AssignMethod(wx_StyledTextCtrl, SetAdditionalSelBackground);
	Gura_AssignMethod(wx_StyledTextCtrl, SetAdditionalSelAlpha);
	Gura_AssignMethod(wx_StyledTextCtrl, GetAdditionalSelAlpha);
	Gura_AssignMethod(wx_StyledTextCtrl, SetAdditionalCaretForeground);
	Gura_AssignMethod(wx_StyledTextCtrl, GetAdditionalCaretForeground);
	Gura_AssignMethod(wx_StyledTextCtrl, RotateSelection);
	Gura_AssignMethod(wx_StyledTextCtrl, SwapMainAnchorCaret);
	Gura_AssignMethod(wx_StyledTextCtrl, ChangeLexerState);
	Gura_AssignMethod(wx_StyledTextCtrl, ContractedFoldNext);
	Gura_AssignMethod(wx_StyledTextCtrl, VerticalCentreCaret);
	Gura_AssignMethod(wx_StyledTextCtrl, MoveSelectedLinesUp);
	Gura_AssignMethod(wx_StyledTextCtrl, MoveSelectedLinesDown);
	Gura_AssignMethod(wx_StyledTextCtrl, SetIdentifier);
	Gura_AssignMethod(wx_StyledTextCtrl, GetIdentifier);
	Gura_AssignMethod(wx_StyledTextCtrl, RGBAImageSetWidth);
	Gura_AssignMethod(wx_StyledTextCtrl, RGBAImageSetHeight);
	Gura_AssignMethod(wx_StyledTextCtrl, MarkerDefineRGBAImage);
	Gura_AssignMethod(wx_StyledTextCtrl, RegisterRGBAImage);
	Gura_AssignMethod(wx_StyledTextCtrl, ScrollToStart);
	Gura_AssignMethod(wx_StyledTextCtrl, ScrollToEnd);
	Gura_AssignMethod(wx_StyledTextCtrl, SetTechnology);
	Gura_AssignMethod(wx_StyledTextCtrl, GetTechnology);
	Gura_AssignMethod(wx_StyledTextCtrl, CreateLoader);
	Gura_AssignMethod(wx_StyledTextCtrl, StartRecord);
	Gura_AssignMethod(wx_StyledTextCtrl, StopRecord);
	Gura_AssignMethod(wx_StyledTextCtrl, SetLexer);
	Gura_AssignMethod(wx_StyledTextCtrl, GetLexer);
	Gura_AssignMethod(wx_StyledTextCtrl, Colourise);
	Gura_AssignMethod(wx_StyledTextCtrl, SetProperty);
	Gura_AssignMethod(wx_StyledTextCtrl, SetKeyWords);
	Gura_AssignMethod(wx_StyledTextCtrl, SetLexerLanguage);
	Gura_AssignMethod(wx_StyledTextCtrl, GetProperty);
	Gura_AssignMethod(wx_StyledTextCtrl, GetPropertyExpanded);
	Gura_AssignMethod(wx_StyledTextCtrl, GetPropertyInt);
	Gura_AssignMethod(wx_StyledTextCtrl, GetStyleBitsNeeded);
	Gura_AssignMethod(wx_StyledTextCtrl, PrivateLexerCall);
	Gura_AssignMethod(wx_StyledTextCtrl, PropertyNames);
	Gura_AssignMethod(wx_StyledTextCtrl, PropertyType);
	Gura_AssignMethod(wx_StyledTextCtrl, DescribeProperty);
	Gura_AssignMethod(wx_StyledTextCtrl, DescribeKeyWordSets);
	Gura_AssignMethod(wx_StyledTextCtrl, GetCurrentLine);
	Gura_AssignMethod(wx_StyledTextCtrl, StyleSetSpec);
	Gura_AssignMethod(wx_StyledTextCtrl, StyleGetFont);
	Gura_AssignMethod(wx_StyledTextCtrl, StyleSetFont);
	Gura_AssignMethod(wx_StyledTextCtrl, StyleSetFontAttr);
	Gura_AssignMethod(wx_StyledTextCtrl, StyleSetCharacterSet);
	Gura_AssignMethod(wx_StyledTextCtrl, StyleSetFontEncoding);
	Gura_AssignMethod(wx_StyledTextCtrl, CmdKeyExecute);
	Gura_AssignMethod(wx_StyledTextCtrl, SetMargins);
	Gura_AssignMethod(wx_StyledTextCtrl, PointFromPosition);
	Gura_AssignMethod(wx_StyledTextCtrl, ScrollToLine);
	Gura_AssignMethod(wx_StyledTextCtrl, ScrollToColumn);
	Gura_AssignMethod(wx_StyledTextCtrl, SendMsg);
	Gura_AssignMethod(wx_StyledTextCtrl, SetVScrollBar);
	Gura_AssignMethod(wx_StyledTextCtrl, SetHScrollBar);
	Gura_AssignMethod(wx_StyledTextCtrl, GetLastKeydownProcessed);
	Gura_AssignMethod(wx_StyledTextCtrl, SetLastKeydownProcessed);
	Gura_AssignMethod(wx_StyledTextCtrl, SaveFile);
	Gura_AssignMethod(wx_StyledTextCtrl, LoadFile);
	Gura_AssignMethod(wx_StyledTextCtrl, DoDragOver);
	Gura_AssignMethod(wx_StyledTextCtrl, DoDropText);
	Gura_AssignMethod(wx_StyledTextCtrl, AnnotationClearLine);
	Gura_AssignMethod(wx_StyledTextCtrl, AddTextRaw);
	Gura_AssignMethod(wx_StyledTextCtrl, InsertTextRaw);
	Gura_AssignMethod(wx_StyledTextCtrl, GetCurLineRaw);
	Gura_AssignMethod(wx_StyledTextCtrl, GetLineRaw);
	Gura_AssignMethod(wx_StyledTextCtrl, GetSelectedTextRaw);
	Gura_AssignMethod(wx_StyledTextCtrl, GetTextRangeRaw);
	Gura_AssignMethod(wx_StyledTextCtrl, SetTextRaw);
	Gura_AssignMethod(wx_StyledTextCtrl, GetTextRaw);
	Gura_AssignMethod(wx_StyledTextCtrl, AppendTextRaw);
	Gura_AssignMethod(wx_StyledTextCtrl, GetLibraryVersionInfo);
	Gura_AssignMethod(wx_StyledTextCtrl, WriteText);
	Gura_AssignMethod(wx_StyledTextCtrl, Remove);
	Gura_AssignMethod(wx_StyledTextCtrl, Replace);
	Gura_AssignMethod(wx_StyledTextCtrl, SetInsertionPoint);
	Gura_AssignMethod(wx_StyledTextCtrl, GetInsertionPoint);
	Gura_AssignMethod(wx_StyledTextCtrl, GetLastPosition);
	Gura_AssignMethod(wx_StyledTextCtrl, SetSelection);
	Gura_AssignMethod(wx_StyledTextCtrl, SelectNone);
	Gura_AssignMethod(wx_StyledTextCtrl, GetSelection);
	Gura_AssignMethod(wx_StyledTextCtrl, IsEditable);
	Gura_AssignMethod(wx_StyledTextCtrl, SetEditable);
	Gura_AssignMethod(wx_StyledTextCtrl, GetLineLength);
	Gura_AssignMethod(wx_StyledTextCtrl, GetLineText);
	Gura_AssignMethod(wx_StyledTextCtrl, GetNumberOfLines);
	Gura_AssignMethod(wx_StyledTextCtrl, IsModified);
	Gura_AssignMethod(wx_StyledTextCtrl, MarkDirty);
	Gura_AssignMethod(wx_StyledTextCtrl, DiscardEdits);
	Gura_AssignMethod(wx_StyledTextCtrl, SetStyle);
	Gura_AssignMethod(wx_StyledTextCtrl, GetStyle);
	Gura_AssignMethod(wx_StyledTextCtrl, SetDefaultStyle);
	Gura_AssignMethod(wx_StyledTextCtrl, XYToPosition);
	Gura_AssignMethod(wx_StyledTextCtrl, PositionToXY);
	Gura_AssignMethod(wx_StyledTextCtrl, ShowPosition);
	Gura_AssignMethod(wx_StyledTextCtrl, HitTest);
	Gura_AssignMethod(wx_StyledTextCtrl, HitTestXY);
	// assignment of events
	Gura_AssignWxEvent(EVT_STC_CHANGE,					EVT_STC_CHANGE,					StyledTextEvent);
	Gura_AssignWxEvent(EVT_STC_STYLENEEDED,				EVT_STC_STYLENEEDED,			StyledTextEvent);
	Gura_AssignWxEvent(EVT_STC_CHARADDED,				EVT_STC_CHARADDED,				StyledTextEvent);
	Gura_AssignWxEvent(EVT_STC_SAVEPOINTREACHED,		EVT_STC_SAVEPOINTREACHED,		StyledTextEvent);
	Gura_AssignWxEvent(EVT_STC_SAVEPOINTLEFT,			EVT_STC_SAVEPOINTLEFT,			StyledTextEvent);
	Gura_AssignWxEvent(EVT_STC_ROMODIFYATTEMPT,			EVT_STC_ROMODIFYATTEMPT,		StyledTextEvent);
	Gura_AssignWxEvent(EVT_STC_KEY,						EVT_STC_KEY,					StyledTextEvent);
	Gura_AssignWxEvent(EVT_STC_DOUBLECLICK,				EVT_STC_DOUBLECLICK,			StyledTextEvent);
	Gura_AssignWxEvent(EVT_STC_UPDATEUI,				EVT_STC_UPDATEUI,				StyledTextEvent);
	Gura_AssignWxEvent(EVT_STC_MODIFIED,				EVT_STC_MODIFIED,				StyledTextEvent);
	Gura_AssignWxEvent(EVT_STC_MACRORECORD,				EVT_STC_MACRORECORD,			StyledTextEvent);
	Gura_AssignWxEvent(EVT_STC_MARGINCLICK,				EVT_STC_MARGINCLICK,			StyledTextEvent);
	Gura_AssignWxEvent(EVT_STC_NEEDSHOWN,				EVT_STC_NEEDSHOWN,				StyledTextEvent);
	Gura_AssignWxEvent(EVT_STC_PAINTED,					EVT_STC_PAINTED,				StyledTextEvent);
	Gura_AssignWxEvent(EVT_STC_USERLISTSELECTION,		EVT_STC_USERLISTSELECTION,		StyledTextEvent);
	Gura_AssignWxEvent(EVT_STC_URIDROPPED,				EVT_STC_URIDROPPED,				StyledTextEvent);
	Gura_AssignWxEvent(EVT_STC_DWELLSTART,				EVT_STC_DWELLSTART,				StyledTextEvent);
	Gura_AssignWxEvent(EVT_STC_DWELLEND,				EVT_STC_DWELLEND,				StyledTextEvent);
	Gura_AssignWxEvent(EVT_STC_START_DRAG,				EVT_STC_START_DRAG,				StyledTextEvent);
	Gura_AssignWxEvent(EVT_STC_DRAG_OVER,				EVT_STC_DRAG_OVER,				StyledTextEvent);
	Gura_AssignWxEvent(EVT_STC_DO_DROP,					EVT_STC_DO_DROP,				StyledTextEvent);
	Gura_AssignWxEvent(EVT_STC_ZOOM,					EVT_STC_ZOOM,					StyledTextEvent);
	Gura_AssignWxEvent(EVT_STC_HOTSPOT_CLICK,			EVT_STC_HOTSPOT_CLICK,			StyledTextEvent);
	Gura_AssignWxEvent(EVT_STC_HOTSPOT_DCLICK,			EVT_STC_HOTSPOT_DCLICK,			StyledTextEvent);
	Gura_AssignWxEvent(EVT_STC_CALLTIP_CLICK,			EVT_STC_CALLTIP_CLICK,			StyledTextEvent);
	Gura_AssignWxEvent(EVT_STC_AUTOCOMP_SELECTION,		EVT_STC_AUTOCOMP_SELECTION,		StyledTextEvent);
	Gura_AssignWxEvent(EVT_STC_INDICATOR_CLICK,			EVT_STC_INDICATOR_CLICK,		StyledTextEvent);
	Gura_AssignWxEvent(EVT_STC_INDICATOR_RELEASE,		EVT_STC_INDICATOR_RELEASE,		StyledTextEvent);
	Gura_AssignWxEvent(EVT_STC_AUTOCOMP_CANCELLED,		EVT_STC_AUTOCOMP_CANCELLED,		StyledTextEvent);
	Gura_AssignWxEvent(EVT_STC_AUTOCOMP_CHAR_DELETED,	EVT_STC_AUTOCOMP_CHAR_DELETED,	StyledTextEvent);
}

Gura_ImplementDescendantCreator(wx_StyledTextCtrl)
{
	return new Object_wx_StyledTextCtrl((pClass == NULL)? this : pClass, NULL, NULL, OwnerFalse);
}

Gura_EndModuleScope(wx)
