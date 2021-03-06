//=============================================================================
// Gura class: pointer
//=============================================================================
#ifndef __GURA_CLASS_POINTER_H__
#define __GURA_CLASS_POINTER_H__

#include "Class_binary.h"
#include "Pointer.h"

namespace Gura {

//-----------------------------------------------------------------------------
// Class_pointer
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE Class_pointer : public ClassFundamental {
public:
	Class_pointer(Environment *pEnvOuter);
	virtual void DoPrepare(Environment &env);
	virtual bool CastFrom(Environment &env, Value &value, ULong flags);
	virtual Object *CreateDescendant(Environment &env, Class *pClass);
};

//-----------------------------------------------------------------------------
// Object_pointer
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE Object_pointer : public Object {
public:
	Gura_DeclareObjectAccessor(pointer)
private:
	AutoPtr<Pointer> _pPointer;
public:
	inline Object_pointer(Class *pClass, Pointer *pPointer) : Object(pClass), _pPointer(pPointer) {}
	inline Object_pointer(Environment &env, Pointer *pPointer) :
		Object(env.LookupClass(VTYPE_pointer)), _pPointer(pPointer) {}
	inline Object_pointer(const Object_pointer &obj) :
		Object(obj), _pPointer(obj.GetPointer()->Clone()) {}
	virtual ~Object_pointer();
	virtual Object *Clone() const;
	virtual String ToString(bool exprFlag);
	inline Pointer *GetPointer() const { return _pPointer.get(); }
};

}

#endif
