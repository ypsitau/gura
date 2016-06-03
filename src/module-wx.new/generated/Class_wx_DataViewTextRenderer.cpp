//----------------------------------------------------------------------------
// wxDataViewTextRenderer
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Gura interfaces for wxDataViewTextRenderer
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Object implementation for wxDataViewTextRenderer
//----------------------------------------------------------------------------
Object_wx_DataViewTextRenderer::~Object_wx_DataViewTextRenderer()
{
}

Object *Object_wx_DataViewTextRenderer::Clone() const
{
	return nullptr;
}

String Object_wx_DataViewTextRenderer::ToString(bool exprFlag)
{
	String rtn("<wx.DataViewTextRenderer:");
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
Gura_DeclareMethodAlias(wx_DataViewTextRenderer, __GetDefaultType, "GetDefaultType")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_DataViewTextRenderer, __GetDefaultType)
{
	Object_wx_DataViewTextRenderer *pThis = Object_wx_DataViewTextRenderer::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->GetDefaultType();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_DataViewTextRenderer, __wxDataViewTextRenderer, "wxDataViewTextRenderer")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "varianttype", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "mode", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "align", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_DataViewTextRenderer, __wxDataViewTextRenderer)
{
	Object_wx_DataViewTextRenderer *pThis = Object_wx_DataViewTextRenderer::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int varianttype = arg.GetNumber(0)
	//int mode = arg.GetNumber(1)
	//int align = arg.GetNumber(2)
	//pThis->GetEntity()->wxDataViewTextRenderer();
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Class implementation for wxDataViewTextRenderer
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_DataViewTextRenderer)
{
	Gura_AssignMethod(wx_DataViewTextRenderer, __GetDefaultType);
	Gura_AssignMethod(wx_DataViewTextRenderer, __wxDataViewTextRenderer);
}

Gura_ImplementDescendantCreator(wx_DataViewTextRenderer)
{
	return new Object_wx_DataViewTextRenderer((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
