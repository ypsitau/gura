//----------------------------------------------------------------------------
// wxHtmlSelection
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Gura interfaces for wxHtmlSelection
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Object implementation for wxHtmlSelection
//----------------------------------------------------------------------------
Object_wx_HtmlSelection::~Object_wx_HtmlSelection()
{
}

Object *Object_wx_HtmlSelection::Clone() const
{
	return nullptr;
}

String Object_wx_HtmlSelection::ToString(bool exprFlag)
{
	String rtn("<wx.HtmlSelection:");
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
Gura_DeclareMethod(wx_HtmlSelection, wxHtmlSelection)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_HtmlSelection, wxHtmlSelection)
{
	Object_wx_HtmlSelection *pThis = Object_wx_HtmlSelection::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->wxHtmlSelection();
	return Value::Nil;
}

Gura_DeclareMethod(wx_HtmlSelection, Set)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "fromPos", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "fromCell", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "toPos", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "toCell", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_HtmlSelection, Set)
{
	Object_wx_HtmlSelection *pThis = Object_wx_HtmlSelection::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int fromPos = arg.GetNumber(0)
	//int fromCell = arg.GetNumber(1)
	//int toPos = arg.GetNumber(2)
	//int toCell = arg.GetNumber(3)
	//pThis->GetEntity()->Set();
	return Value::Nil;
}

Gura_DeclareMethod(wx_HtmlSelection, Set_1)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "fromCell", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "toCell", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_HtmlSelection, Set_1)
{
	Object_wx_HtmlSelection *pThis = Object_wx_HtmlSelection::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int fromCell = arg.GetNumber(0)
	//int toCell = arg.GetNumber(1)
	//pThis->GetEntity()->Set();
	return Value::Nil;
}

Gura_DeclareMethod(wx_HtmlSelection, GetFromCell)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_HtmlSelection, GetFromCell)
{
	Object_wx_HtmlSelection *pThis = Object_wx_HtmlSelection::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->GetFromCell();
	return Value::Nil;
}

Gura_DeclareMethod(wx_HtmlSelection, GetToCell)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_HtmlSelection, GetToCell)
{
	Object_wx_HtmlSelection *pThis = Object_wx_HtmlSelection::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->GetToCell();
	return Value::Nil;
}

Gura_DeclareMethod(wx_HtmlSelection, GetFromPos)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_HtmlSelection, GetFromPos)
{
	Object_wx_HtmlSelection *pThis = Object_wx_HtmlSelection::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->GetFromPos();
	return Value::Nil;
}

Gura_DeclareMethod(wx_HtmlSelection, GetToPos)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_HtmlSelection, GetToPos)
{
	Object_wx_HtmlSelection *pThis = Object_wx_HtmlSelection::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->GetToPos();
	return Value::Nil;
}

Gura_DeclareMethod(wx_HtmlSelection, ClearFromToCharacterPos)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_HtmlSelection, ClearFromToCharacterPos)
{
	Object_wx_HtmlSelection *pThis = Object_wx_HtmlSelection::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->ClearFromToCharacterPos();
	return Value::Nil;
}

Gura_DeclareMethod(wx_HtmlSelection, AreFromToCharacterPosSet)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_HtmlSelection, AreFromToCharacterPosSet)
{
	Object_wx_HtmlSelection *pThis = Object_wx_HtmlSelection::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->AreFromToCharacterPosSet();
	return Value::Nil;
}

Gura_DeclareMethod(wx_HtmlSelection, SetFromCharacterPos)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "pos", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_HtmlSelection, SetFromCharacterPos)
{
	Object_wx_HtmlSelection *pThis = Object_wx_HtmlSelection::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int pos = arg.GetNumber(0)
	//pThis->GetEntity()->SetFromCharacterPos();
	return Value::Nil;
}

Gura_DeclareMethod(wx_HtmlSelection, SetToCharacterPos)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "pos", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_HtmlSelection, SetToCharacterPos)
{
	Object_wx_HtmlSelection *pThis = Object_wx_HtmlSelection::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int pos = arg.GetNumber(0)
	//pThis->GetEntity()->SetToCharacterPos();
	return Value::Nil;
}

Gura_DeclareMethod(wx_HtmlSelection, GetFromCharacterPos)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_HtmlSelection, GetFromCharacterPos)
{
	Object_wx_HtmlSelection *pThis = Object_wx_HtmlSelection::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->GetFromCharacterPos();
	return Value::Nil;
}

Gura_DeclareMethod(wx_HtmlSelection, GetToCharacterPos)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_HtmlSelection, GetToCharacterPos)
{
	Object_wx_HtmlSelection *pThis = Object_wx_HtmlSelection::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->GetToCharacterPos();
	return Value::Nil;
}

Gura_DeclareMethod(wx_HtmlSelection, IsEmpty)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_HtmlSelection, IsEmpty)
{
	Object_wx_HtmlSelection *pThis = Object_wx_HtmlSelection::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->IsEmpty();
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Class implementation for wxHtmlSelection
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_HtmlSelection)
{
	Gura_AssignMethod(wx_HtmlSelection, wxHtmlSelection);
	Gura_AssignMethod(wx_HtmlSelection, Set);
	Gura_AssignMethod(wx_HtmlSelection, Set_1);
	Gura_AssignMethod(wx_HtmlSelection, GetFromCell);
	Gura_AssignMethod(wx_HtmlSelection, GetToCell);
	Gura_AssignMethod(wx_HtmlSelection, GetFromPos);
	Gura_AssignMethod(wx_HtmlSelection, GetToPos);
	Gura_AssignMethod(wx_HtmlSelection, ClearFromToCharacterPos);
	Gura_AssignMethod(wx_HtmlSelection, AreFromToCharacterPosSet);
	Gura_AssignMethod(wx_HtmlSelection, SetFromCharacterPos);
	Gura_AssignMethod(wx_HtmlSelection, SetToCharacterPos);
	Gura_AssignMethod(wx_HtmlSelection, GetFromCharacterPos);
	Gura_AssignMethod(wx_HtmlSelection, GetToCharacterPos);
	Gura_AssignMethod(wx_HtmlSelection, IsEmpty);
}

Gura_ImplementDescendantCreator(wx_HtmlSelection)
{
	return new Object_wx_HtmlSelection((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
