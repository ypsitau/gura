//----------------------------------------------------------------------------
// wxTreeCtrl
// extracted from treectrl.tex
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

Gura_DeclarePrivUserSymbol(OnCompareItems);

//----------------------------------------------------------------------------
// Class derivation
//----------------------------------------------------------------------------
class wx_TreeCtrl: public wxTreeCtrl, public GuraObjectObserver {
private:
	DECLARE_DYNAMIC_CLASS(wx_TreeCtrl)
	//Gura::Signal *_pSig;
	AutoPtr<Object_wx_TreeCtrl> _pObj;
public:
	inline wx_TreeCtrl() : wxTreeCtrl(), _pObj(nullptr) {}
	inline wx_TreeCtrl(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxValidator& validator, const wxString& name) : wxTreeCtrl(parent, id, pos, size, style, validator, name), _pObj(nullptr) {}
	//inline wx_TreeCtrl(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxValidator& validator, const wxString& name) : wxTreeCtrl(parent, id, pos, size, style, validator, name), _pObj(nullptr) {}
	~wx_TreeCtrl();
	inline void AssocWithGura(Object_wx_TreeCtrl *pObj) {
		_pObj.reset(Object_wx_TreeCtrl::Reference(pObj));
	}
	virtual int OnCompareItems(const wxTreeItemId& item1, const wxTreeItemId& item2);
	// virtual function of GuraObjectObserver
	virtual void GuraObjectDeleted();
};

IMPLEMENT_DYNAMIC_CLASS(wx_TreeCtrl, wxTreeCtrl)

wx_TreeCtrl::~wx_TreeCtrl()
{
}

void wx_TreeCtrl::GuraObjectDeleted()
{
}

int wx_TreeCtrl::OnCompareItems(const wxTreeItemId& item1, const wxTreeItemId& item2)
{
	const Function *pFunc = Gura_LookupWxMethod(_pObj, OnCompareItems);
	if (pFunc == nullptr) return wxTreeCtrl::OnCompareItems(item1, item2);
	ValueList valList;
	valList.reserve(2);
	valList.push_back(Value(new Object_wx_TreeItemId(new wxTreeItemId(item1), nullptr, OwnerTrue)));
	valList.push_back(Value(new Object_wx_TreeItemId(new wxTreeItemId(item2), nullptr, OwnerTrue)));
	Value rtn = _pObj->EvalMethod(*_pObj, pFunc, valList);
	if (!CheckMethodResult(_pObj->GetSignal(), rtn, VTYPE_number)) return 0;
	return rtn.GetInt();
}

//-----------------------------------------------------------------------------
// Iterator_TreeCtrl_ItemChildren
//-----------------------------------------------------------------------------
class Iterator_TreeCtrl_ItemChildren : public Iterator {
private:
	AutoPtr<Object_wx_TreeCtrl> _pObj;
	wxTreeItemId _item;
	wxTreeItemId _itemChild;
	wxTreeItemIdValue _cookie;
public:
	inline Iterator_TreeCtrl_ItemChildren(Object_wx_TreeCtrl *pObj,
			wxTreeItemId item, wxTreeItemId itemChild, wxTreeItemIdValue cookie) :
		Iterator(Finite), _pObj(pObj),
		_item(item), _itemChild(itemChild), _cookie(cookie) {}
	virtual Iterator *GetSource();
	virtual bool DoNext(Environment &env, Value &value);
	virtual String ToString() const;
	virtual void GatherFollower(Environment::Frame *pFrame, EnvironmentSet &envSet);
};

Iterator *Iterator_TreeCtrl_ItemChildren::GetSource()
{
	return nullptr;
}

bool Iterator_TreeCtrl_ItemChildren::DoNext(Environment &env, Value &value)
{
	Signal &sig = env.GetSignal();
	if (_pObj->IsInvalid(sig)) return false;
	if (!_item.IsOk() || !_itemChild.IsOk()) return false;
	value = Value(new Object_wx_TreeItemId(new wxTreeItemId(_itemChild), nullptr, true));
	_itemChild = _pObj->GetEntity()->GetNextChild(_item, _cookie);
	return true;
}

String Iterator_TreeCtrl_ItemChildren::ToString() const
{
	String str;
	str = "<iterator:wx.TreeCtrl.ItemChildren>";
	return str;
}

void Iterator_TreeCtrl_ItemChildren::GatherFollower(Environment::Frame *pFrame, EnvironmentSet &envSet)
{
}

//----------------------------------------------------------------------------
// Gura interfaces for wxTreeCtrl
//----------------------------------------------------------------------------
Gura_DeclareFunction(TreeCtrlEmpty)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	SetClassToConstruct(Gura_UserClass(wx_TreeCtrl));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(TreeCtrlEmpty)
{
	Signal &sig = env.GetSignal();
	if (!CheckWxReady(sig)) return Value::Nil;
	wx_TreeCtrl *pEntity = new wx_TreeCtrl();
	Object_wx_TreeCtrl *pObj = Object_wx_TreeCtrl::GetObjectThis(arg);
	if (pObj == nullptr) {
		pObj = new Object_wx_TreeCtrl(pEntity, pEntity, OwnerFalse);
		pEntity->AssocWithGura(pObj);
		return ReturnValue(env, arg, Value(pObj));
	}
	pObj->SetEntity(pEntity, pEntity, OwnerFalse);
	pEntity->AssocWithGura(pObj);
	return ReturnValue(env, arg, arg.GetValueThis());
}

