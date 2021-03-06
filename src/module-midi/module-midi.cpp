//-----------------------------------------------------------------------------
// Gura module: midi
//-----------------------------------------------------------------------------
#include "stdafx.h"

Gura_BeginModuleBody(midi)

Value ActivatePlayer(Environment &env, Signal &sig, Argument &arg,
				Sequence &sequence, Port *pPort, double speed, int cntRepeat);

//-----------------------------------------------------------------------------
// information table
//-----------------------------------------------------------------------------
static ControllerInfo g_controllerInfos[] = {
	{ "bank_select",					nullptr }, // 0
	{ "modulation_wheel",				nullptr }, // 1
	{ "breath_controller",				nullptr }, // 2
	{ nullptr,							nullptr }, // 3
	{ "foot_pedal",						nullptr }, // 4
	{ "portamento_time",				nullptr }, // 5
	{ "data_entry",						nullptr }, // 6
	{ "volume",							nullptr }, // 7
	{ "balance",						nullptr }, // 8
	{ nullptr,							nullptr }, // 9
	{ "pan_position",					nullptr }, // 10
	{ "expression",						nullptr }, // 11
	{ "effect_control_1",				nullptr }, // 12
	{ "effect_control_2",				nullptr }, // 13
	{ nullptr,							nullptr }, // 14
	{ nullptr,							nullptr }, // 15
	{ "general_purpose_slider_1",		nullptr }, // 16
	{ "general_purpose_slider_2",		nullptr }, // 17
	{ "general_purpose_slider_3",		nullptr }, // 18
	{ "general_purpose_slider_4",		nullptr }, // 19
	{ nullptr,							nullptr }, // 20
	{ nullptr,							nullptr }, // 21
	{ nullptr,							nullptr }, // 22
	{ nullptr,							nullptr }, // 23
	{ nullptr,							nullptr }, // 24
	{ nullptr,							nullptr }, // 25
	{ nullptr,							nullptr }, // 26
	{ nullptr,							nullptr }, // 27
	{ nullptr,							nullptr }, // 28
	{ nullptr,							nullptr }, // 29
	{ nullptr,							nullptr }, // 30
	{ nullptr,							nullptr }, // 31
	{ "bank_select_fine",				nullptr }, // 32
	{ "modulation_wheel_fine",			nullptr }, // 33
	{ "breath_controller_fine",			nullptr }, // 34
	{ nullptr,							nullptr }, // 35
	{ "foot_pedal_fine",				nullptr }, // 36
	{ "portamento_time_fine",			nullptr }, // 37
	{ "data_entry_fine",				nullptr }, // 38
	{ "volume_fine",					nullptr }, // 39
	{ "balance_fine",					nullptr }, // 40
	{ nullptr,							nullptr }, // 41
	{ "pan_position_fine",				nullptr }, // 42
	{ "expression_fine",				nullptr }, // 43
	{ "effect_control_1_fine",			nullptr }, // 44
	{ "effect_control_2_fine",			nullptr }, // 45
	{ nullptr,							nullptr }, // 46
	{ nullptr,							nullptr }, // 47
	{ nullptr,							nullptr }, // 48
	{ nullptr,							nullptr }, // 49
	{ nullptr,							nullptr }, // 50
	{ nullptr,							nullptr }, // 51
	{ nullptr,							nullptr }, // 52
	{ nullptr,							nullptr }, // 53
	{ nullptr,							nullptr }, // 54
	{ nullptr,							nullptr }, // 55
	{ nullptr,							nullptr }, // 56
	{ nullptr,							nullptr }, // 57
	{ nullptr,							nullptr }, // 58
	{ nullptr,							nullptr }, // 59
	{ nullptr,							nullptr }, // 60
	{ nullptr,							nullptr }, // 61
	{ nullptr,							nullptr }, // 62
	{ nullptr,							nullptr }, // 63
	{ "hold_pedal",						nullptr }, // 64
	{ "portamento",						nullptr }, // 65
	{ "sustenuto_pedal",				nullptr }, // 66
	{ "soft_pedal",						nullptr }, // 67
	{ "legato_pedal",					nullptr }, // 68
	{ "hold_2_pedal",					nullptr }, // 69
	{ "sound_variation",				nullptr }, // 70
	{ "sound_timbre",					nullptr }, // 71
	{ "sound_release_time",				nullptr }, // 72
	{ "sound_attack_time",				nullptr }, // 73
	{ "sound_brightness",				nullptr }, // 74
	{ "sound_control_6",				nullptr }, // 75
	{ "sound_control_7",				nullptr }, // 76
	{ "sound_control_8",				nullptr }, // 77
	{ "sound_control_9",				nullptr }, // 78
	{ "sound_control_10",				nullptr }, // 79
	{ "general_purpose_button_1",		nullptr }, // 80
	{ "general_purpose_button_2",		nullptr }, // 81
	{ "general_purpose_button_3",		nullptr }, // 82
	{ "general_purpose_button_4",		nullptr }, // 83
	{ nullptr,							nullptr }, // 84
	{ nullptr,							nullptr }, // 85
	{ nullptr,							nullptr }, // 86
	{ nullptr,							nullptr }, // 87
	{ nullptr,							nullptr }, // 88
	{ nullptr,							nullptr }, // 89
	{ nullptr,							nullptr }, // 90
	{ "effects_level",					nullptr }, // 91
	{ "tremulo_level",					nullptr }, // 92
	{ "chorus_level",					nullptr }, // 93
	{ "celeste_level",					nullptr }, // 94
	{ "phaser_level",					nullptr }, // 95
	{ "data_button_increment",			nullptr }, // 96
	{ "data_button_decrement",			nullptr }, // 97
	{ "non_registered_parameter_fine",	nullptr }, // 98
	{ "non_registered_parameter",		nullptr }, // 99
	{ "registered_parameter_fine",		nullptr }, // 100
	{ "registered_parameter",			nullptr }, // 101
	{ nullptr,							nullptr }, // 102
	{ nullptr,							nullptr }, // 103
	{ nullptr,							nullptr }, // 104
	{ nullptr,							nullptr }, // 105
	{ nullptr,							nullptr }, // 106
	{ nullptr,							nullptr }, // 107
	{ nullptr,							nullptr }, // 108
	{ nullptr,							nullptr }, // 109
	{ nullptr,							nullptr }, // 110
	{ nullptr,							nullptr }, // 111
	{ nullptr,							nullptr }, // 112
	{ nullptr,							nullptr }, // 113
	{ nullptr,							nullptr }, // 114
	{ nullptr,							nullptr }, // 115
	{ nullptr,							nullptr }, // 116
	{ nullptr,							nullptr }, // 117
	{ nullptr,							nullptr }, // 118
	{ nullptr,							nullptr }, // 119
	{ "all_sound_off",					nullptr }, // 120
	{ "all_controllers_off",			nullptr }, // 121
	{ "local_keyboard",					nullptr }, // 122
	{ "all_notes_off",					nullptr }, // 123
	{ "omni_mode_off",					nullptr }, // 124
	{ "omni_mode_on",					nullptr }, // 125
	{ "mono_operation",					nullptr }, // 126
	{ "poly_operation",					nullptr }, // 127
};

static ProgramInfo g_programInfos[] = {
	// Piano
	{ "acoustic_piano",				"Acoustic Piano",			nullptr }, // 0
	{ "bright_piano",				"Bright Piano",				nullptr }, // 1
	{ "electric_grand_piano",		"Electric Grand Piano",		nullptr }, // 2
	{ "honky_tonk_piano",			"Honky-tonk Piano",			nullptr }, // 3
	{ "electric_piano",				"Electric Piano",			nullptr }, // 4
	{ "electric_piano_2",			"Electric Piano 2",			nullptr }, // 5
	{ "harpsichord",				"Harpsichord",				nullptr }, // 6
	{ "clavi",						"Clavi",					nullptr }, // 7
	// Chromatic Percussion
	{ "celesta",					"Celesta",					nullptr }, // 8
	{ "glockenspiel",				"Glockenspiel",				nullptr }, // 9
	{ "musical_box",				"Musical box",				nullptr }, // 10
	{ "vibraphone",					"Vibraphone",				nullptr }, // 11
	{ "marimba",					"Marimba",					nullptr }, // 12
	{ "xylophone",					"Xylophone",				nullptr }, // 13
	{ "tubular_bell",				"Tubular Bell",				nullptr }, // 14
	{ "dulcimer",					"Dulcimer",					nullptr }, // 15
	// Organ
	{ "drawbar_organ",				"Drawbar Organ",			nullptr }, // 16
	{ "percussive_organ",			"Percussive Organ",			nullptr }, // 17
	{ "rock_organ",					"Rock Organ",				nullptr }, // 18
	{ "church_organ",				"Church organ",				nullptr }, // 19
	{ "reed_organ",					"Reed organ",				nullptr }, // 20
	{ "accordion",					"Accordion",				nullptr }, // 21
	{ "harmonica",					"Harmonica",				nullptr }, // 22
	{ "tango_accordion",			"Tango Accordion",			nullptr }, // 23
	// Guitar
	{ "acoustic_guitar_nylon",		"Acoustic Guitar (nylon)",	nullptr }, // 24
	{ "acoustic_guitar_steel",		"Acoustic Guitar (steel)",	nullptr }, // 25
	{ "electric_guitar_jazz",		"Electric Guitar (jazz)",	nullptr }, // 26
	{ "electric_guitar_clean",		"Electric Guitar (clean)",	nullptr }, // 27
	{ "electric_guitar_muted",		"Electric Guitar (muted)",	nullptr }, // 28
	{ "overdriven_guitar",			"Overdriven Guitar",		nullptr }, // 29
	{ "distortion_guitar",			"Distortion Guitar",		nullptr }, // 30
	{ "guitar_harmonics",			"Guitar harmonics",			nullptr }, // 31
	// Bass
	{ "acoustic_bass",				"Acoustic Bass",			nullptr }, // 32
	{ "electric_bass_finger",		"Electric Bass (finger)",	nullptr }, // 33
	{ "electric_bass_pick",			"Electric Bass (pick)",		nullptr }, // 34
	{ "fretless_bass",				"Fretless Bass",			nullptr }, // 35
	{ "slap_bass_1",				"Slap Bass 1",				nullptr }, // 36
	{ "slap_bass_2",				"Slap Bass 2",				nullptr }, // 37
	{ "synth_bass_1",				"Synth Bass 1",				nullptr }, // 38
	{ "synth_bass_2",				"Synth Bass 2",				nullptr }, // 39
	// Strings
	{ "violin",						"Violin",					nullptr }, // 40
	{ "viola",						"Viola",					nullptr }, // 41
	{ "cello",						"Cello",					nullptr }, // 42
	{ "double_bass",				"Double bass",				nullptr }, // 43
	{ "tremolo_strings",			"Tremolo Strings",			nullptr }, // 44
	{ "pizzicato_strings",			"Pizzicato Strings",		nullptr }, // 45
	{ "orchestral_harp",			"Orchestral Harp",			nullptr }, // 46
	{ "timpani",					"Timpani",					nullptr }, // 47
	// Ensemble
	{ "string_ensemble_1",			"String Ensemble 1",		nullptr }, // 48
	{ "string_ensemble_2",			"String Ensemble 2",		nullptr }, // 49
	{ "synth_strings_1",			"Synth Strings 1",			nullptr }, // 50
	{ "synth_strings_2",			"Synth Strings 2",			nullptr }, // 51
	{ "voice_aahs",					"Voice Aahs",				nullptr }, // 52
	{ "voice_oohs",					"Voice Oohs",				nullptr }, // 53
	{ "synth_voice",				"Synth Voice",				nullptr }, // 54
	{ "orchestra_hit",				"Orchestra Hit",			nullptr }, // 55
	// Brass
	{ "trumpet",					"Trumpet",					nullptr }, // 56
	{ "trombone",					"Trombone",					nullptr }, // 57
	{ "tuba",						"Tuba",						nullptr }, // 58
	{ "muted_trumpet",				"Muted Trumpet",			nullptr }, // 59
	{ "french_horn",				"French horn",				nullptr }, // 60
	{ "brass_section",				"Brass Section",			nullptr }, // 61
	{ "synth_brass_1",				"Synth Brass 1",			nullptr }, // 62
	{ "synth_brass_2",				"Synth Brass 2",			nullptr }, // 63
	// Reed
	{ "soprano_sax",				"Soprano Sax",				nullptr }, // 64
	{ "alto_sax",					"Alto Sax",					nullptr }, // 65
	{ "tenor_sax",					"Tenor Sax",				nullptr }, // 66
	{ "baritone_sax",				"Baritone Sax",				nullptr }, // 67
	{ "oboe",						"Oboe",						nullptr }, // 68
	{ "english_horn",				"English Horn",				nullptr }, // 69
	{ "bassoon",					"Bassoon",					nullptr }, // 70
	{ "clarinet",					"Clarinet",					nullptr }, // 71
	// Pipe
	{ "piccolo",					"Piccolo",					nullptr }, // 72
	{ "flute",						"Flute",					nullptr }, // 73
	{ "recorder",					"Recorder",					nullptr }, // 74
	{ "pan_flute",					"Pan Flute",				nullptr }, // 75
	{ "blown_bottle",				"Blown Bottle",				nullptr }, // 76
	{ "shakuhachi",					"Shakuhachi",				nullptr }, // 77
	{ "whistle",					"Whistle",					nullptr }, // 78
	{ "ocarina",					"Ocarina",					nullptr }, // 79
	// Synth Lead
	{ "lead_1_square",				"Lead 1 (square)",			nullptr }, // 80
	{ "lead_2_sawtooth",			"Lead 2 (sawtooth)",		nullptr }, // 81
	{ "lead_3_calliope",			"Lead 3 (calliope)",		nullptr }, // 82
	{ "lead_4_chiff",				"Lead 4 (chiff)",			nullptr }, // 83
	{ "lead_5_charang",				"Lead 5 (charang)",			nullptr }, // 84
	{ "lead_6_voice",				"Lead 6 (voice)",			nullptr }, // 85
	{ "lead_7_fifths",				"Lead 7 (fifths)",			nullptr }, // 86
	{ "lead_8_bass_lead",			"Lead 8 (bass + lead)",		nullptr }, // 87
	// Synth Pad
	{ "pad_1_fantasia",				"Pad 1 (Fantasia)",			nullptr }, // 88
	{ "pad_2_warm",					"Pad 2 (warm)",				nullptr }, // 89
	{ "pad_3_polysynth",			"Pad 3 (polysynth)",		nullptr }, // 90
	{ "pad_4_choir",				"Pad 4 (choir)",			nullptr }, // 91
	{ "pad_5_bowed",				"Pad 5 (bowed)",			nullptr }, // 92
	{ "pad_6_metallic",				"Pad 6 (metallic)",			nullptr }, // 93
	{ "pad_7_halo",					"Pad 7 (halo)",				nullptr }, // 94
	{ "pad_8_sweep",				"Pad 8 (sweep)",			nullptr }, // 95
	// Synth Effects
	{ "fx_1_rain",					"FX 1 (rain)",				nullptr }, // 96
	{ "fx_2_soundtrack",			"FX 2 (soundtrack)",		nullptr }, // 97
	{ "fx_3_crystal",				"FX 3 (crystal)",			nullptr }, // 98
	{ "fx_4_atmosphere",			"FX 4 (atmosphere)",		nullptr }, // 99
	{ "fx_5_brightness",			"FX 5 (brightness)",		nullptr }, // 100
	{ "fx_6_goblins",				"FX 6 (goblins)",			nullptr }, // 101
	{ "fx_7_echoes",				"FX 7 (echoes)",			nullptr }, // 102
	{ "fx_8_sci_fi",				"FX 8 (sci-fi)",			nullptr }, // 103
	// Ethnic
	{ "sitar",						"Sitar",					nullptr }, // 104
	{ "banjo",						"Banjo",					nullptr }, // 105
	{ "shamisen",					"Shamisen",					nullptr }, // 106
	{ "koto",						"Koto",						nullptr }, // 107
	{ "kalimba",					"Kalimba",					nullptr }, // 108
	{ "bagpipe",					"Bagpipe",					nullptr }, // 109
	{ "fiddle",						"Fiddle",					nullptr }, // 110
	{ "shanai",						"Shanai",					nullptr }, // 111
	// Percussive
	{ "tinkle_bell",				"Tinkle Bell",				nullptr }, // 112
	{ "agogo",						"Agogo",					nullptr }, // 113
	{ "steel_drums",				"Steel Drums",				nullptr }, // 114
	{ "woodblock",					"Woodblock",				nullptr }, // 115
	{ "taiko_drum",					"Taiko Drum",				nullptr }, // 116
	{ "melodic_tom",				"Melodic Tom",				nullptr }, // 117
	{ "synth_drum",					"Synth Drum",				nullptr }, // 118
	{ "reverse_cymbal",				"Reverse Cymbal",			nullptr }, // 119
	// Sound effects
	{ "guitar_fret_noise",			"Guitar Fret Noise",		nullptr }, // 120
	{ "breath_noise",				"Breath Noise",				nullptr }, // 121
	{ "seashore",					"Seashore",					nullptr }, // 122
	{ "bird_tweet",					"Bird Tweet",				nullptr }, // 123
	{ "telephone_ring",				"Telephone Ring",			nullptr }, // 124
	{ "helicopter",					"Helicopter",				nullptr }, // 125
	{ "applause",					"Applause",					nullptr }, // 126
	{ "gunshot",					"Gunshot",					nullptr }, // 127
};

