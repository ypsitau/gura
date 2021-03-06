#include "stdafx.h"
#include "Event.h"
#include "Sequence.h"

Gura_BeginModuleScope(midi)

//-----------------------------------------------------------------------------
// Event
//-----------------------------------------------------------------------------
bool Event::IsMIDIEvent() const { return false; }
bool Event::IsSysExEvent() const { return false; }
bool Event::IsMetaEvent() const { return false; }

Event::~Event()
{
	// virtual destructor
}

bool Event::DoDirProp(Environment &env, SymbolSet &symbols)
{
	return true;
}

Value Event::DoGetProp(Environment &env, const Symbol *pSymbol,
							const SymbolSet &attrs, bool &evaluatedFlag)
{
	return Value::Nil;
}

Value Event::DoSetProp(Environment &env, const Symbol *pSymbol, const Value &value,
								const SymbolSet &attrs, bool &evaluatedFlag)
{
	return Value::Nil;
}

bool Event::WriteVariableFormat(Signal &sig, Stream &stream, ULong num)
{
	UChar buff[32];
	UChar *p = buff + sizeof(buff);
	size_t bytes = 0;
	while (bytes < sizeof(buff)) {
		UChar data = static_cast<UChar>(num & 0x7f);
		if (bytes > 0) data |= 0x80;
		num >>= 7;
		p--, bytes++;
		*p = data;
		if (num == 0) break;
	}
	return stream.Write(sig, p, bytes) == bytes;
}

//-----------------------------------------------------------------------------
// EventList
//-----------------------------------------------------------------------------
void EventList::Sort()
{
	std::stable_sort(begin(), end(), Comparator_TimeStamp());
}

//-----------------------------------------------------------------------------
// EventOwner
//-----------------------------------------------------------------------------
EventOwner::~EventOwner()
{
	Clear();
}

void EventOwner::Clear()
{
	foreach (EventOwner, ppEvent, *this) {
		Event *pEvent = *ppEvent;
		Event::Delete(pEvent);
	}
	clear();
}

void EventOwner::AddEvents(const EventList &eventList)
{
	foreach_const (EventList, ppEvent, eventList) {
		Event *pEvent = *ppEvent;
		push_back(Event::Reference(pEvent));
	}
}

//-----------------------------------------------------------------------------
// MIDIEvent
//-----------------------------------------------------------------------------
bool MIDIEvent::IsMIDIEvent() const { return true; }

UChar MIDIEvent::GetStatusCode() const
{
	return _status | _channel;
}

bool MIDIEvent::Play(Signal &sig, Player *pPlayer) const
{
	if (_nParams == 1) {
		pPlayer->GetPort()->Send(_status | _channel, _params[0]);
	} else {
		pPlayer->GetPort()->Send(_status | _channel, _params[0], _params[1]);
	}
	return true;
}

bool MIDIEvent::Write(Signal &sig, Stream &stream, const Event *pEventPrev) const
{
	size_t bytes = 0;
	UChar buff[8];
	if (!IsEnabledRunningStatus() || pEventPrev == nullptr || !pEventPrev->IsMIDIEvent() ||
			dynamic_cast<const MIDIEvent *>(pEventPrev)->GetStatusByte() != GetStatusByte()) {
		buff[bytes++] = GetStatusByte();
	}
	for (int i = 0; i < _nParams; i++) {
		buff[bytes++] = _params[i];
	}
	return stream.Write(sig, buff, bytes) == bytes;
}

bool MIDIEvent::DoDirProp(Environment &env, SymbolSet &symbols)
{
	symbols.insert(Gura_UserSymbol(channel));
	return true;
}

Value MIDIEvent::DoGetProp(Environment &env, const Symbol *pSymbol,
							const SymbolSet &attrs, bool &evaluatedFlag)
{
	evaluatedFlag = true;
	if (pSymbol->IsIdentical(Gura_UserSymbol(channel))) {
		return Value(GetChannel());
	}
	evaluatedFlag = false;
	return Value::Nil;
}

Value MIDIEvent::DoSetProp(Environment &env, const Symbol *pSymbol, const Value &value,
								const SymbolSet &attrs, bool &evaluatedFlag)
{
	return Value::Nil;
}

//-----------------------------------------------------------------------------
// MIDIEvent_NoteOff
//-----------------------------------------------------------------------------
const Symbol *MIDIEvent_NoteOff::GetSymbol() const
{
	return Gura_UserSymbol(note_off);
}

String MIDIEvent_NoteOff::GetArgsName() const
{
	char str[128];
	::sprintf(str, "channel:%d note:%d velocity:%d",
								GetChannel(), GetNote(), GetVelocity());
	return String(str);
}

Event *MIDIEvent_NoteOff::Clone() const
{
	return new MIDIEvent_NoteOff(*this);
}

bool MIDIEvent_NoteOff::DoDirProp(Environment &env, SymbolSet &symbols)
{
	Signal &sig = env.GetSignal();
	if (!MIDIEvent::DoDirProp(env, symbols)) return false;
	symbols.insert(Gura_UserSymbol(note));
	symbols.insert(Gura_UserSymbol(velocity));
	return true;
}

Value MIDIEvent_NoteOff::DoGetProp(Environment &env, const Symbol *pSymbol,
							const SymbolSet &attrs, bool &evaluatedFlag)
{
	Signal &sig = env.GetSignal();
	evaluatedFlag = true;
	if (pSymbol->IsIdentical(Gura_UserSymbol(note))) {
		return Value(GetNote());
	} else if (pSymbol->IsIdentical(Gura_UserSymbol(velocity))) {
		return Value(GetVelocity());
	}
	evaluatedFlag = false;
	return MIDIEvent::DoGetProp(env, pSymbol, attrs, evaluatedFlag);
}

Value MIDIEvent_NoteOff::DoSetProp(Environment &env, const Symbol *pSymbol, const Value &value,
								const SymbolSet &attrs, bool &evaluatedFlag)
{
	Signal &sig = env.GetSignal();
	evaluatedFlag = true;
	if (pSymbol->IsIdentical(Gura_UserSymbol(note))) {
		if (!value.MustBe_number(sig)) return Value::Nil;
		SetNote(value.GetUChar());
		return Value(GetNote());
	} else if (pSymbol->IsIdentical(Gura_UserSymbol(velocity))) {
		if (!value.MustBe_number(sig)) return Value::Nil;
		SetVelocity(value.GetUChar());
		return Value(GetVelocity());
	}
	evaluatedFlag = false;
	return MIDIEvent::DoSetProp(env, pSymbol, value, attrs, evaluatedFlag);
}

//-----------------------------------------------------------------------------
// MIDIEvent_NoteOn
//-----------------------------------------------------------------------------
const Symbol *MIDIEvent_NoteOn::GetSymbol() const
{
	return Gura_UserSymbol(note_on);
}

String MIDIEvent_NoteOn::GetArgsName() const
{
	char str[128];
	::sprintf(str, "channel:%d note:%d velocity:%d",
								GetChannel(), GetNote(), GetVelocity());
	return String(str);
}

Event *MIDIEvent_NoteOn::Clone() const
{
	return new MIDIEvent_NoteOn(*this);
}

bool MIDIEvent_NoteOn::DoDirProp(Environment &env, SymbolSet &symbols)
{
	Signal &sig = env.GetSignal();
	if (!MIDIEvent::DoDirProp(env, symbols)) return false;
	symbols.insert(Gura_UserSymbol(note));
	symbols.insert(Gura_UserSymbol(velocity));
	return true;
}

Value MIDIEvent_NoteOn::DoGetProp(Environment &env, const Symbol *pSymbol,
							const SymbolSet &attrs, bool &evaluatedFlag)
{
	Signal &sig = env.GetSignal();
	evaluatedFlag = true;
	if (pSymbol->IsIdentical(Gura_UserSymbol(note))) {
		return Value(GetNote());
	} else if (pSymbol->IsIdentical(Gura_UserSymbol(velocity))) {
		return Value(GetVelocity());
	}
	evaluatedFlag = false;
	return MIDIEvent::DoGetProp(env, pSymbol, attrs, evaluatedFlag);
}

