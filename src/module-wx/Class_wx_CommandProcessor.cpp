//----------------------------------------------------------------------------
// wxCommandProcessor
// extracted from cmdproc.tex
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

Gura_DeclarePrivUserSymbol(CanUndo);
Gura_DeclarePrivUserSymbol(ClearCommands);
Gura_DeclarePrivUserSymbol(Redo);
Gura_DeclarePrivUserSymbol(Initialize);
Gura_DeclarePrivUserSymbol(IsDirty);
Gura_DeclarePrivUserSymbol(MarkAsSaved);
Gura_DeclarePrivUserSymbol(Submit);
Gura_DeclarePrivUserSymbol(Undo);

//----------------------------------------------------------------------------
// Class derivation
//----------------------------------------------------------------------------
class wx_CommandProcessor: public wxCommandProcessor, public GuraObjectObserver {
private:
	//Gura::Signal *_pSig;
	Object_wx_CommandProcessor *_pObj;
public:
	inline wx_CommandProcessor(int maxCommands) : wxCommandProcessor(maxCommands), _pObj(nullptr) {}
	//virtual bool CanUndo();
	//virtual void ClearCommands();
	//virtual bool Redo();
	//virtual void Initialize();
	//virtual bool IsDirty();
	//virtual void MarkAsSaved();
	//virtual bool Submit(wxCommand * command, bool storeIt);
	//virtual bool Undo();
	~wx_CommandProcessor();
	inline void AssocWithGura(Object_wx_CommandProcessor *pObj) {
		_pObj = pObj;
	}
	// virtual function of GuraObjectObserver
	virtual void GuraObjectDeleted();
};

wx_CommandProcessor::~wx_CommandProcessor()
{
	if (_pObj != nullptr) _pObj->InvalidateEntity();
}

void wx_CommandProcessor::GuraObjectDeleted()
{
	_pObj = nullptr;
}

//----------------------------------------------------------------------------
// Gura interfaces for wxCommandProcessor
//----------------------------------------------------------------------------
Gura_DeclareFunction(CommandProcessor)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	SetClassToConstruct(Gura_UserClass(wx_CommandProcessor));
	DeclareArg(env, "maxCommands", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(CommandProcessor)
{
	Signal &sig = env.GetSignal();
	if (!CheckWxReady(sig)) return Value::Nil;
	int maxCommands = -1;
	if (arg.IsValid(0)) maxCommands = arg.GetInt(0);
	wx_CommandProcessor *pEntity = new wx_CommandProcessor(maxCommands);
	Object_wx_CommandProcessor *pObj = Object_wx_CommandProcessor::GetObjectThis(arg);
	if (pObj == nullptr) {
		pObj = new Object_wx_CommandProcessor(pEntity, pEntity, OwnerFalse);
		pEntity->AssocWithGura(pObj);
		return ReturnValue(env, arg, Value(pObj));
	}
	pObj->SetEntity(pEntity, pEntity, OwnerFalse);
	pEntity->AssocWithGura(pObj);
	return ReturnValue(env, arg, arg.GetValueThis());
}

Gura_DeclareMethod(wx_CommandProcessor, CanUndo)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_CommandProcessor, CanUndo)
{
	Signal &sig = env.GetSignal();
	Object_wx_CommandProcessor *pThis = Object_wx_CommandProcessor::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	bool rtn = pThis->GetEntity()->CanUndo();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_CommandProcessor, ClearCommands)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_CommandProcessor, ClearCommands)
{
	Signal &sig = env.GetSignal();
	Object_wx_CommandProcessor *pThis = Object_wx_CommandProcessor::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	pThis->GetEntity()->ClearCommands();
	return Value::Nil;
}

Gura_DeclareMethod(wx_CommandProcessor, Redo)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_CommandProcessor, Redo)
{
	Signal &sig = env.GetSignal();
	Object_wx_CommandProcessor *pThis = Object_wx_CommandProcessor::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	bool rtn = pThis->GetEntity()->Redo();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_CommandProcessor, GetCommands)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_CommandProcessor, GetCommands)
{
	Signal &sig = env.GetSignal();
	Object_wx_CommandProcessor *pThis = Object_wx_CommandProcessor::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxList &rtn = pThis->GetEntity()->GetCommands();
	return ReturnValue(env, arg, Value(new Object_wx_List(new wxList(rtn), nullptr, OwnerTrue)));
}

