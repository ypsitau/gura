//----------------------------------------------------------------------------
// wxRichTextBuffer
// extracted from richtextbuffer.tex
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Class derivation
//----------------------------------------------------------------------------
class wx_RichTextBuffer: public wxRichTextBuffer, public GuraObjectObserver {
private:
	//Gura::Signal *_pSig;
	Object_wx_RichTextBuffer *_pObj;
public:
	inline wx_RichTextBuffer(const wxRichTextBuffer& obj) : wxRichTextBuffer(obj), _pObj(nullptr) {}
	inline wx_RichTextBuffer() : wxRichTextBuffer(), _pObj(nullptr) {}
	~wx_RichTextBuffer();
	inline void AssocWithGura(Object_wx_RichTextBuffer *pObj) {
		_pObj = pObj;
	}
	// virtual function of GuraObjectObserver
	virtual void GuraObjectDeleted();
};

wx_RichTextBuffer::~wx_RichTextBuffer()
{
	if (_pObj != nullptr) _pObj->InvalidateEntity();
}

void wx_RichTextBuffer::GuraObjectDeleted()
{
	_pObj = nullptr;
}

//----------------------------------------------------------------------------
// Gura interfaces for wxRichTextBuffer
//----------------------------------------------------------------------------
Gura_DeclareFunction(RichTextBuffer)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	SetClassToConstruct(Gura_UserClass(wx_RichTextBuffer));
	DeclareArg(env, "obj", VTYPE_wx_RichTextBuffer, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(RichTextBuffer)
{
	Signal &sig = env.GetSignal();
	if (!CheckWxReady(sig)) return Value::Nil;
	wxRichTextBuffer *obj = Object_wx_RichTextBuffer::GetObject(arg, 0)->GetEntity();
	wx_RichTextBuffer *pEntity = new wx_RichTextBuffer(*obj);
	Object_wx_RichTextBuffer *pObj = Object_wx_RichTextBuffer::GetObjectThis(arg);
	if (pObj == nullptr) {
		pObj = new Object_wx_RichTextBuffer(pEntity, pEntity, OwnerFalse);
		pEntity->AssocWithGura(pObj);
		return ReturnValue(env, arg, Value(pObj));
	}
	pObj->SetEntity(pEntity, pEntity, OwnerFalse);
	pEntity->AssocWithGura(pObj);
	return ReturnValue(env, arg, arg.GetValueThis());
}

Gura_DeclareFunction(RichTextBufferEmpty)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	SetClassToConstruct(Gura_UserClass(wx_RichTextBuffer));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(RichTextBufferEmpty)
{
	Signal &sig = env.GetSignal();
	if (!CheckWxReady(sig)) return Value::Nil;
	wx_RichTextBuffer *pEntity = new wx_RichTextBuffer();
	Object_wx_RichTextBuffer *pObj = Object_wx_RichTextBuffer::GetObjectThis(arg);
	if (pObj == nullptr) {
		pObj = new Object_wx_RichTextBuffer(pEntity, pEntity, OwnerFalse);
		pEntity->AssocWithGura(pObj);
		return ReturnValue(env, arg, Value(pObj));
	}
	pObj->SetEntity(pEntity, pEntity, OwnerFalse);
	pEntity->AssocWithGura(pObj);
	return ReturnValue(env, arg, arg.GetValueThis());
}

Gura_DeclareMethod(wx_RichTextBuffer, AddEventHandler)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "handler", VTYPE_wx_EvtHandler, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_RichTextBuffer, AddEventHandler)
{
	Signal &sig = env.GetSignal();
	Object_wx_RichTextBuffer *pThis = Object_wx_RichTextBuffer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxEvtHandler *handler = Object_wx_EvtHandler::GetObject(arg, 0)->GetEntity();
	bool rtn = pThis->GetEntity()->AddEventHandler(handler);
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareClassMethod(wx_RichTextBuffer, AddHandler)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "handler", VTYPE_wx_RichTextFileHandler, OCCUR_Once);
}

Gura_ImplementClassMethod(wx_RichTextBuffer, AddHandler)
{
	Signal &sig = env.GetSignal();
	if (!CheckWxReady(sig)) return Value::Nil;
	wxRichTextFileHandler *handler = Object_wx_RichTextFileHandler::GetObject(arg, 0)->GetEntity();
	wxRichTextBuffer::AddHandler(handler);
	return Value::Nil;
}

Gura_DeclareMethod(wx_RichTextBuffer, AddParagraph)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "text", VTYPE_string, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_RichTextBuffer, AddParagraph)
{
	Signal &sig = env.GetSignal();
	Object_wx_RichTextBuffer *pThis = Object_wx_RichTextBuffer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxString text = wxString::FromUTF8(arg.GetString(0));
	wxRichTextRange rtn = pThis->GetEntity()->AddParagraph(text);
	return ReturnValue(env, arg, Value(new Object_wx_RichTextRange(new wxRichTextRange(rtn), nullptr, OwnerTrue)));
}

