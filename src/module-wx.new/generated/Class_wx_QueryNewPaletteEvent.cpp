//----------------------------------------------------------------------------
// wxQueryNewPaletteEvent
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Gura interfaces for wxQueryNewPaletteEvent
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Object implementation for wxQueryNewPaletteEvent
//----------------------------------------------------------------------------
Object_wx_QueryNewPaletteEvent::~Object_wx_QueryNewPaletteEvent()
{
}

Object *Object_wx_QueryNewPaletteEvent::Clone() const
{
	return nullptr;
}

String Object_wx_QueryNewPaletteEvent::ToString(bool exprFlag)
{
	String rtn("<wx.QueryNewPaletteEvent:");
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
Gura_DeclareMethod(wx_QueryNewPaletteEvent, wxQueryNewPaletteEvent)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "winid", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_QueryNewPaletteEvent, wxQueryNewPaletteEvent)
{
	Signal &sig = env.GetSignal();
	Object_wx_QueryNewPaletteEvent *pThis = Object_wx_QueryNewPaletteEvent::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	//int winid = arg.GetNumber(0)
	//pThis->GetEntity()->wxQueryNewPaletteEvent();
	return Value::Nil;
}

Gura_DeclareMethod(wx_QueryNewPaletteEvent, SetPaletteRealized)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "realized", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_QueryNewPaletteEvent, SetPaletteRealized)
{
	Signal &sig = env.GetSignal();
	Object_wx_QueryNewPaletteEvent *pThis = Object_wx_QueryNewPaletteEvent::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	//int realized = arg.GetNumber(0)
	//pThis->GetEntity()->SetPaletteRealized();
	return Value::Nil;
}

Gura_DeclareMethod(wx_QueryNewPaletteEvent, GetPaletteRealized)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_QueryNewPaletteEvent, GetPaletteRealized)
{
	Signal &sig = env.GetSignal();
	Object_wx_QueryNewPaletteEvent *pThis = Object_wx_QueryNewPaletteEvent::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	//pThis->GetEntity()->GetPaletteRealized();
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Class implementation for wxQueryNewPaletteEvent
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_QueryNewPaletteEvent)
{
	Gura_AssignMethod(wx_QueryNewPaletteEvent, wxQueryNewPaletteEvent);
	Gura_AssignMethod(wx_QueryNewPaletteEvent, SetPaletteRealized);
	Gura_AssignMethod(wx_QueryNewPaletteEvent, GetPaletteRealized);
}

Gura_ImplementDescendantCreator(wx_QueryNewPaletteEvent)
{
	return new Object_wx_QueryNewPaletteEvent((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
