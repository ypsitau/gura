//----------------------------------------------------------------------------
// wxRichTextImage
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Gura interfaces for wxRichTextImage
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Object implementation for wxRichTextImage
//----------------------------------------------------------------------------
Object_wx_RichTextImage::~Object_wx_RichTextImage()
{
}

Object *Object_wx_RichTextImage::Clone() const
{
	return nullptr;
}

String Object_wx_RichTextImage::ToString(bool exprFlag)
{
	String rtn("<wx.RichTextImage:");
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
Gura_DeclareFunctionAlias(__wxRichTextImage, "wxRichTextImage")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "parent", VTYPE_number, OCCUR_Once);
	SetClassToConstruct(Gura_UserClass(wx_RichTextImage));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(__wxRichTextImage)
{
	//int parent = arg.GetNumber(0)
	//wxRichTextImage();
	return Value::Nil;
}

Gura_DeclareFunctionAlias(__wxRichTextImage_1, "wxRichTextImage_1")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "image", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "parent", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "charStyle", VTYPE_number, OCCUR_Once);
	SetClassToConstruct(Gura_UserClass(wx_RichTextImage));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(__wxRichTextImage_1)
{
	//int image = arg.GetNumber(0)
	//int parent = arg.GetNumber(1)
	//int charStyle = arg.GetNumber(2)
	//wxRichTextImage();
	return Value::Nil;
}

Gura_DeclareFunctionAlias(__wxRichTextImage_2, "wxRichTextImage_2")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "imageBlock", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "parent", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "charStyle", VTYPE_number, OCCUR_Once);
	SetClassToConstruct(Gura_UserClass(wx_RichTextImage));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(__wxRichTextImage_2)
{
	//int imageBlock = arg.GetNumber(0)
	//int parent = arg.GetNumber(1)
	//int charStyle = arg.GetNumber(2)
	//wxRichTextImage();
	return Value::Nil;
}