Gura_DeclareMethod(wx_RichTextBuffer, BatchingUndo)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_RichTextBuffer, BatchingUndo)
{
	Signal &sig = env.GetSignal();
	Object_wx_RichTextBuffer *pThis = Object_wx_RichTextBuffer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	bool rtn = pThis->GetEntity()->BatchingUndo();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_RichTextBuffer, BeginAlignment)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "alignment", VTYPE_number, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_RichTextBuffer, BeginAlignment)
{
	Signal &sig = env.GetSignal();
	Object_wx_RichTextBuffer *pThis = Object_wx_RichTextBuffer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxTextAttrAlignment alignment = static_cast<wxTextAttrAlignment>(arg.GetInt(0));
	bool rtn = pThis->GetEntity()->BeginAlignment(alignment);
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_RichTextBuffer, BeginBatchUndo)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "cmdName", VTYPE_string, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_RichTextBuffer, BeginBatchUndo)
{
	Signal &sig = env.GetSignal();
	Object_wx_RichTextBuffer *pThis = Object_wx_RichTextBuffer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxString cmdName = wxString::FromUTF8(arg.GetString(0));
	bool rtn = pThis->GetEntity()->BeginBatchUndo(cmdName);
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_RichTextBuffer, BeginBold)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_RichTextBuffer, BeginBold)
{
	Signal &sig = env.GetSignal();
	Object_wx_RichTextBuffer *pThis = Object_wx_RichTextBuffer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	bool rtn = pThis->GetEntity()->BeginBold();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_RichTextBuffer, BeginCharacterStyle)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "characterStyle", VTYPE_string, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_RichTextBuffer, BeginCharacterStyle)
{
	Signal &sig = env.GetSignal();
	Object_wx_RichTextBuffer *pThis = Object_wx_RichTextBuffer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxString characterStyle = wxString::FromUTF8(arg.GetString(0));
	bool rtn = pThis->GetEntity()->BeginCharacterStyle(characterStyle);
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_RichTextBuffer, BeginFont)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "font", VTYPE_wx_Font, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_RichTextBuffer, BeginFont)
{
	Signal &sig = env.GetSignal();
	Object_wx_RichTextBuffer *pThis = Object_wx_RichTextBuffer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxFont *font = Object_wx_Font::GetObject(arg, 0)->GetEntity();
	bool rtn = pThis->GetEntity()->BeginFont(*font);
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_RichTextBuffer, BeginFontSize)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "pointSize", VTYPE_number, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_RichTextBuffer, BeginFontSize)
{
	Signal &sig = env.GetSignal();
	Object_wx_RichTextBuffer *pThis = Object_wx_RichTextBuffer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	int pointSize = arg.GetInt(0);
	bool rtn = pThis->GetEntity()->BeginFontSize(pointSize);
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_RichTextBuffer, BeginItalic)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_RichTextBuffer, BeginItalic)
{
	Signal &sig = env.GetSignal();
	Object_wx_RichTextBuffer *pThis = Object_wx_RichTextBuffer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	bool rtn = pThis->GetEntity()->BeginItalic();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_RichTextBuffer, BeginLeftIndent)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "leftIndent", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "leftSubIndent", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_RichTextBuffer, BeginLeftIndent)
{
	Signal &sig = env.GetSignal();
	Object_wx_RichTextBuffer *pThis = Object_wx_RichTextBuffer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	int leftIndent = arg.GetInt(0);
	int leftSubIndent = 0;
	if (arg.IsValid(1)) leftSubIndent = arg.GetInt(1);
	bool rtn = pThis->GetEntity()->BeginLeftIndent(leftIndent, leftSubIndent);
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_RichTextBuffer, BeginLineSpacing)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "lineSpacing", VTYPE_number, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_RichTextBuffer, BeginLineSpacing)
{
	Signal &sig = env.GetSignal();
	Object_wx_RichTextBuffer *pThis = Object_wx_RichTextBuffer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	int lineSpacing = arg.GetInt(0);
	bool rtn = pThis->GetEntity()->BeginLineSpacing(lineSpacing);
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_RichTextBuffer, BeginListStyle)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "listStyle", VTYPE_string, OCCUR_Once);
	DeclareArg(env, "level", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareArg(env, "number", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_RichTextBuffer, BeginListStyle)
{
	Signal &sig = env.GetSignal();
	Object_wx_RichTextBuffer *pThis = Object_wx_RichTextBuffer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxString listStyle = wxString::FromUTF8(arg.GetString(0));
	int level = 1;
	if (arg.IsValid(1)) level = arg.GetInt(1);
	int number = 1;
	if (arg.IsValid(2)) number = arg.GetInt(2);
	bool rtn = pThis->GetEntity()->BeginListStyle(listStyle, level, number);
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_RichTextBuffer, BeginNumberedBullet)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "bulletNumber", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "leftIndent", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "leftSubIndent", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "bulletStyle", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_RichTextBuffer, BeginNumberedBullet)
{
	Signal &sig = env.GetSignal();
	Object_wx_RichTextBuffer *pThis = Object_wx_RichTextBuffer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	int bulletNumber = arg.GetInt(0);
	int leftIndent = arg.GetInt(1);
	int leftSubIndent = arg.GetInt(2);
	int bulletStyle = wxTEXT_ATTR_BULLET_STYLE_ARABIC|wxTEXT_ATTR_BULLET_STYLE_PERIOD;
	if (arg.IsValid(3)) bulletStyle = arg.GetInt(3);
	bool rtn = pThis->GetEntity()->BeginNumberedBullet(bulletNumber, leftIndent, leftSubIndent, bulletStyle);
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_RichTextBuffer, BeginParagraphSpacing)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "before", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "after", VTYPE_number, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_RichTextBuffer, BeginParagraphSpacing)
{
	Signal &sig = env.GetSignal();
	Object_wx_RichTextBuffer *pThis = Object_wx_RichTextBuffer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	int before = arg.GetInt(0);
	int after = arg.GetInt(1);
	bool rtn = pThis->GetEntity()->BeginParagraphSpacing(before, after);
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_RichTextBuffer, BeginParagraphStyle)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "paragraphStyle", VTYPE_string, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_RichTextBuffer, BeginParagraphStyle)
{
	Signal &sig = env.GetSignal();
	Object_wx_RichTextBuffer *pThis = Object_wx_RichTextBuffer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxString paragraphStyle = wxString::FromUTF8(arg.GetString(0));
	bool rtn = pThis->GetEntity()->BeginParagraphStyle(paragraphStyle);
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_RichTextBuffer, BeginRightIndent)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "rightIndent", VTYPE_number, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_RichTextBuffer, BeginRightIndent)
{
	Signal &sig = env.GetSignal();
	Object_wx_RichTextBuffer *pThis = Object_wx_RichTextBuffer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	int rightIndent = arg.GetInt(0);
	bool rtn = pThis->GetEntity()->BeginRightIndent(rightIndent);
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_RichTextBuffer, BeginStyle)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "style", VTYPE_wx_TextAttrEx, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_RichTextBuffer, BeginStyle)
{
	Signal &sig = env.GetSignal();
	Object_wx_RichTextBuffer *pThis = Object_wx_RichTextBuffer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxTextAttrEx *style = Object_wx_TextAttrEx::GetObject(arg, 0)->GetEntity();
	bool rtn = pThis->GetEntity()->BeginStyle(*style);
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_RichTextBuffer, BeginSuppressUndo)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_RichTextBuffer, BeginSuppressUndo)
{
	Signal &sig = env.GetSignal();
	Object_wx_RichTextBuffer *pThis = Object_wx_RichTextBuffer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	bool rtn = pThis->GetEntity()->BeginSuppressUndo();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_RichTextBuffer, BeginStandardBullet)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "bulletName", VTYPE_string, OCCUR_Once);
	DeclareArg(env, "leftIndent", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "leftSubIndent", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "bulletStyle", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_RichTextBuffer, BeginStandardBullet)
{
	Signal &sig = env.GetSignal();
	Object_wx_RichTextBuffer *pThis = Object_wx_RichTextBuffer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxString bulletName = wxString::FromUTF8(arg.GetString(0));
	int leftIndent = arg.GetInt(1);
	int leftSubIndent = arg.GetInt(2);
	int bulletStyle = wxTEXT_ATTR_BULLET_STYLE_STANDARD;
	if (arg.IsValid(3)) bulletStyle = arg.GetInt(3);
	bool rtn = pThis->GetEntity()->BeginStandardBullet(bulletName, leftIndent, leftSubIndent, bulletStyle);
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_RichTextBuffer, BeginSymbolBullet)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "symbol", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "leftIndent", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "leftSubIndent", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "bulletStyle", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_RichTextBuffer, BeginSymbolBullet)
{
	Signal &sig = env.GetSignal();
	Object_wx_RichTextBuffer *pThis = Object_wx_RichTextBuffer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxChar symbol = static_cast<wxChar>(arg.GetInt(0));
	int leftIndent = arg.GetInt(1);
	int leftSubIndent = arg.GetInt(2);
	int bulletStyle = wxTEXT_ATTR_BULLET_STYLE_SYMBOL;
	if (arg.IsValid(3)) bulletStyle = arg.GetInt(3);
	bool rtn = pThis->GetEntity()->BeginSymbolBullet(symbol, leftIndent, leftSubIndent, bulletStyle);
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_RichTextBuffer, BeginTextColour)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "colour", VTYPE_wx_Colour, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_RichTextBuffer, BeginTextColour)
{
	Signal &sig = env.GetSignal();
	Object_wx_RichTextBuffer *pThis = Object_wx_RichTextBuffer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxColour *colour = Object_wx_Colour::GetObject(arg, 0)->GetEntity();
	bool rtn = pThis->GetEntity()->BeginTextColour(*colour);
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_RichTextBuffer, BeginUnderline)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_RichTextBuffer, BeginUnderline)
{
	Signal &sig = env.GetSignal();
	Object_wx_RichTextBuffer *pThis = Object_wx_RichTextBuffer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	bool rtn = pThis->GetEntity()->BeginUnderline();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_RichTextBuffer, BeginURL)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "url", VTYPE_string, OCCUR_Once);
	DeclareArg(env, "characterStyle", VTYPE_string, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_RichTextBuffer, BeginURL)
{
	Signal &sig = env.GetSignal();
	Object_wx_RichTextBuffer *pThis = Object_wx_RichTextBuffer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxString url = wxString::FromUTF8(arg.GetString(0));
	wxString characterStyle = wxEmptyString;
	if (arg.IsValid(1)) characterStyle = wxString::FromUTF8(arg.GetString(1));
	bool rtn = pThis->GetEntity()->BeginURL(url, characterStyle);
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_RichTextBuffer, CanPasteFromClipboard)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_RichTextBuffer, CanPasteFromClipboard)
{
	Signal &sig = env.GetSignal();
	Object_wx_RichTextBuffer *pThis = Object_wx_RichTextBuffer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	bool rtn = pThis->GetEntity()->CanPasteFromClipboard();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareClassMethod(wx_RichTextBuffer, CleanUpHandlers)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementClassMethod(wx_RichTextBuffer, CleanUpHandlers)
{
	Signal &sig = env.GetSignal();
	if (!CheckWxReady(sig)) return Value::Nil;
	wxRichTextBuffer::CleanUpHandlers();
	return Value::Nil;
}

Gura_DeclareMethod(wx_RichTextBuffer, Clear)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_RichTextBuffer, Clear)
{
	Signal &sig = env.GetSignal();
	Object_wx_RichTextBuffer *pThis = Object_wx_RichTextBuffer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	pThis->GetEntity()->Clear();
	return Value::Nil;
}

Gura_DeclareMethod(wx_RichTextBuffer, ClearListStyle)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "range", VTYPE_wx_RichTextRange, OCCUR_Once);
	DeclareArg(env, "flags", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_RichTextBuffer, ClearListStyle)
{
	Signal &sig = env.GetSignal();
	Object_wx_RichTextBuffer *pThis = Object_wx_RichTextBuffer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxRichTextRange *range = Object_wx_RichTextRange::GetObject(arg, 0)->GetEntity();
	int flags = wxRICHTEXT_SETSTYLE_WITH_UNDO;
	if (arg.IsValid(1)) flags = arg.GetInt(1);
	bool rtn = pThis->GetEntity()->ClearListStyle(*range, flags);
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_RichTextBuffer, ClearListStyle_1)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "range", VTYPE_wx_RichTextRange, OCCUR_Once);
	DeclareArg(env, "flags", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_RichTextBuffer, ClearListStyle_1)
{
	Signal &sig = env.GetSignal();
	Object_wx_RichTextBuffer *pThis = Object_wx_RichTextBuffer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxRichTextRange *range = Object_wx_RichTextRange::GetObject(arg, 0)->GetEntity();
	int flags = wxRICHTEXT_SETSTYLE_WITH_UNDO;
	if (arg.IsValid(1)) flags = arg.GetInt(1);
	bool rtn = pThis->GetEntity()->ClearListStyle(*range, flags);
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_RichTextBuffer, ClearStyleStack)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_RichTextBuffer, ClearStyleStack)
{
	Signal &sig = env.GetSignal();
	Object_wx_RichTextBuffer *pThis = Object_wx_RichTextBuffer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	pThis->GetEntity()->ClearStyleStack();
	return Value::Nil;
}

