//----------------------------------------------------------------------------
// wxPrintData
// extracted from print.tex
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Class derivation
//----------------------------------------------------------------------------
class wx_PrintData: public wxPrintData, public GuraObjectObserver {
private:
	//Gura::Signal *_pSig;
	Object_wx_PrintData *_pObj;
public:
	inline wx_PrintData() : wxPrintData(), _pObj(nullptr) {}
	inline wx_PrintData(const wxPrintData& data) : wxPrintData(data), _pObj(nullptr) {}
	~wx_PrintData();
	inline void AssocWithGura(Object_wx_PrintData *pObj) {
		_pObj = pObj;
	}
	// virtual function of GuraObjectObserver
	virtual void GuraObjectDeleted();
};

wx_PrintData::~wx_PrintData()
{
	if (_pObj != nullptr) _pObj->InvalidateEntity();
}

void wx_PrintData::GuraObjectDeleted()
{
	_pObj = nullptr;
}

//----------------------------------------------------------------------------
// Gura interfaces for wxPrintData
//----------------------------------------------------------------------------
Gura_DeclareFunction(PrintDataEmpty)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	SetClassToConstruct(Gura_UserClass(wx_PrintData));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(PrintDataEmpty)
{
	Signal &sig = env.GetSignal();
	if (!CheckWxReady(sig)) return Value::Nil;
	wx_PrintData *pEntity = new wx_PrintData();
	Object_wx_PrintData *pObj = Object_wx_PrintData::GetObjectThis(arg);
	if (pObj == nullptr) {
		pObj = new Object_wx_PrintData(pEntity, pEntity, OwnerFalse);
		pEntity->AssocWithGura(pObj);
		return ReturnValue(env, arg, Value(pObj));
	}
	pObj->SetEntity(pEntity, pEntity, OwnerFalse);
	pEntity->AssocWithGura(pObj);
	return ReturnValue(env, arg, arg.GetValueThis());
}

Gura_DeclareFunction(PrintData)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	SetClassToConstruct(Gura_UserClass(wx_PrintData));
	DeclareArg(env, "data", VTYPE_wx_PrintData, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(PrintData)
{
	Signal &sig = env.GetSignal();
	if (!CheckWxReady(sig)) return Value::Nil;
	wxPrintData *data = Object_wx_PrintData::GetObject(arg, 0)->GetEntity();
	wx_PrintData *pEntity = new wx_PrintData(*data);
	Object_wx_PrintData *pObj = Object_wx_PrintData::GetObjectThis(arg);
	if (pObj == nullptr) {
		pObj = new Object_wx_PrintData(pEntity, pEntity, OwnerFalse);
		pEntity->AssocWithGura(pObj);
		return ReturnValue(env, arg, Value(pObj));
	}
	pObj->SetEntity(pEntity, pEntity, OwnerFalse);
	pEntity->AssocWithGura(pObj);
	return ReturnValue(env, arg, arg.GetValueThis());
}

Gura_DeclareMethod(wx_PrintData, GetCollate)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_PrintData, GetCollate)
{
	Signal &sig = env.GetSignal();
	Object_wx_PrintData *pThis = Object_wx_PrintData::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	bool rtn = pThis->GetEntity()->GetCollate();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_PrintData, GetBin)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_PrintData, GetBin)
{
	Signal &sig = env.GetSignal();
	Object_wx_PrintData *pThis = Object_wx_PrintData::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxPrintBin rtn = pThis->GetEntity()->GetBin();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_PrintData, GetColour)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_PrintData, GetColour)
{
	Signal &sig = env.GetSignal();
	Object_wx_PrintData *pThis = Object_wx_PrintData::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	bool rtn = pThis->GetEntity()->GetColour();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_PrintData, GetDuplex)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_PrintData, GetDuplex)
{
	Signal &sig = env.GetSignal();
	Object_wx_PrintData *pThis = Object_wx_PrintData::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxDuplexMode rtn = pThis->GetEntity()->GetDuplex();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_PrintData, GetNoCopies)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_PrintData, GetNoCopies)
{
	Signal &sig = env.GetSignal();
	Object_wx_PrintData *pThis = Object_wx_PrintData::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	int rtn = pThis->GetEntity()->GetNoCopies();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_PrintData, GetOrientation)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_PrintData, GetOrientation)
{
	Signal &sig = env.GetSignal();
	Object_wx_PrintData *pThis = Object_wx_PrintData::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	int rtn = pThis->GetEntity()->GetOrientation();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_PrintData, GetPaperId)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_PrintData, GetPaperId)
{
	Signal &sig = env.GetSignal();
	Object_wx_PrintData *pThis = Object_wx_PrintData::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxPaperSize rtn = pThis->GetEntity()->GetPaperId();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_PrintData, GetPrinterName)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_PrintData, GetPrinterName)
{
	Signal &sig = env.GetSignal();
	Object_wx_PrintData *pThis = Object_wx_PrintData::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxString rtn = pThis->GetEntity()->GetPrinterName();
	return ReturnValue(env, arg, Value(static_cast<const char *>(rtn.ToUTF8())));
}

Gura_DeclareMethod(wx_PrintData, GetQuality)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_PrintData, GetQuality)
{
	Signal &sig = env.GetSignal();
	Object_wx_PrintData *pThis = Object_wx_PrintData::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxPrintQuality rtn = pThis->GetEntity()->GetQuality();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_PrintData, IsOk)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_PrintData, IsOk)
{
	Signal &sig = env.GetSignal();
	Object_wx_PrintData *pThis = Object_wx_PrintData::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	bool rtn = pThis->GetEntity()->IsOk();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_PrintData, SetBin)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "flag", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_PrintData, SetBin)
{
	Signal &sig = env.GetSignal();
	Object_wx_PrintData *pThis = Object_wx_PrintData::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxPrintBin flag = static_cast<wxPrintBin>(arg.GetInt(0));
	pThis->GetEntity()->SetBin(flag);
	return Value::Nil;
}

