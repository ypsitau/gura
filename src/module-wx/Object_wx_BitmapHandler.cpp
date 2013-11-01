//----------------------------------------------------------------------------
// wxBitmapHandler
// extracted from bmphand.tex
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

Gura_DeclarePrivUserSymbol(Create);

//----------------------------------------------------------------------------
// Class derivation
//----------------------------------------------------------------------------
class wx_BitmapHandler: public wxBitmapHandler, public GuraObjectObserver {
private:
	Gura::Signal _sig;
	Object_wx_BitmapHandler *_pObj;
public:
	inline wx_BitmapHandler() : wxBitmapHandler(), _sig(NULL), _pObj(NULL) {}
	//virtual bool Create(wxBitmap* bitmap, const void* data, int type, int width, int height, int depth);
	~wx_BitmapHandler();
	inline void AssocWithGura(Gura::Signal &sig, Object_wx_BitmapHandler *pObj) {
		_sig = sig, _pObj = pObj;
	}
	// virtual function of GuraObjectObserver
	virtual void GuraObjectDeleted();
};

wx_BitmapHandler::~wx_BitmapHandler()
{
	if (_pObj != NULL) _pObj->InvalidateEntity();
}

void wx_BitmapHandler::GuraObjectDeleted()
{
	_pObj = NULL;
}

//----------------------------------------------------------------------------
// Gura interfaces for wxBitmapHandler
//----------------------------------------------------------------------------
Gura_DeclareFunction(BitmapHandlerEmpty)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	SetClassToConstruct(Gura_UserClass(wx_BitmapHandler));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(BitmapHandlerEmpty)
{
	if (!CheckWxReady(sig)) return Value::Null;
	wx_BitmapHandler *pEntity = new wx_BitmapHandler();
	Object_wx_BitmapHandler *pObj = Object_wx_BitmapHandler::GetThisObj(args);
	if (pObj == NULL) {
		pObj = new Object_wx_BitmapHandler(pEntity, pEntity, OwnerFalse);
		pEntity->AssocWithGura(sig, pObj);
		return ReturnValue(env, sig, args, Value(pObj));
	}
	pObj->SetEntity(pEntity, pEntity, OwnerFalse);
	pEntity->AssocWithGura(sig, pObj);
	return ReturnValue(env, sig, args, args.GetThis());
}

Gura_DeclareMethod(wx_BitmapHandler, Create)
{
	SetMode(RSLTMODE_Normal, FLAG_Map);
#if 0
	DeclareArg(env, "bitmap", VTYPE_wx_Bitmap, OCCUR_Once);
	DeclareArg(env, "data", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "type", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "width", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "height", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "depth", VTYPE_number, OCCUR_ZeroOrOnce);
#endif
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_BitmapHandler, Create)
{
#if 0
	Object_wx_BitmapHandler *pThis = Object_wx_BitmapHandler::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	wxBitmap *bitmap = Object_wx_Bitmap::GetObject(args, 0)->GetEntity();
	int data = args.GetInt(1);
	int type = args.GetInt(2);
	int width = args.GetInt(3);
	int height = args.GetInt(4);
	int depth = -1;
	if (args.IsValid(5)) depth = args.GetInt(5);
	bool rtn = pThis->GetEntity()->Create(bitmap, data, type, width, height, depth);
	return ReturnValue(env, sig, args, Value(rtn));
#endif
	SetError_NotImplemented(sig);
	return Value::Null;
}

Gura_DeclareMethod(wx_BitmapHandler, GetName)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_BitmapHandler, GetName)
{
	Object_wx_BitmapHandler *pThis = Object_wx_BitmapHandler::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	wxString rtn = pThis->GetEntity()->GetName();
	return ReturnValue(env, sig, args, Value(env, static_cast<const char *>(rtn.ToUTF8())));
}

Gura_DeclareMethod(wx_BitmapHandler, GetExtension)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_BitmapHandler, GetExtension)
{
	Object_wx_BitmapHandler *pThis = Object_wx_BitmapHandler::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	wxString rtn = pThis->GetEntity()->GetExtension();
	return ReturnValue(env, sig, args, Value(env, static_cast<const char *>(rtn.ToUTF8())));
}

