//=============================================================================
// Gura class: array
//=============================================================================
#include "stdafx.h"

namespace Gura {

typedef Value (*ConstructorT)(Environment &env, Argument &arg);
typedef Value (*PropertyGetterT)(Environment &env, Array *pArraySelf);
typedef Value (*EvalIndexGetT)(Environment &env, const ValueList &valListIdx, Object_array *pObj);
typedef void (*EvalIndexSetT)(Environment &env, const ValueList &valListIdx, const Value &value, Object_array *pObj);
typedef Iterator *(*CreateIteratorT)(Array *pArray);
typedef Value (*MethodT)(Environment &env, Argument &arg, const Function *pFunc, Array *pArraySelf);
typedef bool (*CastToT)(Environment &env, Value &value, const Declaration &decl, const Array *pArraySelf);

static const char *helpDoc_en = R"**(

)**";

//-----------------------------------------------------------------------------
// utilities
//-----------------------------------------------------------------------------
Value CallPropertyGetter(Environment &env,
						 const PropertyGetterT propertyGetters[], Array *pArraySelf)
{
	PropertyGetterT pPropertyGetter = propertyGetters[pArraySelf->GetElemType()];
	if (pPropertyGetter == nullptr) {
		env.SetError(ERR_TypeError, "no property implemented");
		return Value::Nil;
	}
	return (*pPropertyGetter)(env, pArraySelf);
}

Value CallMethod(Environment &env, Argument &arg, const MethodT methods[],
				 const Function *pFunc, Array *pArraySelf)
{
	MethodT pMethod = methods[pArraySelf->GetElemType()];
	if (pMethod == nullptr) {
		env.SetError(ERR_TypeError, "no methods implemented");
		return Value::Nil;
	}
	return (*pMethod)(env, arg, pFunc, pArraySelf);
}

template<typename T_ElemResult, typename T_Elem>
ArrayT<T_ElemResult> *CalcSum(const ArrayT<T_Elem> *pArrayT,
							  Array::Dimensions::const_iterator pDimAxis)
{
	const Array::Dimensions &dims = pArrayT->GetDimensions();
	AutoPtr<ArrayT<T_ElemResult> > pArrayTResult(
		ArrayT<T_ElemResult>::Create(dims.begin(), pDimAxis, pDimAxis + 1, dims.end()));
	pArrayTResult->FillZero();
	const T_Elem *pElem = pArrayT->GetPointer();
	T_ElemResult *pElemResult = pArrayTResult->GetPointer();
	if (pDimAxis + 1 == dims.end()) {
		size_t cnt = pArrayT->GetElemNum() / pDimAxis->GetSize();
		while (cnt-- > 0) {
			for (size_t i = 0; i < pDimAxis->GetSize(); i++, pElem++) {
				*pElemResult += *pElem;
			}
			pElemResult++;
		}
	} else {
		size_t stride = pDimAxis->GetStride();
		size_t cnt = pArrayT->GetElemNum() / (pDimAxis->GetSize() * stride);
		while (cnt-- > 0) {
			for (size_t i = 0; i < pDimAxis->GetSize(); i++) {
				for (size_t j = 0; j < stride; j++, pElem++) {
					*(pElemResult + j) += *pElem;
				}
			}
			pElemResult += stride;
		}
	}
	return pArrayTResult.release();
}

template<typename T_ElemResult, typename T_Elem>
T_ElemResult CalcSumFlat(const ArrayT<T_Elem> *pArrayT)
{
	T_ElemResult rtn = 0;
	const T_Elem *p = pArrayT->GetPointer();
	for (size_t i = 0; i < pArrayT->GetElemNum(); i++, p++) {
		rtn += *p;
	}
	return rtn;
}

template<typename T_ElemResult, typename T_Elem>
ArrayT<T_ElemResult> *CalcAverage(const ArrayT<T_Elem> *pArrayT,
								  Array::Dimensions::const_iterator pDimAxis)
{
	ArrayT<T_ElemResult> *pArrayTResult = CalcSum<T_ElemResult, T_Elem>(pArrayT, pDimAxis);
	size_t n = pDimAxis->GetSize();
	if (n != 0) {
		T_ElemResult *p = pArrayTResult->GetPointer();
		for (size_t i = 0; i < pArrayTResult->GetElemNum(); i++, p++) {
			*p /= n;
		}
	}
	return pArrayTResult;
}

template<typename T_ElemResult, typename T_Elem>
T_ElemResult CalcAverageFlat(const ArrayT<T_Elem> *pArrayT)
{
	if (pArrayT->GetElemNum() == 0) return 0;
	return static_cast<T_ElemResult>(CalcSumFlat<T_ElemResult, T_Elem>(pArrayT) / pArrayT->GetElemNum());
}

template<>
Complex CalcAverageFlat(const ArrayT<Complex> *pArrayT)
{
	if (pArrayT->GetElemNum() == 0) return 0;
	return CalcSumFlat<Complex, Complex>(pArrayT) / static_cast<double>(pArrayT->GetElemNum());
}

//-----------------------------------------------------------------------------
// Object_array
//-----------------------------------------------------------------------------
Object *Object_array::Clone() const
{
	return nullptr;
}

String Object_array::ToString(bool exprFlag)
{
	return _pArray->ToString(exprFlag);
}

template<typename T_Elem>
Value EvalIndexGetTmpl(Environment &env, const ValueList &valListIdx, Object_array *pObj)
{
	if (valListIdx.empty()) return Value::Nil;
	ArrayT<T_Elem> *pArrayT = dynamic_cast<ArrayT<T_Elem> *>(pObj->GetArray());
	Array::Indexer indexer(pArrayT->GetDimensions());
	if (!indexer.InitIndices(env, valListIdx)) return Value::Nil;
	Value valueRtn;
	if (indexer.HasGenerator()) {
		Array::Dimensions dimsRtn;
		indexer.MakeResultDimensions(dimsRtn);
		AutoPtr<ArrayT<T_Elem> > pArrayTRtn(ArrayT<T_Elem>::Create(dimsRtn));
		size_t nElemsUnit = indexer.GetElemNumUnit();
		size_t bytesUnit = nElemsUnit * pArrayTRtn->GetElemBytes();
		const T_Elem *pElemTgt = pArrayT->GetPointer() + indexer.GetOffsetTarget();
		T_Elem *pElemDst = pArrayTRtn->GetPointer();
		do {
			::memcpy(pElemDst, pElemTgt + indexer.GenerateOffset(), bytesUnit);
			pElemDst += nElemsUnit;
		} while (indexer.NextGenerator());
		valueRtn = Value(new Object_array(env, pArrayTRtn.release()));
	} else if (indexer.IsTargetScalar()) {
		const T_Elem *pElemTgt = pArrayT->GetPointer() + indexer.GetOffsetTarget();
		valueRtn = Value(*pElemTgt);
	} else {
		AutoPtr<ArrayT<T_Elem> > pArrayTRtn(
			new ArrayT<T_Elem>(pArrayT->GetMemory().Reference(),
							   pArrayT->GetOffsetBase() + indexer.GetOffsetTarget()));
		Array::Dimensions dimsRtn;
		indexer.MakeResultDimensions(dimsRtn);
		pArrayTRtn->SetDimensions(dimsRtn);
		valueRtn = Value(new Object_array(env, pArrayTRtn.release()));
	}
	return valueRtn;
}

