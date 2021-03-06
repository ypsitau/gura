//----------------------------------------------------------------------------
// wxSize
// extracted from size.tex
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Class derivation
//----------------------------------------------------------------------------
class wx_Size: public wxSize, public GuraObjectObserver {
private:
	//Gura::Signal *_pSig;
	Object_wx_Size *_pObj;
public:
	inline wx_Size() : wxSize(), _pObj(nullptr) {}
	inline wx_Size(int width, int height) : wxSize(width, height), _pObj(nullptr) {}
	~wx_Size();
	inline void AssocWithGura(Object_wx_Size *pObj) {
		_pObj = pObj;
	}
	// virtual function of GuraObjectObserver
	virtual void GuraObjectDeleted();
};

wx_Size::~wx_Size()
{
	if (_pObj != nullptr) _pObj->InvalidateEntity();
}

void wx_Size::GuraObjectDeleted()
{
	_pObj = nullptr;
}

//----------------------------------------------------------------------------
// Gura interfaces for wxSize
//----------------------------------------------------------------------------
Gura_DeclareFunction(SizeEmpty)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	SetClassToConstruct(Gura_UserClass(wx_Size));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(SizeEmpty)
{
	Signal &sig = env.GetSignal();
	//if (!CheckWxReady(sig)) return Value::Nil;
	wx_Size *pEntity = new wx_Size();
	Object_wx_Size *pObj = Object_wx_Size::GetObjectThis(arg);
	if (pObj == nullptr) {
		pObj = new Object_wx_Size(pEntity, pEntity, OwnerFalse);
		pEntity->AssocWithGura(pObj);
		return ReturnValue(env, arg, Value(pObj));
	}
	pObj->SetEntity(pEntity, pEntity, OwnerFalse);
	pEntity->AssocWithGura(pObj);
	return ReturnValue(env, arg, arg.GetValueThis());
}

Gura_DeclareFunction(Size)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	SetClassToConstruct(Gura_UserClass(wx_Size));
	DeclareArg(env, "width", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "height", VTYPE_number, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(Size)
{
	Signal &sig = env.GetSignal();
	//if (!CheckWxReady(sig)) return Value::Nil;
	int width = arg.GetInt(0);
	int height = arg.GetInt(1);
	wx_Size *pEntity = new wx_Size(width, height);
	Object_wx_Size *pObj = Object_wx_Size::GetObjectThis(arg);
	if (pObj == nullptr) {
		pObj = new Object_wx_Size(pEntity, pEntity, OwnerFalse);
		pEntity->AssocWithGura(pObj);
		return ReturnValue(env, arg, Value(pObj));
	}
	pObj->SetEntity(pEntity, pEntity, OwnerFalse);
	pEntity->AssocWithGura(pObj);
	return ReturnValue(env, arg, arg.GetValueThis());
}

Gura_DeclareMethod(wx_Size, DecBy)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "size", VTYPE_wx_Size, OCCUR_Once);
}

Gura_ImplementMethod(wx_Size, DecBy)
{
	Signal &sig = env.GetSignal();
	Object_wx_Size *pThis = Object_wx_Size::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxSize *size = Object_wx_Size::GetObject(arg, 0)->GetEntity();
	pThis->GetEntity()->DecBy(*size);
	return Value::Nil;
}

Gura_DeclareMethod(wx_Size, DecBy_1)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "dx", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "dy", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Size, DecBy_1)
{
	Signal &sig = env.GetSignal();
	Object_wx_Size *pThis = Object_wx_Size::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	int dx = arg.GetInt(0);
	int dy = arg.GetInt(1);
	pThis->GetEntity()->DecBy(dx, dy);
	return Value::Nil;
}

Gura_DeclareMethod(wx_Size, DecBy_2)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "d", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Size, DecBy_2)
{
	Signal &sig = env.GetSignal();
	Object_wx_Size *pThis = Object_wx_Size::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	int d = arg.GetInt(0);
	pThis->GetEntity()->DecBy(d);
	return Value::Nil;
}

Gura_DeclareMethod(wx_Size, DecTo)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "size", VTYPE_wx_Size, OCCUR_Once);
}

Gura_ImplementMethod(wx_Size, DecTo)
{
	Signal &sig = env.GetSignal();
	Object_wx_Size *pThis = Object_wx_Size::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxSize *size = Object_wx_Size::GetObject(arg, 0)->GetEntity();
	pThis->GetEntity()->DecTo(*size);
	return Value::Nil;
}

Gura_DeclareMethod(wx_Size, IsFullySpecified)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_Size, IsFullySpecified)
{
	Signal &sig = env.GetSignal();
	Object_wx_Size *pThis = Object_wx_Size::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	bool rtn = pThis->GetEntity()->IsFullySpecified();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_Size, GetWidth)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_Size, GetWidth)
{
	Signal &sig = env.GetSignal();
	Object_wx_Size *pThis = Object_wx_Size::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	int rtn = pThis->GetEntity()->GetWidth();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_Size, GetHeight)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_Size, GetHeight)
{
	Signal &sig = env.GetSignal();
	Object_wx_Size *pThis = Object_wx_Size::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	int rtn = pThis->GetEntity()->GetHeight();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_Size, IncBy)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "size", VTYPE_wx_Size, OCCUR_Once);
}

