//----------------------------------------------------------------------------
// wxZipOutputStream
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Gura interfaces for wxZipOutputStream
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Object implementation for wxZipOutputStream
//----------------------------------------------------------------------------
Object_wx_ZipOutputStream::~Object_wx_ZipOutputStream()
{
}

Object *Object_wx_ZipOutputStream::Clone() const
{
	return nullptr;
}

String Object_wx_ZipOutputStream::ToString(bool exprFlag)
{
	String rtn("<wx.ZipOutputStream:");
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
Gura_DeclareFunctionAlias(__ZipOutputStream, "ZipOutputStream")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "stream", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "level", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "conv", VTYPE_number, OCCUR_Once);
	SetClassToConstruct(Gura_UserClass(wx_ZipOutputStream));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(__ZipOutputStream)
{
	//wxOutputStream& stream = arg.GetNumber(0)
	//int level = arg.GetNumber(1)
	//wxMBConv& conv = arg.GetNumber(2)
	//wxZipOutputStream(stream, level, conv);
	return Value::Nil;
}

Gura_DeclareFunctionAlias(__ZipOutputStream_1, "ZipOutputStream_1")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "stream", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "level", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "conv", VTYPE_number, OCCUR_Once);
	SetClassToConstruct(Gura_UserClass(wx_ZipOutputStream));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(__ZipOutputStream_1)
{
	//wxOutputStream* stream = arg.GetNumber(0)
	//int level = arg.GetNumber(1)
	//wxMBConv& conv = arg.GetNumber(2)
	//wxZipOutputStream(stream, level, conv);
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Method implementation
//----------------------------------------------------------------------------
Gura_DeclareMethodAlias(wx_ZipOutputStream, __Close, "Close")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_ZipOutputStream, __Close)
{
	Object_wx_ZipOutputStream *pThis = Object_wx_ZipOutputStream::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//bool _rtn = pThis->GetEntity()->Close();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_ZipOutputStream, __CloseEntry, "CloseEntry")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_ZipOutputStream, __CloseEntry)
{
	Object_wx_ZipOutputStream *pThis = Object_wx_ZipOutputStream::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//bool _rtn = pThis->GetEntity()->CloseEntry();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_ZipOutputStream, __CopyArchiveMetaData, "CopyArchiveMetaData")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "inputStream", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_ZipOutputStream, __CopyArchiveMetaData)
{
	Object_wx_ZipOutputStream *pThis = Object_wx_ZipOutputStream::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxZipInputStream& inputStream = arg.GetNumber(0)
	//bool _rtn = pThis->GetEntity()->CopyArchiveMetaData(inputStream);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_ZipOutputStream, __CopyEntry, "CopyEntry")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "entry", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "inputStream", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_ZipOutputStream, __CopyEntry)
{
	Object_wx_ZipOutputStream *pThis = Object_wx_ZipOutputStream::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxZipEntry* entry = arg.GetNumber(0)
	//wxZipInputStream& inputStream = arg.GetNumber(1)
	//bool _rtn = pThis->GetEntity()->CopyEntry(entry, inputStream);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_ZipOutputStream, __GetLevel, "GetLevel")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_ZipOutputStream, __GetLevel)
{
	Object_wx_ZipOutputStream *pThis = Object_wx_ZipOutputStream::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int _rtn = pThis->GetEntity()->GetLevel();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_ZipOutputStream, __SetLevel, "SetLevel")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "level", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_ZipOutputStream, __SetLevel)
{
	Object_wx_ZipOutputStream *pThis = Object_wx_ZipOutputStream::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int level = arg.GetNumber(0)
	//pThis->GetEntity()->SetLevel(level);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_ZipOutputStream, __PutNextDirEntry, "PutNextDirEntry")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "name", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "dt", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_ZipOutputStream, __PutNextDirEntry)
{
	Object_wx_ZipOutputStream *pThis = Object_wx_ZipOutputStream::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxString& name = arg.GetNumber(0)
	//const wxDateTime& dt = arg.GetNumber(1)
	//bool _rtn = pThis->GetEntity()->PutNextDirEntry(name, dt);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_ZipOutputStream, __PutNextEntry, "PutNextEntry")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "entry", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_ZipOutputStream, __PutNextEntry)
{
	Object_wx_ZipOutputStream *pThis = Object_wx_ZipOutputStream::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxZipEntry* entry = arg.GetNumber(0)
	//bool _rtn = pThis->GetEntity()->PutNextEntry(entry);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_ZipOutputStream, __PutNextEntry_1, "PutNextEntry_1")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "name", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "dt", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "size", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_ZipOutputStream, __PutNextEntry_1)
{
	Object_wx_ZipOutputStream *pThis = Object_wx_ZipOutputStream::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxString& name = arg.GetNumber(0)
	//const wxDateTime& dt = arg.GetNumber(1)
	//wxFileOffset size = arg.GetNumber(2)
	//bool _rtn = pThis->GetEntity()->PutNextEntry(name, dt, size);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_ZipOutputStream, __SetComment, "SetComment")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "comment", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_ZipOutputStream, __SetComment)
{
	Object_wx_ZipOutputStream *pThis = Object_wx_ZipOutputStream::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxString& comment = arg.GetNumber(0)
	//pThis->GetEntity()->SetComment(comment);
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Class implementation for wxZipOutputStream
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_ZipOutputStream)
{
	// Constructor assignment
	Gura_AssignFunction(__ZipOutputStream);
	Gura_AssignFunction(__ZipOutputStream_1);
	// Method assignment
	Gura_AssignMethod(wx_ZipOutputStream, __Close);
	Gura_AssignMethod(wx_ZipOutputStream, __CloseEntry);
	Gura_AssignMethod(wx_ZipOutputStream, __CopyArchiveMetaData);
	Gura_AssignMethod(wx_ZipOutputStream, __CopyEntry);
	Gura_AssignMethod(wx_ZipOutputStream, __GetLevel);
	Gura_AssignMethod(wx_ZipOutputStream, __SetLevel);
	Gura_AssignMethod(wx_ZipOutputStream, __PutNextDirEntry);
	Gura_AssignMethod(wx_ZipOutputStream, __PutNextEntry);
	Gura_AssignMethod(wx_ZipOutputStream, __PutNextEntry_1);
	Gura_AssignMethod(wx_ZipOutputStream, __SetComment);
}

Gura_ImplementDescendantCreator(wx_ZipOutputStream)
{
	return new Object_wx_ZipOutputStream((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