Value Object_array::EvalIndexGet(Environment &env, const ValueList &valListIdx)
{
	static const EvalIndexGetT evalIndexGetTbl[] = {
		nullptr,
		&EvalIndexGetTmpl<Boolean>,
		&EvalIndexGetTmpl<Int8>,
		&EvalIndexGetTmpl<UInt8>,
		&EvalIndexGetTmpl<Int16>,
		&EvalIndexGetTmpl<UInt16>,
		&EvalIndexGetTmpl<Int32>,
		&EvalIndexGetTmpl<UInt32>,
		&EvalIndexGetTmpl<Int64>,
		&EvalIndexGetTmpl<UInt64>,
		&EvalIndexGetTmpl<Half>,
		&EvalIndexGetTmpl<Float>,
		&EvalIndexGetTmpl<Double>,
		&EvalIndexGetTmpl<Complex>,
		//&EvalIndexGetTmpl<Value>,
	};
	return (*evalIndexGetTbl[GetArray()->GetElemType()])(env, valListIdx, this);
}

template<typename T_Elem>
void EvalIndexSetTmpl(Environment &env, const ValueList &valListIdx, const Value &value, Object_array *pObj)
{
	const bool complexFlag = (ArrayT<T_Elem>::ElemTypeThis == Array::ETYPE_Complex);
	ArrayT<T_Elem> *pArrayT = dynamic_cast<ArrayT<T_Elem> *>(pObj->GetArray());
	if (!pArrayT->PrepareModification(env.GetSignal())) return;
	if (valListIdx.empty()) {
		if (value.Is_number() || value.Is_boolean()) {
			FillDouble(pArrayT->GetPointer(), pArrayT->GetElemNum(), value.GetDouble());
		} else if (complexFlag && value.Is_complex()) {
			FillComplex(pArrayT->GetPointer(), pArrayT->GetElemNum(), value.GetComplex());
		} else if (value.IsListOrIterator()) {
			AutoPtr<Iterator> pIteratorSrc(value.CreateIterator(env.GetSignal()));
			if (env.IsSignalled()) return;
			AutoPtr<Iterator> pIterator(
				new Iterator_Flatten(pIteratorSrc.release(), Iterator_Flatten::MODE_DepthFirstSearch));
			Value valueEach;
			T_Elem *pElemDst = pArrayT->GetPointer();
			size_t nElems = pArrayT->GetElemNum();
			for (size_t i = 0; i < nElems; i++, pElemDst++) {
				if (!pIterator->Next(env, valueEach) ||
					!StoreValueAt(env, pElemDst, valueEach)) return;
			}
		} else {
			Array::SetError_UnacceptableValueAsElement(env, value);
		}
		return;
	}
	Array::Indexer indexer(pArrayT->GetDimensions());
	if (!indexer.InitIndices(env, valListIdx)) return;
	T_Elem *pElemTgt = pArrayT->GetPointer() + indexer.GetOffsetTarget();
	size_t nElemsUnit = indexer.GetElemNumUnit();
	if (value.Is_number() || value.Is_boolean()) {
		Double num = value.GetDouble();
		if (indexer.HasGenerator()) {
			do {
				FillDouble(pElemTgt + indexer.GenerateOffset(), nElemsUnit, num);
			} while (indexer.NextGenerator());
		} else {
			FillDouble(pElemTgt, nElemsUnit, num);
		}
	} else if (complexFlag && value.Is_complex()) {
		const Complex &num = value.GetComplex();
		if (indexer.HasGenerator()) {
			do {
				FillComplex(pElemTgt + indexer.GenerateOffset(), nElemsUnit, num);
			} while (indexer.NextGenerator());
		} else {
			FillComplex(pElemTgt, nElemsUnit, num);
		}
		
	} else if (value.IsListOrIterator()) {
		AutoPtr<Iterator> pIteratorSrc(value.CreateIterator(env.GetSignal()));
		if (env.IsSignalled()) return;
		AutoPtr<Iterator> pIterator(
			new Iterator_Flatten(pIteratorSrc.release(), Iterator_Flatten::MODE_DepthFirstSearch));
		Value valueEach;
		if (indexer.HasGenerator()) {
			do {
				T_Elem *pElemDst = pElemTgt + indexer.GenerateOffset();
				for (size_t i = 0; i < nElemsUnit; i++, pElemDst++) {
					if (!pIterator->Next(env, valueEach) ||
						!StoreValueAt(env, pElemDst, valueEach)) return;
				}
			} while (indexer.NextGenerator());
		} else {
			T_Elem *pElemDst = pElemTgt;
			for (size_t i = 0; i < nElemsUnit; i++, pElemDst++) {
				if (!pIterator->Next(env, valueEach) ||
					!StoreValueAt(env, pElemDst, valueEach)) return;
			}
		}
	} else if (value.IsInstanceOf(VTYPE_array)) {
		Array *pArraySrc = Object_array::GetObject(value)->GetArray();
		if (indexer.HasGenerator()) {
			char *pElemSrc = pArraySrc->GetPointerRaw();
			size_t nElemsSrc = pArraySrc->GetElemNum();
			size_t elemBytesSrc = pArraySrc->GetElemBytes();
			do {
				T_Elem *pElemDst = pElemTgt + indexer.GenerateOffset();
				size_t nElemsToCopy = ChooseMin(nElemsUnit, nElemsSrc);
				if (!Array::CopyElements(env, pElemDst, pArrayT->GetElemType(),
										 pElemSrc, pArraySrc->GetElemType(), nElemsToCopy)) return;
				nElemsSrc -= nElemsToCopy;
				if (nElemsSrc == 0) {
					pElemSrc = pArraySrc->GetPointerRaw();
					nElemsSrc = pArraySrc->GetElemNum();
				} else {
					pElemSrc += nElemsToCopy * elemBytesSrc;
				}
			} while (indexer.NextGenerator());
		} else {
			T_Elem *pElemDst = pElemTgt;
			char *pElemSrc = pArraySrc->GetPointerRaw();
			size_t nElemsSrc = pArraySrc->GetElemNum();
			size_t nElemsToCopy = ChooseMin(nElemsUnit, nElemsSrc);
			if (!Array::CopyElements(env, pElemDst, pArrayT->GetElemType(),
									 pElemSrc, pArraySrc->GetElemType(), nElemsToCopy)) return;
		}
	} else {
		Array::SetError_UnacceptableValueAsElement(env, value);
	}
}

void Object_array::EvalIndexSet(Environment &env, const ValueList &valListIdx, const Value &value)
{
	static const EvalIndexSetT evalIndexSetTbl[] = {
		nullptr,
		&EvalIndexSetTmpl<Boolean>,
		&EvalIndexSetTmpl<Int8>,
		&EvalIndexSetTmpl<UInt8>,
		&EvalIndexSetTmpl<Int16>,
		&EvalIndexSetTmpl<UInt16>,
		&EvalIndexSetTmpl<Int32>,
		&EvalIndexSetTmpl<UInt32>,
		&EvalIndexSetTmpl<Int64>,
		&EvalIndexSetTmpl<UInt64>,
		&EvalIndexSetTmpl<Half>,
		&EvalIndexSetTmpl<Float>,
		&EvalIndexSetTmpl<Double>,
		&EvalIndexSetTmpl<Complex>,
		//&EvalIndexSetTmpl<Value>,
	};
	(*evalIndexSetTbl[GetArray()->GetElemType()])(env, valListIdx, value, this);
}

template<typename T_Elem>
Iterator *CreateIteratorTmpl(Array *pArray)
{
	bool flatFlag = true;
	ArrayT<T_Elem> *pArrayT = dynamic_cast<ArrayT<T_Elem> *>(pArray);
	return new Iterator_ArrayT_Each<T_Elem>(pArrayT->Reference(), flatFlag);
}

