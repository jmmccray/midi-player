#ifndef TRACK_HPP
#define TRACK_HPP


#include "event.hpp"
#include <iterator>
#include <list>

using namespace std;

/** A Track represents a sequence of Events ordered by thier MIDI tock time.
* Events can be added to the Track based on type of event. Events can be accessed
* using a constant iterator in order, first to last.
*/
class Track {

public:

	/** Typdef for iterator type. This object should support the operators
	* ++, *, and -> (i.e. it is a forward iterator).  */
	// TODO typedef ????? ConstIteratorType; Instructor said in Piazza iterator can be bidirectional
	typedef list<MIDIEvent>::const_iterator ConstIteratorType; //Const interator makes container of Events Read only


public:

	/** Construct Track with ticks per beat in microsec.
	* default is 120 BPM = 0.5 sec per beat = 500000 microsec per beat
	*/
	Track(intmax_t ticks_per_beat = 500000);

	/** Get ticks per beat in microsec. */
	intmax_t getTicksPerBeat() const;

	/** Get iterator to first event. */
	ConstIteratorType begin() const;

	/** Get iterator to end of event sequence. */
	ConstIteratorType end() const;

	/** Add an EndEvent to the track sequence.
	* \param tick_time, the MIDI tick time of the event.
	*/
	void addEndEvent(intmax_t tick_time);

	/** Add a TempoEvent to the track sequence.
	* \param tempo the new tempo of the track after this tick
	* \param tick_time the MIDI tick time of the event.
	*/
	void addTempoEvent(intmax_t tempo, intmax_t tick_time);

	/** Add a NoteEvent to the track sequence.
	* \param code the event code (8 = On, 9 = Off unless data2 = 0) !!!Should be 8 = Off, 9 = On!!
	* \param data1 the first data byte (holding the note number)
	* \param data2 the second data byte (holding the velocity)
	* \param tick_time, the MIDI tick time of the event.
	*/
	void addNoteEvent(uint8_t code, uint8_t data1, uint8_t data2, intmax_t tick_time);

	//Method I created. getTrackSize(), returns size of the Track list
	bool getTrackListEvents();

private:
	// TODO
	intmax_t midi_tick_time_;
	intmax_t ticks_per_beat_;
	list<MIDIEvent> track_list_;

};

/** A list of tracks. */
typedef list<Track> TrackListType;

#endif