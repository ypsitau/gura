//=============================================================================
// Gura class: help
//=============================================================================
#ifndef __GURA_CLASS_HELP_H__
#define __GURA_CLASS_HELP_H__

#include "Class.h"

namespace Gura {

//-----------------------------------------------------------------------------
// Class_help
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE Class_help : public ClassFundamental {
public:
	Class_help(Environment *pEnvOuter);
	virtual void DoPrepare(Environment &env);
};

//-----------------------------------------------------------------------------
// Object_help
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE Object_help : public Object {
public:
	Gura_DeclareObjectAccessor(help)
private:
	AutoPtr<Help> _pHelp;
public:
	Object_help(Environment &env, Help *pHelp);
	Object_help(Class *pClass, Help *pHelp);
	inline Help *GetHelp() { return _pHelp.get(); }
	inline const Help *GetHelp() const { return _pHelp.get(); }
	virtual Object *Clone() const;
	virtual String ToString(bool exprFlag);
};

}

#endif
