//=============================================================================
// Array
//=============================================================================
#ifndef __GURA_ARRAY_H__
#define __GURA_ARRAY_H__

#include "Memory.h"
#include "Iterator.h"
#include "Stream.h"

#define Gura_ImplementArrayMethod_Array_UnaryFunc(op) \
inline static bool op(Signal &sig, AutoPtr<Array> &pArrayRtn, const Array *pArray) { \
	return ApplyUnaryFunc(sig, unaryFuncPack_##op, pArrayRtn, pArray); \
}

#define Gura_ImplementArrayMethod_Array_BinaryFunc(op) \
inline static bool op(Signal &sig, AutoPtr<Array> &pArrayRtn, const Array *pArrayL, const Array *pArrayR) { \
	return ApplyBinaryFunc(sig, binaryFuncPack_##op, pArrayRtn, pArrayL, pArrayR); \
} \
inline static bool op(Signal &sig, AutoPtr<Array> &pArrayRtn, const Array *pArrayL, const Double &elemR) { \
	return ApplyBinaryFunc_array_number(sig, binaryFuncPack_##op, pArrayRtn, pArrayL, elemR); \
} \
inline static bool op(Signal &sig, AutoPtr<Array> &pArrayRtn, const Double &elemL, const Array *pArrayR) { \
	return ApplyBinaryFunc_number_array(sig, binaryFuncPack_##op, pArrayRtn, elemL, pArrayR); \
} \
inline static bool op(Signal &sig, AutoPtr<Array> &pArrayRtn, const Array *pArrayL, const Complex &complexR) { \
	return ApplyBinaryFunc_array_complex(sig, binaryFuncPack_##op, pArrayRtn, pArrayL, complexR); \
} \
inline static bool op(Signal &sig, AutoPtr<Array> &pArrayRtn, const Complex &complexL, const Array *pArrayR) { \
	return ApplyBinaryFunc_complex_array(sig, binaryFuncPack_##op, pArrayRtn, complexL, pArrayR); \
}

namespace Gura {

//-----------------------------------------------------------------------------
// Array
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE Array {
public:
	enum ElemType {
		ETYPE_None,
		ETYPE_Boolean,
		ETYPE_Int8,
		ETYPE_UInt8,
		ETYPE_Int16,
		ETYPE_UInt16,
		ETYPE_Int32,
		ETYPE_UInt32,
		ETYPE_Int64,
		ETYPE_UInt64,
		ETYPE_Half,
		ETYPE_Float,
		ETYPE_Double,
		ETYPE_Complex,
		ETYPE_reserved1,
		ETYPE_Max,
	};
	enum ChannelPos {
		CHANNELPOS_Invalid,
		CHANNELPOS_None,
		CHANNELPOS_First,
		CHANNELPOS_Last,
	};
public:
	typedef bool (*UnaryFuncT)(Signal &sig, AutoPtr<Array> &pArrayRtn, const Array *pArray);
	typedef bool (*Unary2OutFuncT)(Signal &sig, AutoPtr<Array> &pArrayRtnA,
								   AutoPtr<Array> &pArrayRtnB, const Array *pArray);
	typedef bool (*BinaryFuncT_array_array)(Signal &sig, AutoPtr<Array> &pArrayRtn,
											const Array *pArrayL, const Array *pArrayR);
	typedef bool (*BinaryFuncT_array_number)(Signal &sig, AutoPtr<Array> &pArrayRtn,
											 const Array *pArrayL, const Double &elemR);
	typedef bool (*BinaryFuncT_number_array)(Signal &sig, AutoPtr<Array> &pArrayRtn,
											 const Double &elemL, const Array *pArrayR);
	typedef bool (*BinaryFuncT_array_complex)(Signal &sig, AutoPtr<Array> &pArrayRtn,
											  const Array *pArrayL, const Complex &complexR);
	typedef bool (*BinaryFuncT_complex_array)(Signal &sig, AutoPtr<Array> &pArrayRtn,
											  const Complex &complexL, const Array *pArrayR);
	typedef bool (*BinaryFuncT_number_number)(Signal &sig, AutoPtr<Array> &pArrayRtn,
											  const Double &elemL, const Double &elemR);
	typedef bool (*BinaryFuncT_complex_complex)(Signal &sig, AutoPtr<Array> &pArrayRtn,
												const Complex &complexL, const Complex &complexR);
	typedef bool (*InvertFuncT)(Signal &sig, AutoPtr<Array> &pArrayRtn, const Array *pArray, Double epsilon);
	struct UnaryFuncTable {
		UnaryFuncT funcs[ETYPE_Max];
	};
	struct UnaryFuncPack {
		const char *name;
		const char *symbol;
		UnaryFuncTable table;
	};
	struct BinaryFuncTable {
		BinaryFuncT_array_array funcs_array_array[ETYPE_Max][ETYPE_Max];
		BinaryFuncT_array_number funcs_array_number[ETYPE_Max];
		BinaryFuncT_number_array funcs_number_array[ETYPE_Max];
		BinaryFuncT_array_complex funcs_array_complex[ETYPE_Max];
		BinaryFuncT_complex_array funcs_complex_array[ETYPE_Max];
		BinaryFuncT_number_number func_number_number;
		BinaryFuncT_complex_complex func_complex_complex;
	};
	struct BinaryFuncPack {
		const char *name;
		const char *symbol;
		bool elemwiseFlag;
		BinaryFuncTable table;
	};
	struct InvertFuncTable {
		InvertFuncT funcs[ETYPE_Max];
	};
	typedef std::map<const Symbol *, ElemType, Symbol::LessThan> MapToElemType;
public:
	static UnaryFuncPack unaryFuncPack_Pos;
	static UnaryFuncPack unaryFuncPack_Neg;
	static BinaryFuncPack binaryFuncPack_Add;
	static BinaryFuncPack binaryFuncPack_Sub;
	static BinaryFuncPack binaryFuncPack_Mul;
	static BinaryFuncPack binaryFuncPack_Div;
	static BinaryFuncPack binaryFuncPack_Mod;
	static BinaryFuncPack binaryFuncPack_Pow;
	static BinaryFuncPack binaryFuncPack_Dot;
	static BinaryFuncPack binaryFuncPack_Eq;
	static BinaryFuncPack binaryFuncPack_Ne;
	static BinaryFuncPack binaryFuncPack_Gt;
	static BinaryFuncPack binaryFuncPack_Lt;
	static BinaryFuncPack binaryFuncPack_Ge;
	static BinaryFuncPack binaryFuncPack_Le;
	static BinaryFuncPack binaryFuncPack_And;
	static BinaryFuncPack binaryFuncPack_Or;
	static BinaryFuncPack binaryFuncPack_Xor;
	static BinaryFuncPack binaryFuncPack_Shl;
	static BinaryFuncPack binaryFuncPack_Shr;
	static UnaryFuncPack unaryFuncPack_Math_abs;
	static UnaryFuncPack unaryFuncPack_Math_acos;
	static UnaryFuncPack unaryFuncPack_Math_arg;
	static UnaryFuncPack unaryFuncPack_Math_asin;
	static UnaryFuncPack unaryFuncPack_Math_atan;
	static UnaryFuncPack unaryFuncPack_Math_ceil;
	static UnaryFuncPack unaryFuncPack_Math_conj;
	static UnaryFuncPack unaryFuncPack_Math_cos;
	static UnaryFuncPack unaryFuncPack_Math_cosh;
	static UnaryFuncPack unaryFuncPack_Math_delta;
	static UnaryFuncPack unaryFuncPack_Math_exp;
	static UnaryFuncPack unaryFuncPack_Math_floor;
	static UnaryFuncPack unaryFuncPack_Math_imag;
	static UnaryFuncPack unaryFuncPack_Math_log;
	static UnaryFuncPack unaryFuncPack_Math_log10;
	static UnaryFuncPack unaryFuncPack_Math_norm;
	static UnaryFuncPack unaryFuncPack_Math_real;
	static UnaryFuncPack unaryFuncPack_Math_relu;
	static UnaryFuncPack unaryFuncPack_Math_sigmoid;
	static UnaryFuncPack unaryFuncPack_Math_sin;
	static UnaryFuncPack unaryFuncPack_Math_sinh;
	static UnaryFuncPack unaryFuncPack_Math_sqrt;
	static UnaryFuncPack unaryFuncPack_Math_tan;
	static UnaryFuncPack unaryFuncPack_Math_tanh;
	static UnaryFuncPack unaryFuncPack_Math_unitstep;
	static InvertFuncTable invertFuncTable;
public:
	class GURA_DLLDECLARE Dimension {
	private:
		size_t _size;
		size_t _sizeProd;	// calculated by Array::UpdateMetrics()
		size_t _strides;	// calculated by Array::UpdateMetrics() 
	public:
		inline Dimension() : _size(0), _sizeProd(0), _strides(0) {}
		inline Dimension(const Dimension &dim) :
			_size(dim._size), _sizeProd(dim._sizeProd), _strides(dim._strides) {}
		inline Dimension(size_t size) : _size(size), _sizeProd(0), _strides(0) {}
		inline Dimension(size_t size, size_t sizeProd, size_t strides) :
			_size(size), _sizeProd(sizeProd), _strides(strides) {}
		inline size_t GetSize() const { return _size; }
		inline size_t GetSizeProd() const { return _sizeProd; }
		inline size_t GetStrides() const { return _strides; }
		inline void SetSizeProd(size_t sizeProd) { _sizeProd = sizeProd; }
		inline void SetStrides(size_t strides) { _strides = strides; }
	};
	class GURA_DLLDECLARE Dimensions : public std::vector<Dimension> {
	public:
		inline bool HasRowCol() const { return size() >= 2; }
		inline bool HasPlaneRowCol() const { return size() >= 3; }
		inline Dimension &GetBack(size_t idx) { return *(rbegin() + idx); }
		inline Dimension &GetPlane() { return GetBack(2); }
		inline Dimension &GetRow() { return GetBack(1); }
		inline Dimension &GetCol() { return GetBack(0); }
		inline const Dimension &GetBack(size_t idx) const { return *(rbegin() + idx); }
		inline const Dimension &GetPlane() const { return GetBack(2); }
		inline const Dimension &GetRow() const { return GetBack(1); }
		inline const Dimension &GetCol() const { return GetBack(0); }
		inline void SetBack(size_t idx, const Dimension &dim) { *(rbegin() + idx) = dim; }
		inline void SetPlane(const Dimension &dim) { SetBack(2, dim); } 
		inline void SetRow(const Dimension &dim) { SetBack(1, dim); } 
		inline void SetCol(const Dimension &dim) { SetBack(0, dim); } 
		inline bool IsColMajor() const { return !empty() && GetCol().GetStrides() != 1; }
		inline bool IsRowMajor() const { return !IsColMajor(); }
		inline size_t GetElemNum() const { return empty()? 1 : front().GetSizeProd(); }
		void Store(size_t size1);
		void Store(size_t size1, size_t size2);
		void Store(size_t size1, size_t size2, size_t size3);
		void Store(size_t size1, size_t size2, size_t size3, size_t size4);
		void Store(const Dimensions &dims);
		void Store(const_iterator pDim, const_iterator pDimEnd);
		void Store(size_t size1, const_iterator pDim, const_iterator pDimEnd);
		void Store(const_iterator pDim, const_iterator pDimEnd, size_t size1);
		void Store(const_iterator pDim, const_iterator pDimEnd, size_t size1, size_t size2);
		void Store(const_iterator pDim, const_iterator pDimEnd, size_t size1, size_t size2, size_t size3);
		void Store(const_iterator pDim, const_iterator pDimEnd,
						   size_t size1, size_t size2, size_t size3, size_t size4);
		void Store(const_iterator pDim1, const_iterator pDim1End,
						   const_iterator pDim2, const_iterator pDim2End);
		void Store(const ValueList &valList);
		bool HasShape(size_t size1) const;
		bool HasShape(size_t size1, size_t size2) const;
		bool HasShape(size_t size1, size_t size2, size_t size3) const;
		bool HasShape(size_t size1, size_t size2, size_t size3, size_t size4) const;
		bool HasShape(const Dimensions &dims) const;
		bool HasShape(const_iterator pDim, const_iterator pDimEnd) const;
		bool HasShape(size_t size1, const_iterator pDim, const_iterator pDimEnd) const;
		bool HasShape(const_iterator pDim, const_iterator pDimEnd, size_t size1) const;
		bool HasShape(const_iterator pDim, const_iterator pDimEnd, size_t size1, size_t size2) const;
		bool HasShape(const_iterator pDim, const_iterator pDimEnd, size_t size1, size_t size2, size_t size3) const;
		bool HasShape(const_iterator pDim, const_iterator pDimEnd,
					  size_t size1, size_t size2, size_t size3, size_t size4) const;
		bool HasShape(const_iterator pDim1, const_iterator pDim1End,
					  const_iterator pDim2, const_iterator pDim2End) const;
		bool HasEnoughDims(Signal &sig, size_t nDims, ChannelPos channelPos) const;
		static String ToString(const_iterator pDim, const_iterator pDimEnd, const char *sep = ", ");
		inline String ToString(const char *sep = ", ") const { return ToString(begin(), end(), sep); }
		inline void Print() const { ::printf("%s\n", ToString().c_str()); }
		bool Serialize(Environment &env, Stream &stream) const;
		bool Deserialize(Environment &env, Stream &stream);
		void UpdateMetrics();
		void SetColMajor();
		static bool Compare(const_iterator &pDim, const_iterator pDimEnd, size_t size1);
		static bool Compare(const_iterator &pDim, const_iterator pDimEnd, size_t size1, size_t size2);
		static bool Compare(const_iterator &pDim, const_iterator pDimEnd, size_t size1, size_t size2, size_t size3);
		static bool Compare(const_iterator &pDim, const_iterator pDimEnd, size_t size1, size_t size2, size_t size3, size_t size4);
		static bool Compare(const_iterator &pDimA, const_iterator pDimEndA,
							const_iterator &pDimB, const_iterator pDimEndB);
		static bool IsSameShape(const_iterator pDimA, const_iterator pDimEndA,
								const_iterator pDimB, const_iterator pDimEndB);
		inline static bool IsSameShape(const Dimensions &dimsA, const Dimensions &dimsB) {
			return IsSameShape(dimsA.begin(), dimsA.end(), dimsB.begin(), dimsB.end());
		}
		static bool IsElemwiseCalculatable(const Dimensions &dimsA, const Dimensions &dimsB);
		static bool CheckSameShape(Signal &sig, const_iterator pDimA, const_iterator pDimEndA,
								   const_iterator pDimB, const_iterator pDimEndB);
		inline static bool CheckSameShape(Signal &sig, const Dimensions &dimsA, const Dimensions &dimsB) {
			return CheckSameShape(sig, dimsA.begin(), dimsA.end(), dimsB.begin(), dimsB.end());
		}
		static bool CheckElemwiseCalculatable(Signal &sig, const BinaryFuncPack &pack,
											  const Dimensions &dimsL, const Dimensions &dimsR);
	};
	class GURA_DLLDECLARE Indexer {
	public:
		class GURA_DLLDECLARE Generator {
		private:
			size_t _strides;
			SizeTList _offsets;
			SizeTList::const_iterator _pOffset;
		public:
			inline Generator(size_t strides) : _strides(strides) {}
			inline void Add(size_t offset) { _offsets.push_back(offset); }
			inline bool IsEmpty() const { return _offsets.empty(); }
			inline size_t CalcOffset() const { return _strides * *_pOffset; }
			inline void Reset() { _pOffset = _offsets.begin(); }
			inline size_t GetSize() const { return _offsets.size(); }
			bool Next();
		};
		class GURA_DLLDECLARE GeneratorList : public std::vector<Generator *> {
		public:
			bool IsEmptyGenerator() const;
			void Reset();
			size_t CalcOffset() const;
			bool Next();
		};
		class GURA_DLLDECLARE GeneratorOwner : public GeneratorList {
		public:
			~GeneratorOwner();
			void Clear();
		};
	private:
		const Array *_pArray;
		const Dimensions &_dims;
		Dimensions::const_iterator _pDim;
		size_t _offsetTarget;
		std::unique_ptr<GeneratorOwner> _pGeneratorOwner;
	public:
		Indexer(const Array *pArray);
		bool InitIndices(Environment &env, const ValueList &valListIdx);
		void MakeResultDims(Dimensions &dimsRtn);
		inline size_t GetOffsetTarget() const { return _offsetTarget; }
		inline bool HasGenerator() const { return _pGeneratorOwner.get() != nullptr; }
		inline bool IsEmptyGenerator() const { return HasGenerator() && _pGeneratorOwner->IsEmptyGenerator(); }
		inline size_t GenerateOffset() const { return _pGeneratorOwner->CalcOffset(); }
		inline bool NextGenerator() { return _pGeneratorOwner->Next(); }
		size_t GetElemNumUnit() const;
		size_t GetStridesUnit() const;
		inline bool IsTargetScalar() const { return _pDim == _dims.end(); }
	};
protected:
	int _cntRef;
	ElemType _elemType;
	AutoPtr<Memory> _pMemory;
	Dimensions _dims;
	size_t _offsetBase;
	static MapToElemType _mapToElemType;
public:
	Gura_DeclareReferenceAccessor(Array);
protected:
	inline Array(const Array &src) : _cntRef(1),
		_elemType(src._elemType), _pMemory(src._pMemory->Reference()), _dims(src._dims),
		_offsetBase(src._offsetBase) {}
	inline Array(ElemType elemType) : _cntRef(1), _elemType(elemType), _offsetBase(0) {}
protected:
	virtual ~Array();
public:
	static void Bootup();
public:
	inline ElemType GetElemType() const { return _elemType; }
	inline bool IsElemType(ElemType elemType) const { return _elemType == elemType; }
	inline bool IsColMajor() const { return _dims.IsColMajor(); }
	inline bool IsRowMajor() const { return _dims.IsRowMajor(); }
	inline void AllocMemory() {
		_pMemory.reset(new MemoryHeap(GetElemBytes() * GetElemNum()));
	}
	inline void SetMemory(Memory *pMemory, size_t offsetBase) {
		_pMemory.reset(pMemory), _offsetBase = offsetBase;
	}
	inline Memory &GetMemory() { return *_pMemory; }
	inline const Memory &GetMemory() const { return *_pMemory; }
	inline Dimensions &GetDims() { return _dims; }
	inline const Dimensions &GetDims() const { return _dims; }
	inline bool IsScalar() const { return _dims.empty(); }
	inline size_t GetElemNum() const { return _dims.GetElemNum(); }
	inline void SetOffsetBase(size_t offsetBase) { _offsetBase = offsetBase; }
	inline size_t GetOffsetBase() const { return _offsetBase; }
	inline char *GetPointerRawOrigin() { return _pMemory->GetPointer(); }
	inline const char *GetPointerRawOrigin() const { return _pMemory->GetPointer(); }
	inline char *GetPointerRaw() { return GetPointerRawOrigin() + GetOffsetBase() * GetElemBytes(); }
	inline const char *GetPointerRaw() const { return GetPointerRawOrigin() + GetOffsetBase() * GetElemBytes(); }
	virtual Array *Clone(bool cloneMemoryFlag) const = 0;
	virtual String ToString(bool exprFlag, size_t nDimsOnHorz = 1) const = 0;
	virtual Array *CreateLike() const = 0;
	virtual void Dump(Signal &sig, Stream &stream, bool upperFlag) const = 0;
	virtual bool DoesContainZero() const = 0;
	virtual bool DoesContainMinus() const = 0;
	virtual bool DoesContainZeroOrMinus() const = 0;
	virtual Double GetScalarNumber() const = 0;
	virtual Complex GetScalarComplex() const = 0;
	virtual void CopyToList(Object_list *pObjList) const = 0;
	virtual void FillRand() = 0;
	virtual void FillRandRange(UInt range) = 0;
	virtual void FillRandNormal(double mu, double sigma) = 0;
	static size_t GetElemBytes(ElemType elemType);
	inline size_t GetElemBytes() const { return GetElemBytes(_elemType); }
	static const char *GetElemTypeName(ElemType elemType);
	inline const char *GetElemTypeName() const { return GetElemTypeName(_elemType); }
	void FlipAxisMajor();
	void StoreDims(const Dimensions &dims);
	void SetDim(size_t size);
	void SetDims(size_t size1, size_t size2);
	void SetDims(size_t size1, size_t size2, size_t size3);
	void SetDims(size_t size1, size_t size2, size_t size3, size_t size4);
	void SetDims(const Dimensions &dims);
	void SetDims(Dimensions::const_iterator pDim, Dimensions::const_iterator pDimEnd);
	void SetDims(size_t size,
				 Dimensions::const_iterator pDim, Dimensions::const_iterator pDimEnd);
	void SetDims(Dimensions::const_iterator pDim, Dimensions::const_iterator pDimEnd,
				 size_t size);
	void SetDims(Dimensions::const_iterator pDim, Dimensions::const_iterator pDimEnd,
				 size_t size1, size_t size2);
	void SetDims(Dimensions::const_iterator pDim, Dimensions::const_iterator pDimEnd,
				 size_t size1, size_t size2, size_t size3);
	void SetDims(Dimensions::const_iterator pDim, Dimensions::const_iterator pDimEnd,
				 size_t size1, size_t size2, size_t size3, size_t size4);
	void SetDims(Dimensions::const_iterator pDim1, Dimensions::const_iterator pDim1End,
				 Dimensions::const_iterator pDim2, Dimensions::const_iterator pDim2End);
	void SetDims(const ValueList &valList);
	inline void PrintDims() const { _dims.Print(); }
	inline void UpdateMetrics() { _dims.UpdateMetrics(); }
	inline void SetColMajor() { _dims.SetColMajor(); }
	void FillZero();
	virtual void Fill(Double num) = 0;
	virtual void RoundOff(AutoPtr<Array> &pArrayRtn, double threshold) const = 0;
	bool Head(Signal &sig, AutoPtr<Array> &pArrayRtn, size_t n) const;
	bool Tail(Signal &sig, AutoPtr<Array> &pArrayRtn, size_t n) const;
	bool Offset(Signal &sig, AutoPtr<Array> &pArrayRtn, size_t n) const;
	virtual void Flatten(AutoPtr<Array> &pArrayRtn) const = 0;
	void Reshape(AutoPtr<Array> &pArrayRtn, const Dimensions &dims) const;
	bool Reshape(Signal &sig, AutoPtr<Array> &pArrayRtn, const ValueList &valList) const;
	bool Transpose(Signal &sig, AutoPtr<Array> &pArrayRtn, const ValueList &valList) const;
	virtual void Transpose(AutoPtr<Array> &pArrayRtn, const IntList &axes) const = 0;
	void Transpose2d(AutoPtr<Array> &pArrayRtn) const;
	virtual bool FindMax(Signal &sig, AutoPtr<Array> &pArrayRtn, int axis) const = 0;
	virtual bool FindMin(Signal &sig, AutoPtr<Array> &pArrayRtn, int axis) const = 0;
	virtual bool FindMaxIndex(Signal &sig, AutoPtr<Array> &pArrayRtn, int axis, bool lastFlag) const = 0;
	virtual bool FindMinIndex(Signal &sig, AutoPtr<Array> &pArrayRtn, int axis, bool lastFlag) const = 0;
	virtual bool CalcSum(Signal &sig, AutoPtr<Array> &pArrayRtn, int axis, bool meanFlag) const = 0;
	virtual bool CalcVar(Signal &sig, AutoPtr<Array> &pArrayRtn, int axis, bool populationFlag, bool stdFlag) const = 0;
	bool Paste(Signal &sig, size_t offset, const Array *pArraySrc);
	virtual bool ExpandKernelVec1d(
		Signal &sig, AutoPtr<Array> &pArrayVec, size_t *pSize, size_t sizeKernel, size_t stridesKernel,
		size_t sizePad, ChannelPos channelPos, Double padNum) const = 0;
	virtual bool ExpandKernelVec2d(
		Signal &sig, AutoPtr<Array> &pArrayVec, size_t *pSizeRow, size_t *pSizeCol,
		size_t sizeKernelRow, size_t sizeKernelCol,
		size_t stridesKernelRow, size_t stridesKernelCol, size_t sizePadRow, size_t sizePadCol,
		ChannelPos channelPos, Double padNum) const = 0;
	virtual bool ExpandKernelVec3d(
		Signal &sig, AutoPtr<Array> &pArrayVec, size_t *pSizePlane, size_t *pSizeRow, size_t *pSizeCol,
		size_t sizeKernelPlane, size_t sizeKernelRow, size_t sizeKernelCol,
		size_t stridesKernelPlane, size_t stridesKernelRow, size_t stridesKernelCol,
		size_t sizePadPlane, size_t sizePadRow, size_t sizePadCol,
		ChannelPos channelPos, Double padNum) const = 0;
	virtual bool RestoreKernelVec1d(
		Signal &sig, AutoPtr<Array> &pArrayRtn, size_t size, size_t sizeKernel, size_t stridesKernel,
		size_t sizePad, ChannelPos channelPos) const = 0;
	virtual bool RestoreKernelVec2d(
		Signal &sig, AutoPtr<Array> &pArrayRtn, size_t sizeRow, size_t sizeCol,
		size_t sizeKernelRow, size_t sizeKernelCol,
		size_t stridesKernelRow, size_t stridesKernelCol,
		size_t sizePadRow, size_t sizePadCol, ChannelPos channelPos) const = 0;
	virtual bool RestoreKernelVec3d(
		Signal &sig, AutoPtr<Array> &pArrayRtn, size_t sizePlane, size_t sizeRow, size_t sizeCol,
		size_t sizeKernelPlane, size_t sizeKernelRow, size_t sizeKernelCol,
		size_t stridesKernelPlane, size_t stridesKernelRow, size_t stridesKernelCol,
		size_t sizePadPlane, size_t sizePadRow, size_t sizePadCol, ChannelPos channelPos) const = 0;
	virtual bool CalcAveragePool1d(
		Signal &sig, AutoPtr<Array> &pArrayRtn, size_t sizeKernel, size_t stridesKernel,
		size_t sizePad, ChannelPos channelPos) const = 0;
	virtual bool CalcAveragePool2d(
		Signal &sig, AutoPtr<Array> &pArrayRtn, size_t sizeKernelRow, size_t sizeKernelCol,
		size_t stridesKernelRow, size_t stridesKernelCol,
		size_t sizePadRow, size_t sizePadCol, ChannelPos channelPos) const = 0;
	virtual bool CalcAveragePool3d(
		Signal &sig, AutoPtr<Array> &pArrayRtn, size_t sizeKernelPlane, size_t sizeKernelRow, size_t sizeKernelCol,
		size_t stridesKernelPlane, size_t stridesKernelRow, size_t stridesKernelCol,
		size_t sizePadPlane, size_t sizePadRow, size_t sizePadCol, ChannelPos channelPos) const = 0;
	virtual bool CalcMaxPool1d(
		Signal &sig, AutoPtr<Array> &pArrayRtn, size_t sizeKernel, size_t stridesKernel,
		size_t sizePad, ChannelPos channelPos) const = 0;
	virtual bool CalcMaxPool2d(
		Signal &sig, AutoPtr<Array> &pArrayRtn, size_t sizeKernelRow, size_t sizeKernelCol,
		size_t stridesKernelRow, size_t stridesKernelCol,
		size_t sizePadRow, size_t sizePadCol, ChannelPos channelPos) const = 0;
	virtual bool CalcMaxPool3d(
		Signal &sig, AutoPtr<Array> &pArrayRtn, size_t sizeKernelPlane, size_t sizeKernelRow, size_t sizeKernelCol,
		size_t stridesKernelPlane, size_t stridesKernelRow, size_t stridesKernelCol,
		size_t sizePadPlane, size_t sizePadRow, size_t sizePadCol, ChannelPos channelPos) const = 0;
	virtual bool CalcMaxPoolWithIndex1d(
		Signal &sig, AutoPtr<Array> &pArrayRtn, AutoPtr<Array> &pArrayOfIndex,
		size_t sizeKernel, size_t stridesKernel,
		size_t sizePad, ChannelPos channelPos) const = 0;
	virtual bool CalcMaxPoolWithIndex2d(
		Signal &sig, AutoPtr<Array> &pArrayRtn, AutoPtr<Array> &pArrayOfIndex,
		size_t sizeKernelRow, size_t sizeKernelCol,
		size_t stridesKernelRow, size_t stridesKernelCol,
		size_t sizePadRow, size_t sizePadCol, ChannelPos channelPos) const = 0;
	virtual bool CalcMaxPoolWithIndex3d(
		Signal &sig, AutoPtr<Array> &pArrayRtn, AutoPtr<Array> &pArrayOfIndex,
		size_t sizeKernelPlane, size_t sizeKernelRow, size_t sizeKernelCol,
		size_t stridesKernelPlane, size_t stridesKernelRow, size_t stridesKernelCol,
		size_t sizePadPlane, size_t sizePadRow, size_t sizePadCol, ChannelPos channelPos) const = 0;
	virtual void AccumMaxPoolBackward(AutoPtr<Array> &pArrayGradDst, const Array *pArrayOfIndex) const = 0;
	bool CheckDimsGearForCalcConv(Signal &sig, const Dimensions &dimsGear,
								  size_t nDimsKernel, ChannelPos channelPos) const;
	virtual bool CalcConv1d(
		Signal &sig, AutoPtr<Array> &pArrayRtn, const Array *pArrayGear, size_t stridesKernel,
		size_t sizePad, ChannelPos channelPos) const = 0;
	virtual bool CalcConv2d(
		Signal &sig, AutoPtr<Array> &pArrayRtn, const Array *pArrayGear,
		size_t stridesKernelRow, size_t stridesKernelCol,
		size_t sizePadRow, size_t sizePadCol, ChannelPos channelPos) const = 0;
	virtual bool CalcConv3d(
		Signal &sig, AutoPtr<Array> &pArrayRtn, const Array *pArrayGear,
		size_t stridesKernelPlane, size_t stridesKernelRow, size_t stridesKernelCol,
		size_t sizePadPlane, size_t sizePadRow, size_t sizePadCol, ChannelPos channelPos) const = 0;
	virtual Iterator *CreateIteratorEach(bool flatFlag) const = 0;
	bool IsSquare() const;
	bool HasSameElements(const Array &array) const;
	void CloneMemory();
	void PrepareModification();
	static Value ToValue(Environment &env, Array *pArray);
	bool Serialize(Environment &env, Stream &stream) const;
	static Array *Deserialize(Environment &env, Stream &stream);
public:
	static Array *Create(ElemType elemType);
public:
	static ElemType SymbolToElemType(const Symbol *pSymbol);
	static ElemType SymbolToElemType(Signal &sig, const Symbol *pSymbol);
	static ChannelPos SymbolToChannelPos(Signal &sig, const Symbol *pSymbol);
	static ChannelPos SymbolToChannelPos(const Symbol *pSymbol);
	static const Symbol *ChannelPosToSymbol(ChannelPos channelPos);
	inline static bool IsSameMajor(const Array *pArrayA, const Array *pArrayB) {
		return pArrayA->IsColMajor() == pArrayB->IsColMajor();
	}
	inline static bool CheckSameShape(Signal &sig, const Array *pArrayA, const Array *pArrayB) {
		return Dimensions::CheckSameShape(sig, pArrayA->GetDims(), pArrayB->GetDims());
	}
	inline static bool CheckElemwiseCalculatable(Signal &sig, const BinaryFuncPack &pack,
												 const Array *pArrayL, const Array *pArrayR) {
		return Dimensions::CheckElemwiseCalculatable(sig, pack, pArrayL->GetDims(), pArrayR->GetDims());
	}
	static bool CopyElements(Environment &env, Array *pArrayDst, const Array *pArraySrc);
	static bool CopyElements(Environment &env, void *pElemRawDst, ElemType elemTypeDst,
							 const void *pElemRawSrc, ElemType elemTypeSrc, size_t nElems);
	static bool ApplyUnaryFunc(
		Signal &sig, const UnaryFuncPack &pack, AutoPtr<Array> &pArrayRtn, const Array *pArray);
	static Value ApplyUnaryFuncOnValue(
		Environment &env, const UnaryFuncPack &pack, const Value &value);
	static bool ApplyBinaryFunc(
		Signal &sig, const BinaryFuncPack &pack, AutoPtr<Array> &pArrayRtn, const Array *pArrayL, const Array *pArrayR);
	static bool ApplyBinaryFunc_array_array(
		Signal &sig, const BinaryFuncPack &pack, AutoPtr<Array> &pArrayRtn, const Array *pArrayL, const Array *pArrayR);
	static Value ApplyBinaryFuncOnValue_array_array(
		Environment &env, const BinaryFuncPack &pack, const Value &valueL, const Value &valueR);
	static bool ApplyBinaryFunc_array_number(
		Signal &sig, const BinaryFuncPack &pack, AutoPtr<Array> &pArrayRtn, const Array *pArrayL, const Double &elemR);
	static Value ApplyBinaryFuncOnValue_array_number(
		Environment &env, const BinaryFuncPack &pack, const Value &valueL, const Value &valueR);
	static bool ApplyBinaryFunc_number_array(
		Signal &sig, const BinaryFuncPack &pack, AutoPtr<Array> &pArrayRtn, const Double &elemL, const Array *pArrayR);
	static Value ApplyBinaryFuncOnValue_number_array(
		Environment &env, const BinaryFuncPack &pack, const Value &valueL, const Value &valueR);
	static bool ApplyBinaryFunc_array_complex(
		Signal &sig, const BinaryFuncPack &pack, AutoPtr<Array> &pArrayRtn, const Array *pArrayL, const Complex &complexR);
	static Value ApplyBinaryFuncOnValue_array_complex(
		Environment &env, const BinaryFuncPack &pack, const Value &valueL, const Value &valueR);
	static bool ApplyBinaryFunc_complex_array(
		Signal &sig, const BinaryFuncPack &pack, AutoPtr<Array> &pArrayRtn, const Complex &complexL, const Array *pArrayR);
	static Value ApplyBinaryFuncOnValue_complex_array(
		Environment &env, const BinaryFuncPack &pack, const Value &valueL, const Value &valueR);
	static bool ApplyInvertFunc(
		Signal &sig, AutoPtr<Array> &pArrayRtn, const Array *pArray, Double epsilon);
	static void SetError_UnacceptableValueAsElement(Environment &env, const Value &value);
public:
	Gura_ImplementArrayMethod_Array_UnaryFunc(Pos);
	Gura_ImplementArrayMethod_Array_UnaryFunc(Neg);
	Gura_ImplementArrayMethod_Array_BinaryFunc(Add);
	Gura_ImplementArrayMethod_Array_BinaryFunc(Sub);
	Gura_ImplementArrayMethod_Array_BinaryFunc(Mul);
	Gura_ImplementArrayMethod_Array_BinaryFunc(Div);
	Gura_ImplementArrayMethod_Array_BinaryFunc(Mod);
	Gura_ImplementArrayMethod_Array_BinaryFunc(Pow);
	Gura_ImplementArrayMethod_Array_BinaryFunc(Dot);
	Gura_ImplementArrayMethod_Array_BinaryFunc(Eq);
	Gura_ImplementArrayMethod_Array_BinaryFunc(Ne);
	Gura_ImplementArrayMethod_Array_BinaryFunc(Gt);
	Gura_ImplementArrayMethod_Array_BinaryFunc(Lt);
	Gura_ImplementArrayMethod_Array_BinaryFunc(Ge);
	Gura_ImplementArrayMethod_Array_BinaryFunc(Le);
	Gura_ImplementArrayMethod_Array_BinaryFunc(And);
	Gura_ImplementArrayMethod_Array_BinaryFunc(Or);
	Gura_ImplementArrayMethod_Array_BinaryFunc(Xor);
	Gura_ImplementArrayMethod_Array_BinaryFunc(Shl);
	Gura_ImplementArrayMethod_Array_BinaryFunc(Shr);
	Gura_ImplementArrayMethod_Array_UnaryFunc(Math_abs);
	Gura_ImplementArrayMethod_Array_UnaryFunc(Math_acos);
	Gura_ImplementArrayMethod_Array_UnaryFunc(Math_arg);
	Gura_ImplementArrayMethod_Array_UnaryFunc(Math_asin);
	Gura_ImplementArrayMethod_Array_UnaryFunc(Math_atan);
	Gura_ImplementArrayMethod_Array_UnaryFunc(Math_ceil);
	Gura_ImplementArrayMethod_Array_UnaryFunc(Math_conj);
	Gura_ImplementArrayMethod_Array_UnaryFunc(Math_cos);
	Gura_ImplementArrayMethod_Array_UnaryFunc(Math_cosh);
	Gura_ImplementArrayMethod_Array_UnaryFunc(Math_delta);
	Gura_ImplementArrayMethod_Array_UnaryFunc(Math_exp);
	Gura_ImplementArrayMethod_Array_UnaryFunc(Math_floor);
	Gura_ImplementArrayMethod_Array_UnaryFunc(Math_imag);
	Gura_ImplementArrayMethod_Array_UnaryFunc(Math_log);
	Gura_ImplementArrayMethod_Array_UnaryFunc(Math_log10);
	Gura_ImplementArrayMethod_Array_UnaryFunc(Math_norm);
	Gura_ImplementArrayMethod_Array_UnaryFunc(Math_real);
	Gura_ImplementArrayMethod_Array_UnaryFunc(Math_relu);
	Gura_ImplementArrayMethod_Array_UnaryFunc(Math_sigmoid);
	Gura_ImplementArrayMethod_Array_UnaryFunc(Math_sin);
	Gura_ImplementArrayMethod_Array_UnaryFunc(Math_sinh);
	Gura_ImplementArrayMethod_Array_UnaryFunc(Math_sqrt);
	Gura_ImplementArrayMethod_Array_UnaryFunc(Math_tan);
	Gura_ImplementArrayMethod_Array_UnaryFunc(Math_tanh);
	Gura_ImplementArrayMethod_Array_UnaryFunc(Math_unitstep);
public:
	template<typename T_Elem> inline static bool IsZero(const T_Elem &elem) { return elem == 0; }
	template<typename T_ElemRtn, typename T_Elem, typename T_Operator>
	static bool UnaryFuncTmpl(Signal &sig, AutoPtr<Array> &pArrayRtn, const Array *pArray);
	template<typename T_ElemRtn, typename T_Elem, typename T_Operator>
	static bool UnaryFuncTmpl_ExcludeZero(Signal &sig, AutoPtr<Array> &pArrayRtn, const Array *pArray);
	template<typename T_ElemRtnA, typename T_ElemRtnB, typename T_Elem, typename T_Operator>
	static bool Unary2OutFuncTmpl(Signal &sig, AutoPtr<Array> &pArrayRtnA,
								  AutoPtr<Array> &pArrayRtnB, const Array *pArray);
	template<typename T_ElemRtn, typename T_ElemL, typename T_ElemR, typename T_Operator>
	static bool BinaryFuncTmpl_array_array(Signal &sig, AutoPtr<Array> &pArrayRtn,
										   const Array *pArrayL, const Array *pArrayR);
	template<typename T_ElemRtn, typename T_ElemL, typename T_ElemR, typename T_Operator>
	static bool BinaryFuncTmpl_array_scalar(Signal &sig, AutoPtr<Array> &pArrayRtn,
											const Array *pArrayL, const T_ElemR &elemR);
	template<typename T_ElemRtn, typename T_ElemL, typename T_ElemR, typename T_Operator>
	static bool BinaryFuncTmpl_scalar_array(Signal &sig, AutoPtr<Array> &pArrayRtn,
											const T_ElemL &elemL, const Array *pArrayR);
	template<typename T_ElemRtn, typename T_ElemL, typename T_ElemR, typename T_Operator>
	static bool BinaryFuncTmpl_scalar_scalar(Signal &sig, AutoPtr<Array> &pArrayRtn,
											 const T_ElemL &elemL, const T_ElemR &elemR);
	template<typename T_ElemRtn, typename T_ElemL, typename T_ElemR, typename T_Operator>
	static bool BinaryFuncTmpl_Div_array_array(Signal &sig, AutoPtr<Array> &pArrayRtn,
											   const Array *pArrayL, const Array *pArrayR);
	template<typename T_ElemRtn, typename T_ElemL, typename T_ElemR, typename T_Operator>
	static bool BinaryFuncTmpl_Div_array_scalar(Signal &sig, AutoPtr<Array> &pArrayRtn,
												const Array *pArrayL, const T_ElemR &elemR);
	template<typename T_ElemRtn, typename T_ElemL, typename T_ElemR, typename T_Operator>
	static bool BinaryFuncTmpl_Div_scalar_array(Signal &sig, AutoPtr<Array> &pArrayRtn,
												const T_ElemL &elemL, const Array *pArrayR);
	template<typename T_ElemRtn, typename T_ElemL, typename T_ElemR, typename T_Operator>
	static bool BinaryFuncTmpl_Div_scalar_scalar(Signal &sig, AutoPtr<Array> &pArrayRtn,
												 const T_ElemL &elemL, const T_ElemR &elemR);
	template<typename T_ElemRtn, typename T_ElemL, typename T_ElemR>
	static void DotFuncTmpl_1d_1d(T_ElemRtn *pElemRtn, const T_ElemL *pElemL, const T_ElemR *pElemR, size_t size);
	template<typename T_ElemRtn, typename T_ElemL, typename T_ElemR>
	static void DotFuncTmpl_1d_2d(T_ElemRtn *pElemRtn,
								  const T_ElemL *pElemL, const Dimension &dimColL,
								  const T_ElemR *pElemR, const Dimension &dimRowR, const Dimension &dimColR);
	template<typename T_ElemRtn, typename T_ElemL, typename T_ElemR>
	static void DotFuncTmpl_2d_1d(T_ElemRtn *pElemRtn,
								  const T_ElemL *pElemL, const Dimension &dimRowL, const Dimension &dimColL,
								  const T_ElemR *pElemR, const Dimension &dimRowR);
	template<typename T_ElemRtn, typename T_ElemL, typename T_ElemR>
	static void DotFuncTmpl_2d_2d(T_ElemRtn *pElemRtn,
								  const T_ElemL *pElemL, const Dimension &dimRowL, const Dimension &dimColL,
								  const T_ElemR *pElemR, const Dimension &dimRowR, const Dimension &dimColR);
	template<typename T_ElemRtn, typename T_ElemL, typename T_ElemR>
	static bool BinaryFuncTmpl_Dot(Signal &sig, AutoPtr<Array> &pArrayRtn, const Array *pArrayL, const Array *pArrayR);
};
	
template<> inline bool Array::IsZero<Complex>(const Complex &elem) { return elem.IsZero(); }

//-----------------------------------------------------------------------------
// ArrayList
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE ArrayList : public std::vector<Array *> {
public:
	static const ArrayList Empty;
public:
	inline ArrayList() {}
};

//-----------------------------------------------------------------------------
// ArrayOwner
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE ArrayOwner : public ArrayList {
private:
	int _cntRef;
public:
	Gura_DeclareReferenceAccessor(ArrayOwner);
public:
	ArrayOwner();
private:
	~ArrayOwner();
public:
	void Clear();
};



}

#endif
