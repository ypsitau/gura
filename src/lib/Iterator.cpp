//=============================================================================
// Iterator
//=============================================================================
#include "stdafx.h"

namespace Gura {

//-----------------------------------------------------------------------------
// Iterator
//-----------------------------------------------------------------------------
Iterator::~Iterator()
{
	// virtual destructor
}

bool Iterator::IsSequence() const { return false; }
bool Iterator::IsSequenceInf() const { return false; }

Iterator *Iterator::_Clone()
{
	if (_pShare.get() == nullptr) _pShare.reset(new Share());
	int id = _pShare->Register();
	return new Iterator_GenericClone(Reference(this), id);
}

Iterator *Iterator::Clone() const
{
	return const_cast<Iterator *>(this)->_Clone();
}

bool Iterator::NextShared(Environment &env, int id, Value &value)
{
	if (_pShare.get() == nullptr) {
		for (;;) {
			if (!DoNext(env, value)) return false;
			if (!IsSkipInvalid() || value.IsValid()) break;
		}
	} else if (_pShare->Next(id, value)) {
		// nothing to do
	} else if (_pShare->IsDone()) {
		return false;
	} else {
		for (;;) {
			if (!DoNext(env, value)) {
				_pShare->SetDone();
				return false;
			}
			if (!IsSkipInvalid() || value.IsValid()) break;
		}
		_pShare->Store(id, value);
	}
	return true;
}

bool Iterator::Consume(Environment &env)
{
	Signal &sig = env.GetSignal();
	if (IsInfinite()) {
		SetError_InfiniteNotAllowed(sig);
		return false;
	}
	Value value;
	while (Next(env, value)) ;
	return !sig.IsSignalled();
}

Value Iterator::ToList(Environment &env, bool alwaysListFlag, bool excludeNilFlag)
{
	Signal &sig = env.GetSignal();
	if (IsInfinite()) {
		SetError_InfiniteNotAllowed(sig);
		return Value::Nil;
	}
	Value result;
	ValueList *pValList = nullptr;
	size_t cnt = 0;
	Value value;
	if (alwaysListFlag) {
		pValList = &result.InitAsList(env);
	}
	while (Next(env, value)) {
		if (pValList == nullptr && !value.IsUndefined()) {
			pValList = &result.InitAsList(env, cnt, Value::Nil);
		}
		if (value.IsValid()) {
			if (pValList == nullptr) {
				pValList = &result.InitAsList(env, cnt, Value::Nil);
			}
			pValList->push_back(value);
		} else if (excludeNilFlag) {
			// nothing to do
		} else if (pValList != nullptr) {
			pValList->push_back(value);
		}
		cnt++;
	}
	if (sig.IsSignalled()) return Value::Nil;
	return result;
}

Value Iterator::Eval(Environment &env, Argument &arg)
{
	Signal &sig = env.GetSignal();
	if (IsInfinite()) {
		SetError_InfiniteNotAllowed(sig);
		return Value::Nil;
	}
	Value value, result;
	Function::ResultComposer resultComposer(env, arg, result);
	while (Next(env, value)) {
		if (!resultComposer.Store(env, value)) return Value::Nil;
	}
	if (sig.IsSignalled()) return Value::Nil;
	return result;
}

Value Iterator::Reduce(Environment &env, Value valueAccum, const Function *pFuncBlock)
{
	Signal &sig = env.GetSignal();
	if (IsInfinite()) {
		SetError_InfiniteNotAllowed(sig);
		return Value::Nil;
	}
	Value value;
	while (Next(env, value)) {
		AutoPtr<Argument> pArgSub(new Argument(pFuncBlock));
		if (!pArgSub->AddValue(env, value, valueAccum)) return Value::Nil;
		Value result = pFuncBlock->Eval(env, *pArgSub);
		if (!sig.IsSignalled()) {
			// nothing to do
		} else if (sig.IsBreak()) {
			result = sig.GetValue();
			sig.ClearSignal();
			if (result.IsValid()) return result;
			return valueAccum;
		} else if (sig.IsContinue()) {
			result = sig.GetValue();
			sig.ClearSignal();
			if (result.IsInvalid()) continue;
		} else if (sig.IsReturn()) {
			return Value::Nil;
		} else {
			return Value::Nil;
		}
		valueAccum = result;
	}
	if (sig.IsSignalled()) return Value::Nil;
	return valueAccum;
}

Value Iterator::MinMax(Environment &env, bool maxFlag, const SymbolSet &attrs)
{
	Signal &sig = env.GetSignal();
	if (IsInfinite()) {
		SetError_InfiniteNotAllowed(sig);
		return Value::Nil;
	}
	Value valueHit;
	if (!Next(env, valueHit)) return Value::Nil;
	Value result;
	if (attrs.IsSet(Gura_Symbol(index))) {
		int idxHit = GetIndexCur();
		Value value;
		while (Next(env, value)) {
			int cmp = Value::Compare(env, valueHit, value);
			if (sig.IsSignalled()) return Value::Nil;
			if (maxFlag) cmp = -cmp;
			if (cmp > 0) {
				valueHit = value;
				idxHit = GetIndexCur();
			}
		}
		if (sig.IsSignalled()) return Value::Nil;
		result.SetNumber(idxHit);
	} else if (attrs.IsSet(Gura_Symbol(last_index))) {
		int idxHit = GetIndexCur();
		Value value;
		while (Next(env, value)) {
			int cmp = Value::Compare(env, valueHit, value);
			if (sig.IsSignalled()) return Value::Nil;
			if (maxFlag) cmp = -cmp;
			if (cmp >= 0) {
				valueHit = value;
				idxHit = GetIndexCur();
			}
		}
		if (sig.IsSignalled()) return Value::Nil;
		result.SetNumber(idxHit);
	} else if (attrs.IsSet(Gura_Symbol(indices))) {
		int idxHit = GetIndexCur();
		ValueList &resultList = result.InitAsList(env);
		resultList.push_back(Value(idxHit));
		Value value;
		while (Next(env, value)) {
			int cmp = Value::Compare(env, valueHit, value);
			if (sig.IsSignalled()) return Value::Nil;
			if (maxFlag) cmp = -cmp;
			if (cmp > 0) {
				int idxHit = GetIndexCur();
				valueHit = value;
				resultList.clear();
				resultList.push_back(Value(idxHit));
			} else if (cmp == 0) {
				int idxHit = GetIndexCur();
				resultList.push_back(Value(static_cast<Number>(idxHit)));
			}
		}
		if (sig.IsSignalled()) return Value::Nil;
	} else {
		Value value;
		while (Next(env, value)) {
			int cmp = Value::Compare(env, valueHit, value);
			if (sig.IsSignalled()) return Value::Nil;
			if (maxFlag) cmp = -cmp;
			if (cmp > 0) {
				valueHit = value;
			}
		}
		if (sig.IsSignalled()) return Value::Nil;
		result = valueHit;
	}
	return result;
}

void Iterator::SetError_InvalidDataTypeOfElement(Signal &sig)
{
	sig.SetError(ERR_ValueError, "invalid data type of element");
}

void Iterator::SetError_InfiniteNotAllowed(Signal &sig)
{
	sig.SetError(ERR_IteratorError, "cannot evaluate infinite iterator");
}

Value Iterator::Sum(Environment &env, size_t &cnt)
{
	Signal &sig = env.GetSignal();
	cnt = 0;
	Value value;
	if (!Next(env, value)) return Value::Nil;
	if (!value.Is_number()) {
		const Operator *pOperatorAdd = env.GetOperator(OPTYPE_Add);
		Value valResult(value);
		cnt = 1;
		while (Next(env, value)) {
			valResult = pOperatorAdd->EvalBinary(env, valResult, value);
			cnt++;
			if (sig.IsSignalled()) return Value::Nil;
		}
		return valResult;
	}
	Number result = value.GetNumber();
	cnt = 1;
	while (Next(env, value)) {
		if (value.Is_number()) {
			result += value.GetNumber();
			cnt++;
		} else {
			const Operator *pOperatorAdd = env.GetOperator(OPTYPE_Add);
			Value valResult(result);
			do {
				valResult = pOperatorAdd->EvalBinary(env, valResult, value);
				cnt++;
				if (sig.IsSignalled()) return Value::Nil;
			} while (Next(env, value));
			return valResult;
		}
	}
	return Value(result);
}

Value Iterator::Prod(Environment &env)
{
	Signal &sig = env.GetSignal();
	Value value;
	if (!Next(env, value)) return Value::Nil;
	if (!value.Is_number()) {
		const Operator *pOperatorMul = env.GetOperator(OPTYPE_Mul);
		Value valResult(value);
		while (Next(env, value)) {
			valResult = pOperatorMul->EvalBinary(env, valResult, value);
			if (sig.IsSignalled()) return Value::Nil;
		}
		return valResult;
	}
	Number result = value.GetNumber();
	while (Next(env, value)) {
		if (value.Is_number()) {
			if (result == 0) break;
			result *= value.GetNumber();
		} else {
			const Operator *pOperatorMul = env.GetOperator(OPTYPE_Mul);
			Value valResult(result);
			do {
				valResult = pOperatorMul->EvalBinary(env, valResult, value);
				if (sig.IsSignalled()) return Value::Nil;
			} while (Next(env, value));
			return valResult;
		}
	}
	return Value(result);
}

Value Iterator::Average(Environment &env, size_t &cnt)
{
	Signal &sig = env.GetSignal();
	if (IsInfinite()) {
		SetError_InfiniteNotAllowed(sig);
		return Value::Nil;
	}
	Value valueSum = Clone()->Sum(env, cnt);
	if (valueSum.IsInvalid()) {
		return Value::Nil;
	} else if (valueSum.Is_number()) {
		return Value(valueSum.GetNumber() / static_cast<Number>(cnt));
	} else if (valueSum.Is_complex()) {
		return Value(valueSum.GetComplex() / static_cast<Number>(cnt));
	} else {
		const Operator *pOperatorDiv = env.GetOperator(OPTYPE_Div);
		return pOperatorDiv->EvalBinary(env, valueSum, Value(cnt));
	}
}

Value Iterator::Variance(Environment &env, size_t &cnt)
{
	Signal &sig = env.GetSignal();
	if (IsInfinite()) {
		SetError_InfiniteNotAllowed(sig);
		return Value::Nil;
	}
	// this doesn't use a variance calculation formula V(x) = E(x**2) - E(x)**2
	// to minimize calculation error.
	Value valueAve = Clone()->Average(env, cnt);
	if (!valueAve.IsNumberOrComplex()) return Value::Nil;
	Value value;
	if (!Next(env, value)) return Value::Nil;
	if (value.Is_number() && valueAve.Is_number()) {
		Number result;
		Number average = valueAve.GetNumber();
		do {
			Number tmp = value.GetNumber() - average;
			result = tmp * tmp;
		} while (0);
		while (Next(env, value)) {
			if (value.Is_number()) {
				Number tmp = value.GetNumber() - average;
				result += tmp * tmp;
			} else if (value.Is_complex()) {
				while (Next(env, value)) {
					if (value.IsNumberOrComplex()) {
						Complex tmp = value.GetComplex() - average;
						result += std::norm(tmp);
					} else {
						SetError_InvalidDataTypeOfElement(sig);
						return Value::Nil;
					}
				}
			} else {
				SetError_InvalidDataTypeOfElement(sig);
				return Value::Nil;
			}
		}
		if (sig.IsSignalled()) return Value::Nil;
		return Value(result / static_cast<Number>(cnt));
	} else if (value.IsNumberOrComplex()) {
		Number result;
		Complex average = valueAve.GetComplex();
		do {
			Complex tmp = value.GetComplex() - average;
			result = std::norm(tmp);
		} while (0);
		while (Next(env, value)) {
			if (value.IsNumberOrComplex()) {
				Complex tmp = value.GetComplex() - average;
				result += std::norm(tmp);
			} else {
				SetError_InvalidDataTypeOfElement(sig);
				return Value::Nil;
			}
		}
		if (sig.IsSignalled()) return Value::Nil;
		return Value(result / static_cast<Number>(cnt));
	} else {
		SetError_InvalidDataTypeOfElement(sig);
		return Value::Nil;
	}
}

Value Iterator::StandardDeviation(Environment &env, size_t &cnt)
{
	Signal &sig = env.GetSignal();
	if (IsInfinite()) {
		SetError_InfiniteNotAllowed(sig);
		return Value::Nil;
	}
	Value valueVar = Clone()->Variance(env, cnt);
	if (!valueVar.Is_number()) return Value::Nil;
	return Value(::sqrt(valueVar.GetNumber()));
}

Value Iterator::And(Environment &env)
{
	Signal &sig = env.GetSignal();
	if (IsInfinite()) {
		SetError_InfiniteNotAllowed(sig);
		return Value::Nil;
	}
	Value value;
	if (!Next(env, value)) return Value::Nil;
	if (!value.GetBoolean()) return Value(false);
	while (Next(env, value)) {
		if (!value.GetBoolean()) return Value(false);
	}
	if (sig.IsSignalled()) return Value::Nil;
	return Value(true);
}

Value Iterator::Or(Environment &env)
{
	Signal &sig = env.GetSignal();
	if (IsInfinite()) {
		SetError_InfiniteNotAllowed(sig);
		return Value::Nil;
	}
	Value value;
	if (!Next(env, value)) return Value::Nil;
	if (value.GetBoolean()) return Value(true);
	while (Next(env, value)) {
		if (value.GetBoolean()) return Value(true);
	}
	if (sig.IsSignalled()) return Value::Nil;
	return Value(false);
}

size_t Iterator::Find(Environment &env, const Value &criteria, Value &value)
{
	Signal &sig = env.GetSignal();
	if (criteria.Is_function()) {
		if (IsInfinite()) {
			SetError_InfiniteNotAllowed(sig);
			return InvalidSize;
		}
		const Function *pFunc = criteria.GetFunction();
		while (Next(env, value)) {
			AutoPtr<Argument> pArg(new Argument(pFunc));
			if (!pArg->AddValue(env, value)) return InvalidSize;
			Value valueFlag = pFunc->Eval(env, *pArg);
			if (sig.IsSignalled()) return InvalidSize;
			if (valueFlag.GetBoolean()) return GetIndexCur();
		}
		if (sig.IsSignalled()) return InvalidSize;
	} else if (criteria.Is_list() || criteria.Is_iterator()) {
		AutoPtr<Iterator> pIteratorCriteria(criteria.CreateIterator(sig));
		if (sig.IsSignalled()) return InvalidSize;
		if (IsInfinite() && pIteratorCriteria->IsInfinite()) {
			SetError_InfiniteNotAllowed(sig);
			return InvalidSize;
		}
		while (Next(env, value)) {
			Value valueCriteria;
			if (!pIteratorCriteria->Next(env, valueCriteria)) break;
			if (valueCriteria.GetBoolean()) return GetIndexCur();
		}
		return InvalidSize;
	} else {
		while (Next(env, value)) {
			//int cmp = Value::Compare(env, value, criteria);
			//if (sig.IsSignalled()) return InvalidSize;
			//if (cmp == 0) return GetIndexCur();
			if (value.Is(criteria)) return GetIndexCur();
		}
	}
	return InvalidSize;
}

size_t Iterator::FindTrue(Environment &env, Value &value)
{
	Signal &sig = env.GetSignal();
	if (IsInfinite()) {
		SetError_InfiniteNotAllowed(sig);
		return 0;
	}
	while (Next(env, value)) {
		if (value.GetBoolean()) return GetIndexCur();
	}
	return InvalidSize;
}

size_t Iterator::Count(Environment &env, const Value &criteria)
{
	Signal &sig = env.GetSignal();
	if (IsInfinite()) {
		SetError_InfiniteNotAllowed(sig);
		return 0;
	}
	size_t cnt = 0;
	if (criteria.Is_function()) {
		const Function *pFunc = criteria.GetFunction();
		Value value;
		while (Next(env, value)) {
			AutoPtr<Argument> pArg(new Argument(pFunc));
			if (!pArg->AddValue(env, value)) return 0;
			Value valueFlag = pFunc->Eval(env, *pArg);
			if (sig.IsSignalled()) return 0;
			if (valueFlag.GetBoolean()) cnt++;
		}
		if (sig.IsSignalled()) return 0;
	} else {
		Value value;
		while (Next(env, value)) {
			int cmp = Value::Compare(env, value, criteria);
			if (sig.IsSignalled()) return 0;
			if (cmp == 0) cnt++;
		}
	}
	return cnt;
}

size_t Iterator::CountTrue(Environment &env)
{
	Signal &sig = env.GetSignal();
	if (IsInfinite()) {
		SetError_InfiniteNotAllowed(sig);
		return 0;
	}
	size_t cnt = 0;
	Value value;
	while (Next(env, value)) {
		if (value.GetBoolean()) cnt++;
	}
	return cnt;
}

Iterator *Iterator::Filter(Environment &env, const Value &criteria)
{
	Signal &sig = env.GetSignal();
	if (criteria.Is_function()) {
		Object_function *pFuncObjCriteria =
			Object_function::Reference(Object_function::GetObject(criteria));
		return new Iterator_FilterWithFunc(new Environment(env), this, pFuncObjCriteria);
	} else if (criteria.Is_list() || criteria.Is_iterator()) {
		Iterator *pIteratorCriteria = criteria.CreateIterator(sig);
		if (sig.IsSignalled()) return nullptr;
		return new Iterator_FilterWithIter(this, pIteratorCriteria);
	} else {
		sig.SetError(ERR_ValueError, "invalid type of criteria for filter");
		return nullptr;
	}
}

Iterator *Iterator::While(Environment &env, const Value &criteria)
{
	Signal &sig = env.GetSignal();
	if (criteria.Is_function()) {
		Object_function *pFuncObjCriteria = 
			Object_function::Reference(Object_function::GetObject(criteria));
		return new Iterator_WhileWithFunc(new Environment(env), this, pFuncObjCriteria);
	} else if (criteria.Is_list() || criteria.Is_iterator()) {
		Iterator *pIteratorCriteria = criteria.CreateIterator(sig);
		if (sig.IsSignalled()) return nullptr;
		return new Iterator_WhileWithIter(this, pIteratorCriteria);
	} else {
		sig.SetError(ERR_ValueError, "invalid type of criteria for while");
		return nullptr;
	}
}

Iterator *Iterator::Since(Environment &env, const Value &criteria, bool containFirstFlag)
{
	Signal &sig = env.GetSignal();
	if (criteria.Is_function()) {
		Object_function *pFuncObjCriteria = 
			Object_function::Reference(Object_function::GetObject(criteria));
		return new Iterator_SinceWithFunc(new Environment(env), this, pFuncObjCriteria, containFirstFlag);
	} else if (criteria.Is_list() || criteria.Is_iterator()) {
		Iterator *pIteratorCriteria = criteria.CreateIterator(sig);
		if (sig.IsSignalled()) return nullptr;
		return new Iterator_SinceWithIter(this, pIteratorCriteria, containFirstFlag);
	} else {
		sig.SetError(ERR_ValueError, "invalid type of criteria for since");
		return nullptr;
	}
}

Iterator *Iterator::Until(Environment &env, const Value &criteria, bool containLastFlag)
{
	Signal &sig = env.GetSignal();
	if (criteria.Is_function()) {
		Object_function *pFuncObjCriteria = 
			Object_function::Reference(Object_function::GetObject(criteria));
		return new Iterator_UntilWithFunc(new Environment(env), this, pFuncObjCriteria, containLastFlag);
	} else if (criteria.Is_list() || criteria.Is_iterator()) {
		Iterator *pIteratorCriteria = criteria.CreateIterator(sig);
		if (sig.IsSignalled()) return nullptr;
		return new Iterator_UntilWithIter(this, pIteratorCriteria, containLastFlag);
	} else {
		sig.SetError(ERR_ValueError, "invalid type of criteria for since");
		return nullptr;
	}
}

bool Iterator::DoesContain(Environment &env, const Value &value)
{
	Signal &sig = env.GetSignal();
	if (IsInfinite()) {
		SetError_InfiniteNotAllowed(sig);
		return false;
	}
	Value valueToFind;
	while (Next(env, valueToFind)) {
		int cmp = Value::Compare(env, value, valueToFind);
		if (sig.IsSignalled()) return false;
		if (cmp == 0) return true;
	}
	return false;
}

String Iterator::Join(Environment &env, const char *sep)
{
	Signal &sig = env.GetSignal();
	String rtn;
	Value value;
	if (IsInfinite()) {
		SetError_InfiniteNotAllowed(sig);
		return rtn;
	}
	if (Next(env, value)) {
		rtn += value.ToString(false);
		while (Next(env, value)) {
			rtn += sep;
			rtn += value.ToString(false);
		}
	}
	return rtn;
}

Binary Iterator::Joinb(Environment &env)
{
	Signal &sig = env.GetSignal();
	Binary rtn;
	Value value;
	if (IsInfinite()) {
		SetError_InfiniteNotAllowed(sig);
		return rtn;
	}
	while (Next(env, value)) {
		if (!value.Is_binary()) {
			sig.SetError(ERR_ValueError, "invalid value type");
			return "";
		}
		rtn += value.GetBinary();
	}
	return rtn;
}

void Iterator::PrintEach(Environment &env, Stream *pStream)
{
	Signal &sig = env.GetSignal();
	Value value;
	while (Next(env, value)) {
		pStream->Print(sig, value.ToString(false).c_str());
		if (sig.IsSignalled()) break;
	}
}

void Iterator::PrintfEach(Environment &env, Stream *pStream, const char *format)
{
	Signal &sig = env.GetSignal();
	Value value;
	while (Next(env, value)) {
		if (value.Is_list()) {
			pStream->PrintFmt(sig, format, value.GetList());
		} else {
			pStream->PrintFmt(sig, format, ValueList(value));
		}
		if (sig.IsSignalled()) break;
	}
}

void Iterator::PrintlnEach(Environment &env, Stream *pStream)
{
	Signal &sig = env.GetSignal();
	Value value;
	while (Next(env, value)) {
		pStream->Println(sig, value.ToString(false).c_str());
		if (sig.IsSignalled()) break;
	}
}

String Iterator::ToString() const
{
	return String("");
}

//-----------------------------------------------------------------------------
// Iterator::Share
//-----------------------------------------------------------------------------
Iterator::Share::Share() : _doneFlag(false), _indexMin(0)
{
	_indexList.push_back(_indexMin);
}

int Iterator::Share::Register()
{
	int id = static_cast<int>(_indexList.size());
	_indexList.push_back(_indexMin);
	return id;
}

bool Iterator::Share::Next(int id, Value &value)
{
	size_t iElem = _indexList[id] - _indexMin;
	if (iElem >= _valueDeque.size()) return false;
	value = _valueDeque[iElem];
	_indexList[id] = static_cast<UInt>(_indexMin + iElem + 1);
	size_t indexMinCur = _indexMin;
	foreach (IndexList, pIndex, _indexList) {
		if (indexMinCur > *pIndex) indexMinCur = *pIndex;
	}
	for (size_t cnt = indexMinCur - _indexMin; cnt > 0; cnt--) {
		_valueDeque.pop_front();
	}
	_indexMin = indexMinCur;
	return true;
}

void Iterator::Share::Store(int id, const Value &value)
{
	_valueDeque.push_back(value);
	_indexList[id] = static_cast<UInt>(_indexMin + _valueDeque.size());
}

//-----------------------------------------------------------------------------
// IteratorOwner
//-----------------------------------------------------------------------------
IteratorOwner::IteratorOwner(const IteratorOwner &iterOwner)
{
	reserve(iterOwner.size());
	foreach_const (IteratorOwner, ppIterator, iterOwner) {
		push_back((*ppIterator)->Clone());
	}
}

IteratorOwner::~IteratorOwner()
{
	foreach (IteratorOwner, ppIterator, *this) {
		Iterator::Delete(*ppIterator);
	}
}

bool IteratorOwner::Next(Environment &env, ValueList &valList)
{
	valList.clear();
	foreach (IteratorOwner, ppIterator, *this) {
		Iterator *pIterator = *ppIterator;
		Value value;
		if (!pIterator->Next(env, value)) return false;
		valList.push_back(value);
	}
	return true;
}

void IteratorOwner::GatherFollower(Environment::Frame *pFrame, EnvironmentSet &envSet)
{
	foreach (IteratorOwner, ppIterator, *this) {
		Iterator *pIterator = *ppIterator;
		pIterator->GatherFollower(pFrame, envSet);
	}
}

bool IteratorOwner::IsInfinite() const
{
	foreach_const (IteratorOwner, ppIterator, *this) {
		if (!(*ppIterator)->IsInfinite()) return false;
	}
	return true;
}

}
