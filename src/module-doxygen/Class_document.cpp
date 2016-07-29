//=============================================================================
// Class_document.cpp
//=============================================================================
#include "stdafx.h"

Gura_BeginModuleScope(doxygen)

//-----------------------------------------------------------------------------
// Object_document
//-----------------------------------------------------------------------------
Object_document::~Object_document()
{
}

Object *Object_document::Clone() const
{
	return nullptr;
}

bool Object_document::DoDirProp(Environment &env, SymbolSet &symbols)
{
	Signal &sig = GetSignal();
	if (!Object::DoDirProp(env, symbols)) return false;
	return true;
}

Value Object_document::DoGetProp(Environment &env, const Symbol *pSymbol,
							const SymbolSet &attrs, bool &evaluatedFlag)
{
	evaluatedFlag = false;
	return Value::Nil;
}

String Object_document::ToString(bool exprFlag)
{
	String rtn;
	rtn += "<doxygen.document:";
	if (_pDocument.IsNull()) {
		rtn += "invalid";
	} else {
		char buff[32];
		rtn += _pDocument->GetSourceName();
		::sprintf(buff, ":%ldstructures", _pDocument->GetStructureOwner().size());
		rtn += buff;
	}
	rtn += ">";
	return rtn;
}

//----------------------------------------------------------------------------
// Constructor
//----------------------------------------------------------------------------
// doxygen.document(stream?:stream, aliases?:doxygen.aliases, extracted?:boolean):[] {block?}
Gura_DeclareFunction(document)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "stream", VTYPE_stream, OCCUR_ZeroOrOnce);
	DeclareArg(env, "aliases", VTYPE_aliases, OCCUR_ZeroOrOnce);
	DeclareArg(env, "extracted", VTYPE_boolean, OCCUR_ZeroOrOnce);
	SetClassToConstruct(Gura_UserClass(document));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(document)
{
	AutoPtr<Object_document> pObj(new Object_document());
	if (arg.IsValid(0)) {
		AutoPtr<Document> pDocument(new Document());
		Stream &stream = arg.GetStream(0);
		const Aliases *pAliases = arg.IsValid(1)?
			Object_aliases::GetObject(arg, 1)->GetAliases() : nullptr;
		bool extractedFlag = arg.IsValid(2) && arg.GetBoolean(2);
		if (!pDocument->ReadStream(env, stream, pAliases, extractedFlag)) return Value::Nil;
		pObj->SetDocument(pDocument.release());
	}
	return ReturnValue(env, arg, Value(pObj.release()));
}

//----------------------------------------------------------------------------
// Methods
//----------------------------------------------------------------------------
// doxygen.document#structures() {block?}
Gura_DeclareMethod(document, structures)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareBlock(OCCUR_ZeroOrOnce);
	AddHelp(
		Gura_Symbol(en), Help::FMT_markdown,
		"");
}

Gura_ImplementMethod(document, structures)
{
	const Document *pDocument = Object_document::GetObjectThis(arg)->GetDocument();
	AutoPtr<Iterator> pIterator(
		new Iterator_Structure(pDocument->GetStructureOwner().Reference()));
	return ReturnIterator(env, arg, pIterator.release());
}

//-----------------------------------------------------------------------------
// Class implementation for doxygen.document
//-----------------------------------------------------------------------------
Gura_ImplementUserClass(document)
{
	Gura_AssignFunction(document);
	Gura_AssignMethod(document, structures);
}

Gura_EndModuleScope(doxygen)
