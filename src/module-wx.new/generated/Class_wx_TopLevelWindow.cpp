//----------------------------------------------------------------------------
// wxTopLevelWindow
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Gura interfaces for wxTopLevelWindow
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Object implementation for wxTopLevelWindow
//----------------------------------------------------------------------------
Object_wx_TopLevelWindow::~Object_wx_TopLevelWindow()
{
}

Object *Object_wx_TopLevelWindow::Clone() const
{
	return nullptr;
}

String Object_wx_TopLevelWindow::ToString(bool exprFlag)
{
	String rtn("<wx.TopLevelWindow:");
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
Gura_DeclareMethodAlias(wx_TopLevelWindow, __wxTopLevelWindow, "wxTopLevelWindow")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_TopLevelWindow, __wxTopLevelWindow)
{
	Object_wx_TopLevelWindow *pThis = Object_wx_TopLevelWindow::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->wxTopLevelWindow();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_TopLevelWindow, __wxTopLevelWindow_1, "wxTopLevelWindow_1")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "parent", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "id", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "title", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "pos", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "size", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "style", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "name", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_TopLevelWindow, __wxTopLevelWindow_1)
{
	Object_wx_TopLevelWindow *pThis = Object_wx_TopLevelWindow::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int parent = arg.GetNumber(0)
	//int id = arg.GetNumber(1)
	//int title = arg.GetNumber(2)
	//int pos = arg.GetNumber(3)
	//int size = arg.GetNumber(4)
	//int style = arg.GetNumber(5)
	//int name = arg.GetNumber(6)
	//pThis->GetEntity()->wxTopLevelWindow();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_TopLevelWindow, __Create, "Create")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "parent", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "id", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "title", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "pos", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "size", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "style", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "name", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_TopLevelWindow, __Create)
{
	Object_wx_TopLevelWindow *pThis = Object_wx_TopLevelWindow::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int parent = arg.GetNumber(0)
	//int id = arg.GetNumber(1)
	//int title = arg.GetNumber(2)
	//int pos = arg.GetNumber(3)
	//int size = arg.GetNumber(4)
	//int style = arg.GetNumber(5)
	//int name = arg.GetNumber(6)
	//pThis->GetEntity()->Create();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_TopLevelWindow, __CanSetTransparent, "CanSetTransparent")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_TopLevelWindow, __CanSetTransparent)
{
	Object_wx_TopLevelWindow *pThis = Object_wx_TopLevelWindow::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->CanSetTransparent();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_TopLevelWindow, __CenterOnScreen, "CenterOnScreen")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "direction", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_TopLevelWindow, __CenterOnScreen)
{
	Object_wx_TopLevelWindow *pThis = Object_wx_TopLevelWindow::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int direction = arg.GetNumber(0)
	//pThis->GetEntity()->CenterOnScreen();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_TopLevelWindow, __CentreOnScreen, "CentreOnScreen")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "direction", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_TopLevelWindow, __CentreOnScreen)
{
	Object_wx_TopLevelWindow *pThis = Object_wx_TopLevelWindow::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int direction = arg.GetNumber(0)
	//pThis->GetEntity()->CentreOnScreen();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_TopLevelWindow, __EnableCloseButton, "EnableCloseButton")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "enable", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_TopLevelWindow, __EnableCloseButton)
{
	Object_wx_TopLevelWindow *pThis = Object_wx_TopLevelWindow::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int enable = arg.GetNumber(0)
	//pThis->GetEntity()->EnableCloseButton();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_TopLevelWindow, __EnableMaximizeButton, "EnableMaximizeButton")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "enable", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_TopLevelWindow, __EnableMaximizeButton)
{
	Object_wx_TopLevelWindow *pThis = Object_wx_TopLevelWindow::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int enable = arg.GetNumber(0)
	//pThis->GetEntity()->EnableMaximizeButton();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_TopLevelWindow, __EnableMinimizeButton, "EnableMinimizeButton")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "enable", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_TopLevelWindow, __EnableMinimizeButton)
{
	Object_wx_TopLevelWindow *pThis = Object_wx_TopLevelWindow::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int enable = arg.GetNumber(0)
	//pThis->GetEntity()->EnableMinimizeButton();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_TopLevelWindow, __GetDefaultItem, "GetDefaultItem")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_TopLevelWindow, __GetDefaultItem)
{
	Object_wx_TopLevelWindow *pThis = Object_wx_TopLevelWindow::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->GetDefaultItem();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_TopLevelWindow, __GetDefaultSize, "GetDefaultSize")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_TopLevelWindow, __GetDefaultSize)
{
	Object_wx_TopLevelWindow *pThis = Object_wx_TopLevelWindow::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->GetDefaultSize();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_TopLevelWindow, __GetIcon, "GetIcon")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_TopLevelWindow, __GetIcon)
{
	Object_wx_TopLevelWindow *pThis = Object_wx_TopLevelWindow::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->GetIcon();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_TopLevelWindow, __GetIcons, "GetIcons")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_TopLevelWindow, __GetIcons)
{
	Object_wx_TopLevelWindow *pThis = Object_wx_TopLevelWindow::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->GetIcons();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_TopLevelWindow, __GetTitle, "GetTitle")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_TopLevelWindow, __GetTitle)
{
	Object_wx_TopLevelWindow *pThis = Object_wx_TopLevelWindow::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->GetTitle();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_TopLevelWindow, __Iconize, "Iconize")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "iconize", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_TopLevelWindow, __Iconize)
{
	Object_wx_TopLevelWindow *pThis = Object_wx_TopLevelWindow::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int iconize = arg.GetNumber(0)
	//pThis->GetEntity()->Iconize();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_TopLevelWindow, __IsActive, "IsActive")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_TopLevelWindow, __IsActive)
{
	Object_wx_TopLevelWindow *pThis = Object_wx_TopLevelWindow::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->IsActive();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_TopLevelWindow, __IsAlwaysMaximized, "IsAlwaysMaximized")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_TopLevelWindow, __IsAlwaysMaximized)
{
	Object_wx_TopLevelWindow *pThis = Object_wx_TopLevelWindow::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->IsAlwaysMaximized();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_TopLevelWindow, __IsFullScreen, "IsFullScreen")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_TopLevelWindow, __IsFullScreen)
{
	Object_wx_TopLevelWindow *pThis = Object_wx_TopLevelWindow::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->IsFullScreen();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_TopLevelWindow, __IsIconized, "IsIconized")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_TopLevelWindow, __IsIconized)
{
	Object_wx_TopLevelWindow *pThis = Object_wx_TopLevelWindow::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->IsIconized();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_TopLevelWindow, __IsMaximized, "IsMaximized")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_TopLevelWindow, __IsMaximized)
{
	Object_wx_TopLevelWindow *pThis = Object_wx_TopLevelWindow::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->IsMaximized();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_TopLevelWindow, __IsUsingNativeDecorations, "IsUsingNativeDecorations")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_TopLevelWindow, __IsUsingNativeDecorations)
{
	Object_wx_TopLevelWindow *pThis = Object_wx_TopLevelWindow::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->IsUsingNativeDecorations();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_TopLevelWindow, __Layout, "Layout")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_TopLevelWindow, __Layout)
{
	Object_wx_TopLevelWindow *pThis = Object_wx_TopLevelWindow::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->Layout();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_TopLevelWindow, __Maximize, "Maximize")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "maximize", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_TopLevelWindow, __Maximize)
{
	Object_wx_TopLevelWindow *pThis = Object_wx_TopLevelWindow::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int maximize = arg.GetNumber(0)
	//pThis->GetEntity()->Maximize();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_TopLevelWindow, __MSWGetSystemMenu, "MSWGetSystemMenu")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_TopLevelWindow, __MSWGetSystemMenu)
{
	Object_wx_TopLevelWindow *pThis = Object_wx_TopLevelWindow::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->MSWGetSystemMenu();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_TopLevelWindow, __RequestUserAttention, "RequestUserAttention")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "flags", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_TopLevelWindow, __RequestUserAttention)
{
	Object_wx_TopLevelWindow *pThis = Object_wx_TopLevelWindow::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int flags = arg.GetNumber(0)
	//pThis->GetEntity()->RequestUserAttention();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_TopLevelWindow, __Restore, "Restore")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_TopLevelWindow, __Restore)
{
	Object_wx_TopLevelWindow *pThis = Object_wx_TopLevelWindow::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->Restore();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_TopLevelWindow, __SetDefaultItem, "SetDefaultItem")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "win", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_TopLevelWindow, __SetDefaultItem)
{
	Object_wx_TopLevelWindow *pThis = Object_wx_TopLevelWindow::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int win = arg.GetNumber(0)
	//pThis->GetEntity()->SetDefaultItem();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_TopLevelWindow, __SetTmpDefaultItem, "SetTmpDefaultItem")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "win", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_TopLevelWindow, __SetTmpDefaultItem)
{
	Object_wx_TopLevelWindow *pThis = Object_wx_TopLevelWindow::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int win = arg.GetNumber(0)
	//pThis->GetEntity()->SetTmpDefaultItem();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_TopLevelWindow, __GetTmpDefaultItem, "GetTmpDefaultItem")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_TopLevelWindow, __GetTmpDefaultItem)
{
	Object_wx_TopLevelWindow *pThis = Object_wx_TopLevelWindow::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->GetTmpDefaultItem();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_TopLevelWindow, __SetIcon, "SetIcon")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "icon", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_TopLevelWindow, __SetIcon)
{
	Object_wx_TopLevelWindow *pThis = Object_wx_TopLevelWindow::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int icon = arg.GetNumber(0)
	//pThis->GetEntity()->SetIcon();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_TopLevelWindow, __SetIcons, "SetIcons")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "icons", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_TopLevelWindow, __SetIcons)
{
	Object_wx_TopLevelWindow *pThis = Object_wx_TopLevelWindow::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int icons = arg.GetNumber(0)
	//pThis->GetEntity()->SetIcons();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_TopLevelWindow, __SetMaxSize, "SetMaxSize")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "size", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_TopLevelWindow, __SetMaxSize)
{
	Object_wx_TopLevelWindow *pThis = Object_wx_TopLevelWindow::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int size = arg.GetNumber(0)
	//pThis->GetEntity()->SetMaxSize();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_TopLevelWindow, __SetMinSize, "SetMinSize")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "size", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_TopLevelWindow, __SetMinSize)
{
	Object_wx_TopLevelWindow *pThis = Object_wx_TopLevelWindow::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int size = arg.GetNumber(0)
	//pThis->GetEntity()->SetMinSize();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_TopLevelWindow, __SetSizeHints, "SetSizeHints")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "minW", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "minH", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "maxW", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "maxH", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "incW", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "incH", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_TopLevelWindow, __SetSizeHints)
{
	Object_wx_TopLevelWindow *pThis = Object_wx_TopLevelWindow::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int minW = arg.GetNumber(0)
	//int minH = arg.GetNumber(1)
	//int maxW = arg.GetNumber(2)
	//int maxH = arg.GetNumber(3)
	//int incW = arg.GetNumber(4)
	//int incH = arg.GetNumber(5)
	//pThis->GetEntity()->SetSizeHints();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_TopLevelWindow, __SetSizeHints_1, "SetSizeHints_1")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "minSize", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "maxSize", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "incSize", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_TopLevelWindow, __SetSizeHints_1)
{
	Object_wx_TopLevelWindow *pThis = Object_wx_TopLevelWindow::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int minSize = arg.GetNumber(0)
	//int maxSize = arg.GetNumber(1)
	//int incSize = arg.GetNumber(2)
	//pThis->GetEntity()->SetSizeHints();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_TopLevelWindow, __SetTitle, "SetTitle")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "title", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_TopLevelWindow, __SetTitle)
{
	Object_wx_TopLevelWindow *pThis = Object_wx_TopLevelWindow::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int title = arg.GetNumber(0)
	//pThis->GetEntity()->SetTitle();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_TopLevelWindow, __SetTransparent, "SetTransparent")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "alpha", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_TopLevelWindow, __SetTransparent)
{
	Object_wx_TopLevelWindow *pThis = Object_wx_TopLevelWindow::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int alpha = arg.GetNumber(0)
	//pThis->GetEntity()->SetTransparent();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_TopLevelWindow, __ShouldPreventAppExit, "ShouldPreventAppExit")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_TopLevelWindow, __ShouldPreventAppExit)
{
	Object_wx_TopLevelWindow *pThis = Object_wx_TopLevelWindow::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->ShouldPreventAppExit();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_TopLevelWindow, __OSXSetModified, "OSXSetModified")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "modified", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_TopLevelWindow, __OSXSetModified)
{
	Object_wx_TopLevelWindow *pThis = Object_wx_TopLevelWindow::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int modified = arg.GetNumber(0)
	//pThis->GetEntity()->OSXSetModified();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_TopLevelWindow, __OSXIsModified, "OSXIsModified")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_TopLevelWindow, __OSXIsModified)
{
	Object_wx_TopLevelWindow *pThis = Object_wx_TopLevelWindow::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->OSXIsModified();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_TopLevelWindow, __SetRepresentedFilename, "SetRepresentedFilename")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "filename", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_TopLevelWindow, __SetRepresentedFilename)
{
	Object_wx_TopLevelWindow *pThis = Object_wx_TopLevelWindow::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int filename = arg.GetNumber(0)
	//pThis->GetEntity()->SetRepresentedFilename();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_TopLevelWindow, __ShowWithoutActivating, "ShowWithoutActivating")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_TopLevelWindow, __ShowWithoutActivating)
{
	Object_wx_TopLevelWindow *pThis = Object_wx_TopLevelWindow::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//pThis->GetEntity()->ShowWithoutActivating();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_TopLevelWindow, __EnableFullScreenView, "EnableFullScreenView")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "enable", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_TopLevelWindow, __EnableFullScreenView)
{
	Object_wx_TopLevelWindow *pThis = Object_wx_TopLevelWindow::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int enable = arg.GetNumber(0)
	//pThis->GetEntity()->EnableFullScreenView();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_TopLevelWindow, __ShowFullScreen, "ShowFullScreen")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "show", VTYPE_number, OCCUR_Once);
	//DeclareArg(env, "style", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_TopLevelWindow, __ShowFullScreen)
{
	Object_wx_TopLevelWindow *pThis = Object_wx_TopLevelWindow::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int show = arg.GetNumber(0)
	//int style = arg.GetNumber(1)
	//pThis->GetEntity()->ShowFullScreen();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_TopLevelWindow, __UseNativeDecorations, "UseNativeDecorations")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "native", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_TopLevelWindow, __UseNativeDecorations)
{
	Object_wx_TopLevelWindow *pThis = Object_wx_TopLevelWindow::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int native = arg.GetNumber(0)
	//pThis->GetEntity()->UseNativeDecorations();
	return Value::Nil;
}

Gura_DeclareMethodAlias(wx_TopLevelWindow, __UseNativeDecorationsByDefault, "UseNativeDecorationsByDefault")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	//DeclareArg(env, "native", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_TopLevelWindow, __UseNativeDecorationsByDefault)
{
	Object_wx_TopLevelWindow *pThis = Object_wx_TopLevelWindow::GetObjectThis(arg);
	if (pThis->IsInvalid(env)) return Value::Nil;
	//int native = arg.GetNumber(0)
	//pThis->GetEntity()->UseNativeDecorationsByDefault();
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Class implementation for wxTopLevelWindow
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_TopLevelWindow)
{
	Gura_AssignMethod(wx_TopLevelWindow, __wxTopLevelWindow);
	Gura_AssignMethod(wx_TopLevelWindow, __wxTopLevelWindow_1);
	Gura_AssignMethod(wx_TopLevelWindow, __Create);
	Gura_AssignMethod(wx_TopLevelWindow, __CanSetTransparent);
	Gura_AssignMethod(wx_TopLevelWindow, __CenterOnScreen);
	Gura_AssignMethod(wx_TopLevelWindow, __CentreOnScreen);
	Gura_AssignMethod(wx_TopLevelWindow, __EnableCloseButton);
	Gura_AssignMethod(wx_TopLevelWindow, __EnableMaximizeButton);
	Gura_AssignMethod(wx_TopLevelWindow, __EnableMinimizeButton);
	Gura_AssignMethod(wx_TopLevelWindow, __GetDefaultItem);
	Gura_AssignMethod(wx_TopLevelWindow, __GetDefaultSize);
	Gura_AssignMethod(wx_TopLevelWindow, __GetIcon);
	Gura_AssignMethod(wx_TopLevelWindow, __GetIcons);
	Gura_AssignMethod(wx_TopLevelWindow, __GetTitle);
	Gura_AssignMethod(wx_TopLevelWindow, __Iconize);
	Gura_AssignMethod(wx_TopLevelWindow, __IsActive);
	Gura_AssignMethod(wx_TopLevelWindow, __IsAlwaysMaximized);
	Gura_AssignMethod(wx_TopLevelWindow, __IsFullScreen);
	Gura_AssignMethod(wx_TopLevelWindow, __IsIconized);
	Gura_AssignMethod(wx_TopLevelWindow, __IsMaximized);
	Gura_AssignMethod(wx_TopLevelWindow, __IsUsingNativeDecorations);
	Gura_AssignMethod(wx_TopLevelWindow, __Layout);
	Gura_AssignMethod(wx_TopLevelWindow, __Maximize);
	Gura_AssignMethod(wx_TopLevelWindow, __MSWGetSystemMenu);
	Gura_AssignMethod(wx_TopLevelWindow, __RequestUserAttention);
	Gura_AssignMethod(wx_TopLevelWindow, __Restore);
	Gura_AssignMethod(wx_TopLevelWindow, __SetDefaultItem);
	Gura_AssignMethod(wx_TopLevelWindow, __SetTmpDefaultItem);
	Gura_AssignMethod(wx_TopLevelWindow, __GetTmpDefaultItem);
	Gura_AssignMethod(wx_TopLevelWindow, __SetIcon);
	Gura_AssignMethod(wx_TopLevelWindow, __SetIcons);
	Gura_AssignMethod(wx_TopLevelWindow, __SetMaxSize);
	Gura_AssignMethod(wx_TopLevelWindow, __SetMinSize);
	Gura_AssignMethod(wx_TopLevelWindow, __SetSizeHints);
	Gura_AssignMethod(wx_TopLevelWindow, __SetSizeHints_1);
	Gura_AssignMethod(wx_TopLevelWindow, __SetTitle);
	Gura_AssignMethod(wx_TopLevelWindow, __SetTransparent);
	Gura_AssignMethod(wx_TopLevelWindow, __ShouldPreventAppExit);
	Gura_AssignMethod(wx_TopLevelWindow, __OSXSetModified);
	Gura_AssignMethod(wx_TopLevelWindow, __OSXIsModified);
	Gura_AssignMethod(wx_TopLevelWindow, __SetRepresentedFilename);
	Gura_AssignMethod(wx_TopLevelWindow, __ShowWithoutActivating);
	Gura_AssignMethod(wx_TopLevelWindow, __EnableFullScreenView);
	Gura_AssignMethod(wx_TopLevelWindow, __ShowFullScreen);
	Gura_AssignMethod(wx_TopLevelWindow, __UseNativeDecorations);
	Gura_AssignMethod(wx_TopLevelWindow, __UseNativeDecorationsByDefault);
}

Gura_ImplementDescendantCreator(wx_TopLevelWindow)
{
	return new Object_wx_TopLevelWindow((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