Iterator *Object_array::CreateIterator(Signal &sig)
{
	static const CreateIteratorT createIteratorTbl[] = {
		nullptr,
		&CreateIteratorTmpl<Boolean>,
		&CreateIteratorTmpl<Int8>,
		&CreateIteratorTmpl<UInt8>,
		&CreateIteratorTmpl<Int16>,
		&CreateIteratorTmpl<UInt16>,
		&CreateIteratorTmpl<Int32>,
		&CreateIteratorTmpl<UInt32>,
		&CreateIteratorTmpl<Int64>,
		&CreateIteratorTmpl<UInt64>,
		&CreateIteratorTmpl<Half>,
		&CreateIteratorTmpl<Float>,
		&CreateIteratorTmpl<Double>,
		&CreateIteratorTmpl<Complex>,
		//&CreateIteratorTmpl<Value>,
	};
	return (*createIteratorTbl[GetArray()->GetElemType()])(GetArray());
}

//-----------------------------------------------------------------------------
// Object_array::PointerEx
//-----------------------------------------------------------------------------
Object_array::PointerEx::PointerEx(size_t offset, Object_array *pObjArray) :
	Pointer(offset), _pObjArray(pObjArray)
{
}

Object_array::PointerEx::PointerEx(const PointerEx &ptr) :
	Pointer(ptr), _pObjArray(dynamic_cast<Object_array *>(ptr._pObjArray->Reference()))
{
}

bool Object_array::PointerEx::StorePrepare(Signal &sig, size_t bytes)
{
	Memory &memory = GetMemory();
	if (_offset + bytes <= memory.GetSize()) return true;
	sig.SetError(ERR_OutOfRangeError, "pointer exceeds the range of memory");
	return false;
}

void Object_array::PointerEx::StoreBuffer(const void *buff, size_t bytes)
{
	Memory &memory = GetMemory();
	if (_offset >= memory.GetSize()) return;
	size_t bytesToCopy = ChooseMin(memory.GetSize() - _offset, bytes);
	if (buff != nullptr) ::memcpy(memory.GetPointer(_offset), buff, bytesToCopy);
	_offset += bytesToCopy;
}

const UChar *Object_array::PointerEx::ExtractPrepare(
	Signal &sig, size_t bytes, bool exceedErrorFlag)
{
	Memory &memory = GetMemory();
	if (_offset + bytes <= memory.GetSize()) {
		const UChar *p = reinterpret_cast<const UChar *>(memory.GetPointer(_offset));
		_offset += bytes;
		return p;
	}
	if (exceedErrorFlag) {
		sig.SetError(ERR_OutOfRangeError, "pointer exceeds the range of memory");
	}
	return nullptr;
}

Pointer *Object_array::PointerEx::Clone() const
{
	return new PointerEx(*this);
}

Object *Object_array::PointerEx::GetTarget() const
{
	return _pObjArray.get();
}

const UChar *Object_array::PointerEx::GetPointerC() const
{
	return reinterpret_cast<const UChar *>(GetMemory().GetPointer(_offset));
}

UChar *Object_array::PointerEx::GetWritablePointerC() const
{
	return reinterpret_cast<UChar *>(GetMemory().GetPointer(_offset));
}

size_t Object_array::PointerEx::GetEntireSize() const
{
	return GetMemory().GetSize();
}

bool Object_array::PointerEx::IsWritable() const
{
	return true;
}

//-----------------------------------------------------------------------------
// Implementation of properties
//-----------------------------------------------------------------------------
// array#elembytes
Gura_DeclareProperty_R(array, elembytes)
{
	SetPropAttr(VTYPE_number);
	AddHelp(
		Gura_Symbol(en),
		"Returns the size of each element in bytes.");
}

Gura_ImplementPropertyGetter(array, elembytes)
{
	Array *pArray = Object_array::GetObject(valueThis)->GetArray();
	return Value(pArray->GetElemBytes());
}

// array#elemtype
Gura_DeclareProperty_R(array, elemtype)
{
	SetPropAttr(VTYPE_symbol);
	AddHelp(
		Gura_Symbol(en),
		"Returns the typename of the elements as a `symbol` such as\n"
		"`` `boolean``,\n"
		"`` `int8``,\n"
		"`` `uint8``,\n"
		"`` `int16``,\n"
		"`` `uint16``,\n"
		"`` `int32``,\n"
		"`` `uint32``,\n"
		"`` `int64``,\n"
		"`` `uint64``,\n"
		"`` `half``,\n"
		"`` `float``,\n"
		"`` `double`` and\n"
		"`` `complex``.");
}

Gura_ImplementPropertyGetter(array, elemtype)
{
	Array *pArray = Object_array::GetObject(valueThis)->GetArray();
	return Value(Symbol::Add(pArray->GetElemTypeName()));
}

// array#memoryid
Gura_DeclareProperty_R(array, memoryid)
{
	SetPropAttr(VTYPE_string);
	AddHelp(
		Gura_Symbol(en),
		"Returns the id of memory.");
}

Gura_ImplementPropertyGetter(array, memoryid)
{
	Array *pArray = Object_array::GetObject(valueThis)->GetArray();
	return Value(pArray->GetMemory().MakeId());
}

// array#ndim
Gura_DeclareProperty_R(array, ndim)
{
	SetPropAttr(VTYPE_number);
	AddHelp(
		Gura_Symbol(en),
		"Returns the number of dimensions.");
}

Gura_ImplementPropertyGetter(array, ndim)
{
	Array *pArray = Object_array::GetObject(valueThis)->GetArray();
	return Value(pArray->GetDimensions().size());
}

// array#p
Gura_DeclareProperty_R(array, p)
{
	SetPropAttr(VTYPE_pointer);
	AddHelp(
		Gura_Symbol(en),
		"Returns the pointer through which you can inspect and modify the content of the array\n"
		"as a binary data.");
}

Gura_ImplementPropertyGetter(array, p)
{
	Object_array *pObj = Object_array::GetObject(valueThis);
	Pointer *pPointer = new Object_array::PointerEx(0, pObj->Reference());
	return Value(new Object_pointer(env, pPointer));
}

// array#shape
Gura_DeclareProperty_R(array, shape)
{
	SetPropAttr(VTYPE_number, FLAG_ListVar);
	AddHelp(
		Gura_Symbol(en),
		"Returns a list of sizes of each dimension.");
}

Gura_ImplementPropertyGetter(array, shape)
{
	Array *pArray = Object_array::GetObject(valueThis)->GetArray();
	Value value;
	Object_list *pObjList = value.InitAsList(env);
	Array::Dimensions &dims = pArray->GetDimensions();
	pObjList->Reserve(dims.size());
	foreach_const (Array::Dimensions, pDim, dims) {
		pObjList->AddFast(Value(pDim->GetSize()));
	}
	pObjList->SetValueType(VTYPE_number);
	return value;
}

// array#size
Gura_DeclareProperty_R(array, size)
{
	SetPropAttr(VTYPE_number);
	AddHelp(
		Gura_Symbol(en),
		"Returns the total number of elements.");
}

Gura_ImplementPropertyGetter(array, size)
{
	Array *pArray = Object_array::GetObject(valueThis)->GetArray();
	return Value(pArray->GetElemNum());
}

// array#T
Gura_DeclareProperty_R(array, T)
{
	SetPropAttr(VTYPE_array);
	AddHelp(
		Gura_Symbol(en),
		"Return an array with its row and column being tranposed."
		);
}

template<typename T_Elem>
Value PropertyGetter_T(Environment &env, Array *pArraySelf)
{
	ArrayT<T_Elem> *pArrayT = dynamic_cast<ArrayT<T_Elem> *>(pArraySelf);
	return Value(new Object_array(env, pArrayT->Transpose()));
}

