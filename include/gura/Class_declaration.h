//=============================================================================
// Gura class: declaration
//=============================================================================
#ifndef __GURA_CLASS_DECLARATION_H__
#define __GURA_CLASS_DECLARATION_H__

#include "Class.h"

namespace Gura {

//-----------------------------------------------------------------------------
// Class_declaration
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE Class_declaration : public ClassFundamental {
public:
	Class_declaration(Environment *pEnvOuter);
	virtual void DoPrepare(Environment &env);
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
	virtual String ToString(bool exprFlag);
	inline Declaration *GetDeclaration() { return _pDeclaration.get(); }
};

//-----------------------------------------------------------------------------
// Iterator_declaration
//-----------------------------------------------------------------------------
class Iterator_declaration : public Iterator {
private:
	size_t _idx;
	AutoPtr<DeclarationOwner> _pDeclarationOwner;
public:
	Iterator_declaration(DeclarationOwner *pDeclarationOwner);
	virtual Iterator *GetSource();
	virtual bool DoNext(Environment &env, Value &value);
	virtual String ToString() const;
	virtual void GatherFollower(Environment::Frame *pFrame, EnvironmentSet &envSet);
};

}

#endif
