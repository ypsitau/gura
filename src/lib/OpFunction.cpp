#include "stdafx.h"

namespace Gura {

//-----------------------------------------------------------------------------
// Operator assignment
//-----------------------------------------------------------------------------
void AssignOpFunctions(Environment &env)
{
	Environment::Global *pGlobal = env.GetGlobal();
	pGlobal->_pOpFuncTbl[OPTYPE_Pos]		= new Func_Pos(env);
	pGlobal->_pOpFuncTbl[OPTYPE_Neg]		= new Func_Neg(env);
	pGlobal->_pOpFuncTbl[OPTYPE_Inv]		= new Func_Inv(env);
	pGlobal->_pOpFuncTbl[OPTYPE_Not]		= new Func_Not(env);
	pGlobal->_pOpFuncTbl[OPTYPE_Add]		= new Func_Add(env);
	pGlobal->_pOpFuncTbl[OPTYPE_Sub]		= new Func_Sub(env);
	pGlobal->_pOpFuncTbl[OPTYPE_Mul]		= new Func_Mul(env);
	pGlobal->_pOpFuncTbl[OPTYPE_Div]		= new Func_Div(env);
	pGlobal->_pOpFuncTbl[OPTYPE_Mod]		= new Func_Mod(env);
	pGlobal->_pOpFuncTbl[OPTYPE_Pow]		= new Func_Pow(env);
	pGlobal->_pOpFuncTbl[OPTYPE_Eq]			= new Func_Eq(env);
	pGlobal->_pOpFuncTbl[OPTYPE_Ne]			= new Func_Ne(env);
	pGlobal->_pOpFuncTbl[OPTYPE_Gt]			= new Func_Gt(env);
	pGlobal->_pOpFuncTbl[OPTYPE_Lt]			= new Func_Lt(env);
	pGlobal->_pOpFuncTbl[OPTYPE_Ge]			= new Func_Ge(env);
	pGlobal->_pOpFuncTbl[OPTYPE_Le]			= new Func_Le(env);
	pGlobal->_pOpFuncTbl[OPTYPE_Cmp]		= new Func_Cmp(env);
	pGlobal->_pOpFuncTbl[OPTYPE_Contains]	= new Func_Contains(env);
	pGlobal->_pOpFuncTbl[OPTYPE_Or]			= new Func_Or(env);
	pGlobal->_pOpFuncTbl[OPTYPE_And]		= new Func_And(env);
	pGlobal->_pOpFuncTbl[OPTYPE_Xor]		= new Func_Xor(env);
	pGlobal->_pOpFuncTbl[OPTYPE_Shl]		= new Func_Shl(env);
	pGlobal->_pOpFuncTbl[OPTYPE_Shr]		= new Func_Shr(env);
	pGlobal->_pOpFuncTbl[OPTYPE_OrOr]		= new Func_OrOr(env);
	pGlobal->_pOpFuncTbl[OPTYPE_AndAnd]		= new Func_AndAnd(env);
	pGlobal->_pOpFuncTbl[OPTYPE_Seq]		= new Func_Seq(env);
	pGlobal->_pOpFuncTbl[OPTYPE_SeqInf]		= new Func_SeqInf(env);
}

//-----------------------------------------------------------------------------
// FuncUnaryOperator
//-----------------------------------------------------------------------------
FuncUnaryOperator::FuncUnaryOperator(Environment &env, const Symbol *pSymbol,
				Parser::ElemType elemType, OpType opType,
				unsigned long flags, ValueType valType) :
		Function(env, pSymbol, FUNCTYPE_Function, FLAG_None)
{
	SetOperatorInfo(elemType, opType);
	SetMode(RSLTMODE_Normal, flags);
	DeclareArg(env, "n", valType);
}

Value FuncUnaryOperator::DoEval(Environment &env, Signal sig, Args &args) const
{
	const Value &value = args.GetValue(0);
	return Operator::EvalUnary(env, sig, GetOpType(), value);
}

Expr *FuncUnaryOperator::DiffUnary(Environment &env, Signal sig,
							const Expr *pExprArg, const Symbol *pSymbol) const
{
	Operator *pOperator = env.GetGlobal()->GetOperator(GetOpType());
	return pOperator->DiffUnary(env, sig, pExprArg, pSymbol);
}

Expr *FuncUnaryOperator::OptimizeUnary(Environment &env, Signal sig, Expr *pExprOpt) const
{
	Operator *pOperator = env.GetGlobal()->GetOperator(GetOpType());
	return pOperator->OptimizeUnary(env, sig, pExprOpt);
}

//-----------------------------------------------------------------------------
// FuncBinaryOperator
//-----------------------------------------------------------------------------
FuncBinaryOperator::FuncBinaryOperator(Environment &env, const Symbol *pSymbol,
				Parser::ElemType elemType, OpType opType,
				unsigned long flags, ValueType valType) :
		Function(env, pSymbol, FUNCTYPE_Function, FLAG_None)
{
	SetOperatorInfo(elemType, opType);
	SetMode(RSLTMODE_Normal, flags);
	DeclareArg(env, "n", valType);
	DeclareArg(env, "m", valType);
}

Value FuncBinaryOperator::DoEval(Environment &env, Signal sig, Args &args) const
{
	const Value &valueLeft = args.GetValue(0);
	const Value &valueRight = args.GetValue(1);
	return Operator::EvalBinary(env, sig, GetOpType(), valueLeft, valueRight);
}

Expr *FuncBinaryOperator::DiffBinary(Environment &env, Signal sig,
		const Expr *pExprArg1, const Expr *pExprArg2, const Symbol *pSymbol) const
{
	Operator *pOperator = env.GetGlobal()->GetOperator(GetOpType());
	return pOperator->DiffBinary(env, sig, pExprArg1, pExprArg2, pSymbol);
}

Expr *FuncBinaryOperator::OptimizeBinary(Environment &env, Signal sig,
									Expr *pExprOpt1, Expr *pExprOpt2) const
{
	Operator *pOperator = env.GetGlobal()->GetOperator(GetOpType());
	return pOperator->OptimizeBinary(env, sig, pExprOpt1, pExprOpt2);
}

//-----------------------------------------------------------------------------
// +n
//-----------------------------------------------------------------------------
bool Func_Pos::IsPos() const { return true; }

Func_Pos::Func_Pos(Environment &env) : FuncUnaryOperator(env,
				Symbol::Add("__pos__"), Parser::ETYPE_Add, OPTYPE_Pos)
{
}

//-----------------------------------------------------------------------------
// -n
//-----------------------------------------------------------------------------
bool Func_Neg::IsNeg() const { return true; }

Func_Neg::Func_Neg(Environment &env) : FuncUnaryOperator(env,
				Symbol::Add("__neg__"), Parser::ETYPE_Sub, OPTYPE_Neg)
{
}

//-----------------------------------------------------------------------------
// ~x
//-----------------------------------------------------------------------------
Func_Inv::Func_Inv(Environment &env) : FuncUnaryOperator(env,
				Symbol::Add("__inv__"), Parser::ETYPE_Inv, OPTYPE_Inv)
{
}

//-----------------------------------------------------------------------------
// !n
//-----------------------------------------------------------------------------
Func_Not::Func_Not(Environment &env) : FuncUnaryOperator(env,
				Symbol::Add("__not__"), Parser::ETYPE_Not, OPTYPE_Not)
{
}

//-----------------------------------------------------------------------------
// n ..
//-----------------------------------------------------------------------------
Func_SeqInf::Func_SeqInf(Environment &env) : FuncUnaryOperator(env,
				Symbol::Add("__seqinf__"), Parser::ETYPE_Seq, OPTYPE_SeqInf)
{
}

//-----------------------------------------------------------------------------
// n + m
//-----------------------------------------------------------------------------
bool Func_Add::IsAdd() const { return true; }

Func_Add::Func_Add(Environment &env) : FuncBinaryOperator(env,
				Symbol::Add("__add__"), Parser::ETYPE_Add, OPTYPE_Add)
{
}

//-----------------------------------------------------------------------------
// n - m
//-----------------------------------------------------------------------------
bool Func_Sub::IsSub() const { return true; }

Func_Sub::Func_Sub(Environment &env) : FuncBinaryOperator(env,
				Symbol::Add("__sub__"), Parser::ETYPE_Sub, OPTYPE_Sub)
{
}

//-----------------------------------------------------------------------------
// n * m
//-----------------------------------------------------------------------------
bool Func_Mul::IsMul() const { return true; }

Func_Mul::Func_Mul(Environment &env) : FuncBinaryOperator(env,
				Symbol::Add("__mul__"), Parser::ETYPE_Mul, OPTYPE_Mul)
{
}

Value Func_Mul::EvalExpr(Environment &env, Signal sig, Args &args) const
{
	const ExprList &exprListArg = args.GetExprListArg();
	ValueList valListArg;
	Value valueWithDict;
	valueWithDict.InitAsDict(env, false);
	if (!_declOwner.PrepareArgs(env, sig, exprListArg, valListArg, valueWithDict)) {
		return Value::Null;
	}
	const Value &valueLeft = valListArg[0];
	const Value &valueRight = valListArg[1];
	Args argsSub(args, valListArg, valueWithDict, _resultMode, _flags);
	if (valueLeft.IsFunction()) {
		const Function *pFunc = valueLeft.GetFunction();
		if (pFunc->IsUnary()) {
			// nothing to do
		} else if (valueRight.IsList()) {
			const ValueList &valList = valueRight.GetList();
			if (valList.IsFlat()) {
				ValueList valListComp = valList;
				if (!pFunc->GetDeclOwner().Compensate(env, sig, valListComp)) {
					return Value::Null;
				}
				const Function *pFuncLeader = NULL;
				Args argsSub(valListComp, Value::Null, NULL, false, &pFuncLeader);
				return pFunc->Eval(env, sig, argsSub);
			}
			AutoPtr<Iterator> pIterator(valueRight.CreateIterator(sig));
			if (sig.IsSignalled()) return Value::Null;
			AutoPtr<Iterator> pIteratorFuncBinder(new Iterator_FuncBinder(env,
						Function::Reference(pFunc),
						Object_function::GetObject(valueLeft)->GetThis(), pIterator.release()));
			return pIteratorFuncBinder->Eval(env, sig, argsSub);
		} else if (valueRight.IsIterator()) {
			AutoPtr<Iterator> pIterator(valueRight.CreateIterator(sig));
			if (sig.IsSignalled()) return Value::Null;
			AutoPtr<Iterator> pIteratorFuncBinder(new Iterator_FuncBinder(env,
						Function::Reference(pFunc),
						Object_function::GetObject(valueLeft)->GetThis(), pIterator.release()));
			if (pFunc->IsRsltNormal() ||
						pFunc->IsRsltIterator() || pFunc->IsRsltXIterator()) {
				return Value(env, pIteratorFuncBinder.release());
			} else {
				return pIteratorFuncBinder->Eval(env, sig, argsSub);
			}
		}
	} else if (valueLeft.IsMatrix() && valueRight.IsList() ||
			   valueLeft.IsList() && valueRight.IsMatrix()) {
		return Eval(env, sig, argsSub);
	}
	if (_declOwner.ShouldImplicitMap(argsSub)) {
		return EvalMap(env, sig, argsSub);
	} else {
		return Eval(env, sig, argsSub);
	}
}

//-----------------------------------------------------------------------------
// n / m
//-----------------------------------------------------------------------------
bool Func_Div::IsDiv() const { return true; }

Func_Div::Func_Div(Environment &env) : FuncBinaryOperator(env,
				Symbol::Add("__div__"), Parser::ETYPE_Div, OPTYPE_Div)
{
}

//-----------------------------------------------------------------------------
// n % m
//-----------------------------------------------------------------------------
bool Func_Mod::IsMod() const { return true; }

Func_Mod::Func_Mod(Environment &env) : FuncBinaryOperator(env,
				Symbol::Add("mod"), Parser::ETYPE_Mod, OPTYPE_Mod)
{
}

Value Func_Mod::EvalExpr(Environment &env, Signal sig, Args &args) const
{
	const ExprList &exprListArg = args.GetExprListArg();
	ValueList valListArg;
	Value valueWithDict;
	valueWithDict.InitAsDict(env, false);
	if (!_declOwner.PrepareArgs(env, sig, exprListArg, valListArg, valueWithDict)) {
		return Value::Null;
	}
	const Value &valueLeft = valListArg[0];
	const Value &valueRight = valListArg[1];
	if (valueLeft.IsFunction()) {
		const Function *pFunc = valueLeft.GetFunction();
		Value result;
		if (!valueRight.IsList()) {
			ValueList valListArg(valueRight);
			Args argsSub(valListArg);
			result = pFunc->Eval(env, sig, argsSub);
		} else if (pFunc->GetMapFlag() == MAP_Off ||
				!pFunc->GetDeclOwner().ShouldImplicitMap(valueRight.GetList())) {
			Args argsSub(valueRight.GetList());
			result = pFunc->Eval(env, sig, argsSub);
		} else if (pFunc->IsUnary()) {
			ValueList valListArg(valueRight);
			Args argsSub(valListArg);
			result = pFunc->EvalMap(env, sig, argsSub);
		} else {
			Args argsSub(valueRight.GetList());
			result = pFunc->EvalMap(env, sig, argsSub);
		}
		return result;
	} else if (valueLeft.IsString()) {
		const char *format = valueLeft.GetString();
		if (!valueRight.IsList()) {
			String str = Formatter::Format(sig, format, ValueList(valueRight));
			if (sig.IsSignalled()) return Value::Null;
			return Value(env, str.c_str());
		} else {
			const ValueList &valList = valueRight.GetList();
			if (valList.IsFlat() && !valList.IsContainIterator()) {
				String str = Formatter::Format(sig, format, valList);
				if (sig.IsSignalled()) return Value::Null;
				return Value(env, str.c_str());
			} else {
				IteratorOwner iterOwner;
				foreach_const (ValueList, pValue, valList) {
					AutoPtr<Iterator> pIterator;
					if (pValue->IsList() || pValue->IsIterator()) {
						pIterator.reset(pValue->CreateIterator(sig));
						if (pIterator.IsNull()) return Value::Null;
					} else {
						pIterator.reset(new Iterator_Constant(*pValue));
					}
					iterOwner.push_back(pIterator.release());
				}
				return Formatter::Format(env, sig, format, iterOwner);
			}
		}
	}
	Args argsSub(args, valListArg, valueWithDict, _resultMode, _flags);
	if (_declOwner.ShouldImplicitMap(valListArg)) {
		return EvalMap(env, sig, argsSub);
	} else {
		return Eval(env, sig, argsSub);
	}
}

//-----------------------------------------------------------------------------
// n ** m
//-----------------------------------------------------------------------------
bool Func_Pow::IsPow() const { return true; }

Func_Pow::Func_Pow(Environment &env) : FuncBinaryOperator(env,
				Symbol::Add("__pow__"), Parser::ETYPE_Pow, OPTYPE_Pow)
{
}

//-----------------------------------------------------------------------------
// n == m
//-----------------------------------------------------------------------------
Func_Eq::Func_Eq(Environment &env) : FuncBinaryOperator(env,
				Symbol::Add("__eq__"), Parser::ETYPE_Eq, OPTYPE_Eq)
{
}

//-----------------------------------------------------------------------------
// n != m
//-----------------------------------------------------------------------------
Func_Ne::Func_Ne(Environment &env) : FuncBinaryOperator(env,
				Symbol::Add("__ne__"), Parser::ETYPE_Ne, OPTYPE_Ne)
{
}

//-----------------------------------------------------------------------------
// n > m
//-----------------------------------------------------------------------------
Func_Gt::Func_Gt(Environment &env) : FuncBinaryOperator(env,
				Symbol::Add("__gt__"), Parser::ETYPE_Gt, OPTYPE_Gt)
{
}

//-----------------------------------------------------------------------------
// n < m
//-----------------------------------------------------------------------------
Func_Lt::Func_Lt(Environment &env) : FuncBinaryOperator(env,
				Symbol::Add("__lt__"), Parser::ETYPE_Lt, OPTYPE_Lt)
{
}

//-----------------------------------------------------------------------------
// n >= m
//-----------------------------------------------------------------------------
Func_Ge::Func_Ge(Environment &env) : FuncBinaryOperator(env,
				Symbol::Add("__ge__"), Parser::ETYPE_Ge, OPTYPE_Ge)
{
}

//-----------------------------------------------------------------------------
// n <= m
//-----------------------------------------------------------------------------
Func_Le::Func_Le(Environment &env) : FuncBinaryOperator(env,
				Symbol::Add("__le__"), Parser::ETYPE_Le, OPTYPE_Le)
{
}

//-----------------------------------------------------------------------------
// n <=> m
//-----------------------------------------------------------------------------
Func_Cmp::Func_Cmp(Environment &env) : FuncBinaryOperator(env,
				Symbol::Add("__cmp__"), Parser::ETYPE_Cmp, OPTYPE_Cmp)
{
}

//-----------------------------------------------------------------------------
// n in m
//-----------------------------------------------------------------------------
bool Func_Contains::IsContains() const { return true; }

Func_Contains::Func_Contains(Environment &env) : FuncBinaryOperator(env,
	Symbol::Add("in"), Parser::ETYPE_Contains, OPTYPE_Contains, FLAG_None)
{
}

//-----------------------------------------------------------------------------
// n | m
//-----------------------------------------------------------------------------
Func_Or::Func_Or(Environment &env) : FuncBinaryOperator(env,
				Symbol::Add("__or__"), Parser::ETYPE_Or, OPTYPE_Or)
{
}

//-----------------------------------------------------------------------------
// n & m
//-----------------------------------------------------------------------------
Func_And::Func_And(Environment &env) : FuncBinaryOperator(env,
				Symbol::Add("__and__"), Parser::ETYPE_And, OPTYPE_And)
{
}

//-----------------------------------------------------------------------------
// n ^ m
//-----------------------------------------------------------------------------
Func_Xor::Func_Xor(Environment &env) : FuncBinaryOperator(env,
				Symbol::Add("__xor__"), Parser::ETYPE_Xor, OPTYPE_Xor)
{
}

//-----------------------------------------------------------------------------
// n << m
//-----------------------------------------------------------------------------
Func_Shl::Func_Shl(Environment &env) : FuncBinaryOperator(env,
				Symbol::Add("__shl__"), Parser::ETYPE_Shl, OPTYPE_Shl)
{
}

//-----------------------------------------------------------------------------
// n >> m
//-----------------------------------------------------------------------------
Func_Shr::Func_Shr(Environment &env) : FuncBinaryOperator(env,
				Symbol::Add("__shr__"), Parser::ETYPE_Shr, OPTYPE_Shr)
{
}

//-----------------------------------------------------------------------------
// n || m
// this function takes quoted values as its arguments to implement
// a short-circuit evaluation.
//-----------------------------------------------------------------------------
Func_OrOr::Func_OrOr(Environment &env) : FuncBinaryOperator(env,
				Symbol::Add("__oror__"), Parser::ETYPE_OrOr, OPTYPE_OrOr, FLAG_None, VTYPE_quote)
{
}

//-----------------------------------------------------------------------------
// n && m
// this function takes quoted values as its arguments to implement
// a short-circuit evaluation.
//-----------------------------------------------------------------------------
Func_AndAnd::Func_AndAnd(Environment &env) : FuncBinaryOperator(env,
				Symbol::Add("__andand__"), Parser::ETYPE_AndAnd, OPTYPE_AndAnd, FLAG_None, VTYPE_quote)
{
}

//-----------------------------------------------------------------------------
// n .. m
//-----------------------------------------------------------------------------
bool Func_Seq::IsSeq() const { return true; }

Func_Seq::Func_Seq(Environment &env) : FuncBinaryOperator(env,
				Symbol::Add("__seq__"), Parser::ETYPE_Seq, OPTYPE_Seq)
{
}

}
