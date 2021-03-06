//----------------------------------------------------------------------------
// wxDataViewProgressRenderer
// extracted from dataviewrenderer.tex
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Class derivation
//----------------------------------------------------------------------------
class wx_DataViewProgressRenderer: public wxDataViewProgressRenderer, public GuraObjectObserver {
private:
	//Gura::Signal *_pSig;
	Object_wx_DataViewProgressRenderer *_pObj;
public:
	inline wx_DataViewProgressRenderer(const wxString& label, const wxString& varianttype, wxDataViewCellMode mode) : wxDataViewProgressRenderer(label, varianttype, mode), _pObj(nullptr) {}
	~wx_DataViewProgressRenderer();
	inline void AssocWithGura(Object_wx_DataViewProgressRenderer *pObj) {
		_pObj = pObj;
	}
	// virtual function of GuraObjectObserver
	virtual void GuraObjectDeleted();
};

wx_DataViewProgressRenderer::~wx_DataViewProgressRenderer()
{
	if (_pObj != nullptr) _pObj->InvalidateEntity();
}

void wx_DataViewProgressRenderer::GuraObjectDeleted()
{
	_pObj = nullptr;
}

//----------------------------------------------------------------------------
// Gura interfaces for wxDataViewProgressRenderer
//----------------------------------------------------------------------------
Gura_DeclareFunction(DataViewProgressRenderer)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	SetClassToConstruct(Gura_UserClass(wx_DataViewProgressRenderer));
	DeclareArg(env, "label", VTYPE_string, OCCUR_ZeroOrOnce);
	DeclareArg(env, "varianttype", VTYPE_string, OCCUR_ZeroOrOnce);
	DeclareArg(env, "mode", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(DataViewProgressRenderer)
{
	Signal &sig = env.GetSignal();
	if (!CheckWxReady(sig)) return Value::Nil;
	wxString label = wxEmptyString;
	if (arg.IsValid(0)) label = wxString::FromUTF8(arg.GetString(0));
	wxString varianttype = wxT("long");
	if (arg.IsValid(1)) varianttype = wxString::FromUTF8(arg.GetString(1));
	wxDataViewCellMode mode = wxDATAVIEW_CELL_INERT;
	if (arg.IsValid(2)) mode = static_cast<wxDataViewCellMode>(arg.GetInt(2));
	wx_DataViewProgressRenderer *pEntity = new wx_DataViewProgressRenderer(label, varianttype, mode);
	Object_wx_DataViewProgressRenderer *pObj = Object_wx_DataViewProgressRenderer::GetObjectThis(arg);
	if (pObj == nullptr) {
		pObj = new Object_wx_DataViewProgressRenderer(pEntity, pEntity, OwnerFalse);
		pEntity->AssocWithGura(pObj);
		return ReturnValue(env, arg, Value(pObj));
	}
	pObj->SetEntity(pEntity, pEntity, OwnerFalse);
	pEntity->AssocWithGura(pObj);
	return ReturnValue(env, arg, arg.GetValueThis());
}

//----------------------------------------------------------------------------
// Object implementation for wxDataViewProgressRenderer
//----------------------------------------------------------------------------
Object_wx_DataViewProgressRenderer::~Object_wx_DataViewProgressRenderer()
{
}

Object *Object_wx_DataViewProgressRenderer::Clone() const
{
	return nullptr;
}

String Object_wx_DataViewProgressRenderer::ToString(bool exprFlag)
{
	String rtn("<wx.DataViewProgressRenderer:");
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
// Class implementation for wxDataViewProgressRenderer
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_DataViewProgressRenderer)
{
	Gura_AssignFunction(DataViewProgressRenderer);
}

Gura_ImplementDescendantCreator(wx_DataViewProgressRenderer)
{
	return new Object_wx_DataViewProgressRenderer((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
