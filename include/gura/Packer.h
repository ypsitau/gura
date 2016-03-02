//=============================================================================
// Packer
//=============================================================================
#ifndef __GURA_PACKER_H__
#define __GURA_PACKER_H__

#include "Common.h"
#include "Value.h"

namespace Gura {

//-----------------------------------------------------------------------------
// Packer
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE Packer {
public:
	bool Pack(Environment &env, const char *format, const ValueList &valListArg);
	Value Unpack(Environment &env, const char *format,
				 const ValueList &valListArg, bool exceedErrorFlag);
	bool PutChar(Environment &env, Char num);
	bool PutUChar(Environment &env, UChar num);
	bool PutShort(Environment &env, Short num, bool bigEndianFlag);
	bool PutUShort(Environment &env, UShort num, bool bigEndianFlag);
	bool PutInt32(Environment &env, Int32 num, bool bigEndianFlag);
	bool PutUInt32(Environment &env, UInt32 num, bool bigEndianFlag);
	bool PutInt64(Environment &env, Int64 num, bool bigEndianFlag);
	bool PutUInt64(Environment &env, UInt64 num, bool bigEndianFlag);
	bool GetChar(Environment &env, Char *pNum);
	bool GetUChar(Environment &env, UChar *pNum);
	bool GetShort(Environment &env, Short *pNum, bool bigEndianFlag);
	bool GetUShort(Environment &env, UShort *pNum, bool bigEndianFlag);
	bool GetInt32(Environment &env, Int32 *pNum, bool bigEndianFlag);
	bool GetUInt32(Environment &env, UInt32 *pNum, bool bigEndianFlag);
	bool GetInt64(Environment &env, Int64 *pNum, bool bigEndianFlag);
	bool GetUInt64(Environment &env, UInt64 *pNum, bool bigEndianFlag);
public:
	virtual bool PackPrepare(Environment &env, size_t bytes) = 0;
	virtual void PackBuffer(const UChar *buff, size_t bytes) = 0;
	virtual const UChar *UnpackPrepare(Environment &env, size_t bytes, bool exceedErrorFlag) = 0;
private:
	static bool CheckString(Environment &env,
							const ValueList &valList, ValueList::const_iterator pValue);
	static bool CheckNumber(Environment &env,
							const ValueList &valList, ValueList::const_iterator pValue);
	static bool CheckNumber(Environment &env, const ValueList &valList,
							ValueList::const_iterator pValue, Number numMin, Number numMax);
private:
	inline void PackForward(size_t bytes) {
		PackBuffer(nullptr, bytes);
	}
	inline void PackChar(Char num) {
		PackUChar(static_cast<UChar>(num));
	}
	inline void PackUChar(UChar num) {
		PackBuffer(&num, sizeof(UChar));
	}
	inline void PackShort(Short num, bool bigEndianFlag) {
		PackUShort(static_cast<UShort>(num), bigEndianFlag);
	}
	void PackUShort(UShort num, bool bigEndianFlag);
	inline void PackInt32(Int32 num, bool bigEndianFlag) {
		PackUInt32(static_cast<UInt32>(num), bigEndianFlag);
	}
	void PackUInt32(UInt32 num, bool bigEndianFlag);
	inline void PackInt64(Int64 num, bool bigEndianFlag) {
		PackUInt64(static_cast<UInt64>(num), bigEndianFlag);
	}
	void PackUInt64(UInt64 num, bool bigEndianFlag);
	inline void PackFloat(float num, bool bigEndianFlag) {
		PackUInt32(*reinterpret_cast<UInt32 *>(&num), bigEndianFlag);
	}
	inline void PackDouble(double num, bool bigEndianFlag) {
		PackUInt64(*reinterpret_cast<UInt64 *>(&num), bigEndianFlag);
	}
private:
	inline static Char UnpackChar(const UChar *pByte) {
		return static_cast<Char>(UnpackUChar(pByte));
	}
	inline static UChar UnpackUChar(const UChar *pByte) { return *pByte; }
	inline static Short UnpackShort(const UChar *pByte, bool bigEndianFlag) {
		return static_cast<Short>(UnpackUShort(pByte, bigEndianFlag));
	}
	static UShort UnpackUShort(const UChar *pByte, bool bigEndianFlag);
	inline static Int32 UnpackInt32(const UChar *pByte, bool bigEndianFlag) {
		return static_cast<Int32>(UnpackUInt32(pByte, bigEndianFlag));
	}
	static UInt32 UnpackUInt32(const UChar *pByte, bool bigEndianFlag);
	inline static Int64 UnpackInt64(const UChar *pByte, bool bigEndianFlag) {
		return static_cast<Int64>(UnpackUInt64(pByte, bigEndianFlag));
	}
	static UInt64 UnpackUInt64(const UChar *pByte, bool bigEndianFlag);
	inline static float UnpackFloat(const UChar *pByte, bool bigEndianFlag) {
		UInt32 num = UnpackUInt32(pByte, bigEndianFlag);
		return *reinterpret_cast<float *>(&num);
	}
	inline static double UnpackDouble(const UChar *pByte, bool bigEndianFlag) {
		UInt64 num = UnpackUInt64(pByte, bigEndianFlag);
		return *reinterpret_cast<double *>(&num);
	}
};

}

#endif
