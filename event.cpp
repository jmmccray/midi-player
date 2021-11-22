//EVENT.CPP
#include "event.hpp"
// TODO

/** Construct a TempoEvent. The default tempo is 0.5 bpm
*/
TempoEvent::TempoEvent(intmax_t t)
{
	tempo = t;
}

/** Get the tempo in micro-sec per beat.
*/
intmax_t TempoEvent::getTempo() const
{
	return tempo; //private variable tempo
}


//END TRACK EVENT END TRACK EVENT
/** An EndTrackEvent. This event indicates that the track has ended and the
* synthesizer should halt sampling the instrument.
*/
//class EndTrackEvent {};

/** A NoteEvent. This event indicates that a note should be activated
* or deactivated.
*/
//NOTE EVENTS NOTE EVENTS
/** You cannot default construct a Note Event. */
//NoteEvent() = delete; //Double check this function definition
/*NoteEvent::NoteEvent()
{
delete this;
}*/

/** Construct a note event.
* \param on true if the note should be turned on, false if it should be
*           turned off.
* \param notenum the MIDI note number (0-127) to be modified.
* \param notevelocity the velocity of the note change.
*/
NoteEvent::NoteEvent(bool on, int8_t notenum, int8_t notevelocity)
{
	on_ = on;
	notenum_ = notenum;
	notevelocity_ = notevelocity;
}

/** Get note change type. true if ON, false if OFF.
*/
bool NoteEvent::getNoteOn()
{
	return on_;
}

/** Get MIDI note number to change. Takes on values in [0,127]
*/
int8_t NoteEvent::getNoteNumber() const
{
	return notenum_;
	//Need to throw error if notenum < 0, notenum > 127
}

/** Get the velocity of the note change.
*/
int8_t NoteEvent::getNoteVelocity() const
{
	return notevelocity_;
}



//MIDI EVENT, MIDI EVENT
/** A MIDI Event holds one of a TempoEvent, EndTrackEvent, or NoteEvent and an
* associated MIDI tick time in units of ticks-per-beat.
*/
//Construct a MIDI event holding a TempEvent at ticktime.
MIDIEvent::MIDIEvent(TempoEvent e, intmax_t ticktime)
{
	event.tempoEvent_ = e;
	midi_ticktime_ = ticktime;
	eventType = tempo;
}

//Construct a MIDI event holding an EndTrackEvent at ticktime.
MIDIEvent::MIDIEvent(EndTrackEvent e, intmax_t ticktime)
{
	event.endTrack_ = e;
	midi_ticktime_ = ticktime;
	eventType = endTrack;
}

// Construct a MIDI event holding a NoteEvent at ticktime.
MIDIEvent::MIDIEvent(NoteEvent e, intmax_t ticktime)
{
	event.noteEvent_ = e;
	midi_ticktime_ = ticktime;
	eventType = note;
}

/** True if event is a TempoEvent, else false.
*/
bool MIDIEvent::isTempoEvent() const
{
	if (eventType == tempo)
		return true;
	else
		return false;
}

/** True if event is an EndTrackEvent, else false.
*/
bool MIDIEvent::isEndTrackEvent() const
{
	if (eventType == endTrack)
		return true;
	else
		return false;
}

/** True if event is a NoteEvent, else false.
*/
bool MIDIEvent::isNoteEvent() const
{
	if (eventType == note)
		return true;
	else
		return false;
}

/** Get the MIDI tick time of this event (ticks per beat)
*/
intmax_t MIDIEvent::getTickTime() const
{
	return midi_ticktime_;
}

/** Cast the MIDI event as a TempoEvent. Only valid if
* isTempoEvent() returns true.
*/
TempoEvent MIDIEvent::asTempoEvent() const
{
	//Need to use union for this
	TempoEvent tempo_event;
	/*if (this->isTempoEvent())
	{
		return tempo_event;
	}*/
	return event.tempoEvent_;
}

/** Cast the MIDI event as a NoteEvent. Only valid if
* isNoteEvent() returns true.
*/
NoteEvent MIDIEvent::asNoteEvent() const
{
	/*NoteEvent note_event(true, 0, 0);
	//NoteEvent note_event1(event.noteEvent_.getNoteOn(), event.noteEvent_.getNoteNumber(), event.noteEvent_.getNoteVelocity());
	if (this->isNoteEvent())
	{
		return note_event;
	}*/
	return event.noteEvent_;
}