//-----------------------------------------------------------------------------
// Object_event
//-----------------------------------------------------------------------------
Object *Object_event::Clone() const
{
	return nullptr;
}

bool Object_event::DoDirProp(Environment &env, SymbolSet &symbols)
{
	return true;
}

Value Object_event::DoGetProp(Environment &env, const Symbol *pSymbol,
							const SymbolSet &attrs, bool &evaluatedFlag)
{
	return _pEvent->DoGetProp(env, pSymbol, attrs, evaluatedFlag);
}

String Object_event::ToString(bool exprFlag)
{
	String rtn;
	rtn += "<midi.event:";
	do {
		char buff[32];
		::sprintf(buff, "%08lx:", _pEvent->GetTimeStamp());
		rtn += buff;
	} while (0);
	rtn += _pEvent->GetSymbol()->GetName();
	String argsName = _pEvent->GetArgsName();
	if (!argsName.empty()) {
		rtn += " ";
		rtn += argsName;
	}
	rtn += ">";
	return rtn;
}

//-----------------------------------------------------------------------------
// Implementation of properties
//-----------------------------------------------------------------------------
// midi.event#args
Gura_DeclareProperty_R(event, args)
{
	SetPropAttr(VTYPE_string);
	AddHelp(
		Gura_Symbol(en),
		""
		);
}

Gura_ImplementPropertyGetter(event, args)
{
	const Event *pEvent = Object_event::GetObject(valueThis)->GetEvent();
	return Value(pEvent->GetArgsName());
}

// midi.event#name
Gura_DeclareProperty_R(event, name)
{
	SetPropAttr(VTYPE_string);
	AddHelp(
		Gura_Symbol(en),
		""
		);
}

Gura_ImplementPropertyGetter(event, name)
{
	const Event *pEvent = Object_event::GetObject(valueThis)->GetEvent();
	return Value(pEvent->GetSymbol()->GetName());
}

// midi.event#status
Gura_DeclareProperty_R(event, status)
{
	SetPropAttr(VTYPE_number);
	AddHelp(
		Gura_Symbol(en),
		""
		);
}

Gura_ImplementPropertyGetter(event, status)
{
	const Event *pEvent = Object_event::GetObject(valueThis)->GetEvent();
	return Value(pEvent->GetStatusCode());
}

// midi.event#symbol
Gura_DeclareProperty_R(event, symbol)
{
	SetPropAttr(VTYPE_symbol);
	AddHelp(
		Gura_Symbol(en),
		""
		);
}

Gura_ImplementPropertyGetter(event, symbol)
{
	const Event *pEvent = Object_event::GetObject(valueThis)->GetEvent();
	return Value(pEvent->GetSymbol());
}

// midi.event#timestamp
Gura_DeclareProperty_R(event, timestamp)
{
	SetPropAttr(VTYPE_number);
	AddHelp(
		Gura_Symbol(en),
		""
		);
}

Gura_ImplementPropertyGetter(event, timestamp)
{
	const Event *pEvent = Object_event::GetObject(valueThis)->GetEvent();
	return Value(pEvent->GetTimeStamp());
}

// midi.event#type
Gura_DeclareProperty_R(event, type)
{
	SetPropAttr(VTYPE_symbol);
	AddHelp(
		Gura_Symbol(en),
		""
		);
}

Gura_ImplementPropertyGetter(event, type)
{
	const Event *pEvent = Object_event::GetObject(valueThis)->GetEvent();
	if (pEvent->IsMIDIEvent()) {
		return Value(Gura_UserSymbol(midi));
	} else if (pEvent->IsSysExEvent()) {
		return Value(Gura_UserSymbol(sysex));
	} else if (pEvent->IsMetaEvent()) {
		return Value(Gura_UserSymbol(meta));
	} else {
		return Value::Nil; // this must not happen
	}
}

//-----------------------------------------------------------------------------
// Gura interfaces for midi.event
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Class implementation for midi.event
//-----------------------------------------------------------------------------
Gura_ImplementUserClass(event)
{
	// Assignment of properties
	Gura_AssignProperty(event, args);
	Gura_AssignProperty(event, name);
	Gura_AssignProperty(event, status);
	Gura_AssignProperty(event, symbol);
	Gura_AssignProperty(event, timestamp);
	Gura_AssignProperty(event, type);
}

//-----------------------------------------------------------------------------
// Object_track
//-----------------------------------------------------------------------------
Object *Object_track::Clone() const
{
	return nullptr;
}

String Object_track::ToString(bool exprFlag)
{
	String rtn;
	rtn += "<midi.track";
	do {
		char buff[64];
		::sprintf(buff, ":%ldevents:seek%ld",
					_pTrack->GetEventOwner().size(), _pTrack->Tell());
		rtn += buff;
	} while (0);
	rtn += ">";
	return rtn;
}

//-----------------------------------------------------------------------------
// Implementation of properties
//-----------------------------------------------------------------------------
// midi.track#events
Gura_DeclareProperty_R(track, events)
{
	SetPropAttr(VTYPE_iterator);
	AddHelp(
		Gura_Symbol(en),
		""
		);
}

Gura_ImplementPropertyGetter(track, events)
{
	const Track *pTrack = Object_track::GetObject(valueThis)->GetTrack();
	Iterator *pIterator = new Iterator_event(pTrack->GetEventOwner().Reference());
	return Value(new Object_iterator(env, pIterator));
}

//-----------------------------------------------------------------------------
// Gura interfaces for midi.track
//-----------------------------------------------------------------------------
// midi.track#seek(offset:number, origin?:symbol):reduce
Gura_DeclareMethod(track, seek)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Reduce, FLAG_None);
	DeclareArg(env, "offset", VTYPE_number);
	DeclareArg(env, "origin", VTYPE_symbol, OCCUR_ZeroOrOnce);
	AddHelp(
		Gura_Symbol(en),
		"Moves the insertion point in the track at which the next event is inserted.\n"
		"If `origin` is omitted or set to `` `set``, the insertion point will be set to absolute offset from the beginning.\n"
		"If `origin` is set to `` `cur``, the insertion point will be moved by offset from the current position.\n");
}

Gura_ImplementMethod(track, seek)
{
	Signal &sig = env.GetSignal();
	Track *pTrack = Object_track::GetObjectThis(arg)->GetTrack();
	if (!arg.Is_symbol(1)) {
		if (!pTrack->SeekSet(sig, arg.GetLong(0))) return Value::Nil;
	} else if (arg.GetSymbol(1)->IsIdentical(Gura_Symbol(set))) {
		if (!pTrack->SeekSet(sig, arg.GetLong(0))) return Value::Nil;
	} else if (arg.GetSymbol(1)->IsIdentical(Gura_Symbol(cur))) {
		if (!pTrack->SeekCur(sig, arg.GetLong(0))) return Value::Nil;
	} else {
		sig.SetError(ERR_ArgumentError, "invalid symbol");
		return Value::Nil;
	}
	return arg.GetValueThis();
}

// midi.track#tell()
Gura_DeclareMethod(track, tell)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	AddHelp(
		Gura_Symbol(en),
		"Returns the current insertion point in the track.\n");
}

Gura_ImplementMethod(track, tell)
{
	Track *pTrack = Object_track::GetObjectThis(arg)->GetTrack();
	return Value(static_cast<Int32>(pTrack->Tell()));
}

// midi.track#erase(n?:number):reduce
Gura_DeclareMethod(track, erase)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Reduce, FLAG_None);
	DeclareArg(env, "n", VTYPE_number, OCCUR_ZeroOrOnce);
	AddHelp(
		Gura_Symbol(en),
		"Deletes an event at the current insertion point in the track.\n"
		"The argument `n` specifies the number of events to be deleted.\n"
		"If `n` is omitted, one event will be deleted.\n");
}

