//----------------------------------------------------------------------------
// wxArchiveClassFactory
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Gura interfaces for wxArchiveClassFactory
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Object implementation for wxArchiveClassFactory
//----------------------------------------------------------------------------
Object_wx_ArchiveClassFactory::~Object_wx_ArchiveClassFactory()
{
}

Object *Object_wx_ArchiveClassFactory::Clone() const
{
	return nullptr;
}

String Object_wx_ArchiveClassFactory::ToString(bool exprFlag)
{
	String rtn("<wx.ArchiveClassFactory:");
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
Gura_DeclareMethodAlias(wx_ArchiveClassFactory, __CanHandle, "CanHandle")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "protocol", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "type", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_ArchiveClassFactory, __CanHandle)
{
	Object_wx_ArchiveClassFactory *pThis = Object_wx_ArchiveClassFactory::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxString& protocol = arg.GetNumber(0)
	//wxStreamProtocolType type = arg.GetNumber(1)
	//bool _rtn = pThis->GetEntity()->CanHandle(protocol, type);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_ArchiveClassFactory, __Find, "Find")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "protocol", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "type", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_ArchiveClassFactory, __Find)
{
	Object_wx_ArchiveClassFactory *pThis = Object_wx_ArchiveClassFactory::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxString& protocol = arg.GetNumber(0)
	//wxStreamProtocolType type = arg.GetNumber(1)
	//const wxArchiveClassFactory* _rtn = pThis->GetEntity()->Find(protocol, type);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_ArchiveClassFactory, __GetConv, "GetConv")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_ArchiveClassFactory, __GetConv)
{
	Object_wx_ArchiveClassFactory *pThis = Object_wx_ArchiveClassFactory::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxMBConv& _rtn = pThis->GetEntity()->GetConv();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_ArchiveClassFactory, __SetConv, "SetConv")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "conv", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_ArchiveClassFactory, __SetConv)
{
	Object_wx_ArchiveClassFactory *pThis = Object_wx_ArchiveClassFactory::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxMBConv& conv = arg.GetNumber(0)
	//pThis->GetEntity()->SetConv(conv);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_ArchiveClassFactory, __GetFirst, "GetFirst")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_ArchiveClassFactory, __GetFirst)
{
	Object_wx_ArchiveClassFactory *pThis = Object_wx_ArchiveClassFactory::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxArchiveClassFactory* _rtn = pThis->GetEntity()->GetFirst();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_ArchiveClassFactory, __GetNext, "GetNext")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_ArchiveClassFactory, __GetNext)
{
	Object_wx_ArchiveClassFactory *pThis = Object_wx_ArchiveClassFactory::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxArchiveClassFactory* _rtn = pThis->GetEntity()->GetNext();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_ArchiveClassFactory, __GetInternalName, "GetInternalName")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "name", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "format", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_ArchiveClassFactory, __GetInternalName)
{
	Object_wx_ArchiveClassFactory *pThis = Object_wx_ArchiveClassFactory::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxString& name = arg.GetNumber(0)
	//wxPathFormat format = arg.GetNumber(1)
	//wxString _rtn = pThis->GetEntity()->GetInternalName(name, format);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_ArchiveClassFactory, __GetProtocol, "GetProtocol")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_ArchiveClassFactory, __GetProtocol)
{
	Object_wx_ArchiveClassFactory *pThis = Object_wx_ArchiveClassFactory::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxString _rtn = pThis->GetEntity()->GetProtocol();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_ArchiveClassFactory, __GetProtocols, "GetProtocols")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "type", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_ArchiveClassFactory, __GetProtocols)
{
	Object_wx_ArchiveClassFactory *pThis = Object_wx_ArchiveClassFactory::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxStreamProtocolType type = arg.GetNumber(0)
	//const wxChar** _rtn = pThis->GetEntity()->GetProtocols(type);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_ArchiveClassFactory, __NewEntry, "NewEntry")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_ArchiveClassFactory, __NewEntry)
{
	Object_wx_ArchiveClassFactory *pThis = Object_wx_ArchiveClassFactory::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxArchiveEntry* _rtn = pThis->GetEntity()->NewEntry();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_ArchiveClassFactory, __NewStream, "NewStream")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "stream", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_ArchiveClassFactory, __NewStream)
{
	Object_wx_ArchiveClassFactory *pThis = Object_wx_ArchiveClassFactory::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxInputStream& stream = arg.GetNumber(0)
	//wxArchiveInputStream* _rtn = pThis->GetEntity()->NewStream(stream);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_ArchiveClassFactory, __NewStream_1, "NewStream_1")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "stream", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_ArchiveClassFactory, __NewStream_1)
{
	Object_wx_ArchiveClassFactory *pThis = Object_wx_ArchiveClassFactory::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxOutputStream& stream = arg.GetNumber(0)
	//wxArchiveOutputStream* _rtn = pThis->GetEntity()->NewStream(stream);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_ArchiveClassFactory, __NewStream_2, "NewStream_2")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "stream", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_ArchiveClassFactory, __NewStream_2)
{
	Object_wx_ArchiveClassFactory *pThis = Object_wx_ArchiveClassFactory::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxInputStream* stream = arg.GetNumber(0)
	//wxArchiveInputStream* _rtn = pThis->GetEntity()->NewStream(stream);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_ArchiveClassFactory, __NewStream_3, "NewStream_3")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "stream", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_ArchiveClassFactory, __NewStream_3)
{
	Object_wx_ArchiveClassFactory *pThis = Object_wx_ArchiveClassFactory::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxOutputStream* stream = arg.GetNumber(0)
	//wxArchiveOutputStream* _rtn = pThis->GetEntity()->NewStream(stream);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_ArchiveClassFactory, __PushFront, "PushFront")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_ArchiveClassFactory, __PushFront)
{
	Object_wx_ArchiveClassFactory *pThis = Object_wx_ArchiveClassFactory::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->PushFront();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_ArchiveClassFactory, __Remove, "Remove")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_ArchiveClassFactory, __Remove)
{
	Object_wx_ArchiveClassFactory *pThis = Object_wx_ArchiveClassFactory::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->Remove();
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Class implementation for wxArchiveClassFactory
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_ArchiveClassFactory)
{
	// Class assignment
	Gura_AssignValueEx("ArchiveClassFactory", Reference());
	// Method assignment
	Gura_AssignMethod(wx_ArchiveClassFactory, __CanHandle);
	Gura_AssignMethod(wx_ArchiveClassFactory, __Find);
	Gura_AssignMethod(wx_ArchiveClassFactory, __GetConv);
	Gura_AssignMethod(wx_ArchiveClassFactory, __SetConv);
	Gura_AssignMethod(wx_ArchiveClassFactory, __GetFirst);
	Gura_AssignMethod(wx_ArchiveClassFactory, __GetNext);
	Gura_AssignMethod(wx_ArchiveClassFactory, __GetInternalName);
	Gura_AssignMethod(wx_ArchiveClassFactory, __GetProtocol);
	Gura_AssignMethod(wx_ArchiveClassFactory, __GetProtocols);
	Gura_AssignMethod(wx_ArchiveClassFactory, __NewEntry);
	Gura_AssignMethod(wx_ArchiveClassFactory, __NewStream);
	Gura_AssignMethod(wx_ArchiveClassFactory, __NewStream_1);
	Gura_AssignMethod(wx_ArchiveClassFactory, __NewStream_2);
	Gura_AssignMethod(wx_ArchiveClassFactory, __NewStream_3);
	Gura_AssignMethod(wx_ArchiveClassFactory, __PushFront);
	Gura_AssignMethod(wx_ArchiveClassFactory, __Remove);
}

Gura_ImplementDescendantCreator(wx_ArchiveClassFactory)
{
	return new Object_wx_ArchiveClassFactory((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
