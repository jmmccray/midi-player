//INSTRUMENT.HPP
/** \file The DefaultInstrument Module
*/
#ifndef INSTRUMENT_HPP
#define INSTRUMENT_HPP

#include "event.hpp"
#include "track.hpp"
#include <vector>

/** The default instrument. A simple fixed length note instrument using a
* a sinusoid weighted by an envelope function.
*/
class DefaultInstrument {
public:

	/** No default constructor. A DefaultInstrument must have an associated
	* track.
	*/
	DefaultInstrument() = delete;

	/** Cannot be copied.
	*/
	DefaultInstrument(const DefaultInstrument &) = delete;

	/** Cannot be assigned.
	*/
	DefaultInstrument & operator=(const DefaultInstrument &) = delete;

	/** Construct a Default Instrument using the specified track.
	* \param track the track to read events from.
	*/
	DefaultInstrument(const Track & track);

	/** Returns true of the DefaultInstrument has stopped processing events.
	* This can occu e.g. if all events have been consumed or a EndTrackEvent
	* has been processed.
	*/
	bool halted();

	/** Return the sample after the (real) time increment. Samples the
	* instrument based on its state after processing all events prior
	* to this time.
	* \param deltaT the time increment in seconds.
	*/
	double sample(double deltaT);
	

private:
	// TODO
	//State
	//enum State { on, off } state;
	// contianer of active notes
	Track track_list_;
	//vector<MIDIEvent> track_eventsOn_list_;

	// for each active note: need a it's note number, time turned on, velocity
	int note_num_ = 0;
	int start_time_ = 0;
	int velocity_ = 0;
	double real_time_ = 0.0;

	bool halt_ = false;
	double envelope(double elapse_time); //Passes
	double getNoteFrequency(int8_t note_num);
	double convertNoteMIDITime(intmax_t tempo, double midi_time, double sec_beat);
	list<MIDIEvent>::const_iterator prev_ = track_list_.begin();
	void testFreq();
	intmax_t tempTE_ = 500000; //used to be intmax

	
};


#endif