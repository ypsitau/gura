//----------------------------------------------------------------------------
// wxGridCornerHeaderRenderer
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Gura interfaces for wxGridCornerHeaderRenderer
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Object implementation for wxGridCornerHeaderRenderer
//----------------------------------------------------------------------------
Object_wx_GridCornerHeaderRenderer::~Object_wx_GridCornerHeaderRenderer()
{
}

Object *Object_wx_GridCornerHeaderRenderer::Clone() const
{
	return nullptr;
}

String Object_wx_GridCornerHeaderRenderer::ToString(bool exprFlag)
{
	String rtn("<wx.GridCornerHeaderRenderer:");
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
// Method implementation
//----------------------------------------------------------------------------
Gura_DeclareMethod(wx_GridCornerHeaderRenderer, DrawBorder)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "grid", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "dc", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "rect", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_GridCornerHeaderRenderer, DrawBorder)
{
	Signal &sig = env.GetSignal();
	Object_wx_GridCornerHeaderRenderer *pThis = Object_wx_GridCornerHeaderRenderer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	//int grid = arg.GetNumber(0)
	//int dc = arg.GetNumber(1)
	//int rect = arg.GetNumber(2)
	//pThis->GetEntity()->DrawBorder();
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Class implementation for wxGridCornerHeaderRenderer
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_GridCornerHeaderRenderer)
{
	Gura_AssignMethod(wx_GridCornerHeaderRenderer, DrawBorder);
}

Gura_ImplementDescendantCreator(wx_GridCornerHeaderRenderer)
{
	return new Object_wx_GridCornerHeaderRenderer((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