Value MIDIEvent_NoteOn::DoSetProp(Environment &env, const Symbol *pSymbol, const Value &value,
								const SymbolSet &attrs, bool &evaluatedFlag)
{
	Signal &sig = env.GetSignal();
	evaluatedFlag = true;
	if (pSymbol->IsIdentical(Gura_UserSymbol(note))) {
		if (!value.MustBe_number(sig)) return Value::Nil;
		SetNote(value.GetUChar());
		return Value(GetNote());
	} else if (pSymbol->IsIdentical(Gura_UserSymbol(velocity))) {
		if (!value.MustBe_number(sig)) return Value::Nil;
		SetVelocity(value.GetUChar());
		return Value(GetVelocity());
	}
	evaluatedFlag = false;
	return MIDIEvent::DoSetProp(env, pSymbol, value, attrs, evaluatedFlag);
}

//-----------------------------------------------------------------------------
// MIDIEvent_PolyPressure
//-----------------------------------------------------------------------------
const Symbol *MIDIEvent_PolyPressure::GetSymbol() const
{
	return Gura_UserSymbol(poly_pressure);
}

String MIDIEvent_PolyPressure::GetArgsName() const
{
	char str[128];
	::sprintf(str, "channel:%d note:%d value:%d",
								GetChannel(), GetNote(), GetValue());
	return String(str);
}

Event *MIDIEvent_PolyPressure::Clone() const
{
	return new MIDIEvent_PolyPressure(*this);
}

bool MIDIEvent_PolyPressure::DoDirProp(Environment &env, SymbolSet &symbols)
{
	Signal &sig = env.GetSignal();
	if (!MIDIEvent::DoDirProp(env, symbols)) return false;
	symbols.insert(Gura_UserSymbol(note));
	symbols.insert(Gura_UserSymbol(value));
	return true;
}

Value MIDIEvent_PolyPressure::DoGetProp(Environment &env, const Symbol *pSymbol,
							const SymbolSet &attrs, bool &evaluatedFlag)
{
	Signal &sig = env.GetSignal();
	evaluatedFlag = true;
	if (pSymbol->IsIdentical(Gura_UserSymbol(note))) {
		return Value(GetNote());
	} else if (pSymbol->IsIdentical(Gura_UserSymbol(value))) {
		return Value(GetValue());
	}
	evaluatedFlag = false;
	return MIDIEvent::DoGetProp(env, pSymbol, attrs, evaluatedFlag);
}

Value MIDIEvent_PolyPressure::DoSetProp(Environment &env, const Symbol *pSymbol, const Value &value,
								const SymbolSet &attrs, bool &evaluatedFlag)
{
	Signal &sig = env.GetSignal();
	evaluatedFlag = true;
	if (pSymbol->IsIdentical(Gura_UserSymbol(note))) {
		if (!value.MustBe_number(sig)) return Value::Nil;
		SetNote(value.GetUChar());
		return Value(GetNote());
	} else if (pSymbol->IsIdentical(Gura_UserSymbol(velocity))) {
		if (!value.MustBe_number(sig)) return Value::Nil;
		SetValue(value.GetUChar());
		return Value(GetValue());
	}
	evaluatedFlag = false;
	return MIDIEvent::DoSetProp(env, pSymbol, value, attrs, evaluatedFlag);
}

//-----------------------------------------------------------------------------
// MIDIEvent_ControlChange
//-----------------------------------------------------------------------------
const Symbol *MIDIEvent_ControlChange::GetSymbol() const
{
	return Gura_UserSymbol(control_change);
}

String MIDIEvent_ControlChange::GetArgsName() const
{
	char str[128];
	const ControllerInfo *pControllerInfo = ControllerInfoById(GetController());
	::sprintf(str, "channel:%d controller:%s(%d) value:%d",
		GetChannel(), (pControllerInfo == nullptr)? "unknown" : pControllerInfo->name,
		GetController(), GetValue());
	return String(str);
}

Event *MIDIEvent_ControlChange::Clone() const
{
	return new MIDIEvent_ControlChange(*this);
}

bool MIDIEvent_ControlChange::DoDirProp(Environment &env, SymbolSet &symbols)
{
	Signal &sig = env.GetSignal();
	if (!MIDIEvent::DoDirProp(env, symbols)) return false;
	symbols.insert(Gura_UserSymbol(controller));
	symbols.insert(Gura_UserSymbol(value));
	return true;
}

Value MIDIEvent_ControlChange::DoGetProp(Environment &env, const Symbol *pSymbol,
							const SymbolSet &attrs, bool &evaluatedFlag)
{
	Signal &sig = env.GetSignal();
	evaluatedFlag = true;
	if (pSymbol->IsIdentical(Gura_UserSymbol(controller))) {
		if (attrs.IsSet(Gura_Symbol(symbol))) {
			const ControllerInfo *pControllerInfo = ControllerInfoById(GetController());
			if (pControllerInfo == nullptr) {
				return Value::Nil;
			} else {
				return Value(pControllerInfo->pSymbol);
			}
		} else {
			return Value(GetController());
		}
	} else if (pSymbol->IsIdentical(Gura_UserSymbol(value))) {
		return Value(GetValue());
	}
	evaluatedFlag = false;
	return MIDIEvent::DoGetProp(env, pSymbol, attrs, evaluatedFlag);
}

Value MIDIEvent_ControlChange::DoSetProp(Environment &env, const Symbol *pSymbol, const Value &value,
								const SymbolSet &attrs, bool &evaluatedFlag)
{
	Signal &sig = env.GetSignal();
	evaluatedFlag = true;
	if (pSymbol->IsIdentical(Gura_UserSymbol(controller))) {
		if (!value.MustBe_number(sig)) return Value::Nil;
		SetController(value.GetUChar());
		return Value(GetController());
	} else if (pSymbol->IsIdentical(Gura_UserSymbol(value))) {
		if (!value.MustBe_number(sig)) return Value::Nil;
		SetValue(value.GetUChar());
		return Value(GetValue());
	}
	evaluatedFlag = false;
	return MIDIEvent::DoSetProp(env, pSymbol, value, attrs, evaluatedFlag);
}

//-----------------------------------------------------------------------------
// MIDIEvent_ProgramChange
//-----------------------------------------------------------------------------
const Symbol *MIDIEvent_ProgramChange::GetSymbol() const
{
	return Gura_UserSymbol(program_change);
}

String MIDIEvent_ProgramChange::GetArgsName() const
{
	char str[128];
	const ProgramInfo *pProgramInfo = ProgramInfoById(GetProgram());
	::sprintf(str, "channel:%d program:%s(%d)", GetChannel(),
		(pProgramInfo == nullptr)? "unknown" : pProgramInfo->name, GetProgram());
	return String(str);
}

Event *MIDIEvent_ProgramChange::Clone() const
{
	return new MIDIEvent_ProgramChange(*this);
}

bool MIDIEvent_ProgramChange::DoDirProp(Environment &env, SymbolSet &symbols)
{
	Signal &sig = env.GetSignal();
	if (!MIDIEvent::DoDirProp(env, symbols)) return false;
	symbols.insert(Gura_UserSymbol(program));
	return true;
}

Value MIDIEvent_ProgramChange::DoGetProp(Environment &env, const Symbol *pSymbol,
							const SymbolSet &attrs, bool &evaluatedFlag)
{
	Signal &sig = env.GetSignal();
	evaluatedFlag = true;
	if (pSymbol->IsIdentical(Gura_UserSymbol(program))) {
		return Value(GetProgram());
	}
	evaluatedFlag = false;
	return MIDIEvent::DoGetProp(env, pSymbol, attrs, evaluatedFlag);
}

Value MIDIEvent_ProgramChange::DoSetProp(Environment &env, const Symbol *pSymbol, const Value &value,
								const SymbolSet &attrs, bool &evaluatedFlag)
{
	Signal &sig = env.GetSignal();
	evaluatedFlag = true;
	if (pSymbol->IsIdentical(Gura_UserSymbol(program))) {
		if (!value.MustBe_number(sig)) return Value::Nil;
		SetProgram(value.GetUChar());
		return Value(GetProgram());
	}
	evaluatedFlag = false;
	return MIDIEvent::DoSetProp(env, pSymbol, value, attrs, evaluatedFlag);
}

//-----------------------------------------------------------------------------
// MIDIEvent_ChannelPressure
//-----------------------------------------------------------------------------
const Symbol *MIDIEvent_ChannelPressure::GetSymbol() const
{
	return Gura_UserSymbol(channel_pressure);
}

String MIDIEvent_ChannelPressure::GetArgsName() const
{
	char str[128];
	::sprintf(str, "channel:%d pressure:%d", GetChannel(), GetPressure());
	return String(str);
}

Event *MIDIEvent_ChannelPressure::Clone() const
{
	return new MIDIEvent_ChannelPressure(*this);
}

