//----------------------------------------------------------------------------
// wxNotebookEvent
// extracted from noteevt.tex
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Class derivation
//----------------------------------------------------------------------------
class wx_NotebookEvent: public wxNotebookEvent, public GuraObjectObserver {
private:
	//Gura::Signal *_pSig;
	Object_wx_NotebookEvent *_pObj;
public:
	inline wx_NotebookEvent(wxEventType eventType, int id, int sel, int oldSel) : wxNotebookEvent(eventType, id, sel, oldSel), _pObj(nullptr) {}
	~wx_NotebookEvent();
	inline void AssocWithGura(Object_wx_NotebookEvent *pObj) {
		_pObj = pObj;
	}
	// virtual function of GuraObjectObserver
	virtual void GuraObjectDeleted();
};

wx_NotebookEvent::~wx_NotebookEvent()
{
	if (_pObj != nullptr) _pObj->InvalidateEntity();
}

void wx_NotebookEvent::GuraObjectDeleted()
{
	_pObj = nullptr;
}

//----------------------------------------------------------------------------
// Gura interfaces for wxNotebookEvent
//----------------------------------------------------------------------------
Gura_DeclareFunction(NotebookEvent)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	SetClassToConstruct(Gura_UserClass(wx_NotebookEvent));
	DeclareArg(env, "eventType", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareArg(env, "id", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareArg(env, "sel", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareArg(env, "oldSel", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(NotebookEvent)
{
	Signal &sig = env.GetSignal();
	if (!CheckWxReady(sig)) return Value::Nil;
	wxEventType eventType = wxEVT_NULL;
	if (arg.IsValid(0)) eventType = static_cast<wxEventType>(arg.GetInt(0));
	int id = 0;
	if (arg.IsValid(1)) id = arg.GetInt(1);
	int sel = -1;
	if (arg.IsValid(2)) sel = arg.GetInt(2);
	int oldSel = -1;
	if (arg.IsValid(3)) oldSel = arg.GetInt(3);
	wx_NotebookEvent *pEntity = new wx_NotebookEvent(eventType, id, sel, oldSel);
	Object_wx_NotebookEvent *pObj = Object_wx_NotebookEvent::GetObjectThis(arg);
	if (pObj == nullptr) {
		pObj = new Object_wx_NotebookEvent(pEntity, pEntity, OwnerFalse);
		pEntity->AssocWithGura(pObj);
		return ReturnValue(env, arg, Value(pObj));
	}
	pObj->SetEntity(pEntity, pEntity, OwnerFalse);
	pEntity->AssocWithGura(pObj);
	return ReturnValue(env, arg, arg.GetValueThis());
}

Gura_DeclareMethod(wx_NotebookEvent, GetOldSelection)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_NotebookEvent, GetOldSelection)
{
	Signal &sig = env.GetSignal();
	Object_wx_NotebookEvent *pThis = Object_wx_NotebookEvent::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	int rtn = pThis->GetEntity()->GetOldSelection();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_NotebookEvent, GetSelection)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_NotebookEvent, GetSelection)
{
	Signal &sig = env.GetSignal();
	Object_wx_NotebookEvent *pThis = Object_wx_NotebookEvent::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	int rtn = pThis->GetEntity()->GetSelection();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_NotebookEvent, SetOldSelection)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "page", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_NotebookEvent, SetOldSelection)
{
	Signal &sig = env.GetSignal();
	Object_wx_NotebookEvent *pThis = Object_wx_NotebookEvent::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	int page = arg.GetInt(0);
	pThis->GetEntity()->SetOldSelection(page);
	return Value::Nil;
}

Gura_DeclareMethod(wx_NotebookEvent, SetSelection)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "page", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_NotebookEvent, SetSelection)
{
	Signal &sig = env.GetSignal();
	Object_wx_NotebookEvent *pThis = Object_wx_NotebookEvent::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	int page = arg.GetInt(0);
	pThis->GetEntity()->SetSelection(page);
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Object implementation for wxNotebookEvent
//----------------------------------------------------------------------------
Object_wx_NotebookEvent::~Object_wx_NotebookEvent()
{
}

Object *Object_wx_NotebookEvent::Clone() const
{
	return nullptr;
}

String Object_wx_NotebookEvent::ToString(bool exprFlag)
{
	String rtn("<wx.NotebookEvent:");
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
// Class implementation for wxNotebookEvent
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_NotebookEvent)
{
	Gura_AssignFunction(NotebookEvent);
	Gura_AssignMethod(wx_NotebookEvent, GetOldSelection);
	Gura_AssignMethod(wx_NotebookEvent, GetSelection);
	Gura_AssignMethod(wx_NotebookEvent, SetOldSelection);
	Gura_AssignMethod(wx_NotebookEvent, SetSelection);
}

Gura_ImplementDescendantCreator(wx_NotebookEvent)
{
	return new Object_wx_NotebookEvent((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
