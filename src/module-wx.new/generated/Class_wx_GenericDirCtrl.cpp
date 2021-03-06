//----------------------------------------------------------------------------
// wxGenericDirCtrl
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Gura interfaces for wxGenericDirCtrl
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Object implementation for wxGenericDirCtrl
//----------------------------------------------------------------------------
Object_wx_GenericDirCtrl::~Object_wx_GenericDirCtrl()
{
}

Object *Object_wx_GenericDirCtrl::Clone() const
{
	return nullptr;
}

String Object_wx_GenericDirCtrl::ToString(bool exprFlag)
{
	String rtn("<wx.GenericDirCtrl:");
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
Gura_DeclareFunctionAlias(__GenericDirCtrl, "GenericDirCtrl")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	SetClassToConstruct(Gura_UserClass(wx_GenericDirCtrl));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(__GenericDirCtrl)
{
	//wxGenericDirCtrl();
	return Value::Nil;
}

Gura_DeclareFunctionAlias(__GenericDirCtrl_1, "GenericDirCtrl_1")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "parent", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "id", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "dir", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "pos", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "size", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "style", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "filter", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "defaultFilter", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "name", VTYPE_number, OCCUR_Once);
	SetClassToConstruct(Gura_UserClass(wx_GenericDirCtrl));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(__GenericDirCtrl_1)
{
	//wxWindow* parent = arg.GetNumber(0)
	//wxWindowID id = arg.GetNumber(1)
	//const wxString& dir = arg.GetNumber(2)
	//const wxPoint& pos = arg.GetNumber(3)
	//const wxSize& size = arg.GetNumber(4)
	//long style = arg.GetNumber(5)
	//const wxString& filter = arg.GetNumber(6)
	//int defaultFilter = arg.GetNumber(7)
	//const wxString& name = arg.GetNumber(8)
	//wxGenericDirCtrl(parent, id, dir, pos, size, style, filter, defaultFilter, name);
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Method implementation
//----------------------------------------------------------------------------
Gura_DeclareMethodAlias(wx_GenericDirCtrl, __CollapsePath, "CollapsePath")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "path", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_GenericDirCtrl, __CollapsePath)
{
	Object_wx_GenericDirCtrl *pThis = Object_wx_GenericDirCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxString& path = arg.GetNumber(0)
	//bool _rtn = pThis->GetEntity()->CollapsePath(path);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_GenericDirCtrl, __CollapseTree, "CollapseTree")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_GenericDirCtrl, __CollapseTree)
{
	Object_wx_GenericDirCtrl *pThis = Object_wx_GenericDirCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->CollapseTree();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_GenericDirCtrl, __Create, "Create")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "parent", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "id", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "dir", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "pos", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "size", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "style", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "filter", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "defaultFilter", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "name", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_GenericDirCtrl, __Create)
{
	Object_wx_GenericDirCtrl *pThis = Object_wx_GenericDirCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxWindow* parent = arg.GetNumber(0)
	//wxWindowID id = arg.GetNumber(1)
	//const wxString& dir = arg.GetNumber(2)
	//const wxPoint& pos = arg.GetNumber(3)
	//const wxSize& size = arg.GetNumber(4)
	//long style = arg.GetNumber(5)
	//const wxString& filter = arg.GetNumber(6)
	//int defaultFilter = arg.GetNumber(7)
	//const wxString& name = arg.GetNumber(8)
	//bool _rtn = pThis->GetEntity()->Create(parent, id, dir, pos, size, style, filter, defaultFilter, name);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_GenericDirCtrl, __ExpandPath, "ExpandPath")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "path", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_GenericDirCtrl, __ExpandPath)
{
	Object_wx_GenericDirCtrl *pThis = Object_wx_GenericDirCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxString& path = arg.GetNumber(0)
	//bool _rtn = pThis->GetEntity()->ExpandPath(path);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_GenericDirCtrl, __GetDefaultPath, "GetDefaultPath")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_GenericDirCtrl, __GetDefaultPath)
{
	Object_wx_GenericDirCtrl *pThis = Object_wx_GenericDirCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxString _rtn = pThis->GetEntity()->GetDefaultPath();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_GenericDirCtrl, __GetFilePath, "GetFilePath")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_GenericDirCtrl, __GetFilePath)
{
	Object_wx_GenericDirCtrl *pThis = Object_wx_GenericDirCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxString _rtn = pThis->GetEntity()->GetFilePath();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_GenericDirCtrl, __GetFilePaths, "GetFilePaths")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "paths", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_GenericDirCtrl, __GetFilePaths)
{
	Object_wx_GenericDirCtrl *pThis = Object_wx_GenericDirCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxArrayString& paths = arg.GetNumber(0)
	//pThis->GetEntity()->GetFilePaths(paths);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_GenericDirCtrl, __GetFilter, "GetFilter")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_GenericDirCtrl, __GetFilter)
{
	Object_wx_GenericDirCtrl *pThis = Object_wx_GenericDirCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxString _rtn = pThis->GetEntity()->GetFilter();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_GenericDirCtrl, __GetFilterIndex, "GetFilterIndex")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_GenericDirCtrl, __GetFilterIndex)
{
	Object_wx_GenericDirCtrl *pThis = Object_wx_GenericDirCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int _rtn = pThis->GetEntity()->GetFilterIndex();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_GenericDirCtrl, __GetFilterListCtrl, "GetFilterListCtrl")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_GenericDirCtrl, __GetFilterListCtrl)
{
	Object_wx_GenericDirCtrl *pThis = Object_wx_GenericDirCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxDirFilterListCtrl* _rtn = pThis->GetEntity()->GetFilterListCtrl();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_GenericDirCtrl, __GetPath, "GetPath")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_GenericDirCtrl, __GetPath)
{
	Object_wx_GenericDirCtrl *pThis = Object_wx_GenericDirCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxString _rtn = pThis->GetEntity()->GetPath();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_GenericDirCtrl, __GetPath_1, "GetPath_1")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "itemId", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_GenericDirCtrl, __GetPath_1)
{
	Object_wx_GenericDirCtrl *pThis = Object_wx_GenericDirCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxTreeItemId itemId = arg.GetNumber(0)
	//wxString _rtn = pThis->GetEntity()->GetPath(itemId);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_GenericDirCtrl, __GetPaths, "GetPaths")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "paths", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_GenericDirCtrl, __GetPaths)
{
	Object_wx_GenericDirCtrl *pThis = Object_wx_GenericDirCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxArrayString& paths = arg.GetNumber(0)
	//pThis->GetEntity()->GetPaths(paths);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_GenericDirCtrl, __GetRootId, "GetRootId")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_GenericDirCtrl, __GetRootId)
{
	Object_wx_GenericDirCtrl *pThis = Object_wx_GenericDirCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxTreeItemId _rtn = pThis->GetEntity()->GetRootId();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_GenericDirCtrl, __GetTreeCtrl, "GetTreeCtrl")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_GenericDirCtrl, __GetTreeCtrl)
{
	Object_wx_GenericDirCtrl *pThis = Object_wx_GenericDirCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxTreeCtrl* _rtn = pThis->GetEntity()->GetTreeCtrl();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_GenericDirCtrl, __Init, "Init")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_GenericDirCtrl, __Init)
{
	Object_wx_GenericDirCtrl *pThis = Object_wx_GenericDirCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->Init();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_GenericDirCtrl, __ReCreateTree, "ReCreateTree")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_GenericDirCtrl, __ReCreateTree)
{
	Object_wx_GenericDirCtrl *pThis = Object_wx_GenericDirCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->ReCreateTree();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_GenericDirCtrl, __SetDefaultPath, "SetDefaultPath")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "path", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_GenericDirCtrl, __SetDefaultPath)
{
	Object_wx_GenericDirCtrl *pThis = Object_wx_GenericDirCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxString& path = arg.GetNumber(0)
	//pThis->GetEntity()->SetDefaultPath(path);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_GenericDirCtrl, __SetFilter, "SetFilter")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "filter", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_GenericDirCtrl, __SetFilter)
{
	Object_wx_GenericDirCtrl *pThis = Object_wx_GenericDirCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxString& filter = arg.GetNumber(0)
	//pThis->GetEntity()->SetFilter(filter);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_GenericDirCtrl, __SetFilterIndex, "SetFilterIndex")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "n", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_GenericDirCtrl, __SetFilterIndex)
{
	Object_wx_GenericDirCtrl *pThis = Object_wx_GenericDirCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int n = arg.GetNumber(0)
	//pThis->GetEntity()->SetFilterIndex(n);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_GenericDirCtrl, __SetPath, "SetPath")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "path", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_GenericDirCtrl, __SetPath)
{
	Object_wx_GenericDirCtrl *pThis = Object_wx_GenericDirCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxString& path = arg.GetNumber(0)
	//pThis->GetEntity()->SetPath(path);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_GenericDirCtrl, __ShowHidden, "ShowHidden")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "show", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_GenericDirCtrl, __ShowHidden)
{
	Object_wx_GenericDirCtrl *pThis = Object_wx_GenericDirCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//bool show = arg.GetNumber(0)
	//pThis->GetEntity()->ShowHidden(show);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_GenericDirCtrl, __SelectPath, "SelectPath")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "path", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "select", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_GenericDirCtrl, __SelectPath)
{
	Object_wx_GenericDirCtrl *pThis = Object_wx_GenericDirCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxString& path = arg.GetNumber(0)
	//bool select = arg.GetNumber(1)
	//pThis->GetEntity()->SelectPath(path, select);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_GenericDirCtrl, __SelectPaths, "SelectPaths")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "paths", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_GenericDirCtrl, __SelectPaths)
{
	Object_wx_GenericDirCtrl *pThis = Object_wx_GenericDirCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxArrayString& paths = arg.GetNumber(0)
	//pThis->GetEntity()->SelectPaths(paths);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_GenericDirCtrl, __UnselectAll, "UnselectAll")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_GenericDirCtrl, __UnselectAll)
{
	Object_wx_GenericDirCtrl *pThis = Object_wx_GenericDirCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->UnselectAll();
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Class implementation for wxGenericDirCtrl
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_GenericDirCtrl)
{
	// Constructor assignment
	Gura_AssignFunction(__GenericDirCtrl);
	Gura_AssignFunction(__GenericDirCtrl_1);
	// Method assignment
	Gura_AssignMethod(wx_GenericDirCtrl, __CollapsePath);
	Gura_AssignMethod(wx_GenericDirCtrl, __CollapseTree);
	Gura_AssignMethod(wx_GenericDirCtrl, __Create);
	Gura_AssignMethod(wx_GenericDirCtrl, __ExpandPath);
	Gura_AssignMethod(wx_GenericDirCtrl, __GetDefaultPath);
	Gura_AssignMethod(wx_GenericDirCtrl, __GetFilePath);
	Gura_AssignMethod(wx_GenericDirCtrl, __GetFilePaths);
	Gura_AssignMethod(wx_GenericDirCtrl, __GetFilter);
	Gura_AssignMethod(wx_GenericDirCtrl, __GetFilterIndex);
	Gura_AssignMethod(wx_GenericDirCtrl, __GetFilterListCtrl);
	Gura_AssignMethod(wx_GenericDirCtrl, __GetPath);
	Gura_AssignMethod(wx_GenericDirCtrl, __GetPath_1);
	Gura_AssignMethod(wx_GenericDirCtrl, __GetPaths);
	Gura_AssignMethod(wx_GenericDirCtrl, __GetRootId);
	Gura_AssignMethod(wx_GenericDirCtrl, __GetTreeCtrl);
	Gura_AssignMethod(wx_GenericDirCtrl, __Init);
	Gura_AssignMethod(wx_GenericDirCtrl, __ReCreateTree);
	Gura_AssignMethod(wx_GenericDirCtrl, __SetDefaultPath);
	Gura_AssignMethod(wx_GenericDirCtrl, __SetFilter);
	Gura_AssignMethod(wx_GenericDirCtrl, __SetFilterIndex);
	Gura_AssignMethod(wx_GenericDirCtrl, __SetPath);
	Gura_AssignMethod(wx_GenericDirCtrl, __ShowHidden);
	Gura_AssignMethod(wx_GenericDirCtrl, __SelectPath);
	Gura_AssignMethod(wx_GenericDirCtrl, __SelectPaths);
	Gura_AssignMethod(wx_GenericDirCtrl, __UnselectAll);
}

Gura_ImplementDescendantCreator(wx_GenericDirCtrl)
{
	return new Object_wx_GenericDirCtrl((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
