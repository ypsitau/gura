//----------------------------------------------------------------------------
// wxScopedPtr
// extracted from scpdptr.tex
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Class derivation
//----------------------------------------------------------------------------
class wx_ScopedPtr: public wxScopedPtr, public GuraObjectObserver {
private:
	Gura::Signal _sig;
	Object_wx_ScopedPtr *_pObj;
public:
	~wx_ScopedPtr();
	inline void AssocWithGura(Gura::Signal &sig, Object_wx_ScopedPtr *pObj) {
		_sig = sig, _pObj = pObj;
	}
	// virtual function of GuraObjectObserver
	virtual void GuraObjectDeleted();
};

wx_ScopedPtr::~wx_ScopedPtr()
{
	if (_pObj != NULL) _pObj->InvalidateEntity();
}

void wx_ScopedPtr::GuraObjectDeleted()
{
	_pObj = NULL;
}

//----------------------------------------------------------------------------
// Gura interfaces for wxScopedPtr
//----------------------------------------------------------------------------
Gura_DeclareMethod(wx_ScopedPtr, explicit wxScopedPtr)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
}

Gura_ImplementMethod(wx_ScopedPtr, explicit wxScopedPtr)
{
	Object_wx_ScopedPtr *pThis = Object_wx_ScopedPtr::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->explicit wxScopedPtr();
	return Value::Null;
}

Gura_DeclareMethod(wx_ScopedPtr, release)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_ScopedPtr, release)
{
	Object_wx_ScopedPtr *pThis = Object_wx_ScopedPtr::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
}

Gura_DeclareMethod(wx_ScopedPtr, reset)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
}

Gura_ImplementMethod(wx_ScopedPtr, reset)
{
	Object_wx_ScopedPtr *pThis = Object_wx_ScopedPtr::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	pThis->GetEntity()->reset();
	return Value::Null;
}

Gura_DeclareMethod(wx_ScopedPtr, get)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_ScopedPtr, get)
{
	Object_wx_ScopedPtr *pThis = Object_wx_ScopedPtr::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
}

Gura_DeclareMethod(wx_ScopedPtr, swap)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "& other", VTYPE_wx_ScopedPtr, OCCUR_Once);
}

Gura_ImplementMethod(wx_ScopedPtr, swap)
{
	Object_wx_ScopedPtr *pThis = Object_wx_ScopedPtr::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	wxScopedPtr *& other = Object_wx_ScopedPtr::GetObject(args, 0)->GetEntity();
	pThis->GetEntity()->swap(*& other);
	return Value::Null;
}

//----------------------------------------------------------------------------
// Object implementation for wxScopedPtr
//----------------------------------------------------------------------------
Object_wx_ScopedPtr::~Object_wx_ScopedPtr()
{
	if (_pEntity != NULL) NotifyGuraObjectDeleted();
	if (_ownerFlag) delete _pEntity;
	_pEntity = NULL;
}

Object *Object_wx_ScopedPtr::Clone() const
{
	return NULL;
}

String Object_wx_ScopedPtr::ToString(bool exprFlag)
{
	String rtn("<wx.ScopedPtr:");
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
// Class implementation for wxScopedPtr
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_ScopedPtr)
{
	Gura_AssignMethod(wx_ScopedPtr, explicit wxScopedPtr);
	Gura_AssignMethod(wx_ScopedPtr, release);
	Gura_AssignMethod(wx_ScopedPtr, reset);
	Gura_AssignMethod(wx_ScopedPtr, get);
	Gura_AssignMethod(wx_ScopedPtr, swap);
}

Gura_ImplementDescendantCreator(wx_ScopedPtr)
{
	return new Object_wx_ScopedPtr((pClass == NULL)? this : pClass, NULL, NULL, OwnerFalse);
}

Gura_EndModuleScope(wx)