Gura_ImplementMethod(track, erase)
{
	Signal &sig = env.GetSignal();
	Track *pTrack = Object_track::GetObjectThis(arg)->GetTrack();
	size_t cnt = arg.Is_number(0)? arg.GetSizeT(0) : 1;
	if (!pTrack->Erase(sig, cnt)) return Value::Nil;
	return arg.GetValueThis();
}

// midi.track#mml(str:string, max_velocity?:number):map:reduce
Gura_DeclareMethod(track, mml)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Reduce, FLAG_Map);
	DeclareArg(env, "str", VTYPE_string);
	DeclareArg(env, "max_velocity", VTYPE_number, OCCUR_ZeroOrOnce);
	AddHelp(
		Gura_Symbol(en),
		"Parses MML in the string `str` and inserts resulted MIDI events at the current insertion point in the track.\n"
		"\n"
		"The argument `max_velocity` specifies the maximum number of velocity in the MML.\n"
		"If omitted, it will be set to 127.\n");
}

Gura_ImplementMethod(track, mml)
{
	Signal &sig = env.GetSignal();
	Track *pTrack = Object_track::GetObjectThis(arg)->GetTrack();
	int velocityMax = arg.Is_number(1)? arg.GetInt(1) : 127;
	MML mml(velocityMax);
	if (mml.ParseString(sig, pTrack, arg.GetString(0)) == MML::RSLT_Error) {
		return Value::Nil;
	}
	return arg.GetValueThis();
}

// midi.track#note_off(channel:number, note:number, velocity:number, deltaTime?:number):map:reduce
Gura_DeclareMethod(track, note_off)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Reduce, FLAG_Map);
	DeclareArg(env, "channel", VTYPE_number);
	DeclareArg(env, "note", VTYPE_number);
	DeclareArg(env, "velocity", VTYPE_number);
	DeclareArg(env, "deltaTime", VTYPE_number, OCCUR_ZeroOrOnce);
	AddHelp(
		Gura_Symbol(en),
		"");
}

Gura_ImplementMethod(track, note_off)
{
	Track *pTrack = Object_track::GetObjectThis(arg)->GetTrack();
	UChar channel = arg.GetUChar(0) & 0x0f;
	UChar note = arg.GetUChar(1);
	UChar velocity = arg.GetUChar(2);
	ULong deltaTime = arg.Is_number(3)? arg.GetULong(3) : 0;
	AutoPtr<Event> pEvent(new MIDIEvent_NoteOff(0, channel, note, velocity));
	pTrack->AddEvent(pEvent.release(), deltaTime);
	return arg.GetValueThis();
}

// midi.track#note_on(channel:number, note:number, velocity:number, deltaTime?:number):map:reduce
Gura_DeclareMethod(track, note_on)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Reduce, FLAG_Map);
	DeclareArg(env, "channel", VTYPE_number);
	DeclareArg(env, "note", VTYPE_number);
	DeclareArg(env, "velocity", VTYPE_number);
	DeclareArg(env, "deltaTime", VTYPE_number, OCCUR_ZeroOrOnce);
	AddHelp(
		Gura_Symbol(en),
		"");
}

Gura_ImplementMethod(track, note_on)
{
	Track *pTrack = Object_track::GetObjectThis(arg)->GetTrack();
	UChar channel = arg.GetUChar(0) & 0x0f;
	UChar note = arg.GetUChar(1);
	UChar velocity = arg.GetUChar(2);
	ULong deltaTime = arg.Is_number(3)? arg.GetULong(3) : 0;
	AutoPtr<Event> pEvent(new MIDIEvent_NoteOn(0, channel, note, velocity));
	pTrack->AddEvent(pEvent.release(), deltaTime);
	return arg.GetValueThis();
}

// midi.track#poly_pressure(channel:number, note:number, value:number, deltaTime?:number):map:reduce
Gura_DeclareMethod(track, poly_pressure)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Reduce, FLAG_Map);
	DeclareArg(env, "channel", VTYPE_number);
	DeclareArg(env, "note", VTYPE_number);
	DeclareArg(env, "value", VTYPE_number);
	DeclareArg(env, "deltaTime", VTYPE_number, OCCUR_ZeroOrOnce);
	AddHelp(
		Gura_Symbol(en),
		"");
}

Gura_ImplementMethod(track, poly_pressure)
{
	Track *pTrack = Object_track::GetObjectThis(arg)->GetTrack();
	UChar channel = arg.GetUChar(0) & 0x0f;
	UChar note = arg.GetUChar(1);
	UChar value = arg.GetUChar(2);
	ULong deltaTime = arg.Is_number(3)? arg.GetULong(3) : 0;
	AutoPtr<Event> pEvent(new MIDIEvent_PolyPressure(0, channel, note, value));
	pTrack->AddEvent(pEvent.release(), deltaTime);
	return arg.GetValueThis();
}

// midi.track#control_change(channel:number, controller, value:number, deltaTime?:number):map:reduce
Gura_DeclareMethod(track, control_change)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Reduce, FLAG_Map);
	DeclareArg(env, "channel", VTYPE_number);
	DeclareArg(env, "controller", VTYPE_any);
	DeclareArg(env, "value", VTYPE_number);
	DeclareArg(env, "deltaTime", VTYPE_number, OCCUR_ZeroOrOnce);
	AddHelp(
		Gura_Symbol(en),
		"");
}

Gura_ImplementMethod(track, control_change)
{
	Signal &sig = env.GetSignal();
	Track *pTrack = Object_track::GetObjectThis(arg)->GetTrack();
	UChar channel = arg.GetUChar(0) & 0x0f;
	UChar controller = 0;
	if (arg.Is_number(1)) {
		controller = arg.GetUChar(1);
	} else if (arg.Is_symbol(1)) {
		int n = ControllerIdBySymbol(arg.GetSymbol(1));
		if (n < 0) {
			sig.SetError(ERR_TypeError, "invalid controller name '%s'",
											arg.GetSymbol(1)->GetName());
			return Value::Nil;
		}
		controller = static_cast<UChar>(n);
	} else {
		sig.SetError(ERR_TypeError, "controller must be specified by number or symbol");
		return Value::Nil;
	}
	UChar value = arg.GetUChar(2);
	ULong deltaTime = arg.Is_number(3)? arg.GetULong(3) : 0;
	AutoPtr<Event> pEvent(new MIDIEvent_ControlChange(0, channel, controller, value));
	pTrack->AddEvent(pEvent.release(), deltaTime);
	return arg.GetValueThis();
}

// midi.track#program_change(channel:number, program, deltaTime?:number):map:reduce
Gura_DeclareMethod(track, program_change)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Reduce, FLAG_Map);
	DeclareArg(env, "channel", VTYPE_number);
	DeclareArg(env, "program", VTYPE_any);
	DeclareArg(env, "deltaTime", VTYPE_number, OCCUR_ZeroOrOnce);
	AddHelp(
		Gura_Symbol(en),
		"");
}

Gura_ImplementMethod(track, program_change)
{
	Signal &sig = env.GetSignal();
	Track *pTrack = Object_track::GetObjectThis(arg)->GetTrack();
	UChar channel = arg.GetUChar(0) & 0x0f;
	UChar program = 0;
	if (arg.Is_number(1)) {
		program = arg.GetUChar(1);
	} else if (arg.Is_symbol(1)) {
		int n = ProgramIdBySymbol(arg.GetSymbol(1));
		if (n < 0) {
			sig.SetError(ERR_TypeError, "invalid program name '%s'",
											arg.GetSymbol(1)->GetName());
			return Value::Nil;
		}
		program = static_cast<UChar>(n);
	} else {
		sig.SetError(ERR_TypeError, "program must be specified by number or symbol");
		return Value::Nil;
	}
	ULong deltaTime = arg.Is_number(2)? arg.GetULong(2) : 0;
	AutoPtr<Event> pEvent(new MIDIEvent_ProgramChange(0, channel, program));
	pTrack->AddEvent(pEvent.release(), deltaTime);
	return arg.GetValueThis();
}

// midi.track#channel_pressure(channel:number, pressure:number, deltaTime?:number):map:reduce
Gura_DeclareMethod(track, channel_pressure)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Reduce, FLAG_Map);
	DeclareArg(env, "channel", VTYPE_number);
	DeclareArg(env, "pressure", VTYPE_number);
	DeclareArg(env, "deltaTime", VTYPE_number, OCCUR_ZeroOrOnce);
	AddHelp(
		Gura_Symbol(en),
		"");
}

Gura_ImplementMethod(track, channel_pressure)
{
	Track *pTrack = Object_track::GetObjectThis(arg)->GetTrack();
	UChar channel = arg.GetUChar(0) & 0x0f;
	UChar pressure = arg.GetUChar(1);
	ULong deltaTime = arg.Is_number(2)? arg.GetULong(2) : 0;
	AutoPtr<Event> pEvent(new MIDIEvent_ChannelPressure(0, channel, pressure));
	pTrack->AddEvent(pEvent.release(), deltaTime);
	return arg.GetValueThis();
}

// midi.track#pitch_bend(channel:number, value:number, deltaTime?:number):map:reduce
Gura_DeclareMethod(track, pitch_bend)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Reduce, FLAG_Map);
	DeclareArg(env, "channel", VTYPE_number);
	DeclareArg(env, "value", VTYPE_number);
	DeclareArg(env, "deltaTime", VTYPE_number, OCCUR_ZeroOrOnce);
	AddHelp(
		Gura_Symbol(en),
		"");
}

Gura_ImplementMethod(track, pitch_bend)
{
	Track *pTrack = Object_track::GetObjectThis(arg)->GetTrack();
	UChar channel = arg.GetUChar(0) & 0x0f;
	UShort value = arg.GetUShort(1);
	ULong deltaTime = arg.Is_number(2)? arg.GetULong(2) : 0;
	AutoPtr<Event> pEvent(new MIDIEvent_PitchBend(0, channel, value));
	pTrack->AddEvent(pEvent.release(), deltaTime);
	return arg.GetValueThis();
}

// midi.track#sequence_number(number:number, deltaTime?:number):map:reduce
Gura_DeclareMethod(track, sequence_number)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Reduce, FLAG_Map);
	DeclareArg(env, "number", VTYPE_number);
	DeclareArg(env, "deltaTime", VTYPE_number, OCCUR_ZeroOrOnce);
	AddHelp(
		Gura_Symbol(en),
		"");
}

Gura_ImplementMethod(track, sequence_number)
{
	Track *pTrack = Object_track::GetObjectThis(arg)->GetTrack();
	ULong deltaTime = arg.Is_number(1)? arg.GetULong(1) : 0;
	AutoPtr<Event> pEvent(new MetaEvent_SequenceNumber(0, arg.GetUShort(0)));
	pTrack->AddEvent(pEvent.release(), deltaTime);
	return arg.GetValueThis();
}

// midi.track#text_event(text:string, deltaTime?:number):map:reduce
Gura_DeclareMethod(track, text_event)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Reduce, FLAG_Map);
	DeclareArg(env, "text", VTYPE_string);
	DeclareArg(env, "deltaTime", VTYPE_number, OCCUR_ZeroOrOnce);
	AddHelp(
		Gura_Symbol(en),
		"");
}

Gura_ImplementMethod(track, text_event)
{
	Track *pTrack = Object_track::GetObjectThis(arg)->GetTrack();
	ULong deltaTime = arg.Is_number(1)? arg.GetULong(1) : 0;
	AutoPtr<Event> pEvent(new MetaEvent_TextEvent(0, arg.GetStringSTL(0)));
	pTrack->AddEvent(pEvent.release(), deltaTime);
	return arg.GetValueThis();
}

// midi.track#copyright_notice(text:string, deltaTime?:number):map:reduce
Gura_DeclareMethod(track, copyright_notice)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Reduce, FLAG_Map);
	DeclareArg(env, "text", VTYPE_string);
	DeclareArg(env, "deltaTime", VTYPE_number, OCCUR_ZeroOrOnce);
	AddHelp(
		Gura_Symbol(en),
		"");
}

Gura_ImplementMethod(track, copyright_notice)
{
	Track *pTrack = Object_track::GetObjectThis(arg)->GetTrack();
	ULong deltaTime = arg.Is_number(1)? arg.GetULong(1) : 0;
	AutoPtr<Event> pEvent(new MetaEvent_CopyrightNotice(0, arg.GetStringSTL(0)));
	pTrack->AddEvent(pEvent.release(), deltaTime);
	return arg.GetValueThis();
}

