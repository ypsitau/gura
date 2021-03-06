//----------------------------------------------------------------------------
// wxDebugContext
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Gura interfaces for wxDebugContext
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Object implementation for wxDebugContext
//----------------------------------------------------------------------------
Object_wx_DebugContext::~Object_wx_DebugContext()
{
}

Object *Object_wx_DebugContext::Clone() const
{
	return nullptr;
}

String Object_wx_DebugContext::ToString(bool exprFlag)
{
	String rtn("<wx.DebugContext:");
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
Gura_DeclareMethodAlias(wx_DebugContext, __Check, "Check")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "checkAll", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_DebugContext, __Check)
{
	Object_wx_DebugContext *pThis = Object_wx_DebugContext::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//bool checkAll = arg.GetNumber(0)
	//int _rtn = pThis->GetEntity()->Check(checkAll);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_DebugContext, __Dump, "Dump")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_DebugContext, __Dump)
{
	Object_wx_DebugContext *pThis = Object_wx_DebugContext::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//bool _rtn = pThis->GetEntity()->Dump();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_DebugContext, __GetCheckPrevious, "GetCheckPrevious")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_DebugContext, __GetCheckPrevious)
{
	Object_wx_DebugContext *pThis = Object_wx_DebugContext::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//bool _rtn = pThis->GetEntity()->GetCheckPrevious();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_DebugContext, __GetDebugMode, "GetDebugMode")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_DebugContext, __GetDebugMode)
{
	Object_wx_DebugContext *pThis = Object_wx_DebugContext::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//bool _rtn = pThis->GetEntity()->GetDebugMode();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_DebugContext, __GetLevel, "GetLevel")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_DebugContext, __GetLevel)
{
	Object_wx_DebugContext *pThis = Object_wx_DebugContext::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int _rtn = pThis->GetEntity()->GetLevel();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_DebugContext, __PrintClasses, "PrintClasses")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_DebugContext, __PrintClasses)
{
	Object_wx_DebugContext *pThis = Object_wx_DebugContext::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//bool _rtn = pThis->GetEntity()->PrintClasses();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_DebugContext, __PrintStatistics, "PrintStatistics")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "detailed", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_DebugContext, __PrintStatistics)
{
	Object_wx_DebugContext *pThis = Object_wx_DebugContext::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//bool detailed = arg.GetNumber(0)
	//bool _rtn = pThis->GetEntity()->PrintStatistics(detailed);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_DebugContext, __SetCheckPrevious, "SetCheckPrevious")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "check", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_DebugContext, __SetCheckPrevious)
{
	Object_wx_DebugContext *pThis = Object_wx_DebugContext::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//bool check = arg.GetNumber(0)
	//pThis->GetEntity()->SetCheckPrevious(check);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_DebugContext, __SetCheckpoint, "SetCheckpoint")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "all", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_DebugContext, __SetCheckpoint)
{
	Object_wx_DebugContext *pThis = Object_wx_DebugContext::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//bool all = arg.GetNumber(0)
	//pThis->GetEntity()->SetCheckpoint(all);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_DebugContext, __SetDebugMode, "SetDebugMode")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "debug", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_DebugContext, __SetDebugMode)
{
	Object_wx_DebugContext *pThis = Object_wx_DebugContext::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//bool debug = arg.GetNumber(0)
	//pThis->GetEntity()->SetDebugMode(debug);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_DebugContext, __SetLevel, "SetLevel")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "level", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_DebugContext, __SetLevel)
{
	Object_wx_DebugContext *pThis = Object_wx_DebugContext::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int level = arg.GetNumber(0)
	//pThis->GetEntity()->SetLevel(level);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_DebugContext, __SetShutdownNotifyFunction, "SetShutdownNotifyFunction")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "func", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_DebugContext, __SetShutdownNotifyFunction)
{
	Object_wx_DebugContext *pThis = Object_wx_DebugContext::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxShutdownNotifyFunction func = arg.GetNumber(0)
	//pThis->GetEntity()->SetShutdownNotifyFunction(func);
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Class implementation for wxDebugContext
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_DebugContext)
{
	// Class assignment
	Gura_AssignValueEx("DebugContext", Reference());
	// Method assignment
	Gura_AssignMethod(wx_DebugContext, __Check);
	Gura_AssignMethod(wx_DebugContext, __Dump);
	Gura_AssignMethod(wx_DebugContext, __GetCheckPrevious);
	Gura_AssignMethod(wx_DebugContext, __GetDebugMode);
	Gura_AssignMethod(wx_DebugContext, __GetLevel);
	Gura_AssignMethod(wx_DebugContext, __PrintClasses);
	Gura_AssignMethod(wx_DebugContext, __PrintStatistics);
	Gura_AssignMethod(wx_DebugContext, __SetCheckPrevious);
	Gura_AssignMethod(wx_DebugContext, __SetCheckpoint);
	Gura_AssignMethod(wx_DebugContext, __SetDebugMode);
	Gura_AssignMethod(wx_DebugContext, __SetLevel);
	Gura_AssignMethod(wx_DebugContext, __SetShutdownNotifyFunction);
}

Gura_ImplementDescendantCreator(wx_DebugContext)
{
	return new Object_wx_DebugContext((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
