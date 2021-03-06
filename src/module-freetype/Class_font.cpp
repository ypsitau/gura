#include "stdafx.h"

Gura_BeginModuleScope(freetype)

//-----------------------------------------------------------------------------
// Object_font implementation
//-----------------------------------------------------------------------------
Object_font::Object_font(Object_Face *pObjFace, Object_color *pObjColor) :
		Object(Gura_UserClass(font)), _pObjFace(pObjFace), _pObjColor(pObjColor)
{
	ClearDeco();
}

Object *Object_font::Clone() const
{
	return nullptr; //new Object_font(*this);
}

String Object_font::ToString(bool exprFlag)
{
	String str;
	str = "<freetype.font:";
	str += _pObjFace->ToString(false);
	str += ">";
	return str;
}

void Object_font::ClearDeco()
{
	_pObjColor->SetColor(Color::black);
	_mode = MODE_Blend;
	_width = 0, _height = 0; // default value is used when _height == 0.
	_strength = 0.;
	_slant = 0.;
	_rotate.deg = 0.;
	_rotate.cosNum = 1., _rotate.sinNum = 0.;
}

bool Object_font::CalcSize(Environment &env, const String &str,
					size_t &width, size_t &height, const Function *pFuncDeco)
{
	Signal &sig = env.GetSignal();
	int xShifted = 0, yShifted = 0;
	String::const_iterator p = str.begin();
	int xMin = 0, xMax = 0, yMin = 0, yMax = 0;
	size_t idx = 0;
	do {
		UInt32 codeUTF32;
		p = Gura::NextUTF32(str, p, codeUTF32);
		if (codeUTF32 == 0x00000000) break;
		if (LoadAndDecorateChar(env, sig, codeUTF32, idx, pFuncDeco) != 0) continue;
		FT_GlyphSlot glyphSlot = GetFace()->glyph;
		FT_Bitmap &bitmap = glyphSlot->bitmap;
		int xLeft = (xShifted >> 6) + glyphSlot->bitmap_left;
		int yTop = (yShifted >> 6)  - glyphSlot->bitmap_top;
		int xRight = xLeft + bitmap.width;
		int yBottom = yTop + bitmap.rows;
		if (xMin > xLeft) xMin = xLeft;
		if (xMax < xRight) xMax = xRight;
		if (yMin > yTop) yMin = yTop;
		if (yMax < yBottom) yMax = yBottom;
		xShifted += glyphSlot->advance.x;	// 26.6 fixed float
		yShifted += glyphSlot->advance.y;	// 26.6 fixed float
		idx++;
	} while (p != str.end());
	width = xMax - xMin, height = yMax - yMin;
	return true;
}

bool Object_font::DrawOnImage(Environment &env, Signal &sig, Image *pImage,
				int x, int y, const String &str, const Function *pFuncDeco)
{
	const Color &color = _pObjColor->GetColor();
	unsigned long redFg = color.GetR();
	unsigned long greenFg = color.GetG();
	unsigned long blueFg = color.GetB();
	String::const_iterator p = str.begin();
	int xShifted = x << 6, yShifted = y << 6;
	size_t idx = 0;
	do {
		UInt32 codeUTF32;
		p = Gura::NextUTF32(str, p, codeUTF32);
		if (codeUTF32 == 0x00000000) break;
		if (LoadAndDecorateChar(env, sig, codeUTF32, idx, pFuncDeco) != 0) continue;
		FT_GlyphSlot glyphSlot = GetFace()->glyph;
		if (glyphSlot->format == FT_GLYPH_FORMAT_BITMAP) {
			FT_Bitmap &bitmap = glyphSlot->bitmap;
			int xOrg = (xShifted >> 6) + glyphSlot->bitmap_left;
			int yOrg = (yShifted >> 6) - glyphSlot->bitmap_top;
			int xAdj = xOrg, yAdj = yOrg;
			int width = bitmap.width;
			int height = bitmap.rows;
			if (bitmap.buffer == nullptr) {
				// nothing to do
			} else if (!pImage->AdjustCoord(xAdj, yAdj, width, height)) {
				// nothing to do
			} else if (bitmap.pixel_mode == FT_PIXEL_MODE_MONO) {
				DrawMonoOnImage(pImage, xAdj, yAdj, bitmap.buffer,
							width, height, bitmap.pitch, xAdj - xOrg, yAdj - yOrg);
			} else if (bitmap.pixel_mode == FT_PIXEL_MODE_GRAY) {
				DrawGrayOnImage(pImage, xAdj, yAdj, bitmap.buffer,
							width, height, bitmap.pitch, xAdj - xOrg, yAdj - yOrg);
			}
		}
		xShifted += glyphSlot->advance.x;	// 26.6 fixed float
		yShifted += glyphSlot->advance.y;	// 26.6 fixed float
		idx++;
	} while (p != str.end());
	return true;
}

