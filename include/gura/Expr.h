#ifndef __GURA_EXPR_H__
#define __GURA_EXPR_H__

#include "Common.h"
#include "Symbol.h"
#include "Signal.h"
#include "Environment.h"
#include "Processor.h"

namespace Gura {

class Expr;
class ExprList;
class Expr_Member;
class Callable;

//-----------------------------------------------------------------------------
// ExprType
//-----------------------------------------------------------------------------
enum ExprType {
	EXPRTYPE_None,
	EXPRTYPE_UnaryOp,
	EXPRTYPE_Quote,
	EXPRTYPE_BinaryOp,
	EXPRTYPE_Assign,
	EXPRTYPE_Member,
	EXPRTYPE_Root,
	EXPRTYPE_Block,
	EXPRTYPE_Lister,
	EXPRTYPE_Iterer,
	EXPRTYPE_TmplScript,
	EXPRTYPE_Indexer,
	EXPRTYPE_Caller,
	EXPRTYPE_Value,
	EXPRTYPE_Symbol,
	EXPRTYPE_String,
	EXPRTYPE_TmplString,
};

GURA_DLLDECLARE const char *GetExprTypeName(ExprType exprType);

//-----------------------------------------------------------------------------
// TrailCtrl
//-----------------------------------------------------------------------------
enum TrailCtrl {
	TRAILCTRL_Continue,
	TRAILCTRL_Quit,
	TRAILCTRL_Finalize,
};

//-----------------------------------------------------------------------------
// TrailCtrlHolder
//-----------------------------------------------------------------------------
class TrailCtrlHolder {
private:
	int _cntRef;
	TrailCtrl _trailCtrl;
public:
	Gura_DeclareReferenceAccessor(TrailCtrlHolder);
public:
	inline TrailCtrlHolder(TrailCtrl trailCtrl) :
									_cntRef(1), _trailCtrl(trailCtrl) {}
private:
	inline ~TrailCtrlHolder() {}
public:
	inline void Set(TrailCtrl trailCtrl) { _trailCtrl = trailCtrl; }
	inline TrailCtrl Get() const { return _trailCtrl; }
};

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
//        |                   `- Expr_Quote
//        +- Expr_Binary <----+- Expr_BinaryOp
//        |                   +- Expr_Assign
//        |                   `- Expr_Member
//        +- Expr_Container <-+- Expr_Root
//        |                   +- Expr_Block
//        |                   +- Expr_Lister
//        |                   +- Expr_Iterer
//        |                   `- Expr_TmplScript
//        +- Expr_Compound <--+- Expr_Indexer
//        |                   `- Expr_Caller
//        +- Expr_Value
//        +- Expr_Symbol
//        +- Expr_String
//        `- Expr_TmplString
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE Expr {
public:
	enum ScriptStyle {
		SCRSTYLE_None,
		SCRSTYLE_Crammed,
		SCRSTYLE_OneLine,
		SCRSTYLE_Brief,
		SCRSTYLE_Fancy,
	};
	enum Separator {
		SEP_Comma,
		SEP_NewLine,
	};
public:
	class GURA_DLLDECLARE ExprVisitor_GatherSymbol : public ExprVisitor {
	private:
		SymbolSet &_symbolSet;
	public:
		inline ExprVisitor_GatherSymbol(SymbolSet &symbolSet) :
												_symbolSet(symbolSet) {}
		virtual bool Visit(const Expr *pExpr);
	};
	class GURA_DLLDECLARE ExprVisitor_GatherSimpleLambdaArgs : public ExprVisitor {
	private:
		SymbolSet _symbolSet;
		ExprOwner &_exprOwnerArg;
	public:
		inline ExprVisitor_GatherSimpleLambdaArgs(ExprOwner &exprOwnerArg) : _exprOwnerArg(exprOwnerArg) {}
		virtual bool Visit(const Expr *pExpr);
	};
	class GURA_DLLDECLARE ExprVisitor_SearchBar : public ExprVisitor {
	private:
		bool _foundFlag;
	public:
		inline ExprVisitor_SearchBar() : _foundFlag(false) {}
		virtual bool Visit(const Expr *pExpr);
		inline bool GetFoundFlag() const { return _foundFlag; }
	};
	class GURA_DLLDECLARE SequenceRoot : public Sequence {
	private:
		AutoPtr<ExprOwner> _pExprOwner;
		size_t _idxExpr;
	public:
		SequenceRoot(Environment *pEnv, ExprOwner *pExprOwner);
		virtual bool DoStep(Signal sig, Value &result);
		virtual String ToString() const;
	};
private:
	ExprType _exprType;
	int _cntRef;	// const_cast is used to update this value
	int _lineNoTop, _lineNoBtm;
	const Expr *_pExprParent;
public:
	Gura_DeclareReferenceAccessor(Expr);
public:
	inline Expr(ExprType exprType) : _exprType(exprType),
		_cntRef(1), _lineNoTop(0), _lineNoBtm(0), _pExprParent(NULL) {}
	inline Expr(const Expr &expr) : _exprType(expr._exprType),
		_cntRef(1), _lineNoTop(expr._lineNoTop), _lineNoBtm(expr._lineNoBtm), _pExprParent(expr._pExprParent) {}
protected:
	virtual ~Expr();
public:
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
	Value Exec(Environment &env, Signal sig,
		AutoPtr<SeqPostHandler> pSeqPostHandler, bool evalSymFuncFlag = false) const;
	Value Assign(Environment &env, Signal sig, Value &valueAssigned,
					const SymbolSet *pSymbolsAssignable, bool escalateFlag) const;
	inline Value Exec2(Environment &env, Signal sig,
			SeqPostHandler *pSeqPostHandler, bool evalSymFuncFlag = false) const {
		return Exec(env, sig, pSeqPostHandler, evalSymFuncFlag);
	}
	Function *ToFunction(Environment &env, Signal sig,
				const ValueList &valListArg, const SymbolSet &attrs) const;
	bool IsAtSameLine(const Expr *pExpr) const;
	void GatherSymbol(SymbolSet &symbolSet) const;
	void GatherSimpleLambdaArgs(ExprOwner &exprOwner) const;
	bool GetChainedSymbolList(SymbolList &symbolList) const;
	void SetError(Signal sig, ErrorType errType, const char *format, ...) const;
	void SetError_NotAssignableSymbol(Signal sig, const Symbol *pSymbol) const;
	static bool NeedParenthesis(const Operator *pOperatorOuter,
										const Operator *pOperator, bool rightFlag);
	virtual Expr *Clone() const = 0;
	virtual const char *GetSourceName() const;
	virtual Callable *LookupCallable(Environment &env, Signal sig) const;
private:
	virtual Value DoExec(Environment &env, Signal sig, SeqPostHandler *pSeqPostHandler) const = 0;
	virtual Value DoAssign(Environment &env, Signal sig, Value &valueAssigned,
					const SymbolSet *pSymbolsAssignable, bool escalateFlag) const;
public:
	virtual void Accept(ExprVisitor &visitor) const = 0;
	virtual bool IsParentOf(const Expr *pExpr) const;
	virtual Expr *MathDiff(Environment &env, Signal sig, const Symbol *pSymbol) const;
	virtual Expr *MathOptimize(Environment &env, Signal sig) const;
	virtual const Expr *Unquote() const;
	// type chekers - Unary and descendants
	virtual bool IsUnary() const;
	virtual bool IsUnaryOp() const;
	virtual bool IsUnaryOpSuffix() const;
	virtual bool IsQuote() const;
	// type chekers - Binary and descendants
	virtual bool IsBinary() const;
	virtual bool IsBinaryOp() const;
	virtual bool IsAssign() const;
	virtual bool IsMember() const;
	// type chekers - Container and descendants
	virtual bool IsContainer() const;
	virtual bool IsRoot() const;
	virtual bool IsBlock() const;
	virtual bool IsLister() const;
	virtual bool IsIterer() const;
	virtual bool IsTmplScript() const;
	// type chekers - Compound and descendants
	virtual bool IsCompound() const;
	virtual bool IsIndexer() const;
	virtual bool IsCaller() const;
	// type chekers - others
	virtual bool IsValue() const;
	virtual bool IsSymbol() const;
	virtual bool IsString() const;
	virtual bool IsTmplString() const;
	bool IsConstNumber(Number num) const;
	bool IsConstEvenNumber() const;
	bool IsConstNegNumber() const;
	bool IsOperatorNeg() const;
	bool IsOperatorMul() const;
	bool IsOperatorPow() const;
	bool IsOperatorSeq() const;
	bool IsOperatorPair() const;
	virtual bool GenerateCode(Environment &env, Signal sig, Stream &stream);
	virtual bool GenerateScript(Signal sig, SimpleStream &stream,
							ScriptStyle scriptStyle, int nestLevel) const;
	virtual String ToString(ScriptStyle scriptStyle) const;
	String MakePosText() const;
	static bool PutNestIndent(Signal sig, SimpleStream &stream, int nestLevel);
	static ScriptStyle SymbolToScriptStyle(const Symbol *pSymbol);
};

//-----------------------------------------------------------------------------
// ExprList
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE ExprList : public std::vector<Expr *> {
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
	void ExtractTrace(ExprOwner &exprOwner) const;
	bool GenerateCode(Environment &env, Signal sig, Stream &stream);
	bool GenerateScript(Signal sig, SimpleStream &stream,
		Expr::ScriptStyle scriptStyle, int nestLevel, Expr::Separator sep) const;
	void Accept(ExprVisitor &visitor) const;
	bool IsContained(const Expr *pExpr) const;
	void SetParent(const Expr *pExpr);
	bool IsAtSameLine() const;
private:
	inline ExprList(const ExprList &exprList) {}; // not supported
};

//-----------------------------------------------------------------------------
// ExprOwner
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE ExprOwner : public ExprList {
public:
	class GURA_DLLDECLARE Iterator : public Gura::Iterator {
	private:
		size_t _idx;
		AutoPtr<ExprOwner> _pExprOwner;
	public:
		Iterator(ExprOwner *pExprOwner);
		virtual Gura::Iterator *GetSource();
		virtual bool DoNext(Environment &env, Signal sig, Value &value);
		virtual String ToString() const;
		virtual void GatherFollower(Environment::Frame *pFrame, EnvironmentSet &envSet);
	};
	class GURA_DLLDECLARE SequenceEach : public Sequence {
	protected:
		AutoPtr<ExprOwner> _pExprOwner;
		size_t _idxExpr;
	public:
		SequenceEach(Environment *pEnv, ExprOwner *pExprOwner);
	public:
		virtual bool DoStep(Signal sig, Value &result);
		virtual String ToString() const;
	};
	class GURA_DLLDECLARE SequenceToList : public Sequence {
	public:
		class SeqPostHandlerEach : public SeqPostHandler {
		private:
			ValueList &_valList;
		public:
			inline SeqPostHandlerEach(Environment *pEnv, ValueList &valList) :
									SeqPostHandler(pEnv), _valList(valList) {}
			virtual bool DoPost(Signal sig, const Value &result);
		};
	protected:
		AutoPtr<ExprOwner> _pExprOwner;
		size_t _idxExpr;
		Value _result;
		ValueList *_pValList;
		AutoPtr<SeqPostHandlerEach> _pSeqPostHandlerEach;
	public:
		SequenceToList(Environment *pEnv, ExprOwner *pExprOwner);
	public:
		virtual bool DoStep(Signal sig, Value &result);
		virtual String ToString() const;
	};
private:
	int _cntRef;
public:
	Gura_DeclareReferenceAccessor(ExprOwner);
public:
	ExprOwner();
	ExprOwner(const ExprList &exprList);
	ExprOwner(const ExprOwner &exprOwner);
private:
	~ExprOwner();
public:
	void Clear();
};

//-----------------------------------------------------------------------------
// Expr_Unary
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE Expr_Unary : public Expr {
private:
	AutoPtr<Expr> _pExprChild;
public:
	Expr_Unary(ExprType exprType, Expr *pExprChild);
	Expr_Unary(const Expr_Unary &expr);
	inline static Expr_Unary *Reference(const Expr_Unary *pExpr) {
		return dynamic_cast<Expr_Unary *>(Expr::Reference(pExpr));
	}
	virtual ~Expr_Unary();
	virtual bool IsUnary() const;
	virtual void Accept(ExprVisitor &visitor) const;
	virtual bool IsParentOf(const Expr *pExpr) const;
	inline Expr *GetChild() { return _pExprChild.get(); }
	inline const Expr *GetChild() const { return _pExprChild.get(); }
};

//-----------------------------------------------------------------------------
// Expr_Binary
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE Expr_Binary : public Expr {
private:
	AutoPtr<Expr> _pExprLeft;
	AutoPtr<Expr> _pExprRight;
public:
	Expr_Binary(ExprType exprType, Expr *pExprLeft, Expr *pExprRight);
	Expr_Binary(const Expr_Binary &expr);
	inline static Expr_Binary *Reference(const Expr_Binary *pExpr) {
		return dynamic_cast<Expr_Binary *>(Expr::Reference(pExpr));
	}
	virtual ~Expr_Binary();
	virtual bool IsBinary() const;
	virtual void Accept(ExprVisitor &visitor) const;
	virtual bool IsParentOf(const Expr *pExpr) const;
	inline Expr *GetLeft() { return _pExprLeft.get(); }
	inline Expr *GetRight() { return _pExprRight.get(); }
	inline const Expr *GetLeft() const { return _pExprLeft.get(); }
	inline const Expr *GetRight() const { return _pExprRight.get(); }
};

//-----------------------------------------------------------------------------
// Expr_Container
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE Expr_Container : public Expr {
protected:
	AutoPtr<ExprOwner> _pExprOwner;
public:
	Expr_Container(ExprType exprType);
	Expr_Container(const Expr_Container &expr);
	inline static Expr_Container *Reference(const Expr_Container *pExpr) {
		return dynamic_cast<Expr_Container *>(Expr::Reference(pExpr));
	}
	virtual bool IsContainer() const;
	virtual ~Expr_Container();
	virtual void Accept(ExprVisitor &visitor) const;
	virtual bool IsParentOf(const Expr *pExpr) const;
	inline void AddExpr(Expr *pExpr) {
		GetExprOwner().push_back(pExpr);
		pExpr->SetParent(this);
	}
	inline ExprOwner &GetExprOwner() { return *_pExprOwner; }
	inline const ExprOwner &GetExprOwner() const { return *_pExprOwner; }
};

//-----------------------------------------------------------------------------
// Expr_Value
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE Expr_Value : public Expr {
protected:
	Value _value;
	std::auto_ptr<String> _pScript;
public:
	inline Expr_Value(Number num) : Expr(EXPRTYPE_Value), _value(num) {}
	inline Expr_Value(const Complex &comp) : Expr(EXPRTYPE_Value), _value(comp) {}
	inline Expr_Value(const Value &value) : Expr(EXPRTYPE_Value), _value(value) {}
	inline Expr_Value(const Expr_Value &expr) : Expr(expr), _value(expr._value) {}
	inline const Value &GetValue() const { return _value; }
	inline void SetScript(const String &script) { _pScript.reset(new String(script)); }
	inline const String *GetScript() const { return _pScript.get(); }
	inline static Expr_Value *Reference(const Expr_Value *pExpr) {
		return dynamic_cast<Expr_Value *>(Expr::Reference(pExpr));
	}
	virtual bool IsValue() const;
	virtual Expr *Clone() const;
	virtual Value DoExec(Environment &env, Signal sig, SeqPostHandler *pSeqPostHandler) const;
	virtual Expr *MathDiff(Environment &env, Signal sig, const Symbol *pSymbol) const;
	virtual Expr *MathOptimize(Environment &env, Signal sig) const;
	virtual void Accept(ExprVisitor &visitor) const;
	virtual bool GenerateCode(Environment &env, Signal sig, Stream &stream);
	virtual bool GenerateScript(Signal sig, SimpleStream &stream,
							ScriptStyle scriptStyle, int nestLevel) const;
};

//-----------------------------------------------------------------------------
// Expr_Symbol
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE Expr_Symbol : public Expr {
protected:
	const Symbol *_pSymbol;
	SymbolSet _attrs;
	SymbolSet _attrsOpt;
	SymbolList _attrFront;
public:
	inline Expr_Symbol(const Symbol *pSymbol) : Expr(EXPRTYPE_Symbol), _pSymbol(pSymbol) {}
	inline Expr_Symbol(const Expr_Symbol &expr) : Expr(expr),
							_pSymbol(expr._pSymbol), _attrs(expr._attrs) {}
	inline static Expr_Symbol *Reference(const Expr_Symbol *pExpr) {
		return dynamic_cast<Expr_Symbol *>(Expr::Reference(pExpr));
	}
	virtual bool IsSymbol() const;
	virtual Expr *Clone() const;
	virtual Callable *LookupCallable(Environment &env, Signal sig) const;
	virtual Value DoExec(Environment &env, Signal sig, SeqPostHandler *pSeqPostHandler) const;
	Value Exec(Environment &env, Signal sig, const Value &valueThis, SeqPostHandler *pSeqPostHandler) const;
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
	virtual bool GenerateScript(Signal sig, SimpleStream &stream,
							ScriptStyle scriptStyle, int nestLevel) const;
	bool GenerateScriptHead(Signal sig, SimpleStream &stream,
							ScriptStyle scriptStyle, int nestLevel) const;
	bool GenerateScriptTail(Signal sig, SimpleStream &stream,
							ScriptStyle scriptStyle, int nestLevel) const;
};

//-----------------------------------------------------------------------------
// Expr_String
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE Expr_String : public Expr {
protected:
	String _str;
public:
	inline Expr_String(const String &str) : Expr(EXPRTYPE_String), _str(str) {}
	inline Expr_String(const Expr_String &expr) : Expr(expr), _str(expr._str) {}
	inline const char *GetString() const { return _str.c_str(); }
	inline static Expr_String *Reference(const Expr_String *pExpr) {
		return dynamic_cast<Expr_String *>(Expr::Reference(pExpr));
	}
	virtual bool IsString() const;
	virtual Expr *Clone() const;
	virtual Value DoExec(Environment &env, Signal sig, SeqPostHandler *pSeqPostHandler) const;
	virtual void Accept(ExprVisitor &visitor) const;
	virtual bool GenerateCode(Environment &env, Signal sig, Stream &stream);
	virtual bool GenerateScript(Signal sig, SimpleStream &stream,
							ScriptStyle scriptStyle, int nestLevel) const;
};

//-----------------------------------------------------------------------------
// Expr_TmplString
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE Expr_TmplString : public Expr {
protected:
	SimpleStream &_streamDst;
	String _str;
public:
	inline Expr_TmplString(SimpleStream &streamDst, const String &str) :
				Expr(EXPRTYPE_TmplString), _streamDst(streamDst), _str(str) {}
	inline Expr_TmplString(const Expr_TmplString &expr) :
				Expr(expr), _streamDst(expr._streamDst), _str(expr._str) {}
	inline SimpleStream &GetStreamDst() { return _streamDst;; }
	inline const char *GetString() const { return _str.c_str(); }
	inline static Expr_TmplString *Reference(const Expr_TmplString *pExpr) {
		return dynamic_cast<Expr_TmplString *>(Expr::Reference(pExpr));
	}
	virtual bool IsTmplString() const;
	virtual Expr *Clone() const;
	virtual Value DoExec(Environment &env, Signal sig, SeqPostHandler *pSeqPostHandler) const;
	virtual void Accept(ExprVisitor &visitor) const;
	virtual bool GenerateCode(Environment &env, Signal sig, Stream &stream);
	virtual bool GenerateScript(Signal sig, SimpleStream &stream,
							ScriptStyle scriptStyle, int nestLevel) const;
};

//-----------------------------------------------------------------------------
// Expr_Root
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE Expr_Root : public Expr_Container {
private:
	String _sourceName;
public:
	Expr_Root(const String &sourceName);
	Expr_Root(const Expr_Root &expr);
	inline static Expr_Root *Reference(const Expr_Root *pExpr) {
		return dynamic_cast<Expr_Root *>(Expr::Reference(pExpr));
	}
	virtual bool IsRoot() const;
	virtual Expr *Clone() const;
	virtual const char *GetSourceName() const;
	virtual Value DoExec(Environment &env, Signal sig, SeqPostHandler *pSeqPostHandler) const;
	virtual bool GenerateCode(Environment &env, Signal sig, Stream &stream);
	virtual bool GenerateScript(Signal sig, SimpleStream &stream,
							ScriptStyle scriptStyle, int nestLevel) const;
};

//-----------------------------------------------------------------------------
// Expr_Block
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE Expr_Block : public Expr_Container {
protected:
	AutoPtr<ExprOwner> _pExprOwnerParam;		// this may be NULL
public:
	inline Expr_Block() : Expr_Container(EXPRTYPE_Block) {}
	Expr_Block(const Expr_Block &expr);
	inline static Expr_Block *Reference(const Expr_Block *pExpr) {
		return dynamic_cast<Expr_Block *>(Expr::Reference(pExpr));
	}
	virtual ~Expr_Block();
	virtual bool IsBlock() const;
	virtual Expr *Clone() const;
	virtual Value DoExec(Environment &env, Signal sig, SeqPostHandler *pSeqPostHandler) const;
	virtual Expr *MathDiff(Environment &env, Signal sig, const Symbol *pSymbol) const;
	virtual void Accept(ExprVisitor &visitor) const;
	virtual bool GenerateCode(Environment &env, Signal sig, Stream &stream);
	virtual bool GenerateScript(Signal sig, SimpleStream &stream,
							ScriptStyle scriptStyle, int nestLevel) const;
	inline void SetExprOwnerParam(ExprOwner *pExprOwnerParam) {
		_pExprOwnerParam.reset(pExprOwnerParam);
	}
	inline ExprOwner *GetExprOwnerParam() { return _pExprOwnerParam.get(); }
	inline const ExprOwner *GetExprOwnerParam() const { return _pExprOwnerParam.get(); }
};

//-----------------------------------------------------------------------------
// Expr_Lister
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE Expr_Lister : public Expr_Container {
public:
	class GURA_DLLDECLARE SequenceEx : public Sequence {
	public:
		SequenceEx(Environment *pEnv);
		virtual bool DoStep(Signal sig, Value &result);
		virtual String ToString() const;
	};
public:
	inline Expr_Lister() : Expr_Container(EXPRTYPE_Lister) {}
	inline Expr_Lister(Expr *pExpr) : Expr_Container(EXPRTYPE_Lister) {
		AddExpr(pExpr);
	}
	inline Expr_Lister(const Expr_Lister &expr) : Expr_Container(expr) {}
	inline static Expr_Lister *Reference(const Expr_Lister *pExpr) {
		return dynamic_cast<Expr_Lister *>(Expr::Reference(pExpr));
	}
	virtual bool IsLister() const;
	virtual Expr *Clone() const;
	virtual Value DoExec(Environment &env, Signal sig, SeqPostHandler *pSeqPostHandler) const;
	virtual Value DoAssign(Environment &env, Signal sig, Value &value,
					const SymbolSet *pSymbolsAssignable, bool escalateFlag) const;
	virtual bool GenerateCode(Environment &env, Signal sig, Stream &stream);
	virtual bool GenerateScript(Signal sig, SimpleStream &stream,
							ScriptStyle scriptStyle, int nestLevel) const;
};

//-----------------------------------------------------------------------------
// Expr_Iterer
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE Expr_Iterer : public Expr_Container {
public:
	class GURA_DLLDECLARE SequenceEx : public Sequence {
	public:
		SequenceEx(Environment *pEnv);
		virtual bool DoStep(Signal sig, Value &result);
		virtual String ToString() const;
	};
public:
	inline Expr_Iterer() : Expr_Container(EXPRTYPE_Iterer) {}
	inline Expr_Iterer(Expr *pExpr) : Expr_Container(EXPRTYPE_Iterer) {
		AddExpr(pExpr);
	}
	inline Expr_Iterer(const Expr_Iterer &expr) : Expr_Container(expr) {}
	inline static Expr_Iterer *Reference(const Expr_Iterer *pExpr) {
		return dynamic_cast<Expr_Iterer *>(Expr::Reference(pExpr));
	}
	virtual bool IsIterer() const;
	virtual Expr *Clone() const;
	virtual Value DoExec(Environment &env, Signal sig, SeqPostHandler *pSeqPostHandler) const;
	virtual bool GenerateCode(Environment &env, Signal sig, Stream &stream);
	virtual bool GenerateScript(Signal sig, SimpleStream &stream,
							ScriptStyle scriptStyle, int nestLevel) const;
};

//-----------------------------------------------------------------------------
// Expr_TmplScript
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE Expr_TmplScript : public Expr_Container {
public:
	class GURA_DLLDECLARE SequenceEx : public Sequence {
	public:
		SequenceEx(Environment *pEnv);
		virtual bool DoStep(Signal sig, Value &result);
		virtual String ToString() const;
	};
protected:
	SimpleStream &_streamDst;
	String _strIndent;
	String _strPost;
	bool _autoIndentFlag;
	bool _appendLastEOLFlag;
public:
	inline Expr_TmplScript(SimpleStream &streamDst,
							const String &strIndent, const String &strPost,
							bool autoIndentFlag, bool appendLastEOLFlag) :
			Expr_Container(EXPRTYPE_TmplScript), _streamDst(streamDst),
			_strIndent(strIndent), _strPost(strPost),
			_autoIndentFlag(autoIndentFlag), _appendLastEOLFlag(appendLastEOLFlag) {}
	inline Expr_TmplScript(const Expr_TmplScript &expr) :
			Expr_Container(expr), _streamDst(expr._streamDst),
			_strIndent(expr._strIndent), _strPost(expr._strPost),
			_autoIndentFlag(expr._autoIndentFlag), _appendLastEOLFlag(expr._appendLastEOLFlag) {}
	inline SimpleStream &GetStreamDst() { return _streamDst;; }
	inline void SetStringIndent(const String &strIndent) { _strIndent = strIndent; }
	inline void SetStringPost(const String &strPost) { _strPost = strPost; }
	inline static Expr_TmplScript *Reference(const Expr_TmplScript *pExpr) {
		return dynamic_cast<Expr_TmplScript *>(Expr::Reference(pExpr));
	}
	virtual bool IsTmplScript() const;
	virtual Expr *Clone() const;
	virtual Value DoExec(Environment &env, Signal sig, SeqPostHandler *pSeqPostHandler) const;
	virtual bool GenerateCode(Environment &env, Signal sig, Stream &stream);
	virtual bool GenerateScript(Signal sig, SimpleStream &stream,
							ScriptStyle scriptStyle, int nestLevel) const;
};

//-----------------------------------------------------------------------------
// Expr_Compound
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE Expr_Compound : public Expr {
protected:
	AutoPtr<Expr> _pExprCar;
	AutoPtr<Expr_Lister> _pExprLister;
public:
	Expr_Compound(ExprType exprType, Expr *pExprCar, Expr_Lister *pExprLister);
	Expr_Compound(const Expr_Compound &expr);
	inline static Expr_Compound *Reference(const Expr_Compound *pExpr) {
		return dynamic_cast<Expr_Compound *>(Expr::Reference(pExpr));
	}
	virtual ~Expr_Compound();
	virtual bool IsCompound() const;
	virtual bool IsParentOf(const Expr *pExpr) const;
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
class GURA_DLLDECLARE Expr_Indexer : public Expr_Compound {
public:
	class GURA_DLLDECLARE SequenceEx : public Sequence {
	public:
		SequenceEx(Environment *pEnv);
		virtual bool DoStep(Signal sig, Value &result);
		virtual String ToString() const;
	};
public:
	inline Expr_Indexer(Expr *pExprCar, Expr_Lister *pExprLister) :
			Expr_Compound(EXPRTYPE_Indexer, pExprCar, pExprLister) {}
	inline Expr_Indexer(const Expr_Indexer &expr) : Expr_Compound(expr) {}
	inline static Expr_Indexer *Reference(const Expr_Indexer *pExpr) {
		return dynamic_cast<Expr_Indexer *>(Expr::Reference(pExpr));
	}
	virtual bool IsIndexer() const;
	virtual Expr *Clone() const;
	virtual Value DoExec(Environment &env, Signal sig, SeqPostHandler *pSeqPostHandler) const;
	virtual Value DoAssign(Environment &env, Signal sig, Value &value,
					const SymbolSet *pSymbolsAssignable, bool escalateFlag) const;
	virtual void Accept(ExprVisitor &visitor) const;
	virtual bool GenerateCode(Environment &env, Signal sig, Stream &stream);
	virtual bool GenerateScript(Signal sig, SimpleStream &stream,
							ScriptStyle scriptStyle, int nestLevel) const;
};

//-----------------------------------------------------------------------------
// Expr_Caller
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE Expr_Caller : public Expr_Compound {
public:
	class GURA_DLLDECLARE SequenceEx : public Sequence {
	public:
		SequenceEx(Environment *pEnv);
		virtual bool DoStep(Signal sig, Value &result);
		virtual String ToString() const;
	};
protected:
	AutoPtr<Expr_Block> _pExprBlock;		// this may be NULL
	AutoPtr<Expr_Caller> _pExprTrailer;		// this may be NULL
	SymbolSet _attrs;
	SymbolSet _attrsOpt;
	SymbolList _attrFront;
public:
	Expr_Caller(Expr *pExprCar, Expr_Lister *pExprLister, Expr_Block *pExprBlock);
	Expr_Caller(const Expr_Caller &expr);
	inline static Expr_Caller *Reference(const Expr_Caller *pExpr) {
		return dynamic_cast<Expr_Caller *>(Expr::Reference(pExpr));
	}
	virtual ~Expr_Caller();
	virtual bool IsCaller() const;
	virtual Expr *Clone() const;
	virtual Callable *LookupCallable(Environment &env, Signal sig) const;
	virtual Value DoExec(Environment &env, Signal sig, SeqPostHandler *pSeqPostHandler) const;
	virtual Value DoAssign(Environment &env, Signal sig, Value &value,
					const SymbolSet *pSymbolsAssignable, bool escalateFlag) const;
	virtual void Accept(ExprVisitor &visitor) const;
	virtual bool IsParentOf(const Expr *pExpr) const;
	virtual Expr *MathDiff(Environment &env, Signal sig, const Symbol *pSymbol) const;
	virtual Expr *MathOptimize(Environment &env, Signal sig) const;
	virtual bool GenerateCode(Environment &env, Signal sig, Stream &stream);
	virtual bool GenerateScript(Signal sig, SimpleStream &stream,
							ScriptStyle scriptStyle, int nestLevel) const;
	Value EvalEach(Environment &env, Signal sig, const Value &valueThis,
		Iterator *pIteratorThis, bool listThisFlag, TrailCtrlHolder *pTrailCtrlHolder) const;
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
	Value DoExec(Environment &env, Signal sig, TrailCtrlHolder *pTrailCtrlHolder) const;
};

//-----------------------------------------------------------------------------
// Expr_UnaryOp
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE Expr_UnaryOp : public Expr_Unary {
public:
	class GURA_DLLDECLARE SequenceEx : public Sequence {
	public:
		SequenceEx(Environment *pEnv);
		virtual bool DoStep(Signal sig, Value &result);
		virtual String ToString() const;
	};
protected:
	const Operator *_pOperator;
	bool _suffixFlag;
public:
	inline Expr_UnaryOp(const Operator *pOperator, Expr *pExprChild, bool suffixFlag) :
					Expr_Unary(EXPRTYPE_UnaryOp, pExprChild),
					_pOperator(pOperator), _suffixFlag(suffixFlag) {}
	inline Expr_UnaryOp(const Expr_UnaryOp &expr) :
					Expr_Unary(expr),
					_pOperator(expr._pOperator), _suffixFlag(expr._suffixFlag) {}
	inline const Operator *GetOperator() const { return _pOperator; }
	inline static Expr_UnaryOp *Reference(const Expr_UnaryOp *pExpr) {
		return dynamic_cast<Expr_UnaryOp *>(Expr::Reference(pExpr));
	}
	virtual Expr *Clone() const;
	virtual Value DoExec(Environment &env, Signal sig, SeqPostHandler *pSeqPostHandler) const;
	virtual Expr *MathDiff(Environment &env, Signal sig, const Symbol *pSymbol) const;
	virtual Expr *MathOptimize(Environment &env, Signal sig) const;
	virtual bool IsUnaryOp() const;
	virtual bool IsUnaryOpSuffix() const;
	virtual bool GenerateCode(Environment &env, Signal sig, Stream &stream);
	virtual bool GenerateScript(Signal sig, SimpleStream &stream,
							ScriptStyle scriptStyle, int nestLevel) const;
	inline static bool IsSuffixed(const Expr *pExpr, const Symbol *pSymbol) {
		return pExpr->IsUnaryOpSuffix() && dynamic_cast<const Expr_UnaryOp *>(pExpr)->
								GetOperator()->GetSymbol()->IsIdentical(pSymbol);
	}
};

//-----------------------------------------------------------------------------
// Expr_BinaryOp
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE Expr_BinaryOp : public Expr_Binary {
public:
	class GURA_DLLDECLARE SequenceEx : public Sequence {
	public:
		SequenceEx(Environment *pEnv);
		virtual bool DoStep(Signal sig, Value &result);
		virtual String ToString() const;
	};
protected:
	const Operator *_pOperator;
public:
	inline Expr_BinaryOp(const Operator *pOperator, Expr *pExprLeft, Expr *pExprRight) :
					Expr_Binary(EXPRTYPE_BinaryOp, pExprLeft, pExprRight), _pOperator(pOperator) {}
	inline Expr_BinaryOp(const Expr_BinaryOp &expr) :
					Expr_Binary(expr), _pOperator(expr._pOperator) {}
	inline const Operator *GetOperator() const { return _pOperator; }
	inline static Expr_BinaryOp *Reference(const Expr_BinaryOp *pExpr) {
		return dynamic_cast<Expr_BinaryOp *>(Expr::Reference(pExpr));
	}
	virtual Expr *Clone() const;
	virtual Value DoExec(Environment &env, Signal sig, SeqPostHandler *pSeqPostHandler) const;
	virtual Expr *MathDiff(Environment &env, Signal sig, const Symbol *pSymbol) const;
	virtual Expr *MathOptimize(Environment &env, Signal sig) const;
	virtual bool IsBinaryOp() const;
	virtual bool GenerateCode(Environment &env, Signal sig, Stream &stream);
	virtual bool GenerateScript(Signal sig, SimpleStream &stream,
							ScriptStyle scriptStyle, int nestLevel) const;
};

//-----------------------------------------------------------------------------
// Expr_Quote
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE Expr_Quote : public Expr_Unary {
public:
	class GURA_DLLDECLARE SequenceEx : public Sequence {
	public:
		SequenceEx(Environment *pEnv);
		virtual bool DoStep(Signal sig, Value &result);
		virtual String ToString() const;
	};
public:
	inline Expr_Quote(Expr *pExprChild) : Expr_Unary(EXPRTYPE_Quote, pExprChild) {}
	inline Expr_Quote(const Expr_Quote &expr) : Expr_Unary(expr) {}
	inline static Expr_Quote *Reference(const Expr_Quote *pExpr) {
		return dynamic_cast<Expr_Quote *>(Expr::Reference(pExpr));
	}
	virtual Expr *Clone() const;
	virtual Value DoExec(Environment &env, Signal sig, SeqPostHandler *pSeqPostHandler) const;
	virtual const Expr *Unquote() const;
	virtual bool IsQuote() const;
	virtual bool GenerateCode(Environment &env, Signal sig, Stream &stream);
	virtual bool GenerateScript(Signal sig, SimpleStream &stream,
							ScriptStyle scriptStyle, int nestLevel) const;
};

//-----------------------------------------------------------------------------
// Expr_Assign
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE Expr_Assign : public Expr_Binary {
public:
	class GURA_DLLDECLARE SequenceEx : public Sequence {
	public:
		SequenceEx(Environment *pEnv);
		virtual bool DoStep(Signal sig, Value &result);
		virtual String ToString() const;
	};
private:
	const Operator *_pOperatorToApply;	// this may be NULL
public:
	inline Expr_Assign(Expr *pExprLeft, Expr *pExprRight, const Operator *pOperatorToApply) :
				Expr_Binary(EXPRTYPE_Assign, pExprLeft, pExprRight), _pOperatorToApply(pOperatorToApply) {}
	inline Expr_Assign(const Expr_Assign &expr) :
				Expr_Binary(expr), _pOperatorToApply(expr._pOperatorToApply) {}
	inline static Expr_Assign *Reference(const Expr_Assign *pExpr) {
		return dynamic_cast<Expr_Assign *>(Expr::Reference(pExpr));
	}
	inline const Operator *GetOperatorToApply() const { return _pOperatorToApply; }
	virtual Value DoExec(Environment &env, Signal sig, SeqPostHandler *pSeqPostHandler) const;
	Value Exec(Environment &env, Signal sig, Environment &envDst,
		const SymbolSet *pSymbolsAssignable, SeqPostHandler *pSeqPostHandler) const;
	virtual Expr *Clone() const;
	virtual bool IsAssign() const;
	virtual bool GenerateCode(Environment &env, Signal sig, Stream &stream);
	virtual bool GenerateScript(Signal sig, SimpleStream &stream,
							ScriptStyle scriptStyle, int nestLevel) const;
};

//-----------------------------------------------------------------------------
// Expr_Member
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE Expr_Member : public Expr_Binary {
public:
	class GURA_DLLDECLARE SequenceEx : public Sequence {
	public:
		SequenceEx(Environment *pEnv);
		virtual bool DoStep(Signal sig, Value &result);
		virtual String ToString() const;
	};
public:
	enum Mode {
		MODE_Normal,		// foo.bar
		MODE_MapToList,		// foo::bar .. map-to-list
		MODE_MapToIter,		// foo:*bar .. map-to-iterator
		MODE_MapAlong,		// foo:&bar .. map-along
	};
private:
	Mode _mode;
public:
	inline Expr_Member(Expr *pExprLeft, Expr *pExprRight, Mode mode = MODE_Normal) :
				Expr_Binary(EXPRTYPE_Member, pExprLeft, pExprRight), _mode(mode) {}
	inline Expr_Member(const Expr_Member &expr) : Expr_Binary(expr), _mode(expr._mode) {}
	inline Mode GetMode() const { return _mode; }
	inline static Expr_Member *Reference(const Expr_Member *pExpr) {
		return dynamic_cast<Expr_Member *>(Expr::Reference(pExpr));
	}
	virtual Expr *Clone() const;
	virtual Value DoExec(Environment &env, Signal sig, SeqPostHandler *pSeqPostHandler) const;
	virtual Value DoAssign(Environment &env, Signal sig, Value &value,
					const SymbolSet *pSymbolsAssignable, bool escalateFlag) const;
	virtual bool IsMember() const;
	virtual bool GenerateCode(Environment &env, Signal sig, Stream &stream);
	virtual bool GenerateScript(Signal sig, SimpleStream &stream,
							ScriptStyle scriptStyle, int nestLevel) const;
};

}

#endif
