#ifndef __CAIRO_CLASS_SCALED_FONT_H__
#define __CAIRO_CLASS_SCALED_FONT_H__

Gura_BeginModuleScope(cairo)

//-----------------------------------------------------------------------------
// Object_scaled_font declaration
//-----------------------------------------------------------------------------
Gura_DeclareUserClass(scaled_font);

class Object_scaled_font : public Object {
private:
	cairo_scaled_font_t *_scaled_font;
public:
	Gura_DeclareObjectAccessor(scaled_font)
public:
	inline Object_scaled_font(cairo_scaled_font_t *scaled_font) :
					Object(Gura_UserClass(scaled_font)), _scaled_font(scaled_font) {}
	virtual ~Object_scaled_font();
	virtual Object *Clone() const;
	virtual String ToString(bool exprFlag);
	inline cairo_scaled_font_t *GetEntity() { return _scaled_font; }
};

Gura_EndModuleScope(cairo)

#endif