bool MIDIEvent_ChannelPressure::DoDirProp(Environment &env, SymbolSet &symbols)
{
	Signal &sig = env.GetSignal();
	if (!MIDIEvent::DoDirProp(env, symbols)) return false;
	symbols.insert(Gura_UserSymbol(pressure));
	return true;
}

Value MIDIEvent_ChannelPressure::DoGetProp(Environment &env, const Symbol *pSymbol,
							const SymbolSet &attrs, bool &evaluatedFlag)
{
	Signal &sig = env.GetSignal();
	evaluatedFlag = true;
	if (pSymbol->IsIdentical(Gura_UserSymbol(pressure))) {
		return Value(GetPressure());
	}
	evaluatedFlag = false;
	return MIDIEvent::DoGetProp(env, pSymbol, attrs, evaluatedFlag);
}

Value MIDIEvent_ChannelPressure::DoSetProp(Environment &env, const Symbol *pSymbol, const Value &value,
								const SymbolSet &attrs, bool &evaluatedFlag)
{
	Signal &sig = env.GetSignal();
	evaluatedFlag = true;
	if (pSymbol->IsIdentical(Gura_UserSymbol(pressure))) {
		if (!value.MustBe_number(sig)) return Value::Nil;
		SetPressure(value.GetUChar());
		return Value(GetPressure());
	}
	evaluatedFlag = false;
	return MIDIEvent::DoSetProp(env, pSymbol, value, attrs, evaluatedFlag);
}

//-----------------------------------------------------------------------------
// MIDIEvent_PitchBend
//-----------------------------------------------------------------------------
const Symbol *MIDIEvent_PitchBend::GetSymbol() const
{
	return Gura_UserSymbol(pitch_bend);
}

String MIDIEvent_PitchBend::GetArgsName() const
{
	char str[128];
	::sprintf(str, "channel:%d value:%d", GetChannel(), GetValue());
	return String(str);
}

Event *MIDIEvent_PitchBend::Clone() const
{
	return new MIDIEvent_PitchBend(*this);
}

bool MIDIEvent_PitchBend::DoDirProp(Environment &env, SymbolSet &symbols)
{
	Signal &sig = env.GetSignal();
	if (!MIDIEvent::DoDirProp(env, symbols)) return false;
	symbols.insert(Gura_UserSymbol(value));
	return true;
}

Value MIDIEvent_PitchBend::DoGetProp(Environment &env, const Symbol *pSymbol,
							const SymbolSet &attrs, bool &evaluatedFlag)
{
	Signal &sig = env.GetSignal();
	evaluatedFlag = true;
	if (pSymbol->IsIdentical(Gura_UserSymbol(value))) {
		return Value(GetValue());
	}
	evaluatedFlag = false;
	return MIDIEvent::DoGetProp(env, pSymbol, attrs, evaluatedFlag);
}

Value MIDIEvent_PitchBend::DoSetProp(Environment &env, const Symbol *pSymbol, const Value &value,
								const SymbolSet &attrs, bool &evaluatedFlag)
{
	Signal &sig = env.GetSignal();
	evaluatedFlag = true;
	if (pSymbol->IsIdentical(Gura_UserSymbol(value))) {
		if (!value.MustBe_number(sig)) return Value::Nil;
		SetValue(value.GetUShort());
		return Value(GetValue());
	}
	evaluatedFlag = false;
	return MIDIEvent::DoSetProp(env, pSymbol, value, attrs, evaluatedFlag);
}

//-----------------------------------------------------------------------------
// SysExEvent
//-----------------------------------------------------------------------------
bool SysExEvent::IsSysExEvent() const { return true; }

UChar SysExEvent::GetStatusCode() const
{
	return static_cast<UChar>(_binary[0]);
}

const Symbol *SysExEvent::GetSymbol() const
{
	return Gura_UserSymbol(sys_ex_event);
}

String SysExEvent::GetArgsName() const
{
	char str[128];
	::sprintf(str, "%lubytes", _binary.size());
	return String(str);
}

bool SysExEvent::Play(Signal &sig, Player *pPlayer) const
{
	return true;
}

bool SysExEvent::Write(Signal &sig, Stream &stream, const Event *pEventPrev) const
{
	return stream.Write(sig, _binary.data(), _binary.size()) == _binary.size();
}

Event *SysExEvent::Clone() const
{
	return new SysExEvent(*this);
}

bool SysExEvent::DoDirProp(Environment &env, SymbolSet &symbols)
{
	symbols.insert(Gura_UserSymbol(binary));
	return true;
}

Value SysExEvent::DoGetProp(Environment &env, const Symbol *pSymbol,
							const SymbolSet &attrs, bool &evaluatedFlag)
{
	evaluatedFlag = true;
	if (pSymbol->IsIdentical(Gura_UserSymbol(binary))) {
		return Value(new Object_binary(env, _binary, false));
	}
	evaluatedFlag = false;
	return Value::Nil;
}

Value SysExEvent::DoSetProp(Environment &env, const Symbol *pSymbol, const Value &value,
								const SymbolSet &attrs, bool &evaluatedFlag)
{
	Signal &sig = env.GetSignal();
	evaluatedFlag = true;
	if (pSymbol->IsIdentical(Gura_UserSymbol(binary))) {
		if (!value.MustBe_binary(sig)) return Value::Nil;
		_binary = value.GetBinary();
		return value;
	}
	evaluatedFlag = false;
	return Value::Nil;
}

//-----------------------------------------------------------------------------
// MetaEvent
//-----------------------------------------------------------------------------
bool MetaEvent::IsMetaEvent() const { return true; }

UChar MetaEvent::GetStatusCode() const
{
	return Status;
}

bool MetaEvent::Add(Signal &sig, Track *pTrack, bool enableRunningStatus,
		ULong timeStamp, UChar eventType, const Binary &binary)
{
	MetaEvent *pEvent = nullptr;
	if (eventType == MetaEvent_SequenceNumber::EventType) {
		pEvent = new MetaEvent_SequenceNumber(timeStamp);
	} else if (eventType == MetaEvent_TextEvent::EventType) {
		pEvent = new MetaEvent_TextEvent(timeStamp);
	} else if (eventType == MetaEvent_CopyrightNotice::EventType) {
		pEvent = new MetaEvent_CopyrightNotice(timeStamp);
	} else if (eventType == MetaEvent_SequenceOrTrackName::EventType) {
		pEvent = new MetaEvent_SequenceOrTrackName(timeStamp);
	} else if (eventType == MetaEvent_InstrumentName::EventType) {
		pEvent = new MetaEvent_InstrumentName(timeStamp);
	} else if (eventType == MetaEvent_LyricText::EventType) {
		pEvent = new MetaEvent_LyricText(timeStamp);
	} else if (eventType == MetaEvent_MarkerText::EventType) {
		pEvent = new MetaEvent_MarkerText(timeStamp);
	} else if (eventType == MetaEvent_CuePoint::EventType) {
		pEvent = new MetaEvent_CuePoint(timeStamp);
	} else if (eventType == MetaEvent_MIDIChannelPrefixAssignment::EventType) {
		pEvent = new MetaEvent_MIDIChannelPrefixAssignment(timeStamp);
	} else if (eventType == MetaEvent_EndOfTrack::EventType) {
		pEvent = new MetaEvent_EndOfTrack(timeStamp);
	} else if (eventType == MetaEvent_TempoSetting::EventType) {
		pEvent = new MetaEvent_TempoSetting(timeStamp);
	} else if (eventType == MetaEvent_SMPTEOffset::EventType) {
		pEvent = new MetaEvent_SMPTEOffset(timeStamp);
	} else if (eventType == MetaEvent_TimeSignature::EventType) {
		pEvent = new MetaEvent_TimeSignature(timeStamp);
	} else if (eventType == MetaEvent_KeySignature::EventType) {
		pEvent = new MetaEvent_KeySignature(timeStamp);
	} else if (eventType == MetaEvent_SequencerSpecificEvent::EventType) {
		pEvent = new MetaEvent_SequencerSpecificEvent(timeStamp);
	} else {
		pEvent = new MetaEvent_Unknown(timeStamp, eventType);
	}
	pEvent->EnableRunningStatus(enableRunningStatus);
	if (pEvent->Prepare(sig, binary)) {
		pTrack->AddEvent(pEvent);
		return true;
	}
	delete pEvent;
	return false;
}

