//----------------------------------------------------------------------------
// wxArchiveEntry
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Gura interfaces for wxArchiveEntry
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Object implementation for wxArchiveEntry
//----------------------------------------------------------------------------
Object_wx_ArchiveEntry::~Object_wx_ArchiveEntry()
{
}

Object *Object_wx_ArchiveEntry::Clone() const
{
	return nullptr;
}

String Object_wx_ArchiveEntry::ToString(bool exprFlag)
{
	String rtn("<wx.ArchiveEntry:");
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
Gura_DeclareMethodAlias(wx_ArchiveEntry, __Clone, "Clone")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_ArchiveEntry, __Clone)
{
	Object_wx_ArchiveEntry *pThis = Object_wx_ArchiveEntry::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxArchiveEntry* _rtn = pThis->GetEntity()->Clone();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_ArchiveEntry, __GetDateTime, "GetDateTime")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_ArchiveEntry, __GetDateTime)
{
	Object_wx_ArchiveEntry *pThis = Object_wx_ArchiveEntry::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxDateTime _rtn = pThis->GetEntity()->GetDateTime();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_ArchiveEntry, __SetDateTime, "SetDateTime")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "dt", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_ArchiveEntry, __SetDateTime)
{
	Object_wx_ArchiveEntry *pThis = Object_wx_ArchiveEntry::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxDateTime& dt = arg.GetNumber(0)
	//pThis->GetEntity()->SetDateTime(dt);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_ArchiveEntry, __GetName, "GetName")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "format", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_ArchiveEntry, __GetName)
{
	Object_wx_ArchiveEntry *pThis = Object_wx_ArchiveEntry::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxPathFormat format = arg.GetNumber(0)
	//wxString _rtn = pThis->GetEntity()->GetName(format);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_ArchiveEntry, __SetName, "SetName")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "name", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "format", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_ArchiveEntry, __SetName)
{
	Object_wx_ArchiveEntry *pThis = Object_wx_ArchiveEntry::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxString& name = arg.GetNumber(0)
	//wxPathFormat format = arg.GetNumber(1)
	//pThis->GetEntity()->SetName(name, format);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_ArchiveEntry, __GetSize, "GetSize")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_ArchiveEntry, __GetSize)
{
	Object_wx_ArchiveEntry *pThis = Object_wx_ArchiveEntry::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxFileOffset _rtn = pThis->GetEntity()->GetSize();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_ArchiveEntry, __SetSize, "SetSize")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "size", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_ArchiveEntry, __SetSize)
{
	Object_wx_ArchiveEntry *pThis = Object_wx_ArchiveEntry::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxFileOffset size = arg.GetNumber(0)
	//pThis->GetEntity()->SetSize(size);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_ArchiveEntry, __GetInternalFormat, "GetInternalFormat")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_ArchiveEntry, __GetInternalFormat)
{
	Object_wx_ArchiveEntry *pThis = Object_wx_ArchiveEntry::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxPathFormat _rtn = pThis->GetEntity()->GetInternalFormat();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_ArchiveEntry, __GetInternalName, "GetInternalName")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_ArchiveEntry, __GetInternalName)
{
	Object_wx_ArchiveEntry *pThis = Object_wx_ArchiveEntry::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxString _rtn = pThis->GetEntity()->GetInternalName();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_ArchiveEntry, __GetOffset, "GetOffset")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_ArchiveEntry, __GetOffset)
{
	Object_wx_ArchiveEntry *pThis = Object_wx_ArchiveEntry::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxFileOffset _rtn = pThis->GetEntity()->GetOffset();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_ArchiveEntry, __IsDir, "IsDir")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_ArchiveEntry, __IsDir)
{
	Object_wx_ArchiveEntry *pThis = Object_wx_ArchiveEntry::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//bool _rtn = pThis->GetEntity()->IsDir();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_ArchiveEntry, __SetIsDir, "SetIsDir")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "isDir", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_ArchiveEntry, __SetIsDir)
{
	Object_wx_ArchiveEntry *pThis = Object_wx_ArchiveEntry::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//bool isDir = arg.GetNumber(0)
	//pThis->GetEntity()->SetIsDir(isDir);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_ArchiveEntry, __IsReadOnly, "IsReadOnly")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_ArchiveEntry, __IsReadOnly)
{
	Object_wx_ArchiveEntry *pThis = Object_wx_ArchiveEntry::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//bool _rtn = pThis->GetEntity()->IsReadOnly();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_ArchiveEntry, __SetIsReadOnly, "SetIsReadOnly")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "isReadOnly", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_ArchiveEntry, __SetIsReadOnly)
{
	Object_wx_ArchiveEntry *pThis = Object_wx_ArchiveEntry::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//bool isReadOnly = arg.GetNumber(0)
	//pThis->GetEntity()->SetIsReadOnly(isReadOnly);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_ArchiveEntry, __SetNotifier, "SetNotifier")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "notifier", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_ArchiveEntry, __SetNotifier)
{
	Object_wx_ArchiveEntry *pThis = Object_wx_ArchiveEntry::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxArchiveNotifier& notifier = arg.GetNumber(0)
	//pThis->GetEntity()->SetNotifier(notifier);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_ArchiveEntry, __UnsetNotifier, "UnsetNotifier")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_ArchiveEntry, __UnsetNotifier)
{
	Object_wx_ArchiveEntry *pThis = Object_wx_ArchiveEntry::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->UnsetNotifier();
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Class implementation for wxArchiveEntry
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_ArchiveEntry)
{
	// Class assignment
	Gura_AssignValueEx("ArchiveEntry", Reference());
	// Method assignment
	Gura_AssignMethod(wx_ArchiveEntry, __Clone);
	Gura_AssignMethod(wx_ArchiveEntry, __GetDateTime);
	Gura_AssignMethod(wx_ArchiveEntry, __SetDateTime);
	Gura_AssignMethod(wx_ArchiveEntry, __GetName);
	Gura_AssignMethod(wx_ArchiveEntry, __SetName);
	Gura_AssignMethod(wx_ArchiveEntry, __GetSize);
	Gura_AssignMethod(wx_ArchiveEntry, __SetSize);
	Gura_AssignMethod(wx_ArchiveEntry, __GetInternalFormat);
	Gura_AssignMethod(wx_ArchiveEntry, __GetInternalName);
	Gura_AssignMethod(wx_ArchiveEntry, __GetOffset);
	Gura_AssignMethod(wx_ArchiveEntry, __IsDir);
	Gura_AssignMethod(wx_ArchiveEntry, __SetIsDir);
	Gura_AssignMethod(wx_ArchiveEntry, __IsReadOnly);
	Gura_AssignMethod(wx_ArchiveEntry, __SetIsReadOnly);
	Gura_AssignMethod(wx_ArchiveEntry, __SetNotifier);
	Gura_AssignMethod(wx_ArchiveEntry, __UnsetNotifier);
}

Gura_ImplementDescendantCreator(wx_ArchiveEntry)
{
	return new Object_wx_ArchiveEntry((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
