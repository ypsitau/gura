#include "Object_exif.h"

Gura_BeginModule(jpeg)

enum {
	BYTES_IFDHeader	= 2,
	BYTES_TagRaw	= 12,
};

enum {
	TYPE_BYTE		= 1,
	TYPE_ASCII		= 2,
	TYPE_SHORT		= 3,
	TYPE_LONG		= 4,
	TYPE_RATIONAL	= 5,
	TYPE_UNDEFINED	= 7,
	TYPE_SLONG		= 9,
	TYPE_SRATIONAL	= 10,
};

enum {
	UNITSIZE_BYTE		= 1,
	UNITSIZE_ASCII		= 1,
	UNITSIZE_SHORT		= 2,
	UNITSIZE_LONG		= 4,
	UNITSIZE_RATIONAL	= 8,
	UNITSIZE_UNDEFINED	= 0,
	UNITSIZE_SLONG		= 4,
	UNITSIZE_SRATIONAL	= 8,
};

enum {
	TAG_ImageWidth					= 0x0100,
	TAG_ImageLength					= 0x0101,
	TAG_BitsPerSample				= 0x0102,
	TAG_Compression					= 0x0103,
	TAG_PhotometricInterpretation	= 0x0106,
	TAG_Orientation					= 0x0112,
	TAG_SamplesPerPixel				= 0x0115,
	TAG_PlanarConfiguration			= 0x011c,
	TAG_YCbCrSubSampling			= 0x0212,
	TAG_YCbCrPositioning			= 0x0213,
	TAG_XResolution					= 0x011a,
	TAG_YResolution					= 0x011b,
	TAG_ResolutionUnit				= 0x0128,
	TAG_StripOffsets				= 0x0111,
	TAG_RowsPerStrip				= 0x0116,
	TAG_StripByteCounts				= 0x0117,
	TAG_JPEGInterchangeFormat		= 0x0201,
	TAG_JPEGInterchangeFormatLength	= 0x0202,
	TAG_TransferFunction			= 0x012d,
	TAG_WhitePoint					= 0x013e,
	TAG_PrimaryChromaticities		= 0x013f,
	TAG_YCbCrCoefficients			= 0x0211,
	TAG_ReferenceBlackWhite			= 0x0214,
	TAG_DateTime					= 0x0132,
	TAG_ImageDescription			= 0x010e,
	TAG_Make						= 0x010f,
	TAG_Model						= 0x0110,
	TAG_Software					= 0x0131,
	TAG_Artist						= 0x013b,
	TAG_Copyright					= 0x0d68,
	TAG_ExifIFDPointer				= 0x8769,
	TAG_GPSInfoIFDPointer			= 0x8825,
	TAG_ExifVersion					= 0x9000,
	TAG_FlashPixVersion				= 0xa000,
	TAG_ColorSpace					= 0xa001,
	TAG_ComponentsConfiguration		= 0x9101,
	TAG_CompressedBitsPerPixel		= 0x9102,
	TAG_PixelXDimension				= 0xa002,
	TAG_PixelYDimension				= 0xa003,
	TAG_MakerNote					= 0x927c,
	TAG_UserComment					= 0x9286,
	TAG_RelatedSoundFile			= 0xa004,
	TAG_DateTimeOriginal			= 0x9003,
	TAG_DateTimeDigitized			= 0x9004,
	TAG_SubSecTime					= 0x9290,
	TAG_SubSecTimeOriginal			= 0x9291,
	TAG_SubSecTimeDigitized			= 0x9292,
	TAG_ExposureTime				= 0x829a,
	TAG_FNumber						= 0x829d,
	TAG_ExposureProgram				= 0x8822,
	TAG_SpectralSensitivity			= 0x8824,
	TAG_ISOSpeedRatings				= 0x8827,
	TAG_OECF						= 0x8828,
	TAG_ShutterSpeedValue			= 0x9201,
	TAG_ApertureValue				= 0x9202,
	TAG_BrightnessValue				= 0x9203,
	TAG_ExposureBiasValue			= 0x9204,
	TAG_MaxApertureValue			= 0x9205,
	TAG_SubjectDistance				= 0x9206,
	TAG_MeteringMode				= 0x9207,
	TAG_LightSource					= 0x9208,
	TAG_Flash						= 0x9209,
	TAG_FocalLength					= 0x920a,
	TAG_FlashEnergy					= 0xa20b,
	TAG_SpatialFrequencyResponse	= 0xa20c,
	TAG_FocalPlaneXResolution		= 0xa20e,
	TAG_FocalPlaneYResolution		= 0xa20f,
	TAG_FocalPlaneResolutionUnit	= 0xa210,
	TAG_SubjectLocation				= 0xa214,
	TAG_ExposureIndex				= 0xa215,
	TAG_SensingMethod				= 0xa217,
	TAG_FileSource					= 0xa300,
	TAG_SceneType					= 0xa301,
	TAG_CFAPattern					= 0xa302,
	TAG_InteroperabilityIFDPointer	= 0xa005,
	TAG_GPSVersionID				= 0x0000,
	TAG_GPSLatitudeRef				= 0x0001,
	TAG_GPSLatitude					= 0x0002,
	TAG_GPSLongitudeRef				= 0x0003,
	TAG_GPSLongitude				= 0x0004,
	TAG_GPSAltitudeRef				= 0x0005,
	TAG_GPSAltitude					= 0x0006,
	TAG_GPSTimeStamp				= 0x0007,
	TAG_GPSSatellites				= 0x0008,
	TAG_GPSStatus					= 0x0009,
	TAG_GPSMeasureMode				= 0x000a,
	TAG_GPSDOP						= 0x000b,
	TAG_GPSSpeedRef					= 0x000c,
	TAG_GPSSpeed					= 0x000d,
	TAG_GPSTrackRef					= 0x000e,
	TAG_GPSTrack					= 0x000f,
	TAG_GPSImgDirectionRef			= 0x0010,
	TAG_GPSImgDirection				= 0x0011,
	TAG_GPSMapDatum					= 0x0012,
	TAG_GPSDestLatitudeRef			= 0x0013,
	TAG_GPSDestLatitude				= 0x0014,
	TAG_GPSDestLongitudeRef			= 0x0015,
	TAG_GPSDestLongitude			= 0x0016,
	TAG_GPSBearingRef				= 0x0017,
	TAG_GPSBearing					= 0x0018,
	TAG_GPSDestDistanceRef			= 0x0019,
	TAG_GPSDestDistance				= 0x001a,
};

