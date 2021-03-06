//----------------------------------------------------------------------------
// wxGridCellStringRenderer
// extracted from gridrend.tex
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Class derivation
//----------------------------------------------------------------------------
class wx_GridCellStringRenderer: public wxGridCellStringRenderer, public GuraObjectObserver {
private:
	//Gura::Signal *_pSig;
	AutoPtr<Object_wx_GridCellStringRenderer> _pObj;
public:
	inline wx_GridCellStringRenderer() : wxGridCellStringRenderer(), _pObj(nullptr) {}
	inline wx_GridCellStringRenderer(const wx_GridCellStringRenderer &renderer) :
		wxGridCellStringRenderer(),
		_pObj(Object_wx_GridCellStringRenderer::Reference(renderer._pObj.get())) {}
	~wx_GridCellStringRenderer();
	inline void AssocWithGura(Object_wx_GridCellStringRenderer *pObj) {
		_pObj.reset(Object_wx_GridCellStringRenderer::Reference(pObj));
	}
	virtual void Draw(wxGrid &grid, wxGridCellAttr &attr, wxDC &dc,
					const wxRect &rect, int row, int col, bool isSelected);
	virtual wxGridCellRenderer *Clone() const;
	// reveal private or protected member functions to public
	inline void _Draw(wxGrid &grid, wxGridCellAttr &attr, wxDC &dc,
					const wxRect &rect, int row, int col, bool isSelected) {
		wxGridCellStringRenderer::Draw(grid, attr, dc, rect, row, col, isSelected);
	}
	// virtual function of GuraObjectObserver
	virtual void GuraObjectDeleted();
};

wx_GridCellStringRenderer::~wx_GridCellStringRenderer()
{
}

void wx_GridCellStringRenderer::Draw(wxGrid &grid, wxGridCellAttr &attr, wxDC &dc,
					const wxRect &rect, int row, int col, bool isSelected)
{
	bool evaluatedFlag = false;
	_pObj->EvalMethod_Draw(_pObj->GetSignal(), evaluatedFlag,
							grid, attr, dc, rect, row, col, isSelected);
	if (!evaluatedFlag) wxGridCellStringRenderer::Draw(grid, attr, dc, rect, row, col, isSelected);
}

wxGridCellRenderer *wx_GridCellStringRenderer::Clone() const
{
	return new wx_GridCellStringRenderer(*this);
}

void wx_GridCellStringRenderer::GuraObjectDeleted()
{
}

//----------------------------------------------------------------------------
// Gura interfaces for wxGridCellStringRenderer
//----------------------------------------------------------------------------
Gura_DeclareFunction(GridCellStringRenderer)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	SetClassToConstruct(Gura_UserClass(wx_GridCellStringRenderer));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(GridCellStringRenderer)
{
	Signal &sig = env.GetSignal();
	if (!CheckWxReady(sig)) return Value::Nil;
	wx_GridCellStringRenderer *pEntity = new wx_GridCellStringRenderer();
	Object_wx_GridCellStringRenderer *pObj = Object_wx_GridCellStringRenderer::GetObjectThis(arg);
	if (pObj == nullptr) {
		pObj = new Object_wx_GridCellStringRenderer(pEntity, pEntity, OwnerFalse);
		pEntity->AssocWithGura(pObj);
		return ReturnValue(env, arg, Value(pObj));
	}
	pObj->SetEntity(pEntity, pEntity, OwnerFalse);
	pEntity->AssocWithGura(pObj);
	return ReturnValue(env, arg, arg.GetValueThis());
}

Gura_DeclareMethod(wx_GridCellStringRenderer, Draw)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "grid", VTYPE_wx_Grid, OCCUR_Once);
	DeclareArg(env, "attr", VTYPE_wx_GridCellAttr, OCCUR_Once);
	DeclareArg(env, "dc", VTYPE_wx_DC, OCCUR_Once);
	DeclareArg(env, "rect", VTYPE_wx_Rect, OCCUR_Once);
	DeclareArg(env, "row", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "col", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "isSelected", VTYPE_boolean, OCCUR_Once);
}

Gura_ImplementMethod(wx_GridCellStringRenderer, Draw)
{
	Signal &sig = env.GetSignal();
	Object_wx_GridCellRenderer *pThis = Object_wx_GridCellRenderer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxGrid *grid = Object_wx_Grid::GetObject(arg, 0)->GetEntity();
	wxGridCellAttr *attr = Object_wx_GridCellAttr::GetObject(arg, 1)->GetEntity();
	wxDC *dc = Object_wx_DC::GetObject(arg, 2)->GetEntity();
	wxRect *rect = Object_wx_Rect::GetObject(arg, 3)->GetEntity();
	int row = arg.GetInt(4);
	int col = arg.GetInt(5);
	bool isSelected = arg.GetBoolean(6);
	dynamic_cast<wx_GridCellStringRenderer *>(pThis->GetEntity())->
		_Draw(*grid, *attr, *dc, *rect, row, col, isSelected);
	return Value::Nil;
}

//----------------------------------------------------------------------------
// Object implementation for wxGridCellStringRenderer
//----------------------------------------------------------------------------
Object_wx_GridCellStringRenderer::~Object_wx_GridCellStringRenderer()
{
}

Object *Object_wx_GridCellStringRenderer::Clone() const
{
	return nullptr;
}

String Object_wx_GridCellStringRenderer::ToString(bool exprFlag)
{
	String rtn("<wx.GridCellStringRenderer:");
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
// Class implementation for wxGridCellStringRenderer
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_GridCellStringRenderer)
{
	Gura_AssignFunction(GridCellStringRenderer);
	Gura_AssignMethod(wx_GridCellStringRenderer, Draw);
}

Gura_ImplementDescendantCreator(wx_GridCellStringRenderer)
{
	return new Object_wx_GridCellStringRenderer((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
