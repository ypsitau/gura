//----------------------------------------------------------------------------
// wxStreamBuffer
// extracted from stream.tex
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

//----------------------------------------------------------------------------
// Class derivation
//----------------------------------------------------------------------------
class wx_StreamBuffer: public wxStreamBuffer, public GuraObjectObserver {
private:
	//Gura::Signal *_pSig;
	Object_wx_StreamBuffer *_pObj;
public:
	inline wx_StreamBuffer(wxStreamBase& stream, BufMode mode) : wxStreamBuffer(stream, mode), _pObj(nullptr) {}
	inline wx_StreamBuffer(BufMode mode) : wxStreamBuffer(mode), _pObj(nullptr) {}
	inline wx_StreamBuffer(const wxStreamBuffer& buffer) : wxStreamBuffer(buffer), _pObj(nullptr) {}
	//inline wx_StreamBuffer() : wxStreamBuffer(), _pObj(nullptr) {}
	~wx_StreamBuffer();
	inline void AssocWithGura(Object_wx_StreamBuffer *pObj) {
		_pObj = pObj;
	}
	// virtual function of GuraObjectObserver
	virtual void GuraObjectDeleted();
};

wx_StreamBuffer::~wx_StreamBuffer()
{
	if (_pObj != nullptr) _pObj->InvalidateEntity();
}

void wx_StreamBuffer::GuraObjectDeleted()
{
	_pObj = nullptr;
}

//----------------------------------------------------------------------------
// Gura interfaces for wxStreamBuffer
//----------------------------------------------------------------------------
Gura_DeclareFunction(StreamBuffer)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	SetClassToConstruct(Gura_UserClass(wx_StreamBuffer));
	DeclareArg(env, "stream", VTYPE_wx_StreamBase, OCCUR_Once);
	DeclareArg(env, "mode", VTYPE_number, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(StreamBuffer)
{
	Signal &sig = env.GetSignal();
	if (!CheckWxReady(sig)) return Value::Nil;
	wxStreamBase *stream = Object_wx_StreamBase::GetObject(arg, 0)->GetEntity();
	wxStreamBuffer::BufMode mode = static_cast<wxStreamBuffer::BufMode>(arg.GetInt(1));
	wx_StreamBuffer *pEntity = new wx_StreamBuffer(*stream, mode);
	Object_wx_StreamBuffer *pObj = Object_wx_StreamBuffer::GetObjectThis(arg);
	if (pObj == nullptr) {
		pObj = new Object_wx_StreamBuffer(pEntity, pEntity, OwnerFalse);
		pEntity->AssocWithGura(pObj);
		return ReturnValue(env, arg, Value(pObj));
	}
	pObj->SetEntity(pEntity, pEntity, OwnerFalse);
	pEntity->AssocWithGura(pObj);
	return ReturnValue(env, arg, arg.GetValueThis());
}

Gura_DeclareFunction(StreamBuffer_1)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	SetClassToConstruct(Gura_UserClass(wx_StreamBuffer));
	DeclareArg(env, "mode", VTYPE_number, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(StreamBuffer_1)
{
	Signal &sig = env.GetSignal();
	if (!CheckWxReady(sig)) return Value::Nil;
	wxStreamBuffer::BufMode mode = static_cast<wxStreamBuffer::BufMode>(arg.GetInt(0));
	wx_StreamBuffer *pEntity = new wx_StreamBuffer(mode);
	Object_wx_StreamBuffer *pObj = Object_wx_StreamBuffer::GetObjectThis(arg);
	if (pObj == nullptr) {
		pObj = new Object_wx_StreamBuffer(pEntity, pEntity, OwnerFalse);
		pEntity->AssocWithGura(pObj);
		return ReturnValue(env, arg, Value(pObj));
	}
	pObj->SetEntity(pEntity, pEntity, OwnerFalse);
	pEntity->AssocWithGura(pObj);
	return ReturnValue(env, arg, arg.GetValueThis());
}

Gura_DeclareFunction(StreamBuffer_2)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	SetClassToConstruct(Gura_UserClass(wx_StreamBuffer));
	DeclareArg(env, "buffer", VTYPE_wx_StreamBuffer, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(StreamBuffer_2)
{
	Signal &sig = env.GetSignal();
	if (!CheckWxReady(sig)) return Value::Nil;
	wxStreamBuffer *buffer = Object_wx_StreamBuffer::GetObject(arg, 0)->GetEntity();
	wx_StreamBuffer *pEntity = new wx_StreamBuffer(*buffer);
	Object_wx_StreamBuffer *pObj = Object_wx_StreamBuffer::GetObjectThis(arg);
	if (pObj == nullptr) {
		pObj = new Object_wx_StreamBuffer(pEntity, pEntity, OwnerFalse);
		pEntity->AssocWithGura(pObj);
		return ReturnValue(env, arg, Value(pObj));
	}
	pObj->SetEntity(pEntity, pEntity, OwnerFalse);
	pEntity->AssocWithGura(pObj);
	return ReturnValue(env, arg, arg.GetValueThis());
}

Gura_DeclareFunction(StreamBufferEmpty)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
#if 0
	SetClassToConstruct(Gura_UserClass(wx_StreamBuffer));
	DeclareBlock(OCCUR_ZeroOrOnce);
#endif
}

Gura_ImplementFunction(StreamBufferEmpty)
{
	Signal &sig = env.GetSignal();
	if (!CheckWxReady(sig)) return Value::Nil;
#if 0
	wx_StreamBuffer *pEntity = new wx_StreamBuffer();
	Object_wx_StreamBuffer *pObj = Object_wx_StreamBuffer::GetObjectThis(arg);
	if (pObj == nullptr) {
		pObj = new Object_wx_StreamBuffer(pEntity, pEntity, OwnerFalse);
		pEntity->AssocWithGura(pObj);
		return ReturnValue(env, arg, Value(pObj));
	}
	pObj->SetEntity(pEntity, pEntity, OwnerFalse);
	pEntity->AssocWithGura(pObj);
	return ReturnValue(env, arg, arg.GetValueThis());
#endif
	SetError_NotImplemented(sig);
	return Value::Nil;
}

Gura_DeclareMethod(wx_StreamBuffer, Read)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
#if 0
	DeclareArg(env, "buffer", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "size", VTYPE_number, OCCUR_Once);
#endif
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_StreamBuffer, Read)
{
	Signal &sig = env.GetSignal();
#if 0
	Object_wx_StreamBuffer *pThis = Object_wx_StreamBuffer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	int buffer = arg.GetInt(0);
	size_t size = arg.GetSizeT(1);
	size_t rtn = pThis->GetEntity()->Read(buffer, size);
	return ReturnValue(env, arg, Value(rtn));
#endif
	SetError_NotImplemented(sig);
	return Value::Nil;
}

Gura_DeclareMethod(wx_StreamBuffer, Read_1)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "buffer", VTYPE_wx_StreamBuffer, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_StreamBuffer, Read_1)
{
	Signal &sig = env.GetSignal();
	Object_wx_StreamBuffer *pThis = Object_wx_StreamBuffer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxStreamBuffer *buffer = Object_wx_StreamBuffer::GetObject(arg, 0)->GetEntity();
	size_t rtn = pThis->GetEntity()->Read(buffer);
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_StreamBuffer, Write)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
#if 0
	DeclareArg(env, "buffer", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "size", VTYPE_number, OCCUR_Once);
