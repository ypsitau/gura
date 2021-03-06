//-----------------------------------------------------------------------------
// Gura module: os
//-----------------------------------------------------------------------------
#include "stdafx.h"
#if !defined(GURA_ON_MSWIN)
#include "unistd.h"
#endif

Gura_BeginModuleBody(os)

static Environment *_pEnvThis = nullptr;

//-----------------------------------------------------------------------------
// Gura module functions: os
//-----------------------------------------------------------------------------
// os.clock() {block?}
Gura_DeclareFunction(clock)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
	AddHelp(
		Gura_Symbol(en),
		"Returns the time duration in second since the system has started.\n"
		"\n"
		"If `block` is specified, it would calculate how much time has been spent\n"
		"during evaluating the block.\n ");
}

Gura_ImplementFunction(clock)
{
	if (!arg.IsBlockSpecified()) return Value(OAL::GetTickTime());
	AutoPtr<Environment> pEnvBlock(env.Derive(ENVTYPE_local));
	const Expr_Block *pExprBlock = arg.GetBlockCooked(*pEnvBlock);
	if (env.IsSignalled()) return Value::Nil;
	Number timeStart = OAL::GetTickTime();
	pExprBlock->Exec(*pEnvBlock);
	Number timeEnd = OAL::GetTickTime();
	if (env.IsSignalled()) return Value::Nil;
	return Value(timeEnd - timeStart);
}

// os.exec(pathname:string, args*:string):map:[fork]
Gura_DeclareFunction(exec)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "pathname", VTYPE_string);
	DeclareArg(env, "args", VTYPE_string, OCCUR_ZeroOrMore);
	DeclareAttr(Gura_Symbol(fork));
	AddHelp(
		Gura_Symbol(en),
		"Executes the specified executable file.");
}

Gura_ImplementFunction(exec)
{
	Signal &sig = env.GetSignal();
	bool forkFlag = arg.IsSet(Gura_Symbol(fork));
	const char *pathName = arg.GetString(0);
	if (forkFlag) {
		OAL::ExecProgram(env, pathName, arg.GetList(1),
						 nullptr, nullptr, nullptr, forkFlag);
		return Value::Nil;
	}
	const Value *pValue = nullptr;
	pValue = _pEnvThis->LookupValue(Gura_Symbol(stdin), ENVREF_NoEscalate);
	Stream *pStreamStdin = (pValue != nullptr && pValue->Is_stream())?
										&pValue->GetStream() : nullptr;
	pValue = _pEnvThis->LookupValue(Gura_Symbol(stdout), ENVREF_NoEscalate);
	Stream *pStreamStdout = (pValue != nullptr && pValue->Is_stream())?
										&pValue->GetStream() : nullptr;
	pValue = _pEnvThis->LookupValue(Gura_Symbol(stderr), ENVREF_NoEscalate);
	Stream *pStreamStderr = (pValue != nullptr && pValue->Is_stream())?
										&pValue->GetStream() : nullptr;
	int rtn = OAL::ExecProgram(env, pathName, arg.GetList(1),
					   pStreamStdin, pStreamStdout, pStreamStderr, forkFlag);
	if (sig.IsSignalled()) return Value::Nil;
	return Value(rtn);
}

// os.fromnative(buff:binary):map
Gura_DeclareFunction(fromnative)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "buff", VTYPE_binary);
	AddHelp(
		Gura_Symbol(en), 
		"Converts binary data that includes OS's native string into Gura's regulated string.");
}

Gura_ImplementFunction(fromnative)
{
	const Binary &buff = arg.GetBinary(0);
	String str = OAL::FromNativeString(buff.data(), static_cast<int>(buff.size()));
	return Value(str);
}

// os.getenv(name:string, default?:string):map
Gura_DeclareFunction(getenv)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "name", VTYPE_string);
	DeclareArg(env, "default", VTYPE_string, OCCUR_ZeroOrOnce);
	AddHelp(
		Gura_Symbol(en),
		"Returns the value of an environment variable.");
}

Gura_ImplementFunction(getenv)
{
	bool foundFlag = false;
	String str = OAL::GetEnv(arg.GetString(0), &foundFlag);
	if (!foundFlag) return arg.IsValid(1)? arg.GetValue(1) : Value::Nil;
	return Value(str);
}

// os.putenv(name:string, value:string):void
Gura_DeclareFunction(putenv)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "name", VTYPE_string);
	DeclareArg(env, "value", VTYPE_string);
	AddHelp(
		Gura_Symbol(en),
		"Set the value of an environment variable.");
}

Gura_ImplementFunction(putenv)
{
	OAL::PutEnv(arg.GetString(0), arg.GetString(1));
	return Value::Nil;
}

// os.redirect(stdin:stream:nil:r, stdout:stream:nil:w, stderr?:stream:w) {block?}
Gura_DeclareFunction(redirect)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "stdin", VTYPE_stream, OCCUR_Once, FLAG_Nil | FLAG_Read);
	DeclareArg(env, "stdout", VTYPE_stream, OCCUR_Once, FLAG_Nil | FLAG_Write);
	DeclareArg(env, "stderr", VTYPE_stream, OCCUR_ZeroOrOnce, FLAG_Write);
	DeclareBlock(OCCUR_ZeroOrOnce);
	AddHelp(
		Gura_Symbol(en),
		"Modifies variables `os.stdin`, `os.stdout` and `os.stderr` with values of arguments.\n"
		"When `block` is specified, the modification only has effect within the block.");
}

