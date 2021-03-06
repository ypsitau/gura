//----------------------------------------------------------------------------
// wxDataViewListModel
// extracted from dataviewmodel.tex
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

Gura_DeclarePrivUserSymbol(GetColType);
Gura_DeclarePrivUserSymbol(GetNumberOfCols);
Gura_DeclarePrivUserSymbol(GetNumberOfRows);
Gura_DeclarePrivUserSymbol(GetValue);
Gura_DeclarePrivUserSymbol(RowAppended);
Gura_DeclarePrivUserSymbol(RowChanged);
Gura_DeclarePrivUserSymbol(RowDeleted);
Gura_DeclarePrivUserSymbol(RowInserted);
Gura_DeclarePrivUserSymbol(RowPrepended);
Gura_DeclarePrivUserSymbol(RowsReordered);
Gura_DeclarePrivUserSymbol(SetValue);
Gura_DeclarePrivUserSymbol(ValueChanged);

//----------------------------------------------------------------------------
// Class derivation
//----------------------------------------------------------------------------
class wx_DataViewListModel: public wxDataViewListModel, public GuraObjectObserver {
private:
	//Gura::Signal *_pSig;
	Object_wx_DataViewListModel *_pObj;
public:
	inline wx_DataViewListModel() : wxDataViewListModel(), _pObj(nullptr) {}
	virtual wxString GetColType(unsigned int col);
	virtual unsigned int GetNumberOfCols();
	virtual unsigned int GetNumberOfRows();
	virtual void GetValue(wxVariant& variant, unsigned int col, unsigned int row);
	virtual bool RowAppended();
	virtual bool RowChanged(unsigned int row);
	virtual bool RowDeleted(unsigned int row);
	virtual bool RowInserted(unsigned int before);
	virtual bool RowPrepended();
	virtual bool RowsReordered(unsigned int* new_order);
	virtual bool SetValue(wxVariant& variant, unsigned int col, unsigned int row);
	virtual bool ValueChanged(unsigned int col, unsigned int row);
	~wx_DataViewListModel();
	inline void AssocWithGura(Object_wx_DataViewListModel *pObj) {
		_pObj = pObj;
	}
	// virtual function of GuraObjectObserver
	virtual void GuraObjectDeleted();
};

wx_DataViewListModel::~wx_DataViewListModel()
{
	if (_pObj != nullptr) _pObj->InvalidateEntity();
}

void wx_DataViewListModel::GuraObjectDeleted()
{
	_pObj = nullptr;
}

// pure virtual function
wxString wx_DataViewListModel::GetColType(unsigned int col)
{
	const Function *pFunc = Gura_LookupWxMethod(_pObj, GetColType);
	if (pFunc == nullptr) {
		_pObj->GetSignal().SetError(ERR_NotImplementedError, "wx.DataViewListModel#GetColType method is missing");
		wxDynamicCast(wxApp::GetInstance(), wxApp)->ExitMainLoop();
		return wxEmptyString;
	}
	ValueList valListArg;
	valListArg.reserve(1);
	valListArg.push_back(Value(col));
	Value rtn = _pObj->EvalMethod(*_pObj, pFunc, valListArg);
	if (!CheckMethodResult(_pObj->GetSignal(), rtn, VTYPE_string)) return wxEmptyString;
	return wxString::FromUTF8(rtn.GetString());
}

// pure virtual function
unsigned int wx_DataViewListModel::GetNumberOfCols()
{
	const Function *pFunc = Gura_LookupWxMethod(_pObj, GetNumberOfCols);
	if (pFunc == nullptr) {
		_pObj->GetSignal().SetError(ERR_NotImplementedError, "wx.DataViewListModel#GetNumberOfCols method is missing");
		wxDynamicCast(wxApp::GetInstance(), wxApp)->ExitMainLoop();
		return 0;
	}
	Value rtn = _pObj->EvalMethod(*_pObj, pFunc, ValueList::Empty);
	if (!CheckMethodResult(_pObj->GetSignal(), rtn, VTYPE_number)) return 0;
	return rtn.GetUInt();
}

