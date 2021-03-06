//----------------------------------------------------------------------------
// wxPGChoices
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Gura interfaces for wxPGChoices
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Object implementation for wxPGChoices
//----------------------------------------------------------------------------
Object_wx_PGChoices::~Object_wx_PGChoices()
{
}

Object *Object_wx_PGChoices::Clone() const
{
	return nullptr;
}

String Object_wx_PGChoices::ToString(bool exprFlag)
{
	String rtn("<wx.PGChoices:");
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
Gura_DeclareFunctionAlias(__PGChoices, "PGChoices")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	SetClassToConstruct(Gura_UserClass(wx_PGChoices));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(__PGChoices)
{
	//wxPGChoices();
	return Value::Nil;
}

Gura_DeclareFunctionAlias(__PGChoices_1, "PGChoices_1")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "a", VTYPE_number, OCCUR_Once);
	SetClassToConstruct(Gura_UserClass(wx_PGChoices));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(__PGChoices_1)
{
	//const wxPGChoices& a = arg.GetNumber(0)
	//wxPGChoices(a);
	return Value::Nil;
}

Gura_DeclareFunctionAlias(__PGChoices_2, "PGChoices_2")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "labels", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "values", VTYPE_number, OCCUR_Once);
	SetClassToConstruct(Gura_UserClass(wx_PGChoices));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(__PGChoices_2)
{
	//const wxChar** labels = arg.GetNumber(0)
	//const long* values = arg.GetNumber(1)
	//wxPGChoices(labels, values);
	return Value::Nil;
}

Gura_DeclareFunctionAlias(__PGChoices_3, "PGChoices_3")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "labels", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "values", VTYPE_number, OCCUR_Once);
	SetClassToConstruct(Gura_UserClass(wx_PGChoices));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(__PGChoices_3)
{
	//const wxArrayString& labels = arg.GetNumber(0)
	//const wxArrayInt& values = arg.GetNumber(1)
	//wxPGChoices(labels, values);
	return Value::Nil;
}