Gura_DeclareFunctionAlias(__wxRichTextImage_3, "wxRichTextImage_3")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	SetClassToConstruct(Gura_UserClass(wx_RichTextImage));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(__wxRichTextImage_3)
{
	//wxRichTextImage();
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Method implementation
//----------------------------------------------------------------------------
Gura_DeclareMethodAlias(wx_RichTextImage, __Draw, "Draw")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "dc", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "context", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "range", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "selection", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "rect", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "descent", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "style", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_RichTextImage, __Draw)
{
	Object_wx_RichTextImage *pThis = Object_wx_RichTextImage::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int dc = arg.GetNumber(0)
	//int context = arg.GetNumber(1)
	//int range = arg.GetNumber(2)
	//int selection = arg.GetNumber(3)
	//int rect = arg.GetNumber(4)
	//int descent = arg.GetNumber(5)
	//int style = arg.GetNumber(6)
	//pThis->GetEntity()->Draw();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RichTextImage, __Layout, "Layout")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "dc", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "context", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "rect", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "parentRect", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "style", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_RichTextImage, __Layout)
{
	Object_wx_RichTextImage *pThis = Object_wx_RichTextImage::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int dc = arg.GetNumber(0)
	//int context = arg.GetNumber(1)
	//int rect = arg.GetNumber(2)
	//int parentRect = arg.GetNumber(3)
	//int style = arg.GetNumber(4)
	//pThis->GetEntity()->Layout();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RichTextImage, __GetRangeSize, "GetRangeSize")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "range", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "size", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "descent", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "dc", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "context", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "flags", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "position", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "parentSize", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "partialExtents", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_RichTextImage, __GetRangeSize)
{
	Object_wx_RichTextImage *pThis = Object_wx_RichTextImage::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int range = arg.GetNumber(0)
	//int size = arg.GetNumber(1)
	//int descent = arg.GetNumber(2)
	//int dc = arg.GetNumber(3)
	//int context = arg.GetNumber(4)
	//int flags = arg.GetNumber(5)
	//int position = arg.GetNumber(6)
	//int parentSize = arg.GetNumber(7)
	//int partialExtents = arg.GetNumber(8)
	//pThis->GetEntity()->GetRangeSize();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RichTextImage, __GetNaturalSize, "GetNaturalSize")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_RichTextImage, __GetNaturalSize)
{
	Object_wx_RichTextImage *pThis = Object_wx_RichTextImage::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->GetNaturalSize();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RichTextImage, __IsEmpty, "IsEmpty")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_RichTextImage, __IsEmpty)
{
	Object_wx_RichTextImage *pThis = Object_wx_RichTextImage::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->IsEmpty();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RichTextImage, __CanEditProperties, "CanEditProperties")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_RichTextImage, __CanEditProperties)
{
	Object_wx_RichTextImage *pThis = Object_wx_RichTextImage::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->CanEditProperties();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RichTextImage, __EditProperties, "EditProperties")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "parent", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "buffer", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_RichTextImage, __EditProperties)
{
	Object_wx_RichTextImage *pThis = Object_wx_RichTextImage::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int parent = arg.GetNumber(0)
	//int buffer = arg.GetNumber(1)
	//pThis->GetEntity()->EditProperties();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RichTextImage, __GetPropertiesMenuLabel, "GetPropertiesMenuLabel")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_RichTextImage, __GetPropertiesMenuLabel)
{
	Object_wx_RichTextImage *pThis = Object_wx_RichTextImage::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->GetPropertiesMenuLabel();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RichTextImage, __UsesParagraphAttributes, "UsesParagraphAttributes")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_RichTextImage, __UsesParagraphAttributes)
{
	Object_wx_RichTextImage *pThis = Object_wx_RichTextImage::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->UsesParagraphAttributes();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RichTextImage, __ImportFromXML, "ImportFromXML")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "buffer", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "node", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "handler", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "recurse", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_RichTextImage, __ImportFromXML)
{
	Object_wx_RichTextImage *pThis = Object_wx_RichTextImage::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int buffer = arg.GetNumber(0)
	//int node = arg.GetNumber(1)
	//int handler = arg.GetNumber(2)
	//int recurse = arg.GetNumber(3)
	//pThis->GetEntity()->ImportFromXML();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RichTextImage, __ExportXML, "ExportXML")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "stream", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "indent", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "handler", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_RichTextImage, __ExportXML)
{
	Object_wx_RichTextImage *pThis = Object_wx_RichTextImage::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int stream = arg.GetNumber(0)
	//int indent = arg.GetNumber(1)
	//int handler = arg.GetNumber(2)
	//pThis->GetEntity()->ExportXML();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RichTextImage, __ExportXML_1, "ExportXML_1")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "parent", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "handler", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_RichTextImage, __ExportXML_1)
{
	Object_wx_RichTextImage *pThis = Object_wx_RichTextImage::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int parent = arg.GetNumber(0)
	//int handler = arg.GetNumber(1)
	//pThis->GetEntity()->ExportXML();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RichTextImage, __IsFloatable, "IsFloatable")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_RichTextImage, __IsFloatable)
{
	Object_wx_RichTextImage *pThis = Object_wx_RichTextImage::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->IsFloatable();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RichTextImage, __GetXMLNodeName, "GetXMLNodeName")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_RichTextImage, __GetXMLNodeName)
{
	Object_wx_RichTextImage *pThis = Object_wx_RichTextImage::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->GetXMLNodeName();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RichTextImage, __GetImageCache, "GetImageCache")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_RichTextImage, __GetImageCache)
{
	Object_wx_RichTextImage *pThis = Object_wx_RichTextImage::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->GetImageCache();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RichTextImage, __SetImageCache, "SetImageCache")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "bitmap", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_RichTextImage, __SetImageCache)
{
	Object_wx_RichTextImage *pThis = Object_wx_RichTextImage::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int bitmap = arg.GetNumber(0)
	//pThis->GetEntity()->SetImageCache();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RichTextImage, __ResetImageCache, "ResetImageCache")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_RichTextImage, __ResetImageCache)
{
	Object_wx_RichTextImage *pThis = Object_wx_RichTextImage::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->ResetImageCache();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RichTextImage, __GetImageBlock, "GetImageBlock")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_RichTextImage, __GetImageBlock)
{
	Object_wx_RichTextImage *pThis = Object_wx_RichTextImage::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->GetImageBlock();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RichTextImage, __GetOriginalImageSize, "GetOriginalImageSize")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_RichTextImage, __GetOriginalImageSize)
{
	Object_wx_RichTextImage *pThis = Object_wx_RichTextImage::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->GetOriginalImageSize();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RichTextImage, __SetOriginalImageSize, "SetOriginalImageSize")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "sz", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_RichTextImage, __SetOriginalImageSize)
{
	Object_wx_RichTextImage *pThis = Object_wx_RichTextImage::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int sz = arg.GetNumber(0)
	//pThis->GetEntity()->SetOriginalImageSize();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RichTextImage, __Copy, "Copy")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "obj", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_RichTextImage, __Copy)
{
	Object_wx_RichTextImage *pThis = Object_wx_RichTextImage::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int obj = arg.GetNumber(0)
	//pThis->GetEntity()->Copy();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RichTextImage, __Clone, "Clone")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_RichTextImage, __Clone)
{
	Object_wx_RichTextImage *pThis = Object_wx_RichTextImage::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->Clone();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RichTextImage, __LoadImageCache, "LoadImageCache")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "dc", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "context", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "retImageSize", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "resetCache", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "parentSize", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_RichTextImage, __LoadImageCache)
{
	Object_wx_RichTextImage *pThis = Object_wx_RichTextImage::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int dc = arg.GetNumber(0)
	//int context = arg.GetNumber(1)
	//int retImageSize = arg.GetNumber(2)
	//int resetCache = arg.GetNumber(3)
	//int parentSize = arg.GetNumber(4)
	//pThis->GetEntity()->LoadImageCache();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RichTextImage, __LoadAndScaleImageCache, "LoadAndScaleImageCache")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "image", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "sz", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "delayLoading", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "changed", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_RichTextImage, __LoadAndScaleImageCache)
{
	Object_wx_RichTextImage *pThis = Object_wx_RichTextImage::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int image = arg.GetNumber(0)
	//int sz = arg.GetNumber(1)
	//int delayLoading = arg.GetNumber(2)
	//int changed = arg.GetNumber(3)
	//pThis->GetEntity()->LoadAndScaleImageCache();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RichTextImage, __GetImageState, "GetImageState")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_RichTextImage, __GetImageState)
{
	Object_wx_RichTextImage *pThis = Object_wx_RichTextImage::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->GetImageState();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_RichTextImage, __SetImageState, "SetImageState")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "state", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_RichTextImage, __SetImageState)
{
	Object_wx_RichTextImage *pThis = Object_wx_RichTextImage::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int state = arg.GetNumber(0)
	//pThis->GetEntity()->SetImageState();
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Class implementation for wxRichTextImage
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_RichTextImage)
{
	// Constructor assignment
	Gura_AssignFunction(__wxRichTextImage);
	Gura_AssignFunction(__wxRichTextImage_1);
	Gura_AssignFunction(__wxRichTextImage_2);
	Gura_AssignFunction(__wxRichTextImage_3);
	// Method assignment
	Gura_AssignMethod(wx_RichTextImage, __Draw);
	Gura_AssignMethod(wx_RichTextImage, __Layout);
	Gura_AssignMethod(wx_RichTextImage, __GetRangeSize);
	Gura_AssignMethod(wx_RichTextImage, __GetNaturalSize);
	Gura_AssignMethod(wx_RichTextImage, __IsEmpty);
	Gura_AssignMethod(wx_RichTextImage, __CanEditProperties);
	Gura_AssignMethod(wx_RichTextImage, __EditProperties);
	Gura_AssignMethod(wx_RichTextImage, __GetPropertiesMenuLabel);
	Gura_AssignMethod(wx_RichTextImage, __UsesParagraphAttributes);
	Gura_AssignMethod(wx_RichTextImage, __ImportFromXML);
	Gura_AssignMethod(wx_RichTextImage, __ExportXML);
	Gura_AssignMethod(wx_RichTextImage, __ExportXML_1);
	Gura_AssignMethod(wx_RichTextImage, __IsFloatable);
	Gura_AssignMethod(wx_RichTextImage, __GetXMLNodeName);
	Gura_AssignMethod(wx_RichTextImage, __GetImageCache);
	Gura_AssignMethod(wx_RichTextImage, __SetImageCache);
	Gura_AssignMethod(wx_RichTextImage, __ResetImageCache);
	Gura_AssignMethod(wx_RichTextImage, __GetImageBlock);
	Gura_AssignMethod(wx_RichTextImage, __GetOriginalImageSize);
	Gura_AssignMethod(wx_RichTextImage, __SetOriginalImageSize);
	Gura_AssignMethod(wx_RichTextImage, __Copy);
	Gura_AssignMethod(wx_RichTextImage, __Clone);
	Gura_AssignMethod(wx_RichTextImage, __LoadImageCache);
	Gura_AssignMethod(wx_RichTextImage, __LoadAndScaleImageCache);
	Gura_AssignMethod(wx_RichTextImage, __GetImageState);
	Gura_AssignMethod(wx_RichTextImage, __SetImageState);
}

Gura_ImplementDescendantCreator(wx_RichTextImage)
{
	return new Object_wx_RichTextImage((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