Gura_DeclareFunction(TreeCtrl)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	SetClassToConstruct(Gura_UserClass(wx_TreeCtrl));
	DeclareArg(env, "parent", VTYPE_wx_Window, OCCUR_Once);
	DeclareArg(env, "id", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "pos", VTYPE_wx_Point, OCCUR_ZeroOrOnce);
	DeclareArg(env, "size", VTYPE_wx_Size, OCCUR_ZeroOrOnce);
	DeclareArg(env, "style", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareArg(env, "validator", VTYPE_wx_Validator, OCCUR_ZeroOrOnce);
	DeclareArg(env, "name", VTYPE_string, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(TreeCtrl)
{
	Signal &sig = env.GetSignal();
	if (!CheckWxReady(sig)) return Value::Nil;
	wxWindow *parent = Object_wx_Window::GetObject(arg, 0)->GetEntity();
	wxWindowID id = static_cast<wxWindowID>(arg.GetInt(1));
	wxPoint *pos = (wxPoint *)(&wxDefaultPosition);
	if (arg.IsValid(2)) pos = Object_wx_Point::GetObject(arg, 2)->GetEntity();
	wxSize *size = (wxSize *)(&wxDefaultSize);
	if (arg.IsValid(3)) size = Object_wx_Size::GetObject(arg, 3)->GetEntity();
	long style = wxTR_HAS_BUTTONS;
	if (arg.IsValid(4)) style = arg.GetLong(4);
	wxValidator *validator = (wxValidator *)(&wxDefaultValidator);
	if (arg.IsValid(5)) validator = Object_wx_Validator::GetObject(arg, 5)->GetEntity();
	wxString name = wxT("treeCtrl");
	if (arg.IsValid(6)) name = wxString::FromUTF8(arg.GetString(6));
	wx_TreeCtrl *pEntity = new wx_TreeCtrl(parent, id, *pos, *size, style, *validator, name);
	Object_wx_TreeCtrl *pObj = Object_wx_TreeCtrl::GetObjectThis(arg);
	if (pObj == nullptr) {
		pObj = new Object_wx_TreeCtrl(pEntity, pEntity, OwnerFalse);
		pEntity->AssocWithGura(pObj);
		return ReturnValue(env, arg, Value(pObj));
	}
	pObj->SetEntity(pEntity, pEntity, OwnerFalse);
	pEntity->AssocWithGura(pObj);
	return ReturnValue(env, arg, arg.GetValueThis());
}

Gura_DeclareMethod(wx_TreeCtrl, AddRoot)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "text", VTYPE_string, OCCUR_Once);
	DeclareArg(env, "image", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareArg(env, "selImage", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareArg(env, "data", VTYPE_wx_TreeItemData, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_TreeCtrl, AddRoot)
{
	Signal &sig = env.GetSignal();
	Object_wx_TreeCtrl *pThis = Object_wx_TreeCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxString text = wxString::FromUTF8(arg.GetString(0));
	int image = -1;
	if (arg.IsValid(1)) image = arg.GetInt(1);
	int selImage = -1;
	if (arg.IsValid(2)) selImage = arg.GetInt(2);
	wxTreeItemData *data = (wxTreeItemData *)(nullptr);
	if (arg.IsValid(3)) data = new wx_TreeItemData(*Object_wx_TreeItemData::GetObject(arg, 3)->GetEntity());
	wxTreeItemId rtn = pThis->GetEntity()->AddRoot(text, image, selImage, data);
	return ReturnValue(env, arg, Value(new Object_wx_TreeItemId(new wxTreeItemId(rtn), nullptr, OwnerTrue)));
}

Gura_DeclareMethod(wx_TreeCtrl, AppendItem)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "parent", VTYPE_wx_TreeItemId, OCCUR_Once);
	DeclareArg(env, "text", VTYPE_string, OCCUR_Once);
	DeclareArg(env, "image", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareArg(env, "selImage", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareArg(env, "data", VTYPE_wx_TreeItemData, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_TreeCtrl, AppendItem)
{
	Signal &sig = env.GetSignal();
	Object_wx_TreeCtrl *pThis = Object_wx_TreeCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxTreeItemId *parent = Object_wx_TreeItemId::GetObject(arg, 0)->GetEntity();
	wxString text = wxString::FromUTF8(arg.GetString(1));
	int image = -1;
	if (arg.IsValid(2)) image = arg.GetInt(2);
	int selImage = -1;
	if (arg.IsValid(3)) selImage = arg.GetInt(3);
	wxTreeItemData *data = (wxTreeItemData *)(nullptr);
	if (arg.IsValid(4)) data = new wx_TreeItemData(*Object_wx_TreeItemData::GetObject(arg, 4)->GetEntity());
	wxTreeItemId rtn = pThis->GetEntity()->AppendItem(*parent, text, image, selImage, data);
	return ReturnValue(env, arg, Value(new Object_wx_TreeItemId(new wxTreeItemId(rtn), nullptr, OwnerTrue)));
}

Gura_DeclareMethod(wx_TreeCtrl, AssignImageList)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "imageList", VTYPE_wx_ImageList, OCCUR_Once);
}

Gura_ImplementMethod(wx_TreeCtrl, AssignImageList)
{
	Signal &sig = env.GetSignal();
	Object_wx_TreeCtrl *pThis = Object_wx_TreeCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxImageList *imageList = new wxImageList();
	imageList->Ref(*Object_wx_ImageList::GetObject(arg, 0)->GetEntity());
	pThis->GetEntity()->AssignImageList(imageList);
	return Value::Nil;
}

Gura_DeclareMethod(wx_TreeCtrl, AssignStateImageList)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "imageList", VTYPE_wx_ImageList, OCCUR_Once);
}

Gura_ImplementMethod(wx_TreeCtrl, AssignStateImageList)
{
	Signal &sig = env.GetSignal();
	Object_wx_TreeCtrl *pThis = Object_wx_TreeCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxImageList *imageList = new wxImageList();
	imageList->Ref(*Object_wx_ImageList::GetObject(arg, 0)->GetEntity());
	pThis->GetEntity()->AssignStateImageList(imageList);
	return Value::Nil;
}

Gura_DeclareMethod(wx_TreeCtrl, Collapse)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "item", VTYPE_wx_TreeItemId, OCCUR_Once);
}

Gura_ImplementMethod(wx_TreeCtrl, Collapse)
{
	Signal &sig = env.GetSignal();
	Object_wx_TreeCtrl *pThis = Object_wx_TreeCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxTreeItemId *item = Object_wx_TreeItemId::GetObject(arg, 0)->GetEntity();
	pThis->GetEntity()->Collapse(*item);
	return Value::Nil;
}

Gura_DeclareMethod(wx_TreeCtrl, CollapseAll)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_TreeCtrl, CollapseAll)
{
	Signal &sig = env.GetSignal();
	Object_wx_TreeCtrl *pThis = Object_wx_TreeCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	pThis->GetEntity()->CollapseAll();
	return Value::Nil;
}

Gura_DeclareMethod(wx_TreeCtrl, CollapseAllChildren)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "item", VTYPE_wx_TreeItemId, OCCUR_Once);
}

Gura_ImplementMethod(wx_TreeCtrl, CollapseAllChildren)
{
	Signal &sig = env.GetSignal();
	Object_wx_TreeCtrl *pThis = Object_wx_TreeCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxTreeItemId *item = Object_wx_TreeItemId::GetObject(arg, 0)->GetEntity();
	pThis->GetEntity()->CollapseAllChildren(*item);
	return Value::Nil;
}

Gura_DeclareMethod(wx_TreeCtrl, CollapseAndReset)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "item", VTYPE_wx_TreeItemId, OCCUR_Once);
}

Gura_ImplementMethod(wx_TreeCtrl, CollapseAndReset)
{
	Signal &sig = env.GetSignal();
	Object_wx_TreeCtrl *pThis = Object_wx_TreeCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxTreeItemId *item = Object_wx_TreeItemId::GetObject(arg, 0)->GetEntity();
	pThis->GetEntity()->CollapseAndReset(*item);
	return Value::Nil;
}

Gura_DeclareMethod(wx_TreeCtrl, Delete)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "item", VTYPE_wx_TreeItemId, OCCUR_Once);
}

Gura_ImplementMethod(wx_TreeCtrl, Delete)
{
	Signal &sig = env.GetSignal();
	Object_wx_TreeCtrl *pThis = Object_wx_TreeCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxTreeItemId *item = Object_wx_TreeItemId::GetObject(arg, 0)->GetEntity();
	pThis->GetEntity()->Delete(*item);
	return Value::Nil;
}

Gura_DeclareMethod(wx_TreeCtrl, DeleteAllItems)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_TreeCtrl, DeleteAllItems)
{
	Signal &sig = env.GetSignal();
	Object_wx_TreeCtrl *pThis = Object_wx_TreeCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	pThis->GetEntity()->DeleteAllItems();
	return Value::Nil;
}

Gura_DeclareMethod(wx_TreeCtrl, DeleteChildren)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "item", VTYPE_wx_TreeItemId, OCCUR_Once);
}

Gura_ImplementMethod(wx_TreeCtrl, DeleteChildren)
{
	Signal &sig = env.GetSignal();
	Object_wx_TreeCtrl *pThis = Object_wx_TreeCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxTreeItemId *item = Object_wx_TreeItemId::GetObject(arg, 0)->GetEntity();
	pThis->GetEntity()->DeleteChildren(*item);
	return Value::Nil;
}

Gura_DeclareMethod(wx_TreeCtrl, EditLabel)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "item", VTYPE_wx_TreeItemId, OCCUR_Once);
}

Gura_ImplementMethod(wx_TreeCtrl, EditLabel)
{
	Signal &sig = env.GetSignal();
	Object_wx_TreeCtrl *pThis = Object_wx_TreeCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxTreeItemId *item = Object_wx_TreeItemId::GetObject(arg, 0)->GetEntity();
	pThis->GetEntity()->EditLabel(*item);
	return Value::Nil;
}

Gura_DeclareMethod(wx_TreeCtrl, EndEditLabel)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
#if 0
	DeclareArg(env, "cancelEdit", VTYPE_boolean, OCCUR_Once);
#endif
}

Gura_ImplementMethod(wx_TreeCtrl, EndEditLabel)
{
	Signal &sig = env.GetSignal();
#if 0
	Object_wx_TreeCtrl *pThis = Object_wx_TreeCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	bool cancelEdit = arg.GetBoolean(0);
	pThis->GetEntity()->EndEditLabel(cancelEdit);
	return Value::Nil;
#endif
	SetError_NotImplemented(sig);
	return Value::Nil;
}

Gura_DeclareMethod(wx_TreeCtrl, EnsureVisible)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "item", VTYPE_wx_TreeItemId, OCCUR_Once);
}

