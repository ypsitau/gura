//=============================================================================
// Gura class: suffixmgr
//=============================================================================
#include "stdafx.h"

namespace Gura {

static const char *helpDoc_en = R"**(
)**";

//-----------------------------------------------------------------------------
// Object_suffixmgr
//-----------------------------------------------------------------------------
Object_suffixmgr::Object_suffixmgr(Environment &env, SuffixMgr &suffixMgr) :
			Object(env.LookupClass(VTYPE_suffixmgr)), _suffixMgr(suffixMgr)
{
}

Object_suffixmgr::Object_suffixmgr(Class *pClass, SuffixMgr &suffixMgr) :
			Object(pClass), _suffixMgr(suffixMgr)
{
}

Object *Object_suffixmgr::Clone() const
{
	return nullptr; //new Object_suffixmgr(*this);
}

bool Object_suffixmgr::DoDirProp(Environment &env, SymbolSet &symbols)
{
	if (!Object::DoDirProp(env, symbols)) return false;
	return true;
}

Value Object_suffixmgr::DoGetProp(Environment &env, const Symbol *pSymbol,
								const SymbolSet &attrs, bool &evaluatedFlag)
{
	return Value::Nil;
}

Value Object_suffixmgr::DoSetProp(Environment &env, const Symbol *pSymbol, const Value &value,
								const SymbolSet &attrs, bool &evaluatedFlag)
{
	return DoGetProp(env, pSymbol, attrs, evaluatedFlag);
}

String Object_suffixmgr::ToString(bool exprFlag)
{
	String rtn;
	rtn += "<suffixmgr";
	rtn += ">";
	return rtn;
}

//-----------------------------------------------------------------------------
// Implementation of functions
//-----------------------------------------------------------------------------
// suffixmgr(type:symbol) {block?}
Gura_DeclareFunction(suffixmgr)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "type", VTYPE_symbol);
	DeclareBlock(OCCUR_ZeroOrOnce);
	SetClassToConstruct(env.LookupClass(VTYPE_suffixmgr));
	AddHelp(
		Gura_Symbol(en),
		"Creates a reference to one of two suffix managers, number and string.\n"
		"\n"
		"- The number suffix manager works with number literals.\n"
		"- The string suffix manager works with string literals.\n"
		"\n"
		"Specify the argument `type` with a symbol `` `number`` for a number suffix manager\n"
		"and `` `string`` for a string suffix manager.\n");
}

Gura_ImplementFunction(suffixmgr)
{
	Signal &sig = env.GetSignal();
	const Symbol *pSymbol = arg.GetSymbol(0);
	AutoPtr<Object_suffixmgr> pObj;
	if (pSymbol->IsIdentical(Gura_Symbol(number))) {
		pObj.reset(new Object_suffixmgr(env,
						env.GetGlobal()->GetSuffixMgrForNumber()));
	} else if (pSymbol->IsIdentical(Gura_Symbol(string))) {
		pObj.reset(new Object_suffixmgr(env,
						env.GetGlobal()->GetSuffixMgrForString()));
	} else {
		sig.SetError(ERR_ValueError, "type must be `number or `string");
		return Value::Nil;
	}
	return Value(pObj.release());
}

//-----------------------------------------------------------------------------
// Implementation of methods
//-----------------------------------------------------------------------------
// suffixmgr#assign(suffix:symbol):void:[overwrite] {block}
Gura_DeclareMethod(suffixmgr, assign)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "suffix", VTYPE_symbol);
	DeclareAttr(Gura_Symbol(overwrite));
	DeclareBlock(OCCUR_Once);
	AddHelp(
		Gura_Symbol(en),
		"Assigns a procedure to a specified symbol in the suffix manager.\n"
		"The procedure is provided by the `block` that takes a block parameter `|value|`\n"
		"where `value` comes from the preceded literal.\n"
		"\n"
		"An error occurs if the same suffix symbol has already been assigned.\n"
		"Specifying `:overwrite` attribute will forcibly overwrite an existing assignment.\n");
}

Gura_ImplementMethod(suffixmgr, assign)
{
	Signal &sig = env.GetSignal();
	SuffixMgr &suffixMgr = Object_suffixmgr::GetObjectThis(arg)->GetSuffixMgr();
	const Function *pFuncBlock = arg.GetBlockFunc(env, GetSymbolForBlock());
	if (pFuncBlock == nullptr) return Value::Nil;
	const Symbol *pSymbol = arg.GetSymbol(0);
	if (!arg.IsSet(Gura_Symbol(overwrite)) && suffixMgr.Lookup(pSymbol) != nullptr) {
		sig.SetError(ERR_ValueError, "suffix '%s' has already been assigned", pSymbol->GetName());
		return Value::Nil;
	}
	SuffixMgrEntryCustom *pSuffixMgrEntry =
					new SuffixMgrEntryCustom(Function::Reference(pFuncBlock));
	suffixMgr.Assign(pSymbol, pSuffixMgrEntry);
	return Value::Nil;
}

//-----------------------------------------------------------------------------
// Implementation of class
//-----------------------------------------------------------------------------
Class_suffixmgr::Class_suffixmgr(Environment *pEnvOuter) : Class(pEnvOuter, VTYPE_suffixmgr)
{

}

void Class_suffixmgr::Prepare(Environment &env)
{
	Gura_AssignFunction(suffixmgr);
	Gura_AssignMethod(suffixmgr, assign);
	// help document
	AddHelpTemplate(env, Gura_Symbol(en), helpDoc_en + 1);
}

}
