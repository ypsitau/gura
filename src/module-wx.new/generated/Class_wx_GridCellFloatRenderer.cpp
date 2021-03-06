//----------------------------------------------------------------------------
// wxGridCellFloatRenderer
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Gura interfaces for wxGridCellFloatRenderer
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Object implementation for wxGridCellFloatRenderer
//----------------------------------------------------------------------------
Object_wx_GridCellFloatRenderer::~Object_wx_GridCellFloatRenderer()
{
}

Object *Object_wx_GridCellFloatRenderer::Clone() const
{
	return nullptr;
}

String Object_wx_GridCellFloatRenderer::ToString(bool exprFlag)
{
	String rtn("<wx.GridCellFloatRenderer:");
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
Gura_DeclareFunctionAlias(__GridCellFloatRenderer, "GridCellFloatRenderer")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "width", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "precision", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "format", VTYPE_number, OCCUR_Once);
	SetClassToConstruct(Gura_UserClass(wx_GridCellFloatRenderer));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(__GridCellFloatRenderer)
{
	//int width = arg.GetNumber(0)
	//int precision = arg.GetNumber(1)
	//int format = arg.GetNumber(2)
	//wxGridCellFloatRenderer(width, precision, format);
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Method implementation
//----------------------------------------------------------------------------
Gura_DeclareMethodAlias(wx_GridCellFloatRenderer, __GetFormat, "GetFormat")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_GridCellFloatRenderer, __GetFormat)
{
	Object_wx_GridCellFloatRenderer *pThis = Object_wx_GridCellFloatRenderer::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int _rtn = pThis->GetEntity()->GetFormat();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_GridCellFloatRenderer, __GetPrecision, "GetPrecision")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_GridCellFloatRenderer, __GetPrecision)
{
	Object_wx_GridCellFloatRenderer *pThis = Object_wx_GridCellFloatRenderer::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int _rtn = pThis->GetEntity()->GetPrecision();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_GridCellFloatRenderer, __GetWidth, "GetWidth")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_GridCellFloatRenderer, __GetWidth)
{
	Object_wx_GridCellFloatRenderer *pThis = Object_wx_GridCellFloatRenderer::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int _rtn = pThis->GetEntity()->GetWidth();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_GridCellFloatRenderer, __SetFormat, "SetFormat")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "format", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_GridCellFloatRenderer, __SetFormat)
{
	Object_wx_GridCellFloatRenderer *pThis = Object_wx_GridCellFloatRenderer::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int format = arg.GetNumber(0)
	//pThis->GetEntity()->SetFormat(format);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_GridCellFloatRenderer, __SetParameters, "SetParameters")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "params", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_GridCellFloatRenderer, __SetParameters)
{
	Object_wx_GridCellFloatRenderer *pThis = Object_wx_GridCellFloatRenderer::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxString& params = arg.GetNumber(0)
	//pThis->GetEntity()->SetParameters(params);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_GridCellFloatRenderer, __SetPrecision, "SetPrecision")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "precision", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_GridCellFloatRenderer, __SetPrecision)
{
	Object_wx_GridCellFloatRenderer *pThis = Object_wx_GridCellFloatRenderer::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int precision = arg.GetNumber(0)
	//pThis->GetEntity()->SetPrecision(precision);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_GridCellFloatRenderer, __SetWidth, "SetWidth")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "width", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_GridCellFloatRenderer, __SetWidth)
{
	Object_wx_GridCellFloatRenderer *pThis = Object_wx_GridCellFloatRenderer::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int width = arg.GetNumber(0)
	//pThis->GetEntity()->SetWidth(width);
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Class implementation for wxGridCellFloatRenderer
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_GridCellFloatRenderer)
{
	// Constructor assignment
	Gura_AssignFunction(__GridCellFloatRenderer);
	// Method assignment
	Gura_AssignMethod(wx_GridCellFloatRenderer, __GetFormat);
	Gura_AssignMethod(wx_GridCellFloatRenderer, __GetPrecision);
	Gura_AssignMethod(wx_GridCellFloatRenderer, __GetWidth);
	Gura_AssignMethod(wx_GridCellFloatRenderer, __SetFormat);
	Gura_AssignMethod(wx_GridCellFloatRenderer, __SetParameters);
	Gura_AssignMethod(wx_GridCellFloatRenderer, __SetPrecision);
	Gura_AssignMethod(wx_GridCellFloatRenderer, __SetWidth);
}

Gura_ImplementDescendantCreator(wx_GridCellFloatRenderer)
{
	return new Object_wx_GridCellFloatRenderer((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