struct Header {
	XPackedUShort_BE(SOI);
	XPackedUShort_BE(APP1);
	XPackedUShort_BE(Size);
	char ExifCode[6];
};

struct TIFF_BE {
	XPackedUShort_BE(Code);
	XPackedULong_BE(Offset0thIFD);
};

struct TIFF_LE {
	XPackedUShort_LE(Code);
	XPackedULong_LE(Offset0thIFD);
};

struct IFDHeader_BE {
	XPackedUShort_BE(TagCount);
};

struct IFDHeader_LE {
	XPackedUShort_LE(TagCount);
};

struct RATIONAL_BE {
	XPackedULong_BE(top);
	XPackedULong_BE(bottom);
};

struct RATIONAL_LE {
	XPackedULong_LE(top);
	XPackedULong_LE(bottom);
};

union ValueRaw_BE {
	unsigned char BYTE[4];
	char ASCII[4];
	struct {
		XPackedUShort_BE(num);
		XPackedUShort_BE(second);
	} SHORT;
	struct {
		XPackedULong_BE(num);
	} LONG;
	struct {
		XPackedULong_BE(num);
	} SLONG;
};

struct TagRaw_BE {
	XPackedUShort_BE(Tag);
	XPackedUShort_BE(Type);
	XPackedULong_BE(Count);
	unsigned char ValueRaw[4];
};

