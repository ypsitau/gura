// Don't edit this file. This has been generated by Functions.cpp.gura.
#include "stdafx.h"

Gura_BeginModuleScope(glut)

// glut.glutInit
Gura_DeclareFunction(glutInit)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
	DeclareArg(env, "argv", VTYPE_string, OCCUR_Once, FLAG_List);
	AddHelp(
		Gura_Symbol(en), Help::FMT_markdown,
		"");
}

Gura_ImplementFunction(glutInit)
{
	const ValueList &argv = args.GetList(0);
	int argc = static_cast<int>(argv.size());
	char **_argv = new char *[argc];
	int i = 0;
	foreach_const (ValueList, pValue, argv) {
		_argv[i++] = strdup(pValue->GetString());
	}
	glutInit(&argc, _argv);
	Value _rtnVal(Value::CreateList(env, _argv, argc));
	for (int i = 0; i < argc; i++) {
		::free(_argv[i]);
	}
	delete[] _argv;
	return ReturnValue(env, sig, args, _rtnVal);
}

// glut.glutInitDisplayMode
Gura_DeclareFunction(glutInitDisplayMode)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "mode", VTYPE_number, OCCUR_Once, FLAG_None);
	AddHelp(
		Gura_Symbol(en), Help::FMT_markdown,
		"");
}

Gura_ImplementFunction(glutInitDisplayMode)
{
	unsigned int mode = args.GetUInt(0);
	glutInitDisplayMode(mode);
	return Value::Null;
}

// glut.glutInitDisplayString
Gura_DeclareFunction(glutInitDisplayString)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "string", VTYPE_string, OCCUR_Once, FLAG_None);
	AddHelp(
		Gura_Symbol(en), Help::FMT_markdown,
		"");
}

Gura_ImplementFunction(glutInitDisplayString)
{
#if 0
	const char *string = args.GetString(0);
	glutInitDisplayString(string);
	return Value::Null;
#endif
	SetError_NotImpFunction(sig, "glutInitDisplayString");
	return Value::Null;
}

// glut.glutInitWindowPosition
Gura_DeclareFunction(glutInitWindowPosition)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "x", VTYPE_number, OCCUR_Once, FLAG_None);
	DeclareArg(env, "y", VTYPE_number, OCCUR_Once, FLAG_None);
	AddHelp(
		Gura_Symbol(en), Help::FMT_markdown,
		"");
}

Gura_ImplementFunction(glutInitWindowPosition)
{
	int x = args.GetInt(0);
	int y = args.GetInt(1);
	glutInitWindowPosition(x, y);
	return Value::Null;
}

// glut.glutInitWindowSize
Gura_DeclareFunction(glutInitWindowSize)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "width", VTYPE_number, OCCUR_Once, FLAG_None);
	DeclareArg(env, "height", VTYPE_number, OCCUR_Once, FLAG_None);
	AddHelp(
		Gura_Symbol(en), Help::FMT_markdown,
		"");
}

Gura_ImplementFunction(glutInitWindowSize)
{
	int width = args.GetInt(0);
	int height = args.GetInt(1);
	glutInitWindowSize(width, height);
	return Value::Null;
}

// glut.glutMainLoop
Gura_DeclareFunction(glutMainLoop)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	AddHelp(
		Gura_Symbol(en), Help::FMT_markdown,
		"");
}

Gura_ImplementFunction(glutMainLoop)
{
	glutMainLoop();
	return Value::Null;
}

// glut.glutCreateWindow
Gura_DeclareFunction(glutCreateWindow)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareBlock(OCCUR_ZeroOrOnce);
	DeclareArg(env, "title", VTYPE_string, OCCUR_Once, FLAG_None);
	AddHelp(
		Gura_Symbol(en), Help::FMT_markdown,
		"");
}

Gura_ImplementFunction(glutCreateWindow)
{
#if 0
	const char *title = args.GetString(0);
	int _rtn = glutCreateWindow(title);
	return ReturnValue(env, sig, args, Value(_rtn));
#endif
	SetError_NotImpFunction(sig, "glutCreateWindow");
	return Value::Null;
}

// glut.glutCreateSubWindow
Gura_DeclareFunction(glutCreateSubWindow)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareBlock(OCCUR_ZeroOrOnce);
	DeclareArg(env, "win", VTYPE_number, OCCUR_Once, FLAG_None);
	DeclareArg(env, "x", VTYPE_number, OCCUR_Once, FLAG_None);
	DeclareArg(env, "y", VTYPE_number, OCCUR_Once, FLAG_None);
	DeclareArg(env, "width", VTYPE_number, OCCUR_Once, FLAG_None);
	DeclareArg(env, "height", VTYPE_number, OCCUR_Once, FLAG_None);
	AddHelp(
		Gura_Symbol(en), Help::FMT_markdown,
		"");
}

Gura_ImplementFunction(glutCreateSubWindow)
{
	int win = args.GetInt(0);
	int x = args.GetInt(1);
	int y = args.GetInt(2);
	int width = args.GetInt(3);
	int height = args.GetInt(4);
	int _rtn = glutCreateSubWindow(win, x, y, width, height);
	return ReturnValue(env, sig, args, Value(_rtn));
}

// glut.glutDestroyWindow
Gura_DeclareFunction(glutDestroyWindow)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "win", VTYPE_number, OCCUR_Once, FLAG_None);
	AddHelp(
		Gura_Symbol(en), Help::FMT_markdown,
		"");
}

Gura_ImplementFunction(glutDestroyWindow)
{
	int win = args.GetInt(0);
	glutDestroyWindow(win);
	return Value::Null;
}

// glut.glutPostRedisplay
Gura_DeclareFunction(glutPostRedisplay)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	AddHelp(
		Gura_Symbol(en), Help::FMT_markdown,
		"");
}

Gura_ImplementFunction(glutPostRedisplay)
{
	glutPostRedisplay();
	return Value::Null;
}

