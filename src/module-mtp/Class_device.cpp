//=============================================================================
// Gura class: mtp.device
//=============================================================================
#include "stdafx.h"

Gura_BeginModuleScope(mtp)

//-----------------------------------------------------------------------------
// Device
//-----------------------------------------------------------------------------
Device::Device(LIBMTP_mtpdevice_t *mtpDevice) : _cntRef(1), _mtpDevice(mtpDevice)
{
}

Device::~Device()
{
	::LIBMTP_Release_Device(_mtpDevice);
}

void Device::LookupStorages(Object_list *pObjList) const
{
	LIBMTP_devicestorage_t *deviceStorage = _mtpDevice->storage;
	for ( ; deviceStorage != nullptr; deviceStorage = deviceStorage->next) {
		pObjList->Add(Value(new Object_storage(new Storage(Reference(), deviceStorage))));
	}
}

Directory_MTP *Device::GenerateDirectory(Signal &sig, uint32_t storageId, const char *pathName, const char *pathNameEnd) const
{
	const char *p = pathName;
	if (pathNameEnd == nullptr) pathNameEnd = pathName + ::strlen(pathName);
	if (p != pathNameEnd && IsFileSeparator(*p)) p++;
	Directory_MTP *pDirectory = new Directory_MTP(
		nullptr, "/", Directory::TYPE_Container,
		Reference(), storageId, LIBMTP_FILES_AND_FOLDERS_ROOT,
		new Stat("", "", 0, DateTime(), LIBMTP_FILETYPE_FOLDER));
	while (p != pathNameEnd) {
		if (!pDirectory->IsContainer()) {
			sig.SetError(ERR_IOError, "can't browse inside an item");
			return nullptr;
		}
		String field;
		for ( ; ; p++) {
			if (p == pathNameEnd) {
				break;
			} else if (IsFileSeparator(*p)) {
				p++;
				break;
			}
			field += *p;
		}
		if (field.empty()) {
			sig.SetError(ERR_FormatError, "wrong format of path name");
			return nullptr;
		}
		//::printf("[%s]\n", field.c_str());
		LIBMTP_file_t *mtpfileHead = ::LIBMTP_Get_Files_And_Folders(_mtpDevice, storageId, pDirectory->GetItemId());
		if (mtpfileHead == nullptr) {
			::LIBMTP_Dump_Errorstack(_mtpDevice);
			::LIBMTP_Clear_Errorstack(_mtpDevice);
			sig.SetError(ERR_LibraryError, "failed to get file information from MTP");
			return nullptr;
		}
		LIBMTP_file_t *mtpfileFound = nullptr;
		for (LIBMTP_file_t *mtpfile = mtpfileHead; mtpfile != nullptr; mtpfile = mtpfile->next) {
			if (field == mtpfile->filename) {
				mtpfileFound = mtpfile;
				break;
			}
		}
		if (mtpfileFound == nullptr) {
			DestroyMtpfileList(mtpfileHead);
			sig.SetError(ERR_IOError, "specified path doesn't exist");
			return nullptr;
		}
		pDirectory = new Directory_MTP(
			pDirectory, mtpfileFound->filename,
			(mtpfileFound->filetype == LIBMTP_FILETYPE_FOLDER)?
								Directory::TYPE_Container : Directory::TYPE_Item,
			Reference(), storageId, mtpfileFound->item_id,
			new Stat(pDirectory->MakePathName(false).c_str(), mtpfileFound));
		DestroyMtpfileList(mtpfileHead);
	}
	return pDirectory;
}

//-----------------------------------------------------------------------------
// Device::Reader
//-----------------------------------------------------------------------------
Device::Reader::Reader(Signal &sig, Device *pDevice, uint32_t itemId, Stream *pStream) :
	_sig(sig), _pDevice(pDevice), _itemId(itemId), _pStream(pStream)
{
}

uint16_t Device::Reader::OnDataPut(void *params, uint32_t sendlen, unsigned char *data, uint32_t *putlen)
{
	//::printf("OnWrite()\n");
	*putlen = static_cast<uint32_t>(_pStream->Write(_sig, data, sendlen));
	return _sig.IsSignalled()? LIBMTP_HANDLER_RETURN_ERROR : LIBMTP_HANDLER_RETURN_OK;
}

uint16_t Device::Reader::OnDataPutStub(void *params, void *priv,
								 uint32_t sendlen, unsigned char *data, uint32_t *putlen)
{
	Reader *pReader = reinterpret_cast<Reader *>(priv);
	return pReader->OnDataPut(params, sendlen, data, putlen);
}

void Device::Reader::Run()
{
	if (::LIBMTP_Get_File_To_Handler(
			_pDevice->GetMtpDevice(), _itemId, OnDataPutStub, this, nullptr, nullptr) != 0) {
		_sig.SetError(ERR_LibraryError, "error while communicating in MTP protocol");
	}
}

//-----------------------------------------------------------------------------
// Device::Writer
//-----------------------------------------------------------------------------
Device::Writer::Writer(Signal &sig, Device *pDevice, uint32_t itemIdParent, const char *fileName, Stream *pStream) :
	_sig(sig), _pDevice(pDevice), _itemIdParent(itemIdParent), _fileName(fileName), _pStream(pStream)
{
}

