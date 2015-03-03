//=============================================================================
// Gura class: Sequence
//=============================================================================
#ifndef __GURA_CLASS_SEQUENCE_H__
#define __GURA_CLASS_SEQUENCE_H__

#include "Class.h"

namespace Gura {

//-----------------------------------------------------------------------------
// Class_Sequence
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE Class_Sequence : public Class {
public:
	Class_Sequence(Environment *pEnvOuter);
	virtual void Prepare(Environment &env);
	virtual bool CastFrom(Environment &env, Signal sig, Value &value, const Declaration *pDecl);
	virtual bool Serialize(Environment &env, Signal sig, Stream &stream, const Value &value) const;
	virtual bool Deserialize(Environment &env, Signal sig, Stream &stream, Value &value) const;
};

}

#endif