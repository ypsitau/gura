//----------------------------------------------------------------------------
// wxRegConfig
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Gura interfaces for wxRegConfig
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Object implementation for wxRegConfig
//----------------------------------------------------------------------------
Object_wx_RegConfig::~Object_wx_RegConfig()
{
}

Object *Object_wx_RegConfig::Clone() const
{
	return nullptr;
}

String Object_wx_RegConfig::ToString(bool exprFlag)
{
	String rtn("<wx.RegConfig:");
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
Gura_DeclareMethod(wx_RegConfig, wxRegConfig)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "appName", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "vendorName", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "localFilename", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "globalFilename", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "style", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_RegConfig, wxRegConfig)
{
	Object_wx_RegConfig *pThis = Object_wx_RegConfig::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int appName = arg.GetNumber(0)
	//int vendorName = arg.GetNumber(1)
	//int localFilename = arg.GetNumber(2)
	//int globalFilename = arg.GetNumber(3)
	//int style = arg.GetNumber(4)
	//pThis->GetEntity()->wxRegConfig();
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Class implementation for wxRegConfig
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_RegConfig)
{
	Gura_AssignMethod(wx_RegConfig, wxRegConfig);
}

Gura_ImplementDescendantCreator(wx_RegConfig)
{
	return new Object_wx_RegConfig((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
