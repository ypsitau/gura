//----------------------------------------------------------------------------
// wxRichTextStdRenderer
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Gura interfaces for wxRichTextStdRenderer
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Object implementation for wxRichTextStdRenderer
//----------------------------------------------------------------------------
Object_wx_RichTextStdRenderer::~Object_wx_RichTextStdRenderer()
{
}

Object *Object_wx_RichTextStdRenderer::Clone() const
{
	return nullptr;
}

String Object_wx_RichTextStdRenderer::ToString(bool exprFlag)
{
	String rtn("<wx.RichTextStdRenderer:");
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
Gura_DeclareMethod(wx_RichTextStdRenderer, wxRichTextStdRenderer)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_RichTextStdRenderer, wxRichTextStdRenderer)
{
	Object_wx_RichTextStdRenderer *pThis = Object_wx_RichTextStdRenderer::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->wxRichTextStdRenderer();
	return Value::Nil;
}

Gura_DeclareMethod(wx_RichTextStdRenderer, DrawStandardBullet)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "paragraph", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "dc", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "attr", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "rect", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_RichTextStdRenderer, DrawStandardBullet)
{
	Object_wx_RichTextStdRenderer *pThis = Object_wx_RichTextStdRenderer::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int paragraph = arg.GetNumber(0)
	//int dc = arg.GetNumber(1)
	//int attr = arg.GetNumber(2)
	//int rect = arg.GetNumber(3)
	//pThis->GetEntity()->DrawStandardBullet();
	return Value::Nil;
}

Gura_DeclareMethod(wx_RichTextStdRenderer, DrawTextBullet)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "paragraph", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "dc", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "attr", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "rect", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "text", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_RichTextStdRenderer, DrawTextBullet)
{
	Object_wx_RichTextStdRenderer *pThis = Object_wx_RichTextStdRenderer::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int paragraph = arg.GetNumber(0)
	//int dc = arg.GetNumber(1)
	//int attr = arg.GetNumber(2)
	//int rect = arg.GetNumber(3)
	//int text = arg.GetNumber(4)
	//pThis->GetEntity()->DrawTextBullet();
	return Value::Nil;
}

Gura_DeclareMethod(wx_RichTextStdRenderer, DrawBitmapBullet)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "paragraph", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "dc", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "attr", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "rect", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_RichTextStdRenderer, DrawBitmapBullet)
{
	Object_wx_RichTextStdRenderer *pThis = Object_wx_RichTextStdRenderer::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int paragraph = arg.GetNumber(0)
	//int dc = arg.GetNumber(1)
	//int attr = arg.GetNumber(2)
	//int rect = arg.GetNumber(3)
	//pThis->GetEntity()->DrawBitmapBullet();
	return Value::Nil;
}

Gura_DeclareMethod(wx_RichTextStdRenderer, EnumerateStandardBulletNames)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "bulletNames", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_RichTextStdRenderer, EnumerateStandardBulletNames)
{
	Object_wx_RichTextStdRenderer *pThis = Object_wx_RichTextStdRenderer::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int bulletNames = arg.GetNumber(0)
	//pThis->GetEntity()->EnumerateStandardBulletNames();
	return Value::Nil;
}

Gura_DeclareMethod(wx_RichTextStdRenderer, MeasureBullet)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "paragraph", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "dc", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "attr", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "sz", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_RichTextStdRenderer, MeasureBullet)
{
	Object_wx_RichTextStdRenderer *pThis = Object_wx_RichTextStdRenderer::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int paragraph = arg.GetNumber(0)
	//int dc = arg.GetNumber(1)
	//int attr = arg.GetNumber(2)
	//int sz = arg.GetNumber(3)
	//pThis->GetEntity()->MeasureBullet();
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Class implementation for wxRichTextStdRenderer
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_RichTextStdRenderer)
{
	Gura_AssignMethod(wx_RichTextStdRenderer, wxRichTextStdRenderer);
	Gura_AssignMethod(wx_RichTextStdRenderer, DrawStandardBullet);
	Gura_AssignMethod(wx_RichTextStdRenderer, DrawTextBullet);
	Gura_AssignMethod(wx_RichTextStdRenderer, DrawBitmapBullet);
	Gura_AssignMethod(wx_RichTextStdRenderer, EnumerateStandardBulletNames);
	Gura_AssignMethod(wx_RichTextStdRenderer, MeasureBullet);
}

Gura_ImplementDescendantCreator(wx_RichTextStdRenderer)
{
	return new Object_wx_RichTextStdRenderer((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
