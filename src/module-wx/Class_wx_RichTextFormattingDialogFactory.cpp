//----------------------------------------------------------------------------
// wxRichTextFormattingDialogFactory
// extracted from richtextformattingdialog.tex
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

Gura_DeclarePrivUserSymbol(CreateButtons);
Gura_DeclarePrivUserSymbol(CreatePage);
Gura_DeclarePrivUserSymbol(CreatePages);
Gura_DeclarePrivUserSymbol(GetPageId);
Gura_DeclarePrivUserSymbol(GetPageIdCount);
Gura_DeclarePrivUserSymbol(GetPageImage);
Gura_DeclarePrivUserSymbol(SetSheetStyle);
Gura_DeclarePrivUserSymbol(ShowHelp);

//----------------------------------------------------------------------------
// Class derivation
//----------------------------------------------------------------------------
class wx_RichTextFormattingDialogFactory: public wxRichTextFormattingDialogFactory, public GuraObjectObserver {
private:
	//Gura::Signal *_pSig;
	Object_wx_RichTextFormattingDialogFactory *_pObj;
public:
	inline wx_RichTextFormattingDialogFactory() : wxRichTextFormattingDialogFactory(), _pObj(nullptr) {}
	//virtual bool CreateButtons(wxRichTextFormattingDialog* dialog);
	//virtual wxPanel* CreatePage(int page, wxString& title, wxRichTextFormattingDialog* dialog);
	//virtual bool CreatePages(long pages, wxRichTextFormattingDialog* dialog);
	//virtual int GetPageId(int i);
	//virtual int GetPageIdCount();
	//virtual int GetPageImage(int id);
	//virtual bool SetSheetStyle(wxRichTextFormattingDialog* dialog);
	//virtual bool ShowHelp(int page, wxRichTextFormattingDialog* dialog);
	~wx_RichTextFormattingDialogFactory();
	inline void AssocWithGura(Object_wx_RichTextFormattingDialogFactory *pObj) {
		_pObj = pObj;
	}
	// virtual function of GuraObjectObserver
	virtual void GuraObjectDeleted();
};

wx_RichTextFormattingDialogFactory::~wx_RichTextFormattingDialogFactory()
{
	if (_pObj != nullptr) _pObj->InvalidateEntity();
}

void wx_RichTextFormattingDialogFactory::GuraObjectDeleted()
{
	_pObj = nullptr;
}

//----------------------------------------------------------------------------
// Gura interfaces for wxRichTextFormattingDialogFactory
//----------------------------------------------------------------------------
Gura_DeclareFunction(RichTextFormattingDialogFactoryEmpty)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	SetClassToConstruct(Gura_UserClass(wx_RichTextFormattingDialogFactory));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(RichTextFormattingDialogFactoryEmpty)
{
	Signal &sig = env.GetSignal();
	if (!CheckWxReady(sig)) return Value::Nil;
	wx_RichTextFormattingDialogFactory *pEntity = new wx_RichTextFormattingDialogFactory();
	Object_wx_RichTextFormattingDialogFactory *pObj = Object_wx_RichTextFormattingDialogFactory::GetObjectThis(arg);
	if (pObj == nullptr) {
		pObj = new Object_wx_RichTextFormattingDialogFactory(pEntity, pEntity, OwnerFalse);
		pEntity->AssocWithGura(pObj);
		return ReturnValue(env, arg, Value(pObj));
	}
	pObj->SetEntity(pEntity, pEntity, OwnerFalse);
	pEntity->AssocWithGura(pObj);
	return ReturnValue(env, arg, arg.GetValueThis());
}

Gura_DeclareMethod(wx_RichTextFormattingDialogFactory, CreateButtons)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "dialog", VTYPE_wx_RichTextFormattingDialog, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_RichTextFormattingDialogFactory, CreateButtons)
{
	Signal &sig = env.GetSignal();
	Object_wx_RichTextFormattingDialogFactory *pThis = Object_wx_RichTextFormattingDialogFactory::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxRichTextFormattingDialog *dialog = Object_wx_RichTextFormattingDialog::GetObject(arg, 0)->GetEntity();
	bool rtn = pThis->GetEntity()->CreateButtons(dialog);
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_RichTextFormattingDialogFactory, CreatePage)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "page", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "title", VTYPE_string, OCCUR_Once);
	DeclareArg(env, "dialog", VTYPE_wx_RichTextFormattingDialog, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_RichTextFormattingDialogFactory, CreatePage)
{
	Signal &sig = env.GetSignal();
	Object_wx_RichTextFormattingDialogFactory *pThis = Object_wx_RichTextFormattingDialogFactory::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	int page = arg.GetInt(0);
	wxString title = wxString::FromUTF8(arg.GetString(1));
	wxRichTextFormattingDialog *dialog = Object_wx_RichTextFormattingDialog::GetObject(arg, 2)->GetEntity();
	wxPanel *rtn = (wxPanel *)pThis->GetEntity()->CreatePage(page, title, dialog);
	return ReturnValue(env, arg, Value(new Object_wx_Panel(rtn, nullptr, OwnerFalse)));
}

