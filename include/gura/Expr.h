#ifndef __GURA_EXPR_H__
#define __GURA_EXPR_H__

#include "Common.h"
#include "Symbol.h"
#include "Signal.h"
#include "Environment.h"

namespace Gura {

class Expr;
class ExprList;
class Expr_Member;
class ICallable;

//-----------------------------------------------------------------------------
// ExprType
//-----------------------------------------------------------------------------
enum ExprType {
	EXPRTYPE_None,
	EXPRTYPE_UnaryOp,
	EXPRTYPE_Quote,
	EXPRTYPE_Force,
	EXPRTYPE_Prefix,
	EXPRTYPE_Suffix,
	EXPRTYPE_BinaryOp,
	EXPRTYPE_Assign,
	EXPRTYPE_DictAssign,
	EXPRTYPE_Member,
	EXPRTYPE_Root,
	EXPRTYPE_BlockParam,
	EXPRTYPE_Block,
	EXPRTYPE_Lister,
	EXPRTYPE_TemplateScript,
	EXPRTYPE_Indexer,
	EXPRTYPE_Caller,
	EXPRTYPE_Value,
	EXPRTYPE_Symbol,
	EXPRTYPE_String,
	EXPRTYPE_TemplateString,
};

DLLDECLARE const char *GetExprTypeName(ExprType exprType);

//-----------------------------------------------------------------------------
// ExprVisitor
//-----------------------------------------------------------------------------
class ExprVisitor {
public:
	virtual bool Visit(const Expr *pExpr) = 0;
};

//-----------------------------------------------------------------------------
// Expr
// [class hierarchy under Expr]
// Expr <-+- Expr_Unary <-----+- Expr_UnaryOp
//        |                   +- Expr_Quote
//        |                   +- Expr_Force
//        |                   +- Expr_Prefix
//        |                   `- Expr_Suffix
//        +- Expr_Binary <----+- Expr_BinaryOp
//        |                   +- Expr_Assign
//        |                   +- Expr_DictAssign
//        |                   `- Expr_Member
//        +- Expr_Container <-+- Expr_Root
//        |                   +- Expr_BlockParam
//        |                   +- Expr_Block
//        |                   +- Expr_Lister
//        |                   `- Expr_TemplateScript
//        +- Expr_Compound <--+- Expr_Indexer
//        |                   `- Expr_Caller
//        +- Expr_Value
//        +- Expr_Symbol
//        +- Expr_String
//        `- Expr_TemplateString
//-----------------------------------------------------------------------------
class DLLDECLARE Expr {
public:
	class ExprVisitor_GatherSymbol : public ExprVisitor {
	private:
		SymbolSet &_symbolSet;
	public:
		inline ExprVisitor_GatherSymbol(SymbolSet &symbolSet) :
												_symbolSet(symbolSet) {}
		virtual bool Visit(const Expr *pExpr);
	};
	class ExprVisitor_GatherSimpleLambdaArgs : public ExprVisitor {
	private:
		SymbolSet _symbolSet;
		ExprList &_exprListArg;
	public:
		inline ExprVisitor_GatherSimpleLambdaArgs(ExprList &exprListArg) : _exprListArg(exprListArg) {}
		virtual bool Visit(const Expr *pExpr);
	};
private:
	ExprType _exprType;
	int _cntRef;	// const_cast is used to update this value
	int _lineNoTop, _lineNoBtm;
	const Expr *_pExprParent;
public:
	inline Expr(ExprType exprType) : _exprType(exprType),
		_cntRef(1), _lineNoTop(0), _lineNoBtm(0), _pExprParent(NULL) {}
	inline Expr(const Expr &expr) : _exprType(expr._exprType),
		_cntRef(1), _lineNoTop(expr._lineNoTop), _lineNoBtm(expr._lineNoBtm), _pExprParent(expr._pExprParent) {}
protected:
	virtual ~Expr();
public:
	inline static Expr *Reference(const Expr *pExpr) {
		if (pExpr == NULL) return NULL;
		Expr *pExprCasted = const_cast<Expr *>(pExpr);
		pExprCasted->_cntRef++;
		return pExprCasted;
	}
	virtual Expr *IncRef() const;
	inline int DecRef() { if (_cntRef > 0) _cntRef--; return _cntRef; }
	inline int GetRefCnt() const { return _cntRef; }
	inline static void Delete(Expr *pExpr) {
		if (pExpr != NULL && pExpr->DecRef() <= 0) delete pExpr;
	}
	inline void SetLineNo(int lineNoTop, int lineNoBtm) {
		_lineNoTop = lineNoTop, _lineNoBtm = lineNoBtm;
	}
	inline int GetLineNoTop() const { return _lineNoTop; }
	inline int GetLineNoBtm() const { return _lineNoBtm; }
	inline void SetParent(const Expr *pExpr) { _pExprParent = pExpr; }
	inline const Expr *GetParent() const { return _pExprParent; }
	inline const char *GetTypeName() const { return GetExprTypeName(_exprType); }
	inline ExprType GetType() const { return _exprType; }
	inline bool IsType(ExprType exprType) const { return _exprType == exprType; }
	Function *ToFunction(Environment &env, Signal sig,
				const ValueList &valListArg, const SymbolSet &attrs) const;
	bool IsAtSameLine(const Expr *pExpr) const;
	void GatherSymbol(SymbolSet &symbolSet) const;
	void GatherSimpleLambdaArgs(ExprList &exprList) const;
	bool GetChainedSymbolList(SymbolList &symbolList) const;
	void SetError(Signal sig, ErrorType errType, const char *format, ...) const;
	void SetError_NotAssignableSymbol(Signal sig, const Symbol *pSymbol) const;
	static bool NeedParenthesis(const Function &funcOuter,
										const Function &func, bool rightFlag);
	virtual Expr *Clone() const = 0;
	virtual const char *GetPathName() const;
	