bool MetaEvent::Write(Signal &sig, Stream &stream, const Event *pEventPrev) const
{
	size_t bytes = 0;
	UChar buff[2];
	if (!IsEnabledRunningStatus() || pEventPrev == nullptr || !pEventPrev->IsMetaEvent()) {
		buff[bytes++] = Status;
	}
	buff[bytes++] = _eventType;
	return stream.Write(sig, buff, bytes) == bytes;
}

void MetaEvent::SetError_TooShortMetaEvent(Signal &sig)
{
	sig.SetError(ERR_FormatError, "too short meta event");
}

//-----------------------------------------------------------------------------
// MetaEvent_Unknown
//-----------------------------------------------------------------------------
bool MetaEvent_Unknown::Prepare(Signal &sig, const Binary &binary)
{
	_binary = binary;
	return true;
}

bool MetaEvent_Unknown::Play(Signal &sig, Player *pPlayer) const
{
	return true;
}

bool MetaEvent_Unknown::Write(Signal &sig, Stream &stream, const Event *pEventPrev) const
{
	if (!MetaEvent::Write(sig, stream, pEventPrev)) return false;
	if (!WriteVariableFormat(sig, stream, static_cast<ULong>(_binary.size()))) return false;
	return stream.Write(sig, _binary.data(), _binary.size()) == _binary.size();
}

const Symbol *MetaEvent_Unknown::GetSymbol() const
{
	return Gura_UserSymbol(unknown);
}

String MetaEvent_Unknown::GetArgsName() const
{
	char str[128];
	::sprintf(str, "%lubytes", _binary.size());
	return String(str);
}

Event *MetaEvent_Unknown::Clone() const
{
	return new MetaEvent_Unknown(*this);
}

bool MetaEvent_Unknown::DoDirProp(Environment &env, SymbolSet &symbols)
{
	symbols.insert(Gura_UserSymbol(binary));
	return true;
}

Value MetaEvent_Unknown::DoGetProp(Environment &env, const Symbol *pSymbol,
							const SymbolSet &attrs, bool &evaluatedFlag)
{
	evaluatedFlag = true;
	if (pSymbol->IsIdentical(Gura_UserSymbol(binary))) {
		return Value(new Object_binary(env, _binary, false));
	}
	evaluatedFlag = false;
	return Value::Nil;
}

Value MetaEvent_Unknown::DoSetProp(Environment &env, const Symbol *pSymbol, const Value &value,
								const SymbolSet &attrs, bool &evaluatedFlag)
{
	Signal &sig = env.GetSignal();
	evaluatedFlag = true;
	if (pSymbol->IsIdentical(Gura_UserSymbol(binary))) {
		if (!value.MustBe_binary(sig)) return Value::Nil;
		_binary = value.GetBinary();
		return value;
	}
	evaluatedFlag = false;
	return Value::Nil;
}

//-----------------------------------------------------------------------------
// MetaEvent_SequenceNumber
//-----------------------------------------------------------------------------
bool MetaEvent_SequenceNumber::Prepare(Signal &sig, const Binary &binary)
{
	if (binary.size() < 2) {
		SetError_TooShortMetaEvent(sig);
		return false;
	}
	_number =
		(static_cast<UShort>(static_cast<UChar>(binary[0])) << 8) +
		(static_cast<UShort>(static_cast<UChar>(binary[1])) << 0);
	return true;
}

bool MetaEvent_SequenceNumber::Play(Signal &sig, Player *pPlayer) const
{
	return true;
}

bool MetaEvent_SequenceNumber::Write(Signal &sig, Stream &stream, const Event *pEventPrev) const
{
	if (!MetaEvent::Write(sig, stream, pEventPrev)) return false;
	const size_t bytes = 2;
	UChar buff[bytes];
	buff[0] = static_cast<UChar>(_number >> 8);
	buff[1] = static_cast<UChar>(_number >> 0);
	if (!WriteVariableFormat(sig, stream, static_cast<ULong>(bytes))) return false;
	return stream.Write(sig, buff, bytes) == bytes;
}

const Symbol *MetaEvent_SequenceNumber::GetSymbol() const
{
	return Gura_UserSymbol(sequence_number);
}

String MetaEvent_SequenceNumber::GetArgsName() const
{
	char str[128];
	::sprintf(str, "number:%d", _number);
	return String(str);
}

Event *MetaEvent_SequenceNumber::Clone() const
{
	return new MetaEvent_SequenceNumber(*this);
}

bool MetaEvent_SequenceNumber::DoDirProp(Environment &env, SymbolSet &symbols)
{
	symbols.insert(Gura_UserSymbol(number));
	return true;
}

Value MetaEvent_SequenceNumber::DoGetProp(Environment &env, const Symbol *pSymbol,
							const SymbolSet &attrs, bool &evaluatedFlag)
{
	evaluatedFlag = true;
	if (pSymbol->IsIdentical(Gura_UserSymbol(number))) {
		return Value(_number);
	}
	evaluatedFlag = false;
	return Value::Nil;
}

Value MetaEvent_SequenceNumber::DoSetProp(Environment &env, const Symbol *pSymbol, const Value &value,
								const SymbolSet &attrs, bool &evaluatedFlag)
{
	Signal &sig = env.GetSignal();
	evaluatedFlag = true;
	if (pSymbol->IsIdentical(Gura_UserSymbol(number))) {
		if (!value.MustBe_number(sig)) return Value::Nil;
		_number = value.GetUShort();
		return Value(_number);
	}
	evaluatedFlag = false;
	return Value::Nil;
}

//-----------------------------------------------------------------------------
// MetaEvent_TextEvent
//-----------------------------------------------------------------------------
bool MetaEvent_TextEvent::Prepare(Signal &sig, const Binary &binary)
{
	_text = String(binary);
	return true;
}

bool MetaEvent_TextEvent::Play(Signal &sig, Player *pPlayer) const
{
	return true;
}

bool MetaEvent_TextEvent::Write(Signal &sig, Stream &stream, const Event *pEventPrev) const
{
	if (!MetaEvent::Write(sig, stream, pEventPrev)) return false;
	if (!WriteVariableFormat(sig, stream, static_cast<ULong>(_text.size()))) return false;
	return stream.Write(sig, _text.data(), _text.size()) == _text.size();
}

const Symbol *MetaEvent_TextEvent::GetSymbol() const
{
	return Gura_UserSymbol(text_event);
}

String MetaEvent_TextEvent::GetArgsName() const
{
	char str[128];
	::sprintf(str, "text:%s", MakeQuotedString(_text.c_str()).c_str());
	return String(str);
}

Event *MetaEvent_TextEvent::Clone() const
{
	return new MetaEvent_TextEvent(*this);
}

bool MetaEvent_TextEvent::DoDirProp(Environment &env, SymbolSet &symbols)
{
	symbols.insert(Gura_UserSymbol(text));
	return true;
}

Value MetaEvent_TextEvent::DoGetProp(Environment &env, const Symbol *pSymbol,
							const SymbolSet &attrs, bool &evaluatedFlag)
{
	evaluatedFlag = true;
	if (pSymbol->IsIdentical(Gura_UserSymbol(text))) {
		return Value(_text);
	}
	evaluatedFlag = false;
	return Value::Nil;
}

Value MetaEvent_TextEvent::DoSetProp(Environment &env, const Symbol *pSymbol, const Value &value,
								const SymbolSet &attrs, bool &evaluatedFlag)
{
	Signal &sig = env.GetSignal();
	evaluatedFlag = true;
	if (pSymbol->IsIdentical(Gura_UserSymbol(text))) {
		if (!value.MustBe_string(sig)) return Value::Nil;
		_text = value.GetStringSTL();
		return value;
	}
	evaluatedFlag = false;
	return Value::Nil;
}

//-----------------------------------------------------------------------------
// MetaEvent_CopyrightNotice
//-----------------------------------------------------------------------------
bool MetaEvent_CopyrightNotice::Prepare(Signal &sig, const Binary &binary)
{
	_text = String(binary);
	return true;
}

bool MetaEvent_CopyrightNotice::Play(Signal &sig, Player *pPlayer) const
{
	return true;
}

bool MetaEvent_CopyrightNotice::Write(Signal &sig, Stream &stream, const Event *pEventPrev) const
{
	if (!MetaEvent::Write(sig, stream, pEventPrev)) return false;
	if (!WriteVariableFormat(sig, stream, static_cast<ULong>(_text.size()))) return false;
	return stream.Write(sig, _text.data(), _text.size()) == _text.size();
}

const Symbol *MetaEvent_CopyrightNotice::GetSymbol() const
{
	return Gura_UserSymbol(copyright_notice);
}