Gura_ImplementMethod(wx_TreeCtrl, EnsureVisible)
{
	Signal &sig = env.GetSignal();
	Object_wx_TreeCtrl *pThis = Object_wx_TreeCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxTreeItemId *item = Object_wx_TreeItemId::GetObject(arg, 0)->GetEntity();
	pThis->GetEntity()->EnsureVisible(*item);
	return Value::Nil;
}

Gura_DeclareMethod(wx_TreeCtrl, Expand)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "item", VTYPE_wx_TreeItemId, OCCUR_Once);
}

Gura_ImplementMethod(wx_TreeCtrl, Expand)
{
	Signal &sig = env.GetSignal();
	Object_wx_TreeCtrl *pThis = Object_wx_TreeCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxTreeItemId *item = Object_wx_TreeItemId::GetObject(arg, 0)->GetEntity();
	pThis->GetEntity()->Expand(*item);
	return Value::Nil;
}

Gura_DeclareMethod(wx_TreeCtrl, ExpandAll)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_TreeCtrl, ExpandAll)
{
	Signal &sig = env.GetSignal();
	Object_wx_TreeCtrl *pThis = Object_wx_TreeCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	pThis->GetEntity()->ExpandAll();
	return Value::Nil;
}

Gura_DeclareMethod(wx_TreeCtrl, ExpandAllChildren)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "item", VTYPE_wx_TreeItemId, OCCUR_Once);
}

Gura_ImplementMethod(wx_TreeCtrl, ExpandAllChildren)
{
	Signal &sig = env.GetSignal();
	Object_wx_TreeCtrl *pThis = Object_wx_TreeCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxTreeItemId *item = Object_wx_TreeItemId::GetObject(arg, 0)->GetEntity();
	pThis->GetEntity()->ExpandAllChildren(*item);
	return Value::Nil;
}

Gura_DeclareMethod(wx_TreeCtrl, GetBoundingRect)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "item", VTYPE_wx_TreeItemId, OCCUR_Once);
	DeclareArg(env, "textOnly", VTYPE_boolean, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_TreeCtrl, GetBoundingRect)
{
	Signal &sig = env.GetSignal();
	Object_wx_TreeCtrl *pThis = Object_wx_TreeCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxTreeItemId *item = Object_wx_TreeItemId::GetObject(arg, 0)->GetEntity();
	wxRect rect;
	bool textOnly = false;
	if (arg.IsValid(1)) textOnly = arg.GetBoolean(1);
	bool rtn = pThis->GetEntity()->GetBoundingRect(*item, rect, textOnly);
	Value value;
	if (rtn) {
		value = Value(new Object_wx_Rect(new wxRect(rect), nullptr, OwnerTrue));
	}
	return ReturnValue(env, arg, value);
}

Gura_DeclareMethod(wx_TreeCtrl, GetChildrenCount)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "item", VTYPE_wx_TreeItemId, OCCUR_Once);
	DeclareArg(env, "recursively", VTYPE_boolean, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_TreeCtrl, GetChildrenCount)
{
	Signal &sig = env.GetSignal();
	Object_wx_TreeCtrl *pThis = Object_wx_TreeCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxTreeItemId *item = Object_wx_TreeItemId::GetObject(arg, 0)->GetEntity();
	bool recursively = true;
	if (arg.IsValid(1)) recursively = arg.GetBoolean(1);
	unsigned rtn = pThis->GetEntity()->GetChildrenCount(*item, recursively);
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_TreeCtrl, GetCount)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_TreeCtrl, GetCount)
{
	Signal &sig = env.GetSignal();
	Object_wx_TreeCtrl *pThis = Object_wx_TreeCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	unsigned rtn = pThis->GetEntity()->GetCount();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_TreeCtrl, GetEditControl)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_TreeCtrl, GetEditControl)
{
	Signal &sig = env.GetSignal();
	Object_wx_TreeCtrl *pThis = Object_wx_TreeCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxTextCtrl *rtn = (wxTextCtrl *)pThis->GetEntity()->GetEditControl();
	return ReturnValue(env, arg, Value(new Object_wx_TextCtrl(rtn, nullptr, OwnerFalse)));
}

Gura_DeclareMethod(wx_TreeCtrl, GetFirstChild)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "item", VTYPE_wx_TreeItemId, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_TreeCtrl, GetFirstChild)
{
	Signal &sig = env.GetSignal();
	Object_wx_TreeCtrl *pThis = Object_wx_TreeCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxTreeItemId *item = Object_wx_TreeItemId::GetObject(arg, 0)->GetEntity();
	wxTreeItemIdValue cookie;
	wxTreeItemId rtn = pThis->GetEntity()->GetFirstChild(*item, cookie);
	return ReturnValue(env, arg, Value::CreateList(env,
		Value(new Object_wx_TreeItemId(new wxTreeItemId(rtn), nullptr, OwnerTrue)),
		Value(reinterpret_cast<size_t>(cookie))));
}

Gura_DeclareMethod(wx_TreeCtrl, GetFirstVisibleItem)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_TreeCtrl, GetFirstVisibleItem)
{
	Signal &sig = env.GetSignal();
	Object_wx_TreeCtrl *pThis = Object_wx_TreeCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxTreeItemId rtn = pThis->GetEntity()->GetFirstVisibleItem();
	return ReturnValue(env, arg, Value(new Object_wx_TreeItemId(new wxTreeItemId(rtn), nullptr, OwnerTrue)));
}

Gura_DeclareMethod(wx_TreeCtrl, GetImageList)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_TreeCtrl, GetImageList)
{
	Signal &sig = env.GetSignal();
	Object_wx_TreeCtrl *pThis = Object_wx_TreeCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxImageList *rtn = (wxImageList *)pThis->GetEntity()->GetImageList();
	return ReturnValue(env, arg, Value(new Object_wx_ImageList(rtn, nullptr, OwnerFalse)));
}

Gura_DeclareMethod(wx_TreeCtrl, GetIndent)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_TreeCtrl, GetIndent)
{
	Signal &sig = env.GetSignal();
	Object_wx_TreeCtrl *pThis = Object_wx_TreeCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	int rtn = pThis->GetEntity()->GetIndent();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_TreeCtrl, GetSpacing)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_TreeCtrl, GetSpacing)
{
	Signal &sig = env.GetSignal();
	Object_wx_TreeCtrl *pThis = Object_wx_TreeCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	unsigned int rtn = pThis->GetEntity()->GetSpacing();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_TreeCtrl, GetItemBackgroundColour)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "item", VTYPE_wx_TreeItemId, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_TreeCtrl, GetItemBackgroundColour)
{
	Signal &sig = env.GetSignal();
	Object_wx_TreeCtrl *pThis = Object_wx_TreeCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxTreeItemId *item = Object_wx_TreeItemId::GetObject(arg, 0)->GetEntity();
	wxColour rtn = pThis->GetEntity()->GetItemBackgroundColour(*item);
	return ReturnValue(env, arg, Value(new Object_wx_Colour(new wxColour(rtn), nullptr, OwnerTrue)));
}

Gura_DeclareMethod(wx_TreeCtrl, GetItemData)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "item", VTYPE_wx_TreeItemId, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_TreeCtrl, GetItemData)
{
	Signal &sig = env.GetSignal();
	Object_wx_TreeCtrl *pThis = Object_wx_TreeCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxTreeItemId *item = Object_wx_TreeItemId::GetObject(arg, 0)->GetEntity();
	wx_TreeItemData *rtn = dynamic_cast<wx_TreeItemData *>(pThis->GetEntity()->GetItemData(*item));
	Value value;
	if (rtn != nullptr) value = Value(new Object_wx_TreeItemData(
									new wx_TreeItemData(*rtn), nullptr, OwnerTrue));
	return ReturnValue(env, arg, value);
}

