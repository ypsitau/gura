//----------------------------------------------------------------------------
// wxDocMDIParentFrame
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Gura interfaces for wxDocMDIParentFrame
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Object implementation for wxDocMDIParentFrame
//----------------------------------------------------------------------------
Object_wx_DocMDIParentFrame::~Object_wx_DocMDIParentFrame()
{
}

Object *Object_wx_DocMDIParentFrame::Clone() const
{
	return nullptr;
}

String Object_wx_DocMDIParentFrame::ToString(bool exprFlag)
{
	String rtn("<wx.DocMDIParentFrame:");
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
Gura_DeclareMethod(wx_DocMDIParentFrame, wxDocMDIParentFrame)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_DocMDIParentFrame, wxDocMDIParentFrame)
{
	Signal &sig = env.GetSignal();
	Object_wx_DocMDIParentFrame *pThis = Object_wx_DocMDIParentFrame::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	//pThis->GetEntity()->wxDocMDIParentFrame();
	return Value::Nil;
}

Gura_DeclareMethod(wx_DocMDIParentFrame, wxDocMDIParentFrame_1)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "manager", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "parent", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "id", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "title", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "pos", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "size", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "style", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "name", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_DocMDIParentFrame, wxDocMDIParentFrame_1)
{
	Signal &sig = env.GetSignal();
	Object_wx_DocMDIParentFrame *pThis = Object_wx_DocMDIParentFrame::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	//int manager = arg.GetNumber(0)
	//int parent = arg.GetNumber(1)
	//int id = arg.GetNumber(2)
	//int title = arg.GetNumber(3)
	//int pos = arg.GetNumber(4)
	//int size = arg.GetNumber(5)
	//int style = arg.GetNumber(6)
	//int name = arg.GetNumber(7)
	//pThis->GetEntity()->wxDocMDIParentFrame();
	return Value::Nil;
}

Gura_DeclareMethod(wx_DocMDIParentFrame, ~wxDocMDIParentFrame)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_DocMDIParentFrame, ~wxDocMDIParentFrame)
{
	Signal &sig = env.GetSignal();
	Object_wx_DocMDIParentFrame *pThis = Object_wx_DocMDIParentFrame::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	//pThis->GetEntity()->~wxDocMDIParentFrame();
	return Value::Nil;
}

Gura_DeclareMethod(wx_DocMDIParentFrame, Create)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "manager", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "parent", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "id", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "title", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "pos", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "size", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "style", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "name", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_DocMDIParentFrame, Create)
{
	Signal &sig = env.GetSignal();
	Object_wx_DocMDIParentFrame *pThis = Object_wx_DocMDIParentFrame::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	//int manager = arg.GetNumber(0)
	//int parent = arg.GetNumber(1)
	//int id = arg.GetNumber(2)
	//int title = arg.GetNumber(3)
	//int pos = arg.GetNumber(4)
	//int size = arg.GetNumber(5)
	//int style = arg.GetNumber(6)
	//int name = arg.GetNumber(7)
	//pThis->GetEntity()->Create();
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Class implementation for wxDocMDIParentFrame
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_DocMDIParentFrame)
{
	Gura_AssignMethod(wx_DocMDIParentFrame, wxDocMDIParentFrame);
	Gura_AssignMethod(wx_DocMDIParentFrame, wxDocMDIParentFrame_1);
	Gura_AssignMethod(wx_DocMDIParentFrame, ~wxDocMDIParentFrame);
	Gura_AssignMethod(wx_DocMDIParentFrame, Create);
}

Gura_ImplementDescendantCreator(wx_DocMDIParentFrame)
{
	return new Object_wx_DocMDIParentFrame((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
