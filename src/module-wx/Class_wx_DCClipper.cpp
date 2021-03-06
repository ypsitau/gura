//----------------------------------------------------------------------------
// wxDCClipper
// extracted from dcclipper.tex
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Class derivation
//----------------------------------------------------------------------------
class wx_DCClipper: public wxDCClipper, public GuraObjectObserver {
private:
	//Gura::Signal *_pSig;
	Object_wx_DCClipper *_pObj;
public:
	inline wx_DCClipper(wxDC& dc, const wxRegion& r) : wxDCClipper(dc, r), _pObj(nullptr) {}
	inline wx_DCClipper(wxDC& dc, const wxRect& rect) : wxDCClipper(dc, rect), _pObj(nullptr) {}
	inline wx_DCClipper(wxDC& dc, int x, int y, int w, int h) : wxDCClipper(dc, x, y, w, h), _pObj(nullptr) {}
	~wx_DCClipper();
	inline void AssocWithGura(Object_wx_DCClipper *pObj) {
		_pObj = pObj;
	}
	// virtual function of GuraObjectObserver
	virtual void GuraObjectDeleted();
};

wx_DCClipper::~wx_DCClipper()
{
	if (_pObj != nullptr) _pObj->InvalidateEntity();
}

void wx_DCClipper::GuraObjectDeleted()
{
	_pObj = nullptr;
}

//----------------------------------------------------------------------------
// Gura interfaces for wxDCClipper
//----------------------------------------------------------------------------
Gura_DeclareFunction(DCClipper)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	SetClassToConstruct(Gura_UserClass(wx_DCClipper));
	DeclareArg(env, "dc", VTYPE_wx_DC, OCCUR_Once);
	DeclareArg(env, "r", VTYPE_wx_Region, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(DCClipper)
{
	Signal &sig = env.GetSignal();
	if (!CheckWxReady(sig)) return Value::Nil;
	wxDC *dc = Object_wx_DC::GetObject(arg, 0)->GetEntity();
	wxRegion *r = Object_wx_Region::GetObject(arg, 1)->GetEntity();
	wx_DCClipper *pEntity = new wx_DCClipper(*dc, *r);
	Object_wx_DCClipper *pObj = Object_wx_DCClipper::GetObjectThis(arg);
	if (pObj == nullptr) {
		pObj = new Object_wx_DCClipper(pEntity, pEntity, OwnerFalse);
		pEntity->AssocWithGura(pObj);
		return ReturnValue(env, arg, Value(pObj));
	}
	pObj->SetEntity(pEntity, pEntity, OwnerFalse);
	pEntity->AssocWithGura(pObj);
	return ReturnValue(env, arg, arg.GetValueThis());
}

Gura_DeclareFunction(DCClipper_1)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	SetClassToConstruct(Gura_UserClass(wx_DCClipper));
	DeclareArg(env, "dc", VTYPE_wx_DC, OCCUR_Once);
	DeclareArg(env, "rect", VTYPE_wx_Rect, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(DCClipper_1)
{
	Signal &sig = env.GetSignal();
	if (!CheckWxReady(sig)) return Value::Nil;
	wxDC *dc = Object_wx_DC::GetObject(arg, 0)->GetEntity();
	wxRect *rect = Object_wx_Rect::GetObject(arg, 1)->GetEntity();
	wx_DCClipper *pEntity = new wx_DCClipper(*dc, *rect);
	Object_wx_DCClipper *pObj = Object_wx_DCClipper::GetObjectThis(arg);
	if (pObj == nullptr) {
		pObj = new Object_wx_DCClipper(pEntity, pEntity, OwnerFalse);
		pEntity->AssocWithGura(pObj);
		return ReturnValue(env, arg, Value(pObj));
	}
	pObj->SetEntity(pEntity, pEntity, OwnerFalse);
	pEntity->AssocWithGura(pObj);
	return ReturnValue(env, arg, arg.GetValueThis());
}

Gura_DeclareFunction(DCClipper_2)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	SetClassToConstruct(Gura_UserClass(wx_DCClipper));
	DeclareArg(env, "dc", VTYPE_wx_DC, OCCUR_Once);
	DeclareArg(env, "x", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "y", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "w", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "h", VTYPE_number, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(DCClipper_2)
{
	Signal &sig = env.GetSignal();
	if (!CheckWxReady(sig)) return Value::Nil;
	wxDC *dc = Object_wx_DC::GetObject(arg, 0)->GetEntity();
	int x = arg.GetInt(1);
	int y = arg.GetInt(2);
	int w = arg.GetInt(3);
	int h = arg.GetInt(4);
	wx_DCClipper *pEntity = new wx_DCClipper(*dc, x, y, w, h);
	Object_wx_DCClipper *pObj = Object_wx_DCClipper::GetObjectThis(arg);
	if (pObj == nullptr) {
		pObj = new Object_wx_DCClipper(pEntity, pEntity, OwnerFalse);
		pEntity->AssocWithGura(pObj);
		return ReturnValue(env, arg, Value(pObj));
	}
	pObj->SetEntity(pEntity, pEntity, OwnerFalse);
	pEntity->AssocWithGura(pObj);
	return ReturnValue(env, arg, arg.GetValueThis());
}

//----------------------------------------------------------------------------
// Object implementation for wxDCClipper
//----------------------------------------------------------------------------
Object_wx_DCClipper::~Object_wx_DCClipper()
{
	if (_pEntity != nullptr) NotifyGuraObjectDeleted();
	if (_ownerFlag) delete _pEntity;
	_pEntity = nullptr;
}

Object *Object_wx_DCClipper::Clone() const
{
	return nullptr;
}

String Object_wx_DCClipper::ToString(bool exprFlag)
{
	String rtn("<wx.DCClipper:");
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
// Class implementation for wxDCClipper
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_DCClipper)
{
	Gura_AssignFunction(DCClipper);
	Gura_AssignFunction(DCClipper_1);
	Gura_AssignFunction(DCClipper_2);
}

Gura_ImplementDescendantCreator(wx_DCClipper)
{
	return new Object_wx_DCClipper((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