Gura_ImplementPropertyGetter(array, T)
{
	static const PropertyGetterT propertyGetters[] = {
		nullptr,
		&PropertyGetter_T<Boolean>,
		&PropertyGetter_T<Int8>,
		&PropertyGetter_T<UInt8>,
		&PropertyGetter_T<Int16>,
		&PropertyGetter_T<UInt16>,
		&PropertyGetter_T<Int32>,
		&PropertyGetter_T<UInt32>,
		&PropertyGetter_T<Int64>,
		&PropertyGetter_T<UInt64>,
		&PropertyGetter_T<Half>,
		&PropertyGetter_T<Float>,
		&PropertyGetter_T<Double>,
		&PropertyGetter_T<Complex>,
		//&PropertyGetter_T<Value>,
	};
	return CallPropertyGetter(env, propertyGetters, Object_array::GetObject(valueThis)->GetArray());
}

//-----------------------------------------------------------------------------
// Implementation of functions
//-----------------------------------------------------------------------------
// array(src?, elemtype?:symbol) {block?}
Gura_DeclareFunction(array)
{
	SetFuncAttr(VTYPE_array_at_double, RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "src", VTYPE_any, OCCUR_ZeroOrOnce);
	DeclareArg(env, "elemtype", VTYPE_symbol, OCCUR_ZeroOrOnce);
	SetClassToConstruct(env.LookupClass(VTYPE_array));
	DeclareBlock(OCCUR_ZeroOrOnce);
	AddHelp(
		Gura_Symbol(en),
		"Creates an `array` instance with elements of type `double` from a `list` or an `iterator` specified in the argument `src`,\n"
		"or elements described in a block. Below are examples:\n"
		"\n"
		"    array([[0, 1, 2], [3, 4, 5]])\n"
		"    array {{0, 1, 2}, {3, 4, 5}}\n"
		"\n"
		"Specifying the argument `elemtype` would create an array of other type than `double`.\n"
		"\n"
		"Available symbols for `elemtype` are as follows:\n"
		"\n"
		"- `` `boolean``\n"
		"- `` `int8``\n"
		"- `` `uint8``\n"
		"- `` `int16``\n"
		"- `` `uint16``\n"
		"- `` `int32``\n"
		"- `` `uint32``\n"
		"- `` `int64``\n"
		"- `` `uint64``\n"
		"- `` `half``\n"
		"- `` `float``\n"
		"- `` `double``\n"
		"- `` `complex``\n"
		"\n"
		GURA_HELPTEXT_BLOCK_en("array", "array"));
}

Gura_ImplementFunction(array)
{
	static const ConstructorT constructorTbl[] = {
		nullptr,
		&Object_arrayT<Boolean>::Constructor,
		&Object_arrayT<Int8>::Constructor,
		&Object_arrayT<UInt8>::Constructor,
		&Object_arrayT<Int16>::Constructor,
		&Object_arrayT<UInt16>::Constructor,
		&Object_arrayT<Int32>::Constructor,
		&Object_arrayT<UInt32>::Constructor,
		&Object_arrayT<Int64>::Constructor,
		&Object_arrayT<UInt64>::Constructor,
		&Object_arrayT<Half>::Constructor,
		&Object_arrayT<Float>::Constructor,
		&Object_arrayT<Double>::Constructor,
		&Object_arrayT<Complex>::Constructor,
		//&Object_arrayT<Value>::Constructor,
	};
	Array::ElemType elemType = arg.IsValid(1)?
		Array::SymbolToElemTypeWithError(env, arg.GetSymbol(1)) : Array::ETYPE_Double;
	if (env.IsSignalled()) return Value::Nil;
	return (*constructorTbl[elemType])(env, arg);
}

// @@ {block?}
Gura_DeclareFunctionAlias(at_at, "@@")
{
	SetFuncAttr(VTYPE_array_at_double, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_Once);
	AddHelp(
		Gura_Symbol(en),
		"Creates an `array@double` instance that contains elements described in the block.\n"
		"The example below creates an array with a dimension of 2 rows and 3 columns:\n"
		"\n"
		"    @@{{0, 1, 2}, {3, 4, 5}}\n");
}

Gura_ImplementFunction(at_at)
{
	AutoPtr<ArrayT<Double> > pArrayT(ArrayT<Double>::CreateFromExpr(env, arg.GetBlockCooked(env)));
	if (pArrayT.IsNull()) return Value::Nil;
	return Value(new Object_array(env, pArrayT.release()));
}

//-----------------------------------------------------------------------------
// Implementation of methods
//-----------------------------------------------------------------------------
// array#average(axis?:number) {block?}
Gura_DeclareMethod(array, average)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "axis", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
	AddHelp(
		Gura_Symbol(en),
		"Calculates an average value of elements in the array.\n"
		"\n"
		GURA_HELPTEXT_BLOCK_en("array", "array"));
}

template<typename T_ElemResult, typename T_Elem>
Value Method_average(Environment &env, Argument &arg, const Function *pFunc, Array *pArraySelf)
{
	const ArrayT<T_Elem> *pArrayT = dynamic_cast<ArrayT<T_Elem> *>(pArraySelf);
	Value valueRtn;
	if (arg.IsValid(0)) {
		size_t axis = arg.GetSizeT(0);
		const Array::Dimensions &dims = pArrayT->GetDimensions();
		if (axis >= dims.size()) {
			env.SetError(ERR_OutOfRangeError, "specified axis is out of range");
			return Value::Nil;
		} else if (axis == 0 && dims.size() == 1) {
			valueRtn = Value(CalcAverageFlat<T_ElemResult, T_Elem>(pArrayT));
		} else {
			Array::Dimensions::const_iterator pDimAxis = dims.begin() + axis;
			ArrayT<T_ElemResult> *pArrayTResult = CalcAverage<T_ElemResult, T_Elem>(pArrayT, pDimAxis);
			if (pArrayTResult == nullptr) return Value::Nil;
			valueRtn = Value(new Object_array(env, pArrayTResult));
		}
	} else {
		valueRtn = Value(CalcAverageFlat<T_ElemResult, T_Elem>(pArrayT));
	}
	return pFunc->ReturnValue(env, arg, valueRtn);
}

Gura_ImplementMethod(array, average)
{
	static const MethodT methods[] = {
		nullptr,
		&Method_average<UInt32, Boolean>,
		&Method_average<Int8, Int8>,
		&Method_average<UInt8, UInt8>,
		&Method_average<Int16, Int16>,
		&Method_average<UInt16, UInt16>,
		&Method_average<Int32, Int32>,
		&Method_average<UInt32, UInt32>,
		&Method_average<Int64, Int64>,
		&Method_average<UInt64, UInt64>,
		&Method_average<Half, Half>,
		&Method_average<Float, Float>,
		&Method_average<Double, Double>,
		&Method_average<Complex, Complex>,
		//&Method_average<Value, Value>,
	};
	return CallMethod(env, arg, methods, this, Object_array::GetObjectThis(arg)->GetArray());
}

// array.dot(a:array, b:array):static:map {block?}
Gura_DeclareClassMethod(array, dot)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "a", VTYPE_array);
	DeclareArg(env, "b", VTYPE_array);
	DeclareBlock(OCCUR_ZeroOrOnce);
	AddHelp(
		Gura_Symbol(en),
		"Calculates a dot product between two arrays that have one or two dimensions.\n"
		"\n"
		GURA_HELPTEXT_BLOCK_en("array", "array"));
}

Gura_ImplementClassMethod(array, dot)
{
	const Array *pArrayL = Object_array::GetObject(arg, 0)->GetArray();
	const Array *pArrayR = Object_array::GetObject(arg, 1)->GetArray();
	Value valResult = Array::Dot(env, pArrayL, pArrayR);
	if (env.IsSignalled()) return Value::Nil;
	return ReturnValue(env, arg, valResult);
}

// array#dump():void
Gura_DeclareMethod(array, dump)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "stream", VTYPE_stream, OCCUR_ZeroOrOnce);
	DeclareAttr(Gura_Symbol(upper));
	AddHelp(
		Gura_Symbol(en),
		"Prints out a binary dump of the array's content.\n"
		);
}