Gura_DeclareMethod(wx_RichTextBuffer, Clone)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_RichTextBuffer, Clone)
{
	Signal &sig = env.GetSignal();
	Object_wx_RichTextBuffer *pThis = Object_wx_RichTextBuffer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxRichTextObject *rtn = (wxRichTextObject *)pThis->GetEntity()->Clone();
	return ReturnValue(env, arg, Value(new Object_wx_RichTextObject(rtn, nullptr, OwnerFalse)));
}

Gura_DeclareMethod(wx_RichTextBuffer, Copy)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "obj", VTYPE_wx_RichTextBuffer, OCCUR_Once);
}

Gura_ImplementMethod(wx_RichTextBuffer, Copy)
{
	Signal &sig = env.GetSignal();
	Object_wx_RichTextBuffer *pThis = Object_wx_RichTextBuffer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxRichTextBuffer *obj = Object_wx_RichTextBuffer::GetObject(arg, 0)->GetEntity();
	pThis->GetEntity()->Copy(*obj);
	return Value::Nil;
}

Gura_DeclareMethod(wx_RichTextBuffer, CopyToClipboard)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "range", VTYPE_wx_RichTextRange, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_RichTextBuffer, CopyToClipboard)
{
	Signal &sig = env.GetSignal();
	Object_wx_RichTextBuffer *pThis = Object_wx_RichTextBuffer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxRichTextRange *range = Object_wx_RichTextRange::GetObject(arg, 0)->GetEntity();
	bool rtn = pThis->GetEntity()->CopyToClipboard(*range);
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_RichTextBuffer, DeleteRangeWithUndo)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "range", VTYPE_wx_RichTextRange, OCCUR_Once);
	DeclareArg(env, "ctrl", VTYPE_wx_RichTextCtrl, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_RichTextBuffer, DeleteRangeWithUndo)
{
	Signal &sig = env.GetSignal();
	Object_wx_RichTextBuffer *pThis = Object_wx_RichTextBuffer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxRichTextRange *range = Object_wx_RichTextRange::GetObject(arg, 0)->GetEntity();
	wxRichTextCtrl *ctrl = Object_wx_RichTextCtrl::GetObject(arg, 1)->GetEntity();
	bool rtn = pThis->GetEntity()->DeleteRangeWithUndo(*range, ctrl);
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_RichTextBuffer, Dump)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_RichTextBuffer, Dump)
{
	Signal &sig = env.GetSignal();
	Object_wx_RichTextBuffer *pThis = Object_wx_RichTextBuffer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	pThis->GetEntity()->Dump();
	return Value::Nil;
}

Gura_DeclareMethod(wx_RichTextBuffer, Dump_1)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "stream", VTYPE_wx_TextOutputStream, OCCUR_Once);
}

Gura_ImplementMethod(wx_RichTextBuffer, Dump_1)
{
	Signal &sig = env.GetSignal();
	Object_wx_RichTextBuffer *pThis = Object_wx_RichTextBuffer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxTextOutputStream *stream = Object_wx_TextOutputStream::GetObject(arg, 0)->GetEntity();
	pThis->GetEntity()->Dump(*stream);
	return Value::Nil;
}

Gura_DeclareMethod(wx_RichTextBuffer, EndAlignment)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_RichTextBuffer, EndAlignment)
{
	Signal &sig = env.GetSignal();
	Object_wx_RichTextBuffer *pThis = Object_wx_RichTextBuffer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	bool rtn = pThis->GetEntity()->EndAlignment();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_RichTextBuffer, EndAllStyles)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_RichTextBuffer, EndAllStyles)
{
	Signal &sig = env.GetSignal();
	Object_wx_RichTextBuffer *pThis = Object_wx_RichTextBuffer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	bool rtn = pThis->GetEntity()->EndAllStyles();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_RichTextBuffer, EndBatchUndo)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_RichTextBuffer, EndBatchUndo)
{
	Signal &sig = env.GetSignal();
	Object_wx_RichTextBuffer *pThis = Object_wx_RichTextBuffer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	bool rtn = pThis->GetEntity()->EndBatchUndo();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_RichTextBuffer, EndBold)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_RichTextBuffer, EndBold)
{
	Signal &sig = env.GetSignal();
	Object_wx_RichTextBuffer *pThis = Object_wx_RichTextBuffer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	bool rtn = pThis->GetEntity()->EndBold();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_RichTextBuffer, EndCharacterStyle)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_RichTextBuffer, EndCharacterStyle)
{
	Signal &sig = env.GetSignal();
	Object_wx_RichTextBuffer *pThis = Object_wx_RichTextBuffer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	bool rtn = pThis->GetEntity()->EndCharacterStyle();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_RichTextBuffer, EndFont)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_RichTextBuffer, EndFont)
{
	Signal &sig = env.GetSignal();
	Object_wx_RichTextBuffer *pThis = Object_wx_RichTextBuffer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	bool rtn = pThis->GetEntity()->EndFont();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_RichTextBuffer, EndFontSize)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_RichTextBuffer, EndFontSize)
{
	Signal &sig = env.GetSignal();
	Object_wx_RichTextBuffer *pThis = Object_wx_RichTextBuffer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	bool rtn = pThis->GetEntity()->EndFontSize();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_RichTextBuffer, EndItalic)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_RichTextBuffer, EndItalic)
{
	Signal &sig = env.GetSignal();
	Object_wx_RichTextBuffer *pThis = Object_wx_RichTextBuffer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	bool rtn = pThis->GetEntity()->EndItalic();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_RichTextBuffer, EndLeftIndent)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_RichTextBuffer, EndLeftIndent)
{
	Signal &sig = env.GetSignal();
	Object_wx_RichTextBuffer *pThis = Object_wx_RichTextBuffer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	bool rtn = pThis->GetEntity()->EndLeftIndent();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_RichTextBuffer, EndLineSpacing)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_RichTextBuffer, EndLineSpacing)
{
	Signal &sig = env.GetSignal();
	Object_wx_RichTextBuffer *pThis = Object_wx_RichTextBuffer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	bool rtn = pThis->GetEntity()->EndLineSpacing();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_RichTextBuffer, EndListStyle)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_RichTextBuffer, EndListStyle)
{
	Signal &sig = env.GetSignal();
	Object_wx_RichTextBuffer *pThis = Object_wx_RichTextBuffer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	bool rtn = pThis->GetEntity()->EndListStyle();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_RichTextBuffer, EndNumberedBullet)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_RichTextBuffer, EndNumberedBullet)
{
	Signal &sig = env.GetSignal();
	Object_wx_RichTextBuffer *pThis = Object_wx_RichTextBuffer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	bool rtn = pThis->GetEntity()->EndNumberedBullet();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_RichTextBuffer, EndParagraphSpacing)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_RichTextBuffer, EndParagraphSpacing)
{
	Signal &sig = env.GetSignal();
	Object_wx_RichTextBuffer *pThis = Object_wx_RichTextBuffer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	bool rtn = pThis->GetEntity()->EndParagraphSpacing();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_RichTextBuffer, EndParagraphStyle)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_RichTextBuffer, EndParagraphStyle)
{
	Signal &sig = env.GetSignal();
	Object_wx_RichTextBuffer *pThis = Object_wx_RichTextBuffer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	bool rtn = pThis->GetEntity()->EndParagraphStyle();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_RichTextBuffer, EndRightIndent)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_RichTextBuffer, EndRightIndent)
{
	Signal &sig = env.GetSignal();
	Object_wx_RichTextBuffer *pThis = Object_wx_RichTextBuffer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	bool rtn = pThis->GetEntity()->EndRightIndent();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_RichTextBuffer, EndStyle)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_RichTextBuffer, EndStyle)
{
	Signal &sig = env.GetSignal();
	Object_wx_RichTextBuffer *pThis = Object_wx_RichTextBuffer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	bool rtn = pThis->GetEntity()->EndStyle();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_RichTextBuffer, EndSuppressUndo)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_RichTextBuffer, EndSuppressUndo)
{
	Signal &sig = env.GetSignal();
	Object_wx_RichTextBuffer *pThis = Object_wx_RichTextBuffer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	bool rtn = pThis->GetEntity()->EndSuppressUndo();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_RichTextBuffer, EndSymbolBullet)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_RichTextBuffer, EndSymbolBullet)
{
	Signal &sig = env.GetSignal();
	Object_wx_RichTextBuffer *pThis = Object_wx_RichTextBuffer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	bool rtn = pThis->GetEntity()->EndSymbolBullet();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_RichTextBuffer, EndStandardBullet)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_RichTextBuffer, EndStandardBullet)
{
	Signal &sig = env.GetSignal();
	Object_wx_RichTextBuffer *pThis = Object_wx_RichTextBuffer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	bool rtn = pThis->GetEntity()->EndStandardBullet();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_RichTextBuffer, EndTextColour)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_RichTextBuffer, EndTextColour)
{
	Signal &sig = env.GetSignal();
	Object_wx_RichTextBuffer *pThis = Object_wx_RichTextBuffer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	bool rtn = pThis->GetEntity()->EndTextColour();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_RichTextBuffer, EndUnderline)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_RichTextBuffer, EndUnderline)
{
	Signal &sig = env.GetSignal();
	Object_wx_RichTextBuffer *pThis = Object_wx_RichTextBuffer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	bool rtn = pThis->GetEntity()->EndUnderline();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_RichTextBuffer, EndURL)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_RichTextBuffer, EndURL)
{
	Signal &sig = env.GetSignal();
	Object_wx_RichTextBuffer *pThis = Object_wx_RichTextBuffer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	bool rtn = pThis->GetEntity()->EndURL();
	return ReturnValue(env, arg, Value(rtn));
}

