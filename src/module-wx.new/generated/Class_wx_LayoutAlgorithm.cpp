//----------------------------------------------------------------------------
// wxLayoutAlgorithm
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Gura interfaces for wxLayoutAlgorithm
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Object implementation for wxLayoutAlgorithm
//----------------------------------------------------------------------------
Object_wx_LayoutAlgorithm::~Object_wx_LayoutAlgorithm()
{
}

Object *Object_wx_LayoutAlgorithm::Clone() const
{
	return nullptr;
}

String Object_wx_LayoutAlgorithm::ToString(bool exprFlag)
{
	String rtn("<wx.LayoutAlgorithm:");
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
Gura_DeclareFunctionAlias(__wxLayoutAlgorithm, "wxLayoutAlgorithm")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	SetClassToConstruct(Gura_UserClass(wx_LayoutAlgorithm));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(__wxLayoutAlgorithm)
{
	//wxLayoutAlgorithm();
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Method implementation
//----------------------------------------------------------------------------
Gura_DeclareMethodAlias(wx_LayoutAlgorithm, __LayoutFrame, "LayoutFrame")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "frame", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "mainWindow", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_LayoutAlgorithm, __LayoutFrame)
{
	Object_wx_LayoutAlgorithm *pThis = Object_wx_LayoutAlgorithm::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int frame = arg.GetNumber(0)
	//int mainWindow = arg.GetNumber(1)
	//pThis->GetEntity()->LayoutFrame();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_LayoutAlgorithm, __LayoutMDIFrame, "LayoutMDIFrame")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "frame", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "rect", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_LayoutAlgorithm, __LayoutMDIFrame)
{
	Object_wx_LayoutAlgorithm *pThis = Object_wx_LayoutAlgorithm::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int frame = arg.GetNumber(0)
	//int rect = arg.GetNumber(1)
	//pThis->GetEntity()->LayoutMDIFrame();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_LayoutAlgorithm, __LayoutWindow, "LayoutWindow")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "parent", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "mainWindow", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_LayoutAlgorithm, __LayoutWindow)
{
	Object_wx_LayoutAlgorithm *pThis = Object_wx_LayoutAlgorithm::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int parent = arg.GetNumber(0)
	//int mainWindow = arg.GetNumber(1)
	//pThis->GetEntity()->LayoutWindow();
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Class implementation for wxLayoutAlgorithm
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_LayoutAlgorithm)
{
	// Constructor assignment
	Gura_AssignFunction(__wxLayoutAlgorithm);
	// Method assignment
	Gura_AssignMethod(wx_LayoutAlgorithm, __LayoutFrame);
	Gura_AssignMethod(wx_LayoutAlgorithm, __LayoutMDIFrame);
	Gura_AssignMethod(wx_LayoutAlgorithm, __LayoutWindow);
}

Gura_ImplementDescendantCreator(wx_LayoutAlgorithm)
{
	return new Object_wx_LayoutAlgorithm((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
