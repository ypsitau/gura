//----------------------------------------------------------------------------
// wxPageSetupDialogData
// extracted from pagedlg.tex
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Class derivation
//----------------------------------------------------------------------------
class wx_PageSetupDialogData: public wxPageSetupDialogData, public GuraObjectObserver {
private:
	//Gura::Signal *_pSig;
	Object_wx_PageSetupDialogData *_pObj;
public:
	inline wx_PageSetupDialogData() : wxPageSetupDialogData(), _pObj(nullptr) {}
	inline wx_PageSetupDialogData(wxPageSetupDialogData& data) : wxPageSetupDialogData(data), _pObj(nullptr) {}
	inline wx_PageSetupDialogData(wxPrintData& printData) : wxPageSetupDialogData(printData), _pObj(nullptr) {}
	~wx_PageSetupDialogData();
	inline void AssocWithGura(Object_wx_PageSetupDialogData *pObj) {
		_pObj = pObj;
	}
	// virtual function of GuraObjectObserver
	virtual void GuraObjectDeleted();
};

wx_PageSetupDialogData::~wx_PageSetupDialogData()
{
	if (_pObj != nullptr) _pObj->InvalidateEntity();
}

void wx_PageSetupDialogData::GuraObjectDeleted()
{
	_pObj = nullptr;
}

//----------------------------------------------------------------------------
// Gura interfaces for wxPageSetupDialogData
//----------------------------------------------------------------------------
Gura_DeclareFunction(PageSetupDialogDataEmpty)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	SetClassToConstruct(Gura_UserClass(wx_PageSetupDialogData));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(PageSetupDialogDataEmpty)
{
	Signal &sig = env.GetSignal();
	if (!CheckWxReady(sig)) return Value::Nil;
	wx_PageSetupDialogData *pEntity = new wx_PageSetupDialogData();
	Object_wx_PageSetupDialogData *pObj = Object_wx_PageSetupDialogData::GetObjectThis(arg);
	if (pObj == nullptr) {
		pObj = new Object_wx_PageSetupDialogData(pEntity, pEntity, OwnerFalse);
		pEntity->AssocWithGura(pObj);
		return ReturnValue(env, arg, Value(pObj));
	}
	pObj->SetEntity(pEntity, pEntity, OwnerFalse);
	pEntity->AssocWithGura(pObj);
	return ReturnValue(env, arg, arg.GetValueThis());
}

Gura_DeclareFunction(PageSetupDialogData)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	SetClassToConstruct(Gura_UserClass(wx_PageSetupDialogData));
	DeclareArg(env, "data", VTYPE_wx_PageSetupDialogData, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(PageSetupDialogData)
{
	Signal &sig = env.GetSignal();
	if (!CheckWxReady(sig)) return Value::Nil;
	wxPageSetupDialogData *data = Object_wx_PageSetupDialogData::GetObject(arg, 0)->GetEntity();
	wx_PageSetupDialogData *pEntity = new wx_PageSetupDialogData(*data);
	Object_wx_PageSetupDialogData *pObj = Object_wx_PageSetupDialogData::GetObjectThis(arg);
	if (pObj == nullptr) {
		pObj = new Object_wx_PageSetupDialogData(pEntity, pEntity, OwnerFalse);
		pEntity->AssocWithGura(pObj);
		return ReturnValue(env, arg, Value(pObj));
	}
	pObj->SetEntity(pEntity, pEntity, OwnerFalse);
	pEntity->AssocWithGura(pObj);
	return ReturnValue(env, arg, arg.GetValueThis());
}

Gura_DeclareFunction(PageSetupDialogData_1)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	SetClassToConstruct(Gura_UserClass(wx_PageSetupDialogData));
	DeclareArg(env, "printData", VTYPE_wx_PrintData, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(PageSetupDialogData_1)
{
	Signal &sig = env.GetSignal();
	if (!CheckWxReady(sig)) return Value::Nil;
	wxPrintData *printData = Object_wx_PrintData::GetObject(arg, 0)->GetEntity();
	wx_PageSetupDialogData *pEntity = new wx_PageSetupDialogData(*printData);
	Object_wx_PageSetupDialogData *pObj = Object_wx_PageSetupDialogData::GetObjectThis(arg);
	if (pObj == nullptr) {
		pObj = new Object_wx_PageSetupDialogData(pEntity, pEntity, OwnerFalse);
		pEntity->AssocWithGura(pObj);
		return ReturnValue(env, arg, Value(pObj));
	}
	pObj->SetEntity(pEntity, pEntity, OwnerFalse);
	pEntity->AssocWithGura(pObj);
	return ReturnValue(env, arg, arg.GetValueThis());
}

Gura_DeclareMethod(wx_PageSetupDialogData, EnableHelp)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "flag", VTYPE_boolean, OCCUR_Once);
}

