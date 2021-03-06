//=============================================================================
// Gura class: operator
//=============================================================================
#include "stdafx.h"

namespace Gura {

static const char *helpDoc_en = R"**(
# Overview

The `operator` class provides measures to assign operators with a user-defined procedure.


# Property

An `operator` instance has the following properties:

${markdown.makedoc@property(`en, operator)}


# Constructor

${markdown.makedoc@function(`en
operator
)}


# Method

${markdown.makedoc@function(`en
operator.assign
operator.entries
)}
)**";

//-----------------------------------------------------------------------------
// Object_operator
//-----------------------------------------------------------------------------
Object_operator::Object_operator(const Object_operator &obj) :
	Object(obj), _opTypeUnary(obj._opTypeUnary), _opTypeBinary(obj._opTypeBinary)
{
}

Object *Object_operator::Clone() const
{
	return new Object_operator(*this);
}

String Object_operator::ToString(bool exprFlag)
{
	String rtn;
	rtn += "<operator:";
	rtn += GetSymbol()->GetName();
	rtn += ">";
	return rtn;
}

Value Object_operator::DoCall(
	Environment &env, const CallerInfo &callerInfo, ULong flags,
	const Value &valueThis, const Iterator *pIteratorThis,
	const TrailCtrlHolder *pTrailCtrlHolder)
{
	Signal &sig = env.GetSignal();
	const ExprList &exprListArg = callerInfo.GetExprListArg();
	if (exprListArg.size() == 1) {
		if (_opTypeUnary == OPTYPE_None) {
			sig.SetError(ERR_ArgumentError,
						 "operator '%s' is not a unary one", GetSymbol()->GetName());
			return Value::Nil;
		}
		return GetOperator(_opTypeUnary)->ExecUnary(env, exprListArg[0]);
	} else if (exprListArg.size() == 2) {
		if (_opTypeBinary == OPTYPE_None) {
			sig.SetError(ERR_ArgumentError,
						 "operator '%s' is not a binary one", GetSymbol()->GetName());
			return Value::Nil;
		}
		return GetOperator(_opTypeBinary)->ExecBinary(env, exprListArg[0], exprListArg[1]);
	} else {
		sig.SetError(ERR_ArgumentError, "operator must take one or two arguments");
		return Value::Nil;
	}
}

const Symbol *Object_operator::GetSymbol() const
{
	const Operator *pOperator = GetOperator(
			(_opTypeUnary != OPTYPE_None)? _opTypeUnary : _opTypeBinary);
	return pOperator->GetSymbol();
}

//-----------------------------------------------------------------------------
// Implementation of functions
//-----------------------------------------------------------------------------
// operator(symbol:symbol) {block?}
Gura_DeclareFunctionAlias(operator_, "operator")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "symbol", VTYPE_symbol);
	DeclareBlock(OCCUR_ZeroOrOnce);
	SetClassToConstruct(env.LookupClass(VTYPE_operator));
	AddHelp(
		Gura_Symbol(en), 
		"Creates an `operator` instance that is associated with the specified symbol.\n"
		"\n"
		GURA_HELPTEXT_BLOCK_en("op", "operator")
		"\n"
		"Below is an example to create an `operator` instance that is associated with the plus symbol.\n"
		"\n"
		"    op = operator(`+)\n");
}

Gura_ImplementFunction(operator_)
{
	Signal &sig = env.GetSignal();
	const Symbol *pSymbolOp = arg.GetSymbol(0);
	OpType opTypeUnary = Operator::LookupUnaryOpType(pSymbolOp->GetName());
	OpType opTypeBinary = Operator::LookupBinaryOpType(pSymbolOp->GetName());
	if (opTypeUnary == OPTYPE_None && opTypeBinary == OPTYPE_None) {
		sig.SetError(ERR_ValueError,
			"invalid symbol for operator: '%s'", pSymbolOp->GetName());
		return Value::Nil;
	}
	Object_operator *pObj = new Object_operator(env, opTypeUnary, opTypeBinary);
	return ReturnValue(env, arg, Value(pObj));
}

//-----------------------------------------------------------------------------
// Implementation of methods
//-----------------------------------------------------------------------------
// operator#symbol
Gura_DeclareProperty_R(operator_, symbol)
{
	SetPropAttr(VTYPE_symbol);
	AddHelp(
		Gura_Symbol(en),
		"A `symbol` instance that represents the operator's type.");
}

Gura_ImplementPropertyGetter(operator_, symbol)
{
	Object_operator *pObjThis = Object_operator::GetObject(valueThis);
	return Value(pObjThis->GetSymbol());
}

//-----------------------------------------------------------------------------
// Implementation of methods
//-----------------------------------------------------------------------------
// operator#assign(type_l:expr, type_r?:expr):map:void {block}
Gura_DeclareMethod(operator_, assign)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "type_l", VTYPE_expr);
	DeclareArg(env, "type_r", VTYPE_expr, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_Once);
	AddHelp(
		Gura_Symbol(en),
		"Associates the `operator` instance with a procedure described in `block`\n"
		"that takes values as a block parameter and returns its operation result.\n"
		"\n"
		"Some `operator` instances have two forms of expression: unary and binary.\n"
		"This method assignes the procedure to one of them according to\n"
		"how it takes its arguments as below:"
		"\n"
		"- `operator#assign(type:expr)` .. Assigns procedure to the unary form.\n"
		"- `operator#assign(type_l:expr, type_r:expr)` .. Assignes procedure to the binary form.\n"
		"\n"
		"They take different format of block parameters as below:\n"
		"\n"
		"- `|value|` .. For unary form.\n"
		"- `|value_l, value_r|` .. For binary form.\n"
		"\n"
		"Below is an example to assign a procedure to a unary form of operator `-`.\n"
		"\n"
		"    operator(`-).assign(`string) = {|value|\n"
		"        // any job\n"
		"    }\n"
		"\n"
		"Below is an example to assign a procedure to a binary form of operator `-`.\n"
		"\n"
		"    operator(`-).assign(`string, `number) = {|value_l, value_r|\n"
		"        // any job\n"
		"    }\n"
		"\n");
}

