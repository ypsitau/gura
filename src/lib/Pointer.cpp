//=============================================================================
// Pointer
//=============================================================================
#include "stdafx.h"

namespace Gura {

//-----------------------------------------------------------------------------
// Pointer
//-----------------------------------------------------------------------------
Pointer::Pointer(size_t offset) : _cntRef(1), _offset(offset)
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

//-----------------------------------------------------------------------------
// Pointer::IteratorUnpack
//-----------------------------------------------------------------------------
Pointer::IteratorUnpack::IteratorUnpack(Pointer *pPointer,
				const char *format, const ValueList &valListArg) :
		Iterator(false), _pPointer(pPointer), _format(format), _valListArg(valListArg)
{
}

Iterator *Pointer::IteratorUnpack::GetSource()
{
	return nullptr;
}

bool Pointer::IteratorUnpack::DoNext(Environment &env, Value &value)
{
	value = _pPointer->Unpack(env, true, _format.c_str(), _valListArg, false);
	return value.IsValid();
}

String Pointer::IteratorUnpack::ToString() const
{
	return String("pointer.unpacks");
}

void Pointer::IteratorUnpack::GatherFollower(Environment::Frame *pFrame, EnvironmentSet &envSet)
{
}

}
