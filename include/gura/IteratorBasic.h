//=============================================================================
// IteratorBasic
//=============================================================================
#ifndef __GURA_ITERATORBASIC_H__
#define __GURA_ITERATORBASIC_H__

#include "Environment.h"
#include "Signal.h"
#include "Expr.h"
#include "Declaration.h"
#include "Value.h"
#include "OAL.h"
#include "Iterator.h"

namespace Gura {

class Argument;
class Object_function;

//-----------------------------------------------------------------------------
// Iterator_GenericClone
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE Iterator_GenericClone : public Iterator {
private:
	AutoPtr<Iterator> _pIterator;
	int _id;
public:
	inline Iterator_GenericClone(Iterator *pIterator, int id) :
			Iterator(pIterator->GetFiniteness(), pIterator->IsSkipInvalid()),
			_pIterator(pIterator), _id(id) {}
	virtual Iterator *GetSource();
	virtual bool DoNext(Environment &env, Value &value);
	virtual String ToString() const;
	virtual void GatherFollower(Environment::Frame *pFrame, EnvironmentSet &envSet);
};

//-----------------------------------------------------------------------------
// Iterator_Constant
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE Iterator_Constant : public Iterator {
private:
	Value _value;
public:
	inline Iterator_Constant(const Value &value) : Iterator(Infinite), _value(value) {}
	inline Iterator_Constant(const Iterator_Constant &iter) :
										Iterator(Infinite), _value(iter._value) {}
	virtual Iterator *Clone() const;
	virtual Iterator *GetSource();
	virtual bool DoNext(Environment &env, Value &value);
	virtual String ToString() const;
	virtual void GatherFollower(Environment::Frame *pFrame, EnvironmentSet &envSet);
};

//-----------------------------------------------------------------------------
// Iterator_ConstantN
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE Iterator_ConstantN : public Iterator {
private:
	Value _value;
	int _cnt;
	int _idx;
public:
	inline Iterator_ConstantN(const Value &value, int cnt) :
				Iterator(Finite), _value(value), _cnt(cnt), _idx(0) {}
	inline Iterator_ConstantN(const Iterator_ConstantN &iter) :
				Iterator(Finite), _value(iter._value), _cnt(iter._cnt),
				_idx(iter._idx) {}
	virtual Iterator *Clone() const;
	virtual Iterator *GetSource();
	virtual bool DoNext(Environment &env, Value &value);
	virtual String ToString() const;
	virtual void GatherFollower(Environment::Frame *pFrame, EnvironmentSet &envSet);
};

//-----------------------------------------------------------------------------
// Iterator_OneShot
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE Iterator_OneShot : public Iterator {
private:
	Value _value;
	bool _doneFlag;
public:
	inline Iterator_OneShot(const Value &value) :
				Iterator(Finite), _value(value), _doneFlag(false) {}
	inline Iterator_OneShot(const Iterator_OneShot &iter) :
				Iterator(Finite), _value(iter._value), _doneFlag(iter._doneFlag) {}
	virtual Iterator *Clone() const;
	virtual Iterator *GetSource();
	virtual bool DoNext(Environment &env, Value &value);
	virtual String ToString() const;
	virtual void GatherFollower(Environment::Frame *pFrame, EnvironmentSet &envSet);
};

//-----------------------------------------------------------------------------
// Iterator_Rand
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE Iterator_Rand : public Iterator {
private:
	int _range;
	int _cnt;
	int _idx;
public:
	inline Iterator_Rand(int range, int cnt) :
		Iterator((cnt < 0)? Infinite : Finite), _range(range), _cnt(cnt), _idx(0) {}
	virtual Iterator *GetSource();
	virtual bool DoNext(Environment &env, Value &value);
	virtual String ToString() const;
	virtual void GatherFollower(Environment::Frame *pFrame, EnvironmentSet &envSet);
};

//-----------------------------------------------------------------------------
// Iterator_Randn
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE Iterator_Randn : public Iterator {
private:
	double _mu;
	double _sigma;
	int _cnt;
	int _idx;
public:
	inline Iterator_Randn(double mu, double sigma, int cnt) :
		Iterator((cnt < 0)? Infinite : Finite), _mu(mu), _sigma(sigma), _cnt(cnt), _idx(0) {}
	virtual Iterator *GetSource();
	virtual bool DoNext(Environment &env, Value &value);
	virtual String ToString() const;
	virtual void GatherFollower(Environment::Frame *pFrame, EnvironmentSet &envSet);
};

//-----------------------------------------------------------------------------
// Iterator_Range
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE Iterator_Range : public Iterator {
private:
	Number _num;
	Number _numBegin;
	Number _numEnd;
	Number _numStep;
public:
	inline Iterator_Range(Number numBegin, Number numEnd, Number numStep) :
			Iterator(Finite), _num(numBegin),
			_numBegin(numBegin), _numEnd(numEnd), _numStep(numStep) {}
	inline Iterator_Range(const Iterator_Range &iter) :
			Iterator(iter), _num(iter._num),
			_numBegin(iter._numBegin), _numEnd(iter._numEnd), _numStep(iter._numStep) {}
	virtual Iterator *Clone() const;
	virtual Iterator *GetSource();
	virtual bool DoNext(Environment &env, Value &value);
	virtual String ToString() const;
	virtual void GatherFollower(Environment::Frame *pFrame, EnvironmentSet &envSet);
};

//-----------------------------------------------------------------------------
// Iterator_Sequence
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE Iterator_Sequence : public Iterator {
private:
	Number _num;
	Number _numBegin;
	Number _numEnd;
	Number _numStep;
public:
	inline Iterator_Sequence(Number numBegin, Number numEnd, Number numStep) :
			Iterator(Finite), _num(numBegin),
			_numBegin(numBegin), _numEnd(numEnd), _numStep(numStep) {}
	inline Iterator_Sequence(const Iterator_Sequence &iter) :
			Iterator(iter), _num(iter._num),
			_numBegin(iter._numBegin), _numEnd(iter._numEnd), _numStep(iter._numStep) {}
	virtual bool IsSequence() const;
	virtual Iterator *Clone() const;
	virtual Iterator *GetSource();
	virtual bool DoNext(Environment &env, Value &value);
	virtual String ToString() const;
	virtual void GatherFollower(Environment::Frame *pFrame, EnvironmentSet &envSet);
	inline Number GetBegin() const { return _numBegin; }
	inline Number GetEnd() const { return _numEnd; }
	inline Number GetStep() const { return _numStep; }
};

//-----------------------------------------------------------------------------
// Iterator_SequenceInf
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE Iterator_SequenceInf : public Iterator {
private:
	Number _num;
	Number _numBegin;
	Number _numStep;
public:
	inline Iterator_SequenceInf(Number numBegin, Number numStep = 1) :
			Iterator(Infinite), _num(numBegin), _numBegin(numBegin), _numStep(numStep) {}
	inline Iterator_SequenceInf(const Iterator_SequenceInf &iter) :
			Iterator(iter), _num(iter._num), _numBegin(iter._numBegin), _numStep(iter._numStep) {}
	virtual bool IsSequenceInf() const;
	virtual Iterator *Clone() const;
	virtual Iterator *GetSource();
	virtual bool DoNext(Environment &env, Value &value);
	virtual String ToString() const;
	virtual void GatherFollower(Environment::Frame *pFrame, EnvironmentSet &envSet);
	inline Number GetBegin() const { return _numBegin; }
	inline Number GetStep() const { return _numStep; }
};

//-----------------------------------------------------------------------------
// Iterator_Interval
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE Iterator_Interval : public Iterator {
private:
	Number _numBegin;
	Number _numEnd;
	int _numSamples;
	Number _numDenom;
	int _iFactor;
	int _idx;
public:
	inline Iterator_Interval(Number numBegin, Number numEnd,
								int numSamples, Number numDenom, int iFactor) :
		Iterator(Finite), _numBegin(numBegin), _numEnd(numEnd), _numSamples(numSamples),
		_numDenom(numDenom), _iFactor(iFactor), _idx(0) {}
	inline Iterator_Interval(Number numBegin, Number numEnd, int numSamples) :
		Iterator(Finite), _numBegin(numBegin), _numEnd(numEnd), _numSamples(numSamples),
		_numDenom(numSamples - 1), _iFactor(0), _idx(0) {}
	inline Iterator_Interval(const Iterator_Interval &iter) :
		Iterator(iter), _numBegin(iter._numBegin), _numEnd(iter._numEnd), _numSamples(iter._numSamples),
		_numDenom(iter._numDenom), _iFactor(iter._iFactor), _idx(iter._idx) {}
	virtual Iterator *Clone() const;
	virtual Iterator *GetSource();
	virtual bool DoNext(Environment &env, Value &value);
	virtual String ToString() const;
	virtual void GatherFollower(Environment::Frame *pFrame, EnvironmentSet &envSet);
protected:
	inline bool _DoNext(Number &num) {
		if (_idx >= _numSamples) return false;
		num = (_numEnd - _numBegin) * _iFactor / _numDenom + _numBegin;
		_iFactor++, _idx++;
		return true;
	}
};

//-----------------------------------------------------------------------------
// Iterator_ExplicitMap
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE Iterator_ExplicitMap : public Iterator {
private:
	AutoPtr<Environment> _pEnv;
	AutoPtr<Iterator> _pIterator;
	AutoPtr<Object_function> _pObjFunc;
public:
	Iterator_ExplicitMap(Environment *pEnv,
							Iterator *pIterator, Object_function *pObjFunc);
	Iterator_ExplicitMap(const Iterator_ExplicitMap &iter);
	virtual ~Iterator_ExplicitMap();
	virtual Iterator *Clone() const;
	virtual Iterator *GetSource();
	virtual bool DoNext(Environment &env, Value &value);
	virtual String ToString() const;
	virtual void GatherFollower(Environment::Frame *pFrame, EnvironmentSet &envSet);
};

//-----------------------------------------------------------------------------
// Iterator_ImplicitMap
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE Iterator_ImplicitMap : public Iterator {
private:
	AutoPtr<Environment> _pEnv;
	AutoPtr<Argument> _pArg;
	bool _doneThisFlag;
public:
	Iterator_ImplicitMap(Environment *pEnv, Argument *pArg, bool skipInvalidFlag);
	virtual ~Iterator_ImplicitMap();
	virtual Iterator *GetSource();
	virtual bool DoNext(Environment &env, Value &value);
	virtual String ToString() const;
	virtual void GatherFollower(Environment::Frame *pFrame, EnvironmentSet &envSet);
};

//-----------------------------------------------------------------------------
// Iterator_UnaryOperatorMap
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE Iterator_UnaryOperatorMap : public Iterator {
private:
	AutoPtr<Environment> _pEnv;
	const Operator *_pOperator;
	AutoPtr<Iterator> _pIterator;
	const OperatorEntry *_pOperatorEntry;
	ValueType _valTypePrev;
	ULong _flags;
public:
	Iterator_UnaryOperatorMap(
		Environment *pEnv, const Operator *pOperator, const Value &value, ULong flags);
	virtual ~Iterator_UnaryOperatorMap();
	virtual Iterator *GetSource();
	virtual bool DoNext(Environment &env, Value &value);
	virtual String ToString() const;
	virtual void GatherFollower(Environment::Frame *pFrame, EnvironmentSet &envSet);
};

//-----------------------------------------------------------------------------
// Iterator_BinaryOperatorMap
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE Iterator_BinaryOperatorMap : public Iterator {
private:
	AutoPtr<Environment> _pEnv;
	const Operator *_pOperator;
	AutoPtr<Iterator> _pIteratorLeft;
	AutoPtr<Iterator> _pIteratorRight;
	const OperatorEntry *_pOperatorEntry;
	ValueType _valTypeLeftPrev, _valTypeRightPrev;
	ULong _flags;
public:
	Iterator_BinaryOperatorMap(
		Environment *pEnv, const Operator *pOperator,
		const Value &valueLeft, const Value &valueRight, ULong flags);
	virtual ~Iterator_BinaryOperatorMap();
	virtual Iterator *GetSource();
	virtual bool DoNext(Environment &env, Value &value);
	virtual String ToString() const;
	virtual void GatherFollower(Environment::Frame *pFrame, EnvironmentSet &envSet);
};

//-----------------------------------------------------------------------------
// Iterator_MemberMap
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE Iterator_MemberMap : public Iterator {
private:
	AutoPtr<Environment> _pEnv;
	AutoPtr<Iterator> _pIterator;
	const Symbol *_pSymbol;
	AutoPtr<SymbolSetShared> _pAttrsShrd;
public:
	Iterator_MemberMap(Environment *pEnv, Iterator *pIterator,
					   const Symbol *pSymbol, SymbolSetShared *pAttrsShrd);
	virtual ~Iterator_MemberMap();
	virtual Iterator *GetSource();
	virtual bool DoNext(Environment &env, Value &value);
	virtual String ToString() const;
	virtual void GatherFollower(Environment::Frame *pFrame, EnvironmentSet &envSet);
	inline const Symbol *GetSymbol() const { return _pSymbol; }
	inline const SymbolSet &GetAttrs() const {
		return _pAttrsShrd.IsNull()? SymbolSet::Empty : _pAttrsShrd->GetSymbolSet();
	}
};

//-----------------------------------------------------------------------------
// Iterator_MethodMap
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE Iterator_MethodMap : public Iterator {
private:
	AutoPtr<Environment> _pEnv;
	AutoPtr<Iterator> _pIteratorThis;
	AutoPtr<Expr_Caller> _pExprCaller;
	AutoPtr<Callable> _pCallable;
	const Expr_Identifier *_pExprSelector;
	ValueType _valTypePrev;
public:
	Iterator_MethodMap(Environment *pEnv, Iterator *pIteratorThis, Expr_Caller *pExprCaller);
	virtual ~Iterator_MethodMap();
	virtual Iterator *GetSource();
	virtual bool DoNext(Environment &env, Value &value);
	virtual String ToString() const;
	virtual void GatherFollower(Environment::Frame *pFrame, EnvironmentSet &envSet);
};

//-----------------------------------------------------------------------------
// Iterator_FuncBinder
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE Iterator_FuncBinder : public Iterator {
private:
	AutoPtr<Environment> _pEnv;
	AutoPtr<Function> _pFunc;
	Value _valueThis;
	AutoPtr<Iterator> _pIterator;
public:
	Iterator_FuncBinder(Environment *pEnv,
				Function *pFunc, const Value &valueThis, Iterator *pIterator);
	virtual Iterator *GetSource();
	virtual bool DoNext(Environment &env, Value &value);
	virtual String ToString() const;
	virtual void GatherFollower(Environment::Frame *pFrame, EnvironmentSet &envSet);
};

//-----------------------------------------------------------------------------
// Iterator_Delay
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE Iterator_Delay : public Iterator {
private:
	AutoPtr<Iterator> _pIterator;
	Number _delay;
public:
	inline Iterator_Delay(Iterator *pIterator, Number delay) : 
		Iterator(pIterator->GetFiniteness()), _pIterator(pIterator), _delay(delay) {}
	virtual Iterator *GetSource();
	virtual bool DoNext(Environment &env, Value &value);
	virtual String ToString() const;
	virtual void GatherFollower(Environment::Frame *pFrame, EnvironmentSet &envSet);
};

//-----------------------------------------------------------------------------
// Iterator_Contains
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE Iterator_Contains : public Iterator {
private:
	AutoPtr<Iterator> _pIterator;
	ValueList _valListToFind;
public:
	inline Iterator_Contains(Iterator *pIterator) :
		Iterator(pIterator->GetFiniteness()), _pIterator(pIterator) {}
	ValueList &GetValueListToFind() { return _valListToFind; }
	virtual Iterator *GetSource();
	virtual bool DoNext(Environment &env, Value &value);
	virtual String ToString() const;
	virtual void GatherFollower(Environment::Frame *pFrame, EnvironmentSet &envSet);
};

//-----------------------------------------------------------------------------
// Iterator_Skip
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE Iterator_Skip : public Iterator {
private:
	AutoPtr<Iterator> _pIterator;
	int _nSkip;
	bool _firstFlag;
public:
	inline Iterator_Skip(Iterator *pIterator, int nSkip) :
		Iterator(pIterator->IsInfinite()? Infinite : Finite), // must be revised later
		_pIterator(pIterator), _nSkip(nSkip), _firstFlag(true) {}
	virtual Iterator *GetSource();
	virtual bool DoNext(Environment &env, Value &value);
	virtual String ToString() const;
	virtual void GatherFollower(Environment::Frame *pFrame, EnvironmentSet &envSet);
};

//-----------------------------------------------------------------------------
// Iterator_SkipInvalid
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE Iterator_SkipInvalid : public Iterator {
private:
	AutoPtr<Iterator> _pIterator;
public:
	inline Iterator_SkipInvalid(Iterator *pIterator) :
		Iterator(pIterator->IsInfinite()? Infinite : Finite), _pIterator(pIterator) {}
	virtual Iterator *GetSource();
	virtual bool DoNext(Environment &env, Value &value);
	virtual String ToString() const;
	virtual void GatherFollower(Environment::Frame *pFrame, EnvironmentSet &envSet);
};

//-----------------------------------------------------------------------------
// Iterator_SkipFalse
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE Iterator_SkipFalse : public Iterator {
private:
	AutoPtr<Iterator> _pIterator;
public:
	inline Iterator_SkipFalse(Iterator *pIterator) :
		Iterator(pIterator->IsInfinite()? Infinite : Finite), _pIterator(pIterator) {}
	virtual Iterator *GetSource();
	virtual bool DoNext(Environment &env, Value &value);
	virtual String ToString() const;
	virtual void GatherFollower(Environment::Frame *pFrame, EnvironmentSet &envSet);
};

//-----------------------------------------------------------------------------
// Iterator_RoundOff
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE Iterator_RoundOff : public Iterator {
private:
	AutoPtr<Iterator> _pIterator;
	Number _threshold;
public:
	inline Iterator_RoundOff(Iterator *pIterator, Number threshold) :
		Iterator(pIterator->GetFiniteness()), _pIterator(pIterator), _threshold(threshold) {}
	virtual Iterator *GetSource();
	virtual bool DoNext(Environment &env, Value &value);
	virtual String ToString() const;
	virtual void GatherFollower(Environment::Frame *pFrame, EnvironmentSet &envSet);
};

//-----------------------------------------------------------------------------
// Iterator_FilterWithFunc
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE Iterator_FilterWithFunc : public Iterator {
private:
	AutoPtr<Environment> _pEnv;
	AutoPtr<Iterator> _pIterator;
	AutoPtr<Object_function> _pObjFunc;
public:
	Iterator_FilterWithFunc(Environment *pEnv,
							Iterator *pIterator, Object_function *pObjFunc);
	virtual Iterator *GetSource();
	virtual bool DoNext(Environment &env, Value &value);
	virtual String ToString() const;
	virtual void GatherFollower(Environment::Frame *pFrame, EnvironmentSet &envSet);
};

//-----------------------------------------------------------------------------
// Iterator_FilterWithIter
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE Iterator_FilterWithIter : public Iterator {
private:
	AutoPtr<Iterator> _pIterator;
	AutoPtr<Iterator> _pIteratorCriteria;
public:
	inline Iterator_FilterWithIter(Iterator *pIterator, Iterator *pIteratorCriteria) :
		Iterator((pIterator->IsInfinite() && pIteratorCriteria->IsInfinite())? Infinite : Finite),
		_pIterator(pIterator), _pIteratorCriteria(pIteratorCriteria) {}
	virtual Iterator *GetSource();
	virtual bool DoNext(Environment &env, Value &value);
	virtual String ToString() const;
	virtual void GatherFollower(Environment::Frame *pFrame, EnvironmentSet &envSet);
};

//-----------------------------------------------------------------------------
// Iterator_WhileWithFunc
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE Iterator_WhileWithFunc : public Iterator {
private:
	AutoPtr<Environment> _pEnv;
	AutoPtr<Iterator> _pIterator;
	AutoPtr<Object_function> _pObjFunc;
public:
	Iterator_WhileWithFunc(Environment *pEnv,
							Iterator *pIterator, Object_function *pObjFunc);
	virtual Iterator *GetSource();
	virtual bool DoNext(Environment &env, Value &value);
	virtual String ToString() const;
	virtual void GatherFollower(Environment::Frame *pFrame, EnvironmentSet &envSet);
};

//-----------------------------------------------------------------------------
// Iterator_WhileWithIter
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE Iterator_WhileWithIter : public Iterator {
private:
	AutoPtr<Iterator> _pIterator;
	AutoPtr<Iterator> _pIteratorCriteria;
public:
	inline Iterator_WhileWithIter(Iterator *pIterator, Iterator *pIteratorCriteria) :
			Iterator(Finite), _pIterator(pIterator), _pIteratorCriteria(pIteratorCriteria) {}
	virtual Iterator *GetSource();
	virtual bool DoNext(Environment &env, Value &value);
	virtual String ToString() const;
	virtual void GatherFollower(Environment::Frame *pFrame, EnvironmentSet &envSet);
};

//-----------------------------------------------------------------------------
// Iterator_UntilWithFunc
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE Iterator_UntilWithFunc : public Iterator {
private:
	AutoPtr<Environment> _pEnv;
	AutoPtr<Iterator> _pIterator;
	AutoPtr<Object_function> _pObjFunc;
	bool _containLastFlag;
public:
	Iterator_UntilWithFunc(Environment *pEnv, Iterator *pIterator,
								Object_function *pObjFunc, bool containLastFlag);
	virtual Iterator *GetSource();
	virtual bool DoNext(Environment &env, Value &value);
	virtual String ToString() const;
	virtual void GatherFollower(Environment::Frame *pFrame, EnvironmentSet &envSet);
};

//-----------------------------------------------------------------------------
// Iterator_UntilWithIter
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE Iterator_UntilWithIter : public Iterator {
private:
	AutoPtr<Iterator> _pIterator;
	AutoPtr<Iterator> _pIteratorCriteria;
	bool _containLastFlag;
public:
	inline Iterator_UntilWithIter(Iterator *pIterator,
								Iterator *pIteratorCriteria, bool containLastFlag) :
			Iterator(Finite), _pIterator(pIterator), _pIteratorCriteria(pIteratorCriteria),
			_containLastFlag(containLastFlag) {}
	virtual Iterator *GetSource();
	virtual bool DoNext(Environment &env, Value &value);
	virtual String ToString() const;
	virtual void GatherFollower(Environment::Frame *pFrame, EnvironmentSet &envSet);
};

//-----------------------------------------------------------------------------
// Iterator_SinceWithFunc
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE Iterator_SinceWithFunc : public Iterator {
private:
	AutoPtr<Environment> _pEnv;
	AutoPtr<Iterator> _pIterator;
	AutoPtr<Object_function> _pObjFunc;
	bool _containFirstFlag;
public:
	Iterator_SinceWithFunc(Environment *pEnv, Iterator *pIterator,
								Object_function *pObjFunc, bool containFirstFlag);
	virtual Iterator *GetSource();
	virtual bool DoNext(Environment &env, Value &value);
	virtual String ToString() const;
	virtual void GatherFollower(Environment::Frame *pFrame, EnvironmentSet &envSet);
};

//-----------------------------------------------------------------------------
// Iterator_SinceWithIter
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE Iterator_SinceWithIter : public Iterator {
private:
	AutoPtr<Iterator> _pIterator;
	AutoPtr<Iterator> _pIteratorCriteria;
	bool _containFirstFlag;
public:
	inline Iterator_SinceWithIter(Iterator *pIterator,
								Iterator *pIteratorCriteria, bool containFirstFlag) :
		Iterator((pIterator->IsInfinite() && pIteratorCriteria->IsInfinite())? Infinite : Finite),
		_pIterator(pIterator), _pIteratorCriteria(pIteratorCriteria),
		_containFirstFlag(containFirstFlag) {}
	virtual Iterator *GetSource();
	virtual bool DoNext(Environment &env, Value &value);
	virtual String ToString() const;
	virtual void GatherFollower(Environment::Frame *pFrame, EnvironmentSet &envSet);
};

//-----------------------------------------------------------------------------
// Iterator_Replace
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE Iterator_Replace : public Iterator {
private:
	AutoPtr<Iterator> _pIterator;
	Value _value;
	Value _valueReplace;
public:
	inline Iterator_Replace(Iterator *pIterator,
							const Value &value, const Value &valueReplace) :
			Iterator(pIterator->GetFiniteness()), _pIterator(pIterator),
			_value(value), _valueReplace(valueReplace) {}
	virtual Iterator *GetSource();
	virtual bool DoNext(Environment &env, Value &value);
	virtual String ToString() const;
	virtual void GatherFollower(Environment::Frame *pFrame, EnvironmentSet &envSet);
};

//-----------------------------------------------------------------------------
// Iterator_ReplaceInvalid
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE Iterator_ReplaceInvalid : public Iterator {
private:
	AutoPtr<Iterator> _pIterator;
	Value _valueReplace;
public:
	inline Iterator_ReplaceInvalid(Iterator *pIterator, const Value &valueReplace) :
			Iterator(pIterator->GetFiniteness()), _pIterator(pIterator),
			_valueReplace(valueReplace) {}
	virtual Iterator *GetSource();
	virtual bool DoNext(Environment &env, Value &value);
	virtual String ToString() const;
	virtual void GatherFollower(Environment::Frame *pFrame, EnvironmentSet &envSet);
};

//-----------------------------------------------------------------------------
// Iterator_Format
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE Iterator_Format : public Iterator {
private:
	AutoPtr<Iterator> _pIterator;
	String _format;
public:
	inline Iterator_Format(Iterator *pIterator, const char *format) :
			Iterator(pIterator->GetFiniteness()),
			_pIterator(pIterator), _format(format) {}
	virtual Iterator *GetSource();
	virtual bool DoNext(Environment &env, Value &value);
	virtual String ToString() const;
	virtual void GatherFollower(Environment::Frame *pFrame, EnvironmentSet &envSet);
};

//-----------------------------------------------------------------------------
// Iterator_Pack
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE Iterator_Pack : public Iterator {
private:
	AutoPtr<Iterator> _pIterator;
	String _format;
public:
	inline Iterator_Pack(Iterator *pIterator, const char *format) :
			Iterator(pIterator->GetFiniteness()),
			_pIterator(pIterator), _format(format) {}
	virtual Iterator *GetSource();
	virtual bool DoNext(Environment &env, Value &value);
	virtual String ToString() const;
	virtual void GatherFollower(Environment::Frame *pFrame, EnvironmentSet &envSet);
};

//-----------------------------------------------------------------------------
// Iterator_Zipv
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE Iterator_Zipv : public Iterator {
private:
	IteratorOwner _iterOwner;
public:
	inline Iterator_Zipv(const IteratorOwner &iterOwner) :
		Iterator(iterOwner.IsInfinite()? Infinite : Finite), // must be revised later
		_iterOwner(iterOwner) {}
	virtual Iterator *GetSource();
	virtual bool DoNext(Environment &env, Value &value);
	virtual String ToString() const;
	virtual void GatherFollower(Environment::Frame *pFrame, EnvironmentSet &envSet);
};

//-----------------------------------------------------------------------------
// Iterator_RunLength
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE Iterator_RunLength : public Iterator {
private:
	AutoPtr<Iterator> _pIterator;
	int _cnt;
	bool _doneFlag;
	Value _valuePrev;
public:
	inline Iterator_RunLength(Iterator *pIterator) :
		Iterator(pIterator->IsInfinite()? Infinite : Finite), _pIterator(pIterator),
		_cnt(0), _doneFlag(false) {}
	virtual Iterator *GetSource();
	virtual bool DoNext(Environment &env, Value &value);
	virtual String ToString() const;
	virtual void GatherFollower(Environment::Frame *pFrame, EnvironmentSet &envSet);
};

//-----------------------------------------------------------------------------
// Iterator_Align
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE Iterator_Align : public Iterator {
private:
	AutoPtr<Iterator> _pIterator;
	int _cnt;
	Value _valueFill;
public:
	inline Iterator_Align(Iterator *pIterator, int cnt, const Value &valueFill) :
		Iterator(Finite), _pIterator(pIterator), _cnt(cnt), _valueFill(valueFill) {}
	virtual Iterator *GetSource();
	virtual bool DoNext(Environment &env, Value &value);
	virtual String ToString() const;
	virtual void GatherFollower(Environment::Frame *pFrame, EnvironmentSet &envSet);
};

//-----------------------------------------------------------------------------
// Iterator_Head
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE Iterator_Head : public Iterator {
private:
	AutoPtr<Iterator> _pIterator;
	int _cnt;
public:
	inline Iterator_Head(Iterator *pIterator, int cnt) :
						Iterator(Finite), _pIterator(pIterator), _cnt(cnt) {}
	virtual Iterator *GetSource();
	virtual bool DoNext(Environment &env, Value &value);
	virtual String ToString() const;
	virtual void GatherFollower(Environment::Frame *pFrame, EnvironmentSet &envSet);
};

//-----------------------------------------------------------------------------
// Iterator_Fold
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE Iterator_Fold : public Iterator {
private:
	AutoPtr<Iterator> _pIterator;
	size_t _cnt;
	size_t _cntStep;
	bool _listItemFlag;
	bool _neatFlag;
	ValueList _valListRemain;
	bool _doneFlag;
public:
	inline Iterator_Fold(Iterator *pIterator, size_t cnt,
						 size_t cntStep, bool listItemFlag, bool neatFlag) :
		Iterator(pIterator->IsInfinite()? Infinite : Finite), // must be revised later
		_pIterator(pIterator), _cnt(cnt), _cntStep(cntStep),
		_listItemFlag(listItemFlag), _neatFlag(neatFlag), _doneFlag(false) {}
	virtual Iterator *GetSource();
	virtual bool DoNext(Environment &env, Value &value);
	virtual String ToString() const;
	virtual void GatherFollower(Environment::Frame *pFrame, EnvironmentSet &envSet);
};

//-----------------------------------------------------------------------------
// Iterator_Concat
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE Iterator_Concat : public Iterator {
private:
	IteratorOwner _iterOwner;
	IteratorOwner::iterator _ppIterator;
public:
	inline Iterator_Concat() : Iterator(Finite), _ppIterator(_iterOwner.begin()) {}
	virtual Iterator *GetSource();
	virtual bool DoNext(Environment &env, Value &value);
	virtual String ToString() const;
	void Add(Iterator *pIterator);
	virtual void GatherFollower(Environment::Frame *pFrame, EnvironmentSet &envSet);
};

//-----------------------------------------------------------------------------
// Iterator_Flatten
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE Iterator_Flatten : public Iterator {
public:
	enum Mode {
		MODE_DepthFirstSearch,
		MODE_BreadthFirstSearch,
	};
private:
	IteratorDeque _iterDeque;
	Iterator *_pIteratorCur;
	Mode _mode;
public:
	Iterator_Flatten(Iterator *pIterator, Mode mode);
	~Iterator_Flatten();
	virtual Iterator *GetSource();
	virtual bool DoNext(Environment &env, Value &value);
	virtual String ToString() const;
	virtual void GatherFollower(Environment::Frame *pFrame, EnvironmentSet &envSet);
};

//-----------------------------------------------------------------------------
// Iterator_Repeater
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE Iterator_Repeater : public Iterator {
private:
	AutoPtr<Environment> _pEnv;
	AutoPtr<Function> _pFuncBlock;
	bool _genIterFlag;
	AutoPtr<Iterator> _pIteratorNest;
	AutoPtr<Iterator> _pIteratorSrc;
	int _idx;
	bool _doneFlag;
public:
	Iterator_Repeater(Environment *pEnv, Function *pFuncBlock,
			bool skipInvalidFlag, bool genIterFlag, Iterator *pIteratorSrc);
	virtual Iterator *GetSource();
	virtual bool DoNext(Environment &env, Value &value);
	virtual String ToString() const;
	virtual void GatherFollower(Environment::Frame *pFrame, EnvironmentSet &envSet);
};

//-----------------------------------------------------------------------------
// Iterator_repeat
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE Iterator_repeat : public Iterator {
private:
	AutoPtr<Environment> _pEnv;
	AutoPtr<Function> _pFuncBlock;
	bool _genIterFlag;
	AutoPtr<Iterator> _pIteratorNest;
	int _cnt;
	int _idx;
	bool _doneFlag;
	AutoPtr<Argument> _pArg;
public:
	Iterator_repeat(Environment *pEnv, Function *pFuncBlock,
					bool skipInvalidFlag, bool genIterFlag, int cnt);
	virtual Iterator *GetSource();
	virtual bool DoNext(Environment &env, Value &value);
	virtual String ToString() const;
	virtual void GatherFollower(Environment::Frame *pFrame, EnvironmentSet &envSet);
};

//-----------------------------------------------------------------------------
// Iterator_while
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE Iterator_while : public Iterator {
private:
	AutoPtr<Environment> _pEnv;
	AutoPtr<Function> _pFuncBlock;
	bool _genIterFlag;
	AutoPtr<Iterator> _pIteratorNest;
	AutoPtr<Expr> _pExpr;
	int _idx;
	bool _doneFlag;
	AutoPtr<Argument> _pArg;
public:
	Iterator_while(Environment *pEnv, Function *pFuncBlock,
					bool skipInvalidFlag, bool genIterFlag, Expr *pExpr);
	virtual Iterator *GetSource();
	virtual bool DoNext(Environment &env, Value &value);
	virtual String ToString() const;
	virtual void GatherFollower(Environment::Frame *pFrame, EnvironmentSet &envSet);
};

//-----------------------------------------------------------------------------
// Iterator_for
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE Iterator_for : public Iterator {
private:
	AutoPtr<Environment> _pEnv;
	AutoPtr<Function> _pFuncBlock;
	bool _genIterFlag;
	AutoPtr<Iterator> _pIteratorNest;
	ExprList _exprLeftList;
	IteratorOwner _iteratorOwner;
	int _idx;
	bool _doneFlag;
	AutoPtr<Argument> _pArg;
public:
	Iterator_for(Environment *pEnv, Function *pFuncBlock,
			bool skipInvalidFlag, bool genIterFlag, const ValueList &valListArg);
	virtual Iterator *GetSource();
	virtual bool DoNext(Environment &env, Value &value);
	virtual String ToString() const;
	virtual void GatherFollower(Environment::Frame *pFrame, EnvironmentSet &envSet);
};

//-----------------------------------------------------------------------------
// Iterator_cross
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE Iterator_cross : public Iterator {
private:
	AutoPtr<Environment> _pEnv;
	AutoPtr<Function> _pFuncBlock;
	bool _genIterFlag;
	AutoPtr<Iterator> _pIteratorNest;
	ExprList _exprLeftList;
	IteratorOwner _iteratorOwner;
	IteratorOwner _iteratorOwnerOrg;
	ValueList _valListArg;
	int _idx;
	bool _doneFlag;
	AutoPtr<Argument> _pArg;
public:
	Iterator_cross(Environment *pEnv, Function *pFuncBlock,
			bool skipInvalidFlag, bool genIterFlag, const ValueList &valListArg);
	virtual Iterator *GetSource();
	virtual bool DoNext(Environment &env, Value &value);
	virtual String ToString() const;
	virtual void GatherFollower(Environment::Frame *pFrame, EnvironmentSet &envSet);
private:
	bool AdvanceIterators(Environment &env);
};

}

#endif