// glut.glutPostWindowRedisplay
Gura_DeclareFunction(glutPostWindowRedisplay)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "win", VTYPE_number, OCCUR_Once, FLAG_None);
	AddHelp(
		Gura_Symbol(en), Help::FMT_markdown,
		"");
}

Gura_ImplementFunction(glutPostWindowRedisplay)
{
	int win = args.GetInt(0);
	glutPostWindowRedisplay(win);
	return Value::Null;
}

// glut.glutSwapBuffers
Gura_DeclareFunction(glutSwapBuffers)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	AddHelp(
		Gura_Symbol(en), Help::FMT_markdown,
		"");
}

Gura_ImplementFunction(glutSwapBuffers)
{
	glutSwapBuffers();
	return Value::Null;
}

// glut.glutGetWindow
Gura_DeclareFunction(glutGetWindow)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
	AddHelp(
		Gura_Symbol(en), Help::FMT_markdown,
		"");
}

Gura_ImplementFunction(glutGetWindow)
{
	int _rtn = glutGetWindow();
	return ReturnValue(env, sig, args, Value(_rtn));
}

// glut.glutSetWindow
Gura_DeclareFunction(glutSetWindow)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "win", VTYPE_number, OCCUR_Once, FLAG_None);
	AddHelp(
		Gura_Symbol(en), Help::FMT_markdown,
		"");
}

Gura_ImplementFunction(glutSetWindow)
{
	int win = args.GetInt(0);
	glutSetWindow(win);
	return Value::Null;
}

// glut.glutSetWindowTitle
Gura_DeclareFunction(glutSetWindowTitle)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "title", VTYPE_string, OCCUR_Once, FLAG_None);
	AddHelp(
		Gura_Symbol(en), Help::FMT_markdown,
		"");
}

Gura_ImplementFunction(glutSetWindowTitle)
{
#if 0
	const char *title = args.GetString(0);
	glutSetWindowTitle(title);
	return Value::Null;
#endif
	SetError_NotImpFunction(sig, "glutSetWindowTitle");
	return Value::Null;
}

// glut.glutSetIconTitle
Gura_DeclareFunction(glutSetIconTitle)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "title", VTYPE_string, OCCUR_Once, FLAG_None);
	AddHelp(
		Gura_Symbol(en), Help::FMT_markdown,
		"");
}

Gura_ImplementFunction(glutSetIconTitle)
{
#if 0
	const char *title = args.GetString(0);
	glutSetIconTitle(title);
	return Value::Null;
#endif
	SetError_NotImpFunction(sig, "glutSetIconTitle");
	return Value::Null;
}

// glut.glutPositionWindow
Gura_DeclareFunction(glutPositionWindow)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "x", VTYPE_number, OCCUR_Once, FLAG_None);
	DeclareArg(env, "y", VTYPE_number, OCCUR_Once, FLAG_None);
	AddHelp(
		Gura_Symbol(en), Help::FMT_markdown,
		"");
}

Gura_ImplementFunction(glutPositionWindow)
{
	int x = args.GetInt(0);
	int y = args.GetInt(1);
	glutPositionWindow(x, y);
	return Value::Null;
}

// glut.glutReshapeWindow
Gura_DeclareFunction(glutReshapeWindow)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "width", VTYPE_number, OCCUR_Once, FLAG_None);
	DeclareArg(env, "height", VTYPE_number, OCCUR_Once, FLAG_None);
	AddHelp(
		Gura_Symbol(en), Help::FMT_markdown,
		"");
}

Gura_ImplementFunction(glutReshapeWindow)
{
	int width = args.GetInt(0);
	int height = args.GetInt(1);
	glutReshapeWindow(width, height);
	return Value::Null;
}

// glut.glutPopWindow
Gura_DeclareFunction(glutPopWindow)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	AddHelp(
		Gura_Symbol(en), Help::FMT_markdown,
		"");
}

Gura_ImplementFunction(glutPopWindow)
{
	glutPopWindow();
	return Value::Null;
}

// glut.glutPushWindow
Gura_DeclareFunction(glutPushWindow)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	AddHelp(
		Gura_Symbol(en), Help::FMT_markdown,
		"");
}

Gura_ImplementFunction(glutPushWindow)
{
	glutPushWindow();
	return Value::Null;
}

// glut.glutIconifyWindow
Gura_DeclareFunction(glutIconifyWindow)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	AddHelp(
		Gura_Symbol(en), Help::FMT_markdown,
		"");
}

Gura_ImplementFunction(glutIconifyWindow)
{
	glutIconifyWindow();
	return Value::Null;
}

// glut.glutShowWindow
Gura_DeclareFunction(glutShowWindow)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	AddHelp(
		Gura_Symbol(en), Help::FMT_markdown,
		"");
}

Gura_ImplementFunction(glutShowWindow)
{
	glutShowWindow();
	return Value::Null;
}

// glut.glutHideWindow
Gura_DeclareFunction(glutHideWindow)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	AddHelp(
		Gura_Symbol(en), Help::FMT_markdown,
		"");
}

Gura_ImplementFunction(glutHideWindow)
{
	glutHideWindow();
	return Value::Null;
}

// glut.glutFullScreen
Gura_DeclareFunction(glutFullScreen)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	AddHelp(
		Gura_Symbol(en), Help::FMT_markdown,
		"");
}

Gura_ImplementFunction(glutFullScreen)
{
	glutFullScreen();
	return Value::Null;
}

// glut.glutSetCursor
Gura_DeclareFunction(glutSetCursor)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "cursor", VTYPE_number, OCCUR_Once, FLAG_None);
	AddHelp(
		Gura_Symbol(en), Help::FMT_markdown,
		"");
}

Gura_ImplementFunction(glutSetCursor)
{
	int cursor = args.GetInt(0);
	glutSetCursor(cursor);
	return Value::Null;
}