Gura_DeclareMethod(wx_TreeCtrl, GetGuraData)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "item", VTYPE_wx_TreeItemId, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_TreeCtrl, GetGuraData)
{
	Signal &sig = env.GetSignal();
	Object_wx_TreeCtrl *pThis = Object_wx_TreeCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxTreeItemId *item = Object_wx_TreeItemId::GetObject(arg, 0)->GetEntity();
	wx_TreeItemData *rtn = dynamic_cast<wx_TreeItemData *>(pThis->GetEntity()->GetItemData(*item));
	Value result;
	if (rtn != nullptr) result = rtn->GetValue();
	return ReturnValue(env, arg, result);
}

Gura_DeclareMethod(wx_TreeCtrl, GetItemChildren)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "item", VTYPE_wx_TreeItemId, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_TreeCtrl, GetItemChildren)
{
	Signal &sig = env.GetSignal();
	Object_wx_TreeCtrl *pThis = Object_wx_TreeCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxTreeItemId *item = Object_wx_TreeItemId::GetObject(arg, 0)->GetEntity();
	wxTreeItemIdValue cookie;
	wxTreeItemId rtn = pThis->GetEntity()->GetFirstChild(*item, cookie);
	Iterator_TreeCtrl_ItemChildren *pIterator = new Iterator_TreeCtrl_ItemChildren(
		Object_wx_TreeCtrl::Reference(pThis), *item, rtn, cookie);
	return ReturnIterator(env, arg, pIterator);
}

Gura_DeclareMethod(wx_TreeCtrl, GetItemFont)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "item", VTYPE_wx_TreeItemId, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_TreeCtrl, GetItemFont)
{
	Signal &sig = env.GetSignal();
	Object_wx_TreeCtrl *pThis = Object_wx_TreeCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxTreeItemId *item = Object_wx_TreeItemId::GetObject(arg, 0)->GetEntity();
	wxFont rtn = pThis->GetEntity()->GetItemFont(*item);
	return ReturnValue(env, arg, Value(new Object_wx_Font(new wxFont(rtn), nullptr, OwnerTrue)));
}

Gura_DeclareMethod(wx_TreeCtrl, GetItemImage)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "item", VTYPE_wx_TreeItemId, OCCUR_Once);
	DeclareArg(env, "which", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_TreeCtrl, GetItemImage)
{
	Signal &sig = env.GetSignal();
	Object_wx_TreeCtrl *pThis = Object_wx_TreeCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxTreeItemId *item = Object_wx_TreeItemId::GetObject(arg, 0)->GetEntity();
	wxTreeItemIcon which = wxTreeItemIcon_Normal;
	if (arg.IsValid(1)) which = static_cast<wxTreeItemIcon>(arg.GetInt(1));
	int rtn = pThis->GetEntity()->GetItemImage(*item, which);
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_TreeCtrl, GetItemText)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "item", VTYPE_wx_TreeItemId, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_TreeCtrl, GetItemText)
{
	Signal &sig = env.GetSignal();
	Object_wx_TreeCtrl *pThis = Object_wx_TreeCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxTreeItemId *item = Object_wx_TreeItemId::GetObject(arg, 0)->GetEntity();
	wxString rtn = pThis->GetEntity()->GetItemText(*item);
	return ReturnValue(env, arg, Value(static_cast<const char *>(rtn.ToUTF8())));
}

Gura_DeclareMethod(wx_TreeCtrl, GetItemTextColour)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "item", VTYPE_wx_TreeItemId, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_TreeCtrl, GetItemTextColour)
{
	Signal &sig = env.GetSignal();
	Object_wx_TreeCtrl *pThis = Object_wx_TreeCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxTreeItemId *item = Object_wx_TreeItemId::GetObject(arg, 0)->GetEntity();
	wxColour rtn = pThis->GetEntity()->GetItemTextColour(*item);
	return ReturnValue(env, arg, Value(new Object_wx_Colour(new wxColour(rtn), nullptr, OwnerTrue)));
}

Gura_DeclareMethod(wx_TreeCtrl, GetLastChild)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "item", VTYPE_wx_TreeItemId, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_TreeCtrl, GetLastChild)
{
	Signal &sig = env.GetSignal();
	Object_wx_TreeCtrl *pThis = Object_wx_TreeCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxTreeItemId *item = Object_wx_TreeItemId::GetObject(arg, 0)->GetEntity();
	wxTreeItemId rtn = pThis->GetEntity()->GetLastChild(*item);
	return ReturnValue(env, arg, Value(new Object_wx_TreeItemId(new wxTreeItemId(rtn), nullptr, OwnerTrue)));
}

Gura_DeclareMethod(wx_TreeCtrl, GetNextChild)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "item", VTYPE_wx_TreeItemId, OCCUR_Once);
	DeclareArg(env, "cookie", VTYPE_number, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_TreeCtrl, GetNextChild)
{
	Signal &sig = env.GetSignal();
	Object_wx_TreeCtrl *pThis = Object_wx_TreeCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxTreeItemId *item = Object_wx_TreeItemId::GetObject(arg, 0)->GetEntity();
	wxTreeItemIdValue cookie = reinterpret_cast<wxTreeItemIdValue>(arg.GetInt(1));
	wxTreeItemId rtn = pThis->GetEntity()->GetNextChild(*item, cookie);
	return ReturnValue(env, arg, Value::CreateList(env,
		Value(new Object_wx_TreeItemId(new wxTreeItemId(rtn), nullptr, OwnerTrue)),
		Value(reinterpret_cast<size_t>(cookie))));
}

Gura_DeclareMethod(wx_TreeCtrl, GetNextSibling)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "item", VTYPE_wx_TreeItemId, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_TreeCtrl, GetNextSibling)
{
	Signal &sig = env.GetSignal();
	Object_wx_TreeCtrl *pThis = Object_wx_TreeCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxTreeItemId *item = Object_wx_TreeItemId::GetObject(arg, 0)->GetEntity();
	wxTreeItemId rtn = pThis->GetEntity()->GetNextSibling(*item);
	return ReturnValue(env, arg, Value(new Object_wx_TreeItemId(new wxTreeItemId(rtn), nullptr, OwnerTrue)));
}

Gura_DeclareMethod(wx_TreeCtrl, GetNextVisible)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "item", VTYPE_wx_TreeItemId, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_TreeCtrl, GetNextVisible)
{
	Signal &sig = env.GetSignal();
	Object_wx_TreeCtrl *pThis = Object_wx_TreeCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxTreeItemId *item = Object_wx_TreeItemId::GetObject(arg, 0)->GetEntity();
	wxTreeItemId rtn = pThis->GetEntity()->GetNextVisible(*item);
	return ReturnValue(env, arg, Value(new Object_wx_TreeItemId(new wxTreeItemId(rtn), nullptr, OwnerTrue)));
}

Gura_DeclareMethod(wx_TreeCtrl, GetItemParent)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "item", VTYPE_wx_TreeItemId, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_TreeCtrl, GetItemParent)
{
	Signal &sig = env.GetSignal();
	Object_wx_TreeCtrl *pThis = Object_wx_TreeCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxTreeItemId *item = Object_wx_TreeItemId::GetObject(arg, 0)->GetEntity();
	wxTreeItemId rtn = pThis->GetEntity()->GetItemParent(*item);
	return ReturnValue(env, arg, Value(new Object_wx_TreeItemId(new wxTreeItemId(rtn), nullptr, OwnerTrue)));
}

Gura_DeclareMethod(wx_TreeCtrl, GetPrevSibling)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "item", VTYPE_wx_TreeItemId, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_TreeCtrl, GetPrevSibling)
{
	Signal &sig = env.GetSignal();
	Object_wx_TreeCtrl *pThis = Object_wx_TreeCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxTreeItemId *item = Object_wx_TreeItemId::GetObject(arg, 0)->GetEntity();
	wxTreeItemId rtn = pThis->GetEntity()->GetPrevSibling(*item);
	return ReturnValue(env, arg, Value(new Object_wx_TreeItemId(new wxTreeItemId(rtn), nullptr, OwnerTrue)));
}

