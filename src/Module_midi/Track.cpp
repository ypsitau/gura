#include "Track.h"

Gura_BeginModule(midi)

//-----------------------------------------------------------------------------
// Track
//-----------------------------------------------------------------------------
Track::Track() : _cntRef(1), _pEventOwner(new EventOwner())
{
}

bool Track::ParseMML(Signal sig, const char *str)
{
	if (_pMML.get() == NULL) {
		_pMML.reset(new MML(this));
	}
	return _pMML->Parse(sig, str);
}

//-----------------------------------------------------------------------------
// TrackList
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// TrackOwner
//-----------------------------------------------------------------------------
TrackOwner::~TrackOwner()
{
	Clear();
}

void TrackOwner::Clear()
{
	foreach (TrackOwner, ppTrack, *this) {
		Track *pTrack = *ppTrack;
		Track::Delete(pTrack);
	}
	clear();
}

}}