template<typename T_Elem>
Value Method_dump(Environment &env, Argument &arg, const Function *pFunc, Array *pArraySelf)
{
	const ArrayT<T_Elem> *pArrayT = dynamic_cast<ArrayT<T_Elem> *>(pArraySelf);
	Signal &sig = env.GetSignal();
	bool upperFlag = arg.IsSet(Gura_Symbol(upper));
	Stream *pStream = arg.IsValid(0)?
		&Object_stream::GetObject(arg, 0)->GetStream() : env.GetConsole();
	pArrayT->Dump(sig, *pStream, upperFlag);
	return Value::Nil;
}

Gura_ImplementMethod(array, dump)
{
	static const MethodT methods[] = {
		nullptr,
		&Method_dump<Boolean>,
		&Method_dump<Int8>,
		&Method_dump<UInt8>,
		&Method_dump<Int16>,
		&Method_dump<UInt16>,
		&Method_dump<Int32>,
		&Method_dump<UInt32>,
		&Method_dump<Int64>,
		&Method_dump<UInt64>,
		&Method_dump<Half>,
		&Method_dump<Float>,
		&Method_dump<Double>,
		&Method_dump<Complex>,
		//&Method_dump<Value>,
	};
	return CallMethod(env, arg, methods, this, Object_array::GetObjectThis(arg)->GetArray());
}

// array#each():[flat] {block?}
Gura_DeclareMethod(array, each)
{
	SetFuncAttr(VTYPE_iterator, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
	DeclareAttr(Gura_Symbol(flat));
	AddHelp(
		Gura_Symbol(en),
		"Creates an iterator that iterates each element in the array.\n"
		"\n"
		GURA_HELPTEXT_ITERATOR_en()
		"\n"
		"The block parameter is `|elem:number, idx:number|`\n"
		"where `elem` is the element value.\n"
		);
}

template<typename T_Elem>
Value Method_each(Environment &env, Argument &arg, const Function *pFunc, Array *pArraySelf)
{
	const ArrayT<T_Elem> *pArrayT = dynamic_cast<ArrayT<T_Elem> *>(pArraySelf);
	AutoPtr<Iterator> pIterator(new Iterator_ArrayT_Each<T_Elem>(
									pArrayT->Reference(), arg.IsSet(Gura_Symbol(flat))));
	return pFunc->ReturnIterator(env, arg, pIterator.release());
}

Gura_ImplementMethod(array, each)
{
	static const MethodT methods[] = {
		nullptr,
		&Method_each<Boolean>,
		&Method_each<Int8>,
		&Method_each<UInt8>,
		&Method_each<Int16>,
		&Method_each<UInt16>,
		&Method_each<Int32>,
		&Method_each<UInt32>,
		&Method_each<Int64>,
		&Method_each<UInt64>,
		&Method_each<Half>,
		&Method_each<Float>,
		&Method_each<Double>,
		&Method_each<Complex>,
		//&Method_each<Value>,
	};
	return CallMethod(env, arg, methods, this, Object_array::GetObjectThis(arg)->GetArray());
}

// array#elemcast(elemtype:symbol) {block?}
Gura_DeclareMethod(array, elemcast)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "elemtype", VTYPE_symbol);
	DeclareBlock(OCCUR_ZeroOrOnce);
	AddHelp(
		Gura_Symbol(en),
		"Cast value type of contained elements.\n"
		"\n"
		"Available symbols for `elemtype` are as follows:\n"
		"\n"
		"- `` `boolean``\n"
		"- `` `int8``\n"
		"- `` `uint8``\n"
		"- `` `int16``\n"
		"- `` `uint16``\n"
		"- `` `int32``\n"
		"- `` `uint32``\n"
		"- `` `int64``\n"
		"- `` `uint64``\n"
		"- `` `half``\n"
		"- `` `float``\n"
		"- `` `double``\n"
		"- `` `complex``\n"
		"\n"
		GURA_HELPTEXT_BLOCK_en("array", "array"));
}

Gura_ImplementMethod(array, elemcast)
{
	Array *pArraySelf = Object_array::GetObjectThis(arg)->GetArray();
	Array::ElemType elemType = Array::SymbolToElemTypeWithError(env, arg.GetSymbol(0));
	if (env.IsSignalled()) return Value::Nil;
	Value value;
	if (pArraySelf->GetElemType() == elemType) {
		value = Value(new Object_array(env, pArraySelf->Clone()));
	} else {
		AutoPtr<Array> pArrayDst(Array::Create(elemType, pArraySelf->GetDimensions()));
		if (!Array::CopyElements(env, pArrayDst.get(), pArraySelf)) return Value::Nil;
		value = Value(new Object_array(env, pArrayDst.release()));
	}
	return ReturnValue(env, arg, value);
}

// array#fill(value:number):void
Gura_DeclareMethod(array, fill)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "value", VTYPE_number, OCCUR_Once);
	AddHelp(
		Gura_Symbol(en),
		"Fills array with a specified value.\n"
		);
}

template<typename T_Elem>
Value Method_fill(Environment &env, Argument &arg, const Function *pFunc, Array *pArraySelf)
{
	ArrayT<T_Elem> *pArrayT = dynamic_cast<ArrayT<T_Elem> *>(pArraySelf);
	if (!pArrayT->PrepareModification(env.GetSignal())) return Value::Nil;
	pArrayT->Fill(static_cast<T_Elem>(arg.GetNumber(0)));
	return Value::Nil;
}

Gura_ImplementMethod(array, fill)
{
	static const MethodT methods[] = {
		nullptr,
		&Method_fill<Boolean>,
		&Method_fill<Int8>,
		&Method_fill<UInt8>,
		&Method_fill<Int16>,
		&Method_fill<UInt16>,
		&Method_fill<Int32>,
		&Method_fill<UInt32>,
		&Method_fill<Int64>,
		&Method_fill<UInt64>,
		&Method_fill<Half>,
		&Method_fill<Float>,
		&Method_fill<Double>,
		&Method_fill<Complex>,
		//&Method_fill<Value>,
	};
	return CallMethod(env, arg, methods, this, Object_array::GetObjectThis(arg)->GetArray());
}

// array#flatten() {block?}
Gura_DeclareMethod(array, flatten)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
	AddHelp(
		Gura_Symbol(en),
		"Returns an `array` instance as a result that\n"
		"has flattened elements in the target `array`.\n"
		"\n"
		GURA_HELPTEXT_BLOCK_en("array", "array"));
}

template<typename T_Elem>
Value Method_flatten(Environment &env, Argument &arg, const Function *pFunc, Array *pArraySelf)
{
	ArrayT<T_Elem> *pArrayT = dynamic_cast<ArrayT<T_Elem> *>(pArraySelf);
	AutoPtr<Array> pArrayTRtn(pArrayT->Flatten());
	return pFunc->ReturnValue(env, arg, Value(new Object_array(env, pArrayTRtn.release())));
}

Gura_ImplementMethod(array, flatten)
{
	static const MethodT methods[] = {
		nullptr,
		&Method_flatten<Boolean>,
		&Method_flatten<Int8>,
		&Method_flatten<UInt8>,
		&Method_flatten<Int16>,
		&Method_flatten<UInt16>,
		&Method_flatten<Int32>,
		&Method_flatten<UInt32>,
		&Method_flatten<Int64>,
		&Method_flatten<UInt64>,
		&Method_flatten<Half>,
		&Method_flatten<Float>,
		&Method_flatten<Double>,
		&Method_flatten<Complex>,
		//&Method_flatten<Value>,
	};
	return CallMethod(env, arg, methods, this, Object_array::GetObjectThis(arg)->GetArray());
}

