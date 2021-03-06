//----------------------------------------------------------------------------
// wxZlibOutputStream
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Gura interfaces for wxZlibOutputStream
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Object implementation for wxZlibOutputStream
//----------------------------------------------------------------------------
Object_wx_ZlibOutputStream::~Object_wx_ZlibOutputStream()
{
}

Object *Object_wx_ZlibOutputStream::Clone() const
{
	return nullptr;
}

String Object_wx_ZlibOutputStream::ToString(bool exprFlag)
{
	String rtn("<wx.ZlibOutputStream:");
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
Gura_DeclareFunctionAlias(__ZlibOutputStream, "ZlibOutputStream")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "stream", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "level", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "flags", VTYPE_number, OCCUR_Once);
	SetClassToConstruct(Gura_UserClass(wx_ZlibOutputStream));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(__ZlibOutputStream)
{
	//wxOutputStream& stream = arg.GetNumber(0)
	//int level = arg.GetNumber(1)
	//int flags = arg.GetNumber(2)
	//wxZlibOutputStream(stream, level, flags);
	return Value::Nil;
}

Gura_DeclareFunctionAlias(__ZlibOutputStream_1, "ZlibOutputStream_1")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "stream", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "level", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "flags", VTYPE_number, OCCUR_Once);
	SetClassToConstruct(Gura_UserClass(wx_ZlibOutputStream));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(__ZlibOutputStream_1)
{
	//wxOutputStream* stream = arg.GetNumber(0)
	//int level = arg.GetNumber(1)
	//int flags = arg.GetNumber(2)
	//wxZlibOutputStream(stream, level, flags);
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Method implementation
//----------------------------------------------------------------------------
Gura_DeclareMethodAlias(wx_ZlibOutputStream, __CanHandleGZip, "CanHandleGZip")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_ZlibOutputStream, __CanHandleGZip)
{
	Object_wx_ZlibOutputStream *pThis = Object_wx_ZlibOutputStream::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//bool _rtn = pThis->GetEntity()->CanHandleGZip();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_ZlibOutputStream, __SetDictionary, "SetDictionary")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "data", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "datalen", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_ZlibOutputStream, __SetDictionary)
{
	Object_wx_ZlibOutputStream *pThis = Object_wx_ZlibOutputStream::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const char* data = arg.GetNumber(0)
	//size_t datalen = arg.GetNumber(1)
	//bool _rtn = pThis->GetEntity()->SetDictionary(data, datalen);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_ZlibOutputStream, __SetDictionary_1, "SetDictionary_1")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "buf", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_ZlibOutputStream, __SetDictionary_1)
{
	Object_wx_ZlibOutputStream *pThis = Object_wx_ZlibOutputStream::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxMemoryBuffer& buf = arg.GetNumber(0)
	//bool _rtn = pThis->GetEntity()->SetDictionary(buf);
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Class implementation for wxZlibOutputStream
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_ZlibOutputStream)
{
	// Constructor assignment
	Gura_AssignFunction(__ZlibOutputStream);
	Gura_AssignFunction(__ZlibOutputStream_1);
	// Method assignment
	Gura_AssignMethod(wx_ZlibOutputStream, __CanHandleGZip);
	Gura_AssignMethod(wx_ZlibOutputStream, __SetDictionary);
	Gura_AssignMethod(wx_ZlibOutputStream, __SetDictionary_1);
}

Gura_ImplementDescendantCreator(wx_ZlibOutputStream)
{
	return new Object_wx_ZlibOutputStream((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
