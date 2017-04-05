#ifndef __ML_LINEAR_CLASS_MODEL_H__
#define __ML_LINEAR_CLASS_MODEL_H__
#include <gura.h>

Gura_BeginModuleScope(ml_linear)

class Object_ifd;

//-----------------------------------------------------------------------------
// Object_model declaration
//-----------------------------------------------------------------------------
Gura_DeclareUserClass(model);

class Object_model : public Object {
private:
	Gura_DeclareObjectAccessor(model)
public:
	Object_model();
	virtual String ToString(bool exprFlag);
};

Gura_EndModuleScope(ml_linear)

#endif