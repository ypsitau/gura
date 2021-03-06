//=============================================================================
// StreamBasic
//=============================================================================
#include "stdafx.h"

namespace Gura {

//-----------------------------------------------------------------------------
// SimpleStream_CStringReader
//-----------------------------------------------------------------------------
const char *SimpleStream_CStringReader::GetName() const
{
	return SRCNAME_string;
}

const char *SimpleStream_CStringReader::GetIdentifier() const
{
	return nullptr;
}

int SimpleStream_CStringReader::GetChar(Signal &sig)
{
	if (*_pStr == '\0' || _pStr == _pEnd) return -1;
	char ch = *_pStr++;
	return static_cast<UChar>(ch);
}

void SimpleStream_CStringReader::PutChar(Signal &sig, char ch)
{
	// nothing to do
}

size_t SimpleStream_CStringReader::Read(Signal &sig, void *buff, size_t len)
{
	size_t lenRest = (_pEnd == nullptr)? ::strlen(_pStr) : _pEnd - _pStr;
	size_t lenToCopy = ChooseMin(lenRest, len);
	::memcpy(buff, _pStr, lenToCopy);
	_pStr += lenToCopy;
	return lenToCopy;
}

size_t SimpleStream_CStringReader::Write(Signal &sig, const void *buff, size_t len)
{
	return 0;
}

//-----------------------------------------------------------------------------
// SimpleStream_StringReader
//-----------------------------------------------------------------------------
const char *SimpleStream_StringReader::GetName() const
{
	return SRCNAME_string;
}

const char *SimpleStream_StringReader::GetIdentifier() const
{
	return nullptr;
}

int SimpleStream_StringReader::GetChar(Signal &sig)
{
	if (_pStr == _pEnd) return -1;
	char ch = *_pStr++;
	return static_cast<UChar>(ch);
}

void SimpleStream_StringReader::PutChar(Signal &sig, char ch)
{
	// nothing to do
}

size_t SimpleStream_StringReader::Read(Signal &sig, void *buff, size_t len)
{
	char *p = reinterpret_cast<char *>(buff);
	size_t lenCopied = 0;
	for ( ; _pStr != _pEnd && lenCopied < len; lenCopied++) {
		*p++ = *_pStr++;
	}
	return lenCopied;
}

size_t SimpleStream_StringReader::Write(Signal &sig, const void *buff, size_t len)
{
	return 0;
}

//-----------------------------------------------------------------------------
// SimpleStream_StringWriter
//-----------------------------------------------------------------------------
const char *SimpleStream_StringWriter::GetName() const
{
	return SRCNAME_string;
}

const char *SimpleStream_StringWriter::GetIdentifier() const
{
	return nullptr;
}

int SimpleStream_StringWriter::GetChar(Signal &sig)
{
	return -1;
}

void SimpleStream_StringWriter::PutChar(Signal &sig, char ch)
{
	_str += ch;
}

size_t SimpleStream_StringWriter::Read(Signal &sig, void *buff, size_t len)
{
	return 0;
}

size_t SimpleStream_StringWriter::Write(Signal &sig, const void *buff, size_t len)
{
	return 0;
}

//-----------------------------------------------------------------------------
// StreamDumb
//-----------------------------------------------------------------------------
StreamDumb::StreamDumb(Environment &env) : Stream(env, ATTR_Writable)
{
}

const char *StreamDumb::GetName() const
{
	return SRCNAME_dumb;
}

const char *StreamDumb::GetIdentifier() const
{
	return SRCNAME_dumb;
}

bool StreamDumb::GetAttribute(Attribute &attr)
{
	return false;
}

bool StreamDumb::SetAttribute(const Attribute &attr)
{
	return false;
}

size_t StreamDumb::DoRead(Signal &sig, void *buff, size_t len)
{
	return 0;
}

size_t StreamDumb::DoWrite(Signal &sig, const void *buff, size_t len)
{
	return len;
}

bool StreamDumb::DoSeek(Signal &sig, long offset, size_t offsetPrev, SeekMode seekMode)
{
	return true;
}

bool StreamDumb::DoFlush(Signal &sig)
{
	return true;
}

bool StreamDumb::DoClose(Signal &sig)
{
	return Stream::DoClose(sig);
}

size_t StreamDumb::DoGetSize()
{
	return 0;
}

//-----------------------------------------------------------------------------
// StreamFIFO
//-----------------------------------------------------------------------------
StreamFIFO::StreamFIFO(Environment &env, size_t bytesBuff) :
		Stream(env, ATTR_Readable | ATTR_Writable), _pEntity(new Entity(bytesBuff))
{
}

StreamFIFO::StreamFIFO(Environment &env, Entity *pEntity) :
		Stream(env, ATTR_Readable | ATTR_Writable), _pEntity(pEntity)
{
}

StreamFIFO::~StreamFIFO()
{
	Close();
}

const char *StreamFIFO::GetName() const
{
	return SRCNAME_fifo;
}

const char *StreamFIFO::GetIdentifier() const
{
	return nullptr;
}

bool StreamFIFO::GetAttribute(Attribute &attr)
{
	return false;
}

bool StreamFIFO::SetAttribute(const Attribute &attr)
{
	return false;
}

size_t StreamFIFO::DoRead(Signal &sig, void *buff, size_t len)
{
	return _pEntity->DoRead(sig, buff, len);
}

size_t StreamFIFO::DoWrite(Signal &sig, const void *buff, size_t len)
{
	return _pEntity->DoWrite(sig, buff, len);
}

bool StreamFIFO::DoSeek(Signal &sig, long offset, size_t offsetPrev, SeekMode seekMode)
{
	return false;
}

bool StreamFIFO::DoFlush(Signal &sig)
{
	return true;
}

bool StreamFIFO::DoClose(Signal &sig)
{
	_pEntity->SetBrokenFlag();
	return Stream::DoClose(sig);
}

size_t StreamFIFO::DoGetSize()
{
	return 0;
}

//-----------------------------------------------------------------------------
// StreamFIFO::Entity
//-----------------------------------------------------------------------------
StreamFIFO::Entity::Entity(size_t bytesBuff) : _cntRef(1),
		_pMemory(new MemoryHeap(bytesBuff)),
		_offsetWrite(0), _offsetRead(0), _bytesAvail(0),
		_brokenFlag(false), _pSemaphore(new OAL::Semaphore())
{
}

size_t StreamFIFO::Entity::DoRead(Signal &sig, void *buff, size_t len)
{
	char *buffp = reinterpret_cast<char *>(buff);
	_pSemaphore->Wait();
	//::printf("+DoRead(%zu) bytesAvail=%zu\n", len, _bytesAvail);
	if (_brokenFlag && _bytesAvail == 0) {
		_pSemaphore->Release();
		return 0;
	}
	size_t offset = 0;
	while (offset < len) {
		size_t bytesSpace = len - offset;
		while (_bytesAvail == 0 && !_brokenFlag) {
			_pSemaphore->Release();
			OAL::Sleep(.001); // sleep for 1 msec
			_pSemaphore->Wait();
		}
		if (_bytesAvail > 0) {
			size_t bytesCopy = ChooseMin(bytesSpace, _bytesAvail);
			if (_offsetRead + bytesCopy <= _pMemory->GetSize()) {
				::memcpy(buffp + offset, _pMemory->GetPointer(_offsetRead), bytesCopy);
				offset += bytesCopy;
				_offsetRead += bytesCopy;
				_bytesAvail -= bytesCopy;
				if (_offsetRead == _pMemory->GetSize()) _offsetRead = 0;
			} else {
				size_t bytesPart = _pMemory->GetSize() - _offsetRead;
				::memcpy(buffp + offset, _pMemory->GetPointer(_offsetRead), bytesPart);
				::memcpy(buffp + offset + bytesPart, _pMemory->GetPointer(), bytesCopy - bytesPart);
				offset += bytesCopy;
				_offsetRead = bytesCopy - bytesPart;
				_bytesAvail -= bytesCopy;
			}
		}
		if (_brokenFlag) {
			//::printf("-DoRead(%zu) rtn=%zu\n", len, offset);
			_pSemaphore->Release();
			return offset;
		}
	}
	//::printf("-DoRead(%zu) rtn=%zu\n", len, offset);
	_pSemaphore->Release();
	return offset;
}

size_t StreamFIFO::Entity::DoWrite(Signal &sig, const void *buff, size_t len)
{
	const char *buffp = reinterpret_cast<const char *>(buff);
	_pSemaphore->Wait();
	//::printf("DoWrite(%zu) bytesAvail=%zu\n", len, _bytesAvail);
	for (size_t offset = 0; offset < len; ) {
		size_t bytesRest = len - offset;
		while (_bytesAvail == _pMemory->GetSize()) {
			_pSemaphore->Release();
			OAL::Sleep(.001); // sleep for 1 msec
			_pSemaphore->Wait();
		}
		size_t bytesSpace = _pMemory->GetSize() - _bytesAvail;
		size_t bytesCopy = ChooseMin(bytesRest, bytesSpace);
		if (_offsetWrite + bytesCopy <= _pMemory->GetSize()) {
			::memcpy(_pMemory->GetPointer(_offsetWrite), buffp + offset, bytesCopy);
			offset += bytesCopy;
			_offsetWrite += bytesCopy;
			_bytesAvail += bytesCopy;
			if (_offsetRead == _pMemory->GetSize()) _offsetRead = 0;
		} else {
			size_t bytesPart = _pMemory->GetSize() - _offsetWrite;
			::memcpy(_pMemory->GetPointer(_offsetWrite), buffp + offset, bytesPart);
			::memcpy(_pMemory->GetPointer(), buffp + offset + bytesPart, bytesCopy - bytesPart);
			offset += bytesCopy;
			_offsetWrite = bytesCopy - bytesPart;
			_bytesAvail += bytesCopy;
		}
	}
	_pSemaphore->Release();
	return len;
}

//-----------------------------------------------------------------------------
// StreamMemory
//-----------------------------------------------------------------------------
StreamMemory::StreamMemory(Environment &env) :
					Stream(env, ATTR_Writable), _pBinary(new Binary())
{
}

const char *StreamMemory::GetName() const
{
	return SRCNAME_memory;
}

const char *StreamMemory::GetIdentifier() const
{
	return nullptr;
}

bool StreamMemory::GetAttribute(Attribute &attr)
{
	return false;
}

bool StreamMemory::SetAttribute(const Attribute &attr)
{
	return false;
}

size_t StreamMemory::DoRead(Signal &sig, void *buff, size_t len)
{
	return 0;
}

size_t StreamMemory::DoWrite(Signal &sig, const void *buff, size_t len)
{
	_pBinary->append(reinterpret_cast<const char *>(buff), len);
	return len;
}

bool StreamMemory::DoSeek(Signal &sig, long offset, size_t offsetPrev, SeekMode seekMode)
{
	return false;
}

bool StreamMemory::DoFlush(Signal &sig)
{
	return true;
}

bool StreamMemory::DoClose(Signal &sig)
{
	return Stream::DoClose(sig);
}

size_t StreamMemory::DoGetSize()
{
	return _pBinary->size();
}

const char *StreamMemory::GetPointer() const
{
	return _pBinary->data();
}

//-----------------------------------------------------------------------------
// StreamMemReader
//-----------------------------------------------------------------------------
StreamMemReader::StreamMemReader(Environment &env, const void *buff, size_t bytes) :
				Stream(env, ATTR_BwdSeekable | ATTR_Readable),
				_buff(reinterpret_cast<const char *>(buff)), _bytes(bytes)
{
}

const char *StreamMemReader::GetName() const
{
	return SRCNAME_memory;
}

const char *StreamMemReader::GetIdentifier() const
{
	return nullptr;
}

bool StreamMemReader::GetAttribute(Attribute &attr)
{
	return false;
}

bool StreamMemReader::SetAttribute(const Attribute &attr)
{
	return false;
}

size_t StreamMemReader::DoRead(Signal &sig, void *buff, size_t len)
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

size_t StreamMemReader::DoWrite(Signal &sig, const void *buff, size_t len)
{
	return 0;
}

bool StreamMemReader::DoSeek(Signal &sig, long offset, size_t offsetPrev, SeekMode seekMode)
{
	if (seekMode == SeekSet) {
		_offsetCur = static_cast<size_t>(offset);
	} else if (seekMode == SeekCur) {
		_offsetCur += offset;
	}
	return true;
}

bool StreamMemReader::DoFlush(Signal &sig)
{
	return true;
}

bool StreamMemReader::DoClose(Signal &sig)
{
	return Stream::DoClose(sig);
}

size_t StreamMemReader::DoGetSize()
{
	return _bytes;
}

//-----------------------------------------------------------------------------
// Stream_Prefetch
//-----------------------------------------------------------------------------
Stream_Prefetch::Stream_Prefetch(Environment &env, Stream *pStreamSrc, size_t bytesUnit) :
			Stream(env, ATTR_Readable), _pStreamSrc(pStreamSrc),
			_offset(0), _bytesAll(0), _bytesUnit(bytesUnit)
{
	CopyCodec(pStreamSrc);
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

size_t Stream_Prefetch::DoRead(Signal &sig, void *buff, size_t len)
{
	size_t iMemory = _offset / _bytesUnit;
	if (iMemory >= _memoryOwner.size()) {
		sig.SetError(ERR_IndexError, "out of range");
		return 0;
	}
	MemoryList::iterator ppMemory = _memoryOwner.begin() + iMemory;
	char *buffDst = reinterpret_cast<char *>(buff);
	size_t offsetUnit = _offset % _bytesUnit;
	size_t bytesCopied = 0;
	size_t bytesRest = len;
	for ( ; ppMemory != _memoryOwner.end() && bytesRest > 0; ppMemory++) {
		Memory *pMemory = *ppMemory;
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

size_t Stream_Prefetch::DoWrite(Signal &sig, const void *buff, size_t len)
{
	return 0;
}

bool Stream_Prefetch::DoSeek(Signal &sig, long offset, size_t offsetPrev, SeekMode seekMode)
{
	if (seekMode == SeekSet) {
		_offset = static_cast<size_t>(offset);
	} else if (seekMode == SeekCur) {
		_offset += offset;
	}
	return true;
}

bool Stream_Prefetch::DoFlush(Signal &sig)
{
	return false;
}

bool Stream_Prefetch::DoClose(Signal &sig)
{
	return Stream::DoClose(sig);
}

size_t Stream_Prefetch::DoGetSize()
{
	return _bytesAll;
}

bool Stream_Prefetch::DoPrefetch(Signal &sig)
{
	_bytesAll = 0;
	for (;;) {
		AutoPtr<Memory> pMemory(new MemoryHeap(_bytesUnit));
		size_t bytes = _pStreamSrc->Read(sig, pMemory->GetPointer(), _bytesUnit);
		if (sig.IsSignalled()) {
			return false;
		} else if (bytes == 0 || sig.IsSignalled()) {
			break;
		}
		_memoryOwner.push_back(pMemory.release());
		_bytesAll += bytes;
		if (bytes < _bytesUnit) break;
	}
	return true;
}

//-----------------------------------------------------------------------------
// Stream_Base64Reader
//-----------------------------------------------------------------------------
Stream_Base64Reader::Stream_Base64Reader(Environment &env, Stream *pStreamSrc) :
			Stream(env, ATTR_Readable), _pStreamSrc(pStreamSrc),
			_nChars(0), _nInvalid(0), _accum(0), _iBuffWork(0)
{
	CopyCodec(pStreamSrc);
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

size_t Stream_Base64Reader::DoRead(Signal &sig, void *buff, size_t len)
{
	UChar *buffp = reinterpret_cast<UChar *>(buff);
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
			_buffWork[0] = static_cast<UChar>(_accum & 0xff); _accum >>= 8;
			_buffWork[1] = static_cast<UChar>(_accum & 0xff); _accum >>= 8;
			_buffWork[2] = static_cast<UChar>(_accum & 0xff);
			_iBuffWork = 3;
		} else if (_nInvalid == 1) {
			_accum >>= 8;
			_buffWork[0] = static_cast<UChar>(_accum & 0xff); _accum >>= 8;
			_buffWork[1] = static_cast<UChar>(_accum & 0xff);
			_iBuffWork = 2;
		} else if (_nInvalid == 2) {
			_accum >>= 8;
			_accum >>= 8;
			_buffWork[0] = static_cast<UChar>(_accum & 0xff);
			_iBuffWork = 1;
		} else {
			_iBuffWork = 0;
		}
		_nChars = 0, _nInvalid = 0, _accum = 0;
	}
	return lenRead;
}

size_t Stream_Base64Reader::DoWrite(Signal &sig, const void *buff, size_t len)
{
	return 0;
}

bool Stream_Base64Reader::DoSeek(Signal &sig, long offset, size_t offsetPrev, SeekMode seekMode)
{
	return false;
}

bool Stream_Base64Reader::DoFlush(Signal &sig)
{
	return false;
}

bool Stream_Base64Reader::DoClose(Signal &sig)
{
	return Stream::DoClose(sig);
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

Stream_Base64Writer::Stream_Base64Writer(Environment &env, Stream *pStreamDst, int nCharsPerLine) :
			Stream(env, ATTR_Writable), _pStreamDst(pStreamDst),
			_nCharsPerLine(nCharsPerLine), _nChars(0), _iBuffWork(0)
{
	CopyCodec(pStreamDst);
	_nCharsPerLine = (_nCharsPerLine + 3) / 4 * 4;
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

size_t Stream_Base64Writer::DoRead(Signal &sig, void *buff, size_t len)
{
	return 0;
}

size_t Stream_Base64Writer::DoWrite(Signal &sig, const void *buff, size_t len)
{
	const UChar *buffp = reinterpret_cast<const UChar *>(buff);
	size_t lenWritten = 0;
	bool addcrFlag = _pStreamDst->GetCodec()->GetEncoder()->GetAddcrFlag();
	for ( ; lenWritten < len; lenWritten++) {
		_buffWork[_iBuffWork++] = buffp[lenWritten];
		if (_iBuffWork < 3) continue;
		UInt32 accum =
			(static_cast<UInt32>(_buffWork[0]) << 16) |
			(static_cast<UInt32>(_buffWork[1]) << 8) |
			(static_cast<UInt32>(_buffWork[2]) << 0);
		char buffDst[8];
		buffDst[0] = _chars[(accum >> 18) & 0x3f];
		buffDst[1] = _chars[(accum >> 12) & 0x3f];
		buffDst[2] = _chars[(accum >> 6) & 0x3f];
		buffDst[3] = _chars[(accum >> 0) & 0x3f];
		_nChars += 4;
		if (_nCharsPerLine > 0 && _nChars >= _nCharsPerLine) {
			size_t bytes = 4;
			if (addcrFlag) buffDst[bytes++] = '\r';
			buffDst[bytes++] = '\n';
			_pStreamDst->Write(sig, buffDst, bytes);
			_nChars = 0;
		} else {
			_pStreamDst->Write(sig, buffDst, 4);
		}
		if (sig.IsSignalled()) return 0;
		_iBuffWork = 0;
	}
	return lenWritten;
}

bool Stream_Base64Writer::DoSeek(Signal &sig, long offset, size_t offsetPrev, SeekMode seekMode)
{
	return false;
}

bool Stream_Base64Writer::DoFlush(Signal &sig)
{
	char buffDst[8];
	bool addcrFlag = _pStreamDst->GetCodec()->GetEncoder()->GetAddcrFlag();
	if (_iBuffWork == 0) {
		if (_nChars > 0 && _nCharsPerLine > 0) {
			size_t bytes = 0;
			if (addcrFlag) buffDst[bytes++] = '\r';
			buffDst[bytes++] = '\n';
			_pStreamDst->Write(sig, buffDst, bytes);
		}
		_nChars = 0;
		_iBuffWork = 0;
		return !sig.IsSignalled();
	} else if (_iBuffWork == 1) {
		UInt32 accum = static_cast<UInt32>(_buffWork[0]) << 16;
		buffDst[0] = _chars[(accum >> 18) & 0x3f];
		buffDst[1] = _chars[(accum >> 12) & 0x3f];
		buffDst[2] = '=';
		buffDst[3] = '=';
	} else if (_iBuffWork == 2) {
		UInt32 accum =
			(static_cast<UInt32>(_buffWork[0]) << 16) |
			(static_cast<UInt32>(_buffWork[1]) << 8);
		buffDst[0] = _chars[(accum >> 18) & 0x3f];
		buffDst[1] = _chars[(accum >> 12) & 0x3f];
		buffDst[2] = _chars[(accum >> 6) & 0x3f];
		buffDst[3] = '=';
	} else { // _iBuffWork == 3
		UInt32 accum =
			(static_cast<UInt32>(_buffWork[0]) << 16) |
			(static_cast<UInt32>(_buffWork[1]) << 8) |
			(static_cast<UInt32>(_buffWork[2]) << 0);
		buffDst[0] = _chars[(accum >> 18) & 0x3f];
		buffDst[1] = _chars[(accum >> 12) & 0x3f];
		buffDst[2] = _chars[(accum >> 6) & 0x3f];
		buffDst[3] = _chars[(accum >> 0) & 0x3f];
	}
	if (_nCharsPerLine > 0) {
		size_t bytes = 4;
		if (addcrFlag) buffDst[bytes++] = '\r';
		buffDst[bytes++] = '\n';
		_pStreamDst->Write(sig, buffDst, bytes);
	} else {
		_pStreamDst->Write(sig, buffDst, 4);
	}
	_nChars = 0;
	_iBuffWork = 0;
	return !sig.IsSignalled();
}

bool Stream_Base64Writer::DoClose(Signal &sig)
{
	if (!DoFlush(sig)) return false;
	return Stream::DoClose(sig);
}

size_t Stream_Base64Writer::DoGetSize()
{
	return 0;
}

//-----------------------------------------------------------------------------
// Stream_CRC32
//-----------------------------------------------------------------------------
Stream_CRC32::Stream_CRC32(Environment &env, Stream *pStreamDst) :
		Stream(env, (pStreamDst == nullptr)? ATTR_Writable : pStreamDst->GetAttr()),
		_pStreamDst(pStreamDst)
{
	CopyCodec(pStreamDst);
}

const char *Stream_CRC32::GetName() const
{
	return _pStreamDst.IsNull()? "" : _pStreamDst->GetName();
}

const char *Stream_CRC32::GetIdentifier() const
{
	return _pStreamDst.IsNull()? nullptr : _pStreamDst->GetIdentifier();
}

size_t Stream_CRC32::DoRead(Signal &sig, void *buff, size_t len)
{
	return _pStreamDst.IsNull()? 0 : _pStreamDst->Read(sig, buff, len);
}

size_t Stream_CRC32::DoWrite(Signal &sig, const void *buff, size_t len)
{
	_crc32.Update(buff, len);
	return _pStreamDst.IsNull()? len : _pStreamDst->Write(sig, buff, len);
}

bool Stream_CRC32::DoSeek(Signal &sig, long offset, size_t offsetPrev, SeekMode seekMode)
{
	return _pStreamDst.IsNull()? true : _pStreamDst->Seek(sig, offset, seekMode);
}

bool Stream_CRC32::DoFlush(Signal &sig)
{
	return _pStreamDst.IsNull()? true : _pStreamDst->Flush(sig);
}

bool Stream_CRC32::DoClose(Signal &sig)
{
	if (!_pStreamDst.IsNull() && !_pStreamDst->DoClose(sig)) return false;
	return Stream::DoClose(sig);
}

size_t Stream_CRC32::DoGetSize()
{
	return _pStreamDst.IsNull()? 0 : _pStreamDst->GetSize();
}

//-----------------------------------------------------------------------------
// Stream_StringReader
//-----------------------------------------------------------------------------
Stream_StringReader::Stream_StringReader(Environment &env, const String &str) :
					Stream(env, ATTR_Readable), _str(str), _offset(0)
{
}

Stream_StringReader::~Stream_StringReader()
{
}

const char *Stream_StringReader::GetName() const
{
	return SRCNAME_string;
}

const char *Stream_StringReader::GetIdentifier() const
{
	return nullptr;
}

size_t Stream_StringReader::DoRead(Signal &sig, void *buff, size_t len)
{
	if (_offset > _str.size()) {
		sig.SetError(ERR_IndexError, "out of range");
		return 0;
	}
	len = ChooseMin(_str.size() - _offset, len);
	::memcpy(buff, _str.data() + _offset, len);
	_offset += len;
	return len;
}

size_t Stream_StringReader::DoWrite(Signal &sig, const void *buff, size_t len)
{
	return 0;
}

bool Stream_StringReader::DoSeek(Signal &sig, long offset, size_t offsetPrev, SeekMode seekMode)
{
	if (seekMode == SeekSet) {
		_offset = static_cast<size_t>(offset);
	} else if (seekMode == SeekCur) {
		_offset += offset;
	}
	return true;
}

bool Stream_StringReader::DoFlush(Signal &sig)
{
	return true;
}

bool Stream_StringReader::DoClose(Signal &sig)
{
	return Stream::DoClose(sig);
}

size_t Stream_StringReader::DoGetSize()
{
	return _str.size();
}

}