Gura_ImplementMethod(wx_PageSetupDialogData, EnableHelp)
{
	Signal &sig = env.GetSignal();
	Object_wx_PageSetupDialogData *pThis = Object_wx_PageSetupDialogData::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	bool flag = arg.GetBoolean(0);
	pThis->GetEntity()->EnableHelp(flag);
	return Value::Nil;
}

Gura_DeclareMethod(wx_PageSetupDialogData, EnableMargins)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "flag", VTYPE_boolean, OCCUR_Once);
}

Gura_ImplementMethod(wx_PageSetupDialogData, EnableMargins)
{
	Signal &sig = env.GetSignal();
	Object_wx_PageSetupDialogData *pThis = Object_wx_PageSetupDialogData::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	bool flag = arg.GetBoolean(0);
	pThis->GetEntity()->EnableMargins(flag);
	return Value::Nil;
}

Gura_DeclareMethod(wx_PageSetupDialogData, EnableOrientation)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "flag", VTYPE_boolean, OCCUR_Once);
}

Gura_ImplementMethod(wx_PageSetupDialogData, EnableOrientation)
{
	Signal &sig = env.GetSignal();
	Object_wx_PageSetupDialogData *pThis = Object_wx_PageSetupDialogData::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	bool flag = arg.GetBoolean(0);
	pThis->GetEntity()->EnableOrientation(flag);
	return Value::Nil;
}

Gura_DeclareMethod(wx_PageSetupDialogData, EnablePaper)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "flag", VTYPE_boolean, OCCUR_Once);
}

Gura_ImplementMethod(wx_PageSetupDialogData, EnablePaper)
{
	Signal &sig = env.GetSignal();
	Object_wx_PageSetupDialogData *pThis = Object_wx_PageSetupDialogData::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	bool flag = arg.GetBoolean(0);
	pThis->GetEntity()->EnablePaper(flag);
	return Value::Nil;
}

Gura_DeclareMethod(wx_PageSetupDialogData, EnablePrinter)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "flag", VTYPE_boolean, OCCUR_Once);
}

Gura_ImplementMethod(wx_PageSetupDialogData, EnablePrinter)
{
	Signal &sig = env.GetSignal();
	Object_wx_PageSetupDialogData *pThis = Object_wx_PageSetupDialogData::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	bool flag = arg.GetBoolean(0);
	pThis->GetEntity()->EnablePrinter(flag);
	return Value::Nil;
}

Gura_DeclareMethod(wx_PageSetupDialogData, GetDefaultMinMargins)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_PageSetupDialogData, GetDefaultMinMargins)
{
	Signal &sig = env.GetSignal();
	Object_wx_PageSetupDialogData *pThis = Object_wx_PageSetupDialogData::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	bool rtn = pThis->GetEntity()->GetDefaultMinMargins();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_PageSetupDialogData, GetEnableMargins)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_PageSetupDialogData, GetEnableMargins)
{
	Signal &sig = env.GetSignal();
	Object_wx_PageSetupDialogData *pThis = Object_wx_PageSetupDialogData::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	bool rtn = pThis->GetEntity()->GetEnableMargins();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_PageSetupDialogData, GetEnableOrientation)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_PageSetupDialogData, GetEnableOrientation)
{
	Signal &sig = env.GetSignal();
	Object_wx_PageSetupDialogData *pThis = Object_wx_PageSetupDialogData::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	bool rtn = pThis->GetEntity()->GetEnableOrientation();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_PageSetupDialogData, GetEnablePaper)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_PageSetupDialogData, GetEnablePaper)
{
	Signal &sig = env.GetSignal();
	Object_wx_PageSetupDialogData *pThis = Object_wx_PageSetupDialogData::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	bool rtn = pThis->GetEntity()->GetEnablePaper();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_PageSetupDialogData, GetEnablePrinter)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_PageSetupDialogData, GetEnablePrinter)
{
	Signal &sig = env.GetSignal();
	Object_wx_PageSetupDialogData *pThis = Object_wx_PageSetupDialogData::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	bool rtn = pThis->GetEntity()->GetEnablePrinter();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_PageSetupDialogData, GetEnableHelp)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_PageSetupDialogData, GetEnableHelp)
{
	Signal &sig = env.GetSignal();
	Object_wx_PageSetupDialogData *pThis = Object_wx_PageSetupDialogData::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	bool rtn = pThis->GetEntity()->GetEnableHelp();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_PageSetupDialogData, GetDefaultInfo)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_PageSetupDialogData, GetDefaultInfo)
{
	Signal &sig = env.GetSignal();
	Object_wx_PageSetupDialogData *pThis = Object_wx_PageSetupDialogData::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	bool rtn = pThis->GetEntity()->GetDefaultInfo();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_PageSetupDialogData, GetMarginTopLeft)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_PageSetupDialogData, GetMarginTopLeft)
{
	Signal &sig = env.GetSignal();
	Object_wx_PageSetupDialogData *pThis = Object_wx_PageSetupDialogData::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxPoint rtn = pThis->GetEntity()->GetMarginTopLeft();
	return ReturnValue(env, arg, Value(new Object_wx_Point(new wxPoint(rtn), nullptr, OwnerTrue)));
}