#if 0
Gura_DeclareClassMethod(wx_RichTextBuffer, FindHandler)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "imageType", VTYPE_number, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementClassMethod(wx_RichTextBuffer, FindHandler)
{
	Signal &sig = env.GetSignal();
	if (!CheckWxReady(sig)) return Value::Nil;
	int imageType = arg.GetInt(0);
	wxRichTextFileHandler *rtn = (wxRichTextFileHandler *)wxRichTextBuffer::FindHandler(imageType);
	return ReturnValue(env, arg, Value(new Object_wx_RichTextFileHandler(rtn, nullptr, OwnerFalse)));
}

Gura_DeclareClassMethod(wx_RichTextBuffer, FindHandler_1)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "extension", VTYPE_string, OCCUR_Once);
	DeclareArg(env, "imageType", VTYPE_number, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementClassMethod(wx_RichTextBuffer, FindHandler_1)
{
	Signal &sig = env.GetSignal();
	if (!CheckWxReady(sig)) return Value::Nil;
	wxString extension = wxString::FromUTF8(arg.GetString(0));
	int imageType = arg.GetInt(1);
	wxRichTextFileHandler *rtn = (wxRichTextFileHandler *)wxRichTextBuffer::FindHandler(extension, imageType);
	return ReturnValue(env, arg, Value(new Object_wx_RichTextFileHandler(rtn, nullptr, OwnerFalse)));
}

Gura_DeclareClassMethod(wx_RichTextBuffer, FindHandler_2)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "name", VTYPE_string, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementClassMethod(wx_RichTextBuffer, FindHandler_2)
{
	Signal &sig = env.GetSignal();
	if (!CheckWxReady(sig)) return Value::Nil;
	wxString name = wxString::FromUTF8(arg.GetString(0));
	wxRichTextFileHandler *rtn = (wxRichTextFileHandler *)wxRichTextBuffer::FindHandler(name);
	return ReturnValue(env, arg, Value(new Object_wx_RichTextFileHandler(rtn, nullptr, OwnerFalse)));
}
#endif

Gura_DeclareClassMethod(wx_RichTextBuffer, FindHandlerFilenameOrType)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "filename", VTYPE_string, OCCUR_Once);
	DeclareArg(env, "imageType", VTYPE_number, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementClassMethod(wx_RichTextBuffer, FindHandlerFilenameOrType)
{
	Signal &sig = env.GetSignal();
	if (!CheckWxReady(sig)) return Value::Nil;
	wxString filename = wxString::FromUTF8(arg.GetString(0));
	wxRichTextFileType imageType = static_cast<wxRichTextFileType>(arg.GetInt(1));
	wxRichTextFileHandler *rtn = (wxRichTextFileHandler *)wxRichTextBuffer::FindHandlerFilenameOrType(filename, imageType);
	return ReturnValue(env, arg, Value(new Object_wx_RichTextFileHandler(rtn, nullptr, OwnerFalse)));
}

Gura_DeclareMethod(wx_RichTextBuffer, GetBasicStyle)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_RichTextBuffer, GetBasicStyle)
{
	Signal &sig = env.GetSignal();
	Object_wx_RichTextBuffer *pThis = Object_wx_RichTextBuffer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	const wxTextAttrEx &rtn = pThis->GetEntity()->GetBasicStyle();
	return ReturnValue(env, arg, Value(new Object_wx_TextAttrEx(new wxTextAttrEx(rtn), nullptr, OwnerTrue)));
}

Gura_DeclareMethod(wx_RichTextBuffer, GetBatchedCommand)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_RichTextBuffer, GetBatchedCommand)
{
	Signal &sig = env.GetSignal();
#if 0
	Object_wx_RichTextBuffer *pThis = Object_wx_RichTextBuffer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxRichTextCommand *rtn = (wxRichTextCommand *)pThis->GetEntity()->GetBatchedCommand();
	return ReturnValue(env, arg, Value(new Object_wx_RichTextCommand(rtn, nullptr, OwnerFalse)));
#endif
	SetError_NotImplemented(sig);
	return Value::Nil;
}

Gura_DeclareMethod(wx_RichTextBuffer, GetCommandProcessor)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_RichTextBuffer, GetCommandProcessor)
{
	Signal &sig = env.GetSignal();
	Object_wx_RichTextBuffer *pThis = Object_wx_RichTextBuffer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxCommandProcessor *rtn = (wxCommandProcessor *)pThis->GetEntity()->GetCommandProcessor();
	return ReturnValue(env, arg, Value(new Object_wx_CommandProcessor(rtn, nullptr, OwnerFalse)));
}

Gura_DeclareMethod(wx_RichTextBuffer, GetDefaultStyle)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_RichTextBuffer, GetDefaultStyle)
{
	Signal &sig = env.GetSignal();
	Object_wx_RichTextBuffer *pThis = Object_wx_RichTextBuffer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	const wxTextAttrEx &rtn = pThis->GetEntity()->GetDefaultStyle();
	return ReturnValue(env, arg, Value(new Object_wx_TextAttrEx(new wxTextAttrEx(rtn), nullptr, OwnerTrue)));
}

Gura_DeclareClassMethod(wx_RichTextBuffer, GetExtWildcard)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "combine", VTYPE_boolean, OCCUR_ZeroOrOnce);
	DeclareArg(env, "save", VTYPE_boolean, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementClassMethod(wx_RichTextBuffer, GetExtWildcard)
{
	Signal &sig = env.GetSignal();
	if (!CheckWxReady(sig)) return Value::Nil;
	bool combine = false;
	if (arg.IsValid(0)) combine = arg.GetBoolean(0);
	bool save = false;
	if (arg.IsValid(1)) save = arg.GetBoolean(1);
	wxArrayInt types;
	wxString rtn = wxRichTextBuffer::GetExtWildcard(combine, save, &types);
	return ReturnValue(env, arg, Value::CreateList(env,
					Value(static_cast<const char *>(rtn.ToUTF8())),
					ArrayIntToValue(env, types)));
}

Gura_DeclareClassMethod(wx_RichTextBuffer, GetHandlers)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementClassMethod(wx_RichTextBuffer, GetHandlers)
{
	Signal &sig = env.GetSignal();
	if (!CheckWxReady(sig)) return Value::Nil;
	wxList &rtn = wxRichTextBuffer::GetHandlers();
	return ReturnValue(env, arg, Value(new Object_wx_List(new wxList(rtn), nullptr, OwnerTrue)));
}

Gura_DeclareClassMethod(wx_RichTextBuffer, GetRenderer)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementClassMethod(wx_RichTextBuffer, GetRenderer)
{
	Signal &sig = env.GetSignal();
	if (!CheckWxReady(sig)) return Value::Nil;
	wxRichTextRenderer *rtn = (wxRichTextRenderer *)wxRichTextBuffer::GetRenderer();
	return ReturnValue(env, arg, Value(new Object_wx_RichTextRenderer(rtn, nullptr, OwnerFalse)));
}

Gura_DeclareMethod(wx_RichTextBuffer, GetStyle)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "position", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "style", VTYPE_wx_RichTextAttr, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_RichTextBuffer, GetStyle)
{
	Signal &sig = env.GetSignal();
	Object_wx_RichTextBuffer *pThis = Object_wx_RichTextBuffer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	long position = arg.GetLong(0);
	wxRichTextAttr *style = Object_wx_RichTextAttr::GetObject(arg, 1)->GetEntity();
	bool rtn = pThis->GetEntity()->GetStyle(position, *style);
	return ReturnValue(env, arg, Value(rtn));
}