// midi.track#sequence_or_track_name(text:string, deltaTime?:number):map:reduce
Gura_DeclareMethod(track, sequence_or_track_name)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Reduce, FLAG_Map);
	DeclareArg(env, "text", VTYPE_string);
	DeclareArg(env, "deltaTime", VTYPE_number, OCCUR_ZeroOrOnce);
	AddHelp(
		Gura_Symbol(en),
		"");
}

Gura_ImplementMethod(track, sequence_or_track_name)
{
	Track *pTrack = Object_track::GetObjectThis(arg)->GetTrack();
	ULong deltaTime = arg.Is_number(1)? arg.GetULong(1) : 0;
	AutoPtr<Event> pEvent(new MetaEvent_SequenceOrTrackName(0, arg.GetStringSTL(0)));
	pTrack->AddEvent(pEvent.release(), deltaTime);
	return arg.GetValueThis();
}

// midi.track#instrument_name(text:string, deltaTime?:number):map:reduce
Gura_DeclareMethod(track, instrument_name)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Reduce, FLAG_Map);
	DeclareArg(env, "text", VTYPE_string);
	DeclareArg(env, "deltaTime", VTYPE_number, OCCUR_ZeroOrOnce);
	AddHelp(
		Gura_Symbol(en),
		"");
}

Gura_ImplementMethod(track, instrument_name)
{
	Track *pTrack = Object_track::GetObjectThis(arg)->GetTrack();
	ULong deltaTime = arg.Is_number(1)? arg.GetULong(1) : 0;
	AutoPtr<Event> pEvent(new MetaEvent_InstrumentName(0, arg.GetStringSTL(0)));
	pTrack->AddEvent(pEvent.release(), deltaTime);
	return arg.GetValueThis();
}

// midi.track#lyric_text(text:string, deltaTime?:number):map:reduce
Gura_DeclareMethod(track, lyric_text)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Reduce, FLAG_Map);
	DeclareArg(env, "text", VTYPE_string);
	DeclareArg(env, "deltaTime", VTYPE_number, OCCUR_ZeroOrOnce);
	AddHelp(
		Gura_Symbol(en),
		"");
}

Gura_ImplementMethod(track, lyric_text)
{
	Track *pTrack = Object_track::GetObjectThis(arg)->GetTrack();
	ULong deltaTime = arg.Is_number(1)? arg.GetULong(1) : 0;
	AutoPtr<Event> pEvent(new MetaEvent_LyricText(0, arg.GetStringSTL(0)));
	pTrack->AddEvent(pEvent.release(), deltaTime);
	return arg.GetValueThis();
}

// midi.track#marker_text(text:string, deltaTime?:number):map:reduce
Gura_DeclareMethod(track, marker_text)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Reduce, FLAG_Map);
	DeclareArg(env, "text", VTYPE_string);
	DeclareArg(env, "deltaTime", VTYPE_number, OCCUR_ZeroOrOnce);
	AddHelp(
		Gura_Symbol(en),
		"");
}

Gura_ImplementMethod(track, marker_text)
{
	Track *pTrack = Object_track::GetObjectThis(arg)->GetTrack();
	ULong deltaTime = arg.Is_number(1)? arg.GetULong(1) : 0;
	AutoPtr<Event> pEvent(new MetaEvent_MarkerText(0, arg.GetStringSTL(0)));
	pTrack->AddEvent(pEvent.release(), deltaTime);
	return arg.GetValueThis();
}

// midi.track#cue_point(text:string, deltaTime?:number):map:reduce
Gura_DeclareMethod(track, cue_point)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Reduce, FLAG_Map);
	DeclareArg(env, "text", VTYPE_string);
	DeclareArg(env, "deltaTime", VTYPE_number, OCCUR_ZeroOrOnce);
	AddHelp(
		Gura_Symbol(en),
		"");
}

Gura_ImplementMethod(track, cue_point)
{
	Track *pTrack = Object_track::GetObjectThis(arg)->GetTrack();
	ULong deltaTime = arg.Is_number(1)? arg.GetULong(1) : 0;
	AutoPtr<Event> pEvent(new MetaEvent_CuePoint(0, arg.GetStringSTL(0)));
	pTrack->AddEvent(pEvent.release(), deltaTime);
	return arg.GetValueThis();
}

// midi.track#midi_channel_prefix_assignment(channel:number, deltaTime?:number):map:reduce
Gura_DeclareMethod(track, midi_channel_prefix_assignment)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Reduce, FLAG_Map);
	DeclareArg(env, "channel", VTYPE_number);
	DeclareArg(env, "deltaTime", VTYPE_number, OCCUR_ZeroOrOnce);
	AddHelp(
		Gura_Symbol(en),
		"");
}

Gura_ImplementMethod(track, midi_channel_prefix_assignment)
{
	Track *pTrack = Object_track::GetObjectThis(arg)->GetTrack();
	UChar channel = arg.GetUChar(0);
	ULong deltaTime = arg.Is_number(1)? arg.GetULong(1) : 0;
	AutoPtr<Event> pEvent(new MetaEvent_MIDIChannelPrefixAssignment(0, channel));
	pTrack->AddEvent(pEvent.release(), deltaTime);
	return arg.GetValueThis();
}

// midi.track#end_of_track(deltaTime?:number):map:reduce
Gura_DeclareMethod(track, end_of_track)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Reduce, FLAG_Map);
	DeclareArg(env, "deltaTime", VTYPE_number, OCCUR_ZeroOrOnce);
	AddHelp(
		Gura_Symbol(en),
		"");
}

Gura_ImplementMethod(track, end_of_track)
{
	Track *pTrack = Object_track::GetObjectThis(arg)->GetTrack();
	ULong deltaTime = arg.Is_number(0)? arg.GetULong(0) : 0;
	AutoPtr<Event> pEvent(new MetaEvent_EndOfTrack(0));
	pTrack->AddEvent(pEvent.release(), deltaTime);
	return arg.GetValueThis();
}

// midi.track#tempo_setting(mpqn:number, deltaTime?:number):map:reduce
Gura_DeclareMethod(track, tempo_setting)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Reduce, FLAG_Map);
	DeclareArg(env, "mpqn", VTYPE_number);
	DeclareArg(env, "deltaTime", VTYPE_number, OCCUR_ZeroOrOnce);
	AddHelp(
		Gura_Symbol(en),
		"");
}

Gura_ImplementMethod(track, tempo_setting)
{
	Track *pTrack = Object_track::GetObjectThis(arg)->GetTrack();
	ULong mpqn = arg.GetULong(0);
	ULong deltaTime = arg.Is_number(1)? arg.GetULong(1) : 0;
	AutoPtr<Event> pEvent(new MetaEvent_TempoSetting(0, mpqn));
	pTrack->AddEvent(pEvent.release(), deltaTime);
	return arg.GetValueThis();
}

// midi.track#smpte_offset(hour:number, minute:number, second:number, frame:number, subFrame:number, deltaTime?:number):map:reduce
Gura_DeclareMethod(track, smpte_offset)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Reduce, FLAG_Map);
	DeclareArg(env, "hour", VTYPE_number);
	DeclareArg(env, "minute", VTYPE_number);
	DeclareArg(env, "second", VTYPE_number);
	DeclareArg(env, "frame", VTYPE_number);
	DeclareArg(env, "subFrame", VTYPE_number);
	DeclareArg(env, "deltaTime", VTYPE_number, OCCUR_ZeroOrOnce);
	AddHelp(
		Gura_Symbol(en),
		"");
}

Gura_ImplementMethod(track, smpte_offset)
{
	Track *pTrack = Object_track::GetObjectThis(arg)->GetTrack();
	UChar hour = arg.GetUChar(0);
	UChar minute = arg.GetUChar(1);
	UChar second = arg.GetUChar(2);
	UChar frame = arg.GetUChar(3);
	UChar subFrame = arg.GetUChar(4);
	ULong deltaTime = arg.Is_number(5)? arg.GetULong(5) : 0;
	AutoPtr<Event> pEvent(new MetaEvent_SMPTEOffset(0, hour, minute, second, frame, subFrame));
	pTrack->AddEvent(pEvent.release(), deltaTime);
	return arg.GetValueThis();
}

// midi.track#time_signature(numerator:number, denominator:number, metronome:number, cnt32nd:number, deltaTime?:number):map:reduce
Gura_DeclareMethod(track, time_signature)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Reduce, FLAG_Map);
	DeclareArg(env, "numerator", VTYPE_number);
	DeclareArg(env, "denominator", VTYPE_number);
	DeclareArg(env, "metronome", VTYPE_number);
	DeclareArg(env, "cnt32nd", VTYPE_number);
	DeclareArg(env, "deltaTime", VTYPE_number, OCCUR_ZeroOrOnce);
	AddHelp(
		Gura_Symbol(en),
		"");
}

Gura_ImplementMethod(track, time_signature)
{
	Track *pTrack = Object_track::GetObjectThis(arg)->GetTrack();
	UChar numerator = arg.GetUChar(0);
	UChar denominator = arg.GetUChar(1);
	UChar metronome = arg.GetUChar(2);
	UChar cnt32nd = arg.GetUChar(3);
	ULong deltaTime = arg.Is_number(4)? arg.GetULong(4) : 0;
	AutoPtr<Event> pEvent(new MetaEvent_TimeSignature(0, numerator, denominator, metronome, cnt32nd));
	pTrack->AddEvent(pEvent.release(), deltaTime);
	return arg.GetValueThis();
}

// midi.track#key_signature(key:number, scale:number, deltaTime?:number):map:reduce
Gura_DeclareMethod(track, key_signature)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Reduce, FLAG_Map);
	DeclareArg(env, "key", VTYPE_number);
	DeclareArg(env, "scale", VTYPE_number);
	DeclareArg(env, "deltaTime", VTYPE_number, OCCUR_ZeroOrOnce);
	AddHelp(
		Gura_Symbol(en),
		"");
}

Gura_ImplementMethod(track, key_signature)
{
	Track *pTrack = Object_track::GetObjectThis(arg)->GetTrack();
	UChar key = arg.GetUChar(0);
	UChar scale = arg.GetUChar(1);
	ULong deltaTime = arg.Is_number(2)? arg.GetULong(2) : 0;
	AutoPtr<Event> pEvent(new MetaEvent_KeySignature(0, key, scale));
	pTrack->AddEvent(pEvent.release(), deltaTime);
	return arg.GetValueThis();
}

// midi.track#sequencer_specific_event(binary:binary, deltaTime?:number):map:reduce
Gura_DeclareMethod(track, sequencer_specific_event)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Reduce, FLAG_Map);
	DeclareArg(env, "binary", VTYPE_binary);
	DeclareArg(env, "deltaTime", VTYPE_number, OCCUR_ZeroOrOnce);
	AddHelp(
		Gura_Symbol(en),
		"");
}

Gura_ImplementMethod(track, sequencer_specific_event)
{
	Track *pTrack = Object_track::GetObjectThis(arg)->GetTrack();
	const Binary &binary = arg.GetBinary(0);
	ULong deltaTime = arg.Is_number(1)? arg.GetULong(1) : 0;
	AutoPtr<Event> pEvent(new MetaEvent_SequencerSpecificEvent(0, binary));
	pTrack->AddEvent(pEvent.release(), deltaTime);
	return arg.GetValueThis();
}

//-----------------------------------------------------------------------------
// Class implementation for midi.track
//-----------------------------------------------------------------------------
Gura_ImplementUserClass(track)
{
	// Assignment of properties
	Gura_AssignProperty(track, events);
	// Assignment of methods
	Gura_AssignMethod(track, seek);
	Gura_AssignMethod(track, tell);
	Gura_AssignMethod(track, erase);
	Gura_AssignMethod(track, mml);
	Gura_AssignMethod(track, note_off);
	Gura_AssignMethod(track, note_on);
	Gura_AssignMethod(track, poly_pressure);
	Gura_AssignMethod(track, control_change);
	Gura_AssignMethod(track, program_change);
	Gura_AssignMethod(track, channel_pressure);
	Gura_AssignMethod(track, pitch_bend);
	Gura_AssignMethod(track, sequence_number);
	Gura_AssignMethod(track, text_event);
	Gura_AssignMethod(track, copyright_notice);
	Gura_AssignMethod(track, sequence_or_track_name);
	Gura_AssignMethod(track, instrument_name);
	Gura_AssignMethod(track, lyric_text);
	Gura_AssignMethod(track, marker_text);
	Gura_AssignMethod(track, cue_point);
	Gura_AssignMethod(track, midi_channel_prefix_assignment);
	Gura_AssignMethod(track, end_of_track);
	Gura_AssignMethod(track, tempo_setting);
	Gura_AssignMethod(track, smpte_offset);
	Gura_AssignMethod(track, time_signature);
	Gura_AssignMethod(track, key_signature);
	Gura_AssignMethod(track, sequencer_specific_event);
}