String MetaEvent_CopyrightNotice::GetArgsName() const
{
	char str[128];
	::sprintf(str, "text:%s", MakeQuotedString(_text.c_str()).c_str());
	return String(str);
}

Event *MetaEvent_CopyrightNotice::Clone() const
{
	return new MetaEvent_CopyrightNotice(*this);
}

bool MetaEvent_CopyrightNotice::DoDirProp(Environment &env, SymbolSet &symbols)
{
	symbols.insert(Gura_UserSymbol(text));
	return true;
}

Value MetaEvent_CopyrightNotice::DoGetProp(Environment &env, const Symbol *pSymbol,
							const SymbolSet &attrs, bool &evaluatedFlag)
{
	evaluatedFlag = true;
	if (pSymbol->IsIdentical(Gura_UserSymbol(text))) {
		return Value(_text);
	}
	evaluatedFlag = false;
	return Value::Nil;
}

Value MetaEvent_CopyrightNotice::DoSetProp(Environment &env, const Symbol *pSymbol, const Value &value,
								const SymbolSet &attrs, bool &evaluatedFlag)
{
	Signal &sig = env.GetSignal();
	evaluatedFlag = true;
	if (pSymbol->IsIdentical(Gura_UserSymbol(text))) {
		if (!value.MustBe_string(sig)) return Value::Nil;
		_text = value.GetStringSTL();
		return value;
	}
	evaluatedFlag = false;
	return Value::Nil;
}

//-----------------------------------------------------------------------------
// MetaEvent_SequenceOrTrackName
//-----------------------------------------------------------------------------
bool MetaEvent_SequenceOrTrackName::Prepare(Signal &sig, const Binary &binary)
{
	_text = String(binary);
	return true;
}

bool MetaEvent_SequenceOrTrackName::Play(Signal &sig, Player *pPlayer) const
{
	return true;
}

bool MetaEvent_SequenceOrTrackName::Write(Signal &sig, Stream &stream, const Event *pEventPrev) const
{
	if (!MetaEvent::Write(sig, stream, pEventPrev)) return false;
	if (!WriteVariableFormat(sig, stream, static_cast<ULong>(_text.size()))) return false;
	return stream.Write(sig, _text.data(), _text.size()) == _text.size();
}

const Symbol *MetaEvent_SequenceOrTrackName::GetSymbol() const
{
	return Gura_UserSymbol(sequence_or_track_name);
}

String MetaEvent_SequenceOrTrackName::GetArgsName() const
{
	char str[128];
	::sprintf(str, "text:%s", MakeQuotedString(_text.c_str()).c_str());
	return String(str);
}

Event *MetaEvent_SequenceOrTrackName::Clone() const
{
	return new MetaEvent_SequenceOrTrackName(*this);
}

bool MetaEvent_SequenceOrTrackName::DoDirProp(Environment &env, SymbolSet &symbols)
{
	symbols.insert(Gura_UserSymbol(text));
	return true;
}

Value MetaEvent_SequenceOrTrackName::DoGetProp(Environment &env, const Symbol *pSymbol,
							const SymbolSet &attrs, bool &evaluatedFlag)
{
	evaluatedFlag = true;
	if (pSymbol->IsIdentical(Gura_UserSymbol(text))) {
		return Value(_text);
	}
	evaluatedFlag = false;
	return Value::Nil;
}

Value MetaEvent_SequenceOrTrackName::DoSetProp(Environment &env, const Symbol *pSymbol, const Value &value,
								const SymbolSet &attrs, bool &evaluatedFlag)
{
	Signal &sig = env.GetSignal();
	evaluatedFlag = true;
	if (pSymbol->IsIdentical(Gura_UserSymbol(text))) {
		if (!value.MustBe_string(sig)) return Value::Nil;
		_text = value.GetStringSTL();
		return value;
	}
	evaluatedFlag = false;
	return Value::Nil;
}

//-----------------------------------------------------------------------------
// MetaEvent_InstrumentName
//-----------------------------------------------------------------------------
bool MetaEvent_InstrumentName::Prepare(Signal &sig, const Binary &binary)
{
	_text = String(binary);
	return true;
}

bool MetaEvent_InstrumentName::Play(Signal &sig, Player *pPlayer) const
{
	return true;
}

bool MetaEvent_InstrumentName::Write(Signal &sig, Stream &stream, const Event *pEventPrev) const
{
	if (!MetaEvent::Write(sig, stream, pEventPrev)) return false;
	if (!WriteVariableFormat(sig, stream, static_cast<ULong>(_text.size()))) return false;
	return stream.Write(sig, _text.data(), _text.size()) == _text.size();
}

const Symbol *MetaEvent_InstrumentName::GetSymbol() const
{
	return Gura_UserSymbol(instrument_name);
}

String MetaEvent_InstrumentName::GetArgsName() const
{
	char str[128];
	::sprintf(str, "text:%s", MakeQuotedString(_text.c_str()).c_str());
	return String(str);
}

Event *MetaEvent_InstrumentName::Clone() const
{
	return new MetaEvent_InstrumentName(*this);
}

bool MetaEvent_InstrumentName::DoDirProp(Environment &env, SymbolSet &symbols)
{
	symbols.insert(Gura_UserSymbol(text));
	return true;
}

Value MetaEvent_InstrumentName::DoGetProp(Environment &env, const Symbol *pSymbol,
							const SymbolSet &attrs, bool &evaluatedFlag)
{
	evaluatedFlag = true;
	if (pSymbol->IsIdentical(Gura_UserSymbol(text))) {
		return Value(_text);
	}
	evaluatedFlag = false;
	return Value::Nil;
}

Value MetaEvent_InstrumentName::DoSetProp(Environment &env, const Symbol *pSymbol, const Value &value,
								const SymbolSet &attrs, bool &evaluatedFlag)
{
	Signal &sig = env.GetSignal();
	evaluatedFlag = true;
	if (pSymbol->IsIdentical(Gura_UserSymbol(text))) {
		if (!value.MustBe_string(sig)) return Value::Nil;
		_text = value.GetStringSTL();
		return value;
	}
	evaluatedFlag = false;
	return Value::Nil;
}

//-----------------------------------------------------------------------------
// MetaEvent_LyricText
//-----------------------------------------------------------------------------
bool MetaEvent_LyricText::Prepare(Signal &sig, const Binary &binary)
{
	_text = String(binary);
	return true;
}

bool MetaEvent_LyricText::Play(Signal &sig, Player *pPlayer) const
{
	return true;
}

bool MetaEvent_LyricText::Write(Signal &sig, Stream &stream, const Event *pEventPrev) const
{
	if (!MetaEvent::Write(sig, stream, pEventPrev)) return false;
	if (!WriteVariableFormat(sig, stream, static_cast<ULong>(_text.size()))) return false;
	return stream.Write(sig, _text.data(), _text.size()) == _text.size();
}

const Symbol *MetaEvent_LyricText::GetSymbol() const
{
	return Gura_UserSymbol(lyric_text);
}

String MetaEvent_LyricText::GetArgsName() const
{
	char str[128];
	::sprintf(str, "text:%s", MakeQuotedString(_text.c_str()).c_str());
	return String(str);
}

Event *MetaEvent_LyricText::Clone() const
{
	return new MetaEvent_LyricText(*this);
}

bool MetaEvent_LyricText::DoDirProp(Environment &env, SymbolSet &symbols)
{
	symbols.insert(Gura_UserSymbol(text));
	return true;
}

Value MetaEvent_LyricText::DoGetProp(Environment &env, const Symbol *pSymbol,
							const SymbolSet &attrs, bool &evaluatedFlag)
{
	evaluatedFlag = true;
	if (pSymbol->IsIdentical(Gura_UserSymbol(text))) {
		return Value(_text);
	}
	evaluatedFlag = false;
	return Value::Nil;
}

Value MetaEvent_LyricText::DoSetProp(Environment &env, const Symbol *pSymbol, const Value &value,
								const SymbolSet &attrs, bool &evaluatedFlag)
{
	Signal &sig = env.GetSignal();
	evaluatedFlag = true;
	if (pSymbol->IsIdentical(Gura_UserSymbol(text))) {
		if (!value.MustBe_string(sig)) return Value::Nil;
		_text = value.GetStringSTL();
		return value;
	}
	evaluatedFlag = false;
	return Value::Nil;
}

//-----------------------------------------------------------------------------
// MetaEvent_MarkerText
//-----------------------------------------------------------------------------
bool MetaEvent_MarkerText::Prepare(Signal &sig, const Binary &binary)
{
	_text = String(binary);
	return true;
}

