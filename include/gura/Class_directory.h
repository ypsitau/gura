//=============================================================================
// Gura class: directory
//=============================================================================
#ifndef __GURA_CLASS_DIRECTORY_H__
#define __GURA_CLASS_DIRECTORY_H__

#include "Class.h"
#include "Directory.h"

namespace Gura {

//-----------------------------------------------------------------------------
// Class_directory
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE Class_directory : public ClassFundamental {
public:
	Class_directory(Environment *pEnvOuter);
	virtual void DoPrepare(Environment &env);
	virtual bool CastFrom(Environment &env, Value &value, ULong flags);
	virtual Object *CreateDescendant(Environment &env, Class *pClass);
};

//-----------------------------------------------------------------------------
// Object_directory
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE Object_directory : public Object {
public:
	Gura_DeclareObjectAccessor(directory)
protected:
	AutoPtr<Directory> _pDirectory;
public:
	inline Object_directory(Environment &env, Directory *pDirectory) :
						Object(env.LookupClass(VTYPE_directory)), _pDirectory(pDirectory) {}
	inline Object_directory(Class *pClass, Directory *pDirectory) :
						Object(pClass), _pDirectory(pDirectory) {}
	inline Directory *GetDirectory() { return _pDirectory.get(); }
	virtual String ToString(bool exprFlag);
};

}

#endif