//-----------------------------------------------------------------------------
// Object_sequence
//-----------------------------------------------------------------------------
Object *Object_sequence::Clone() const
{
	return nullptr;
}

String Object_sequence::ToString(bool exprFlag)
{
	String rtn;
	rtn += "<midi.sequence";
	do {
		char buff[128];
		::sprintf(buff, ":format=%d:tracks=%ld:division=%d",
				_sequence.GetFormat(), _sequence.GetTrackOwner().size(),
				_sequence.GetProperty()->GetDivision());
		rtn += buff;
	} while (0);
	rtn += ">";
	return rtn;
}

//-----------------------------------------------------------------------------
// Implementation of properties
//-----------------------------------------------------------------------------
// midi.sequence#division
Gura_DeclareProperty_RW(sequence, division)
{
	SetPropAttr(VTYPE_number);
	AddHelp(
		Gura_Symbol(en),
		""
		);
}

Gura_ImplementPropertyGetter(sequence, division)
{
	Sequence &sequence = Object_sequence::GetObject(valueThis)->GetSequence();
	return Value(sequence.GetProperty()->GetDivision());
}

Gura_ImplementPropertySetter(sequence, division)
{
	Sequence &sequence = Object_sequence::GetObject(valueThis)->GetSequence();
	UShort division = value.GetUShort();
	sequence.GetProperty()->SetDivision(division);
	return value;
}

// midi.sequence#events
Gura_DeclareProperty_R(sequence, events)
{
	SetPropAttr(VTYPE_iterator);
	AddHelp(
		Gura_Symbol(en),
		""
		);
}

Gura_ImplementPropertyGetter(sequence, events)
{
	const Sequence &sequence = Object_sequence::GetObject(valueThis)->GetSequence();
	Iterator *pIterator = new Iterator_eventAll(sequence.GetTrackOwner().Reference());
	return Value(new Object_iterator(env, pIterator));
}

// midi.sequence#format
Gura_DeclareProperty_RW(sequence, format)
{
	SetPropAttr(VTYPE_number);
	AddHelp(
		Gura_Symbol(en),
		""
		);
}

Gura_ImplementPropertyGetter(sequence, format)
{
	const Sequence &sequence = Object_sequence::GetObject(valueThis)->GetSequence();
	return Value(sequence.GetFormat());
}

Gura_ImplementPropertySetter(sequence, format)
{
	Sequence &sequence = Object_sequence::GetObject(valueThis)->GetSequence();
	UShort format = value.GetUShort();
	if (format > 2) {
		env.SetError(ERR_ValueError, "wrong number for format");
		return Value::Nil;
	}
	sequence.SetFormat(format);
	return value;
}

// midi.sequence#tracks
Gura_DeclareProperty_R(sequence, tracks)
{
	SetPropAttr(VTYPE_iterator);
	AddHelp(
		Gura_Symbol(en),
		""
		);
}

Gura_ImplementPropertyGetter(sequence, tracks)
{
	const Sequence &sequence = Object_sequence::GetObject(valueThis)->GetSequence();
	Iterator *pIterator = new Iterator_track(sequence.GetTrackOwner().Reference());
	return Value(new Object_iterator(env, pIterator));
}

//-----------------------------------------------------------------------------
// Gura interfaces for midi.sequence
//-----------------------------------------------------------------------------
// midi.sequence#read(stream:stream:r):map:reduce
Gura_DeclareMethod(sequence, read)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Reduce, FLAG_Map);
	DeclareArg(env, "stream", VTYPE_stream, OCCUR_Once, FLAG_Read);
	AddHelp(
		Gura_Symbol(en),
		"");
}

Gura_ImplementMethod(sequence, read)
{
	Signal &sig = env.GetSignal();
	Object_sequence *pThis = Object_sequence::GetObjectThis(arg);
	if (!pThis->GetSequence().Read(env, arg.GetStream(0))) return Value::Nil;
	return arg.GetValueThis();
}

// midi.sequence#write(stream:stream:w):map:reduce
Gura_DeclareMethod(sequence, write)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Reduce, FLAG_Map);
	DeclareArg(env, "stream", VTYPE_stream, OCCUR_Once, FLAG_Write);
	AddHelp(
		Gura_Symbol(en),
		"");
}

Gura_ImplementMethod(sequence, write)
{
	Signal &sig = env.GetSignal();
	Object_sequence *pThis = Object_sequence::GetObjectThis(arg);
	if (!pThis->GetSequence().Write(env, arg.GetStream(0))) return Value::Nil;
	return arg.GetValueThis();
}

// midi.sequence#play(port:midi.port, speed?:number, repeat:number:nil => 1):[background,player]
Gura_DeclareMethod(sequence, play)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "port", VTYPE_port);
	DeclareArg(env, "speed", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareArg(env, "repeat", VTYPE_number, OCCUR_Once,
			   FLAG_Nil, 0, new Expr_Value(Value(1)));
	DeclareAttr(Gura_UserSymbol(background));
	DeclareAttr(Gura_UserSymbol(player));
	AddHelp(
		Gura_Symbol(en),
		"");
}

Gura_ImplementMethod(sequence, play)
{
	Signal &sig = env.GetSignal();
	Sequence &sequence = Object_sequence::GetObjectThis(arg)->GetSequence();
	Port *pPort = Object_port::GetObject(arg, 0)->GetPort();
	double speed = arg.Is_number(1)? arg.GetDouble(1) : 1;
	int cntRepeat = arg.Is_number(2)? arg.GetInt(2) : -1;
	return ActivatePlayer(env, sig, arg, sequence, pPort, speed, cntRepeat);
}

// midi.sequence#track(index:number):map {block?}
Gura_DeclareMethod(sequence, track)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "index", VTYPE_number);
	DeclareBlock(OCCUR_ZeroOrOnce);
	AddHelp(
		Gura_Symbol(en),
		"");
}

Gura_ImplementMethod(sequence, track)
{
	Object_sequence *pThis = Object_sequence::GetObjectThis(arg);
	size_t index = arg.GetSizeT(0);
	TrackOwner &trackOwner = pThis->GetSequence().GetTrackOwner();
	if (index >= trackOwner.size()) {
		size_t n = index - trackOwner.size() + 1;
		while (n-- > 0) {
			trackOwner.push_back(new Track(Property::Reference(
									pThis->GetSequence().GetProperty())));
		}
	}
	Track *pTrack = trackOwner[index];
	return ReturnValue(env, arg,
				Value(new Object_track(env, Track::Reference(pTrack))));
}

// midi.sequence#mml(str:string, max_velocity?:number):reduce
Gura_DeclareMethod(sequence, mml)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Reduce, FLAG_None);
	DeclareArg(env, "str", VTYPE_string);
	DeclareArg(env, "max_velocity", VTYPE_number, OCCUR_ZeroOrOnce);
	AddHelp(
		Gura_Symbol(en),
		"");
}

Gura_ImplementMethod(sequence, mml)
{
	Signal &sig = env.GetSignal();
	Object_sequence *pThis = Object_sequence::GetObjectThis(arg);
	int velocityMax = arg.Is_number(1)? arg.GetInt(1) : 127;
	MML mml(velocityMax);
	if (!mml.ParseString(sig, pThis->GetSequence(), arg.GetString(0))) return Value::Nil;
	return arg.GetValueThis();
}

// midi.sequence#readmml(stream:stream, max_velocity?:number):reduce
Gura_DeclareMethod(sequence, readmml)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Reduce, FLAG_None);
	DeclareArg(env, "stream", VTYPE_stream);
	DeclareArg(env, "max_velocity", VTYPE_number, OCCUR_ZeroOrOnce);
	AddHelp(
		Gura_Symbol(en),
		"");
}

Gura_ImplementMethod(sequence, readmml)
{
	Signal &sig = env.GetSignal();
	Object_sequence *pThis = Object_sequence::GetObjectThis(arg);
	int velocityMax = arg.Is_number(1)? arg.GetInt(1) : 127;
	MML mml(velocityMax);
	if (!mml.ParseStream(sig, pThis->GetSequence(), arg.GetStream(0))) return Value::Nil;
	return arg.GetValueThis();
}

//-----------------------------------------------------------------------------
// Class implementation for midi.sequence
//-----------------------------------------------------------------------------
Gura_ImplementUserClassWithCast(sequence)
{
	// Assignment of properties
	Gura_AssignProperty(sequence, division);
	Gura_AssignProperty(sequence, events);
	Gura_AssignProperty(sequence, format);
	Gura_AssignProperty(sequence, tracks);
	// Assignment of methods
	Gura_AssignMethod(sequence, read);
	Gura_AssignMethod(sequence, write);
	Gura_AssignMethod(sequence, play);
	Gura_AssignMethod(sequence, track);
	Gura_AssignMethod(sequence, mml);
	Gura_AssignMethod(sequence, readmml);
}

Gura_ImplementCastFrom(sequence)
{
	Signal &sig = GetSignal();
	Value valueCast(value);
	env.LookupClass(VTYPE_stream)->CastFrom(env, valueCast, flags);
	if (valueCast.Is_stream()) {
		AutoPtr<Object_sequence> pObj(new Object_sequence(env));
		pObj->GetSequence().Read(env, valueCast.GetStream());
		valueCast = Value::Nil; // delete stream instance
		if (sig.IsSignalled()) return false;
		value = Value(pObj.release());
		return true;
	}
	return false;
}

Gura_ImplementCastTo(sequence)
{
	return false;
}

//-----------------------------------------------------------------------------
// Object_portinfo
//-----------------------------------------------------------------------------
Object *Object_portinfo::Clone() const
{
	return nullptr;
}

String Object_portinfo::ToString(bool exprFlag)
{
	String rtn;
	rtn += "<midi.portinfo:";
	rtn += ">";
	return rtn;
}

//-----------------------------------------------------------------------------
// Implementation of properties
//-----------------------------------------------------------------------------
// midi.portinfo#string
Gura_DeclareProperty_R(portinfo, string)
{
	SetPropAttr(VTYPE_string);
	AddHelp(
		Gura_Symbol(en),
		""
		);
}

Gura_ImplementPropertyGetter(portinfo, string)
{
	
	return Value::Nil;
}

//-----------------------------------------------------------------------------
// Gura interfaces for midi.portinfo
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Class implementation for midi.portinfo
//-----------------------------------------------------------------------------
Gura_ImplementUserClass(portinfo)
{
	// Assignment of properties
#if 0
	Gura_AssignProperty(portinfo, string);
#endif
}

//-----------------------------------------------------------------------------
// Object_port
//-----------------------------------------------------------------------------
Object *Object_port::Clone() const
{
	return nullptr;
}

String Object_port::ToString(bool exprFlag)
{
	String rtn;
	rtn += "<midi.port:";
	rtn += ">";
	return rtn;
}

//-----------------------------------------------------------------------------
// Implementation of properties
//-----------------------------------------------------------------------------
// midi.port#string
Gura_DeclareProperty_R(port, string)
{
	SetPropAttr(VTYPE_string);
	AddHelp(
		Gura_Symbol(en),
		""
		);
}

Gura_ImplementPropertyGetter(port, string)
{
	return Value::Nil;
}

//-----------------------------------------------------------------------------
// Gura interfaces for midi.port
//-----------------------------------------------------------------------------
// midi.port#send(msg+:number):map:reduce
Gura_DeclareMethod(port, send)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Reduce, FLAG_Map);
	DeclareArg(env, "msg", VTYPE_number, OCCUR_OnceOrMore);
	AddHelp(
		Gura_Symbol(en),
		"");
}

Gura_ImplementMethod(port, send)
{
	Signal &sig = env.GetSignal();
	Object_port *pThis = Object_port::GetObjectThis(arg);
	const ValueList &valList = arg.GetList(0);
	size_t nArgs = valList.size();
	if (nArgs == 1) {
		pThis->GetPort()->Send(valList[0].GetUChar());
	} else if (nArgs == 2) {
		pThis->GetPort()->Send(valList[0].GetUChar(), valList[1].GetUChar());
	} else if (nArgs == 3) {
		pThis->GetPort()->Send(valList[0].GetUChar(), valList[1].GetUChar(),
														valList[2].GetUChar());
	} else if (nArgs == 4) {
		pThis->GetPort()->Send(valList[0].GetUChar(), valList[1].GetUChar(),
							valList[2].GetUChar(), valList[3].GetUChar());
	} else {
		sig.SetError(ERR_ArgumentError, "too many arguments");
		return Value::Nil;
	}
	return arg.GetValueThis();
}