Gura_DeclareMethod(wx_PageSetupDialogData, GetMarginBottomRight)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_PageSetupDialogData, GetMarginBottomRight)
{
	Signal &sig = env.GetSignal();
	Object_wx_PageSetupDialogData *pThis = Object_wx_PageSetupDialogData::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxPoint rtn = pThis->GetEntity()->GetMarginBottomRight();
	return ReturnValue(env, arg, Value(new Object_wx_Point(new wxPoint(rtn), nullptr, OwnerTrue)));
}

Gura_DeclareMethod(wx_PageSetupDialogData, GetMinMarginTopLeft)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_PageSetupDialogData, GetMinMarginTopLeft)
{
	Signal &sig = env.GetSignal();
	Object_wx_PageSetupDialogData *pThis = Object_wx_PageSetupDialogData::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxPoint rtn = pThis->GetEntity()->GetMinMarginTopLeft();
	return ReturnValue(env, arg, Value(new Object_wx_Point(new wxPoint(rtn), nullptr, OwnerTrue)));
}

Gura_DeclareMethod(wx_PageSetupDialogData, GetMinMarginBottomRight)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_PageSetupDialogData, GetMinMarginBottomRight)
{
	Signal &sig = env.GetSignal();
	Object_wx_PageSetupDialogData *pThis = Object_wx_PageSetupDialogData::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxPoint rtn = pThis->GetEntity()->GetMinMarginBottomRight();
	return ReturnValue(env, arg, Value(new Object_wx_Point(new wxPoint(rtn), nullptr, OwnerTrue)));
}

Gura_DeclareMethod(wx_PageSetupDialogData, GetPaperId)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_PageSetupDialogData, GetPaperId)
{
	Signal &sig = env.GetSignal();
	Object_wx_PageSetupDialogData *pThis = Object_wx_PageSetupDialogData::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxPaperSize rtn = pThis->GetEntity()->GetPaperId();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_PageSetupDialogData, GetPaperSize)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_PageSetupDialogData, GetPaperSize)
{
	Signal &sig = env.GetSignal();
	Object_wx_PageSetupDialogData *pThis = Object_wx_PageSetupDialogData::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxSize rtn = pThis->GetEntity()->GetPaperSize();
	return ReturnValue(env, arg, Value(new Object_wx_Size(new wxSize(rtn), nullptr, OwnerTrue)));
}

Gura_DeclareMethod(wx_PageSetupDialogData, GetPrintData)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_PageSetupDialogData, GetPrintData)
{
	Signal &sig = env.GetSignal();
	Object_wx_PageSetupDialogData *pThis = Object_wx_PageSetupDialogData::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxPrintData &rtn = pThis->GetEntity()->GetPrintData();
	return ReturnValue(env, arg, Value(new Object_wx_PrintData(new wxPrintData(rtn), nullptr, OwnerTrue)));
}