Gura_ImplementMethod(wx_Size, IncBy)
{
	Signal &sig = env.GetSignal();
	Object_wx_Size *pThis = Object_wx_Size::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxSize *size = Object_wx_Size::GetObject(arg, 0)->GetEntity();
	pThis->GetEntity()->IncBy(*size);
	return Value::Nil;
}

Gura_DeclareMethod(wx_Size, IncBy_1)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "dx", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "dy", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Size, IncBy_1)
{
	Signal &sig = env.GetSignal();
	Object_wx_Size *pThis = Object_wx_Size::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	int dx = arg.GetInt(0);
	int dy = arg.GetInt(1);
	pThis->GetEntity()->IncBy(dx, dy);
	return Value::Nil;
}

Gura_DeclareMethod(wx_Size, IncBy_2)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "d", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Size, IncBy_2)
{
	Signal &sig = env.GetSignal();
	Object_wx_Size *pThis = Object_wx_Size::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	int d = arg.GetInt(0);
	pThis->GetEntity()->IncBy(d);
	return Value::Nil;
}

Gura_DeclareMethod(wx_Size, IncTo)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "size", VTYPE_wx_Size, OCCUR_Once);
}

Gura_ImplementMethod(wx_Size, IncTo)
{
	Signal &sig = env.GetSignal();
	Object_wx_Size *pThis = Object_wx_Size::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxSize *size = Object_wx_Size::GetObject(arg, 0)->GetEntity();
	pThis->GetEntity()->IncTo(*size);
	return Value::Nil;
}

Gura_DeclareMethod(wx_Size, Scale)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "xscale", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "yscale", VTYPE_number, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_Size, Scale)
{
	Signal &sig = env.GetSignal();
	Object_wx_Size *pThis = Object_wx_Size::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	float xscale = arg.GetFloat(0);
	float yscale = arg.GetFloat(1);
	wxSize &rtn = pThis->GetEntity()->Scale(xscale, yscale);
	return ReturnValue(env, arg, Value(new Object_wx_Size(new wxSize(rtn), nullptr, OwnerTrue)));
}

Gura_DeclareMethod(wx_Size, Set)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "width", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "height", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Size, Set)
{
	Signal &sig = env.GetSignal();
	Object_wx_Size *pThis = Object_wx_Size::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	int width = arg.GetInt(0);
	int height = arg.GetInt(1);
	pThis->GetEntity()->Set(width, height);
	return Value::Nil;
}

Gura_DeclareMethod(wx_Size, SetDefaults)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "sizeDefault", VTYPE_wx_Size, OCCUR_Once);
}

Gura_ImplementMethod(wx_Size, SetDefaults)
{
	Signal &sig = env.GetSignal();
	Object_wx_Size *pThis = Object_wx_Size::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxSize *sizeDefault = Object_wx_Size::GetObject(arg, 0)->GetEntity();
	pThis->GetEntity()->SetDefaults(*sizeDefault);
	return Value::Nil;
}

Gura_DeclareMethod(wx_Size, SetHeight)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "height", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Size, SetHeight)
{
	Signal &sig = env.GetSignal();
	Object_wx_Size *pThis = Object_wx_Size::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	int height = arg.GetInt(0);
	pThis->GetEntity()->SetHeight(height);
	return Value::Nil;
}

Gura_DeclareMethod(wx_Size, SetWidth)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "width", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Size, SetWidth)
{
	Signal &sig = env.GetSignal();
	Object_wx_Size *pThis = Object_wx_Size::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	int width = arg.GetInt(0);
	pThis->GetEntity()->SetWidth(width);
	return Value::Nil;
}

// operator ==
Gura_ImplementBinaryOperator(Eq, wx_Size, wx_Size)
{
	wxSize *item1 = Object_wx_Size::GetObject(valueLeft)->GetEntity();
	wxSize *item2 = Object_wx_Size::GetObject(valueRight)->GetEntity();
	return *item1 == *item2;
}

// operator !=
Gura_ImplementBinaryOperator(Ne, wx_Size, wx_Size)
{
	wxSize *item1 = Object_wx_Size::GetObject(valueLeft)->GetEntity();
	wxSize *item2 = Object_wx_Size::GetObject(valueRight)->GetEntity();
	return *item1 != *item2;
}

// operator +
Gura_ImplementBinaryOperator(Add, wx_Size, wx_Size)
{
	wxSize *item1 = Object_wx_Size::GetObject(valueLeft)->GetEntity();
	wxSize *item2 = Object_wx_Size::GetObject(valueRight)->GetEntity();
	wxSize rtn = *item1 + *item2;
	return Value(new Object_wx_Size(new wxSize(rtn), nullptr, OwnerTrue));
}