// array#head(n:number):map {block?}
Gura_DeclareMethod(array, head)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "n", VTYPE_number, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
	AddHelp(
		Gura_Symbol(en),
		"Returns an `array` instance as a result that\n"
		"has extracted `n` elements from the beginning of the target `array`.\n"
		"\n"
		GURA_HELPTEXT_BLOCK_en("array", "array"));
}

template<typename T_Elem>
Value Method_head(Environment &env, Argument &arg, const Function *pFunc, Array *pArraySelf)
{
	const ArrayT<T_Elem> *pArrayT = dynamic_cast<ArrayT<T_Elem> *>(pArraySelf);
	Signal &sig = env.GetSignal();
	size_t n = arg.GetSizeT(0);
	AutoPtr<ArrayT<T_Elem> > pArrayTRtn(pArrayT->Head(sig, n));
	if (pArrayTRtn.IsNull()) return Value::Nil;
	Value value(new Object_array(env, pArrayTRtn.release()));
	return pFunc->ReturnValue(env, arg, value);
}

Gura_ImplementMethod(array, head)
{
	static const MethodT methods[] = {
		nullptr,
		&Method_head<Boolean>,
		&Method_head<Int8>,
		&Method_head<UInt8>,
		&Method_head<Int16>,
		&Method_head<UInt16>,
		&Method_head<Int32>,
		&Method_head<UInt32>,
		&Method_head<Int64>,
		&Method_head<UInt64>,
		&Method_head<Half>,
		&Method_head<Float>,
		&Method_head<Double>,
		&Method_head<Complex>,
		//&Method_head<Value>,
	};
	return CallMethod(env, arg, methods, this, Object_array::GetObjectThis(arg)->GetArray());
}

// array#invert(eps?:number) {block?}
Gura_DeclareMethod(array, invert)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "eps", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
	AddHelp(
		Gura_Symbol(en),
		"Returns an `array` instance as a result that\n"
		"has elements of inverted matrix of the target `array`."
		"\n"
		GURA_HELPTEXT_BLOCK_en("array", "array"));
}

template<typename T_Elem>
Value Method_invert(Environment &env, Argument &arg, const Function *pFunc, Array *pArraySelf)
{
	const ArrayT<T_Elem> *pArrayT = dynamic_cast<ArrayT<T_Elem> *>(pArraySelf);
	Signal &sig = env.GetSignal();
	Double epsilon = arg.IsValid(0)? arg.GetDouble(0) : 1.0e-6;
	AutoPtr<Array> pArrayRtn(Array::Invert(sig, pArrayT, epsilon));
	if (pArrayRtn.IsNull()) return Value::Nil;
	Value value(new Object_array(env, pArrayRtn.release()));
	return pFunc->ReturnValue(env, arg, value);
}

Gura_ImplementMethod(array, invert)
{
	static const MethodT methods[] = {
		nullptr,
		&Method_invert<Boolean>,
		&Method_invert<Int8>,
		&Method_invert<UInt8>,
		&Method_invert<Int16>,
		&Method_invert<UInt16>,
		&Method_invert<Int32>,
		&Method_invert<UInt32>,
		&Method_invert<Int64>,
		&Method_invert<UInt64>,
		&Method_invert<Half>,
		&Method_invert<Float>,
		&Method_invert<Double>,
		&Method_invert<Complex>,
		//&Method_invert<Value>,
	};
	return CallMethod(env, arg, methods, this, Object_array::GetObjectThis(arg)->GetArray());
}

// array#iselemsame(array:array)
Gura_DeclareMethod(array, iselemsame)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "array", VTYPE_array);
	AddHelp(
		Gura_Symbol(en),
		"Returns `true` if the target `array` instance has the same elements\n"
		"with the specified `array`.\n");
}

Gura_ImplementMethod(array, iselemsame)
{
	Array *pArray = Object_array::GetObjectThis(arg)->GetArray();
	Array *pArrayCmp = Object_array::GetObject(arg, 0)->GetArray();
	return Value(pArray->HasSameElements(*pArrayCmp));
}

// array#issquare()
Gura_DeclareMethod(array, issquare)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	AddHelp(
		Gura_Symbol(en),
		"Returns `true` if the target `array` consists square matrices.");
}

Gura_ImplementMethod(array, issquare)
{
	Array *pArray = Object_array::GetObjectThis(arg)->GetArray();
	return Value(pArray->IsSquare());
}

// array#offset(n:number):map {block?}
Gura_DeclareMethod(array, offset)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "n", VTYPE_number, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
	AddHelp(
		Gura_Symbol(en),
		"Returns an `array` instance as a result that\n"
		"has extracted elements of the target `array` after skipping its first `n` elements.\n"
		"\n"
		GURA_HELPTEXT_BLOCK_en("array", "array"));
}

template<typename T_Elem>
Value Method_offset(Environment &env, Argument &arg, const Function *pFunc, Array *pArraySelf)
{
	const ArrayT<T_Elem> *pArrayT = dynamic_cast<ArrayT<T_Elem> *>(pArraySelf);
	Signal &sig = env.GetSignal();
	size_t n = arg.GetSizeT(0);
	AutoPtr<ArrayT<T_Elem> > pArrayTRtn(pArrayT->Offset(sig, n));
	if (pArrayTRtn.IsNull()) return Value::Nil;
	Value value(new Object_array(env, pArrayTRtn.release()));
	return pFunc->ReturnValue(env, arg, value);
}

Gura_ImplementMethod(array, offset)
{
	static const MethodT methods[] = {
		nullptr,
		&Method_offset<Boolean>,
		&Method_offset<Int8>,
		&Method_offset<UInt8>,
		&Method_offset<Int16>,
		&Method_offset<UInt16>,
		&Method_offset<Int32>,
		&Method_offset<UInt32>,
		&Method_offset<Int64>,
		&Method_offset<UInt64>,
		&Method_offset<Half>,
		&Method_offset<Float>,
		&Method_offset<Double>,
		&Method_offset<Complex>,
		//&Method_offset<Value>,
	};
	return CallMethod(env, arg, methods, this, Object_array::GetObjectThis(arg)->GetArray());
}

// array#paste(offset:number, src:array):map:void
Gura_DeclareMethod(array, paste)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "offset", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "src", VTYPE_array, OCCUR_Once);
	AddHelp(
		Gura_Symbol(en),
		"Pastes elements of `src` into the target `array` instance.\n"
		"\n"
		"The argument `offset` specifies the posision where elements are pasted in\n"
		);
}

template<typename T_Elem>
Value Method_paste(Environment &env, Argument &arg, const Function *pFunc, Array *pArraySelf)
{
	ArrayT<T_Elem> *pArrayT = dynamic_cast<ArrayT<T_Elem> *>(pArraySelf);
	Signal &sig = env.GetSignal();
	size_t offset = arg.GetSizeT(0);
	const Array *pArraySrc = Object_array::GetObject(arg, 1)->GetArray();
	if (pArraySrc->GetElemType() != ArrayT<T_Elem>::ElemTypeThis) {
		sig.SetError(ERR_TypeError,
					 "source and destination array must cosist of elements of the same type");
		return Value::Nil;
	}
	const ArrayT<T_Elem> *pArrayTSrc = dynamic_cast<const ArrayT<T_Elem> *>(pArraySrc);
	if (!pArrayT->PrepareModification(sig)) return Value::Nil;
	pArrayT->Paste(sig, offset, pArrayTSrc);
	return Value::Nil;
}

Gura_ImplementMethod(array, paste)
{
	static const MethodT methods[] = {
		nullptr,
		&Method_paste<Boolean>,
		&Method_paste<Int8>,
		&Method_paste<UInt8>,
		&Method_paste<Int16>,
		&Method_paste<UInt16>,
		&Method_paste<Int32>,
		&Method_paste<UInt32>,
		&Method_paste<Int64>,
		&Method_paste<UInt64>,
		&Method_paste<Half>,
		&Method_paste<Float>,
		&Method_paste<Double>,
		&Method_paste<Complex>,
		//&Method_paste<Value>,
	};
	return CallMethod(env, arg, methods, this, Object_array::GetObjectThis(arg)->GetArray());
}

