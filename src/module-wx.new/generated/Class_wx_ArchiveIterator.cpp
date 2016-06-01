//----------------------------------------------------------------------------
// wxArchiveIterator
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Gura interfaces for wxArchiveIterator
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Object implementation for wxArchiveIterator
//----------------------------------------------------------------------------
Object_wx_ArchiveIterator::~Object_wx_ArchiveIterator()
{
}

Object *Object_wx_ArchiveIterator::Clone() const
{
	return nullptr;
}

String Object_wx_ArchiveIterator::ToString(bool exprFlag)
{
	String rtn("<wx.ArchiveIterator:");
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
Gura_DeclareMethod(wx_ArchiveIterator, wxArchiveIterator)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_ArchiveIterator, wxArchiveIterator)
{
	Signal &sig = env.GetSignal();
	Object_wx_ArchiveIterator *pThis = Object_wx_ArchiveIterator::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	//pThis->GetEntity()->wxArchiveIterator();
	return Value::Nil;
}

Gura_DeclareMethod(wx_ArchiveIterator, wxArchiveIterator_1)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "arc", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_ArchiveIterator, wxArchiveIterator_1)
{
	Signal &sig = env.GetSignal();
	Object_wx_ArchiveIterator *pThis = Object_wx_ArchiveIterator::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	//int arc = arg.GetNumber(0)
	//pThis->GetEntity()->wxArchiveIterator();
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Class implementation for wxArchiveIterator
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_ArchiveIterator)
{
	Gura_AssignMethod(wx_ArchiveIterator, wxArchiveIterator);
	Gura_AssignMethod(wx_ArchiveIterator, wxArchiveIterator_1);
}

Gura_ImplementDescendantCreator(wx_ArchiveIterator)
{
	return new Object_wx_ArchiveIterator((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
