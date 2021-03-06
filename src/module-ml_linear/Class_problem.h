#ifndef __ML_LINEAR_CLASS_PROBLEM_H__
#define __ML_LINEAR_CLASS_PROBLEM_H__
#include <gura.h>
#include "Sample.h"

Gura_BeginModuleScope(ml_linear)

//-----------------------------------------------------------------------------
// Object_problem declaration
//-----------------------------------------------------------------------------
Gura_DeclareUserClass(problem);

class Object_problem : public Object {
private:
	int _indexMax;
	struct problem _prob;
	AutoPtr<SampleOwner> _pSampleOwner;
public:
	Gura_DeclareObjectAccessor(problem)
public:
	Object_problem();
	virtual ~Object_problem();
	virtual String ToString(bool exprFlag);
	struct problem &UpdateEntity(double bias);
	void AddSample(Sample *pSample);
	void AddSample(double label, Feature *pFeature);
	inline const SampleOwner *GetSampleOwner() const { return _pSampleOwner.get(); }
};

Gura_EndModuleScope(ml_linear)

#endif

