//-----------------------------------------------------------------------------
// Gura wav module
//-----------------------------------------------------------------------------
#ifndef __MODULE_WAV_H__
#define __MODULE_WAV_H__
#include <gura.h>

Gura_BeginModule(wav)

//-----------------------------------------------------------------------------
// AudioStreamer_WAV
//-----------------------------------------------------------------------------
class AudioStreamer_WAV : public AudioStreamer {
public:
	inline AudioStreamer_WAV() : AudioStreamer("wav") {}
	virtual bool IsResponsible(Signal sig, Stream &stream);
	virtual bool Read(Environment &env, Signal sig, Audio *pAudio, Stream &stream);
	virtual bool Write(Environment &env, Signal sig, Audio *pAudio, Stream &stream);
public:
	static bool ReadStream(Signal sig, Audio *pAudio, Stream &stream);
	static bool WriteStream(Signal sig, Audio *pAudio, Stream &stream);
	static void SetError_InvalidWAVFormat(Signal sig);
};

}}

#endif
