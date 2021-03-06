//----------------------------------------------------------------------------
// wxInputStream
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Gura interfaces for wxInputStream
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Object implementation for wxInputStream
//----------------------------------------------------------------------------
Object_wx_InputStream::~Object_wx_InputStream()
{
}

Object *Object_wx_InputStream::Clone() const
{
	return nullptr;
}

String Object_wx_InputStream::ToString(bool exprFlag)
{
	String rtn("<wx.InputStream:");
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
Gura_DeclareFunctionAlias(__InputStream, "InputStream")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	SetClassToConstruct(Gura_UserClass(wx_InputStream));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(__InputStream)
{
	//wxInputStream();
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Method implementation
//----------------------------------------------------------------------------
Gura_DeclareMethodAlias(wx_InputStream, __CanRead, "CanRead")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_InputStream, __CanRead)
{
	Object_wx_InputStream *pThis = Object_wx_InputStream::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//bool _rtn = pThis->GetEntity()->CanRead();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_InputStream, __Eof, "Eof")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_InputStream, __Eof)
{
	Object_wx_InputStream *pThis = Object_wx_InputStream::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//bool _rtn = pThis->GetEntity()->Eof();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_InputStream, __GetC, "GetC")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_InputStream, __GetC)
{
	Object_wx_InputStream *pThis = Object_wx_InputStream::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int _rtn = pThis->GetEntity()->GetC();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_InputStream, __LastRead, "LastRead")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_InputStream, __LastRead)
{
	Object_wx_InputStream *pThis = Object_wx_InputStream::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//size_t _rtn = pThis->GetEntity()->LastRead();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_InputStream, __Peek, "Peek")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_InputStream, __Peek)
{
	Object_wx_InputStream *pThis = Object_wx_InputStream::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//char _rtn = pThis->GetEntity()->Peek();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_InputStream, __Read, "Read")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "buffer", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "size", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_InputStream, __Read)
{
	Object_wx_InputStream *pThis = Object_wx_InputStream::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//void* buffer = arg.GetNumber(0)
	//size_t size = arg.GetNumber(1)
	//wxInputStream& _rtn = pThis->GetEntity()->Read(buffer, size);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_InputStream, __Read_1, "Read_1")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "stream_out", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_InputStream, __Read_1)
{
	Object_wx_InputStream *pThis = Object_wx_InputStream::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxOutputStream& stream_out = arg.GetNumber(0)
	//wxInputStream& _rtn = pThis->GetEntity()->Read(stream_out);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_InputStream, __ReadAll, "ReadAll")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "buffer", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "size", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_InputStream, __ReadAll)
{
	Object_wx_InputStream *pThis = Object_wx_InputStream::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//void* buffer = arg.GetNumber(0)
	//size_t size = arg.GetNumber(1)
	//bool _rtn = pThis->GetEntity()->ReadAll(buffer, size);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_InputStream, __SeekI, "SeekI")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "pos", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "mode", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_InputStream, __SeekI)
{
	Object_wx_InputStream *pThis = Object_wx_InputStream::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxFileOffset pos = arg.GetNumber(0)
	//wxSeekMode mode = arg.GetNumber(1)
	//wxFileOffset _rtn = pThis->GetEntity()->SeekI(pos, mode);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_InputStream, __TellI, "TellI")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_InputStream, __TellI)
{
	Object_wx_InputStream *pThis = Object_wx_InputStream::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxFileOffset _rtn = pThis->GetEntity()->TellI();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_InputStream, __Ungetch, "Ungetch")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "buffer", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "size", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_InputStream, __Ungetch)
{
	Object_wx_InputStream *pThis = Object_wx_InputStream::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const void* buffer = arg.GetNumber(0)
	//size_t size = arg.GetNumber(1)
	//size_t _rtn = pThis->GetEntity()->Ungetch(buffer, size);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_InputStream, __Ungetch_1, "Ungetch_1")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "c", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_InputStream, __Ungetch_1)
{
	Object_wx_InputStream *pThis = Object_wx_InputStream::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//char c = arg.GetNumber(0)
	//bool _rtn = pThis->GetEntity()->Ungetch(c);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_InputStream, __OnSysRead, "OnSysRead")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "buffer", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "bufsize", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_InputStream, __OnSysRead)
{
	Object_wx_InputStream *pThis = Object_wx_InputStream::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//void* buffer = arg.GetNumber(0)
	//size_t bufsize = arg.GetNumber(1)
	//size_t _rtn = pThis->GetEntity()->OnSysRead(buffer, bufsize);
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Class implementation for wxInputStream
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_InputStream)
{
	// Constructor assignment
	Gura_AssignFunction(__InputStream);
	// Method assignment
	Gura_AssignMethod(wx_InputStream, __CanRead);
	Gura_AssignMethod(wx_InputStream, __Eof);
	Gura_AssignMethod(wx_InputStream, __GetC);
	Gura_AssignMethod(wx_InputStream, __LastRead);
	Gura_AssignMethod(wx_InputStream, __Peek);
	Gura_AssignMethod(wx_InputStream, __Read);
	Gura_AssignMethod(wx_InputStream, __Read_1);
	Gura_AssignMethod(wx_InputStream, __ReadAll);
	Gura_AssignMethod(wx_InputStream, __SeekI);
	Gura_AssignMethod(wx_InputStream, __TellI);
	Gura_AssignMethod(wx_InputStream, __Ungetch);
	Gura_AssignMethod(wx_InputStream, __Ungetch_1);
	Gura_AssignMethod(wx_InputStream, __OnSysRead);
}

Gura_ImplementDescendantCreator(wx_InputStream)
{
	return new Object_wx_InputStream((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