union ValueRaw_LE {
	unsigned char BYTE[4];
	char ASCII[4];
	struct {
		XPackedUShort_LE(num);
		XPackedUShort_LE(second);
	} SHORT;
	struct {
		XPackedULong_LE(num);
	} LONG;
	struct {
		XPackedULong_LE(num);
	} SLONG;
};

struct TagRaw_LE {
	XPackedUShort_LE(Tag);
	XPackedUShort_LE(Type);
	XPackedULong_LE(Count);
	unsigned char ValueRaw[4];
};

struct TagInfo {
	unsigned short tag;
	const char *name;
	unsigned short type;
};

struct TypeInfo {
	unsigned short type;
	const char *name;
	size_t unitSize;
};

static const TagInfo g_tagInfoTbl[] = {
	{ TAG_ImageWidth,					"ImageWidth",					TYPE_UNDEFINED,	},
	{ TAG_ImageLength,					"ImageLength",					TYPE_UNDEFINED,	},
	{ TAG_BitsPerSample,				"BitsPerSample",				TYPE_UNDEFINED,	},
	{ TAG_Compression,					"Compression",					TYPE_UNDEFINED,	},
	{ TAG_PhotometricInterpretation,	"PhotometricInterpretation",	TYPE_UNDEFINED,	},
	{ TAG_Orientation,					"Orientation",					TYPE_SHORT,		},
	{ TAG_SamplesPerPixel,				"SamplesPerPixel",				TYPE_UNDEFINED,	},
	{ TAG_PlanarConfiguration,			"PlanarConfiguration",			TYPE_UNDEFINED,	},
	{ TAG_YCbCrSubSampling,				"YCbCrSubSampling",				TYPE_UNDEFINED,	},
	{ TAG_YCbCrPositioning,				"YCbCrPositioning",				TYPE_SHORT,		},
	{ TAG_XResolution,					"XResolution",					TYPE_RATIONAL,	},
	{ TAG_YResolution,					"YResolution",					TYPE_RATIONAL,	},
	{ TAG_ResolutionUnit,				"ResolutionUnit",				TYPE_SHORT,		},
	{ TAG_StripOffsets,					"StripOffsets",					TYPE_UNDEFINED,	},
	{ TAG_RowsPerStrip,					"RowsPerStrip",					TYPE_UNDEFINED,	},
	{ TAG_StripByteCounts,				"StripByteCounts",				TYPE_UNDEFINED,	},
	{ TAG_JPEGInterchangeFormat,		"JPEGInterchangeFormat",		TYPE_UNDEFINED,	},
	{ TAG_JPEGInterchangeFormatLength,	"JPEGInterchangeFormatLength",	TYPE_UNDEFINED,	},
	{ TAG_TransferFunction,				"TransferFunction",				TYPE_UNDEFINED,	},
	{ TAG_WhitePoint,					"WhitePoint",					TYPE_UNDEFINED,	},
	{ TAG_PrimaryChromaticities,		"PrimaryChromaticities",		TYPE_UNDEFINED,	},
	{ TAG_YCbCrCoefficients,			"YCbCrCoefficients",			TYPE_UNDEFINED,	},
	{ TAG_ReferenceBlackWhite,			"ReferenceBlackWhite",			TYPE_UNDEFINED,	},
	{ TAG_DateTime,						"DateTime",						TYPE_ASCII,		},
	{ TAG_ImageDescription,				"ImageDescription",				TYPE_UNDEFINED,	},
	{ TAG_Make,							"Make",							TYPE_ASCII,		},
	{ TAG_Model,						"Model",						TYPE_ASCII,		},
	{ TAG_Software,						"Software",						TYPE_UNDEFINED,	},
	{ TAG_Artist,						"Artist",						TYPE_UNDEFINED,	},
	{ TAG_Copyright,					"Copyright",					TYPE_UNDEFINED,	},
	{ TAG_ExifIFDPointer,				"ExifIFDPointer",				TYPE_SHORT,		},
	{ TAG_GPSInfoIFDPointer,			"GPSInfoIFDPointer",			TYPE_UNDEFINED,	},
	{ TAG_ExifVersion,					"ExifVersion",					TYPE_UNDEFINED,	},
	{ TAG_FlashPixVersion,				"FlashPixVersion",				TYPE_UNDEFINED,	},
	{ TAG_ColorSpace,					"ColorSpace",					TYPE_UNDEFINED,	},
	{ TAG_ComponentsConfiguration,		"ComponentsConfiguration",		TYPE_UNDEFINED,	},
	{ TAG_CompressedBitsPerPixel,		"CompressedBitsPerPixel",		TYPE_UNDEFINED,	},
	{ TAG_PixelXDimension,				"PixelXDimension",				TYPE_UNDEFINED,	},
	{ TAG_PixelYDimension,				"PixelYDimension",				TYPE_UNDEFINED,	},
	{ TAG_MakerNote,					"MakerNote",					TYPE_UNDEFINED,	},
	{ TAG_UserComment,					"UserComment",					TYPE_UNDEFINED,	},
	{ TAG_RelatedSoundFile,				"RelatedSoundFile",				TYPE_UNDEFINED,	},
	{ TAG_DateTimeOriginal,				"DateTimeOriginal",				TYPE_UNDEFINED,	},
	{ TAG_DateTimeDigitized,			"DateTimeDigitized",			TYPE_UNDEFINED,	},
	{ TAG_SubSecTime,					"SubSecTime",					TYPE_UNDEFINED,	},
	{ TAG_SubSecTimeOriginal,			"SubSecTimeOriginal",			TYPE_UNDEFINED,	},
	{ TAG_SubSecTimeDigitized,			"SubSecTimeDigitized",			TYPE_UNDEFINED,	},
	{ TAG_ExposureTime,					"ExposureTime",					TYPE_UNDEFINED,	},
	{ TAG_FNumber,						"FNumber",						TYPE_UNDEFINED,	},
	{ TAG_ExposureProgram,				"ExposureProgram",				TYPE_UNDEFINED,	},
	{ TAG_SpectralSensitivity,			"SpectralSensitivity",			TYPE_UNDEFINED,	},
	{ TAG_ISOSpeedRatings,				"ISOSpeedRatings",				TYPE_UNDEFINED,	},
	{ TAG_OECF,							"OECF",							TYPE_UNDEFINED,	},
	{ TAG_ShutterSpeedValue,			"ShutterSpeedValue",			TYPE_UNDEFINED,	},
	{ TAG_ApertureValue,				"ApertureValue",				TYPE_UNDEFINED,	},
	{ TAG_BrightnessValue,				"BrightnessValue",				TYPE_UNDEFINED,	},
	{ TAG_ExposureBiasValue,			"ExposureBiasValue",			TYPE_UNDEFINED,	},
	{ TAG_MaxApertureValue,				"MaxApertureValue",				TYPE_UNDEFINED,	},
	{ TAG_SubjectDistance,				"SubjectDistance",				TYPE_UNDEFINED,	},
	{ TAG_MeteringMode,					"MeteringMode",					TYPE_UNDEFINED,	},
	{ TAG_LightSource,					"LightSource",					TYPE_UNDEFINED,	},
	{ TAG_Flash,						"Flash",						TYPE_UNDEFINED,	},
	{ TAG_FocalLength,					"FocalLength",					TYPE_UNDEFINED,	},
	{ TAG_FlashEnergy,					"FlashEnergy",					TYPE_UNDEFINED,	},
	{ TAG_SpatialFrequencyResponse,		"SpatialFrequencyResponse",		TYPE_UNDEFINED,	},
	{ TAG_FocalPlaneXResolution,		"FocalPlaneXResolution",		TYPE_UNDEFINED,	},
	{ TAG_FocalPlaneYResolution,		"FocalPlaneYResolution",		TYPE_UNDEFINED,	},
	{ TAG_FocalPlaneResolutionUnit,		"FocalPlaneResolutionUnit",		TYPE_UNDEFINED,	},
	{ TAG_SubjectLocation,				"SubjectLocation",				TYPE_UNDEFINED,	},
	{ TAG_ExposureIndex,				"ExposureIndex",				TYPE_UNDEFINED,	},
	{ TAG_SensingMethod,				"SensingMethod",				TYPE_UNDEFINED,	},
	{ TAG_FileSource,					"FileSource",					TYPE_UNDEFINED,	},
	{ TAG_SceneType,					"SceneType",					TYPE_UNDEFINED,	},
	{ TAG_CFAPattern,					"CFAPattern",					TYPE_UNDEFINED,	},
	{ TAG_InteroperabilityIFDPointer,	"InteroperabilityIFDPointer",	TYPE_UNDEFINED,	},
	{ TAG_GPSVersionID,					"GPSVersionID",					TYPE_UNDEFINED,	},
	{ TAG_GPSLatitudeRef,				"GPSLatitudeRef",				TYPE_UNDEFINED,	},
	{ TAG_GPSLatitude,					"GPSLatitude",					TYPE_UNDEFINED,	},
	{ TAG_GPSLongitudeRef,				"GPSLongitudeRef",				TYPE_UNDEFINED,	},
	{ TAG_GPSLongitude,					"GPSLongitude",					TYPE_UNDEFINED,	},
	{ TAG_GPSAltitudeRef,				"GPSAltitudeRef",				TYPE_UNDEFINED,	},
	{ TAG_GPSAltitude,					"GPSAltitude",					TYPE_UNDEFINED,	},
	{ TAG_GPSTimeStamp,					"GPSTimeStamp",					TYPE_UNDEFINED,	},
	{ TAG_GPSSatellites,				"GPSSatellites",				TYPE_UNDEFINED,	},
	{ TAG_GPSStatus,					"GPSStatus",					TYPE_UNDEFINED,	},
	{ TAG_GPSMeasureMode,				"GPSMeasureMode",				TYPE_UNDEFINED,	},
	{ TAG_GPSDOP,						"GPSDOP",						TYPE_UNDEFINED,	},
	{ TAG_GPSSpeedRef,					"GPSSpeedRef",					TYPE_UNDEFINED,	},
	{ TAG_GPSSpeed,						"GPSSpeed",						TYPE_UNDEFINED,	},
	{ TAG_GPSTrackRef,					"GPSTrackRef",					TYPE_UNDEFINED,	},
	{ TAG_GPSTrack,						"GPSTrack",						TYPE_UNDEFINED,	},
	{ TAG_GPSImgDirectionRef,			"GPSImgDirectionRef",			TYPE_UNDEFINED,	},
	{ TAG_GPSImgDirection,				"GPSImgDirection",				TYPE_UNDEFINED,	},
	{ TAG_GPSMapDatum,					"GPSMapDatum",					TYPE_UNDEFINED,	},
	{ TAG_GPSDestLatitudeRef,			"GPSDestLatitudeRef",			TYPE_UNDEFINED,	},
	{ TAG_GPSDestLatitude,				"GPSDestLatitude",				TYPE_UNDEFINED,	},
	{ TAG_GPSDestLongitudeRef,			"GPSDestLongitudeRef",			TYPE_UNDEFINED,	},
	{ TAG_GPSDestLongitude,				"GPSDestLongitude",				TYPE_UNDEFINED,	},
	{ TAG_GPSBearingRef,				"GPSBearingRef",				TYPE_UNDEFINED,	},
	{ TAG_GPSBearing,					"GPSBearing",					TYPE_UNDEFINED,	},
	{ TAG_GPSDestDistanceRef,			"GPSDestDistanceRef",			TYPE_UNDEFINED,	},
	{ TAG_GPSDestDistance,				"GPSDestDistance",				TYPE_UNDEFINED,	},
};