FT_Error Object_font::LoadAndDecorateChar(Environment &env, Signal &sig,
			UInt32 codeUTF32, size_t idx, const Function *pFuncDeco)
{
	bool transformFlag = (pFuncDeco != nullptr);
	FT_Matrix matrix;	// 16.16 fixed float
	matrix.xx = 1 << 16;
	matrix.xy = 0 << 16;
	matrix.yx = 0 << 16;
	matrix.yy = 1 << 16;
	// slanting the font
	if (_slant != 0.) {
		transformFlag = true;
		matrix.xy = static_cast<FT_Fixed>(_slant * (1 << 16));
	}
	// rotating the font
	if (_rotate.deg != 0.) {
		transformFlag = true;
		FT_Matrix matRot;
		int cos16 = static_cast<int>(_rotate.cosNum * (1 << 16));
		int sin16 = static_cast<int>(_rotate.sinNum * (1 << 16));
		matRot.xx = cos16;
		matRot.xy = -sin16;
		matRot.yx = sin16;
		matRot.yy = cos16;
		::FT_Matrix_Multiply(&matRot, &matrix);
	}
	if (_height != 0) {
		FT_Error err = ::FT_Set_Pixel_Sizes(GetFace(),
					static_cast<FT_UInt>(_width), static_cast<FT_UInt>(_height));
		if (err != 0) return err;
	}
	// FT_Load_Char calls FT_Get_Char_Index and FT_Load_Glypy internally.
	if (pFuncDeco == nullptr) {
		FT_Error err = ::FT_Load_Char(GetFace(), codeUTF32,
					FT_LOAD_DEFAULT | (transformFlag? FT_LOAD_NO_BITMAP : 0));
		if (err != 0) return err;
	} else {
		AutoPtr<Argument> pArg(new Argument(pFuncDeco));
		if (!pArg->StoreValue(env, Value(codeUTF32), Value(idx))) return FT_Err_Syntax_Error;
		pFuncDeco->Eval(env, *pArg);
	}
	FT_GlyphSlot glyphSlot = GetFace()->glyph;
	if (_strength == 0.) {
		// nothing to do
	} else if (glyphSlot->format == FT_GLYPH_FORMAT_NONE) {
		// nothing to do
	} else if (glyphSlot->format == FT_GLYPH_FORMAT_COMPOSITE) {
		// nothing to do
	} else if (glyphSlot->format == FT_GLYPH_FORMAT_BITMAP) {
		FT_Pos xStrength = static_cast<FT_Pos>(_strength * (1 << 6)); // 26.6 fixed float
		FT_Pos yStrength = 0;
		FT_Error err = ::FT_Bitmap_Embolden(g_lib, &glyphSlot->bitmap, xStrength, yStrength);
		if (err != 0) return err;
	} else if (glyphSlot->format == FT_GLYPH_FORMAT_OUTLINE) {
		FT_Pos strength = static_cast<FT_Pos>(_strength * (1 << 6)); // 26.6 fixed float
		FT_Error err = ::FT_Outline_Embolden(&glyphSlot->outline, strength);
		if (err != 0) return err;
	} else if (glyphSlot->format == FT_GLYPH_FORMAT_PLOTTER) {
		// nothing to do
	}
	if (glyphSlot->format == FT_GLYPH_FORMAT_NONE) {
		// nothing to do
	} else if (glyphSlot->format == FT_GLYPH_FORMAT_COMPOSITE) {
		// nothing to do
	} else if (glyphSlot->format == FT_GLYPH_FORMAT_BITMAP) {
		// nothing to do
	} else if (glyphSlot->format == FT_GLYPH_FORMAT_OUTLINE) {
		if (transformFlag) {
			::FT_Outline_Transform(&glyphSlot->outline, &matrix);
		}
		// convert outline to bitmap
		FT_Error err = ::FT_Render_Glyph(glyphSlot, FT_RENDER_MODE_NORMAL);
		if (err != 0) return err;
		if (_rotate.deg != 0.) {
			double cosNum = _rotate.cosNum;
			double sinNum = -_rotate.sinNum;
			FT_Pos x = glyphSlot->advance.x;
			FT_Pos y = glyphSlot->advance.y;
			glyphSlot->advance.x = static_cast<FT_Pos>(cosNum * x - sinNum * y);
			glyphSlot->advance.y = static_cast<FT_Pos>(sinNum * x + cosNum * y);
		}
	} else if (glyphSlot->format == FT_GLYPH_FORMAT_PLOTTER) {
		// nothing to do
	}
	return 0;
}

