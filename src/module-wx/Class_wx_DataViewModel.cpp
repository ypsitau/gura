//----------------------------------------------------------------------------
// wxDataViewModel
// extracted from dataviewmodel.tex
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Class derivation
//----------------------------------------------------------------------------
class wx_DataViewModel: public wxDataViewModel, public GuraObjectObserver {
private:
	//Gura::Signal *_pSig;
	Object_wx_DataViewModel *_pObj;
public:
	//inline wx_DataViewModel() : wxDataViewModel(), _pObj(nullptr) {}
	~wx_DataViewModel();
	inline void AssocWithGura(Object_wx_DataViewModel *pObj) {
		_pObj = pObj;
	}
	// virtual function of GuraObjectObserver
	virtual void GuraObjectDeleted();
};

wx_DataViewModel::~wx_DataViewModel()
{
	if (_pObj != nullptr) _pObj->InvalidateEntity();
}

void wx_DataViewModel::GuraObjectDeleted()
{
	_pObj = nullptr;
}

//----------------------------------------------------------------------------
// Gura interfaces for wxDataViewModel
//----------------------------------------------------------------------------
Gura_DeclareFunction(DataViewModelEmpty)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
#if 0
	SetClassToConstruct(Gura_UserClass(wx_DataViewModel));
	DeclareBlock(OCCUR_ZeroOrOnce);
#endif
}

Gura_ImplementFunction(DataViewModelEmpty)
{
	Signal &sig = env.GetSignal();
	if (!CheckWxReady(sig)) return Value::Nil;
#if 0
	wx_DataViewModel *pEntity = new wx_DataViewModel();
	Object_wx_DataViewModel *pObj = Object_wx_DataViewModel::GetObjectThis(arg);
	if (pObj == nullptr) {
		pObj = new Object_wx_DataViewModel(pEntity, pEntity, OwnerFalse);
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

//----------------------------------------------------------------------------
// Object implementation for wxDataViewModel
//----------------------------------------------------------------------------
Object_wx_DataViewModel::~Object_wx_DataViewModel()
{
}

Object *Object_wx_DataViewModel::Clone() const
{
	return nullptr;
}

String Object_wx_DataViewModel::ToString(bool exprFlag)
{
	String rtn("<wx.DataViewModel:");
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
// Class implementation for wxDataViewModel
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_DataViewModel)
{
	Gura_AssignFunction(DataViewModelEmpty);
}

Gura_ImplementDescendantCreator(wx_DataViewModel)
{
	return new Object_wx_DataViewModel((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
