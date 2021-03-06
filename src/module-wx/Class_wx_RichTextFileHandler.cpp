//----------------------------------------------------------------------------
// wxRichTextFileHandler
// extracted from richtextfilehandler.tex
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Class derivation
//----------------------------------------------------------------------------
class wx_RichTextFileHandler: public wxRichTextFileHandler, public GuraObjectObserver {
private:
	//Gura::Signal *_pSig;
	Object_wx_RichTextFileHandler *_pObj;
public:
	//inline wx_RichTextFileHandler(const wxString& name, const wxString& ext, int type) : wxRichTextFileHandler(name, ext, type), _pObj(nullptr) {}
	~wx_RichTextFileHandler();
	inline void AssocWithGura(Object_wx_RichTextFileHandler *pObj) {
		_pObj = pObj;
	}
	// virtual function of GuraObjectObserver
	virtual void GuraObjectDeleted();
};

wx_RichTextFileHandler::~wx_RichTextFileHandler()
{
	if (_pObj != nullptr) _pObj->InvalidateEntity();
}

void wx_RichTextFileHandler::GuraObjectDeleted()
{
	_pObj = nullptr;
}

//----------------------------------------------------------------------------
// Gura interfaces for wxRichTextFileHandler
//----------------------------------------------------------------------------
Gura_DeclareFunction(RichTextFileHandler)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
#if 0
	SetClassToConstruct(Gura_UserClass(wx_RichTextFileHandler));
	DeclareArg(env, "name", VTYPE_string, OCCUR_ZeroOrOnce);
	DeclareArg(env, "ext", VTYPE_string, OCCUR_ZeroOrOnce);
	DeclareArg(env, "type", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
#endif
}

Gura_ImplementFunction(RichTextFileHandler)
{
	Signal &sig = env.GetSignal();
	if (!CheckWxReady(sig)) return Value::Nil;
#if 0
	wxString name = wxEmptyString;
	if (arg.IsValid(0)) name = wxString::FromUTF8(arg.GetString(0));
	wxString ext = wxEmptyString;
	if (arg.IsValid(1)) ext = wxString::FromUTF8(arg.GetString(1));
	int type = 0;
	if (arg.IsValid(2)) type = arg.GetInt(2);
	wx_RichTextFileHandler *pEntity = new wx_RichTextFileHandler(name, ext, type);
	Object_wx_RichTextFileHandler *pObj = Object_wx_RichTextFileHandler::GetObjectThis(arg);
	if (pObj == nullptr) {
		pObj = new Object_wx_RichTextFileHandler(pEntity, pEntity, OwnerFalse);
		pEntity->AssocWithGura(pObj);
		return ReturnValue(env, arg, Value(pObj));
	}
	pObj->SetEntity(pEntity, pEntity, OwnerFalse);
	pEntity->AssocWithGura(pObj);
	return ReturnValue(env, arg, arg.GetValueThis());
#endif
	SetError_NotImplemented(sig);
	return Value::Nil;
}

Gura_DeclareMethod(wx_RichTextFileHandler, CanHandle)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "filename", VTYPE_string, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_RichTextFileHandler, CanHandle)
{
	Signal &sig = env.GetSignal();
	Object_wx_RichTextFileHandler *pThis = Object_wx_RichTextFileHandler::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxString filename = wxString::FromUTF8(arg.GetString(0));
	bool rtn = pThis->GetEntity()->CanHandle(filename);
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_RichTextFileHandler, CanLoad)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_RichTextFileHandler, CanLoad)
{
	Signal &sig = env.GetSignal();
	Object_wx_RichTextFileHandler *pThis = Object_wx_RichTextFileHandler::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	bool rtn = pThis->GetEntity()->CanLoad();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_RichTextFileHandler, CanSave)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_RichTextFileHandler, CanSave)
{
	Signal &sig = env.GetSignal();
	Object_wx_RichTextFileHandler *pThis = Object_wx_RichTextFileHandler::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	bool rtn = pThis->GetEntity()->CanSave();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_RichTextFileHandler, DoLoadFile)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
