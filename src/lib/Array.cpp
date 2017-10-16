//=============================================================================
// Array
//=============================================================================
#include "stdafx.h"

namespace Gura {

//-----------------------------------------------------------------------------
// Array
//-----------------------------------------------------------------------------
Array::MapToElemType Array::_mapToElemType;

Array::~Array()
{
}

void Array::Bootup()
{
	static const struct {
		const char *name;
		ElemType elemType;
	} tbl[] = {
		{ "boolean",	ETYPE_Boolean	},
		{ "int8",		ETYPE_Int8		},
		{ "uint8",		ETYPE_UInt8		},
		{ "int16",		ETYPE_Int16		},
		{ "uint16",		ETYPE_UInt16	},
		{ "int32",		ETYPE_Int32		},
		{ "uint32",		ETYPE_UInt32	},
		{ "int64",		ETYPE_Int64		},
		{ "uint64",		ETYPE_UInt64	},
		{ "half",		ETYPE_Half		},
		{ "float",		ETYPE_Float		},
		{ "double",		ETYPE_Double	},
		{ "complex",	ETYPE_Complex	},
		{ "value",		ETYPE_reserved1	},
	};
	for (size_t i = 0; i < ArraySizeOf(tbl); i++) {
		_mapToElemType[Symbol::Add(tbl[i].name)] = tbl[i].elemType;
	}
}

size_t Array::GetElemBytes(ElemType elemType)
{
	const static size_t elemBytesTbl[ETYPE_Max] = {
		0,
		ArrayT<Boolean>::ElemBytes,
		ArrayT<Int8>::ElemBytes,
		ArrayT<UInt8>::ElemBytes,
		ArrayT<Int16>::ElemBytes,
		ArrayT<UInt16>::ElemBytes,
		ArrayT<Int32>::ElemBytes,
		ArrayT<UInt32>::ElemBytes,
		ArrayT<Int64>::ElemBytes,
		ArrayT<UInt64>::ElemBytes,
		ArrayT<Half>::ElemBytes,
		ArrayT<Float>::ElemBytes,
		ArrayT<Double>::ElemBytes,
		ArrayT<Complex>::ElemBytes,
		//ArrayT<Value>::ElemBytes,
	};
	return elemBytesTbl[elemType];
}

const char *Array::GetElemTypeName(ElemType elemType)
{
	const static char *elemTypeNameTbl[ETYPE_Max] = {
		"",
		ArrayT<Boolean>::ElemTypeName,
		ArrayT<Int8>::ElemTypeName,
		ArrayT<UInt8>::ElemTypeName,
		ArrayT<Int16>::ElemTypeName,
		ArrayT<UInt16>::ElemTypeName,
		ArrayT<Int32>::ElemTypeName,
		ArrayT<UInt32>::ElemTypeName,
		ArrayT<Int64>::ElemTypeName,
		ArrayT<UInt64>::ElemTypeName,
		ArrayT<Half>::ElemTypeName,
		ArrayT<Float>::ElemTypeName,
		ArrayT<Double>::ElemTypeName,
		ArrayT<Complex>::ElemTypeName,
		//ArrayT<Value>::ElemTypeName,
	};
	return elemTypeNameTbl[elemType];
}

void Array::FlipAxisMajor()
{
	if (_dims.HasRowCol()) {
		_colMajorFlag = !_colMajorFlag;
		Dimension dimRow = _dims.GetRow(); // don't use reference here!
		Dimension dimCol = _dims.GetCol();
		_dims.SetRow(Dimension(dimCol.GetSize(), dimCol.GetSize() * dimRow.GetSize(), dimCol.GetStrides()));
		_dims.SetCol(Dimension(dimRow.GetSize(), dimRow.GetSize(), dimRow.GetStrides()));
	}
}

void Array::SetDimension(size_t size)
{
	_dims.reserve(1);
	_dims.push_back(Dimension(size));
	UpdateMetrics();
}

void Array::SetDimensions(size_t sizeRow, size_t sizeCol)
{
	_dims.reserve(2);
	_dims.push_back(Dimension(sizeRow));
	_dims.push_back(Dimension(sizeCol));
	UpdateMetrics();
}

void Array::SetDimensions(size_t sizePlane, size_t sizeRow, size_t sizeCol)
{
	_dims.reserve(3);
	_dims.push_back(Dimension(sizePlane));
	_dims.push_back(Dimension(sizeRow));
	_dims.push_back(Dimension(sizeCol));
	UpdateMetrics();
}

void Array::SetDimensions(const Dimensions &dims)
{
	_dims = dims;
	UpdateMetrics();
}

void Array::SetDimensions(Dimensions::const_iterator pDim, Dimensions::const_iterator pDimEnd)
{
	_dims.reserve(std::distance(pDim, pDimEnd));
	std::copy(pDim, pDimEnd, std::back_inserter(_dims));
	UpdateMetrics();
}

void Array::SetDimensions(size_t size,
						  Dimensions::const_iterator pDim, Dimensions::const_iterator pDimEnd)
{
	_dims.reserve(std::distance(pDim, pDimEnd) + 1);
	_dims.push_back(Dimension(size));
	_dims.insert(_dims.end(), pDim, pDimEnd);
	UpdateMetrics();
}

void Array::SetDimensions(Dimensions::const_iterator pDim, Dimensions::const_iterator pDimEnd,
						  size_t size)
{
	_dims.reserve(std::distance(pDim, pDimEnd) + 1);
	_dims.insert(_dims.end(), pDim, pDimEnd);
	_dims.push_back(Dimension(size));
	UpdateMetrics();
}

void Array::SetDimensions(Dimensions::const_iterator pDim, Dimensions::const_iterator pDimEnd,
						  size_t sizeRow, size_t sizeCol)
{
	_dims.reserve(std::distance(pDim, pDimEnd) + 2);
	_dims.insert(_dims.end(), pDim, pDimEnd);
	_dims.push_back(Dimension(sizeRow));
	_dims.push_back(Dimension(sizeCol));
	UpdateMetrics();
}

void Array::SetDimensions(Dimensions::const_iterator pDim, Dimensions::const_iterator pDimEnd,
						  size_t sizePlane, size_t sizeRow, size_t sizeCol)
{
	_dims.reserve(std::distance(pDim, pDimEnd) + 3);
	_dims.insert(_dims.end(), pDim, pDimEnd);
	_dims.push_back(Dimension(sizePlane));
	_dims.push_back(Dimension(sizeRow));
	_dims.push_back(Dimension(sizeCol));
	UpdateMetrics();
}

void Array::SetDimensions(Dimensions::const_iterator pDim1, Dimensions::const_iterator pDim1End,
						  Dimensions::const_iterator pDim2, Dimensions::const_iterator pDim2End)
{
	_dims.reserve(std::distance(pDim1, pDim1End) + std::distance(pDim2, pDim2End));
	_dims.insert(_dims.end(), pDim1, pDim1End);
	_dims.insert(_dims.end(), pDim2, pDim2End);
	UpdateMetrics();
}

void Array::SetDimensions(const ValueList &valList)
{
	_dims.reserve(valList.size());
	foreach_const (ValueList, pValue, valList) {
		_dims.push_back(pValue->GetSizeT());
	}
	UpdateMetrics();
}

void Array::UpdateMetrics()
{
	size_t strides = 1;
	foreach_reverse (Dimensions, pDim, _dims) {
		pDim->SetStrides(strides);
		strides *= pDim->GetSize();
		pDim->SetSizeProd(strides);
	}
	_elemNum = strides;	// set to one when _dims is empty
	if (IsColMajor() && _dims.size() >= 2) {
		_dims.GetCol().SetStrides(_dims.GetRow().GetSize());
		_dims.GetRow().SetStrides(1);
	}
}

void Array::FillZero()
{
	::memset(GetPointerRaw(), 0x00, GetElemBytes() * GetElemNum());
}

template<typename T_Elem>
void FillTmpl(Array *pArray, Double num) {
	dynamic_cast<ArrayT<T_Elem> *>(pArray)->Fill(static_cast<T_Elem>(num));
}

void Array::Fill(Double num)
{
	typedef void (*FuncT)(Array *pArray, Double num);
	static const FuncT funcs[ETYPE_Max] = {
		nullptr,
		&FillTmpl<Boolean>,
		&FillTmpl<Int8>,
		&FillTmpl<UInt8>,
		&FillTmpl<Int16>,
		&FillTmpl<UInt16>,
		&FillTmpl<Int32>,
		&FillTmpl<UInt32>,
		&FillTmpl<Int64>,
		&FillTmpl<UInt64>,
		&FillTmpl<Half>,
		&FillTmpl<Float>,
		&FillTmpl<Double>,
		&FillTmpl<Complex>,
		//&FillTmpl<Value>,
	};
	FuncT func = funcs[GetElemType()];
	(*func)(this, num);
}

bool Array::Head(Signal &sig, AutoPtr<Array> &pArrayRtn, size_t n) const
{
	const Dimension &dimFirst = GetDimensions().front();
	if (n > dimFirst.GetSize()) {
		sig.SetError(ERR_OutOfRangeError, "specified size is out of range");
		return false;
	}
	size_t offsetBase = GetOffsetBase();
	pArrayRtn.reset(Create(GetElemType(), GetColMajorFlag()));
	pArrayRtn->SetDimensions(n, GetDimensions().begin() + 1, GetDimensions().end());
	pArrayRtn->SetMemory(GetMemory().Reference(), offsetBase);
	return true;
}

bool Array::Tail(Signal &sig, AutoPtr<Array> &pArrayRtn, size_t n) const
{
	const Dimension &dimFirst = GetDimensions().front();
	if (n > dimFirst.GetSize()) {
		sig.SetError(ERR_OutOfRangeError, "specified size is out of range");
		return false;
	}
	size_t offsetBase = GetOffsetBase() + dimFirst.GetStrides() * (dimFirst.GetSize() - n);
	pArrayRtn.reset(Create(GetElemType(), GetColMajorFlag()));
	pArrayRtn->SetDimensions(n, GetDimensions().begin() + 1, GetDimensions().end());
	pArrayRtn->SetMemory(GetMemory().Reference(), offsetBase);
	return true;
}

bool Array::Offset(Signal &sig, AutoPtr<Array> &pArrayRtn, size_t n) const
{
	const Dimension &dimFirst = GetDimensions().front();
	if (n > dimFirst.GetSize()) {
		sig.SetError(ERR_OutOfRangeError, "offset is out of range");
		return false;
	}
	size_t nElems = dimFirst.GetSize() - n;
	size_t offsetBase = GetOffsetBase() + dimFirst.GetStrides() * n;
	pArrayRtn.reset(Create(GetElemType(), GetColMajorFlag()));
	pArrayRtn->SetDimensions(nElems, GetDimensions().begin() + 1, GetDimensions().end());
	pArrayRtn->SetMemory(GetMemory().Reference(), offsetBase);
	return true;
}

template<typename T_Elem>
void FlattenTmpl(Array *pArrayRtn, const Array *pArraySrc)
{
	const Array::Dimensions &dims = pArraySrc->GetDimensions();
	const T_Elem *pElem = dynamic_cast<const ArrayT<T_Elem> *>(pArraySrc)->GetPointer();
	T_Elem *pElemRtn = dynamic_cast<ArrayT<T_Elem> *>(pArrayRtn)->GetPointer();
	const Array::Dimension &dimRow = dims.GetRow();
	const Array::Dimension &dimCol = dims.GetCol();
	size_t nMats = pArraySrc->GetElemNum() / dimRow.GetSizeProd();
	const T_Elem *pElemMat = pElem;
	for (size_t iMat = 0; iMat < nMats; iMat++, pElemMat += dimRow.GetSizeProd()) {
		const T_Elem *pElemRow = pElemMat;
		for (size_t iRow = 0; iRow < dimRow.GetSize(); iRow++,
				 pElemRow += dimRow.GetStrides()) {
			const T_Elem *pElemCol = pElemRow;
			for (size_t iCol = 0; iCol < dimCol.GetSize(); iCol++,
					 pElemCol += dimCol.GetStrides()) {
				*pElemRtn++ = *pElemCol;
			}
		}
	}
}

void Array::Flatten(AutoPtr<Array> &pArrayRtn) const
{
	typedef void (*FuncT)(Array *pArrayRtn, const Array *pArraySrc);
	static const FuncT funcs[ETYPE_Max] = {
		nullptr,
		&FlattenTmpl<Boolean>,
		&FlattenTmpl<Int8>,
		&FlattenTmpl<UInt8>,
		&FlattenTmpl<Int16>,
		&FlattenTmpl<UInt16>,
		&FlattenTmpl<Int32>,
		&FlattenTmpl<UInt32>,
		&FlattenTmpl<Int64>,
		&FlattenTmpl<UInt64>,
		&FlattenTmpl<Half>,
		&FlattenTmpl<Float>,
		&FlattenTmpl<Double>,
		&FlattenTmpl<Complex>,
		//&FlattenTmpl<Value>,
	};
	bool colMajorFlag = false;
	const Array::Dimensions &dims = GetDimensions();
	pArrayRtn.reset(Create(GetElemType(), colMajorFlag));
	pArrayRtn->SetDimension(GetElemNum());
	if (IsRowMajor() || dims.size() < 2) {
		pArrayRtn->SetMemory(GetMemory().Reference(), GetOffsetBase());
	} else {
		FuncT func = funcs[GetElemType()];
		pArrayRtn->AllocMemory();
		(*func)(pArrayRtn.get(), this);
	}
}

bool Array::Reshape(Signal &sig, AutoPtr<Array> &pArrayRtn, const ValueList &valList) const
{
	bool unfixedFlag = false;
	size_t nElems = 1;
	foreach_const (ValueList, pValue, valList) {
		if (pValue->Is_number() && pValue->GetNumber() >= 0) {
			nElems *= pValue->GetSizeT();
		} else if (unfixedFlag) {
			sig.SetError(ERR_ValueError, "only one dimension can be specified as an unfixed");
			return false;
		} else {
			unfixedFlag = true;
		}
	}
	if ((unfixedFlag && (GetElemNum() % nElems != 0)) ||
		(!unfixedFlag && (nElems != GetElemNum()))) {
		sig.SetError(ERR_ValueError, "incorrect shape specified");
		return false;
	}
	pArrayRtn.reset(Create(GetElemType(), GetColMajorFlag()));
	Dimensions &dims = pArrayRtn->GetDimensions();
	dims.reserve(valList.size());
	foreach_const (ValueList, pValue, valList) {
		if (pValue->Is_number() && pValue->GetNumber() >= 0) {
			dims.push_back(Dimension(pValue->GetSizeT()));
		} else {
			dims.push_back(Dimension(GetElemNum() / nElems));
		}
	}	
	pArrayRtn->UpdateMetrics();
	pArrayRtn->SetMemory(GetMemory().Reference(), GetOffsetBase());
	return true;
}

template<typename T_Elem>
void TransposeSubTmpl(void **ppElemDstRaw, const void *pElemSrcRaw, const Array::Dimensions &dimsSrc,
					  SizeTList::const_iterator pAxis, SizeTList::const_iterator pAxisEnd)
{
	T_Elem *&pElemDst = *reinterpret_cast<T_Elem **>(ppElemDstRaw);
	const T_Elem *pElemSrc = reinterpret_cast<const T_Elem *>(pElemSrcRaw);
	const Array::Dimension &dimSrc = dimsSrc[*pAxis];
	if (pAxis + 1 == pAxisEnd) {
		for (size_t i = 0; i < dimSrc.GetSize(); i++, pElemSrc += dimSrc.GetStrides(), pElemDst++) {
			*pElemDst = *pElemSrc;
		}
	} else {
		for (size_t i = 0; i < dimSrc.GetSize(); i++, pElemSrc += dimSrc.GetStrides()) {
			TransposeSubTmpl<T_Elem>(reinterpret_cast<void **>(&pElemDst),
									 reinterpret_cast<const void *>(pElemSrc), dimsSrc, pAxis + 1, pAxisEnd);
		}
	}
}

bool Array::Transpose(Signal &sig, AutoPtr<Array> &pArrayRtn, const ValueList &valList) const
{
	if (GetDimensions().size() != valList.size()) {
		sig.SetError(ERR_ValueError, "mismatched number of axes to transpose");
		return false;
	}
	SizeTList axes;
	foreach_const (ValueList, pValue, valList) {
		size_t axis = pValue->GetSizeT();
		if (std::find(axes.begin(), axes.end(), axis) != axes.end()) {
			sig.SetError(ERR_ValueError, "duplicated axis is specified");
			return false;
		}
		if (axis >= GetDimensions().size()) {
			sig.SetError(ERR_ValueError, "specified axis is out of range");
			return false;
		}
		axes.push_back(axis);
	}
	return Transpose(pArrayRtn, axes);
}

bool Array::Transpose(AutoPtr<Array> &pArrayRtn, const SizeTList &axes) const
{
	typedef void (*FuncT)(void **ppElemDstRaw, const void *pElemSrcRaw, const Array::Dimensions &dimsSrc,
						  SizeTList::const_iterator pAxis, SizeTList::const_iterator pAxisEnd);
	static const FuncT funcs[ETYPE_Max] = {
		nullptr,
		&TransposeSubTmpl<Boolean>,
		&TransposeSubTmpl<Int8>,
		&TransposeSubTmpl<UInt8>,
		&TransposeSubTmpl<Int16>,
		&TransposeSubTmpl<UInt16>,
		&TransposeSubTmpl<Int32>,
		&TransposeSubTmpl<UInt32>,
		&TransposeSubTmpl<Int64>,
		&TransposeSubTmpl<UInt64>,
		&TransposeSubTmpl<Half>,
		&TransposeSubTmpl<Float>,
		&TransposeSubTmpl<Double>,
		&TransposeSubTmpl<Complex>,
		//&TransposeSubTmpl<Value>,
	};
	FuncT func = funcs[GetElemType()];
	if (axes.size() < 2) {
		pArrayRtn.reset(Clone());
		return true;
	}
	Dimensions::const_reverse_iterator pDim = GetDimensions().rbegin();
	bool memorySharableFlag = false;
	if (pDim->GetSize() == 1 || (pDim + 1)->GetSize() == 1) {
		memorySharableFlag = true;
		SizeTList::const_iterator pAxis = axes.begin();
		SizeTList::const_iterator pAxisEnd = axes.begin() + axes.size() - 2;
		for (size_t axisInc = 0; pAxis != pAxisEnd; pAxis++, axisInc++) {
			if (*pAxis != axisInc) {
				memorySharableFlag = false;
				break;
			}
		}
	}
	if (pArrayRtn.IsNull()) {
		bool colMajorFlag = false;
		pArrayRtn.reset(Create(GetElemType(), colMajorFlag));
		Dimensions &dimsDst = pArrayRtn->GetDimensions();
		dimsDst.reserve(GetDimensions().size());
		foreach_const (SizeTList, pAxis, axes) {
			const Dimension &dimSrc = GetDimensions()[*pAxis];
			dimsDst.push_back(Dimension(dimSrc.GetSize()));
		}
		pArrayRtn->UpdateMetrics();
		if (memorySharableFlag) {
			pArrayRtn->SetMemory(GetMemory().Reference(), GetOffsetBase());
		} else {
			pArrayRtn->AllocMemory();
			void *pElemDstRaw = pArrayRtn->GetPointerRaw();
			(*func)(&pElemDstRaw, GetPointerRaw(), GetDimensions(), axes.begin(), axes.end());
		}
	} else {
		if (!memorySharableFlag) {
			void *pElemDstRaw = pArrayRtn->GetPointerRaw();
			(*func)(&pElemDstRaw, GetPointerRaw(), GetDimensions(), axes.begin(), axes.end());
		}
	}
	return true;
}

void Array::Transpose2d(AutoPtr<Array> &pArrayRtn) const
{
	pArrayRtn.reset(Clone());
	pArrayRtn->FlipAxisMajor();
}

template<typename T_Elem, bool (*op)(T_Elem, T_Elem)>
Array *FindMinMax(const ArrayT<T_Elem> *pArrayT, size_t axis)
{
	bool colMajorFlag = false;
	const Array::Dimensions &dims = pArrayT->GetDimensions();
	Array::Dimensions::const_iterator pDimAxis = dims.begin() + axis;
	AutoPtr<ArrayT<T_Elem> > pArrayTValue(ArrayT<T_Elem>::Create(colMajorFlag));
	pArrayTValue->SetDimensions(dims.begin(), pDimAxis, pDimAxis + 1, dims.end());
	pArrayTValue->AllocMemory();
	pArrayTValue->FillZero();
	const T_Elem *pElem = pArrayT->GetPointer();
	T_Elem *pElemValue = pArrayTValue->GetPointer();
	size_t sizeSub = pDimAxis->GetStrides() * pDimAxis->GetSize();
	if (pArrayT->IsRowMajor() || axis + 2 >= dims.size()) {
		for (size_t offset = 0; offset < pArrayT->GetElemNum(); offset += sizeSub) {
			do {
				// first element
				T_Elem *pElemValueEach = pElemValue;
				for (size_t j = 0; j < pDimAxis->GetStrides(); j++, pElem++) {
					*pElemValueEach = *pElem;
					pElemValueEach++;
				}
			} while (0);
			for (size_t i = 1; i < pDimAxis->GetSize(); i++) {
				T_Elem *pElemValueEach = pElemValue;
				for (size_t j = 0; j < pDimAxis->GetStrides(); j++, pElem++) {
					if ((*op)(*pElemValueEach, *pElem)) *pElemValueEach = *pElem;
					pElemValueEach++;
				}
			}
			pElemValue += pDimAxis->GetStrides();
		}
	} else { // pArrayT->IsColMajor() && axis + 2 < dim.size()
		const Array::Dimension &dimRow = dims.GetRow();
		const Array::Dimension &dimCol = dims.GetCol();
		size_t nMats = pDimAxis->GetStrides() / dimRow.GetSizeProd();
		for (size_t offset = 0; offset < pArrayT->GetElemNum(); offset += sizeSub) {
			do {
				// first element
				T_Elem *pElemValueEach = pElemValue;
				for (size_t iMat = 0; iMat < nMats; iMat++, pElem += dimRow.GetSizeProd()) {
					const T_Elem *pElemRow = pElem;
					for (size_t iRow = 0; iRow < dimRow.GetSize(); iRow++, pElemRow += dimRow.GetStrides()) {
						const T_Elem *pElemCol = pElemRow;
						for (size_t iCol = 0; iCol < dimCol.GetSize(); iCol++, pElemCol += dimCol.GetStrides()) {
							*pElemValueEach = *pElemCol;
							pElemValueEach++;
						}
					}
				}
			} while (0);
			for (size_t i = 1; i < pDimAxis->GetSize(); i++) {
				T_Elem *pElemValueEach = pElemValue;
				for (size_t iMat = 0; iMat < nMats; iMat++, pElem += dimRow.GetSizeProd()) {
					const T_Elem *pElemRow = pElem;
					for (size_t iRow = 0; iRow < dimRow.GetSize(); iRow++, pElemRow += dimRow.GetStrides()) {
						const T_Elem *pElemCol = pElemRow;
						for (size_t iCol = 0; iCol < dimCol.GetSize(); iCol++, pElemCol += dimCol.GetStrides()) {
							if ((*op)(*pElemValueEach, *pElemCol)) *pElemValueEach = *pElemCol;
							pElemValueEach++;
						}
					}
				}
			}
			pElemValue += pDimAxis->GetStrides();
		}
	}
	return pArrayTValue.release();
}

template<typename T_Elem, bool (*op)(T_Elem, T_Elem)>
T_Elem FindMinMaxFlat(const ArrayT<T_Elem> *pArrayT)
{
	const T_Elem *pElem = pArrayT->GetPointer();
	T_Elem rtn = *pElem++;
	for (size_t i = 1; i < pArrayT->GetElemNum(); i++, pElem++) {
		if ((*op)(rtn, *pElem)) rtn = *pElem;
	}
	return rtn;
}

template<typename T_Elem>
bool FindMaxTmpl(Signal &sig, AutoPtr<Array> &pArrayRtn, const Array *pArraySelf, ssize_t axis)
{
	const ArrayT<T_Elem> *pArrayT = dynamic_cast<const ArrayT<T_Elem> *>(pArraySelf);
	const Array::Dimensions &dims = pArrayT->GetDimensions();
	if (pArrayT->GetElemNum() == 0) {
		// nothing to do
	} else if (axis < 0 || (axis == 0 && dims.size() == 1)) {
		pArrayRtn.reset(ArrayT<T_Elem>::CreateScalar(FindMinMaxFlat<T_Elem, CompareLt>(pArrayT)));
	} else if (axis >= dims.size()) {
		sig.SetError(ERR_OutOfRangeError, "specified axis is out of range");
		return false;
	} else {
		pArrayRtn.reset(FindMinMax<T_Elem, CompareLt>(pArrayT, axis));
	}
	return true;
}

template<typename T_Elem>
bool FindMinTmpl(Signal &sig, AutoPtr<Array> &pArrayRtn, const Array *pArraySelf, ssize_t axis)
{
	const ArrayT<T_Elem> *pArrayT = dynamic_cast<const ArrayT<T_Elem> *>(pArraySelf);
	const Array::Dimensions &dims = pArrayT->GetDimensions();
	if (pArrayT->GetElemNum() == 0) {
		// nothing to do
	} else if (axis < 0 || (axis == 0 && dims.size() == 1)) {
		pArrayRtn.reset(ArrayT<T_Elem>::CreateScalar(FindMinMaxFlat<T_Elem, CompareGt>(pArrayT)));
	} else if (axis >= dims.size()) {
		sig.SetError(ERR_OutOfRangeError, "specified axis is out of range");
		return false;
	} else {
		pArrayRtn.reset(FindMinMax<T_Elem, CompareGt>(pArrayT, axis));
	}
	return true;
}

bool Array::FindMax(Signal &sig, AutoPtr<Array> &pArrayRtn, ssize_t axis) const
{
	typedef bool (*FuncT)(Signal &sig, AutoPtr<Array> &pArrayRtn, const Array *pArraySelf, ssize_t axis);
	static const FuncT funcs[ETYPE_Max] = {
		nullptr,
		&FindMaxTmpl<Boolean>,
		&FindMaxTmpl<Int8>,
		&FindMaxTmpl<UInt8>,
		&FindMaxTmpl<Int16>,
		&FindMaxTmpl<UInt16>,
		&FindMaxTmpl<Int32>,
		&FindMaxTmpl<UInt32>,
		&FindMaxTmpl<Int64>,
		&FindMaxTmpl<UInt64>,
		&FindMaxTmpl<Half>,
		&FindMaxTmpl<Float>,
		&FindMaxTmpl<Double>,
		&FindMaxTmpl<Complex>,
		//&FindMaxTmpl<Value>,
	};
	FuncT func = funcs[GetElemType()];
	return (*func)(sig, pArrayRtn, this, axis);
}

bool Array::FindMin(Signal &sig, AutoPtr<Array> &pArrayRtn, ssize_t axis) const
{
	typedef bool (*FuncT)(Signal &sig, AutoPtr<Array> &pArrayRtn, const Array *pArraySelf, ssize_t axis);
	static const FuncT funcs[ETYPE_Max] = {
		nullptr,
		&FindMinTmpl<Boolean>,
		&FindMinTmpl<Int8>,
		&FindMinTmpl<UInt8>,
		&FindMinTmpl<Int16>,
		&FindMinTmpl<UInt16>,
		&FindMinTmpl<Int32>,
		&FindMinTmpl<UInt32>,
		&FindMinTmpl<Int64>,
		&FindMinTmpl<UInt64>,
		&FindMinTmpl<Half>,
		&FindMinTmpl<Float>,
		&FindMinTmpl<Double>,
		&FindMinTmpl<Complex>,
		//&FindMinTmpl<Value>,
	};
	FuncT func = funcs[GetElemType()];
	return (*func)(sig, pArrayRtn, this, axis);
}

template<typename T_Elem, bool (*op)(T_Elem, T_Elem)>
Array *FindMinMaxIndex(const ArrayT<T_Elem> *pArrayT, size_t axis)
{
	bool colMajorFlag = false;
	const Array::Dimensions &dims = pArrayT->GetDimensions();
	Array::Dimensions::const_iterator pDimAxis = dims.begin() + axis;
	AutoPtr<ArrayT<UInt32> > pArrayTIndex(ArrayT<UInt32>::Create(colMajorFlag));
	pArrayTIndex->SetDimensions(dims.begin(), pDimAxis, pDimAxis + 1, dims.end());
	pArrayTIndex->AllocMemory();
	AutoPtr<Memory> pMemoryValue(new MemoryHeap(pArrayTIndex->GetElemNum() * sizeof(T_Elem)));
	pArrayTIndex->FillZero();
	const T_Elem *pElem = pArrayT->GetPointer();
	UInt32 *pElemIndex = pArrayTIndex->GetPointer();
	T_Elem *pElemValue = reinterpret_cast<T_Elem *>(pMemoryValue->GetPointer());
	size_t sizeSub = pDimAxis->GetStrides() * pDimAxis->GetSize();
	if (pArrayT->IsRowMajor() || axis + 2 >= dims.size()) {
		for (size_t offset = 0; offset < pArrayT->GetElemNum(); offset += sizeSub) {
			do {
				UInt32 *pElemIndexEach = pElemIndex;
				T_Elem *pElemValueEach = pElemValue;
				for (size_t j = 0; j < pDimAxis->GetStrides(); j++, pElem++) {
					*pElemIndexEach = 0;
					*pElemValueEach = *pElem;
					pElemIndexEach++;
					pElemValueEach++;
				}
			} while (0);
			for (size_t i = 1; i < pDimAxis->GetSize(); i++) {
				UInt32 *pElemIndexEach = pElemIndex;
				T_Elem *pElemValueEach = pElemValue;
				for (size_t j = 0; j < pDimAxis->GetStrides(); j++, pElem++) {
					if ((*op)(*pElemValueEach, *pElem)) {
						*pElemIndexEach = static_cast<UInt32>(i);
						*pElemValueEach = *pElem;
					}
					pElemIndexEach++;
					pElemValueEach++;
				}
			}
			pElemIndex += pDimAxis->GetStrides();
			pElemValue += pDimAxis->GetStrides();
		}
	} else { // pArrayT->IsColMajor() && axis + 2 < dim.size()
		const Array::Dimension &dimRow = dims.GetRow();
		const Array::Dimension &dimCol = dims.GetCol();
		size_t nMats = pDimAxis->GetStrides() / dimRow.GetSizeProd();
		for (size_t offset = 0; offset < pArrayT->GetElemNum(); offset += sizeSub) {
			do {
				// first element
				UInt32 *pElemIndexEach = pElemIndex;
				T_Elem *pElemValueEach = pElemValue;
				for (size_t iMat = 0; iMat < nMats; iMat++, pElem += dimRow.GetSizeProd()) {
					const T_Elem *pElemRow = pElem;
					for (size_t iRow = 0; iRow < dimRow.GetSize(); iRow++, pElemRow += dimRow.GetStrides()) {
						const T_Elem *pElemCol = pElemRow;
						for (size_t iCol = 0; iCol < dimCol.GetSize(); iCol++, pElemCol += dimCol.GetStrides()) {
							*pElemIndexEach = 0;
							*pElemValueEach = *pElemCol;
							pElemIndexEach++;
							pElemValueEach++;
						}
					}
				}
			} while (0);
			for (size_t i = 1; i < pDimAxis->GetSize(); i++) {
				UInt32 *pElemIndexEach = pElemIndex;
				T_Elem *pElemValueEach = pElemValue;
				for (size_t iMat = 0; iMat < nMats; iMat++, pElem += dimRow.GetSizeProd()) {
					const T_Elem *pElemRow = pElem;
					for (size_t iRow = 0; iRow < dimRow.GetSize(); iRow++, pElemRow += dimRow.GetStrides()) {
						const T_Elem *pElemCol = pElemRow;
						for (size_t iCol = 0; iCol < dimCol.GetSize(); iCol++, pElemCol += dimCol.GetStrides()) {
							if ((*op)(*pElemValueEach, *pElemCol)) {
								*pElemIndexEach = static_cast<UInt32>(i);
								*pElemValueEach = *pElemCol;
							}
							pElemIndexEach++;
							pElemValueEach++;
						}
					}
				}
			}
			pElemIndex += pDimAxis->GetStrides();
			pElemValue += pDimAxis->GetStrides();
		}
	}
	return pArrayTIndex.release();
}

template<typename T_Elem, bool (*op)(T_Elem, T_Elem)>
UInt32 FindMinMaxIndexFlat(const ArrayT<T_Elem> *pArrayT)
{
	const T_Elem *pElem = pArrayT->GetPointer();
	size_t index = 0;
	T_Elem value = *pElem++;
	for (size_t i = 1; i < pArrayT->GetElemNum(); i++, pElem++) {
		if ((*op)(value, *pElem)) {
			index = i;
			value = *pElem;
		}
	}
	return static_cast<UInt32>(index);
}

template<typename T_Elem>
bool FindMaxIndexTmpl(Signal &sig, AutoPtr<Array> &pArrayRtn, const Array *pArraySelf, ssize_t axis, bool lastFlag)
{
	const ArrayT<T_Elem> *pArrayT = dynamic_cast<const ArrayT<T_Elem> *>(pArraySelf);
	const Array::Dimensions &dims = pArrayT->GetDimensions();
	if (pArrayT->GetElemNum() == 0) {
		// nothing to do
	} else if (axis < 0 || (axis == 0 && dims.size() == 1)) {
		pArrayRtn.reset(ArrayT<UInt32>::CreateScalar(
							lastFlag? 
							FindMinMaxIndexFlat<T_Elem, CompareLe>(pArrayT) :
							FindMinMaxIndexFlat<T_Elem, CompareLt>(pArrayT)));
	} else if (axis >= dims.size()) {
		sig.SetError(ERR_OutOfRangeError, "specified axis is out of range");
		return false;
	} else {
		pArrayRtn.reset(lastFlag?
						FindMinMaxIndex<T_Elem, CompareLe>(pArrayT, axis) :
						FindMinMaxIndex<T_Elem, CompareLt>(pArrayT, axis));
	}
	return true;
}

template<typename T_Elem>
bool FindMinIndexTmpl(Signal &sig, AutoPtr<Array> &pArrayRtn, const Array *pArraySelf, ssize_t axis, bool lastFlag)
{
	const ArrayT<T_Elem> *pArrayT = dynamic_cast<const ArrayT<T_Elem> *>(pArraySelf);
	const Array::Dimensions &dims = pArrayT->GetDimensions();
	if (pArrayT->GetElemNum() == 0) {
		// nothing to do
	} else if (axis < 0 || (axis == 0 && dims.size() == 1)) {
		pArrayRtn.reset(ArrayT<UInt32>::CreateScalar(
							lastFlag? 
							FindMinMaxIndexFlat<T_Elem, CompareGe>(pArrayT) :
							FindMinMaxIndexFlat<T_Elem, CompareGt>(pArrayT)));
	} else if (axis >= dims.size()) {
		sig.SetError(ERR_OutOfRangeError, "specified axis is out of range");
		return false;
	} else {
		pArrayRtn.reset(lastFlag?
						FindMinMaxIndex<T_Elem, CompareGe>(pArrayT, axis) :
						FindMinMaxIndex<T_Elem, CompareGt>(pArrayT, axis));
	}
	return true;
}

bool Array::FindMaxIndex(Signal &sig, AutoPtr<Array> &pArrayRtn, ssize_t axis, bool lastFlag) const
{
	typedef bool (*FuncT)(Signal &sig, AutoPtr<Array> &pArrayRtn, const Array *pArraySelf, ssize_t axis, bool lastFlag);
	static const FuncT funcs[ETYPE_Max] = {
		nullptr,
		&FindMaxIndexTmpl<Boolean>,
		&FindMaxIndexTmpl<Int8>,
		&FindMaxIndexTmpl<UInt8>,
		&FindMaxIndexTmpl<Int16>,
		&FindMaxIndexTmpl<UInt16>,
		&FindMaxIndexTmpl<Int32>,
		&FindMaxIndexTmpl<UInt32>,
		&FindMaxIndexTmpl<Int64>,
		&FindMaxIndexTmpl<UInt64>,
		&FindMaxIndexTmpl<Half>,
		&FindMaxIndexTmpl<Float>,
		&FindMaxIndexTmpl<Double>,
		&FindMaxIndexTmpl<Complex>,
		//&FindMaxIndexTmpl<Value>,
	};
	FuncT func = funcs[GetElemType()];
	return (*func)(sig, pArrayRtn, this, axis, lastFlag);
}

bool Array::FindMinIndex(Signal &sig, AutoPtr<Array> &pArrayRtn, ssize_t axis, bool lastFlag) const
{
	typedef bool (*FuncT)(Signal &sig, AutoPtr<Array> &pArrayRtn, const Array *pArraySelf, ssize_t axis, bool lastFlag);
	static const FuncT funcs[ETYPE_Max] = {
		nullptr,
		&FindMinIndexTmpl<Boolean>,
		&FindMinIndexTmpl<Int8>,
		&FindMinIndexTmpl<UInt8>,
		&FindMinIndexTmpl<Int16>,
		&FindMinIndexTmpl<UInt16>,
		&FindMinIndexTmpl<Int32>,
		&FindMinIndexTmpl<UInt32>,
		&FindMinIndexTmpl<Int64>,
		&FindMinIndexTmpl<UInt64>,
		&FindMinIndexTmpl<Half>,
		&FindMinIndexTmpl<Float>,
		&FindMinIndexTmpl<Double>,
		&FindMinIndexTmpl<Complex>,
		//&FindMinIndexTmpl<Value>,
	};
	FuncT func = funcs[GetElemType()];
	return (*func)(sig, pArrayRtn, this, axis, lastFlag);
}

template<typename T_ElemRtn, typename T_Elem>
ArrayT<T_ElemRtn> *CalcSum(const ArrayT<T_Elem> *pArrayT, size_t axis, bool meanFlag)
{
	bool colMajorFlag = false;
	const Array::Dimensions &dims = pArrayT->GetDimensions();
	Array::Dimensions::const_iterator pDimAxis = dims.begin() + axis;
	AutoPtr<ArrayT<T_ElemRtn> > pArrayTRtn(ArrayT<T_ElemRtn>::Create(colMajorFlag));
	pArrayTRtn->SetDimensions(dims.begin(), pDimAxis, pDimAxis + 1, dims.end());
	pArrayTRtn->AllocMemory();
	pArrayTRtn->FillZero();
	Double numDenom = static_cast<Double>(pDimAxis->GetSize());
	const T_Elem *pElemTop = pArrayT->GetPointer();
	T_ElemRtn *pElemRtn = pArrayTRtn->GetPointer();
	size_t sizeSub = pDimAxis->GetStrides() * pDimAxis->GetSize();
	if (pArrayT->IsRowMajor() || axis + 2 >= dims.size()) {
		for (size_t offset = 0; offset < pArrayT->GetElemNum(); offset += sizeSub) {
			const T_Elem *pElemBlock = pElemTop + offset;
			for (size_t j = 0; j < pDimAxis->GetStrides(); j++, pElemBlock++) {
				T_ElemRtn numAccum = 0;
				const T_Elem *pElemEach = pElemBlock;
				for (size_t i = 0; i < pDimAxis->GetSize(); i++, pElemEach += pDimAxis->GetStrides()) {
					numAccum += *pElemEach;
				}
				*pElemRtn++ = meanFlag? numAccum / numDenom : numAccum;
			}
		}
	} else { // pArrayT->IsColMajor() && axis + 2 < dim.size()
		const Array::Dimension &dimRow = dims.GetRow();
		const Array::Dimension &dimCol = dims.GetCol();
		size_t nMats = pDimAxis->GetStrides() / dimRow.GetSizeProd();
		for (size_t offset = 0; offset < pArrayT->GetElemNum(); offset += sizeSub) {
			const T_Elem *pElemMat = pElemTop + offset;
			for (size_t iMat = 0; iMat < nMats; iMat++, pElemMat += dimRow.GetSizeProd()) {
				const T_Elem *pElemRow = pElemMat;
				for (size_t iRow = 0; iRow < dimRow.GetSize(); iRow++, pElemRow += dimRow.GetStrides()) {
					const T_Elem *pElemCol = pElemRow;
					for (size_t iCol = 0; iCol < dimCol.GetSize(); iCol++, pElemCol += dimCol.GetStrides()) {
						T_ElemRtn numAccum = 0;
						const T_Elem *pElemEach = pElemCol;
						for (size_t i = 0; i < pDimAxis->GetSize(); i++, pElemEach += pDimAxis->GetStrides()) {
							numAccum += *pElemEach;
						}
						*pElemRtn++ = meanFlag? numAccum / numDenom : numAccum;
					}
				}
			}
		}
	}
	return pArrayTRtn.release();
}

template<typename T_ElemRtn, typename T_Elem>
T_ElemRtn CalcSumFlat(const ArrayT<T_Elem> *pArrayT, bool meanFlag)
{
	Double numDenom = static_cast<Double>(pArrayT->GetElemNum());
	if (numDenom == 0) return 0;
	T_ElemRtn numAccum = 0;
	const T_Elem *pElem = pArrayT->GetPointer();
	for (size_t i = 0; i < pArrayT->GetElemNum(); i++, pElem++) {
		numAccum += *pElem;
	}
	return meanFlag? numAccum / numDenom : numAccum;
}

template<typename T_ElemRtn, typename T_Elem>
bool CalcSumTmpl(Signal &sig, AutoPtr<Array> &pArrayRtn, const Array *pArraySelf, ssize_t axis, bool meanFlag)
{
	const ArrayT<T_Elem> *pArrayT = dynamic_cast<const ArrayT<T_Elem> *>(pArraySelf);
	const Array::Dimensions &dims = pArrayT->GetDimensions();
	if (axis < 0 || (axis == 0 && dims.size() == 1)) {
		pArrayRtn.reset(ArrayT<T_ElemRtn>::CreateScalar(CalcSumFlat<T_ElemRtn, T_Elem>(pArrayT, meanFlag)));
	} else if (axis >= dims.size()) {
		sig.SetError(ERR_OutOfRangeError, "specified axis is out of range");
		return false;
	} else {
		pArrayRtn.reset(CalcSum<T_ElemRtn, T_Elem>(pArrayT, axis, meanFlag));
	}
	return true;
}

bool Array::CalcSum(Signal &sig, AutoPtr<Array> &pArrayRtn, ssize_t axis, bool meanFlag) const
{
	typedef bool (*FuncT)(Signal &sig, AutoPtr<Array> &pArrayRtn, const Array *pArraySelf,
						  ssize_t axis, bool meanFlag);
	static const FuncT funcs[ETYPE_Max] = {
		nullptr,
		&CalcSumTmpl<UInt32,	Boolean>,
		&CalcSumTmpl<Int8,		Int8>,
		&CalcSumTmpl<UInt8,		UInt8>,
		&CalcSumTmpl<Int16,		Int16>,
		&CalcSumTmpl<UInt16,	UInt16>,
		&CalcSumTmpl<Int32,		Int32>,
		&CalcSumTmpl<UInt32,	UInt32>,
		&CalcSumTmpl<Int64,		Int64>,
		&CalcSumTmpl<UInt64,	UInt64>,
		&CalcSumTmpl<Half,		Half>,
		&CalcSumTmpl<Float,		Float>,
		&CalcSumTmpl<Double,	Double>,
		&CalcSumTmpl<Complex,	Complex>,
		//&CalcSumTmpl<Value,	Value>,
	};
	FuncT func = funcs[GetElemType()];
	return (*func)(sig, pArrayRtn, this, axis, meanFlag);
}

template<typename T_ElemRtn, typename T_Elem>
ArrayT<T_ElemRtn> *CalcVar(const ArrayT<T_Elem> *pArrayT, size_t axis, bool populationFlag, bool stdFlag)
{
	bool colMajorFlag = false;
	const Array::Dimensions &dims = pArrayT->GetDimensions();
	Array::Dimensions::const_iterator pDimAxis = dims.begin() + axis;
	AutoPtr<ArrayT<T_ElemRtn> > pArrayTRtn(ArrayT<T_ElemRtn>::Create(colMajorFlag));
	pArrayTRtn->SetDimensions(dims.begin(), pDimAxis, pDimAxis + 1, dims.end());
	pArrayTRtn->AllocMemory();
	pArrayTRtn->FillZero();
	Double numDenom = static_cast<Double>(pDimAxis->GetSize());
	Double numDenomVar = (numDenom <= 1)? 1 : populationFlag? numDenom : numDenom - 1;
	const T_Elem *pElemTop = pArrayT->GetPointer();
	T_ElemRtn *pElemRtn = pArrayTRtn->GetPointer();
	size_t sizeSub = pDimAxis->GetStrides() * pDimAxis->GetSize();
	if (pArrayT->IsRowMajor() || axis + 2 >= dims.size()) {
		for (size_t offset = 0; offset < pArrayT->GetElemNum(); offset += sizeSub) {
			const T_Elem *pElemBlock = pElemTop + offset;
			for (size_t j = 0; j < pDimAxis->GetStrides(); j++, pElemBlock++) {
				// calculates a mean value numMean
				T_ElemRtn numMean = 0;
				const T_Elem *pElemEach = pElemBlock;
				for (size_t i = 0; i < pDimAxis->GetSize(); i++, pElemEach += pDimAxis->GetStrides()) {
					numMean += *pElemEach;
				}
				numMean /= numDenom;
				// accumulates values of ((*pElemEach - numMean) ** 2)
				T_ElemRtn numAccum = 0;
				pElemEach = pElemBlock;
				for (size_t i = 0; i < pDimAxis->GetSize(); i++, pElemEach += pDimAxis->GetStrides()) {
					T_ElemRtn tmp = *pElemEach - numMean;
					numAccum += tmp * tmp;
				}
				numAccum /= numDenomVar;
				if (stdFlag) Operator_Math_sqrt::Calc(numAccum, numAccum);
				*pElemRtn++ = numAccum;
			}
		}
	} else { // pArrayT->IsColMajor() && axis + 2 < dim.size()
		const Array::Dimension &dimRow = dims.GetRow();
		const Array::Dimension &dimCol = dims.GetCol();
		size_t nMats = pDimAxis->GetStrides() / dimRow.GetSizeProd();
		for (size_t offset = 0; offset < pArrayT->GetElemNum(); offset += sizeSub) {
			const T_Elem *pElemMat = pElemTop + offset;
			for (size_t iMat = 0; iMat < nMats; iMat++, pElemMat += dimRow.GetSizeProd()) {
				const T_Elem *pElemRow = pElemMat;
				for (size_t iRow = 0; iRow < dimRow.GetSize(); iRow++, pElemRow += dimRow.GetStrides()) {
					const T_Elem *pElemCol = pElemRow;
					for (size_t iCol = 0; iCol < dimCol.GetSize(); iCol++, pElemCol += dimCol.GetStrides()) {
						// calculates a mean value numMean
						T_ElemRtn numMean = 0;
						const T_Elem *pElemEach = pElemCol;
						for (size_t i = 0; i < pDimAxis->GetSize(); i++, pElemEach += pDimAxis->GetStrides()) {
							numMean += *pElemEach;
						}
						numMean /= numDenom;
						// accumulates values of ((*pElemEach - numMean) ** 2)
						T_ElemRtn numAccum = 0;
						pElemEach = pElemCol;
						for (size_t i = 0; i < pDimAxis->GetSize(); i++, pElemEach += pDimAxis->GetStrides()) {
							T_ElemRtn tmp = *pElemEach - numMean;
							numAccum += tmp * tmp;
						}
						numAccum /= numDenomVar;
						if (stdFlag) Operator_Math_sqrt::Calc(numAccum, numAccum);
						*pElemRtn++ = numAccum;
					}
				}
			}
		}
	}
	return pArrayTRtn.release();
}

template<typename T_ElemRtn, typename T_Elem>
T_ElemRtn CalcVarFlat(const ArrayT<T_Elem> *pArrayT, bool populationFlag, bool stdFlag)
{
	Double numDenom = static_cast<Double>(pArrayT->GetElemNum());
	if (numDenom == 0) return 0;
	Double numDenomVar = (numDenom <= 1)? 1 : populationFlag? numDenom : numDenom - 1;
	T_ElemRtn numMean = 0;
	const T_Elem *pElem = pArrayT->GetPointer();
	for (size_t i = 0; i < pArrayT->GetElemNum(); i++, pElem++) {
		numMean += *pElem;
	}
	numMean /= numDenom;
	T_ElemRtn numAccum = 0;
	pElem = pArrayT->GetPointer();
	for (size_t i = 0; i < pArrayT->GetElemNum(); i++, pElem++) {
		T_ElemRtn tmp = *pElem - numMean;
		numAccum += tmp * tmp;
	}
	numAccum /= numDenomVar;
	if (stdFlag) Operator_Math_sqrt::Calc(numAccum, numAccum);
	return numAccum;
}

template<typename T_ElemRtn, typename T_Elem>
bool CalcVarTmpl(Signal &sig, AutoPtr<Array> &pArrayRtn, const Array *pArraySelf,
				 ssize_t axis, bool populationFlag, bool stdFlag)
{
	const ArrayT<T_Elem> *pArrayT = dynamic_cast<const ArrayT<T_Elem> *>(pArraySelf);
	const Array::Dimensions &dims = pArrayT->GetDimensions();
	if (axis < 0 || (axis == 0 && dims.size() == 1)) {
		pArrayRtn.reset(ArrayT<T_ElemRtn>::CreateScalar(CalcVarFlat<T_ElemRtn, T_Elem>(
															pArrayT, populationFlag, stdFlag)));
	} else if (axis >= dims.size()) {
		sig.SetError(ERR_OutOfRangeError, "specified axis is out of range");
		return false;
	} else {
		pArrayRtn.reset(CalcVar<T_ElemRtn, T_Elem>(pArrayT, axis, populationFlag, stdFlag));
	}
	return true;
}

bool Array::CalcVar(Signal &sig, AutoPtr<Array> &pArrayRtn, ssize_t axis, bool populationFlag, bool stdFlag) const
{
	typedef bool (*FuncT)(Signal &sig, AutoPtr<Array> &pArrayRtn, const Array *pArraySelf,
						  ssize_t axis, bool populationFlag, bool stdFlag);
	static const FuncT funcs[ETYPE_Max] = {
		nullptr,
		&CalcVarTmpl<UInt32,	Boolean>,
		&CalcVarTmpl<Int8,		Int8>,
		&CalcVarTmpl<UInt8,		UInt8>,
		&CalcVarTmpl<Int16,		Int16>,
		&CalcVarTmpl<UInt16,	UInt16>,
		&CalcVarTmpl<Int32,		Int32>,
		&CalcVarTmpl<UInt32,	UInt32>,
		&CalcVarTmpl<Int64,		Int64>,
		&CalcVarTmpl<UInt64,	UInt64>,
		&CalcVarTmpl<Half,		Half>,
		&CalcVarTmpl<Float,		Float>,
		&CalcVarTmpl<Double,	Double>,
		&CalcVarTmpl<Complex,	Complex>,
		//&CalcVarTmpl<Value,	Value>,
	};
	FuncT func = funcs[GetElemType()];
	return (*func)(sig, pArrayRtn, this, axis, populationFlag, stdFlag);
}

void Array::ExpandKernelToColVector(AutoPtr<Array> &pArrayRtn, size_t htKernel, size_t wdKernel, size_t strides, size_t padding) const
{
}

void Array::StoreColVectorToKernel(AutoPtr<Array> &pArrayRtn, size_t htKernel, size_t wdKernel, size_t strides, size_t padding) const
{
}

bool Array::IsSquare() const
{
	return _dims.HasRowCol() && (_dims.GetRow().GetSize() == _dims.GetCol().GetSize());
}

bool Array::HasShape(size_t size) const
{
	return (_dims.size() == 1) && _dims[0].GetSize() == size;
}

bool Array::HasShape(size_t sizeRow, size_t sizeCol) const
{
	return (_dims.size() == 2) && _dims[0].GetSize() == sizeRow && _dims[1].GetSize() == sizeCol;
}

bool Array::HasSameElements(const Array &array) const
{
	if (GetElemType() != array.GetElemType()) return false;
	if (!Dimensions::IsSameShape(GetDimensions(), array.GetDimensions())) return false;
	size_t bytes = GetElemBytes() * GetElemNum();
	if (memcmp(GetPointerRaw(), array.GetPointerRaw(), bytes) != 0) return false;
	return true;
}

bool Array::PrepareModification(Signal &sig)
{
	if (_pMemory->GetCntRef() > 1) {
		_pMemory.reset(_pMemory->Clone());
		if (_pMemory.IsNull()) {
			sig.SetError(ERR_MemoryError, "failed to allocate memory for array");
			return false;
		}
	}
	return true;
}

Value Array::ToValue(Environment &env, Array *pArray)
{
	return (pArray == nullptr)? Value::Nil :
		!pArray->IsScalar()? Value(new Object_array(env, pArray)) :
		pArray->IsElemType(ETYPE_Complex)? Value(pArray->GetScalarComplex()) :
		Value(pArray->GetScalarNumber());
}

bool Array::Serialize(Environment &env, Stream &stream) const
{
	if (!stream.SerializeUInt8(env, static_cast<UInt8>(_elemType))) return false;
	if (!stream.SerializeUInt8(env, static_cast<UInt8>(_colMajorFlag))) return false;
	if (!_dims.Serialize(env, stream)) return false;
	size_t bytes = GetElemBytes() * GetElemNum();
	if (stream.Write(env, GetPointerRaw(), bytes) < bytes) return false;
	return true;
}

Array *Array::Deserialize(Environment &env, Stream &stream)
{
	UInt8 elemTypeRaw = 0;
	if (!stream.DeserializeUInt8(env, elemTypeRaw)) return nullptr;
	UInt8 colMajorFlagRaw = 0;
	if (!stream.DeserializeUInt8(env, colMajorFlagRaw)) return nullptr;
	Array::Dimensions dims;
	if (!dims.Deserialize(env, stream)) return nullptr;
	AutoPtr<Array> pArray(Create(static_cast<ElemType>(elemTypeRaw), static_cast<bool>(colMajorFlagRaw)));
	pArray->SetDimensions(dims);
	pArray->AllocMemory();
	size_t bytes = pArray->GetElemBytes() * pArray->GetElemNum();
	if (stream.Read(env, pArray->GetPointerRaw(), bytes) < bytes) return nullptr;
	return pArray.release();
}

template<typename T_Elem>
Array *CreateTmpl(bool colMajorFlag)
{
	return ArrayT<T_Elem>::Create(colMajorFlag);
}

Array *Array::Create(ElemType elemType, bool colMajorFlag)
{
	typedef Array *(*FuncT)(bool colMajorFlag);
	static const FuncT funcs[ETYPE_Max] = {
		nullptr,
		&CreateTmpl<Boolean>,
		&CreateTmpl<Int8>,
		&CreateTmpl<UInt8>,
		&CreateTmpl<Int16>,
		&CreateTmpl<UInt16>,
		&CreateTmpl<Int32>,
		&CreateTmpl<UInt32>,
		&CreateTmpl<Int64>,
		&CreateTmpl<UInt64>,
		&CreateTmpl<Half>,
		&CreateTmpl<Float>,
		&CreateTmpl<Double>,
		&CreateTmpl<Complex>,
		//&CreateTmpl<Value>,
	};
	FuncT func = funcs[elemType];
	return (*func)(colMajorFlag);
}

Array::ElemType Array::SymbolToElemType(const Symbol *pSymbol)
{
	MapToElemType::const_iterator iter = _mapToElemType.find(pSymbol);
	return (iter == _mapToElemType.end())? ETYPE_None : iter->second;
}

Array::ElemType Array::SymbolToElemType(Signal &sig, const Symbol *pSymbol)
{
	ElemType elemType = SymbolToElemType(pSymbol);
	if (elemType == ETYPE_None) {
		sig.SetError(ERR_ValueError, "invalid symbol for element type of array: %s",
					 pSymbol->GetName());
	}
	return elemType;
}

template<typename T_ElemDst, typename T_ElemSrc>
void CopyElementsTmpl(void *pElemRawDst, const void *pElemRawSrc, size_t nElems)
{
	T_ElemDst *pElemDst = reinterpret_cast<T_ElemDst *>(pElemRawDst);
	const T_ElemSrc *pElemSrc = reinterpret_cast<const T_ElemSrc *>(pElemRawSrc);
	for (size_t i = 0; i < nElems; i++, pElemDst++, pElemSrc++) {
		*pElemDst = static_cast<T_ElemDst>(*pElemSrc);
	}
}

bool Array::CopyElements(Environment &env, Array *pArrayDst, const Array *pArraySrc)
{
	size_t nElems = ChooseMin(pArrayDst->GetElemNum(), pArraySrc->GetElemNum());
	return CopyElements(env, pArrayDst->GetPointerRaw(), pArrayDst->GetElemType(),
						pArraySrc->GetPointerRaw(), pArraySrc->GetElemType(), nElems);
}

bool Array::CopyElements(Environment &env, void *pElemRawDst, ElemType elemTypeDst,
						 const void *pElemRawSrc, ElemType elemTypeSrc, size_t nElems)
{
	typedef void (*FuncT)(void *pElemRawDst, const void *pElemRawSrc, size_t nElems);
	static const FuncT funcs[][ETYPE_Max] = {
		{
			nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
			nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
		}, {
			nullptr,
			&CopyElementsTmpl<Boolean, Boolean>,
			&CopyElementsTmpl<Boolean, Int8>,
			&CopyElementsTmpl<Boolean, UInt8>,
			&CopyElementsTmpl<Boolean, Int16>,
			&CopyElementsTmpl<Boolean, UInt16>,
			&CopyElementsTmpl<Boolean, Int32>,
			&CopyElementsTmpl<Boolean, UInt32>,
			&CopyElementsTmpl<Boolean, Int64>,
			&CopyElementsTmpl<Boolean, UInt64>,
			&CopyElementsTmpl<Boolean, Half>,
			&CopyElementsTmpl<Boolean, Float>,
			&CopyElementsTmpl<Boolean, Double>,
			&CopyElementsTmpl<Boolean, Complex>,
			nullptr,
		}, {
			nullptr,
			&CopyElementsTmpl<Int8, Boolean>,
			&CopyElementsTmpl<Int8, Int8>,
			&CopyElementsTmpl<Int8, UInt8>,
			&CopyElementsTmpl<Int8, Int16>,
			&CopyElementsTmpl<Int8, UInt16>,
			&CopyElementsTmpl<Int8, Int32>,
			&CopyElementsTmpl<Int8, UInt32>,
			&CopyElementsTmpl<Int8, Int64>,
			&CopyElementsTmpl<Int8, UInt64>,
			&CopyElementsTmpl<Int8, Half>,
			&CopyElementsTmpl<Int8, Float>,
			&CopyElementsTmpl<Int8, Double>,
			nullptr,
			nullptr,
		}, {
			nullptr,
			&CopyElementsTmpl<UInt8, Boolean>,
			&CopyElementsTmpl<UInt8, Int8>,
			&CopyElementsTmpl<UInt8, UInt8>,
			&CopyElementsTmpl<UInt8, Int16>,
			&CopyElementsTmpl<UInt8, UInt16>,
			&CopyElementsTmpl<UInt8, Int32>,
			&CopyElementsTmpl<UInt8, UInt32>,
			&CopyElementsTmpl<UInt8, Int64>,
			&CopyElementsTmpl<UInt8, UInt64>,
			&CopyElementsTmpl<UInt8, Half>,
			&CopyElementsTmpl<UInt8, Float>,
			&CopyElementsTmpl<UInt8, Double>,
			nullptr,
			nullptr,
		}, {
			nullptr,
			&CopyElementsTmpl<Int16, Boolean>,
			&CopyElementsTmpl<Int16, Int8>,
			&CopyElementsTmpl<Int16, UInt8>,
			&CopyElementsTmpl<Int16, Int16>,
			&CopyElementsTmpl<Int16, UInt16>,
			&CopyElementsTmpl<Int16, Int32>,
			&CopyElementsTmpl<Int16, UInt32>,
			&CopyElementsTmpl<Int16, Int64>,
			&CopyElementsTmpl<Int16, UInt64>,
			&CopyElementsTmpl<Int16, Half>,
			&CopyElementsTmpl<Int16, Float>,
			&CopyElementsTmpl<Int16, Double>,
			nullptr,
			nullptr,
		}, {
			nullptr,
			&CopyElementsTmpl<UInt16, Boolean>,
			&CopyElementsTmpl<UInt16, Int8>,
			&CopyElementsTmpl<UInt16, UInt8>,
			&CopyElementsTmpl<UInt16, Int16>,
			&CopyElementsTmpl<UInt16, UInt16>,
			&CopyElementsTmpl<UInt16, Int32>,
			&CopyElementsTmpl<UInt16, UInt32>,
			&CopyElementsTmpl<UInt16, Int64>,
			&CopyElementsTmpl<UInt16, UInt64>,
			&CopyElementsTmpl<UInt16, Half>,
			&CopyElementsTmpl<UInt16, Float>,
			&CopyElementsTmpl<UInt16, Double>,
			nullptr,
			nullptr,
		}, {
			nullptr,
			&CopyElementsTmpl<Int32, Boolean>,
			&CopyElementsTmpl<Int32, Int8>,
			&CopyElementsTmpl<Int32, UInt8>,
			&CopyElementsTmpl<Int32, Int16>,
			&CopyElementsTmpl<Int32, UInt16>,
			&CopyElementsTmpl<Int32, Int32>,
			&CopyElementsTmpl<Int32, UInt32>,
			&CopyElementsTmpl<Int32, Int64>,
			&CopyElementsTmpl<Int32, UInt64>,
			&CopyElementsTmpl<Int32, Half>,
			&CopyElementsTmpl<Int32, Float>,
			&CopyElementsTmpl<Int32, Double>,
			nullptr,
			nullptr,
		}, {
			nullptr,
			&CopyElementsTmpl<UInt32, Boolean>,
			&CopyElementsTmpl<UInt32, Int8>,
			&CopyElementsTmpl<UInt32, UInt8>,
			&CopyElementsTmpl<UInt32, Int16>,
			&CopyElementsTmpl<UInt32, UInt16>,
			&CopyElementsTmpl<UInt32, Int32>,
			&CopyElementsTmpl<UInt32, UInt32>,
			&CopyElementsTmpl<UInt32, Int64>,
			&CopyElementsTmpl<UInt32, UInt64>,
			&CopyElementsTmpl<UInt32, Half>,
			&CopyElementsTmpl<UInt32, Float>,
			&CopyElementsTmpl<UInt32, Double>,
			nullptr,
			nullptr,
		}, {
			nullptr,
			&CopyElementsTmpl<Int64, Boolean>,
			&CopyElementsTmpl<Int64, Int8>,
			&CopyElementsTmpl<Int64, UInt8>,
			&CopyElementsTmpl<Int64, Int16>,
			&CopyElementsTmpl<Int64, UInt16>,
			&CopyElementsTmpl<Int64, Int32>,
			&CopyElementsTmpl<Int64, UInt32>,
			&CopyElementsTmpl<Int64, Int64>,
			&CopyElementsTmpl<Int64, UInt64>,
			&CopyElementsTmpl<Int64, Half>,
			&CopyElementsTmpl<Int64, Float>,
			&CopyElementsTmpl<Int64, Double>,
			nullptr,
			nullptr,
		}, {
			nullptr,
			&CopyElementsTmpl<UInt64, Boolean>,
			&CopyElementsTmpl<UInt64, Int8>,
			&CopyElementsTmpl<UInt64, UInt8>,
			&CopyElementsTmpl<UInt64, Int16>,
			&CopyElementsTmpl<UInt64, UInt16>,
			&CopyElementsTmpl<UInt64, Int32>,
			&CopyElementsTmpl<UInt64, UInt32>,
			&CopyElementsTmpl<UInt64, Int64>,
			&CopyElementsTmpl<UInt64, UInt64>,
			&CopyElementsTmpl<UInt64, Half>,
			&CopyElementsTmpl<UInt64, Float>,
			&CopyElementsTmpl<UInt64, Double>,
			nullptr,
			nullptr,
		}, {
			nullptr,
			&CopyElementsTmpl<Half,	Boolean>,
			&CopyElementsTmpl<Half,	Int8>,
			&CopyElementsTmpl<Half, UInt8>,
			&CopyElementsTmpl<Half, Int16>,
			&CopyElementsTmpl<Half, UInt16>,
			&CopyElementsTmpl<Half, Int32>,
			&CopyElementsTmpl<Half, UInt32>,
			&CopyElementsTmpl<Half, Int64>,
			&CopyElementsTmpl<Half, UInt64>,
			&CopyElementsTmpl<Half, Half>,
			&CopyElementsTmpl<Half, Float>,
			&CopyElementsTmpl<Half, Double>,
			nullptr,
			nullptr,
		}, {
			nullptr,
			&CopyElementsTmpl<Float, Boolean>,
			&CopyElementsTmpl<Float, Int8>,
			&CopyElementsTmpl<Float, UInt8>,
			&CopyElementsTmpl<Float, Int16>,
			&CopyElementsTmpl<Float, UInt16>,
			&CopyElementsTmpl<Float, Int32>,
			&CopyElementsTmpl<Float, UInt32>,
			&CopyElementsTmpl<Float, Int64>,
			&CopyElementsTmpl<Float, UInt64>,
			&CopyElementsTmpl<Float, Half>,
			&CopyElementsTmpl<Float, Float>,
			&CopyElementsTmpl<Float, Double>,
			nullptr,
			nullptr,
		}, {
			nullptr,
			&CopyElementsTmpl<Double, Boolean>,
			&CopyElementsTmpl<Double, Int8>,
			&CopyElementsTmpl<Double, UInt8>,
			&CopyElementsTmpl<Double, Int16>,
			&CopyElementsTmpl<Double, UInt16>,
			&CopyElementsTmpl<Double, Int32>,
			&CopyElementsTmpl<Double, UInt32>,
			&CopyElementsTmpl<Double, Int64>,
			&CopyElementsTmpl<Double, UInt64>,
			&CopyElementsTmpl<Double, Half>,
			&CopyElementsTmpl<Double, Float>,
			&CopyElementsTmpl<Double, Double>,
			nullptr,
			nullptr,
		}, {
			nullptr,
			&CopyElementsTmpl<Complex, Boolean>,
			&CopyElementsTmpl<Complex, Int8>,
			&CopyElementsTmpl<Complex, UInt8>,
			&CopyElementsTmpl<Complex, Int16>,
			&CopyElementsTmpl<Complex, UInt16>,
			&CopyElementsTmpl<Complex, Int32>,
			&CopyElementsTmpl<Complex, UInt32>,
			&CopyElementsTmpl<Complex, Int64>,
			&CopyElementsTmpl<Complex, UInt64>,
			&CopyElementsTmpl<Complex, Half>,
			&CopyElementsTmpl<Complex, Float>,
			&CopyElementsTmpl<Complex, Double>,
			&CopyElementsTmpl<Complex, Complex>,
			nullptr,
		}, {
			nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
			nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
		},
	};
	FuncT func = funcs[elemTypeDst][elemTypeSrc];
	if (func == nullptr) {
		env.SetError(ERR_TypeError, "can't copy elements from array@%s to array@%s",
					 GetElemTypeName(elemTypeSrc), GetElemTypeName(elemTypeDst));
		return false;
	}
	(*func)(pElemRawDst, pElemRawSrc, nElems);
	return true;
}

bool Array::ApplyUnaryFunc(Signal &sig, const UnaryFuncPack &pack, AutoPtr<Array> &pArrayRtn, const Array *pArray)
{
	UnaryFuncT unaryFunc = pack.table.funcs[pArray->GetElemType()];
	if (unaryFunc == nullptr) {
		sig.SetError(ERR_TypeError, "can't apply %s function on these arrays", pack.name);
		return nullptr;
	}
	return (*unaryFunc)(sig, pArrayRtn, pArray);
}

Value Array::ApplyUnaryFuncOnValue(Environment &env, const UnaryFuncPack &pack, const Value &value)
{
	AutoPtr<Array> pArrayRtn;
	if (!ApplyUnaryFunc(
			env, pack, pArrayRtn, Object_array::GetObject(value)->GetArray())) return Value::Nil;
	return ToValue(env, pArrayRtn.release());
}

bool Array::ApplyBinaryFunc(
	Signal &sig, const BinaryFuncPack &pack, AutoPtr<Array> &pArrayRtn, const Array *pArrayL, const Array *pArrayR)
{
	if (!pArrayL->IsScalar() && !pArrayR->IsScalar()) {
		return ApplyBinaryFunc_array_array(sig, pack, pArrayRtn, pArrayL, pArrayR);
	} else if (!pArrayL->IsScalar() && pArrayR->IsScalar()) {
		if (pArrayR->IsElemType(ETYPE_Complex)) {
			return ApplyBinaryFunc_array_complex(sig, pack, pArrayRtn, pArrayL, pArrayR->GetScalarComplex());
		} else {
			return ApplyBinaryFunc_array_number(sig, pack, pArrayRtn, pArrayL, pArrayR->GetScalarNumber());
		}
	} else if (pArrayL->IsScalar() && !pArrayR->IsScalar()) {
		if (pArrayL->IsElemType(ETYPE_Complex)) {
			return ApplyBinaryFunc_complex_array(sig, pack, pArrayRtn, pArrayL->GetScalarComplex(), pArrayR);
		} else {
			return ApplyBinaryFunc_number_array(sig, pack, pArrayRtn, pArrayL->GetScalarNumber(), pArrayR);
		}
	} else {
		if (!pArrayL->IsElemType(ETYPE_Complex) && !pArrayR->IsElemType(ETYPE_Complex)) {
			if (pack.table.func_number_number == nullptr) {
				sig.SetError(ERR_TypeError, "can't apply %s function on these scalars", pack.name);
				return nullptr;
			}
			return (*pack.table.func_number_number)(
				sig, pArrayRtn, pArrayL->GetScalarNumber(), pArrayR->GetScalarNumber());
		} else {
			if (pack.table.func_complex_complex == nullptr) {
				sig.SetError(ERR_TypeError, "can't apply %s function on these scalars", pack.name);
				return nullptr;
			}
			return (*pack.table.func_complex_complex)(
				sig, pArrayRtn, pArrayL->GetScalarComplex(), pArrayR->GetScalarComplex());
		}
	}
	return nullptr;
}

bool Array::ApplyBinaryFunc_array_array(
	Signal &sig, const BinaryFuncPack &pack, AutoPtr<Array> &pArrayRtn, const Array *pArrayL, const Array *pArrayR)
{
	if (pack.elemwiseFlag && !CheckElemwiseCalculatable(sig, pack, pArrayL, pArrayR)) return nullptr;
	BinaryFuncT_array_array binaryFunc_array_array =
		pack.table.funcs_array_array[pArrayL->GetElemType()][pArrayR->GetElemType()];
	if (binaryFunc_array_array == nullptr) {
		sig.SetError(ERR_TypeError, "can't apply %s function on these arrays", pack.name);
		return nullptr;
	}
	return (*binaryFunc_array_array)(sig, pArrayRtn, pArrayL, pArrayR);
}

Value Array::ApplyBinaryFuncOnValue_array_array(
	Environment &env, const BinaryFuncPack &pack, const Value &valueL, const Value &valueR)
{
	AutoPtr<Array> pArrayRtn;
	if (!ApplyBinaryFunc_array_array(
			env, pack, pArrayRtn,
			Object_array::GetObject(valueL)->GetArray(),
			Object_array::GetObject(valueR)->GetArray())) return Value::Nil;
	return ToValue(env, pArrayRtn.release());
}

bool Array::ApplyBinaryFunc_array_number(
	Signal &sig, const BinaryFuncPack &pack, AutoPtr<Array> &pArrayRtn, const Array *pArrayL, const Double &elemR)
{
	BinaryFuncT_array_number binaryFunc_array_number =
		pack.table.funcs_array_number[pArrayL->GetElemType()];
	if (binaryFunc_array_number == nullptr) {
		sig.SetError(ERR_TypeError, "can't apply %s function on these arrays", pack.name);
		return nullptr;
	}
	return (*binaryFunc_array_number)(sig, pArrayRtn, pArrayL, elemR);
}

Value Array::ApplyBinaryFuncOnValue_array_number(
	Environment &env, const BinaryFuncPack &pack, const Value &valueL, const Value &valueR)
{
	AutoPtr<Array> pArrayRtn;
	if (!ApplyBinaryFunc_array_number(
			env, pack, pArrayRtn,
			Object_array::GetObject(valueL)->GetArray(), valueR.GetDouble())) return Value::Nil;
	return ToValue(env, pArrayRtn.release());
}

bool Array::ApplyBinaryFunc_number_array(
	Signal &sig, const BinaryFuncPack &pack, AutoPtr<Array> &pArrayRtn, const Double &elemL, const Array *pArrayR)
{
	BinaryFuncT_number_array binaryFunc_number_array =
		pack.table.funcs_number_array[pArrayR->GetElemType()];
	if (binaryFunc_number_array == nullptr) {
		sig.SetError(ERR_TypeError, "can't apply %s function on these arrays", pack.name);
		return nullptr;
	}
	return (*binaryFunc_number_array)(sig, pArrayRtn, elemL, pArrayR);
}

Value Array::ApplyBinaryFuncOnValue_number_array(
	Environment &env, const BinaryFuncPack &pack, const Value &valueL, const Value &valueR)
{
	AutoPtr<Array> pArrayRtn;
	if (!ApplyBinaryFunc_number_array(
			env, pack, pArrayRtn,
			valueL.GetDouble(), Object_array::GetObject(valueR)->GetArray())) return false;
	return ToValue(env, pArrayRtn.release());
}

bool Array::ApplyBinaryFunc_array_complex(
	Signal &sig, const BinaryFuncPack &pack, AutoPtr<Array> &pArrayRtn, const Array *pArrayL, const Complex &complexR)
{
	BinaryFuncT_array_complex binaryFunc_array_complex =
		pack.table.funcs_array_complex[pArrayL->GetElemType()];
	if (binaryFunc_array_complex == nullptr) {
		sig.SetError(ERR_TypeError, "can't apply %s function on these arrays", pack.name);
		return nullptr;
	}
	return (*binaryFunc_array_complex)(sig, pArrayRtn, pArrayL, complexR);
}

Value Array::ApplyBinaryFuncOnValue_array_complex(
	Environment &env, const BinaryFuncPack &pack, const Value &valueL, const Value &valueR)
{
	AutoPtr<Array> pArrayRtn;
	if (!ApplyBinaryFunc_array_complex(
			env, pack, pArrayRtn,
			Object_array::GetObject(valueL)->GetArray(), valueR.GetComplex())) return Value::Nil;
	return ToValue(env, pArrayRtn.release());
}

bool Array::ApplyBinaryFunc_complex_array(
	Signal &sig, const BinaryFuncPack &pack, AutoPtr<Array> &pArrayRtn, const Complex &complexL, const Array *pArrayR)
{
	BinaryFuncT_complex_array binaryFunc_complex_array =
		pack.table.funcs_complex_array[pArrayR->GetElemType()];
	if (binaryFunc_complex_array == nullptr) {
		sig.SetError(ERR_TypeError, "can't apply %s function on these arrays", pack.name);
		return nullptr;
	}
	return (*binaryFunc_complex_array)(sig, pArrayRtn, complexL, pArrayR);
}

Value Array::ApplyBinaryFuncOnValue_complex_array(
	Environment &env, const BinaryFuncPack &pack, const Value &valueL, const Value &valueR)
{
	AutoPtr<Array> pArrayRtn;
	if (!ApplyBinaryFunc_complex_array(
			env, pack, pArrayRtn,
			valueL.GetComplex(), Object_array::GetObject(valueR)->GetArray())) return false;
	return ToValue(env, pArrayRtn.release());
}

bool Array::ApplyInvertFunc(Signal &sig, AutoPtr<Array> &pArrayRtn, const Array *pArray, Double epsilon)
{
	InvertFuncT invertFunc = invertFuncTable.funcs[pArray->GetElemType()];
	if (invertFunc == nullptr) {
		sig.SetError(ERR_TypeError, "can't apply invert function on this array");
		return nullptr;
	}
	return (*invertFunc)(sig, pArrayRtn, pArray, epsilon);
}

void Array::SetError_UnacceptableValueAsElement(Environment &env, const Value &value)
{
	env.SetError(ERR_ValueError, "value of %s can not be stored in array",
				 value.MakeValueTypeName().c_str());
}

//-----------------------------------------------------------------------------
// Array::Dimension
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Array::Dimensions
//-----------------------------------------------------------------------------
String Array::Dimensions::ToString(const_iterator pDim, const_iterator pDimEnd, const char *sep)
{
	String rtn;
	char buff[80];
	for ( ; pDim != pDimEnd; pDim++) {
		::sprintf(buff, "%zu", pDim->GetSize());
		if (!rtn.empty()) rtn += sep;
		rtn += buff;
	}
	return rtn;
}

bool Array::Dimensions::Serialize(Environment &env, Stream &stream) const
{
	if (!stream.SerializePackedUInt64(env, static_cast<UInt64>(size()))) return false;
	foreach_const (Dimensions, pDim, *this) {
		if (!stream.SerializePackedUInt64(env, static_cast<UInt64>(pDim->GetSize()))) return false;
	}	
	return true;
}

bool Array::Dimensions::Deserialize(Environment &env, Stream &stream)
{
	clear();
	UInt64 nDims = 0;
	if (!stream.DeserializePackedUInt64(env, nDims)) return false;
	reserve(nDims);
	for (UInt64 i = 0; i < nDims; i++) {
		UInt64 size = 0;
		if (!stream.DeserializePackedUInt64(env, size)) return false;
		push_back(size);
	}
	return true;
}

bool Array::Dimensions::IsSameShape(const_iterator pDimA, const_iterator pDimEndA,
									const_iterator pDimB, const_iterator pDimEndB)
{
	for ( ; pDimA != pDimEndA && pDimB != pDimEndB; pDimA++, pDimB++) {
		if (pDimA->GetSize() != pDimB->GetSize()) return false;
	}
	return pDimA == pDimEndA && pDimB == pDimEndB;
}

bool Array::Dimensions::CheckSameShape(Signal &sig, const_iterator pDimA, const_iterator pDimEndA,
									   const_iterator pDimB, const_iterator pDimEndB)
{
	if (IsSameShape(pDimA, pDimEndA, pDimB, pDimEndB)) return true;
	sig.SetError(ERR_ValueError, "mismatched dimension of arrays between (%s) and (%s)",
				 ToString(pDimA, pDimEndA).c_str(), ToString(pDimB, pDimEndB).c_str());
	return false;
}

bool Array::Dimensions::IsElemwiseCalculatable(const Dimensions &dimsA, const Dimensions &dimsB)
{
	const_reverse_iterator pDimA = dimsA.rbegin();
	const_reverse_iterator pDimB = dimsB.rbegin();
	for ( ; pDimA != dimsA.rend() && pDimB != dimsB.rend(); pDimA++, pDimB++) {
		if (pDimA->GetSize() != pDimB->GetSize()) return false;
	}
	return true;
}

bool Array::Dimensions::CheckElemwiseCalculatable(Signal &sig, const BinaryFuncPack &pack,
												  const Dimensions &dimsL, const Dimensions &dimsR)
{
	if (IsElemwiseCalculatable(dimsL, dimsR)) return true;
	if (*pack.symbol == '\0') {
		sig.SetError(ERR_ValueError,
					 "failed in array calculation: %s((%s), (%s))",
					 pack.name, dimsL.ToString().c_str(), dimsR.ToString().c_str());
	} else {
		sig.SetError(ERR_ValueError,
					 "failed in array calculation: (%s) %s (%s)",
					 dimsL.ToString().c_str(), pack.symbol, dimsR.ToString().c_str());
	}
	return false;
}

//------------------------------------------------------------------------------
// InvertFuncTmpl
//------------------------------------------------------------------------------
template<typename T_Elem> inline Double _CalcInvError(const T_Elem &num)
{
	return std::abs(static_cast<Double>(num));
}

template<> inline Double _CalcInvError<Complex>(const Complex &num)
{
	return std::norm(num);
}

template<typename T_Elem> inline Double _CalcInvErrorThreshold(Double epsilon)
{
	return epsilon;
}

template<> inline Double _CalcInvErrorThreshold<Complex>(Double epsilon)
{
	return epsilon * epsilon;
}

template<typename T_Elem>
bool InvertFuncTmpl_Sub(T_Elem *pElemRtn, bool colMajorFlagRtn,
						const T_Elem *pElemOrg, bool colMajorFlagOrg, size_t nRows,
						T_Elem &det, T_Elem *pElemWork, T_Elem *pElemRows[], Double epsilon)
{
	static const Double invErrThreshold = _CalcInvErrorThreshold<T_Elem>(epsilon);
	size_t nCols = nRows;
	size_t nCols2 = nCols * 2;
	size_t bytesPerRow = nCols * sizeof(T_Elem);
	det = 1;
	do {
		const T_Elem *pElemSrc = pElemOrg;
		T_Elem *pElemDst = pElemWork;
		::memset(pElemWork, 0x00, nRows * nCols2 * sizeof(T_Elem));
		if (colMajorFlagOrg) {
			// column-major order
			for (size_t iRow = 0; iRow < nRows; iRow++, pElemDst += nCols2, pElemSrc++) {
				const T_Elem *pElemSrcWk = pElemSrc;
				T_Elem *pElemDstWk = pElemDst;
				for (size_t iCol = 0; iCol < nCols; iCol++, pElemDstWk++, pElemSrcWk += nRows) {
					*pElemDstWk = *pElemSrcWk;
				}
				*(pElemDst + nCols + iRow) = 1;
				pElemRows[iRow] = pElemDst;
			}
		} else {
			// row-major order
			for (size_t iRow = 0; iRow < nRows; iRow++, pElemDst += nCols2, pElemSrc += nCols) {
				::memcpy(pElemDst, pElemSrc, bytesPerRow);
				*(pElemDst + nCols + iRow) = 1;
				pElemRows[iRow] = pElemDst;
			}
		}
	} while (0);
	for (size_t iRowPivot = 0; iRowPivot < nRows; iRowPivot++) {
		size_t iRowMax = iRowPivot;
		Double invErrMax = _CalcInvError<T_Elem>(pElemRows[iRowMax][iRowPivot]);
		for (size_t iRow = iRowMax + 1; iRow < nRows; iRow++) {
			Double invErr = _CalcInvError<T_Elem>(pElemRows[iRow][iRowPivot]);
			if (invErrMax < invErr) {
				iRowMax = iRow;
				invErrMax = invErr;
			}
		}
		if (invErrMax < invErrThreshold) {
			det = 0;
			return false;
		}
		if (iRowPivot != iRowMax) {
			std::swap(pElemRows[iRowPivot], pElemRows[iRowMax]);
			det = -det;
		}
		do {
			T_Elem *pElemPivot = pElemRows[iRowPivot];
			T_Elem factor = *(pElemPivot + iRowPivot);
			det *= factor;
			for (size_t i = 0; i < nCols2; i++, pElemPivot++) {
				*pElemPivot /= factor;
			}
		} while (0);
		for (size_t iRow = 0; iRow < nRows; iRow++) {
			if (iRowPivot == iRow) continue;
			T_Elem *pElemPivot = pElemRows[iRowPivot];
			T_Elem *pElemEach = pElemRows[iRow];
			T_Elem factor = *(pElemEach + iRowPivot);
			for (size_t i = 0; i < nCols2; i++, pElemPivot++, pElemEach++) {
				*pElemEach -= *pElemPivot * factor;
			}
		}
	}
	if (pElemRtn != nullptr) {
		T_Elem *pElemDst = pElemRtn;
		if (colMajorFlagRtn) {
			// column-major order
			for (size_t iRow = 0; iRow < nRows; iRow++, pElemDst++) {
				const T_Elem *pElemSrcWk = pElemRows[iRow] + nCols;
				T_Elem *pElemDstWk = pElemDst;
				for (size_t iCol = 0; iCol < nCols; iCol++, pElemDstWk += nRows, pElemSrcWk++) {
					*pElemDstWk = *pElemSrcWk;
				}
			}
		} else {
			// row-major order
			for (size_t iRow = 0; iRow < nRows; iRow++, pElemDst += nCols) {
				::memcpy(pElemDst, pElemRows[iRow] + nCols, bytesPerRow);
			}
		}
	}
	return true;
}

template<typename T_Elem>
bool InvertFuncTmpl(Signal &sig, AutoPtr<Array> &pArrayRtn, const Array *pArray, Double epsilon)
{
	const ArrayT<T_Elem> *pArrayT = dynamic_cast<const ArrayT<T_Elem> *>(pArray);
	const Array::Dimensions &dims = pArrayT->GetDimensions();
	if (!dims.HasRowCol()) {
		sig.SetError(ERR_ValueError, "inversion can only be calculated with matrix");
		return false;
	}
	size_t nRows = dims.GetRow().GetSize();
	size_t nCols = dims.GetCol().GetSize();
	if (nRows != nCols) {
		sig.SetError(ERR_ValueError, "inversion can only be applied to square matrix");
		return false;
	}
	std::unique_ptr<T_Elem []> pElemWork(new T_Elem [nRows * nCols * 2]);
	std::unique_ptr<T_Elem *[]> pElemRows(new T_Elem *[nRows]);
	bool colMajorFlag = false;
	if (pArrayRtn.IsNull()) pArrayRtn.reset(ArrayT<T_Elem>::Create(colMajorFlag, pArrayT->GetDimensions()));
	size_t elemNumMat = nRows * nCols;
	const T_Elem *pElemOrg = pArrayT->GetPointer();
	T_Elem *pElemRtn = dynamic_cast<ArrayT<T_Elem> *>(pArrayRtn.get())->GetPointer();
	bool colMajorFlagOrg = pArrayT->IsColMajor();
	bool colMajorFlagRtn = pArrayRtn->IsColMajor();
	for (size_t cnt = pArrayRtn->GetElemNum() / elemNumMat; cnt > 0; cnt--) {
		T_Elem det = 0;
		if (!InvertFuncTmpl_Sub(pElemRtn, colMajorFlagRtn, pElemOrg, colMajorFlagOrg, nRows,
								det, pElemWork.get(), pElemRows.get(), epsilon)) {
			sig.SetError(ERR_ValueError, "failed to calculate inverted matrix");
			return false;
		}
		pElemRtn += elemNumMat;
		pElemOrg += elemNumMat;
	}
	return true;
}

//-----------------------------------------------------------------------------
// Array::Indexer
//-----------------------------------------------------------------------------
Array::Indexer::Indexer(const Array *pArray) :
	_pArray(pArray), _dims(pArray->GetDimensions()), _offsetTarget(0)
{
	_pDim = _dims.begin();
}

bool Array::Indexer::InitIndices(Environment &env, const ValueList &valListIdx)
{
	_offsetTarget = 0;
	foreach_const (ValueList, pValueIdx, valListIdx) {
		const Value &valueIdx = *pValueIdx;
		if (_pDim == _dims.end()) {
			env.SetError(ERR_IndexError, "number of indices exceeds dimensions");
			return false;
		}
		if (valueIdx.Is_number()) {
			size_t idx = valueIdx.GetSizeT();
			if (idx >= _pDim->GetSize()) {
				env.SetError(ERR_OutOfRangeError, "index is out of range");
				return false;
			}
			_offsetTarget += idx * _pDim->GetStrides();
			_pDim++;
		} else if (valueIdx.IsListOrIterator()) {
			AutoPtr<Iterator> pIterator(valueIdx.CreateIterator(env));
			if (env.IsSignalled()) return false;
			std::unique_ptr<Generator> pGenerator(new Generator(_pDim->GetStrides()));
			Value valueIdxEach;
			while (pIterator->Next(env, valueIdxEach)) {
				if (valueIdxEach.Is_number()) {
					size_t idx = valueIdxEach.GetSizeT();
					if (idx >= _pDim->GetSize()) break;
					pGenerator->Add(idx);
				} else {
					env.SetError(ERR_ValueError, "index must be a number");
					return false;
				}
			}
			if (pGenerator->IsEmpty()) {
				env.SetError(ERR_ValueError, "no indices specified");
				return false;
			}
			if (_pGeneratorOwner.get() == nullptr) {
				_pGeneratorOwner.reset(new GeneratorOwner());
			}
			_pGeneratorOwner->push_back(pGenerator.release());
			_pDim++;
		} else if (valueIdx.IsInstanceOf(VTYPE_array)) {
			if (pValueIdx + 1 != valListIdx.end()) {
				env.SetError(ERR_IndexError, "boolean index can only be specified at the end");
				return false;
			}
			const Array *pArrayIdx = Object_array::GetObject(valueIdx)->GetArray();
			if (!pArrayIdx->IsElemType(Array::ETYPE_Boolean)) {
				env.SetError(ERR_IndexError, "array for indices must be boolean type");
				return false;
			}
			const Dimensions &dimsIdx = pArrayIdx->GetDimensions();
			if (!Dimensions::CheckSameShape(env, _pDim, _dims.end(), dimsIdx.begin(), dimsIdx.end())) return false;
			std::unique_ptr<Generator> pGenerator(new Generator(1));
			const Boolean *pElemIdx = dynamic_cast<const ArrayT<Boolean> *>(pArrayIdx)->GetPointer();
			size_t nElems = pArrayIdx->GetElemNum();
			if ((_pArray->IsRowMajor() && pArrayIdx->IsRowMajor()) || dimsIdx.size() < 2) {
				for (size_t offset = 0; offset < nElems; offset++, pElemIdx++) {
					if (*pElemIdx) pGenerator->Add(offset);
				}
			} else {
				size_t nRows = dimsIdx.GetRow().GetSize();
				size_t nCols = dimsIdx.GetCol().GetSize();
				size_t sizeMat = nRows * nCols;
				if (_pArray->IsRowMajor() && pArrayIdx->IsColMajor()) {
					size_t offset = 0;
					for (size_t offset1 = 0; offset1 < nElems; offset1 += sizeMat) {
						for (size_t iRow = 0; iRow < nRows; iRow++) {
							for (size_t offset2 = 0; offset2 < sizeMat; offset2 += nRows, offset++) {
								size_t offsetIdx = offset1 + offset2 + iRow;
								if (*(pElemIdx + offsetIdx)) pGenerator->Add(offset);
							}
						}
					}
				} else if (_pArray->IsColMajor() && pArrayIdx->IsRowMajor()) {
					for (size_t offset1 = 0; offset1 < nElems; offset1 += sizeMat) {
						for (size_t iRow = 0; iRow < nRows; iRow++) {
							for (size_t offset2 = 0; offset2 < sizeMat; offset2 += nRows, pElemIdx++) {
								if (*pElemIdx) pGenerator->Add(offset1 + offset2 + iRow);
							}
						}
					}
				} else { // _pArray->IsColMajor() && pArrayIdx->IsColMajor()
					for (size_t offset1 = 0; offset1 < nElems; offset1 += sizeMat) {
						for (size_t iRow = 0; iRow < nRows; iRow++) {
							for (size_t offset2 = 0; offset2 < sizeMat; offset2 += nRows) {
								size_t offsetIdx = offset1 + offset2 + iRow;
								if (*(pElemIdx + offsetIdx)) pGenerator->Add(offsetIdx);
							}
						}
					}
				}
			}
			if (_pGeneratorOwner.get() == nullptr) {
				_pGeneratorOwner.reset(new GeneratorOwner());
			}
			_pGeneratorOwner->push_back(pGenerator.release());
			_pDim = _dims.end();
		} else {
			env.SetError(ERR_ValueError, "index must be a number");
			return false;
		}
	}
	if (_pGeneratorOwner.get() != nullptr) _pGeneratorOwner->Reset();
	return true;
}

void Array::Indexer::MakeResultDimensions(Dimensions &dimsRtn)
{
	if (_pGeneratorOwner.get() == nullptr) {
		dimsRtn.reserve(std::distance(_pDim, _dims.end()));
	} else {
		dimsRtn.reserve(_pGeneratorOwner->size() + std::distance(_pDim, _dims.end()));
		foreach (GeneratorOwner, ppGenerator, *_pGeneratorOwner) {
			Generator *pGenerator = *ppGenerator;
			dimsRtn.push_back(Dimension(pGenerator->GetSize()));
		}
	}
	dimsRtn.insert(dimsRtn.end(), _pDim, _dims.end());
}

size_t Array::Indexer::GetElemNumUnit() const
{
	return (_pDim == _dims.end())? 1 : _pDim->GetSizeProd();
}

size_t Array::Indexer::GetStridesUnit() const
{
	return (_pDim == _dims.end())? 1 : (_pDim + 1 == _dims.end())? _pDim->GetStrides() : 1;
}

//-----------------------------------------------------------------------------
// Array::Indexer::Generator
//-----------------------------------------------------------------------------
bool Array::Indexer::Generator::Next()
{
	_pOffset++;
	if (_pOffset != _offsets.end()) return true;
	_pOffset = _offsets.begin();
	return false;
}

//-----------------------------------------------------------------------------
// Array::Indexer::GeneratorList
//-----------------------------------------------------------------------------
bool Array::Indexer::GeneratorList::IsEmptyGenerator() const
{
	foreach_const (GeneratorList, ppGenerator, *this) {
		const Generator *pGenerator = *ppGenerator;
		if (!pGenerator->IsEmpty()) return false;
	}
	return true;
}

void Array::Indexer::GeneratorList::Reset()
{
	foreach (GeneratorList, ppGenerator, *this) {
		Generator *pGenerator = *ppGenerator;
		pGenerator->Reset();
	}
}

size_t Array::Indexer::GeneratorList::CalcOffset() const
{
	size_t offset = 0;
	foreach_const (GeneratorList, ppGenerator, *this) {
		const Generator *pGenerator = *ppGenerator;
		offset += pGenerator->CalcOffset();
	}
	return offset;
}

bool Array::Indexer::GeneratorList::Next()
{
	foreach_reverse (GeneratorList, ppGenerator, *this) {
		Generator *pGenerator = *ppGenerator;
		if (pGenerator->Next()) return true;
	}
	return false;
}

//-----------------------------------------------------------------------------
// Array::Indexer::GeneratorOwner
//-----------------------------------------------------------------------------
Array::Indexer::GeneratorOwner::~GeneratorOwner()
{
	Clear();
}

void Array::Indexer::GeneratorOwner::Clear()
{
	foreach (GeneratorOwner, ppGenerator, *this) {
		Generator *pGenerator = *ppGenerator;
		delete pGenerator;
	}
	clear();
}

//-----------------------------------------------------------------------------
// ArrayList
//-----------------------------------------------------------------------------
const ArrayList ArrayList::Empty;

//-----------------------------------------------------------------------------
// ArrayOwner
//-----------------------------------------------------------------------------
ArrayOwner::ArrayOwner() : _cntRef(1)
{
}

ArrayOwner::~ArrayOwner()
{
	Clear();
}

void ArrayOwner::Clear()
{
	foreach (ArrayOwner, ppArray, *this) {
		Array::Delete(*ppArray);
	}
	clear();
}

//-----------------------------------------------------------------------------
// Function Pack
//-----------------------------------------------------------------------------
Array::UnaryFuncPack Array::unaryFuncPack_Pos =				{ "pos",			"+",			};
Array::UnaryFuncPack Array::unaryFuncPack_Neg =				{ "neg",			"-",			};
Array::BinaryFuncPack Array::binaryFuncPack_Add =			{ "add",			"+",	true	};
Array::BinaryFuncPack Array::binaryFuncPack_Sub =			{ "sub",			"-",	true	};
Array::BinaryFuncPack Array::binaryFuncPack_Mul =			{ "mul",			"*",	true	};
Array::BinaryFuncPack Array::binaryFuncPack_Div =			{ "div",			"/",	true	};
Array::BinaryFuncPack Array::binaryFuncPack_Mod =			{ "mod",			"%",	true	};
Array::BinaryFuncPack Array::binaryFuncPack_Pow =			{ "pow",			"**",	true	};
Array::BinaryFuncPack Array::binaryFuncPack_Dot =			{ "dot",			"|.|",	false	};
Array::BinaryFuncPack Array::binaryFuncPack_Eq =			{ "eq",				"==",	true	};
Array::BinaryFuncPack Array::binaryFuncPack_Ne =			{ "ne",				"!=",	true	};
Array::BinaryFuncPack Array::binaryFuncPack_Gt =			{ "gt",				">",	true	};
Array::BinaryFuncPack Array::binaryFuncPack_Lt =			{ "lt",				"<",	true	};
Array::BinaryFuncPack Array::binaryFuncPack_Ge =			{ "ge",				">=",	true	};
Array::BinaryFuncPack Array::binaryFuncPack_Le =			{ "le",				"<=",	true	};
Array::BinaryFuncPack Array::binaryFuncPack_And =			{ "and",			"&",	true	};
Array::BinaryFuncPack Array::binaryFuncPack_Or =			{ "or",				"|",	true	};
Array::BinaryFuncPack Array::binaryFuncPack_Xor =			{ "xor",			"^",	true	};
Array::BinaryFuncPack Array::binaryFuncPack_Shl =			{ "shl",			"<<",	true	};
Array::BinaryFuncPack Array::binaryFuncPack_Shr =			{ "shr",			">>",	true	};
Array::UnaryFuncPack Array::unaryFuncPack_Math_abs =		{ "math.abs",		"",				};
Array::UnaryFuncPack Array::unaryFuncPack_Math_acos =		{ "math.acos",		"",				};
Array::UnaryFuncPack Array::unaryFuncPack_Math_arg =		{ "math.arg",		"",				};
Array::UnaryFuncPack Array::unaryFuncPack_Math_asin =		{ "math.asin",		"",				};
Array::UnaryFuncPack Array::unaryFuncPack_Math_atan =		{ "math.atan",		"",				};
Array::UnaryFuncPack Array::unaryFuncPack_Math_ceil =		{ "math.ceil",		"",				};
Array::UnaryFuncPack Array::unaryFuncPack_Math_conj	=		{ "math.conj",		"",				};
Array::UnaryFuncPack Array::unaryFuncPack_Math_cos =		{ "math.cos",		"",				};
Array::UnaryFuncPack Array::unaryFuncPack_Math_cosh =		{ "math.cosh",		"",				};
Array::UnaryFuncPack Array::unaryFuncPack_Math_delta =		{ "math.delta",		"",				};
Array::UnaryFuncPack Array::unaryFuncPack_Math_exp =		{ "math.exp",		"",				};
Array::UnaryFuncPack Array::unaryFuncPack_Math_floor =		{ "math.floor",		"",				};
Array::UnaryFuncPack Array::unaryFuncPack_Math_imag =		{ "math.imag",		"",				};
Array::UnaryFuncPack Array::unaryFuncPack_Math_log =		{ "math.log",		"",				};
Array::UnaryFuncPack Array::unaryFuncPack_Math_log10 =		{ "math.log10",		"",				};
Array::UnaryFuncPack Array::unaryFuncPack_Math_norm =		{ "math.norm",		"",				};
Array::UnaryFuncPack Array::unaryFuncPack_Math_real =		{ "math.real",		"",				};
Array::UnaryFuncPack Array::unaryFuncPack_Math_relu =		{ "math.relu",		"",				};
Array::UnaryFuncPack Array::unaryFuncPack_Math_sigmoid =	{ "math.sigmoid",	"",				};
Array::UnaryFuncPack Array::unaryFuncPack_Math_sin =		{ "math.sin",		"",				};
Array::UnaryFuncPack Array::unaryFuncPack_Math_sinh =		{ "math.sinh",		"",				};
Array::UnaryFuncPack Array::unaryFuncPack_Math_sqrt =		{ "math.sqrt",		"",				};
Array::UnaryFuncPack Array::unaryFuncPack_Math_tan =		{ "math.tan",		"",				};
Array::UnaryFuncPack Array::unaryFuncPack_Math_tanh =		{ "math.tanh",		"",				};
Array::UnaryFuncPack Array::unaryFuncPack_Math_unitstep =	{ "math.unitstep",	"",				};

//-----------------------------------------------------------------------------
// Function Table
//-----------------------------------------------------------------------------
Array::InvertFuncTable Array::invertFuncTable = {
	{
		nullptr,
		nullptr,
		nullptr,
		nullptr,
		nullptr,
		nullptr,
		nullptr,
		nullptr,
		nullptr,
		nullptr,
		&InvertFuncTmpl<Half>,
		&InvertFuncTmpl<Float>,
		&InvertFuncTmpl<Double>,
		&InvertFuncTmpl<Complex>,
		nullptr,
	}
};

}