#endif
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_StreamBuffer, Write)
{
	Signal &sig = env.GetSignal();
#if 0
	Object_wx_StreamBuffer *pThis = Object_wx_StreamBuffer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	int buffer = arg.GetInt(0);
	size_t size = arg.GetSizeT(1);
	size_t rtn = pThis->GetEntity()->Write(buffer, size);
	return ReturnValue(env, arg, Value(rtn));
#endif
	SetError_NotImplemented(sig);
	return Value::Nil;
}

Gura_DeclareMethod(wx_StreamBuffer, Write_1)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "buffer", VTYPE_wx_StreamBuffer, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_StreamBuffer, Write_1)
{
	Signal &sig = env.GetSignal();
	Object_wx_StreamBuffer *pThis = Object_wx_StreamBuffer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxStreamBuffer *buffer = Object_wx_StreamBuffer::GetObject(arg, 0)->GetEntity();
	size_t rtn = pThis->GetEntity()->Write(buffer);
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_StreamBuffer, GetChar)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_StreamBuffer, GetChar)
{
	Signal &sig = env.GetSignal();
	Object_wx_StreamBuffer *pThis = Object_wx_StreamBuffer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	char rtn = pThis->GetEntity()->GetChar();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_StreamBuffer, PutChar)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "c", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StreamBuffer, PutChar)
{
	Signal &sig = env.GetSignal();
	Object_wx_StreamBuffer *pThis = Object_wx_StreamBuffer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	char c = arg.GetChar(0);
	pThis->GetEntity()->PutChar(c);
	return Value::Nil;
}