// pure virtual function
unsigned int wx_DataViewListModel::GetNumberOfRows()
{
	const Function *pFunc = Gura_LookupWxMethod(_pObj, GetNumberOfRows);
	if (pFunc == nullptr) {
		_pObj->GetSignal().SetError(ERR_NotImplementedError, "wx.DataViewListModel#GetNumberOfRows method is missing");
		wxDynamicCast(wxApp::GetInstance(), wxApp)->ExitMainLoop();
		return 0;
	}
	Value rtn = _pObj->EvalMethod(*_pObj, pFunc, ValueList::Empty);
	if (!CheckMethodResult(_pObj->GetSignal(), rtn, VTYPE_number)) return 0;
	return rtn.GetUInt();
}

// pure virtual function
void wx_DataViewListModel::GetValue(wxVariant& variant, unsigned int col, unsigned int row)
{
	const Function *pFunc = Gura_LookupWxMethod(_pObj, GetValue);
	if (pFunc == nullptr) {
		_pObj->GetSignal().SetError(ERR_NotImplementedError, "wx.DataViewListModel#GetValue method is missing");
		wxDynamicCast(wxApp::GetInstance(), wxApp)->ExitMainLoop();
		return;
	}
	ValueList valListArg;
	valListArg.reserve(2);
	valListArg.push_back(Value(col));
	valListArg.push_back(Value(row));
	Value rtn = _pObj->EvalMethod(*_pObj, pFunc, valListArg);
	if (!CheckMethodResult(_pObj->GetSignal(), rtn, VTYPE_wx_Variant)) return;
	variant = *Object_wx_Variant::GetObject(rtn)->GetEntity();
}

bool wx_DataViewListModel::RowAppended()
{
	const Function *pFunc = Gura_LookupWxMethod(_pObj, RowAppended);
	if (pFunc == nullptr) return wxDataViewListModel::RowAppended();
	Value rtn = _pObj->EvalMethod(*_pObj, pFunc, ValueList::Empty);
	if (!CheckMethodResult(_pObj->GetSignal(), rtn, VTYPE_boolean)) return false;
	return rtn.GetBoolean();
}

bool wx_DataViewListModel::RowChanged(unsigned int row)
{
	const Function *pFunc = Gura_LookupWxMethod(_pObj, RowChanged);
	if (pFunc == nullptr) return wxDataViewListModel::RowChanged(row);
	ValueList valListArg;
	valListArg.reserve(1);
	valListArg.push_back(Value(row));
	Value rtn = _pObj->EvalMethod(*_pObj, pFunc, valListArg);
	if (!CheckMethodResult(_pObj->GetSignal(), rtn, VTYPE_boolean)) return false;
	return rtn.GetBoolean();
}

bool wx_DataViewListModel::RowDeleted(unsigned int row)
{
	const Function *pFunc = Gura_LookupWxMethod(_pObj, RowDeleted);
	if (pFunc == nullptr) return wxDataViewListModel::RowDeleted(row);
	ValueList valListArg;
	valListArg.reserve(1);
	valListArg.push_back(Value(row));
	Value rtn = _pObj->EvalMethod(*_pObj, pFunc, valListArg);
	if (!CheckMethodResult(_pObj->GetSignal(), rtn, VTYPE_boolean)) return false;
	return rtn.GetBoolean();
}

bool wx_DataViewListModel::RowInserted(unsigned int before)
{
	const Function *pFunc = Gura_LookupWxMethod(_pObj, RowInserted);
	if (pFunc == nullptr) return wxDataViewListModel::RowInserted(before);
	ValueList valListArg;
	valListArg.reserve(1);
	valListArg.push_back(Value(before));
	Value rtn = _pObj->EvalMethod(*_pObj, pFunc, valListArg);
	if (!CheckMethodResult(_pObj->GetSignal(), rtn, VTYPE_boolean)) return false;
	return rtn.GetBoolean();
}