Gura_DeclareFunctionAlias(__PGChoices_4, "PGChoices_4")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "data", VTYPE_number, OCCUR_Once);
	SetClassToConstruct(Gura_UserClass(wx_PGChoices));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(__PGChoices_4)
{
	//wxPGChoicesData* data = arg.GetNumber(0)
	//wxPGChoices(data);
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Method implementation
//----------------------------------------------------------------------------
Gura_DeclareMethodAlias(wx_PGChoices, __Add, "Add")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "labels", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "values", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_PGChoices, __Add)
{
	Object_wx_PGChoices *pThis = Object_wx_PGChoices::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxChar** labels = arg.GetNumber(0)
	//const ValArrItem* values = arg.GetNumber(1)
	//pThis->GetEntity()->Add(labels, values);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_PGChoices, __Add_1, "Add_1")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "arr", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "arrint", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_PGChoices, __Add_1)
{
	Object_wx_PGChoices *pThis = Object_wx_PGChoices::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxArrayString& arr = arg.GetNumber(0)
	//const wxArrayInt& arrint = arg.GetNumber(1)
	//pThis->GetEntity()->Add(arr, arrint);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_PGChoices, __Add_2, "Add_2")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "label", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "value", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_PGChoices, __Add_2)
{
	Object_wx_PGChoices *pThis = Object_wx_PGChoices::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxString& label = arg.GetNumber(0)
	//int value = arg.GetNumber(1)
	//wxPGChoiceEntry& _rtn = pThis->GetEntity()->Add(label, value);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_PGChoices, __Add_3, "Add_3")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "label", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "bitmap", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "value", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_PGChoices, __Add_3)
{
	Object_wx_PGChoices *pThis = Object_wx_PGChoices::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxString& label = arg.GetNumber(0)
	//const wxBitmap& bitmap = arg.GetNumber(1)
	//int value = arg.GetNumber(2)
	//wxPGChoiceEntry& _rtn = pThis->GetEntity()->Add(label, bitmap, value);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_PGChoices, __Add_4, "Add_4")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "entry", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_PGChoices, __Add_4)
{
	Object_wx_PGChoices *pThis = Object_wx_PGChoices::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxPGChoiceEntry& entry = arg.GetNumber(0)
	//wxPGChoiceEntry& _rtn = pThis->GetEntity()->Add(entry);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_PGChoices, __AddAsSorted, "AddAsSorted")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "label", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "value", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_PGChoices, __AddAsSorted)
{
	Object_wx_PGChoices *pThis = Object_wx_PGChoices::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxString& label = arg.GetNumber(0)
	//int value = arg.GetNumber(1)
	//wxPGChoiceEntry& _rtn = pThis->GetEntity()->AddAsSorted(label, value);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_PGChoices, __Assign, "Assign")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "a", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_PGChoices, __Assign)
{
	Object_wx_PGChoices *pThis = Object_wx_PGChoices::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxPGChoices& a = arg.GetNumber(0)
	//pThis->GetEntity()->Assign(a);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_PGChoices, __AssignData, "AssignData")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "data", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_PGChoices, __AssignData)
{
	Object_wx_PGChoices *pThis = Object_wx_PGChoices::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxPGChoicesData* data = arg.GetNumber(0)
	//pThis->GetEntity()->AssignData(data);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_PGChoices, __Clear, "Clear")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_PGChoices, __Clear)
{
	Object_wx_PGChoices *pThis = Object_wx_PGChoices::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->Clear();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_PGChoices, __Copy, "Copy")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_PGChoices, __Copy)
{
	Object_wx_PGChoices *pThis = Object_wx_PGChoices::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxPGChoices _rtn = pThis->GetEntity()->Copy();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_PGChoices, __GetLabel, "GetLabel")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "ind", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_PGChoices, __GetLabel)
{
	Object_wx_PGChoices *pThis = Object_wx_PGChoices::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//unsigned int ind = arg.GetNumber(0)
	//const wxString& _rtn = pThis->GetEntity()->GetLabel(ind);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_PGChoices, __GetCount, "GetCount")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_PGChoices, __GetCount)
{
	Object_wx_PGChoices *pThis = Object_wx_PGChoices::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//unsigned int _rtn = pThis->GetEntity()->GetCount();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_PGChoices, __GetValue, "GetValue")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "ind", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_PGChoices, __GetValue)
{
	Object_wx_PGChoices *pThis = Object_wx_PGChoices::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//unsigned int ind = arg.GetNumber(0)
	//int _rtn = pThis->GetEntity()->GetValue(ind);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_PGChoices, __GetValuesForStrings, "GetValuesForStrings")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "strings", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_PGChoices, __GetValuesForStrings)
{
	Object_wx_PGChoices *pThis = Object_wx_PGChoices::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxArrayString& strings = arg.GetNumber(0)
	//wxArrayInt _rtn = pThis->GetEntity()->GetValuesForStrings(strings);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_PGChoices, __GetIndicesForStrings, "GetIndicesForStrings")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "strings", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "unmatched", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_PGChoices, __GetIndicesForStrings)
{
	Object_wx_PGChoices *pThis = Object_wx_PGChoices::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxArrayString& strings = arg.GetNumber(0)
	//wxArrayString* unmatched = arg.GetNumber(1)
	//wxArrayInt _rtn = pThis->GetEntity()->GetIndicesForStrings(strings, unmatched);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_PGChoices, __Index, "Index")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "label", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_PGChoices, __Index)
{
	Object_wx_PGChoices *pThis = Object_wx_PGChoices::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxString& label = arg.GetNumber(0)
	//int _rtn = pThis->GetEntity()->Index(label);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_PGChoices, __Index_1, "Index_1")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "val", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_PGChoices, __Index_1)
{
	Object_wx_PGChoices *pThis = Object_wx_PGChoices::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int val = arg.GetNumber(0)
	//int _rtn = pThis->GetEntity()->Index(val);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_PGChoices, __Insert, "Insert")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "label", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "index", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "value", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_PGChoices, __Insert)
{
	Object_wx_PGChoices *pThis = Object_wx_PGChoices::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxString& label = arg.GetNumber(0)
	//int index = arg.GetNumber(1)
	//int value = arg.GetNumber(2)
	//wxPGChoiceEntry& _rtn = pThis->GetEntity()->Insert(label, index, value);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_PGChoices, __Insert_1, "Insert_1")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "entry", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "index", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_PGChoices, __Insert_1)
{
	Object_wx_PGChoices *pThis = Object_wx_PGChoices::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxPGChoiceEntry& entry = arg.GetNumber(0)
	//int index = arg.GetNumber(1)
	//wxPGChoiceEntry& _rtn = pThis->GetEntity()->Insert(entry, index);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_PGChoices, __IsOk, "IsOk")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_PGChoices, __IsOk)
{
	Object_wx_PGChoices *pThis = Object_wx_PGChoices::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//bool _rtn = pThis->GetEntity()->IsOk();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_PGChoices, __Item, "Item")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "i", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_PGChoices, __Item)
{
	Object_wx_PGChoices *pThis = Object_wx_PGChoices::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//unsigned int i = arg.GetNumber(0)
	//const wxPGChoiceEntry& _rtn = pThis->GetEntity()->Item(i);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_PGChoices, __Item_1, "Item_1")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	//DeclareArg(env, "i", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_PGChoices, __Item_1)
{
	Object_wx_PGChoices *pThis = Object_wx_PGChoices::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//unsigned int i = arg.GetNumber(0)
	//wxPGChoiceEntry& _rtn = pThis->GetEntity()->Item(i);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_PGChoices, __RemoveAt, "RemoveAt")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "nIndex", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "count", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_PGChoices, __RemoveAt)
{
	Object_wx_PGChoices *pThis = Object_wx_PGChoices::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//size_t nIndex = arg.GetNumber(0)
	//size_t count = arg.GetNumber(1)
	//pThis->GetEntity()->RemoveAt(nIndex, count);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_PGChoices, __Set, "Set")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "labels", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "values", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_PGChoices, __Set)
{
	Object_wx_PGChoices *pThis = Object_wx_PGChoices::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxChar** labels = arg.GetNumber(0)
	//const long* values = arg.GetNumber(1)
	//pThis->GetEntity()->Set(labels, values);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_PGChoices, __Set_1, "Set_1")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "labels", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "values", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_PGChoices, __Set_1)
{
	Object_wx_PGChoices *pThis = Object_wx_PGChoices::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//const wxArrayString& labels = arg.GetNumber(0)
	//const wxArrayInt& values = arg.GetNumber(1)
	//pThis->GetEntity()->Set(labels, values);
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_PGChoices, __AllocExclusive, "AllocExclusive")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_PGChoices, __AllocExclusive)
{
	Object_wx_PGChoices *pThis = Object_wx_PGChoices::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->AllocExclusive();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_PGChoices, __GetLabels, "GetLabels")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
}

Gura_ImplementMethod(wx_PGChoices, __GetLabels)
{
	Object_wx_PGChoices *pThis = Object_wx_PGChoices::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//wxArrayString _rtn = pThis->GetEntity()->GetLabels();
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Class implementation for wxPGChoices
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_PGChoices)
{
	// Constructor assignment
	Gura_AssignFunction(__PGChoices);
	Gura_AssignFunction(__PGChoices_1);
	Gura_AssignFunction(__PGChoices_2);
	Gura_AssignFunction(__PGChoices_3);
	Gura_AssignFunction(__PGChoices_4);
	// Method assignment
	Gura_AssignMethod(wx_PGChoices, __Add);
	Gura_AssignMethod(wx_PGChoices, __Add_1);
	Gura_AssignMethod(wx_PGChoices, __Add_2);
	Gura_AssignMethod(wx_PGChoices, __Add_3);
	Gura_AssignMethod(wx_PGChoices, __Add_4);
	Gura_AssignMethod(wx_PGChoices, __AddAsSorted);
	Gura_AssignMethod(wx_PGChoices, __Assign);
	Gura_AssignMethod(wx_PGChoices, __AssignData);
	Gura_AssignMethod(wx_PGChoices, __Clear);
	Gura_AssignMethod(wx_PGChoices, __Copy);
	Gura_AssignMethod(wx_PGChoices, __GetLabel);
	Gura_AssignMethod(wx_PGChoices, __GetCount);
	Gura_AssignMethod(wx_PGChoices, __GetValue);
	Gura_AssignMethod(wx_PGChoices, __GetValuesForStrings);
	Gura_AssignMethod(wx_PGChoices, __GetIndicesForStrings);
	Gura_AssignMethod(wx_PGChoices, __Index);
	Gura_AssignMethod(wx_PGChoices, __Index_1);
	Gura_AssignMethod(wx_PGChoices, __Insert);
	Gura_AssignMethod(wx_PGChoices, __Insert_1);
	Gura_AssignMethod(wx_PGChoices, __IsOk);
	Gura_AssignMethod(wx_PGChoices, __Item);
	Gura_AssignMethod(wx_PGChoices, __Item_1);
	Gura_AssignMethod(wx_PGChoices, __RemoveAt);
	Gura_AssignMethod(wx_PGChoices, __Set);
	Gura_AssignMethod(wx_PGChoices, __Set_1);
	Gura_AssignMethod(wx_PGChoices, __AllocExclusive);
	Gura_AssignMethod(wx_PGChoices, __GetLabels);
}

Gura_ImplementDescendantCreator(wx_PGChoices)
{
	return new Object_wx_PGChoices((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