// glut.glutWarpPointer
Gura_DeclareFunction(glutWarpPointer)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "x", VTYPE_number, OCCUR_Once, FLAG_None);
	DeclareArg(env, "y", VTYPE_number, OCCUR_Once, FLAG_None);
	AddHelp(
		Gura_Symbol(en), Help::FMT_markdown,
		"");
}

Gura_ImplementFunction(glutWarpPointer)
{
	int x = args.GetInt(0);
	int y = args.GetInt(1);
	glutWarpPointer(x, y);
	return Value::Null;
}

// glut.glutSurfaceTexture
Gura_DeclareFunction(glutSurfaceTexture)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "target", VTYPE_number, OCCUR_Once, FLAG_None);
	DeclareArg(env, "internalformat", VTYPE_number, OCCUR_Once, FLAG_None);
	DeclareArg(env, "surfacewin", VTYPE_number, OCCUR_Once, FLAG_None);
	AddHelp(
		Gura_Symbol(en), Help::FMT_markdown,
		"");
}

Gura_ImplementFunction(glutSurfaceTexture)
{
	GLenum target = static_cast<GLenum>(args.GetInt(0));
	GLenum internalformat = static_cast<GLenum>(args.GetInt(1));
	int surfacewin = args.GetInt(2);
	glutSurfaceTexture(target, internalformat, surfacewin);
	return Value::Null;
}

// glut.glutWMCloseFunc
Gura_DeclareFunction(glutWMCloseFunc)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "func", VTYPE_function, OCCUR_Once, FLAG_None);
	AddHelp(
		Gura_Symbol(en), Help::FMT_markdown,
		"");
}

Gura_ImplementFunction(glutWMCloseFunc)
{
	const Function *func = Object_function::GetObject(args, 0)->GetFunction();
	return Value::Null;
}

// glut.glutCheckLoop
Gura_DeclareFunction(glutCheckLoop)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	AddHelp(
		Gura_Symbol(en), Help::FMT_markdown,
		"");
}

Gura_ImplementFunction(glutCheckLoop)
{
	glutCheckLoop();
	return Value::Null;
}

// glut.glutEstablishOverlay
Gura_DeclareFunction(glutEstablishOverlay)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	AddHelp(
		Gura_Symbol(en), Help::FMT_markdown,
		"");
}

Gura_ImplementFunction(glutEstablishOverlay)
{
	glutEstablishOverlay();
	return Value::Null;
}

// glut.glutRemoveOverlay
Gura_DeclareFunction(glutRemoveOverlay)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	AddHelp(
		Gura_Symbol(en), Help::FMT_markdown,
		"");
}

Gura_ImplementFunction(glutRemoveOverlay)
{
	glutRemoveOverlay();
	return Value::Null;
}

// glut.glutUseLayer
Gura_DeclareFunction(glutUseLayer)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "layer", VTYPE_number, OCCUR_Once, FLAG_None);
	AddHelp(
		Gura_Symbol(en), Help::FMT_markdown,
		"");
}

Gura_ImplementFunction(glutUseLayer)
{
	GLenum layer = static_cast<GLenum>(args.GetInt(0));
	glutUseLayer(layer);
	return Value::Null;
}

// glut.glutPostOverlayRedisplay
Gura_DeclareFunction(glutPostOverlayRedisplay)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	AddHelp(
		Gura_Symbol(en), Help::FMT_markdown,
		"");
}

Gura_ImplementFunction(glutPostOverlayRedisplay)
{
	glutPostOverlayRedisplay();
	return Value::Null;
}

// glut.glutPostWindowOverlayRedisplay
Gura_DeclareFunction(glutPostWindowOverlayRedisplay)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "win", VTYPE_number, OCCUR_Once, FLAG_None);
	AddHelp(
		Gura_Symbol(en), Help::FMT_markdown,
		"");
}

Gura_ImplementFunction(glutPostWindowOverlayRedisplay)
{
	int win = args.GetInt(0);
	glutPostWindowOverlayRedisplay(win);
	return Value::Null;
}

// glut.glutShowOverlay
Gura_DeclareFunction(glutShowOverlay)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	AddHelp(
		Gura_Symbol(en), Help::FMT_markdown,
		"");
}

Gura_ImplementFunction(glutShowOverlay)
{
	glutShowOverlay();
	return Value::Null;
}

// glut.glutHideOverlay
Gura_DeclareFunction(glutHideOverlay)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	AddHelp(
		Gura_Symbol(en), Help::FMT_markdown,
		"");
}

Gura_ImplementFunction(glutHideOverlay)
{
	glutHideOverlay();
	return Value::Null;
}

// glut.glutCreateMenu
Gura_DeclareFunction(glutCreateMenu)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
	AddHelp(
		Gura_Symbol(en), Help::FMT_markdown,
		"");
}

Gura_ImplementFunction(glutCreateMenu)
{
#if 0
	int _rtn = glutCreateMenu();
	return ReturnValue(env, sig, args, Value(_rtn));
#endif
	SetError_NotImpFunction(sig, "glutCreateMenu");
	return Value::Null;
}

// glut.glutDestroyMenu
Gura_DeclareFunction(glutDestroyMenu)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "menu", VTYPE_number, OCCUR_Once, FLAG_None);
	AddHelp(
		Gura_Symbol(en), Help::FMT_markdown,
		"");
}

Gura_ImplementFunction(glutDestroyMenu)
{
	int menu = args.GetInt(0);
	glutDestroyMenu(menu);
	return Value::Null;
}

// glut.glutGetMenu
Gura_DeclareFunction(glutGetMenu)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
	AddHelp(
		Gura_Symbol(en), Help::FMT_markdown,
		"");
}

Gura_ImplementFunction(glutGetMenu)
{
	int _rtn = glutGetMenu();
	return ReturnValue(env, sig, args, Value(_rtn));
}

