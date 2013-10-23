#ifndef __GURA_OBJECT_DECLARATION_H__
#define __GURA_OBJECT_DECLARATION_H__

#include "Object.h"

namespace Gura {

//-----------------------------------------------------------------------------
// Class_declaration
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE Class_declaration : public Class {
public:
	Class_declaration(Environment *pEnvOuter);
	virtual void Prepare(Environment &env);
};

//-----------------------------------------------------------------------------
// Object_declaration
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE Object_declaration : public Object {
private:
	AutoPtr<Declaration> _pDeclaration;
public:
	Gura_DeclareObjectAccessor(declaration)
public:
	inline Object_declaration(Environment &env, Declaration *pDeclaration) :
					Object(env.LookupClass(VTYPE_declaration)), _pDeclaration(pDeclaration) {}
	inline Object_declaration(Class *pClass, Declaration *pDeclaration) :
					Object(pClass), _pDeclaration(pDeclaration) {}
	virtual Object *Clone() const;
	virtual bool DoDirProp(Environment &env, Signal sig, SymbolSet &symbols);
	virtual Value DoGetProp(Environment &env, Signal sig, const Symbol *pSymbol,
								const SymbolSet &attrs, bool &evaluatedFlag);
	virtual String ToString(Signal sig, bool exprFlag);
	inline Declaration *GetDeclaration() { return _pDeclaration.get(); }
};

}

#endif
