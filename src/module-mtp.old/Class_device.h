//=============================================================================
// Gura class: mtp.device
//=============================================================================
#ifndef __GURA_MODULE_MTP_CLASS_DEVICE_H__
#define __GURA_MODULE_MTP_CLASS_DEVICE_H__
#include <gura.h>

Gura_BeginModuleScope(mtp)

class Directory_MTP;

//-----------------------------------------------------------------------------
// Device
//-----------------------------------------------------------------------------
class Device {
public:
	class Reader : public OAL::Thread {
	private:
		Signal &_sig;
		AutoPtr<Device> _pDevice;
		uint32_t _itemId;
		AutoPtr<Stream> _pStream;
	public:
		Reader(Signal &sig, Device *pDevice, uint32_t itemId, Stream *pStream);
		uint16_t OnDataPut(void *params, uint32_t sendlen, unsigned char *data, uint32_t *putlen);
		static uint16_t OnDataPutStub(void *params, void *priv,
									  uint32_t sendlen, unsigned char *data, uint32_t *putlen);
		virtual void Run();
	};
	// Writer can not be implemented because MTP protocol needs to know the whole file size
	// before transmitting data to a device while Writer is not capable of knowing it in advance.
private:
	int _cntRef;
	LIBMTP_mtpdevice_t *_mtpDevice;
public:
	Gura_DeclareReferenceAccessor(Device);
public:
	Device(LIBMTP_mtpdevice_t *mtpDevice);
protected:
	~Device();
public:
	void LookupStorages(Object_list *pObjList) const;
	Directory_MTP *GeneratePartialDirectory(
		Signal &sig, uint32_t storageId, const char *pathName, const char **pPathNamePartial) const;
	Directory_MTP *GenerateDirectory(Signal &sig, uint32_t storageId, const char *pathName) const;
	inline LIBMTP_mtpdevice_t *GetMtpDevice() const { return _mtpDevice; }
#if 0
	inline const char *GetManufacturerName() const { return ::LIBMTP_Get_Manufacturername(_mtpDevice); }
	inline const char *GetModelName() const { return ::LIBMTP_Get_Modelname(_mtpDevice); }
	inline const char *GetSerialNumber() const { return ::LIBMTP_Get_Serialnumber(_mtpDevice); }
	inline const char *GetDeviceVersion() const { return ::LIBMTP_Get_Deviceversion(_mtpDevice); }
	inline const char *GetFriendlyname() const { return ::LIBMTP_Get_Friendlyname(_mtpDevice); }
	inline const char *GetSyncPartner() const { return ::LIBMTP_Get_Syncpartner(_mtpDevice); }
	inline int GetBatterylevel(uint8_t * const maximum_level, uint8_t * ) const {
		//int LIBMTP_Get_Batterylevel(LIBMTP_mtpdevice_t *, uint8_t * const, uint8_t * const);
		return 0;
	}
	inline int GetSecureTime() const {
		//int LIBMTP_Get_Secure_Time(LIBMTP_mtpdevice_t *, char ** const);
		return 0;
	}
	inline int GetDeviceCertificate() const {
		//int LIBMTP_Get_Device_Certificate(LIBMTP_mtpdevice_t *, char ** const);
		return 0;
	}
	inline int GetSupportedFileTypes() const {
		//int LIBMTP_Get_Supported_Filetypes(LIBMTP_mtpdevice_t *, uint16_t ** const, uint16_t * const);
		return 0;
	}
	//int LIBMTP_Set_Friendlyname(LIBMTP_mtpdevice_t*, char const * const);
	//int LIBMTP_Set_Syncpartner(LIBMTP_mtpdevice_t*, char const * const);
#endif
};

//-----------------------------------------------------------------------------
// Directory_MTP declaration
//-----------------------------------------------------------------------------
class Directory_MTP : public Directory {
private:
	AutoPtr<Device> _pDevice;
	uint32_t _storageId;
	uint32_t _itemId;
	AutoPtr<Stat> _pStat;
	struct {
		LIBMTP_file_t *mtpfileHead;
		LIBMTP_file_t *mtpfile;
	} _browsePack;
public:
	Directory_MTP(Directory *pParent, const char *name, Type type,
				  Device *pDevice, uint32_t storageId, uint32_t itemId, Stat *pStat);
	virtual ~Directory_MTP();
	virtual Directory *DoNext(Environment &env);
	virtual Stream *DoOpenStream(Environment &env, UInt32 attr);
	virtual Object *DoGetStatObj(Signal &sig);
	inline uint32_t GetItemId() const { return _itemId; }
	inline Stat *GetStat() const { return _pStat.get(); }
};

//-----------------------------------------------------------------------------
// Object_device declaration
//-----------------------------------------------------------------------------
Gura_DeclareUserClass(device);

class Object_device : public Object {
private:
	AutoPtr<Device> _pDevice;
public:
	Gura_DeclareObjectAccessor(device)
public:
	Object_device(Device *pDevice);
	virtual String ToString(bool exprFlag);
	inline const Device *GetDevice() const { return _pDevice.get(); }
};

Gura_EndModuleScope(mtp)

#endif
