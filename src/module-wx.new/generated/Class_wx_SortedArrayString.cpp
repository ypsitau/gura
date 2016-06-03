//----------------------------------------------------------------------------
// wxSortedArrayString
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Gura interfaces for wxSortedArrayString
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Object implementation for wxSortedArrayString
//----------------------------------------------------------------------------
Object_wx_SortedArrayString::~Object_wx_SortedArrayString()
{
}

Object *Object_wx_SortedArrayString::Clone() const
{
	return nullptr;
}

String Object_wx_SortedArrayString::ToString(bool exprFlag)
{
	String rtn("<wx.SortedArrayString:");
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
Gura_DeclareFunctionAlias(__wxSortedArrayString, "wxSortedArrayString")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	SetClassToConstruct(Gura_UserClass(wx_SortedArrayString));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(__wxSortedArrayString)
{
	//wxSortedArrayString();
	return Value::Nil;
}

Gura_DeclareFunctionAlias(__wxSortedArrayString_1, "wxSortedArrayString_1")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "compareFunction", VTYPE_number, OCCUR_Once);
	SetClassToConstruct(Gura_UserClass(wx_SortedArrayString));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(__wxSortedArrayString_1)
{
	//int compareFunction = arg.GetNumber(0)
	//wxSortedArrayString();
	return Value::Nil;
}

Gura_DeclareFunctionAlias(__wxSortedArrayString_2, "wxSortedArrayString_2")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "array", VTYPE_number, OCCUR_Once);
	SetClassToConstruct(Gura_UserClass(wx_SortedArrayString));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(__wxSortedArrayString_2)
{
	//int array = arg.GetNumber(0)
	//wxSortedArrayString();
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Method implementation
//----------------------------------------------------------------------------
Gura_DeclareMethodAlias(wx_SortedArrayString, __Add, "Add")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "str", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "copies", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_SortedArrayString, __Add)
{
	Object_wx_SortedArrayString *pThis = Object_wx_SortedArrayString::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int str = arg.GetNumber(0)
	//int copies = arg.GetNumber(1)
	//pThis->GetEntity()->Add();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_SortedArrayString, __Index, "Index")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "sz", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "bCase", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "bFromEnd", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_SortedArrayString, __Index)
{
	Object_wx_SortedArrayString *pThis = Object_wx_SortedArrayString::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int sz = arg.GetNumber(0)
	//int bCase = arg.GetNumber(1)
	//int bFromEnd = arg.GetNumber(2)
	//pThis->GetEntity()->Index();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_SortedArrayString, __Insert, "Insert")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "str", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "nIndex", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "copies", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_SortedArrayString, __Insert)
{
	Object_wx_SortedArrayString *pThis = Object_wx_SortedArrayString::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int str = arg.GetNumber(0)
	//int nIndex = arg.GetNumber(1)
	//int copies = arg.GetNumber(2)
	//pThis->GetEntity()->Insert();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_SortedArrayString, __Sort, "Sort")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "reverseOrder", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_SortedArrayString, __Sort)
{
	Object_wx_SortedArrayString *pThis = Object_wx_SortedArrayString::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int reverseOrder = arg.GetNumber(0)
	//pThis->GetEntity()->Sort();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_SortedArrayString, __Sort_1, "Sort_1")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "compareFunction", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_SortedArrayString, __Sort_1)
{
	Object_wx_SortedArrayString *pThis = Object_wx_SortedArrayString::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int compareFunction = arg.GetNumber(0)
	//pThis->GetEntity()->Sort();
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Class implementation for wxSortedArrayString
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_SortedArrayString)
{
	// Constructor assignment
	Gura_AssignFunction(__wxSortedArrayString);
	Gura_AssignFunction(__wxSortedArrayString_1);
	Gura_AssignFunction(__wxSortedArrayString_2);
	// Method assignment
	Gura_AssignMethod(wx_SortedArrayString, __Add);
	Gura_AssignMethod(wx_SortedArrayString, __Index);
	Gura_AssignMethod(wx_SortedArrayString, __Insert);
	Gura_AssignMethod(wx_SortedArrayString, __Sort);
	Gura_AssignMethod(wx_SortedArrayString, __Sort_1);
}

Gura_ImplementDescendantCreator(wx_SortedArrayString)
{
	return new Object_wx_SortedArrayString((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
