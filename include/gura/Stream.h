#ifndef __GURA_STREAM_H__
#define __GURA_STREAM_H__

#include "Signal.h"
#include "OAL.h"
#include "Codec.h"
#include "Algorithm.h"

namespace Gura {

class Object;
class ValueList;
class Function;

//-----------------------------------------------------------------------------
// SimpleStream
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE SimpleStream {
public:
	void Print(Signal sig, const char *str);
	void Printf(Signal sig, const char *format, const ValueList &valList);
	void Println(Signal sig, const char *str);
	void PrintSignal(Signal sig, const Signal &sigToPrint);
	void Dump(Signal sig, const void *buff, size_t bytes, bool upperFlag = false);
	virtual int GetChar(Signal sig) = 0;
	virtual void PutChar(Signal sig, char ch) = 0;
};

//-----------------------------------------------------------------------------
// SimpleStream_CString
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE SimpleStream_CString : public SimpleStream {
private:
	const char *_pStr;
	const char *_pEnd;
public:
	inline SimpleStream_CString(const char *pStr, const char *pEnd = NULL) :
													_pStr(pStr), _pEnd(pEnd) {}
	virtual int GetChar(Signal sig);
	virtual void PutChar(Signal sig, char ch);
};

//-----------------------------------------------------------------------------
// SimpleStream_String
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE SimpleStream_String : public SimpleStream {
private:
	String::const_iterator _pStr;
	String::const_iterator _pEnd;
public:
	inline SimpleStream_String(String::const_iterator pStr,
				String::const_iterator pEnd) : _pStr(pStr), _pEnd(pEnd) {}
	virtual int GetChar(Signal sig);
	virtual void PutChar(Signal sig, char ch);
};

//-----------------------------------------------------------------------------
// SimpleStream_StringWrite
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE SimpleStream_StringWrite : public SimpleStream {
private:
	String &_str;
public:
	inline SimpleStream_StringWrite(String &str) : _str(str) {}
	virtual int GetChar(Signal sig);
	virtual void PutChar(Signal sig, char ch);
};

//-----------------------------------------------------------------------------
// Stream
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE Stream : public SimpleStream {
public:
	enum SeekMode { SeekSet, SeekCur };
	enum Error {
		ERROR_None,
		ERROR_Codec,
	};
	enum {
		ATTR_None			= 0,
		ATTR_Infinite		= (1 << 0),
		ATTR_BwdSeekable	= (1 << 1),
		ATTR_Readable		= (1 << 2),
		ATTR_Writable		= (1 << 3),
		ATTR_Append			= (1 << 4),
	};
	struct Attribute {
	public:
		DateTime atime;
		DateTime mtime;
		DateTime ctime;
		ULong attr;
		ULong attrMask;
	public:
		inline Attribute() : attr(0), attrMask(0) {}
	};
protected:
	int _cntRef;
	Signal _sig;
	ULong _attr;
	size_t _offsetCur;
	AutoPtr<Codec> _pCodec;
	struct {
		char *buff;
		size_t bytes;
		size_t offsetRead;
	} _peek;
public:
	Gura_DeclareReferenceAccessor(Stream);
protected:
	virtual ~Stream();
public:
	Stream(Environment &env, Signal sig, ULong attr);
	void Close();
	void SetCodec(Codec *pCodec);
	void CopyCodec(Stream *pStream);
	void CopyCodec(const Codec *pCodec);
	inline Codec *GetCodec() { return _pCodec.get(); }
	String ReadChar(Signal sig);
	virtual int GetChar(Signal sig);
	virtual void PutChar(Signal sig, char ch);
	virtual const char *GetName() const = 0;
	virtual const char *GetIdentifier() const = 0;
	virtual bool GetAttribute(Attribute &attr);
	virtual bool SetAttribute(const Attribute &attr);
	virtual size_t DoRead(Signal sig, void *buff, size_t len);
	virtual size_t DoWrite(Signal sig, const void *buff, size_t len);
	virtual bool DoSeek(Signal sig, long offset, size_t offsetPrev, SeekMode seekMode);
	virtual bool DoFlush(Signal sig);
	virtual bool DoClose(Signal sig);
	virtual size_t DoGetSize();
	virtual int DoGetChar(Signal sig);
	virtual void DoPutChar(Signal sig, char ch);
	virtual Object *DoGetStatObj(Signal sig);
	inline int GetRefCount() const { return _cntRef; }
	inline ULong GetAttr() const { return _attr; }
	inline bool IsInfinite() const { return (_attr & ATTR_Infinite)? true : false; }
	inline bool IsReadable() const { return (_attr & ATTR_Readable)? true : false; }
	inline bool IsWritable() const { return (_attr & ATTR_Writable)? true : false; }
	inline bool IsAppend() const { return (_attr & ATTR_Append)? true : false; }
	inline bool IsBwdSeekable() const { return (_attr & ATTR_BwdSeekable)? true : false; }
	inline void SetReadable(bool flag) {
		_attr = (_attr & ~ATTR_Readable) | (flag? ATTR_Readable : 0);
	}
	inline void SetWritable(bool flag) {
		_attr = (_attr & ~ATTR_Writable) | (flag? ATTR_Writable : 0);
	}
	inline void SetAppend(bool flag) {
		_attr = (_attr & ~ATTR_Append) | (flag? ATTR_Append : 0);
	}
	size_t Read(Signal sig, void *buff, size_t len);
	size_t Write(Signal sig, const void *buff, size_t len);
	size_t Peek(Signal sig, void *buff, size_t len);
	bool Seek(Signal sig, long offset, SeekMode seekMode);
	inline size_t Tell() { return _offsetCur; }
	inline size_t GetSize() { return DoGetSize(); }
	inline Object *GetStatObj(Signal sig) { return DoGetStatObj(sig); }
	bool Flush(Signal sig);
	bool HasNameSuffix(const char *suffix, bool ignoreCase = true) const;
	bool CheckReadable(Signal sig) const;
	bool CheckWritable(Signal sig) const;
	bool CheckBwdSeekable(Signal sig) const;
	bool Compare(Signal sig, Stream &stream);
	bool ReadToStream(Environment &env, Signal sig, Stream &streamDst,
					size_t bytesUnit = 0x10000, bool finalizeFlag = true,
					const Function *pFuncFilter = NULL);
	bool SerializeBoolean(Signal sig, bool num);
	bool DeserializeBoolean(Signal sig, bool &num);
	bool SerializeUChar(Signal sig, UChar num);
	bool DeserializeUChar(Signal sig, UChar &num);
	bool SerializeUShort(Signal sig, UShort num);
	bool DeserializeUShort(Signal sig, UShort &num);
	bool SerializeULong(Signal sig, ULong num);
	bool DeserializeULong(Signal sig, ULong &num);
	bool SerializeUInt64(Signal sig, uint64 num);
	bool DeserializeUInt64(Signal sig, uint64 &num);
	bool SerializeDouble(Signal sig, double num);
	bool DeserializeDouble(Signal sig, double &num);
	bool SerializeString(Signal sig, const char *str);
	bool DeserializeString(Signal sig, String &str);
	bool SerializeBinary(Signal sig, const Binary &binary);
	bool DeserializeBinary(Signal sig, Binary &binary);
	bool SerializeSymbol(Signal sig, const Symbol *pSymbol);
	bool DeserializeSymbol(Signal sig, const Symbol **ppSymbol);
	bool SerializeSymbolSet(Signal sig, const SymbolSet &symbolSet);
	bool DeserializeSymbolSet(Signal sig, SymbolSet &symbolSet);
	bool SerializeSymbolList(Signal sig, const SymbolList &symbolList);
	bool DeserializeSymbolList(Signal sig, SymbolList &symbolList);
	bool SerializePackedULong(Signal sig, ULong num);
	bool DeserializePackedULong(Signal sig, ULong &num);
public:
	static Stream *Prefetch(Environment &env, Signal sig, Stream *pStreamSrc,
							bool deleteSrcFlag, size_t bytesUnit = 0x10000);
	static ULong ParseOpenMode(Signal sig, const char *mode);
};

//-----------------------------------------------------------------------------
// StreamDumb
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE StreamDumb : public Stream {
public:
	StreamDumb(Environment &env, Signal sig);
	virtual const char *GetName() const;
	virtual const char *GetIdentifier() const;
	virtual bool GetAttribute(Attribute &attr);
	virtual bool SetAttribute(const Attribute &attr);
	virtual size_t DoRead(Signal sig, void *buff, size_t len);
	virtual size_t DoWrite(Signal sig, const void *buff, size_t len);
	virtual bool DoSeek(Signal sig, long offset, size_t offsetPrev, SeekMode seekMode);
	virtual bool DoFlush(Signal sig);
	virtual bool DoClose(Signal sig);
	virtual size_t DoGetSize();
};

//-----------------------------------------------------------------------------
// StreamFIFO
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE StreamFIFO : public Stream {
private:
	AutoPtr<Memory> _pMemory;
	size_t _offsetWrite;
	size_t _offsetRead;
	size_t _bytesAvail;
	bool _readReqFlag;
	bool _writeReqFlag;
	bool _writeDoneFlag;
	std::auto_ptr<OAL::Semaphore> _pSemaphore;
	std::auto_ptr<OAL::Event> _pEventReadReq;
	std::auto_ptr<OAL::Event> _pEventWriteReq;
public:
	StreamFIFO(Environment &env, Signal sig, size_t bytesBuff);
	virtual const char *GetName() const;
	virtual const char *GetIdentifier() const;
	virtual bool GetAttribute(Attribute &attr);
	virtual bool SetAttribute(const Attribute &attr);
	virtual size_t DoRead(Signal sig, void *buff, size_t len);
	virtual size_t DoWrite(Signal sig, const void *buff, size_t len);
	virtual bool DoSeek(Signal sig, long offset, size_t offsetPrev, SeekMode seekMode);
	virtual bool DoFlush(Signal sig);
	virtual bool DoClose(Signal sig);
	virtual size_t DoGetSize();
	void SetWriteDoneFlag();
public:
	size_t GetOffsetWrite() const { return _offsetWrite; }
	size_t GetOffsetRead() const { return _offsetRead; }
	size_t GetBytesAvail() const { return _bytesAvail; }
};

//-----------------------------------------------------------------------------
// StreamMemory
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE StreamMemory : public Stream {
private:
	std::auto_ptr<Binary> _pBinary;
public:
	StreamMemory(Environment &env, Signal sig);
	virtual const char *GetName() const;
	virtual const char *GetIdentifier() const;
	virtual bool GetAttribute(Attribute &attr);
	virtual bool SetAttribute(const Attribute &attr);
	virtual size_t DoRead(Signal sig, void *buff, size_t len);
	virtual size_t DoWrite(Signal sig, const void *buff, size_t len);
	virtual bool DoSeek(Signal sig, long offset, size_t offsetPrev, SeekMode seekMode);
	virtual bool DoFlush(Signal sig);
	virtual bool DoClose(Signal sig);
	virtual size_t DoGetSize();
	const char *GetPointer() const;
};

//-----------------------------------------------------------------------------
// StreamMemReader
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE StreamMemReader : public Stream {
private:
	const char *_buff;
	size_t _bytes;
public:
	StreamMemReader(Environment &env, Signal sig, const void *buff, size_t bytes);
	virtual const char *GetName() const;
	virtual const char *GetIdentifier() const;
	virtual bool GetAttribute(Attribute &attr);
	virtual bool SetAttribute(const Attribute &attr);
	virtual size_t DoRead(Signal sig, void *buff, size_t len);
	virtual size_t DoWrite(Signal sig, const void *buff, size_t len);
	virtual bool DoSeek(Signal sig, long offset, size_t offsetPrev, SeekMode seekMode);
	virtual bool DoFlush(Signal sig);
	virtual bool DoClose(Signal sig);
	virtual size_t DoGetSize();
};

//-----------------------------------------------------------------------------
// Stream_Prefetch
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE Stream_Prefetch : public Stream {
private:
	AutoPtr<Stream> _pStreamSrc;
	size_t _offset;
	size_t _bytesAll;
	size_t _bytesUnit;
	MemoryOwner _memoryOwner;
public:
	Stream_Prefetch(Environment &env, Signal sig, Stream *pStreamSrc, size_t bytesUnit);
	virtual const char *GetName() const;
	virtual const char *GetIdentifier() const;
	virtual bool GetAttribute(Attribute &attr);
	virtual bool SetAttribute(const Attribute &attr);
	virtual size_t DoRead(Signal sig, void *buff, size_t len);
	virtual size_t DoWrite(Signal sig, const void *buff, size_t len);
	virtual bool DoSeek(Signal sig, long offset, size_t offsetPrev, SeekMode seekMode);
	virtual bool DoFlush(Signal sig);
	virtual bool DoClose(Signal sig);
	virtual size_t DoGetSize();
	bool DoPrefetch(Signal sig);
};

//-----------------------------------------------------------------------------
// Stream_Base64Reader
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE Stream_Base64Reader : public Stream {
private:
	AutoPtr<Stream> _pStreamSrc;
	int _nChars;
	int _nInvalid;
	ULong _accum;
	size_t _iBuffWork;
	UChar _buffWork[8];
public:
	Stream_Base64Reader(Environment &env, Signal sig, Stream *pStreamSrc);
	virtual const char *GetName() const;
	virtual const char *GetIdentifier() const;
	virtual bool GetAttribute(Attribute &attr);
	virtual bool SetAttribute(const Attribute &attr);
	virtual size_t DoRead(Signal sig, void *buff, size_t len);
	virtual size_t DoWrite(Signal sig, const void *buff, size_t len);
	virtual bool DoSeek(Signal sig, long offset, size_t offsetPrev, SeekMode seekMode);
	virtual bool DoFlush(Signal sig);
	virtual bool DoClose(Signal sig);
	virtual size_t DoGetSize();
};

//-----------------------------------------------------------------------------
// Stream_Base64Writer
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE Stream_Base64Writer : public Stream {
private:
	AutoPtr<Stream> _pStreamDst;
	int _nCharsPerLine;
	int _nChars;
	size_t _iBuffWork;
	UChar _buffWork[8];
	static const char _chars[];
public:
	Stream_Base64Writer(Environment &env, Signal sig, Stream *pStreamDst, int nCharsPerLine);
	virtual const char *GetName() const;
	virtual const char *GetIdentifier() const;
	virtual bool GetAttribute(Attribute &attr);
	virtual bool SetAttribute(const Attribute &attr);
	virtual size_t DoRead(Signal sig, void *buff, size_t len);
	virtual size_t DoWrite(Signal sig, const void *buff, size_t len);
	virtual bool DoSeek(Signal sig, long offset, size_t offsetPrev, SeekMode seekMode);
	virtual bool DoFlush(Signal sig);
	virtual bool DoClose(Signal sig);
	virtual size_t DoGetSize();
};

//-----------------------------------------------------------------------------
// Stream_CRC32
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE Stream_CRC32 : public Stream {
private:
	AutoPtr<Stream> _pStreamDst;
	CRC32 _crc32;
public:
	Stream_CRC32(Environment &env, Signal sig, Stream *pStreamDst);
	virtual const char *GetName() const;
	virtual const char *GetIdentifier() const;
	virtual size_t DoRead(Signal sig, void *buff, size_t len);
	virtual size_t DoWrite(Signal sig, const void *buff, size_t len);
	virtual bool DoSeek(Signal sig, long offset, size_t offsetPrev, SeekMode seekMode);
	virtual bool DoFlush(Signal sig);
	virtual bool DoClose(Signal sig);
	virtual size_t DoGetSize();
	inline void Initialize() { _crc32.Initialize(); }
	inline ULong GetCRC32() const { return _crc32.GetResult(); }
	inline size_t GetBytes() const { return _crc32.GetBytes(); }
};

}

#endif
