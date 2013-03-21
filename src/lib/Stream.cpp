#include "stdafx.h"

namespace Gura {

//-----------------------------------------------------------------------------
// SimpleStream
//-----------------------------------------------------------------------------
void SimpleStream::Print(Signal sig, const char *str)
{
	for ( ; *str != '\0'; str++) PutChar(sig, *str);
}

void SimpleStream::Println(Signal sig, const char *str)
{
	Print(sig, str);
	PutChar(sig, '\n');
}

void SimpleStream::Printf(Signal sig, const char *format, const ValueList &valList)
{
	String str = Formatter::Format(sig, format, valList);
	if (sig.IsSignalled()) return;
	Print(sig, str.c_str());
}

void SimpleStream::PrintSignal(Signal sig, const Signal &sigToPrint)
{
	if (sig.GetSignalType() == SIGTYPE_Error) {
		Println(sig, sigToPrint.GetErrString().c_str());
		Print(sig, sigToPrint.GetErrTrace().c_str());
	} else {
		Println(sig, sigToPrint.GetSignalName());
	}
}

void SimpleStream::Dump(Signal sig, const void *buff, size_t bytes, bool upperFlag)
{
	int iCol = 0;
	String strHex, strASCII;
	const unsigned char *p = reinterpret_cast<const unsigned char *>(buff);
	for (size_t i = 0; i < bytes; i++, p++) {
		unsigned char ch = *p;
		char buff[8];
		if (upperFlag) {
			::sprintf(buff, (iCol > 0)? " %02X" : "%02X", ch);
		} else {
			::sprintf(buff, (iCol > 0)? " %02x" : "%02x", ch);
		}
		strHex += buff;
		strASCII += (0x20 <= ch && ch < 0x7f)? ch : '.';
		iCol++;
		if (iCol == 16) {
			String strLine = strHex;
			strLine += "  ";
			strLine += strASCII;
			Println(sig, strLine.c_str());
			if (sig.IsSignalled()) return;
			strHex.clear();
			strASCII.clear();
			iCol = 0;
		}
	}
	if (iCol > 0) {
		String strLine = strHex;
		for ( ; iCol < 16; iCol++) strLine += "   ";
		strLine += "  ";
		strLine += strASCII;
		Println(sig, strLine.c_str());
	}
}

//-----------------------------------------------------------------------------
// SimpleStream_StringRead
//-----------------------------------------------------------------------------
int SimpleStream_StringRead::GetChar(Signal sig)
{
	if (_pStr == _pEnd) return -1;
	char ch = *_pStr++;
	return static_cast<unsigned char>(ch);
}

void SimpleStream_StringRead::PutChar(Signal sig, char ch)
{
}

//-----------------------------------------------------------------------------
// SimpleStream_StringWrite
//-----------------------------------------------------------------------------
int SimpleStream_StringWrite::GetChar(Signal sig)
{
	return -1;
}

void SimpleStream_StringWrite::PutChar(Signal sig, char ch)
{
	_str += ch;
}

//-----------------------------------------------------------------------------
// Stream
//-----------------------------------------------------------------------------
Stream::Stream(Signal sig, unsigned long attr) :
						_cntRef(1), _sig(sig), _attr(attr), _offsetCur(0)
{
	_peek.buff = NULL;
	_peek.bytes = 0;
	_peek.offsetRead = 0;
}

Stream::~Stream()
{
	ReleaseCodec();
	delete[] _peek.buff;
}

void Stream::Close()
{
	DoClose(_sig);
	_attr &= ~(ATTR_Readable | ATTR_Writable | ATTR_Append);
}

bool Stream::InstallCodec(const char *encoding, bool processEOLFlag)
{
	if (encoding == NULL) {
		ReleaseCodec();
		return true;
	}
	CodecFactory *pCodecFactory = CodecFactory::Lookup(encoding);
	if (pCodecFactory == NULL) return false;
	ReleaseCodec();
	_encoding = encoding;
	_pDecoder.reset(pCodecFactory->CreateDecoder(true));
	_pEncoder.reset(pCodecFactory->CreateEncoder(processEOLFlag));
	return true;
}

void Stream::CopyCodec(Stream *pStream)
{
	Codec_Decoder *pDecoder = pStream->GetDecoder();
	Codec_Encoder *pEncoder = pStream->GetEncoder();
	_pDecoder.reset((pDecoder == NULL)? NULL : pDecoder->Duplicate());
	_pEncoder.reset((pEncoder == NULL)? NULL : pEncoder->Duplicate());
}

void Stream::CopyCodec(Object_codec *pObjCodec)
{
	Codec_Decoder *pDecoder = pObjCodec->GetDecoder();
	Codec_Encoder *pEncoder = pObjCodec->GetEncoder();
	_pDecoder.reset((pDecoder == NULL)? NULL : pDecoder->Duplicate());
	_pEncoder.reset((pEncoder == NULL)? NULL : pEncoder->Duplicate());
}

void Stream::ReleaseCodec()
{
	_encoding.clear();
	_pDecoder.reset(NULL);
	_pEncoder.reset(NULL);
}

void Stream::PutChar(Signal sig, char ch)
{
	if (_pEncoder.get() == NULL) {
		DoPutChar(sig, ch);
	} else {
		char chConv;
		Codec::Result rtn = _pEncoder->FeedChar(ch, chConv);
		if (rtn == Codec::RESULT_Complete) {
			DoPutChar(sig, chConv);
			while (_pEncoder->FollowChar(chConv)) DoPutChar(sig, chConv);
		} else if (rtn == Codec::RESULT_Error) {
			// nothing to do
		}
	}
}

int Stream::GetChar(Signal sig)
{
	if (_pDecoder.get() == NULL) return DoGetChar(sig);
	char chConv;
	if (_pDecoder->FollowChar(chConv)) return static_cast<unsigned char>(chConv);
	for (;;) {
		int ch = DoGetChar(sig);
		if (ch < 0) return ch;
		Codec::Result rtn = _pDecoder->FeedChar(static_cast<char>(ch), chConv);
		if (rtn == Codec::RESULT_Complete) {
			break;
		} else if (rtn == Codec::RESULT_Error) {
			sig.SetError(ERR_CodecError, "not a valid character of %s", _pDecoder->GetName());
			return -1;
		}
	}
	return static_cast<unsigned char>(chConv);
}

void Stream::FlushConsole()
{
}

bool Stream::GetAttribute(Attribute &attr)
{
	return false;
}

bool Stream::SetAttribute(const Attribute &attr)
{
	return false;
}

size_t Stream::DoRead(Signal sig, void *buff, size_t len)
{
	return 0;
}

size_t Stream::DoWrite(Signal sig, const void *buff, size_t len)
{
	return 0;
}

bool Stream::DoSeek(Signal sig, long offset, size_t offsetPrev, SeekMode seekMode)
{
	return true;
}

bool Stream::DoFlush(Signal sig)
{
	return true;
}

bool Stream::DoClose(Signal sig)
{
	return true;
}

size_t Stream::DoGetSize()
{
	return InvalidSize;
}

int Stream::DoGetChar(Signal sig)
{
	unsigned char ch;
	if (Read(sig, &ch, 1) == 0) return -1;
	return ch;
}

void Stream::DoPutChar(Signal sig, char ch)
{
	Write(sig, &ch, 1);
}

Object *Stream::DoGetStatObj(Signal sig)
{
	sig.SetError(ERR_IOError, "can't retrieve stat object");
	return NULL;
}

size_t Stream::Read(Signal sig, void *buff, size_t len)
{
	char *p = reinterpret_cast<char *>(buff);
	size_t bytesFromPeek = 0;
	if (_peek.buff != NULL) {
		bytesFromPeek = _peek.bytes - _peek.offsetRead;
		if (bytesFromPeek > len) bytesFromPeek = len;
		::memcpy(p, _peek.buff + _peek.offsetRead, bytesFromPeek);
		p += bytesFromPeek;
		_peek.offsetRead += bytesFromPeek;
		if (_peek.offsetRead >= _peek.bytes) {
			delete[] _peek.buff;
			_peek.buff = NULL;
			_peek.bytes = 0;
			_peek.offsetRead = 0;
		}
		len -= bytesFromPeek;
	}
	if (len == 0) {
		_offsetCur += bytesFromPeek;
		return bytesFromPeek;
	}
	size_t bytesRead = bytesFromPeek + DoRead(sig, p, len);
	_offsetCur += bytesRead;
	return bytesRead;
}

size_t Stream::Write(Signal sig, const void *buff, size_t len)
{
	size_t rtn = DoWrite(sig, buff, len);
	_offsetCur += rtn;
	return rtn;
}

size_t Stream::Peek(Signal sig, void *buff, size_t len)
{
	if (len == 0) return 0;
	if (_peek.buff == NULL) {
		_peek.buff = new char [len];
		_peek.bytes = DoRead(sig, _peek.buff, len);
		_peek.offsetRead = 0;
		if (sig.IsSignalled()) return 0;
	} else if (_peek.bytes < len) {
		char *buffNew = new char [len];
		::memcpy(buffNew, _peek.buff, _peek.bytes);
		size_t bytesAdd = DoRead(sig, buffNew + _peek.bytes, len - _peek.bytes);
		if (sig.IsSignalled()) return 0;
		delete[] _peek.buff;
		_peek.buff = buffNew;
		_peek.bytes += bytesAdd;
		_peek.offsetRead = 0;
	}
	size_t bytesToPeek = ChooseMin(_peek.bytes, len);
	::memcpy(buff, _peek.buff, bytesToPeek);
	return bytesToPeek;
}

bool Stream::Seek(Signal sig, long offset, SeekMode seekMode)
{
	size_t offsetPrev = _offsetCur;
	if (seekMode == SeekSet) {
		_offsetCur = static_cast<size_t>(offset);
	} else if (seekMode == SeekCur) {
		_offsetCur = _offsetCur + offset;
	} else {
		// this must not happen because illegal value has to be rejected before.
		return false;
	}
	if (_peek.buff == NULL) return DoSeek(sig, offset, offsetPrev, seekMode);
	if (_offsetCur < offsetPrev) {
		size_t bytesPeeked = _peek.bytes;
		if (_peek.offsetRead >= offsetPrev - _offsetCur) {
			_peek.offsetRead -= (offsetPrev - _offsetCur);
			return true;
		}
		delete[] _peek.buff;
		_peek.buff = NULL;
		_peek.bytes = 0;
		_peek.offsetRead = 0;
		if (seekMode == SeekSet) return DoSeek(sig, offset, offsetPrev, SeekSet);
		offset -= static_cast<long>(bytesPeeked);
		return DoSeek(sig, offset, offsetPrev, SeekCur);
	} else {
		if (_peek.offsetRead + _offsetCur - offsetPrev <= _peek.bytes) {
			_peek.offsetRead += _offsetCur - offsetPrev;
			return true;
		}
		size_t bytesTrail = _peek.bytes - _peek.offsetRead;
		delete[] _peek.buff;
		_peek.buff = NULL;
		_peek.bytes = 0;
		_peek.offsetRead = 0;
		if (seekMode == SeekSet) return DoSeek(sig, offset, offsetPrev, SeekSet);
		offset -= static_cast<long>(bytesTrail);
		return DoSeek(sig, offset, offsetPrev, SeekCur);
	}
}

bool Stream::Flush(Signal sig)
{
	return DoFlush(sig);
}

bool Stream::HasNameSuffix(const char *suffix, bool ignoreCase) const
{
	return EndsWith(GetName(), suffix, ignoreCase) != NULL;
}

bool Stream::CheckReadable(Signal sig) const
{
	if (IsReadable()) return true;
	sig.SetError(ERR_IOError, "stream is not readable");
	return false;
}

bool Stream::CheckWritable(Signal sig) const
{
	if (IsWritable()) return true;
	sig.SetError(ERR_IOError, "stream is not writable");
	return false;
}

bool Stream::CheckBwdSeekable(Signal sig) const
{
	if (IsBwdSeekable()) return true;
	sig.SetError(ERR_IOError, "stream is not capable of backward seeking");
	return false;
}

bool Stream::Compare(Signal sig, Stream &stream)
{
	if (!CheckReadable(sig) || !stream.CheckReadable(sig)) return false;
	const size_t bytesBuff = 1024 * 16;
	OAL::Memory memory(bytesBuff * 2);
	void *buff1 = memory.GetPointer(0);
	void *buff2 = memory.GetPointer(bytesBuff);
	bool sameFlag = false;
	for (;;) {
		size_t bytesRead1 = Read(sig, buff1, bytesBuff);
		if (sig.IsSignalled()) return false;
		size_t bytesRead2 = stream.Read(sig, buff2, bytesBuff);
		if (sig.IsSignalled()) return false;
		if (bytesRead1 != bytesRead2) {
			break;
		} else if (bytesRead1 == 0) {
			sameFlag = true;
			break;
		} else if (::memcmp(buff1, buff2, bytesRead1) != 0) {
			break;
		}
	}
	return sameFlag;
}

bool Stream::ReadToStream(Environment &env, Signal sig, Stream &streamDst,
			size_t bytesUnit, bool finalizeFlag, const Function *pFuncFilter)
{
	if (!CheckReadable(sig) || !streamDst.CheckWritable(sig)) return false;
	Attribute attr;
	bool validAttrFlag = false;
	if (finalizeFlag) {
		validAttrFlag = GetAttribute(attr);
	}
	OAL::Memory memory(bytesUnit);
	char *buff = reinterpret_cast<char *>(memory.GetPointer());
	for (;;) {
		size_t bytesRead = Read(sig, buff, bytesUnit);
		if (bytesRead == 0) break;
		if (pFuncFilter != NULL) {
			Value value(new Object_binary(env, buff, bytesUnit, false));
			ValueList valListArg(value);
			Args argsSub(valListArg);
			Value rtn = pFuncFilter->Eval(env, sig, argsSub);
			if (sig.IsSignalled()) return false;
			if (rtn.IsBinary()) {
				const Binary &buffRtn = rtn.GetBinary();
				streamDst.Write(sig, buffRtn.data(), buffRtn.size());
				if (sig.IsSignalled()) return false;
				continue;
			}
		}
		streamDst.Write(sig, buff, bytesRead);
		if (sig.IsSignalled()) return false;
	}
	if (sig.IsSignalled()) return false;
	if (finalizeFlag) {
		streamDst.Close();
		if (sig.IsSignalled()) return false;
		if (validAttrFlag) streamDst.SetAttribute(attr);
		return true;
	}
	if (!streamDst.Flush(sig)) return false;
	return true;
}

bool Stream::SerializeBoolean(Signal sig, bool num)
{
	unsigned char numRaw = static_cast<unsigned char>(num);
	return Write(sig, &numRaw, sizeof(numRaw)) == sizeof(numRaw);
}

bool Stream::DeserializeBoolean(Signal sig, bool &num)
{
	unsigned char numRaw = 0;
	if (!Read(sig, &numRaw, sizeof(numRaw)) == sizeof(numRaw)) return false;
	num = (numRaw != 0);
	return true;
}

bool Stream::SerializeUChar(Signal sig, unsigned char num)
{
	return Write(sig, &num, sizeof(num)) == sizeof(num);
}

bool Stream::DeserializeUChar(Signal sig, unsigned char &num)
{
	return Read(sig, &num, sizeof(num)) == sizeof(num);
}

bool Stream::SerializeUShort(Signal sig, unsigned short num)
{
	unsigned char buff[2] = {
		static_cast<unsigned char>((num >> 0) & 0xff),
		static_cast<unsigned char>((num >> 8) & 0xff),
	};
	return Write(sig, buff, sizeof(buff)) == sizeof(buff);
}

bool Stream::DeserializeUShort(Signal sig, unsigned short &num)
{
	unsigned char buff[2];
	if (Read(sig, buff, sizeof(buff)) != sizeof(buff)) return false;
	num =
		(static_cast<unsigned short>(buff[0]) << 0) +
		(static_cast<unsigned short>(buff[1]) << 8);
	return true;
}

bool Stream::SerializeULong(Signal sig, unsigned long num)
{
	unsigned char buff[4] = {
		static_cast<unsigned char>((num >> 0) & 0xff),
		static_cast<unsigned char>((num >> 8) & 0xff),
		static_cast<unsigned char>((num >> 16) & 0xff),
		static_cast<unsigned char>((num >> 24) & 0xff),
	};
	return Write(sig, buff, sizeof(buff)) == sizeof(buff);
}

bool Stream::DeserializeULong(Signal sig, unsigned long &num)
{
	unsigned char buff[4];
	if (Read(sig, buff, sizeof(buff)) != sizeof(buff)) return false;
	num =
		(static_cast<unsigned long>(buff[0]) << 0) +
		(static_cast<unsigned long>(buff[1]) << 8) +
		(static_cast<unsigned long>(buff[2]) << 16) +
		(static_cast<unsigned long>(buff[3]) << 24);
	return true;
}

bool Stream::SerializeUInt64(Signal sig, uint64 num)
{
	unsigned char buff[8] = {
		static_cast<unsigned char>((num >> 0) & 0xff),
		static_cast<unsigned char>((num >> 8) & 0xff),
		static_cast<unsigned char>((num >> 16) & 0xff),
		static_cast<unsigned char>((num >> 24) & 0xff),
		static_cast<unsigned char>((num >> 32) & 0xff),
		static_cast<unsigned char>((num >> 40) & 0xff),
		static_cast<unsigned char>((num >> 48) & 0xff),
		static_cast<unsigned char>((num >> 56) & 0xff),
	};
	return Write(sig, buff, sizeof(buff)) == sizeof(buff);
}

bool Stream::DeserializeUInt64(Signal sig, uint64 &num)
{
	unsigned char buff[8];
	if (Read(sig, buff, sizeof(buff)) != sizeof(buff)) return false;
	num =
		(static_cast<uint64>(buff[0]) << 0) +
		(static_cast<uint64>(buff[1]) << 8) +
		(static_cast<uint64>(buff[2]) << 16) +
		(static_cast<uint64>(buff[3]) << 24) +
		(static_cast<uint64>(buff[4]) << 32) +
		(static_cast<uint64>(buff[5]) << 40) +
		(static_cast<uint64>(buff[6]) << 48) +
		(static_cast<uint64>(buff[7]) << 56);
	return true;
}

bool Stream::SerializeDouble(Signal sig, double num)
{
	unsigned char *buff = reinterpret_cast<unsigned char *>(&num);
	return Write(sig, buff, sizeof(num)) == sizeof(num);
}

bool Stream::DeserializeDouble(Signal sig, double &num)
{
	unsigned char *buff = reinterpret_cast<unsigned char *>(&num);
	return Read(sig, buff, sizeof(num)) == sizeof(num);
}

bool Stream::SerializeString(Signal sig, const char *str)
{
	unsigned long len = static_cast<unsigned long>(::strlen(str));
	if (!SerializePackedULong(sig, len)) return false;
	return Write(sig, str, len) == len;
}

bool Stream::DeserializeString(Signal sig, String &str)
{
	unsigned long len = 0;
	if (!DeserializePackedULong(sig, len)) return false;
	if (len == 0) {
		str.clear();
		return true;
	}
	char *buff = new char [len + 1];
	if (Read(sig, buff, len) != len) {
		delete[] buff;
		return false;
	}
	buff[len] = '\0';
	str = buff;
	delete[] buff;
	return true;
}

bool Stream::SerializeBinary(Signal sig, const Binary &binary)
{
	unsigned long len = static_cast<unsigned long>(binary.size());
	if (!SerializePackedULong(sig, len)) return false;
	return Write(sig, binary.data(), len) == len;
}

bool Stream::DeserializeBinary(Signal sig, Binary &binary)
{
	unsigned long len = 0;
	if (!DeserializePackedULong(sig, len)) return false;
	if (len == 0) {
		binary.clear();
		return true;
	}
	char *buff = new char [len];
	if (Read(sig, buff, len) != len) {
		delete[] buff;
		return false;
	}
	binary = Binary(buff, len);
	delete[] buff;
	return true;
}

bool Stream::SerializeSymbol(Signal sig, const Symbol *pSymbol)
{
	return SerializeString(sig, pSymbol->GetName());
}

bool Stream::DeserializeSymbol(Signal sig, const Symbol **ppSymbol)
{
	String str;
	if (!DeserializeString(sig, str)) return false;
	*ppSymbol = Symbol::Add(str.c_str());
	return true;
}

bool Stream::SerializeSymbolSet(Signal sig, const SymbolSet &symbolSet)
{
	unsigned long len = static_cast<unsigned long>(symbolSet.size());
	if (!SerializePackedULong(sig, len)) return false;
	foreach_const (SymbolSet, ppSymbol, symbolSet) {
		if (!SerializeSymbol(sig, *ppSymbol)) return false;
	}
	return true;
}

bool Stream::DeserializeSymbolSet(Signal sig, SymbolSet &symbolSet)
{
	unsigned long len = 0;
	if (!DeserializePackedULong(sig, len)) return false;
	symbolSet.clear();
	if (len == 0) return true;
	const Symbol *pSymbol = NULL;
	while (len-- > 0) {
		if (!DeserializeSymbol(sig, &pSymbol)) return false;
		symbolSet.insert(pSymbol);
	}
	return true;
}

bool Stream::SerializeSymbolList(Signal sig, const SymbolList &symbolList)
{
	unsigned long len = static_cast<unsigned long>(symbolList.size());
	if (!SerializePackedULong(sig, len)) return false;
	foreach_const (SymbolList, ppSymbol, symbolList) {
		if (!SerializeSymbol(sig, *ppSymbol)) return false;
	}
	return true;
}

bool Stream::DeserializeSymbolList(Signal sig, SymbolList &symbolList)
{
	unsigned long len = 0;
	if (!DeserializePackedULong(sig, len)) return false;
	symbolList.clear();
	if (len == 0) return true;
	symbolList.reserve(len);
	const Symbol *pSymbol = NULL;
	while (len-- > 0) {
		if (!DeserializeSymbol(sig, &pSymbol)) return false;
		symbolList.push_back(pSymbol);
	}
	return true;
}

bool Stream::SerializePackedULong(Signal sig, unsigned long num)
{
	unsigned char buff[16];
	size_t bytesBuff = 0;
	if (num == 0) {
		buff[bytesBuff++] = 0x00;
	} else {
		while (num > 0) {
			unsigned char data = static_cast<unsigned char>(num & 0x7f);
			num >>= 7;
			if (num != 0) data |= 0x80;
			buff[bytesBuff++] = data;
		}
	}
	return Write(sig, buff, bytesBuff) == bytesBuff;
}

bool Stream::DeserializePackedULong(Signal sig, unsigned long &num)
{
	num = 0;
	unsigned char data = 0x00;
	for (size_t bytesBuff = 0; bytesBuff < 5; bytesBuff++) {
		if (Read(sig, &data, sizeof(data)) != sizeof(data)) return false;
		num = (num << 7) + (data & 0x7f);
		if ((data & 0x80) == 0x00) break;
	}
	if (data & 0x80) {
		sig.SetError(ERR_FormatError, "invalid format of packed ULong in serialized data");
		return false;
	}
	return true;
}

Stream *Stream::Prefetch(Signal sig, Stream *pStreamSrc,
										bool deleteSrcFlag, size_t bytesUnit)
{
	Stream_Prefetch *pStreamPrefetch =
			new Stream_Prefetch(sig, Stream::Reference(pStreamSrc), bytesUnit);
	pStreamPrefetch->DoPrefetch(sig);
	if (deleteSrcFlag) Stream::Delete(pStreamSrc);
	if (sig.IsSignalled()) {
		Stream::Delete(pStreamPrefetch);
		return NULL;
	}
	return pStreamPrefetch;
}

//-----------------------------------------------------------------------------
// StreamDumb
//-----------------------------------------------------------------------------
StreamDumb::StreamDumb(Signal sig) : Stream(sig, ATTR_Writable)
{
}

StreamDumb::~StreamDumb()
{
}

const char *StreamDumb::GetName() const
{
	return "dumb";
}

const char *StreamDumb::GetIdentifier() const
{
	return "dumb";
}

bool StreamDumb::GetAttribute(Attribute &attr)
{
	return false;
}

bool StreamDumb::SetAttribute(const Attribute &attr)
{
	return false;
}

size_t StreamDumb::DoRead(Signal sig, void *buff, size_t len)
{
	return 0;
}

size_t StreamDumb::DoWrite(Signal sig, const void *buff, size_t len)
{
	return len;
}

bool StreamDumb::DoSeek(Signal sig, long offset, size_t offsetPrev, SeekMode seekMode)
{
	return true;
}

bool StreamDumb::DoFlush(Signal sig)
{
	return true;
}

bool StreamDumb::DoClose(Signal sig)
{
	return true;
}

size_t StreamDumb::DoGetSize()
{
	return 0;
}

//-----------------------------------------------------------------------------
// StreamMemReader
//-----------------------------------------------------------------------------
StreamMemReader::StreamMemReader(Signal sig, const void *buff, size_t bytes) :
				Stream(sig, ATTR_BwdSeekable | ATTR_Readable),
				_buff(reinterpret_cast<const char *>(buff)), _bytes(bytes)
{
}

StreamMemReader::~StreamMemReader()
{
}

const char *StreamMemReader::GetName() const
{
	return "MemReader";
}

const char *StreamMemReader::GetIdentifier() const
{
	return NULL;
}

bool StreamMemReader::GetAttribute(Attribute &attr)
{
	return false;
}

bool StreamMemReader::SetAttribute(const Attribute &attr)
{
	return false;
}

size_t StreamMemReader::DoRead(Signal sig, void *buff, size_t len)
{
	if (_offsetCur > _bytes) {
		sig.SetError(ERR_IndexError, "out of range");
		return 0;
	}
	size_t lenRest = _bytes - _offsetCur;
	size_t lenRead = ChooseMin(lenRest, len);
	::memcpy(buff, _buff + _offsetCur, lenRead);
	_offsetCur += lenRead;
	return lenRead;
}

size_t StreamMemReader::DoWrite(Signal sig, const void *buff, size_t len)
{
	return 0;
}

bool StreamMemReader::DoSeek(Signal sig, long offset, size_t offsetPrev, SeekMode seekMode)
{
	if (seekMode == SeekSet) {
		_offsetCur = static_cast<size_t>(offset);
	} else if (seekMode == SeekCur) {
		_offsetCur += offset;
	}
	return true;
}

bool StreamMemReader::DoFlush(Signal sig)
{
	return true;
}

bool StreamMemReader::DoClose(Signal sig)
{
	return true;
}

size_t StreamMemReader::DoGetSize()
{
	return _bytes;
}

//-----------------------------------------------------------------------------
// Stream_Prefetch
//-----------------------------------------------------------------------------
Stream_Prefetch::Stream_Prefetch(Signal sig, Stream *pStreamSrc, size_t bytesUnit) :
			Stream(sig, ATTR_Readable), _pStreamSrc(pStreamSrc),
			_offset(0), _bytesAll(0), _bytesUnit(bytesUnit)
{
	CopyCodec(pStreamSrc);
}

Stream_Prefetch::~Stream_Prefetch()
{
	foreach (MemoryList, ppMemory, _memoryList) {
		OAL::Memory *pMemory = *ppMemory;
		delete pMemory;
	}
}

const char *Stream_Prefetch::GetName() const
{
	return _pStreamSrc->GetName();
}

const char *Stream_Prefetch::GetIdentifier() const
{
	return _pStreamSrc->GetIdentifier();
}

bool Stream_Prefetch::GetAttribute(Attribute &attr)
{
	return _pStreamSrc->GetAttribute(attr);
}

bool Stream_Prefetch::SetAttribute(const Attribute &attr)
{
	return _pStreamSrc->SetAttribute(attr);
}

size_t Stream_Prefetch::DoRead(Signal sig, void *buff, size_t len)
{
	size_t iMemory = _offset / _bytesUnit;
	if (iMemory >= _memoryList.size()) {
		sig.SetError(ERR_IndexError, "out of range");
		return 0;
	}
	MemoryList::iterator ppMemory = _memoryList.begin() + iMemory;
	char *buffDst = reinterpret_cast<char *>(buff);
	size_t offsetUnit = _offset % _bytesUnit;
	size_t bytesCopied = 0;
	size_t bytesRest = len;
	for ( ; ppMemory != _memoryList.end() && bytesRest > 0; ppMemory++) {
		OAL::Memory *pMemory = *ppMemory;
		size_t bytesToCopy = _bytesUnit - offsetUnit;
		bytesToCopy = ChooseMin(bytesToCopy, bytesRest);
		::memcpy(buffDst + bytesCopied, pMemory->GetPointer(offsetUnit), bytesToCopy);
		offsetUnit = 0;
		_offset += bytesToCopy;
		bytesCopied += bytesToCopy;
		bytesRest -= bytesToCopy;
	}
	return bytesCopied;
}

size_t Stream_Prefetch::DoWrite(Signal sig, const void *buff, size_t len)
{
	return 0;
}

bool Stream_Prefetch::DoSeek(Signal sig, long offset, size_t offsetPrev, SeekMode seekMode)
{
	if (seekMode == SeekSet) {
		_offset = static_cast<size_t>(offset);
	} else if (seekMode == SeekCur) {
		_offset += offset;
	}
	return true;
}

bool Stream_Prefetch::DoFlush(Signal sig)
{
	return false;
}

bool Stream_Prefetch::DoClose(Signal sig)
{
	return true;
}

size_t Stream_Prefetch::DoGetSize()
{
	return _bytesAll;
}

bool Stream_Prefetch::DoPrefetch(Signal sig)
{
	_bytesAll = 0;
	for (;;) {
		OAL::Memory *pMemory = new OAL::Memory(_bytesUnit);
		size_t bytes = _pStreamSrc->Read(sig, pMemory->GetPointer(), _bytesUnit);
		if (sig.IsSignalled()) {
			delete pMemory;
			return false;
		} else if (bytes == 0 || sig.IsSignalled()) {
			delete pMemory;
			break;
		}
		_memoryList.push_back(pMemory);
		_bytesAll += bytes;
		if (bytes < _bytesUnit) break;
	}
	return true;
}

//-----------------------------------------------------------------------------
// Stream_Base64Reader
//-----------------------------------------------------------------------------
Stream_Base64Reader::Stream_Base64Reader(Signal sig, Stream *pStreamSrc) :
			Stream(sig, ATTR_Readable), _pStreamSrc(pStreamSrc),
			_nChars(0), _nInvalid(0), _accum(0), _iBuffWork(0)
{
	CopyCodec(pStreamSrc);
}

Stream_Base64Reader::~Stream_Base64Reader()
{
}

const char *Stream_Base64Reader::GetName() const
{
	return _pStreamSrc->GetName();
}

const char *Stream_Base64Reader::GetIdentifier() const
{
	return _pStreamSrc->GetIdentifier();
}

bool Stream_Base64Reader::GetAttribute(Attribute &attr)
{
	return _pStreamSrc->GetAttribute(attr);
}

bool Stream_Base64Reader::SetAttribute(const Attribute &attr)
{
	return _pStreamSrc->SetAttribute(attr);
}

size_t Stream_Base64Reader::DoRead(Signal sig, void *buff, size_t len)
{
	unsigned char *buffp = reinterpret_cast<unsigned char *>(buff);
	size_t lenRead = 0;
	while (lenRead < len) {
		if (_iBuffWork > 0) {
			_iBuffWork--;
			buffp[lenRead++] = _buffWork[_iBuffWork];
			continue;
		}
		char ch;
		size_t bytes = _pStreamSrc->Read(sig, &ch, 1);
		if (bytes == 0) break;
		if ('A' <= ch && ch <= 'Z') {
			_accum = (_accum << 6) | (ch - 'A');
		} else if ('a' <= ch && ch <= 'z') {
			_accum = (_accum << 6) | (ch - 'a' + 26);
		} else if ('0' <= ch && ch <= '9') {
			_accum = (_accum << 6) | (ch - '0' + 52);
		} else if (ch == '+') {
			_accum = (_accum << 6) | 62;
		} else if (ch == '/') {
			_accum = (_accum << 6) | 63;
		} else if (ch == '=') {
			_nInvalid++;
			_accum = (_accum << 6);
		} else if (ch == ' ' || ch == '\t' || ch == '\r' || ch == '\n') {
			continue;
		} else {
			sig.SetError(ERR_FormatError, "invalid base64 format");
			return 0;
		}
		_nChars++;
		if (_nChars < 4) continue;
		if (_nInvalid == 0) {
			_buffWork[0] = static_cast<unsigned char>(_accum & 0xff); _accum >>= 8;
			_buffWork[1] = static_cast<unsigned char>(_accum & 0xff); _accum >>= 8;
			_buffWork[2] = static_cast<unsigned char>(_accum & 0xff);
			_iBuffWork = 3;
		} else if (_nInvalid == 1) {
			_accum >>= 8;
			_buffWork[0] = static_cast<unsigned char>(_accum & 0xff); _accum >>= 8;
			_buffWork[1] = static_cast<unsigned char>(_accum & 0xff);
			_iBuffWork = 2;
		} else if (_nInvalid == 2) {
			_accum >>= 8;
			_accum >>= 8;
			_buffWork[0] = static_cast<unsigned char>(_accum & 0xff);
			_iBuffWork = 1;
		} else {
			_iBuffWork = 0;
		}
		_nChars = 0, _nInvalid = 0, _accum = 0;
	}
	return lenRead;
}

size_t Stream_Base64Reader::DoWrite(Signal sig, const void *buff, size_t len)
{
	return 0;
}

bool Stream_Base64Reader::DoSeek(Signal sig, long offset, size_t offsetPrev, SeekMode seekMode)
{
	return false;
}

bool Stream_Base64Reader::DoFlush(Signal sig)
{
	return false;
}

bool Stream_Base64Reader::DoClose(Signal sig)
{
	return true;
}

size_t Stream_Base64Reader::DoGetSize()
{
	return 0;
}

//-----------------------------------------------------------------------------
// Stream_Base64Writer
//-----------------------------------------------------------------------------
const char Stream_Base64Writer::_chars[] =
	"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

Stream_Base64Writer::Stream_Base64Writer(Signal sig, Stream *pStreamDst, int nCharsPerLine) :
			Stream(sig, ATTR_Writable), _pStreamDst(pStreamDst),
			_nCharsPerLine(nCharsPerLine), _nChars(0), _iBuffWork(0)
{
	CopyCodec(pStreamDst);
	_nCharsPerLine = (_nCharsPerLine + 3) / 4 * 4;
}

Stream_Base64Writer::~Stream_Base64Writer()
{
}

const char *Stream_Base64Writer::GetName() const
{
	return _pStreamDst->GetName();
}

const char *Stream_Base64Writer::GetIdentifier() const
{
	return _pStreamDst->GetIdentifier();
}

bool Stream_Base64Writer::GetAttribute(Attribute &attr)
{
	return _pStreamDst->GetAttribute(attr);
}

bool Stream_Base64Writer::SetAttribute(const Attribute &attr)
{
	return _pStreamDst->SetAttribute(attr);
}

size_t Stream_Base64Writer::DoRead(Signal sig, void *buff, size_t len)
{
	return 0;
}

size_t Stream_Base64Writer::DoWrite(Signal sig, const void *buff, size_t len)
{
	const unsigned char *buffp = reinterpret_cast<const unsigned char *>(buff);
	size_t lenWritten = 0;
	for ( ; lenWritten < len; lenWritten++) {
		_buffWork[_iBuffWork++] = buffp[lenWritten];
		if (_iBuffWork < 3) continue;
		unsigned long accum =
			(static_cast<unsigned long>(_buffWork[0]) << 16) |
			(static_cast<unsigned long>(_buffWork[1]) << 8) |
			(static_cast<unsigned long>(_buffWork[2]) << 0);
		char buffDst[8];
		buffDst[0] = _chars[(accum >> 18) & 0x3f];
		buffDst[1] = _chars[(accum >> 12) & 0x3f];
		buffDst[2] = _chars[(accum >> 6) & 0x3f];
		buffDst[3] = _chars[(accum >> 0) & 0x3f];
		_nChars += 4;
		if (_nCharsPerLine > 0 && _nChars >= _nCharsPerLine) {
			buffDst[4] = '\r';
			buffDst[5] = '\n';
			_pStreamDst->Write(sig, buffDst, 6);
			_nChars = 0;
		} else {
			_pStreamDst->Write(sig, buffDst, 4);
		}
		if (sig.IsSignalled()) return 0;
		_iBuffWork = 0;
	}
	return lenWritten;
}

bool Stream_Base64Writer::DoSeek(Signal sig, long offset, size_t offsetPrev, SeekMode seekMode)
{
	return false;
}

bool Stream_Base64Writer::DoFlush(Signal sig)
{
	char buffDst[8];
	if (_iBuffWork == 0) {
		if (_nChars > 0 && _nCharsPerLine > 0) {
			buffDst[0] = '\r';
			buffDst[1] = '\n';
			_pStreamDst->Write(sig, buffDst, 2);
		}
		_nChars = 0;
		_iBuffWork = 0;
		return !sig.IsSignalled();
	} else if (_iBuffWork == 1) {
		unsigned long accum =
			static_cast<unsigned long>(_buffWork[0]) << 16;
		buffDst[0] = _chars[(accum >> 18) & 0x3f];
		buffDst[1] = _chars[(accum >> 12) & 0x3f];
		buffDst[2] = '=';
		buffDst[3] = '=';
	} else if (_iBuffWork == 2) {
		unsigned long accum =
			(static_cast<unsigned long>(_buffWork[0]) << 16) |
			(static_cast<unsigned long>(_buffWork[1]) << 8);
		buffDst[0] = _chars[(accum >> 18) & 0x3f];
		buffDst[1] = _chars[(accum >> 12) & 0x3f];
		buffDst[2] = _chars[(accum >> 6) & 0x3f];
		buffDst[3] = '=';
	} else { // _iBuffWork == 3
		unsigned long accum =
			(static_cast<unsigned long>(_buffWork[0]) << 16) |
			(static_cast<unsigned long>(_buffWork[1]) << 8) |
			(static_cast<unsigned long>(_buffWork[2]) << 0);
		buffDst[0] = _chars[(accum >> 18) & 0x3f];
		buffDst[1] = _chars[(accum >> 12) & 0x3f];
		buffDst[2] = _chars[(accum >> 6) & 0x3f];
		buffDst[3] = _chars[(accum >> 0) & 0x3f];
	}
	if (_nCharsPerLine > 0) {
		buffDst[4] = '\r';
		buffDst[5] = '\n';
		_pStreamDst->Write(sig, buffDst, 6);
	} else {
		_pStreamDst->Write(sig, buffDst, 4);
	}
	_nChars = 0;
	_iBuffWork = 0;
	return !sig.IsSignalled();
}

bool Stream_Base64Writer::DoClose(Signal sig)
{
	return DoFlush(sig);
}

size_t Stream_Base64Writer::DoGetSize()
{
	return 0;
}

//-----------------------------------------------------------------------------
// Stream_CRC32
//-----------------------------------------------------------------------------
Stream_CRC32::Stream_CRC32(Signal sig, Stream *pStreamDst) :
		Stream(sig, (pStreamDst == NULL)? ATTR_Writable : pStreamDst->GetAttr()),
		_pStreamDst(pStreamDst)
{
	CopyCodec(pStreamDst);
}

Stream_CRC32::~Stream_CRC32()
{
}

const char *Stream_CRC32::GetName() const
{
	return _pStreamDst.IsNull()? "" : _pStreamDst->GetName();
}

const char *Stream_CRC32::GetIdentifier() const
{
	return _pStreamDst.IsNull()? NULL : _pStreamDst->GetIdentifier();
}

size_t Stream_CRC32::DoRead(Signal sig, void *buff, size_t len)
{
	return _pStreamDst.IsNull()? 0 : _pStreamDst->Read(sig, buff, len);
}

size_t Stream_CRC32::DoWrite(Signal sig, const void *buff, size_t len)
{
	_crc32.Update(buff, len);
	return _pStreamDst.IsNull()? len : _pStreamDst->Write(sig, buff, len);
}

bool Stream_CRC32::DoSeek(Signal sig, long offset, size_t offsetPrev, SeekMode seekMode)
{
	return _pStreamDst.IsNull()? true : _pStreamDst->Seek(sig, offset, seekMode);
}

bool Stream_CRC32::DoFlush(Signal sig)
{
	return _pStreamDst.IsNull()? true : _pStreamDst->Flush(sig);
}

bool Stream_CRC32::DoClose(Signal sig)
{
	return _pStreamDst.IsNull()? 0 : _pStreamDst->DoClose(sig);
}

size_t Stream_CRC32::DoGetSize()
{
	return _pStreamDst.IsNull()? 0 : _pStreamDst->GetSize();
}

}
