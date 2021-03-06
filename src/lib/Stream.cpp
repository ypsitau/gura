//=============================================================================
// Stream
//=============================================================================
#include "stdafx.h"

namespace Gura {

//-----------------------------------------------------------------------------
// SimpleStream
//-----------------------------------------------------------------------------
void SimpleStream::Print(Signal &sig, const char *str)
{
	for ( ; *str != '\0'; str++) PutChar(sig, *str);
}

void SimpleStream::Println(Signal &sig, const char *str)
{
	Print(sig, str);
	PutChar(sig, '\n');
}

void SimpleStream::PrintFmt(Signal &sig, const char *format, const ValueList &valList)
{
	String str = Formatter::FormatValueList(sig, format, valList);
	if (sig.IsSignalled()) return;
	Print(sig, str.c_str());
}

void SimpleStream::Printf(Signal &sig, const char *format, ...)
{
	va_list ap;
	va_start(ap, format);
	String str = Formatter::FormatV(sig, format, ap);
	va_end(ap);
	if (sig.IsSignalled()) return;
	Print(sig, str.c_str());
}

bool SimpleStream::ReadLine(Signal &sig, String &str, bool includeEOLFlag)
{
	int ch = GetChar(sig);
	if (ch < 0) return false;
	for ( ; ch >= 0; ch = GetChar(sig)) {
		if (ch == '\n') {
			if (includeEOLFlag) str += ch;
			break;
		}
		str += ch;
	}
	return !sig.IsSignalled();
}

bool SimpleStream::ReadLines(Signal &sig, StringList &strList, bool includeEOLFlag)
{
	for (;;) {
		String str;
		if (!ReadLine(sig, str, includeEOLFlag)) break;
		strList.push_back(str);
	}
	return !sig.IsSignalled();
}

void SimpleStream::Dump(Signal &sig, const void *buff, size_t bytes, bool upperFlag)
{
	int iCol = 0;
	String strHex, strASCII;
	const UChar *p = reinterpret_cast<const UChar *>(buff);
	for (size_t i = 0; i < bytes; i++, p++) {
		UChar ch = *p;
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
// Stream
//-----------------------------------------------------------------------------
Stream::Stream(Environment &env, UInt32 attr) :
	_cntRef(1), _sig(env.GetSignal()), _attr(attr), _offsetCur(0), _blockingFlag(false),
	_pCodec(Codec::CreateCodecNone(true, false))
{
	_peek.buff = nullptr;
	_peek.bytes = 0;
	_peek.offsetRead = 0;
}

Stream::~Stream()
{
	delete[] _peek.buff;
}

bool Stream::Close()
{
	return DoClose(_sig);
}

void Stream::SetCodec(Codec *pCodec)
{
	_pCodec.reset(pCodec);
}

void Stream::CopyCodec(Stream *pStream)
{
	CopyCodec(pStream->GetCodec());
}

void Stream::CopyCodec(const Codec *pCodec)
{
	if (pCodec != nullptr) {
		_pCodec.reset(pCodec->Duplicate());
	}
}

void Stream::PutChar(Signal &sig, char ch)
{
	Codec::Encoder *pEncoder = GetCodec()->GetEncoder();
	if (pEncoder == nullptr) {
		DoPutChar(sig, ch);
	} else {
		char chConv;
		Codec::Result rtn = pEncoder->FeedChar(ch, chConv);
		if (rtn == Codec::RESULT_Complete) {
			DoPutChar(sig, chConv);
			while (pEncoder->FollowChar(chConv)) DoPutChar(sig, chConv);
		} else if (rtn == Codec::RESULT_Error) {
			// nothing to do
		}
	}
}

String Stream::ReadChar(Signal &sig)
{
	char chConv = '\0';
	String str;
	Codec::Decoder *pDecoder = GetCodec()->GetDecoder();
	for (;;) {
		int ch = DoGetChar(sig);
		if (ch < 0) break;
		Codec::Result rtn = pDecoder->FeedChar(static_cast<char>(ch), chConv);
		if (rtn == Codec::RESULT_Complete) {
			str += chConv;
			break;
		} else if (rtn == Codec::RESULT_Error) {
			sig.SetError(ERR_CodecError, "not a valid character of %s", GetCodec()->GetEncoding());
			return "";
		}
	}
	while (pDecoder->FollowChar(chConv)) str += chConv;
	return str;
}

int Stream::GetChar(Signal &sig)
{
	char chConv = '\0';
	Codec::Decoder *pDecoder = GetCodec()->GetDecoder();
	if (pDecoder->FollowChar(chConv)) return static_cast<UChar>(chConv);
	for (;;) {
		int ch = DoGetChar(sig);
		if (ch < 0) return ch;
		Codec::Result rtn = pDecoder->FeedChar(static_cast<char>(ch), chConv);
		if (rtn == Codec::RESULT_Complete) {
			break;
		} else if (rtn == Codec::RESULT_Error) {
			sig.SetError(ERR_CodecError, "not a valid character of %s", GetCodec()->GetEncoding());
			return -1;
		}
	}
	return static_cast<UChar>(chConv);
}

bool Stream::GetAttribute(Attribute &attr)
{
	return false;
}

bool Stream::SetAttribute(const Attribute &attr)
{
	return false;
}

void Stream::SetBlocking(bool blockingFlag)
{
}

bool Stream::GetBlocking() const
{
	return _blockingFlag;
}

size_t Stream::DoRead(Signal &sig, void *buff, size_t len)
{
	return 0;
}

size_t Stream::DoWrite(Signal &sig, const void *buff, size_t len)
{
	return 0;
}

bool Stream::DoSeek(Signal &sig, long offset, size_t offsetPrev, SeekMode seekMode)
{
	return true;
}

bool Stream::DoFlush(Signal &sig)
{
	return true;
}

bool Stream::DoClose(Signal &sig)
{
	_attr &= ~(ATTR_Readable | ATTR_Writable | ATTR_Append);
	return true;
}

size_t Stream::DoGetSize()
{
	return InvalidSize;
}

int Stream::DoGetChar(Signal &sig)
{
	UChar ch;
	if (Read(sig, &ch, 1) == 0) return -1;
	return ch;
}

void Stream::DoPutChar(Signal &sig, char ch)
{
	Write(sig, &ch, 1);
}

Object *Stream::DoGetStatObj(Signal &sig)
{
	sig.SetError(ERR_IOError, "can't retrieve stat object");
	return nullptr;
}

size_t Stream::Read(Signal &sig, void *buff, size_t len)
{
	char *p = reinterpret_cast<char *>(buff);
	size_t bytesFromPeek = 0;
	if (_peek.buff != nullptr) {
		bytesFromPeek = _peek.bytes - _peek.offsetRead;
		if (bytesFromPeek > len) bytesFromPeek = len;
		::memcpy(p, _peek.buff + _peek.offsetRead, bytesFromPeek);
		p += bytesFromPeek;
		_peek.offsetRead += bytesFromPeek;
		if (_peek.offsetRead >= _peek.bytes) {
			delete[] _peek.buff;
			_peek.buff = nullptr;
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

size_t Stream::Write(Signal &sig, const void *buff, size_t len)
{
	size_t rtn = DoWrite(sig, buff, len);
	_offsetCur += rtn;
	return rtn;
}

size_t Stream::Peek(Signal &sig, void *buff, size_t len)
{
	if (len == 0) return 0;
	if (_peek.buff == nullptr) {
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

bool Stream::Seek(Signal &sig, long offset, SeekMode seekMode)
{
	size_t offsetPrev = _offsetCur;
	if (seekMode == SeekSet) {
		_offsetCur = static_cast<size_t>(offset);
	} else if (seekMode == SeekCur) {
		_offsetCur = _offsetCur + offset;
	} else if (seekMode == SeekEnd) {
		_offsetCur = DoGetSize();
		if (offset < 0 && _offsetCur < static_cast<size_t>(-offset)) {
			sig.SetError(ERR_IOError, "seek error");
			return false;
		}
	} else {
		// this must not happen because illegal value has to be rejected before.
		return false;
	}
	if (_peek.buff == nullptr) return DoSeek(sig, offset, offsetPrev, seekMode);
	if (_offsetCur < offsetPrev) {
		size_t bytesPeeked = _peek.bytes;
		if (_peek.offsetRead >= offsetPrev - _offsetCur) {
			_peek.offsetRead -= (offsetPrev - _offsetCur);
			return true;
		}
		delete[] _peek.buff;
		_peek.buff = nullptr;
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
		_peek.buff = nullptr;
		_peek.bytes = 0;
		_peek.offsetRead = 0;
		if (seekMode == SeekSet) return DoSeek(sig, offset, offsetPrev, SeekSet);
		offset -= static_cast<long>(bytesTrail);
		return DoSeek(sig, offset, offsetPrev, SeekCur);
	}
}

bool Stream::SkipLines(Signal &sig, size_t nLines)
{
	bool rtn = true;
	if (nLines == 0) return true;
	for (;;) {
		int ch = DoGetChar(sig);
		if (ch < 0) {
			rtn = sig.IsNoSignalled();
			break;
		}
		if (ch == '\n') {
			nLines--;
			if (nLines == 0) break;
		}
	}
	return rtn;
}

bool Stream::Flush(Signal &sig)
{
	return DoFlush(sig);
}

bool Stream::HasNameSuffix(const char *suffix, bool ignoreCase) const
{
	return EndsWith(GetName(), suffix, ignoreCase) != nullptr;
}

bool Stream::CheckReadable(Signal &sig) const
{
	if (IsReadable()) return true;
	sig.SetError(ERR_IOError, "stream is not readable");
	return false;
}

bool Stream::CheckWritable(Signal &sig) const
{
	if (IsWritable()) return true;
	sig.SetError(ERR_IOError, "stream is not writable");
	return false;
}

bool Stream::CheckBwdSeekable(Signal &sig) const
{
	if (IsBwdSeekable()) return true;
	sig.SetError(ERR_IOError, "stream is not capable of backward seeking");
	return false;
}

bool Stream::Compare(Signal &sig, Stream &stream)
{
	if (!CheckReadable(sig) || !stream.CheckReadable(sig)) return false;
	const size_t bytesBuff = 1024 * 16;
	AutoPtr<Memory> pMemory(new MemoryHeap(bytesBuff * 2));
	void *buff1 = pMemory->GetPointer(0);
	void *buff2 = pMemory->GetPointer(bytesBuff);
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

bool Stream::ReadToStream(Environment &env, Stream &streamDst,
			size_t bytesUnit, bool finalizeFlag, const Function *pFuncFilter)
{
	Signal &sig = env.GetSignal();
	if (!CheckReadable(sig) || !streamDst.CheckWritable(sig)) return false;
	Attribute attr;
	bool validAttrFlag = false;
	if (finalizeFlag) {
		validAttrFlag = GetAttribute(attr);
	}
	AutoPtr<Memory> pMemory(new MemoryHeap(bytesUnit));
	char *buff = reinterpret_cast<char *>(pMemory->GetPointer());
	for (;;) {
		size_t bytesRead = Read(sig, buff, bytesUnit);
		if (bytesRead == 0) break;
		if (pFuncFilter != nullptr) {
			Value value(new Object_binary(env, buff, bytesUnit, false));
			AutoPtr<Argument> pArgSub(new Argument(pFuncFilter));
			if (!pArgSub->StoreValue(env, value)) return false;
			Value rtn = pFuncFilter->Eval(env, *pArgSub);
			if (sig.IsSignalled()) return false;
			if (rtn.Is_binary()) {
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

bool Stream::SerializeBoolean(Signal &sig, bool num)
{
	UChar numRaw = static_cast<UChar>(num);
	return Write(sig, &numRaw, sizeof(numRaw)) == sizeof(numRaw);
}

bool Stream::DeserializeBoolean(Signal &sig, bool &num)
{
	UChar numRaw = 0;
	if (Read(sig, &numRaw, sizeof(numRaw)) != sizeof(numRaw)) return false;
	num = (numRaw != 0);
	return true;
}

bool Stream::SerializeUInt8(Signal &sig, UInt8 num)
{
	return Write(sig, &num, sizeof(num)) == sizeof(num);
}

bool Stream::DeserializeUInt8(Signal &sig, UInt8 &num)
{
	return Read(sig, &num, sizeof(num)) == sizeof(num);
}

bool Stream::SerializeUInt16(Signal &sig, UInt16 num)
{
	UChar buff[2] = {
		static_cast<UChar>((num >> 0) & 0xff),
		static_cast<UChar>((num >> 8) & 0xff),
	};
	return Write(sig, buff, sizeof(buff)) == sizeof(buff);
}

bool Stream::DeserializeUInt16(Signal &sig, UInt16 &num)
{
	UChar buff[2];
	if (Read(sig, buff, sizeof(buff)) != sizeof(buff)) return false;
	num =
		(static_cast<UInt16>(buff[0]) << 0) +
		(static_cast<UInt16>(buff[1]) << 8);
	return true;
}

bool Stream::SerializeUInt32(Signal &sig, UInt32 num)
{
	UChar buff[4] = {
		static_cast<UChar>((num >> 0) & 0xff),
		static_cast<UChar>((num >> 8) & 0xff),
		static_cast<UChar>((num >> 16) & 0xff),
		static_cast<UChar>((num >> 24) & 0xff),
	};
	return Write(sig, buff, sizeof(buff)) == sizeof(buff);
}

bool Stream::DeserializeUInt32(Signal &sig, UInt32 &num)
{
	UChar buff[4];
	if (Read(sig, buff, sizeof(buff)) != sizeof(buff)) return false;
	num =
		(static_cast<UInt32>(buff[0]) << 0) +
		(static_cast<UInt32>(buff[1]) << 8) +
		(static_cast<UInt32>(buff[2]) << 16) +
		(static_cast<UInt32>(buff[3]) << 24);
	return true;
}

bool Stream::SerializeUInt64(Signal &sig, UInt64 num)
{
	UChar buff[8] = {
		static_cast<UChar>((num >> 0) & 0xff),
		static_cast<UChar>((num >> 8) & 0xff),
		static_cast<UChar>((num >> 16) & 0xff),
		static_cast<UChar>((num >> 24) & 0xff),
		static_cast<UChar>((num >> 32) & 0xff),
		static_cast<UChar>((num >> 40) & 0xff),
		static_cast<UChar>((num >> 48) & 0xff),
		static_cast<UChar>((num >> 56) & 0xff),
	};
	return Write(sig, buff, sizeof(buff)) == sizeof(buff);
}

bool Stream::DeserializeUInt64(Signal &sig, UInt64 &num)
{
	UChar buff[8];
	if (Read(sig, buff, sizeof(buff)) != sizeof(buff)) return false;
	num =
		(static_cast<UInt64>(buff[0]) << 0) +
		(static_cast<UInt64>(buff[1]) << 8) +
		(static_cast<UInt64>(buff[2]) << 16) +
		(static_cast<UInt64>(buff[3]) << 24) +
		(static_cast<UInt64>(buff[4]) << 32) +
		(static_cast<UInt64>(buff[5]) << 40) +
		(static_cast<UInt64>(buff[6]) << 48) +
		(static_cast<UInt64>(buff[7]) << 56);
	return true;
}

bool Stream::SerializeDouble(Signal &sig, Double num)
{
	UChar *buff = reinterpret_cast<UChar *>(&num);
	return Write(sig, buff, sizeof(num)) == sizeof(num);
}

bool Stream::DeserializeDouble(Signal &sig, Double &num)
{
	UChar *buff = reinterpret_cast<UChar *>(&num);
	return Read(sig, buff, sizeof(num)) == sizeof(num);
}

bool Stream::SerializeString(Signal &sig, const char *str)
{
	UInt32 len = static_cast<UInt32>(::strlen(str));
	if (!SerializePackedUInt32(sig, len)) return false;
	return Write(sig, str, len) == len;
}

bool Stream::DeserializeString(Signal &sig, String &str)
{
	UInt32 len = 0;
	if (!DeserializePackedUInt32(sig, len)) return false;
	if (len == 0) {
		str.clear();
		return true;
	}
	str = String(len + 1, '\0');
	if (Read(sig, &str[0], len) != len) return false;
	str.resize(len);
	return true;
}

bool Stream::SerializeBinary(Signal &sig, const Binary &binary)
{
	UInt32 len = static_cast<UInt32>(binary.size());
	if (!SerializePackedUInt32(sig, len)) return false;
	return Write(sig, binary.data(), len) == len;
}

bool Stream::DeserializeBinary(Signal &sig, Binary &binary)
{
	UInt32 len = 0;
	if (!DeserializePackedUInt32(sig, len)) return false;
	if (len == 0) {
		binary.clear();
		return true;
	}
	binary = Binary(len);
	if (Read(sig, &binary[0], len) != len) return false;
	return true;
}

bool Stream::SerializeSymbol(Signal &sig, const Symbol *pSymbol)
{
	return SerializeString(sig, pSymbol->GetName());
}

bool Stream::DeserializeSymbol(Signal &sig, const Symbol **ppSymbol)
{
	String str;
	if (!DeserializeString(sig, str)) return false;
	*ppSymbol = Symbol::Add(str.c_str());
	return true;
}

bool Stream::SerializeSymbolSet(Signal &sig, const SymbolSet &symbolSet)
{
	UInt32 len = static_cast<UInt32>(symbolSet.size());
	if (!SerializePackedUInt32(sig, len)) return false;
	foreach_const (SymbolSet, ppSymbol, symbolSet) {
		if (!SerializeSymbol(sig, *ppSymbol)) return false;
	}
	return true;
}

bool Stream::DeserializeSymbolSet(Signal &sig, SymbolSet &symbolSet)
{
	UInt32 len = 0;
	if (!DeserializePackedUInt32(sig, len)) return false;
	symbolSet.clear();
	if (len == 0) return true;
	const Symbol *pSymbol = nullptr;
	while (len-- > 0) {
		if (!DeserializeSymbol(sig, &pSymbol)) return false;
		symbolSet.insert(pSymbol);
	}
	return true;
}

bool Stream::SerializeSymbolList(Signal &sig, const SymbolList &symbolList)
{
	UInt32 len = static_cast<UInt32>(symbolList.size());
	if (!SerializePackedUInt32(sig, len)) return false;
	foreach_const (SymbolList, ppSymbol, symbolList) {
		if (!SerializeSymbol(sig, *ppSymbol)) return false;
	}
	return true;
}

bool Stream::DeserializeSymbolList(Signal &sig, SymbolList &symbolList)
{
	UInt32 len = 0;
	if (!DeserializePackedUInt32(sig, len)) return false;
	symbolList.clear();
	if (len == 0) return true;
	symbolList.reserve(len);
	const Symbol *pSymbol = nullptr;
	while (len-- > 0) {
		if (!DeserializeSymbol(sig, &pSymbol)) return false;
		symbolList.push_back(pSymbol);
	}
	return true;
}

bool Stream::SerializePackedUInt32(Signal &sig, UInt32 num)
{
	UChar buff[16];
	size_t bytesBuff = 0;
	if (num == 0) {
		buff[bytesBuff++] = 0x00;
	} else {
		while (num > 0) {
			UChar data = static_cast<UChar>(num & 0x7f);
			num >>= 7;
			if (num != 0) data |= 0x80;
			buff[bytesBuff++] = data;
		}
	}
	return Write(sig, buff, bytesBuff) == bytesBuff;
}

bool Stream::DeserializePackedUInt32(Signal &sig, UInt32 &num)
{
	const size_t bytesBuffMax = 5;	// 32 / 7 = 4.6
	num = 0;
	UChar data = 0x00;
	for (size_t bytesBuff = 0; bytesBuff < bytesBuffMax; bytesBuff++) {
		if (Read(sig, &data, sizeof(data)) != sizeof(data)) return false;
		num = (num << 7) + (data & 0x7f);
		if ((data & 0x80) == 0x00) break;
	}
	if (data & 0x80) {
		sig.SetError(ERR_FormatError, "invalid serialization format for packed 32bit number");
		return false;
	}
	return true;
}

bool Stream::SerializePackedUInt64(Signal &sig, UInt64 num)
{
	UChar buff[16];
	size_t bytesBuff = 0;
	if (num == 0) {
		buff[bytesBuff++] = 0x00;
	} else {
		while (num > 0) {
			UChar data = static_cast<UChar>(num & 0x7f);
			num >>= 7;
			if (num != 0) data |= 0x80;
			buff[bytesBuff++] = data;
		}
	}
	return Write(sig, buff, bytesBuff) == bytesBuff;
}

bool Stream::DeserializePackedUInt64(Signal &sig, UInt64 &num)
{
	const size_t bytesBuffMax = 10;	// 64 / 7 = 9.2
	num = 0;
	UChar data = 0x00;
	for (size_t bytesBuff = 0; bytesBuff < bytesBuffMax; bytesBuff++) {
		if (Read(sig, &data, sizeof(data)) != sizeof(data)) return false;
		num = (num << 7) + (data & 0x7f);
		if ((data & 0x80) == 0x00) break;
	}
	if (data & 0x80) {
		sig.SetError(ERR_FormatError, "invalid serialization format for packed 64bit number");
		return false;
	}
	return true;
}

Stream *Stream::Open(Environment &env, const char *pathName, UInt32 attr)
{
	Signal &sig = env.GetSignal();
	if (*pathName == '>') {
		pathName++;
		attr = (attr & ~ATTR_Readable) | ATTR_Writable;
		if (*pathName == '>') {
			pathName++;
			attr |= ATTR_Append;
		}
	}
	PathMgr::NotFoundMode notFoundMode = (attr & ATTR_Writable)?
								PathMgr::NF_Wouldbe : PathMgr::NF_Signal;
	AutoPtr<Directory> pDirectory(Directory::Open(env, pathName, notFoundMode));
	if (sig.IsSignalled()) return nullptr;
	return pDirectory->DoOpenStream(env, attr);
}

Stream *Stream::Prefetch(Environment &env, Stream *pStreamSrc,
										bool deleteSrcFlag, size_t bytesUnit)
{
	Signal &sig = env.GetSignal();
	Stream_Prefetch *pStreamPrefetch =
			new Stream_Prefetch(env, Stream::Reference(pStreamSrc), bytesUnit);
	pStreamPrefetch->DoPrefetch(sig);
	if (deleteSrcFlag) Stream::Delete(pStreamSrc);
	if (sig.IsSignalled()) {
		Stream::Delete(pStreamPrefetch);
		return nullptr;
	}
	return pStreamPrefetch;
}

UInt32 Stream::ParseOpenMode(Signal &sig, const char *mode)
{
	UInt32 attr = ATTR_None;
	const char *p = mode;
	if (*p == 'r') {
		attr |= ATTR_Readable;
	} else if (*p == 'w') {
		attr |= ATTR_Writable;
	} else if (*p == 'a') {
		attr |= ATTR_Writable | ATTR_Append;
	} else {
		sig.SetError(ERR_IOError, "invalid open mode");
		return 0;
	}
	p++;
	for ( ; *p != '\0'; p++) {
		char ch = *p;
		if (ch == '+') {
			attr |= ATTR_Readable | ATTR_Writable;
		} else {
			sig.SetError(ERR_IOError, "invalid open mode");
			return 0;
		}
	}
	return attr;
}

}