// glut.glutSetMenu
Gura_DeclareFunction(glutSetMenu)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "menu", VTYPE_number, OCCUR_Once, FLAG_None);
	AddHelp(
		Gura_Symbol(en), Help::FMT_markdown,
		"");
}

Gura_ImplementFunction(glutSetMenu)
{
	int menu = args.GetInt(0);
	glutSetMenu(menu);
	return Value::Null;
}

// glut.glutAddMenuEntry
Gura_DeclareFunction(glutAddMenuEntry)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "label", VTYPE_string, OCCUR_Once, FLAG_None);
	DeclareArg(env, "value", VTYPE_number, OCCUR_Once, FLAG_None);
	AddHelp(
		Gura_Symbol(en), Help::FMT_markdown,
		"");
}

Gura_ImplementFunction(glutAddMenuEntry)
{
#if 0
	const char *label = args.GetString(0);
	int value = args.GetInt(1);
	glutAddMenuEntry(label, value);
	return Value::Null;
#endif
	SetError_NotImpFunction(sig, "glutAddMenuEntry");
	return Value::Null;
}

// glut.glutAddSubMenu
Gura_DeclareFunction(glutAddSubMenu)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "label", VTYPE_string, OCCUR_Once, FLAG_None);
	DeclareArg(env, "submenu", VTYPE_number, OCCUR_Once, FLAG_None);
	AddHelp(
		Gura_Symbol(en), Help::FMT_markdown,
		"");
}

Gura_ImplementFunction(glutAddSubMenu)
{
#if 0
	const char *label = args.GetString(0);
	int submenu = args.GetInt(1);
	glutAddSubMenu(label, submenu);
	return Value::Null;
#endif
	SetError_NotImpFunction(sig, "glutAddSubMenu");
	return Value::Null;
}

// glut.glutChangeToMenuEntry
Gura_DeclareFunction(glutChangeToMenuEntry)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "item", VTYPE_number, OCCUR_Once, FLAG_None);
	DeclareArg(env, "label", VTYPE_string, OCCUR_Once, FLAG_None);
	DeclareArg(env, "value", VTYPE_number, OCCUR_Once, FLAG_None);
	AddHelp(
		Gura_Symbol(en), Help::FMT_markdown,
		"");
}

Gura_ImplementFunction(glutChangeToMenuEntry)
{
#if 0
	int item = args.GetInt(0);
	const char *label = args.GetString(1);
	int value = args.GetInt(2);
	glutChangeToMenuEntry(item, label, value);
	return Value::Null;
#endif
	SetError_NotImpFunction(sig, "glutChangeToMenuEntry");
	return Value::Null;
}

// glut.glutChangeToSubMenu
Gura_DeclareFunction(glutChangeToSubMenu)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "item", VTYPE_number, OCCUR_Once, FLAG_None);
	DeclareArg(env, "label", VTYPE_string, OCCUR_Once, FLAG_None);
	DeclareArg(env, "submenu", VTYPE_number, OCCUR_Once, FLAG_None);
	AddHelp(
		Gura_Symbol(en), Help::FMT_markdown,
		"");
}

Gura_ImplementFunction(glutChangeToSubMenu)
{
#if 0
	int item = args.GetInt(0);
	const char *label = args.GetString(1);
	int submenu = args.GetInt(2);
	glutChangeToSubMenu(item, label, submenu);
	return Value::Null;
#endif
	SetError_NotImpFunction(sig, "glutChangeToSubMenu");
	return Value::Null;
}

// glut.glutRemoveMenuItem
Gura_DeclareFunction(glutRemoveMenuItem)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "item", VTYPE_number, OCCUR_Once, FLAG_None);
	AddHelp(
		Gura_Symbol(en), Help::FMT_markdown,
		"");
}

Gura_ImplementFunction(glutRemoveMenuItem)
{
	int item = args.GetInt(0);
	glutRemoveMenuItem(item);
	return Value::Null;
}

// glut.glutAttachMenu
Gura_DeclareFunction(glutAttachMenu)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "button", VTYPE_number, OCCUR_Once, FLAG_None);
	AddHelp(
		Gura_Symbol(en), Help::FMT_markdown,
		"");
}

Gura_ImplementFunction(glutAttachMenu)
{
	int button = args.GetInt(0);
	glutAttachMenu(button);
	return Value::Null;
}

// glut.glutDetachMenu
Gura_DeclareFunction(glutDetachMenu)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "button", VTYPE_number, OCCUR_Once, FLAG_None);
	AddHelp(
		Gura_Symbol(en), Help::FMT_markdown,
		"");
}

Gura_ImplementFunction(glutDetachMenu)
{
	int button = args.GetInt(0);
	glutDetachMenu(button);
	return Value::Null;
}

// glut.glutSetColor
Gura_DeclareFunction(glutSetColor)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	AddHelp(
		Gura_Symbol(en), Help::FMT_markdown,
		"");
}

Gura_ImplementFunction(glutSetColor)
{
#if 0
	glutSetColor();
	return Value::Null;
#endif
	SetError_NotImpFunction(sig, "glutSetColor");
	return Value::Null;
}

// glut.glutGetColor
Gura_DeclareFunction(glutGetColor)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareBlock(OCCUR_ZeroOrOnce);
	DeclareArg(env, "ndx", VTYPE_number, OCCUR_Once, FLAG_None);
	DeclareArg(env, "component", VTYPE_number, OCCUR_Once, FLAG_None);
	AddHelp(
		Gura_Symbol(en), Help::FMT_markdown,
		"");
}

Gura_ImplementFunction(glutGetColor)
{
	int ndx = args.GetInt(0);
	int component = args.GetInt(1);
	GLfloat _rtn = glutGetColor(ndx, component);
	return ReturnValue(env, sig, args, Value(_rtn));
}