// midi.port#play(sequence:midi.sequence, speed?:number, repeat:number:nil => 1):map:[background,player]
Gura_DeclareMethod(port, play)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "sequence", VTYPE_sequence);
	DeclareArg(env, "speed", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareArg(env, "repeat", VTYPE_number, OCCUR_Once,
			   FLAG_Nil, 0, new Expr_Value(Value(1)));
	DeclareAttr(Gura_UserSymbol(background));
	DeclareAttr(Gura_UserSymbol(player));
	AddHelp(
		Gura_Symbol(en),
		"");
}

Gura_ImplementMethod(port, play)
{
	Signal &sig = env.GetSignal();
	Object_port *pThis = Object_port::GetObjectThis(arg);
	Sequence &sequence = Object_sequence::GetObject(arg, 0)->GetSequence();
	double speed = arg.Is_number(1)? arg.GetDouble(1) : 1;
	int cntRepeat = arg.Is_number(2)? arg.GetInt(2) : -1;
	return ActivatePlayer(env, sig, arg, sequence, pThis->GetPort(), speed, cntRepeat);
}

// midi.port#mml(str:string, max_velocity?:number):[background,player]
Gura_DeclareMethod(port, mml)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "str", VTYPE_string);
	DeclareArg(env, "max_velocity", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareAttr(Gura_UserSymbol(background));
	DeclareAttr(Gura_UserSymbol(player));
	AddHelp(
		Gura_Symbol(en),
		"");
}

Gura_ImplementMethod(port, mml)
{
	Signal &sig = env.GetSignal();
	Object_port *pThis = Object_port::GetObjectThis(arg);
	Sequence sequence;
	int velocityMax = arg.Is_number(1)? arg.GetInt(1) : 127;
	MML mml(velocityMax);
	if (!mml.ParseString(sig, sequence, arg.GetString(0))) return Value::Nil;
	double speed = 1;
	int cntRepeat = 1;
	return ActivatePlayer(env, sig, arg, sequence, pThis->GetPort(), speed, cntRepeat);
}

// midi.port#readmml(stream:stream, max_velocity?:number):[background,player]
Gura_DeclareMethod(port, readmml)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "stream", VTYPE_stream);
	DeclareArg(env, "max_velocity", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareAttr(Gura_UserSymbol(background));
	DeclareAttr(Gura_UserSymbol(player));
	AddHelp(
		Gura_Symbol(en),
		"");
}

Gura_ImplementMethod(port, readmml)
{
	Signal &sig = env.GetSignal();
	Object_port *pThis = Object_port::GetObjectThis(arg);
	Sequence sequence;
	int velocityMax = arg.Is_number(1)? arg.GetInt(1) : 127;
	MML mml(velocityMax);
	if (!mml.ParseStream(sig, sequence, arg.GetStream(0))) return Value::Nil;
	double speed = 1;
	int cntRepeat = 1;
	return ActivatePlayer(env, sig, arg, sequence, pThis->GetPort(), speed, cntRepeat);
}

// midi.port#note_off(channel:number, note:number, velocity:number):map:reduce
Gura_DeclareMethod(port, note_off)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Reduce, FLAG_Map);
	DeclareArg(env, "channel", VTYPE_number);
	DeclareArg(env, "note", VTYPE_number);
	DeclareArg(env, "velocity", VTYPE_number);
	AddHelp(
		Gura_Symbol(en),
		"");
}

Gura_ImplementMethod(port, note_off)
{
	Port *pPort = Object_port::GetObjectThis(arg)->GetPort();
	UChar channel = arg.GetUChar(0) & 0x0f;
	UChar note = arg.GetUChar(1);
	UChar velocity = arg.GetUChar(2);
	pPort->Send(MIDIEvent_NoteOff::Status | channel, note, velocity);
	return arg.GetValueThis();
}

// midi.port#note_on(channel:number, note:number, velocity:number):map:reduce
Gura_DeclareMethod(port, note_on)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Reduce, FLAG_Map);
	DeclareArg(env, "channel", VTYPE_number);
	DeclareArg(env, "note", VTYPE_number);
	DeclareArg(env, "velocity", VTYPE_number);
	AddHelp(
		Gura_Symbol(en),
		"");
}

Gura_ImplementMethod(port, note_on)
{
	Port *pPort = Object_port::GetObjectThis(arg)->GetPort();
	UChar channel = arg.GetUChar(0) & 0x0f;
	UChar note = arg.GetUChar(1);
	UChar velocity = arg.GetUChar(2);
	pPort->Send(MIDIEvent_NoteOn::Status | channel, note, velocity);
	return arg.GetValueThis();
}

// midi.port#poly_pressure(channel:number, note:number, value:number):map:reduce
Gura_DeclareMethod(port, poly_pressure)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Reduce, FLAG_Map);
	DeclareArg(env, "channel", VTYPE_number);
	DeclareArg(env, "note", VTYPE_number);
	DeclareArg(env, "value", VTYPE_number);
	AddHelp(
		Gura_Symbol(en),
		"");
}

Gura_ImplementMethod(port, poly_pressure)
{
	Port *pPort = Object_port::GetObjectThis(arg)->GetPort();
	UChar channel = arg.GetUChar(0) & 0x0f;
	UChar note = arg.GetUChar(1);
	UChar value = arg.GetUChar(2);
	pPort->Send(MIDIEvent_PolyPressure::Status | channel, note, value);
	return arg.GetValueThis();
}

// midi.port#control_change(channel:number, controller:number, value:number):map:reduce
Gura_DeclareMethod(port, control_change)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Reduce, FLAG_Map);
	DeclareArg(env, "channel", VTYPE_number);
	DeclareArg(env, "controller", VTYPE_number);
	DeclareArg(env, "value", VTYPE_number);
	AddHelp(
		Gura_Symbol(en),
		"");
}

Gura_ImplementMethod(port, control_change)
{
	Port *pPort = Object_port::GetObjectThis(arg)->GetPort();
	UChar channel = arg.GetUChar(0) & 0x0f;
	UChar controller = arg.GetUChar(1);
	UChar value = arg.GetUChar(2);
	pPort->Send(MIDIEvent_ControlChange::Status | channel, controller, value);
	return arg.GetValueThis();
}

// midi.port#program_change(channel:number, program:number):map:reduce
Gura_DeclareMethod(port, program_change)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Reduce, FLAG_Map);
	DeclareArg(env, "channel", VTYPE_number);
	DeclareArg(env, "program", VTYPE_number);
	AddHelp(
		Gura_Symbol(en),
		"");
}

Gura_ImplementMethod(port, program_change)
{
	Port *pPort = Object_port::GetObjectThis(arg)->GetPort();
	UChar channel = arg.GetUChar(0) & 0x0f;
	UChar program = arg.GetUChar(1);
	pPort->Send(MIDIEvent_ProgramChange::Status | channel, program);
	return arg.GetValueThis();
}

// midi.port#channel_pressure(channel:number, pressure:number):map:reduce
Gura_DeclareMethod(port, channel_pressure)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Reduce, FLAG_Map);
	DeclareArg(env, "channel", VTYPE_number);
	DeclareArg(env, "pressure", VTYPE_number);
	AddHelp(
		Gura_Symbol(en),
		"");
}

Gura_ImplementMethod(port, channel_pressure)
{
	Port *pPort = Object_port::GetObjectThis(arg)->GetPort();
	UChar channel = arg.GetUChar(0) & 0x0f;
	UChar pressure = arg.GetUChar(1);
	pPort->Send(MIDIEvent_ChannelPressure::Status | channel, pressure);
	return arg.GetValueThis();
}

// midi.port#pitch_bend(channel:number, value:number):map:reduce
Gura_DeclareMethod(port, pitch_bend)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Reduce, FLAG_Map);
	DeclareArg(env, "channel", VTYPE_number);
	DeclareArg(env, "value", VTYPE_number);
	AddHelp(
		Gura_Symbol(en),
		"");
}

Gura_ImplementMethod(port, pitch_bend)
{
	Port *pPort = Object_port::GetObjectThis(arg)->GetPort();
	UChar channel = arg.GetUChar(0) & 0x0f;
	UShort value = arg.GetUShort(1);
	pPort->Send(MIDIEvent_PitchBend::Status | channel,
			static_cast<UChar>((value >> 0) & 0x7f),
			static_cast<UChar>((value >> 7) & 0x7f));
	return arg.GetValueThis();
}

//-----------------------------------------------------------------------------
// Class implementation for midi.port
//-----------------------------------------------------------------------------
Gura_ImplementUserClassWithCast(port)
{
	// Assignment of properties
#if 0
	Gura_AssignProperty(port, string);
#endif
	// Assignment of methods
	Gura_AssignMethod(port, send);
	Gura_AssignMethod(port, play);
	Gura_AssignMethod(port, mml);
	Gura_AssignMethod(port, readmml);
	Gura_AssignMethod(port, note_off);
	Gura_AssignMethod(port, note_on);
	Gura_AssignMethod(port, poly_pressure);
	Gura_AssignMethod(port, control_change);
	Gura_AssignMethod(port, program_change);
	Gura_AssignMethod(port, channel_pressure);
	Gura_AssignMethod(port, pitch_bend);
}

Gura_ImplementCastFrom(port)
{
	Signal &sig = GetSignal();
	if (value.Is_number()) {
		int id = value.GetInt();
		AutoPtr<Object_port> pObj(new Object_port(env));
		if (!pObj->GetPort()->Open(id)) {
			sig.SetError(ERR_IOError, "can't open MIDI port #%d", id);
			return false;
		}
		value = Value(pObj.release());
		return true;
	}
	return false;
}

Gura_ImplementCastTo(port)
{
	return false;
}

//-----------------------------------------------------------------------------
// Object_player
//-----------------------------------------------------------------------------
Object *Object_player::Clone() const
{
	return nullptr;
}

String Object_player::ToString(bool exprFlag)
{
	String rtn;
	rtn += "<midi.player";
	rtn += ">";
	return rtn;
}

//-----------------------------------------------------------------------------
// Implementation of properties
//-----------------------------------------------------------------------------
// midi.player#count
Gura_DeclareProperty_R(player, count)
{
	SetPropAttr(VTYPE_number);
	AddHelp(
		Gura_Symbol(en),
		""
		);
}

Gura_ImplementPropertyGetter(player, count)
{
	const Player *pPlayer = Object_player::GetObject(valueThis)->GetPlayer();
	return Value(pPlayer->CountEvents());
}

// midi.player#progress
Gura_DeclareProperty_R(player, progress)
{
	SetPropAttr(VTYPE_number);
	AddHelp(
		Gura_Symbol(en),
		""
		);
}

Gura_ImplementPropertyGetter(player, progress)
{
	const Player *pPlayer = Object_player::GetObject(valueThis)->GetPlayer();
	return Value(pPlayer->GetProgress());
}

// midi.player#repeat
Gura_DeclareProperty_R(player, repeat)
{
	SetPropAttr(VTYPE_number);
	AddHelp(
		Gura_Symbol(en),
		""
		);
}

Gura_ImplementPropertyGetter(player, repeat)
{
	const Player *pPlayer = Object_player::GetObject(valueThis)->GetPlayer();
	return Value(pPlayer->GetRepeat());
}

// midi.player#speed
Gura_DeclareProperty_RW(player, speed)
{
	SetPropAttr(VTYPE_number);
	AddHelp(
		Gura_Symbol(en),
		""
		);
}

Gura_ImplementPropertyGetter(player, speed)
{
	const Player *pPlayer = Object_player::GetObject(valueThis)->GetPlayer();
	return Value(pPlayer->GetSpeed());
}

Gura_ImplementPropertySetter(player, speed)
{
	Player *pPlayer = Object_player::GetObject(valueThis)->GetPlayer();
	double speed = value.GetDouble();
	if (speed <= 0) {
		env.SetError(ERR_ValueError, "nuber of speed must be more than zero");
		return Value::Nil;
	}
	pPlayer->SetSpeed(speed);
	return value;
}

//-----------------------------------------------------------------------------
// Gura interfaces for midi.player
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Class implementation for midi.player
//-----------------------------------------------------------------------------
Gura_ImplementUserClass(player)
{
	// Assignment of properties
	Gura_AssignProperty(player, count);
	Gura_AssignProperty(player, progress);
	Gura_AssignProperty(player, repeat);
	Gura_AssignProperty(player, speed);
}

