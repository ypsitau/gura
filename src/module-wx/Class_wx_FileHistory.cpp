//----------------------------------------------------------------------------
// wxFileHistory
// extracted from filehist.tex
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Class derivation
//----------------------------------------------------------------------------
class wx_FileHistory: public wxFileHistory, public GuraObjectObserver {
private:
	//Gura::Signal *_pSig;
	Object_wx_FileHistory *_pObj;
public:
	inline wx_FileHistory(size_t maxFiles, wxWindowID idBase) : wxFileHistory(maxFiles, idBase), _pObj(nullptr) {}
	~wx_FileHistory();
	inline void AssocWithGura(Object_wx_FileHistory *pObj) {
		_pObj = pObj;
	}
	// virtual function of GuraObjectObserver
	virtual void GuraObjectDeleted();
};

wx_FileHistory::~wx_FileHistory()
{
	if (_pObj != nullptr) _pObj->InvalidateEntity();
}

void wx_FileHistory::GuraObjectDeleted()
{
	_pObj = nullptr;
}

//----------------------------------------------------------------------------
// Gura interfaces for wxFileHistory
//----------------------------------------------------------------------------
Gura_DeclareFunction(FileHistory)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	SetClassToConstruct(Gura_UserClass(wx_FileHistory));
	DeclareArg(env, "maxFiles", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareArg(env, "idBase", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(FileHistory)
{
	Signal &sig = env.GetSignal();
	if (!CheckWxReady(sig)) return Value::Nil;
	size_t maxFiles = 9;
	if (arg.IsValid(0)) maxFiles = arg.GetSizeT(0);
	wxWindowID idBase = wxID_FILE1;
	if (arg.IsValid(1)) idBase = static_cast<wxWindowID>(arg.GetInt(1));
	wx_FileHistory *pEntity = new wx_FileHistory(maxFiles, idBase);
	Object_wx_FileHistory *pObj = Object_wx_FileHistory::GetObjectThis(arg);
	if (pObj == nullptr) {
		pObj = new Object_wx_FileHistory(pEntity, pEntity, OwnerFalse);
		pEntity->AssocWithGura(pObj);
		return ReturnValue(env, arg, Value(pObj));
	}
	pObj->SetEntity(pEntity, pEntity, OwnerFalse);
	pEntity->AssocWithGura(pObj);
	return ReturnValue(env, arg, arg.GetValueThis());
}

Gura_DeclareMethod(wx_FileHistory, AddFileToHistory)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "filename", VTYPE_string, OCCUR_Once);
}

Gura_ImplementMethod(wx_FileHistory, AddFileToHistory)
{
	Signal &sig = env.GetSignal();
	Object_wx_FileHistory *pThis = Object_wx_FileHistory::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxString filename = wxString::FromUTF8(arg.GetString(0));
	pThis->GetEntity()->AddFileToHistory(filename);
	return Value::Nil;
}

Gura_DeclareMethod(wx_FileHistory, AddFilesToMenu)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_FileHistory, AddFilesToMenu)
{
	Signal &sig = env.GetSignal();
	Object_wx_FileHistory *pThis = Object_wx_FileHistory::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	pThis->GetEntity()->AddFilesToMenu();
	return Value::Nil;
}

Gura_DeclareMethod(wx_FileHistory, AddFilesToMenu_1)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "menu", VTYPE_wx_Menu, OCCUR_Once);
}

Gura_ImplementMethod(wx_FileHistory, AddFilesToMenu_1)
{
	Signal &sig = env.GetSignal();
	Object_wx_FileHistory *pThis = Object_wx_FileHistory::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxMenu *menu = Object_wx_Menu::GetObject(arg, 0)->GetEntity();
	pThis->GetEntity()->AddFilesToMenu(menu);
	return Value::Nil;
}

Gura_DeclareMethod(wx_FileHistory, GetBaseId)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_FileHistory, GetBaseId)
{
	Signal &sig = env.GetSignal();
	Object_wx_FileHistory *pThis = Object_wx_FileHistory::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxWindowID rtn = pThis->GetEntity()->GetBaseId();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_FileHistory, GetCount)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_FileHistory, GetCount)
{
	Signal &sig = env.GetSignal();
	Object_wx_FileHistory *pThis = Object_wx_FileHistory::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	size_t rtn = pThis->GetEntity()->GetCount();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_FileHistory, GetHistoryFile)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "index", VTYPE_number, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_FileHistory, GetHistoryFile)
{
	Signal &sig = env.GetSignal();
	Object_wx_FileHistory *pThis = Object_wx_FileHistory::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	size_t index = arg.GetSizeT(0);
	wxString rtn = pThis->GetEntity()->GetHistoryFile(index);
	return ReturnValue(env, arg, Value(static_cast<const char *>(rtn.ToUTF8())));
}