Gura_DeclareMethod(wx_TreeCtrl, GetPrevVisible)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "item", VTYPE_wx_TreeItemId, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_TreeCtrl, GetPrevVisible)
{
	Signal &sig = env.GetSignal();
	Object_wx_TreeCtrl *pThis = Object_wx_TreeCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxTreeItemId *item = Object_wx_TreeItemId::GetObject(arg, 0)->GetEntity();
	wxTreeItemId rtn = pThis->GetEntity()->GetPrevVisible(*item);
	return ReturnValue(env, arg, Value(new Object_wx_TreeItemId(new wxTreeItemId(rtn), nullptr, OwnerTrue)));
}

Gura_DeclareMethod(wx_TreeCtrl, GetQuickBestSize)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_TreeCtrl, GetQuickBestSize)
{
	Signal &sig = env.GetSignal();
	Object_wx_TreeCtrl *pThis = Object_wx_TreeCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	bool rtn = pThis->GetEntity()->GetQuickBestSize();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_TreeCtrl, GetRootItem)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_TreeCtrl, GetRootItem)
{
	Signal &sig = env.GetSignal();
	Object_wx_TreeCtrl *pThis = Object_wx_TreeCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxTreeItemId rtn = pThis->GetEntity()->GetRootItem();
	return ReturnValue(env, arg, Value(new Object_wx_TreeItemId(new wxTreeItemId(rtn), nullptr, OwnerTrue)));
}

Gura_DeclareMethod(wx_TreeCtrl, GetSelection)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_TreeCtrl, GetSelection)
{
	Signal &sig = env.GetSignal();
	Object_wx_TreeCtrl *pThis = Object_wx_TreeCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxTreeItemId rtn = pThis->GetEntity()->GetSelection();
	return ReturnValue(env, arg, Value(new Object_wx_TreeItemId(new wxTreeItemId(rtn), nullptr, OwnerTrue)));
}

Gura_DeclareMethod(wx_TreeCtrl, GetSelections)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_TreeCtrl, GetSelections)
{
	Signal &sig = env.GetSignal();
	Object_wx_TreeCtrl *pThis = Object_wx_TreeCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxArrayTreeItemIds selection;
	unsigned int rtn = pThis->GetEntity()->GetSelections(selection);
	Value result;
	Object_list *pObjList = result.InitAsList(env);
	pObjList->Reserve(selection.size());
	foreach (wxArrayTreeItemIds, pTreeItemId, selection) {
		pObjList->Add(Value(new Object_wx_TreeItemId(
						new wxTreeItemId(*pTreeItemId), nullptr, OwnerTrue)));
	}
	return ReturnValue(env, arg, result);
}

Gura_DeclareMethod(wx_TreeCtrl, GetStateImageList)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_TreeCtrl, GetStateImageList)
{
	Signal &sig = env.GetSignal();
	Object_wx_TreeCtrl *pThis = Object_wx_TreeCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxImageList *rtn = (wxImageList *)pThis->GetEntity()->GetStateImageList();
	return ReturnValue(env, arg, Value(new Object_wx_ImageList(rtn, nullptr, OwnerFalse)));
}

Gura_DeclareMethod(wx_TreeCtrl, HitTest)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "point", VTYPE_wx_Point, OCCUR_Once);
	DeclareArg(env, "flags", VTYPE_number, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_TreeCtrl, HitTest)
{
	Signal &sig = env.GetSignal();
	Object_wx_TreeCtrl *pThis = Object_wx_TreeCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxPoint *point = Object_wx_Point::GetObject(arg, 0)->GetEntity();
	int flags = arg.GetInt(1);
	wxTreeItemId rtn = pThis->GetEntity()->HitTest(*point, flags);
	return ReturnValue(env, arg, Value(new Object_wx_TreeItemId(new wxTreeItemId(rtn), nullptr, OwnerTrue)));
}

Gura_DeclareMethod(wx_TreeCtrl, InsertItem)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "parent", VTYPE_wx_TreeItemId, OCCUR_Once);
	DeclareArg(env, "previous", VTYPE_wx_TreeItemId, OCCUR_Once);
	DeclareArg(env, "text", VTYPE_string, OCCUR_Once);
	DeclareArg(env, "image", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareArg(env, "selImage", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareArg(env, "data", VTYPE_wx_TreeItemData, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_TreeCtrl, InsertItem)
{
	Signal &sig = env.GetSignal();
	Object_wx_TreeCtrl *pThis = Object_wx_TreeCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxTreeItemId *parent = Object_wx_TreeItemId::GetObject(arg, 0)->GetEntity();
	wxTreeItemId *previous = Object_wx_TreeItemId::GetObject(arg, 1)->GetEntity();
	wxString text = wxString::FromUTF8(arg.GetString(2));
	int image = -1;
	if (arg.IsValid(3)) image = arg.GetInt(3);
	int selImage = -1;
	if (arg.IsValid(4)) selImage = arg.GetInt(4);
	wxTreeItemData *data = (wxTreeItemData *)(nullptr);
	if (arg.IsValid(5)) data = new wx_TreeItemData(*Object_wx_TreeItemData::GetObject(arg, 5)->GetEntity());
	wxTreeItemId rtn = pThis->GetEntity()->InsertItem(*parent, *previous, text, image, selImage, data);
	return ReturnValue(env, arg, Value(new Object_wx_TreeItemId(new wxTreeItemId(rtn), nullptr, OwnerTrue)));
}

Gura_DeclareMethod(wx_TreeCtrl, InsertItemBefore)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "parent", VTYPE_wx_TreeItemId, OCCUR_Once);
	DeclareArg(env, "before", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "text", VTYPE_string, OCCUR_Once);
	DeclareArg(env, "image", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareArg(env, "selImage", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareArg(env, "data", VTYPE_wx_TreeItemData, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_TreeCtrl, InsertItemBefore)
{
	Signal &sig = env.GetSignal();
	Object_wx_TreeCtrl *pThis = Object_wx_TreeCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxTreeItemId *parent = Object_wx_TreeItemId::GetObject(arg, 0)->GetEntity();
	size_t before = arg.GetSizeT(1);
	wxString text = wxString::FromUTF8(arg.GetString(2));
	int image = -1;
	if (arg.IsValid(3)) image = arg.GetInt(3);
	int selImage = -1;
	if (arg.IsValid(4)) selImage = arg.GetInt(4);
	wxTreeItemData *data = (wxTreeItemData *)(nullptr);
	if (arg.IsValid(5)) data = new wx_TreeItemData(*Object_wx_TreeItemData::GetObject(arg, 5)->GetEntity());
	wxTreeItemId rtn = pThis->GetEntity()->InsertItem(*parent, before, text, image, selImage, data);
	return ReturnValue(env, arg, Value(new Object_wx_TreeItemId(new wxTreeItemId(rtn), nullptr, OwnerTrue)));
}

Gura_DeclareMethod(wx_TreeCtrl, IsBold)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "item", VTYPE_wx_TreeItemId, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_TreeCtrl, IsBold)
{
	Signal &sig = env.GetSignal();
	Object_wx_TreeCtrl *pThis = Object_wx_TreeCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxTreeItemId *item = Object_wx_TreeItemId::GetObject(arg, 0)->GetEntity();
	bool rtn = pThis->GetEntity()->IsBold(*item);
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_TreeCtrl, IsEmpty)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_TreeCtrl, IsEmpty)
{
	Signal &sig = env.GetSignal();
	Object_wx_TreeCtrl *pThis = Object_wx_TreeCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	bool rtn = pThis->GetEntity()->IsEmpty();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_TreeCtrl, IsExpanded)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "item", VTYPE_wx_TreeItemId, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_TreeCtrl, IsExpanded)
{
	Signal &sig = env.GetSignal();
	Object_wx_TreeCtrl *pThis = Object_wx_TreeCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxTreeItemId *item = Object_wx_TreeItemId::GetObject(arg, 0)->GetEntity();
	bool rtn = pThis->GetEntity()->IsExpanded(*item);
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_TreeCtrl, IsSelected)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "item", VTYPE_wx_TreeItemId, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_TreeCtrl, IsSelected)
{
	Signal &sig = env.GetSignal();
	Object_wx_TreeCtrl *pThis = Object_wx_TreeCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxTreeItemId *item = Object_wx_TreeItemId::GetObject(arg, 0)->GetEntity();
	bool rtn = pThis->GetEntity()->IsSelected(*item);
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_TreeCtrl, IsVisible)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "item", VTYPE_wx_TreeItemId, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_TreeCtrl, IsVisible)
{
	Signal &sig = env.GetSignal();
	Object_wx_TreeCtrl *pThis = Object_wx_TreeCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxTreeItemId *item = Object_wx_TreeItemId::GetObject(arg, 0)->GetEntity();
	bool rtn = pThis->GetEntity()->IsVisible(*item);
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_TreeCtrl, ItemHasChildren)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "item", VTYPE_wx_TreeItemId, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_TreeCtrl, ItemHasChildren)
{
	Signal &sig = env.GetSignal();
	Object_wx_TreeCtrl *pThis = Object_wx_TreeCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxTreeItemId *item = Object_wx_TreeItemId::GetObject(arg, 0)->GetEntity();
	bool rtn = pThis->GetEntity()->ItemHasChildren(*item);
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_TreeCtrl, OnCompareItems)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "item1", VTYPE_wx_TreeItemId, OCCUR_Once);
	DeclareArg(env, "item2", VTYPE_wx_TreeItemId, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_TreeCtrl, OnCompareItems)
{
	Signal &sig = env.GetSignal();
	Object_wx_TreeCtrl *pThis = Object_wx_TreeCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxTreeItemId *item1 = Object_wx_TreeItemId::GetObject(arg, 0)->GetEntity();
	wxTreeItemId *item2 = Object_wx_TreeItemId::GetObject(arg, 1)->GetEntity();
	int rtn = pThis->GetEntity()->wxTreeCtrl::OnCompareItems(*item1, *item2);
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_TreeCtrl, PrependItem)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "parent", VTYPE_wx_TreeItemId, OCCUR_Once);
	DeclareArg(env, "text", VTYPE_string, OCCUR_Once);
	DeclareArg(env, "image", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareArg(env, "selImage", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareArg(env, "data", VTYPE_wx_TreeItemData, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_TreeCtrl, PrependItem)
{
	Signal &sig = env.GetSignal();
	Object_wx_TreeCtrl *pThis = Object_wx_TreeCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxTreeItemId *parent = Object_wx_TreeItemId::GetObject(arg, 0)->GetEntity();
	wxString text = wxString::FromUTF8(arg.GetString(1));
	int image = -1;
	if (arg.IsValid(2)) image = arg.GetInt(2);
	int selImage = -1;
	if (arg.IsValid(3)) selImage = arg.GetInt(3);
	wxTreeItemData *data = (wxTreeItemData *)(nullptr);
	if (arg.IsValid(4)) data = new wx_TreeItemData(*Object_wx_TreeItemData::GetObject(arg, 4)->GetEntity());
	wxTreeItemId rtn = pThis->GetEntity()->PrependItem(*parent, text, image, selImage, data);
	return ReturnValue(env, arg, Value(new Object_wx_TreeItemId(new wxTreeItemId(rtn), nullptr, OwnerTrue)));
}

Gura_DeclareMethod(wx_TreeCtrl, ScrollTo)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "item", VTYPE_wx_TreeItemId, OCCUR_Once);
}

