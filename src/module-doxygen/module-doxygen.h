//=============================================================================
// Gura module: doxygen
//=============================================================================
#ifndef __GURA_MODULE_DOXYGEN_H__
#define __GURA_MODULE_DOXYGEN_H__
#include <gura.h>
#include "CommandFormat.h"
#include "Elem.h"
#include "Alias.h"
#include "Structure.h"
#include "Parser.h"
#include "Document.h"
#include "Configuration.h"
#include "Renderer.h"
#include "Class_elem.h"
#include "Class_structure.h"
#include "Class_document.h"
#include "Class_configuration.h"
#include "Class_aliases.h"
#include "Class_renderer.h"

#define BeginPushbackRegion(var) \
_pushbackBuff[_pushbackLevel++] = var; \
while (_pushbackLevel > 0) { \
var = _pushbackBuff[--_pushbackLevel];

#define EndPushbackRegion() \
}

Gura_BeginModuleHeader(doxygen)

Gura_DeclareUserSymbol(aliases);
Gura_DeclareUserSymbol(elem);

//-----------------------------------------------------------------------------
// HelpPresenter_doxygen
//-----------------------------------------------------------------------------
class HelpPresenter_doxygen : public HelpPresenter {
public:
	inline HelpPresenter_doxygen() : HelpPresenter("doxygen") {}
	virtual bool DoPresent(Environment &env, const char *title, const Help *pHelp) const;
};

//-----------------------------------------------------------------------------
// utilities
//-----------------------------------------------------------------------------
inline static bool IsCommandMark(char ch)
{
	return ch == '@' || ch == '\\';
}

inline static bool IsWordChar(char ch)
{
	return IsAlpha(ch) || IsDigit(ch) || ch == '_';
}

Gura_EndModuleHeader(doxygen)

#endif
