//
// Object_audio
//

#include "stdafx.h"

namespace Gura {

//-----------------------------------------------------------------------------
// Object implementation for audio
//-----------------------------------------------------------------------------
Object_audio::~Object_audio()
{
}

Object *Object_audio::Clone() const
{
	return NULL; //new Object_audio(*this);
}

bool Object_audio::DoDirProp(Environment &env, Signal sig, SymbolSet &symbols)
{
	if (!Object::DoDirProp(env, sig, symbols)) return false;
	symbols.insert(Gura_Symbol(format));
	symbols.insert(Gura_Symbol(channels));
	symbols.insert(Gura_Symbol(len));
	return true;
}

Value Object_audio::DoGetProp(Environment &env, Signal sig, const Symbol *pSymbol,
								const SymbolSet &attrs, bool &evaluatedFlag)
{
	evaluatedFlag = true;
	if (pSymbol->IsIdentical(Gura_Symbol(format))) {
		return Value(Audio::FormatToSymbol(_pAudio->GetFormat()));
	} else if (pSymbol->IsIdentical(Gura_Symbol(channels))) {
		return Value(static_cast<unsigned int>(_pAudio->GetChannels()));
	} else if (pSymbol->IsIdentical(Gura_Symbol(len))) {
		return Value(static_cast<unsigned int>(_pAudio->GetLength()));
	}
	evaluatedFlag = false;
	return Value::Null;
}

Value Object_audio::DoSetProp(Environment &env, Signal sig, const Symbol *pSymbol, const Value &value,
								const SymbolSet &attrs, bool &evaluatedFlag)
{
	return DoGetProp(env, sig, pSymbol, attrs, evaluatedFlag);
}

String Object_audio::ToString(Signal sig, bool exprFlag)
{
	String rtn;
	rtn += "<audio:";
	rtn += Audio::FormatToSymbol(_pAudio->GetFormat())->GetName();
	rtn += ":";
	if (_pAudio->IsValid()) {
		char buff[32];
		::sprintf(buff, "%d", static_cast<int>(_pAudio->GetLength()));
		rtn += buff;
	} else {
		rtn += "invalid";
	}
	rtn += ":";
	do {
		char buff[32];
		::sprintf(buff, "%dch", static_cast<int>(_pAudio->GetChannels()));
		rtn += buff;
	} while (0);
	rtn += ">";
	return rtn;
}

//-----------------------------------------------------------------------------
// Global functions
//-----------------------------------------------------------------------------
// audio(format:symbol, len:number, channels:number => 1) {block?}
Gura_DeclareFunction(audio)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "format", VTYPE_symbol);
	DeclareArg(env, "len", VTYPE_number);
	DeclareArg(env, "channels", VTYPE_number,
							OCCUR_Once, FLAG_None, new Expr_Value(1));
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(audio)
{
	Audio::Format format = Audio::SymbolToFormat(sig, args.GetSymbol(0));
	if (sig.IsSignalled()) return Value::Null;
	size_t nChannels = args.GetSizeT(2);
	AutoPtr<Audio> pAudio(new Audio(format, nChannels));
	if (!pAudio->AllocBuffer(sig, args.GetSizeT(1))) return Value::Null;
	return ReturnValue(env, sig, args, Value(new Object_audio(env, pAudio.release())));
}

