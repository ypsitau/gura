//----------------------------------------------------------------------------
// wxThread
// extracted from thread.tex
//----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleScope(wx)

Gura_DeclarePrivUserSymbol(Entry);
Gura_DeclarePrivUserSymbol(TestDestroy);

//----------------------------------------------------------------------------
// Class derivation
//----------------------------------------------------------------------------
class wx_Thread: public wxThread, public GuraObjectObserver {
private:
	//Gura::Signal *_pSig;
	Object_wx_Thread *_pObj;
public:
	//inline wx_Thread(wxThreadKind kind) : wxThread(kind), _pObj(nullptr) {}
	virtual ExitCode Entry();
	virtual bool TestDestroy();
	~wx_Thread();
	inline void AssocWithGura(Object_wx_Thread *pObj) {
		_pObj = pObj;
	}
	// virtual function of GuraObjectObserver
	virtual void GuraObjectDeleted();
};

wx_Thread::~wx_Thread()
{
	if (_pObj != nullptr) _pObj->InvalidateEntity();
}

void wx_Thread::GuraObjectDeleted()
{
	_pObj = nullptr;
}

wxThread::ExitCode wx_Thread::Entry()
{
	return 0;
}

bool wx_Thread::TestDestroy()
{
	return true;
}

//----------------------------------------------------------------------------
// Gura interfaces for wxThread
//----------------------------------------------------------------------------
Gura_DeclareFunction(Thread)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
#if 0
	SetClassToConstruct(Gura_UserClass(wx_Thread));
	DeclareArg(env, "kind", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
#endif
}

Gura_ImplementFunction(Thread)
{
	Signal &sig = env.GetSignal();
	if (!CheckWxReady(sig)) return Value::Nil;
#if 0
	wxThreadKind kind = wxTHREAD_DETACHED;
	if (arg.IsValid(0)) kind = static_cast<wxThreadKind>(arg.GetInt(0));
	wx_Thread *pEntity = new wx_Thread(kind);
	Object_wx_Thread *pObj = Object_wx_Thread::GetObjectThis(arg);
	if (pObj == nullptr) {
		pObj = new Object_wx_Thread(pEntity, pEntity, OwnerFalse);
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

Gura_DeclareMethod(wx_Thread, Create)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "stackSize", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_Thread, Create)
{
	Signal &sig = env.GetSignal();
	Object_wx_Thread *pThis = Object_wx_Thread::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	unsigned stackSize = 0;
	if (arg.IsValid(0)) stackSize = arg.GetInt(0);
	wxThreadError rtn = pThis->GetEntity()->Create(stackSize);
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_Thread, Delete)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_Thread, Delete)
{
	Signal &sig = env.GetSignal();
	Object_wx_Thread *pThis = Object_wx_Thread::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxThreadError rtn = pThis->GetEntity()->Delete();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_Thread, Entry)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_Thread, Entry)
{
	Signal &sig = env.GetSignal();
#if 0
	Object_wx_Thread *pThis = Object_wx_Thread::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxThread::ExitCode rtn = pThis->GetEntity()->wxThread::Entry();
	return ReturnValue(env, arg, Value(rtn));
#endif
	SetError_NotImplemented(sig);
	return Value::Nil;
}

Gura_DeclareMethod(wx_Thread, Exit)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
#if 0
	DeclareArg(env, "exitcode", VTYPE_number, OCCUR_ZeroOrOnce);
#endif
}

Gura_ImplementMethod(wx_Thread, Exit)
{
	Signal &sig = env.GetSignal();
#if 0
	Object_wx_Thread *pThis = Object_wx_Thread::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxThread::ExitCode exitcode = 0;
	if (arg.IsValid(0)) exitcode = static_cast<wxThread::ExitCode>(arg.GetInt(0));
	pThis->GetEntity()->Exit(exitcode);
	return Value::Nil;
#endif
	SetError_NotImplemented(sig);
	return Value::Nil;
}

