//=============================================================================
// Gura class: function
//=============================================================================
#ifndef __GURA_CLASS_FUNCTION_H__
#define __GURA_CLASS_FUNCTION_H__

#include "Class.h"
#include "Expr.h"

namespace Gura {

//-----------------------------------------------------------------------------
// Class_function / Object_function
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE Class_function : public Class {
public:
	Class_function(Environment *pEnvOuter);
	virtual void Prepare(Environment &env);
	virtual bool CastFrom(Environment &env, Signal sig, Value &value, const Declaration *pDecl);
	virtual bool Serialize(Environment &env, Signal sig, Stream &stream, const Value &value) const;
	virtual bool Deserialize(Environment &env, Signal sig, Stream &stream, Value &value) const;
	virtual Object *CreateDescendant(Environment &env, Signal sig, Class *pClass);
};

class GURA_DLLDECLARE Object_function : public Object {
public:
	Gura_DeclareObjectAccessor(function)
protected:
	AutoPtr<Function> _pFunc;
	Value _valueThis;
public:
	inline Object_function(Environment &env, Function *pFunc) :
				Object(env.LookupClass(VTYPE_function)), _pFunc(pFunc) {}
	inline Object_function(Class *pClass, Function *pFunc) :
				Object(pClass), _pFunc(pFunc) {}
	inline Object_function(const Object_function &obj) :
				Object(obj), _pFunc(Function::Reference(obj._pFunc.get())),
				_valueThis(obj._valueThis) {}
	~Object_function();
	virtual bool IsFunction() const;
	virtual Object *Clone() const;
	inline Function *GetFunction() { return _pFunc.get(); }
	inline const Function *GetFunction() const { return _pFunc.get(); }
	inline void SetThis(const Value &valueThis) { _valueThis = valueThis; }
	inline Value GetThis() const { return _valueThis; }
	virtual String ToString(bool exprFlag);
	virtual bool DoDirProp(Environment &env, Signal sig, SymbolSet &symbols);
	virtual Value DoGetProp(Environment &env, Signal sig, const Symbol *pSymbol,
							const SymbolSet &attrs, bool &evaluatedFlag);
	virtual Value DoSetProp(Environment &env, Signal sig, const Symbol *pSymbol, const Value &value,
							const SymbolSet &attrs, bool &evaluatedFlag);
	virtual bool IsLeader() const;
	virtual bool IsTrailer() const;
	virtual bool IsFinalizer() const;
	virtual bool IsEndMarker() const;
	virtual OccurPattern GetBlockOccurPattern() const;
	virtual Value DoCall(Environment &env, Signal sig, Args &args);
	virtual void GatherFollower(Environment::Frame *pFrame, EnvironmentSet &envSet);
	Value Eval(Environment &env, Signal sig, ValueList &valListArg) const;
};

}

#endif