Gura_DeclareMethod(wx_PageSetupDialogData, IsOk)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_PageSetupDialogData, IsOk)
{
	Signal &sig = env.GetSignal();
	Object_wx_PageSetupDialogData *pThis = Object_wx_PageSetupDialogData::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	bool rtn = pThis->GetEntity()->IsOk();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_PageSetupDialogData, SetDefaultInfo)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "flag", VTYPE_boolean, OCCUR_Once);
}

Gura_ImplementMethod(wx_PageSetupDialogData, SetDefaultInfo)
{
	Signal &sig = env.GetSignal();
	Object_wx_PageSetupDialogData *pThis = Object_wx_PageSetupDialogData::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	bool flag = arg.GetBoolean(0);
	pThis->GetEntity()->SetDefaultInfo(flag);
	return Value::Nil;
}

Gura_DeclareMethod(wx_PageSetupDialogData, SetDefaultMinMargins)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "flag", VTYPE_boolean, OCCUR_Once);
}

Gura_ImplementMethod(wx_PageSetupDialogData, SetDefaultMinMargins)
{
	Signal &sig = env.GetSignal();
	Object_wx_PageSetupDialogData *pThis = Object_wx_PageSetupDialogData::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	bool flag = arg.GetBoolean(0);
	pThis->GetEntity()->SetDefaultMinMargins(flag);
	return Value::Nil;
}

Gura_DeclareMethod(wx_PageSetupDialogData, SetMarginTopLeft)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "pt", VTYPE_wx_Point, OCCUR_Once);
}

Gura_ImplementMethod(wx_PageSetupDialogData, SetMarginTopLeft)
{
	Signal &sig = env.GetSignal();
	Object_wx_PageSetupDialogData *pThis = Object_wx_PageSetupDialogData::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxPoint *pt = Object_wx_Point::GetObject(arg, 0)->GetEntity();
	pThis->GetEntity()->SetMarginTopLeft(*pt);
	return Value::Nil;
}

Gura_DeclareMethod(wx_PageSetupDialogData, SetMarginBottomRight)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "pt", VTYPE_wx_Point, OCCUR_Once);
}

Gura_ImplementMethod(wx_PageSetupDialogData, SetMarginBottomRight)
{
	Signal &sig = env.GetSignal();
	Object_wx_PageSetupDialogData *pThis = Object_wx_PageSetupDialogData::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxPoint *pt = Object_wx_Point::GetObject(arg, 0)->GetEntity();
	pThis->GetEntity()->SetMarginBottomRight(*pt);
	return Value::Nil;
}

Gura_DeclareMethod(wx_PageSetupDialogData, SetMinMarginTopLeft)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "pt", VTYPE_wx_Point, OCCUR_Once);
}

Gura_ImplementMethod(wx_PageSetupDialogData, SetMinMarginTopLeft)
{
	Signal &sig = env.GetSignal();
	Object_wx_PageSetupDialogData *pThis = Object_wx_PageSetupDialogData::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxPoint *pt = Object_wx_Point::GetObject(arg, 0)->GetEntity();
	pThis->GetEntity()->SetMinMarginTopLeft(*pt);
	return Value::Nil;
}

Gura_DeclareMethod(wx_PageSetupDialogData, SetMinMarginBottomRight)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "pt", VTYPE_wx_Point, OCCUR_Once);
}

Gura_ImplementMethod(wx_PageSetupDialogData, SetMinMarginBottomRight)
{
	Signal &sig = env.GetSignal();
	Object_wx_PageSetupDialogData *pThis = Object_wx_PageSetupDialogData::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxPoint *pt = Object_wx_Point::GetObject(arg, 0)->GetEntity();
	pThis->GetEntity()->SetMinMarginBottomRight(*pt);
	return Value::Nil;
}

Gura_DeclareMethod(wx_PageSetupDialogData, SetPaperId)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "id", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_PageSetupDialogData, SetPaperId)
{
	Signal &sig = env.GetSignal();
	Object_wx_PageSetupDialogData *pThis = Object_wx_PageSetupDialogData::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxPaperSize id = static_cast<wxPaperSize>(arg.GetInt(0));
	pThis->GetEntity()->SetPaperId(id);
	return Value::Nil;
}

Gura_DeclareMethod(wx_PageSetupDialogData, SetPaperSize)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "size", VTYPE_wx_Size, OCCUR_Once);
}

