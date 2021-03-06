//----------------------------------------------------------------------------
// wxStaticLine
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Gura interfaces for wxStaticLine
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Object implementation for wxStaticLine
//----------------------------------------------------------------------------
Object_wx_StaticLine::~Object_wx_StaticLine()
{
}

Object *Object_wx_StaticLine::Clone() const
{
	return nullptr;
}

String Object_wx_StaticLine::ToString(bool exprFlag)
{
	String rtn("<wx.StaticLine:");
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
Gura_DeclareFunctionAlias(__StaticLine, "StaticLine")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	SetClassToConstruct(Gura_UserClass(wx_StaticLine));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(__StaticLine)
{
	//wxStaticLine();
	return Value::Nil;
}

Gura_DeclareFunctionAlias(__StaticLine_1, "StaticLine_1")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "parent", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "id", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "pos", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "size", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "style", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "name", VTYPE_number, OCCUR_Once);
	SetClassToConstruct(Gura_UserClass(wx_StaticLine));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(__StaticLine_1)
{
	//wxWindow* parent = arg.GetNumber(0)
	//wxWindowID id = arg.GetNumber(1)
	//const wxPoint& pos = arg.GetNumber(2)
	//const wxSize& size = arg.GetNumber(3)
	//long style = arg.GetNumber(4)
	//const wxString& name = arg.GetNumber(5)
	//wxStaticLine(parent, id, pos, size, style, name);
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Method implementation
//----------------------------------------------------------------------------
Gura_DeclareMethodAlias(wx_StaticLine, __Create, "Create")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "parent", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "id", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "pos", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "size", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "style", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "name", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StaticLine, __Create)
{
	Object_wx_StaticLine *pThis = Object_wx_StaticLine::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxWindow* parent = arg.GetNumber(0)
	//wxWindowID id = arg.GetNumber(1)
	//const wxPoint& pos = arg.GetNumber(2)
	//const wxSize& size = arg.GetNumber(3)
	//long style = arg.GetNumber(4)
	//const wxString& name = arg.GetNumber(5)
	//bool _rtn = pThis->GetEntity()->Create(parent, id, pos, size, style, name);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_StaticLine, __GetDefaultSize, "GetDefaultSize")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StaticLine, __GetDefaultSize)
{
	Object_wx_StaticLine *pThis = Object_wx_StaticLine::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int _rtn = pThis->GetEntity()->GetDefaultSize();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_StaticLine, __IsVertical, "IsVertical")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_StaticLine, __IsVertical)
{
	Object_wx_StaticLine *pThis = Object_wx_StaticLine::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//bool _rtn = pThis->GetEntity()->IsVertical();
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Class implementation for wxStaticLine
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_StaticLine)
{
	// Constructor assignment
	Gura_AssignFunction(__StaticLine);
	Gura_AssignFunction(__StaticLine_1);
	// Method assignment
	Gura_AssignMethod(wx_StaticLine, __Create);
	Gura_AssignMethod(wx_StaticLine, __GetDefaultSize);
	Gura_AssignMethod(wx_StaticLine, __IsVertical);
}

Gura_ImplementDescendantCreator(wx_StaticLine)
{
	return new Object_wx_StaticLine((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
