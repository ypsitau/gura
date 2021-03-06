//----------------------------------------------------------------------------
// wxCommandProcessor
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Gura interfaces for wxCommandProcessor
//----------------------------------------------------------------------------

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
// Constructor implementation
//----------------------------------------------------------------------------
Gura_DeclareFunctionAlias(__CommandProcessor, "CommandProcessor")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "maxCommands", VTYPE_number, OCCUR_Once);
	SetClassToConstruct(Gura_UserClass(wx_CommandProcessor));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(__CommandProcessor)
{
	//int maxCommands = arg.GetNumber(0)
	//wxCommandProcessor(maxCommands);
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Method implementation
//----------------------------------------------------------------------------
Gura_DeclareMethodAlias(wx_CommandProcessor, __CanUndo, "CanUndo")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_CommandProcessor, __CanUndo)
{
	Object_wx_CommandProcessor *pThis = Object_wx_CommandProcessor::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//bool _rtn = pThis->GetEntity()->CanUndo();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_CommandProcessor, __CanRedo, "CanRedo")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_CommandProcessor, __CanRedo)
{
	Object_wx_CommandProcessor *pThis = Object_wx_CommandProcessor::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//bool _rtn = pThis->GetEntity()->CanRedo();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_CommandProcessor, __ClearCommands, "ClearCommands")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_CommandProcessor, __ClearCommands)
{
	Object_wx_CommandProcessor *pThis = Object_wx_CommandProcessor::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->ClearCommands();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_CommandProcessor, __GetCommands, "GetCommands")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_CommandProcessor, __GetCommands)
{
	Object_wx_CommandProcessor *pThis = Object_wx_CommandProcessor::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxList& _rtn = pThis->GetEntity()->GetCommands();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_CommandProcessor, __GetCurrentCommand, "GetCurrentCommand")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_CommandProcessor, __GetCurrentCommand)
{
	Object_wx_CommandProcessor *pThis = Object_wx_CommandProcessor::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxCommand* _rtn = pThis->GetEntity()->GetCurrentCommand();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_CommandProcessor, __GetEditMenu, "GetEditMenu")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_CommandProcessor, __GetEditMenu)
{
	Object_wx_CommandProcessor *pThis = Object_wx_CommandProcessor::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxMenu* _rtn = pThis->GetEntity()->GetEditMenu();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_CommandProcessor, __GetMaxCommands, "GetMaxCommands")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_CommandProcessor, __GetMaxCommands)
{
	Object_wx_CommandProcessor *pThis = Object_wx_CommandProcessor::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int _rtn = pThis->GetEntity()->GetMaxCommands();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_CommandProcessor, __GetRedoAccelerator, "GetRedoAccelerator")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_CommandProcessor, __GetRedoAccelerator)
{
	Object_wx_CommandProcessor *pThis = Object_wx_CommandProcessor::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxString& _rtn = pThis->GetEntity()->GetRedoAccelerator();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_CommandProcessor, __GetRedoMenuLabel, "GetRedoMenuLabel")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_CommandProcessor, __GetRedoMenuLabel)
{
	Object_wx_CommandProcessor *pThis = Object_wx_CommandProcessor::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxString _rtn = pThis->GetEntity()->GetRedoMenuLabel();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_CommandProcessor, __GetUndoAccelerator, "GetUndoAccelerator")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_CommandProcessor, __GetUndoAccelerator)
{
	Object_wx_CommandProcessor *pThis = Object_wx_CommandProcessor::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxString& _rtn = pThis->GetEntity()->GetUndoAccelerator();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_CommandProcessor, __GetUndoMenuLabel, "GetUndoMenuLabel")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_CommandProcessor, __GetUndoMenuLabel)
{
	Object_wx_CommandProcessor *pThis = Object_wx_CommandProcessor::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxString _rtn = pThis->GetEntity()->GetUndoMenuLabel();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_CommandProcessor, __Initialize, "Initialize")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_CommandProcessor, __Initialize)
{
	Object_wx_CommandProcessor *pThis = Object_wx_CommandProcessor::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->Initialize();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_CommandProcessor, __IsDirty, "IsDirty")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_CommandProcessor, __IsDirty)
{
	Object_wx_CommandProcessor *pThis = Object_wx_CommandProcessor::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//bool _rtn = pThis->GetEntity()->IsDirty();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_CommandProcessor, __MarkAsSaved, "MarkAsSaved")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_CommandProcessor, __MarkAsSaved)
{
	Object_wx_CommandProcessor *pThis = Object_wx_CommandProcessor::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->MarkAsSaved();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_CommandProcessor, __Redo, "Redo")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_CommandProcessor, __Redo)
{
	Object_wx_CommandProcessor *pThis = Object_wx_CommandProcessor::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//bool _rtn = pThis->GetEntity()->Redo();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_CommandProcessor, __SetEditMenu, "SetEditMenu")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "menu", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_CommandProcessor, __SetEditMenu)
{
	Object_wx_CommandProcessor *pThis = Object_wx_CommandProcessor::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxMenu* menu = arg.GetNumber(0)
	//pThis->GetEntity()->SetEditMenu(menu);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_CommandProcessor, __SetMenuStrings, "SetMenuStrings")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_CommandProcessor, __SetMenuStrings)
{
	Object_wx_CommandProcessor *pThis = Object_wx_CommandProcessor::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->SetMenuStrings();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_CommandProcessor, __SetRedoAccelerator, "SetRedoAccelerator")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "accel", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_CommandProcessor, __SetRedoAccelerator)
{
	Object_wx_CommandProcessor *pThis = Object_wx_CommandProcessor::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxString& accel = arg.GetNumber(0)
	//pThis->GetEntity()->SetRedoAccelerator(accel);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_CommandProcessor, __SetUndoAccelerator, "SetUndoAccelerator")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "accel", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_CommandProcessor, __SetUndoAccelerator)
{
	Object_wx_CommandProcessor *pThis = Object_wx_CommandProcessor::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxString& accel = arg.GetNumber(0)
	//pThis->GetEntity()->SetUndoAccelerator(accel);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_CommandProcessor, __Submit, "Submit")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "command", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "storeIt", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_CommandProcessor, __Submit)
{
	Object_wx_CommandProcessor *pThis = Object_wx_CommandProcessor::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxCommand* command = arg.GetNumber(0)
	//bool storeIt = arg.GetNumber(1)
	//bool _rtn = pThis->GetEntity()->Submit(command, storeIt);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_CommandProcessor, __Store, "Store")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "command", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_CommandProcessor, __Store)
{
	Object_wx_CommandProcessor *pThis = Object_wx_CommandProcessor::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxCommand* command = arg.GetNumber(0)
	//pThis->GetEntity()->Store(command);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_CommandProcessor, __Undo, "Undo")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_CommandProcessor, __Undo)
{
	Object_wx_CommandProcessor *pThis = Object_wx_CommandProcessor::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//bool _rtn = pThis->GetEntity()->Undo();
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Class implementation for wxCommandProcessor
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_CommandProcessor)
{
	// Constructor assignment
	Gura_AssignFunction(__CommandProcessor);
	// Method assignment
	Gura_AssignMethod(wx_CommandProcessor, __CanUndo);
	Gura_AssignMethod(wx_CommandProcessor, __CanRedo);
	Gura_AssignMethod(wx_CommandProcessor, __ClearCommands);
	Gura_AssignMethod(wx_CommandProcessor, __GetCommands);
	Gura_AssignMethod(wx_CommandProcessor, __GetCurrentCommand);
	Gura_AssignMethod(wx_CommandProcessor, __GetEditMenu);
	Gura_AssignMethod(wx_CommandProcessor, __GetMaxCommands);
	Gura_AssignMethod(wx_CommandProcessor, __GetRedoAccelerator);
	Gura_AssignMethod(wx_CommandProcessor, __GetRedoMenuLabel);
	Gura_AssignMethod(wx_CommandProcessor, __GetUndoAccelerator);
	Gura_AssignMethod(wx_CommandProcessor, __GetUndoMenuLabel);
	Gura_AssignMethod(wx_CommandProcessor, __Initialize);
	Gura_AssignMethod(wx_CommandProcessor, __IsDirty);
	Gura_AssignMethod(wx_CommandProcessor, __MarkAsSaved);
	Gura_AssignMethod(wx_CommandProcessor, __Redo);
	Gura_AssignMethod(wx_CommandProcessor, __SetEditMenu);
	Gura_AssignMethod(wx_CommandProcessor, __SetMenuStrings);
	Gura_AssignMethod(wx_CommandProcessor, __SetRedoAccelerator);
	Gura_AssignMethod(wx_CommandProcessor, __SetUndoAccelerator);
	Gura_AssignMethod(wx_CommandProcessor, __Submit);
	Gura_AssignMethod(wx_CommandProcessor, __Store);
	Gura_AssignMethod(wx_CommandProcessor, __Undo);
}

Gura_ImplementDescendantCreator(wx_CommandProcessor)
{
	return new Object_wx_CommandProcessor((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
