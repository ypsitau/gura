//----------------------------------------------------------------------------
// wxFileOutputStream
// extracted from fileostr.tex
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Class derivation
//----------------------------------------------------------------------------
class wx_FileOutputStream: public wxFileOutputStream, public GuraObjectObserver {
private:
	//Gura::Signal *_pSig;
	Object_wx_FileOutputStream *_pObj;
public:
	inline wx_FileOutputStream(const wxString& ofileName) : wxFileOutputStream(ofileName), _pObj(nullptr) {}
	inline wx_FileOutputStream(wxFile& file) : wxFileOutputStream(file), _pObj(nullptr) {}
	inline wx_FileOutputStream(int fd) : wxFileOutputStream(fd), _pObj(nullptr) {}
	~wx_FileOutputStream();
	inline void AssocWithGura(Object_wx_FileOutputStream *pObj) {
		_pObj = pObj;
	}
	// virtual function of GuraObjectObserver
	virtual void GuraObjectDeleted();
};

wx_FileOutputStream::~wx_FileOutputStream()
{
	if (_pObj != nullptr) _pObj->InvalidateEntity();
}

void wx_FileOutputStream::GuraObjectDeleted()
{
	_pObj = nullptr;
}

//----------------------------------------------------------------------------
// Gura interfaces for wxFileOutputStream
//----------------------------------------------------------------------------
Gura_DeclareFunction(FileOutputStream)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	SetClassToConstruct(Gura_UserClass(wx_FileOutputStream));
	DeclareArg(env, "ofileName", VTYPE_string, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(FileOutputStream)
{
	Signal &sig = env.GetSignal();
	if (!CheckWxReady(sig)) return Value::Nil;
	wxString ofileName = wxString::FromUTF8(arg.GetString(0));
	wx_FileOutputStream *pEntity = new wx_FileOutputStream(ofileName);
	Object_wx_FileOutputStream *pObj = Object_wx_FileOutputStream::GetObjectThis(arg);
	if (pObj == nullptr) {
		pObj = new Object_wx_FileOutputStream(pEntity, pEntity, OwnerFalse);
		pEntity->AssocWithGura(pObj);
		return ReturnValue(env, arg, Value(pObj));
	}
	pObj->SetEntity(pEntity, pEntity, OwnerFalse);
	pEntity->AssocWithGura(pObj);
	return ReturnValue(env, arg, arg.GetValueThis());
}

Gura_DeclareFunction(FileOutputStream_1)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	SetClassToConstruct(Gura_UserClass(wx_FileOutputStream));
	DeclareArg(env, "file", VTYPE_wx_File, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(FileOutputStream_1)
{
	Signal &sig = env.GetSignal();
	if (!CheckWxReady(sig)) return Value::Nil;
	wxFile *file = Object_wx_File::GetObject(arg, 0)->GetEntity();
	wx_FileOutputStream *pEntity = new wx_FileOutputStream(*file);
	Object_wx_FileOutputStream *pObj = Object_wx_FileOutputStream::GetObjectThis(arg);
	if (pObj == nullptr) {
		pObj = new Object_wx_FileOutputStream(pEntity, pEntity, OwnerFalse);
		pEntity->AssocWithGura(pObj);
		return ReturnValue(env, arg, Value(pObj));
	}
	pObj->SetEntity(pEntity, pEntity, OwnerFalse);
	pEntity->AssocWithGura(pObj);
	return ReturnValue(env, arg, arg.GetValueThis());
}

Gura_DeclareFunction(FileOutputStream_2)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	SetClassToConstruct(Gura_UserClass(wx_FileOutputStream));
	DeclareArg(env, "fd", VTYPE_number, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(FileOutputStream_2)
{
	Signal &sig = env.GetSignal();
	if (!CheckWxReady(sig)) return Value::Nil;
	int fd = arg.GetInt(0);
	wx_FileOutputStream *pEntity = new wx_FileOutputStream(fd);
	Object_wx_FileOutputStream *pObj = Object_wx_FileOutputStream::GetObjectThis(arg);
	if (pObj == nullptr) {
		pObj = new Object_wx_FileOutputStream(pEntity, pEntity, OwnerFalse);
		pEntity->AssocWithGura(pObj);
		return ReturnValue(env, arg, Value(pObj));
	}
	pObj->SetEntity(pEntity, pEntity, OwnerFalse);
	pEntity->AssocWithGura(pObj);
	return ReturnValue(env, arg, arg.GetValueThis());
}

Gura_DeclareMethod(wx_FileOutputStream, IsOk)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_FileOutputStream, IsOk)
{
	Signal &sig = env.GetSignal();
	Object_wx_FileOutputStream *pThis = Object_wx_FileOutputStream::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	bool rtn = pThis->GetEntity()->IsOk();
	return ReturnValue(env, arg, Value(rtn));
}

//----------------------------------------------------------------------------
// Object implementation for wxFileOutputStream
//----------------------------------------------------------------------------
Object_wx_FileOutputStream::~Object_wx_FileOutputStream()
{
}

Object *Object_wx_FileOutputStream::Clone() const
{
	return nullptr;
}

String Object_wx_FileOutputStream::ToString(bool exprFlag)
{
	String rtn("<wx.FileOutputStream:");
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
// Class implementation for wxFileOutputStream
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_FileOutputStream)
{
	Gura_AssignFunction(FileOutputStream);
	Gura_AssignFunction(FileOutputStream_1);
	Gura_AssignFunction(FileOutputStream_2);
	Gura_AssignMethod(wx_FileOutputStream, IsOk);
}

Gura_ImplementDescendantCreator(wx_FileOutputStream)
{
	return new Object_wx_FileOutputStream((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