Gura_ImplementMethod(wx_TreeCtrl, ScrollTo)
{
	Signal &sig = env.GetSignal();
	Object_wx_TreeCtrl *pThis = Object_wx_TreeCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxTreeItemId *item = Object_wx_TreeItemId::GetObject(arg, 0)->GetEntity();
	pThis->GetEntity()->ScrollTo(*item);
	return Value::Nil;
}

Gura_DeclareMethod(wx_TreeCtrl, SelectItem)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "item", VTYPE_wx_TreeItemId, OCCUR_Once);
	DeclareArg(env, "select", VTYPE_boolean, OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_TreeCtrl, SelectItem)
{
	Signal &sig = env.GetSignal();
	Object_wx_TreeCtrl *pThis = Object_wx_TreeCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxTreeItemId *item = Object_wx_TreeItemId::GetObject(arg, 0)->GetEntity();
	bool select = true;
	if (arg.IsValid(1)) select = arg.GetBoolean(1);
	pThis->GetEntity()->SelectItem(*item, select);
	return Value::Nil;
}

Gura_DeclareMethod(wx_TreeCtrl, SetIndent)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "indent", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_TreeCtrl, SetIndent)
{
	Signal &sig = env.GetSignal();
	Object_wx_TreeCtrl *pThis = Object_wx_TreeCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	int indent = arg.GetInt(0);
	pThis->GetEntity()->SetIndent(indent);
	return Value::Nil;
}

Gura_DeclareMethod(wx_TreeCtrl, SetSpacing)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "spacing", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_TreeCtrl, SetSpacing)
{
	Signal &sig = env.GetSignal();
	Object_wx_TreeCtrl *pThis = Object_wx_TreeCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	unsigned int spacing = arg.GetUInt(0);
	pThis->GetEntity()->SetSpacing(spacing);
	return Value::Nil;
}

Gura_DeclareMethod(wx_TreeCtrl, SetImageList)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "imageList", VTYPE_wx_ImageList, OCCUR_Once, FLAG_Nil);
}

Gura_ImplementMethod(wx_TreeCtrl, SetImageList)
{
	Signal &sig = env.GetSignal();
	Object_wx_TreeCtrl *pThis = Object_wx_TreeCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxImageList *imageList = nullptr;
	if (arg.IsValid(0)) imageList = Object_wx_ImageList::GetObject(arg, 0)->GetEntity();
	pThis->GetEntity()->SetImageList(imageList);
	return Value::Nil;
}

Gura_DeclareMethod(wx_TreeCtrl, SetItemBackgroundColour)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "item", VTYPE_wx_TreeItemId, OCCUR_Once);
	DeclareArg(env, "col", VTYPE_wx_Colour, OCCUR_Once);
}

Gura_ImplementMethod(wx_TreeCtrl, SetItemBackgroundColour)
{
	Signal &sig = env.GetSignal();
	Object_wx_TreeCtrl *pThis = Object_wx_TreeCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxTreeItemId *item = Object_wx_TreeItemId::GetObject(arg, 0)->GetEntity();
	wxColour *col = Object_wx_Colour::GetObject(arg, 1)->GetEntity();
	pThis->GetEntity()->SetItemBackgroundColour(*item, *col);
	return Value::Nil;
}

Gura_DeclareMethod(wx_TreeCtrl, SetItemBold)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "item", VTYPE_wx_TreeItemId, OCCUR_Once);
	DeclareArg(env, "bold", VTYPE_boolean, OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_TreeCtrl, SetItemBold)
{
	Signal &sig = env.GetSignal();
	Object_wx_TreeCtrl *pThis = Object_wx_TreeCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxTreeItemId *item = Object_wx_TreeItemId::GetObject(arg, 0)->GetEntity();
	bool bold = true;
	if (arg.IsValid(1)) bold = arg.GetBoolean(1);
	pThis->GetEntity()->SetItemBold(*item, bold);
	return Value::Nil;
}

Gura_DeclareMethod(wx_TreeCtrl, SetItemData)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "item", VTYPE_wx_TreeItemId, OCCUR_Once);
	DeclareArg(env, "data", VTYPE_wx_TreeItemData, OCCUR_Once);
}

Gura_ImplementMethod(wx_TreeCtrl, SetItemData)
{
	Signal &sig = env.GetSignal();
	Object_wx_TreeCtrl *pThis = Object_wx_TreeCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxTreeItemId *item = Object_wx_TreeItemId::GetObject(arg, 0)->GetEntity();
	wxTreeItemData *data = data = new wx_TreeItemData(*Object_wx_TreeItemData::GetObject(arg, 1)->GetEntity());
	pThis->GetEntity()->SetItemData(*item, data);
	return Value::Nil;
}

Gura_DeclareMethod(wx_TreeCtrl, SetGuraData)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "item", VTYPE_wx_TreeItemId, OCCUR_Once);
	DeclareArg(env, "data", VTYPE_any, OCCUR_Once);
}