#if 0
Gura_DeclareMethod(wx_RichTextBuffer, GetStyle_1)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "position", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "style", VTYPE_wx_TextAttrEx, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_RichTextBuffer, GetStyle_1)
{
	Signal &sig = env.GetSignal();
	Object_wx_RichTextBuffer *pThis = Object_wx_RichTextBuffer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	long position = arg.GetLong(0);
	wxTextAttrEx *style = Object_wx_TextAttrEx::GetObject(arg, 1)->GetEntity();
	bool rtn = pThis->GetEntity()->GetStyle(position, *style);
	return ReturnValue(env, arg, Value(rtn));
}
#endif

Gura_DeclareMethod(wx_RichTextBuffer, GetStyleForRange)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "range", VTYPE_wx_RichTextRange, OCCUR_Once);
	DeclareArg(env, "style", VTYPE_wx_RichTextAttr, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_RichTextBuffer, GetStyleForRange)
{
	Signal &sig = env.GetSignal();
	Object_wx_RichTextBuffer *pThis = Object_wx_RichTextBuffer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxRichTextRange *range = Object_wx_RichTextRange::GetObject(arg, 0)->GetEntity();
	wxRichTextAttr *style = Object_wx_RichTextAttr::GetObject(arg, 1)->GetEntity();
	bool rtn = pThis->GetEntity()->GetStyleForRange(*range, *style);
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_RichTextBuffer, GetStyleSheet)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_RichTextBuffer, GetStyleSheet)
{
	Signal &sig = env.GetSignal();
	Object_wx_RichTextBuffer *pThis = Object_wx_RichTextBuffer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxRichTextStyleSheet *rtn = (wxRichTextStyleSheet *)pThis->GetEntity()->GetStyleSheet();
	return ReturnValue(env, arg, Value(new Object_wx_RichTextStyleSheet(rtn, nullptr, OwnerFalse)));
}

Gura_DeclareMethod(wx_RichTextBuffer, GetStyleStackSize)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_RichTextBuffer, GetStyleStackSize)
{
	Signal &sig = env.GetSignal();
	Object_wx_RichTextBuffer *pThis = Object_wx_RichTextBuffer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	size_t rtn = pThis->GetEntity()->GetStyleStackSize();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_RichTextBuffer, GetUncombinedStyle)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "position", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "style", VTYPE_wx_RichTextAttr, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_RichTextBuffer, GetUncombinedStyle)
{
	Signal &sig = env.GetSignal();
	Object_wx_RichTextBuffer *pThis = Object_wx_RichTextBuffer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	long position = arg.GetLong(0);
	wxRichTextAttr *style = Object_wx_RichTextAttr::GetObject(arg, 1)->GetEntity();
	bool rtn = pThis->GetEntity()->GetUncombinedStyle(position, *style);
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_RichTextBuffer, GetUncombinedStyle_1)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "position", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "style", VTYPE_wx_RichTextAttr, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_RichTextBuffer, GetUncombinedStyle_1)
{
	Signal &sig = env.GetSignal();
	Object_wx_RichTextBuffer *pThis = Object_wx_RichTextBuffer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	long position = arg.GetLong(0);
	wxRichTextAttr *style = Object_wx_RichTextAttr::GetObject(arg, 1)->GetEntity();
	bool rtn = pThis->GetEntity()->GetUncombinedStyle(position, *style);
	return ReturnValue(env, arg, Value(rtn));
}

#if 0
Gura_DeclareMethod(wx_RichTextBuffer, HitTest)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "dc", VTYPE_wx_DC, OCCUR_Once);
	DeclareArg(env, "pt", VTYPE_wx_Point, OCCUR_Once);
	DeclareArg(env, "textPosition", VTYPE_number, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_RichTextBuffer, HitTest)
{
	Signal &sig = env.GetSignal();
	Object_wx_RichTextBuffer *pThis = Object_wx_RichTextBuffer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxDC *dc = Object_wx_DC::GetObject(arg, 0)->GetEntity();
	wxPoint *pt = Object_wx_Point::GetObject(arg, 1)->GetEntity();
	long textPosition = arg.GetLong(2);
	int rtn = pThis->GetEntity()->HitTest(*dc, *pt, textPosition);
	return ReturnValue(env, arg, Value(rtn));
}
#endif

Gura_DeclareMethod(wx_RichTextBuffer, Init)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_RichTextBuffer, Init)
{
	Signal &sig = env.GetSignal();
	Object_wx_RichTextBuffer *pThis = Object_wx_RichTextBuffer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	pThis->GetEntity()->Init();
	return Value::Nil;
}

Gura_DeclareClassMethod(wx_RichTextBuffer, InitStandardHandlers)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementClassMethod(wx_RichTextBuffer, InitStandardHandlers)
{
	Signal &sig = env.GetSignal();
	if (!CheckWxReady(sig)) return Value::Nil;
	wxRichTextBuffer::InitStandardHandlers();
	return Value::Nil;
}

Gura_DeclareClassMethod(wx_RichTextBuffer, InsertHandler)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "handler", VTYPE_wx_RichTextFileHandler, OCCUR_Once);
}

Gura_ImplementClassMethod(wx_RichTextBuffer, InsertHandler)
{
	Signal &sig = env.GetSignal();
	if (!CheckWxReady(sig)) return Value::Nil;
	wxRichTextFileHandler *handler = Object_wx_RichTextFileHandler::GetObject(arg, 0)->GetEntity();
	wxRichTextBuffer::InsertHandler(handler);
	return Value::Nil;
}

Gura_DeclareMethod(wx_RichTextBuffer, InsertImageWithUndo)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "pos", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "imageBlock", VTYPE_wx_RichTextImageBlock, OCCUR_Once);
	DeclareArg(env, "ctrl", VTYPE_wx_RichTextCtrl, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_RichTextBuffer, InsertImageWithUndo)
{
	Signal &sig = env.GetSignal();
	Object_wx_RichTextBuffer *pThis = Object_wx_RichTextBuffer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	long pos = arg.GetLong(0);
	wxRichTextImageBlock *imageBlock = Object_wx_RichTextImageBlock::GetObject(arg, 1)->GetEntity();
	wxRichTextCtrl *ctrl = Object_wx_RichTextCtrl::GetObject(arg, 2)->GetEntity();
	bool rtn = pThis->GetEntity()->InsertImageWithUndo(pos, *imageBlock, ctrl);
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_RichTextBuffer, InsertNewlineWithUndo)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "pos", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "ctrl", VTYPE_wx_RichTextCtrl, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_RichTextBuffer, InsertNewlineWithUndo)
{
	Signal &sig = env.GetSignal();
	Object_wx_RichTextBuffer *pThis = Object_wx_RichTextBuffer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	long pos = arg.GetLong(0);
	wxRichTextCtrl *ctrl = Object_wx_RichTextCtrl::GetObject(arg, 1)->GetEntity();
	bool rtn = pThis->GetEntity()->InsertNewlineWithUndo(pos, ctrl);
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_RichTextBuffer, InsertTextWithUndo)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "pos", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "text", VTYPE_string, OCCUR_Once);
	DeclareArg(env, "ctrl", VTYPE_wx_RichTextCtrl, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_RichTextBuffer, InsertTextWithUndo)
{
	Signal &sig = env.GetSignal();
	Object_wx_RichTextBuffer *pThis = Object_wx_RichTextBuffer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	long pos = arg.GetLong(0);
	wxString text = wxString::FromUTF8(arg.GetString(1));
	wxRichTextCtrl *ctrl = Object_wx_RichTextCtrl::GetObject(arg, 2)->GetEntity();
	bool rtn = pThis->GetEntity()->InsertTextWithUndo(pos, text, ctrl);
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_RichTextBuffer, IsModified)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_RichTextBuffer, IsModified)
{
	Signal &sig = env.GetSignal();
	Object_wx_RichTextBuffer *pThis = Object_wx_RichTextBuffer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	bool rtn = pThis->GetEntity()->IsModified();
	return ReturnValue(env, arg, Value(rtn));
}

#if 0
Gura_DeclareMethod(wx_RichTextBuffer, LoadFile)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "stream", VTYPE_wx_InputStream, OCCUR_Once);
	DeclareArg(env, "type", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_RichTextBuffer, LoadFile)
{
	Signal &sig = env.GetSignal();
	Object_wx_RichTextBuffer *pThis = Object_wx_RichTextBuffer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxInputStream *stream = Object_wx_InputStream::GetObject(arg, 0)->GetEntity();
	int type = wxRICHTEXT_TYPE_ANY;
	if (arg.IsValid(1)) type = arg.GetInt(1);
	bool rtn = pThis->GetEntity()->LoadFile(*stream, type);
	return ReturnValue(env, arg, Value(rtn));
}
#endif