// glut.glutCopyColormap
Gura_DeclareFunction(glutCopyColormap)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "win", VTYPE_number, OCCUR_Once, FLAG_None);
	AddHelp(
		Gura_Symbol(en), Help::FMT_markdown,
		"");
}

Gura_ImplementFunction(glutCopyColormap)
{
	int win = args.GetInt(0);
	glutCopyColormap(win);
	return Value::Null;
}

// glut.glutGet
Gura_DeclareFunction(glutGet)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareBlock(OCCUR_ZeroOrOnce);
	DeclareArg(env, "type", VTYPE_number, OCCUR_Once, FLAG_None);
	AddHelp(
		Gura_Symbol(en), Help::FMT_markdown,
		"");
}

Gura_ImplementFunction(glutGet)
{
	GLenum type = static_cast<GLenum>(args.GetInt(0));
	int _rtn = glutGet(type);
	return ReturnValue(env, sig, args, Value(_rtn));
}

// glut.glutDeviceGet
Gura_DeclareFunction(glutDeviceGet)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareBlock(OCCUR_ZeroOrOnce);
	DeclareArg(env, "type", VTYPE_number, OCCUR_Once, FLAG_None);
	AddHelp(
		Gura_Symbol(en), Help::FMT_markdown,
		"");
}

Gura_ImplementFunction(glutDeviceGet)
{
	GLenum type = static_cast<GLenum>(args.GetInt(0));
	int _rtn = glutDeviceGet(type);
	return ReturnValue(env, sig, args, Value(_rtn));
}

// glut.glutExtensionSupported
Gura_DeclareFunction(glutExtensionSupported)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareBlock(OCCUR_ZeroOrOnce);
	DeclareArg(env, "name", VTYPE_string, OCCUR_Once, FLAG_None);
	AddHelp(
		Gura_Symbol(en), Help::FMT_markdown,
		"");
}

Gura_ImplementFunction(glutExtensionSupported)
{
#if 0
	const char *name = args.GetString(0);
	int _rtn = glutExtensionSupported(name);
	return ReturnValue(env, sig, args, Value(_rtn));
#endif
	SetError_NotImpFunction(sig, "glutExtensionSupported");
	return Value::Null;
}

// glut.glutGetModifiers
Gura_DeclareFunction(glutGetModifiers)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
	AddHelp(
		Gura_Symbol(en), Help::FMT_markdown,
		"");
}

Gura_ImplementFunction(glutGetModifiers)
{
	int _rtn = glutGetModifiers();
	return ReturnValue(env, sig, args, Value(_rtn));
}

// glut.glutLayerGet
Gura_DeclareFunction(glutLayerGet)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareBlock(OCCUR_ZeroOrOnce);
	DeclareArg(env, "type", VTYPE_number, OCCUR_Once, FLAG_None);
	AddHelp(
		Gura_Symbol(en), Help::FMT_markdown,
		"");
}

Gura_ImplementFunction(glutLayerGet)
{
	GLenum type = static_cast<GLenum>(args.GetInt(0));
	int _rtn = glutLayerGet(type);
	return ReturnValue(env, sig, args, Value(_rtn));
}

// glut.glutWireSphere
Gura_DeclareFunction(glutWireSphere)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "radius", VTYPE_number, OCCUR_Once, FLAG_None);
	DeclareArg(env, "slices", VTYPE_number, OCCUR_Once, FLAG_None);
	DeclareArg(env, "stacks", VTYPE_number, OCCUR_Once, FLAG_None);
	AddHelp(
		Gura_Symbol(en), Help::FMT_markdown,
		"");
}

Gura_ImplementFunction(glutWireSphere)
{
	GLdouble radius = args.GetDouble(0);
	GLint slices = args.GetInt(1);
	GLint stacks = args.GetInt(2);
	glutWireSphere(radius, slices, stacks);
	return Value::Null;
}

// glut.glutSolidSphere
Gura_DeclareFunction(glutSolidSphere)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "radius", VTYPE_number, OCCUR_Once, FLAG_None);
	DeclareArg(env, "slices", VTYPE_number, OCCUR_Once, FLAG_None);
	DeclareArg(env, "stacks", VTYPE_number, OCCUR_Once, FLAG_None);
	AddHelp(
		Gura_Symbol(en), Help::FMT_markdown,
		"");
}

Gura_ImplementFunction(glutSolidSphere)
{
	GLdouble radius = args.GetDouble(0);
	GLint slices = args.GetInt(1);
	GLint stacks = args.GetInt(2);
	glutSolidSphere(radius, slices, stacks);
	return Value::Null;
}

// glut.glutWireCone
Gura_DeclareFunction(glutWireCone)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "base", VTYPE_number, OCCUR_Once, FLAG_None);
	DeclareArg(env, "height", VTYPE_number, OCCUR_Once, FLAG_None);
	DeclareArg(env, "slices", VTYPE_number, OCCUR_Once, FLAG_None);
	DeclareArg(env, "stacks", VTYPE_number, OCCUR_Once, FLAG_None);
	AddHelp(
		Gura_Symbol(en), Help::FMT_markdown,
		"");
}

Gura_ImplementFunction(glutWireCone)
{
	GLdouble base = args.GetDouble(0);
	GLdouble height = args.GetDouble(1);
	GLint slices = args.GetInt(2);
	GLint stacks = args.GetInt(3);
	glutWireCone(base, height, slices, stacks);
	return Value::Null;
}

// glut.glutSolidCone
Gura_DeclareFunction(glutSolidCone)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "base", VTYPE_number, OCCUR_Once, FLAG_None);
	DeclareArg(env, "height", VTYPE_number, OCCUR_Once, FLAG_None);
	DeclareArg(env, "slices", VTYPE_number, OCCUR_Once, FLAG_None);
	DeclareArg(env, "stacks", VTYPE_number, OCCUR_Once, FLAG_None);
	AddHelp(
		Gura_Symbol(en), Help::FMT_markdown,
		"");
}