Gura_DeclareMethod(wx_BitmapHandler, GetType)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_BitmapHandler, GetType)
{
	Object_wx_BitmapHandler *pThis = Object_wx_BitmapHandler::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	long rtn = pThis->GetEntity()->GetType();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_BitmapHandler, LoadFile)
{
	SetMode(RSLTMODE_Normal, FLAG_Map);
#if 0
	DeclareArg(env, "bitmap", VTYPE_wx_Bitmap, OCCUR_Once);
	DeclareArg(env, "name", VTYPE_string, OCCUR_Once);
	DeclareArg(env, "type", VTYPE_number, OCCUR_Once);
#endif
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_BitmapHandler, LoadFile)
{
#if 0
	Object_wx_BitmapHandler *pThis = Object_wx_BitmapHandler::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	wxBitmap *bitmap = Object_wx_Bitmap::GetObject(args, 0)->GetEntity();
	wxString name = wxString::FromUTF8(args.GetString(1));
	long type = args.GetLong(2);
	bool rtn = pThis->GetEntity()->LoadFile(bitmap, name, type);
	return ReturnValue(env, sig, args, Value(rtn));
#endif
	SetError_NotImplemented(sig);
	return Value::Null;
}

Gura_DeclareMethod(wx_BitmapHandler, SaveFile)
{
	SetMode(RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "bitmap", VTYPE_wx_Bitmap, OCCUR_Once);
	DeclareArg(env, "name", VTYPE_string, OCCUR_Once);
	DeclareArg(env, "type", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "palette", VTYPE_wx_Palette, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_BitmapHandler, SaveFile)
{
	Object_wx_BitmapHandler *pThis = Object_wx_BitmapHandler::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	wxBitmap *bitmap = Object_wx_Bitmap::GetObject(args, 0)->GetEntity();
	wxString name = wxString::FromUTF8(args.GetString(1));
	int type = args.GetInt(2);
	wxPalette *palette = (wxPalette *)(NULL);
	if (args.IsValid(3)) palette = Object_wx_Palette::GetObject(args, 3)->GetEntity();
	bool rtn = pThis->GetEntity()->SaveFile(bitmap, name, type, palette);
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_BitmapHandler, SetName)
{
	SetMode(RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "name", VTYPE_string, OCCUR_Once);
}

Gura_ImplementMethod(wx_BitmapHandler, SetName)
{
	Object_wx_BitmapHandler *pThis = Object_wx_BitmapHandler::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	wxString name = wxString::FromUTF8(args.GetString(0));
	pThis->GetEntity()->SetName(name);
	return Value::Null;
}

Gura_DeclareMethod(wx_BitmapHandler, SetExtension)
{
	SetMode(RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "extension", VTYPE_string, OCCUR_Once);
}

Gura_ImplementMethod(wx_BitmapHandler, SetExtension)
{
	Object_wx_BitmapHandler *pThis = Object_wx_BitmapHandler::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	wxString extension = wxString::FromUTF8(args.GetString(0));
	pThis->GetEntity()->SetExtension(extension);
	return Value::Null;
}

Gura_DeclareMethod(wx_BitmapHandler, SetType)
{
	SetMode(RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "type", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_BitmapHandler, SetType)
{
	Object_wx_BitmapHandler *pThis = Object_wx_BitmapHandler::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	long type = args.GetLong(0);
	pThis->GetEntity()->SetType(static_cast<wxBitmapType>(type));
	return Value::Null;
}

//----------------------------------------------------------------------------
// Object implementation for wxBitmapHandler
//----------------------------------------------------------------------------
Object_wx_BitmapHandler::~Object_wx_BitmapHandler()
{
}

Object *Object_wx_BitmapHandler::Clone() const
{
	return NULL;
}

String Object_wx_BitmapHandler::ToString(bool exprFlag)
{
	String rtn("<wx.BitmapHandler:");
	if (GetEntity() == NULL) {
		rtn += "invalid>";
	} else {
		char buff[64];
		::sprintf(buff, "%p>", GetEntity());
		rtn += buff;
	}
	return rtn;
}

//----------------------------------------------------------------------------
// Class implementation for wxBitmapHandler
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_BitmapHandler)
{
	Gura_RealizeUserSymbol(Create);
	Gura_AssignFunction(BitmapHandlerEmpty);
	Gura_AssignMethod(wx_BitmapHandler, Create);
	Gura_AssignMethod(wx_BitmapHandler, GetName);
	Gura_AssignMethod(wx_BitmapHandler, GetExtension);
	Gura_AssignMethod(wx_BitmapHandler, GetType);
	Gura_AssignMethod(wx_BitmapHandler, LoadFile);
	Gura_AssignMethod(wx_BitmapHandler, SaveFile);
	Gura_AssignMethod(wx_BitmapHandler, SetName);
	Gura_AssignMethod(wx_BitmapHandler, SetExtension);
	Gura_AssignMethod(wx_BitmapHandler, SetType);
}

Gura_ImplementDescendantCreator(wx_BitmapHandler)
{
	return new Object_wx_BitmapHandler((pClass == NULL)? this : pClass, NULL, NULL, OwnerFalse);
}

Gura_EndModuleScope(wx)
