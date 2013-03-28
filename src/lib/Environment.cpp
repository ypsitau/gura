#include "stdafx.h"

#if defined(HAVE_LIBDL)
#include <dlfcn.h>
#endif

Gura_IncludeModule(basement)
Gura_IncludeModuleBegin(sys)
bool SetupValues(Module *pModule, Signal sig, int argc, const char *argv[]);
Gura_IncludeModuleEnd()
Gura_IncludeModule(codecs_basic)
Gura_IncludeModule(codecs_iso8859)
Gura_IncludeModule(codecs_japanese)
Gura_IncludeModule(base64)
Gura_IncludeModule(fs)
Gura_IncludeModule(os)
Gura_IncludeModule(path)
Gura_IncludeModule(time)
Gura_IncludeModule(math)
Gura_IncludeModule(conio)

namespace Gura {

//-----------------------------------------------------------------------------
// EnvType
//-----------------------------------------------------------------------------
const char *GetEnvTypeName(EnvType envType)
{
	static const struct {
		EnvType envType;
		const char *name;
	} tbl[] = {
		{ ENVTYPE_invalid,			"invalid",			},
		{ ENVTYPE_root,				"root",				},
		{ ENVTYPE_local,			"local",			},
		{ ENVTYPE_block,			"block",			},
		{ ENVTYPE_class,			"class",			},
		{ ENVTYPE_object,			"object",			},
		{ ENVTYPE_method,			"method",			},
		{ ENVTYPE_lister,			"lister",			},
	};
	for (int i = 0; i < ArraySizeOf(tbl); i++) {
		if (tbl[i].envType == envType) return tbl[i].name;
	}
	return "unknown";
}

//-----------------------------------------------------------------------------
// IntegratedModule
//-----------------------------------------------------------------------------
bool IntegratedModule::IsMatch(const SymbolList &symbolOfModule) const
{
	return symbolOfModule.size() == 1 &&
			::strcmp(symbolOfModule.back()->GetName(), _name.c_str()) == 0;
}

//-----------------------------------------------------------------------------
// IntegratedModuleOwner
//-----------------------------------------------------------------------------
IntegratedModuleOwner::~IntegratedModuleOwner()
{
	foreach (IntegratedModuleOwner, ppIntegratedModule, *this) {
		delete *ppIntegratedModule;
	}
}


//-----------------------------------------------------------------------------
// ModuleIntegrator
//-----------------------------------------------------------------------------
ModuleIntegrator::ModuleIntegrator(const char *name,
			ModuleEntryType moduleEntry, ModuleTerminateType moduleTerminate)
{
	Environment::IntegrateModule(name, moduleEntry, moduleTerminate);
}

//-----------------------------------------------------------------------------
// Environment
//-----------------------------------------------------------------------------
IntegratedModuleOwner *Environment::_pIntegratedModuleOwner = NULL;

Environment::Environment()
{
}

Environment::Environment(const Environment &env)
{
	// _pFrameCache will be initialized when the program reads some variable at first
	foreach_const (FrameOwner, ppFrame, env.GetFrameOwner()) {
		Frame *pFrame = *ppFrame;
		_frameOwner.push_back(Frame::Reference(pFrame));
	}
}

Environment::Environment(const Environment *pEnvOuter, EnvType envType)
{
	// _pFrameCache will be initialized when the program reads some variable at first
	_frameOwner.push_back(new Frame(envType, pEnvOuter->GetGlobal()));
	foreach_const (FrameOwner, ppFrame, pEnvOuter->GetFrameOwner()) {
		Frame *pFrame = *ppFrame;
		_frameOwner.push_back(Frame::Reference(pFrame));
	}
}

Environment::~Environment()
{
	// virtual destructor
}

void Environment::AddRootFrame(const FrameList &frameListSrc)
{
	// reference to the root environment
	foreach_const (FrameList, ppFrame, frameListSrc) {
		Frame *pFrame = *ppFrame;
		if (pFrame->GetEnvType() == ENVTYPE_root) {
			_frameOwner.push_back(Frame::Reference(pFrame));
			break;
		}
	}
}

void Environment::AddOuterFrame(const FrameList &frameListSrc)
{
	if (frameListSrc.size() <= 1) return;
	FrameList::const_iterator ppFrame = frameListSrc.begin();
	ppFrame++;
	for ( ; ppFrame != frameListSrc.end(); ppFrame++) {
		Frame *pFrame = *ppFrame;
		_frameOwner.push_back(Frame::Reference(pFrame));
	}
}

void Environment::AddLackingFrame(const FrameList &frameListSrc)
{
	foreach_const (FrameList, ppFrame, frameListSrc) {
		Frame *pFrame = *ppFrame;
		if (!_frameOwner.IsExist(pFrame)) {
			_frameOwner.push_back(Frame::Reference(pFrame));
		}
	}
}

void Environment::CacheFrame(const Symbol *pSymbol, Frame *pFrame)
{
	if (_pFrameCache.get() == NULL) _pFrameCache.reset(new FrameCache());
	(*_pFrameCache)[pSymbol] = pFrame;
}

void Environment::AssignValue(const Symbol *pSymbol, const Value &value, bool escalateFlag)
{
	unsigned long extra = EXTRA_Public;
	if (escalateFlag) {
		if (_pFrameCache.get() != NULL) {
			FrameCache::iterator iter = _pFrameCache->find(pSymbol);
			if (iter != _pFrameCache->end()) {
				Frame *pFrame = iter->second;
				pFrame->AssignValue(pSymbol, value, extra);
				return;
			}
		}
		foreach (FrameOwner, ppFrame, _frameOwner) {
			Frame *pFrame = *ppFrame;
			if (!pFrame->IsType(ENVTYPE_block)) {
				pFrame->AssignValue(pSymbol, value, extra);
				break;
			}
		}
	} else {
		GetTopFrame()->AssignValue(pSymbol, value, extra);
		CacheFrame(pSymbol, GetTopFrame());
	}
}

bool Environment::ImportValue(const Symbol *pSymbol, const Value &value, bool overwriteFlag)
{
	unsigned long extra = EXTRA_Public;
	foreach (FrameOwner, ppFrame, _frameOwner) {
		Frame *pFrame = *ppFrame;
		if (pFrame->IsType(ENVTYPE_block)) {
			// nothing to do
		} else if (overwriteFlag || pFrame->LookupValue(pSymbol) == NULL) {
			pFrame->AssignValue(pSymbol, value, extra);
			break;
		} else {
			return false;
		}
	}
	return true;
}

void Environment::RemoveValue(const Symbol *pSymbol)
{
	GetTopFrame()->RemoveValue(pSymbol);
}

ValueEx *Environment::LookupValue(const Symbol *pSymbol, EnvRefMode envRefMode, int cntSuperSkip)
{
	EnvType envType = GetTopFrame()->GetEnvType();
	if (envRefMode == ENVREF_NoEscalate) {
		Frame *pFrame = GetTopFrame();
		ValueEx *pValue = pFrame->LookupValue(pSymbol);
		if (pValue != NULL) {
			CacheFrame(pSymbol, pFrame);
			return pValue;
		}
	} else if (envType == ENVTYPE_method) {
		foreach (FrameOwner, ppFrame, _frameOwner) {
			Frame *pFrame = *ppFrame;
			if (pFrame->IsType(ENVTYPE_object)) continue;
			//if (pFrame->IsType(ENVTYPE_class)) continue;
			ValueEx *pValue = pFrame->LookupValue(pSymbol);
			if (pValue != NULL) {
				CacheFrame(pSymbol, pFrame);
				return pValue;
			}
		}
	} else if (envType == ENVTYPE_object || envType == ENVTYPE_class) {
		foreach (FrameOwner, ppFrame, _frameOwner) {
			Frame *pFrame = *ppFrame;
			if (pFrame->IsType(ENVTYPE_object)) {
				ValueEx *pValue = pFrame->LookupValue(pSymbol);
				if (pValue != NULL) {
					CacheFrame(pSymbol, pFrame);
					return pValue;
				}
			} else if (pFrame->IsType(ENVTYPE_class)) {
				if (cntSuperSkip > 0) {
					cntSuperSkip--;
				} else {
					ValueEx *pValue = pFrame->LookupValue(pSymbol);
					if (pValue != NULL) {
						CacheFrame(pSymbol, pFrame);
						return pValue;
					}
				}
			}
		}
	} else {
		foreach (FrameOwner, ppFrame, _frameOwner) {
			Frame *pFrame = *ppFrame;
			ValueEx *pValue = pFrame->LookupValue(pSymbol);
			if (pValue != NULL) {
				CacheFrame(pSymbol, pFrame);
				return pValue;
			}
		}
	}
	return NULL;
}

Function *Environment::AssignFunction(Function *pFunc)
{
	unsigned long extra = EXTRA_Public;
	Value value(*this, pFunc, Value::Null);
	GetTopFrame()->AssignValue(pFunc->GetSymbol(), value, extra);
	return pFunc;
}

Function *Environment::LookupFunction(const Symbol *pSymbol, EnvRefMode envRefMode, int cntSuperSkip) const
{
	EnvType envType = GetTopFrame()->GetEnvType();
	if (envRefMode == ENVREF_NoEscalate) {
		Frame *pFrame = const_cast<Frame *>(GetTopFrame());
		Value *pValue = pFrame->LookupValue(pSymbol);
		if (pValue != NULL && pValue->IsFunction()) {
			return pValue->GetFunction();
		}
	} else if (envType == ENVTYPE_object || envType == ENVTYPE_class) {
		foreach_const (FrameOwner, ppFrame, _frameOwner) {
			Frame *pFrame = *ppFrame;
			if (pFrame->IsType(ENVTYPE_object)) {
				Value *pValue = pFrame->LookupValue(pSymbol);
				if (pValue != NULL && pValue->IsFunction()) {
					return pValue->GetFunction();
				}
			} else if (pFrame->IsType(ENVTYPE_class)) {
				if (cntSuperSkip > 0) {
					cntSuperSkip--;
				} else {
					Value *pValue = pFrame->LookupValue(pSymbol);
					if (pValue != NULL && pValue->IsFunction()) {
						return pValue->GetFunction();
					}
				}
			}
		}
	} else {
		foreach_const (FrameOwner, ppFrame, _frameOwner) {
			Frame *pFrame = *ppFrame;
			Value *pValue = pFrame->LookupValue(pSymbol);
			if (pValue != NULL && pValue->IsFunction()) {
				return pValue->GetFunction();
			}
		}
	}
	return NULL;
}

FunctionCustom *Environment::LookupFunctionCustom(const Symbol *pSymbol, EnvRefMode envRefMode, int cntSuperSkip) const
{
	Function *pFunc = LookupFunction(pSymbol, envRefMode, cntSuperSkip);
	return (pFunc != NULL && pFunc->IsCustom())?
						dynamic_cast<FunctionCustom *>(pFunc) : NULL;
}

void Environment::AssignValueType(const ValueTypeInfo *pValueTypeInfo)
{
	GetTopFrame()->AssignValueType(pValueTypeInfo);
}

const ValueTypeInfo *Environment::LookupValueType(const SymbolList &symbolList) const
{
	std::auto_ptr<Environment> pEnvRoot;
	SymbolList::const_iterator ppSymbol = symbolList.begin();
	const Environment *pEnv = this;
	if ((*ppSymbol)->IsIdentical(Gura_Symbol(root))) {
		// make a reference to the root environment
		pEnvRoot.reset(new Environment());
		pEnvRoot->AddRootFrame(GetFrameOwner());
		pEnv = pEnvRoot.get();
		ppSymbol++;
		if (ppSymbol == symbolList.end()) return NULL;
	}
	EnvRefMode envRefMode = ENVREF_Escalate;
	int cntSuperSkip = 0;
	for ( ; ppSymbol + 1 != symbolList.end(); ppSymbol++) {
		const Value *pValue = pEnv->LookupValue(*ppSymbol, envRefMode, cntSuperSkip);
		if (pValue == NULL || !pValue->IsModule()) return NULL;
		pEnv = pValue->GetModule();
		envRefMode = ENVREF_NoEscalate;
	}
	return pEnv->LookupValueType(*ppSymbol);
}

const ValueTypeInfo *Environment::LookupValueType(const Symbol *pSymbol) const
{
	foreach_const (FrameOwner, ppFrame, _frameOwner) {
		const Frame *pFrame = *ppFrame;
		const ValueTypeInfo *pValueTypeInfo = pFrame->LookupValueType(pSymbol);
		if (pValueTypeInfo != NULL) return pValueTypeInfo;
	}
	return NULL;
}

Value Environment::DoGetProp(Environment &env, Signal sig, const Symbol *pSymbol,
								const SymbolSet &attrs, bool &evaluatedFlag)
{
	return Value::Null;
}

Value Environment::DoSetProp(Environment &env, Signal sig, const Symbol *pSymbol, const Value &value,
								const SymbolSet &attrs, bool &evaluatedFlag)
{
	return Value::Null;
}

ICallable *Environment::GetCallable(Signal sig, const Symbol *pSymbol)
{
	return NULL;
}

Value Environment::GetProp(Environment &env, Signal sig, const Symbol *pSymbol,
						const SymbolSet &attrs, const Value *pValueDefault,
						EnvRefMode envRefMode, int cntSuperSkip)
{
	const ValueEx *pValue = LookupValue(pSymbol, envRefMode, cntSuperSkip);
	if (pValue == NULL) {
		// nothing to do
	} else if (envRefMode != ENVREF_Restricted) {
		return *pValue;
	} else if (pValue->GetExtra() & EXTRA_Public) {
		return *pValue;
	} else {
		sig.SetError(ERR_MemberAccessError,
				"can't access private member property %s", pSymbol->GetName());
		return Value::Null;
	}
	bool evaluatedFlag = false;
	Value result = DoGetProp(env, sig, pSymbol, attrs, evaluatedFlag);
	if (sig.IsSignalled()) return Value::Null;
	if (evaluatedFlag) return result;
	if (pValueDefault != NULL) return *pValueDefault;
	if (IsModule()) {
		sig.SetError(ERR_ValueError,
				"%s module does not have a symbol '%s'",
				dynamic_cast<Module *>(this)->GetName(), pSymbol->GetName());
	} else if (IsClass()) {
		sig.SetError(ERR_ValueError,
				"%s class does not have a property '%s'",
				dynamic_cast<Class *>(this)->GetName(), pSymbol->GetName());
	} else if (IsObject()) {
		sig.SetError(ERR_ValueError,
				"the object of %s class does not have a property '%s'",
				dynamic_cast<Object *>(this)->GetClass()->GetName(),
				pSymbol->GetName());
	} else {
		sig.SetError(ERR_ValueError,
				"undefined symbol '%s'", pSymbol->GetName());
	}
	return Value::Null;
}

void Environment::AssignModule(Module *pModule)
{
	unsigned long extra = 0;
	Value value(pModule);
	foreach (FrameOwner, ppFrame, _frameOwner) {
		Frame *pFrame = *ppFrame;
		if (!pFrame->IsType(ENVTYPE_block)) {
			pFrame->AssignValue(pModule->GetSymbol(), value, extra);
			break;
		}
	}
}

bool Environment::ImportModules(Signal sig,
		const char *moduleNames, bool binaryOnlyFlag, bool mixinTypeFlag)
{
	String moduleName;
	for (const char *p = moduleNames; ; p++) {
		char ch = *p;
		if (ch == ',' || ch == '\0') {
			moduleName = Strip(moduleName.c_str());
			SymbolList symbolList;
			String field;
			foreach (String, p, moduleName) {
				char ch = *p;
				if (ch == '.') {
					symbolList.push_back(Symbol::Add(field.c_str()));
					field.clear();
				} else {
					field += ch;
				}
			}
			if (!field.empty()) {
				symbolList.push_back(Symbol::Add(field.c_str()));
			}
			if (!ImportModule(sig, symbolList, NULL, NULL,
					true, true, binaryOnlyFlag, mixinTypeFlag)) return false;
			moduleName.clear();
			if (ch == '\0') break;
		} else {
			moduleName += ch;
		}
	}
	return true;
}

bool Environment::ImportModule(Signal sig, const Expr *pExpr,
			const Symbol *pSymbolOfModule, const SymbolSet *pSymbolsToMixIn,
			bool overwriteFlag, bool binaryOnlyFlag, bool mixinTypeFlag)
{
	bool assignModuleNameFlag = true;
	SymbolList symbolOfModule;
	if (pExpr->IsPrefix()) {
		const Expr_Prefix *pExprEx = dynamic_cast<const Expr_Prefix *>(pExpr);
		const Symbol *pSymbol = pExprEx->GetSymbol();
		if (!pSymbol->IsIdentical(Gura_Symbol(Char_Multiply))) {
			sig.SetError(ERR_ImportError, "wrong format for module name");
		}
		assignModuleNameFlag = false;
		pExpr = pExprEx->GetChild();
	}
	if (!pExpr->GetChainedSymbolList(symbolOfModule)) {
		sig.SetError(ERR_ImportError, "wrong format for module name");
		return false;
	}
	return ImportModule(sig, symbolOfModule, pSymbolOfModule, pSymbolsToMixIn,
			overwriteFlag, assignModuleNameFlag, binaryOnlyFlag, mixinTypeFlag);
}

bool Environment::ImportModule(Signal sig, const SymbolList &symbolOfModule,
			const Symbol *pSymbolAlias, const SymbolSet *pSymbolsToMixIn,
			bool overwriteFlag, bool assignModuleNameFlag,
			bool binaryOnlyFlag, bool mixinTypeFlag)
{
	Module *pModule = NULL;
	if (!binaryOnlyFlag) {
		pModule = ImportIntegratedModule(sig, symbolOfModule);
		if (sig.IsSignalled()) return false;
	}
	if (pModule == NULL) {
		pModule = ImportSeparatedModule(sig, symbolOfModule, binaryOnlyFlag);
		if (sig.IsSignalled()) return false;
	}
	if (pSymbolsToMixIn == NULL) {
		// import(hoge)
		if (!assignModuleNameFlag) {
			// nothing to do
		} else if (pSymbolAlias == NULL) {
			Environment *pEnvDst = this;
			for (SymbolList::const_iterator ppSymbol = symbolOfModule.begin();
									ppSymbol + 1 != symbolOfModule.end(); ppSymbol++) {
				const Symbol *pSymbol = *ppSymbol;
				Value *pValue = pEnvDst->LookupValue(pSymbol, ENVREF_NoEscalate);
				if (pValue != NULL && pValue->IsModule()) {
					pEnvDst = pValue->GetModule();
				} else {
					Module *pModuleParent = new Module(pEnvDst, pSymbol,
													"<integrated>", NULL, NULL);
					Value valueOfModule(pModuleParent);
					if (!pEnvDst->ImportValue(pSymbol, valueOfModule, false)) {
						sig.SetError(ERR_ImportError,
							"module symbol conflicts with an existing variable '%s'",
							symbolOfModule.Join('.').c_str());
						return false;
					}
					pEnvDst = pModuleParent;
				}
			}
			const Symbol *pSymbolOfModule = symbolOfModule.back();
			Value valueOfModule(Module::Reference(pModule));
			if (!pEnvDst->ImportValue(pSymbolOfModule, valueOfModule, false)) {
				sig.SetError(ERR_ImportError,
						"module symbol conflicts with an existing variable '%s'",
						symbolOfModule.front()->GetName());
				return false;
			}
		} else {
			Value valueOfModule(Module::Reference(pModule));
			if (!ImportValue(pSymbolAlias, valueOfModule, false)) {
				sig.SetError(ERR_ImportError,
						"module symbol conflicts with an existing variable '%s'",
						pSymbolAlias->GetName());
				return false;
			}
		}
	} else if (pSymbolsToMixIn->IsSet(Gura_Symbol(Char_Multiply))) {
		// import(hoge) {*}
		//GetFrameOwner().DbgPrint();
		foreach_const (ValueMap, iter, pModule->GetTopFrame()->GetValueMap()) {
			const Symbol *pSymbol = iter->first;
			const Value &value = iter->second;
			if (pSymbol->IsPrivateName()) {
				// nothing to do
			} else if (!ImportValue(pSymbol, value, overwriteFlag)) {
				sig.SetError(ERR_ImportError,
						"imported variable name conflicts with an existing one '%s'",
						pSymbol->GetName());
				return false;
			}
		}
	} else {
		// import(hoge) {foo, bar}
		foreach_const (SymbolSet, ppSymbol, *pSymbolsToMixIn) {
			const Symbol *pSymbol = *ppSymbol;
			Value *pValue = pModule->LookupValue(pSymbol, ENVREF_NoEscalate);
			if (pValue == NULL) {
				// nothing to do
			} else if (!ImportValue(pSymbol, *pValue, overwriteFlag)) {
				sig.SetError(ERR_ImportError,
						"imported variable name conflicts with an existing one '%s'",
												pSymbol->GetName());
				return false;
			}
		}
	}
	if (mixinTypeFlag) {
		foreach_const (ValueTypeMap, iter, pModule->GetTopFrame()->GetValueTypeMap()) {
			const ValueTypeInfo *pValueTypeInfo = iter->second;
			AssignValueType(pValueTypeInfo);
		}
	}
	return true;
}

Module *Environment::ImportIntegratedModule(Signal sig, const SymbolList &symbolOfModule)
{
	int id = 0;
	IntegratedModule *pIntegratedModule = NULL;
	if (_pIntegratedModuleOwner != NULL) {
		foreach (IntegratedModuleOwner, ppIntegratedModule, *_pIntegratedModuleOwner) {
			if ((*ppIntegratedModule)->IsMatch(symbolOfModule)) {
				pIntegratedModule = *ppIntegratedModule;
				break;
			}
			id++;
		}
	}
	if (pIntegratedModule == NULL) return NULL;
	Module *pModule = GetGlobal()->LookupIntegratedModule(id);
	if (pModule == NULL) {
		pModule = new Module(this, symbolOfModule.back(), "<integrated>", NULL, NULL);
		pIntegratedModule->ModuleEntry(*pModule, sig);
		if (sig.IsSignalled()) {
			delete pModule;
			return NULL;
		}
		GetGlobal()->RegisterIntegratedModule(id, pModule);
	}
	return pModule;
}

Module *Environment::ImportSeparatedModule(Signal sig,
					const SymbolList &symbolOfModule, bool binaryOnlyFlag)
{
	String pathName;
	if (!SearchSeparatedModuleFile(sig, pathName,
		symbolOfModule.begin(), symbolOfModule.end(), binaryOnlyFlag)) return NULL;
	Module *pModule = GetGlobal()->LookupSeparatedModule(pathName.c_str());
	if (pModule != NULL) return pModule;
	if (IsBinaryModule(pathName.c_str())) {
		pModule = ImportSeparatedModule_Binary(sig, this,
								pathName.c_str(), symbolOfModule);
	} else {
		pModule = ImportSeparatedModule_Script(sig, this,
								pathName.c_str(), symbolOfModule);
	}
	return pModule;
}

bool Environment::SearchSeparatedModuleFile(Signal sig, String &pathName,
		SymbolList::const_iterator ppSymbolOfModule,
		SymbolList::const_iterator ppSymbolOfModuleEnd, bool binaryOnlyFlag)
{
	Environment &env = *this;
	const Value *pValDirNameList =
			GetModule_sys()->LookupValue(Gura_Symbol(path), ENVREF_NoEscalate);
	if (pValDirNameList == NULL) {
		sig.SetError(ERR_ImportError, "variable path is not specified");
		return false;
	} else if (!pValDirNameList->IsList()) {
		sig.SetError(ERR_ImportError, "variable path must be a list");
		return false;
	}
	StringList extNameList;
	if (!binaryOnlyFlag) {
		extNameList.push_back("gura"); // script module shall be searched first
	}
	extNameList.push_back("gurd");
	String baseName = SymbolList::Join(ppSymbolOfModule,
									ppSymbolOfModuleEnd, OAL::FileSeparator);
	foreach_const (ValueList, pValue, pValDirNameList->GetList()) {
		if (!pValue->IsString()) {
			sig.SetError(ERR_ImportError, "elements of variable path must be strings");
			return false;
		}
		do {
			String pathNameBase = pValue->GetString();
			pathNameBase += OAL::FileSeparator;
			pathNameBase += baseName;
			pathNameBase += '.';
			foreach_const (StringList, pExtName, extNameList) {
				pathName = pathNameBase + *pExtName;
				if (Directory::IsExist(env, sig, pathName.c_str())) return true;
				if (sig.IsSignalled()) return false;
			}
		} while (0);
		do {
			String pathNameBase = pValue->GetString();
			pathNameBase += OAL::FileSeparator;
			pathNameBase += baseName;
			if (Directory::IsContainer(env, sig, pathNameBase.c_str())) {
				pathNameBase += OAL::FileSeparator;
				pathNameBase += "__init__.";
				foreach_const (StringList, pExtName, extNameList) {
					pathName = pathNameBase + *pExtName;
					if (Directory::IsExist(env, sig, pathName.c_str())) return true;
					if (sig.IsSignalled()) return false;
				}
			}
			if (sig.IsSignalled()) return false;
		} while (0);
	}
	sig.SetError(ERR_ImportError, "can't find a module named '%s'",
		SymbolList::Join(ppSymbolOfModule, ppSymbolOfModuleEnd, '.').c_str());
	return false;
}

Module *Environment::ImportSeparatedModule_Script(Signal sig, Environment *pEnvOuter,
						const char *pathName, const SymbolList &symbolOfModule)
{
	Environment &env = *this;
	AutoPtr<Stream> pStream(Directory::OpenStream(env, sig,
										pathName, Stream::ATTR_Readable, NULL));
	if (sig.IsError()) return NULL;
	Expr *pExpr = Parser().ParseStream(*pEnvOuter, sig, *pStream);
	if (sig.IsSignalled()) return NULL;
	Module *pModule = new Module(pEnvOuter, symbolOfModule.back(), pathName, pExpr, NULL);
	GetGlobal()->RegisterSeparatedModule(pathName, pModule);
	bool echoFlagSaved = pModule->GetEchoFlag();
	pModule->SetEchoFlag(false);
	pExpr->Exec(*pModule, sig);
	pModule->SetEchoFlag(echoFlagSaved);
	if (sig.IsSignalled()) {
		GetGlobal()->UnregisterSeparatedModule(pathName);
		delete pModule;
		return NULL;
	}
	return pModule;
}

Module *Environment::ImportSeparatedModule_Binary(Signal sig, Environment *pEnvOuter,
						const char *pathName, const SymbolList &symbolOfModule)
{
	OAL::DynamicLibrary dynamicLibrary;
	if (!dynamicLibrary.Open(sig, pathName)) return NULL;
	void *pFunc = NULL;
	pFunc = dynamicLibrary.GetEntry(sig, "GuraModuleEntry");
	if (pFunc == NULL) return NULL;
	// gcc of a certain version such as 3.4.6 may cause an error when trying to
	// cast between pointer-to-function and pointer-to-using with reinterpret_cast.
	ModuleEntryType moduleEntry = (ModuleEntryType)(pFunc);
	pFunc = dynamicLibrary.GetEntry(sig, "GuraModuleTerminate");
	if (pFunc == NULL) return NULL;
	ModuleTerminateType moduleTerminate = (ModuleTerminateType)(pFunc);
	Module *pModule = new Module(pEnvOuter, symbolOfModule.back(), pathName, NULL, moduleTerminate);
	GetGlobal()->RegisterSeparatedModule(pathName, pModule);
	(*moduleEntry)(*pModule, sig);
	if (sig.IsSignalled()) {
		GetGlobal()->UnregisterSeparatedModule(pathName);
		delete pModule;
		return NULL;
	}
	return pModule;
}

bool Environment::IsBinaryModule(const char *pathName)
{
	return ::strcasecmp(Directory::SeekExtName(pathName), ".gurd") == 0;
}

bool Environment::AddModuleSearchPath(Signal sig, const StringList &strList)
{
	Environment &env = *this;
	Value *pValDirNameList =
			GetModule_sys()->LookupValue(Gura_Symbol(path), ENVREF_NoEscalate);
	if (pValDirNameList == NULL) {
		sig.SetError(ERR_ImportError, "path variable is not specified");
		return false;
	}
	ValueList &valList = pValDirNameList->GetList();
	foreach_const (StringList, pStr, strList) {
		Value value(env, pStr->c_str());
		valList.push_back(value);
	}
	return true;
}

const char *Environment::GetPrompt(bool indentFlag)
{
	Value *pValue = GetModule_sys()->LookupValue(
			indentFlag? Gura_Symbol(ps2) : Gura_Symbol(ps1), ENVREF_NoEscalate);
	return (pValue == NULL || !pValue->IsString())? "" : pValue->GetString();
}

Stream *Environment::GetConsole()
{
	Value *pValue = GetModule_sys()->LookupValue(Gura_Symbol(stdout), ENVREF_NoEscalate);
	if (pValue == NULL || !pValue->IsInstanceOf(VTYPE_stream)) {
		return GetConsoleDumb();
	}
	return &pValue->GetStream();
}

Stream *Environment::GetConsoleErr()
{
	Value *pValue = GetModule_sys()->LookupValue(Gura_Symbol(stderr), ENVREF_NoEscalate);
	if (pValue == NULL || !pValue->IsInstanceOf(VTYPE_stream)) {
		return GetConsoleDumb();
	}
	return &pValue->GetStream();
}

Stream *Environment::GetConsoleDumb()
{
	return GetGlobal()->GetConsoleDumb();
}

// this function is called in a args before main() function.
void Environment::IntegrateModule(const char *name,
			ModuleEntryType moduleEntry, ModuleTerminateType moduleTerminate)
{
	if (_pIntegratedModuleOwner == NULL) {
		_pIntegratedModuleOwner = new IntegratedModuleOwner();
	}
	_pIntegratedModuleOwner->push_back(
					new IntegratedModule(name, moduleEntry, moduleTerminate));
}

bool Environment::IsModule() const { return false; }
bool Environment::IsClass() const { return false; }
bool Environment::IsObject() const { return false; }

//-----------------------------------------------------------------------------
// Environment::Global
//-----------------------------------------------------------------------------
Environment::Global::Global() : _echoFlag(false)
{
	for (size_t i = 0; i < OPTYPE_max; i++) {
		_pOpFuncTbl[i] = NULL;
	}
}

Environment::Global::~Global()
{
	foreach_const (SeparatedModuleMap, iter, _separatedModuleMap) {
		delete iter->second;
	}
	for (size_t i = 0; i < OPTYPE_max; i++) {
		Function::Delete(_pOpFuncTbl[i]);
	}
}

void Environment::Global::Prepare(Signal sig)
{
	_workingDirList.push_back(OAL::GetCurDir());
	_pValueTypePool = ValueTypePool::GetInstance();
	_pConsoleDumb.reset(new StreamDumb(sig));
}

Class *Environment::Global::LookupClass(ValueType valType) const
{
	return ValueTypePool::GetInstance()->Lookup(valType)->GetClass();
}

Module *Environment::Global::LookupIntegratedModule(int id) const
{
	IntegratedModuleMap::const_iterator iter = _integratedModuleMap.find(id);
	return (iter == _integratedModuleMap.end())? NULL : iter->second;
}

void Environment::Global::RegisterIntegratedModule(int id, Module *pModule)
{
	_integratedModuleMap[id] = pModule;
}

Module *Environment::Global::LookupSeparatedModule(const char *pathName) const
{
	SeparatedModuleMap::const_iterator iter = _separatedModuleMap.find(pathName);
	return (iter == _separatedModuleMap.end())? NULL : iter->second;
}

void Environment::Global::RegisterSeparatedModule(const char *pathName, Module *pModule)
{
	_separatedModuleMap[pathName] = pModule;
}

void Environment::Global::UnregisterSeparatedModule(const char *pathName)
{
	_separatedModuleMap.erase(_separatedModuleMap.find(pathName));
}

//-----------------------------------------------------------------------------
// Environment::Frame
//-----------------------------------------------------------------------------
Environment::Frame::Frame(const Frame &frame) :
			_cntRef(1), _envType(frame._envType), _pGlobal(frame._pGlobal)
{
	if (frame._pValueMap.get() != NULL) {
		_pValueMap.reset(new ValueMap(*frame._pValueMap));
	}
	if (frame._pValueTypeMap.get() != NULL) {
		_pValueTypeMap.reset(new ValueTypeMap(*frame._pValueTypeMap));
	}
}

Environment::Frame::Frame(EnvType envType, Global *pGlobal) :
			_cntRef(1), _envType(envType), _pGlobal(pGlobal)
{
}

Environment::Frame::~Frame()
{
}

void Environment::Frame::Delete(Frame *pFrame)
{
	if (pFrame == NULL) return;
	EnvType envType = pFrame->GetEnvType();
	if (envType != ENVTYPE_root && envType != ENVTYPE_class &&
										pFrame->_pValueMap.get() != NULL) {
		const ValueMap &valueMap = *pFrame->_pValueMap;
		EnvironmentSet envSet;
		foreach_const (ValueMap, iter, valueMap) {
			const Value &value = iter->second;
			if (value.IsObject() && !value.GetTinyBuffFlag()) {
				value.GetObject()->GatherFollower(pFrame, envSet);
			}
		}
		int cntFollower = static_cast<int>(envSet.size());
		if (pFrame->GetRefCnt() <= cntFollower + 1) {
			foreach (EnvironmentSet, ppEnv, envSet) {
				(*ppEnv)->GetFrameOwner().remove(pFrame);
			}
			delete pFrame;
		} else {
			pFrame->DecRef();
		}
	
	} else if (pFrame->DecRef() <= 0) {
		delete pFrame;
	}
}

void Environment::Frame::AssignValue(const Symbol *pSymbol,
									const Value &value, unsigned long extra)
{
	if (_pValueMap.get() == NULL) _pValueMap.reset(new ValueMap());
	(*_pValueMap)[pSymbol] = ValueEx(value, extra);
}

void Environment::Frame::RemoveValue(const Symbol *pSymbol)
{
	if (_pValueMap.get() == NULL) return;
	_pValueMap->erase(pSymbol);
}

ValueEx *Environment::Frame::LookupValue(const Symbol *pSymbol)
{
	if (_pValueMap.get() == NULL) return NULL;
	ValueMap::iterator iter = _pValueMap->find(pSymbol);
	return (iter == _pValueMap->end())? NULL : &iter->second;
}

void Environment::Frame::AssignValueType(const ValueTypeInfo *pValueTypeInfo)
{
	if (_pValueTypeMap.get() == NULL) _pValueTypeMap.reset(new ValueTypeMap());
	(*_pValueTypeMap)[pValueTypeInfo->GetSymbol()] = pValueTypeInfo;
}

const ValueTypeInfo *Environment::Frame::LookupValueType(const Symbol *pSymbol) const
{
	if (_pValueTypeMap.get() == NULL) return NULL;
	ValueTypeMap::iterator iter = _pValueTypeMap->find(pSymbol);
	return (iter == _pValueTypeMap->end())? NULL : iter->second;
}

void Environment::Frame::DbgPrint() const
{
	::printf("%p %-10s\n", this, GetEnvTypeName(GetEnvType()));
	if (_pValueMap.get() == NULL) {
		::printf(" [Values] .. null\n");
	} else {
		::printf(" [Values] .. %p\n", _pValueMap.get());
		if (!_pValueMap->empty()) {
			foreach_const (ValueMap, iter, *_pValueMap) {
				::printf(" %s", iter->first->GetName());
			}
			::printf("\n");
		}
	}
	if (_pValueTypeMap.get() == NULL) {
		::printf(" [Value Types] .. null\n");
	} else {
		::printf(" [Value Types] .. %p\n", _pValueTypeMap.get());
		if (!_pValueTypeMap->empty()) {
			foreach_const (ValueTypeMap, iter, *_pValueTypeMap) {
				::printf(" %s", iter->first->GetName());
			}
			::printf("\n");
		}
	}
}

//-----------------------------------------------------------------------------
// Environment::FrameList
//-----------------------------------------------------------------------------
void Environment::FrameList::DbgPrint() const
{
	int idx = 0;
	foreach_const (FrameList, ppFrame, *this) {
		const Frame *pFrame = *ppFrame;
		idx++;
		::printf("frame#%d ", idx);
		pFrame->DbgPrint();
	}
}

//-----------------------------------------------------------------------------
// Environment::FrameOwner
//-----------------------------------------------------------------------------
Environment::FrameOwner::~FrameOwner()
{
	Clear();
}

void Environment::FrameOwner::Clear()
{
	foreach (FrameOwner, ppFrame, *this) {
		Frame *pFrame = *ppFrame;
		Frame::Delete(pFrame);
	}
	clear();
}

//-----------------------------------------------------------------------------
// EnvironmentRoot
//-----------------------------------------------------------------------------
EnvironmentRoot::EnvironmentRoot()
{
	SymbolPool::Initialize();
	Global *pGlobal = new Global();
	pGlobal->_pSymbolPool = SymbolPool::GetInstance();
	_frameOwner.push_back(new Frame(ENVTYPE_root, pGlobal));
}

EnvironmentRoot::~EnvironmentRoot()
{
	Global *pGlobal = GetGlobal();
	Global::Delete(pGlobal);
}

bool EnvironmentRoot::Initialize(Signal sig, int argc, const char *argv[])
{
	Environment &env = *this;
#if defined(_MSC_VER)
	::_set_output_format(_TWO_DIGIT_EXPONENT);
#endif
	RandomGenerator::Initialize(1234);	// initialize random generator SFMT
	ValueTypePool::Initialize(env);
	GetGlobal()->Prepare(sig);
	AssignErrorTypes(env);	// Signal.cpp
	AssignOperators(env);	// Operators.cpp
	do {
		ValueTypePool::OnModuleEntry(env, sig);
	} while (0);
	do { // import(basement) { * }
		Gura_Module(basement)::MixIn(env, sig);
		if (sig.IsSignalled()) return false;
	} while (0);
	do { // import(sys), this module must be imported just after basement
		Module *pModule = Gura_Module(sys)::Import(env, sig);
		if (sig.IsSignalled()) return false;
		GetGlobal()->_pModule_sys = pModule;
	} while (0);
	do {
		Module *pModule = new Module(&env, Symbol::Add("codecs"),
											"<integrated>", NULL, NULL);
		env.AssignModule(pModule);
		// import(codecs.basic)
		if (Gura_Module(codecs_basic)::Import(*pModule, sig) == NULL) return false;
		// import(codecs.iso8859)
		if (Gura_Module(codecs_iso8859)::Import(*pModule, sig) == NULL) return false;
		// import(codecs.japanese)
		if (Gura_Module(codecs_japanese)::Import(*pModule, sig) == NULL) return false;
	} while (0);
	// import(base64)
	if (Gura_Module(base64)::Import(env, sig) == NULL) return false;
	// import(fs)
	if (Gura_Module(fs)::Import(env, sig) == NULL) return false;
	// import(os)
	if (Gura_Module(os)::Import(env, sig) == NULL) return false;
	// import(path)
	if (Gura_Module(path)::Import(env, sig) == NULL) return false;
	// import(time)
	if (Gura_Module(time)::Import(env, sig) == NULL) return false;
	// import(math)
	if (Gura_Module(math)::Import(env, sig) == NULL) return false;
	// import(conio)
	if (Gura_Module(conio)::Import(env, sig) == NULL) return false;
	// setup values in sys module
	if (!Gura_Module(sys)::SetupValues(GetModule_sys(), sig, argc, argv)) {
		return false;
	}
	OAL::SetupExecutablePath();
	return true;
}

}
