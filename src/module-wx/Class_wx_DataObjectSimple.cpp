//----------------------------------------------------------------------------
// wxDataObjectSimple
// extracted from dobjsmpl.tex
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

Gura_DeclarePrivUserSymbol(GetDataSize);
Gura_DeclarePrivUserSymbol(GetDataHere);
Gura_DeclarePrivUserSymbol(SetData);

//----------------------------------------------------------------------------
// Class derivation
//----------------------------------------------------------------------------
class wx_DataObjectSimple: public wxDataObjectSimple, public GuraObjectObserver {
private:
	Gura::Signal _sig;
	Object_wx_DataObjectSimple *_pObj;
public:
	inline wx_DataObjectSimple(const wxDataFormat& format) : wxDataObjectSimple(format), _sig(NULL), _pObj(NULL) {}
	//virtual size_t GetDataSize();
	//virtual bool GetDataHere(void *buf);
	//virtual bool SetData(size_t len, const void *buf);
	~wx_DataObjectSimple();
	inline void AssocWithGura(Gura::Signal &sig, Object_wx_DataObjectSimple *pObj) {
		_sig = sig, _pObj = pObj;
	}
	// virtual function of GuraObjectObserver
	virtual void GuraObjectDeleted();
};

wx_DataObjectSimple::~wx_DataObjectSimple()
{
	if (_pObj != NULL) _pObj->InvalidateEntity();
}

void wx_DataObjectSimple::GuraObjectDeleted()
{
	_pObj = NULL;
}

//----------------------------------------------------------------------------
// Gura interfaces for wxDataObjectSimple
//----------------------------------------------------------------------------
Gura_DeclareFunction(DataObjectSimple)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	SetClassToConstruct(Gura_UserClass(wx_DataObjectSimple));
	DeclareArg(env, "format", VTYPE_wx_DataFormat, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(DataObjectSimple)
{
	if (!CheckWxReady(sig)) return Value::Null;
	wxDataFormat *format = (wxDataFormat *)(&wxFormatInvalid);
	if (args.IsValid(0)) format = Object_wx_DataFormat::GetObject(args, 0)->GetEntity();
	wx_DataObjectSimple *pEntity = new wx_DataObjectSimple(*format);
	Object_wx_DataObjectSimple *pObj = Object_wx_DataObjectSimple::GetThisObj(args);
	if (pObj == NULL) {
		pObj = new Object_wx_DataObjectSimple(pEntity, pEntity, OwnerFalse);
		pEntity->AssocWithGura(sig, pObj);
		return ReturnValue(env, sig, args, Value(pObj));
	}
	pObj->SetEntity(pEntity, pEntity, OwnerFalse);
	pEntity->AssocWithGura(sig, pObj);
	return ReturnValue(env, sig, args, args.GetThis());
}

Gura_DeclareMethod(wx_DataObjectSimple, GetFormat)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_DataObjectSimple, GetFormat)
{
	Object_wx_DataObjectSimple *pThis = Object_wx_DataObjectSimple::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	const wxDataFormat &rtn = pThis->GetEntity()->GetFormat();
	return ReturnValue(env, sig, args, Value(new Object_wx_DataFormat(new wxDataFormat(rtn), NULL, OwnerTrue)));
}

Gura_DeclareMethod(wx_DataObjectSimple, SetFormat)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "format", VTYPE_wx_DataFormat, OCCUR_Once);
}

Gura_ImplementMethod(wx_DataObjectSimple, SetFormat)
{
	Object_wx_DataObjectSimple *pThis = Object_wx_DataObjectSimple::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	wxDataFormat *format = Object_wx_DataFormat::GetObject(args, 0)->GetEntity();
	pThis->GetEntity()->SetFormat(*format);
	return Value::Null;
}

Gura_DeclareMethod(wx_DataObjectSimple, GetDataSize)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_DataObjectSimple, GetDataSize)
{
	Object_wx_DataObjectSimple *pThis = Object_wx_DataObjectSimple::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	size_t rtn = pThis->GetEntity()->GetDataSize();
	return ReturnValue(env, sig, args, Value(rtn));
}

Gura_DeclareMethod(wx_DataObjectSimple, GetDataHere)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
#if 0
	DeclareArg(env, "*buf", VTYPE_number, OCCUR_Once);
#endif
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_DataObjectSimple, GetDataHere)
{
#if 0
	Object_wx_DataObjectSimple *pThis = Object_wx_DataObjectSimple::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	int *buf = args.GetInt(0);
	bool rtn = pThis->GetEntity()->GetDataHere(*buf);
	return ReturnValue(env, sig, args, Value(rtn));
#endif
	SetError_NotImplemented(sig);
	return Value::Null;
}

Gura_DeclareMethod(wx_DataObjectSimple, SetData)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
#if 0
	DeclareArg(env, "len", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "*buf", VTYPE_number, OCCUR_Once);
#endif
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_DataObjectSimple, SetData)
{
#if 0
	Object_wx_DataObjectSimple *pThis = Object_wx_DataObjectSimple::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	size_t len = args.GetSizeT(0);
	int *buf = args.GetInt(1);
	bool rtn = pThis->GetEntity()->SetData(len, *buf);
	return ReturnValue(env, sig, args, Value(rtn));
#endif
	SetError_NotImplemented(sig);
	return Value::Null;
}

//----------------------------------------------------------------------------
// Object implementation for wxDataObjectSimple
//----------------------------------------------------------------------------
Object_wx_DataObjectSimple::~Object_wx_DataObjectSimple()
{
}

Object *Object_wx_DataObjectSimple::Clone() const
{
	return NULL;
}

String Object_wx_DataObjectSimple::ToString(bool exprFlag)
{
	String rtn("<wx.DataObjectSimple:");
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
// Class implementation for wxDataObjectSimple
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_DataObjectSimple)
{
	Gura_RealizeUserSymbol(GetDataSize);
	Gura_RealizeUserSymbol(GetDataHere);
	Gura_RealizeUserSymbol(SetData);
	Gura_AssignFunction(DataObjectSimple);
	Gura_AssignMethod(wx_DataObjectSimple, GetFormat);
	Gura_AssignMethod(wx_DataObjectSimple, SetFormat);
	Gura_AssignMethod(wx_DataObjectSimple, GetDataSize);
	Gura_AssignMethod(wx_DataObjectSimple, GetDataHere);
	Gura_AssignMethod(wx_DataObjectSimple, SetData);
}

Gura_ImplementDescendantCreator(wx_DataObjectSimple)
{
	return new Object_wx_DataObjectSimple((pClass == NULL)? this : pClass, NULL, NULL, OwnerFalse);
}

Gura_EndModuleScope(wx)