Gura_ImplementFunction(glutSolidCone)
{
	GLdouble base = args.GetDouble(0);
	GLdouble height = args.GetDouble(1);
	GLint slices = args.GetInt(2);
	GLint stacks = args.GetInt(3);
	glutSolidCone(base, height, slices, stacks);
	return Value::Null;
}

// glut.glutWireCube
Gura_DeclareFunction(glutWireCube)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "size", VTYPE_number, OCCUR_Once, FLAG_None);
	AddHelp(
		Gura_Symbol(en), Help::FMT_markdown,
		"");
}

Gura_ImplementFunction(glutWireCube)
{
	GLdouble size = args.GetDouble(0);
	glutWireCube(size);
	return Value::Null;
}

// glut.glutSolidCube
Gura_DeclareFunction(glutSolidCube)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "size", VTYPE_number, OCCUR_Once, FLAG_None);
	AddHelp(
		Gura_Symbol(en), Help::FMT_markdown,
		"");
}

Gura_ImplementFunction(glutSolidCube)
{
	GLdouble size = args.GetDouble(0);
	glutSolidCube(size);
	return Value::Null;
}

// glut.glutWireTorus
Gura_DeclareFunction(glutWireTorus)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "innerRadius", VTYPE_number, OCCUR_Once, FLAG_None);
	DeclareArg(env, "outerRadius", VTYPE_number, OCCUR_Once, FLAG_None);
	DeclareArg(env, "sides", VTYPE_number, OCCUR_Once, FLAG_None);
	DeclareArg(env, "rings", VTYPE_number, OCCUR_Once, FLAG_None);
	AddHelp(
		Gura_Symbol(en), Help::FMT_markdown,
		"");
}

Gura_ImplementFunction(glutWireTorus)
{
	GLdouble innerRadius = args.GetDouble(0);
	GLdouble outerRadius = args.GetDouble(1);
	GLint sides = args.GetInt(2);
	GLint rings = args.GetInt(3);
	glutWireTorus(innerRadius, outerRadius, sides, rings);
	return Value::Null;
}

// glut.glutSolidTorus
Gura_DeclareFunction(glutSolidTorus)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "innerRadius", VTYPE_number, OCCUR_Once, FLAG_None);
	DeclareArg(env, "outerRadius", VTYPE_number, OCCUR_Once, FLAG_None);
	DeclareArg(env, "sides", VTYPE_number, OCCUR_Once, FLAG_None);
	DeclareArg(env, "rings", VTYPE_number, OCCUR_Once, FLAG_None);
	AddHelp(
		Gura_Symbol(en), Help::FMT_markdown,
		"");
}

Gura_ImplementFunction(glutSolidTorus)
{
	GLdouble innerRadius = args.GetDouble(0);
	GLdouble outerRadius = args.GetDouble(1);
	GLint sides = args.GetInt(2);
	GLint rings = args.GetInt(3);
	glutSolidTorus(innerRadius, outerRadius, sides, rings);
	return Value::Null;
}

// glut.glutWireDodecahedron
Gura_DeclareFunction(glutWireDodecahedron)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	AddHelp(
		Gura_Symbol(en), Help::FMT_markdown,
		"");
}

Gura_ImplementFunction(glutWireDodecahedron)
{
	glutWireDodecahedron();
	return Value::Null;
}

// glut.glutSolidDodecahedron
Gura_DeclareFunction(glutSolidDodecahedron)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	AddHelp(
		Gura_Symbol(en), Help::FMT_markdown,
		"");
}

Gura_ImplementFunction(glutSolidDodecahedron)
{
	glutSolidDodecahedron();
	return Value::Null;
}

// glut.glutWireTeapot
Gura_DeclareFunction(glutWireTeapot)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "size", VTYPE_number, OCCUR_Once, FLAG_None);
	AddHelp(
		Gura_Symbol(en), Help::FMT_markdown,
		"");
}

Gura_ImplementFunction(glutWireTeapot)
{
	GLdouble size = args.GetDouble(0);
	glutWireTeapot(size);
	return Value::Null;
}

// glut.glutSolidTeapot
Gura_DeclareFunction(glutSolidTeapot)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "size", VTYPE_number, OCCUR_Once, FLAG_None);
	AddHelp(
		Gura_Symbol(en), Help::FMT_markdown,
		"");
}

Gura_ImplementFunction(glutSolidTeapot)
{
	GLdouble size = args.GetDouble(0);
	glutSolidTeapot(size);
	return Value::Null;
}

// glut.glutWireOctahedron
Gura_DeclareFunction(glutWireOctahedron)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	AddHelp(
		Gura_Symbol(en), Help::FMT_markdown,
		"");
}

Gura_ImplementFunction(glutWireOctahedron)
{
	glutWireOctahedron();
	return Value::Null;
}

// glut.glutSolidOctahedron
Gura_DeclareFunction(glutSolidOctahedron)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	AddHelp(
		Gura_Symbol(en), Help::FMT_markdown,
		"");
}

Gura_ImplementFunction(glutSolidOctahedron)
{
	glutSolidOctahedron();
	return Value::Null;
}

// glut.glutWireTetrahedron
Gura_DeclareFunction(glutWireTetrahedron)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	AddHelp(
		Gura_Symbol(en), Help::FMT_markdown,
		"");
}

Gura_ImplementFunction(glutWireTetrahedron)
{
	glutWireTetrahedron();
	return Value::Null;
}

// glut.glutSolidTetrahedron
Gura_DeclareFunction(glutSolidTetrahedron)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	AddHelp(
		Gura_Symbol(en), Help::FMT_markdown,
		"");
}

Gura_ImplementFunction(glutSolidTetrahedron)
{
	glutSolidTetrahedron();
	return Value::Null;
}