Gura_ImplementMethod(operator_, assign)
{
	Object_operator *pThis = Object_operator::GetObjectThis(arg);
	const Function *pFuncBlock = arg.GetBlockFunc(env, GetSymbolForBlock());
	if (pFuncBlock == nullptr) return Value::Nil;
	OperatorEntryCustom *pOperatorEntry = nullptr;
	if (arg.IsValid(1)) {
		// assign binary operator
		OpType opType = pThis->GetBinaryOpType();
		if (opType == OPTYPE_None) {
			env.SetError(ERR_ValueError,
				"operator '%s' is not a binary one", pThis->GetSymbol()->GetName());
			return Value::Nil;
		}
		const ValueTypeInfo *pValueTypeInfoL = env.LookupValueType(arg.GetExpr(0));
		if (pValueTypeInfoL == nullptr) return Value::Nil;
		const ValueTypeInfo *pValueTypeInfoR = env.LookupValueType(arg.GetExpr(1));
		if (pValueTypeInfoR == nullptr) return Value::Nil;
		pOperatorEntry = new OperatorEntryCustom(opType,
					pValueTypeInfoL->GetValueType(), pValueTypeInfoR->GetValueType(),
					Function::Reference(pFuncBlock));
	} else {
		// assign unary operator
		OpType opType = pThis->GetUnaryOpType();
		if (opType == OPTYPE_None) {
			env.SetError(ERR_ValueError,
				"operator '%s' is not a unary one", pThis->GetSymbol()->GetName());
			return Value::Nil;
		}
		const ValueTypeInfo *pValueTypeInfo = env.LookupValueType(arg.GetExpr(0));
		if (pValueTypeInfo == nullptr) return Value::Nil;
		pOperatorEntry = new OperatorEntryCustom(opType,
					pValueTypeInfo->GetValueType(), VTYPE_undefined,
					Function::Reference(pFuncBlock));
	}
	Operator::Assign(env, pOperatorEntry);
	return Value::Nil;
}

