#include "stdafx.h"

Gura_BeginModule(freetype)

//-----------------------------------------------------------------------------
// Object_GlyphSlot implementation
//-----------------------------------------------------------------------------
Object *Object_GlyphSlot::Clone() const
{
	return NULL;
}

String Object_GlyphSlot::ToString(Signal sig, bool exprFlag)
{
	char buff[80];
	::sprintf(buff, "<freetype.GlyphSlot>");
	return String(buff);
}

bool Object_GlyphSlot::DoDirProp(Environment &env, Signal sig, SymbolSet &symbols)
{
	if (!Object::DoDirProp(env, sig, symbols)) return false;
	symbols.insert(Gura_UserSymbol(bitmap));
	return true;
}

Value Object_GlyphSlot::DoGetProp(Environment &env, Signal sig, const Symbol *pSymbol,
						const SymbolSet &attrs, bool &evaluatedFlag)
{
	evaluatedFlag = true;
	if (pSymbol->IsIdentical(Gura_UserSymbol(bitmap))) {
		AutoPtr<Object_Bitmap> pObj(new Object_Bitmap(
								Object::Reference(this), &_glyphSlot->bitmap));
		return Value(pObj.release());
	}
	evaluatedFlag = false;
	return Value::Null;
}

Value Object_GlyphSlot::DoSetProp(Environment &env, Signal sig, const Symbol *pSymbol, const Value &value,
							const SymbolSet &attrs, bool &evaluatedFlag)
{
	evaluatedFlag = true;
#if 0
	if (pSymbol->IsIdentical(Gura_Symbol(x))) {
		if (!value.MustBeNumber(sig)) return Value::Null;
		_vector.x = static_cast<FT_Pos>(value.GetLong());
		return Value(_vector.x);
	} else if (pSymbol->IsIdentical(Gura_Symbol(y))) {
		if (!value.MustBeNumber(sig)) return Value::Null;
		_vector.y = static_cast<FT_Pos>(value.GetLong());
		return Value(_vector.y);
	}
#endif
	evaluatedFlag = false;
	return Value::Null;
}

//-----------------------------------------------------------------------------
// Gura interfaces for freetype.GlyphSlot
//-----------------------------------------------------------------------------
// freetype.GlyphSlot#Render(render_mode:number):reduce
Gura_DeclareMethod(GlyphSlot, Render)
{
	SetMode(RSLTMODE_Reduce, FLAG_None);
	DeclareArg(env, "render_mode", VTYPE_number);
}

Gura_ImplementMethod(GlyphSlot, Render)
{
	FT_GlyphSlot glyphSlot = Object_GlyphSlot::GetThisObj(args)->GetEntity();
	FT_Render_Mode render_mode = static_cast<FT_Render_Mode>(args.GetInt(0));
	FT_Error err = ::FT_Render_Glyph(glyphSlot, render_mode);
	if (err != 0) {
		SetError_Freetype(sig, err);
		return Value::Null;
	}
	return args.GetThis();
}

//-----------------------------------------------------------------------------
// Class implementation for freetype.GlyphSlot
//-----------------------------------------------------------------------------
Gura_ImplementUserClass(GlyphSlot)
{
	Gura_AssignMethod(GlyphSlot, Render);
}

}}
