//----------------------------------------------------------------------------
// wxLog
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Gura interfaces for wxLog
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Object implementation for wxLog
//----------------------------------------------------------------------------
Object_wx_Log::~Object_wx_Log()
{
}

Object *Object_wx_Log::Clone() const
{
	return nullptr;
}

String Object_wx_Log::ToString(bool exprFlag)
{
	String rtn("<wx.Log:");
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
Gura_DeclareMethodAlias(wx_Log, __AddTraceMask, "AddTraceMask")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "mask", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Log, __AddTraceMask)
{
	Object_wx_Log *pThis = Object_wx_Log::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxString& mask = arg.GetNumber(0)
	//pThis->GetEntity()->AddTraceMask(mask);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Log, __ClearTraceMasks, "ClearTraceMasks")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_Log, __ClearTraceMasks)
{
	Object_wx_Log *pThis = Object_wx_Log::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->ClearTraceMasks();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Log, __GetTraceMasks, "GetTraceMasks")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_Log, __GetTraceMasks)
{
	Object_wx_Log *pThis = Object_wx_Log::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxArrayString& _rtn = pThis->GetEntity()->GetTraceMasks();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Log, __IsAllowedTraceMask, "IsAllowedTraceMask")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "mask", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Log, __IsAllowedTraceMask)
{
	Object_wx_Log *pThis = Object_wx_Log::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxString& mask = arg.GetNumber(0)
	//bool _rtn = pThis->GetEntity()->IsAllowedTraceMask(mask);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Log, __RemoveTraceMask, "RemoveTraceMask")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "mask", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Log, __RemoveTraceMask)
{
	Object_wx_Log *pThis = Object_wx_Log::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxString& mask = arg.GetNumber(0)
	//pThis->GetEntity()->RemoveTraceMask(mask);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Log, __DontCreateOnDemand, "DontCreateOnDemand")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_Log, __DontCreateOnDemand)
{
	Object_wx_Log *pThis = Object_wx_Log::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->DontCreateOnDemand();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Log, __GetActiveTarget, "GetActiveTarget")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_Log, __GetActiveTarget)
{
	Object_wx_Log *pThis = Object_wx_Log::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxLog* _rtn = pThis->GetEntity()->GetActiveTarget();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Log, __SetActiveTarget, "SetActiveTarget")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "logtarget", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Log, __SetActiveTarget)
{
	Object_wx_Log *pThis = Object_wx_Log::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxLog* logtarget = arg.GetNumber(0)
	//wxLog* _rtn = pThis->GetEntity()->SetActiveTarget(logtarget);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Log, __SetThreadActiveTarget, "SetThreadActiveTarget")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "logger", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Log, __SetThreadActiveTarget)
{
	Object_wx_Log *pThis = Object_wx_Log::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxLog* logger = arg.GetNumber(0)
	//wxLog* _rtn = pThis->GetEntity()->SetThreadActiveTarget(logger);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Log, __FlushActive, "FlushActive")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_Log, __FlushActive)
{
	Object_wx_Log *pThis = Object_wx_Log::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->FlushActive();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Log, __Resume, "Resume")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_Log, __Resume)
{
	Object_wx_Log *pThis = Object_wx_Log::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->Resume();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Log, __Suspend, "Suspend")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_Log, __Suspend)
{
	Object_wx_Log *pThis = Object_wx_Log::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->Suspend();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Log, __GetLogLevel, "GetLogLevel")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_Log, __GetLogLevel)
{
	Object_wx_Log *pThis = Object_wx_Log::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxLogLevel _rtn = pThis->GetEntity()->GetLogLevel();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Log, __IsLevelEnabled, "IsLevelEnabled")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "level", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "component", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Log, __IsLevelEnabled)
{
	Object_wx_Log *pThis = Object_wx_Log::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxLogLevel level = arg.GetNumber(0)
	//wxString component = arg.GetNumber(1)
	//bool _rtn = pThis->GetEntity()->IsLevelEnabled(level, component);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Log, __SetComponentLevel, "SetComponentLevel")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "component", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "level", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Log, __SetComponentLevel)
{
	Object_wx_Log *pThis = Object_wx_Log::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxString& component = arg.GetNumber(0)
	//wxLogLevel level = arg.GetNumber(1)
	//pThis->GetEntity()->SetComponentLevel(component, level);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Log, __SetLogLevel, "SetLogLevel")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "logLevel", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Log, __SetLogLevel)
{
	Object_wx_Log *pThis = Object_wx_Log::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxLogLevel logLevel = arg.GetNumber(0)
	//pThis->GetEntity()->SetLogLevel(logLevel);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Log, __EnableLogging, "EnableLogging")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "enable", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Log, __EnableLogging)
{
	Object_wx_Log *pThis = Object_wx_Log::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//bool enable = arg.GetNumber(0)
	//bool _rtn = pThis->GetEntity()->EnableLogging(enable);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Log, __IsEnabled, "IsEnabled")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_Log, __IsEnabled)
{
	Object_wx_Log *pThis = Object_wx_Log::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//bool _rtn = pThis->GetEntity()->IsEnabled();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Log, __GetRepetitionCounting, "GetRepetitionCounting")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_Log, __GetRepetitionCounting)
{
	Object_wx_Log *pThis = Object_wx_Log::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//bool _rtn = pThis->GetEntity()->GetRepetitionCounting();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Log, __SetRepetitionCounting, "SetRepetitionCounting")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "repetCounting", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Log, __SetRepetitionCounting)
{
	Object_wx_Log *pThis = Object_wx_Log::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//bool repetCounting = arg.GetNumber(0)
	//pThis->GetEntity()->SetRepetitionCounting(repetCounting);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Log, __GetTimestamp, "GetTimestamp")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_Log, __GetTimestamp)
{
	Object_wx_Log *pThis = Object_wx_Log::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxString& _rtn = pThis->GetEntity()->GetTimestamp();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Log, __SetTimestamp, "SetTimestamp")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "format", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Log, __SetTimestamp)
{
	Object_wx_Log *pThis = Object_wx_Log::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxString& format = arg.GetNumber(0)
	//pThis->GetEntity()->SetTimestamp(format);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Log, __DisableTimestamp, "DisableTimestamp")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_Log, __DisableTimestamp)
{
	Object_wx_Log *pThis = Object_wx_Log::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->DisableTimestamp();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Log, __GetVerbose, "GetVerbose")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_Log, __GetVerbose)
{
	Object_wx_Log *pThis = Object_wx_Log::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//bool _rtn = pThis->GetEntity()->GetVerbose();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Log, __SetVerbose, "SetVerbose")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "verbose", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Log, __SetVerbose)
{
	Object_wx_Log *pThis = Object_wx_Log::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//bool verbose = arg.GetNumber(0)
	//pThis->GetEntity()->SetVerbose(verbose);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Log, __SetFormatter, "SetFormatter")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "formatter", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Log, __SetFormatter)
{
	Object_wx_Log *pThis = Object_wx_Log::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxLogFormatter* formatter = arg.GetNumber(0)
	//wxLogFormatter* _rtn = pThis->GetEntity()->SetFormatter(formatter);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Log, __Flush, "Flush")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_Log, __Flush)
{
	Object_wx_Log *pThis = Object_wx_Log::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->Flush();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Log, __LogRecord, "LogRecord")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "level", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "msg", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "info", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Log, __LogRecord)
{
	Object_wx_Log *pThis = Object_wx_Log::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxLogLevel level = arg.GetNumber(0)
	//const wxString& msg = arg.GetNumber(1)
	//const wxLogRecordInfo& info = arg.GetNumber(2)
	//pThis->GetEntity()->LogRecord(level, msg, info);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Log, __DoLogRecord, "DoLogRecord")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "level", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "msg", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "info", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Log, __DoLogRecord)
{
	Object_wx_Log *pThis = Object_wx_Log::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxLogLevel level = arg.GetNumber(0)
	//const wxString& msg = arg.GetNumber(1)
	//const wxLogRecordInfo& info = arg.GetNumber(2)
	//pThis->GetEntity()->DoLogRecord(level, msg, info);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Log, __DoLogTextAtLevel, "DoLogTextAtLevel")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "level", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "msg", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Log, __DoLogTextAtLevel)
{
	Object_wx_Log *pThis = Object_wx_Log::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxLogLevel level = arg.GetNumber(0)
	//const wxString& msg = arg.GetNumber(1)
	//pThis->GetEntity()->DoLogTextAtLevel(level, msg);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_Log, __DoLogText, "DoLogText")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "msg", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Log, __DoLogText)
{
	Object_wx_Log *pThis = Object_wx_Log::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxString& msg = arg.GetNumber(0)
	//pThis->GetEntity()->DoLogText(msg);
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Class implementation for wxLog
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_Log)
{
	// Class assignment
	Gura_AssignValueEx("Log", Reference());
	// Method assignment
	Gura_AssignMethod(wx_Log, __AddTraceMask);
	Gura_AssignMethod(wx_Log, __ClearTraceMasks);
	Gura_AssignMethod(wx_Log, __GetTraceMasks);
	Gura_AssignMethod(wx_Log, __IsAllowedTraceMask);
	Gura_AssignMethod(wx_Log, __RemoveTraceMask);
	Gura_AssignMethod(wx_Log, __DontCreateOnDemand);
	Gura_AssignMethod(wx_Log, __GetActiveTarget);
	Gura_AssignMethod(wx_Log, __SetActiveTarget);
	Gura_AssignMethod(wx_Log, __SetThreadActiveTarget);
	Gura_AssignMethod(wx_Log, __FlushActive);
	Gura_AssignMethod(wx_Log, __Resume);
	Gura_AssignMethod(wx_Log, __Suspend);
	Gura_AssignMethod(wx_Log, __GetLogLevel);
	Gura_AssignMethod(wx_Log, __IsLevelEnabled);
	Gura_AssignMethod(wx_Log, __SetComponentLevel);
	Gura_AssignMethod(wx_Log, __SetLogLevel);
	Gura_AssignMethod(wx_Log, __EnableLogging);
	Gura_AssignMethod(wx_Log, __IsEnabled);
	Gura_AssignMethod(wx_Log, __GetRepetitionCounting);
	Gura_AssignMethod(wx_Log, __SetRepetitionCounting);
	Gura_AssignMethod(wx_Log, __GetTimestamp);
	Gura_AssignMethod(wx_Log, __SetTimestamp);
	Gura_AssignMethod(wx_Log, __DisableTimestamp);
	Gura_AssignMethod(wx_Log, __GetVerbose);
	Gura_AssignMethod(wx_Log, __SetVerbose);
	Gura_AssignMethod(wx_Log, __SetFormatter);
	Gura_AssignMethod(wx_Log, __Flush);
	Gura_AssignMethod(wx_Log, __LogRecord);
	Gura_AssignMethod(wx_Log, __DoLogRecord);
	Gura_AssignMethod(wx_Log, __DoLogTextAtLevel);
	Gura_AssignMethod(wx_Log, __DoLogText);
}

Gura_ImplementDescendantCreator(wx_Log)
{
	return new Object_wx_Log((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