// operator#entries(type?:symbol)
Gura_DeclareMethod(operator_, entries)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "type", VTYPE_symbol, OCCUR_ZeroOrOnce);
	AddHelp(
		Gura_Symbol(en),
		"Returns a list that contains type expressions\n"
		"that the operator can accept as its arguments.\n"
		"\n"
		"The argument `type` takes a symbol `` `binary`` or `` `unary``.\n"
		"\n"
		"- If it's omitted or specified with `` `binary``,\n"
		"  the method would return a list of pairs of type expressions\n"
		"  for its left element and right one.\n"
		"- If it's specified with `` `unary``, the method would return a list of type expressions\n"
		"  for its single element.\n");
}

Gura_ImplementMethod(operator_, entries)
{
	Signal &sig = env.GetSignal();
	Object_operator *pThis = Object_operator::GetObjectThis(arg);
	Value rtn;
	Object_list *pObjList = rtn.InitAsList(env);
	if (arg.IsInvalid(0) || arg.GetSymbol(0)->IsIdentical(Gura_Symbol(binary))) {
		OpType opType = pThis->GetBinaryOpType();
		if (opType == OPTYPE_None) {
			sig.SetError(ERR_ValueError,
				"operator '%s' is not a binary one", pThis->GetSymbol()->GetName());
			return Value::Nil;
		}
		const Operator *pOperator = env.GetOperator(opType);
		const Operator::EntryDict &entryDict = pOperator->GetEntryDict();
		foreach_const (Operator::EntryDict, iter, entryDict) {
			Operator::Key key = iter->first;
			ValueType valTypeLeft = Operator::ExtractValueTypeLeft(key);
			ValueType valTypeRight = Operator::ExtractValueTypeRight(key);
			Expr *pExprLeft = ValueTypeInfo::MakeExpr(valTypeLeft);
			Expr *pExprRight = ValueTypeInfo::MakeExpr(valTypeRight);
			pObjList->Add(Value::CreateList(env,
				Value(new Object_expr(env, pExprLeft)), Value(new Object_expr(env, pExprRight))));
		}
	} else if (arg.GetSymbol(0)->IsIdentical(Gura_Symbol(unary))) {
		OpType opType = pThis->GetUnaryOpType();
		if (opType == OPTYPE_None) {
			sig.SetError(ERR_ValueError,
				"operator '%s' is not a unary one", pThis->GetSymbol()->GetName());
			return Value::Nil;
		}
		const Operator *pOperator = env.GetOperator(opType);
		const Operator::EntryDict &entryDict = pOperator->GetEntryDict();
		foreach_const (Operator::EntryDict, iter, entryDict) {
			Operator::Key key = iter->first;
			ValueType valType = Operator::ExtractValueType(key);
			Expr *pExpr = ValueTypeInfo::MakeExpr(valType);
			pObjList->Add(Value(new Object_expr(env, pExpr)));
		}
	} else {
		sig.SetError(ERR_ValueError, "invalid symbol: %s", arg.GetSymbol(0)->GetName());
		return Value::Nil;
	}
	return rtn;
}

//-----------------------------------------------------------------------------
// Class implementation
//-----------------------------------------------------------------------------
Class_operator::Class_operator(Environment *pEnvOuter) : ClassFundamental(pEnvOuter, VTYPE_operator)
{
}

void Class_operator::DoPrepare(Environment &env)
{
	// Assignment of function
	Gura_AssignFunction(operator_);
	// Assignment of properties
	Gura_AssignProperty(operator_, symbol);
	// Assignment of methods
	Gura_AssignMethod(operator_, assign);
	Gura_AssignMethod(operator_, entries);
	// help document
	AddHelpTemplate(env, Gura_Symbol(en), helpDoc_en);
}

Object *Class_operator::CreateDescendant(Environment &env, Class *pClass)
{
	GURA_ERROREND(env, "this function must not be called");
	return nullptr;
}

}
