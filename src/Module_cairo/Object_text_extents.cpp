#include "stdafx.h"

Gura_BeginModule(cairo)

//-----------------------------------------------------------------------------
// Object_text_extents implementation
//-----------------------------------------------------------------------------
Object_text_extents::~Object_text_extents()
{
}

Object *Object_text_extents::Clone() const
{
	return NULL;
}

bool Object_text_extents::DoDirProp(Signal sig, SymbolSet &symbols)
{
	if (!Object::DoDirProp(sig, symbols)) return false;
	symbols.insert(Gura_UserSymbol(x_bearing));
	symbols.insert(Gura_UserSymbol(y_bearing));
	symbols.insert(Gura_UserSymbol(width));
	symbols.insert(Gura_UserSymbol(height));
	symbols.insert(Gura_UserSymbol(x_advance));
	symbols.insert(Gura_UserSymbol(y_advance));
	return true;
}

Value Object_text_extents::DoGetProp(Signal sig, const Symbol *pSymbol, bool &evaluatedFlag)
{
	evaluatedFlag = true;
	if (pSymbol->IsIdentical(Gura_UserSymbol(x_bearing))) {
		return Value(_text_extents.x_bearing);
	} else if (pSymbol->IsIdentical(Gura_UserSymbol(y_bearing))) {
		return Value(_text_extents.y_bearing);
	} else if (pSymbol->IsIdentical(Gura_UserSymbol(width))) {
		return Value(_text_extents.width);
	} else if (pSymbol->IsIdentical(Gura_UserSymbol(height))) {
		return Value(_text_extents.height);
	} else if (pSymbol->IsIdentical(Gura_UserSymbol(x_advance))) {
		return Value(_text_extents.x_advance);
	} else if (pSymbol->IsIdentical(Gura_UserSymbol(y_advance))) {
		return Value(_text_extents.y_advance);
	}
	evaluatedFlag = false;
	return Value::Null;
}

String Object_text_extents::ToString(Signal sig, bool exprFlag)
{
	return String("<cairo.text_extents>");
}

//-----------------------------------------------------------------------------
// Gura interfaces for text_extents
//-----------------------------------------------------------------------------
// implementation of class text_extents
Gura_ImplementUserClass(text_extents)
{
}

}}
