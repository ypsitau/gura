//----------------------------------------------------------------------------
// wxImageList
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Gura interfaces for wxImageList
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Object implementation for wxImageList
//----------------------------------------------------------------------------
Object_wx_ImageList::~Object_wx_ImageList()
{
}

Object *Object_wx_ImageList::Clone() const
{
	return nullptr;
}

String Object_wx_ImageList::ToString(bool exprFlag)
{
	String rtn("<wx.ImageList:");
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
Gura_DeclareFunctionAlias(__ImageList, "ImageList")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	SetClassToConstruct(Gura_UserClass(wx_ImageList));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(__ImageList)
{
	//wxImageList();
	return Value::Nil;
}

Gura_DeclareFunctionAlias(__ImageList_1, "ImageList_1")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "width", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "height", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "mask", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "initialCount", VTYPE_number, OCCUR_Once);
	SetClassToConstruct(Gura_UserClass(wx_ImageList));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(__ImageList_1)
{
	//int width = arg.GetNumber(0)
	//int height = arg.GetNumber(1)
	//bool mask = arg.GetNumber(2)
	//int initialCount = arg.GetNumber(3)
	//wxImageList(width, height, mask, initialCount);
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Method implementation
//----------------------------------------------------------------------------
Gura_DeclareMethodAlias(wx_ImageList, __Add, "Add")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "bitmap", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "mask", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_ImageList, __Add)
{
	Object_wx_ImageList *pThis = Object_wx_ImageList::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxBitmap& bitmap = arg.GetNumber(0)
	//const wxBitmap& mask = arg.GetNumber(1)
	//int _rtn = pThis->GetEntity()->Add(bitmap, mask);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_ImageList, __Add_1, "Add_1")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "bitmap", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "maskColour", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_ImageList, __Add_1)
{
	Object_wx_ImageList *pThis = Object_wx_ImageList::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxBitmap& bitmap = arg.GetNumber(0)
	//const wxColour& maskColour = arg.GetNumber(1)
	//int _rtn = pThis->GetEntity()->Add(bitmap, maskColour);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_ImageList, __Add_2, "Add_2")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "icon", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_ImageList, __Add_2)
{
	Object_wx_ImageList *pThis = Object_wx_ImageList::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxIcon& icon = arg.GetNumber(0)
	//int _rtn = pThis->GetEntity()->Add(icon);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_ImageList, __Create, "Create")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "width", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "height", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "mask", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "initialCount", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_ImageList, __Create)
{
	Object_wx_ImageList *pThis = Object_wx_ImageList::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int width = arg.GetNumber(0)
	//int height = arg.GetNumber(1)
	//bool mask = arg.GetNumber(2)
	//int initialCount = arg.GetNumber(3)
	//bool _rtn = pThis->GetEntity()->Create(width, height, mask, initialCount);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_ImageList, __Draw, "Draw")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "index", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "dc", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "x", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "y", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "flags", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "solidBackground", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_ImageList, __Draw)
{
	Object_wx_ImageList *pThis = Object_wx_ImageList::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int index = arg.GetNumber(0)
	//wxDC& dc = arg.GetNumber(1)
	//int x = arg.GetNumber(2)
	//int y = arg.GetNumber(3)
	//int flags = arg.GetNumber(4)
	//bool solidBackground = arg.GetNumber(5)
	//bool _rtn = pThis->GetEntity()->Draw(index, dc, x, y, flags, solidBackground);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_ImageList, __GetBitmap, "GetBitmap")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "index", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_ImageList, __GetBitmap)
{
	Object_wx_ImageList *pThis = Object_wx_ImageList::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int index = arg.GetNumber(0)
	//wxBitmap _rtn = pThis->GetEntity()->GetBitmap(index);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_ImageList, __GetIcon, "GetIcon")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "index", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_ImageList, __GetIcon)
{
	Object_wx_ImageList *pThis = Object_wx_ImageList::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int index = arg.GetNumber(0)
	//wxIcon _rtn = pThis->GetEntity()->GetIcon(index);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_ImageList, __GetImageCount, "GetImageCount")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_ImageList, __GetImageCount)
{
	Object_wx_ImageList *pThis = Object_wx_ImageList::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int _rtn = pThis->GetEntity()->GetImageCount();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_ImageList, __GetSize, "GetSize")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "index", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "width", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "height", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_ImageList, __GetSize)
{
	Object_wx_ImageList *pThis = Object_wx_ImageList::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int index = arg.GetNumber(0)
	//int& width = arg.GetNumber(1)
	//int& height = arg.GetNumber(2)
	//bool _rtn = pThis->GetEntity()->GetSize(index, width, height);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_ImageList, __GetSize_1, "GetSize_1")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_ImageList, __GetSize_1)
{
	Object_wx_ImageList *pThis = Object_wx_ImageList::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxSize _rtn = pThis->GetEntity()->GetSize();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_ImageList, __Remove, "Remove")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "index", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_ImageList, __Remove)
{
	Object_wx_ImageList *pThis = Object_wx_ImageList::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int index = arg.GetNumber(0)
	//bool _rtn = pThis->GetEntity()->Remove(index);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_ImageList, __RemoveAll, "RemoveAll")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_ImageList, __RemoveAll)
{
	Object_wx_ImageList *pThis = Object_wx_ImageList::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//bool _rtn = pThis->GetEntity()->RemoveAll();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_ImageList, __Replace, "Replace")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "index", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "bitmap", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "mask", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_ImageList, __Replace)
{
	Object_wx_ImageList *pThis = Object_wx_ImageList::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int index = arg.GetNumber(0)
	//const wxBitmap& bitmap = arg.GetNumber(1)
	//const wxBitmap& mask = arg.GetNumber(2)
	//bool _rtn = pThis->GetEntity()->Replace(index, bitmap, mask);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_ImageList, __Replace_1, "Replace_1")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "index", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "icon", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_ImageList, __Replace_1)
{
	Object_wx_ImageList *pThis = Object_wx_ImageList::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int index = arg.GetNumber(0)
	//const wxIcon& icon = arg.GetNumber(1)
	//bool _rtn = pThis->GetEntity()->Replace(index, icon);
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Class implementation for wxImageList
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_ImageList)
{
	// Constructor assignment
	Gura_AssignFunction(__ImageList);
	Gura_AssignFunction(__ImageList_1);
	// Method assignment
	Gura_AssignMethod(wx_ImageList, __Add);
	Gura_AssignMethod(wx_ImageList, __Add_1);
	Gura_AssignMethod(wx_ImageList, __Add_2);
	Gura_AssignMethod(wx_ImageList, __Create);
	Gura_AssignMethod(wx_ImageList, __Draw);
	Gura_AssignMethod(wx_ImageList, __GetBitmap);
	Gura_AssignMethod(wx_ImageList, __GetIcon);
	Gura_AssignMethod(wx_ImageList, __GetImageCount);
	Gura_AssignMethod(wx_ImageList, __GetSize);
	Gura_AssignMethod(wx_ImageList, __GetSize_1);
	Gura_AssignMethod(wx_ImageList, __Remove);
	Gura_AssignMethod(wx_ImageList, __RemoveAll);
	Gura_AssignMethod(wx_ImageList, __Replace);
	Gura_AssignMethod(wx_ImageList, __Replace_1);
}

Gura_ImplementDescendantCreator(wx_ImageList)
{
	return new Object_wx_ImageList((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
