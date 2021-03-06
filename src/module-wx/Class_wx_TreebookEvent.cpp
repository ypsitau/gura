//----------------------------------------------------------------------------
// wxTreebookEvent
// extracted from treebookevent.tex
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Class derivation
//----------------------------------------------------------------------------
class wx_TreebookEvent: public wxTreebookEvent, public GuraObjectObserver {
private:
	//Gura::Signal *_pSig;
	Object_wx_TreebookEvent *_pObj;
public:
	inline wx_TreebookEvent(wxEventType commandType, int id, int nSel, int nOldSel) : wxTreebookEvent(commandType, id, nSel, nOldSel), _pObj(nullptr) {}
	~wx_TreebookEvent();
	inline void AssocWithGura(Object_wx_TreebookEvent *pObj) {
		_pObj = pObj;
	}
	// virtual function of GuraObjectObserver
	virtual void GuraObjectDeleted();
};

wx_TreebookEvent::~wx_TreebookEvent()
{
	if (_pObj != nullptr) _pObj->InvalidateEntity();
}

void wx_TreebookEvent::GuraObjectDeleted()
{
	_pObj = nullptr;
}

//----------------------------------------------------------------------------
// Gura interfaces for wxTreebookEvent
//----------------------------------------------------------------------------
Gura_DeclareFunction(TreebookEvent)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	SetClassToConstruct(Gura_UserClass(wx_TreebookEvent));
	DeclareArg(env, "commandType", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareArg(env, "id", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareArg(env, "nSel", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareArg(env, "nOldSel", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(TreebookEvent)
{
	Signal &sig = env.GetSignal();
	if (!CheckWxReady(sig)) return Value::Nil;
	wxEventType commandType = wxEVT_NULL;
	if (arg.IsValid(0)) commandType = static_cast<wxEventType>(arg.GetInt(0));
	int id = 0;
	if (arg.IsValid(1)) id = arg.GetInt(1);
	int nSel = wxNOT_FOUND;
	if (arg.IsValid(2)) nSel = arg.GetInt(2);
	int nOldSel = wxNOT_FOUND;
	if (arg.IsValid(3)) nOldSel = arg.GetInt(3);
	wx_TreebookEvent *pEntity = new wx_TreebookEvent(commandType, id, nSel, nOldSel);
	Object_wx_TreebookEvent *pObj = Object_wx_TreebookEvent::GetObjectThis(arg);
	if (pObj == nullptr) {
		pObj = new Object_wx_TreebookEvent(pEntity, pEntity, OwnerFalse);
		pEntity->AssocWithGura(pObj);
		return ReturnValue(env, arg, Value(pObj));
	}
	pObj->SetEntity(pEntity, pEntity, OwnerFalse);
	pEntity->AssocWithGura(pObj);
	return ReturnValue(env, arg, arg.GetValueThis());
}

Gura_DeclareMethod(wx_TreebookEvent, GetOldSelection)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_TreebookEvent, GetOldSelection)
{
	Signal &sig = env.GetSignal();
	Object_wx_TreebookEvent *pThis = Object_wx_TreebookEvent::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	int rtn = pThis->GetEntity()->GetOldSelection();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_TreebookEvent, GetSelection)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_TreebookEvent, GetSelection)
{
	Signal &sig = env.GetSignal();
	Object_wx_TreebookEvent *pThis = Object_wx_TreebookEvent::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	int rtn = pThis->GetEntity()->GetSelection();
	return ReturnValue(env, arg, Value(rtn));
}

//----------------------------------------------------------------------------
// Object implementation for wxTreebookEvent
//----------------------------------------------------------------------------
Object_wx_TreebookEvent::~Object_wx_TreebookEvent()
{
}

Object *Object_wx_TreebookEvent::Clone() const
{
	return nullptr;
}

String Object_wx_TreebookEvent::ToString(bool exprFlag)
{
	String rtn("<wx.TreebookEvent:");
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
// Class implementation for wxTreebookEvent
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_TreebookEvent)
{
	Gura_AssignFunction(TreebookEvent);
	Gura_AssignMethod(wx_TreebookEvent, GetOldSelection);
	Gura_AssignMethod(wx_TreebookEvent, GetSelection);
}

Gura_ImplementDescendantCreator(wx_TreebookEvent)
{
	return new Object_wx_TreebookEvent((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
