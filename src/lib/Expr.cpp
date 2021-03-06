//=============================================================================
// Expr
//=============================================================================
#include "stdafx.h"

namespace Gura {

static const int MaxCharsForBriefStyle = 32;
static const int MaxBytesForBriefStyle = 32;

//-----------------------------------------------------------------------------
// ExprType
//-----------------------------------------------------------------------------
const char *GetExprTypeName(ExprType exprType)
{
	static const struct {
		ExprType exprType;
		const char *name;
	} tbl[] = {
		{ EXPRTYPE_Value,			"value",			},
		{ EXPRTYPE_Identifier,		"identifier",		},
		{ EXPRTYPE_Suffixed,		"suffixed",			},
		{ EXPRTYPE_Member,			"member",			},
		{ EXPRTYPE_UnaryOp,			"unaryop",			},
		{ EXPRTYPE_Quote,			"quote",			},
		{ EXPRTYPE_BinaryOp,		"binaryop",			},
		{ EXPRTYPE_Assign,			"assign",			},
		{ EXPRTYPE_Root,			"root",				},
		{ EXPRTYPE_Block,			"block",			},
		{ EXPRTYPE_Lister,			"lister",			},
		{ EXPRTYPE_Iterer,			"iterer",			},
		{ EXPRTYPE_Indexer,			"indexer",			},
		{ EXPRTYPE_Caller,			"caller",			},
	};
	for (size_t i = 0; i < ArraySizeOf(tbl); i++) {
		if (tbl[i].exprType == exprType) return tbl[i].name;
	}
	return "unknown";
}

//-----------------------------------------------------------------------------
// InteractiveHandler
//-----------------------------------------------------------------------------
InteractiveHandler::~InteractiveHandler()
{
}

//-----------------------------------------------------------------------------
// Expr
// [class hierarchy under Expr]
// Expr <-+- Expr_Value
//        +- Expr_EmbedString
//        +- Expr_Identifier
//        +- Expr_Suffixed
//        +- Expr_Member
//        +- Expr_Unary <-----+- Expr_UnaryOp
//        |                   `- Expr_Quote
//        +- Expr_Binary <----+- Expr_BinaryOp
//        |                   `- Expr_Assign
//        +- Expr_Collector <-+- Expr_Root
//        |                   +- Expr_Block
//        |                   +- Expr_Lister
//        |                   `- Expr_Iterer
//        `- Expr_Compound <--+- Expr_Indexer
//                            `- Expr_Caller
//-----------------------------------------------------------------------------
const char *Expr::IndentDefault = "    ";

Expr::Expr(ExprType exprType) :
	_exprType(exprType), _cntRef(1), _lineNoTop(0), _lineNoBtm(0),
	_pExprParent(nullptr), _bridgeFunction(nullptr), _silentFlag(false)
{
}

Expr::Expr(const Expr &expr) :
	_exprType(expr._exprType), _cntRef(1), _lineNoTop(expr._lineNoTop), _lineNoBtm(expr._lineNoBtm),
	_pExprParent(nullptr), _pSourceName(StringShared::Reference(expr._pSourceName.get())),
	_bridgeFunction(expr._bridgeFunction), _silentFlag(expr._silentFlag)
{
}

Expr::~Expr()
{
}

Value Expr::Exec(Environment &env, bool evalSymFuncFlag) const
{
	Signal &sig = env.GetSignal();
	Value result;
	
	if (_bridgeFunction != nullptr) {
		(*_bridgeFunction)(env, Value::Nil, result);
	} else {
		result = DoExec(env);
	}
	if (sig.IsSignalled()) {
		sig.AddExprCause(this);
		return Value::Nil;
	}
	if (evalSymFuncFlag && result.Is_function() && result.GetFunction()->GetFlag(FLAG_SymbolFunc)) {
		// symbol functions are only evaluated by a sequence of block.
		// in the folloiwng example, "return" shall be evaluated by a block
		// of "if" function.
		//   repeat { if (flag) { return } }
		// in the following example, "&&" operator returns "return" function
		// object as its result, and then the block of "repeat" shall evaluate it.
		//   repeat { flag && return }
		Object_function *pFuncObj = Object_function::GetObject(result);
		AutoPtr<Argument> pArg(new Argument(pFuncObj->GetFunction()));
		pArg->SetValueThis(pFuncObj->GetValueThis());
		result = pFuncObj->GetFunction()->EvalAuto(env, *pArg);
		if (sig.IsSignalled()) {
			sig.AddExprCause(this);
			return Value::Nil;
		}
	}
	return result;
}

Value Expr::Assign(Environment &env, Value &valueAssigned, bool escalateFlag) const
{
	Signal &sig = env.GetSignal();
	Value result = DoAssign(env, valueAssigned, escalateFlag);
	if (sig.IsSignalled()) {
		sig.AddExprCause(this);
		return Value::Nil;
	}
	return result;
}

Value Expr::DoAssign(Environment &env, Value &valueAssigned, bool escalateFlag) const
{
	Signal &sig = env.GetSignal();
	SetError(sig, ERR_SyntaxError, "l-value is required");
	return Value::Nil;
}

Expr *Expr::MathDiff(Environment &env, const Symbol *pSymbol) const
{
	Signal &sig = env.GetSignal();
	SetError(sig, ERR_ValueError,
				"differential operation is not supported for this expression");
	return nullptr;
}

Expr *Expr::MathOptimize(Environment &env) const
{
	Signal &sig = env.GetSignal();
	SetError(sig, ERR_ValueError,
				"mathematical optimization is not supported for this expression");
	return nullptr;
}

Expr_Block *Expr::ToExprBlock() const
{
	if (IsBlock()) return dynamic_cast<Expr_Block *>(Expr::Reference(this));
	Expr_Block *pExprBlock = new Expr_Block();
	pExprBlock->AddExpr(Expr::Reference(this));
	return pExprBlock;
}

bool Expr::IsAtSameLine(const Expr *pExpr) const
{
	if (GetLineNoTop() != pExpr->GetLineNoTop()) return false;
	const char *sourceName1 = GetSourceName();
	const char *sourceName2 = pExpr->GetSourceName();
	if (sourceName1 == nullptr && sourceName2 == nullptr) return true;
	if (sourceName1 == nullptr || sourceName2 == nullptr) return false;
	return ::strcmp(sourceName1, sourceName2) == 0;
}

void Expr::GatherSymbol(SymbolSet &symbolSet) const
{
	ExprVisitor_GatherSymbol visitor(symbolSet);
	// It's guaranteed that visitor of ExprVisitor_GatherSymbol doesn't modify.
	const_cast<Expr *>(this)->Accept(visitor);
}

void Expr::GatherSimpleLambdaArgs(ExprOwner &exprOwnerArg) const
{
	ExprVisitor_GatherSimpleLambdaArgs visitor(exprOwnerArg);
	// It's guaranteed that visitor of ExprVisitor_GatherSimpleLambdaArgs doesn't modify.
	const_cast<Expr *>(this)->Accept(visitor);
}

const Expr *Expr::Unquote() const
{
	return this;
}

bool Expr::NeedParenthesis(const Operator *pOperatorOuter,
									const Operator *pOperator, bool rightFlag)
{
	int rtn = Token::CompareOpTypePrec(pOperatorOuter->GetOpType(), pOperator->GetOpType());
	if (rtn == 0) return rightFlag;
	return rtn > 0;
}

bool Expr::IsSymbol(const Symbol *pSymbol) const
{
	if (!IsIdentifier()) return false;
	return dynamic_cast<const Expr_Identifier *>(this)->GetSymbol()->IsIdentical(pSymbol);
}

bool Expr::IsConstNumber(Number num) const
{
	if (!IsValue()) return false;
	const Value &value = dynamic_cast<const Expr_Value *>(this)->GetValue();
	return value.Is_number() && value.GetNumber() == num;
}

bool Expr::IsConstEvenNumber() const
{
	if (!IsValue()) return false;
	const Value &value = dynamic_cast<const Expr_Value *>(this)->GetValue();
	return value.Is_number() && ::fmod(value.GetNumber(), 2) == 0;
}

bool Expr::IsConstNegNumber() const
{
	if (!IsValue()) return false;
	const Value &value = dynamic_cast<const Expr_Value *>(this)->GetValue();
	return value.Is_number() && value.GetNumber() < 0;
}

bool Expr::IsUnaryOp(OpType opType) const
{
	return IsUnaryOp() &&
		dynamic_cast<const Expr_UnaryOp *>(this)->GetOperator()->GetOpType() == opType;
}

bool Expr::IsBinaryOp(OpType opType) const
{
	return IsBinaryOp() &&
		dynamic_cast<const Expr_BinaryOp *>(this)->GetOperator()->GetOpType() == opType;
}

// type chekers - no ancestors
bool Expr::IsValue() const			{ return false; }
bool Expr::IsIdentifier() const		{ return false; }
bool Expr::IsSuffixed() const		{ return false; }
bool Expr::IsMember() const			{ return false; }
// type chekers - Unary and descendants
bool Expr::IsUnary() const			{ return false; }
bool Expr::IsUnaryOp() const		{ return false; }
bool Expr::IsUnaryOpSuffix() const	{ return false; }
bool Expr::IsQuote() const			{ return false; }
// type chekers - Binary and descendants
bool Expr::IsBinary() const			{ return false; }
bool Expr::IsBinaryOp() const		{ return false; }
bool Expr::IsAssign() const			{ return false; }
// type chekers - Collector and descendants
bool Expr::IsCollector() const		{ return false; }
bool Expr::IsRoot() const			{ return false; }
bool Expr::IsBlock() const			{ return false; }
bool Expr::IsLister() const			{ return false; }
bool Expr::IsIterer() const			{ return false; }
// type chekers - Compound and descendants
bool Expr::IsCompound() const		{ return false; }
bool Expr::IsIndexer() const		{ return false; }
bool Expr::IsCaller() const			{ return false; }

bool Expr::IsParentOf(const Expr *pExpr) const
{
	return false;
}

void Expr::SetError(Signal &sig, ErrorType errType, const char *format, ...) const
{
	va_list ap;
	va_start(ap, format);
	sig.SetErrorV(errType, format, ap);
	sig.AddExprCause(this);
	va_end(ap);
}

void Expr::SetError_NotAssignableSymbol(Signal &sig, const Symbol *pSymbol) const
{
	SetError(sig, ERR_ValueError,
		"symbol '%s' cannot be assigned in this object", pSymbol->GetName());
}

Callable *Expr::LookupCallable(Environment &env) const
{
	return nullptr;
}

bool Expr::SearchBar() const
{
	ExprVisitor_SearchBar visitor;
	const_cast<Expr *>(this)->Accept(visitor);
	return visitor.GetFoundFlag();
}

bool Expr::Prepare(Environment &env) const
{
	ExprVisitor_Prepare visitor(env);
	const_cast<Expr *>(this)->Accept(visitor);
	return !env.IsSignalled();
}

bool Expr::DoPrepare(Environment &env)
{
	return true;
}

bool Expr::GenerateCode(Environment &env, CodeGenerator &codeGenerator) const
{
	return false;
}

bool Expr::GenerateScript(Signal &sig, SimpleStream &stream,
								ScriptStyle scriptStyle, int nestLevel, const char *strIndent) const
{
	return false;
}

String Expr::ToString(ScriptStyle scriptStyle) const
{
	const char *strIndent = IndentDefault;
	Signal sig;
	String str;
	SimpleStream_StringWriter stream(str);
	GenerateScript(sig, stream, scriptStyle, 0, strIndent);
	return str;
}

String Expr::MakePosText() const
{
	String str;
	const char *sourceName = GetSourceName();
	if (sourceName == nullptr) {
		str += SRCNAME_unknown;
	} else {
		String fileName;
		PathMgr::SplitFileName(sourceName, nullptr, &fileName);
		str += fileName;
	}
	char buff[64];
	if (GetLineNoTop() == GetLineNoBtm()) {
		::sprintf(buff, ":%d", GetLineNoTop());
	} else {
		::sprintf(buff, ":%d-%d", GetLineNoTop(), GetLineNoBtm());
	}
	str += buff;
	return str;
}

bool Expr::PutNestIndent(Signal &sig, SimpleStream &stream, int nestLevel, const char *strIndent)
{
	for (int i = 0; i < nestLevel; i++) {
		stream.Print(sig, strIndent);
		if (sig.IsSignalled()) return false;
	}
	return true;
}

Expr::ScriptStyle Expr::SymbolToScriptStyle(const Symbol *pSymbol)
{
	if (pSymbol->IsIdentical(Gura_Symbol(crammed))) {
		return SCRSTYLE_Crammed;
	} else if (pSymbol->IsIdentical(Gura_Symbol(oneline))) {
		return SCRSTYLE_OneLine;
	} else if (pSymbol->IsIdentical(Gura_Symbol(brief))) {
		return SCRSTYLE_Brief;
	} else if (pSymbol->IsIdentical(Gura_Symbol(fancy))) {
		return SCRSTYLE_Fancy;
	} else {
		return SCRSTYLE_None;
	}
}

Expr_Caller *Expr::CreateCaller(const Symbol *pContainerSymbol, const Symbol *pFuncSymbol)
{
	AutoPtr<Expr> pExprCar(new Expr_Identifier(pFuncSymbol));
	if (pContainerSymbol != nullptr) {
		pExprCar.reset(new Expr_Member(new Expr_Identifier(pContainerSymbol),
									   dynamic_cast<Expr_Identifier *>(pExprCar.release())));
	}
	AutoPtr<Expr_Lister> pExprLister(new Expr_Lister());
	return new Expr_Caller(pExprCar.release(), pExprLister.release(), nullptr, FLAG_None);
}

Expr_Caller *Expr::CreateCaller(const Symbol *pContainerSymbol, const Symbol *pFuncSymbol,
								 Expr *pExprArg1)
{
	AutoPtr<Expr> pExprCar(new Expr_Identifier(pFuncSymbol));
	if (pContainerSymbol != nullptr) {
		pExprCar.reset(new Expr_Member(new Expr_Identifier(pContainerSymbol),
									   dynamic_cast<Expr_Identifier *>(pExprCar.release())));
	}
	AutoPtr<Expr_Lister> pExprLister(new Expr_Lister());
	pExprLister->Reserve(1);
	pExprLister->AddExpr(pExprArg1);
	return new Expr_Caller(pExprCar.release(), pExprLister.release(), nullptr, FLAG_None);
}

Expr_Caller *Expr::CreateCaller(const Symbol *pContainerSymbol, const Symbol *pFuncSymbol,
								 Expr *pExprArg1, Expr *pExprArg2)
{
	AutoPtr<Expr> pExprCar(new Expr_Identifier(pFuncSymbol));
	if (pContainerSymbol != nullptr) {
		pExprCar.reset(new Expr_Member(new Expr_Identifier(pContainerSymbol),
									   dynamic_cast<Expr_Identifier *>(pExprCar.release())));
	}
	AutoPtr<Expr_Lister> pExprLister(new Expr_Lister());
	pExprLister->Reserve(2);
	pExprLister->AddExpr(pExprArg1);
	pExprLister->AddExpr(pExprArg2);
	return new Expr_Caller(pExprCar.release(), pExprLister.release(), nullptr, FLAG_None);
}

Expr_Caller *Expr::CreateCaller(const Symbol *pContainerSymbol, const Symbol *pFuncSymbol,
								 Expr *pExprArg1, Expr *pExprArg2, Expr *pExprArg3)
{
	AutoPtr<Expr> pExprCar(new Expr_Identifier(pFuncSymbol));
	if (pContainerSymbol != nullptr) {
		pExprCar.reset(new Expr_Member(new Expr_Identifier(pContainerSymbol),
									   dynamic_cast<Expr_Identifier *>(pExprCar.release())));
	}
	AutoPtr<Expr_Lister> pExprLister(new Expr_Lister());
	pExprLister->Reserve(3);
	pExprLister->AddExpr(pExprArg1);
	pExprLister->AddExpr(pExprArg2);
	pExprLister->AddExpr(pExprArg3);
	return new Expr_Caller(pExprCar.release(), pExprLister.release(), nullptr, FLAG_None);
}

Expr_Caller *Expr::CreateCaller(const Symbol *pContainerSymbol, const Symbol *pFuncSymbol,
				 Expr *pExprArg1, Expr *pExprArg2, Expr *pExprArg3, Expr *pExprArg4)
{
	AutoPtr<Expr> pExprCar(new Expr_Identifier(pFuncSymbol));
	if (pContainerSymbol != nullptr) {
		pExprCar.reset(new Expr_Member(new Expr_Identifier(pContainerSymbol),
									   dynamic_cast<Expr_Identifier *>(pExprCar.release())));
	}
	AutoPtr<Expr_Lister> pExprLister(new Expr_Lister());
	pExprLister->Reserve(4);
	pExprLister->AddExpr(pExprArg1);
	pExprLister->AddExpr(pExprArg2);
	pExprLister->AddExpr(pExprArg3);
	pExprLister->AddExpr(pExprArg4);
	return new Expr_Caller(pExprCar.release(), pExprLister.release(), nullptr, FLAG_None);
}

//-----------------------------------------------------------------------------
// Expr::ExprVisitor_GatherSymbol
//-----------------------------------------------------------------------------
bool Expr::ExprVisitor_GatherSymbol::Visit(Expr *pExpr)
{
	if (pExpr->IsIdentifier()) {
		const Expr_Identifier *pExprIdentifier = dynamic_cast<const Expr_Identifier *>(pExpr);
		_symbolSet.insert(pExprIdentifier->GetSymbol());
	}
	return true;
}

//-----------------------------------------------------------------------------
// Expr::ExprVisitor_GatherSimpleLambdaArgs
//-----------------------------------------------------------------------------
bool Expr::ExprVisitor_GatherSimpleLambdaArgs::Visit(Expr *pExpr)
{
	if (pExpr->IsCaller()) {
		// avoid searching in a simple lambda inside
		const Expr *pExprCar =
					dynamic_cast<const Expr_Caller *>(pExpr)->GetCar();
		if (pExprCar->IsIdentifier()) {
			const Symbol *pSymbol =
					dynamic_cast<const Expr_Identifier *>(pExprCar)->GetSymbol();
			if (pSymbol->IsIdentical(Symbol::Amp)) return false;
		}
	} else if (pExpr->IsIdentifier()) {
		const Symbol *pSymbol =
						dynamic_cast<const Expr_Identifier *>(pExpr)->GetSymbol();
		if (pSymbol->GetName()[0] == '$' &&
								_symbolSet.find(pSymbol) == _symbolSet.end()) {
			_exprOwnerArg.push_back(pExpr->Reference());
			_symbolSet.insert(pSymbol);
		}
	}
	return true;
}

//-----------------------------------------------------------------------------
// Expr::ExprVisitor_SearchBar
//-----------------------------------------------------------------------------
bool Expr::ExprVisitor_SearchBar::Visit(Expr *pExpr)
{
	const Operator *pOperator =
		pExpr->IsBinaryOp()? dynamic_cast<const Expr_BinaryOp *>(pExpr)->GetOperator() :
		pExpr->IsAssign()? dynamic_cast<const Expr_Assign *>(pExpr)->GetOperatorToApply() :
		nullptr;
	if (pOperator == nullptr || ::strchr(pOperator->GetSymbol()->GetName(), '|') == nullptr) {
		return true;
	}
	_foundFlag = true;
	return false;
}

//-----------------------------------------------------------------------------
// Expr::ExprVisitor_Prepare
//-----------------------------------------------------------------------------
bool Expr::ExprVisitor_Prepare::Visit(Expr *pExpr)
{
	if (pExpr->DoPrepare(_env)) return true;
	_env.GetSignal().AddExprCause(pExpr);
	return false;
}

//-----------------------------------------------------------------------------
// ExprList
//-----------------------------------------------------------------------------
const ExprList ExprList::Empty;

void ExprList::ExtractTrace(ExprOwner &exprOwner) const
{
	foreach_const (ExprOwner, ppExpr, *this) {
		const Expr *pExpr = *ppExpr;
		if (pExpr->IsRoot() || pExpr->IsBlock()) continue;
		const Expr *pExprParent = pExpr->GetParent();
		if (pExprParent != nullptr && !pExprParent->IsRoot() && !pExprParent->IsBlock()) continue;
		exprOwner.push_back(pExpr->Reference());
	}
}

void ExprList::Accept(ExprVisitor &visitor)
{
	foreach (ExprList, ppExpr, *this) {
		(*ppExpr)->Accept(visitor);
	}
}

bool ExprList::IsContained(const Expr *pExpr) const
{
	return std::find(begin(), end(), const_cast<Expr *>(pExpr)) != end();
}

bool ExprList::GenerateCode(Environment &env, CodeGenerator &codeGenerator) const
{
	foreach_const (ExprList, ppExpr, *this) {
		if (!(*ppExpr)->GenerateCode(env, codeGenerator)) return false;
	}
	return true;
}

bool ExprList::GenerateScript(Signal &sig, SimpleStream &stream,
			Expr::ScriptStyle scriptStyle, int nestLevel, const char *strIndent, Expr::Separator sep) const
{
	const char *sepText =
		(sep == Expr::SEP_Comma)? ((scriptStyle == Expr::SCRSTYLE_Crammed)? "," : ", ") :
		(sep == Expr::SEP_NewLine)? "\n" : ",";
	foreach_const (ExprList, ppExpr, *this) {
		const Expr *pExpr = *ppExpr;
		if (ppExpr != begin()) {
			stream.Print(sig, sepText);
			if (sig.IsSignalled()) return false;
		}
		if (sep == Expr::SEP_NewLine &&
			!Expr::PutNestIndent(sig, stream, nestLevel, strIndent)) return false;
		if (!pExpr->GenerateScript(sig, stream, scriptStyle, nestLevel, strIndent)) return false;
	}
	return true;
}

void ExprList::SetParent(const Expr *pExpr)
{
	foreach_const (ExprList, ppExpr, *this) {
		(*ppExpr)->SetParent(pExpr);
	}
}

bool ExprList::IsAtSameLine() const
{
	if (empty()) return false;
	ExprList::const_iterator ppExpr = begin();
	const Expr *pExprTop = *ppExpr++;
	if (pExprTop->GetLineNoTop() != pExprTop->GetLineNoBtm()) return false;
	for ( ; ppExpr != end(); ppExpr++) {
		const Expr *pExpr = *ppExpr;
		if (pExprTop->GetLineNoTop() != pExpr->GetLineNoTop()) return false;
	}
	return true;
}

Value ExprList::Exec(Environment &env) const
{
	Value result;
	Signal &sig = env.GetSignal();
	foreach_const (ExprList, ppExpr, *this) {
		const Expr *pExpr = *ppExpr;
		//::printf("# %s\n", pExpr->ToString(Expr::SCRSTYLE_Brief).c_str());
		result = pExpr->Exec(env);
		if (sig.IsError()) {
			sig.AddExprCause(pExpr);
			return Value::Nil;
		} else if (sig.IsTerminate()) {
			sig.PrintSignal(*env.GetConsoleErr());
			sig.ClearSignal();
			return Value::Nil;
		} else if (sig.IsSignalled()) {
			sig.PrintSignal(*env.GetConsoleErr());
			sig.ClearSignal();
		} else if (!env.GetGlobal()->GetEchoFlag()) {
			// nothing to do
		} else if (result.IsValid()) {
			env.GetConsole()->Println(sig, result.ToString().c_str());
		}
	}
	return result;
}

//-----------------------------------------------------------------------------
// ExprOwner
//-----------------------------------------------------------------------------
ExprOwner::ExprOwner() : _cntRef(1)
{
}

ExprOwner::ExprOwner(const ExprList &exprList) : _cntRef(1)
{
	foreach_const (ExprList, ppExpr, exprList) {
		push_back(Expr::Reference(*ppExpr));
	}
}

ExprOwner::ExprOwner(const ExprOwner &exprOwner) : _cntRef(1)
{
	foreach_const (ExprOwner, ppExpr, exprOwner) {
		push_back(Expr::Reference(*ppExpr));
	}
}

ExprOwner::~ExprOwner()
{
	Clear();
}

void ExprOwner::Clear()
{
	foreach (ExprOwner, ppExpr, *this) {
		Expr::Delete(*ppExpr);
	}
	clear();
}

//-----------------------------------------------------------------------------
// ExprOwner::Iterator
//-----------------------------------------------------------------------------
ExprOwner::Iterator::Iterator(ExprOwner *pExprOwner) :
	Gura::Iterator(Finite), _idx(0), _pExprOwner(pExprOwner)
{
}

Iterator *ExprOwner::Iterator::GetSource()
{
	return nullptr;
}

bool ExprOwner::Iterator::DoNext(Environment &env, Value &value)
{
	if (_idx < _pExprOwner->size()) {
		Expr *pExpr = (*_pExprOwner)[_idx++];
		value = Value(new Object_expr(env, pExpr->Reference()));
		return true;
	}
	return false;
}

String ExprOwner::Iterator::ToString() const
{
	String rtn;
	rtn += "exprowner";
	return rtn;
}

void ExprOwner::Iterator::GatherFollower(Environment::Frame *pFrame, EnvironmentSet &envSet)
{
}

//-----------------------------------------------------------------------------
// Expr_Unary
//-----------------------------------------------------------------------------
bool Expr_Unary::IsUnary() const { return true; }

Expr_Unary::Expr_Unary(ExprType exprType, Expr *pExprChild) :
	Expr(exprType), _pExprChild(pExprChild)
{
	if (pExprChild != nullptr) pExprChild->SetParent(this);
}

Expr_Unary::Expr_Unary(const Expr_Unary &expr) : Expr(expr)
{
	if (expr.GetChild() != nullptr) {
		_pExprChild.reset(expr.GetChild()->Clone());
		_pExprChild->SetParent(this);
	}
}

Expr_Unary::~Expr_Unary()
{
	if (!_pExprChild.IsNull()) _pExprChild->SetParent(GetParent());
}

void Expr_Unary::Accept(ExprVisitor &visitor)
{
	if (visitor.Visit(this) && !_pExprChild.IsNull()) {
		_pExprChild->Accept(visitor);
	}
}

bool Expr_Unary::IsParentOf(const Expr *pExpr) const
{
	return GetChild() == pExpr;
}

//-----------------------------------------------------------------------------
// Expr_Binary
//-----------------------------------------------------------------------------
bool Expr_Binary::IsBinary() const { return true; }

Expr_Binary::Expr_Binary(ExprType exprType, Expr *pExprLeft, Expr *pExprRight) :
	Expr(exprType), _pExprLeft(pExprLeft), _pExprRight(pExprRight)
{
	if (!_pExprLeft.IsNull()) _pExprLeft->SetParent(this);
	if (!_pExprRight.IsNull()) _pExprRight->SetParent(this);
}

Expr_Binary::Expr_Binary(const Expr_Binary &expr) : Expr(expr)
{
	if (expr.GetLeft() != nullptr) {
		_pExprLeft.reset(expr.GetLeft()->Clone());
		_pExprLeft->SetParent(this);
	}
	if (expr.GetRight() != nullptr) {
		_pExprRight.reset(expr.GetRight()->Clone());
		_pExprRight->SetParent(this);
	}
}

Expr_Binary::~Expr_Binary()
{
	if (!_pExprLeft.IsNull()) _pExprLeft->SetParent(GetParent());
	if (!_pExprRight.IsNull()) _pExprRight->SetParent(GetParent());
}

void Expr_Binary::Accept(ExprVisitor &visitor)
{
	if (visitor.Visit(this)) {
		if (!_pExprLeft.IsNull()) _pExprLeft->Accept(visitor);
		if (!_pExprRight.IsNull()) _pExprRight->Accept(visitor);
	}
}

bool Expr_Binary::IsParentOf(const Expr *pExpr) const
{
	return GetLeft() == pExpr || GetRight() == pExpr;
}

//-----------------------------------------------------------------------------
// Expr_Collector
//-----------------------------------------------------------------------------
bool Expr_Collector::IsCollector() const { return true; }

Expr_Collector::Expr_Collector(ExprType exprType) :
	Expr(exprType), _pExprOwner(new ExprOwner())
{
}

Expr_Collector::Expr_Collector(ExprType exprType, ExprOwner *pExprOwner) :
	Expr(exprType), _pExprOwner(pExprOwner)
{
}

Expr_Collector::Expr_Collector(const Expr_Collector &expr) :
	Expr(expr), _pExprOwner(new ExprOwner())
{
	foreach_const (ExprOwner, ppExpr, expr.GetExprOwner()) {
		AddExpr((*ppExpr)->Clone());
	}
}

Expr_Collector::~Expr_Collector()
{
	GetExprOwner().SetParent(GetParent());
}

void Expr_Collector::Accept(ExprVisitor &visitor)
{
	if (visitor.Visit(this)) {
		GetExprOwner().Accept(visitor);
	}
}

bool Expr_Collector::IsParentOf(const Expr *pExpr) const
{
	return GetExprOwner().IsContained(pExpr);
}

//-----------------------------------------------------------------------------
// Expr_Compound
//-----------------------------------------------------------------------------
bool Expr_Compound::IsCompound() const { return true; }

Expr_Compound::Expr_Compound(ExprType exprType, Expr *pExprCar, Expr_Lister *pExprLister) :
	Expr(exprType), _pExprCar(pExprCar), _pExprLister(pExprLister),
	_exprOwner(_pExprLister->GetExprOwner()), _pSymbolCar(Symbol::Empty)
{
	if (!_pExprCar.IsNull()) {
		_pExprCar->SetParent(this);
		if (_pExprCar->IsIdentifier()) {
			_pSymbolCar = dynamic_cast<Expr_Identifier *>(_pExprCar.get())->GetSymbol();
		}
	}
	if (!_pExprLister.IsNull()) _pExprLister->SetParent(this);
}

Expr_Compound::Expr_Compound(const Expr_Compound &expr) :
	Expr(expr), _pExprCar(expr._pExprCar->Clone()),
	_pExprLister(dynamic_cast<Expr_Lister *>(expr._pExprLister->Clone())),
	_exprOwner(_pExprLister->GetExprOwner()),
	_pSymbolCar(expr._pSymbolCar)
{
	if (!_pExprCar.IsNull()) _pExprCar->SetParent(this);
	if (!_pExprLister.IsNull()) _pExprLister->SetParent(this);
}

Expr_Compound::~Expr_Compound()
{
	if (!_pExprCar.IsNull()) _pExprCar->SetParent(GetParent());
	if (!_pExprLister.IsNull()) _pExprLister->SetParent(GetParent());
}

bool Expr_Compound::IsParentOf(const Expr *pExpr) const
{
	return _pExprCar.get() == pExpr || _pExprLister.get() == pExpr ||
			(!_pExprCar.IsNull() && _pExprCar->IsParentOf(pExpr)) ||
			(!_pExprLister.IsNull() && _pExprLister->IsParentOf(pExpr));
}

//-----------------------------------------------------------------------------
// Expr_Value
//-----------------------------------------------------------------------------
bool Expr_Value::IsValue() const { return true; }

Expr *Expr_Value::Clone() const
{
	return new Expr_Value(*this);
}

Value Expr_Value::DoExec(Environment &env) const
{
	if (!Monitor::NotifyExprPre(env, this)) return Value::Nil;
	Value result;
	if (_value.Is_expr()) {
		result = _value.GetExpr()->Exec(env);
	} else {
		result = _value;
	}
	if (!Monitor::NotifyExprPost(env, this, result)) return Value::Nil;
	return result;
}

Expr *Expr_Value::MathDiff(Environment &env, const Symbol *pSymbol) const
{
	return new Expr_Value(0);
}

Expr *Expr_Value::MathOptimize(Environment &env) const
{
	return Clone();
}

void Expr_Value::Accept(ExprVisitor &visitor)
{
	visitor.Visit(this);
}

bool Expr_Value::GenerateCode(Environment &env, CodeGenerator &codeGenerator) const
{
	return codeGenerator.GenCode_Value(env, this);
}

bool Expr_Value::GenerateScript(Signal &sig, SimpleStream &stream,
								ScriptStyle scriptStyle, int nestLevel, const char *strIndent) const
{
	if (_value.Is_string()) {
		const char *str = _value.GetString();
		if (scriptStyle == SCRSTYLE_Brief && ::strlen(str) > MaxCharsForBriefStyle) {
			stream.Print(sig, "' .. '");
		} else {
			stream.Print(sig, MakeQuotedString(str).c_str());
		}
		if (sig.IsSignalled()) return false;
	} else if (_value.Is_binary()) {
		const Binary &binary = _value.GetBinary();
		if (scriptStyle == SCRSTYLE_Brief && binary.size() > MaxBytesForBriefStyle) {
			stream.Print(sig, "b' .. '");
		} else {
			char buff[32];
			stream.Print(sig, "b'");
			if (sig.IsSignalled()) return false;
			foreach_const (Binary, p, binary) {
				unsigned char ch = static_cast<unsigned char>(*p);
				::sprintf(buff, "\\x%02x", ch);
				stream.Print(sig, buff);
				if (sig.IsSignalled()) return false;
			}
			stream.Print(sig, "'");
		}
		if (sig.IsSignalled()) return false;
	} else {
		String str;
		if (_pScript.get() == nullptr) {
			str = _value.ToString();
			if (sig.IsSignalled()) return false;
		} else {
			str = *_pScript;
		}
		if (_value.IsNumberOrComplex() && str[0] == '-') {
			str = "(" + str + ")";
		}
		stream.Print(sig, str.c_str());
		if (sig.IsSignalled()) return false;
	}
	return true;
}

//-----------------------------------------------------------------------------
// Expr_EmbedString
//-----------------------------------------------------------------------------
bool Expr_EmbedString::IsEmbedString() const { return true; }

Expr_EmbedString::Expr_EmbedString(Template *pTemplate, const String &str) :
		Expr(EXPRTYPE_EmbedString), _pTemplate(pTemplate), _str(str)
{
}

Expr_EmbedString::Expr_EmbedString(const Expr_EmbedString &expr) :
		Expr(expr), _pTemplate(expr._pTemplate->Reference()), _str(expr._str)
{
}

Expr *Expr_EmbedString::Clone() const
{
	return new Expr_EmbedString(*this);
}

Value Expr_EmbedString::DoExec(Environment &env) const
{
	if (!Monitor::NotifyExprPre(env, this)) return Value::Nil;
	String strDst;
	//SimpleStream_StringWriter streamDst(strDst);
	if (!_pTemplate->Render(env, strDst)) return Value::Nil;
	Value result(strDst);
	if (!Monitor::NotifyExprPost(env, this, result)) return Value::Nil;
	return result;
}

void Expr_EmbedString::Accept(ExprVisitor &visitor)
{
	visitor.Visit(this);
}

bool Expr_EmbedString::GenerateCode(Environment &env, CodeGenerator &codeGenerator) const
{
	return codeGenerator.GenCode_EmbedString(env, this);
}

bool Expr_EmbedString::GenerateScript(Signal &sig, SimpleStream &stream,
								ScriptStyle scriptStyle, int nestLevel, const char *strIndent) const
{
	if (scriptStyle == SCRSTYLE_Brief && _str.size() > MaxCharsForBriefStyle) {
		stream.Print(sig, "e' .. '");
	} else {
		String str = "e";
		str += MakeQuotedString(_str.c_str());
		stream.Print(sig, str.c_str());
	}
	if (sig.IsSignalled()) return false;
	return true;
}

//-----------------------------------------------------------------------------
// Expr_Identifier
//-----------------------------------------------------------------------------
bool Expr_Identifier::IsIdentifier() const { return true; }

Expr_Identifier::Expr_Identifier(const Symbol *pSymbol) :
	Expr(EXPRTYPE_Identifier), _pSymbol(pSymbol),
	_pAttrsShrd(new SymbolSetShared()),
	_pAttrsOptShrd(new SymbolSetShared())
{
}

Expr_Identifier::Expr_Identifier(const Expr_Identifier &expr) :
	Expr(expr), _pSymbol(expr._pSymbol),
	_pAttrsShrd(new SymbolSetShared(*expr.GetAttrsShrd())),
	_pAttrsOptShrd(new SymbolSetShared(*expr.GetAttrsOptShrd())),
	_attrFront(expr._attrFront)
{
}

Expr *Expr_Identifier::Clone() const
{
	return new Expr_Identifier(*this);
}

Callable *Expr_Identifier::LookupCallable(Environment &env) const
{
	Signal &sig = env.GetSignal();
	Value rtn = env.GetProp(GetSymbol(), GetAttrs());
	if (sig.IsSignalled()) {
		sig.AddExprCause(this);
		return nullptr;
	}
	return rtn.IsFundamental()? rtn.GetFundamental() : nullptr;
}

Value Expr_Identifier::DoExec(Environment &env) const
{
	if (!Monitor::NotifyExprPre(env, this)) return Value::Nil;
	Signal &sig = env.GetSignal();
	Value result = env.GetProp(GetSymbol(), GetAttrs());
	if (sig.IsSignalled()) return Value::Nil;
	if (!Monitor::NotifyExprPost(env, this, result)) return Value::Nil;
	return result;
}

Value Expr_Identifier::DoAssign(Environment &env, Value &valueAssigned, bool escalateFlag) const
{
	return env.SetProp(GetSymbol(), GetAttrs(), GetAttrFront(), valueAssigned, escalateFlag);
}

void Expr_Identifier::Accept(ExprVisitor &visitor)
{
	visitor.Visit(this);
}

Expr *Expr_Identifier::MathDiff(Environment &env, const Symbol *pSymbol) const
{
	Number num = GetSymbol()->IsIdentical(pSymbol)? 1 : 0;
	return new Expr_Value(num);
}

Expr *Expr_Identifier::MathOptimize(Environment &env) const
{
	return Clone();
}

bool Expr_Identifier::GenerateCode(Environment &env, CodeGenerator &codeGenerator) const
{
	return codeGenerator.GenCode_Identifier(env, this);
}

bool Expr_Identifier::GenerateScript(Signal &sig, SimpleStream &stream,
								ScriptStyle scriptStyle, int nestLevel, const char *strIndent) const
{
	if (!GenerateScriptHead(sig, stream, scriptStyle, nestLevel, strIndent)) return false;
	if (!GenerateScriptTail(sig, stream, scriptStyle, nestLevel, strIndent)) return false;
	return true;
}

bool Expr_Identifier::GenerateScriptHead(Signal &sig, SimpleStream &stream,
								ScriptStyle scriptStyle, int nestLevel, const char *strIndent) const
{
	stream.Print(sig, GetSymbol()->GetName());
	if (sig.IsSignalled()) return false;
	return true;
}

bool Expr_Identifier::GenerateScriptTail(Signal &sig, SimpleStream &stream,
								ScriptStyle scriptStyle, int nestLevel, const char *strIndent) const
{
	const Symbol *pSymbolFront = Symbol::Empty;
	if (!_attrFront.empty()) {
		stream.PutChar(sig, ':');
		if (sig.IsSignalled()) return false;
		pSymbolFront = _attrFront.front();
		foreach_const (SymbolList, ppSymbol, _attrFront) {
			const Symbol *pSymbol = *ppSymbol;
			if (ppSymbol != _attrFront.begin()) {
				stream.PutChar(sig, '.');
				if (sig.IsSignalled()) return false;
			}
			stream.Print(sig, pSymbol->GetName());
			if (sig.IsSignalled()) return false;
		}
	}
	foreach_const (SymbolSet, ppSymbol, GetAttrs()) {
		const Symbol *pSymbol = *ppSymbol;
		if (!pSymbol->IsIdentical(pSymbolFront)) {
			stream.PutChar(sig, ':');
			if (sig.IsSignalled()) return false;
			stream.Print(sig, pSymbol->GetName());
			if (sig.IsSignalled()) return false;
		}
	}
	if (!GetAttrsOpt().empty()) {
		stream.PutChar(sig, ':');
		if (sig.IsSignalled()) return false;
		stream.PutChar(sig, '[');
		if (sig.IsSignalled()) return false;
		foreach_const (SymbolSet, ppSymbol, GetAttrsOpt()) {
			const Symbol *pSymbol = *ppSymbol;
			if (ppSymbol != GetAttrsOpt().begin()) {
				stream.PutChar(sig, ',');
				if (sig.IsSignalled()) return false;
			}
			stream.Print(sig, pSymbol->GetName());
			if (sig.IsSignalled()) return false;
		}
		stream.PutChar(sig, ']');
		if (sig.IsSignalled()) return false;
	}
	return true;
}

//-----------------------------------------------------------------------------
// Expr_Suffixed
//-----------------------------------------------------------------------------
bool Expr_Suffixed::IsSuffixed() const { return true; }

Expr *Expr_Suffixed::Clone() const
{
	return new Expr_Suffixed(*this);
}

Value Expr_Suffixed::DoExec(Environment &env) const
{
	if (!Monitor::NotifyExprPre(env, this)) return Value::Nil;
	Signal &sig = env.GetSignal();
	Value result;
	SuffixMgrEntry *pSuffixMgrEntry = _numberFlag?
				SuffixMgr::LookupForNumber(env, _pSymbolSuffix) :
				SuffixMgr::LookupForString(env, _pSymbolSuffix);
	if (pSuffixMgrEntry == nullptr) {
		sig.SetError(ERR_SyntaxError, "unknown suffix '%s' for %s",
				_pSymbolSuffix->GetName(), _numberFlag? "number" : "string");
		return Value::Nil;
	}
	result = pSuffixMgrEntry->DoEval(env, _body.c_str());
	if (sig.IsSignalled()) return Value::Nil;
	if (!Monitor::NotifyExprPost(env, this, result)) return Value::Nil;
	return result;
}

void Expr_Suffixed::Accept(ExprVisitor &visitor)
{
	visitor.Visit(this);
}

bool Expr_Suffixed::GenerateCode(Environment &env, CodeGenerator &codeGenerator) const
{
	return codeGenerator.GenCode_Suffixed(env, this);
}

bool Expr_Suffixed::GenerateScript(Signal &sig, SimpleStream &stream,
								ScriptStyle scriptStyle, int nestLevel, const char *strIndent) const
{
	if (_numberFlag) {
		if (scriptStyle == SCRSTYLE_Brief && _body.size() > MaxCharsForBriefStyle) {
			stream.Print(sig, "..");
		} else {
			stream.Print(sig, _body.c_str());
		}
	} else {
		if (scriptStyle == SCRSTYLE_Brief && _body.size() > MaxCharsForBriefStyle) {
			stream.Print(sig, "' .. '");
		} else {
			stream.Print(sig, MakeQuotedString(_body.c_str()).c_str());
		}
	}
	if (sig.IsSignalled()) return false;
	stream.Print(sig, _pSymbolSuffix->GetName());
	if (sig.IsSignalled()) return false;
	return true;
}

//-----------------------------------------------------------------------------
// Expr_Member
//-----------------------------------------------------------------------------
bool Expr_Member::IsMember() const { return true; }

Expr_Member::Expr_Member(Expr *pExprTarget, Expr_Identifier *pExprSelector, Mode mode) :
	Expr(EXPRTYPE_Member),
	_pExprTarget(pExprTarget), _pExprSelector(pExprSelector), _mode(mode)
{
	_pExprTarget->SetParent(this);
	_pExprSelector->SetParent(this);
}

Expr_Member::Expr_Member(const Expr_Member &expr) : Expr(expr), _mode(expr._mode)
{
	_pExprTarget.reset(expr.GetTarget()->Clone());
	_pExprTarget->SetParent(this);
	_pExprSelector.reset(dynamic_cast<Expr_Identifier *>(expr.GetSelector()->Clone()));
	_pExprSelector->SetParent(this);
}

Expr *Expr_Member::Clone() const
{
	return new Expr_Member(*this);
}

void Expr_Member::Accept(ExprVisitor &visitor)
{
	if (visitor.Visit(this)) {
		if (!_pExprTarget.IsNull()) _pExprTarget->Accept(visitor);
		if (!_pExprSelector.IsNull()) _pExprSelector->Accept(visitor);
	}
}

bool Expr_Member::IsParentOf(const Expr *pExpr) const
{
	return GetTarget() == pExpr || GetSelector() == pExpr;
}

Value Expr_Member::DoExec(Environment &env) const
{
	if (!Monitor::NotifyExprPre(env, this)) return Value::Nil;
	Signal &sig = env.GetSignal();
	// Expr_Caller::Exec(), Expr_Member::Exec() and Expr_Member::DoAssign()
	// correspond to method-calling, property-getting and property-setting.
	Value valueThis = GetTarget()->Exec(env);
	if (sig.IsSignalled()) return Value::Nil;
	Value result;
	if (_mode == MODE_Normal) {
		result = valueThis.GetProp(env, GetSelector()->GetSymbol(), GetSelector()->GetAttrs(), nullptr);
		if (result.Is_function()) {
			result = Value(new Object_function(env, result.GetFunction()->Reference(), valueThis));
		}
	} else if (valueThis.Is_list() && valueThis.GetList().empty()) {
		result = valueThis;
	} else {
		Fundamental *pFund = valueThis.IsPrimitive()?
			valueThis.GetClass() : valueThis.GetFundamental();
		Iterator *pIterator = pFund->CreateIterator(sig);
		if (sig.IsSignalled()) return Value::Nil;
		if (pIterator == nullptr) {
			sig.SetError(ERR_ValueError, "member mapping can only be applied to iterables");
			return Value::Nil;
		}
		AutoPtr<Iterator>
			pIteratorMap(new Iterator_MemberMap(
							 env.Clone(), pIterator,
							 GetSelector()->GetSymbol(),
							 SymbolSetShared::Reference(GetSelector()->GetAttrsShrd())));;
		if (_mode == MODE_MapToIter) {
			result = Value(new Object_iterator(env, pIteratorMap.release()));
		} else { // _mode == MODE_MapToList
			result = pIteratorMap->ToList(env, false, false);
			if (sig.IsSignalled()) return Value::Nil;
		}
	}
	if (!Monitor::NotifyExprPost(env, this, result)) return Value::Nil;
	return result;
}

Value Expr_Member::DoAssign(Environment &env, Value &valueAssigned, bool escalateFlag) const
{
	Signal &sig = env.GetSignal();
	// Expr_Caller::Exec(), Expr_Member::Exec() and Expr_Member::DoAssign()
	// correspond to method-calling, property-getting and property-setting.
	Value valueThis = GetTarget()->Exec(env);
	if (sig.IsSignalled()) return Value::Nil;
	if (valueThis.IsPrimitive()) {
		sig.SetError(ERR_ValueError, "%s can not be specified as l-value of member",
					 valueThis.MakeValueTypeName().c_str());
		return Value::Nil;
	}
	if (_mode == MODE_Normal) {
		return valueThis.SetProp(env, GetSelector()->GetSymbol(), GetSelector()->GetAttrs(),
								 GetSelector()->GetAttrFront(), valueAssigned, escalateFlag);
	}
	Fundamental *pFund = valueThis.IsPrimitive()?
		valueThis.GetClass() : valueThis.GetFundamental();
	AutoPtr<Iterator> pIteratorThis(pFund->CreateIterator(sig));
	if (pIteratorThis.IsNull()) {
		if (sig.IsSignalled()) return Value::Nil;
		return valueThis.SetProp(env, GetSelector()->GetSymbol(), GetSelector()->GetAttrs(),
								 GetSelector()->GetAttrFront(), valueAssigned, escalateFlag);
	}
	if (valueAssigned.Is_list() || valueAssigned.Is_iterator()) {
		AutoPtr<Iterator> pIteratorValue(valueAssigned.CreateIterator(sig));
		if (sig.IsSignalled()) return Value::Nil;
		Value valueAssignedEach;
		Value valueThisEach;
		while (pIteratorThis->Next(env, valueThisEach) &&
								pIteratorValue->Next(env, valueAssignedEach)) {
			if (valueThisEach.IsPrimitive()) {
				sig.SetError(ERR_ValueError, "%s can not be specified as l-value of member",
							 valueThisEach.MakeValueTypeName().c_str());
				return Value::Nil;
			}
			valueThisEach.SetProp(env, GetSelector()->GetSymbol(), GetSelector()->GetAttrs(),
								  GetSelector()->GetAttrFront(), valueAssignedEach, escalateFlag);
			if (sig.IsSignalled()) break;
		}
		if (sig.IsSignalled()) return Value::Nil;
	} else {
		Value valueThisEach;
		while (pIteratorThis->Next(env, valueThisEach)) {
			if (valueThisEach.IsPrimitive()) {
				sig.SetError(ERR_ValueError, "%s can not be specified as l-value of member",
							 valueThisEach.MakeValueTypeName().c_str());
				return Value::Nil;
			}
			valueThisEach.SetProp(env, GetSelector()->GetSymbol(), GetSelector()->GetAttrs(),
								  GetSelector()->GetAttrFront(), valueAssigned, escalateFlag);
			if (sig.IsSignalled()) break;
		}
		if (sig.IsSignalled()) return Value::Nil;
	}
	return valueAssigned;
}

bool Expr_Member::GenerateCode(Environment &env, CodeGenerator &codeGenerator) const
{
	return codeGenerator.GenCode_Member(env, this);
}

bool Expr_Member::GenerateScript(Signal &sig, SimpleStream &stream,
								ScriptStyle scriptStyle, int nestLevel, const char *strIndent) const
{
	bool needParenthesisFlag = false;
	const Expr *pExprTarget = GetTarget();
	if (pExprTarget->IsIndexer()) {
		const Expr_Indexer *pExprIndexer = dynamic_cast<const Expr_Indexer *>(pExprTarget);
		pExprTarget = pExprIndexer->GetCar();
	}
	if (pExprTarget->IsIdentifier()) {
		const Expr_Identifier *pExprIdentifier = dynamic_cast<const Expr_Identifier *>(pExprTarget);
		needParenthesisFlag = !pExprIdentifier->GetAttrs().empty();
	} else if (pExprTarget->IsCaller()) {
		const Expr_Caller *pExprCaller = dynamic_cast<const Expr_Caller *>(pExprTarget);
		needParenthesisFlag = pExprCaller->GetCallerInfo().HasAttrs();
	}
	if (needParenthesisFlag) {
		stream.PutChar(sig, '(');
		if (sig.IsSignalled()) return false;
		if (!GetTarget()->GenerateScript(sig, stream, scriptStyle, nestLevel, strIndent)) return false;
		stream.PutChar(sig, ')');
		if (sig.IsSignalled()) return false;
	} else {
		if (!GetTarget()->GenerateScript(sig, stream, scriptStyle, nestLevel, strIndent)) return false;
	}
	const char *str =
		(_mode == MODE_Normal)? "." :
		(_mode == MODE_MapToList)? "::" :
		(_mode == MODE_MapToIter)? ":*" :
		(_mode == MODE_MapAlong)? ":&" : nullptr;
	if (str == nullptr) {
		sig.SetError(ERR_SyntaxError, "unknown mapping operator");
		return false;
	}
	stream.Print(sig, str);
	if (!GetSelector()->GenerateScript(sig, stream, scriptStyle, nestLevel, strIndent)) return false;
	return true;
}

//-----------------------------------------------------------------------------
// Expr_UnaryOp
//-----------------------------------------------------------------------------
bool Expr_UnaryOp::IsUnaryOp() const { return true; }
bool Expr_UnaryOp::IsUnaryOpSuffix() const { return _pOperator->IsSuffixedUnaryOperator(); }

Expr *Expr_UnaryOp::Clone() const
{
	return new Expr_UnaryOp(*this);
}

Value Expr_UnaryOp::DoExec(Environment &env) const
{
	if (!Monitor::NotifyExprPre(env, this)) return Value::Nil;
	Value result = _pOperator->ExecUnary(env, GetChild());
	if (env.IsSignalled()) return Value::Nil;
	if (!Monitor::NotifyExprPost(env, this, result)) return Value::Nil;
	return result;
}

Expr *Expr_UnaryOp::MathDiff(Environment &env, const Symbol *pSymbol) const
{
	return _pOperator->MathDiffUnary(env, GetChild(), pSymbol);
}

Expr *Expr_UnaryOp::MathOptimize(Environment &env) const
{
	Signal &sig = env.GetSignal();
	Expr *pExprOpt = GetChild()->MathOptimize(env);
	if (sig.IsSignalled()) {
		sig.AddExprCause(this);
		return nullptr;
	}
	return _pOperator->MathOptimizeUnary(env, pExprOpt);
}

bool Expr_UnaryOp::GenerateCode(Environment &env, CodeGenerator &codeGenerator) const
{
	return codeGenerator.GenCode_UnaryOp(env, this);
}

bool Expr_UnaryOp::GenerateScript(Signal &sig, SimpleStream &stream,
								ScriptStyle scriptStyle, int nestLevel, const char *strIndent) const
{
	bool suffixFlag = _pOperator->IsSuffixedUnaryOperator();
	bool needParenthesisFlag = false;
	if (GetParent() != nullptr) {
		needParenthesisFlag = (GetParent()->IsUnaryOp() ||
					GetParent()->IsBinaryOp() || GetParent()->IsMember());
	}
	if (needParenthesisFlag) {
		stream.PutChar(sig, '(');
		if (sig.IsSignalled()) return false;
	}
	if (!suffixFlag) {
		stream.Print(sig, _pOperator->GetSymbol()->GetName());
		if (sig.IsSignalled()) return false;
	}
	if (!GetChild()->GenerateScript(sig, stream, scriptStyle, nestLevel, strIndent)) return false;
	if (suffixFlag) {
		stream.Print(sig, _pOperator->GetSymbol()->GetName());
		if (sig.IsSignalled()) return false;
	}
	if (needParenthesisFlag) {
		stream.PutChar(sig, ')');
		if (sig.IsSignalled()) return false;
	}
	return true;
}

//-----------------------------------------------------------------------------
// Expr_Quote
//-----------------------------------------------------------------------------
bool Expr_Quote::IsQuote() const { return true; }

Expr *Expr_Quote::Clone() const
{
	return new Expr_Quote(*this);
}

const Expr *Expr_Quote::Unquote() const
{
	return GetChild();
}

Value Expr_Quote::DoExec(Environment &env) const
{
	if (!Monitor::NotifyExprPre(env, this)) return Value::Nil;
	Value result;
	if (GetChild()->IsIdentifier()) {
		const Expr_Identifier *pExprIdentifier =
						dynamic_cast<const Expr_Identifier *>(GetChild());
		result.SetSymbol(pExprIdentifier->GetSymbol());
	} else {
		result = Value(new Object_expr(env, Expr::Reference(GetChild())));
	}
	if (!Monitor::NotifyExprPost(env, this, result)) return Value::Nil;
	return result;
}

bool Expr_Quote::GenerateCode(Environment &env, CodeGenerator &codeGenerator) const
{
	return codeGenerator.GenCode_Quote(env, this);
}

bool Expr_Quote::GenerateScript(Signal &sig, SimpleStream &stream,
								ScriptStyle scriptStyle, int nestLevel, const char *strIndent) const
{
	if (GetChild()->IsUnary() || GetChild()->IsBinary()) {
		stream.Print(sig, "`(");
		if (sig.IsSignalled()) return false;
		if (!GetChild()->GenerateScript(sig, stream, scriptStyle, nestLevel, strIndent)) return false;
		stream.Print(sig, ")");
		if (sig.IsSignalled()) return false;
	} else {
		stream.Print(sig, "`");
		if (sig.IsSignalled()) return false;
		if (!GetChild()->GenerateScript(sig, stream, scriptStyle, nestLevel, strIndent)) return false;
	}
	return true;
}

//-----------------------------------------------------------------------------
// Expr_BinaryOp
//-----------------------------------------------------------------------------
bool Expr_BinaryOp::IsBinaryOp() const { return true; }

Expr *Expr_BinaryOp::Clone() const
{
	return new Expr_BinaryOp(*this);
}

Value Expr_BinaryOp::DoExec(Environment &env) const
{
	if (!Monitor::NotifyExprPre(env, this)) return Value::Nil;
	Value result = _pOperator->ExecBinary(env, GetLeft(), GetRight());
	if (env.IsSignalled()) return Value::Nil;
	if (!Monitor::NotifyExprPost(env, this, result)) return Value::Nil;
	return result;
}

Expr *Expr_BinaryOp::MathDiff(Environment &env, const Symbol *pSymbol) const
{
	return _pOperator->MathDiffBinary(env, GetLeft(), GetRight(), pSymbol);
}

Expr *Expr_BinaryOp::MathOptimize(Environment &env) const
{
	Signal &sig = env.GetSignal();
	AutoPtr<Expr> pExprOpt1(GetLeft()->MathOptimize(env));
	if (sig.IsSignalled()) {
		sig.AddExprCause(this);
		return nullptr;
	}
	AutoPtr<Expr> pExprOpt2(GetRight()->MathOptimize(env));
	if (sig.IsSignalled()) {
		sig.AddExprCause(this);
		return nullptr;
	}
	return _pOperator->MathOptimizeBinary(env, pExprOpt1.release(), pExprOpt2.release());
}

bool Expr_BinaryOp::GenerateCode(Environment &env, CodeGenerator &codeGenerator) const
{
	return codeGenerator.GenCode_BinaryOp(env, this);
}

bool Expr_BinaryOp::GenerateScript(Signal &sig, SimpleStream &stream,
								ScriptStyle scriptStyle, int nestLevel, const char *strIndent) const
{
	bool needParenthesisFlag = false;
	if (GetParent() == nullptr) {
		// nothing to do
	} else if (GetParent()->IsUnaryOp()) {
		needParenthesisFlag = true;
	} else if (GetParent()->IsBinaryOp()) {
		const Expr_BinaryOp *pExprOuter =
								dynamic_cast<const Expr_BinaryOp *>(GetParent());
		needParenthesisFlag = NeedParenthesis(pExprOuter->GetOperator(),
							GetOperator(), pExprOuter->GetRight() == this);
	} else if (GetParent()->IsMember()) {
		needParenthesisFlag = true;
	}
	if (needParenthesisFlag) {
		stream.PutChar(sig, '(');
		if (sig.IsSignalled()) return false;
	}
	if (!GetLeft()->GenerateScript(sig, stream, scriptStyle, nestLevel, strIndent)) return false;
	String text;
	if (scriptStyle != SCRSTYLE_Crammed) text += ' ';
	text += _pOperator->GetSymbol()->GetName();
	if (scriptStyle != SCRSTYLE_Crammed) text += ' ';
	stream.Print(sig, text.c_str());
	if (sig.IsSignalled()) return false;
	if (!GetRight()->GenerateScript(sig, stream, scriptStyle, nestLevel, strIndent)) return false;
	if (needParenthesisFlag) {
		stream.PutChar(sig, ')');
		if (sig.IsSignalled()) return false;
	}
	return true;
}

//-----------------------------------------------------------------------------
// Expr_Assign
//-----------------------------------------------------------------------------
bool Expr_Assign::IsAssign() const { return true; }

Expr *Expr_Assign::Clone() const
{
	return new Expr_Assign(*this);
}

Value Expr_Assign::DoExec(Environment &env) const
{
	if (!Monitor::NotifyExprPre(env, this)) return Value::Nil;
	Value result = DoExecSub(env, env);
	if (!Monitor::NotifyExprPost(env, this, result)) return Value::Nil;
	return result;
}

Value Expr_Assign::DoExecSub(Environment &env, Environment &envDst) const
{
	Signal &sig = env.GetSignal();
	Value valueAssigned;
	const Expr *pExpr = GetLeft();
	if (pExpr->IsCaller()) {
		if (_pOperatorToApply != nullptr) {
			SetError(sig, ERR_SyntaxError, "invalid operation");
			return Value::Nil;
		}
		Expr *pExprBody = Expr::Reference(GetRight()->Unquote());
		valueAssigned = Value(new Object_expr(env, pExprBody));
	} else {
		valueAssigned = GetRight()->Exec(env);
		if (sig.IsSignalled()) return Value::Nil;
		if (_pOperatorToApply != nullptr) {
			Value valueLeft = pExpr->Exec(env);
			if (sig.IsSignalled()) return Value::Nil;
			valueAssigned = _pOperatorToApply->EvalMapBinary(env, valueLeft, valueAssigned, FLAG_None);
			if (sig.IsSignalled()) return Value::Nil;
		}
	}
	return GetLeft()->DoAssign(envDst, valueAssigned, true);
}

bool Expr_Assign::GenerateCode(Environment &env, CodeGenerator &codeGenerator) const
{
	return codeGenerator.GenCode_Assign(env, this);
}

bool Expr_Assign::GenerateScript(Signal &sig, SimpleStream &stream,
								ScriptStyle scriptStyle, int nestLevel, const char *strIndent) const
{
	bool needParenthesisFlag = false;
	if (GetParent() != nullptr) {
		needParenthesisFlag = (GetParent()->IsUnary() ||
						GetParent()->IsBinary()) && !GetParent()->IsQuote();
	}
	if (needParenthesisFlag) {
		stream.PutChar(sig, '(');
		if (sig.IsSignalled()) return false;
	}
	if (!GetLeft()->GenerateScript(sig, stream, scriptStyle, nestLevel, strIndent)) return false;
	String text;
	if (scriptStyle != SCRSTYLE_Crammed) text += ' ';
	if (_pOperatorToApply != nullptr) {
		text += _pOperatorToApply->GetSymbol()->GetName();
	}
	text += '=';
	if (scriptStyle != SCRSTYLE_Crammed) text += ' ';
	stream.Print(sig, text.c_str());
	if (sig.IsSignalled()) return false;
	if (!GetRight()->GenerateScript(sig, stream, scriptStyle, nestLevel, strIndent)) return false;
	if (needParenthesisFlag) {
		stream.PutChar(sig, ')');
		if (sig.IsSignalled()) return false;
	}
	return true;
}

//-----------------------------------------------------------------------------
// Expr_Root
//-----------------------------------------------------------------------------
bool Expr_Root::IsRoot() const { return true; }

Expr_Root::Expr_Root() : Expr_Collector(EXPRTYPE_Root)
{
}

Expr_Root::Expr_Root(const Expr_Root &expr) : Expr_Collector(expr)
{
}

Expr *Expr_Root::Clone() const
{
	return new Expr_Root(*this);
}

Value Expr_Root::DoExec(Environment &env) const
{
	return GetExprOwner().Exec(env);
}

bool Expr_Root::GenerateCode(Environment &env, CodeGenerator &codeGenerator) const
{
	return codeGenerator.GenCode_Root(env, this);
}

bool Expr_Root::GenerateScript(Signal &sig, SimpleStream &stream,
								ScriptStyle scriptStyle, int nestLevel, const char *strIndent) const
{
	if (!GetExprOwner().GenerateScript(sig, stream, scriptStyle, nestLevel, strIndent,
		(scriptStyle == SCRSTYLE_Fancy)? SEP_NewLine : SEP_Comma)) return false;
	if (scriptStyle == SCRSTYLE_Fancy) {
		stream.PutChar(sig, '\n');
		if (sig.IsSignalled()) return false;
	}
	return true;
}

//-----------------------------------------------------------------------------
// Expr_Block
//-----------------------------------------------------------------------------
bool Expr_Block::IsBlock() const { return true; }

Expr_Block::Expr_Block() : Expr_Collector(EXPRTYPE_Block)
{
}

Expr_Block::Expr_Block(ExprOwner *pExprOwner, ExprOwner *pExprOwnerParam) :
	Expr_Collector(EXPRTYPE_Block, pExprOwner), _pExprOwnerParam(pExprOwnerParam)
{
}

Expr_Block::Expr_Block(const Expr_Block &expr) : Expr_Collector(expr)
{
	if (expr.GetExprOwnerParam() != nullptr) {
		SetExprOwnerParam(new ExprOwner());
		foreach_const (ExprOwner, ppExpr, *expr.GetExprOwnerParam()) {
			Expr *pExpr = (*ppExpr)->Clone();
			GetExprOwnerParam()->push_back(pExpr);
			pExpr->SetParent(this);
		}
	}
}

Expr_Block::~Expr_Block()
{
	if (GetExprOwnerParam() != nullptr) {
		GetExprOwnerParam()->SetParent(GetParent());
	}
}

Expr *Expr_Block::Clone() const
{
	return new Expr_Block(*this);
}

Value Expr_Block::DoExec(Environment &env) const
{
	if (!Monitor::NotifyExprPre(env, this)) return Value::Nil;
	Signal &sig = env.GetSignal();
	Value result;
	if (env.IsType(ENVTYPE_lister)) {
		Object_list *pObjList = result.InitAsList(env);
		pObjList->Reserve(GetExprOwner().size());
		foreach_const (ExprOwner, ppExpr, GetExprOwner()) {
			Value value = (*ppExpr)->Exec(env, true);
			if (sig.IsSignalled()) return Value::Nil;
			pObjList->AddFast(value);
		}
		pObjList->DetermineValueType();
	} else {
		foreach_const (ExprList, ppExpr, GetExprOwner()) {
			result = (*ppExpr)->Exec(env, true);
			if (sig.IsSignalled()) return Value::Nil;
		}
	}
	if (!Monitor::NotifyExprPost(env, this, result)) return Value::Nil;
	return result;
}

Expr *Expr_Block::MathDiff(Environment &env, const Symbol *pSymbol) const
{
	return (GetExprOwner().size() == 1)?
			GetExprOwner().front()->MathDiff(env, pSymbol) :
			Expr::MathDiff(env, pSymbol);
}

void Expr_Block::Accept(ExprVisitor &visitor)
{
	if (GetExprOwnerParam() != nullptr) GetExprOwnerParam()->Accept(visitor);
	Expr_Collector::Accept(visitor);
}

bool Expr_Block::GenerateCode(Environment &env, CodeGenerator &codeGenerator) const
{
	return codeGenerator.GenCode_Block(env, this);
}

bool Expr_Block::GenerateScript(Signal &sig, SimpleStream &stream,
								ScriptStyle scriptStyle, int nestLevel, const char *strIndent) const
{
	stream.PutChar(sig, '{');
	if (sig.IsSignalled()) return false;
	if (GetExprOwnerParam() != nullptr) {
		stream.PutChar(sig, '|');
		if (sig.IsSignalled()) return false;
		const char *sepText = (scriptStyle == Expr::SCRSTYLE_Crammed)? "," : ", ";
		foreach_const (ExprList, ppExpr, *GetExprOwnerParam()) {
			Expr *pExpr = *ppExpr;
			if (ppExpr != GetExprOwnerParam()->begin()) {
				stream.Print(sig, sepText);
				if (sig.IsSignalled()) return false;
			}
			if (pExpr->SearchBar()) {
				stream.PutChar(sig, '(');
				if (sig.IsSignalled()) return false;
				if (!pExpr->GenerateScript(sig, stream, scriptStyle,
										   nestLevel, strIndent)) return false;
				stream.PutChar(sig, ')');
				if (sig.IsSignalled()) return false;
			} else {
				if (!pExpr->GenerateScript(sig, stream, scriptStyle,
										   nestLevel, strIndent)) return false;
			}
		}
		stream.PutChar(sig, '|');
		if (sig.IsSignalled()) return false;
	}
	const Expr_Caller *pExprCaller =
			(GetParent() == nullptr || !GetParent()->IsCaller())? nullptr :
			dynamic_cast<const Expr_Caller *>(GetParent());
	if (GetExprOwner().empty()) {
		// nothing to do
	} else if (scriptStyle == SCRSTYLE_Brief && (!GetExprOwner().IsAtSameLine() ||
			(pExprCaller != nullptr && !pExprCaller->IsAtSameLine(GetExprOwner().front())))) {
		stream.Print(sig, " .. ");
		if (sig.IsSignalled()) return false;
	} else {
		const char *sepText =
			(scriptStyle == SCRSTYLE_Crammed)? "" :
			(scriptStyle == SCRSTYLE_OneLine)? " " :
			(scriptStyle == SCRSTYLE_Brief)? " " :
			(scriptStyle == SCRSTYLE_Fancy)? "\n" : "";
		stream.Print(sig, sepText);
		if (sig.IsSignalled()) return false;
		if (!GetExprOwner().GenerateScript(sig, stream, scriptStyle, nestLevel + 1, strIndent,
			(scriptStyle == SCRSTYLE_Fancy)? SEP_NewLine : SEP_Comma)) return false;
		stream.Print(sig, sepText);
		if (sig.IsSignalled()) return false;
		if (scriptStyle == SCRSTYLE_Fancy &&
			!PutNestIndent(sig, stream, nestLevel, strIndent)) return false;
	}
	stream.PutChar(sig, '}');
	if (sig.IsSignalled()) return false;
	return true;
}

//-----------------------------------------------------------------------------
// Expr_Lister
//-----------------------------------------------------------------------------
bool Expr_Lister::IsLister() const { return true; }

Expr *Expr_Lister::Clone() const
{
	return new Expr_Lister(*this);
}

Value Expr_Lister::DoExec(Environment &env) const
{
	if (!Monitor::NotifyExprPre(env, this)) return Value::Nil;
	Signal &sig = env.GetSignal();
	Value result;
	Object_list *pObjList = result.InitAsList(env);
	pObjList->Reserve(GetExprOwner().size());
	foreach_const (ExprOwner, ppExpr, GetExprOwner()) {
		const Expr *pExpr = *ppExpr;
		Value value = pExpr->Exec(env);
		if (sig.IsSignalled()) return Value::Nil;
		if (value.Is_iterator()) {
			AutoPtr<Iterator> pIterator(value.CreateIterator(sig));
			if (sig.IsSignalled()) return Value::Nil;
			if (pIterator->IsInfinite()) {
				Iterator::SetError_InfiniteNotAllowed(sig);
				return Value::Nil;
			}
			Value value;
			while (pIterator->Next(env, value)) {
				pObjList->AddFast(value);
			}
			if (sig.IsSignalled()) return Value::Nil;
		} else {
			pObjList->AddFast(value);
		}
	}
	pObjList->DetermineValueType();
	if (!Monitor::NotifyExprPost(env, this, result)) return Value::Nil;
	return result;
}

Value Expr_Lister::DoAssign(Environment &env, Value &valueAssigned, bool escalateFlag) const
{
	Signal &sig = env.GetSignal();
	const ExprList &exprList = GetExprOwner();
	if (valueAssigned.Is_list() || valueAssigned.Is_iterator()) {
		// [a, b, ..] = [v, v, ..]
		Object_list *pObjList = nullptr;
		ExprList::const_iterator ppExpr = exprList.begin();
		AutoPtr<Iterator> pIterator(valueAssigned.CreateIterator(sig));
		if (pIterator.IsNull()) return Value::Nil;
		Value valueElem;
		while (pIterator->Next(env, valueElem)) {
			if (pObjList != nullptr) {
				pObjList->Add(valueElem);
				continue;
			}
			if (ppExpr == exprList.end()) break;
			const Expr *pExpr = *ppExpr;
			OccurPattern occurPattern = OCCUR_Once;
			if (pExpr->IsUnaryOpSuffix()) {
				const Expr_UnaryOp *pExprUnaryOp =
										dynamic_cast<const Expr_UnaryOp *>(pExpr);
				pExpr = pExprUnaryOp->GetChild();
				occurPattern = Symbol::ToOccurPattern(
									pExprUnaryOp->GetOperator()->GetSymbol());
				if (occurPattern == OCCUR_Invalid) {
					SetError(sig, ERR_SyntaxError,
								"invalid expression of array assignment");
					return Value::Nil;
				}
			}
			if (occurPattern == OCCUR_ZeroOrMore || occurPattern == OCCUR_OnceOrMore) {
				Value value;
				pObjList = value.InitAsList(env);
				pExpr->DoAssign(env, value, escalateFlag);
				if (sig.IsSignalled()) return Value::Nil;
				pObjList->Add(valueElem);
			} else {
				pExpr->DoAssign(env, valueElem, escalateFlag);
				if (sig.IsSignalled()) return Value::Nil;
			}
			ppExpr++;
		}
		for ( ; ppExpr != exprList.end(); ppExpr++) {
			const Expr *pExpr = *ppExpr;
			OccurPattern occurPattern = OCCUR_Once;
			if (pExpr->IsUnaryOpSuffix()) {
				const Expr_UnaryOp *pExprUnaryOp =
								dynamic_cast<const Expr_UnaryOp *>(pExpr);
				pExpr = pExprUnaryOp->GetChild();
				occurPattern = Symbol::ToOccurPattern(
									pExprUnaryOp->GetOperator()->GetSymbol());
			}
			if (occurPattern == OCCUR_ZeroOrMore) {
				Value value;
				pObjList = value.InitAsList(env);
				pExpr->DoAssign(env, value, escalateFlag);
				if (sig.IsSignalled()) return Value::Nil;
			} else if (occurPattern == OCCUR_Once || occurPattern == OCCUR_OnceOrMore) {
				SetError(sig, ERR_ValueError,
						"not enough value to initialize arrayed variables");
				return Value::Nil;
			}
		}
	} else {
		// [a, b, ..] = v
		foreach_const (ExprList, ppExpr, exprList) {
			const Expr *pExpr = *ppExpr;
			pExpr->DoAssign(env, valueAssigned, escalateFlag);
			if (sig.IsSignalled()) return Value::Nil;
		}
	}
	return valueAssigned;
}

bool Expr_Lister::GenerateCode(Environment &env, CodeGenerator &codeGenerator) const
{
	return codeGenerator.GenCode_Lister(env, this);
}

bool Expr_Lister::GenerateScript(Signal &sig, SimpleStream &stream,
								ScriptStyle scriptStyle, int nestLevel, const char *strIndent) const
{
	stream.PutChar(sig, '[');
	if (sig.IsSignalled()) return false;
	if (GetExprOwner().empty()) {
		// nothing to do
	} else if (scriptStyle == SCRSTYLE_Brief && !GetExprOwner().IsAtSameLine()) {
		stream.Print(sig, " .. ");
		if (sig.IsSignalled()) return false;
	} else {
		if (!GetExprOwner().GenerateScript(sig, stream,
							scriptStyle, nestLevel, strIndent, SEP_Comma)) return false;
	}
	stream.PutChar(sig, ']');
	if (sig.IsSignalled()) return false;
	return true;
}

//-----------------------------------------------------------------------------
// Expr_Iterer
//-----------------------------------------------------------------------------
bool Expr_Iterer::IsIterer() const { return true; }

Expr *Expr_Iterer::Clone() const
{
	return new Expr_Iterer(*this);
}

Value Expr_Iterer::DoExec(Environment &env) const
{
	if (!Monitor::NotifyExprPre(env, this)) return Value::Nil;
	Signal &sig = env.GetSignal();
	AutoPtr<Iterator_Concat> pIterator(new Iterator_Concat());
	foreach_const (ExprOwner, ppExpr, GetExprOwner()) {
		const Expr *pExpr = *ppExpr;
		Value value = pExpr->Exec(env);
		if (sig.IsSignalled()) return Value::Nil;
		Iterator *pIteratorArg = nullptr;
		if (value.Is_iterator()) {
			pIteratorArg = value.CreateIterator(sig);
			if (sig.IsSignalled()) return Value::Nil;
		} else {
			pIteratorArg = new Iterator_OneShot(value);
		}
		pIterator->Add(pIteratorArg);
	}
	Value result(new Object_iterator(env, pIterator.release()));
	if (!Monitor::NotifyExprPost(env, this, result)) return Value::Nil;
	return result;
}

bool Expr_Iterer::GenerateCode(Environment &env, CodeGenerator &codeGenerator) const
{
	return codeGenerator.GenCode_Iterer(env, this);
}

bool Expr_Iterer::GenerateScript(Signal &sig, SimpleStream &stream,
								ScriptStyle scriptStyle, int nestLevel, const char *strIndent) const
{
	stream.PutChar(sig, '(');
	if (sig.IsSignalled()) return false;
	if (GetExprOwner().empty()) {
		// nothing to do
	} else if (scriptStyle == SCRSTYLE_Brief && !GetExprOwner().IsAtSameLine()) {
		stream.Print(sig, " .. ");
		if (sig.IsSignalled()) return false;
	} else {
		if (!GetExprOwner().GenerateScript(sig, stream,
						scriptStyle, nestLevel, strIndent, SEP_Comma)) return false;
		if (GetExprOwner().size() == 1) {
			stream.PutChar(sig, ',');
			if (sig.IsSignalled()) return false;
		}
	}
	stream.PutChar(sig, ')');
	if (sig.IsSignalled()) return false;
	return true;
}

//-----------------------------------------------------------------------------
// Expr_Indexer
//-----------------------------------------------------------------------------
bool Expr_Indexer::IsIndexer() const { return true; }

Expr *Expr_Indexer::Clone() const
{
	return new Expr_Indexer(*this);
}

Value Expr_Indexer::DoExec(Environment &env) const
{
	if (!Monitor::NotifyExprPre(env, this)) return Value::Nil;
	Value valueCar = GetCar()->Exec(env);
	if (env.IsSignalled()) return Value::Nil;
	ValueList valListIdx;
	foreach_const (ExprOwner, ppExpr, GetExprOwner()) {
		const Expr *pExpr = *ppExpr;
		Value valueIdx = pExpr->Exec(env);
		if (env.IsSignalled()) return Value::Nil;
		valListIdx.push_back(valueIdx);
	}
	Value result = valueCar.EvalIndexGet(env, valListIdx);
	if (env.IsSignalled()) return Value::Nil;
	if (!Monitor::NotifyExprPost(env, this, result)) return Value::Nil;
	return result;
}

Value Expr_Indexer::DoAssign(Environment &env, Value &valueAssigned, bool escalateFlag) const
{
	Value valueCar = GetCar()->Exec(env);
	if (env.IsSignalled()) return Value::Nil;
	ValueList valListIdx;
	foreach_const (ExprOwner, ppExpr, GetExprOwner()) {
		const Expr *pExpr = *ppExpr;
		Value valueIdx = pExpr->Exec(env);
		if (env.IsSignalled()) return Value::Nil;
		valListIdx.push_back(valueIdx);
	}
	valueCar.EvalIndexSet(env, valListIdx, valueAssigned);
	if (env.IsSignalled()) return Value::Nil;
	return valueAssigned;
}

void Expr_Indexer::Accept(ExprVisitor &visitor)
{
	if (visitor.Visit(this)) {
		GetCar()->Accept(visitor);
		GetExprOwner().Accept(visitor);
	}
}

bool Expr_Indexer::GenerateCode(Environment &env, CodeGenerator &codeGenerator) const
{
	return codeGenerator.GenCode_Indexer(env, this);
}

bool Expr_Indexer::GenerateScript(Signal &sig, SimpleStream &stream,
								ScriptStyle scriptStyle, int nestLevel, const char *strIndent) const
{
	if (GetCar()->IsIdentifier()) {
		const Expr_Identifier *pExprIdentifier = dynamic_cast<const Expr_Identifier *>(GetCar());
		if (!pExprIdentifier->GenerateScriptHead(
				sig, stream, scriptStyle, nestLevel, strIndent)) return false;
		stream.PutChar(sig, '[');
		if (sig.IsSignalled()) return false;
		if (GetExprOwner().empty()) {
			// nothing to do
		} else if (scriptStyle == SCRSTYLE_Brief && !GetExprOwner().IsAtSameLine()) {
			stream.Print(sig, " .. ");
			if (sig.IsSignalled()) return false;
		} else {
			if (!GetExprOwner().GenerateScript(
					sig, stream, scriptStyle, nestLevel, strIndent, SEP_Comma)) return false;
		}
		stream.PutChar(sig, ']');
		if (sig.IsSignalled()) return false;
		if (!pExprIdentifier->GenerateScriptTail(
				sig, stream, scriptStyle, nestLevel, strIndent)) return false;
		return true;
	} else {
		bool needParenthesisFlag = false;
		if (GetCar()->IsCaller()) {
			const Expr_Caller *pExprCaller = dynamic_cast<const Expr_Caller *>(GetCar());
			needParenthesisFlag = !pExprCaller->GetAttrs().empty();
		}
		if (needParenthesisFlag) {
			stream.PutChar(sig, '(');
			if (sig.IsSignalled()) return false;
		}
		if (!GetCar()->GenerateScript(sig, stream, scriptStyle, nestLevel, strIndent)) return false;
		if (needParenthesisFlag) {
			stream.PutChar(sig, ')');
			if (sig.IsSignalled()) return false;
		}
		stream.PutChar(sig, '[');
		if (sig.IsSignalled()) return false;
		if (GetExprOwner().empty()) {
			// nothing to do
		} else if (scriptStyle == SCRSTYLE_Brief && !GetExprOwner().IsAtSameLine()) {
			stream.Print(sig, " .. ");
			if (sig.IsSignalled()) return false;
		} else {
			if (!GetExprOwner().GenerateScript(sig, stream,
								scriptStyle, nestLevel, strIndent, SEP_Comma)) return false;
		}
		stream.PutChar(sig, ']');
		if (sig.IsSignalled()) return false;
		return true;
	}
}

//-----------------------------------------------------------------------------
// Expr_Caller
//-----------------------------------------------------------------------------
bool Expr_Caller::IsCaller() const { return true; }

Expr_Caller::Expr_Caller(Expr *pExprCar, Expr_Lister *pExprLister, Expr_Block *pExprBlock, ULong flags) :
	Expr_Compound(EXPRTYPE_Caller,
				  pExprCar, (pExprLister == nullptr)? new Expr_Lister() : pExprLister),
	_pExprBlock(pExprBlock), _pExprTrailer(nullptr),
	_pAttrsShrd(new SymbolSetShared()),
	_pAttrsOptShrd(new SymbolSetShared()),
	_flags(flags), _implicitBlockFlag(false)
{
	if (!_pExprBlock.IsNull()) _pExprBlock->SetParent(this);
	_pCallerInfo.reset(new CallerInfo(
						   GetExprOwner(), GetBlock(), GetAttrsShared(), GetAttrsOptShared()));
}

Expr_Caller::Expr_Caller(const Expr_Caller &expr) :
	Expr_Compound(expr),
	_pExprBlock(expr._pExprBlock.IsNull()? nullptr :
				dynamic_cast<Expr_Block *>(expr._pExprBlock->Clone())),
	_pExprTrailer(expr._pExprTrailer.IsNull()? nullptr :
				  dynamic_cast<Expr_Caller *>(expr._pExprTrailer->Clone())),
	_pAttrsShrd(new SymbolSetShared(*expr._pAttrsShrd)),
	_pAttrsOptShrd(new SymbolSetShared(*expr._pAttrsOptShrd)),
	_flags(expr._flags), _implicitBlockFlag(expr._implicitBlockFlag)
{
	if (!_pExprBlock.IsNull()) _pExprBlock->SetParent(this);
	_pCallerInfo.reset(new CallerInfo(
						   GetExprOwner(), GetBlock(), GetAttrsShared(), GetAttrsOptShared()));
}

Expr_Caller::~Expr_Caller()
{
	if (!_pExprBlock.IsNull()) _pExprBlock->SetParent(GetParent());
	if (!_pExprTrailer.IsNull()) _pExprTrailer->SetParent(GetParent());
}

Expr *Expr_Caller::Clone() const
{
	return new Expr_Caller(*this);
}

void Expr_Caller::UpdateCallerInfo()
{
	ULong flagsToSet = _pCallerInfo->GetFlagsToSet();
	ULong flagsToClear = _pCallerInfo->GetFlagsToClear();
	ResultMode resultMode = _pCallerInfo->GetResultMode();
	ValueType valTypeResult = _pCallerInfo->GetValueTypeResult();
	_pCallerInfo.reset(new CallerInfo(
						   GetExprOwner(), GetBlock(), GetAttrsShared(), GetAttrsOptShared()));
	_pCallerInfo->SetFlagsToSet(flagsToSet);
	_pCallerInfo->SetFlagsToClear(flagsToClear);
	_pCallerInfo->SetResultMode(resultMode);
	_pCallerInfo->SetValueTypeResult(valTypeResult);
}

bool Expr_Caller::AddAttr(const Symbol *pSymbol)
{
	if (_pCallerInfo->UpdateByAttrSymbol(pSymbol)) return false;
	_pAttrsShrd->GetSymbolSet().Insert(pSymbol);
	return true;
}

void Expr_Caller::AddAttrs(const SymbolSet &symbolSet)
{
	foreach_const (SymbolSet, ppSymbol, symbolSet) {
		AddAttr(*ppSymbol);
	}
}

void Expr_Caller::AddTrailingExpr(Expr_Caller *pExprCaller)
{
	if (_pExprBlock.IsNull()) {
		SetBlock(new Expr_Block());
		_implicitBlockFlag = true;
	}
	if (_implicitBlockFlag) {
		_pExprBlock->AddExpr(pExprCaller);
	} else {
		GetLastTrailer()->SetTrailer(pExprCaller);
	}
}

Callable *Expr_Caller::LookupCallable(Environment &env) const
{
	Signal &sig = env.GetSignal();
	if (_pExprCar->IsMember()) return nullptr;
	Value valueCar = _pExprCar->Exec(env);
	if (sig.IsSignalled()) {
		sig.AddExprCause(this);
		return nullptr;
	}
	return valueCar.IsFundamental()? valueCar.GetFundamental() : nullptr;
}

Value Expr_Caller::DoExec(Environment &env) const
{
	Signal &sig = env.GetSignal();
	Value result;
	AutoPtr<TrailCtrlHolder> pTrailCtrlHolder(new TrailCtrlHolder(TRAILCTRL_Continue));
	for (const Expr_Caller *pExprCaller = this; pExprCaller != nullptr;
									pExprCaller = pExprCaller->GetTrailer()) {
		if (!Monitor::NotifyExprPre(env, pExprCaller)) return Value::Nil;
		result = pExprCaller->ExecCallable(env, pTrailCtrlHolder.get());
		if (!Monitor::NotifyExprPost(env, pExprCaller, result)) return Value::Nil;
		TrailCtrl trailCtrl = pTrailCtrlHolder->Get();
		if (trailCtrl == TRAILCTRL_Quit) break;
	}
	// if there's an error suspended by try() function, it would be resumed below.
	// otherwise, nothing would happen and any error would be kept intact.
	sig.ResumeError();
	if (sig.IsSignalled()) return Value::Nil;
	return result;
}

Value Expr_Caller::ExecCallable(Environment &env, TrailCtrlHolder *pTrailCtrlHolder) const
{
	Signal &sig = env.GetSignal();
	// Expr_Caller::Exec(), Expr_Member::Exec() and Expr_Member::DoAssign()
	// correspond to method-calling, property-getting and property-setting.
	if (!_pExprCar->IsMember()) {
		Value valueCar = _pExprCar->Exec(env);
		if (sig.IsSignalled()) return Value::Nil;
		if (!valueCar.IsFundamental()) {
			SetError(sig, ERR_TypeError, "object is not callable");
			return Value::Nil;
		}
		Fundamental *pFund = valueCar.GetFundamental();
		return pFund->DoCall(env, GetCallerInfo(), FLAG_None, Value::Nil, nullptr, pTrailCtrlHolder);
	}
	const Expr_Member *pExprMember = dynamic_cast<const Expr_Member *>(GetCar());
	Value valueThis = pExprMember->GetTarget()->Exec(env);
	Iterator *pIteratorThis = nullptr;
	if (sig.IsSignalled()) return Value::Nil;
	Expr_Member::Mode mode = pExprMember->GetMode();
	ULong flags = FLAG_None;
	if (mode != Expr_Member::MODE_Normal) {
		if (valueThis.Is_list() && valueThis.GetList().empty()) {
			return valueThis;
		}
		Fundamental *pFund = valueThis.IsPrimitive()?
			valueThis.GetClass() : valueThis.GetFundamental();
		pIteratorThis = pFund->CreateIterator(sig);
		if (sig.IsSignalled()) return Value::Nil;
		if (pIteratorThis == nullptr) {
			// nothing to do
		} else if (mode == Expr_Member::MODE_MapAlong) {
			Value valueThisEach;
			pIteratorThis->SetListOriginFlag(valueThis.Is_list());
			if (!pIteratorThis->Next(env, valueThisEach)) return Value::Nil;
			valueThis = valueThisEach;
			flags |= FLAG_Map;
		} else {
			AutoPtr<Iterator> pIteratorMap(new Iterator_MethodMap(
											   env.Clone(),
											   pIteratorThis, Expr_Caller::Reference(this)));
			if (mode == Expr_Member::MODE_MapToIter) {
				return Value(new Object_iterator(env, pIteratorMap.release()));
			}
			Value result = pIteratorMap->ToList(env, false, false);
			if (sig.IsSignalled()) return Value::Nil;
			return result;
		}
	}
	const Expr_Identifier *pExprSelector = pExprMember->GetSelector();
	AutoPtr<Callable> pCallable(
		valueThis.GetCallable(env, pExprSelector->GetSymbol(), pExprSelector->GetAttrs()));
	if (pCallable.IsNull()) return Value::Nil;
	return pCallable->DoCall(env, GetCallerInfo(), flags,
							 valueThis, pIteratorThis, pTrailCtrlHolder);
}

Value Expr_Caller::DoAssign(Environment &env, Value &valueAssigned, bool escalateFlag) const
{
	Signal &sig = env.GetSignal();
	if (!valueAssigned.Is_expr()) {
		SetError(sig, ERR_SyntaxError, "invalid function expression");
		return Value::Nil;
	}
	const Expr *pExprBody = valueAssigned.GetExpr();
	HelpOwner helpOwner;
	while (pExprBody->IsBinaryOp(OPTYPE_ModMod)) {
		const Expr_BinaryOp *pExprEx = dynamic_cast<const Expr_BinaryOp *>(pExprBody);
		if (!pExprEx->GetRight()->IsBlock()) break;
		pExprBody = pExprEx->GetLeft();
		const ExprList &exprList =
			dynamic_cast<const Expr_Block *>(pExprEx->GetRight())->GetExprOwner();
		Help *pHelp = Help::CreateFromExprList(env, exprList);
		if (pHelp == nullptr) return Value::Nil;
		helpOwner.push_back(pHelp);
	}
	// get symbol part of function's declaration
	const Symbol *pSymbol;
	if (GetCar()->IsMember()) {
		const Expr_Member *pExprMember = dynamic_cast<const Expr_Member *>(GetCar());
		pSymbol = pExprMember->GetSelector()->GetSymbol();
	} else if (GetCar()->IsIdentifier()) {
		const Expr_Identifier *pExprIdentifier =
						dynamic_cast<const Expr_Identifier *>(GetCar());
		pSymbol = pExprIdentifier->GetSymbol();
	} else {
		SetError(sig, ERR_SyntaxError, "invalid function expression");
		return Value::Nil;
	}
	FunctionType funcType = !env.IsClass()? FUNCTYPE_Function :
		GetAttrs().IsSet(Gura_Symbol(static_))? FUNCTYPE_Class : FUNCTYPE_Instance;
	FunctionCustom *pFunc = new FunctionCustom(env, pSymbol, pExprBody->Reference(), funcType);
	if (!pFunc->CustomDeclare(env, GetCallerInfo(), SymbolSet::Empty)) {
		Function::Delete(pFunc);
		return Value::Nil;
	}
	Value valueFunc(new Object_function(env, pFunc));
	GetCar()->DoAssign(env, valueFunc, escalateFlag);
	if (sig.IsSignalled()) return Value::Nil;
	if (pFunc->GetFlag(FLAG_SymbolFunc)) return Value::Nil;
	HelpProvider &helpProvider = pFunc->GetHelpProvider();
	foreach_reverse (HelpOwner, ppHelp, helpOwner) {
		Help *pHelp = (*ppHelp)->Reference();
		helpProvider.AddHelp(pHelp);
	}
	return valueFunc;
}

void Expr_Caller::Accept(ExprVisitor &visitor)
{
	if (visitor.Visit(this)) {
		GetCar()->Accept(visitor);
		GetExprOwner().Accept(visitor);
		if (!_pExprBlock.IsNull()) _pExprBlock->Accept(visitor);
		if (!_pExprTrailer.IsNull()) _pExprTrailer->Accept(visitor);
	}
}

bool Expr_Caller::IsParentOf(const Expr *pExpr) const
{
	if (Expr_Compound::IsParentOf(pExpr)) return true;
	if (_pExprBlock.get() == pExpr || _pExprTrailer.get() == pExpr) return true;
	if (!_pExprBlock.IsNull() && _pExprBlock->IsParentOf(pExpr)) return true;
	if (!_pExprTrailer.IsNull() && _pExprTrailer->IsParentOf(pExpr)) return true;
	return false;
}

Expr *Expr_Caller::MathDiff(Environment &env, const Symbol *pSymbol) const
{
	Signal &sig = env.GetSignal();
	// f(g(x))' = f(u)'g(x)'
	if (GetExprOwner().size() != 1) return nullptr;
	const Expr *pExprArg = GetExprOwner().front();
	Value value = GetCar()->Exec(env);
	if (sig.IsSignalled()) {
		sig.AddExprCause(this);
		return nullptr;
	}
	if (!value.Is_function()) {
		SetError(sig, ERR_ValueError, "object must be a function");
		return nullptr;
	}
	Expr *pExprArgDiff = pExprArg->MathDiff(env, pSymbol);
	if (pExprArgDiff == nullptr) return nullptr;
	if (pExprArgDiff->IsConstNumber(0)) {
		return pExprArgDiff;
	}
	Expr *pExprFuncDiff = value.GetFunction()->MathDiff(env, pExprArg, pSymbol);
	if (sig.IsSignalled()) {
		sig.AddExprCause(this);
		return nullptr;
	}
	if (pExprArgDiff->IsConstNumber(1)) {
		Expr::Delete(pExprArgDiff);
		return pExprFuncDiff;
	}
	return Operator_Mul::MathOptimize(env, pExprFuncDiff, pExprArgDiff);
}

Expr *Expr_Caller::MathOptimize(Environment &env) const
{
	return Clone();
}

bool Expr_Caller::GenerateCode(Environment &env, CodeGenerator &codeGenerator) const
{
	return codeGenerator.GenCode_Caller(env, this);
}

bool Expr_Caller::GenerateScript(Signal &sig, SimpleStream &stream,
								ScriptStyle scriptStyle, int nestLevel, const char *strIndent) const
{
	bool argListFlag = !GetExprOwner().empty() || GetCallerInfo().HasAttrs() || _pExprBlock.IsNull();
	if (_pExprCar->IsIdentifier()) {
		const Symbol *pSymbol = dynamic_cast<const Expr_Identifier *>(GetCar())->GetSymbol();
		if (!_pExprCar->GenerateScript(sig, stream, scriptStyle, nestLevel, strIndent)) return false;
		if (pSymbol->IsFlowControlSymbol() && argListFlag) {
			stream.PutChar(sig, ' ');
			if (sig.IsSignalled()) return false;
		}
	} else if (_pExprCar->IsCaller()) {
		stream.PutChar(sig, '(');
		if (sig.IsSignalled()) return false;
		if (!_pExprCar->GenerateScript(sig, stream, scriptStyle, nestLevel, strIndent)) return false;
		stream.PutChar(sig, ')');
		if (sig.IsSignalled()) return false;
	} else {
		if (!_pExprCar->GenerateScript(sig, stream, scriptStyle, nestLevel, strIndent)) return false;
	}
	if (argListFlag) {
		stream.PutChar(sig, '(');
		if (sig.IsSignalled()) return false;
		if (!GetExprOwner().GenerateScript(
				sig, stream, scriptStyle, nestLevel, strIndent, SEP_Comma)) return false;
		stream.PutChar(sig, ')');
		if (sig.IsSignalled()) return false;
	}
	const Symbol *pSymbolFront = Symbol::Empty;
	if (!_attrFront.empty()) {
		stream.PutChar(sig, ':');
		if (sig.IsSignalled()) return false;
		pSymbolFront = _attrFront.front();
		foreach_const (SymbolList, ppSymbol, _attrFront) {
			const Symbol *pSymbol = *ppSymbol;
			if (ppSymbol != _attrFront.begin()) {
				stream.PutChar(sig, '.');
				if (sig.IsSignalled()) return false;
			}
			stream.Print(sig, pSymbol->GetName());
			if (sig.IsSignalled()) return false;
		}
	}
	stream.Print(sig, _pCallerInfo->MakeAttrForFlags().c_str());
	if (sig.IsSignalled()) return false;
	stream.Print(sig, _pCallerInfo->MakeAttrForResultMode().c_str());
	if (sig.IsSignalled()) return false;
	foreach_const (SymbolSet, ppSymbol, GetAttrs()) {
		const Symbol *pSymbol = *ppSymbol;
		if (!pSymbol->IsIdentical(pSymbolFront)) {
			stream.PutChar(sig, ':');
			if (sig.IsSignalled()) return false;
			stream.Print(sig, pSymbol->GetName());
			if (sig.IsSignalled()) return false;
		}
	}
	if (!GetAttrsOpt().empty()) {
		stream.PutChar(sig, ':');
		if (sig.IsSignalled()) return false;
		stream.PutChar(sig, '[');
		if (sig.IsSignalled()) return false;
		foreach_const (SymbolSet, ppSymbol, GetAttrsOpt()) {
			const Symbol *pSymbol = *ppSymbol;
			if (ppSymbol != GetAttrsOpt().begin()) {
				stream.PutChar(sig, ',');
				if (sig.IsSignalled()) return false;
			}
			stream.Print(sig, pSymbol->GetName());
			if (sig.IsSignalled()) return false;
		}
		stream.PutChar(sig, ']');
		if (sig.IsSignalled()) return false;
	}
	if (!_pExprBlock.IsNull()) {
		if (scriptStyle != SCRSTYLE_Crammed) {
			stream.PutChar(sig, ' ');
			if (sig.IsSignalled()) return false;
		}
		if (!_pExprBlock->GenerateScript(sig, stream, scriptStyle, nestLevel, strIndent)) return false;
	}
	if (!_pExprTrailer.IsNull()) {
		if (scriptStyle != SCRSTYLE_Crammed) {
			stream.PutChar(sig, ' ');
			if (sig.IsSignalled()) return false;
		}
		if (!_pExprTrailer->GenerateScript(sig, stream, scriptStyle, nestLevel, strIndent)) return false;
	}
	return true;
}

}
