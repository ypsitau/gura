#include "stdafx.h"

Gura_BeginModuleScope(sdl2)

//-----------------------------------------------------------------------------
// Object_RendererInfo implementation
//-----------------------------------------------------------------------------
Object_RendererInfo::~Object_RendererInfo()
{
}

Object *Object_RendererInfo::Clone() const
{
	return nullptr;
}

String Object_RendererInfo::ToString(bool exprFlag)
{
	return String("<sdl2.RendererInfo>");
}

//-----------------------------------------------------------------------------
// Gura interfaces for RendererInfo
//-----------------------------------------------------------------------------
// implementation of class RendererInfo
Gura_ImplementUserClass(RendererInfo)
{
	Gura_AssignValue(RendererInfo, Value(Reference()));
}

Gura_EndModuleScope(sdl2)