Gura_DeclareMethod(wx_StreamBuffer, Tell)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_StreamBuffer, Tell)
{
	Signal &sig = env.GetSignal();
	Object_wx_StreamBuffer *pThis = Object_wx_StreamBuffer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	off_t rtn = pThis->GetEntity()->Tell();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_StreamBuffer, Seek)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "pos", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "mode", VTYPE_number, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_StreamBuffer, Seek)
{
	Signal &sig = env.GetSignal();
	Object_wx_StreamBuffer *pThis = Object_wx_StreamBuffer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	off_t pos = static_cast<off_t>(arg.GetLong(0));
	wxSeekMode mode = static_cast<wxSeekMode>(arg.GetInt(1));
	off_t rtn = pThis->GetEntity()->Seek(pos, mode);
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_StreamBuffer, ResetBuffer)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StreamBuffer, ResetBuffer)
{
	Signal &sig = env.GetSignal();
	Object_wx_StreamBuffer *pThis = Object_wx_StreamBuffer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	pThis->GetEntity()->ResetBuffer();
	return Value::Nil;
}

Gura_DeclareMethod(wx_StreamBuffer, SetBufferIO)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
#if 0
	DeclareArg(env, "buffer_start", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "buffer_end", VTYPE_number, OCCUR_Once);
#endif
}

Gura_ImplementMethod(wx_StreamBuffer, SetBufferIO)
{
	Signal &sig = env.GetSignal();
#if 0
	Object_wx_StreamBuffer *pThis = Object_wx_StreamBuffer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	char buffer_start = arg.GetChar(0);
	char buffer_end = arg.GetChar(1);
	pThis->GetEntity()->SetBufferIO(buffer_start, buffer_end);
	return Value::Nil;
#endif
	SetError_NotImplemented(sig);
	return Value::Nil;
}

Gura_DeclareMethod(wx_StreamBuffer, SetBufferIO_1)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "bufsize", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StreamBuffer, SetBufferIO_1)
{
	Signal &sig = env.GetSignal();
	Object_wx_StreamBuffer *pThis = Object_wx_StreamBuffer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	size_t bufsize = arg.GetSizeT(0);
	pThis->GetEntity()->SetBufferIO(bufsize);
	return Value::Nil;
}

Gura_DeclareMethod(wx_StreamBuffer, GetBufferStart)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StreamBuffer, GetBufferStart)
{
	Signal &sig = env.GetSignal();
	Object_wx_StreamBuffer *pThis = Object_wx_StreamBuffer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	pThis->GetEntity()->GetBufferStart();
	return Value::Nil;
}

Gura_DeclareMethod(wx_StreamBuffer, GetBufferEnd)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StreamBuffer, GetBufferEnd)
{
	Signal &sig = env.GetSignal();
	Object_wx_StreamBuffer *pThis = Object_wx_StreamBuffer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	pThis->GetEntity()->GetBufferEnd();
	return Value::Nil;
}

Gura_DeclareMethod(wx_StreamBuffer, GetBufferPos)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_StreamBuffer, GetBufferPos)
{
	Signal &sig = env.GetSignal();
	Object_wx_StreamBuffer *pThis = Object_wx_StreamBuffer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	pThis->GetEntity()->GetBufferPos();
	return Value::Nil;
}

Gura_DeclareMethod(wx_StreamBuffer, GetIntPosition)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_StreamBuffer, GetIntPosition)
{
	Signal &sig = env.GetSignal();
	Object_wx_StreamBuffer *pThis = Object_wx_StreamBuffer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	off_t rtn = pThis->GetEntity()->GetIntPosition();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_StreamBuffer, SetIntPosition)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "pos", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_StreamBuffer, SetIntPosition)
{
	Signal &sig = env.GetSignal();
	Object_wx_StreamBuffer *pThis = Object_wx_StreamBuffer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	size_t pos = arg.GetSizeT(0);
	pThis->GetEntity()->SetIntPosition(pos);
	return Value::Nil;
}

Gura_DeclareMethod(wx_StreamBuffer, GetLastAccess)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_StreamBuffer, GetLastAccess)
{
	Signal &sig = env.GetSignal();
	Object_wx_StreamBuffer *pThis = Object_wx_StreamBuffer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	size_t rtn = pThis->GetEntity()->GetLastAccess();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_StreamBuffer, Fixed)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "fixed", VTYPE_boolean, OCCUR_Once);
}

Gura_ImplementMethod(wx_StreamBuffer, Fixed)
{
	Signal &sig = env.GetSignal();
	Object_wx_StreamBuffer *pThis = Object_wx_StreamBuffer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	bool fixed = arg.GetBoolean(0);
	pThis->GetEntity()->Fixed(fixed);
	return Value::Nil;
}

Gura_DeclareMethod(wx_StreamBuffer, Flushable)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "flushable", VTYPE_boolean, OCCUR_Once);
}

