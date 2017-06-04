#ifndef __GURA_FFTW_CLASS_PLAN_H__
#define __GURA_FFTW_CLASS_PLAN_H__

Gura_BeginModuleScope(fftw)

//-----------------------------------------------------------------------------
// Object_plan declaration
//-----------------------------------------------------------------------------
Gura_DeclareUserClass(plan);

class Object_plan : public Object {
public:
	Gura_DeclareObjectAccessor(plan)
public:
	inline Object_plan() : Object(Gura_UserClass(plan)) {}
	virtual ~Object_plan();
	virtual Object *Clone() const;
	virtual String ToString(bool exprFlag);
};

Gura_EndModuleScope(fftw)

#endif