	virtual ICallable *LookupCallable(Environment &env, Signal sig) const;
	virtual Value Exec(Environment &env, Signal sig) const = 0;
	bool ExecInArg(Environment &env, Signal sig,
					ValueList &valListArg, size_t &nElems, bool quoteFlag) const;
	virtual void Accept(ExprVisitor &visitor) const = 0;
	virtual bool IsParentOf(const Expr *pExpr) const;
	virtual Value DoAssign(Environment &env, Signal sig, Value &value,
					const SymbolSet *pSymbolsAssignable, bool escalateFlag) const;
	virtual Expr *MathDiff(Environment &env, Signal sig, const Symbol *pSymbol) const;
	virtual Expr *MathOptimize(Environment &env, Signal sig) const;
	virtual const Expr *Unquote() const;
	virtual bool IsUnary() const;
	virtual bool IsQuote() const;
	virtual bool IsForce() const;
	virtual bool IsPrefix() const;
	virtual bool IsSuffix() const;
	virtual bool IsUnaryOp() const;
	virtual bool IsBinary() const;
	virtual bool IsAssign() const;
	virtual bool IsDictAssign() const;
	virtual bool IsBinaryOp() const;
	virtual bool IsMember() const;
	virtual bool IsContainer() const;
	virtual bool IsRoot() const;
	virtual bool IsBlockParam() const;
	virtual bool IsBlock() const;
	virtual bool IsLister() const;
	virtual bool IsTemplateScript() const;
	virtual bool IsCompound() const;
	virtual bool IsIndexer() const;
	virtual bool IsCaller() const;
	virtual bool IsValue() const;
	virtual bool IsSymbol() const;
	virtual bool IsString() const;
	virtual bool IsTemplateString() const;
	bool IsConstNumber(Number num) const;
	bool IsConstEvenNumber() const;
	bool IsConstNegNumber() const;
	bool IsOperatorNeg() const;
	bool IsOperatorMultiply() const;
	bool IsOperatorPower() const;
	bool IsOperatorSequence() const;
	virtual bool GenerateCode(Environment &env, Signal sig, Stream &stream);
	virtual bool DoSerialize(Environment &env, Signal sig, Stream &stream) const = 0;
	virtual bool DoDeserialize(Environment &env, Signal sig, Stream &stream) = 0;
	virtual String ToString() const = 0;
	static bool Serialize(Environment &env, Signal sig, Stream &stream, const Expr *pExpr);
	static bool Deserialize(Environment &env, Signal sig, Stream &stream, Expr **ppExpr, bool mustBeValidFlag);
};

//-----------------------------------------------------------------------------
// ExprList
//-----------------------------------------------------------------------------
class DLLDECLARE ExprList : public std::vector<Expr *> {
private:
	class ValueVisitorEx : public ValueVisitor {
	private:
		ValueList &_valList;
	public:
		inline ValueVisitorEx(ValueList &valList) : _valList(valList) {}
		virtual void Visit(Signal sig, const Value &value);
	};
public:
	static const ExprList Null;
public:
	inline ExprList() {};
	inline ExprList(Expr *pExpr) : std::vector<Expr *>(1) {
		(*this)[0] = pExpr;
	}
	inline ExprList(Expr *pExpr1, Expr *pExpr2) : std::vector<Expr *>(2) {
		(*this)[0] = pExpr1, (*this)[1] = pExpr2;
	}
	Value Exec(Environment &env, Signal sig, bool evalSymFuncFlag) const;
	Value ExecInRoot(Environment &env, Signal sig) const;
	Value ExecForList(Environment &env, Signal sig,
							bool flattenFlag, bool evalSymFuncFlag) const;
	void IncRef() const;
	bool GenerateCode(Environment &env, Signal sig, Stream &stream);
	bool Serialize(Environment &env, Signal sig, Stream &stream) const;
	String ToString(const char *sep = ", ") const;
	void Accept(ExprVisitor &visitor) const;
	bool IsContained(const Expr *pExpr) const;
	void SetParent(const Expr *pExpr);
private:
	inline ExprList(const ExprList &exprList) {}; // not supported
};

//-----------------------------------------------------------------------------
// ExprOwner
//-----------------------------------------------------------------------------
class DLLDECLARE ExprOwner : public ExprList {
public:
	inline ExprOwner() {}
	ExprOwner(const ExprList &exprList);
	ExprOwner(const ExprOwner &exprOwner);
	void Clear();
	~ExprOwner();
	bool Deserialize(Environment &env, Signal sig, Stream &stream);
};

//-----------------------------------------------------------------------------
// Expr_Unary
//-----------------------------------------------------------------------------
class DLLDECLARE Expr_Unary : public Expr {
private:
	ExprOwner _exprOwner;
public:
	Expr_Unary(ExprType exprType, Expr *pExprChild);
	Expr_Unary(const Expr_Unary &expr);
	virtual ~Expr_Unary();
	virtual bool IsUnary() const;
	virtual Expr *IncRef() const;
	virtual void Accept(ExprVisitor &visitor) const;
	virtual bool IsParentOf(const Expr *pExpr) const;
	virtual bool DoSerialize(Environment &env, Signal sig, Stream &stream) const;
	virtual bool DoDeserialize(Environment &env, Signal sig, Stream &stream);
	inline Expr *GetChild() { return const_cast<Expr *>(_exprOwner[0]); }
	inline const Expr *GetChild() const { return _exprOwner[0]; }
	inline const ExprOwner &GetExprOwner() const { return _exprOwner; }
};

//-----------------------------------------------------------------------------
// Expr_Binary
//-----------------------------------------------------------------------------
class DLLDECLARE Expr_Binary : public Expr {
private:
	ExprOwner _exprOwner;
public:
	Expr_Binary(ExprType exprType, Expr *pExprLeft, Expr *pExprRight);
	Expr_Binary(const Expr_Binary &expr);
	virtual ~Expr_Binary();
	virtual bool IsBinary() const;
	virtual Expr *IncRef() const;
	virtual void Accept(ExprVisitor &visitor) const;
	virtual bool IsParentOf(const Expr *pExpr) const;
	virtual bool DoSerialize(Environment &env, Signal sig, Stream &stream) const;
	virtual bool DoDeserialize(Environment &env, Signal sig, Stream &stream);
	inline Expr *GetLeft() { return const_cast<Expr *>(_exprOwner[0]); }
	inline Expr *GetRight() { return const_cast<Expr *>(_exprOwner[1]); }
	inline const Expr *GetLeft() const { return _exprOwner[0]; }
	inline const Expr *GetRight() const { return _exprOwner[1]; }
	inline const ExprOwner &GetExprOwner() const { return _exprOwner; }
};

//-----------------------------------------------------------------------------
// Expr_Container
//-----------------------------------------------------------------------------
class DLLDECLARE Expr_Container : public Expr {
protected:
	ExprOwner _exprOwner;
public:
	inline Expr_Container(ExprType exprType) : Expr(exprType) {}
	Expr_Container(const Expr_Container &expr);
	virtual bool IsContainer() const;
	virtual ~Expr_Container();
	virtual Expr *IncRef() const;
	virtual void Accept(ExprVisitor &visitor) const;
	virtual bool IsParentOf(const Expr *pExpr) const;
	virtual bool DoSerialize(Environment &env, Signal sig, Stream &stream) const;
	virtual bool DoDeserialize(Environment &env, Signal sig, Stream &stream);
	inline void AddExpr(Expr *pExpr) {
		_exprOwner.push_back(pExpr);
		pExpr->SetParent(this);
	}
	inline ExprOwner &GetExprOwner() { return _exprOwner; }
	inline const ExprOwner &GetExprOwner() const { return _exprOwner; }
};

//-----------------------------------------------------------------------------
// Expr_Value
//-----------------------------------------------------------------------------
class DLLDECLARE Expr_Value : public Expr {
protected:
	Value _value;
public:
	inline Expr_Value(Number num) : Expr(EXPRTYPE_Value), _value(num) {}
	inline Expr_Value(const Complex &comp) : Expr(EXPRTYPE_Value), _value(comp) {}
	inline Expr_Value(const Value &value) : Expr(EXPRTYPE_Value), _value(value) {}
	inline Expr_Value(const Expr_Value &expr) : Expr(expr), _value(expr._value) {}
	inline const Value &GetValue() const { return _value; }
	virtual ~Expr_Value();
	virtual Expr *IncRef() const;
	virtual bool IsValue() const;
	virtual Expr *Clone() const;
	virtual Value Exec(Environment &env, Signal sig) const;
	virtual Expr *MathDiff(Environment &env, Signal sig, const Symbol *pSymbol) const;
	virtual Expr *MathOptimize(Environment &env, Signal sig) const;
	virtual void Accept(ExprVisitor &visitor) const;
	virtual bool GenerateCode(Environment &env, Signal sig, Stream &stream);
	virtual bool DoSerialize(Environment &env, Signal sig, Stream &stream) const;
	virtual bool DoDeserialize(Environment &env, Signal sig, Stream &stream);
	virtual String ToString() const;
};

//-----------------------------------------------------------------------------
// Expr_String
//-----------------------------------------------------------------------------
class DLLDECLARE Expr_String : public Expr {
protected:
	String _str;
public:
	inline Expr_String(const String &str) : Expr(EXPRTYPE_String), _str(str) {}
	inline Expr_String(const Expr_String &expr) : Expr(expr), _str(expr._str) {}
	inline const char *GetString() const { return _str.c_str(); }
	virtual ~Expr_String();
	virtual Expr *IncRef() const;
	virtual bool IsString() const;
	virtual Expr *Clone() const;
	virtual Value Exec(Environment &env, Signal sig) const;
	virtual void Accept(ExprVisitor &visitor) const;
	virtual bool GenerateCode(Environment &env, Signal sig, Stream &stream);
	virtual bool DoSerialize(Environment &env, Signal sig, Stream &stream) const;
	virtual bool DoDeserialize(Environment &env, Signal sig, Stream &stream);
	virtual String ToString() const;
};

//-----------------------------------------------------------------------------
// Expr_TemplateString
//-----------------------------------------------------------------------------
class DLLDECLARE Expr_TemplateString : public Expr {
protected:
	SimpleStream &_streamDst;
	String _str;
public:
	inline Expr_TemplateString(SimpleStream &streamDst, const String &str) :
				Expr(EXPRTYPE_TemplateString), _streamDst(streamDst), _str(str) {}
	inline Expr_TemplateString(const Expr_TemplateString &expr) :
				Expr(expr), _streamDst(expr._streamDst), _str(expr._str) {}
	inline SimpleStream &GetStreamDst() { return _streamDst;; }
	inline const char *GetString() const { return _str.c_str(); }
	virtual ~Expr_TemplateString();
	virtual Expr *IncRef() const;
	virtual bool IsTemplateString() const;
	virtual Expr *Clone() const;
	virtual Value Exec(Environment &env, Signal sig) const;
	virtual void Accept(ExprVisitor &visitor) const;
	virtual bool GenerateCode(Environment &env, Signal sig, Stream &stream);
	virtual bool DoSerialize(Environment &env, Signal sig, Stream &stream) const;
	virtual bool DoDeserialize(Environment &env, Signal sig, Stream &stream);
	virtual String ToString() const;
};

//-----------------------------------------------------------------------------
// Expr_Symbol
//-----------------------------------------------------------------------------
class DLLDECLARE Expr_Symbol : public Expr {
protected:
	const Symbol *_pSymbol;
	SymbolSet _attrs;
	SymbolSet _attrsOpt;
	SymbolList _attrFront;
public:
	inline Expr_Symbol(const Symbol *pSymbol) : Expr(EXPRTYPE_Symbol), _pSymbol(pSymbol) {}
	inline Expr_Symbol(const Expr_Symbol &expr) : Expr(expr),
							_pSymbol(expr._pSymbol), _attrs(expr._attrs) {}
	virtual ~Expr_Symbol();
	virtual Expr *IncRef() const;
	virtual bool IsSymbol() const;
	virtual Expr *Clone() const;
	virtual ICallable *LookupCallable(Environment &env, Signal sig) const;
	virtual Value Exec(Environment &env, Signal sig) const;
	virtual Value DoAssign(Environment &env, Signal sig, Value &value,
					const SymbolSet *pSymbolsAssignable, bool escalateFlag) const;
	virtual void Accept(ExprVisitor &visitor) const;
	virtual Expr *MathDiff(Environment &env, Signal sig, const Symbol *pSymbol) const;
	virtual Expr *MathOptimize(Environment &env, Signal sig) const;
	inline void AddAttr(const Symbol *pSymbol) { _attrs.Insert(pSymbol); }
	inline void AddAttrOpt(const Symbol *pSymbol) { _attrsOpt.Insert(pSymbol); }
	inline const SymbolSet &GetAttrs() const { return _attrs; }
	inline const SymbolSet &GetAttrsOpt() const { return _attrsOpt; }
	inline const Symbol *GetSymbol() const { return _pSymbol; }
	inline SymbolList &GetAttrFront() { return _attrFront; }
	inline const SymbolList &GetAttrFront() const { return _attrFront; }
	virtual bool GenerateCode(Environment &env, Signal sig, Stream &stream);
	virtual bool DoSerialize(Environment &env, Signal sig, Stream &stream) const;
	virtual bool DoDeserialize(Environment &env, Signal sig, Stream &stream);
	virtual String ToString() const;
};

//-----------------------------------------------------------------------------
// Expr_Root
//-----------------------------------------------------------------------------
class DLLDECLARE Expr_Root : public Expr_Container {
private:
	String _pathName;
public:
	inline Expr_Root(const String &pathName) :
						Expr_Container(EXPRTYPE_Root), _pathName(pathName) {}
	inline Expr_Root(const Expr_Root &expr) :
						Expr_Container(expr), _pathName(expr._pathName) {}
	virtual ~Expr_Root();
	virtual bool IsRoot() const;
	virtual Expr *Clone() const;
	virtual const char *GetPathName() const;
	virtual Value Exec(Environment &env, Signal sig) const;
	virtual bool GenerateCode(Environment &env, Signal sig, Stream &stream);
	virtual bool DoSerialize(Environment &env, Signal sig, Stream &stream) const;
	virtual bool DoDeserialize(Environment &env, Signal sig, Stream &stream);
	virtual String ToString() const;
};

//-----------------------------------------------------------------------------
// Expr_BlockParam
//-----------------------------------------------------------------------------
class DLLDECLARE Expr_BlockParam : public Expr_Container {
public:
	inline Expr_BlockParam() : Expr_Container(EXPRTYPE_BlockParam) {}
	inline Expr_BlockParam(const Expr_BlockParam &expr) : Expr_Container(expr) {}
	virtual ~Expr_BlockParam();
	virtual bool IsBlockParam() const;
	virtual Expr *Clone() const;
	virtual Value Exec(Environment &env, Signal sig) const;
	virtual bool GenerateCode(Environment &env, Signal sig, Stream &stream);
	virtual bool DoSerialize(Environment &env, Signal sig, Stream &stream) const;
	virtual bool DoDeserialize(Environment &env, Signal sig, Stream &stream);
	virtual String ToString() const;
};

//-----------------------------------------------------------------------------
// Expr_Block
//-----------------------------------------------------------------------------
class DLLDECLARE Expr_Block : public Expr_Container {
protected:
	AutoPtr<Expr_BlockParam> _pExprBlockParam;	// this may be NULL
public:
	inline Expr_Block() : Expr_Container(EXPRTYPE_Block), _pExprBlockParam(NULL) {}
	Expr_Block(const Expr_Block &expr);
	virtual ~Expr_Block();
	virtual bool IsBlock() const;
	virtual Expr *Clone() const;
	virtual Value Exec(Environment &env, Signal sig) const;
	virtual Expr *MathDiff(Environment &env, Signal sig, const Symbol *pSymbol) const;
	virtual void Accept(ExprVisitor &visitor) const;
	virtual bool GenerateCode(Environment &env, Signal sig, Stream &stream);
	virtual bool DoSerialize(Environment &env, Signal sig, Stream &stream) const;
	virtual bool DoDeserialize(Environment &env, Signal sig, Stream &stream);
	virtual String ToString() const;
	inline void SetParam(Expr_BlockParam *pExprBlockParam) {
		_pExprBlockParam.reset(pExprBlockParam);
	}
	inline const Expr_BlockParam *GetParam() const { return _pExprBlockParam.get(); }
};

//-----------------------------------------------------------------------------
// Expr_Lister
//-----------------------------------------------------------------------------
class DLLDECLARE Expr_Lister : public Expr_Container {
public:
	inline Expr_Lister() : Expr_Container(EXPRTYPE_Lister) {}
	inline Expr_Lister(Expr *pExpr) : Expr_Container(EXPRTYPE_Lister) {
		AddExpr(pExpr);
	}
	inline Expr_Lister(const Expr_Lister &expr) : Expr_Container(expr) {}
	virtual ~Expr_Lister();
	virtual bool IsLister() const;
	virtual Expr *Clone() const;
	virtual Value Exec(Environment &env, Signal sig) const;
	virtual Value DoAssign(Environment &env, Signal sig, Value &value,
					const SymbolSet *pSymbolsAssignable, bool escalateFlag) const;
	virtual bool GenerateCode(Environment &env, Signal sig, Stream &stream);
	virtual bool DoSerialize(Environment &env, Signal sig, Stream &stream) const;
	virtual bool DoDeserialize(Environment &env, Signal sig, Stream &stream);
	virtual String ToString() const;
};

//-----------------------------------------------------------------------------
// Expr_TemplateScript
//-----------------------------------------------------------------------------
class DLLDECLARE Expr_TemplateScript : public Expr_Container {
protected:
	SimpleStream &_streamDst;
	String _strIndent;
	bool _autoIndentFlag;
	bool _appendLastEOLFlag;
public:
	inline Expr_TemplateScript(SimpleStream &streamDst, const String &strIndent,
							bool autoIndentFlag, bool appendLastEOLFlag) :
			Expr_Container(EXPRTYPE_TemplateScript), _streamDst(streamDst), _strIndent(strIndent),
			_autoIndentFlag(autoIndentFlag), _appendLastEOLFlag(appendLastEOLFlag) {}
	inline Expr_TemplateScript(const Expr_TemplateScript &expr) :
			Expr_Container(expr), _streamDst(expr._streamDst), _strIndent(expr._strIndent),
			_autoIndentFlag(expr._autoIndentFlag), _appendLastEOLFlag(expr._appendLastEOLFlag) {}
	inline SimpleStream &GetStreamDst() { return _streamDst;; }
	virtual ~Expr_TemplateScript();
	virtual bool IsTemplateScript() const;
	virtual Expr *Clone() const;
	virtual Value Exec(Environment &env, Signal sig) const;
	virtual bool GenerateCode(Environment &env, Signal sig, Stream &stream);
	virtual bool DoSerialize(Environment &env, Signal sig, Stream &stream) const;
	virtual bool DoDeserialize(Environment &env, Signal sig, Stream &stream);
	virtual String ToString() const;
};

//-----------------------------------------------------------------------------
// Expr_Compound
//-----------------------------------------------------------------------------
class DLLDECLARE Expr_Compound : public Expr {
protected:
	AutoPtr<Expr> _pExprCar;
	AutoPtr<Expr_Lister> _pExprLister;
public:
	Expr_Compound(ExprType exprType, Expr *pExprCar, Expr_Lister *pExprLister);
	Expr_Compound(const Expr_Compound &expr);
	virtual ~Expr_Compound();
	virtual bool IsCompound() const;
	virtual Expr *IncRef() const;
	virtual bool IsParentOf(const Expr *pExpr) const;
	virtual bool DoSerialize(Environment &env, Signal sig, Stream &stream) const;
	virtual bool DoDeserialize(Environment &env, Signal sig, Stream &stream);
	inline Expr *GetCar() { return _pExprCar.get(); }
	inline const Expr *GetCar() const { return _pExprCar.get(); }
	inline Expr_Lister *GetLister() { return _pExprLister.get(); }
	inline const Expr_Lister *GetLister() const { return _pExprLister.get(); }
	inline ExprOwner &GetExprOwner() { return _pExprLister->GetExprOwner(); }
	inline const ExprOwner &GetExprOwner() const { return _pExprLister->GetExprOwner(); }
};

//-----------------------------------------------------------------------------
// Expr_Indexer
//-----------------------------------------------------------------------------
class DLLDECLARE Expr_Indexer : public Expr_Compound {
public:
	inline Expr_Indexer(Expr *pExprCar, Expr_Lister *pExprLister) :
			Expr_Compound(EXPRTYPE_Indexer, pExprCar, pExprLister) {}
	inline Expr_Indexer(const Expr_Indexer &expr) : Expr_Compound(expr) {}
	virtual ~Expr_Indexer();
	virtual Expr *IncRef() const;
	virtual bool IsIndexer() const;
	virtual Expr *Clone() const;
	virtual Value Exec(Environment &env, Signal sig) const;
	virtual Value DoAssign(Environment &env, Signal sig, Value &value,
					const SymbolSet *pSymbolsAssignable, bool escalateFlag) const;
	virtual void Accept(ExprVisitor &visitor) const;
	virtual bool GenerateCode(Environment &env, Signal sig, Stream &stream);
	virtual bool DoSerialize(Environment &env, Signal sig, Stream &stream) const;
	virtual bool DoDeserialize(Environment &env, Signal sig, Stream &stream);
	virtual String ToString() const;
};

//-----------------------------------------------------------------------------
// Expr_Caller
//-----------------------------------------------------------------------------
class DLLDECLARE Expr_Caller : public Expr_Compound {
protected:
	AutoPtr<Expr_Block> _pExprBlock;		// this may be NULL
	AutoPtr<Expr_Caller> _pExprTrailer;		// this may be NULL
	SymbolSet _attrs;
	SymbolSet _attrsOpt;
	SymbolList _attrFront;
public:
	Expr_Caller(Expr *pExprCar, Expr_Lister *pExprLister, Expr_Block *pExprBlock);
	Expr_Caller(const Expr_Caller &expr);
	virtual ~Expr_Caller();
	virtual Expr *IncRef() const;
	virtual bool IsCaller() const;
	virtual Expr *Clone() const;
	virtual ICallable *LookupCallable(Environment &env, Signal sig) const;
	virtual Value Exec(Environment &env, Signal sig) const;
	virtual Value DoAssign(Environment &env, Signal sig, Value &value,
					const SymbolSet *pSymbolsAssignable, bool escalateFlag) const;
	virtual void Accept(ExprVisitor &visitor) const;
	virtual bool IsParentOf(const Expr *pExpr) const;
	virtual Expr *MathDiff(Environment &env, Signal sig, const Symbol *pSymbol) const;
	virtual Expr *MathOptimize(Environment &env, Signal sig) const;
	virtual bool GenerateCode(Environment &env, Signal sig, Stream &stream);
	virtual bool DoSerialize(Environment &env, Signal sig, Stream &stream) const;
	virtual bool DoDeserialize(Environment &env, Signal sig, Stream &stream);
	virtual String ToString() const;
	Value EvalEach(Environment &env, Signal sig, const Value &valueThis,
		Iterator *pIteratorThis, bool listThisFlag, const Function **ppFuncLeader) const;
	inline void AddAttr(const Symbol *pSymbol) { _attrs.Insert(pSymbol); }
	inline void AddAttrOpt(const Symbol *pSymbol) { _attrsOpt.Insert(pSymbol); }
	inline const SymbolSet &GetAttrs() const { return _attrs; }
	inline const SymbolSet &GetAttrsOpt() const { return _attrsOpt; }
	inline SymbolList &GetAttrFront() { return _attrFront; }
	inline const SymbolList &GetAttrFront() const { return _attrFront; }
	inline void SetBlock(Expr_Block *pExprBlock) {
		_pExprBlock.reset(pExprBlock);
		if (!_pExprBlock.IsNull()) _pExprBlock->SetParent(this);
	}
	inline void SetTrailer(Expr_Caller *pExprCaller) {
		_pExprTrailer.reset(pExprCaller);
		if (!_pExprTrailer.IsNull()) _pExprTrailer->SetParent(this);
	}
	inline Expr_Block *GetBlock() { return _pExprBlock.get(); }
	inline const Expr_Block *GetBlock() const { return _pExprBlock.get(); }
	inline const Expr_Caller *GetTrailer() const { return _pExprTrailer.get(); }
	inline Expr_Caller *GetLastTrailer() {
		return (_pExprTrailer.IsNull())? this : _pExprTrailer->GetLastTrailer();
	}
private:
	Value DoExec(Environment &env, Signal sig, const Function **ppFuncLeader) const;
};

//-----------------------------------------------------------------------------
// Expr_UnaryOp
//-----------------------------------------------------------------------------
class DLLDECLARE Expr_UnaryOp : public Expr_Unary {
protected:
	const Function *_pFunc;
	bool _suffixSymbolFlag;
public:
	inline Expr_UnaryOp(const Function *pFunc, Expr *pExprChild, bool suffixSymbolFlag) :
					Expr_Unary(EXPRTYPE_UnaryOp, pExprChild),
					_pFunc(pFunc), _suffixSymbolFlag(suffixSymbolFlag) {}
	inline Expr_UnaryOp(const Expr_UnaryOp &expr) :
					Expr_Unary(expr),
					_pFunc(expr._pFunc), _suffixSymbolFlag(expr._suffixSymbolFlag) {}
	inline const Function &GetFunction() const { return *_pFunc; }
	virtual ~Expr_UnaryOp();
	virtual Expr *Clone() const;
	virtual Value Exec(Environment &env, Signal sig) const;
	virtual Expr *MathDiff(Environment &env, Signal sig, const Symbol *pSymbol) const;
	virtual Expr *MathOptimize(Environment &env, Signal sig) const;
	virtual bool IsUnaryOp() const;
	virtual bool GenerateCode(Environment &env, Signal sig, Stream &stream);
	virtual bool DoSerialize(Environment &env, Signal sig, Stream &stream) const;
	virtual bool DoDeserialize(Environment &env, Signal sig, Stream &stream);
	virtual String ToString() const;
};

//-----------------------------------------------------------------------------
// Expr_BinaryOp
//-----------------------------------------------------------------------------
class DLLDECLARE Expr_BinaryOp : public Expr_Binary {
protected:
	const Function *_pFunc;
public:
	inline Expr_BinaryOp(const Function *pFunc, Expr *pExprLeft, Expr *pExprRight) :
					Expr_Binary(EXPRTYPE_BinaryOp, pExprLeft, pExprRight), _pFunc(pFunc) {}
	inline Expr_BinaryOp(const Expr_BinaryOp &expr) :
					Expr_Binary(expr), _pFunc(expr._pFunc) {}
	inline const Function &GetFunction() const { return *_pFunc; }
	virtual ~Expr_BinaryOp();
	virtual Expr *Clone() const;
	virtual Value Exec(Environment &env, Signal sig) const;
	virtual Expr *MathDiff(Environment &env, Signal sig, const Symbol *pSymbol) const;
	virtual Expr *MathOptimize(Environment &env, Signal sig) const;
	virtual bool IsBinaryOp() const;
	virtual bool GenerateCode(Environment &env, Signal sig, Stream &stream);
	virtual bool DoSerialize(Environment &env, Signal sig, Stream &stream) const;
	virtual bool DoDeserialize(Environment &env, Signal sig, Stream &stream);
	virtual String ToString() const;
};

//-----------------------------------------------------------------------------
// Expr_Quote
//-----------------------------------------------------------------------------
class DLLDECLARE Expr_Quote : public Expr_Unary {
public:
	inline Expr_Quote(Expr *pExprChild) : Expr_Unary(EXPRTYPE_Quote, pExprChild) {}
	inline Expr_Quote(const Expr_Quote &expr) : Expr_Unary(expr) {}
	virtual ~Expr_Quote();
	virtual Expr *Clone() const;
	virtual Value Exec(Environment &env, Signal sig) const;
	virtual const Expr *Unquote() const;
	virtual bool IsQuote() const;
	virtual bool GenerateCode(Environment &env, Signal sig, Stream &stream);
	virtual bool DoSerialize(Environment &env, Signal sig, Stream &stream) const;
	virtual bool DoDeserialize(Environment &env, Signal sig, Stream &stream);
	virtual String ToString() const;
};

//-----------------------------------------------------------------------------
// Expr_Force
//-----------------------------------------------------------------------------
class DLLDECLARE Expr_Force : public Expr_Unary {
public:
	inline Expr_Force(Expr *pExprChild) : Expr_Unary(EXPRTYPE_Force, pExprChild) {}
	inline Expr_Force(const Expr_Force &expr) : Expr_Unary(expr) {}
	virtual ~Expr_Force();
	virtual Expr *Clone() const;
	virtual Value Exec(Environment &env, Signal sig) const;
	virtual bool IsForce() const;
	virtual bool GenerateCode(Environment &env, Signal sig, Stream &stream);
	virtual bool DoSerialize(Environment &env, Signal sig, Stream &stream) const;
	virtual bool DoDeserialize(Environment &env, Signal sig, Stream &stream);
	virtual String ToString() const;
};

//-----------------------------------------------------------------------------
// Expr_Prefix
//-----------------------------------------------------------------------------
class DLLDECLARE Expr_Prefix : public Expr_Unary {
private:
	const Symbol *_pSymbol;
public:
	inline Expr_Prefix(Expr *pExprChild, const Symbol *pSymbol) :
					Expr_Unary(EXPRTYPE_Prefix, pExprChild), _pSymbol(pSymbol) {}
	inline Expr_Prefix(const Expr_Prefix &expr) :
					Expr_Unary(expr), _pSymbol(expr._pSymbol) {}
	virtual ~Expr_Prefix();
	virtual Expr *Clone() const;
	virtual Value Exec(Environment &env, Signal sig) const;
	virtual bool IsPrefix() const;
	inline const Symbol *GetSymbol() const { return _pSymbol; }
	virtual bool GenerateCode(Environment &env, Signal sig, Stream &stream);
	virtual bool DoSerialize(Environment &env, Signal sig, Stream &stream) const;
	virtual bool DoDeserialize(Environment &env, Signal sig, Stream &stream);
	virtual String ToString() const;
};

//-----------------------------------------------------------------------------
// Expr_Suffix
//-----------------------------------------------------------------------------
class DLLDECLARE Expr_Suffix : public Expr_Unary {
private:
	const Symbol *_pSymbol;
public:
	inline Expr_Suffix(Expr *pExprChild, const Symbol *pSymbol) :
					Expr_Unary(EXPRTYPE_Suffix, pExprChild), _pSymbol(pSymbol) {}
	inline Expr_Suffix(const Expr_Suffix &expr) :
					Expr_Unary(expr), _pSymbol(expr._pSymbol) {}
	virtual ~Expr_Suffix();
	virtual Expr *Clone() const;
	virtual Value Exec(Environment &env, Signal sig) const;
	virtual bool IsSuffix() const;
	inline const Symbol *GetSymbol() const { return _pSymbol; }
	OccurPattern GetOccurPattern() const;
	virtual bool GenerateCode(Environment &env, Signal sig, Stream &stream);
	virtual bool DoSerialize(Environment &env, Signal sig, Stream &stream) const;
	virtual bool DoDeserialize(Environment &env, Signal sig, Stream &stream);
	virtual String ToString() const;
};

//-----------------------------------------------------------------------------
// Expr_Assign
//-----------------------------------------------------------------------------
class DLLDECLARE Expr_Assign : public Expr_Binary {
private:
	const Function *_pFuncToApply;
public:
	inline Expr_Assign(Expr *pExprLeft, Expr *pExprRight, const Function *pFuncToApply) :
				Expr_Binary(EXPRTYPE_Assign, pExprLeft, pExprRight), _pFuncToApply(pFuncToApply) {}
	inline Expr_Assign(const Expr_Assign &expr) :
				Expr_Binary(expr), _pFuncToApply(expr._pFuncToApply) {}
	virtual ~Expr_Assign();
	virtual Value Exec(Environment &env, Signal sig) const;
	Value Exec(Environment &env, Signal sig,
				Environment &envDst, const SymbolSet *pSymbolsAssignable) const;
	virtual Expr *Clone() const;
	virtual bool IsAssign() const;
	virtual bool GenerateCode(Environment &env, Signal sig, Stream &stream);
	virtual bool DoSerialize(Environment &env, Signal sig, Stream &stream) const;
	virtual bool DoDeserialize(Environment &env, Signal sig, Stream &stream);
	virtual String ToString() const;
};

//-----------------------------------------------------------------------------
// Expr_DictAssign
//-----------------------------------------------------------------------------
class DLLDECLARE Expr_DictAssign : public Expr_Binary {
public:
	inline Expr_DictAssign(Expr *pExprLeft, Expr *pExprRight) :
				Expr_Binary(EXPRTYPE_DictAssign, pExprLeft, pExprRight) {}
	inline Expr_DictAssign(const Expr_DictAssign &expr) : Expr_Binary(expr) {}
	virtual ~Expr_DictAssign();
	virtual Value Exec(Environment &env, Signal sig) const;
	virtual Expr *Clone() const;
	virtual bool IsDictAssign() const;
	virtual bool GenerateCode(Environment &env, Signal sig, Stream &stream);
	virtual bool DoSerialize(Environment &env, Signal sig, Stream &stream) const;
	virtual bool DoDeserialize(Environment &env, Signal sig, Stream &stream);
	virtual String ToString() const;
	Value GetKey(Environment &env, Signal sig) const;
};

//-----------------------------------------------------------------------------
// Expr_Member
//-----------------------------------------------------------------------------
class DLLDECLARE Expr_Member : public Expr_Binary {
public:
	enum Mode {
		MODE_Normal,		// foo.bar
		MODE_MapToList,		// foo::bar .. map-to-list
		MODE_MapToIter,		// foo:*bar .. map-to-iterator
		MODE_MapAlong,		// foo:&bar .. map-along
		MODE_max,
	};
private:
	Mode _mode;
public:
	inline Expr_Member(Expr *pExprLeft, Expr *pExprRight, Mode mode = MODE_Normal) :
				Expr_Binary(EXPRTYPE_Member, pExprLeft, pExprRight), _mode(mode) {}
	inline Expr_Member(const Expr_Member &expr) : Expr_Binary(expr), _mode(expr._mode) {}
	inline Mode GetMode() const { return _mode; }
	virtual ~Expr_Member();
	virtual Expr *Clone() const;
	virtual Value Exec(Environment &env, Signal sig) const;
	virtual Value DoAssign(Environment &env, Signal sig, Value &value,
					const SymbolSet *pSymbolsAssignable, bool escalateFlag) const;
	virtual bool IsMember() const;
	virtual bool GenerateCode(Environment &env, Signal sig, Stream &stream);
	virtual bool DoSerialize(Environment &env, Signal sig, Stream &stream) const;
	virtual bool DoDeserialize(Environment &env, Signal sig, Stream &stream);
	virtual String ToString() const;
};

}

#endif