void Object_font::DrawMonoOnImage(Image *pImage, int x, int y,
				unsigned char *buffer, int width, int height, int pitch,
				int xOffset, int yOffset)
{
	const Color &color = _pObjColor->GetColor();
	unsigned char red = color.GetR();
	unsigned char green = color.GetG();
	unsigned char blue = color.GetB();
	std::unique_ptr<Image::Scanner>
				pScanner(pImage->CreateScanner(x, y, width, height));
	int bitOffset = xOffset % 8;
	unsigned char mask = 1 << (7 - bitOffset);
	const unsigned char *pLine = buffer + (xOffset / 8) + yOffset * pitch;
	const unsigned char *pPixel = pLine;
	bool alphaFlag = (pImage->GetFormat() == Image::FORMAT_RGBA);
	for (;;) {
		if (!(*pPixel & mask)) {
			// nothing to do
		} else if (alphaFlag) {
			pScanner->StorePixel(red, green, blue, 255);
		} else {
			pScanner->StorePixel(red, green, blue);
		}
		if (pScanner->NextPixel()) {
			mask >>= 1;
			if (mask == 0x00) {
				mask = 1 << 7;
				pPixel++;
			}
		} else if (pScanner->NextLine()) {
			pLine += pitch;
			pPixel = pLine;
			mask = 1 << (7 - bitOffset);
		} else {
			break;
		}
	}
}