#if 0
	DeclareArg(env, "buffer", VTYPE_wx_RichTextBuffer, OCCUR_Once);
	DeclareArg(env, "stream", VTYPE_wx_InputStream, OCCUR_Once);
#endif
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_RichTextFileHandler, DoLoadFile)
{
	Signal &sig = env.GetSignal();
#if 0
	Object_wx_RichTextFileHandler *pThis = Object_wx_RichTextFileHandler::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxRichTextBuffer *buffer = Object_wx_RichTextBuffer::GetObject(arg, 0)->GetEntity();
	wxInputStream *stream = Object_wx_InputStream::GetObject(arg, 1)->GetEntity();
	bool rtn = pThis->GetEntity()->DoLoadFile(buffer, *stream);
	return ReturnValue(env, arg, Value(rtn));
#endif
	SetError_NotImplemented(sig);
	return Value::Nil;
}

Gura_DeclareMethod(wx_RichTextFileHandler, DoSaveFile)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
#if 0
	DeclareArg(env, "buffer", VTYPE_wx_RichTextBuffer, OCCUR_Once);
	DeclareArg(env, "stream", VTYPE_wx_OutputStream, OCCUR_Once);
#endif
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_RichTextFileHandler, DoSaveFile)
{
	Signal &sig = env.GetSignal();
#if 0
	Object_wx_RichTextFileHandler *pThis = Object_wx_RichTextFileHandler::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxRichTextBuffer *buffer = Object_wx_RichTextBuffer::GetObject(arg, 0)->GetEntity();
	wxOutputStream *stream = Object_wx_OutputStream::GetObject(arg, 1)->GetEntity();
	bool rtn = pThis->GetEntity()->DoSaveFile(buffer, *stream);
	return ReturnValue(env, arg, Value(rtn));
#endif
	SetError_NotImplemented(sig);
	return Value::Nil;
}

Gura_DeclareMethod(wx_RichTextFileHandler, GetEncoding)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_RichTextFileHandler, GetEncoding)
{
	Signal &sig = env.GetSignal();
	Object_wx_RichTextFileHandler *pThis = Object_wx_RichTextFileHandler::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxString rtn = pThis->GetEntity()->GetEncoding();
	return ReturnValue(env, arg, Value(static_cast<const char *>(rtn.ToUTF8())));
}

Gura_DeclareMethod(wx_RichTextFileHandler, GetExtension)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_RichTextFileHandler, GetExtension)
{
	Signal &sig = env.GetSignal();
	Object_wx_RichTextFileHandler *pThis = Object_wx_RichTextFileHandler::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxString rtn = pThis->GetEntity()->GetExtension();
	return ReturnValue(env, arg, Value(static_cast<const char *>(rtn.ToUTF8())));
}

Gura_DeclareMethod(wx_RichTextFileHandler, GetFlags)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_RichTextFileHandler, GetFlags)
{
	Signal &sig = env.GetSignal();
	Object_wx_RichTextFileHandler *pThis = Object_wx_RichTextFileHandler::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	int rtn = pThis->GetEntity()->GetFlags();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_RichTextFileHandler, GetName)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_RichTextFileHandler, GetName)
{
	Signal &sig = env.GetSignal();
	Object_wx_RichTextFileHandler *pThis = Object_wx_RichTextFileHandler::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxString rtn = pThis->GetEntity()->GetName();
	return ReturnValue(env, arg, Value(static_cast<const char *>(rtn.ToUTF8())));
}