Gura_ImplementMethod(wx_TreeCtrl, SetGuraData)
{
	Signal &sig = env.GetSignal();
	Object_wx_TreeCtrl *pThis = Object_wx_TreeCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxTreeItemId *item = Object_wx_TreeItemId::GetObject(arg, 0)->GetEntity();
	wx_TreeItemData *data = new wx_TreeItemData(arg.GetValue(1));
	pThis->GetEntity()->SetItemData(*item, data);
	return Value::Nil;
}

Gura_DeclareMethod(wx_TreeCtrl, SetItemDropHighlight)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "item", VTYPE_wx_TreeItemId, OCCUR_Once);
	DeclareArg(env, "highlight", VTYPE_boolean, OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_TreeCtrl, SetItemDropHighlight)
{
	Signal &sig = env.GetSignal();
	Object_wx_TreeCtrl *pThis = Object_wx_TreeCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxTreeItemId *item = Object_wx_TreeItemId::GetObject(arg, 0)->GetEntity();
	bool highlight = true;
	if (arg.IsValid(1)) highlight = arg.GetBoolean(1);
	pThis->GetEntity()->SetItemDropHighlight(*item, highlight);
	return Value::Nil;
}

Gura_DeclareMethod(wx_TreeCtrl, SetItemFont)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "item", VTYPE_wx_TreeItemId, OCCUR_Once);
	DeclareArg(env, "font", VTYPE_wx_Font, OCCUR_Once);
}

Gura_ImplementMethod(wx_TreeCtrl, SetItemFont)
{
	Signal &sig = env.GetSignal();
	Object_wx_TreeCtrl *pThis = Object_wx_TreeCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxTreeItemId *item = Object_wx_TreeItemId::GetObject(arg, 0)->GetEntity();
	wxFont *font = Object_wx_Font::GetObject(arg, 1)->GetEntity();
	pThis->GetEntity()->SetItemFont(*item, *font);
	return Value::Nil;
}

Gura_DeclareMethod(wx_TreeCtrl, SetItemHasChildren)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "item", VTYPE_wx_TreeItemId, OCCUR_Once);
	DeclareArg(env, "hasChildren", VTYPE_boolean, OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_TreeCtrl, SetItemHasChildren)
{
	Signal &sig = env.GetSignal();
	Object_wx_TreeCtrl *pThis = Object_wx_TreeCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxTreeItemId *item = Object_wx_TreeItemId::GetObject(arg, 0)->GetEntity();
	bool hasChildren = true;
	if (arg.IsValid(1)) hasChildren = arg.GetBoolean(1);
	pThis->GetEntity()->SetItemHasChildren(*item, hasChildren);
	return Value::Nil;
}

Gura_DeclareMethod(wx_TreeCtrl, SetItemImage)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "item", VTYPE_wx_TreeItemId, OCCUR_Once);
	DeclareArg(env, "image", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "which", VTYPE_number, OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_TreeCtrl, SetItemImage)
{
	Signal &sig = env.GetSignal();
	Object_wx_TreeCtrl *pThis = Object_wx_TreeCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxTreeItemId *item = Object_wx_TreeItemId::GetObject(arg, 0)->GetEntity();
	int image = arg.GetInt(1);
	wxTreeItemIcon which = wxTreeItemIcon_Normal;
	if (arg.IsValid(2)) which = static_cast<wxTreeItemIcon>(arg.GetInt(2));
	pThis->GetEntity()->SetItemImage(*item, image, which);
	return Value::Nil;
}

Gura_DeclareMethod(wx_TreeCtrl, SetItemText)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "item", VTYPE_wx_TreeItemId, OCCUR_Once);
	DeclareArg(env, "text", VTYPE_string, OCCUR_Once);
}

Gura_ImplementMethod(wx_TreeCtrl, SetItemText)
{
	Signal &sig = env.GetSignal();
	Object_wx_TreeCtrl *pThis = Object_wx_TreeCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxTreeItemId *item = Object_wx_TreeItemId::GetObject(arg, 0)->GetEntity();
	wxString text = wxString::FromUTF8(arg.GetString(1));
	pThis->GetEntity()->SetItemText(*item, text);
	return Value::Nil;
}

Gura_DeclareMethod(wx_TreeCtrl, SetItemTextColour)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "item", VTYPE_wx_TreeItemId, OCCUR_Once);
	DeclareArg(env, "col", VTYPE_wx_Colour, OCCUR_Once);
}

Gura_ImplementMethod(wx_TreeCtrl, SetItemTextColour)
{
	Signal &sig = env.GetSignal();
	Object_wx_TreeCtrl *pThis = Object_wx_TreeCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxTreeItemId *item = Object_wx_TreeItemId::GetObject(arg, 0)->GetEntity();
	wxColour *col = Object_wx_Colour::GetObject(arg, 1)->GetEntity();
	pThis->GetEntity()->SetItemTextColour(*item, *col);
	return Value::Nil;
}

Gura_DeclareMethod(wx_TreeCtrl, SetQuickBestSize)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "quickBestSize", VTYPE_boolean, OCCUR_Once);
}

Gura_ImplementMethod(wx_TreeCtrl, SetQuickBestSize)
{
	Signal &sig = env.GetSignal();
	Object_wx_TreeCtrl *pThis = Object_wx_TreeCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	bool quickBestSize = arg.GetBoolean(0);
	pThis->GetEntity()->SetQuickBestSize(quickBestSize);
	return Value::Nil;
}

Gura_DeclareMethod(wx_TreeCtrl, SetStateImageList)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "imageList", VTYPE_wx_ImageList, OCCUR_Once);
}

Gura_ImplementMethod(wx_TreeCtrl, SetStateImageList)
{
	Signal &sig = env.GetSignal();
	Object_wx_TreeCtrl *pThis = Object_wx_TreeCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxImageList *imageList = Object_wx_ImageList::GetObject(arg, 0)->GetEntity();
	pThis->GetEntity()->SetStateImageList(imageList);
	return Value::Nil;
}

Gura_DeclareMethod(wx_TreeCtrl, SetWindowStyle)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "styles", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_TreeCtrl, SetWindowStyle)
{
	Signal &sig = env.GetSignal();
	Object_wx_TreeCtrl *pThis = Object_wx_TreeCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	long styles = arg.GetLong(0);
	pThis->GetEntity()->SetWindowStyle(styles);
	return Value::Nil;
}

Gura_DeclareMethod(wx_TreeCtrl, SortChildren)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "item", VTYPE_wx_TreeItemId, OCCUR_Once);
}

Gura_ImplementMethod(wx_TreeCtrl, SortChildren)
{
	Signal &sig = env.GetSignal();
	Object_wx_TreeCtrl *pThis = Object_wx_TreeCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxTreeItemId *item = Object_wx_TreeItemId::GetObject(arg, 0)->GetEntity();
	pThis->GetEntity()->SortChildren(*item);
	return Value::Nil;
}

Gura_DeclareMethod(wx_TreeCtrl, Toggle)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "item", VTYPE_wx_TreeItemId, OCCUR_Once);
}

Gura_ImplementMethod(wx_TreeCtrl, Toggle)
{
	Signal &sig = env.GetSignal();
	Object_wx_TreeCtrl *pThis = Object_wx_TreeCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxTreeItemId *item = Object_wx_TreeItemId::GetObject(arg, 0)->GetEntity();
	pThis->GetEntity()->Toggle(*item);
	return Value::Nil;
}

Gura_DeclareMethod(wx_TreeCtrl, ToggleItemSelection)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "item", VTYPE_wx_TreeItemId, OCCUR_Once);
}

Gura_ImplementMethod(wx_TreeCtrl, ToggleItemSelection)
{
	Signal &sig = env.GetSignal();
	Object_wx_TreeCtrl *pThis = Object_wx_TreeCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxTreeItemId *item = Object_wx_TreeItemId::GetObject(arg, 0)->GetEntity();
	pThis->GetEntity()->ToggleItemSelection(*item);
	return Value::Nil;
}

Gura_DeclareMethod(wx_TreeCtrl, Unselect)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_TreeCtrl, Unselect)
{
	Signal &sig = env.GetSignal();
	Object_wx_TreeCtrl *pThis = Object_wx_TreeCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	pThis->GetEntity()->Unselect();
	return Value::Nil;
}