// glut.glutWireIcosahedron
Gura_DeclareFunction(glutWireIcosahedron)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	AddHelp(
		Gura_Symbol(en), Help::FMT_markdown,
		"");
}

Gura_ImplementFunction(glutWireIcosahedron)
{
	glutWireIcosahedron();
	return Value::Null;
}

// glut.glutSolidIcosahedron
Gura_DeclareFunction(glutSolidIcosahedron)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	AddHelp(
		Gura_Symbol(en), Help::FMT_markdown,
		"");
}

Gura_ImplementFunction(glutSolidIcosahedron)
{
	glutSolidIcosahedron();
	return Value::Null;
}

// glut.glutVideoResizeGet
Gura_DeclareFunction(glutVideoResizeGet)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareBlock(OCCUR_ZeroOrOnce);
	DeclareArg(env, "param", VTYPE_number, OCCUR_Once, FLAG_None);
	AddHelp(
		Gura_Symbol(en), Help::FMT_markdown,
		"");
}

Gura_ImplementFunction(glutVideoResizeGet)
{
	GLenum param = static_cast<GLenum>(args.GetInt(0));
	int _rtn = glutVideoResizeGet(param);
	return ReturnValue(env, sig, args, Value(_rtn));
}

// glut.glutSetupVideoResizing
Gura_DeclareFunction(glutSetupVideoResizing)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	AddHelp(
		Gura_Symbol(en), Help::FMT_markdown,
		"");
}

Gura_ImplementFunction(glutSetupVideoResizing)
{
	glutSetupVideoResizing();
	return Value::Null;
}

// glut.glutStopVideoResizing
Gura_DeclareFunction(glutStopVideoResizing)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	AddHelp(
		Gura_Symbol(en), Help::FMT_markdown,
		"");
}

Gura_ImplementFunction(glutStopVideoResizing)
{
	glutStopVideoResizing();
	return Value::Null;
}

// glut.glutVideoResize
Gura_DeclareFunction(glutVideoResize)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "x", VTYPE_number, OCCUR_Once, FLAG_None);
	DeclareArg(env, "y", VTYPE_number, OCCUR_Once, FLAG_None);
	DeclareArg(env, "width", VTYPE_number, OCCUR_Once, FLAG_None);
	DeclareArg(env, "height", VTYPE_number, OCCUR_Once, FLAG_None);
	AddHelp(
		Gura_Symbol(en), Help::FMT_markdown,
		"");
}

Gura_ImplementFunction(glutVideoResize)
{
	int x = args.GetInt(0);
	int y = args.GetInt(1);
	int width = args.GetInt(2);
	int height = args.GetInt(3);
	glutVideoResize(x, y, width, height);
	return Value::Null;
}

// glut.glutVideoPan
Gura_DeclareFunction(glutVideoPan)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "x", VTYPE_number, OCCUR_Once, FLAG_None);
	DeclareArg(env, "y", VTYPE_number, OCCUR_Once, FLAG_None);
	DeclareArg(env, "width", VTYPE_number, OCCUR_Once, FLAG_None);
	DeclareArg(env, "height", VTYPE_number, OCCUR_Once, FLAG_None);
	AddHelp(
		Gura_Symbol(en), Help::FMT_markdown,
		"");
}

Gura_ImplementFunction(glutVideoPan)
{
	int x = args.GetInt(0);
	int y = args.GetInt(1);
	int width = args.GetInt(2);
	int height = args.GetInt(3);
	glutVideoPan(x, y, width, height);
	return Value::Null;
}

// glut.glutReportErrors
Gura_DeclareFunction(glutReportErrors)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	AddHelp(
		Gura_Symbol(en), Help::FMT_markdown,
		"");
}

Gura_ImplementFunction(glutReportErrors)
{
	glutReportErrors();
	return Value::Null;
}

// glut.glutIgnoreKeyRepeat
Gura_DeclareFunction(glutIgnoreKeyRepeat)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "ignore", VTYPE_number, OCCUR_Once, FLAG_None);
	AddHelp(
		Gura_Symbol(en), Help::FMT_markdown,
		"");
}

Gura_ImplementFunction(glutIgnoreKeyRepeat)
{
	int ignore = args.GetInt(0);
	glutIgnoreKeyRepeat(ignore);
	return Value::Null;
}

// glut.glutSetKeyRepeat
Gura_DeclareFunction(glutSetKeyRepeat)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "repeatMode", VTYPE_number, OCCUR_Once, FLAG_None);
	AddHelp(
		Gura_Symbol(en), Help::FMT_markdown,
		"");
}

Gura_ImplementFunction(glutSetKeyRepeat)
{
	int repeatMode = args.GetInt(0);
	glutSetKeyRepeat(repeatMode);
	return Value::Null;
}

// glut.glutForceJoystickFunc
Gura_DeclareFunction(glutForceJoystickFunc)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	AddHelp(
		Gura_Symbol(en), Help::FMT_markdown,
		"");
}

Gura_ImplementFunction(glutForceJoystickFunc)
{
	glutForceJoystickFunc();
	return Value::Null;
}

// glut.glutGameModeString
Gura_DeclareFunction(glutGameModeString)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "string", VTYPE_string, OCCUR_Once, FLAG_None);
	AddHelp(
		Gura_Symbol(en), Help::FMT_markdown,
		"");
}

Gura_ImplementFunction(glutGameModeString)
{
#if 0
	const char *string = args.GetString(0);
	glutGameModeString(string);
	return Value::Null;
#endif
	SetError_NotImpFunction(sig, "glutGameModeString");
	return Value::Null;
}

// glut.glutEnterGameMode
Gura_DeclareFunction(glutEnterGameMode)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
	AddHelp(
		Gura_Symbol(en), Help::FMT_markdown,
		"");
}

Gura_ImplementFunction(glutEnterGameMode)
{
	int _rtn = glutEnterGameMode();
	return ReturnValue(env, sig, args, Value(_rtn));
}

