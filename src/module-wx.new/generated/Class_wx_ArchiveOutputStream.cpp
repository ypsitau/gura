//----------------------------------------------------------------------------
// wxArchiveOutputStream
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Gura interfaces for wxArchiveOutputStream
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Object implementation for wxArchiveOutputStream
//----------------------------------------------------------------------------
Object_wx_ArchiveOutputStream::~Object_wx_ArchiveOutputStream()
{
}

Object *Object_wx_ArchiveOutputStream::Clone() const
{
	return nullptr;
}

String Object_wx_ArchiveOutputStream::ToString(bool exprFlag)
{
	String rtn("<wx.ArchiveOutputStream:");
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
Gura_DeclareMethod(wx_ArchiveOutputStream, ~wxArchiveOutputStream)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_ArchiveOutputStream, ~wxArchiveOutputStream)
{
	Signal &sig = env.GetSignal();
	Object_wx_ArchiveOutputStream *pThis = Object_wx_ArchiveOutputStream::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	//pThis->GetEntity()->~wxArchiveOutputStream();
	return Value::Nil;
}

Gura_DeclareMethod(wx_ArchiveOutputStream, Close)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_ArchiveOutputStream, Close)
{
	Signal &sig = env.GetSignal();
	Object_wx_ArchiveOutputStream *pThis = Object_wx_ArchiveOutputStream::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	//pThis->GetEntity()->Close();
	return Value::Nil;
}

Gura_DeclareMethod(wx_ArchiveOutputStream, CloseEntry)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_ArchiveOutputStream, CloseEntry)
{
	Signal &sig = env.GetSignal();
	Object_wx_ArchiveOutputStream *pThis = Object_wx_ArchiveOutputStream::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	//pThis->GetEntity()->CloseEntry();
	return Value::Nil;
}

Gura_DeclareMethod(wx_ArchiveOutputStream, CopyArchiveMetaData)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "stream", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_ArchiveOutputStream, CopyArchiveMetaData)
{
	Signal &sig = env.GetSignal();
	Object_wx_ArchiveOutputStream *pThis = Object_wx_ArchiveOutputStream::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	//int stream = arg.GetNumber(0)
	//pThis->GetEntity()->CopyArchiveMetaData();
	return Value::Nil;
}

Gura_DeclareMethod(wx_ArchiveOutputStream, CopyEntry)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "entry", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "stream", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_ArchiveOutputStream, CopyEntry)
{
	Signal &sig = env.GetSignal();
	Object_wx_ArchiveOutputStream *pThis = Object_wx_ArchiveOutputStream::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	//int entry = arg.GetNumber(0)
	//int stream = arg.GetNumber(1)
	//pThis->GetEntity()->CopyEntry();
	return Value::Nil;
}

Gura_DeclareMethod(wx_ArchiveOutputStream, PutNextDirEntry)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "name", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "dt", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_ArchiveOutputStream, PutNextDirEntry)
{
	Signal &sig = env.GetSignal();
	Object_wx_ArchiveOutputStream *pThis = Object_wx_ArchiveOutputStream::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	//int name = arg.GetNumber(0)
	//int dt = arg.GetNumber(1)
	//pThis->GetEntity()->PutNextDirEntry();
	return Value::Nil;
}

Gura_DeclareMethod(wx_ArchiveOutputStream, PutNextEntry)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "entry", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_ArchiveOutputStream, PutNextEntry)
{
	Signal &sig = env.GetSignal();
	Object_wx_ArchiveOutputStream *pThis = Object_wx_ArchiveOutputStream::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	//int entry = arg.GetNumber(0)
	//pThis->GetEntity()->PutNextEntry();
	return Value::Nil;
}

Gura_DeclareMethod(wx_ArchiveOutputStream, PutNextEntry_1)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "name", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "dt", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "size", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_ArchiveOutputStream, PutNextEntry_1)
{
	Signal &sig = env.GetSignal();
	Object_wx_ArchiveOutputStream *pThis = Object_wx_ArchiveOutputStream::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	//int name = arg.GetNumber(0)
	//int dt = arg.GetNumber(1)
	//int size = arg.GetNumber(2)
	//pThis->GetEntity()->PutNextEntry();
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Class implementation for wxArchiveOutputStream
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_ArchiveOutputStream)
{
	Gura_AssignMethod(wx_ArchiveOutputStream, ~wxArchiveOutputStream);
	Gura_AssignMethod(wx_ArchiveOutputStream, Close);
	Gura_AssignMethod(wx_ArchiveOutputStream, CloseEntry);
	Gura_AssignMethod(wx_ArchiveOutputStream, CopyArchiveMetaData);
	Gura_AssignMethod(wx_ArchiveOutputStream, CopyEntry);
	Gura_AssignMethod(wx_ArchiveOutputStream, PutNextDirEntry);
	Gura_AssignMethod(wx_ArchiveOutputStream, PutNextEntry);
	Gura_AssignMethod(wx_ArchiveOutputStream, PutNextEntry_1);
}

Gura_ImplementDescendantCreator(wx_ArchiveOutputStream)
{
	return new Object_wx_ArchiveOutputStream((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
