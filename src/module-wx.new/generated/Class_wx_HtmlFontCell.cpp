//----------------------------------------------------------------------------
// wxHtmlFontCell
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Gura interfaces for wxHtmlFontCell
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Object implementation for wxHtmlFontCell
//----------------------------------------------------------------------------
Object_wx_HtmlFontCell::~Object_wx_HtmlFontCell()
{
}

Object *Object_wx_HtmlFontCell::Clone() const
{
	return nullptr;
}

String Object_wx_HtmlFontCell::ToString(bool exprFlag)
{
	String rtn("<wx.HtmlFontCell:");
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
Gura_DeclareMethod(wx_HtmlFontCell, wxHtmlFontCell)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "font", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_HtmlFontCell, wxHtmlFontCell)
{
	Signal &sig = env.GetSignal();
	Object_wx_HtmlFontCell *pThis = Object_wx_HtmlFontCell::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	//int font = arg.GetNumber(0)
	//pThis->GetEntity()->wxHtmlFontCell();
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Class implementation for wxHtmlFontCell
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_HtmlFontCell)
{
	Gura_AssignMethod(wx_HtmlFontCell, wxHtmlFontCell);
}

Gura_ImplementDescendantCreator(wx_HtmlFontCell)
{
	return new Object_wx_HtmlFontCell((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