// glut.glutLeaveGameMode
Gura_DeclareFunction(glutLeaveGameMode)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	AddHelp(
		Gura_Symbol(en), Help::FMT_markdown,
		"");
}

Gura_ImplementFunction(glutLeaveGameMode)
{
	glutLeaveGameMode();
	return Value::Null;
}

// glut.glutGameModeGet
Gura_DeclareFunction(glutGameModeGet)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareBlock(OCCUR_ZeroOrOnce);
	DeclareArg(env, "mode", VTYPE_number, OCCUR_Once, FLAG_None);
	AddHelp(
		Gura_Symbol(en), Help::FMT_markdown,
		"");
}

Gura_ImplementFunction(glutGameModeGet)
{
	GLenum mode = static_cast<GLenum>(args.GetInt(0));
	int _rtn = glutGameModeGet(mode);
	return ReturnValue(env, sig, args, Value(_rtn));
}


void AssignFunctions(Environment &env)
{
	Gura_AssignFunction(glutInit);
	Gura_AssignFunction(glutInitDisplayMode);
	Gura_AssignFunction(glutInitDisplayString);
	Gura_AssignFunction(glutInitWindowPosition);
	Gura_AssignFunction(glutInitWindowSize);
	Gura_AssignFunction(glutMainLoop);
	Gura_AssignFunction(glutCreateWindow);
	Gura_AssignFunction(glutCreateSubWindow);
	Gura_AssignFunction(glutDestroyWindow);
	Gura_AssignFunction(glutPostRedisplay);
	Gura_AssignFunction(glutPostWindowRedisplay);
	Gura_AssignFunction(glutSwapBuffers);
	Gura_AssignFunction(glutGetWindow);
	Gura_AssignFunction(glutSetWindow);
	Gura_AssignFunction(glutSetWindowTitle);
	Gura_AssignFunction(glutSetIconTitle);
	Gura_AssignFunction(glutPositionWindow);
	Gura_AssignFunction(glutReshapeWindow);
	Gura_AssignFunction(glutPopWindow);
	Gura_AssignFunction(glutPushWindow);
	Gura_AssignFunction(glutIconifyWindow);
	Gura_AssignFunction(glutShowWindow);
	Gura_AssignFunction(glutHideWindow);
	Gura_AssignFunction(glutFullScreen);
	Gura_AssignFunction(glutSetCursor);
	Gura_AssignFunction(glutWarpPointer);
	Gura_AssignFunction(glutSurfaceTexture);
	Gura_AssignFunction(glutWMCloseFunc);
	Gura_AssignFunction(glutCheckLoop);
	Gura_AssignFunction(glutEstablishOverlay);
	Gura_AssignFunction(glutRemoveOverlay);
	Gura_AssignFunction(glutUseLayer);
	Gura_AssignFunction(glutPostOverlayRedisplay);
	Gura_AssignFunction(glutPostWindowOverlayRedisplay);
	Gura_AssignFunction(glutShowOverlay);
	Gura_AssignFunction(glutHideOverlay);
	Gura_AssignFunction(glutCreateMenu);
	Gura_AssignFunction(glutDestroyMenu);
	Gura_AssignFunction(glutGetMenu);
	Gura_AssignFunction(glutSetMenu);
	Gura_AssignFunction(glutAddMenuEntry);
	Gura_AssignFunction(glutAddSubMenu);
	Gura_AssignFunction(glutChangeToMenuEntry);
	Gura_AssignFunction(glutChangeToSubMenu);
	Gura_AssignFunction(glutRemoveMenuItem);
	Gura_AssignFunction(glutAttachMenu);
	Gura_AssignFunction(glutDetachMenu);
	Gura_AssignFunction(glutSetColor);
	Gura_AssignFunction(glutGetColor);
	Gura_AssignFunction(glutCopyColormap);
	Gura_AssignFunction(glutGet);
	Gura_AssignFunction(glutDeviceGet);
	Gura_AssignFunction(glutExtensionSupported);
	Gura_AssignFunction(glutGetModifiers);
	Gura_AssignFunction(glutLayerGet);
	Gura_AssignFunction(glutWireSphere);
	Gura_AssignFunction(glutSolidSphere);
	Gura_AssignFunction(glutWireCone);
	Gura_AssignFunction(glutSolidCone);
	Gura_AssignFunction(glutWireCube);
	Gura_AssignFunction(glutSolidCube);
	Gura_AssignFunction(glutWireTorus);
	Gura_AssignFunction(glutSolidTorus);
	Gura_AssignFunction(glutWireDodecahedron);
	Gura_AssignFunction(glutSolidDodecahedron);
	Gura_AssignFunction(glutWireTeapot);
	Gura_AssignFunction(glutSolidTeapot);
	Gura_AssignFunction(glutWireOctahedron);
	Gura_AssignFunction(glutSolidOctahedron);
	Gura_AssignFunction(glutWireTetrahedron);
	Gura_AssignFunction(glutSolidTetrahedron);
	Gura_AssignFunction(glutWireIcosahedron);
	Gura_AssignFunction(glutSolidIcosahedron);
	Gura_AssignFunction(glutVideoResizeGet);
	Gura_AssignFunction(glutSetupVideoResizing);
	Gura_AssignFunction(glutStopVideoResizing);
	Gura_AssignFunction(glutVideoResize);
	Gura_AssignFunction(glutVideoPan);
	Gura_AssignFunction(glutReportErrors);
	Gura_AssignFunction(glutIgnoreKeyRepeat);
	Gura_AssignFunction(glutSetKeyRepeat);
	Gura_AssignFunction(glutForceJoystickFunc);
	Gura_AssignFunction(glutGameModeString);
	Gura_AssignFunction(glutEnterGameMode);
	Gura_AssignFunction(glutLeaveGameMode);
	Gura_AssignFunction(glutGameModeGet);
}

Gura_EndModuleScope(glut)
