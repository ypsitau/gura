//----------------------------------------------------------------------------
// wxImageHistogram
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Gura interfaces for wxImageHistogram
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Object implementation for wxImageHistogram
//----------------------------------------------------------------------------
Object_wx_ImageHistogram::~Object_wx_ImageHistogram()
{
}

Object *Object_wx_ImageHistogram::Clone() const
{
	return nullptr;
}

String Object_wx_ImageHistogram::ToString(bool exprFlag)
{
	String rtn("<wx.ImageHistogram:");
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
Gura_DeclareMethod(wx_ImageHistogram, wxImageHistogram)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_ImageHistogram, wxImageHistogram)
{
	Object_wx_ImageHistogram *pThis = Object_wx_ImageHistogram::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->wxImageHistogram();
	return Value::Nil;
}

Gura_DeclareMethod(wx_ImageHistogram, MakeKey)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "r", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "g", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "b", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_ImageHistogram, MakeKey)
{
	Object_wx_ImageHistogram *pThis = Object_wx_ImageHistogram::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int r = arg.GetNumber(0)
	//int g = arg.GetNumber(1)
	//int b = arg.GetNumber(2)
	//pThis->GetEntity()->MakeKey();
	return Value::Nil;
}

Gura_DeclareMethod(wx_ImageHistogram, FindFirstUnusedColour)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "r", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "g", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "b", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "startR", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "startG", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "startB", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_ImageHistogram, FindFirstUnusedColour)
{
	Object_wx_ImageHistogram *pThis = Object_wx_ImageHistogram::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int r = arg.GetNumber(0)
	//int g = arg.GetNumber(1)
	//int b = arg.GetNumber(2)
	//int startR = arg.GetNumber(3)
	//int startG = arg.GetNumber(4)
	//int startB = arg.GetNumber(5)
	//pThis->GetEntity()->FindFirstUnusedColour();
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Class implementation for wxImageHistogram
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_ImageHistogram)
{
	Gura_AssignMethod(wx_ImageHistogram, wxImageHistogram);
	Gura_AssignMethod(wx_ImageHistogram, MakeKey);
	Gura_AssignMethod(wx_ImageHistogram, FindFirstUnusedColour);
}

Gura_ImplementDescendantCreator(wx_ImageHistogram)
{
	return new Object_wx_ImageHistogram((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
