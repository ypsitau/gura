//----------------------------------------------------------------------------
// wxGenericProgressDialog
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Gura interfaces for wxGenericProgressDialog
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Object implementation for wxGenericProgressDialog
//----------------------------------------------------------------------------
Object_wx_GenericProgressDialog::~Object_wx_GenericProgressDialog()
{
}

Object *Object_wx_GenericProgressDialog::Clone() const
{
	return nullptr;
}

String Object_wx_GenericProgressDialog::ToString(bool exprFlag)
{
	String rtn("<wx.GenericProgressDialog:");
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
Gura_DeclareFunctionAlias(__GenericProgressDialog, "GenericProgressDialog")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "title", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "message", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "maximum", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "parent", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "style", VTYPE_number, OCCUR_Once);
	SetClassToConstruct(Gura_UserClass(wx_GenericProgressDialog));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(__GenericProgressDialog)
{
	//const wxString& title = arg.GetNumber(0)
	//const wxString& message = arg.GetNumber(1)
	//int maximum = arg.GetNumber(2)
	//wxWindow* parent = arg.GetNumber(3)
	//int style = arg.GetNumber(4)
	//wxGenericProgressDialog(title, message, maximum, parent, style);
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Method implementation
//----------------------------------------------------------------------------
Gura_DeclareMethodAlias(wx_GenericProgressDialog, __GetValue, "GetValue")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_GenericProgressDialog, __GetValue)
{
	Object_wx_GenericProgressDialog *pThis = Object_wx_GenericProgressDialog::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int _rtn = pThis->GetEntity()->GetValue();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_GenericProgressDialog, __GetRange, "GetRange")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_GenericProgressDialog, __GetRange)
{
	Object_wx_GenericProgressDialog *pThis = Object_wx_GenericProgressDialog::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int _rtn = pThis->GetEntity()->GetRange();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_GenericProgressDialog, __GetMessage, "GetMessage")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_GenericProgressDialog, __GetMessage)
{
	Object_wx_GenericProgressDialog *pThis = Object_wx_GenericProgressDialog::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxString _rtn = pThis->GetEntity()->GetMessage();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_GenericProgressDialog, __Pulse, "Pulse")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "newmsg", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "skip", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_GenericProgressDialog, __Pulse)
{
	Object_wx_GenericProgressDialog *pThis = Object_wx_GenericProgressDialog::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxString& newmsg = arg.GetNumber(0)
	//bool* skip = arg.GetNumber(1)
	//bool _rtn = pThis->GetEntity()->Pulse(newmsg, skip);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_GenericProgressDialog, __Resume, "Resume")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_GenericProgressDialog, __Resume)
{
	Object_wx_GenericProgressDialog *pThis = Object_wx_GenericProgressDialog::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->Resume();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_GenericProgressDialog, __SetRange, "SetRange")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "maximum", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_GenericProgressDialog, __SetRange)
{
	Object_wx_GenericProgressDialog *pThis = Object_wx_GenericProgressDialog::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int maximum = arg.GetNumber(0)
	//pThis->GetEntity()->SetRange(maximum);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_GenericProgressDialog, __WasCancelled, "WasCancelled")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_GenericProgressDialog, __WasCancelled)
{
	Object_wx_GenericProgressDialog *pThis = Object_wx_GenericProgressDialog::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//bool _rtn = pThis->GetEntity()->WasCancelled();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_GenericProgressDialog, __WasSkipped, "WasSkipped")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_GenericProgressDialog, __WasSkipped)
{
	Object_wx_GenericProgressDialog *pThis = Object_wx_GenericProgressDialog::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//bool _rtn = pThis->GetEntity()->WasSkipped();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_GenericProgressDialog, __Update, "Update")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "value", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "newmsg", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "skip", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_GenericProgressDialog, __Update)
{
	Object_wx_GenericProgressDialog *pThis = Object_wx_GenericProgressDialog::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int value = arg.GetNumber(0)
	//const wxString& newmsg = arg.GetNumber(1)
	//bool* skip = arg.GetNumber(2)
	//bool _rtn = pThis->GetEntity()->Update(value, newmsg, skip);
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Class implementation for wxGenericProgressDialog
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_GenericProgressDialog)
{
	// Constructor assignment
	Gura_AssignFunction(__GenericProgressDialog);
	// Method assignment
	Gura_AssignMethod(wx_GenericProgressDialog, __GetValue);
	Gura_AssignMethod(wx_GenericProgressDialog, __GetRange);
	Gura_AssignMethod(wx_GenericProgressDialog, __GetMessage);
	Gura_AssignMethod(wx_GenericProgressDialog, __Pulse);
	Gura_AssignMethod(wx_GenericProgressDialog, __Resume);
	Gura_AssignMethod(wx_GenericProgressDialog, __SetRange);
	Gura_AssignMethod(wx_GenericProgressDialog, __WasCancelled);
	Gura_AssignMethod(wx_GenericProgressDialog, __WasSkipped);
	Gura_AssignMethod(wx_GenericProgressDialog, __Update);
}

Gura_ImplementDescendantCreator(wx_GenericProgressDialog)
{
	return new Object_wx_GenericProgressDialog((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