bool MetaEvent_MarkerText::Play(Signal &sig, Player *pPlayer) const
{
	return true;
}

bool MetaEvent_MarkerText::Write(Signal &sig, Stream &stream, const Event *pEventPrev) const
{
	if (!MetaEvent::Write(sig, stream, pEventPrev)) return false;
	if (!WriteVariableFormat(sig, stream, static_cast<ULong>(_text.size()))) return false;
	return stream.Write(sig, _text.data(), _text.size()) == _text.size();
}

const Symbol *MetaEvent_MarkerText::GetSymbol() const
{
	return Gura_UserSymbol(marker_text);
}

String MetaEvent_MarkerText::GetArgsName() const
{
	char str[128];
	::sprintf(str, "text:%s", MakeQuotedString(_text.c_str()).c_str());
	return String(str);
}

Event *MetaEvent_MarkerText::Clone() const
{
	return new MetaEvent_MarkerText(*this);
}

bool MetaEvent_MarkerText::DoDirProp(Environment &env, SymbolSet &symbols)
{
	symbols.insert(Gura_UserSymbol(text));
	return true;
}

Value MetaEvent_MarkerText::DoGetProp(Environment &env, const Symbol *pSymbol,
							const SymbolSet &attrs, bool &evaluatedFlag)
{
	evaluatedFlag = true;
	if (pSymbol->IsIdentical(Gura_UserSymbol(text))) {
		return Value(_text);
	}
	evaluatedFlag = false;
	return Value::Nil;
}

Value MetaEvent_MarkerText::DoSetProp(Environment &env, const Symbol *pSymbol, const Value &value,
								const SymbolSet &attrs, bool &evaluatedFlag)
{
	Signal &sig = env.GetSignal();
	evaluatedFlag = true;
	if (pSymbol->IsIdentical(Gura_UserSymbol(text))) {
		if (!value.MustBe_string(sig)) return Value::Nil;
		_text = value.GetStringSTL();
		return value;
	}
	evaluatedFlag = false;
	return Value::Nil;
}

//-----------------------------------------------------------------------------
// MetaEvent_CuePoint
//-----------------------------------------------------------------------------
bool MetaEvent_CuePoint::Prepare(Signal &sig, const Binary &binary)
{
	_text = String(binary);
	return true;
}

bool MetaEvent_CuePoint::Play(Signal &sig, Player *pPlayer) const
{
	return true;
}

bool MetaEvent_CuePoint::Write(Signal &sig, Stream &stream, const Event *pEventPrev) const
{
	if (!MetaEvent::Write(sig, stream, pEventPrev)) return false;
	if (!WriteVariableFormat(sig, stream, static_cast<ULong>(_text.size()))) return false;
	return stream.Write(sig, _text.data(), _text.size()) == _text.size();
}

const Symbol *MetaEvent_CuePoint::GetSymbol() const
{
	return Gura_UserSymbol(cue_point);
}

String MetaEvent_CuePoint::GetArgsName() const
{
	char str[128];
	::sprintf(str, "text:%s", MakeQuotedString(_text.c_str()).c_str());
	return String(str);
}

Event *MetaEvent_CuePoint::Clone() const
{
	return new MetaEvent_CuePoint(*this);
}

bool MetaEvent_CuePoint::DoDirProp(Environment &env, SymbolSet &symbols)
{
	symbols.insert(Gura_UserSymbol(text));
	return true;
}

Value MetaEvent_CuePoint::DoGetProp(Environment &env, const Symbol *pSymbol,
							const SymbolSet &attrs, bool &evaluatedFlag)
{
	evaluatedFlag = true;
	if (pSymbol->IsIdentical(Gura_UserSymbol(text))) {
		return Value(_text);
	}
	evaluatedFlag = false;
	return Value::Nil;
}

Value MetaEvent_CuePoint::DoSetProp(Environment &env, const Symbol *pSymbol, const Value &value,
								const SymbolSet &attrs, bool &evaluatedFlag)
{
	Signal &sig = env.GetSignal();
	evaluatedFlag = true;
	if (pSymbol->IsIdentical(Gura_UserSymbol(text))) {
		if (!value.MustBe_string(sig)) return Value::Nil;
		_text = value.GetStringSTL();
		return value;
	}
	evaluatedFlag = false;
	return Value::Nil;
}

//-----------------------------------------------------------------------------
// MetaEvent_MIDIChannelPrefixAssignment
//-----------------------------------------------------------------------------
bool MetaEvent_MIDIChannelPrefixAssignment::Prepare(Signal &sig, const Binary &binary)
{
	if (binary.size() < 1) {
		SetError_TooShortMetaEvent(sig);
		return false;
	}
	_channel = static_cast<UChar>(binary[0]);
	return true;
}

bool MetaEvent_MIDIChannelPrefixAssignment::Play(Signal &sig, Player *pPlayer) const
{
	return true;
}

bool MetaEvent_MIDIChannelPrefixAssignment::Write(Signal &sig, Stream &stream, const Event *pEventPrev) const
{
	if (!MetaEvent::Write(sig, stream, pEventPrev)) return false;
	const size_t bytes = 1;
	UChar buff[bytes];
	buff[0] = _channel;
	if (!WriteVariableFormat(sig, stream, static_cast<ULong>(bytes))) return false;
	return stream.Write(sig, buff, bytes) == bytes;
}

const Symbol *MetaEvent_MIDIChannelPrefixAssignment::GetSymbol() const
{
	return Gura_UserSymbol(midi_channel_prefix_assignment);
}

String MetaEvent_MIDIChannelPrefixAssignment::GetArgsName() const
{
	char str[128];
	::sprintf(str, "channel:%d", _channel);
	return String(str);
}

Event *MetaEvent_MIDIChannelPrefixAssignment::Clone() const
{
	return new MetaEvent_MIDIChannelPrefixAssignment(*this);
}

bool MetaEvent_MIDIChannelPrefixAssignment::DoDirProp(Environment &env, SymbolSet &symbols)
{
	symbols.insert(Gura_UserSymbol(channel));
	return true;
}

Value MetaEvent_MIDIChannelPrefixAssignment::DoGetProp(Environment &env, const Symbol *pSymbol,
							const SymbolSet &attrs, bool &evaluatedFlag)
{
	evaluatedFlag = true;
	if (pSymbol->IsIdentical(Gura_UserSymbol(channel))) {
		return Value(_channel);
	}
	evaluatedFlag = false;
	return Value::Nil;
}

Value MetaEvent_MIDIChannelPrefixAssignment::DoSetProp(Environment &env, const Symbol *pSymbol, const Value &value,
								const SymbolSet &attrs, bool &evaluatedFlag)
{
	Signal &sig = env.GetSignal();
	evaluatedFlag = true;
	if (pSymbol->IsIdentical(Gura_UserSymbol(channel))) {
		if (!value.MustBe_number(sig)) return Value::Nil;
		_channel = value.GetUChar();
		return Value(_channel);
	}
	evaluatedFlag = false;
	return Value::Nil;
}

//-----------------------------------------------------------------------------
// MetaEvent_EndOfTrack
//-----------------------------------------------------------------------------
bool MetaEvent_EndOfTrack::Prepare(Signal &sig, const Binary &binary)
{
	// no buff
	return true;
}

bool MetaEvent_EndOfTrack::Play(Signal &sig, Player *pPlayer) const
{
	return true;
}

bool MetaEvent_EndOfTrack::Write(Signal &sig, Stream &stream, const Event *pEventPrev) const
{
	if (!MetaEvent::Write(sig, stream, pEventPrev)) return false;
	if (!WriteVariableFormat(sig, stream, 0)) return false;
	return true;
}

const Symbol *MetaEvent_EndOfTrack::GetSymbol() const
{
	return Gura_UserSymbol(end_of_track);
}

String MetaEvent_EndOfTrack::GetArgsName() const
{
	char str[128];
	::sprintf(str, "");
	return String(str);
}

Event *MetaEvent_EndOfTrack::Clone() const
{
	return new MetaEvent_EndOfTrack(*this);
}

bool MetaEvent_EndOfTrack::DoDirProp(Environment &env, SymbolSet &symbols)
{
	return true;
}

Value MetaEvent_EndOfTrack::DoGetProp(Environment &env, const Symbol *pSymbol,
							const SymbolSet &attrs, bool &evaluatedFlag)
{
	return Value::Nil;
}

Value MetaEvent_EndOfTrack::DoSetProp(Environment &env, const Symbol *pSymbol, const Value &value,
								const SymbolSet &attrs, bool &evaluatedFlag)
{
	return Value::Nil;
}