Gura_DeclareMethod(wx_RichTextBuffer, LoadFile)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "filename", VTYPE_string, OCCUR_Once);
	DeclareArg(env, "type", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_RichTextBuffer, LoadFile)
{
	Signal &sig = env.GetSignal();
	Object_wx_RichTextBuffer *pThis = Object_wx_RichTextBuffer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxString filename = wxString::FromUTF8(arg.GetString(0));
	wxRichTextFileType type = wxRICHTEXT_TYPE_ANY;
	if (arg.IsValid(1)) type = static_cast<wxRichTextFileType>(arg.GetInt(1));
	bool rtn = pThis->GetEntity()->LoadFile(filename, type);
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_RichTextBuffer, Modify)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "modify", VTYPE_boolean, OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_RichTextBuffer, Modify)
{
	Signal &sig = env.GetSignal();
	Object_wx_RichTextBuffer *pThis = Object_wx_RichTextBuffer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	bool modify = true;
	if (arg.IsValid(0)) modify = arg.GetBoolean(0);
	pThis->GetEntity()->Modify(modify);
	return Value::Nil;
}

Gura_DeclareMethod(wx_RichTextBuffer, NumberList)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "range", VTYPE_wx_RichTextRange, OCCUR_Once);
	DeclareArg(env, "style", VTYPE_wx_RichTextListStyleDefinition, OCCUR_Once);
	DeclareArg(env, "flags", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareArg(env, "startFrom", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareArg(env, "listLevel", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_RichTextBuffer, NumberList)
{
	Signal &sig = env.GetSignal();
	Object_wx_RichTextBuffer *pThis = Object_wx_RichTextBuffer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxRichTextRange *range = Object_wx_RichTextRange::GetObject(arg, 0)->GetEntity();
	wxRichTextListStyleDefinition *style = Object_wx_RichTextListStyleDefinition::GetObject(arg, 1)->GetEntity();
	int flags = wxRICHTEXT_SETSTYLE_WITH_UNDO;
	if (arg.IsValid(2)) flags = arg.GetInt(2);
	int startFrom = -1;
	if (arg.IsValid(3)) startFrom = arg.GetInt(3);
	int listLevel = -1;
	if (arg.IsValid(4)) listLevel = arg.GetInt(4);
	bool rtn = pThis->GetEntity()->NumberList(*range, style, flags, startFrom, listLevel);
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_RichTextBuffer, Number)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
#if 0
	DeclareArg(env, "range", VTYPE_wx_RichTextRange, OCCUR_Once);
	DeclareArg(env, "styleName", VTYPE_string, OCCUR_Once);
	DeclareArg(env, "flags", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareArg(env, "startFrom", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareArg(env, "listLevel", VTYPE_number, OCCUR_ZeroOrOnce);
#endif
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_RichTextBuffer, Number)
{
	Signal &sig = env.GetSignal();
#if 0
	Object_wx_RichTextBuffer *pThis = Object_wx_RichTextBuffer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxRichTextRange *range = Object_wx_RichTextRange::GetObject(arg, 0)->GetEntity();
	wxString styleName = wxString::FromUTF8(arg.GetString(1));
	int flags = wxRICHTEXT_SETSTYLE_WITH_UNDO;
	if (arg.IsValid(2)) flags = arg.GetInt(2);
	int startFrom = -1;
	if (arg.IsValid(3)) startFrom = arg.GetInt(3);
	int listLevel = -1;
	if (arg.IsValid(4)) listLevel = arg.GetInt(4);
	bool rtn = pThis->GetEntity()->Number(*range, styleName, flags, startFrom, listLevel);
	return ReturnValue(env, arg, Value(rtn));
#endif
	SetError_NotImplemented(sig);
	return Value::Nil;
}

Gura_DeclareMethod(wx_RichTextBuffer, PasteFromClipboard)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "position", VTYPE_number, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_RichTextBuffer, PasteFromClipboard)
{
	Signal &sig = env.GetSignal();
	Object_wx_RichTextBuffer *pThis = Object_wx_RichTextBuffer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	long position = arg.GetLong(0);
	bool rtn = pThis->GetEntity()->PasteFromClipboard(position);
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_RichTextBuffer, PromoteList)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "promoteBy", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "range", VTYPE_wx_RichTextRange, OCCUR_Once);
	DeclareArg(env, "style", VTYPE_wx_RichTextListStyleDefinition, OCCUR_Once);
	DeclareArg(env, "flags", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareArg(env, "listLevel", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_RichTextBuffer, PromoteList)
{
	Signal &sig = env.GetSignal();
	Object_wx_RichTextBuffer *pThis = Object_wx_RichTextBuffer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	int promoteBy = arg.GetInt(0);
	wxRichTextRange *range = Object_wx_RichTextRange::GetObject(arg, 1)->GetEntity();
	wxRichTextListStyleDefinition *style = Object_wx_RichTextListStyleDefinition::GetObject(arg, 2)->GetEntity();
	int flags = wxRICHTEXT_SETSTYLE_WITH_UNDO;
	if (arg.IsValid(3)) flags = arg.GetInt(3);
	int listLevel = -1;
	if (arg.IsValid(4)) listLevel = arg.GetInt(4);
	bool rtn = pThis->GetEntity()->PromoteList(promoteBy, *range, style, flags, listLevel);
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_RichTextBuffer, PromoteList_1)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "promoteBy", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "range", VTYPE_wx_RichTextRange, OCCUR_Once);
	DeclareArg(env, "styleName", VTYPE_string, OCCUR_Once);
	DeclareArg(env, "flags", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareArg(env, "listLevel", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_RichTextBuffer, PromoteList_1)
{
	Signal &sig = env.GetSignal();
	Object_wx_RichTextBuffer *pThis = Object_wx_RichTextBuffer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	int promoteBy = arg.GetInt(0);
	wxRichTextRange *range = Object_wx_RichTextRange::GetObject(arg, 1)->GetEntity();
	wxString styleName = wxString::FromUTF8(arg.GetString(2));
	int flags = wxRICHTEXT_SETSTYLE_WITH_UNDO;
	if (arg.IsValid(3)) flags = arg.GetInt(3);
	int listLevel = -1;
	if (arg.IsValid(4)) listLevel = arg.GetInt(4);
	bool rtn = pThis->GetEntity()->PromoteList(promoteBy, *range, styleName, flags, listLevel);
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_RichTextBuffer, RemoveEventHandler)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "handler", VTYPE_wx_EvtHandler, OCCUR_Once);
	DeclareArg(env, "deleteHandler", VTYPE_boolean, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_RichTextBuffer, RemoveEventHandler)
{
	Signal &sig = env.GetSignal();
	Object_wx_RichTextBuffer *pThis = Object_wx_RichTextBuffer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxEvtHandler *handler = Object_wx_EvtHandler::GetObject(arg, 0)->GetEntity();
	bool deleteHandler = false;
	if (arg.IsValid(1)) deleteHandler = arg.GetBoolean(1);
	bool rtn = pThis->GetEntity()->RemoveEventHandler(handler, deleteHandler);
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareClassMethod(wx_RichTextBuffer, RemoveHandler)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "name", VTYPE_string, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementClassMethod(wx_RichTextBuffer, RemoveHandler)
{
	Signal &sig = env.GetSignal();
	if (!CheckWxReady(sig)) return Value::Nil;
	wxString name = wxString::FromUTF8(arg.GetString(0));
	bool rtn = wxRichTextBuffer::RemoveHandler(name);
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_RichTextBuffer, ResetAndClearCommands)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_RichTextBuffer, ResetAndClearCommands)
{
	Signal &sig = env.GetSignal();
	Object_wx_RichTextBuffer *pThis = Object_wx_RichTextBuffer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	pThis->GetEntity()->ResetAndClearCommands();
	return Value::Nil;
}

#if 0
Gura_DeclareMethod(wx_RichTextBuffer, SaveFile)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "stream", VTYPE_wx_OutputStream, OCCUR_Once);
	DeclareArg(env, "type", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_RichTextBuffer, SaveFile)
{
	Signal &sig = env.GetSignal();
	Object_wx_RichTextBuffer *pThis = Object_wx_RichTextBuffer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxOutputStream *stream = Object_wx_OutputStream::GetObject(arg, 0)->GetEntity();
	int type = wxRICHTEXT_TYPE_ANY;
	if (arg.IsValid(1)) type = arg.GetInt(1);
	bool rtn = pThis->GetEntity()->SaveFile(*stream, type);
	return ReturnValue(env, arg, Value(rtn));
}
#endif

Gura_DeclareMethod(wx_RichTextBuffer, SaveFile)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "filename", VTYPE_string, OCCUR_Once);
	DeclareArg(env, "type", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_RichTextBuffer, SaveFile)
{
	Signal &sig = env.GetSignal();
	Object_wx_RichTextBuffer *pThis = Object_wx_RichTextBuffer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxString filename = wxString::FromUTF8(arg.GetString(0));
	wxRichTextFileType type = wxRICHTEXT_TYPE_ANY;
	if (arg.IsValid(1)) type = static_cast<wxRichTextFileType>(arg.GetInt(1));
	bool rtn = pThis->GetEntity()->SaveFile(filename, type);
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_RichTextBuffer, SetBasicStyle)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "style", VTYPE_wx_RichTextAttr, OCCUR_Once);
}