bool wx_DataViewListModel::RowPrepended()
{
	const Function *pFunc = Gura_LookupWxMethod(_pObj, RowPrepended);
	if (pFunc == nullptr) return wxDataViewListModel::RowPrepended();
	Value rtn = _pObj->EvalMethod(*_pObj, pFunc, ValueList::Empty);
	if (!CheckMethodResult(_pObj->GetSignal(), rtn, VTYPE_boolean)) return false;
	return rtn.GetBoolean();
}

bool wx_DataViewListModel::RowsReordered(unsigned int* new_order)
{
	Environment &env = *_pObj;
	const Function *pFunc = Gura_LookupWxMethod(_pObj, RowsReordered);
	if (pFunc == nullptr) return wxDataViewListModel::RowsReordered(new_order);
	size_t nRows = GetNumberOfRows();
	if (_pObj->GeSignal().IsSignalled()) return false;
	Value v;
	do {
		Object_list *pObjList = v.InitAsList(env);
		pObjList->Reserve(nRows);
		for (size_t iRow = 0; iRow < nRows; iRow++) pObjList->Add(Value(new_order[iRow]));
	} while (0);
	ValueList valListArg;
	valListArg.reserve(1);
	valListArg.push_back(v);
	Value rtn = _pObj->EvalMethod(*_pObj, pFunc, valListArg);
	if (!CheckMethodResult(_pObj->GetSignal(), rtn, VTYPE_boolean)) return false;
	return rtn.GetBoolean();
}

// pure virtual function
bool wx_DataViewListModel::SetValue(wxVariant& variant, unsigned int col, unsigned int row)
{
	const Function *pFunc = Gura_LookupWxMethod(_pObj, SetValue);
	if (pFunc == nullptr) {
		_pObj->GetSignal().SetError(ERR_NotImplementedError, "wx.DataViewListModel#SetValue method is missing");
		wxDynamicCast(wxApp::GetInstance(), wxApp)->ExitMainLoop();
		return false;
	}
	ValueList valListArg;
	valListArg.reserve(3);
	valListArg.push_back(Value(new Object_wx_Variant(new wxVariant(variant), nullptr, OwnerTrue)));
	valListArg.push_back(Value(col));
	valListArg.push_back(Value(row));
	Value rtn = _pObj->EvalMethod(*_pObj, pFunc, valListArg);
	if (!CheckMethodResult(_pObj->GetSignal(), rtn, VTYPE_boolean)) return false;
	return rtn.GetBoolean();
}

bool wx_DataViewListModel::ValueChanged(unsigned int col, unsigned int row)
{
	const Function *pFunc = Gura_LookupWxMethod(_pObj, ValueChanged);
	if (pFunc == nullptr) return wxDataViewListModel::ValueChanged(col, row);
	ValueList valListArg;
	valListArg.reserve(2);
	valListArg.push_back(Value(col));
	valListArg.push_back(Value(row));
	Value rtn = _pObj->EvalMethod(*_pObj, pFunc, valListArg);
	if (!CheckMethodResult(_pObj->GetSignal(), rtn, VTYPE_boolean)) return false;
	return rtn.GetBoolean();
}

//----------------------------------------------------------------------------
// Gura interfaces for wxDataViewListModel
//----------------------------------------------------------------------------
Gura_DeclareFunction(DataViewListModel)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	SetClassToConstruct(Gura_UserClass(wx_DataViewListModel));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(DataViewListModel)
{
	Signal &sig = env.GetSignal();
	if (!CheckWxReady(sig)) return Value::Nil;
	wx_DataViewListModel *pEntity = new wx_DataViewListModel();
	Object_wx_DataViewListModel *pObj = Object_wx_DataViewListModel::GetObjectThis(arg);
	if (pObj == nullptr) {
		pObj = new Object_wx_DataViewListModel(pEntity, pEntity, OwnerFalse);
		pEntity->AssocWithGura(pObj);
		return ReturnValue(env, arg, Value(pObj));
	}
	pObj->SetEntity(pEntity, pEntity, OwnerFalse);
	pEntity->AssocWithGura(pObj);
	return ReturnValue(env, arg, arg.GetValueThis());
}