//-----------------------------------------------------------------------------
// MetaEvent_TempoSetting
//-----------------------------------------------------------------------------
bool MetaEvent_TempoSetting::Prepare(Signal &sig, const Binary &binary)
{
	if (binary.size() < 3) {
		SetError_TooShortMetaEvent(sig);
		return false;
	}
	_mpqn =
		(static_cast<ULong>(static_cast<UChar>(binary[0])) << 16) +
		(static_cast<ULong>(static_cast<UChar>(binary[1])) << 8) +
		(static_cast<ULong>(static_cast<UChar>(binary[2])) << 0);
	return true;
}

bool MetaEvent_TempoSetting::Play(Signal &sig, Player *pPlayer) const
{
	pPlayer->SetMPQN(_mpqn);
	return true;
}

bool MetaEvent_TempoSetting::Write(Signal &sig, Stream &stream, const Event *pEventPrev) const
{
	if (!MetaEvent::Write(sig, stream, pEventPrev)) return false;
	const size_t bytes = 3;
	UChar buff[bytes];
	buff[0] = static_cast<UChar>(_mpqn >> 16);
	buff[1] = static_cast<UChar>(_mpqn >> 8);
	buff[2] = static_cast<UChar>(_mpqn >> 0);
	if (!WriteVariableFormat(sig, stream, static_cast<ULong>(bytes))) return false;
	return stream.Write(sig, buff, bytes) == bytes;
}

const Symbol *MetaEvent_TempoSetting::GetSymbol() const
{
	return Gura_UserSymbol(tempo_setting);
}

String MetaEvent_TempoSetting::GetArgsName() const
{
	char str[128];
	::sprintf(str, "mpqn:%lu", _mpqn);
	return String(str);
}

Event *MetaEvent_TempoSetting::Clone() const
{
	return new MetaEvent_TempoSetting(*this);
}

bool MetaEvent_TempoSetting::DoDirProp(Environment &env, SymbolSet &symbols)
{
	symbols.insert(Gura_UserSymbol(mpqn));
	return true;
}

Value MetaEvent_TempoSetting::DoGetProp(Environment &env, const Symbol *pSymbol,
							const SymbolSet &attrs, bool &evaluatedFlag)
{
	evaluatedFlag = true;
	if (pSymbol->IsIdentical(Gura_UserSymbol(mpqn))) {
		return Value(_mpqn);
	}
	evaluatedFlag = false;
	return Value::Nil;
}

Value MetaEvent_TempoSetting::DoSetProp(Environment &env, const Symbol *pSymbol, const Value &value,
								const SymbolSet &attrs, bool &evaluatedFlag)
{
	Signal &sig = env.GetSignal();
	evaluatedFlag = true;
	if (pSymbol->IsIdentical(Gura_UserSymbol(mpqn))) {
		if (!value.MustBe_number(sig)) return Value::Nil;
		_mpqn = value.GetULong();
		return Value(_mpqn);
	}
	evaluatedFlag = false;
	return Value::Nil;
}

//-----------------------------------------------------------------------------
// MetaEvent_SMPTEOffset
//-----------------------------------------------------------------------------
bool MetaEvent_SMPTEOffset::Prepare(Signal &sig, const Binary &binary)
{
	if (binary.size() < 5) {
		SetError_TooShortMetaEvent(sig);
		return false;
	}
	_hour = static_cast<UChar>(binary[0]);
	_minute = static_cast<UChar>(binary[1]);
	_second = static_cast<UChar>(binary[2]);
	_frame = static_cast<UChar>(binary[3]);
	_subFrame = static_cast<UChar>(binary[4]);
	return true;
}

bool MetaEvent_SMPTEOffset::Play(Signal &sig, Player *pPlayer) const
{
	return true;
}

bool MetaEvent_SMPTEOffset::Write(Signal &sig, Stream &stream, const Event *pEventPrev) const
{
	if (!MetaEvent::Write(sig, stream, pEventPrev)) return false;
	const size_t bytes = 5;
	UChar buff[bytes];
	buff[0] = _hour;
	buff[1] = _minute;
	buff[2] = _second;
	buff[3] = _frame;
	buff[4] = _subFrame;
	if (!WriteVariableFormat(sig, stream, static_cast<ULong>(bytes))) return false;
	return stream.Write(sig, buff, bytes) == bytes;
}

const Symbol *MetaEvent_SMPTEOffset::GetSymbol() const
{
	return Gura_UserSymbol(smpte_offset);
}

String MetaEvent_SMPTEOffset::GetArgsName() const
{
	char str[128];
	::sprintf(str, "hour:%d minute:%d second:%d frame:%d subFrame:%d",
						_hour, _minute, _second, _frame, _subFrame);
	return String(str);
}

Event *MetaEvent_SMPTEOffset::Clone() const
{
	return new MetaEvent_SMPTEOffset(*this);
}

bool MetaEvent_SMPTEOffset::DoDirProp(Environment &env, SymbolSet &symbols)
{
	symbols.insert(Gura_UserSymbol(hour));
	symbols.insert(Gura_UserSymbol(minute));
	symbols.insert(Gura_UserSymbol(second));
	symbols.insert(Gura_UserSymbol(frame));
	symbols.insert(Gura_UserSymbol(subFrame));
	return true;
}

Value MetaEvent_SMPTEOffset::DoGetProp(Environment &env, const Symbol *pSymbol,
							const SymbolSet &attrs, bool &evaluatedFlag)
{
	evaluatedFlag = true;
	if (pSymbol->IsIdentical(Gura_UserSymbol(hour))) {
		return Value(_hour);
	} else if (pSymbol->IsIdentical(Gura_UserSymbol(minute))) {
		return Value(_minute);
	} else if (pSymbol->IsIdentical(Gura_UserSymbol(second))) {
		return Value(_second);
	} else if (pSymbol->IsIdentical(Gura_UserSymbol(frame))) {
		return Value(_frame);
	} else if (pSymbol->IsIdentical(Gura_UserSymbol(subFrame))) {
		return Value(_subFrame);
	}
	evaluatedFlag = false;
	return Value::Nil;
}

Value MetaEvent_SMPTEOffset::DoSetProp(Environment &env, const Symbol *pSymbol, const Value &value,
								const SymbolSet &attrs, bool &evaluatedFlag)
{
	Signal &sig = env.GetSignal();
	evaluatedFlag = true;
	if (pSymbol->IsIdentical(Gura_UserSymbol(hour))) {
		if (!value.MustBe_number(sig)) return Value::Nil;
		_hour = value.GetUChar();
		return Value(_hour);
	} else if (pSymbol->IsIdentical(Gura_UserSymbol(minute))) {
		if (!value.MustBe_number(sig)) return Value::Nil;
		_minute = value.GetUChar();
		return Value(_minute);
	} else if (pSymbol->IsIdentical(Gura_UserSymbol(second))) {
		if (!value.MustBe_number(sig)) return Value::Nil;
		_second = value.GetUChar();
		return Value(_second);
	} else if (pSymbol->IsIdentical(Gura_UserSymbol(frame))) {
		if (!value.MustBe_number(sig)) return Value::Nil;
		_frame = value.GetUChar();
		return Value(_frame);
	} else if (pSymbol->IsIdentical(Gura_UserSymbol(subFrame))) {
		if (!value.MustBe_number(sig)) return Value::Nil;
		_subFrame = value.GetUChar();
		return Value(_subFrame);
	}
	evaluatedFlag = false;
	return Value::Nil;
}

//-----------------------------------------------------------------------------
// MetaEvent_TimeSignature
//-----------------------------------------------------------------------------
bool MetaEvent_TimeSignature::Prepare(Signal &sig, const Binary &binary)
{
	if (binary.size() < 4) {
		SetError_TooShortMetaEvent(sig);
		return false;
	}
	_numerator = static_cast<UChar>(binary[0]);
	_denominator = static_cast<UChar>(binary[1]);
	_metronome = static_cast<UChar>(binary[2]);
	_cnt32nd = static_cast<UChar>(binary[3]);
	return true;
}

bool MetaEvent_TimeSignature::Play(Signal &sig, Player *pPlayer) const
{
	return true;
}

bool MetaEvent_TimeSignature::Write(Signal &sig, Stream &stream, const Event *pEventPrev) const
{
	if (!MetaEvent::Write(sig, stream, pEventPrev)) return false;
	const size_t bytes = 4;
	UChar buff[bytes];
	buff[0] = _numerator;
	buff[1] = _denominator;
	buff[2] = _metronome;
	buff[3] = _cnt32nd;
	if (!WriteVariableFormat(sig, stream, static_cast<ULong>(bytes))) return false;
	return stream.Write(sig, buff, bytes) == bytes;
}

