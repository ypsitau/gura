//-----------------------------------------------------------------------------
// Gura module: wav
//-----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleBody(wav)

//-----------------------------------------------------------------------------
// Gura interfaces for Object_audio
// These methods are available after importing wav module.
//-----------------------------------------------------------------------------
// audio#read@wav(stream:stream:r):reduce
Gura_DeclareMethodAlias(audio, read_wav, "read@wav")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Reduce, FLAG_None);
	DeclareArg(env, "stream", VTYPE_stream, OCCUR_Once, FLAG_Read);
	AddHelp(
		Gura_Symbol(en),
		"Reads WAV audio from a stream.");
}

Gura_ImplementMethod(audio, read_wav)
{
	Signal &sig = env.GetSignal();
	Object_audio *pThis = Object_audio::GetObjectThis(arg);
	if (!AudioStreamer_WAV::ReadStream(sig, pThis->GetAudio(), arg.GetStream(0))) return Value::Nil;
	return arg.GetValueThis();
}

// audio#write@wav(stream:stream:w):reduce
Gura_DeclareMethodAlias(audio, write_wav, "write@wav")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Reduce, FLAG_None);
	DeclareArg(env, "stream", VTYPE_stream, OCCUR_Once, FLAG_Write);
	AddHelp(
		Gura_Symbol(en),
		"Writes WAV audio to a stream.");
}

Gura_ImplementMethod(audio, write_wav)
{
	Signal &sig = env.GetSignal();
	Object_audio *pThis = Object_audio::GetObjectThis(arg);
	if (!AudioStreamer_WAV::WriteStream(sig, pThis->GetAudio(), arg.GetStream(0))) return Value::Nil;
	return arg.GetValueThis();
}

//-----------------------------------------------------------------------------
// Gura module functions: wav
//-----------------------------------------------------------------------------
// mav.test(stream:stream, streamOut:stream:w)
Gura_DeclareFunction(test)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "stream", VTYPE_stream);
	DeclareArg(env, "streamOut", VTYPE_stream, OCCUR_Once, FLAG_Write);
	AddHelp(
		Gura_Symbol(en),
		"");
}

Gura_ImplementFunction(test)
{
	Signal &sig = env.GetSignal();
	std::unique_ptr<Wave> pWave(new Wave());
	pWave->Read(sig, arg.GetStream(0));
	pWave->Write(sig, arg.GetStream(1));
	pWave->Print();
	return Value::Nil;
}

//-----------------------------------------------------------------------------
// Module Entries
//-----------------------------------------------------------------------------
Gura_ModuleValidate()
{
	return Version::CheckCoreVersion(GURA_VERSION, nullptr);
}

Gura_ModuleEntry()
{
	Gura_AssignMethodTo(VTYPE_audio, audio, read_wav);
	Gura_AssignMethodTo(VTYPE_audio, audio, write_wav);
	AudioStreamer::Register(new AudioStreamer_WAV());
	// function assignment
	Gura_AssignFunction(test);
	return true;
}

Gura_ModuleTerminate()
{
}

//-----------------------------------------------------------------------------
// AudioStreamer_WAV
//-----------------------------------------------------------------------------
bool AudioStreamer_WAV::IsResponsible(Signal &sig, Stream &stream)
{
	if (stream.IsReadable()) {
	}
	return stream.HasNameSuffix(".wav");
}

bool AudioStreamer_WAV::Read(Environment &env, Audio *pAudio, Stream &stream)
{
	Signal &sig = env.GetSignal();
	return AudioStreamer_WAV::ReadStream(sig, pAudio, stream);
}

bool AudioStreamer_WAV::Write(Environment &env, Audio *pAudio, Stream &stream)
{
	Signal &sig = env.GetSignal();
	return AudioStreamer_WAV::WriteStream(sig, pAudio, stream);
}

bool AudioStreamer_WAV::ReadStream(Signal &sig, Audio *pAudio, Stream &stream)
{
	//if (!pObjAudio->CheckEmpty(sig)) return false;
	return false;
}

bool AudioStreamer_WAV::WriteStream(Signal &sig, Audio *pAudio, Stream &stream)
{
	std::unique_ptr<Wave> pWave(new Wave());
	if (!pWave->SetAudio(sig, pAudio)) return false;
	if (!pWave->Write(sig, stream)) return false;
	return true;
}

void AudioStreamer_WAV::SetError_InvalidWAVFormat(Signal &sig)
{
	sig.SetError(ERR_FormatError, "invalid WAV format");
}

Gura_EndModuleBody(wav, wav)

Gura_RegisterModule(wav)
