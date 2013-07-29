//
// Object_audio
//

#include "stdafx.h"

namespace Gura {

//-----------------------------------------------------------------------------
// Object implementation for audio
//-----------------------------------------------------------------------------
Object_audio::Object_audio(Environment &env, Audio *pAudio) :
			Object(env.LookupClass(VTYPE_audio)), _pAudio(pAudio)
{
}

Object_audio::Object_audio(Class *pClass, Audio *pAudio) :
			Object(pClass), _pAudio(pAudio)
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
	symbols.insert(Gura_Symbol(samples));
	symbols.insert(Gura_Symbol(samplespersec));
	symbols.insert(Gura_Symbol(bytespersample));
	return true;
}

Value Object_audio::DoGetProp(Environment &env, Signal sig, const Symbol *pSymbol,
								const SymbolSet &attrs, bool &evaluatedFlag)
{
	evaluatedFlag = true;
	if (pSymbol->IsIdentical(Gura_Symbol(format))) {
		return Value(Audio::FormatToSymbol(_pAudio->GetFormat()));
	} else if (pSymbol->IsIdentical(Gura_Symbol(channels))) {
		return Value(static_cast<UInt>(_pAudio->GetChannels()));
	} else if (pSymbol->IsIdentical(Gura_Symbol(samples))) {
		return Value(static_cast<UInt>(_pAudio->GetSamples()));
	} else if (pSymbol->IsIdentical(Gura_Symbol(samplespersec))) {
		return Value(static_cast<UInt>(_pAudio->GetSamplesPerSec()));
	} else if (pSymbol->IsIdentical(Gura_Symbol(bytespersample))) {
		return Value(static_cast<UInt>(_pAudio->GetBytesPerSample()));
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
	do {
		char buff[32];
		::sprintf(buff, "%dch", static_cast<int>(_pAudio->GetChannels()));
		rtn += buff;
	} while (0);
	rtn += ":";
	do {
		char buff[32];
		::sprintf(buff, "%dHz", static_cast<int>(_pAudio->GetSamplesPerSec()));
		rtn += buff;
	} while (0);
	rtn += ":";
	if (_pAudio->IsValid()) {
		char buff[32];
		::sprintf(buff, "%dsamples", static_cast<int>(_pAudio->GetSamples()));
		rtn += buff;
	} else {
		rtn += "invalid";
	}
	rtn += ">";
	return rtn;
}

//-----------------------------------------------------------------------------
// Global functions
//-----------------------------------------------------------------------------
// audio(args+):map {block?}
Gura_DeclareFunction(audio)
{
	SetMode(RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "args", VTYPE_any, OCCUR_OnceOrMore);
	DeclareBlock(OCCUR_ZeroOrOnce);
}

Gura_ImplementFunction(audio)
{
	size_t nChannels = 1;
	size_t nSamplesPerSec = 10000;
	ValueList valList = args.GetList(0);
	AutoPtr<Audio> pAudio;
	if (valList[0].IsSymbol()) {
		Audio::Format format = Audio::SymbolToFormat(sig, valList[0].GetSymbol());
		if (sig.IsSignalled()) return Value::Null;
		if (valList.size() >= 2) {
			Declaration(Gura_Symbol(channels), VTYPE_number).
									ValidateAndCast(env, sig, valList[1]);
			if (sig.IsSignalled()) return Value::Null;
			nChannels = valList[1].GetSizeT();
			if (nChannels != 1 && nChannels != 2) {
				sig.SetError(ERR_ValueError, "channels must be one or two");
				return Value::Null;
			}
		}
		if (valList.size() >= 3) {
			Declaration(Gura_Symbol(samplespersec), VTYPE_number).
									ValidateAndCast(env, sig, valList[2]);
			if (sig.IsSignalled()) return Value::Null;
			nSamplesPerSec = valList[2].GetSizeT();
			if (nSamplesPerSec == 0) {
				sig.SetError(ERR_ValueError, "samplespersec must be more then zero");
				return Value::Null;
			}
		}
		pAudio.reset(new Audio(format, nChannels, nSamplesPerSec));
	} else {
		Declaration(Gura_Symbol(stream), VTYPE_stream, OCCUR_Once, FLAG_Read, NULL).
									ValidateAndCast(env, sig, valList[0]);
		if (sig.IsSignalled()) return Value::Null;
		Stream &stream = valList[0].GetStream();
		pAudio.reset(new Audio(Audio::FORMAT_None, nChannels, nSamplesPerSec));
		const char *audioType = NULL;
		if (valList.size() >= 2) {
			Declaration(Gura_Symbol(audiotype), VTYPE_string).
									ValidateAndCast(env, sig, valList[1]);
			if (sig.IsSignalled()) return Value::Null;
			audioType = valList[1].GetString();
		}
		if (!pAudio->Read(env, sig, stream, audioType)) return Value::Null;
	}
	return ReturnValue(env, sig, args, Value(new Object_audio(env, pAudio.release())));
}

//-----------------------------------------------------------------------------
// Gura interfaces for audio
//-----------------------------------------------------------------------------
// audio#sinewave(channel:number, freq:number, len:number, amplitude?:number):reduce:map
Gura_DeclareMethod(audio, sinewave)
{
	SetMode(RSLTMODE_Reduce, FLAG_Map);
	DeclareArg(env, "channel", VTYPE_number);
	DeclareArg(env, "freq", VTYPE_number);
	DeclareArg(env, "len", VTYPE_number);
	DeclareArg(env, "amplitude", VTYPE_number, OCCUR_ZeroOrOnce);
}

Gura_ImplementMethod(audio, sinewave)
{
	Audio *pAudio = Object_audio::GetThisObj(args)->GetAudio();
	size_t iChannel = args.GetSizeT(0);
	double freq = args.GetDouble(1);
	size_t nSamples = static_cast<size_t>(args.GetDouble(2) * pAudio->GetSamplesPerSec());
	int amplitude = args.IsNumber(3)? args.GetInt(3) : -1;
	if (!pAudio->AddSineWave(sig, iChannel, freq, nSamples, amplitude)) {
		return Value::Null;
	}
	return args.GetThis();
}

// audio#put(channel:number, offset:number, data:number):reduce:map
Gura_DeclareMethod(audio, put)
{
	SetMode(RSLTMODE_Reduce, FLAG_Map);
	DeclareArg(env, "channel", VTYPE_number);
	DeclareArg(env, "offset", VTYPE_number);
	DeclareArg(env, "data", VTYPE_number);
}

Gura_ImplementMethod(audio, put)
{
	Audio *pAudio = Object_audio::GetThisObj(args)->GetAudio();
	size_t iChannel = args.GetSizeT(0);
	size_t offset = args.GetSizeT(1);
	int data = args.GetInt(2);
	if (!pAudio->PutData(iChannel, offset, data)) {
		sig.SetError(ERR_IndexError, "offset is out of range");
		return Value::Null;
	}
	return args.GetThis();
}

// audio#get(channel:number, offset:number):map
Gura_DeclareMethod(audio, get)
{
	SetMode(RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "channel", VTYPE_number);
	DeclareArg(env, "offset", VTYPE_number);
}

Gura_ImplementMethod(audio, get)
{
	Audio *pAudio = Object_audio::GetThisObj(args)->GetAudio();
	size_t iChannel = args.GetSizeT(0);
	size_t offset = args.GetSizeT(1);
	int data = 0;
	if (!pAudio->GetData(iChannel, offset, &data)) {
		sig.SetError(ERR_IndexError, "offset is out of range");
		return Value::Null;
	}
	return Value(data);
}

// audio#each(channel:number):map
Gura_DeclareMethod(audio, each)
{
	SetMode(RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "channel", VTYPE_number);
}

Gura_ImplementMethod(audio, each)
{
	Audio *pAudio = Object_audio::GetThisObj(args)->GetAudio();
	size_t iChannel = args.GetSizeT(0);
	AutoPtr<Iterator> pIterator(new Audio::IteratorEach(pAudio->Reference(), iChannel));
	return ReturnIterator(env, sig, args, pIterator.release());
}

// audio#store(channel:number, offset:number, samples:number, src):reduce
Gura_DeclareMethod(audio, store)
{
	SetMode(RSLTMODE_Reduce, FLAG_None);
	DeclareArg(env, "channel", VTYPE_number);
	DeclareArg(env, "offset", VTYPE_number);
	DeclareArg(env, "samples", VTYPE_number);
	DeclareArg(env, "src", VTYPE_any);
}

Gura_ImplementMethod(audio, store)
{
	Audio *pAudio = Object_audio::GetThisObj(args)->GetAudio();
	return args.GetThis();
}

// audio#extract(channel:number, offset:number, samples:number, dst)
Gura_DeclareMethod(audio, extract)
{
	SetMode(RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "channel", VTYPE_number);
	DeclareArg(env, "offset", VTYPE_number);
	DeclareArg(env, "samples", VTYPE_number);
	DeclareArg(env, "dst", VTYPE_any);
}

Gura_ImplementMethod(audio, extract)
{
	Audio *pAudio = Object_audio::GetThisObj(args)->GetAudio();
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
	Audio *pAudio = Object_audio::GetThisObj(args)->GetAudio();
	return args.GetThis();
}

// audio#fillrange(channel:number, offset:number, samples:number, data:number):reduce
Gura_DeclareMethod(audio, fillrange)
{
	SetMode(RSLTMODE_Reduce, FLAG_None);
	DeclareArg(env, "channel", VTYPE_number);
	DeclareArg(env, "offset", VTYPE_number);
	DeclareArg(env, "samples", VTYPE_number);
	DeclareArg(env, "data", VTYPE_number);
}

Gura_ImplementMethod(audio, fillrange)
{
	Audio *pAudio = Object_audio::GetThisObj(args)->GetAudio();
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
	Gura_AssignMethod(audio, each);
	Gura_AssignMethod(audio, store);
	Gura_AssignMethod(audio, extract);
	Gura_AssignMethod(audio, fill);
	Gura_AssignMethod(audio, fillrange);
}

bool Class_audio::CastFrom(Environment &env, Signal sig, Value &value, const Declaration *pDecl)
{
	size_t nChannels = 1;
	size_t nSamplesPerSec = 10000;
	env.LookupClass(VTYPE_stream)->CastFrom(env, sig, value, pDecl);
	if (value.IsStream()) {
		AutoPtr<Audio> pAudio(new Audio(Audio::FORMAT_None, nChannels, nSamplesPerSec));
		pAudio->Read(env, sig, value.GetStream(), NULL);
		value = Value::Null; // delete stream instance
		if (sig.IsSignalled()) return false;
		value = Value(new Object_audio(env, pAudio.release()));
		return true;
	}
	return false;
}

}
