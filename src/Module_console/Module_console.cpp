//-----------------------------------------------------------------------------
// Gura console module
//-----------------------------------------------------------------------------
#include "Module_console.h"

Gura_BeginModule(console)

//-----------------------------------------------------------------------------
// Gura module functions: console
//-----------------------------------------------------------------------------
// console.test(num1:number, num2:number)
Gura_DeclareFunction(test)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "num1", VTYPE_number);
	DeclareArg(env, "num2", VTYPE_number);
	AddHelp(Gura_Symbol(en), "adds two numbers and returns the result.");
}

Gura_ImplementFunction(test)
{
	return Value(args.GetNumber(0) + args.GetNumber(1));
}

//-----------------------------------------------------------------------------
// Module entry
//-----------------------------------------------------------------------------
Gura_ModuleEntry()
{
	// function assignment
	Gura_AssignFunction(test);
}

Gura_ModuleTerminate()
{
}

Gura_EndModule(console, console)

Gura_RegisterModule(console)
