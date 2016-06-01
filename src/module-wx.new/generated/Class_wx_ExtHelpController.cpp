//----------------------------------------------------------------------------
// wxExtHelpController
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Gura interfaces for wxExtHelpController
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Object implementation for wxExtHelpController
//----------------------------------------------------------------------------
Object_wx_ExtHelpController::~Object_wx_ExtHelpController()
{
}

Object *Object_wx_ExtHelpController::Clone() const
{
	return nullptr;
}

String Object_wx_ExtHelpController::ToString(bool exprFlag)
{
	String rtn("<wx.ExtHelpController:");
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
// Method implementation
//----------------------------------------------------------------------------
Gura_DeclareMethod(wx_ExtHelpController, wxExtHelpController)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "parentWindow", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_ExtHelpController, wxExtHelpController)
{
	Signal &sig = env.GetSignal();
	Object_wx_ExtHelpController *pThis = Object_wx_ExtHelpController::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	//int parentWindow = arg.GetNumber(0)
	//pThis->GetEntity()->wxExtHelpController();
	return Value::Nil;
}

Gura_DeclareMethod(wx_ExtHelpController, ~wxExtHelpController)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_ExtHelpController, ~wxExtHelpController)
{
	Signal &sig = env.GetSignal();
	Object_wx_ExtHelpController *pThis = Object_wx_ExtHelpController::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	//pThis->GetEntity()->~wxExtHelpController();
	return Value::Nil;
}

Gura_DeclareMethod(wx_ExtHelpController, SetViewer)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "viewer", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "flags", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_ExtHelpController, SetViewer)
{
	Signal &sig = env.GetSignal();
	Object_wx_ExtHelpController *pThis = Object_wx_ExtHelpController::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	//int viewer = arg.GetNumber(0)
	//int flags = arg.GetNumber(1)
	//pThis->GetEntity()->SetViewer();
	return Value::Nil;
}

Gura_DeclareMethod(wx_ExtHelpController, Initialize)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "dir", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_ExtHelpController, Initialize)
{
	Signal &sig = env.GetSignal();
	Object_wx_ExtHelpController *pThis = Object_wx_ExtHelpController::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	//int dir = arg.GetNumber(0)
	//pThis->GetEntity()->Initialize();
	return Value::Nil;
}

Gura_DeclareMethod(wx_ExtHelpController, LoadFile)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "file", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_ExtHelpController, LoadFile)
{
	Signal &sig = env.GetSignal();
	Object_wx_ExtHelpController *pThis = Object_wx_ExtHelpController::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	//int file = arg.GetNumber(0)
	//pThis->GetEntity()->LoadFile();
	return Value::Nil;
}

Gura_DeclareMethod(wx_ExtHelpController, DisplayContents)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_ExtHelpController, DisplayContents)
{
	Signal &sig = env.GetSignal();
	Object_wx_ExtHelpController *pThis = Object_wx_ExtHelpController::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	//pThis->GetEntity()->DisplayContents();
	return Value::Nil;
}

Gura_DeclareMethod(wx_ExtHelpController, DisplaySection)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "sectionNo", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_ExtHelpController, DisplaySection)
{
	Signal &sig = env.GetSignal();
	Object_wx_ExtHelpController *pThis = Object_wx_ExtHelpController::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	//int sectionNo = arg.GetNumber(0)
	//pThis->GetEntity()->DisplaySection();
	return Value::Nil;
}

Gura_DeclareMethod(wx_ExtHelpController, DisplaySection_1)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "section", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_ExtHelpController, DisplaySection_1)
{
	Signal &sig = env.GetSignal();
	Object_wx_ExtHelpController *pThis = Object_wx_ExtHelpController::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	//int section = arg.GetNumber(0)
	//pThis->GetEntity()->DisplaySection();
	return Value::Nil;
}

Gura_DeclareMethod(wx_ExtHelpController, DisplayBlock)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "blockNo", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_ExtHelpController, DisplayBlock)
{
	Signal &sig = env.GetSignal();
	Object_wx_ExtHelpController *pThis = Object_wx_ExtHelpController::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	//int blockNo = arg.GetNumber(0)
	//pThis->GetEntity()->DisplayBlock();
	return Value::Nil;
}

