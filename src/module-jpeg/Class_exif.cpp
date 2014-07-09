//-----------------------------------------------------------------------------
// Reference: http://www.exif.org/
//-----------------------------------------------------------------------------
#include "stdafx.h"
#include "Class_exif.h"

Gura_BeginModuleScope(jpeg)

//-----------------------------------------------------------------------------
// Object_exif implementation
//-----------------------------------------------------------------------------
Object_exif::Object_exif() : Object(Gura_UserClass(exif)), _bigendianFlag(false)
{
	_strip.validFlag = false;
	_strip.width = _strip.height = 0;
}

Object_exif::~Object_exif()
{
}

Object *Object_exif::Clone() const
{
	return NULL;
}

Value Object_exif::IndexGet(Environment &env, Signal sig, const Value &valueIdx)
{
	if (_pObj0thIFD.IsNull()) return Value::Null;
	return _pObj0thIFD->IndexGet(env, sig, valueIdx);
}

bool Object_exif::DoDirProp(Environment &env, Signal sig, SymbolSet &symbols)
{
	if (!Object::DoDirProp(env, sig, symbols)) return false;
	if (_pObj0thIFD.IsNull()) return true;
	symbols.insert(Gura_UserSymbol(ifd0));
	symbols.insert(Gura_UserSymbol(ifd1));
	symbols.insert(Gura_UserSymbol(thumbnail));
	symbols.insert(Gura_UserSymbol(thumbnail_jpeg));
	return _pObj0thIFD->DoDirProp(env, sig, symbols);
}

Value Object_exif::DoGetProp(Environment &env, Signal sig, const Symbol *pSymbol,
							const SymbolSet &attrs, bool &evaluatedFlag)
{
	if (_pObj0thIFD.IsNull()) return Value::Null;
	evaluatedFlag = true;
	if (pSymbol->IsIdentical(Gura_UserSymbol(endian))) {
		return Value(_bigendianFlag? Gura_UserSymbol(big) : Gura_UserSymbol(little));
	} else if (pSymbol->IsIdentical(Gura_UserSymbol(ifd0))) {
		return Value(Object_ifd::Reference(_pObj0thIFD.get()));
	} else if (pSymbol->IsIdentical(Gura_UserSymbol(ifd1))) {
		if (_pObj1stIFD.IsNull()) return Value::Null;
		return Value(Object_ifd::Reference(_pObj1stIFD.get()));
	} else if (pSymbol->IsIdentical(Gura_UserSymbol(thumbnail))) {
		if (_pObjBinaryThumbnail.IsNull()) return Value::Null;
		if (_pObjImageThumbnail.IsNull()) {
			AutoPtr<Object_image> pObjImage(new Object_image(env, new Image(Image::FORMAT_RGBA)));
			if (_strip.validFlag) {
				if (!pObjImage->GetImage()->AllocBuffer(sig, _strip.width, _strip.height, 0x00)) {
					return Value::Null;
				}
				const Binary &buff = _pObjBinaryThumbnail->GetBinary();
				size_t bytesExpect = _strip.width * _strip.height * 3;
				if (buff.size() < bytesExpect) {
					return Value::Null;
				}
				Binary::const_iterator p = buff.begin();
				std::auto_ptr<Image::Scanner> pScannerDst(
					pObjImage->GetImage()->CreateScanner(Image::SCAN_LeftTopHorz));
				do {
					unsigned char red = *p++;
					unsigned char green = *p++;
					unsigned char blue = *p++;
					pScannerDst->StorePixel(red, green, blue, 0);
				} while (pScannerDst->Next());
			} else {
				Stream_Binary stream(env, sig,
					Object_binary::Reference(_pObjBinaryThumbnail.get()), false);
				if (!ImageStreamer_JPEG::ReadStream(env, sig, pObjImage->GetImage(), stream)) {
					return Value::Null;
				}
			}
			_pObjImageThumbnail.reset(pObjImage.release());
		}
		return Value(Object_image::Reference(_pObjImageThumbnail.get()));
	} else if (pSymbol->IsIdentical(Gura_UserSymbol(thumbnail_jpeg))) {
		if (_pObjBinaryThumbnail.IsNull() || _strip.validFlag) return Value::Null;
		return Value(Object_binary::Reference(_pObjBinaryThumbnail.get()));
	}
	return _pObj0thIFD->DoGetProp(env, sig, pSymbol, attrs, evaluatedFlag);
}

