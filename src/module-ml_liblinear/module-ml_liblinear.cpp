//=============================================================================
// Gura module: ml.liblinear
//=============================================================================
#include "stdafx.h"

Gura_BeginModuleBody(ml_liblinear)

//-----------------------------------------------------------------------------
// Module functions
//-----------------------------------------------------------------------------
// ml.liblinear.train()
Gura_DeclareFunction(train)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "num1", VTYPE_number);
	//DeclareArg(env, "num2", VTYPE_number);
	AddHelp(
		Gura_Symbol(en),
		"This function adds two numbers and returns the result.\n");
}

Gura_ImplementFunction(train)
{
	//return Value(arg.GetNumber(0) + arg.GetNumber(1));
	::train(nullptr, nullptr);
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
	// function assignment
	Gura_AssignFunction(train);
	return true;
}

Gura_ModuleTerminate()
{
}

Gura_EndModuleBody(ml_liblinear, liblinear)

Gura_RegisterModule(ml_liblinear)
