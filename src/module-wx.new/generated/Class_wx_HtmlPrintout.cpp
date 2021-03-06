//----------------------------------------------------------------------------
// wxHtmlPrintout
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Gura interfaces for wxHtmlPrintout
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Object implementation for wxHtmlPrintout
//----------------------------------------------------------------------------
Object_wx_HtmlPrintout::~Object_wx_HtmlPrintout()
{
}

Object *Object_wx_HtmlPrintout::Clone() const
{
	return nullptr;
}

String Object_wx_HtmlPrintout::ToString(bool exprFlag)
{
	String rtn("<wx.HtmlPrintout:");
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
Gura_DeclareFunctionAlias(__HtmlPrintout, "HtmlPrintout")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "title", VTYPE_number, OCCUR_Once);
	SetClassToConstruct(Gura_UserClass(wx_HtmlPrintout));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(__HtmlPrintout)
{
	//const wxString& title = arg.GetNumber(0)
	//wxHtmlPrintout(title);
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Method implementation
//----------------------------------------------------------------------------
Gura_DeclareMethodAlias(wx_HtmlPrintout, __AddFilter, "AddFilter")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "filter", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_HtmlPrintout, __AddFilter)
{
	Object_wx_HtmlPrintout *pThis = Object_wx_HtmlPrintout::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxHtmlFilter* filter = arg.GetNumber(0)
	//pThis->GetEntity()->AddFilter(filter);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_HtmlPrintout, __SetFonts, "SetFonts")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "normal_face", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "fixed_face", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "sizes", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_HtmlPrintout, __SetFonts)
{
	Object_wx_HtmlPrintout *pThis = Object_wx_HtmlPrintout::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxString& normal_face = arg.GetNumber(0)
	//const wxString& fixed_face = arg.GetNumber(1)
	//const int* sizes = arg.GetNumber(2)
	//pThis->GetEntity()->SetFonts(normal_face, fixed_face, sizes);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_HtmlPrintout, __SetFooter, "SetFooter")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "footer", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "pg", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_HtmlPrintout, __SetFooter)
{
	Object_wx_HtmlPrintout *pThis = Object_wx_HtmlPrintout::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxString& footer = arg.GetNumber(0)
	//int pg = arg.GetNumber(1)
	//pThis->GetEntity()->SetFooter(footer, pg);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_HtmlPrintout, __SetHeader, "SetHeader")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "header", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "pg", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_HtmlPrintout, __SetHeader)
{
	Object_wx_HtmlPrintout *pThis = Object_wx_HtmlPrintout::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxString& header = arg.GetNumber(0)
	//int pg = arg.GetNumber(1)
	//pThis->GetEntity()->SetHeader(header, pg);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_HtmlPrintout, __SetHtmlFile, "SetHtmlFile")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "htmlfile", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_HtmlPrintout, __SetHtmlFile)
{
	Object_wx_HtmlPrintout *pThis = Object_wx_HtmlPrintout::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxString& htmlfile = arg.GetNumber(0)
	//pThis->GetEntity()->SetHtmlFile(htmlfile);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_HtmlPrintout, __SetHtmlText, "SetHtmlText")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "html", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "basepath", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "isdir", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_HtmlPrintout, __SetHtmlText)
{
	Object_wx_HtmlPrintout *pThis = Object_wx_HtmlPrintout::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxString& html = arg.GetNumber(0)
	//const wxString& basepath = arg.GetNumber(1)
	//bool isdir = arg.GetNumber(2)
	//pThis->GetEntity()->SetHtmlText(html, basepath, isdir);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_HtmlPrintout, __SetMargins, "SetMargins")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "top", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "bottom", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "left", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "right", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "spaces", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_HtmlPrintout, __SetMargins)
{
	Object_wx_HtmlPrintout *pThis = Object_wx_HtmlPrintout::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//float top = arg.GetNumber(0)
	//float bottom = arg.GetNumber(1)
	//float left = arg.GetNumber(2)
	//float right = arg.GetNumber(3)
	//float spaces = arg.GetNumber(4)
	//pThis->GetEntity()->SetMargins(top, bottom, left, right, spaces);
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Class implementation for wxHtmlPrintout
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_HtmlPrintout)
{
	// Constructor assignment
	Gura_AssignFunction(__HtmlPrintout);
	// Method assignment
	Gura_AssignMethod(wx_HtmlPrintout, __AddFilter);
	Gura_AssignMethod(wx_HtmlPrintout, __SetFonts);
	Gura_AssignMethod(wx_HtmlPrintout, __SetFooter);
	Gura_AssignMethod(wx_HtmlPrintout, __SetHeader);
	Gura_AssignMethod(wx_HtmlPrintout, __SetHtmlFile);
	Gura_AssignMethod(wx_HtmlPrintout, __SetHtmlText);
	Gura_AssignMethod(wx_HtmlPrintout, __SetMargins);
}

Gura_ImplementDescendantCreator(wx_HtmlPrintout)
{
	return new Object_wx_HtmlPrintout((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