Gura_DeclareMethod(wx_FileHistory, GetMaxFiles)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_FileHistory, GetMaxFiles)
{
	Signal &sig = env.GetSignal();
	Object_wx_FileHistory *pThis = Object_wx_FileHistory::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	int rtn = pThis->GetEntity()->GetMaxFiles();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_FileHistory, GetMenus)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_FileHistory, GetMenus)
{
	Signal &sig = env.GetSignal();
#if 0
	Object_wx_FileHistory *pThis = Object_wx_FileHistory::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	const wxList &rtn = pThis->GetEntity()->GetMenus();
	return ReturnValue(env, arg, Value(new Object_wx_List(new wxList(rtn), nullptr, OwnerTrue)));
#endif
	SetError_NotImplemented(sig);
	return Value::Nil;
}

Gura_DeclareMethod(wx_FileHistory, Load)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "config", VTYPE_wx_ConfigBase, OCCUR_Once);
}

Gura_ImplementMethod(wx_FileHistory, Load)
{
	Signal &sig = env.GetSignal();
	Object_wx_FileHistory *pThis = Object_wx_FileHistory::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxConfigBase *config = Object_wx_ConfigBase::GetObject(arg, 0)->GetEntity();
	pThis->GetEntity()->Load(*config);
	return Value::Nil;
}

Gura_DeclareMethod(wx_FileHistory, RemoveFileFromHistory)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "i", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_FileHistory, RemoveFileFromHistory)
{
	Signal &sig = env.GetSignal();
	Object_wx_FileHistory *pThis = Object_wx_FileHistory::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	size_t i = arg.GetSizeT(0);
	pThis->GetEntity()->RemoveFileFromHistory(i);
	return Value::Nil;
}

Gura_DeclareMethod(wx_FileHistory, RemoveMenu)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "menu", VTYPE_wx_Menu, OCCUR_Once);
}

Gura_ImplementMethod(wx_FileHistory, RemoveMenu)
{
	Signal &sig = env.GetSignal();
	Object_wx_FileHistory *pThis = Object_wx_FileHistory::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxMenu *menu = Object_wx_Menu::GetObject(arg, 0)->GetEntity();
	pThis->GetEntity()->RemoveMenu(menu);
	return Value::Nil;
}

Gura_DeclareMethod(wx_FileHistory, Save)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "config", VTYPE_wx_ConfigBase, OCCUR_Once);
}

Gura_ImplementMethod(wx_FileHistory, Save)
{
	Signal &sig = env.GetSignal();
	Object_wx_FileHistory *pThis = Object_wx_FileHistory::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxConfigBase *config = Object_wx_ConfigBase::GetObject(arg, 0)->GetEntity();
	pThis->GetEntity()->Save(*config);
	return Value::Nil;
}

Gura_DeclareMethod(wx_FileHistory, SetBaseId)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "baseId", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_FileHistory, SetBaseId)
{
	Signal &sig = env.GetSignal();
	Object_wx_FileHistory *pThis = Object_wx_FileHistory::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxWindowID baseId = static_cast<wxWindowID>(arg.GetInt(0));
	pThis->GetEntity()->SetBaseId(baseId);
	return Value::Nil;
}

Gura_DeclareMethod(wx_FileHistory, UseMenu)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "menu", VTYPE_wx_Menu, OCCUR_Once);
}

Gura_ImplementMethod(wx_FileHistory, UseMenu)
{
	Signal &sig = env.GetSignal();
	Object_wx_FileHistory *pThis = Object_wx_FileHistory::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxMenu *menu = Object_wx_Menu::GetObject(arg, 0)->GetEntity();
	pThis->GetEntity()->UseMenu(menu);
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Object implementation for wxFileHistory
//----------------------------------------------------------------------------
Object_wx_FileHistory::~Object_wx_FileHistory()
{
}

Object *Object_wx_FileHistory::Clone() const
{
	return nullptr;
}

String Object_wx_FileHistory::ToString(bool exprFlag)
{
	String rtn("<wx.FileHistory:");
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
// Class implementation for wxFileHistory
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_FileHistory)
{
	Gura_AssignFunction(FileHistory);
	Gura_AssignMethod(wx_FileHistory, AddFileToHistory);
	Gura_AssignMethod(wx_FileHistory, AddFilesToMenu);
	Gura_AssignMethod(wx_FileHistory, AddFilesToMenu_1);
	Gura_AssignMethod(wx_FileHistory, GetBaseId);
	Gura_AssignMethod(wx_FileHistory, GetCount);
	Gura_AssignMethod(wx_FileHistory, GetHistoryFile);
	Gura_AssignMethod(wx_FileHistory, GetMaxFiles);
	Gura_AssignMethod(wx_FileHistory, GetMenus);
	Gura_AssignMethod(wx_FileHistory, Load);
	Gura_AssignMethod(wx_FileHistory, RemoveFileFromHistory);
	Gura_AssignMethod(wx_FileHistory, RemoveMenu);
	Gura_AssignMethod(wx_FileHistory, Save);
	Gura_AssignMethod(wx_FileHistory, SetBaseId);
	Gura_AssignMethod(wx_FileHistory, UseMenu);
}

Gura_ImplementDescendantCreator(wx_FileHistory)
{
	return new Object_wx_FileHistory((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
