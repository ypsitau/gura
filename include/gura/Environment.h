//=============================================================================
// Environment
//=============================================================================
#ifndef __GURA_ENVIRONMENT_H__
#define __GURA_ENVIRONMENT_H__

#include "Value.h"
#include "String.h"
#include "Operator.h"
#include "Help.h"
#include "Option.h"
#include "SuffixMgr.h"
#include "PathMgr.h"
#include "Callable.h"

//-----------------------------------------------------------------------------
// macros
//-----------------------------------------------------------------------------
#define Gura_AssignFunction(name) \
env.AssignFunction(new Func_##name(env))

#define Gura_AssignFunctionEx(name, arg1) \
env.AssignFunction(new Func_##name(env, arg1))

#define Gura_AssignFunctionExx(name, arg1, arg2) \
env.AssignFunction(new Func_##name(env, arg1, arg2))

#define Gura_AssignMethod(className, name) \
AssignFunction(new Func_##className##__##name(*this))

#define Gura_AssignClassMethod(className, name) \
AssignFunction(new Func_##className##__##name(*this))

#define Gura_AssignMethodTo(valType, className, name) \
do { \
	Class *pClass = env.LookupClass(valType); \
	pClass->AssignFunction(new Func_##className##__##name(*pClass)); \
} while (0)

#define Gura_AssignMethodEx(className, name, arg1) \
AssignFunction(new Func_##className##__##name(*this, arg1))

#define Gura_AssignMethodExx(className, name, arg1, arg2) \
AssignFunction(new Func_##className##__##name(*this, arg1, arg2))

#define Gura_AssignValue(name, value) \
env.AssignValue(Symbol::Add(#name), value, EXTRA_Public)

#define Gura_AssignValueEx(name, value) \
env.AssignValue(Symbol::Add(name), value, EXTRA_Public)

#define Gura_AssignClassValue(name, value) \
AssignValue(Symbol::Add(#name), value, EXTRA_Public)

#define Gura_AssignClassValueEx(name, value) \
AssignValue(Symbol::Add(name), value, EXTRA_Public)

#define Gura_AssignValueTo(valType, name, value) \
do { \
	Class *pClass = env.LookupClass(valType); \
	pClass->AssignValue(Symbol::Add(#name), value, EXTRA_Public); \
} while (0)


namespace Gura {

class Class;
class Class_function;
class Class_string;
class Class_binary;
class Class_BinaryPtr;
class Class_list;
class Class_dict;
class Class_datetime;
class Class_iterator;
class Class_expr;
class Class_environment;
class Class_error;
class Class_semaphore;
class Class_Struct;

class Module;
class Monitor;
class InteractiveHandler;

class FunctionCustom;

//-----------------------------------------------------------------------------
// EnvType
//-----------------------------------------------------------------------------
enum EnvType {
	ENVTYPE_invalid,
	ENVTYPE_root,
	ENVTYPE_local,
	ENVTYPE_block,
	ENVTYPE_class,
	ENVTYPE_object,
	ENVTYPE_lister,
};

//-----------------------------------------------------------------------------
// EnvRefMode
//-----------------------------------------------------------------------------
enum EnvRefMode {
	ENVREF_NoEscalate,
	ENVREF_Module,
	ENVREF_Escalate,
	ENVREF_Restricted,
};

GURA_DLLDECLARE const char *GetEnvTypeName(EnvType envType);

//-----------------------------------------------------------------------------
// ModuleMap
//-----------------------------------------------------------------------------
typedef std::map<String, Module *> ModuleMap;

//-----------------------------------------------------------------------------
// Environment
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE Environment : public Callable {
public:
	class GURA_DLLDECLARE Global {
	private:
		Option				_opt;
		ModuleMap 			_moduleMapIntegrated;
		ModuleMap			_moduleMapSeparated;
		StringList			_workingDirList;
		SuffixMgr			_suffixMgrForString;
		SuffixMgr			_suffixMgrForNumber;
		PathMgrOwner		_pathMgrOwner;
		HelpRendererOwner	_helpRendererOwner;
		Operator			*_operatorTbl[OPTYPE_max];
		SymbolPool			*_pSymbolPool;
		ValueTypePool		*_pValueTypePool;
		bool				_echoFlag;
		Module				*_pModule_sys;
		AutoPtr<Stream>		_pConsoleDumb;
		AutoPtr<Monitor>	_pMonitor;
		AutoPtr<InteractiveHandler> _pInteractiveHandler;
	public:
		Global();
		~Global();
		inline static void Delete(Global *pGlobal) {
			delete pGlobal;
		}
		void Prepare(Environment &env);
		Class *LookupClass(ValueType valType) const;
		Module *LookupIntegratedModule(const char *name) const;
		void RegisterIntegratedModule(Module *pModule);
		Module *LookupSeparatedModule(const char *pathName) const;
		void RegisterSeparatedModule(const char *pathName, Module *pModule);
		void UnregisterSeparatedModule(const char *pathName);
		inline Option &GetOption() { return _opt; }
		inline SuffixMgr &GetSuffixMgrForString() { return _suffixMgrForString; }
		inline const SuffixMgr &GetSuffixMgrForString() const { return _suffixMgrForString; }
		inline SuffixMgr &GetSuffixMgrForNumber() { return _suffixMgrForNumber; }
		inline const SuffixMgr &GetSuffixMgrForNumber() const { return _suffixMgrForNumber; }
		inline PathMgrOwner &GetPathMgrOwner() { return _pathMgrOwner; }
		inline const PathMgrOwner &GetPathMgrOwner() const { return _pathMgrOwner; }
		inline HelpRendererOwner &GetHelpRendererOwner() { return _helpRendererOwner; }
		inline const HelpRendererOwner &GetHelpRendererOwner() const { return _helpRendererOwner; }
		inline void SetOperator(OpType opType, Operator *pOperator) { _operatorTbl[opType] = pOperator; }
		inline Operator *GetOperator(OpType opType) { return _operatorTbl[opType]; }
		inline const Operator *GetOperator(OpType opType) const { return _operatorTbl[opType]; }
		inline Stream *GetConsoleDumb() { return _pConsoleDumb.get(); }
		inline void SetModule_sys(Module *pModule) { _pModule_sys = pModule; }
		inline Module *GetModule_sys() { return _pModule_sys; }
		inline void SetEchoFlag(bool echoFlag) { _echoFlag = echoFlag; }
		inline bool GetEchoFlag() const { return _echoFlag; }
		inline void SetMonitor(Monitor *pMonitor) { _pMonitor.reset(pMonitor); }
		inline Monitor *GetMonitor() { return _pMonitor.get(); }
		inline void SetInteractiveHandler(InteractiveHandler *pInteractiveHandler) {
			_pInteractiveHandler.reset(pInteractiveHandler);
		}
		inline InteractiveHandler *GetInteractiveHandler() { return _pInteractiveHandler.get(); }
	};
	class GURA_DLLDECLARE Frame {
	private:
		int _cntRef;
		EnvType _envType;
		Global *_pGlobal;
		AutoPtr<ValueExMap> _pValueExMap;
		std::unique_ptr<ValueTypeMap> _pValueTypeMap;
		std::unique_ptr<SymbolSet> _pSymbolsPublic;
		Argument *_pArgWeak;
		ValueEx _valueEx_arg;
		ValueEx _valueEx_this;
	public:
		inline static void *operator new(size_t size) {
			return MemoryPool::Allocate(size, "Frame");
		}
		inline static void operator delete(void *pv) {
			MemoryPool::Deallocate(pv);
		}
	public:
		Frame(const Frame &frame);
		Frame(EnvType envType, Global *pGlobal);
		virtual ~Frame();
		inline static Frame *Reference(const Frame *pFrame) {
			if (pFrame == nullptr) return nullptr;
			Frame *pFrameCasted = const_cast<Frame *>(pFrame);
			pFrameCasted->_cntRef++;
			return pFrameCasted;
		}
		inline int DecRef() { if (_cntRef > 0) _cntRef--; return _cntRef; }
		inline int GetCntRef() const { return _cntRef; }
		static void Delete(Frame *pFrame);
		inline Frame *Clone() const { return new Frame(*this); }
		inline EnvType GetEnvType() const { return _envType; }
		inline const char *GetTypeName() const { return GetEnvTypeName(_envType); }
		inline bool IsType(EnvType envType) const { return _envType == envType; }
		inline Global *GetGlobal() { return _pGlobal; }
		inline Global *GetGlobal() const { return _pGlobal; }
		inline const ValueExMap &GetValueExMap() const {
			return _pValueExMap.IsNull()? ValueExMap::Empty : *_pValueExMap;
		}
		inline const ValueTypeMap &GetValueTypeMap() const {
			return (_pValueTypeMap.get() == nullptr)? ValueTypeMap::Empty : *_pValueTypeMap;
		}
		inline const SymbolSet &GetSymbolsPublic() const {
			return (_pSymbolsPublic.get() == nullptr)? SymbolSet::Empty : *_pSymbolsPublic;
		}
		inline bool IsSymbolPublic(const Symbol *pSymbol) const {
			return _pSymbolsPublic.get() != nullptr && _pSymbolsPublic->IsSet(pSymbol);
		}
		inline void SetAssocArgument(Argument *pArg) { _pArgWeak = pArg; }
		inline Argument *GetArgument() { return _pArgWeak; }
		inline void InvalidateValueThis() {
			_valueEx_this = ValueEx(VTYPE_undefined, VFLAG_None, EXTRA_None);
		}
		void AssignValue(const Symbol *pSymbol, const Value &value, ULong extra);
		ValueEx *LookupValue(Environment &env, const Symbol *pSymbol);
		void RemoveValue(const Symbol *pSymbol);
		void AssignValueType(ValueTypeInfo *pValueTypeInfo);
		ValueTypeInfo *LookupValueType(const Symbol *pSymbol);
		SymbolSet &PrepareSymbolsPublic();
		void DbgPrint() const;
	};
	class GURA_DLLDECLARE FrameList : public std::vector<Frame *, Allocator<Frame *> > {
	public:
		inline bool DoesExist(Frame *pFrame) const {
			return std::find(begin(), end(), pFrame) != end();
		}
		void DbgPrint() const;
	};
	class GURA_DLLDECLARE FrameOwner : public FrameList {
	public:
		~FrameOwner();
		void Clear();
	};
	class GURA_DLLDECLARE FrameCache :
		public std::unordered_map<const Symbol *, Frame *, Symbol::Hasher, Symbol::EqualTo> {
	protected:
		int _cntRef;
	public:
		Gura_DeclareReferenceAccessor(FrameCache)
	public:
		FrameCache();
	protected:
		virtual ~FrameCache();
	};
protected:
	Signal &_sig;	// this must be placed at top.
	FrameOwner _frameOwner;
	AutoPtr<FrameCache> _pFrameCache;
public:
	Gura_DeclareReferenceAccessor(Environment)
public:
	inline static void *operator new(size_t size) {
		return MemoryPool::Allocate(size, "Environment");
	}
	inline static void operator delete(void *pv) {
		MemoryPool::Deallocate(pv);
	}
public:
	Environment(Signal &sig);
protected:
	Environment(const Environment &env);
	Environment(const Environment &envOuter, EnvType envType);
public:
	inline Environment *Clone() const			{ return new Environment(*this);			}
	inline Environment *Derive(EnvType envType)	const
												{ return new Environment(*this, envType);	}
	inline Signal &GetSignal() const { return _sig; }
	bool InitializeAsRoot(int &argc, const char *argv[],
						  const Option::Info *optInfoTbl, int cntOptInfo);
	inline FrameOwner &GetFrameOwner()			{ return _frameOwner;						}
	inline const FrameOwner &GetFrameOwner() const
												{ return _frameOwner;						}
	inline FrameCache *GetFrameCache()			{ return _pFrameCache.get();				}
	inline const FrameCache *GetFrameCache() const
												{ return _pFrameCache.get();				}
	inline Frame *GetTopFrame()					{ return _frameOwner.front();				}
	inline const Frame *GetTopFrame() const		{ return _frameOwner.front();				}
	inline Frame *GetBottomFrame()				{ return _frameOwner.back();				}
	inline const Frame *GetBottomFrame() const	{ return _frameOwner.back();				}
	inline EnvType GetEnvType() const			{ return GetTopFrame()->GetEnvType();		}
	inline const char *GetTypeName() const		{ return GetTopFrame()->GetTypeName();		}
	inline bool IsType(EnvType envType) const	{ return GetTopFrame()->IsType(envType);	}
	inline Global *GetGlobal()					{ return GetTopFrame()->GetGlobal();		}
	inline Global *GetGlobal() const			{ return GetTopFrame()->GetGlobal();		}
	inline void SetAssocArgument(Argument *pArg){ GetTopFrame()->SetAssocArgument(pArg);	}
	inline Argument *GetArgument()				{ return GetTopFrame()->GetArgument();		}
	inline void InvalidateValueThis()			{ GetTopFrame()->InvalidateValueThis();		}
	inline Option &GetOption()					{ return GetGlobal()->GetOption();			}
	inline Operator *GetOperator(OpType opType) { return GetGlobal()->GetOperator(opType);	}
	inline const Operator *GetOperator(OpType opType) const
												{ return GetGlobal()->GetOperator(opType);	}
	inline void SetOperator(OpType opType, Operator *pOperator)
												{ GetGlobal()->SetOperator(opType, pOperator); }
	inline Class *LookupClass(ValueType valType) const
												{ return GetGlobal()->LookupClass(valType);	}
	inline void SetMonitor(Monitor *pMonitor)	{ GetGlobal()->SetMonitor(pMonitor);		}
	inline Monitor *GetMonitor()				{ return GetGlobal()->GetMonitor();			}
	inline void SetInteractiveHandler(InteractiveHandler *pInteractiveHandler)	{
		GetGlobal()->SetInteractiveHandler(pInteractiveHandler);
	}
	inline InteractiveHandler *GetInteractiveHandler() {
		return GetGlobal()->GetInteractiveHandler();
	}
	inline operator Signal&() { return _sig; }
	Value ExecInteractiveHandler();
public:
	const SymbolSet &GetSymbolsPublic() const;
	SymbolSet &PrepareSymbolsPublic();
	bool IsSymbolPublic(const Symbol *pSymbol) const;
public:
	void AddRootFrame(const FrameList &frameListSrc);
	void AddOuterFrame(const FrameList &frameListSrc);
	void AddLackingFrame(const FrameList &frameListSrc);
	void CacheFrame(const Symbol *pSymbol, Frame *pFrame);
public:
	void AssignValue(const Symbol *pSymbol, const Value &value, ULong extra);
	Function *AssignFunction(Function *pFunc, ULong extra = EXTRA_Public);
	void AssignValueFromBlock(const Symbol *pSymbol, const Value &value, ULong extra);
	bool ImportValue(const Symbol *pSymbol, const Value &value,
										ULong extra, bool overwriteFlag);
public:
	ValueEx *LookupValue(const Symbol *pSymbol, EnvType envType,
						 EnvRefMode envRefMode, int cntSuperSkip = 0);
	inline ValueEx *LookupValue(const Symbol *pSymbol,
								EnvRefMode envRefMode, int cntSuperSkip = 0) {
		return LookupValue(pSymbol, GetEnvType(), envRefMode, cntSuperSkip);
	}
	inline const ValueEx *LookupValue(const Symbol *pSymbol,
									  EnvRefMode envRefMode, int cntSuperSkip = 0) const {
		return const_cast<const ValueEx *>(
			const_cast<Environment *>(this)->
			LookupValue(pSymbol, GetEnvType(), envRefMode, cntSuperSkip));
	}
	Function *LookupFunction(const Symbol *pSymbol, EnvRefMode envRefMode, int cntSuperSkip = 0) const;
public:
	void RemoveValue(const Symbol *pSymbol);
protected:
	virtual Value DoGetProp(Environment &env, const Symbol *pSymbol,
						const SymbolSet &attrs, bool &evaluatedFlag);
	virtual Value DoSetProp(Environment &env, const Symbol *pSymbol, const Value &value,
						const SymbolSet &attrs, bool &evaluatedFlag);
public:
	virtual Callable *GetCallable(const Symbol *pSymbol);
	Value GetProp(const Symbol *pSymbol, const SymbolSet &attrs,
				  const Value *pValueDefault = nullptr, EnvRefMode envRefMode = ENVREF_Escalate,
				  int cntSuperSkip = 0);
	Value SetProp(const Symbol *pSymbol, const SymbolSet &attrs, const SymbolList &attrFront,
				  Value &valueAssigned, bool escalateFlag);
public:
	virtual void AssignValueType(ValueTypeInfo *pValueTypeInfo);
	ValueTypeInfo *LookupValueType(const SymbolList &symbolList);
	ValueTypeInfo *LookupValueType(const Symbol *pSymbol);
	ValueTypeInfo *LookupValueType(const ValueList &valList);
	ValueTypeInfo *LookupValueType(const Expr *pExpr);
public:
	void AssignIntegratedModule(Module *pModule);
	bool ImportModules(const char *moduleNames, bool binaryOnlyFlag, bool mixinTypeFlag);
	Module *ImportModule(
		const Expr *pExpr, const Symbol *pSymbolAlias, const SymbolSet *pSymbolsToMixIn,
		bool overwriteFlag, bool binaryOnlyFlag, bool mixinTypeFlag);
	Module *ImportModule(
		SymbolList::const_iterator ppSymbolOfModule,
		SymbolList::const_iterator ppSymbolOfModuleEnd, bool assignModuleNameFlag,
		const Symbol *pSymbolAlias, const SymbolSet *pSymbolsToMixIn,
		bool overwriteFlag, bool binaryOnlyFlag, bool mixinTypeFlag);
public:
	static bool IsBinaryModule(const char *pathName);
	virtual bool IsModule() const;
	virtual bool IsClass() const;
	virtual bool IsObject() const;
	inline void Error(const char *fileName, int lineNo, const char *str) {
		::fprintf(stderr, "fatal error at line.%d in %s: %s\n", lineNo, fileName, str);
	}
	const char *GetPrompt(bool indentFlag);
	void SetConsole(Stream *pConsole);
	void SetConsoleErr(Stream *pConsole);
	const Symbol *GetLangCode();
	Stream *GetConsole();
	Stream *GetConsoleErr();
	Stream *GetConsoleDumb();
	inline bool IsSignalled() const { return GetSignal().IsSignalled(); }
	inline bool IsNoSignalled() const { return GetSignal().IsNoSignalled(); }
	inline void ClearSignal() { GetSignal().ClearSignal(); }
	inline void SetSignal(ULong sigType, const Value &value) { GetSignal().SetSignal(sigType, value); }
	void SetError(ErrorType errType, const char *format, ...) const;
	inline void SetErrorV(ErrorType errType,
						  const char *format, va_list ap, const char *textPre = "") const {
		GetSignal().SetErrorV(errType, format, ap, textPre);
	}
	void SetError_AccessViolation(const Symbol *pSymbol) const;
	void SetError_PropertyNotFound(const Symbol *pSymbol) const;
public:
	bool SearchSeparatedModuleFile(
		String &pathName, SymbolList::const_iterator ppSymbolOfModule,
		SymbolList::const_iterator ppSymbolOfModuleEnd, bool binaryOnlyFlag);
	Module *ImportSeparatedModule_Script(Environment *pEnvOuter,
							const char *pathName, const Symbol *pSymbol);
	Module *ImportSeparatedModule_Binary(Environment *pEnvOuter,
							const char *pathName, const Symbol *pSymbol);
};

typedef std::set<Environment *> EnvironmentSet;

}
#endif