Gura_ImplementMethod(wx_StreamBuffer, Flushable)
{
	Signal &sig = env.GetSignal();
	Object_wx_StreamBuffer *pThis = Object_wx_StreamBuffer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	bool flushable = arg.GetBoolean(0);
	pThis->GetEntity()->Flushable(flushable);
	return Value::Nil;
}

Gura_DeclareMethod(wx_StreamBuffer, FlushBuffer)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_StreamBuffer, FlushBuffer)
{
	Signal &sig = env.GetSignal();
	Object_wx_StreamBuffer *pThis = Object_wx_StreamBuffer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	bool rtn = pThis->GetEntity()->FlushBuffer();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_StreamBuffer, FillBuffer)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_StreamBuffer, FillBuffer)
{
	Signal &sig = env.GetSignal();
	Object_wx_StreamBuffer *pThis = Object_wx_StreamBuffer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	bool rtn = pThis->GetEntity()->FillBuffer();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_StreamBuffer, GetDataLeft)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_StreamBuffer, GetDataLeft)
{
	Signal &sig = env.GetSignal();
	Object_wx_StreamBuffer *pThis = Object_wx_StreamBuffer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	size_t rtn = pThis->GetEntity()->GetDataLeft();
	return ReturnValue(env, arg, Value(rtn));
}

#if 0
Gura_DeclareMethod(wx_StreamBuffer, Stream)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_StreamBuffer, Stream)
{
	Signal &sig = env.GetSignal();
	Object_wx_StreamBuffer *pThis = Object_wx_StreamBuffer::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxStreamBase *rtn = (wxStreamBase *)pThis->GetEntity()->Stream();
	return ReturnValue(env, arg, Value(new Object_wx_StreamBase(rtn, nullptr, OwnerFalse)));
}
#endif

//----------------------------------------------------------------------------
// Object implementation for wxStreamBuffer
//----------------------------------------------------------------------------
Object_wx_StreamBuffer::~Object_wx_StreamBuffer()
{
	if (_pEntity != nullptr) NotifyGuraObjectDeleted();
	if (_ownerFlag) delete _pEntity;
	_pEntity = nullptr;
}

Object *Object_wx_StreamBuffer::Clone() const
{
	return nullptr;
}

String Object_wx_StreamBuffer::ToString(bool exprFlag)
{
	String rtn("<wx.StreamBuffer:");
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
// Class implementation for wxStreamBuffer
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_StreamBuffer)
{
	Gura_AssignFunction(StreamBuffer);
	Gura_AssignFunction(StreamBuffer_1);
	Gura_AssignFunction(StreamBuffer_2);
	Gura_AssignFunction(StreamBufferEmpty);
	Gura_AssignMethod(wx_StreamBuffer, Read);
	Gura_AssignMethod(wx_StreamBuffer, Read_1);
	Gura_AssignMethod(wx_StreamBuffer, Write);
	Gura_AssignMethod(wx_StreamBuffer, Write_1);
	Gura_AssignMethod(wx_StreamBuffer, GetChar);
	Gura_AssignMethod(wx_StreamBuffer, PutChar);
	Gura_AssignMethod(wx_StreamBuffer, Tell);
	Gura_AssignMethod(wx_StreamBuffer, Seek);
	Gura_AssignMethod(wx_StreamBuffer, ResetBuffer);
	Gura_AssignMethod(wx_StreamBuffer, SetBufferIO);
	Gura_AssignMethod(wx_StreamBuffer, SetBufferIO_1);
	Gura_AssignMethod(wx_StreamBuffer, GetBufferStart);
	Gura_AssignMethod(wx_StreamBuffer, GetBufferEnd);
	Gura_AssignMethod(wx_StreamBuffer, GetBufferPos);
	Gura_AssignMethod(wx_StreamBuffer, GetIntPosition);
	Gura_AssignMethod(wx_StreamBuffer, SetIntPosition);
	Gura_AssignMethod(wx_StreamBuffer, GetLastAccess);
	Gura_AssignMethod(wx_StreamBuffer, Fixed);
	Gura_AssignMethod(wx_StreamBuffer, Flushable);
	Gura_AssignMethod(wx_StreamBuffer, FlushBuffer);
	Gura_AssignMethod(wx_StreamBuffer, FillBuffer);
	Gura_AssignMethod(wx_StreamBuffer, GetDataLeft);
	//Gura_AssignMethod(wx_StreamBuffer, Stream);
}

Gura_ImplementDescendantCreator(wx_StreamBuffer)
{
	return new Object_wx_StreamBuffer((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