Gura_DeclareMethod(wx_RichTextFormattingDialogFactory, CreatePages)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "pages", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "dialog", VTYPE_wx_RichTextFormattingDialog, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_RichTextFormattingDialogFactory, CreatePages)
{
	Signal &sig = env.GetSignal();
	Object_wx_RichTextFormattingDialogFactory *pThis = Object_wx_RichTextFormattingDialogFactory::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	long pages = arg.GetLong(0);
	wxRichTextFormattingDialog *dialog = Object_wx_RichTextFormattingDialog::GetObject(arg, 1)->GetEntity();
	bool rtn = pThis->GetEntity()->CreatePages(pages, dialog);
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_RichTextFormattingDialogFactory, GetPageId)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "i", VTYPE_number, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_RichTextFormattingDialogFactory, GetPageId)
{
	Signal &sig = env.GetSignal();
	Object_wx_RichTextFormattingDialogFactory *pThis = Object_wx_RichTextFormattingDialogFactory::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	int i = arg.GetInt(0);
	int rtn = pThis->GetEntity()->GetPageId(i);
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_RichTextFormattingDialogFactory, GetPageIdCount)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_RichTextFormattingDialogFactory, GetPageIdCount)
{
	Signal &sig = env.GetSignal();
	Object_wx_RichTextFormattingDialogFactory *pThis = Object_wx_RichTextFormattingDialogFactory::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	int rtn = pThis->GetEntity()->GetPageIdCount();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_RichTextFormattingDialogFactory, GetPageImage)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "id", VTYPE_number, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_RichTextFormattingDialogFactory, GetPageImage)
{
	Signal &sig = env.GetSignal();
	Object_wx_RichTextFormattingDialogFactory *pThis = Object_wx_RichTextFormattingDialogFactory::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	int id = arg.GetInt(0);
	int rtn = pThis->GetEntity()->GetPageImage(id);
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_RichTextFormattingDialogFactory, SetSheetStyle)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "dialog", VTYPE_wx_RichTextFormattingDialog, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_RichTextFormattingDialogFactory, SetSheetStyle)
{
	Signal &sig = env.GetSignal();
	Object_wx_RichTextFormattingDialogFactory *pThis = Object_wx_RichTextFormattingDialogFactory::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxRichTextFormattingDialog *dialog = Object_wx_RichTextFormattingDialog::GetObject(arg, 0)->GetEntity();
	bool rtn = pThis->GetEntity()->SetSheetStyle(dialog);
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_RichTextFormattingDialogFactory, ShowHelp)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "page", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "dialog", VTYPE_wx_RichTextFormattingDialog, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_RichTextFormattingDialogFactory, ShowHelp)
{
	Signal &sig = env.GetSignal();
	Object_wx_RichTextFormattingDialogFactory *pThis = Object_wx_RichTextFormattingDialogFactory::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	int page = arg.GetInt(0);
	wxRichTextFormattingDialog *dialog = Object_wx_RichTextFormattingDialog::GetObject(arg, 1)->GetEntity();
	bool rtn = pThis->GetEntity()->ShowHelp(page, dialog);
	return ReturnValue(env, arg, Value(rtn));
}

//----------------------------------------------------------------------------
// Object implementation for wxRichTextFormattingDialogFactory
//----------------------------------------------------------------------------
Object_wx_RichTextFormattingDialogFactory::~Object_wx_RichTextFormattingDialogFactory()
{
}

Object *Object_wx_RichTextFormattingDialogFactory::Clone() const
{
	return nullptr;
}

String Object_wx_RichTextFormattingDialogFactory::ToString(bool exprFlag)
{
	String rtn("<wx.RichTextFormattingDialogFactory:");
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
// Class implementation for wxRichTextFormattingDialogFactory
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_RichTextFormattingDialogFactory)
{
	Gura_RealizeUserSymbol(CreateButtons);
	Gura_RealizeUserSymbol(CreatePage);
	Gura_RealizeUserSymbol(CreatePages);
	Gura_RealizeUserSymbol(GetPageId);
	Gura_RealizeUserSymbol(GetPageIdCount);
	Gura_RealizeUserSymbol(GetPageImage);
	Gura_RealizeUserSymbol(SetSheetStyle);
	Gura_RealizeUserSymbol(ShowHelp);
	Gura_AssignFunction(RichTextFormattingDialogFactoryEmpty);
	Gura_AssignMethod(wx_RichTextFormattingDialogFactory, CreateButtons);
	Gura_AssignMethod(wx_RichTextFormattingDialogFactory, CreatePage);
	Gura_AssignMethod(wx_RichTextFormattingDialogFactory, CreatePages);
	Gura_AssignMethod(wx_RichTextFormattingDialogFactory, GetPageId);
	Gura_AssignMethod(wx_RichTextFormattingDialogFactory, GetPageIdCount);
	Gura_AssignMethod(wx_RichTextFormattingDialogFactory, GetPageImage);
	Gura_AssignMethod(wx_RichTextFormattingDialogFactory, SetSheetStyle);
	Gura_AssignMethod(wx_RichTextFormattingDialogFactory, ShowHelp);
}

Gura_ImplementDescendantCreator(wx_RichTextFormattingDialogFactory)
{
	return new Object_wx_RichTextFormattingDialogFactory((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