const Symbol *MetaEvent_TimeSignature::GetSymbol() const
{
	return Gura_UserSymbol(time_signature);
}

String MetaEvent_TimeSignature::GetArgsName() const
{
	char str[128];
	::sprintf(str, "numerator:%d denominator:%d metronome:%d cnt32nd:%d",
							_numerator, _denominator, _metronome, _cnt32nd);
	return String(str);
}

Event *MetaEvent_TimeSignature::Clone() const
{
	return new MetaEvent_TimeSignature(*this);
}

bool MetaEvent_TimeSignature::DoDirProp(Environment &env, SymbolSet &symbols)
{
	symbols.insert(Gura_UserSymbol(numerator));
	symbols.insert(Gura_UserSymbol(denominator));
	symbols.insert(Gura_UserSymbol(metronome));
	symbols.insert(Gura_UserSymbol(cnt32nd));
	return true;
}

Value MetaEvent_TimeSignature::DoGetProp(Environment &env, const Symbol *pSymbol,
							const SymbolSet &attrs, bool &evaluatedFlag)
{
	evaluatedFlag = true;
	if (pSymbol->IsIdentical(Gura_UserSymbol(numerator))) {
		return Value(_numerator);
	} else if (pSymbol->IsIdentical(Gura_UserSymbol(denominator))) {
		return Value(_denominator);
	} else if (pSymbol->IsIdentical(Gura_UserSymbol(metronome))) {
		return Value(_metronome);
	} else if (pSymbol->IsIdentical(Gura_UserSymbol(cnt32nd))) {
		return Value(_cnt32nd);
	}
	evaluatedFlag = false;
	return Value::Nil;
}

Value MetaEvent_TimeSignature::DoSetProp(Environment &env, const Symbol *pSymbol, const Value &value,
								const SymbolSet &attrs, bool &evaluatedFlag)
{
	Signal &sig = env.GetSignal();
	evaluatedFlag = true;
	if (pSymbol->IsIdentical(Gura_UserSymbol(numerator))) {
		if (!value.MustBe_number(sig)) return Value::Nil;
		_numerator = value.GetUChar();
		return Value(_numerator);
	} else if (pSymbol->IsIdentical(Gura_UserSymbol(denominator))) {
		if (!value.MustBe_number(sig)) return Value::Nil;
		_denominator = value.GetUChar();
		return Value(_denominator);
	} else if (pSymbol->IsIdentical(Gura_UserSymbol(metronome))) {
		if (!value.MustBe_number(sig)) return Value::Nil;
		_metronome = value.GetUChar();
		return Value(_metronome);
	} else if (pSymbol->IsIdentical(Gura_UserSymbol(cnt32nd))) {
		if (!value.MustBe_number(sig)) return Value::Nil;
		_cnt32nd = value.GetUChar();
		return Value(_cnt32nd);
	}
	evaluatedFlag = false;
	return Value::Nil;
}

//-----------------------------------------------------------------------------
// MetaEvent_KeySignature
//-----------------------------------------------------------------------------
bool MetaEvent_KeySignature::Prepare(Signal &sig, const Binary &binary)
{
	if (binary.size() < 2) {
		SetError_TooShortMetaEvent(sig);
		return false;
	}
	_key = static_cast<UChar>(binary[0]);
	_scale = static_cast<UChar>(binary[1]);
	return true;
}

bool MetaEvent_KeySignature::Play(Signal &sig, Player *pPlayer) const
{
	return true;
}

bool MetaEvent_KeySignature::Write(Signal &sig, Stream &stream, const Event *pEventPrev) const
{
	if (!MetaEvent::Write(sig, stream, pEventPrev)) return false;
	const size_t bytes = 2;
	UChar buff[bytes];
	buff[0] = _key;
	buff[1] = _scale;
	if (!WriteVariableFormat(sig, stream, static_cast<ULong>(bytes))) return false;
	return stream.Write(sig, buff, bytes) == bytes;
}

const Symbol *MetaEvent_KeySignature::GetSymbol() const
{
	return Gura_UserSymbol(key_signature);
}

String MetaEvent_KeySignature::GetArgsName() const
{
	char str[128];
	::sprintf(str, "key:%d scale:%d", _key, _scale);
	return String(str);
}

Event *MetaEvent_KeySignature::Clone() const
{
	return new MetaEvent_KeySignature(*this);
}

bool MetaEvent_KeySignature::DoDirProp(Environment &env, SymbolSet &symbols)
{
	symbols.insert(Gura_UserSymbol(key));
	symbols.insert(Gura_UserSymbol(scale));
	return true;
}

Value MetaEvent_KeySignature::DoGetProp(Environment &env, const Symbol *pSymbol,
							const SymbolSet &attrs, bool &evaluatedFlag)
{
	evaluatedFlag = true;
	if (pSymbol->IsIdentical(Gura_UserSymbol(key))) {
		return Value(_key);
	} else if (pSymbol->IsIdentical(Gura_UserSymbol(scale))) {
		return Value(_scale);
	}
	evaluatedFlag = false;
	return Value::Nil;
}

Value MetaEvent_KeySignature::DoSetProp(Environment &env, const Symbol *pSymbol, const Value &value,
								const SymbolSet &attrs, bool &evaluatedFlag)
{
	Signal &sig = env.GetSignal();
	evaluatedFlag = true;
	if (pSymbol->IsIdentical(Gura_UserSymbol(key))) {
		if (!value.MustBe_number(sig)) return Value::Nil;
		_key = value.GetUChar();
		return Value(_key);
	} else if (pSymbol->IsIdentical(Gura_UserSymbol(scale))) {
		if (!value.MustBe_number(sig)) return Value::Nil;
		_scale = value.GetUChar();
		return Value(_scale);
	}
	evaluatedFlag = false;
	return Value::Nil;
}

//-----------------------------------------------------------------------------
// MetaEvent_SequencerSpecificEvent
//-----------------------------------------------------------------------------
bool MetaEvent_SequencerSpecificEvent::Prepare(Signal &sig, const Binary &binary)
{
	_binary = binary;
	return true;
}

bool MetaEvent_SequencerSpecificEvent::Play(Signal &sig, Player *pPlayer) const
{
	return true;
}

bool MetaEvent_SequencerSpecificEvent::Write(Signal &sig, Stream &stream, const Event *pEventPrev) const
{
	if (!MetaEvent::Write(sig, stream, pEventPrev)) return false;
	if (!WriteVariableFormat(sig, stream, static_cast<ULong>(_binary.size()))) return false;
	return stream.Write(sig, _binary.data(), _binary.size()) == _binary.size();
}

const Symbol *MetaEvent_SequencerSpecificEvent::GetSymbol() const
{
	return Gura_UserSymbol(sequencer_specific_event);
}

String MetaEvent_SequencerSpecificEvent::GetArgsName() const
{
	char str[128];
	::sprintf(str, "%lubytes", _binary.size());
	return String(str);
}

Event *MetaEvent_SequencerSpecificEvent::Clone() const
{
	return new MetaEvent_SequencerSpecificEvent(*this);
}

bool MetaEvent_SequencerSpecificEvent::DoDirProp(Environment &env, SymbolSet &symbols)
{
	symbols.insert(Gura_UserSymbol(binary));
	return true;
}

Value MetaEvent_SequencerSpecificEvent::DoGetProp(Environment &env, const Symbol *pSymbol,
							const SymbolSet &attrs, bool &evaluatedFlag)
{
	evaluatedFlag = true;
	if (pSymbol->IsIdentical(Gura_UserSymbol(binary))) {
		return Value(new Object_binary(env, _binary, false));
	}
	evaluatedFlag = false;
	return Value::Nil;
}

Value MetaEvent_SequencerSpecificEvent::DoSetProp(Environment &env, const Symbol *pSymbol, const Value &value,
								const SymbolSet &attrs, bool &evaluatedFlag)
{
	Signal &sig = env.GetSignal();
	evaluatedFlag = true;
	if (pSymbol->IsIdentical(Gura_UserSymbol(binary))) {
		if (!value.MustBe_binary(sig)) return Value::Nil;
		_binary = value.GetBinary();
		return value;
	}
	evaluatedFlag = false;
	return Value::Nil;
}

Gura_EndModuleScope(midi)
