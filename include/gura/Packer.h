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
protected:
	int _cntRef;
public:
	Gura_DeclareReferenceAccessor(Packer)
public:
	class GURA_DLLDECLARE IteratorUnpack : public Iterator {
	private:
		AutoPtr<Packer> _pPacker;
		String _format;
		ValueList _valListArg;
	public:
		IteratorUnpack(Packer *pPacker, const char *format, const ValueList &valListArg);
		virtual Iterator *GetSource();
		virtual bool DoNext(Environment &env, Value &value);
		virtual String ToString() const;
		virtual void GatherFollower(Environment::Frame *pFrame, EnvironmentSet &envSet);
	};
	template<typename T> class GURA_DLLDECLARE IteratorEach : public Iterator {
	private:
		AutoPtr<Packer> _pPacker;
		bool _bigEndianFlag;
	public:
		IteratorEach(Packer *pPacker, bool bigEndianFlag) : Iterator(false),
							_pPacker(pPacker), _bigEndianFlag(bigEndianFlag) {
		}
		virtual Iterator *GetSource() {
			return nullptr;
		}
		virtual bool DoNext(Environment &env, Value &value) {
			T num;
			if (!_pPacker->Get(env, &num, _bigEndianFlag, false)) return false;
			value = Value(num);
			return true;
		}
		virtual String ToString() const {
			return String("packer.each");
		}
		virtual void GatherFollower(Environment::Frame *pFrame, EnvironmentSet &envSet) {
		}
	};
public:
	Packer();
protected:
	virtual ~Packer();
public:
	bool Pack(Environment &env, const char *format, const ValueList &valListArg);
	Value Unpack(Environment &env, const char *format,
				 const ValueList &valListArg, bool exceedErrorFlag);
	template<typename T> bool Put(Environment &env, T num, bool bigEndianFlag) {
		if (!PackPrepare(env, sizeof(T))) return false;
		Store<T>(num, bigEndianFlag);
		return true;
	}
	template<typename T> bool Get(Environment &env, T *pNum, bool bigEndianFlag, bool exceedErrorFlag) {
		const UChar *pByte = UnpackPrepare(env, sizeof(T), exceedErrorFlag);
		if (pByte == nullptr) return false;
		*pNum = Extract<T>(pByte, bigEndianFlag);
		return true;
	}
	bool PutBuffer(Environment &env, const void *buff, size_t bytes);
public:
	virtual bool PackPrepare(Environment &env, size_t bytes) = 0;
	virtual void PackBuffer(const void *buff, size_t bytes) = 0;
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
	template<typename T> void Store(T num, bool bigEndianFlag);
	template<typename T> T Extract(const UChar *pByte, bool bigEndianFlag);
#if 0
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
#endif
private:
#if 0
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
#endif
};

template<> void Packer::Store<Char>(Char num, bool bigEndianFlag);
template<> void Packer::Store<UChar>(UChar num, bool bigEndianFlag);
template<> void Packer::Store<Short>(Short num, bool bigEndianFlag);
template<> void Packer::Store<UShort>(UShort num, bool bigEndianFlag);
template<> void Packer::Store<Int32>(Int32 num, bool bigEndianFlag);
template<> void Packer::Store<UInt32>(UInt32 num, bool bigEndianFlag);
template<> void Packer::Store<Int64>(Int64 num, bool bigEndianFlag);
template<> void Packer::Store<UInt64>(UInt64 num, bool bigEndianFlag);
template<> void Packer::Store<Float>(Float num, bool bigEndianFlag);
template<> void Packer::Store<Double>(Double num, bool bigEndianFlag);

template<> Char Packer::Extract<Char>(const UChar *pByte, bool bigEndianFlag);
template<> UChar Packer::Extract<UChar>(const UChar *pByte, bool bigEndianFlag);
template<> Short Packer::Extract<Short>(const UChar *pByte, bool bigEndianFlag);
template<> UShort Packer::Extract<UShort>(const UChar *pByte, bool bigEndianFlag);
template<> Int32 Packer::Extract<Int32>(const UChar *pByte, bool bigEndianFlag);
template<> UInt32 Packer::Extract<UInt32>(const UChar *pByte, bool bigEndianFlag);
template<> Int64 Packer::Extract<Int64>(const UChar *pByte, bool bigEndianFlag);
template<> UInt64 Packer::Extract<UInt64>(const UChar *pByte, bool bigEndianFlag);
template<> Float Packer::Extract<Float>(const UChar *pByte, bool bigEndianFlag);
template<> Double Packer::Extract<Double>(const UChar *pByte, bool bigEndianFlag);

#if 0
template<> bool Packer::Put<Char>(Environment &env, Char num, bool bigEndianFlag);
template<> bool Packer::Put<UChar>(Environment &env, UChar num, bool bigEndianFlag);
template<> bool Packer::Put<Short>(Environment &env, Short num, bool bigEndianFlag);
template<> bool Packer::Put<UShort>(Environment &env, UShort num, bool bigEndianFlag);
template<> bool Packer::Put<Int32>(Environment &env, Int32 num, bool bigEndianFlag);
template<> bool Packer::Put<UInt32>(Environment &env, UInt32 num, bool bigEndianFlag);
template<> bool Packer::Put<Int64>(Environment &env, Int64 num, bool bigEndianFlag);
template<> bool Packer::Put<UInt64>(Environment &env, UInt64 num, bool bigEndianFlag);
template<> bool Packer::Put<Float>(Environment &env, Float num, bool bigEndianFlag);
template<> bool Packer::Put<Double>(Environment &env, Double num, bool bigEndianFlag);

template<> bool Packer::Get<Char>(Environment &env, Char *pNum, bool bigEndianFlag, bool exceedErrorFlag);
template<> bool Packer::Get<UChar>(Environment &env, UChar *pNum, bool bigEndianFlag, bool exceedErrorFlag);
template<> bool Packer::Get<Short>(Environment &env, Short *pNum, bool bigEndianFlag, bool exceedErrorFlag);
template<> bool Packer::Get<UShort>(Environment &env, UShort *pNum, bool bigEndianFlag, bool exceedErrorFlag);
template<> bool Packer::Get<Int32>(Environment &env, Int32 *pNum, bool bigEndianFlag, bool exceedErrorFlag);
template<> bool Packer::Get<UInt32>(Environment &env, UInt32 *pNum, bool bigEndianFlag, bool exceedErrorFlag);
template<> bool Packer::Get<Int64>(Environment &env, Int64 *pNum, bool bigEndianFlag, bool exceedErrorFlag);
template<> bool Packer::Get<UInt64>(Environment &env, UInt64 *pNum, bool bigEndianFlag, bool exceedErrorFlag);
template<> bool Packer::Get<Float>(Environment &env, Float *pNum, bool bigEndianFlag, bool exceedErrorFlag);
template<> bool Packer::Get<Double>(Environment &env, Double *pNum, bool bigEndianFlag, bool exceedErrorFlag);
#endif

}

#endif
