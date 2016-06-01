//----------------------------------------------------------------------------
// wxVScrolledWindow
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Gura interfaces for wxVScrolledWindow
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Object implementation for wxVScrolledWindow
//----------------------------------------------------------------------------
Object_wx_VScrolledWindow::~Object_wx_VScrolledWindow()
{
}

Object *Object_wx_VScrolledWindow::Clone() const
{
	return nullptr;
}

String Object_wx_VScrolledWindow::ToString(bool exprFlag)
{
	String rtn("<wx.VScrolledWindow:");
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
Gura_DeclareMethod(wx_VScrolledWindow, wxVScrolledWindow)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_VScrolledWindow, wxVScrolledWindow)
{
	Signal &sig = env.GetSignal();
	Object_wx_VScrolledWindow *pThis = Object_wx_VScrolledWindow::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	//pThis->GetEntity()->wxVScrolledWindow();
	return Value::Nil;
}

Gura_DeclareMethod(wx_VScrolledWindow, wxVScrolledWindow_1)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "parent", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "id", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "pos", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "size", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "style", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "name", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_VScrolledWindow, wxVScrolledWindow_1)
{
	Signal &sig = env.GetSignal();
	Object_wx_VScrolledWindow *pThis = Object_wx_VScrolledWindow::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	//int parent = arg.GetNumber(0)
	//int id = arg.GetNumber(1)
	//int pos = arg.GetNumber(2)
	//int size = arg.GetNumber(3)
	//int style = arg.GetNumber(4)
	//int name = arg.GetNumber(5)
	//pThis->GetEntity()->wxVScrolledWindow();
	return Value::Nil;
}

Gura_DeclareMethod(wx_VScrolledWindow, Create)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "parent", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "id", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "pos", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "size", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "style", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "name", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_VScrolledWindow, Create)
{
	Signal &sig = env.GetSignal();
	Object_wx_VScrolledWindow *pThis = Object_wx_VScrolledWindow::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	//int parent = arg.GetNumber(0)
	//int id = arg.GetNumber(1)
	//int pos = arg.GetNumber(2)
	//int size = arg.GetNumber(3)
	//int style = arg.GetNumber(4)
	//int name = arg.GetNumber(5)
	//pThis->GetEntity()->Create();
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Class implementation for wxVScrolledWindow
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_VScrolledWindow)
{
	Gura_AssignMethod(wx_VScrolledWindow, wxVScrolledWindow);
	Gura_AssignMethod(wx_VScrolledWindow, wxVScrolledWindow_1);
	Gura_AssignMethod(wx_VScrolledWindow, Create);
}

Gura_ImplementDescendantCreator(wx_VScrolledWindow)
{
	return new Object_wx_VScrolledWindow((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
