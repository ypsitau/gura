//=============================================================================
// Gura class: quote
//=============================================================================
#ifndef __GURA_CLASS_QUOTE_H__
#define __GURA_CLASS_QUOTE_H__

#include "Class.h"

namespace Gura {

//-----------------------------------------------------------------------------
// Class_quote
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE Class_quote : public ClassPrimitive {
public:
	Class_quote(Environment *pEnvOuter);
	virtual void DoPrepare(Environment &env);
	virtual bool CastFrom(Environment &env, Value &value, ULong flags);
	virtual SerializeFmtVer GetSerializeFmtVer() const;
	virtual bool Serialize(Environment &env, Stream &stream, const Value &value) const;
	virtual bool Deserialize(Environment &env, Stream &stream, Value &value, SerializeFmtVer serializeFmtVer) const;
};

}

#endif
