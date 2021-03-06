//----------------------------------------------------------------------------
// wxFFileInputStream
// extracted from ffilestr.tex
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Class derivation
//----------------------------------------------------------------------------
class wx_FFileInputStream: public wxFFileInputStream, public GuraObjectObserver {
private:
	//Gura::Signal *_pSig;
	Object_wx_FFileInputStream *_pObj;
public:
	//inline wx_FFileInputStream(const wxString& filename, const wxChar * mode) : wxFFileInputStream(filename, mode), _pObj(nullptr) {}
	//inline wx_FFileInputStream(wxFFile& file) : wxFFileInputStream(file), _pObj(nullptr) {}
	//inline wx_FFileInputStream(FILE * fp) : wxFFileInputStream(fp), _pObj(nullptr) {}
	~wx_FFileInputStream();
	inline void AssocWithGura(Object_wx_FFileInputStream *pObj) {
		_pObj = pObj;
	}
	// virtual function of GuraObjectObserver
	virtual void GuraObjectDeleted();
};

wx_FFileInputStream::~wx_FFileInputStream()
{
	if (_pObj != nullptr) _pObj->InvalidateEntity();
}

void wx_FFileInputStream::GuraObjectDeleted()
{
	_pObj = nullptr;
}

//----------------------------------------------------------------------------
// Gura interfaces for wxFFileInputStream
//----------------------------------------------------------------------------
Gura_DeclareFunction(FFileInputStream)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
#if 0
	SetClassToConstruct(Gura_UserClass(wx_FFileInputStream));
	DeclareArg(env, "filename", VTYPE_string, OCCUR_Once);
	DeclareArg(env, "mode", VTYPE_string, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
#endif
}

Gura_ImplementFunction(FFileInputStream)
{
	Signal &sig = env.GetSignal();
	if (!CheckWxReady(sig)) return Value::Nil;
#if 0
	wxString filename = wxString::FromUTF8(arg.GetString(0));
	wxString _mode;
	const wxChar *mode = wxT("rb");
	if (arg.IsValid(1)) {
		_mode = wxString::FromUTF8(arg.GetString(1));
		mode = _mode;
	}
	wx_FFileInputStream *pEntity = new wx_FFileInputStream(filename, mode);
	Object_wx_FFileInputStream *pObj = Object_wx_FFileInputStream::GetObjectThis(arg);
	if (pObj == nullptr) {
		pObj = new Object_wx_FFileInputStream(pEntity, pEntity, OwnerFalse);
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

Gura_DeclareFunction(FFileInputStream_1)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
#if 0
	SetClassToConstruct(Gura_UserClass(wx_FFileInputStream));
	DeclareArg(env, "file", VTYPE_wx_FFile, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
#endif
}

Gura_ImplementFunction(FFileInputStream_1)
{
	Signal &sig = env.GetSignal();
	if (!CheckWxReady(sig)) return Value::Nil;
#if 0
	wxFFile *file = Object_wx_FFile::GetObject(arg, 0)->GetEntity();
	wx_FFileInputStream *pEntity = new wx_FFileInputStream(*file);
	Object_wx_FFileInputStream *pObj = Object_wx_FFileInputStream::GetObjectThis(arg);
	if (pObj == nullptr) {
		pObj = new Object_wx_FFileInputStream(pEntity, pEntity, OwnerFalse);
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

Gura_DeclareFunction(FFileInputStream_2)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
#if 0
	SetClassToConstruct(Gura_UserClass(wx_FFileInputStream));
	DeclareBlock(OCCUR_ZeroOrOnce);
#endif
}

Gura_ImplementFunction(FFileInputStream_2)
{
	Signal &sig = env.GetSignal();
	if (!CheckWxReady(sig)) return Value::Nil;
#if 0
	wx_FFileInputStream *pEntity = new wx_FFileInputStream();
	Object_wx_FFileInputStream *pObj = Object_wx_FFileInputStream::GetObjectThis(arg);
	if (pObj == nullptr) {
		pObj = new Object_wx_FFileInputStream(pEntity, pEntity, OwnerFalse);
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

Gura_DeclareMethod(wx_FFileInputStream, IsOk)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_FFileInputStream, IsOk)
{
	Signal &sig = env.GetSignal();
	Object_wx_FFileInputStream *pThis = Object_wx_FFileInputStream::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	bool rtn = pThis->GetEntity()->IsOk();
	return ReturnValue(env, arg, Value(rtn));
}

//----------------------------------------------------------------------------
// Object implementation for wxFFileInputStream
//----------------------------------------------------------------------------
Object_wx_FFileInputStream::~Object_wx_FFileInputStream()
{
}

Object *Object_wx_FFileInputStream::Clone() const
{
	return nullptr;
}

String Object_wx_FFileInputStream::ToString(bool exprFlag)
{
	String rtn("<wx.FFileInputStream:");
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
// Class implementation for wxFFileInputStream
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_FFileInputStream)
{
	Gura_AssignFunction(FFileInputStream);
	Gura_AssignFunction(FFileInputStream_1);
	Gura_AssignFunction(FFileInputStream_2);
	Gura_AssignMethod(wx_FFileInputStream, IsOk);
}

Gura_ImplementDescendantCreator(wx_FFileInputStream)
{
	return new Object_wx_FFileInputStream((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
