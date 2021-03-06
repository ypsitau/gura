//=============================================================================
// Gura class: mtp.storage
//=============================================================================
#include "stdafx.h"

Gura_BeginModuleScope(mtp)

static const char *helpDoc_en = R"**(
# Overview

The class `mtp.storage` provices methods to transfer files from/to a device and
to list and manipulate files on a device.


# Property

An `mtp.storage` instance has following properties:

${markdown.makedoc@property(`en, mtp.storage)}

# Method

The `mtp.storage` class has following methods:

${markdown.makedoc@function(`en
mtp.storage.opendir
mtp.storage.recvfile
mtp.storage.remove
mtp.storage.sendfile
)}
)**";

//-----------------------------------------------------------------------------
// Implementation of Object_storage
//-----------------------------------------------------------------------------
Object_storage::Object_storage(Storage *pStorage) :
					Object(Gura_UserClass(storage)), _pStorage(pStorage)
{
}

String Object_storage::ToString(bool exprFlag)
{
	String rtn = "<mtp.storage:";
	rtn += ">";
	return rtn;
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// mtp.storage#storage_type
Gura_DeclareProperty_R(storage, storage_type)
{
	SetPropAttr(VTYPE_symbol);
	AddHelp(
		Gura_Symbol(en),
		"Indicates the type of the storage by following symbols:\n"
		"\n"
		"- `` `Undefined`` .. Undefined type.\n"
		"- `` `FixedROM`` .. Non-removable and read-only.\n"
		"- `` `RemovableROM`` .. Removable and read-only.\n"
		"- `` `FixedRAM`` .. Non-removable and read/write capable.\n"
		"- `` `RemovableRAM`` .. Removable and read/write capable.\n"
		);
}

Gura_ImplementPropertyGetter(storage, storage_type)
{
	const Storage *pStorage = Object_storage::GetObject(valueThis)->GetStorage();
	return Value(pStorage->GetStorageType());
}

// mtp.storage#filesystem_type
Gura_DeclareProperty_R(storage, filesystem_type)
{
	SetPropAttr(VTYPE_symbol);
	AddHelp(
		Gura_Symbol(en),
		"Indicates the type of the file system by following symbols:\n"
		"\n"
		"- `` `Undefined`` .. \n"
		"- `` `GenericFlat`` .. \n"
		"- `` `GenericHierarchical`` .. \n"
		"- `` `DCF`` .. \n"
		);
}

Gura_ImplementPropertyGetter(storage, filesystem_type)
{
	const Storage *pStorage = Object_storage::GetObject(valueThis)->GetStorage();
	return Value(pStorage->GetFilesystemType());
}

// mtp.storage#access_capability
Gura_DeclareProperty_R(storage, access_capability)
{
	SetPropAttr(VTYPE_symbol);
	AddHelp(
		Gura_Symbol(en),
		"Indicates what access is permitted to the storage by following symbols:\n"
		"\n"
		"- `` `ReadWrite`` .. Read/write capable.\n"
		"- `` `ReadOnly`` .. Read-only.\n"
		"- `` `ReadOnlyWithObjectDeletion`` .. Read-only but deleting operation is permitted.\n"
		);
}

Gura_ImplementPropertyGetter(storage, access_capability)
{
	const Storage *pStorage = Object_storage::GetObject(valueThis)->GetStorage();
	return Value(pStorage->GetAccessCapability());
}

// mtp.storage#max_capacity
Gura_DeclareProperty_R(storage, max_capacity)
{
	SetPropAttr(VTYPE_number);
	AddHelp(
		Gura_Symbol(en),
		"Returns the maximum capacity of the storage in bytes.");
}

Gura_ImplementPropertyGetter(storage, max_capacity)
{
	const Storage *pStorage = Object_storage::GetObject(valueThis)->GetStorage();
	return Value(pStorage->GetMaxCapacity());
}

// mtp.storage#free_space_in_bytes
Gura_DeclareProperty_R(storage, free_space_in_bytes)
{
	SetPropAttr(VTYPE_number);
	AddHelp(
		Gura_Symbol(en),
		"Returns the free space in the storage in bytes.");
}

Gura_ImplementPropertyGetter(storage, free_space_in_bytes)
{
	const Storage *pStorage = Object_storage::GetObject(valueThis)->GetStorage();
	return Value(pStorage->GetFreeSpaceInBytes());
}

// mtp.storage#free_space_in_objects
Gura_DeclareProperty_R(storage, free_space_in_objects)
{
	SetPropAttr(VTYPE_number);
	AddHelp(
		Gura_Symbol(en),
		"Returns the free space in the storage in number of objects.");
}

Gura_ImplementPropertyGetter(storage, free_space_in_objects)
{
	const Storage *pStorage = Object_storage::GetObject(valueThis)->GetStorage();
	return Value(pStorage->GetFreeSpaceInObjects());
}

// mtp.storage#storage_description
Gura_DeclareProperty_R(storage, storage_description)
{
	SetPropAttr(VTYPE_string);
	AddHelp(
		Gura_Symbol(en),
		"Returns the storage description.");
}

Gura_ImplementPropertyGetter(storage, storage_description)
{
	const Storage *pStorage = Object_storage::GetObject(valueThis)->GetStorage();
	return Value(pStorage->GetStorageDescription());
}

// mtp.storage#volume_identifier
Gura_DeclareProperty_R(storage, volume_identifier)
{
	SetPropAttr(VTYPE_string);
	AddHelp(
		Gura_Symbol(en),
		"Returns the volume identifier.");
}

Gura_ImplementPropertyGetter(storage, volume_identifier)
{
	const Storage *pStorage = Object_storage::GetObject(valueThis)->GetStorage();
	return Value(pStorage->GetVolumeIdentifier());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// mtp.storage#opendir(pathname:string) {block?}
Gura_DeclareMethod(storage, opendir)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "pathname", VTYPE_string);
	DeclareBlock(OCCUR_ZeroOrOnce);
	AddHelp(
		Gura_Symbol(en),
		"Creates a `directory` instance that can be passed to functions that browse directories\n"
		"such as `path.dir()` and `path.walk()`.\n"
		"The argument `pathname` specifies the name of a directory on the device.\n"
		"\n"
		GURA_HELPTEXT_BLOCK_en("directory", "directory"));
}