static const TypeInfo g_typeInfoTbl[] = {
	{ TYPE_BYTE,		"BYTE",			UNITSIZE_BYTE,		},
	{ TYPE_ASCII,		"ASCII",		UNITSIZE_ASCII,		},
	{ TYPE_SHORT,		"SHORT",		UNITSIZE_SHORT,		},
	{ TYPE_LONG,		"LONG",			UNITSIZE_LONG,		},
	{ TYPE_RATIONAL,	"RATIONAL",		UNITSIZE_RATIONAL,	},
	{ TYPE_UNDEFINED,	"UNDEFINED",	UNITSIZE_UNDEFINED,	},
	{ TYPE_SLONG,		"SLONG",		UNITSIZE_SLONG,		},
	{ TYPE_SRATIONAL,	"SRATIONAL",	UNITSIZE_SRATIONAL,	},
};

//-----------------------------------------------------------------------------
// utility functions
//-----------------------------------------------------------------------------
void SetError_InvalidFormat(Signal &sig)
{
	sig.SetError(ERR_FormatError, "invalid Exif format");
}

bool ReadBuff(Signal sig, Stream &stream, void *buff, size_t bytes)
{
	size_t bytesRead = stream.Read(sig, buff, bytes);
	if (sig.IsSignalled()) return false;
	if (bytesRead < bytes) {
		SetError_InvalidFormat(sig);
		return false;
	}
	return true;
}