//-----------------------------------------------------------------------------
// Object_controller
//-----------------------------------------------------------------------------
Object *Object_controller::Clone() const
{
	return nullptr;
}

String Object_controller::ToString(bool exprFlag)
{
	String rtn;
	rtn += "<midi.controller:";
	rtn += GetControllerInfo().name;
	rtn += ">";
	return rtn;
}

//-----------------------------------------------------------------------------
// Implementation of properties
//-----------------------------------------------------------------------------
// midi.controller#id
Gura_DeclareProperty_R(controller, id)
{
	SetPropAttr(VTYPE_number);
	AddHelp(
		Gura_Symbol(en),
		""
		);
}

Gura_ImplementPropertyGetter(controller, id)
{
	Object_controller *pObjThis = Object_controller::GetObject(valueThis);
	return Value(pObjThis->GetController());
}

// midi.controller#name
Gura_DeclareProperty_R(controller, name)
{
	SetPropAttr(VTYPE_string);
	AddHelp(
		Gura_Symbol(en),
		""
		);
}

Gura_ImplementPropertyGetter(controller, name)
{
	Object_controller *pObjThis = Object_controller::GetObject(valueThis);
	return Value(pObjThis->GetControllerInfo().name);
}

//-----------------------------------------------------------------------------
// Gura interfaces for midi.controller
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Class implementation for midi.controller
//-----------------------------------------------------------------------------
Gura_ImplementUserClass(controller)
{
	// Assignment of properties
	Gura_AssignProperty(controller, id);
	Gura_AssignProperty(controller, name);
}

//-----------------------------------------------------------------------------
// Object_program
//-----------------------------------------------------------------------------
Object *Object_program::Clone() const
{
	return nullptr;
}

String Object_program::ToString(bool exprFlag)
{
	String rtn;
	rtn += "<midi.program:";
	rtn += GetProgramInfo().name;
	rtn += ">";
	return rtn;
}

//-----------------------------------------------------------------------------
// Implementation of properties
//-----------------------------------------------------------------------------
// midi.program#dispname
Gura_DeclareProperty_R(program, dispname)
{
	SetPropAttr(VTYPE_string);
	AddHelp(
		Gura_Symbol(en),
		""
		);
}

Gura_ImplementPropertyGetter(program, dispname)
{
	Object_program *pObjThis = Object_program::GetObject(valueThis);
	return Value(pObjThis->GetProgramInfo().dispName);
}

// midi.program#id
Gura_DeclareProperty_R(program, id)
{
	SetPropAttr(VTYPE_number);
	AddHelp(
		Gura_Symbol(en),
		""
		);
}

Gura_ImplementPropertyGetter(program, id)
{
	Object_program *pObjThis = Object_program::GetObject(valueThis);
	return Value(pObjThis->GetProgram());
}

// midi.program#name
Gura_DeclareProperty_R(program, name)
{
	SetPropAttr(VTYPE_string);
	AddHelp(
		Gura_Symbol(en),
		""
		);
}

Gura_ImplementPropertyGetter(program, name)
{
	Object_program *pObjThis = Object_program::GetObject(valueThis);
	return Value(pObjThis->GetProgramInfo().name);
}

//-----------------------------------------------------------------------------
// Gura interfaces for midi.program
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Class implementation for midi.program
//-----------------------------------------------------------------------------
Gura_ImplementUserClass(program)
{
	// Assignment of properties
	Gura_AssignProperty(program, dispname);
	Gura_AssignProperty(program, id);
	Gura_AssignProperty(program, name);
}

//-----------------------------------------------------------------------------
// Object_soundfont
//-----------------------------------------------------------------------------
Object *Object_soundfont::Clone() const
{
	return nullptr;
}

String Object_soundfont::ToString(bool exprFlag)
{
	String rtn;
	rtn += "<midi.soundfont";
	rtn += ">";
	return rtn;
}

//-----------------------------------------------------------------------------
// Implementation of properties
//-----------------------------------------------------------------------------
// midi.soundfont#dispname
Gura_DeclareProperty_R(soundfont, dispname)
{
	SetPropAttr(VTYPE_any);
	AddHelp(
		Gura_Symbol(en),
		""
		);
}

Gura_ImplementPropertyGetter(soundfont, dispname)
{
	return Value::Nil;
}

// midi.soundfont#id
Gura_DeclareProperty_R(soundfont, id)
{
	SetPropAttr(VTYPE_any);
	AddHelp(
		Gura_Symbol(en),
		""
		);
}

Gura_ImplementPropertyGetter(soundfont, id)
{
	return Value::Nil;
}

// midi.soundfont#name
Gura_DeclareProperty_R(soundfont, name)
{
	SetPropAttr(VTYPE_any);
	AddHelp(
		Gura_Symbol(en),
		""
		);
}

Gura_ImplementPropertyGetter(soundfont, name)
{
	return Value::Nil;
}

//-----------------------------------------------------------------------------
// Gura interfaces for midi.soundfont
//-----------------------------------------------------------------------------
// midi.soundfont#synthesizer(preset:number, bank:number, key:number, velocity:number):map {block?}
Gura_DeclareMethod(soundfont, synthesizer)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "preset", VTYPE_number);
	DeclareArg(env, "bank", VTYPE_number);
	DeclareArg(env, "key", VTYPE_number);
	DeclareArg(env, "velocity", VTYPE_number);
	DeclareBlock(OCCUR_ZeroOrOnce);
	AddHelp(
		Gura_Symbol(en),
		"");
}

Gura_ImplementMethod(soundfont, synthesizer)
{
	Signal &sig = env.GetSignal();
	SoundFont &soundFont = Object_soundfont::GetObjectThis(arg)->GetSoundFont();
	UShort wPreset = arg.GetUShort(0);
	UShort wBank = arg.GetUShort(1);
	UChar key = arg.GetUChar(2);
	UChar velocity = arg.GetUChar(3);
	SoundFont::Synthesizer *pSynthesizer =
				soundFont.CreateSynthesizer(sig, wPreset, wBank, key, velocity);
	if (pSynthesizer == nullptr) return Value::Nil;
	return ReturnValue(env, arg, Value(new Object_synthesizer(env, pSynthesizer)));
}

// midi.soundfont#print():void
Gura_DeclareMethod(soundfont, print)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	AddHelp(
		Gura_Symbol(en),
		"");
}

Gura_ImplementMethod(soundfont, print)
{
	SoundFont &soundFont = Object_soundfont::GetObjectThis(arg)->GetSoundFont();
	soundFont.Print();
	return Value::Nil;
}

//-----------------------------------------------------------------------------
// Class implementation for midi.soundfont
//-----------------------------------------------------------------------------
Gura_ImplementUserClass(soundfont)
{
	// Assignment of properties
#if 0
	Gura_AssignProperty(soundfont, dispname);
	Gura_AssignProperty(soundfont, id);
	Gura_AssignProperty(soundfont, name);
#endif
	// Assignment of methods
	Gura_AssignMethod(soundfont, synthesizer);
	Gura_AssignMethod(soundfont, print);
}

//-----------------------------------------------------------------------------
// Object_synthesizer
//-----------------------------------------------------------------------------
Object *Object_synthesizer::Clone() const
{
	return nullptr;
}

String Object_synthesizer::ToString(bool exprFlag)
{
	String rtn;
	rtn += "<midi.synthesizer";
	rtn += ">";
	return rtn;
}

//-----------------------------------------------------------------------------
// Implementation of properties
//-----------------------------------------------------------------------------
// midi.synthesizer#audio
Gura_DeclareProperty_R(synthesizer, audio)
{
	SetPropAttr(VTYPE_any);
	AddHelp(
		Gura_Symbol(en),
		""
		);
}

Gura_ImplementPropertyGetter(synthesizer, audio)
{
	SoundFont::Synthesizer *pSynthesizer =
		Object_synthesizer::GetObject(valueThis)->GetSynthesizer();
	return Value(new Object_audio(
					 env, pSynthesizer->GetSample()->GetAudio()->Reference()));
}

//-----------------------------------------------------------------------------
// Gura interfaces for midi.synthesizer
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Class implementation for midi.synthesizer
//-----------------------------------------------------------------------------
Gura_ImplementUserClass(synthesizer)
{
	// Assignment of properties
	Gura_AssignProperty(synthesizer, audio);
}

//-----------------------------------------------------------------------------
// Iterator_track
//-----------------------------------------------------------------------------
Iterator_track::Iterator_track(TrackOwner *pTrackOwner) :
						Iterator(Finite), _idxTrack(0), _pTrackOwner(pTrackOwner)
{
}

Iterator *Iterator_track::GetSource()
{
	return nullptr;
}

bool Iterator_track::DoNext(Environment &env, Value &value)
{
	if (_idxTrack < _pTrackOwner->size()) {
		Track *pTrack = (*_pTrackOwner)[_idxTrack++];
		value = Value(new Object_track(env, Track::Reference(pTrack)));
		return true;
	}
	return false;
}

String Iterator_track::ToString() const
{
	String rtn;
	rtn += "<iterator:midi.track";
	rtn += ">";
	return rtn;
}

void Iterator_track::GatherFollower(Environment::Frame *pFrame, EnvironmentSet &envSet)
{
}

//-----------------------------------------------------------------------------
// Iterator_eventAll
//-----------------------------------------------------------------------------
Iterator_eventAll::Iterator_eventAll(TrackOwner *pTrackOwner) :
		Iterator(Finite), _idxTrack(0), _idxEvent(0), _pTrackOwner(pTrackOwner)
{
}

Iterator *Iterator_eventAll::GetSource()
{
	return nullptr;
}

bool Iterator_eventAll::DoNext(Environment &env, Value &value)
{
	for ( ; _idxTrack < _pTrackOwner->size(); _idxTrack++) {
		Track *pTrack = (*_pTrackOwner)[_idxTrack];
		const EventOwner &eventOwner = pTrack->GetEventOwner();
		if (_idxEvent < eventOwner.size()) {
			Event *pEvent = eventOwner[_idxEvent++];
			value = Value(new Object_event(env, Event::Reference(pEvent)));
			return true;
		}
	}
	return false;
}

String Iterator_eventAll::ToString() const
{
	String rtn;
	rtn += "<iterator:midi.event_all";
	rtn += ">";
	return rtn;
}

void Iterator_eventAll::GatherFollower(Environment::Frame *pFrame, EnvironmentSet &envSet)
{
}

//-----------------------------------------------------------------------------
// Iterator_event
//-----------------------------------------------------------------------------
Iterator_event::Iterator_event(EventOwner *pEventOwner) :
						Iterator(Finite), _idxEvent(0), _pEventOwner(pEventOwner)
{
}

Iterator *Iterator_event::GetSource()
{
	return nullptr;
}

bool Iterator_event::DoNext(Environment &env, Value &value)
{
	if (_idxEvent < _pEventOwner->size()) {
		Event *pEvent = (*_pEventOwner)[_idxEvent++];
		value = Value(new Object_event(env, Event::Reference(pEvent)));
		return true;
	}
	return false;
}

String Iterator_event::ToString() const
{
	String rtn;
	rtn += "<iterator:midi.event";
	rtn += ">";
	return rtn;
}

void Iterator_event::GatherFollower(Environment::Frame *pFrame, EnvironmentSet &envSet)
{
}

//-----------------------------------------------------------------------------
// Gura module functions: midi
//-----------------------------------------------------------------------------
// midi.sequence(stream?:stream) {block?}
Gura_DeclareFunction(sequence)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "stream", VTYPE_stream, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
	SetClassToConstruct(Gura_UserClass(sequence));
	AddHelp(
		Gura_Symbol(en),
		"It creates an instance that contains SMF information.\n");
}

Gura_ImplementFunction(sequence)
{
	Signal &sig = env.GetSignal();
	AutoPtr<Object_sequence> pObj(new Object_sequence(env));
	Sequence &sequence = pObj->GetSequence();
	if (arg.Is_stream(0)) {
		if (!sequence.Read(env, arg.GetStream(0))) return Value::Nil;
	}
	return ReturnValue(env, arg, Value(pObj.release()));
}

// midi.port(id?:number) {block?}
Gura_DeclareFunction(port)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "id", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
	SetClassToConstruct(Gura_UserClass(port));
	AddHelp(
		Gura_Symbol(en),
		"It opens a MIDI port and returns a handle to it.\n");
}

Gura_ImplementFunction(port)
{
	Signal &sig = env.GetSignal();
	int id = arg.Is_number(0)? arg.GetInt(0) : 0;
	AutoPtr<Object_port> pObj(new Object_port(env));
	if (!pObj->GetPort()->Open(id)) {
		sig.SetError(ERR_IOError, "can't open MIDI port #%d", id);
		return Value::Nil;
	}
	return ReturnValue(env, arg, Value(pObj.release()));
}