void Object_font::DrawGrayOnImage(Image *pImage, int x, int y,
				unsigned char *buffer, int width, int height, int pitch,
				int xOffset, int yOffset)
{
	const Color &color = _pObjColor->GetColor();
	unsigned long redFg = color.GetR();
	unsigned long greenFg = color.GetG();
	unsigned long blueFg = color.GetB();
	std::unique_ptr<Image::Scanner>
				pScanner(pImage->CreateScanner(x, y, width, height));
	const unsigned char *pLine = buffer + xOffset + yOffset * pitch;
	const unsigned char *pPixel = pLine;
	bool alphaFlag = (pImage->GetFormat() == Image::FORMAT_RGBA);
	for (;;) {
		if (_mode == MODE_Alpha) {
			if (alphaFlag) {
				if (pScanner->GetA() < *pPixel) {
					pScanner->StorePixel(
						static_cast<unsigned char>(redFg),
						static_cast<unsigned char>(greenFg),
						static_cast<unsigned char>(blueFg),
						*pPixel);
				}
			} else {
				pScanner->StorePixel(
						static_cast<unsigned char>(redFg),
						static_cast<unsigned char>(greenFg),
						static_cast<unsigned char>(blueFg));
			}
		} else { // _mode == MODE_Blend;
			unsigned long ratioFg = *pPixel;
			unsigned long ratioBg = 255 - ratioFg;
			unsigned long redBg = pScanner->GetR();
			unsigned long greenBg = pScanner->GetG();
			unsigned long blueBg = pScanner->GetB();
			unsigned long red = redFg * ratioFg + redBg * ratioBg;
			unsigned long green = greenFg * ratioFg + greenBg * ratioBg;
			unsigned long blue = blueFg * ratioFg + blueBg * ratioBg;
			red /= 255, green /= 255, blue /= 255;
			if (alphaFlag) {
				pScanner->StorePixel(
						static_cast<unsigned char>(red),
						static_cast<unsigned char>(green),
						static_cast<unsigned char>(blue), 255);
			} else {
				pScanner->StorePixel(
						static_cast<unsigned char>(red),
						static_cast<unsigned char>(green),
						static_cast<unsigned char>(blue));
			}
		}
		if (pScanner->NextPixel()) {
			pPixel++;
		} else if (pScanner->NextLine()) {
			pLine += pitch;
			pPixel = pLine;
		} else {
			break;
		}
	}
}

//-----------------------------------------------------------------------------
// Implementation of properties
//-----------------------------------------------------------------------------
// freetype.font#color
Gura_DeclareProperty_RW(font, color)
{
	SetPropAttr(VTYPE_color);
	AddHelp(
		Gura_Symbol(en),
		""
		);
}

Gura_ImplementPropertyGetter(font, color)
{
	Object_font *pObjThis = Object_font::GetObject(valueThis);
	return Value(Object_color::Reference(pObjThis->GetObjColor()));
}

Gura_ImplementPropertySetter(font, color)
{
	Object_font *pObjThis = Object_font::GetObject(valueThis);
	pObjThis->GetObjColor()->SetColor(Object_color::GetObject(value)->GetColor());
	return Value(Object_color::Reference(pObjThis->GetObjColor()));
}

// freetype.font#face
Gura_DeclareProperty_R(font, face)
{
	SetPropAttr(VTYPE_Face);
	AddHelp(
		Gura_Symbol(en),
		""
		);
}

Gura_ImplementPropertyGetter(font, face)
{
	Object_font *pObjThis = Object_font::GetObject(valueThis);
	return Value(Object_Face::Reference(pObjThis->GetObjFace()));
}

// freetype.font#height
Gura_DeclareProperty_RW(font, height)
{
	SetPropAttr(VTYPE_number);
	AddHelp(
		Gura_Symbol(en),
		""
		);
}

Gura_ImplementPropertyGetter(font, height)
{
	Object_font *pObjThis = Object_font::GetObject(valueThis);
	return Value(pObjThis->GetHeight());
}

Gura_ImplementPropertySetter(font, height)
{
	Object_font *pObjThis = Object_font::GetObject(valueThis);
	pObjThis->SetHeight(value.GetDouble());
	return Value(pObjThis->GetHeight());
}

// freetype.font#mode
Gura_DeclareProperty_RW(font, mode)
{
	SetPropAttr(VTYPE_symbol);
	AddHelp(
		Gura_Symbol(en),
		""
		);
}

Gura_ImplementPropertyGetter(font, mode)
{
	Object_font *pObjThis = Object_font::GetObject(valueThis);
	Object_font::Mode mode = pObjThis->GetMode();
	const Symbol *pSymbol =
		(mode == Object_font::MODE_Blend)? Gura_UserSymbol(blend) :
		(mode == Object_font::MODE_Alpha)? Gura_UserSymbol(alpha) :
		Gura_UserSymbol(blend);
	return Value(pSymbol);
}

