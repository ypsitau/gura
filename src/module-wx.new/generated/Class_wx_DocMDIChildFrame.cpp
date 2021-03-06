//----------------------------------------------------------------------------
// wxDocMDIChildFrame
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Gura interfaces for wxDocMDIChildFrame
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Object implementation for wxDocMDIChildFrame
//----------------------------------------------------------------------------
Object_wx_DocMDIChildFrame::~Object_wx_DocMDIChildFrame()
{
}

Object *Object_wx_DocMDIChildFrame::Clone() const
{
	return nullptr;
}

String Object_wx_DocMDIChildFrame::ToString(bool exprFlag)
{
	String rtn("<wx.DocMDIChildFrame:");
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
Gura_DeclareFunctionAlias(__DocMDIChildFrame, "DocMDIChildFrame")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "doc", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "view", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "parent", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "id", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "title", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "pos", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "size", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "style", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "name", VTYPE_number, OCCUR_Once);
	SetClassToConstruct(Gura_UserClass(wx_DocMDIChildFrame));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(__DocMDIChildFrame)
{
	//wxDocument* doc = arg.GetNumber(0)
	//wxView* view = arg.GetNumber(1)
	//wxMDIParentFrame* parent = arg.GetNumber(2)
	//wxWindowID id = arg.GetNumber(3)
	//const wxString& title = arg.GetNumber(4)
	//const wxPoint& pos = arg.GetNumber(5)
	//const wxSize& size = arg.GetNumber(6)
	//long style = arg.GetNumber(7)
	//const wxString& name = arg.GetNumber(8)
	//wxDocMDIChildFrame(doc, view, parent, id, title, pos, size, style, name);
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Method implementation
//----------------------------------------------------------------------------
Gura_DeclareMethodAlias(wx_DocMDIChildFrame, __GetDocument, "GetDocument")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_DocMDIChildFrame, __GetDocument)
{
	Object_wx_DocMDIChildFrame *pThis = Object_wx_DocMDIChildFrame::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxDocument* _rtn = pThis->GetEntity()->GetDocument();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_DocMDIChildFrame, __GetView, "GetView")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_DocMDIChildFrame, __GetView)
{
	Object_wx_DocMDIChildFrame *pThis = Object_wx_DocMDIChildFrame::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxView* _rtn = pThis->GetEntity()->GetView();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_DocMDIChildFrame, __SetDocument, "SetDocument")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "doc", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_DocMDIChildFrame, __SetDocument)
{
	Object_wx_DocMDIChildFrame *pThis = Object_wx_DocMDIChildFrame::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxDocument* doc = arg.GetNumber(0)
	//pThis->GetEntity()->SetDocument(doc);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_DocMDIChildFrame, __SetView, "SetView")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "view", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_DocMDIChildFrame, __SetView)
{
	Object_wx_DocMDIChildFrame *pThis = Object_wx_DocMDIChildFrame::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxView* view = arg.GetNumber(0)
	//pThis->GetEntity()->SetView(view);
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Class implementation for wxDocMDIChildFrame
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_DocMDIChildFrame)
{
	// Constructor assignment
	Gura_AssignFunction(__DocMDIChildFrame);
	// Method assignment
	Gura_AssignMethod(wx_DocMDIChildFrame, __GetDocument);
	Gura_AssignMethod(wx_DocMDIChildFrame, __GetView);
	Gura_AssignMethod(wx_DocMDIChildFrame, __SetDocument);
	Gura_AssignMethod(wx_DocMDIChildFrame, __SetView);
}

Gura_ImplementDescendantCreator(wx_DocMDIChildFrame)
{
	return new Object_wx_DocMDIChildFrame((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