Gura_ImplementMethod(storage, opendir)
{
	const Storage *pStorage = Object_storage::GetObjectThis(arg)->GetStorage();
	const char *pathName = arg.GetString(0);
	AutoPtr<Directory> pDirectory(pStorage->GenerateDirectory(env, pathName));
	if (pDirectory.IsNull()) return Value::Nil;
	return ReturnValue(env, arg, Value(new Object_directory(env, pDirectory.release())));
}

// mtp.storage#reader(pathname:string) {block?}
Gura_DeclareMethod(storage, reader)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "pathname", VTYPE_string);
	DeclareBlock(OCCUR_ZeroOrOnce);
	AddHelp(
		Gura_Symbol(en),
		"");
}

Gura_ImplementMethod(storage, reader)
{
	//const Storage *pStorage = Object_storage::GetObjectThis(arg)->GetStorage();
	//const char *pathName = arg.GetString(0);
	//return ReturnValue(env, arg, Value(new Object_stream(env, pStorage->GenerateReaderStream(env, pathName))));
	return Value::Nil;
}

// mtp.srorage#recvfile(pathname:string, stream:stream:w):reduce {block?}
Gura_DeclareMethod(storage, recvfile)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Reduce, FLAG_None);
	DeclareArg(env, "pathname", VTYPE_string);
	DeclareArg(env, "stream", VTYPE_stream, OCCUR_Once, FLAG_Write);
	DeclareBlock(OCCUR_ZeroOrOnce);
	AddHelp(
		Gura_Symbol(en),
		"Receives the content of a file on the device that is specified by the argument `pathname`\n"
		"and writes it to `stream`.\n"
		"If `block` is specified, it would be evaluated during the receiving process with a block parameter\n"
		"of `|recv:number, total:number|` where `recv` is a number of bytes that has been received\n"
		"and `total` is that of the total size.\n"
		"This functions returns the reference of the target.\n");
}