Gura_ImplementPropertySetter(font, mode)
{
	Object_font *pObjThis = Object_font::GetObject(valueThis);
	const Symbol *pSymbolVal = value.GetSymbol();
	if (pSymbolVal->IsIdentical(Gura_UserSymbol(blend))) {
		pObjThis->SetMode(Object_font::MODE_Blend);
	} else if (pSymbolVal->IsIdentical(Gura_UserSymbol(alpha))) {
		pObjThis->SetMode(Object_font::MODE_Alpha);
	} else {
		env.SetError(ERR_ValueError, "symbol must be `blend or `alpha");
		return Value::Nil;
	}
	return Value(pSymbolVal);
}

// freetype.font#rotate
Gura_DeclareProperty_RW(font, rotate)
{
	SetPropAttr(VTYPE_number);
	AddHelp(
		Gura_Symbol(en),
		""
		);
}

Gura_ImplementPropertyGetter(font, rotate)
{
	Object_font *pObjThis = Object_font::GetObject(valueThis);
	return Value(pObjThis->GetRotate());
}

Gura_ImplementPropertySetter(font, rotate)
{
	Object_font *pObjThis = Object_font::GetObject(valueThis);
	pObjThis->SetRotate(value.GetDouble());
	return Value(pObjThis->GetRotate());
}

// freetype.font#slant
Gura_DeclareProperty_RW(font, slant)
{
	SetPropAttr(VTYPE_number);
	AddHelp(
		Gura_Symbol(en),
		""
		);
}

Gura_ImplementPropertyGetter(font, slant)
{
	Object_font *pObjThis = Object_font::GetObject(valueThis);
	return Value(pObjThis->GetSlant());
}

Gura_ImplementPropertySetter(font, slant)
{
	Object_font *pObjThis = Object_font::GetObject(valueThis);
	pObjThis->SetSlant(value.GetDouble());
	return Value(pObjThis->GetSlant());
}

// freetype.font#strength
Gura_DeclareProperty_RW(font, strength)
{
	SetPropAttr(VTYPE_number);
	AddHelp(
		Gura_Symbol(en),
		""
		);
}

Gura_ImplementPropertyGetter(font, strength)
{
	Object_font *pObjThis = Object_font::GetObject(valueThis);
	return Value(pObjThis->GetStrength());
}

Gura_ImplementPropertySetter(font, strength)
{
	Object_font *pObjThis = Object_font::GetObject(valueThis);
	pObjThis->SetStrength(value.GetDouble());
	return Value(pObjThis->GetStrength());
}

// freetype.font#width
Gura_DeclareProperty_RW(font, width)
{
	SetPropAttr(VTYPE_number);
	AddHelp(
		Gura_Symbol(en),
		""
		);
}

Gura_ImplementPropertyGetter(font, width)
{
	Object_font *pObjThis = Object_font::GetObject(valueThis);
	return Value(pObjThis->GetWidth());
}

Gura_ImplementPropertySetter(font, width)
{
	Object_font *pObjThis = Object_font::GetObject(valueThis);
	pObjThis->SetWidth(value.GetDouble());
	return Value(pObjThis->GetWidth());
}

//-----------------------------------------------------------------------------
// Gura interfaces for freetype.font
//-----------------------------------------------------------------------------
// freetype.font(face:freetype.Face):map {block?}
Gura_DeclareFunction(font)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "face", VTYPE_Face);
	SetClassToConstruct(Gura_UserClass(font));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(font)
{
	Object_Face *pObjFace = Object_Face::GetObject(arg, 0);
	AutoPtr<Object_font> pObjFont(
		new Object_font(Object_Face::Reference(pObjFace), new Object_color(env)));
	return ReturnValue(env, arg, Value(pObjFont.release()));
}

