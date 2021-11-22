/** \file Synthesizer Module
 */
#ifndef SYNTHESIZER_HPP
#define SYNTHESIZER_HPP

#include "track.hpp"
#include "signal.hpp"
#include "shared_double_buffer.hpp"
#include "message_queue.hpp"
#include "instrument.hpp"
#include "midi.hpp"

using namespace std;

/*\fn Synthesize a Track into a Signal.
 *Returned signal is empty on failure.
 *\param track the track to synthesize.
 */

//CAN SLEEP
class Synthesizer
{
	public:
		Synthesizer();
		~Synthesizer();
		void synthesize(MessageQueue* queue, SharedDoubleBuffer* buffer); //Suggested, create  separate method to create
		void getMIDIFile(string MIDIFilePath);

	private:
		Track track_;
		TrackListType listOfTracks_;
		Signal signal_;
		DefaultInstrument * instrument_;
		enum MessageID {Default, Play, Pause, Stop, Mute, Kill} messageID_;
		//auto rates_;
		//int messageID_;
		int IDNumber_;

		MessageQueue* messageQueue_;
		SharedDoubleBuffer* doubleBuffer_; //Sets Sample Rate
		//DefaultInstrument* instrument_;

		//Implement private variables from instrument
		double deltaTime_;
		double currentTime_;
};
#endif