Gura_DeclareClassMethod(wx_Thread, GetCPUCount)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementClassMethod(wx_Thread, GetCPUCount)
{
	Signal &sig = env.GetSignal();
	if (!CheckWxReady(sig)) return Value::Nil;
	int rtn = wxThread::GetCPUCount();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareClassMethod(wx_Thread, GetCurrentId)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementClassMethod(wx_Thread, GetCurrentId)
{
	Signal &sig = env.GetSignal();
	if (!CheckWxReady(sig)) return Value::Nil;
	unsigned rtn = wxThread::GetCurrentId();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_Thread, GetId)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_Thread, GetId)
{
	Signal &sig = env.GetSignal();
	Object_wx_Thread *pThis = Object_wx_Thread::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	unsigned rtn = pThis->GetEntity()->GetId();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_Thread, GetPriority)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_Thread, GetPriority)
{
	Signal &sig = env.GetSignal();
	Object_wx_Thread *pThis = Object_wx_Thread::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	int rtn = pThis->GetEntity()->GetPriority();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_Thread, IsAlive)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_Thread, IsAlive)
{
	Signal &sig = env.GetSignal();
	Object_wx_Thread *pThis = Object_wx_Thread::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	bool rtn = pThis->GetEntity()->IsAlive();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_Thread, IsDetached)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_Thread, IsDetached)
{
	Signal &sig = env.GetSignal();
	Object_wx_Thread *pThis = Object_wx_Thread::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	bool rtn = pThis->GetEntity()->IsDetached();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareClassMethod(wx_Thread, IsMain)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementClassMethod(wx_Thread, IsMain)
{
	Signal &sig = env.GetSignal();
	if (!CheckWxReady(sig)) return Value::Nil;
	bool rtn = wxThread::IsMain();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_Thread, IsPaused)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_Thread, IsPaused)
{
	Signal &sig = env.GetSignal();
	Object_wx_Thread *pThis = Object_wx_Thread::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	bool rtn = pThis->GetEntity()->IsPaused();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_Thread, IsRunning)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_Thread, IsRunning)
{
	Signal &sig = env.GetSignal();
	Object_wx_Thread *pThis = Object_wx_Thread::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	bool rtn = pThis->GetEntity()->IsRunning();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_Thread, Kill)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_Thread, Kill)
{
	Signal &sig = env.GetSignal();
	Object_wx_Thread *pThis = Object_wx_Thread::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxThreadError rtn = pThis->GetEntity()->Kill();
	return ReturnValue(env, arg, Value(rtn));
}

#if 0
Gura_DeclareMethod(wx_Thread, OnExit)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_Thread, OnExit)
{
	Signal &sig = env.GetSignal();
	Object_wx_Thread *pThis = Object_wx_Thread::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	pThis->GetEntity()->OnExit();
	return Value::Nil;
}
#endif

Gura_DeclareMethod(wx_Thread, Pause)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_Thread, Pause)
{
	Signal &sig = env.GetSignal();
	Object_wx_Thread *pThis = Object_wx_Thread::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxThreadError rtn = pThis->GetEntity()->Pause();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_Thread, Run)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_Thread, Run)
{
	Signal &sig = env.GetSignal();
	Object_wx_Thread *pThis = Object_wx_Thread::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxThreadError rtn = pThis->GetEntity()->Run();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_Thread, SetPriority)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "priority", VTYPE_number, OCCUR_Once);
}

Gura_ImplementMethod(wx_Thread, SetPriority)
{
	Signal &sig = env.GetSignal();
	Object_wx_Thread *pThis = Object_wx_Thread::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	int priority = arg.GetInt(0);
	pThis->GetEntity()->SetPriority(priority);
	return Value::Nil;
}

Gura_DeclareClassMethod(wx_Thread, Sleep)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_Map);
	DeclareArg(env, "milliseconds", VTYPE_number, OCCUR_Once);
}

Gura_ImplementClassMethod(wx_Thread, Sleep)
{
	Signal &sig = env.GetSignal();
	if (!CheckWxReady(sig)) return Value::Nil;
	unsigned milliseconds = arg.GetInt(0);
	wxThread::Sleep(milliseconds);
	return Value::Nil;
}

Gura_DeclareMethod(wx_Thread, Resume)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_Thread, Resume)
{
	Signal &sig = env.GetSignal();
	Object_wx_Thread *pThis = Object_wx_Thread::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxThreadError rtn = pThis->GetEntity()->Resume();
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareClassMethod(wx_Thread, SetConcurrency)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "level", VTYPE_number, OCCUR_Once);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementClassMethod(wx_Thread, SetConcurrency)
{
	Signal &sig = env.GetSignal();
	if (!CheckWxReady(sig)) return Value::Nil;
	size_t level = arg.GetSizeT(0);
	bool rtn = wxThread::SetConcurrency(level);
	return ReturnValue(env, arg, Value(rtn));
}