Gura_DeclareMethod(wx_DataViewListModel, AddNotifier)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "notifier", VTYPE_wx_DataViewListModelNotifier, OCCUR_Once);
}

Gura_ImplementMethod(wx_DataViewListModel, AddNotifier)
{
	Signal &sig = env.GetSignal();
	Object_wx_DataViewListModel *pThis = Object_wx_DataViewListModel::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxDataViewListModelNotifier *notifier = Object_wx_DataViewListModelNotifier::GetObject(arg, 0)->GetEntity();
	pThis->GetEntity()->AddNotifier(notifier);
	return Value::Nil;
}

Gura_DeclareMethod(wx_DataViewListModel, AddViewingColumn)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "view_column", VTYPE_wx_DataViewColumn, OCCUR_Once);
	DeclareArg(env, "model_column", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_DataViewListModel, AddViewingColumn)
{
	Signal &sig = env.GetSignal();
	Object_wx_DataViewListModel *pThis = Object_wx_DataViewListModel::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxDataViewColumn *view_column = Object_wx_DataViewColumn::GetObject(arg, 0)->GetEntity();
	unsigned model_column = arg.GetInt(1);
	pThis->GetEntity()->AddViewingColumn(view_column, model_column);
	return Value::Nil;
}

Gura_DeclareMethod(wx_DataViewListModel, Cleared)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_DataViewListModel, Cleared)
{
	Signal &sig = env.GetSignal();
	Object_wx_DataViewListModel *pThis = Object_wx_DataViewListModel::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	bool rtn = pThis->GetEntity()->Cleared();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_DataViewListModel, RemoveNotifier)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "notifier", VTYPE_wx_DataViewListModelNotifier, OCCUR_Once);
}

Gura_ImplementMethod(wx_DataViewListModel, RemoveNotifier)
{
	Signal &sig = env.GetSignal();
	Object_wx_DataViewListModel *pThis = Object_wx_DataViewListModel::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxDataViewListModelNotifier *notifier = Object_wx_DataViewListModelNotifier::GetObject(arg, 0)->GetEntity();
	pThis->GetEntity()->RemoveNotifier(notifier);
	return Value::Nil;
}

Gura_DeclareMethod(wx_DataViewListModel, RemoveViewingColumn)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "column", VTYPE_wx_DataViewColumn, OCCUR_Once);
}

Gura_ImplementMethod(wx_DataViewListModel, RemoveViewingColumn)
{
	Signal &sig = env.GetSignal();
	Object_wx_DataViewListModel *pThis = Object_wx_DataViewListModel::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxDataViewColumn *column = Object_wx_DataViewColumn::GetObject(arg, 0)->GetEntity();
	pThis->GetEntity()->RemoveViewingColumn(column);
	return Value::Nil;
}