Gura_DeclareMethod(wx_RichTextFileHandler, GetType)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_RichTextFileHandler, GetType)
{
	Signal &sig = env.GetSignal();
	Object_wx_RichTextFileHandler *pThis = Object_wx_RichTextFileHandler::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	int rtn = pThis->GetEntity()->GetType();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_RichTextFileHandler, IsVisible)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_RichTextFileHandler, IsVisible)
{
	Signal &sig = env.GetSignal();
	Object_wx_RichTextFileHandler *pThis = Object_wx_RichTextFileHandler::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	bool rtn = pThis->GetEntity()->IsVisible();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_RichTextFileHandler, LoadFile)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "buffer", VTYPE_wx_RichTextBuffer, OCCUR_Once);
	DeclareArg(env, "stream", VTYPE_wx_InputStream, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_RichTextFileHandler, LoadFile)
{
	Signal &sig = env.GetSignal();
	Object_wx_RichTextFileHandler *pThis = Object_wx_RichTextFileHandler::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxRichTextBuffer *buffer = Object_wx_RichTextBuffer::GetObject(arg, 0)->GetEntity();
	wxInputStream *stream = Object_wx_InputStream::GetObject(arg, 1)->GetEntity();
	bool rtn = pThis->GetEntity()->LoadFile(buffer, *stream);
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_RichTextFileHandler, LoadFile_1)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "buffer", VTYPE_wx_RichTextBuffer, OCCUR_Once);
	DeclareArg(env, "filename", VTYPE_string, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_RichTextFileHandler, LoadFile_1)
{
	Signal &sig = env.GetSignal();
	Object_wx_RichTextFileHandler *pThis = Object_wx_RichTextFileHandler::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxRichTextBuffer *buffer = Object_wx_RichTextBuffer::GetObject(arg, 0)->GetEntity();
	wxString filename = wxString::FromUTF8(arg.GetString(1));
	bool rtn = pThis->GetEntity()->LoadFile(buffer, filename);
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_RichTextFileHandler, SaveFile)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "buffer", VTYPE_wx_RichTextBuffer, OCCUR_Once);
	DeclareArg(env, "stream", VTYPE_wx_OutputStream, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_RichTextFileHandler, SaveFile)
{
	Signal &sig = env.GetSignal();
	Object_wx_RichTextFileHandler *pThis = Object_wx_RichTextFileHandler::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxRichTextBuffer *buffer = Object_wx_RichTextBuffer::GetObject(arg, 0)->GetEntity();
	wxOutputStream *stream = Object_wx_OutputStream::GetObject(arg, 1)->GetEntity();
	bool rtn = pThis->GetEntity()->SaveFile(buffer, *stream);
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_RichTextFileHandler, SaveFile_1)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "buffer", VTYPE_wx_RichTextBuffer, OCCUR_Once);
	DeclareArg(env, "filename", VTYPE_string, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_RichTextFileHandler, SaveFile_1)
{
	Signal &sig = env.GetSignal();
	Object_wx_RichTextFileHandler *pThis = Object_wx_RichTextFileHandler::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxRichTextBuffer *buffer = Object_wx_RichTextBuffer::GetObject(arg, 0)->GetEntity();
	wxString filename = wxString::FromUTF8(arg.GetString(1));
	bool rtn = pThis->GetEntity()->SaveFile(buffer, filename);
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_RichTextFileHandler, SetEncoding)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "encoding", VTYPE_string, OCCUR_Once);
}

Gura_ImplementMethod(wx_RichTextFileHandler, SetEncoding)
{
	Signal &sig = env.GetSignal();
	Object_wx_RichTextFileHandler *pThis = Object_wx_RichTextFileHandler::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxString encoding = wxString::FromUTF8(arg.GetString(0));
	pThis->GetEntity()->SetEncoding(encoding);
	return Value::Nil;
}

Gura_DeclareMethod(wx_RichTextFileHandler, SetExtension)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "ext", VTYPE_string, OCCUR_Once);
}

Gura_ImplementMethod(wx_RichTextFileHandler, SetExtension)
{
	Signal &sig = env.GetSignal();
	Object_wx_RichTextFileHandler *pThis = Object_wx_RichTextFileHandler::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxString ext = wxString::FromUTF8(arg.GetString(0));
	pThis->GetEntity()->SetExtension(ext);
	return Value::Nil;
}