Gura_ImplementFunction(redirect)
{
	Signal &sig = env.GetSignal();
	Value *pValue = nullptr;
	Value value_stdin, value_stdout, value_stderr;
	if ((pValue = _pEnvThis->LookupValue(Gura_Symbol(stdin), ENVREF_NoEscalate)) != nullptr) {
		value_stdin = *pValue;
	}
	if ((pValue = _pEnvThis->LookupValue(Gura_Symbol(stdout), ENVREF_NoEscalate)) != nullptr) {
		value_stdout = *pValue;
	}
	if ((pValue = _pEnvThis->LookupValue(Gura_Symbol(stderr), ENVREF_NoEscalate)) != nullptr) {
		value_stderr = *pValue;
	}
	_pEnvThis->AssignValue(Gura_Symbol(stdin), arg.GetValue(0), EXTRA_Public);
	_pEnvThis->AssignValue(Gura_Symbol(stdout), arg.GetValue(1), EXTRA_Public);
	if (arg.IsDefined(2)) {
		_pEnvThis->AssignValue(Gura_Symbol(stderr), arg.GetValue(2), EXTRA_Public);
	} else {
		_pEnvThis->AssignValue(Gura_Symbol(stderr), arg.GetValue(1), EXTRA_Public);
	}
	Value result;
	if (arg.IsBlockSpecified()) {
		AutoPtr<Environment> pEnvBlock(env.Derive(ENVTYPE_local));
		const Expr_Block *pExprBlock = arg.GetBlockCooked(*pEnvBlock);
		if (sig.IsSignalled()) return Value::Nil;
		result = pExprBlock->Exec(*pEnvBlock);
		_pEnvThis->AssignValue(Gura_Symbol(stdin), value_stdin, EXTRA_Public);
		_pEnvThis->AssignValue(Gura_Symbol(stdout), value_stdout, EXTRA_Public);
		_pEnvThis->AssignValue(Gura_Symbol(stderr), value_stderr, EXTRA_Public);
	}
	return result;
}

// os.sleep(secs)
Gura_DeclareFunction(sleep)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "secs", VTYPE_number);
	AddHelp(
		Gura_Symbol(en),
		"Sleeps for a time specified in seconds.");
}

Gura_ImplementFunction(sleep)
{
	OAL::Sleep(arg.GetNumber(0));
	return Value::Nil;
}

// os.symlink(src:string, tgt:string):map:void
Gura_DeclareFunction(symlink)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "src", VTYPE_string);
	DeclareArg(env, "tgt", VTYPE_string);
	AddHelp(
		Gura_Symbol(en),
		"Creates a symbol link.");
}

Gura_ImplementFunction(symlink)
{
	Signal &sig = env.GetSignal();
#if defined(GURA_ON_MSWIN)
	sig.SetError(ERR_NotImplementedError, "unsupported function");
	return Value::Nil;
#else
	if (::symlink(arg.GetString(0), arg.GetString(1)) < 0) {
		sig.SetError(ERR_IOError, "failed to create a symbolic link");
		return Value::Nil;
	}
	return Value::Nil;
#endif
}

// os.tonative(str:string):map
Gura_DeclareFunction(tonative)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "str", VTYPE_string);
	AddHelp(
		Gura_Symbol(en), 
		"Converts Gura's regulated string into binary data that includes OS's native string.");
}

Gura_ImplementFunction(tonative)
{
	const char *str = arg.GetString(0);
	String buff = OAL::ToNativeString(str);
	return Value(new Object_binary(env, buff.data(), buff.size(), true));
}

// os.unsetenv(name:string):void
Gura_DeclareFunction(unsetenv)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "name", VTYPE_string);
	AddHelp(
		Gura_Symbol(en),
		"Unset an environment variable.");
}

Gura_ImplementFunction(unsetenv)
{
	OAL::UnsetEnv(arg.GetString(0));
	return Value::Nil;
}

//-----------------------------------------------------------------------------
// Module Entries
//-----------------------------------------------------------------------------
Gura_ModuleValidate()
{
	return Version::CheckCoreVersion(GURA_VERSION, nullptr);
}

Gura_ModuleEntry()
{
	_pEnvThis = &env;
	// value assignment
	Module *pModuleSys = env.GetGlobal()->GetModule_sys();
	do {
		const Value *pValue = pModuleSys->LookupValue(Gura_Symbol(stdin), ENVREF_NoEscalate);
		if (pValue == nullptr) pValue = &Value::Nil;
		Gura_AssignValue(stdin, *pValue);
	} while (0);
	do {
		const Value *pValue = pModuleSys->LookupValue(Gura_Symbol(stdout), ENVREF_NoEscalate);
		if (pValue == nullptr) pValue = &Value::Nil;
		Gura_AssignValue(stdout, *pValue);
	} while (0);
	do {
		const Value *pValue = pModuleSys->LookupValue(Gura_Symbol(stderr), ENVREF_NoEscalate);
		if (pValue == nullptr) pValue = &Value::Nil;
		Gura_AssignValue(stderr, *pValue);
	} while (0);
	// function assignment
	Gura_AssignFunction(clock);
	Gura_AssignFunction(exec);
	Gura_AssignFunction(fromnative);
	Gura_AssignFunction(getenv);
	Gura_AssignFunction(putenv);
	Gura_AssignFunction(redirect);
	Gura_AssignFunction(sleep);
	Gura_AssignFunction(symlink);
	Gura_AssignFunction(tonative);
	Gura_AssignFunction(unsetenv);
	return true;
}

Gura_ModuleTerminate()
{
}

Gura_EndModuleBody(os, os)

Gura_RegisterModule(os)