Gura_DeclareMethod(wx_DataViewListModel, RowAppended)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_DataViewListModel, RowAppended)
{
	Signal &sig = env.GetSignal();
	Object_wx_DataViewListModel *pThis = Object_wx_DataViewListModel::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	bool rtn = pThis->GetEntity()->wxDataViewListModel::RowAppended();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_DataViewListModel, RowChanged)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "row", VTYPE_number, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_DataViewListModel, RowChanged)
{
	Signal &sig = env.GetSignal();
	Object_wx_DataViewListModel *pThis = Object_wx_DataViewListModel::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	unsigned row = arg.GetInt(0);
	bool rtn = pThis->GetEntity()->wxDataViewListModel::RowChanged(row);
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_DataViewListModel, RowDeleted)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "row", VTYPE_number, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_DataViewListModel, RowDeleted)
{
	Signal &sig = env.GetSignal();
	Object_wx_DataViewListModel *pThis = Object_wx_DataViewListModel::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	unsigned row = arg.GetInt(0);
	bool rtn = pThis->GetEntity()->wxDataViewListModel::RowDeleted(row);
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_DataViewListModel, RowInserted)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "before", VTYPE_number, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_DataViewListModel, RowInserted)
{
	Signal &sig = env.GetSignal();
	Object_wx_DataViewListModel *pThis = Object_wx_DataViewListModel::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	unsigned before = arg.GetInt(0);
	bool rtn = pThis->GetEntity()->wxDataViewListModel::RowInserted(before);
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_DataViewListModel, RowPrepended)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_DataViewListModel, RowPrepended)
{
	Signal &sig = env.GetSignal();
	Object_wx_DataViewListModel *pThis = Object_wx_DataViewListModel::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	bool rtn = pThis->GetEntity()->wxDataViewListModel::RowPrepended();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_DataViewListModel, RowsReordered)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "new_order", VTYPE_number, OCCUR_Once, FLAG_ListVar);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_DataViewListModel, RowsReordered)
{
	Signal &sig = env.GetSignal();
	Object_wx_DataViewListModel *pThis = Object_wx_DataViewListModel::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	CArrayOfInt new_order(arg.GetList(0));
	bool rtn = pThis->GetEntity()->wxDataViewListModel::RowsReordered(
					reinterpret_cast<unsigned int *>(new_order.Data()));
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_DataViewListModel, ValueChanged)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "col", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "row", VTYPE_number, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_DataViewListModel, ValueChanged)
{
	Signal &sig = env.GetSignal();
	Object_wx_DataViewListModel *pThis = Object_wx_DataViewListModel::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	unsigned col = arg.GetInt(0);
	unsigned row = arg.GetInt(1);
	bool rtn = pThis->GetEntity()->wxDataViewListModel::ValueChanged(col, row);
	return ReturnValue(env, arg, Value(rtn));
}

//----------------------------------------------------------------------------
// Object implementation for wxDataViewListModel
//----------------------------------------------------------------------------
Object_wx_DataViewListModel::~Object_wx_DataViewListModel()
{
}

Object *Object_wx_DataViewListModel::Clone() const
{
	return nullptr;
}

String Object_wx_DataViewListModel::ToString(bool exprFlag)
{
	String rtn("<wx.DataViewListModel:");
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
// Class implementation for wxDataViewListModel
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_DataViewListModel)
{
	Gura_RealizeUserSymbol(GetColType);
	Gura_RealizeUserSymbol(GetNumberOfCols);
	Gura_RealizeUserSymbol(GetNumberOfRows);
	Gura_RealizeUserSymbol(GetValue);
	Gura_RealizeUserSymbol(RowAppended);
	Gura_RealizeUserSymbol(RowChanged);
	Gura_RealizeUserSymbol(RowDeleted);
	Gura_RealizeUserSymbol(RowInserted);
	Gura_RealizeUserSymbol(RowPrepended);
	Gura_RealizeUserSymbol(RowsReordered);
	Gura_RealizeUserSymbol(SetValue);
	Gura_RealizeUserSymbol(ValueChanged);
	Gura_AssignFunction(DataViewListModel);
	Gura_AssignMethod(wx_DataViewListModel, AddNotifier);
	Gura_AssignMethod(wx_DataViewListModel, AddViewingColumn);
	Gura_AssignMethod(wx_DataViewListModel, Cleared);
	Gura_AssignMethod(wx_DataViewListModel, RemoveNotifier);
	Gura_AssignMethod(wx_DataViewListModel, RemoveViewingColumn);
	Gura_AssignMethod(wx_DataViewListModel, RowAppended);
	Gura_AssignMethod(wx_DataViewListModel, RowChanged);
	Gura_AssignMethod(wx_DataViewListModel, RowDeleted);
	Gura_AssignMethod(wx_DataViewListModel, RowInserted);
	Gura_AssignMethod(wx_DataViewListModel, RowPrepended);
	Gura_AssignMethod(wx_DataViewListModel, RowsReordered);
	Gura_AssignMethod(wx_DataViewListModel, ValueChanged);
}

Gura_ImplementDescendantCreator(wx_DataViewListModel)
{
	return new Object_wx_DataViewListModel((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
