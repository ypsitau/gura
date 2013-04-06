#ifndef __GURA_OBJECT_PALETTE_H__
#define __GURA_OBJECT_PALETTE_H__

#include "Object.h"

namespace Gura {

//-----------------------------------------------------------------------------
// Class_palette
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE Class_palette : public Class {
public:
	Class_palette(Environment *pEnvOuter);
	virtual bool CastFrom(Environment &env, Signal sig, Value &value, const Declaration *pDecl);
	virtual Object *CreateDescendant(Environment &env, Signal sig, Class *pClass);
	static void OnModuleEntry(Environment &env, Signal sig);
};

//-----------------------------------------------------------------------------
// Object_palette
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE Object_palette : public Object {
public:
	Gura_DeclareObjectAccessor(palette)
private:
	AutoPtr<Palette> _pPalette;
public:
	inline Object_palette(Class *pClass, Palette *pPalette) :
				Object(pClass), _pPalette(pPalette) {}
	inline Object_palette(Environment &env, Palette *pPalette) :
				Object(env.LookupClass(VTYPE_palette)), _pPalette(pPalette) {}
	Object_palette(const Object_palette &obj);
	virtual ~Object_palette();
	virtual Object *Clone() const;
	virtual String ToString(Signal sig, bool exprFlag);
	virtual Iterator *CreateIterator(Signal sig);
	virtual Value IndexGet(Environment &env, Signal sig, const Value &valueIdx);
	virtual void IndexSet(Environment &env, Signal sig, const Value &valueIdx, const Value &value);
	inline Palette *GetPalette() { return _pPalette.get(); }
	inline const Palette *GetPalette() const { return _pPalette.get(); }
};

}

#endif
