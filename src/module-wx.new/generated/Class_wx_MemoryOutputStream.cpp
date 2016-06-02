//----------------------------------------------------------------------------
// wxMemoryOutputStream
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Gura interfaces for wxMemoryOutputStream
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Object implementation for wxMemoryOutputStream
//----------------------------------------------------------------------------
Object_wx_MemoryOutputStream::~Object_wx_MemoryOutputStream()
{
}

Object *Object_wx_MemoryOutputStream::Clone() const
{
	return nullptr;
}

String Object_wx_MemoryOutputStream::ToString(bool exprFlag)
{
	String rtn("<wx.MemoryOutputStream:");
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
Gura_DeclareMethod(wx_MemoryOutputStream, wxMemoryOutputStream)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "data", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "length", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_MemoryOutputStream, wxMemoryOutputStream)
{
	Object_wx_MemoryOutputStream *pThis = Object_wx_MemoryOutputStream::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int data = arg.GetNumber(0)
	//int length = arg.GetNumber(1)
	//pThis->GetEntity()->wxMemoryOutputStream();
	return Value::Nil;
}

Gura_DeclareMethod(wx_MemoryOutputStream, CopyTo)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "buffer", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "len", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_MemoryOutputStream, CopyTo)
{
	Object_wx_MemoryOutputStream *pThis = Object_wx_MemoryOutputStream::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int buffer = arg.GetNumber(0)
	//int len = arg.GetNumber(1)
	//pThis->GetEntity()->CopyTo();
	return Value::Nil;
}

Gura_DeclareMethod(wx_MemoryOutputStream, GetOutputStreamBuffer)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_MemoryOutputStream, GetOutputStreamBuffer)
{
	Object_wx_MemoryOutputStream *pThis = Object_wx_MemoryOutputStream::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->GetOutputStreamBuffer();
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Class implementation for wxMemoryOutputStream
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_MemoryOutputStream)
{
	Gura_AssignMethod(wx_MemoryOutputStream, wxMemoryOutputStream);
	Gura_AssignMethod(wx_MemoryOutputStream, CopyTo);
	Gura_AssignMethod(wx_MemoryOutputStream, GetOutputStreamBuffer);
}

Gura_ImplementDescendantCreator(wx_MemoryOutputStream)
{
	return new Object_wx_MemoryOutputStream((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