// array#reshape(dims[]:number:nil) {block?}
Gura_DeclareMethod(array, reshape)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "dims", VTYPE_number, OCCUR_Once, FLAG_ListVar | FLAG_Nil);
	DeclareBlock(OCCUR_ZeroOrOnce);
	AddHelp(
		Gura_Symbol(en),
		"Returns an `array` instance as a result that\n"
		"has reshaped the target `array` according to a list of\n"
		"dimension size specified by `dims`.\n"
		"\n"
		"Below are examples:\n"
		"\n"
		"    x = array(1..24)\n"
		"    a = x.reshape([6, 4])    // a is an array of 6x4.\n"
		"    b = x.reshape([2, 3, 4]) // b is an array of 2x3x4.\n"
		"\n"
		"A value of `nil` in the list of dimension means it would be calculated from the whole size\n"
		"and other dimension sizes. Only one `nil` is allowed to exist.\n"
		"\n"
		"    x = array(1..24)\n"
		"    b = x.reshape([2, nil, 4]) // b is an array of 2x3x4.\n"
		"\n"
		GURA_HELPTEXT_BLOCK_en("array", "array"));
}

template<typename T_Elem>
Value Method_reshape(Environment &env, Argument &arg, const Function *pFunc, Array *pArraySelf)
{
	Signal &sig = env.GetSignal();
	ArrayT<T_Elem> *pArrayT = dynamic_cast<ArrayT<T_Elem> *>(pArraySelf);
	AutoPtr<Array> pArrayTRtn(pArrayT->Reshape(sig, arg.GetList(0)));
	if (pArrayTRtn.IsNull()) return Value::Nil;
	return pFunc->ReturnValue(env, arg, Value(new Object_array(env, pArrayTRtn.release())));
}

Gura_ImplementMethod(array, reshape)
{
	static const MethodT methods[] = {
		nullptr,
		&Method_reshape<Boolean>,
		&Method_reshape<Int8>,
		&Method_reshape<UInt8>,
		&Method_reshape<Int16>,
		&Method_reshape<UInt16>,
		&Method_reshape<Int32>,
		&Method_reshape<UInt32>,
		&Method_reshape<Int64>,
		&Method_reshape<UInt64>,
		&Method_reshape<Half>,
		&Method_reshape<Float>,
		&Method_reshape<Double>,
		&Method_reshape<Complex>,
		//&Method_reshape<Value>,
	};
	return CallMethod(env, arg, methods, this, Object_array::GetObjectThis(arg)->GetArray());
}

// array#roundoff(threshold?:number) {block?}
Gura_DeclareMethod(array, roundoff)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "threshold", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
	AddHelp(
		Gura_Symbol(en),
		"Returns an `array` instance as a result that\n"
		"has rounded off elements less than `threshold` to zero in the target `array`.\n"
		"The default value for `threshold` is `1.0e-6` when omitted.\n"
		"\n"
		GURA_HELPTEXT_BLOCK_en("array", "array"));
}

template<typename T_Elem>
Value Method_roundoff(Environment &env, Argument &arg, const Function *pFunc, Array *pArraySelf)
{
	double threshold = arg.IsValid(0)? arg.GetDouble(0) : 1.e-6;
	ArrayT<T_Elem> *pArrayT = dynamic_cast<ArrayT<T_Elem> *>(pArraySelf);
	AutoPtr<Array> pArrayTRtn(pArrayT->RoundOff(threshold));
	return pFunc->ReturnValue(env, arg, Value(new Object_array(env, pArrayTRtn.release())));
}

Gura_ImplementMethod(array, roundoff)
{
	static const MethodT methods[] = {
		nullptr,
		&Method_roundoff<Boolean>,
		&Method_roundoff<Int8>,
		&Method_roundoff<UInt8>,
		&Method_roundoff<Int16>,
		&Method_roundoff<UInt16>,
		&Method_roundoff<Int32>,
		&Method_roundoff<UInt32>,
		&Method_roundoff<Int64>,
		&Method_roundoff<UInt64>,
		&Method_roundoff<Half>,
		&Method_roundoff<Float>,
		&Method_roundoff<Double>,
		&Method_roundoff<Complex>,
		//&Method_roundoff<Value>,
	};
	return CallMethod(env, arg, methods, this, Object_array::GetObjectThis(arg)->GetArray());
}

// array#sum(axis?:number) {block?}
Gura_DeclareMethod(array, sum)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "axis", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
	AddHelp(
		Gura_Symbol(en),
		"Calculates a summation value of elements in the target `array`.\n");
}

template<typename T_ElemResult, typename T_Elem>
Value Method_sum(Environment &env, Argument &arg, const Function *pFunc, Array *pArraySelf)
{
	const ArrayT<T_Elem> *pArrayT = dynamic_cast<ArrayT<T_Elem> *>(pArraySelf);
	Value valueRtn;
	if (arg.IsValid(0)) {
		size_t axis = arg.GetSizeT(0);
		const Array::Dimensions &dims = pArrayT->GetDimensions();
		if (axis >= dims.size()) {
			env.SetError(ERR_OutOfRangeError, "specified axis is out of range");
			return Value::Nil;
		} else if (axis == 0 && dims.size() == 1) {
			valueRtn = Value(CalcSumFlat<T_ElemResult, T_Elem>(pArrayT));
		} else {
			Array::Dimensions::const_iterator pDimAxis = dims.begin() + axis;
			ArrayT<T_ElemResult> *pArrayTResult = CalcSum<T_ElemResult, T_Elem>(pArrayT, pDimAxis);
			if (pArrayTResult == nullptr) return Value::Nil;
			valueRtn = Value(new Object_array(env, pArrayTResult));
		}
	} else {
		valueRtn = Value(CalcSumFlat<T_ElemResult, T_Elem>(pArrayT));
	}
	return pFunc->ReturnValue(env, arg, valueRtn);
}

Gura_ImplementMethod(array, sum)
{
	static const MethodT methods[] = {
		nullptr,
		&Method_sum<UInt32, Boolean>,
		&Method_sum<Int8, Int8>,
		&Method_sum<UInt8, UInt8>,
		&Method_sum<Int16, Int16>,
		&Method_sum<UInt16, UInt16>,
		&Method_sum<Int32, Int32>,
		&Method_sum<UInt32, UInt32>,
		&Method_sum<Int64, Int64>,
		&Method_sum<UInt64, UInt64>,
		&Method_sum<Half, Half>,
		&Method_sum<Float, Float>,
		&Method_sum<Double, Double>,
		&Method_sum<Complex, Complex>,
		//&Method_sum<Value, Value>,
	};
	return CallMethod(env, arg, methods, this, Object_array::GetObjectThis(arg)->GetArray());
}

// array#tail(n:number):map {block?}
Gura_DeclareMethod(array, tail)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "n", VTYPE_number, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
	AddHelp(
		Gura_Symbol(en),
		"Returns an `array` instance as a result that\n"
		"has extracted `n` elements from the bottom of the target `array`.\n"
		"\n"
		GURA_HELPTEXT_BLOCK_en("array", "array"));
}

template<typename T_Elem>
Value Method_tail(Environment &env, Argument &arg, const Function *pFunc, Array *pArraySelf)
{
	const ArrayT<T_Elem> *pArrayT = dynamic_cast<ArrayT<T_Elem> *>(pArraySelf);
	Signal &sig = env.GetSignal();
	size_t n = arg.GetSizeT(0);
	AutoPtr<ArrayT<T_Elem> > pArrayTRtn(pArrayT->Tail(sig, n));
	if (pArrayTRtn.IsNull()) return Value::Nil;
	Value value(new Object_array(env, pArrayTRtn.release()));
	return pFunc->ReturnValue(env, arg, value);
}