String Object_exif::ToString(bool exprFlag)
{
	return String("<jpeg.exif>");
}

Object_exif *Object_exif::ReadStream(Environment &env, Signal sig, Stream &stream)
{
	AutoPtr<Memory> pMemory(new MemoryHeap(65536));
	char *buff = reinterpret_cast<char *>(pMemory->GetPointer());
	SHORT_BE *pShort = reinterpret_cast<SHORT_BE *>(buff);
	if (!ReadBuff(sig, stream, pShort, UNITSIZE_SHORT)) return NULL;
	if (Gura_UnpackUShort(pShort->num) != MARKER_SOI) {
		sig.SetError(ERR_FormatError, "invalid jpeg file");
		return NULL;
	}
	size_t bytesAPP1 = 0;
	for (;;) {
		if (!ReadBuff(sig, stream, pShort, UNITSIZE_SHORT)) return NULL;
		unsigned short marker = Gura_UnpackUShort(pShort->num);
		if (marker < MARKER_APP0 || MARKER_APP15 < marker) {
			return NULL;	// exif doesn't exist
		}
		if (!ReadBuff(sig, stream, pShort, UNITSIZE_SHORT)) return NULL;
		unsigned short bytes = Gura_UnpackUShort(pShort->num);
		if (bytes < UNITSIZE_SHORT) {
			sig.SetError(ERR_FormatError, "invalid jpeg file");
			return NULL;
		}
		if (marker == MARKER_APP1) {
			char code[6];
			if (!ReadBuff(sig, stream, code, 6)) return NULL;
			if (::memcmp(code, "Exif\0\0", 6) != 0) {
				return NULL;	// exif doesn't exist
			}
			bytesAPP1 = bytes;
			break;
		}
		if (!stream.Seek(sig, bytes - 2, Stream::SeekCur)) return NULL;
	}
	if (!ReadBuff(sig, stream, buff, bytesAPP1)) return NULL;
	AutoPtr<Object_exif> pObj(new Object_exif());
	if (::memcmp(buff, "MM", 2) == 0) {
		pObj->_bigendianFlag = true;
		TIFF_BE *pTIFF = reinterpret_cast<TIFF_BE *>(buff + 2);
		if (Gura_UnpackUShort(pTIFF->Code) != 0x002a) {
			SetError_InvalidFormat(sig);
			return NULL;
		}
		size_t offset = Gura_UnpackULong(pTIFF->Offset0thIFD);
		pObj->_pObj0thIFD.reset(ParseIFD_BE(env, sig, Symbol::Add("ifd0"),
										buff, bytesAPP1, offset, &offset));
		if (pObj->_pObj0thIFD.IsNull()) return NULL;
		if (offset != 0) {
			pObj->_pObj1stIFD.reset(ParseIFD_BE(env, sig, Symbol::Add("ifd1"),
										buff, bytesAPP1, offset, &offset));
			if (pObj->_pObj1stIFD.IsNull()) return NULL;
		}
	} else if (::memcmp(buff, "II", 2) == 0) {
		pObj->_bigendianFlag = false;
		TIFF_LE *pTIFF = reinterpret_cast<TIFF_LE *>(buff + 2);
		if (Gura_UnpackUShort(pTIFF->Code) != 0x002a) {
			SetError_InvalidFormat(sig);
			return NULL;
		}
		size_t offset = Gura_UnpackULong(pTIFF->Offset0thIFD);
		pObj->_pObj0thIFD.reset(ParseIFD_LE(env, sig, Symbol::Add("ifd0"),
										buff, bytesAPP1, offset, &offset));
		if (pObj->_pObj0thIFD.IsNull()) return NULL;
		if (offset != 0) {
			pObj->_pObj1stIFD.reset(ParseIFD_LE(env, sig, Symbol::Add("ifd1"),
										buff, bytesAPP1, offset, &offset));
			if (pObj->_pObj1stIFD.IsNull()) return NULL;
		}
	} else {
		SetError_InvalidFormat(sig);
		return NULL;
	}
	if (pObj->_pObj1stIFD.IsNull()) return pObj.release();
	// extract thumbnail image
	UShort compression = 0;
	Object_tag *pObjTag_Compression =
		pObj->_pObj1stIFD->GetTagOwner().FindById(TAG_Compression);
	if (pObjTag_Compression != NULL && pObjTag_Compression->GetType() == TYPE_SHORT) {
		compression = pObjTag_Compression->GetValue().GetUShort();
	}
	if (compression == 1) {	// uncompressed
		Object_tag *pObjTag_ImageWidth =
			pObj->_pObj1stIFD->GetTagOwner().FindById(TAG_ImageWidth);
		Object_tag *pObjTag_ImageLength =
			pObj->_pObj1stIFD->GetTagOwner().FindById(TAG_ImageLength);
		Object_tag *pObjTag_StripOffsets =
			pObj->_pObj1stIFD->GetTagOwner().FindById(TAG_StripOffsets);
		Object_tag *pObjTag_StripByteCounts =
			pObj->_pObj1stIFD->GetTagOwner().FindById(TAG_StripByteCounts);
		if (pObjTag_ImageWidth == NULL ||
					pObjTag_ImageLength == NULL ||
					pObjTag_StripOffsets == NULL ||
					pObjTag_StripByteCounts == NULL) {
			// nothing to do
		} else if (!pObjTag_ImageWidth->IsTypeSHORTorLONG() ||
					!pObjTag_ImageLength->IsTypeSHORTorLONG() ||
					!pObjTag_StripOffsets->IsTypeSHORTorLONG() ||
					!pObjTag_StripByteCounts->IsTypeSHORTorLONG()) {
			// nothing to do
		} else {
			pObj->_strip.validFlag = true;
			pObj->_strip.width = pObjTag_ImageWidth->GetValue().GetULong();
			pObj->_strip.height = pObjTag_ImageLength->GetValue().GetULong();
			size_t offsetThumbnail = pObjTag_StripOffsets->GetValue().GetULong();
			size_t bytesThumbnail = pObjTag_StripByteCounts->GetValue().GetULong();
			if (offsetThumbnail + bytesThumbnail >= bytesAPP1 - 1) {
				SetError_InvalidFormat(sig);
				return NULL;
			}
			pObj->_pObjBinaryThumbnail.reset(new Object_binary(env,
								buff + offsetThumbnail, bytesThumbnail, false));
		}
	} else if (compression == 6) {	// JPEG compression
		Object_tag *pObjTag_JPEGInterchangeFormat =
			pObj->_pObj1stIFD->GetTagOwner().FindById(TAG_JPEGInterchangeFormat);
		Object_tag *pObjTag_JPEGInterchangeFormatLength =
			 pObj->_pObj1stIFD->GetTagOwner().FindById(TAG_JPEGInterchangeFormatLength);
		if (pObjTag_JPEGInterchangeFormat == NULL ||
					pObjTag_JPEGInterchangeFormatLength == NULL) {
			// nothing to do
		} else if (pObjTag_JPEGInterchangeFormat->GetType() != TYPE_LONG ||
					pObjTag_JPEGInterchangeFormatLength->GetType() != TYPE_LONG) {
			// nothing to do
		} else {
			size_t offsetThumbnail = pObjTag_JPEGInterchangeFormat->GetValue().GetULong();
			size_t bytesThumbnail = pObjTag_JPEGInterchangeFormatLength->GetValue().GetULong();
			if (offsetThumbnail + bytesThumbnail >= bytesAPP1 - 1) {
				SetError_InvalidFormat(sig);
				return NULL;
			}
			pObj->_pObjBinaryThumbnail.reset(new Object_binary(env,
								buff + offsetThumbnail, bytesThumbnail, false));
		}
	} else {
		SetError_InvalidFormat(sig);
		return NULL;
	}
	return pObj.release();
}

//-----------------------------------------------------------------------------
// Gura interfaces for jpeg.exif
//-----------------------------------------------------------------------------
// jpeg.exif#each() {block?}
Gura_DeclareMethod(exif, each)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(exif, each)
{
	Object_exif *pThis = Object_exif::GetThisObj(args);
	Object_ifd *pObj0thIFD = pThis->GetObj0thIFD();
	return ReturnIterator(env, sig, args,
					new IteratorTag(Object_ifd::Reference(pObj0thIFD)));
}

// implementation of class exif
Gura_ImplementUserClass(exif)
{
	Gura_AssignMethod(exif, each);
}

Gura_EndModuleScope(jpeg)