Gura_DeclareMethod(wx_ExtHelpController, KeywordSearch)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "k", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "mode", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_ExtHelpController, KeywordSearch)
{
	Signal &sig = env.GetSignal();
	Object_wx_ExtHelpController *pThis = Object_wx_ExtHelpController::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	//int k = arg.GetNumber(0)
	//int mode = arg.GetNumber(1)
	//pThis->GetEntity()->KeywordSearch();
	return Value::Nil;
}

Gura_DeclareMethod(wx_ExtHelpController, Quit)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_ExtHelpController, Quit)
{
	Signal &sig = env.GetSignal();
	Object_wx_ExtHelpController *pThis = Object_wx_ExtHelpController::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	//pThis->GetEntity()->Quit();
	return Value::Nil;
}

Gura_DeclareMethod(wx_ExtHelpController, OnQuit)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_ExtHelpController, OnQuit)
{
	Signal &sig = env.GetSignal();
	Object_wx_ExtHelpController *pThis = Object_wx_ExtHelpController::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	//pThis->GetEntity()->OnQuit();
	return Value::Nil;
}

Gura_DeclareMethod(wx_ExtHelpController, DisplayHelp)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "relativeURL", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_ExtHelpController, DisplayHelp)
{
	Signal &sig = env.GetSignal();
	Object_wx_ExtHelpController *pThis = Object_wx_ExtHelpController::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	//int relativeURL = arg.GetNumber(0)
	//pThis->GetEntity()->DisplayHelp();
	return Value::Nil;
}

Gura_DeclareMethod(wx_ExtHelpController, SetFrameParameters)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "titleFormat", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "size", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "pos", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "newFrameEachTime", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_ExtHelpController, SetFrameParameters)
{
	Signal &sig = env.GetSignal();
	Object_wx_ExtHelpController *pThis = Object_wx_ExtHelpController::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	//int titleFormat = arg.GetNumber(0)
	//int size = arg.GetNumber(1)
	//int pos = arg.GetNumber(2)
	//int newFrameEachTime = arg.GetNumber(3)
	//pThis->GetEntity()->SetFrameParameters();
	return Value::Nil;
}

Gura_DeclareMethod(wx_ExtHelpController, GetFrameParameters)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "size", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "pos", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "newFrameEachTime", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_ExtHelpController, GetFrameParameters)
{
	Signal &sig = env.GetSignal();
	Object_wx_ExtHelpController *pThis = Object_wx_ExtHelpController::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	//int size = arg.GetNumber(0)
	//int pos = arg.GetNumber(1)
	//int newFrameEachTime = arg.GetNumber(2)
	//pThis->GetEntity()->GetFrameParameters();
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Class implementation for wxExtHelpController
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_ExtHelpController)
{
	Gura_AssignMethod(wx_ExtHelpController, wxExtHelpController);
	Gura_AssignMethod(wx_ExtHelpController, ~wxExtHelpController);
	Gura_AssignMethod(wx_ExtHelpController, SetViewer);
	Gura_AssignMethod(wx_ExtHelpController, Initialize);
	Gura_AssignMethod(wx_ExtHelpController, LoadFile);
	Gura_AssignMethod(wx_ExtHelpController, DisplayContents);
	Gura_AssignMethod(wx_ExtHelpController, DisplaySection);
	Gura_AssignMethod(wx_ExtHelpController, DisplaySection_1);
	Gura_AssignMethod(wx_ExtHelpController, DisplayBlock);
	Gura_AssignMethod(wx_ExtHelpController, KeywordSearch);
	Gura_AssignMethod(wx_ExtHelpController, Quit);
	Gura_AssignMethod(wx_ExtHelpController, OnQuit);
	Gura_AssignMethod(wx_ExtHelpController, DisplayHelp);
	Gura_AssignMethod(wx_ExtHelpController, SetFrameParameters);
	Gura_AssignMethod(wx_ExtHelpController, GetFrameParameters);
}

Gura_ImplementDescendantCreator(wx_ExtHelpController)
{
	return new Object_wx_ExtHelpController((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
