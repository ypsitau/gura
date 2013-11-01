//----------------------------------------------------------------------------
// wxNotebookSizer
// extracted from nbsizer.tex
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Class derivation
//----------------------------------------------------------------------------
class wx_NotebookSizer: public wxNotebookSizer, public GuraObjectObserver {
private:
	Gura::Signal _sig;
	Object_wx_NotebookSizer *_pObj;
public:
	inline wx_NotebookSizer(wxNotebook* notebook) : wxNotebookSizer(notebook), _sig(NULL), _pObj(NULL) {}
	~wx_NotebookSizer();
	inline void AssocWithGura(Gura::Signal &sig, Object_wx_NotebookSizer *pObj) {
		_sig = sig, _pObj = pObj;
	}
	// virtual function of GuraObjectObserver
	virtual void GuraObjectDeleted();
};

wx_NotebookSizer::~wx_NotebookSizer()
{
	if (_pObj != NULL) _pObj->InvalidateEntity();
}

void wx_NotebookSizer::GuraObjectDeleted()
{
	_pObj = NULL;
}

//----------------------------------------------------------------------------
// Gura interfaces for wxNotebookSizer
//----------------------------------------------------------------------------
Gura_DeclareFunction(NotebookSizer)
{
	SetMode(RSLTMODE_Normal, FLAG_Map);
	SetClassToConstruct(Gura_UserClass(wx_NotebookSizer));
	DeclareArg(env, "notebook", VTYPE_wx_Notebook, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(NotebookSizer)
{
	if (!CheckWxReady(sig)) return Value::Null;
	wxNotebook *notebook = Object_wx_Notebook::GetObject(args, 0)->GetEntity();
	wx_NotebookSizer *pEntity = new wx_NotebookSizer(notebook);
	Object_wx_NotebookSizer *pObj = Object_wx_NotebookSizer::GetThisObj(args);
	if (pObj == NULL) {
		pObj = new Object_wx_NotebookSizer(pEntity, pEntity, OwnerFalse);
		pEntity->AssocWithGura(sig, pObj);
		return ReturnValue(env, sig, args, Value(pObj));
	}
	pObj->SetEntity(pEntity, pEntity, OwnerFalse);
	pEntity->AssocWithGura(sig, pObj);
	return ReturnValue(env, sig, args, args.GetThis());
}

Gura_DeclareMethod(wx_NotebookSizer, GetNotebook)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_NotebookSizer, GetNotebook)
{
	Object_wx_NotebookSizer *pThis = Object_wx_NotebookSizer::GetThisObj(args);
	if (pThis->IsInvalid(sig)) return Value::Null;
	wxNotebook *rtn = (wxNotebook *)pThis->GetEntity()->GetNotebook();
	return ReturnValue(env, sig, args, Value(new Object_wx_Notebook(rtn, NULL, OwnerFalse)));
}

//----------------------------------------------------------------------------
// Object implementation for wxNotebookSizer
//----------------------------------------------------------------------------
Object_wx_NotebookSizer::~Object_wx_NotebookSizer()
{
}

Object *Object_wx_NotebookSizer::Clone() const
{
	return NULL;
}

String Object_wx_NotebookSizer::ToString(bool exprFlag)
{
	String rtn("<wx.NotebookSizer:");
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
// Class implementation for wxNotebookSizer
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_NotebookSizer)
{
	Gura_AssignFunction(NotebookSizer);
	Gura_AssignMethod(wx_NotebookSizer, GetNotebook);
}

Gura_ImplementDescendantCreator(wx_NotebookSizer)
{
	return new Object_wx_NotebookSizer((pClass == NULL)? this : pClass, NULL, NULL, OwnerFalse);
}

Gura_EndModuleScope(wx)