const TagInfo *TagToInfo(unsigned short tag)
{
	const TagInfo *pTagInfo = g_tagInfoTbl;
	for (int i = 0; i < NUMBEROF(g_tagInfoTbl); i++, pTagInfo++) {
		if (pTagInfo->tag == tag) return pTagInfo;
	}
	return NULL;
}

const TypeInfo *TypeToInfo(unsigned short type)
{
	const TypeInfo *pTypeInfo = g_typeInfoTbl;
	for (int i = 0; i < NUMBEROF(g_typeInfoTbl); i++, pTypeInfo++) {
		if (pTypeInfo->type == type) return pTypeInfo;
	}
	return NULL;
}

bool ParseIFD(Environment &env, Signal sig, char *buff, size_t bytesAPP1, size_t offset)
{
	if (offset + BYTES_IFDHeader >= bytesAPP1 - 1) {
		SetError_InvalidFormat(sig);
		return false;
	}
	IFDHeader_LE *pIFDHeader = reinterpret_cast<IFDHeader_LE *>(buff + offset);
	size_t nTags = XUnpackUShort(pIFDHeader->TagCount);
	offset += BYTES_IFDHeader;
	if (offset + nTags * BYTES_TagRaw >= bytesAPP1 - 1) {
		SetError_InvalidFormat(sig);
		return false;
	}
	for (size_t iTag = 0; iTag < nTags; iTag++, offset += BYTES_TagRaw) {
		TagRaw_LE *pTagRaw = reinterpret_cast<TagRaw_LE *>(buff + offset);
		unsigned short tag = XUnpackUShort(pTagRaw->Tag);
		unsigned short type = XUnpackUShort(pTagRaw->Type);
		unsigned long count = XUnpackULong(pTagRaw->Count);
		ValueRaw_LE *pValueRaw = reinterpret_cast<ValueRaw_LE *>(pTagRaw->ValueRaw);
		const TagInfo *pTagInfo = TagToInfo(tag);
		const TypeInfo *pTypeInfo = TypeToInfo(type);
		::printf("%s [%04x], %s [%04x], %08x, %08x\n",
				(pTagInfo == NULL)? "(unknown)" : pTagInfo->name, tag,
				(pTypeInfo == NULL)? "(unknown)" : pTypeInfo->name, type,
				count, XUnpackULong(pValueRaw->LONG.num));
		if (tag == TAG_ExifIFDPointer) {
			if (!ParseIFD(env, sig, buff, bytesAPP1, XUnpackULong(pValueRaw->LONG.num))) {
				return false;
			}
		} else if (tag == TAG_GPSInfoIFDPointer) {
			if (!ParseIFD(env, sig, buff, bytesAPP1, XUnpackULong(pValueRaw->LONG.num))) {
				return false;
			}
		} else if (tag == TAG_InteroperabilityIFDPointer) {
			if (!ParseIFD(env, sig, buff, bytesAPP1, XUnpackULong(pValueRaw->LONG.num))) {
				return false;
			}
		} else {
			Value value;
			switch (type) {
			case TYPE_BYTE: {
				
				break;
			}
			case TYPE_ASCII: {
				char *p = pValueRaw->ASCII;
				if (count > 4) {
					size_t offset = XUnpackULong(pValueRaw->LONG.num);
					if (offset + count >= bytesAPP1 - 1) {
						SetError_InvalidFormat(sig);
						return false;
					}
					p = buff + offset;
				}
				value = Value(env, String(p, count - 1));
				break;
			}
			case TYPE_SHORT: {
				
				break;
			}
			case TYPE_LONG: {
				
				break;
			}
			case TYPE_RATIONAL: {
				size_t offset = XUnpackULong(pValueRaw->LONG.num);
				if (offset + UNITSIZE_RATIONAL * count >= bytesAPP1 - 1) {
					SetError_InvalidFormat(sig);
					return false;
				}
				RATIONAL_LE *pRational = reinterpret_cast<RATIONAL_LE *>(buff + offset);
				::printf("%08x / %08x\n",
					XUnpackULong(pRational->top), XUnpackULong(pRational->bottom));
				break;
			}
			case TYPE_UNDEFINED: {
				
				break;
			}
			case TYPE_SLONG: {
				
				break;
			}
			case TYPE_SRATIONAL: {
				
				break;
			}
			default: {
				
				break;
			}
			}
		}
	}
	return true;
}