Gura_DeclareMethod(wx_CommandProcessor, GetMaxCommands)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_CommandProcessor, GetMaxCommands)
{
	Signal &sig = env.GetSignal();
	Object_wx_CommandProcessor *pThis = Object_wx_CommandProcessor::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	int rtn = pThis->GetEntity()->GetMaxCommands();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_CommandProcessor, GetEditMenu)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_CommandProcessor, GetEditMenu)
{
	Signal &sig = env.GetSignal();
	Object_wx_CommandProcessor *pThis = Object_wx_CommandProcessor::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxMenu *rtn = (wxMenu *)pThis->GetEntity()->GetEditMenu();
	return ReturnValue(env, arg, Value(new Object_wx_Menu(rtn, nullptr, OwnerFalse)));
}

Gura_DeclareMethod(wx_CommandProcessor, GetRedoAccelerator)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_CommandProcessor, GetRedoAccelerator)
{
	Signal &sig = env.GetSignal();
	Object_wx_CommandProcessor *pThis = Object_wx_CommandProcessor::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxString rtn = pThis->GetEntity()->GetRedoAccelerator();
	return ReturnValue(env, arg, Value(static_cast<const char *>(rtn.ToUTF8())));
}

Gura_DeclareMethod(wx_CommandProcessor, GetRedoMenuLabel)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_CommandProcessor, GetRedoMenuLabel)
{
	Signal &sig = env.GetSignal();
	Object_wx_CommandProcessor *pThis = Object_wx_CommandProcessor::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxString rtn = pThis->GetEntity()->GetRedoMenuLabel();
	return ReturnValue(env, arg, Value(static_cast<const char *>(rtn.ToUTF8())));
}

Gura_DeclareMethod(wx_CommandProcessor, GetUndoAccelerator)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_CommandProcessor, GetUndoAccelerator)
{
	Signal &sig = env.GetSignal();
	Object_wx_CommandProcessor *pThis = Object_wx_CommandProcessor::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxString rtn = pThis->GetEntity()->GetUndoAccelerator();
	return ReturnValue(env, arg, Value(static_cast<const char *>(rtn.ToUTF8())));
}

Gura_DeclareMethod(wx_CommandProcessor, GetUndoMenuLabel)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_CommandProcessor, GetUndoMenuLabel)
{
	Signal &sig = env.GetSignal();
	Object_wx_CommandProcessor *pThis = Object_wx_CommandProcessor::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxString rtn = pThis->GetEntity()->GetUndoMenuLabel();
	return ReturnValue(env, arg, Value(static_cast<const char *>(rtn.ToUTF8())));
}

Gura_DeclareMethod(wx_CommandProcessor, Initialize)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_CommandProcessor, Initialize)
{
	Signal &sig = env.GetSignal();
	Object_wx_CommandProcessor *pThis = Object_wx_CommandProcessor::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	pThis->GetEntity()->Initialize();
	return Value::Nil;
}

Gura_DeclareMethod(wx_CommandProcessor, IsDirty)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_CommandProcessor, IsDirty)
{
	Signal &sig = env.GetSignal();
	Object_wx_CommandProcessor *pThis = Object_wx_CommandProcessor::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	bool rtn = pThis->GetEntity()->IsDirty();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_CommandProcessor, MarkAsSaved)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_CommandProcessor, MarkAsSaved)
{
	Signal &sig = env.GetSignal();
	Object_wx_CommandProcessor *pThis = Object_wx_CommandProcessor::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	pThis->GetEntity()->MarkAsSaved();
	return Value::Nil;
}

Gura_DeclareMethod(wx_CommandProcessor, SetEditMenu)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "menu", VTYPE_wx_Menu, OCCUR_Once);
}

Gura_ImplementMethod(wx_CommandProcessor, SetEditMenu)
{
	Signal &sig = env.GetSignal();
	Object_wx_CommandProcessor *pThis = Object_wx_CommandProcessor::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxMenu *menu = Object_wx_Menu::GetObject(arg, 0)->GetEntity();
	pThis->GetEntity()->SetEditMenu(menu);
	return Value::Nil;
}

Gura_DeclareMethod(wx_CommandProcessor, SetMenuStrings)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_CommandProcessor, SetMenuStrings)
{
	Signal &sig = env.GetSignal();
	Object_wx_CommandProcessor *pThis = Object_wx_CommandProcessor::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	pThis->GetEntity()->SetMenuStrings();
	return Value::Nil;
}

Gura_DeclareMethod(wx_CommandProcessor, SetRedoAccelerator)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "accel", VTYPE_string, OCCUR_Once);
}

