//----------------------------------------------------------------------------
// wxFileDirPickerEvent
// extracted from filepicker.tex
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Class derivation
//----------------------------------------------------------------------------
class wx_FileDirPickerEvent: public wxFileDirPickerEvent, public GuraObjectObserver {
private:
	//Gura::Signal *_pSig;
	Object_wx_FileDirPickerEvent *_pObj;
public:
	inline wx_FileDirPickerEvent(wxEventType type, wxObject * generator, int id, const wxString& path) : wxFileDirPickerEvent(type, generator, id, path), _pObj(nullptr) {}
	~wx_FileDirPickerEvent();
	inline void AssocWithGura(Object_wx_FileDirPickerEvent *pObj) {
		_pObj = pObj;
	}
	// virtual function of GuraObjectObserver
	virtual void GuraObjectDeleted();
};

wx_FileDirPickerEvent::~wx_FileDirPickerEvent()
{
	if (_pObj != nullptr) _pObj->InvalidateEntity();
}

void wx_FileDirPickerEvent::GuraObjectDeleted()
{
	_pObj = nullptr;
}

//----------------------------------------------------------------------------
// Gura interfaces for wxFileDirPickerEvent
//----------------------------------------------------------------------------
Gura_DeclareFunction(FileDirPickerEvent)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	SetClassToConstruct(Gura_UserClass(wx_FileDirPickerEvent));
	DeclareArg(env, "type", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "generator", VTYPE_wx_Object, OCCUR_Once);
	DeclareArg(env, "id", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "path", VTYPE_string, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(FileDirPickerEvent)
{
	Signal &sig = env.GetSignal();
	if (!CheckWxReady(sig)) return Value::Nil;
	wxEventType type = static_cast<wxEventType>(arg.GetInt(0));
	wxObject *generator = Object_wx_Object::GetObject(arg, 1)->GetEntity();
	int id = arg.GetInt(2);
	wxString path = wxString::FromUTF8(arg.GetString(3));
	wx_FileDirPickerEvent *pEntity = new wx_FileDirPickerEvent(type, generator, id, path);
	Object_wx_FileDirPickerEvent *pObj = Object_wx_FileDirPickerEvent::GetObjectThis(arg);
	if (pObj == nullptr) {
		pObj = new Object_wx_FileDirPickerEvent(pEntity, pEntity, OwnerFalse);
		pEntity->AssocWithGura(pObj);
		return ReturnValue(env, arg, Value(pObj));
	}
	pObj->SetEntity(pEntity, pEntity, OwnerFalse);
	pEntity->AssocWithGura(pObj);
	return ReturnValue(env, arg, arg.GetValueThis());
}

Gura_DeclareMethod(wx_FileDirPickerEvent, GetPath)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_FileDirPickerEvent, GetPath)
{
	Signal &sig = env.GetSignal();
	Object_wx_FileDirPickerEvent *pThis = Object_wx_FileDirPickerEvent::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxString rtn = pThis->GetEntity()->GetPath();
	return ReturnValue(env, arg, Value(static_cast<const char *>(rtn.ToUTF8())));
}

Gura_DeclareMethod(wx_FileDirPickerEvent, SetPath)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "path", VTYPE_string, OCCUR_Once);
}

Gura_ImplementMethod(wx_FileDirPickerEvent, SetPath)
{
	Signal &sig = env.GetSignal();
	Object_wx_FileDirPickerEvent *pThis = Object_wx_FileDirPickerEvent::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxString path = wxString::FromUTF8(arg.GetString(0));
	pThis->GetEntity()->SetPath(path);
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Object implementation for wxFileDirPickerEvent
//----------------------------------------------------------------------------
Object_wx_FileDirPickerEvent::~Object_wx_FileDirPickerEvent()
{
}

Object *Object_wx_FileDirPickerEvent::Clone() const
{
	return nullptr;
}

String Object_wx_FileDirPickerEvent::ToString(bool exprFlag)
{
	String rtn("<wx.FileDirPickerEvent:");
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
// Class implementation for wxFileDirPickerEvent
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_FileDirPickerEvent)
{
	Gura_AssignFunction(FileDirPickerEvent);
	Gura_AssignMethod(wx_FileDirPickerEvent, GetPath);
	Gura_AssignMethod(wx_FileDirPickerEvent, SetPath);
}

Gura_ImplementDescendantCreator(wx_FileDirPickerEvent)
{
	return new Object_wx_FileDirPickerEvent((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
