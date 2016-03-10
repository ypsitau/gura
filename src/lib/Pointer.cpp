//=============================================================================
// Pointer
//=============================================================================
#include "stdafx.h"

namespace Gura {

//-----------------------------------------------------------------------------
// Pointer
//-----------------------------------------------------------------------------
Pointer::Pointer(size_t offset) : _offset(offset)
{
}

Pointer::~Pointer()
{
}

bool Pointer::Advance(Environment &env, int distance)
{
	if (distance >= 0) {
		_offset += distance;
		return true;
	}
	if (_offset >= static_cast<size_t>(-distance)) {
		_offset += distance;
		return true;
	}
	env.SetError(ERR_IndexError, "pointer offset becomes negative");
	return false;
}

bool Pointer::PackStay(Environment &env, const char *format, const ValueList &valListArg)
{
	size_t offset = _offset;
	if (!Pack(env, format, valListArg)) return false;
	_offset = offset;
	return true;
}

Value Pointer::UnpackStay(Environment &env, const char *format,
						  const ValueList &valListArg, bool exceedErrorFlag)
{
	size_t offset = _offset;
	Value value = Unpack(env, format, valListArg, exceedErrorFlag);
	_offset = offset;
	return value;
}

//-----------------------------------------------------------------------------
// Pointer::StreamEx
//-----------------------------------------------------------------------------
Pointer::StreamEx::StreamEx(Environment &env, Pointer *pPointer, bool seekEndFlag) :
	Stream(env, ATTR_BwdSeekable | ATTR_Readable | (pPointer->IsWritable()? ATTR_Writable : 0)),
	_pPointer(pPointer)
{
	_pPointer->SetOffset(_pPointer->GetEntireSize());
}

Pointer::StreamEx::~StreamEx()
{
}

const char *Pointer::StreamEx::GetName() const
{
	return "pointer";
}

const char *Pointer::StreamEx::GetIdentifier() const
{
	return nullptr;
}

size_t Pointer::StreamEx::DoRead(Signal &sig, void *buff, size_t len)
{
	return 0;
}

size_t Pointer::StreamEx::DoWrite(Signal &sig, const void *buff, size_t len)
{
	
	return 0;
}

bool Pointer::StreamEx::DoSeek(Signal &sig, long offset, size_t offsetPrev, SeekMode seekMode)
{
	return false;
}

bool Pointer::StreamEx::DoFlush(Signal &sig)
{
	return true;
}

bool Pointer::StreamEx::DoClose(Signal &sig)
{
	return Stream::DoClose(sig);
}

size_t Pointer::StreamEx::DoGetSize()
{
	return 0;
}

}
