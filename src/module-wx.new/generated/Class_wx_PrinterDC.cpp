//----------------------------------------------------------------------------
// wxPrinterDC
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Gura interfaces for wxPrinterDC
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Object implementation for wxPrinterDC
//----------------------------------------------------------------------------
Object_wx_PrinterDC::~Object_wx_PrinterDC()
{
}

Object *Object_wx_PrinterDC::Clone() const
{
	return nullptr;
}

String Object_wx_PrinterDC::ToString(bool exprFlag)
{
	String rtn("<wx.PrinterDC:");
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
Gura_DeclareFunctionAlias(__PrinterDC, "PrinterDC")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "printData", VTYPE_number, OCCUR_Once);
	SetClassToConstruct(Gura_UserClass(wx_PrinterDC));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(__PrinterDC)
{
	//const wxPrintData& printData = arg.GetNumber(0)
	//wxPrinterDC(printData);
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Method implementation
//----------------------------------------------------------------------------
Gura_DeclareMethodAlias(wx_PrinterDC, __GetPaperRect, "GetPaperRect")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_PrinterDC, __GetPaperRect)
{
	Object_wx_PrinterDC *pThis = Object_wx_PrinterDC::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxRect _rtn = pThis->GetEntity()->GetPaperRect();
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Class implementation for wxPrinterDC
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_PrinterDC)
{
	// Constructor assignment
	Gura_AssignFunction(__PrinterDC);
	// Method assignment
	Gura_AssignMethod(wx_PrinterDC, __GetPaperRect);
}

Gura_ImplementDescendantCreator(wx_PrinterDC)
{
	return new Object_wx_PrinterDC((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
