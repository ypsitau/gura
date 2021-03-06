//----------------------------------------------------------------------------
// wxMessageOutputBest
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Gura interfaces for wxMessageOutputBest
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Object implementation for wxMessageOutputBest
//----------------------------------------------------------------------------
Object_wx_MessageOutputBest::~Object_wx_MessageOutputBest()
{
}

Object *Object_wx_MessageOutputBest::Clone() const
{
	return nullptr;
}

String Object_wx_MessageOutputBest::ToString(bool exprFlag)
{
	String rtn("<wx.MessageOutputBest:");
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
Gura_DeclareFunctionAlias(__MessageOutputBest, "MessageOutputBest")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "flags", VTYPE_number, OCCUR_Once);
	SetClassToConstruct(Gura_UserClass(wx_MessageOutputBest));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(__MessageOutputBest)
{
	//wxMessageOutputFlags flags = arg.GetNumber(0)
	//wxMessageOutputBest(flags);
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Class implementation for wxMessageOutputBest
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_MessageOutputBest)
{
	// Constructor assignment
	Gura_AssignFunction(__MessageOutputBest);
}

Gura_ImplementDescendantCreator(wx_MessageOutputBest)
{
	return new Object_wx_MessageOutputBest((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
