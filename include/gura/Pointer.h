//=============================================================================
// Pointer
//=============================================================================
#ifndef __GURA_POINTER_H__
#define __GURA_POINTER_H__

#include "Environment.h"
#include "Signal.h"
#include "Value.h"

namespace Gura {

//-----------------------------------------------------------------------------
// Pointer
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE Pointer : public Packer {
public:
	class GURA_DLLDECLARE IteratorUnpack : public Iterator {
	private:
		AutoPtr<Pointer> _pPointer;
		String _format;
		ValueList _valListArg;
	public:
		IteratorUnpack(Pointer *pPointer, const char *format, const ValueList &valListArg);
		virtual Iterator *GetSource();
		virtual bool DoNext(Environment &env, Value &value);
		virtual String ToString() const;
		virtual void GatherFollower(Environment::Frame *pFrame, EnvironmentSet &envSet);
	};
	template<typename T> class GURA_DLLDECLARE IteratorEach : public Iterator {
	private:
		AutoPtr<Pointer> _pPointer;
		bool _bigEndianFlag;
	public:
		IteratorEach(Pointer *pPointer, bool bigEndianFlag) :
							_pPointer(pPointer), _bigEndianFlag(bigEndianFlag) {
		}
		virtual Iterator *GetSource() {
			return nullptr;
		}
		virtual bool DoNext(Environment &env, Value &value) {
			T num;
			if (!_pPointer->Get(env, &num, _bigEndianFlag, false)) return false;
			value = Value(num);
			return true;
		}
		virtual String ToString() const {
			return String("pointer.each");
		}
		virtual void GatherFollower(Environment::Frame *pFrame, EnvironmentSet &envSet) {
		}
	};
protected:
	int _cntRef;
	size_t _offset;
public:
	Gura_DeclareReferenceAccessor(Pointer)
public:
	Pointer(size_t offset);
protected:
	virtual ~Pointer();
public:
	inline void SetOffset(size_t offset) { _offset = offset; }
	inline size_t GetOffset() const { return _offset; }
	inline void Reset() { _offset = 0; }
	inline size_t GetSize() const {
		size_t bytesEntire = GetEntireSize();
		return (_offset < bytesEntire)? bytesEntire - _offset : 0;
	}
	bool Advance(Environment &env, int distance);
	bool PackStay(Environment &env, const char *format, const ValueList &valListArg);
	Value UnpackStay(Environment &env, const char *format,
				 const ValueList &valListArg, bool exeedErrorFlag);
	template<typename T> bool PutStay(Environment &env, T num, bool bigEndianFlag) {
		size_t offset = _offset;
		bool rtn = Put<T>(env, num, bigEndianFlag);
		_offset = offset;
		return rtn;
	}
	template<typename T> bool GetStay(Environment &env, T *pNum, bool bigEndianFlag, bool exceedErrorFlag) {
		size_t offset = _offset;
		bool rtn = Get<T>(env, pNum, bigEndianFlag, exceedErrorFlag);
		_offset = offset;
		return rtn;
	}
#if 0
	bool PutCharStay(Environment &env, Char num);
	bool PutUCharStay(Environment &env, UChar num);
	bool PutShortStay(Environment &env, Short num, bool bigEndianFlag);
	bool PutUShortStay(Environment &env, UShort num, bool bigEndianFlag);
	bool PutInt32Stay(Environment &env, Int32 num, bool bigEndianFlag);
	bool PutUInt32Stay(Environment &env, UInt32 num, bool bigEndianFlag);
	bool PutInt64Stay(Environment &env, Int64 num, bool bigEndianFlag);
	bool PutUInt64Stay(Environment &env, UInt64 num, bool bigEndianFlag);
	bool PutFloatStay(Environment &env, float num, bool bigEndianFlag);
	bool PutDoubleStay(Environment &env, double num, bool bigEndianFlag);
	bool GetCharStay(Environment &env, Char *pNum, bool exceedErrorFlag);
	bool GetUCharStay(Environment &env, UChar *pNum, bool exceedErrorFlag);
	bool GetShortStay(Environment &env, Short *pNum, bool bigEndianFlag, bool exceedErrorFlag);
	bool GetUShortStay(Environment &env, UShort *pNum, bool bigEndianFlag, bool exceedErrorFlag);
	bool GetInt32Stay(Environment &env, Int32 *pNum, bool bigEndianFlag, bool exceedErrorFlag);
	bool GetUInt32Stay(Environment &env, UInt32 *pNum, bool bigEndianFlag, bool exceedErrorFlag);
	bool GetInt64Stay(Environment &env, Int64 *pNum, bool bigEndianFlag, bool exceedErrorFlag);
	bool GetUInt64Stay(Environment &env, UInt64 *pNum, bool bigEndianFlag, bool exceedErrorFlag);
	bool GetFloatStay(Environment &env, float *pNum, bool bigEndianFlag, bool exceedErrorFlag);
	bool GetDoubleStay(Environment &env, double *pNum, bool bigEndianFlag, bool exceedErrorFlag);
#endif
public:
	virtual Pointer *Clone() const = 0;
	virtual Object *GetTarget() const = 0;
	virtual const UChar *GetPointerC() const = 0;
	virtual size_t GetEntireSize() const = 0;
	virtual bool IsWritable() const = 0;
};

}

#endif