Gura_DeclareMethod(wx_PrintData, SetCollate)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "flag", VTYPE_boolean, OCCUR_Once);
}

Gura_ImplementMethod(wx_PrintData, SetCollate)
{
	Signal &sig = env.GetSignal();
	Object_wx_PrintData *pThis = Object_wx_PrintData::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	bool flag = arg.GetBoolean(0);
	pThis->GetEntity()->SetCollate(flag);
	return Value::Nil;
}

Gura_DeclareMethod(wx_PrintData, SetColour)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "flag", VTYPE_boolean, OCCUR_Once);
}

Gura_ImplementMethod(wx_PrintData, SetColour)
{
	Signal &sig = env.GetSignal();
	Object_wx_PrintData *pThis = Object_wx_PrintData::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	bool flag = arg.GetBoolean(0);
	pThis->GetEntity()->SetColour(flag);
	return Value::Nil;
}

Gura_DeclareMethod(wx_PrintData, SetDuplex)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "mode", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_PrintData, SetDuplex)
{
	Signal &sig = env.GetSignal();
	Object_wx_PrintData *pThis = Object_wx_PrintData::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxDuplexMode mode = static_cast<wxDuplexMode>(arg.GetInt(0));
	pThis->GetEntity()->SetDuplex(mode);
	return Value::Nil;
}

Gura_DeclareMethod(wx_PrintData, SetNoCopies)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "n", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_PrintData, SetNoCopies)
{
	Signal &sig = env.GetSignal();
	Object_wx_PrintData *pThis = Object_wx_PrintData::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	int n = arg.GetInt(0);
	pThis->GetEntity()->SetNoCopies(n);
	return Value::Nil;
}

Gura_DeclareMethod(wx_PrintData, SetOrientation)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "orientation", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_PrintData, SetOrientation)
{
	Signal &sig = env.GetSignal();
	Object_wx_PrintData *pThis = Object_wx_PrintData::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	int orientation = arg.GetInt(0);
	pThis->GetEntity()->SetOrientation(orientation);
	return Value::Nil;
}

Gura_DeclareMethod(wx_PrintData, SetPaperId)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "paperId", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_PrintData, SetPaperId)
{
	Signal &sig = env.GetSignal();
	Object_wx_PrintData *pThis = Object_wx_PrintData::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxPaperSize paperId = static_cast<wxPaperSize>(arg.GetInt(0));
	pThis->GetEntity()->SetPaperId(paperId);
	return Value::Nil;
}

Gura_DeclareMethod(wx_PrintData, SetPrinterName)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "printerName", VTYPE_string, OCCUR_Once);
}

Gura_ImplementMethod(wx_PrintData, SetPrinterName)
{
	Signal &sig = env.GetSignal();
	Object_wx_PrintData *pThis = Object_wx_PrintData::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxString printerName = wxString::FromUTF8(arg.GetString(0));
	pThis->GetEntity()->SetPrinterName(printerName);
	return Value::Nil;
}

Gura_DeclareMethod(wx_PrintData, SetQuality)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "quality", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_PrintData, SetQuality)
{
	Signal &sig = env.GetSignal();
	Object_wx_PrintData *pThis = Object_wx_PrintData::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxPrintQuality quality = static_cast<wxPrintQuality>(arg.GetInt(0));
	pThis->GetEntity()->SetQuality(quality);
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Object implementation for wxPrintData
//----------------------------------------------------------------------------
Object_wx_PrintData::~Object_wx_PrintData()
{
}

Object *Object_wx_PrintData::Clone() const
{
	return nullptr;
}

String Object_wx_PrintData::ToString(bool exprFlag)
{
	String rtn("<wx.PrintData:");
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
// Class implementation for wxPrintData
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_PrintData)
{
	Gura_AssignFunction(PrintDataEmpty);
	Gura_AssignFunction(PrintData);
	Gura_AssignMethod(wx_PrintData, GetCollate);
	Gura_AssignMethod(wx_PrintData, GetBin);
	Gura_AssignMethod(wx_PrintData, GetColour);
	Gura_AssignMethod(wx_PrintData, GetDuplex);
	Gura_AssignMethod(wx_PrintData, GetNoCopies);
	Gura_AssignMethod(wx_PrintData, GetOrientation);
	Gura_AssignMethod(wx_PrintData, GetPaperId);
	Gura_AssignMethod(wx_PrintData, GetPrinterName);
	Gura_AssignMethod(wx_PrintData, GetQuality);
	Gura_AssignMethod(wx_PrintData, IsOk);
	Gura_AssignMethod(wx_PrintData, SetBin);
	Gura_AssignMethod(wx_PrintData, SetCollate);
	Gura_AssignMethod(wx_PrintData, SetColour);
	Gura_AssignMethod(wx_PrintData, SetDuplex);
	Gura_AssignMethod(wx_PrintData, SetNoCopies);
	Gura_AssignMethod(wx_PrintData, SetOrientation);
	Gura_AssignMethod(wx_PrintData, SetPaperId);
	Gura_AssignMethod(wx_PrintData, SetPrinterName);
	Gura_AssignMethod(wx_PrintData, SetQuality);
}

Gura_ImplementDescendantCreator(wx_PrintData)
{
	return new Object_wx_PrintData((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
