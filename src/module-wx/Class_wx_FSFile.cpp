//----------------------------------------------------------------------------
// wxFSFile
// extracted from fsfile.tex
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Class derivation
//----------------------------------------------------------------------------
class wx_FSFile: public wxFSFile, public GuraObjectObserver {
private:
	//Gura::Signal *_pSig;
	Object_wx_FSFile *_pObj;
public:
	//inline wx_FSFile(wxInputStream *stream, const wxString& loc, const wxString& mimetype, const wxString& anchor, wxDateTime modif) : wxFSFile(*stream, loc, mimetype, anchor, modif), _pObj(nullptr) {}
	~wx_FSFile();
	inline void AssocWithGura(Object_wx_FSFile *pObj) {
		_pObj = pObj;
	}
	// virtual function of GuraObjectObserver
	virtual void GuraObjectDeleted();
};

wx_FSFile::~wx_FSFile()
{
	if (_pObj != nullptr) _pObj->InvalidateEntity();
}

void wx_FSFile::GuraObjectDeleted()
{
	_pObj = nullptr;
}

//----------------------------------------------------------------------------
// Gura interfaces for wxFSFile
//----------------------------------------------------------------------------
Gura_DeclareFunction(FSFile)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
#if 0
	SetClassToConstruct(Gura_UserClass(wx_FSFile));
	DeclareArg(env, "*stream", VTYPE_wx_InputStream, OCCUR_Once);
	DeclareArg(env, "loc", VTYPE_string, OCCUR_Once);
	DeclareArg(env, "mimetype", VTYPE_string, OCCUR_Once);
	DeclareArg(env, "anchor", VTYPE_string, OCCUR_Once);
	DeclareArg(env, "modif", VTYPE_wx_DateTime, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
#endif
}

Gura_ImplementFunction(FSFile)
{
	Signal &sig = env.GetSignal();
	if (!CheckWxReady(sig)) return Value::Nil;
#if 0
	wxInputStream **stream = Object_wx_InputStream::GetObject(arg, 0)->GetEntity();
	wxString loc = wxString::FromUTF8(arg.GetString(1));
	wxString mimetype = wxString::FromUTF8(arg.GetString(2));
	wxString anchor = wxString::FromUTF8(arg.GetString(3));
	wxDateTime *modif = Object_wx_DateTime::GetObject(arg, 4)->GetEntity();
	wx_FSFile *pEntity = new wx_FSFile(**stream, loc, mimetype, anchor, *modif);
	Object_wx_FSFile *pObj = Object_wx_FSFile::GetObjectThis(arg);
	if (pObj == nullptr) {
		pObj = new Object_wx_FSFile(pEntity, pEntity, OwnerFalse);
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

Gura_DeclareMethod(wx_FSFile, DetachStream)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_FSFile, DetachStream)
{
	Signal &sig = env.GetSignal();
	Object_wx_FSFile *pThis = Object_wx_FSFile::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	pThis->GetEntity()->DetachStream();
	return Value::Nil;
}

Gura_DeclareMethod(wx_FSFile, GetAnchor)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_FSFile, GetAnchor)
{
	Signal &sig = env.GetSignal();
	Object_wx_FSFile *pThis = Object_wx_FSFile::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxString rtn = pThis->GetEntity()->GetAnchor();
	return ReturnValue(env, arg, Value(static_cast<const char *>(rtn.ToUTF8())));
}

Gura_DeclareMethod(wx_FSFile, GetLocation)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_FSFile, GetLocation)
{
	Signal &sig = env.GetSignal();
	Object_wx_FSFile *pThis = Object_wx_FSFile::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxString rtn = pThis->GetEntity()->GetLocation();
	return ReturnValue(env, arg, Value(static_cast<const char *>(rtn.ToUTF8())));
}

Gura_DeclareMethod(wx_FSFile, GetMimeType)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_FSFile, GetMimeType)
{
	Signal &sig = env.GetSignal();
	Object_wx_FSFile *pThis = Object_wx_FSFile::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxString rtn = pThis->GetEntity()->GetMimeType();
	return ReturnValue(env, arg, Value(static_cast<const char *>(rtn.ToUTF8())));
}

Gura_DeclareMethod(wx_FSFile, GetModificationTime)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_FSFile, GetModificationTime)
{
	Signal &sig = env.GetSignal();
	Object_wx_FSFile *pThis = Object_wx_FSFile::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxDateTime rtn = pThis->GetEntity()->GetModificationTime();
	return ReturnValue(env, arg, Value(new Object_wx_DateTime(new wxDateTime(rtn), nullptr, OwnerTrue)));
}

Gura_DeclareMethod(wx_FSFile, GetStream)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_FSFile, GetStream)
{
	Signal &sig = env.GetSignal();
	Object_wx_FSFile *pThis = Object_wx_FSFile::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxInputStream *rtn = (wxInputStream *)pThis->GetEntity()->GetStream();
	return ReturnValue(env, arg, Value(new Object_wx_InputStream(rtn, nullptr, OwnerFalse)));
}

//----------------------------------------------------------------------------
// Object implementation for wxFSFile
//----------------------------------------------------------------------------
Object_wx_FSFile::~Object_wx_FSFile()
{
}

Object *Object_wx_FSFile::Clone() const
{
	return nullptr;
}

String Object_wx_FSFile::ToString(bool exprFlag)
{
	String rtn("<wx.FSFile:");
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
// Class implementation for wxFSFile
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_FSFile)
{
	Gura_AssignFunction(FSFile);
	Gura_AssignMethod(wx_FSFile, DetachStream);
	Gura_AssignMethod(wx_FSFile, GetAnchor);
	Gura_AssignMethod(wx_FSFile, GetLocation);
	Gura_AssignMethod(wx_FSFile, GetMimeType);
	Gura_AssignMethod(wx_FSFile, GetModificationTime);
	Gura_AssignMethod(wx_FSFile, GetStream);
}

Gura_ImplementDescendantCreator(wx_FSFile)
{
	return new Object_wx_FSFile((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
