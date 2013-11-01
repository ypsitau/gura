//----------------------------------------------------------------------------
// wxFilterInputStream
// extracted from fltinstr.tex
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Class derivation
//----------------------------------------------------------------------------
class wx_FilterInputStream: public wxFilterInputStream, public GuraObjectObserver {
private:
	Gura::Signal _sig;
	Object_wx_FilterInputStream *_pObj;
public:
	//inline wx_FilterInputStream(wxInputStream& stream) : wxFilterInputStream(stream), _sig(NULL), _pObj(NULL) {}
	//inline wx_FilterInputStream(wxInputStream* stream) : wxFilterInputStream(stream), _sig(NULL), _pObj(NULL) {}
	~wx_FilterInputStream();
	inline void AssocWithGura(Gura::Signal &sig, Object_wx_FilterInputStream *pObj) {
		_sig = sig, _pObj = pObj;
	}
	// virtual function of GuraObjectObserver
	virtual void GuraObjectDeleted();
};

wx_FilterInputStream::~wx_FilterInputStream()
{
	if (_pObj != NULL) _pObj->InvalidateEntity();
}

void wx_FilterInputStream::GuraObjectDeleted()
{
	_pObj = NULL;
}

//----------------------------------------------------------------------------
// Gura interfaces for wxFilterInputStream
//----------------------------------------------------------------------------
Gura_DeclareFunction(FilterInputStream)
{
	SetMode(RSLTMODE_Normal, FLAG_Map);
#if 0
	SetClassToConstruct(Gura_UserClass(wx_FilterInputStream));
	DeclareArg(env, "stream", VTYPE_wx_InputStream, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
#endif
}

Gura_ImplementFunction(FilterInputStream)
{
	if (!CheckWxReady(sig)) return Value::Null;
#if 0
	wxInputStream *stream = Object_wx_InputStream::GetObject(args, 0)->GetEntity();
	wx_FilterInputStream *pEntity = new wx_FilterInputStream(*stream);
	Object_wx_FilterInputStream *pObj = Object_wx_FilterInputStream::GetThisObj(args);
	if (pObj == NULL) {
		pObj = new Object_wx_FilterInputStream(pEntity, pEntity, OwnerFalse);
		pEntity->AssocWithGura(sig, pObj);
		return ReturnValue(env, sig, args, Value(pObj));
	}
	pObj->SetEntity(pEntity, pEntity, OwnerFalse);
	pEntity->AssocWithGura(sig, pObj);
	return ReturnValue(env, sig, args, args.GetThis());
#endif
	SetError_NotImplemented(sig);
	return Value::Null;
}

Gura_DeclareFunction(FilterInputStream_1)
{
	SetMode(RSLTMODE_Normal, FLAG_Map);
#if 0
	SetClassToConstruct(Gura_UserClass(wx_FilterInputStream));
	DeclareArg(env, "stream", VTYPE_wx_InputStream, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
#endif
}

Gura_ImplementFunction(FilterInputStream_1)
{
	if (!CheckWxReady(sig)) return Value::Null;
#if 0
	wxInputStream *stream = Object_wx_InputStream::GetObject(args, 0)->GetEntity();
	wx_FilterInputStream *pEntity = new wx_FilterInputStream(stream);
	Object_wx_FilterInputStream *pObj = Object_wx_FilterInputStream::GetThisObj(args);
	if (pObj == NULL) {
		pObj = new Object_wx_FilterInputStream(pEntity, pEntity, OwnerFalse);
		pEntity->AssocWithGura(sig, pObj);
		return ReturnValue(env, sig, args, Value(pObj));
	}
	pObj->SetEntity(pEntity, pEntity, OwnerFalse);
	pEntity->AssocWithGura(sig, pObj);
	return ReturnValue(env, sig, args, args.GetThis());
#endif
	SetError_NotImplemented(sig);
	return Value::Null;
}

//----------------------------------------------------------------------------
// Object implementation for wxFilterInputStream
//----------------------------------------------------------------------------
Object_wx_FilterInputStream::~Object_wx_FilterInputStream()
{
}

Object *Object_wx_FilterInputStream::Clone() const
{
	return NULL;
}

String Object_wx_FilterInputStream::ToString(bool exprFlag)
{
	String rtn("<wx.FilterInputStream:");
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
// Class implementation for wxFilterInputStream
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_FilterInputStream)
{
	Gura_AssignFunction(FilterInputStream);
	Gura_AssignFunction(FilterInputStream_1);
}

Gura_ImplementDescendantCreator(wx_FilterInputStream)
{
	return new Object_wx_FilterInputStream((pClass == NULL)? this : pClass, NULL, NULL, OwnerFalse);
}

Gura_EndModuleScope(wx)