Gura_ImplementMethod(wx_PageSetupDialogData, SetPaperSize)
{
	Signal &sig = env.GetSignal();
	Object_wx_PageSetupDialogData *pThis = Object_wx_PageSetupDialogData::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxSize *size = Object_wx_Size::GetObject(arg, 0)->GetEntity();
	pThis->GetEntity()->SetPaperSize(*size);
	return Value::Nil;
}

Gura_DeclareMethod(wx_PageSetupDialogData, SetPrintData)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "printData", VTYPE_wx_PrintData, OCCUR_Once);
}

Gura_ImplementMethod(wx_PageSetupDialogData, SetPrintData)
{
	Signal &sig = env.GetSignal();
	Object_wx_PageSetupDialogData *pThis = Object_wx_PageSetupDialogData::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxPrintData *printData = Object_wx_PrintData::GetObject(arg, 0)->GetEntity();
	pThis->GetEntity()->SetPrintData(*printData);
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Object implementation for wxPageSetupDialogData
//----------------------------------------------------------------------------
Object_wx_PageSetupDialogData::~Object_wx_PageSetupDialogData()
{
}

Object *Object_wx_PageSetupDialogData::Clone() const
{
	return nullptr;
}

String Object_wx_PageSetupDialogData::ToString(bool exprFlag)
{
	String rtn("<wx.PageSetupDialogData:");
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
// Class implementation for wxPageSetupDialogData
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_PageSetupDialogData)
{
	Gura_AssignFunction(PageSetupDialogDataEmpty);
	Gura_AssignFunction(PageSetupDialogData);
	Gura_AssignFunction(PageSetupDialogData_1);
	Gura_AssignMethod(wx_PageSetupDialogData, EnableHelp);
	Gura_AssignMethod(wx_PageSetupDialogData, EnableMargins);
	Gura_AssignMethod(wx_PageSetupDialogData, EnableOrientation);
	Gura_AssignMethod(wx_PageSetupDialogData, EnablePaper);
	Gura_AssignMethod(wx_PageSetupDialogData, EnablePrinter);
	Gura_AssignMethod(wx_PageSetupDialogData, GetDefaultMinMargins);
	Gura_AssignMethod(wx_PageSetupDialogData, GetEnableMargins);
	Gura_AssignMethod(wx_PageSetupDialogData, GetEnableOrientation);
	Gura_AssignMethod(wx_PageSetupDialogData, GetEnablePaper);
	Gura_AssignMethod(wx_PageSetupDialogData, GetEnablePrinter);
	Gura_AssignMethod(wx_PageSetupDialogData, GetEnableHelp);
	Gura_AssignMethod(wx_PageSetupDialogData, GetDefaultInfo);
	Gura_AssignMethod(wx_PageSetupDialogData, GetMarginTopLeft);
	Gura_AssignMethod(wx_PageSetupDialogData, GetMarginBottomRight);
	Gura_AssignMethod(wx_PageSetupDialogData, GetMinMarginTopLeft);
	Gura_AssignMethod(wx_PageSetupDialogData, GetMinMarginBottomRight);
	Gura_AssignMethod(wx_PageSetupDialogData, GetPaperId);
	Gura_AssignMethod(wx_PageSetupDialogData, GetPaperSize);
	Gura_AssignMethod(wx_PageSetupDialogData, GetPrintData);
	Gura_AssignMethod(wx_PageSetupDialogData, IsOk);
	Gura_AssignMethod(wx_PageSetupDialogData, SetDefaultInfo);
	Gura_AssignMethod(wx_PageSetupDialogData, SetDefaultMinMargins);
	Gura_AssignMethod(wx_PageSetupDialogData, SetMarginTopLeft);
	Gura_AssignMethod(wx_PageSetupDialogData, SetMarginBottomRight);
	Gura_AssignMethod(wx_PageSetupDialogData, SetMinMarginTopLeft);
	Gura_AssignMethod(wx_PageSetupDialogData, SetMinMarginBottomRight);
	Gura_AssignMethod(wx_PageSetupDialogData, SetPaperId);
	Gura_AssignMethod(wx_PageSetupDialogData, SetPaperSize);
	Gura_AssignMethod(wx_PageSetupDialogData, SetPrintData);
}

Gura_ImplementDescendantCreator(wx_PageSetupDialogData)
{
	return new Object_wx_PageSetupDialogData((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
