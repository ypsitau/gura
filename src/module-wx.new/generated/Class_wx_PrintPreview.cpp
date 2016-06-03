//----------------------------------------------------------------------------
// wxPrintPreview
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Gura interfaces for wxPrintPreview
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Object implementation for wxPrintPreview
//----------------------------------------------------------------------------
Object_wx_PrintPreview::~Object_wx_PrintPreview()
{
}

Object *Object_wx_PrintPreview::Clone() const
{
	return nullptr;
}

String Object_wx_PrintPreview::ToString(bool exprFlag)
{
	String rtn("<wx.PrintPreview:");
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
Gura_DeclareMethodAlias(wx_PrintPreview, __wxPrintPreview, "wxPrintPreview")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "printout", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "printoutForPrinting", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "data", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_PrintPreview, __wxPrintPreview)
{
	Object_wx_PrintPreview *pThis = Object_wx_PrintPreview::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int printout = arg.GetNumber(0)
	//int printoutForPrinting = arg.GetNumber(1)
	//int data = arg.GetNumber(2)
	//pThis->GetEntity()->wxPrintPreview();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_PrintPreview, __wxPrintPreview_1, "wxPrintPreview_1")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "printout", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "printoutForPrinting", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "data", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_PrintPreview, __wxPrintPreview_1)
{
	Object_wx_PrintPreview *pThis = Object_wx_PrintPreview::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int printout = arg.GetNumber(0)
	//int printoutForPrinting = arg.GetNumber(1)
	//int data = arg.GetNumber(2)
	//pThis->GetEntity()->wxPrintPreview();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_PrintPreview, __GetCanvas, "GetCanvas")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_PrintPreview, __GetCanvas)
{
	Object_wx_PrintPreview *pThis = Object_wx_PrintPreview::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->GetCanvas();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_PrintPreview, __GetCurrentPage, "GetCurrentPage")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_PrintPreview, __GetCurrentPage)
{
	Object_wx_PrintPreview *pThis = Object_wx_PrintPreview::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->GetCurrentPage();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_PrintPreview, __GetFrame, "GetFrame")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_PrintPreview, __GetFrame)
{
	Object_wx_PrintPreview *pThis = Object_wx_PrintPreview::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->GetFrame();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_PrintPreview, __GetMaxPage, "GetMaxPage")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_PrintPreview, __GetMaxPage)
{
	Object_wx_PrintPreview *pThis = Object_wx_PrintPreview::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->GetMaxPage();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_PrintPreview, __GetMinPage, "GetMinPage")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_PrintPreview, __GetMinPage)
{
	Object_wx_PrintPreview *pThis = Object_wx_PrintPreview::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->GetMinPage();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_PrintPreview, __GetPrintout, "GetPrintout")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_PrintPreview, __GetPrintout)
{
	Object_wx_PrintPreview *pThis = Object_wx_PrintPreview::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->GetPrintout();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_PrintPreview, __GetPrintoutForPrinting, "GetPrintoutForPrinting")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_PrintPreview, __GetPrintoutForPrinting)
{
	Object_wx_PrintPreview *pThis = Object_wx_PrintPreview::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->GetPrintoutForPrinting();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_PrintPreview, __IsOk, "IsOk")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_PrintPreview, __IsOk)
{
	Object_wx_PrintPreview *pThis = Object_wx_PrintPreview::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->IsOk();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_PrintPreview, __PaintPage, "PaintPage")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "canvas", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "dc", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_PrintPreview, __PaintPage)
{
	Object_wx_PrintPreview *pThis = Object_wx_PrintPreview::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int canvas = arg.GetNumber(0)
	//int dc = arg.GetNumber(1)
	//pThis->GetEntity()->PaintPage();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_PrintPreview, __Print, "Print")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "prompt", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_PrintPreview, __Print)
{
	Object_wx_PrintPreview *pThis = Object_wx_PrintPreview::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int prompt = arg.GetNumber(0)
	//pThis->GetEntity()->Print();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_PrintPreview, __RenderPage, "RenderPage")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "pageNum", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_PrintPreview, __RenderPage)
{
	Object_wx_PrintPreview *pThis = Object_wx_PrintPreview::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int pageNum = arg.GetNumber(0)
	//pThis->GetEntity()->RenderPage();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_PrintPreview, __SetCanvas, "SetCanvas")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "window", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_PrintPreview, __SetCanvas)
{
	Object_wx_PrintPreview *pThis = Object_wx_PrintPreview::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int window = arg.GetNumber(0)
	//pThis->GetEntity()->SetCanvas();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_PrintPreview, __SetCurrentPage, "SetCurrentPage")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "pageNum", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_PrintPreview, __SetCurrentPage)
{
	Object_wx_PrintPreview *pThis = Object_wx_PrintPreview::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int pageNum = arg.GetNumber(0)
	//pThis->GetEntity()->SetCurrentPage();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_PrintPreview, __SetFrame, "SetFrame")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "frame", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_PrintPreview, __SetFrame)
{
	Object_wx_PrintPreview *pThis = Object_wx_PrintPreview::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int frame = arg.GetNumber(0)
	//pThis->GetEntity()->SetFrame();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_PrintPreview, __SetPrintout, "SetPrintout")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "printout", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_PrintPreview, __SetPrintout)
{
	Object_wx_PrintPreview *pThis = Object_wx_PrintPreview::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int printout = arg.GetNumber(0)
	//pThis->GetEntity()->SetPrintout();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_PrintPreview, __SetZoom, "SetZoom")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "percent", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_PrintPreview, __SetZoom)
{
	Object_wx_PrintPreview *pThis = Object_wx_PrintPreview::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int percent = arg.GetNumber(0)
	//pThis->GetEntity()->SetZoom();
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Class implementation for wxPrintPreview
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_PrintPreview)
{
	Gura_AssignMethod(wx_PrintPreview, __wxPrintPreview);
	Gura_AssignMethod(wx_PrintPreview, __wxPrintPreview_1);
	Gura_AssignMethod(wx_PrintPreview, __GetCanvas);
	Gura_AssignMethod(wx_PrintPreview, __GetCurrentPage);
	Gura_AssignMethod(wx_PrintPreview, __GetFrame);
	Gura_AssignMethod(wx_PrintPreview, __GetMaxPage);
	Gura_AssignMethod(wx_PrintPreview, __GetMinPage);
	Gura_AssignMethod(wx_PrintPreview, __GetPrintout);
	Gura_AssignMethod(wx_PrintPreview, __GetPrintoutForPrinting);
	Gura_AssignMethod(wx_PrintPreview, __IsOk);
	Gura_AssignMethod(wx_PrintPreview, __PaintPage);
	Gura_AssignMethod(wx_PrintPreview, __Print);
	Gura_AssignMethod(wx_PrintPreview, __RenderPage);
	Gura_AssignMethod(wx_PrintPreview, __SetCanvas);
	Gura_AssignMethod(wx_PrintPreview, __SetCurrentPage);
	Gura_AssignMethod(wx_PrintPreview, __SetFrame);
	Gura_AssignMethod(wx_PrintPreview, __SetPrintout);
	Gura_AssignMethod(wx_PrintPreview, __SetZoom);
}

Gura_ImplementDescendantCreator(wx_PrintPreview)
{
	return new Object_wx_PrintPreview((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
