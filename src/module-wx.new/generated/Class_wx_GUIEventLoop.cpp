//----------------------------------------------------------------------------
// wxGUIEventLoop
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Gura interfaces for wxGUIEventLoop
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Object implementation for wxGUIEventLoop
//----------------------------------------------------------------------------
Object_wx_GUIEventLoop::~Object_wx_GUIEventLoop()
{
}

Object *Object_wx_GUIEventLoop::Clone() const
{
	return nullptr;
}

String Object_wx_GUIEventLoop::ToString(bool exprFlag)
{
	String rtn("<wx.GUIEventLoop:");
	if (GetEntity() == nullptr) {
		rtn += "invalid>";
	} else {
		char buff[64];
		::sprintf(buff, "%p>", GetEntity());
		rtn += buff;
	}
	return rtn;
}

//----------------------------------------------------------------------------
// Constructor implementation
//----------------------------------------------------------------------------
Gura_DeclareFunctionAlias(__wxGUIEventLoop, "wxGUIEventLoop")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	SetClassToConstruct(Gura_UserClass(wx_GUIEventLoop));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(__wxGUIEventLoop)
{
	//wxGUIEventLoop();
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Class implementation for wxGUIEventLoop
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_GUIEventLoop)
{
	// Constructor assignment
	Gura_AssignFunction(__wxGUIEventLoop);
}

Gura_ImplementDescendantCreator(wx_GUIEventLoop)
{
	return new Object_wx_GUIEventLoop((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