//-----------------------------------------------------------------------------
// Object_exif implementation
//-----------------------------------------------------------------------------
Object_exif::~Object_exif()
{
}

Object *Object_exif::Clone() const
{
	return NULL;
}

String Object_exif::ToString(Signal sig, bool exprFlag)
{
	return String("<jpeg.exif>");
}

bool Object_exif::ReadStream(Signal sig, Stream &stream)
{
	Environment &env = *this;
	OAL::Memory mem;
	mem.Allocate(65536);
	char *buff = reinterpret_cast<char *>(mem.GetPointer());
	if (!ReadBuff(sig, stream, buff, 12)) return false;
	size_t bytesAPP1 = 0;
	do {
		Header *pHeader = reinterpret_cast<Header *>(buff);
		if (XUnpackUShort(pHeader->SOI) != 0xffd8) {
			SetError_InvalidFormat(sig);
			return false;
		}
		if (XUnpackUShort(pHeader->APP1) != 0xffe1) {
			SetError_InvalidFormat(sig);
			return false;
		}
		bytesAPP1 = XUnpackUShort(pHeader->Size);
		if (bytesAPP1 < 8) {
			SetError_InvalidFormat(sig);
			return false;
		}
		if (::memcmp(pHeader->ExifCode, "Exif\0\0", 6) != 0) {
			SetError_InvalidFormat(sig);
			return false;
		}
	} while (0);
	if (!ReadBuff(sig, stream, buff, bytesAPP1)) return false;
	if (::memcmp(buff, "MM", 2) == 0) {
		TIFF_BE *pTIFF = reinterpret_cast<TIFF_BE *>(buff + 2);
		
		
	} else if (::memcmp(buff, "II", 2) == 0) {
		TIFF_LE *pTIFF = reinterpret_cast<TIFF_LE *>(buff + 2);
		
		if (XUnpackUShort(pTIFF->Code) != 0x002a) {
			SetError_InvalidFormat(sig);
			return false;
		}
		ParseIFD(env, sig, buff, bytesAPP1, XUnpackULong(pTIFF->Offset0thIFD));
	}
	//GetConsole()->Dump(sig, buff, bytesAPP1);
	return true;
}

//-----------------------------------------------------------------------------
// Gura interfaces for exif
//-----------------------------------------------------------------------------
// implementation of class exif
Gura_ImplementUserClass(exif)
{
}

}}
