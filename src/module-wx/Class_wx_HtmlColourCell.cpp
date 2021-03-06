//----------------------------------------------------------------------------
// wxHtmlColourCell
// extracted from htcolor.tex
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Class derivation
//----------------------------------------------------------------------------
class wx_HtmlColourCell: public wxHtmlColourCell, public GuraObjectObserver {
private:
	//Gura::Signal *_pSig;
	Object_wx_HtmlColourCell *_pObj;
public:
	inline wx_HtmlColourCell(wxColour clr, int flags) : wxHtmlColourCell(clr, flags), _pObj(nullptr) {}
	~wx_HtmlColourCell();
	inline void AssocWithGura(Object_wx_HtmlColourCell *pObj) {
		_pObj = pObj;
	}
	// virtual function of GuraObjectObserver
	virtual void GuraObjectDeleted();
};

wx_HtmlColourCell::~wx_HtmlColourCell()
{
	if (_pObj != nullptr) _pObj->InvalidateEntity();
}

void wx_HtmlColourCell::GuraObjectDeleted()
{
	_pObj = nullptr;
}

//----------------------------------------------------------------------------
// Gura interfaces for wxHtmlColourCell
//----------------------------------------------------------------------------
Gura_DeclareFunction(HtmlColourCell)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	SetClassToConstruct(Gura_UserClass(wx_HtmlColourCell));
	DeclareArg(env, "clr", VTYPE_wx_Colour, OCCUR_Once);
	DeclareArg(env, "flags", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(HtmlColourCell)
{
	Signal &sig = env.GetSignal();
	if (!CheckWxReady(sig)) return Value::Nil;
	wxColour *clr = Object_wx_Colour::GetObject(arg, 0)->GetEntity();
	int flags = wxHTML_CLR_FOREGROUND;
	if (arg.IsValid(1)) flags = arg.GetInt(1);
	wx_HtmlColourCell *pEntity = new wx_HtmlColourCell(*clr, flags);
	Object_wx_HtmlColourCell *pObj = Object_wx_HtmlColourCell::GetObjectThis(arg);
	if (pObj == nullptr) {
		pObj = new Object_wx_HtmlColourCell(pEntity, pEntity, OwnerFalse);
		pEntity->AssocWithGura(pObj);
		return ReturnValue(env, arg, Value(pObj));
	}
	pObj->SetEntity(pEntity, pEntity, OwnerFalse);
	pEntity->AssocWithGura(pObj);
	return ReturnValue(env, arg, arg.GetValueThis());
}

//----------------------------------------------------------------------------
// Object implementation for wxHtmlColourCell
//----------------------------------------------------------------------------
Object_wx_HtmlColourCell::~Object_wx_HtmlColourCell()
{
}

Object *Object_wx_HtmlColourCell::Clone() const
{
	return nullptr;
}

String Object_wx_HtmlColourCell::ToString(bool exprFlag)
{
	String rtn("<wx.HtmlColourCell:");
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
// Class implementation for wxHtmlColourCell
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_HtmlColourCell)
{
	Gura_AssignFunction(HtmlColourCell);
}

Gura_ImplementDescendantCreator(wx_HtmlColourCell)
{
	return new Object_wx_HtmlColourCell((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