Gura_DeclareMethod(wx_RichTextFileHandler, SetFlags)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "flags", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_RichTextFileHandler, SetFlags)
{
	Signal &sig = env.GetSignal();
	Object_wx_RichTextFileHandler *pThis = Object_wx_RichTextFileHandler::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	int flags = arg.GetInt(0);
	pThis->GetEntity()->SetFlags(flags);
	return Value::Nil;
}

Gura_DeclareMethod(wx_RichTextFileHandler, SetName)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "name", VTYPE_string, OCCUR_Once);
}

Gura_ImplementMethod(wx_RichTextFileHandler, SetName)
{
	Signal &sig = env.GetSignal();
	Object_wx_RichTextFileHandler *pThis = Object_wx_RichTextFileHandler::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxString name = wxString::FromUTF8(arg.GetString(0));
	pThis->GetEntity()->SetName(name);
	return Value::Nil;
}

Gura_DeclareMethod(wx_RichTextFileHandler, SetType)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "type", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_RichTextFileHandler, SetType)
{
	Signal &sig = env.GetSignal();
	Object_wx_RichTextFileHandler *pThis = Object_wx_RichTextFileHandler::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	int type = arg.GetInt(0);
	pThis->GetEntity()->SetType(type);
	return Value::Nil;
}

Gura_DeclareMethod(wx_RichTextFileHandler, SetVisible)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "visible", VTYPE_boolean, OCCUR_Once);
}

Gura_ImplementMethod(wx_RichTextFileHandler, SetVisible)
{
	Signal &sig = env.GetSignal();
	Object_wx_RichTextFileHandler *pThis = Object_wx_RichTextFileHandler::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	bool visible = arg.GetBoolean(0);
	pThis->GetEntity()->SetVisible(visible);
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Object implementation for wxRichTextFileHandler
//----------------------------------------------------------------------------
Object_wx_RichTextFileHandler::~Object_wx_RichTextFileHandler()
{
}

Object *Object_wx_RichTextFileHandler::Clone() const
{
	return nullptr;
}

String Object_wx_RichTextFileHandler::ToString(bool exprFlag)
{
	String rtn("<wx.RichTextFileHandler:");
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
// Class implementation for wxRichTextFileHandler
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_RichTextFileHandler)
{
	Gura_AssignFunction(RichTextFileHandler);
	Gura_AssignMethod(wx_RichTextFileHandler, CanHandle);
	Gura_AssignMethod(wx_RichTextFileHandler, CanLoad);
	Gura_AssignMethod(wx_RichTextFileHandler, CanSave);
	Gura_AssignMethod(wx_RichTextFileHandler, DoLoadFile);
	Gura_AssignMethod(wx_RichTextFileHandler, DoSaveFile);
	Gura_AssignMethod(wx_RichTextFileHandler, GetEncoding);
	Gura_AssignMethod(wx_RichTextFileHandler, GetExtension);
	Gura_AssignMethod(wx_RichTextFileHandler, GetFlags);
	Gura_AssignMethod(wx_RichTextFileHandler, GetName);
	Gura_AssignMethod(wx_RichTextFileHandler, GetType);
	Gura_AssignMethod(wx_RichTextFileHandler, IsVisible);
	Gura_AssignMethod(wx_RichTextFileHandler, LoadFile);
	Gura_AssignMethod(wx_RichTextFileHandler, LoadFile_1);
	Gura_AssignMethod(wx_RichTextFileHandler, SaveFile);
	Gura_AssignMethod(wx_RichTextFileHandler, SaveFile_1);
	Gura_AssignMethod(wx_RichTextFileHandler, SetEncoding);
	Gura_AssignMethod(wx_RichTextFileHandler, SetExtension);
	Gura_AssignMethod(wx_RichTextFileHandler, SetFlags);
	Gura_AssignMethod(wx_RichTextFileHandler, SetName);
	Gura_AssignMethod(wx_RichTextFileHandler, SetType);
	Gura_AssignMethod(wx_RichTextFileHandler, SetVisible);
}

Gura_ImplementDescendantCreator(wx_RichTextFileHandler)
{
	return new Object_wx_RichTextFileHandler((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
