//=============================================================================
// Gura class: error
//=============================================================================
#include "stdafx.h"

namespace Gura {

static const char *helpDoc_en = R"**(
# Overview

The `error` class provides measures to access error information.

There is no measures to create an `error` instance.
They're instantiated and passed to a block of `catch()` function
when an error occurs within a `try` block in a `try-catch` sequence.

In the following code, `e` is an instance that contains information
about an error that has occured in the `try` block.

    try {
        // any jobs
    } catch {|e:error|
        // ...
    }


# Predefined Variable

<table>
<tr><th>Variable</th><th>Explanation</th></tr>

<tr><td><code>error.ArgumentError</code></td>
<td>Argument error.</td></tr>

<tr><td><code>error.ArithmeticError</code></td>
<td>Arithmetic error.</td></tr>

<tr><td><code>error.AttributeError</code></td>
<td>Invalid attribute is specified.</td></tr>

<tr><td><code>error.CodecError</code></td>
<td>An error that is related to codec process.</td></tr>

<tr><td><code>error.CommandError</code></td>
<td>An error that could happen in command line.</td></tr>

<tr><td><code>error.DeclarationError</code></td>
<td>An error in a function\'s declarations.</td></tr>

<tr><td><code>error.FormatError</code></td>
<td></td></tr>

<tr><td><code>error.IOError</code></td>
<td></td></tr>

<tr><td><code>error.ImportError</code></td>
<td></td></tr>

<tr><td><code>error.IndexError</code></td>
<td></td></tr>

<tr><td><code>error.IteratorError</code></td>
<td></td></tr>

<tr><td><code>error.KeyError</code></td>
<td></td></tr>

<tr><td><code>error.MemberAccessError</code></td>
<td></td></tr>

<tr><td><code>error.MemoryError</code></td>
<td></td></tr>

<tr><td><code>error.NameError</code></td>
<td></td></tr>

<tr><td><code>error.NotImplementedError</code></td>
<td>An error that could occur when a called function has no implemented body but an entry.</td></tr>

<tr><td><code>error.OutOfRange</code></td>
<td>Index number is out of range.</td></tr>

<tr><td><code>error.ResourceError</code></td>
<td>Resource error.</td></tr>

<tr><td><code>error.RuntimeError</code></td>
<td>Runtime error.</td></tr>

<tr><td><code>error.SyntaxError</code></td>
<td>Syntax error.</td></tr>

<tr><td><code>error.SystemError</code></td>
<td>System error.</td></tr>

<tr><td><code>error.TypeError</code></td>
<td>Type error.</td></tr>

<tr><td><code>error.ValueError</code></td>
<td>Invalid value is specified.</td></tr>

<tr><td><code>error.ZeroDivisionError</code></td>
<td>Zero-division occured in division or modulo operations.</td></tr>

</table>


# Property

An `error` instance has the following properties:

${markdown.makedoc@property(`en, error)}
)**";

//-----------------------------------------------------------------------------
// Object_error
//-----------------------------------------------------------------------------
Object_error::Object_error(const Object_error &obj) : Object(obj), _err(obj._err)
{
}

Object *Object_error::Clone() const
{
	return new Object_error(*this);
}

String Object_error::ToString(bool exprFlag)
{
	String rtn;
	rtn += "<error:";
	rtn += _err.GetTypeName();
	rtn += ">";
	return rtn;
}

//-----------------------------------------------------------------------------
// Implementation of properties
//-----------------------------------------------------------------------------
// error#source
Gura_DeclareProperty_R(error, source)
{
	SetPropAttr(VTYPE_string);
	AddHelp(
		Gura_Symbol(en),
		"The name of the file that causes this error.");
}

Gura_ImplementPropertyGetter(error, source)
{
	const Gura::Error &err = Object_error::GetObject(valueThis)->GetError();
	const char *sourceName = err.GetSourceName();
	if (sourceName == nullptr) return Value::Nil;
	return Value(sourceName);
}

// error#lineno
Gura_DeclareProperty_R(error, lineno)
{
	SetPropAttr(VTYPE_number);
	AddHelp(
		Gura_Symbol(en),
		"The number of line where the expression that causes this error starts.");
}

Gura_ImplementPropertyGetter(error, lineno)
{
	const Gura::Error &err = Object_error::GetObject(valueThis)->GetError();
	return Value(err.GetLineNoTop());
}

// error#linenobtm
Gura_DeclareProperty_R(error, linenobtm)
{
	SetPropAttr(VTYPE_number);
	AddHelp(
		Gura_Symbol(en),
		"The number of line where the expression that causes this error ends.");
}

Gura_ImplementPropertyGetter(error, linenobtm)
{
	const Gura::Error &err = Object_error::GetObject(valueThis)->GetError();
	return Value(err.GetLineNoBtm());
}

// error#postext
Gura_DeclareProperty_R(error, postext)
{
	SetPropAttr(VTYPE_string);
	AddHelp(
		Gura_Symbol(en),
		"A text that consists of a source name and a line number.");
}

Gura_ImplementPropertyGetter(error, postext)
{
	const Gura::Error &err = Object_error::GetObject(valueThis)->GetError();
	return Value(err.MakePosText());
}

// error#text:[lineno]
Gura_DeclareProperty_R(error, text)
{
	SetPropAttr(VTYPE_string);
	AddHelp(
		Gura_Symbol(en),
		"An error message. If an attribute `:lineno` is specified, it would contain a line number.");
}

Gura_ImplementPropertyGetter(error, text)
{
	const Gura::Error &err = Object_error::GetObject(valueThis)->GetError();
	bool lineInfoFlag = attrs.IsSet(Gura_Symbol(lineno));
	return Value(err.MakeText(lineInfoFlag));
}

// error#trace
Gura_DeclareProperty_R(error, trace)
{
	SetPropAttr(VTYPE_iterator);
	AddHelp(
		Gura_Symbol(en),
		"An iterator that generates `expr` instances that indicate stack trace.");
}

Gura_ImplementPropertyGetter(error, trace)
{
	const Gura::Error &err = Object_error::GetObject(valueThis)->GetError();
	AutoPtr<ExprOwner> pExprOwner(new ExprOwner());
	err.GetExprCauseOwner().ExtractTrace(*pExprOwner);
	return Value(new Object_iterator(env, new ExprOwner::Iterator(pExprOwner.release())));
}

//-----------------------------------------------------------------------------
// Implementation of class
//-----------------------------------------------------------------------------
Class_error::Class_error(Environment *pEnvOuter) : ClassFundamental(pEnvOuter, VTYPE_error)
{
}

void Class_error::DoPrepare(Environment &env)
{
	// Assignment of error types
	Error::AssignErrorTypes(*this);
	// Assignment of properties
	Gura_AssignProperty(error, source);
	Gura_AssignProperty(error, lineno);
	Gura_AssignProperty(error, linenobtm);
	Gura_AssignProperty(error, postext);
	Gura_AssignProperty(error, text);
	Gura_AssignProperty(error, trace);
	// Assignment of values
	Gura_AssignValue(error, Value(Reference()));
	// help document
	AddHelpTemplate(env, Gura_Symbol(en), helpDoc_en);
}

Object *Class_error::CreateDescendant(Environment &env, Class *pClass)
{
	GURA_ERROREND(env, "this function must not be called");
	return nullptr;
}

}