Gura_ImplementMethod(wx_RichTextBuffer, SetBasicStyle)
{
	Signal &sig = env.GetSignal();
	Object_wx_RichTextBuffer *pThis = Object_wx_RichTextBuffer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxRichTextAttr *style = Object_wx_RichTextAttr::GetObject(arg, 0)->GetEntity();
	pThis->GetEntity()->SetBasicStyle(*style);
	return Value::Nil;
}

Gura_DeclareMethod(wx_RichTextBuffer, SetBasicStyle_1)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "style", VTYPE_wx_TextAttrEx, OCCUR_Once);
}

Gura_ImplementMethod(wx_RichTextBuffer, SetBasicStyle_1)
{
	Signal &sig = env.GetSignal();
	Object_wx_RichTextBuffer *pThis = Object_wx_RichTextBuffer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxTextAttrEx *style = Object_wx_TextAttrEx::GetObject(arg, 0)->GetEntity();
	pThis->GetEntity()->SetBasicStyle(*style);
	return Value::Nil;
}

Gura_DeclareMethod(wx_RichTextBuffer, SetDefaultStyle)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "style", VTYPE_wx_TextAttrEx, OCCUR_Once);
}

Gura_ImplementMethod(wx_RichTextBuffer, SetDefaultStyle)
{
	Signal &sig = env.GetSignal();
	Object_wx_RichTextBuffer *pThis = Object_wx_RichTextBuffer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxTextAttrEx *style = Object_wx_TextAttrEx::GetObject(arg, 0)->GetEntity();
	pThis->GetEntity()->SetDefaultStyle(*style);
	return Value::Nil;
}

Gura_DeclareMethod(wx_RichTextBuffer, SetListStyle)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "range", VTYPE_wx_RichTextRange, OCCUR_Once);
	DeclareArg(env, "style", VTYPE_wx_RichTextListStyleDefinition, OCCUR_Once);
	DeclareArg(env, "flags", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareArg(env, "startFrom", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareArg(env, "listLevel", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_RichTextBuffer, SetListStyle)
{
	Signal &sig = env.GetSignal();
	Object_wx_RichTextBuffer *pThis = Object_wx_RichTextBuffer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxRichTextRange *range = Object_wx_RichTextRange::GetObject(arg, 0)->GetEntity();
	wxRichTextListStyleDefinition *style = Object_wx_RichTextListStyleDefinition::GetObject(arg, 1)->GetEntity();
	int flags = wxRICHTEXT_SETSTYLE_WITH_UNDO;
	if (arg.IsValid(2)) flags = arg.GetInt(2);
	int startFrom = -1;
	if (arg.IsValid(3)) startFrom = arg.GetInt(3);
	int listLevel = -1;
	if (arg.IsValid(4)) listLevel = arg.GetInt(4);
	bool rtn = pThis->GetEntity()->SetListStyle(*range, style, flags, startFrom, listLevel);
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_RichTextBuffer, SetListStyle_1)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "range", VTYPE_wx_RichTextRange, OCCUR_Once);
	DeclareArg(env, "styleName", VTYPE_string, OCCUR_Once);
	DeclareArg(env, "flags", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareArg(env, "startFrom", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareArg(env, "listLevel", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_RichTextBuffer, SetListStyle_1)
{
	Signal &sig = env.GetSignal();
	Object_wx_RichTextBuffer *pThis = Object_wx_RichTextBuffer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxRichTextRange *range = Object_wx_RichTextRange::GetObject(arg, 0)->GetEntity();
	wxString styleName = wxString::FromUTF8(arg.GetString(1));
	int flags = wxRICHTEXT_SETSTYLE_WITH_UNDO;
	if (arg.IsValid(2)) flags = arg.GetInt(2);
	int startFrom = -1;
	if (arg.IsValid(3)) startFrom = arg.GetInt(3);
	int listLevel = -1;
	if (arg.IsValid(4)) listLevel = arg.GetInt(4);
	bool rtn = pThis->GetEntity()->SetListStyle(*range, styleName, flags, startFrom, listLevel);
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareClassMethod(wx_RichTextBuffer, SetRenderer)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "renderer", VTYPE_wx_RichTextRenderer, OCCUR_Once);
}

Gura_ImplementClassMethod(wx_RichTextBuffer, SetRenderer)
{
	Signal &sig = env.GetSignal();
	if (!CheckWxReady(sig)) return Value::Nil;
	wxRichTextRenderer *renderer = Object_wx_RichTextRenderer::GetObject(arg, 0)->GetEntity();
	wxRichTextBuffer::SetRenderer(renderer);
	return Value::Nil;
}

Gura_DeclareMethod(wx_RichTextBuffer, SetStyle)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "range", VTYPE_wx_RichTextRange, OCCUR_Once);
	DeclareArg(env, "style", VTYPE_wx_RichTextAttr, OCCUR_Once);
	DeclareArg(env, "flags", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_RichTextBuffer, SetStyle)
{
	Signal &sig = env.GetSignal();
	Object_wx_RichTextBuffer *pThis = Object_wx_RichTextBuffer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxRichTextRange *range = Object_wx_RichTextRange::GetObject(arg, 0)->GetEntity();
	wxRichTextAttr *style = Object_wx_RichTextAttr::GetObject(arg, 1)->GetEntity();
	int flags = wxRICHTEXT_SETSTYLE_WITH_UNDO;
	if (arg.IsValid(2)) flags = arg.GetInt(2);
	bool rtn = pThis->GetEntity()->SetStyle(*range, *style, flags);
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_RichTextBuffer, SetStyle_1)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "range", VTYPE_wx_RichTextRange, OCCUR_Once);
	DeclareArg(env, "style", VTYPE_wx_TextAttrEx, OCCUR_Once);
	DeclareArg(env, "flags", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_RichTextBuffer, SetStyle_1)
{
	Signal &sig = env.GetSignal();
	Object_wx_RichTextBuffer *pThis = Object_wx_RichTextBuffer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxRichTextRange *range = Object_wx_RichTextRange::GetObject(arg, 0)->GetEntity();
	wxTextAttrEx *style = Object_wx_TextAttrEx::GetObject(arg, 1)->GetEntity();
	int flags = wxRICHTEXT_SETSTYLE_WITH_UNDO;
	if (arg.IsValid(2)) flags = arg.GetInt(2);
	bool rtn = pThis->GetEntity()->SetStyle(*range, *style, flags);
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_RichTextBuffer, SetStyleSheet)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "styleSheet", VTYPE_wx_RichTextStyleSheet, OCCUR_Once);
}

Gura_ImplementMethod(wx_RichTextBuffer, SetStyleSheet)
{
	Signal &sig = env.GetSignal();
	Object_wx_RichTextBuffer *pThis = Object_wx_RichTextBuffer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxRichTextStyleSheet *styleSheet = Object_wx_RichTextStyleSheet::GetObject(arg, 0)->GetEntity();
	pThis->GetEntity()->SetStyleSheet(styleSheet);
	return Value::Nil;
}

Gura_DeclareMethod(wx_RichTextBuffer, SubmitAction)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "action", VTYPE_wx_RichTextAction, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_RichTextBuffer, SubmitAction)
{
	Signal &sig = env.GetSignal();
	Object_wx_RichTextBuffer *pThis = Object_wx_RichTextBuffer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxRichTextAction *action = Object_wx_RichTextAction::GetObject(arg, 0)->GetEntity();
	bool rtn = pThis->GetEntity()->SubmitAction(action);
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_RichTextBuffer, SuppressingUndo)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_RichTextBuffer, SuppressingUndo)
{
	Signal &sig = env.GetSignal();
	Object_wx_RichTextBuffer *pThis = Object_wx_RichTextBuffer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	bool rtn = pThis->GetEntity()->SuppressingUndo();
	return ReturnValue(env, arg, Value(rtn));
}

//----------------------------------------------------------------------------
// Object implementation for wxRichTextBuffer
//----------------------------------------------------------------------------
Object_wx_RichTextBuffer::~Object_wx_RichTextBuffer()
{
}

Object *Object_wx_RichTextBuffer::Clone() const
{
	return nullptr;
}

