//=============================================================================
// Gura class: formatter
//=============================================================================
#ifndef __GURA_CLASS_FORMATTER_H__
#define __GURA_CLASS_FORMATTER_H__

#include "Class.h"
#include "Environment.h"

namespace Gura {

//-----------------------------------------------------------------------------
// Class_formatter
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE Class_formatter : public ClassFundamental {
public:
	Class_formatter(Environment *pEnvOuter);
	virtual void DoPrepare(Environment &env);
	virtual Object *CreateDescendant(Environment &env, Class *pClass);
};

//-----------------------------------------------------------------------------
// Object_formatter
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE Object_formatter : public Object {
public:
	Gura_DeclareObjectAccessor(formatter)
private:
	Formatter::Flags _flags;
public:
	inline Object_formatter(Class *pClass, const Formatter::Flags &flags) :
				Object(pClass), _flags(flags) {}
	inline Object_formatter(Environment &env, const Formatter::Flags &flags) :
				Object(env.LookupClass(VTYPE_formatter)), _flags(flags) {}
	Object_formatter(const Object_formatter &obj);
	virtual ~Object_formatter();
	virtual Object *Clone() const;
	virtual String ToString(bool exprFlag);
	inline const Formatter::Flags &GetFlags() const { return _flags; }
};

}

#endif