// operator -
Gura_ImplementBinaryOperator(Sub, wx_Size, wx_Size)
{
	wxSize *item1 = Object_wx_Size::GetObject(valueLeft)->GetEntity();
	wxSize *item2 = Object_wx_Size::GetObject(valueRight)->GetEntity();
	wxSize rtn = *item1 - *item2;
	return Value(new Object_wx_Size(new wxSize(rtn), nullptr, OwnerTrue));
}

// operator *
Gura_ImplementBinaryOperator(Mul, wx_Size, number)
{
	wxSize *item = Object_wx_Size::GetObject(valueLeft)->GetEntity();
	int factor = valueRight.GetInt();
	wxSize rtn = *item * factor;
	return Value(new Object_wx_Size(new wxSize(rtn), nullptr, OwnerTrue));
}

// operator /
Gura_ImplementBinaryOperator(Div, wx_Size, number)
{
	wxSize *item = Object_wx_Size::GetObject(valueLeft)->GetEntity();
	int factor = valueRight.GetInt();
	wxSize rtn = *item / factor;
	return Value(new Object_wx_Size(new wxSize(rtn), nullptr, OwnerTrue));
}

//-----------------------------------------------------------------------------
// Implementation of properties
//-----------------------------------------------------------------------------
// wx.Size#x
Gura_DeclareProperty_RW(wx_Size, x)
{
	SetPropAttr(VTYPE_number);
	AddHelp(
		Gura_Symbol(en),
		""
		);
}

Gura_ImplementPropertyGetter(wx_Size, x)
{
	Object_wx_Size *pObjThis = Object_wx_Size::GetObject(valueThis);
	return pObjThis->GetEntity()->x;
}

Gura_ImplementPropertySetter(wx_Size, x)
{
	Object_wx_Size *pObjThis = Object_wx_Size::GetObject(valueThis);
	pObjThis->GetEntity()->x = value.GetInt();
	return value;
}

// wx.Size#y
Gura_DeclareProperty_RW(wx_Size, y)
{
	SetPropAttr(VTYPE_number);
	AddHelp(
		Gura_Symbol(en),
		""
		);
}

Gura_ImplementPropertyGetter(wx_Size, y)
{
	Object_wx_Size *pObjThis = Object_wx_Size::GetObject(valueThis);
	return pObjThis->GetEntity()->y;
}

Gura_ImplementPropertySetter(wx_Size, y)
{
	Object_wx_Size *pObjThis = Object_wx_Size::GetObject(valueThis);
	pObjThis->GetEntity()->y = value.GetInt();
	return value;
}

//----------------------------------------------------------------------------
// Object implementation for wxSize
//----------------------------------------------------------------------------
Object_wx_Size::~Object_wx_Size()
{
	if (_pEntity != nullptr) NotifyGuraObjectDeleted();
	if (_ownerFlag) delete _pEntity;
	_pEntity = nullptr;
}

Object *Object_wx_Size::Clone() const
{
	return nullptr;
}

String Object_wx_Size::ToString(bool exprFlag)
{
	String rtn("<wx.Size:");
	if (GetEntity() == nullptr) {
		rtn += "invalid>";
	} else {
		char buff[64];
		::sprintf(buff, "%d,%d>", GetEntity()->x, GetEntity()->y);
		rtn += buff;
	}
	return rtn;
}

//----------------------------------------------------------------------------
// Class implementation for wxSize
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_Size)
{
	// Assignment of properties
	Gura_AssignProperty(wx_Size, x);
	Gura_AssignProperty(wx_Size, y);
	// Assignment of functions
	Gura_AssignFunction(SizeEmpty);
	Gura_AssignFunction(Size);
	// Assignment of operators
	Gura_AssignBinaryOperator(Eq, wx_Size, wx_Size);
	Gura_AssignBinaryOperator(Ne, wx_Size, wx_Size);
	Gura_AssignBinaryOperator(Add, wx_Size, wx_Size);
	Gura_AssignBinaryOperator(Sub, wx_Size, wx_Size);
	Gura_AssignBinaryOperator(Mul, wx_Size, number);
	Gura_AssignBinaryOperator(Div, wx_Size, number);
	// Assignment of methods
	Gura_AssignMethod(wx_Size, DecBy);
	Gura_AssignMethod(wx_Size, DecBy_1);
	Gura_AssignMethod(wx_Size, DecBy_2);
	Gura_AssignMethod(wx_Size, DecTo);
	Gura_AssignMethod(wx_Size, IsFullySpecified);
	Gura_AssignMethod(wx_Size, GetWidth);
	Gura_AssignMethod(wx_Size, GetHeight);
	Gura_AssignMethod(wx_Size, IncBy);
	Gura_AssignMethod(wx_Size, IncBy_1);
	Gura_AssignMethod(wx_Size, IncBy_2);
	Gura_AssignMethod(wx_Size, IncTo);
	Gura_AssignMethod(wx_Size, Scale);
	Gura_AssignMethod(wx_Size, Set);
	Gura_AssignMethod(wx_Size, SetDefaults);
	Gura_AssignMethod(wx_Size, SetHeight);
	Gura_AssignMethod(wx_Size, SetWidth);
}

Gura_ImplementDescendantCreator(wx_Size)
{
	return new Object_wx_Size((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