// freetype.font#cleardeco()
Gura_DeclareMethod(font, cleardeco)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Reduce, FLAG_None);
}

Gura_ImplementMethod(font, cleardeco)
{
	Object_font *pThis = Object_font::GetObjectThis(arg);
	pThis->ClearDeco();
	return arg.GetValueThis();
}

// freetype.font#drawtext(image:image, x:number, y:number, str:string):map:reduce {block?}
Gura_DeclareMethod(font, drawtext)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Reduce, FLAG_Map);
	DeclareArg(env, "image", VTYPE_image);
	DeclareArg(env, "x", VTYPE_number);
	DeclareArg(env, "y", VTYPE_number);
	DeclareArg(env, "str", VTYPE_string);
	DeclareBlock(OCCUR_ZeroOrOnce);
	AddHelp(Gura_Symbol(en), "Draws a text on the image.");
}

Gura_ImplementMethod(font, drawtext)
{
	Signal &sig = env.GetSignal();
	Object_font *pThis = Object_font::GetObjectThis(arg);
	Image *pImage = Object_image::GetObject(arg, 0)->GetImage();
	int x = arg.GetInt(1);
	int y = arg.GetInt(2);
	String str = arg.GetStringSTL(3);
	const Function *pFuncDeco = nullptr;
	if (arg.IsBlockSpecified()) {
		pFuncDeco = arg.GetBlockFunc(env, GetSymbolForBlock());
		if (pFuncDeco == nullptr) return Value::Nil;
	}
	if (pThis->DrawOnImage(env, sig, pImage, x, y, str, pFuncDeco)) return Value::Nil;
	return arg.GetValueThis();
}

// freetype.font#calcsize(str:string):map
Gura_DeclareMethod(font, calcsize)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "str", VTYPE_string);
}

Gura_ImplementMethod(font, calcsize)
{
	const Function *pFuncDeco = nullptr;
	Object_font *pThis = Object_font::GetObjectThis(arg);
	String str = arg.GetStringSTL(0);
	size_t width, height;
	if (!pThis->CalcSize(env, str, width, height, pFuncDeco)) return Value::Nil;
	return Value::CreateList(env, 
			Value(static_cast<unsigned int>(width)),
			Value(static_cast<unsigned int>(height)));
}

// freetype.font#calcbbox(x:number, y:number, str:string):map
Gura_DeclareMethod(font, calcbbox)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "x", VTYPE_number);
	DeclareArg(env, "y", VTYPE_number);
	DeclareArg(env, "str", VTYPE_string);
}

// ******************* still buggy
Gura_ImplementMethod(font, calcbbox)
{
	const Function *pFuncDeco = nullptr;
	Object_font *pThis = Object_font::GetObjectThis(arg);
	int x = arg.GetInt(0);
	int y = arg.GetInt(1);
	String str = arg.GetStringSTL(2);
	size_t width, height;
	if (!pThis->CalcSize(env, str, width, height, pFuncDeco)) return Value::Nil;
	return Value::CreateList(env,
			Value(x), Value(y - pThis->GetFace()->ascender / 4),
			Value(width), Value(height));
}

// implementation of class font
Gura_ImplementUserClass(font)
{
	// Assignment of properties
	Gura_AssignProperty(font, color);
	Gura_AssignProperty(font, face);
	Gura_AssignProperty(font, height);
	Gura_AssignProperty(font, mode);
	Gura_AssignProperty(font, rotate);
	Gura_AssignProperty(font, slant);
	Gura_AssignProperty(font, strength);
	Gura_AssignProperty(font, width);
	// Assignment of function
	Gura_AssignFunction(font);
	// Assignment of methods
	Gura_AssignMethod(font, cleardeco);
	Gura_AssignMethod(font, drawtext);
	Gura_AssignMethod(font, calcsize);
	Gura_AssignMethod(font, calcbbox);
}

Gura_EndModuleScope(freetype)
