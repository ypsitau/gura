//=============================================================================
// SuffixHandler
//=============================================================================
#ifndef __GURA_SUFFIXHANDLER_H__
#define __GURA_SUFFIXHANDLER_H__

#include "Common.h"
#include "Signal.h"

#define Gura_ImplementSuffixHandlerForNumber(suffix)								\
class SuffixHandler_Number_##suffix : public SuffixHandler {						\
public:																				\
	virtual Value DoEval(Environment &env, Signal sig, const char *body) const;		\
};																					\
Value SuffixHandler_Number_##suffix::DoEval(Environment &env, Signal sig, const char *body) const

#define Gura_ImplementSuffixHandlerForString(suffix)								\
class SuffixHandler_String_##suffix : public SuffixHandler {						\
public:																				\
	virtual Value DoEval(Environment &env, Signal sig, const char *body) const;		\
};																					\
Value SuffixHandler_String_##suffix::DoEval(Environment &env, Signal sig, const char *body) const

#define Gura_RegisterSuffixHandlerForNumber(suffix)									\
SuffixHandler::RegisterForNumber(env, Symbol::Add(#suffix), new SuffixHandler_Number_##suffix());

#define Gura_RegisterSuffixHandlerForString(suffix)									\
SuffixHandler::RegisterForString(env, Symbol::Add(#suffix), new SuffixHandler_String_##suffix());

namespace Gura {

class Environment;

//-----------------------------------------------------------------------------
// SuffixHandler
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE SuffixHandler {
public:
	virtual Value DoEval(Environment &env, Signal sig, const char *body) const = 0;
	static SuffixHandler *LookupForString(Environment &env, const Symbol *pSymbolSuffix);
	static SuffixHandler *LookupForNumber(Environment &env, const Symbol *pSymbolSuffix);
	static void RegisterForString(Environment &env,
				const Symbol *pSymbolSuffix, SuffixHandler *pSuffixHandler);
	static void RegisterForNumber(Environment &env,
				const Symbol *pSymbolSuffix, SuffixHandler *pSuffixHandler);
};

//-----------------------------------------------------------------------------
// SuffixHandlerMap
//-----------------------------------------------------------------------------
class GURA_DLLDECLARE SuffixHandlerMap : public std::map<const Symbol *,
							SuffixHandler *, Symbol::KeyCompare_UniqNumber> {
public:
	~SuffixHandlerMap();
	void Register(const Symbol *pSymbolSuffix, SuffixHandler *pSuffixHandler);
	SuffixHandler *Lookup(const Symbol *pSymbolSuffix);
};

}
#endif