Gura_ImplementMethod(array, tail)
{
	static const MethodT methods[] = {
		nullptr,
		&Method_tail<Boolean>,
		&Method_tail<Int8>,
		&Method_tail<UInt8>,
		&Method_tail<Int16>,
		&Method_tail<UInt16>,
		&Method_tail<Int32>,
		&Method_tail<UInt32>,
		&Method_tail<Int64>,
		&Method_tail<UInt64>,
		&Method_tail<Half>,
		&Method_tail<Float>,
		&Method_tail<Double>,
		&Method_tail<Complex>,
		//&Method_tail<Value>,
	};
	return CallMethod(env, arg, methods, this, Object_array::GetObjectThis(arg)->GetArray());
}

// array#transpose(axes[]?:number) {block?}
Gura_DeclareMethod(array, transpose)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "axes", VTYPE_number, OCCUR_ZeroOrOnce, FLAG_ListVar);
	DeclareBlock(OCCUR_ZeroOrOnce);
	AddHelp(
		Gura_Symbol(en),
		"Creates an array instance that transposes axes of the original array\n"
		"according to the specified argument `axes`.\n"
		"\n"
		"If the argument is not specified, two axes at the lowest rank, which correspond to\n"
		"row and column for a matrix, would be transposed.\n"
		"\n"
		GURA_HELPTEXT_BLOCK_en("array", "array"));
}

template<typename T_Elem>
Value Method_transpose(Environment &env, Argument &arg, const Function *pFunc, Array *pArraySelf)
{
	ArrayT<T_Elem> *pArrayT = dynamic_cast<ArrayT<T_Elem> *>(pArraySelf);
	Signal &sig = env.GetSignal();
	AutoPtr<Array> pArrayTRtn;
	if (arg.IsValid(0)) {
		pArrayTRtn.reset(pArrayT->Transpose(sig, arg.GetList(0)));
		if (pArrayTRtn.IsNull()) return Value::Nil;
	} else {
		pArrayTRtn.reset(pArrayT->Transpose());
	}
	return pFunc->ReturnValue(env, arg, Value(new Object_array(env, pArrayTRtn.release())));
}

Gura_ImplementMethod(array, transpose)
{
	static const MethodT methods[] = {
		nullptr,
		&Method_transpose<Boolean>,
		&Method_transpose<Int8>,
		&Method_transpose<UInt8>,
		&Method_transpose<Int16>,
		&Method_transpose<UInt16>,
		&Method_transpose<Int32>,
		&Method_transpose<UInt32>,
		&Method_transpose<Int64>,
		&Method_transpose<UInt64>,
		&Method_transpose<Half>,
		&Method_transpose<Float>,
		&Method_transpose<Double>,
		&Method_transpose<Complex>,
		//&Method_transpose<Value>,
	};
	return CallMethod(env, arg, methods, this, Object_array::GetObjectThis(arg)->GetArray());
}

//-----------------------------------------------------------------------------
// Implementation of class
//-----------------------------------------------------------------------------
Class_array::Class_array(Environment *pEnvOuter) : ClassFundamental(pEnvOuter, VTYPE_array)
{
}

void Class_array::DoPrepare(Environment &env)
{
	// Assignment of properties
	Gura_AssignProperty(array, elembytes);
	Gura_AssignProperty(array, elemtype);
	Gura_AssignProperty(array, memoryid);
	Gura_AssignProperty(array, ndim);
	Gura_AssignProperty(array, p);
	Gura_AssignProperty(array, shape);
	Gura_AssignProperty(array, size);
	Gura_AssignProperty(array, T);
	// Assignment of function
	Gura_AssignFunction(array);
	Gura_AssignFunction(at_at);
	// Assignment of methods
	Gura_AssignMethod(array, average);
	Gura_AssignMethod(array, dot);
	Gura_AssignMethod(array, dump);
	Gura_AssignMethod(array, each);
	Gura_AssignMethod(array, elemcast);
	Gura_AssignMethod(array, fill);
	Gura_AssignMethod(array, flatten);
	Gura_AssignMethod(array, head);
	Gura_AssignMethod(array, invert);
	Gura_AssignMethod(array, iselemsame);
	Gura_AssignMethod(array, issquare);
	Gura_AssignMethod(array, offset);
	Gura_AssignMethod(array, paste);
	Gura_AssignMethod(array, reshape);
	Gura_AssignMethod(array, roundoff);
	Gura_AssignMethod(array, sum);
	Gura_AssignMethod(array, tail);
	Gura_AssignMethod(array, transpose);
	// help document
	AddHelpTemplate(env, Gura_Symbol(en), helpDoc_en);
}

Class::SerializeFmtVer Class_array::GetSerializeFmtVer() const
{
	return SerializeFmtVer_1;
}

bool Class_array::Serialize(Environment &env, Stream &stream, const Value &value) const
{
	const Array *pArray = Object_array::GetObject(value)->GetArray();
	return pArray->Serialize(env, stream);
}

bool Class_array::Deserialize(Environment &env, Stream &stream, Value &value, SerializeFmtVer serializeFmtVer) const
{
	if (serializeFmtVer == SerializeFmtVer_1) {
		AutoPtr<Array> pArray(Array::Deserialize(env, stream));
		if (pArray.IsNull()) return false;
		value = Value(new Object_array(env, pArray.release()));
		return true;
	}
	SetError_UnsupportedSerializeFmtVer(serializeFmtVer);
	return false;
}

bool Class_array::CastFrom(Environment &env, Value &value, ULong flags)
{
	return false;
}

template<typename T_Elem>
bool CastToTmpl(Environment &env, Value &value, const Declaration &decl, const Array *pArraySelf)
{
	if (decl.IsType(VTYPE_list)) {
		AutoPtr<ArrayT<T_Elem> > pArrayT(
			dynamic_cast<const ArrayT<T_Elem> *>(pArraySelf)->Reference());
		Object_list *pObjList = value.InitAsList(env);
		pArrayT->CopyToList(pObjList->GetListForModify());
		pObjList->SetValueType(VTYPE_number);
		return true;
	} else if (decl.IsType(VTYPE_iterator)) {
		AutoPtr<ArrayT<T_Elem> > pArrayT(
			dynamic_cast<const ArrayT<T_Elem> *>(pArraySelf)->Reference());
		AutoPtr<Iterator> pIterator(new Iterator_ArrayT_Each<T_Elem>(pArrayT.release(), false));
		value = Value(new Object_iterator(env, pIterator.release()));
		return true;
	} else if (decl.IsType(VTYPE_memory)) {
		value = Value(new Object_memory(env, pArraySelf->GetMemory().Reference()));
		return true;
	}
	return false;
}

bool Class_array::CastTo(Environment &env, Value &value, const Declaration &decl)
{
	const Array *pArray = Object_array::GetObject(value)->GetArray();
	static const CastToT castTos[] = {
		nullptr,
		&CastToTmpl<Boolean>,
		&CastToTmpl<Int8>,
		&CastToTmpl<UInt8>,
		&CastToTmpl<Int16>,
		&CastToTmpl<UInt16>,
		&CastToTmpl<Int32>,
		&CastToTmpl<UInt32>,
		&CastToTmpl<Int64>,
		&CastToTmpl<UInt64>,
		&CastToTmpl<Half>,
		&CastToTmpl<Float>,
		&CastToTmpl<Double>,
		&CastToTmpl<Complex>,
		//&CastToTmpl<Value>,
	};
	return (*castTos[pArray->GetElemType()])(env, value, decl, pArray);
}

}