//-----------------------------------------------------------------------------
// Gura interfaces for audio
//-----------------------------------------------------------------------------
// audio#sinewave(channel:number, pitch:number, phase?:number,
//                amplitude?:number, offset?:number, len?:number):reduce
Gura_DeclareMethod(audio, sinewave)
{
	SetMode(RSLTMODE_Reduce, FLAG_None);
	DeclareArg(env, "channel", VTYPE_number);
	DeclareArg(env, "pitch", VTYPE_number);
	DeclareArg(env, "phase", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareArg(env, "amplitude", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareArg(env, "offset", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareArg(env, "len", VTYPE_number, OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(audio, sinewave)
{
	Object_audio *pThis = Object_audio::GetThisObj(args);
	Audio *pAudio = pThis->GetAudio();
	size_t iChannel = args.GetSizeT(0);
	size_t pitch = args.GetSizeT(1);
	int phase = args.IsNumber(2)? args.GetInt(2) : 0;
	int amplitude = args.IsNumber(3)? args.GetInt(3) : -1;
	size_t offset = args.IsNumber(4)? args.GetSizeT(4) : 0;
	size_t len = args.IsNumber(5)? args.GetSizeT(5) : InvalidSize;
	if (!pAudio->SetSineWave(sig, iChannel, pitch, phase, amplitude, offset, len)) {
		return Value::Null;
	}
	//for (size_t i = 0; i < pThis->GetLength() * pThis->GetBytesPerData(); i++) {
	//	::printf(" %02x", pThis->GetBuffer()[i]);
	//}
	return args.GetThis();
}

// audio#put(channel:number, offset:number, data:number):reduce
Gura_DeclareMethod(audio, put)
{
	SetMode(RSLTMODE_Reduce, FLAG_None);
	DeclareArg(env, "channel", VTYPE_number);
	DeclareArg(env, "offset", VTYPE_number);
	DeclareArg(env, "data", VTYPE_number);
}

Gura_ImplementMethod(audio, put)
{
	Object_audio *pThis = Object_audio::GetThisObj(args);
	return args.GetThis();
}

// audio#get(channel:number, offset:number)
Gura_DeclareMethod(audio, get)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "channel", VTYPE_number);
	DeclareArg(env, "offset", VTYPE_number);
}

Gura_ImplementMethod(audio, get)
{
	Object_audio *pThis = Object_audio::GetThisObj(args);
	return Value::Null;
}

// audio#store(channel:number, offset:number, len:number, src):reduce
Gura_DeclareMethod(audio, store)
{
	SetMode(RSLTMODE_Reduce, FLAG_None);
	DeclareArg(env, "channel", VTYPE_number);
	DeclareArg(env, "offset", VTYPE_number);
	DeclareArg(env, "len", VTYPE_number);
	DeclareArg(env, "src", VTYPE_any);
}

Gura_ImplementMethod(audio, store)
{
	Object_audio *pThis = Object_audio::GetThisObj(args);
	return args.GetThis();
}

// audio#extract(channel:number, offset:number, len:number, dst)
Gura_DeclareMethod(audio, extract)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "channel", VTYPE_number);
	DeclareArg(env, "offset", VTYPE_number);
	DeclareArg(env, "len", VTYPE_number);
	DeclareArg(env, "dst", VTYPE_any);
}

Gura_ImplementMethod(audio, extract)
{
	Object_audio *pThis = Object_audio::GetThisObj(args);
	return Value::Null;
}

// audio#fill(data:number):reduce
Gura_DeclareMethod(audio, fill)
{
	SetMode(RSLTMODE_Reduce, FLAG_None);
	DeclareArg(env, "data", VTYPE_number);
}

Gura_ImplementMethod(audio, fill)
{
	Object_audio *pThis = Object_audio::GetThisObj(args);
	return args.GetThis();
}

// audio#fillrange(channel:number, offset:number, len:number, data:number):reduce
Gura_DeclareMethod(audio, fillrange)
{
	SetMode(RSLTMODE_Reduce, FLAG_None);
	DeclareArg(env, "channel", VTYPE_number);
	DeclareArg(env, "offset", VTYPE_number);
	DeclareArg(env, "len", VTYPE_number);
	DeclareArg(env, "data", VTYPE_number);
}

Gura_ImplementMethod(audio, fillrange)
{
	Object_audio *pThis = Object_audio::GetThisObj(args);
	return args.GetThis();
}

//-----------------------------------------------------------------------------
// Class implementation for audio
//-----------------------------------------------------------------------------
Class_audio::Class_audio(Environment *pEnvOuter) : Class(pEnvOuter, VTYPE_audio)
{
}

void Class_audio::Prepare(Environment &env)
{
	Gura_AssignFunction(audio);
	Gura_AssignMethod(audio, sinewave);
	Gura_AssignMethod(audio, put);
	Gura_AssignMethod(audio, get);
	Gura_AssignMethod(audio, store);
	Gura_AssignMethod(audio, extract);
	Gura_AssignMethod(audio, fill);
	Gura_AssignMethod(audio, fillrange);
}

Object *Class_audio::CreateDescendant(Environment &env, Signal sig, Class *pClass)
{
	GURA_ERROREND(env, "this function must not be called");
	return NULL;
}

}