Gura_DeclareMethod(wx_TreeCtrl, UnselectAll)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_TreeCtrl, UnselectAll)
{
	Signal &sig = env.GetSignal();
	Object_wx_TreeCtrl *pThis = Object_wx_TreeCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	pThis->GetEntity()->UnselectAll();
	return Value::Nil;
}

Gura_DeclareMethod(wx_TreeCtrl, UnselectItem)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "item", VTYPE_wx_TreeItemId, OCCUR_Once);
}

Gura_ImplementMethod(wx_TreeCtrl, UnselectItem)
{
	Signal &sig = env.GetSignal();
	Object_wx_TreeCtrl *pThis = Object_wx_TreeCtrl::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxTreeItemId *item = Object_wx_TreeItemId::GetObject(arg, 0)->GetEntity();
	pThis->GetEntity()->UnselectItem(*item);
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Object implementation for wxTreeCtrl
//----------------------------------------------------------------------------
Object_wx_TreeCtrl::~Object_wx_TreeCtrl()
{
}

Object *Object_wx_TreeCtrl::Clone() const
{
	return nullptr;
}

String Object_wx_TreeCtrl::ToString(bool exprFlag)
{
	String rtn("<wx.TreeCtrl:");
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
// Class implementation for wxTreeCtrl
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_TreeCtrl)
{
	Gura_RealizeUserSymbol(OnCompareItems);
	Gura_AssignWxStringValue(TreeCtrlNameStr);
	Gura_AssignFunction(TreeCtrlEmpty);
	Gura_AssignFunction(TreeCtrl);
	Gura_AssignMethod(wx_TreeCtrl, AddRoot);
	Gura_AssignMethod(wx_TreeCtrl, AppendItem);
	Gura_AssignMethod(wx_TreeCtrl, AssignImageList);
	Gura_AssignMethod(wx_TreeCtrl, AssignStateImageList);
	Gura_AssignMethod(wx_TreeCtrl, Collapse);
	Gura_AssignMethod(wx_TreeCtrl, CollapseAll);
	Gura_AssignMethod(wx_TreeCtrl, CollapseAllChildren);
	Gura_AssignMethod(wx_TreeCtrl, CollapseAndReset);
	Gura_AssignMethod(wx_TreeCtrl, Delete);
	Gura_AssignMethod(wx_TreeCtrl, DeleteAllItems);
	Gura_AssignMethod(wx_TreeCtrl, DeleteChildren);
	Gura_AssignMethod(wx_TreeCtrl, EditLabel);
	Gura_AssignMethod(wx_TreeCtrl, EndEditLabel);
	Gura_AssignMethod(wx_TreeCtrl, EnsureVisible);
	Gura_AssignMethod(wx_TreeCtrl, Expand);
	Gura_AssignMethod(wx_TreeCtrl, ExpandAll);
	Gura_AssignMethod(wx_TreeCtrl, ExpandAllChildren);
	Gura_AssignMethod(wx_TreeCtrl, GetBoundingRect);
	Gura_AssignMethod(wx_TreeCtrl, GetChildrenCount);
	Gura_AssignMethod(wx_TreeCtrl, GetCount);
	Gura_AssignMethod(wx_TreeCtrl, GetEditControl);
	Gura_AssignMethod(wx_TreeCtrl, GetFirstChild);
	Gura_AssignMethod(wx_TreeCtrl, GetFirstVisibleItem);
	Gura_AssignMethod(wx_TreeCtrl, GetImageList);
	Gura_AssignMethod(wx_TreeCtrl, GetIndent);
	Gura_AssignMethod(wx_TreeCtrl, GetSpacing);
	Gura_AssignMethod(wx_TreeCtrl, GetItemBackgroundColour);
	Gura_AssignMethod(wx_TreeCtrl, GetItemData);
	Gura_AssignMethod(wx_TreeCtrl, GetGuraData);
	Gura_AssignMethod(wx_TreeCtrl, GetItemChildren);
	Gura_AssignMethod(wx_TreeCtrl, GetItemFont);
	Gura_AssignMethod(wx_TreeCtrl, GetItemImage);
	Gura_AssignMethod(wx_TreeCtrl, GetItemText);
	Gura_AssignMethod(wx_TreeCtrl, GetItemTextColour);
	Gura_AssignMethod(wx_TreeCtrl, GetLastChild);
	Gura_AssignMethod(wx_TreeCtrl, GetNextChild);
	Gura_AssignMethod(wx_TreeCtrl, GetNextSibling);
	Gura_AssignMethod(wx_TreeCtrl, GetNextVisible);
	Gura_AssignMethod(wx_TreeCtrl, GetItemParent);
	Gura_AssignMethod(wx_TreeCtrl, GetPrevSibling);
	Gura_AssignMethod(wx_TreeCtrl, GetPrevVisible);
	Gura_AssignMethod(wx_TreeCtrl, GetQuickBestSize);
	Gura_AssignMethod(wx_TreeCtrl, GetRootItem);
	Gura_AssignMethod(wx_TreeCtrl, GetSelection);
	Gura_AssignMethod(wx_TreeCtrl, GetSelections);
	Gura_AssignMethod(wx_TreeCtrl, GetStateImageList);
	Gura_AssignMethod(wx_TreeCtrl, HitTest);
	Gura_AssignMethod(wx_TreeCtrl, InsertItem);
	Gura_AssignMethod(wx_TreeCtrl, InsertItemBefore);
	Gura_AssignMethod(wx_TreeCtrl, IsBold);
	Gura_AssignMethod(wx_TreeCtrl, IsEmpty);
	Gura_AssignMethod(wx_TreeCtrl, IsExpanded);
	Gura_AssignMethod(wx_TreeCtrl, IsSelected);
	Gura_AssignMethod(wx_TreeCtrl, IsVisible);
	Gura_AssignMethod(wx_TreeCtrl, ItemHasChildren);
	Gura_AssignMethod(wx_TreeCtrl, OnCompareItems);
	Gura_AssignMethod(wx_TreeCtrl, PrependItem);
	Gura_AssignMethod(wx_TreeCtrl, ScrollTo);
	Gura_AssignMethod(wx_TreeCtrl, SelectItem);
	Gura_AssignMethod(wx_TreeCtrl, SetIndent);
	Gura_AssignMethod(wx_TreeCtrl, SetSpacing);
	Gura_AssignMethod(wx_TreeCtrl, SetImageList);
	Gura_AssignMethod(wx_TreeCtrl, SetItemBackgroundColour);
	Gura_AssignMethod(wx_TreeCtrl, SetItemBold);
	Gura_AssignMethod(wx_TreeCtrl, SetItemData);
	Gura_AssignMethod(wx_TreeCtrl, SetGuraData);
	Gura_AssignMethod(wx_TreeCtrl, SetItemDropHighlight);
	Gura_AssignMethod(wx_TreeCtrl, SetItemFont);
	Gura_AssignMethod(wx_TreeCtrl, SetItemHasChildren);
	Gura_AssignMethod(wx_TreeCtrl, SetItemImage);
	Gura_AssignMethod(wx_TreeCtrl, SetItemText);
	Gura_AssignMethod(wx_TreeCtrl, SetItemTextColour);
	Gura_AssignMethod(wx_TreeCtrl, SetQuickBestSize);
	Gura_AssignMethod(wx_TreeCtrl, SetStateImageList);
	Gura_AssignMethod(wx_TreeCtrl, SetWindowStyle);
	Gura_AssignMethod(wx_TreeCtrl, SortChildren);
	Gura_AssignMethod(wx_TreeCtrl, Toggle);
	Gura_AssignMethod(wx_TreeCtrl, ToggleItemSelection);
	Gura_AssignMethod(wx_TreeCtrl, Unselect);
	Gura_AssignMethod(wx_TreeCtrl, UnselectAll);
	Gura_AssignMethod(wx_TreeCtrl, UnselectItem);
}

Gura_ImplementDescendantCreator(wx_TreeCtrl)
{
	return new Object_wx_TreeCtrl((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