Gura_DeclareMethod(wx_Thread, TestDestroy)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_Thread, TestDestroy)
{
	Signal &sig = env.GetSignal();
#if defined(__WXMSW__)
	Object_wx_Thread *pThis = Object_wx_Thread::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	bool rtn = pThis->GetEntity()->wxThread::TestDestroy();
	return ReturnValue(env, arg, Value(rtn));
#else
	SetError_MSWOnly(sig);
	return Value::Nil;
#endif
}

Gura_DeclareClassMethod(wx_Thread, This)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementClassMethod(wx_Thread, This)
{
	Signal &sig = env.GetSignal();
	if (!CheckWxReady(sig)) return Value::Nil;
	wxThread *rtn = (wxThread *)wxThread::This();
	return ReturnValue(env, arg, Value(new Object_wx_Thread(rtn, nullptr, OwnerFalse)));
}

Gura_DeclareMethod(wx_Thread, Yield)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
}

Gura_ImplementMethod(wx_Thread, Yield)
{
	Signal &sig = env.GetSignal();
	Object_wx_Thread *pThis = Object_wx_Thread::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	pThis->GetEntity()->Yield();
	return Value::Nil;
}

Gura_DeclareMethod(wx_Thread, Wait)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(wx_Thread, Wait)
{
	Signal &sig = env.GetSignal();
	Object_wx_Thread *pThis = Object_wx_Thread::GetObjectThis(arg);
	if (pThis->IsInvalid(sig)) return Value::Nil;
	wxThread::ExitCode rtn = pThis->GetEntity()->Wait();
	return ReturnValue(env, arg, Value(rtn));
}

//----------------------------------------------------------------------------
// Object implementation for wxThread
//----------------------------------------------------------------------------
Object_wx_Thread::~Object_wx_Thread()
{
	if (_pEntity != nullptr) NotifyGuraObjectDeleted();
	if (_ownerFlag) delete _pEntity;
	_pEntity = nullptr;
}

Object *Object_wx_Thread::Clone() const
{
	return nullptr;
}

String Object_wx_Thread::ToString(bool exprFlag)
{
	String rtn("<wx.Thread:");
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
// Class implementation for wxThread
//----------------------------------------------------------------------------
Gura_ImplementUserInheritableClass(wx_Thread)
{
	Gura_RealizeUserSymbol(Entry);
	Gura_RealizeUserSymbol(TestDestroy);
	Gura_AssignFunction(Thread);
	Gura_AssignMethod(wx_Thread, Create);
	Gura_AssignMethod(wx_Thread, Delete);
	Gura_AssignMethod(wx_Thread, Entry);
	Gura_AssignMethod(wx_Thread, Exit);
	Gura_AssignMethod(wx_Thread, GetCPUCount);
	Gura_AssignMethod(wx_Thread, GetCurrentId);
	Gura_AssignMethod(wx_Thread, GetId);
	Gura_AssignMethod(wx_Thread, GetPriority);
	Gura_AssignMethod(wx_Thread, IsAlive);
	Gura_AssignMethod(wx_Thread, IsDetached);
	Gura_AssignMethod(wx_Thread, IsMain);
	Gura_AssignMethod(wx_Thread, IsPaused);
	Gura_AssignMethod(wx_Thread, IsRunning);
	Gura_AssignMethod(wx_Thread, Kill);
	//Gura_AssignMethod(wx_Thread, OnExit);
	Gura_AssignMethod(wx_Thread, Pause);
	Gura_AssignMethod(wx_Thread, Run);
	Gura_AssignMethod(wx_Thread, SetPriority);
	Gura_AssignMethod(wx_Thread, Sleep);
	Gura_AssignMethod(wx_Thread, Resume);
	Gura_AssignMethod(wx_Thread, SetConcurrency);
	Gura_AssignMethod(wx_Thread, TestDestroy);
	Gura_AssignMethod(wx_Thread, This);
	Gura_AssignMethod(wx_Thread, Yield);
	Gura_AssignMethod(wx_Thread, Wait);
}

Gura_ImplementDescendantCreator(wx_Thread)
{
	return new Object_wx_Thread((pClass == nullptr)? this : pClass, nullptr, nullptr, OwnerFalse);
}

Gura_EndModuleScope(wx)