Gura_ImplementMethod(storage, recvfile)
{
	const Storage *pStorage = Object_storage::GetObjectThis(arg)->GetStorage();
	const char *pathName = arg.GetString(0);
	Stream *pStream = &arg.GetStream(1);
	const Function *pFuncBlock = nullptr;
	if (arg.IsBlockSpecified()) {
		pFuncBlock = arg.GetBlockFunc(env, GetSymbolForBlock());
		if (pFuncBlock == nullptr) return Value::Nil;
	}
	if (!pStorage->RecvFile(env, pathName, pStream, pFuncBlock)) return Value::Nil;
	return arg.GetValueThis();
}

// mtp.storage#remove(pathname:string):reduce
Gura_DeclareMethod(storage, remove)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Reduce, FLAG_None);
	DeclareArg(env, "pathname", VTYPE_string);
	AddHelp(
		Gura_Symbol(en),
		"Removes a file on the device that is specified by the argument `pathname`.\n"
		"This functions returns the reference of the target.\n");
}

Gura_ImplementMethod(storage, remove)
{
	const Storage *pStorage = Object_storage::GetObjectThis(arg)->GetStorage();
	const char *pathName = arg.GetString(0);
	if (!pStorage->DeleteFile(env, pathName)) return Value::Nil;
	return arg.GetValueThis();
}

// mtp.storage#sendfile(pathname:string, stream:stream:r):reduce {block?}
Gura_DeclareMethod(storage, sendfile)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Reduce, FLAG_None);
	DeclareArg(env, "pathname", VTYPE_string);
	DeclareArg(env, "stream", VTYPE_stream, OCCUR_Once, FLAG_Read);
	DeclareBlock(OCCUR_ZeroOrOnce);
	AddHelp(
		Gura_Symbol(en),
		"Reads data from `stream` and\n"
		"sends it to the device as a file that is specified by the argument `pathname`.\n"
		"If `block` is specified, it would be evaluated during the receiving process with a block parameter\n"
		"of `|sent:number, total:number|` where `sent` is a number of bytes that has been sent\n"
		"and `total` is that of the total size.\n"
		"This functions returns the reference of the target.\n");
}

Gura_ImplementMethod(storage, sendfile)
{
	const Storage *pStorage = Object_storage::GetObjectThis(arg)->GetStorage();
	const char *pathName = arg.GetString(0);
	Stream *pStream  = &arg.GetStream(1);
	const Function *pFuncBlock = nullptr;
	if (arg.IsBlockSpecified()) {
		pFuncBlock = arg.GetBlockFunc(env, GetSymbolForBlock());
		if (pFuncBlock == nullptr) return Value::Nil;
	}
	if (!pStorage->SendFile(env, pathName, pStream, pFuncBlock)) return Value::Nil;
	return arg.GetValueThis();
}

//-----------------------------------------------------------------------------
// Implementation of class mtp.storage
//-----------------------------------------------------------------------------
Gura_ImplementUserClass(storage)
{
	// Assignment of property
	Gura_AssignProperty(storage, storage_type);
	//Gura_AssignProperty(storage, filesystem_type);
	Gura_AssignProperty(storage, access_capability);
	Gura_AssignProperty(storage, max_capacity);
	Gura_AssignProperty(storage, free_space_in_bytes);
	Gura_AssignProperty(storage, free_space_in_objects);
	Gura_AssignProperty(storage, storage_description);
	Gura_AssignProperty(storage, volume_identifier);
	// Assignment of method
	Gura_AssignMethod(storage, opendir);
	//Gura_AssignMethod(storage, reader);
	Gura_AssignMethod(storage, recvfile);
	Gura_AssignMethod(storage, remove);
	Gura_AssignMethod(storage, sendfile);
	// Assignment of value
	Gura_AssignValue(storage, Value(Reference()));
	// help document
	AddHelpTemplate(env, Gura_Symbol(en), helpDoc_en);
}

Gura_EndModuleScope(mtp)