String Object_wx_RichTextBuffer::ToString(bool exprFlag)
{
	String rtn("<wx.RichTextBuffer:");
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
// Class implementation for wxRichTextBuffer
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_RichTextBuffer)
{
	Gura_AssignFunction(RichTextBuffer);
	Gura_AssignFunction(RichTextBufferEmpty);
	Gura_AssignMethod(wx_RichTextBuffer, AddEventHandler);
	Gura_AssignMethod(wx_RichTextBuffer, AddHandler);
	Gura_AssignMethod(wx_RichTextBuffer, AddParagraph);
	Gura_AssignMethod(wx_RichTextBuffer, BatchingUndo);
	Gura_AssignMethod(wx_RichTextBuffer, BeginAlignment);
	Gura_AssignMethod(wx_RichTextBuffer, BeginBatchUndo);
	Gura_AssignMethod(wx_RichTextBuffer, BeginBold);
	Gura_AssignMethod(wx_RichTextBuffer, BeginCharacterStyle);
	Gura_AssignMethod(wx_RichTextBuffer, BeginFont);
	Gura_AssignMethod(wx_RichTextBuffer, BeginFontSize);
	Gura_AssignMethod(wx_RichTextBuffer, BeginItalic);
	Gura_AssignMethod(wx_RichTextBuffer, BeginLeftIndent);
	Gura_AssignMethod(wx_RichTextBuffer, BeginLineSpacing);
	Gura_AssignMethod(wx_RichTextBuffer, BeginListStyle);
	Gura_AssignMethod(wx_RichTextBuffer, BeginNumberedBullet);
	Gura_AssignMethod(wx_RichTextBuffer, BeginParagraphSpacing);
	Gura_AssignMethod(wx_RichTextBuffer, BeginParagraphStyle);
	Gura_AssignMethod(wx_RichTextBuffer, BeginRightIndent);
	Gura_AssignMethod(wx_RichTextBuffer, BeginStyle);
	Gura_AssignMethod(wx_RichTextBuffer, BeginSuppressUndo);
	Gura_AssignMethod(wx_RichTextBuffer, BeginStandardBullet);
	Gura_AssignMethod(wx_RichTextBuffer, BeginSymbolBullet);
	Gura_AssignMethod(wx_RichTextBuffer, BeginTextColour);
	Gura_AssignMethod(wx_RichTextBuffer, BeginUnderline);
	Gura_AssignMethod(wx_RichTextBuffer, BeginURL);
	Gura_AssignMethod(wx_RichTextBuffer, CanPasteFromClipboard);
	Gura_AssignMethod(wx_RichTextBuffer, CleanUpHandlers);
	Gura_AssignMethod(wx_RichTextBuffer, Clear);
	Gura_AssignMethod(wx_RichTextBuffer, ClearListStyle);
	Gura_AssignMethod(wx_RichTextBuffer, ClearListStyle_1);
	Gura_AssignMethod(wx_RichTextBuffer, ClearStyleStack);
	Gura_AssignMethod(wx_RichTextBuffer, Clone);
	Gura_AssignMethod(wx_RichTextBuffer, Copy);
	Gura_AssignMethod(wx_RichTextBuffer, CopyToClipboard);
	Gura_AssignMethod(wx_RichTextBuffer, DeleteRangeWithUndo);
	Gura_AssignMethod(wx_RichTextBuffer, Dump);
	Gura_AssignMethod(wx_RichTextBuffer, Dump_1);
	Gura_AssignMethod(wx_RichTextBuffer, EndAlignment);
	Gura_AssignMethod(wx_RichTextBuffer, EndAllStyles);
	Gura_AssignMethod(wx_RichTextBuffer, EndBatchUndo);
	Gura_AssignMethod(wx_RichTextBuffer, EndBold);
	Gura_AssignMethod(wx_RichTextBuffer, EndCharacterStyle);
	Gura_AssignMethod(wx_RichTextBuffer, EndFont);
	Gura_AssignMethod(wx_RichTextBuffer, EndFontSize);
	Gura_AssignMethod(wx_RichTextBuffer, EndItalic);
	Gura_AssignMethod(wx_RichTextBuffer, EndLeftIndent);
	Gura_AssignMethod(wx_RichTextBuffer, EndLineSpacing);
	Gura_AssignMethod(wx_RichTextBuffer, EndListStyle);
	Gura_AssignMethod(wx_RichTextBuffer, EndNumberedBullet);
	Gura_AssignMethod(wx_RichTextBuffer, EndParagraphSpacing);
	Gura_AssignMethod(wx_RichTextBuffer, EndParagraphStyle);
	Gura_AssignMethod(wx_RichTextBuffer, EndRightIndent);
	Gura_AssignMethod(wx_RichTextBuffer, EndStyle);
	Gura_AssignMethod(wx_RichTextBuffer, EndSuppressUndo);
	Gura_AssignMethod(wx_RichTextBuffer, EndSymbolBullet);
	Gura_AssignMethod(wx_RichTextBuffer, EndStandardBullet);
	Gura_AssignMethod(wx_RichTextBuffer, EndTextColour);
	Gura_AssignMethod(wx_RichTextBuffer, EndUnderline);
	Gura_AssignMethod(wx_RichTextBuffer, EndURL);
	//Gura_AssignMethod(wx_RichTextBuffer, FindHandler);
	//Gura_AssignMethod(wx_RichTextBuffer, FindHandler_1);
	//Gura_AssignMethod(wx_RichTextBuffer, FindHandler_2);
	Gura_AssignMethod(wx_RichTextBuffer, FindHandlerFilenameOrType);
	Gura_AssignMethod(wx_RichTextBuffer, GetBasicStyle);
	Gura_AssignMethod(wx_RichTextBuffer, GetBatchedCommand);
	Gura_AssignMethod(wx_RichTextBuffer, GetCommandProcessor);
	Gura_AssignMethod(wx_RichTextBuffer, GetDefaultStyle);
	Gura_AssignMethod(wx_RichTextBuffer, GetExtWildcard);
	Gura_AssignMethod(wx_RichTextBuffer, GetHandlers);
	Gura_AssignMethod(wx_RichTextBuffer, GetRenderer);
	Gura_AssignMethod(wx_RichTextBuffer, GetStyle);
	//Gura_AssignMethod(wx_RichTextBuffer, GetStyle_1);
	Gura_AssignMethod(wx_RichTextBuffer, GetStyleForRange);
	Gura_AssignMethod(wx_RichTextBuffer, GetStyleSheet);
	Gura_AssignMethod(wx_RichTextBuffer, GetStyleStackSize);
	Gura_AssignMethod(wx_RichTextBuffer, GetUncombinedStyle);
	Gura_AssignMethod(wx_RichTextBuffer, GetUncombinedStyle_1);
	//Gura_AssignMethod(wx_RichTextBuffer, HitTest);
	Gura_AssignMethod(wx_RichTextBuffer, Init);
	Gura_AssignMethod(wx_RichTextBuffer, InitStandardHandlers);
	Gura_AssignMethod(wx_RichTextBuffer, InsertHandler);
	Gura_AssignMethod(wx_RichTextBuffer, InsertImageWithUndo);
	Gura_AssignMethod(wx_RichTextBuffer, InsertNewlineWithUndo);
	Gura_AssignMethod(wx_RichTextBuffer, InsertTextWithUndo);
	Gura_AssignMethod(wx_RichTextBuffer, IsModified);
	Gura_AssignMethod(wx_RichTextBuffer, LoadFile);
	//Gura_AssignMethod(wx_RichTextBuffer, LoadFile_1);
	Gura_AssignMethod(wx_RichTextBuffer, Modify);
	Gura_AssignMethod(wx_RichTextBuffer, NumberList);
	Gura_AssignMethod(wx_RichTextBuffer, Number);
	Gura_AssignMethod(wx_RichTextBuffer, PasteFromClipboard);
	Gura_AssignMethod(wx_RichTextBuffer, PromoteList);
	Gura_AssignMethod(wx_RichTextBuffer, PromoteList_1);
	Gura_AssignMethod(wx_RichTextBuffer, RemoveEventHandler);
	Gura_AssignMethod(wx_RichTextBuffer, RemoveHandler);
	Gura_AssignMethod(wx_RichTextBuffer, ResetAndClearCommands);
	Gura_AssignMethod(wx_RichTextBuffer, SaveFile);
	//Gura_AssignMethod(wx_RichTextBuffer, SaveFile_1);
	Gura_AssignMethod(wx_RichTextBuffer, SetBasicStyle);
	Gura_AssignMethod(wx_RichTextBuffer, SetBasicStyle_1);
	Gura_AssignMethod(wx_RichTextBuffer, SetDefaultStyle);
	Gura_AssignMethod(wx_RichTextBuffer, SetListStyle);
	Gura_AssignMethod(wx_RichTextBuffer, SetListStyle_1);
	Gura_AssignMethod(wx_RichTextBuffer, SetRenderer);
	Gura_AssignMethod(wx_RichTextBuffer, SetStyle);
	Gura_AssignMethod(wx_RichTextBuffer, SetStyle_1);
	Gura_AssignMethod(wx_RichTextBuffer, SetStyleSheet);
	Gura_AssignMethod(wx_RichTextBuffer, SubmitAction);
	Gura_AssignMethod(wx_RichTextBuffer, SuppressingUndo);
}

Gura_ImplementDescendantCreator(wx_RichTextBuffer)
{
	return new Object_wx_RichTextBuffer((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
