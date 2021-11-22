//TRACK.CPP
#include "track.hpp"
#include <list>
#include <iostream>
#include <vector>
// TODO
/** Construct Track with ticks per beat in microsec.
* default is 120 BPM = 0.5 sec per beat = 500000 microsec per beat
*/
Track::Track(intmax_t ticks_per_beat)
{
	//midi_tick_time_ = ticks_per_beat;
	ticks_per_beat_ = ticks_per_beat;
}

/** Get ticks per beat in microsec. */
//return value M (MIDI clock ticks per beat)
intmax_t Track::getTicksPerBeat() const
{
	return ticks_per_beat_;
	//return midi_tick_time_;
}


// Get iterator to first event.
//Track::ConstIteratorType begin() const
 Track::ConstIteratorType Track::begin() const
{
	//ConstIteratorType interator_prev;
	//ConstIteratorType iterator_prev = track_list_.begin();
	return track_list_.begin();
	//return iterator_prev;
}


// Get iterator to end of event sequence.
Track::ConstIteratorType Track::end() const
{
	return track_list_.end();
}

/** Add an EndEvent to the track sequence.
* \param tick_time, the MIDI tick time of the event.
*/

void Track::addEndEvent(intmax_t tick_time)
{
	EndTrackEvent end_event;
	MIDIEvent midi_end_event(end_event, tick_time);
	midi_tick_time_ = tick_time;
	track_list_.push_back(midi_end_event);
}

/** Add a TempoEvent to the track sequence.
* \param tempo the new tempo of the track after this tick
* \param tick_time the MIDI tick time of the event.
*/
void Track::addTempoEvent(intmax_t tempo, intmax_t tick_time)
{
	TempoEvent tempo_event(tempo);
	MIDIEvent midi_tempo_event(tempo_event, tick_time);
	midi_tick_time_ = tick_time; //is this correct?
	track_list_.push_back(midi_tempo_event);
}

/** Add a NoteEvent to the track sequence.
* \param code the event code (8 = On, 9 = Off unless data2 = 0) //Should be 8 = off, 9 = on
* \param data1 the first data byte (holding the note number)
* \param data2 the second data byte (holding the velocity)
* \param tick_time, the MIDI tick time of the event.
*/
void Track::addNoteEvent(uint8_t code, uint8_t data1, uint8_t data2, intmax_t tick_time)
{
	bool temp = false;
	if (code == 9) //ON = true
	{
		temp = true;
	}
	NoteEvent note_event(temp, data1, data2);
	MIDIEvent midi_note_event(note_event, tick_time);
	midi_tick_time_ = tick_time; //is this correct?
	track_list_.push_back(midi_note_event);
}

bool Track::getTrackListEvents()
{
	ConstIteratorType iterator_prev;
	vector<MIDIEvent> list;
	int index = 0;
	bool test = true;
	for (ConstIteratorType iterator_it = track_list_.begin(); iterator_it != track_list_.end(); ++iterator_it)
	{
		cout << "Located of the memory " << &(*iterator_it) << endl;
		list.push_back(*iterator_it);

		if (list.at(index).isTempoEvent())
		{
			cout << "Index: " << index << " Is a Tempo Event" << endl;
		}
		else if (list.at(index).isEndTrackEvent())
		{
			cout << "Index: " << index << " Is a EndTrackEvent" << endl;
		}
		else if (list.at(index).isNoteEvent())
		{
			cout << "Index: " << index << " Is a NoteEvent " << endl;
		}
		else
		{
			cout << "Error Error Error" << endl;
			test = false;
		}

		index++;
		iterator_prev = iterator_it;
	}
	return test;
}