// midi.controller(symbol:symbol) {block?}
Gura_DeclareFunction(controller)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "symbol", VTYPE_symbol);
	DeclareBlock(OCCUR_ZeroOrOnce);
	SetClassToConstruct(Gura_UserClass(controller));
	AddHelp(
		Gura_Symbol(en),
		"It creates a MIDI controller instance.\n");
}

Gura_ImplementFunction(controller)
{
	Signal &sig = env.GetSignal();
	int controller = ControllerIdBySymbol(arg.GetSymbol(0));
	if (controller < 0) {
		sig.SetError(ERR_ValueError, "invalid symbol for midi controller");
		return Value::Nil;
	}
	AutoPtr<Object_controller> pObj(new Object_controller(env, controller));
	return ReturnValue(env, arg, Value(pObj.release()));
}

// midi.program(symbol:symbol) {block?}
Gura_DeclareFunction(program)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "symbol", VTYPE_symbol);
	DeclareBlock(OCCUR_ZeroOrOnce);
	SetClassToConstruct(Gura_UserClass(program));
	AddHelp(
		Gura_Symbol(en),
		"It creates a MIDI program instance.\n");
}

Gura_ImplementFunction(program)
{
	Signal &sig = env.GetSignal();
	int program = ProgramIdBySymbol(arg.GetSymbol(0));
	if (program < 0) {
		sig.SetError(ERR_ValueError, "invalid symbol for midi program");
		return Value::Nil;
	}
	AutoPtr<Object_program> pObj(new Object_program(env, program));
	return ReturnValue(env, arg, Value(pObj.release()));
}

// midi.soundfont(stream:stream) {block?}
Gura_DeclareFunction(soundfont)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "stream", VTYPE_stream);
	DeclareBlock(OCCUR_ZeroOrOnce);
	SetClassToConstruct(Gura_UserClass(soundfont));
	AddHelp(
		Gura_Symbol(en),
		"It creates an instance to access data in SoundFont file.\n");
}

Gura_ImplementFunction(soundfont)
{
	Signal &sig = env.GetSignal();
	AutoPtr<Object_soundfont> pObj(new Object_soundfont(env, arg.GetStream(0).Reference()));
	if (!pObj->GetSoundFont().ReadChunks(env, sig)) return Value::Nil;
	return ReturnValue(env, arg, Value(pObj.release()));
}

// midi.test(stream:stream)
Gura_DeclareFunction(test)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "stream", VTYPE_stream);
}

Gura_ImplementFunction(test)
{
	Signal &sig = env.GetSignal();
	SoundFont sf(arg.GetStream(0).Reference());
	::printf("check\n");
	sf.ReadChunks(env, sig);
	sf.Print();
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
	// symbol realization
	Gura_RealizeUserSymbol(type);
	Gura_RealizeUserSymbol(midi);
	Gura_RealizeUserSymbol(sysex);
	Gura_RealizeUserSymbol(meta);
	Gura_RealizeUserSymbol(timestamp);
	Gura_RealizeUserSymbol(status);
	Gura_RealizeUserSymbol(id);
	Gura_RealizeUserSymbol(name);
	Gura_RealizeUserSymbol(dispname);
	Gura_RealizeUserSymbol(symbol);
	Gura_RealizeUserSymbol(args);
	Gura_RealizeUserSymbol(format);
	Gura_RealizeUserSymbol(division);
	Gura_RealizeUserSymbol(tracks);
	Gura_RealizeUserSymbol(events);
	Gura_RealizeUserSymbol(channel);
	Gura_RealizeUserSymbol(note);
	Gura_RealizeUserSymbol(velocity);
	Gura_RealizeUserSymbol(value);
	Gura_RealizeUserSymbol(controller);
	Gura_RealizeUserSymbol(program);
	Gura_RealizeUserSymbol(pressure);
	Gura_RealizeUserSymbol(binary);
	Gura_RealizeUserSymbol(number);
	Gura_RealizeUserSymbol(text);
	Gura_RealizeUserSymbol(mpqn);
	Gura_RealizeUserSymbol(hour);
	Gura_RealizeUserSymbol(minute);
	Gura_RealizeUserSymbol(second);
	Gura_RealizeUserSymbol(frame);
	Gura_RealizeUserSymbol(subFrame);
	Gura_RealizeUserSymbol(numerator);
	Gura_RealizeUserSymbol(denominator);
	Gura_RealizeUserSymbol(metronome);
	Gura_RealizeUserSymbol(cnt32nd);
	Gura_RealizeUserSymbol(key);
	Gura_RealizeUserSymbol(scale);
	Gura_RealizeUserSymbol(note_off);
	Gura_RealizeUserSymbol(note_on);
	Gura_RealizeUserSymbol(poly_pressure);
	Gura_RealizeUserSymbol(control_change);
	Gura_RealizeUserSymbol(program_change);
	Gura_RealizeUserSymbol(channel_pressure);
	Gura_RealizeUserSymbol(pitch_bend);
	Gura_RealizeUserSymbol(sys_ex_event);
	Gura_RealizeUserSymbol(unknown);
	Gura_RealizeUserSymbol(sequence_number);
	Gura_RealizeUserSymbol(text_event);
	Gura_RealizeUserSymbol(copyright_notice);
	Gura_RealizeUserSymbol(sequence_or_track_name);
	Gura_RealizeUserSymbol(instrument_name);
	Gura_RealizeUserSymbol(lyric_text);
	Gura_RealizeUserSymbol(marker_text);
	Gura_RealizeUserSymbol(cue_point);
	Gura_RealizeUserSymbol(midi_channel_prefix_assignment);
	Gura_RealizeUserSymbol(end_of_track);
	Gura_RealizeUserSymbol(tempo_setting);
	Gura_RealizeUserSymbol(smpte_offset);
	Gura_RealizeUserSymbol(time_signature);
	Gura_RealizeUserSymbol(key_signature);
	Gura_RealizeUserSymbol(sequencer_specific_event);
	Gura_RealizeUserSymbol(background);
	Gura_RealizeUserSymbol(player);
	Gura_RealizeUserSymbol(stream);
	Gura_RealizeUserSymbol(speed);
	Gura_RealizeUserSymbol(count);
	Gura_RealizeUserSymbol(repeat);
	Gura_RealizeUserSymbol(progress);
	Gura_RealizeUserSymbol(audio);
	// class realization
	Gura_RealizeUserClass(event, env.LookupClass(VTYPE_object));
	Gura_RealizeUserClass(track, env.LookupClass(VTYPE_object));
	Gura_RealizeUserClass(sequence, env.LookupClass(VTYPE_object));
	Gura_RealizeUserClass(portinfo, env.LookupClass(VTYPE_object));
	Gura_RealizeUserClass(port, env.LookupClass(VTYPE_object));
	Gura_RealizeUserClass(player, env.LookupClass(VTYPE_object));
	Gura_RealizeUserClass(controller, env.LookupClass(VTYPE_object));
	Gura_RealizeUserClass(program, env.LookupClass(VTYPE_object));
	Gura_RealizeUserClass(soundfont, env.LookupClass(VTYPE_object));
	Gura_RealizeUserClass(synthesizer, env.LookupClass(VTYPE_object));
	// class preparation
	Gura_PrepareUserClass(event);
	Gura_PrepareUserClass(track);
	Gura_PrepareUserClass(sequence);
	Gura_PrepareUserClass(portinfo);
	Gura_PrepareUserClass(port);
	Gura_PrepareUserClass(player);
	Gura_PrepareUserClass(controller);
	Gura_PrepareUserClass(program);
	Gura_PrepareUserClass(soundfont);
	Gura_PrepareUserClass(synthesizer);
	// value assignment
	do {
		Value value;
		Object_list *pObjList = value.InitAsList(env);
		pObjList->Reserve(ArraySizeOf(g_controllerInfos));
		Class *pClass = Gura_UserClass(controller);
		for (size_t i = 0; i < ArraySizeOf(g_controllerInfos); i++) {
			UChar controller = static_cast<UChar>(i);
			ControllerInfo &controllerInfo = g_controllerInfos[i];
			if (controllerInfo.name == nullptr) continue;
			controllerInfo.pSymbol = Symbol::Add(controllerInfo.name);
			Value value(new Object_controller(env, controller));
			pObjList->Add(value);
			pClass->AssignValue(controllerInfo.pSymbol, value, EXTRA_Public);
		}
		Gura_AssignValue(controllers, value);
	} while (0);
	do {
		Value value;
		Object_list *pObjList = value.InitAsList(env);
		pObjList->Reserve(ArraySizeOf(g_programInfos));
		Class *pClass = Gura_UserClass(program);
		for (size_t i = 0; i < ArraySizeOf(g_programInfos); i++) {
			UChar program = static_cast<UChar>(i);
			ProgramInfo &programInfo = g_programInfos[i];
			programInfo.pSymbol = Symbol::Add(programInfo.name);
			Value value(new Object_program(env, program));
			pObjList->Add(value);
			pClass->AssignValue(programInfo.pSymbol, value, EXTRA_Public);
		}
		Gura_AssignValue(programs, value);
	} while (0);
	// assignment of class reference or instance constructor
	Gura_AssignValue(event,			Value(Gura_UserClass(event)->Reference()));
	Gura_AssignValue(track,			Value(Gura_UserClass(track)->Reference()));
	Gura_AssignFunction(sequence);
	Gura_AssignValue(portinfo,		Value(Gura_UserClass(portinfo)->Reference()));
	Gura_AssignFunction(port);
	Gura_AssignValue(player,		Value(Gura_UserClass(player)->Reference()));
	Gura_AssignFunction(controller);
	Gura_AssignFunction(program);
	Gura_AssignFunction(soundfont);
	Gura_AssignValue(synthesizer,	Value(Gura_UserClass(synthesizer)->Reference()));
	Gura_AssignFunction(test);
	return true;
}

Gura_ModuleTerminate()
{
}

//-----------------------------------------------------------------------------
// utility functions
//-----------------------------------------------------------------------------
int ControllerIdBySymbol(const Symbol *pSymbol)
{
	for (int i = 0; i < ArraySizeOf(g_controllerInfos); i++) {
		if (g_controllerInfos[i].pSymbol != nullptr &&
					g_controllerInfos[i].pSymbol->IsIdentical(pSymbol)) {
			return i;
		}
	}
	return -1;
}

int ControllerIdByName(const char *name)
{
	for (int i = 0; i < ArraySizeOf(g_controllerInfos); i++) {
		if (::strcasecmp(g_controllerInfos[i].name, name) == 0) {
			return i;
		}
	}
	return -1;
}

const ControllerInfo *ControllerInfoById(int controller)
{
	if (0 <= controller && controller < ArraySizeOf(g_controllerInfos)) {
		return &g_controllerInfos[controller];
	}
	return nullptr;
}

int ProgramIdBySymbol(const Symbol *pSymbol)
{
	for (int i = 0; i < ArraySizeOf(g_programInfos); i++) {
		if (g_programInfos[i].pSymbol != nullptr &&
					g_programInfos[i].pSymbol->IsIdentical(pSymbol)) {
			return i;
		}
	}
	return -1;
}

int ProgramIdByName(const char *name)
{
	for (int i = 0; i < ArraySizeOf(g_programInfos); i++) {
		if (::strcasecmp(g_programInfos[i].name, name) == 0) {
			return i;
		}
	}
	return -1;
}

const ProgramInfo *ProgramInfoById(int program)
{
	if (0 <= program && program < ArraySizeOf(g_programInfos)) {
		return &g_programInfos[program];
	}
	return nullptr;
}

Value ActivatePlayer(Environment &env, Signal &sig, Argument &arg,
					Sequence &sequence, Port *pPort, double speed, int cntRepeat)
{
	AutoPtr<Player> pPlayer(sequence.GeneratePlayer(sig, pPort, speed, cntRepeat));
	if (sig.IsSignalled()) return Value::Nil;
	if (arg.IsSet(Gura_UserSymbol(background))) {
		Value value(new Object_player(env, Player::Reference(pPlayer.get())));
		pPlayer.release()->PlayBackground();
		return value;
	}
	if (arg.IsSet(Gura_UserSymbol(player))) {
		Value value(new Object_player(env, Player::Reference(pPlayer.get())));
		return value;
	}
	pPlayer->Play();
	return Value::Nil;
}

Gura_EndModuleBody(midi, midi)

Gura_RegisterModule(midi)
