#ifndef __CAIRO_CLASS_WIN32_FONT_FACE_H__
#define __CAIRO_CLASS_WIN32_FONT_FACE_H__

Gura_BeginModuleScope(cairo)

//-----------------------------------------------------------------------------
// Object_win32_font_face declaration
//-----------------------------------------------------------------------------
Gura_DeclareUserClass(win32_font_face);

class Object_win32_font_face : public Object_font_face {
public:
	Gura_DeclareObjectAccessor(win32_font_face)
public:
	inline Object_win32_font_face(cairo_font_face_t *font_face) :
										Object_font_face(font_face) {}
	virtual String ToString(bool exprFlag);
};

Gura_EndModuleScope(cairo)

#endif