Gura_ImplementMethod(wx_CommandProcessor, SetRedoAccelerator)
{
	Signal &sig = env.GetSignal();
	Object_wx_CommandProcessor *pThis = Object_wx_CommandProcessor::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxString accel = wxString::FromUTF8(arg.GetString(0));
	pThis->GetEntity()->SetRedoAccelerator(accel);
	return Value::Nil;
}

Gura_DeclareMethod(wx_CommandProcessor, SetUndoAccelerator)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "accel", VTYPE_string, OCCUR_Once);
}

Gura_ImplementMethod(wx_CommandProcessor, SetUndoAccelerator)
{
	Signal &sig = env.GetSignal();
	Object_wx_CommandProcessor *pThis = Object_wx_CommandProcessor::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxString accel = wxString::FromUTF8(arg.GetString(0));
	pThis->GetEntity()->SetUndoAccelerator(accel);
	return Value::Nil;
}

Gura_DeclareMethod(wx_CommandProcessor, Submit)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "command", VTYPE_wx_Command, OCCUR_Once);
	DeclareArg(env, "storeIt", VTYPE_boolean, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_CommandProcessor, Submit)
{
	Signal &sig = env.GetSignal();
	Object_wx_CommandProcessor *pThis = Object_wx_CommandProcessor::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxCommand *command = Object_wx_Command::GetObject(arg, 0)->GetEntity();
	bool storeIt = true;
	if (arg.IsValid(1)) storeIt = arg.GetBoolean(1);
	bool rtn = pThis->GetEntity()->Submit(command, storeIt);
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_CommandProcessor, Undo)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_CommandProcessor, Undo)
{
	Signal &sig = env.GetSignal();
	Object_wx_CommandProcessor *pThis = Object_wx_CommandProcessor::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	bool rtn = pThis->GetEntity()->Undo();
	return ReturnValue(env, arg, Value(rtn));
}

//----------------------------------------------------------------------------
// Object implementation for wxCommandProcessor
//----------------------------------------------------------------------------
Object_wx_CommandProcessor::~Object_wx_CommandProcessor()
{
}

Object *Object_wx_CommandProcessor::Clone() const
{
	return nullptr;
}

String Object_wx_CommandProcessor::ToString(bool exprFlag)
{
	String rtn("<wx.CommandProcessor:");
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
// Class implementation for wxCommandProcessor
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_CommandProcessor)
{
	Gura_RealizeUserSymbol(CanUndo);
	Gura_RealizeUserSymbol(ClearCommands);
	Gura_RealizeUserSymbol(Redo);
	Gura_RealizeUserSymbol(Initialize);
	Gura_RealizeUserSymbol(IsDirty);
	Gura_RealizeUserSymbol(MarkAsSaved);
	Gura_RealizeUserSymbol(Submit);
	Gura_RealizeUserSymbol(Undo);
	Gura_AssignFunction(CommandProcessor);
	Gura_AssignMethod(wx_CommandProcessor, CanUndo);
	Gura_AssignMethod(wx_CommandProcessor, ClearCommands);
	Gura_AssignMethod(wx_CommandProcessor, Redo);
	Gura_AssignMethod(wx_CommandProcessor, GetCommands);
	Gura_AssignMethod(wx_CommandProcessor, GetMaxCommands);
	Gura_AssignMethod(wx_CommandProcessor, GetEditMenu);
	Gura_AssignMethod(wx_CommandProcessor, GetRedoAccelerator);
	Gura_AssignMethod(wx_CommandProcessor, GetRedoMenuLabel);
	Gura_AssignMethod(wx_CommandProcessor, GetUndoAccelerator);
	Gura_AssignMethod(wx_CommandProcessor, GetUndoMenuLabel);
	Gura_AssignMethod(wx_CommandProcessor, Initialize);
	Gura_AssignMethod(wx_CommandProcessor, IsDirty);
	Gura_AssignMethod(wx_CommandProcessor, MarkAsSaved);
	Gura_AssignMethod(wx_CommandProcessor, SetEditMenu);
	Gura_AssignMethod(wx_CommandProcessor, SetMenuStrings);
	Gura_AssignMethod(wx_CommandProcessor, SetRedoAccelerator);
	Gura_AssignMethod(wx_CommandProcessor, SetUndoAccelerator);
	Gura_AssignMethod(wx_CommandProcessor, Submit);
	Gura_AssignMethod(wx_CommandProcessor, Undo);
}

Gura_ImplementDescendantCreator(wx_CommandProcessor)
{
	return new Object_wx_CommandProcessor((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