uint16_t Device::Writer::OnDataGet(void *params, uint32_t wantlen, unsigned char *data, uint32_t *gotlen)
{
	//::printf("OnRead()\n");
	*gotlen = static_cast<uint32_t>(_pStream->Read(_sig, data, wantlen));
	return _sig.IsSignalled()? LIBMTP_HANDLER_RETURN_ERROR :
		(*gotlen == 0)? LIBMTP_HANDLER_RETURN_CANCEL : LIBMTP_HANDLER_RETURN_OK;
}

uint16_t Device::Writer::OnDataGetStub(void *params, void *priv,
							  uint32_t wantlen, unsigned char *data, uint32_t *gotlen)
{
	Writer *pWriter = reinterpret_cast<Writer *>(priv);
	return pWriter->OnDataGet(params, wantlen, data, gotlen);
}

void Device::Writer::Run()
{
	/*
	::LIBMTP_Send_File_From_Handler(LIBMTP_mtpdevice_t *,
				  MTPDataGetFunc, void *,
				  LIBMTP_file_t * const,
				  LIBMTP_progressfunc_t const,
				  void const * const);
	*/
	LIBMTP_file_t *mtpfile = ::LIBMTP_new_file_t();
	mtpfile->filesize = static_cast<uint64_t>(_pStream->GetSize());
	mtpfile->filename = ::strdup(_fileName.c_str());
	mtpfile->filetype = GetMtpfiletype(_fileName.c_str());
	mtpfile->parent_id = _itemIdParent;
	mtpfile->storage_id = 0;
	::LIBMTP_Send_File_From_Handler(
		_pDevice->GetMtpDevice(), OnDataGetStub, this, mtpfile, nullptr, nullptr);
	::LIBMTP_destroy_file_t(mtpfile);
}

//-----------------------------------------------------------------------------
// Directory_MTP implementation
//-----------------------------------------------------------------------------
Directory_MTP::Directory_MTP(Directory *pParent, const char *name, Type type,
							 Device *pDevice, uint32_t storageId, uint32_t itemId, Stat *pStat) :
	Directory(pParent, name, type, OAL::FileSeparatorUnix),
	_pDevice(pDevice), _storageId(storageId), _itemId(itemId), _pStat(pStat)
{
	_browsePack.mtpfileHead = nullptr;
	_browsePack.mtpfile = nullptr;
}

Directory_MTP::~Directory_MTP()
{
	DestroyMtpfileList(_browsePack.mtpfileHead);
}

Directory *Directory_MTP::DoNext(Environment &env)
{
	if (_browsePack.mtpfileHead == nullptr) {
		_browsePack.mtpfileHead = ::LIBMTP_Get_Files_And_Folders(_pDevice->GetMtpDevice(), _storageId, _itemId);
		_browsePack.mtpfile = _browsePack.mtpfileHead;
	} else {
		_browsePack.mtpfile = _browsePack.mtpfile->next;
	}
	if (_browsePack.mtpfile == nullptr) return nullptr;
	Type type = (_browsePack.mtpfile->filetype == LIBMTP_FILETYPE_FOLDER)? TYPE_Container : TYPE_Item;
	return new Directory_MTP(
		Reference(), _browsePack.mtpfile->filename, type,
		_pDevice->Reference(), _storageId, _browsePack.mtpfile->item_id,
		new Stat(MakePathName(false).c_str(), _browsePack.mtpfile));
}

Stream *Directory_MTP::DoOpenStream(Environment &env, UInt32 attr)
{
	return nullptr;
}

Object *Directory_MTP::DoGetStatObj(Signal &sig)
{
	return new Object_stat(_pStat->Reference());
}

//-----------------------------------------------------------------------------
// Implementation of Object_device
//-----------------------------------------------------------------------------
Object_device::Object_device(Device *pDevice) : Object(Gura_UserClass(device)), _pDevice(pDevice)
{
}

String Object_device::ToString(bool exprFlag)
{
	String rtn = "<mtp.device:";
	rtn += _pDevice->GetFriendlyName();
	rtn += ">";
	return rtn;
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// mtp.device#friendlyName
Gura_DeclareProperty_R(device, friendlyName)
{
	SetPropAttr(VTYPE_string);
	AddHelp(
		Gura_Symbol(en),
		""
		);
}

Gura_ImplementPropertyGetter(device, friendlyName)
{
	Object_device *pObjThis = Object_device::GetObject(valueThis);
	return Value(pObjThis->GetDevice()->GetFriendlyName());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// mtp.device#GetStorages() {block?}
Gura_DeclareMethod(device, GetStorages)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
	AddHelp(
		Gura_Symbol(en),
		"");
}

Gura_ImplementMethod(device, GetStorages)
{
	const Device *pDevice = Object_device::GetObjectThis(arg)->GetDevice();
	Value valueRtn;
	Object_list *pObjList = valueRtn.InitAsList(env);
	pDevice->LookupStorages(pObjList);
	return ReturnValue(env, arg, valueRtn);
}

//-----------------------------------------------------------------------------
// Implementation of class mtp.device
//-----------------------------------------------------------------------------
Gura_ImplementUserClass(device)
{
	// Assignment of property
	Gura_AssignProperty(device, friendlyName);
	// Assignment of method
	Gura_AssignMethod(device, GetStorages);
	// Assignment of value
	Gura_AssignValue(device, Value(Reference()));
}

Gura_EndModuleScope(mtp)
