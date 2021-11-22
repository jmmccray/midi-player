#include "instrument.hpp"
#include <iostream>
#include <string>
#include <math.h>
#define M_PI       3.14159265358979323846   // PI

// TODO
/** Construct a Default Instrument using the specified track.
* \param track the track to read events from.
*/
DefaultInstrument::DefaultInstrument(const Track & track)
{
	track_list_ = track;
}


/** Returns true of the DefaultInstrument has stopped processing events.
* This can occu e.g. if all events have been consumed or a EndTrackEvent
* has been processed.
*/
bool DefaultInstrument::halted()
{
	return halt_;
}

double DefaultInstrument::envelope(double elapse_time)//Passes
{
	double E = 0.0; //Output of envelope function
	const double S = 0.8;
	double t0 = 0.0, t1 = 0.0625, t2 = 0.1125, t3 = 0.2, t4 = 0.25;

	if (elapse_time >= t0 && elapse_time <= t1)
	{
		E = (1.0 / t1) * elapse_time;
	}
	else if (elapse_time > t1 && elapse_time <= t2)
	{
		E = 1.0 - (elapse_time - t1);
	}
	else if (elapse_time > t2 && elapse_time <= t3)
	{
		E = S;
	}
	else if (elapse_time > t3 && elapse_time <= t4)
	{
		E = S - (S / (t4 - t3))*(elapse_time - t3);
	}
	else
	{
		E = 0.0;
	}
	return E;
}

double DefaultInstrument::getNoteFrequency(int8_t note_num)
{
	double note_f = 0.0;
	note_f = 440.0 * pow(2.0, (note_num - 69.0) / 12.0);
	switch (note_num)
	{
	case 5: note_f = 10.9259375; break;
	case 17: note_f =  21.851875; break;
	case 29: note_f =  43.70375; break;
	case 41: note_f =  87.4075; break;
	case 53: note_f =  174.815; break;
	case 65: note_f = 349.63; break;
	case 77: note_f =  699.26; break;
	case 89: note_f = 1398.52; break;
	case 101: note_f = 2797.04; break;
	case 113: note_f = 5594.08; break;
	case 115: note_f = 11188.16; break;
	}
	/*switch (note_num)
	{
	case 0:	note_f = 8.1759375; break;		case 1: note_f = 8.661875; break;
	case 2: note_f = 9.176875; break;		case 3: note_f = 9.7228125; break;
	case 4: note_f = 10.30093765; break;	case 5: note_f = 10.9134375; break;
	case 6: note_f = 11.5623125; break;		case 7: note_f = 12.25; break;
	case 8: note_f = 12.97828125; break;	case 9: note_f = 13.75; break;
	case 10: note_f = 14.5676725; break;	case 11: note_f = 15.43375; break;
	case 12: note_f = 16.351875; break;		case 13: note_f = 17.32375; break;
	case 14: note_f = 18.35375;	break;		case 15: note_f = 19.445625; break;
	case 16: note_f = 20.601875; break;		case 17: note_f = 21.826875; break;
	case 18: note_f = 23.124625; break;		case 19: note_f = 24.5; break;
	case 20: note_f = 25.9565625; break;	case 21: note_f = 27.5; break;
	case 22: note_f = 29.13525;	break;		case 23: note_f = 30.8675; break;
	case 24: note_f = 32.70375;	break;		case 25: note_f = 34.6475; break;
	case 26: note_f = 36.7075; break;		case 27: note_f = 38.89125; break;
	case 28: note_f = 41.20375; break;		case 29: note_f = 43.65375; break;
	case 30: note_f = 46.24925;	break;		case 31: note_f = 49.0; break;
	case 32: note_f = 51.813125; break;		case 33: note_f = 55.0; break;
	case 34: note_f = 58.2705; break;		case 35: note_f = 61.735; break;
	case 36: note_f = 65.4075; break;		case 37: note_f = 69.295; break;
	case 38: note_f = 73.415; break;		case 39: note_f = 77.7825; break;
	case 40: note_f = 82.4075; break;		case 41: note_f = 87.3075; break;
	case 42: note_f = 92.4985; break;		case 43: note_f = 98.0; break;
	case 44: note_f = 103.82625; break;		case 45: note_f = 110.0; break;
	case 46: note_f = 116.541; break;		case 48: note_f = 130.815; break;
	case 47: note_f = 123.47; break;		case 49: note_f = 138.59; break;
	case 50: note_f = 146.83; break;		case 51: note_f = 155.565; break;
	case 52: note_f = 164.815; break;		case 53: note_f = 174.615; break;
	case 54: note_f = 184.997; break;		case 55: note_f = 196; break;
	case 56: note_f = 207.6525;	break;		case 57: note_f = 220.0; break;
	case 58: note_f = 233.082;	break;		case 59: note_f = 246.94; break;
	case 60: note_f = 261.63; break;		case 61: note_f = 277.18; break; //C - C#
	case 62: note_f = 293.66; break;		case 63: note_f = 311.13; break; //D - D#
	case 64: note_f = 329.63; break;		case 65: note_f = 349.23; break; //E
	case 66: note_f = 369.994; break;		case 67: note_f = 392.0; break;
	case 68: note_f = 415.305; break;		case 69: note_f = 440.0; break;
	case 70: note_f = 466.164; break;		case 71: note_f = 493.88; break;
	case 72: note_f = 523.26; break;		case 73: note_f = 554.36; break;
	case 74: note_f = 587.32; break;		case 75: note_f = 622.26; break;
	case 76: note_f = 659.26; break;		case 77: note_f = 698.46; break;
	case 78: note_f = 739.988; break;		case 79: note_f = 784.0; break;
	case 80: note_f = 830.61; break;		case 81: note_f = 880.0; break;
	case 82: note_f = 932.328; break;		case 83: note_f = 987.76; break;
	case 84: note_f = 1046.52; break;		case 85: note_f = 1108.72; break;
	case 86: note_f = 1174.64; break;		case 87: note_f = 1244.52; break;
	case 88: note_f = 1318.52; break;		case 89: note_f = 1396.92; break;
	case 90: note_f = 1479.976; break;		case 91: note_f = 1568.0; break;
	case 92: note_f = 1661.22; break;		case 93: note_f = 1760.0; break;
	case 94: note_f = 1864.656; break;		case 95: note_f = 1975.52; break;
	case 96: note_f = 2093.04; break;		case 97: note_f = 2217.44; break;
	case 98: note_f = 2349.28; break;		case 99: note_f = 2489.04; break;
	case 100: note_f = 2637.04;	break;		case 101: note_f = 2793.84; break;
	case 102: note_f = 2959.952; break;		case 103: note_f = 3136.0; break;
	case 104: note_f = 3322.44;	break;		case 105: note_f = 3520.0; break;
	case 106: note_f = 3729.312; break;		case 107: note_f = 3951.04; break;
	case 108: note_f = 4186.08;	break;		case 109: note_f = 4434.88; break;
	case 110: note_f = 4698.56;	break;		case 111: note_f = 4978.08; break;
	case 112: note_f = 5274.08;	break;		case 113: note_f = 5587.68; break;
	case 114: note_f = 5919.904; break;		case 115: note_f = 6272.0; break;
	case 116: note_f = 6644.88;	break;		case 117: note_f = 7040.0; break;
	case 118: note_f = 7458.624; break;		case 119: note_f = 7902.08; break;
	case 120: note_f = 8772.16;	break;		case 121: note_f = 8869.76; break;
	case 122: note_f = 9397.12;	break;		case 123: note_f = 9956.16; break;
	case 124: note_f = 10548.16; break;		case 125: note_f = 11175.36; break;
	case 126: note_f = 11839.808; break;	case 127: note_f = 12544.0; break;
		default: break;
	}*/
	return note_f;
}

double DefaultInstrument::convertNoteMIDITime(intmax_t tempo, double tick_time, double tick_beat)
{
	
	double real_time =	((double) tempo*tick_time) / (tick_beat * 1000000.0);
	//double real_time = (tempo*tick_time) / (480.0 * 1000000.0);
	return real_time;	
}


double DefaultInstrument::sample(double deltaT) //deltatT = 1/(sample-time) comes from Signal sample rate
{ 
	double real_time_ = deltaT;
	double E = 0.0; //Holds Envelope function
	double sample = 0.0; //The final sum
	double sum = 0.0; //Holds the sum of each ON note
	double note_freq = 0.0; //Holds frequency of note at index i
	double elapsed_time = 0.0; //Holds elapsed_time 
	double note_velocity = 0.0; //Holds note velocity at index i
	double sine = 0.0;
	vector<MIDIEvent> track_eventsOn_list_;
	//int M = 0; //MIDI clock ticket per beat (defined in MIDI file)

	//convert midi-time to real-time, then compare it to the current sample time. 
	//Travese list of Midi-Event 
	//cout << "TicksPerBeat: " << track_list_.getTicksPerBeat() << endl;
	list<MIDIEvent>::const_iterator prev;
	for (prev = track_list_.begin(); prev != track_list_.end(); ++prev)
	{
		//Checks if MIDIEvent is a Note AND if Note is on.
			//tempTE_ = prev->asTempoEvent.getTempo();
		if (prev->isEndTrackEvent() && convertNoteMIDITime(tempTE_, (*prev).getTickTime(), track_list_.getTicksPerBeat()) <= real_time_) //Need to add another condition, EndTrack must occure at real_time
		{
			halt_ = true;
			
		}
		else if (prev->isTempoEvent())
		{
			//updates private variable type TempoEvent
			tempTE_ = prev->asTempoEvent().getTempo();
		}
		else if ((*prev).isNoteEvent() && prev->asNoteEvent().getNoteOn() && convertNoteMIDITime(tempTE_, (*prev).getTickTime(), track_list_.getTicksPerBeat()) <= real_time_) //double check, fix tempo
		{
			track_eventsOn_list_.push_back(*prev); //MIDINoteEvents stored in vector
		}
	}

	



		//Sums all noteON events
		for (unsigned int i = 0; i < track_eventsOn_list_.size(); i++)
		{
				//cout << "Index: " << i << endl;
			elapsed_time = real_time_ - convertNoteMIDITime(tempTE_, (double) track_eventsOn_list_.at(i).getTickTime(), (double) track_list_.getTicksPerBeat());
				//cout << "Elapsed Time: " << elapsed_time << endl; //For debugging
			E = envelope(elapsed_time);
				//cout << "Envelope: " << E << endl;
			note_freq = getNoteFrequency(track_eventsOn_list_.at(i).asNoteEvent().getNoteNumber());
			//cout << "Note Frequency: " << note_freq << endl << endl;
			note_velocity = (double) track_eventsOn_list_.at(i).asNoteEvent().getNoteVelocity();
			//sum += 200.0*(note_velocity)*(E)*sin(2.0*M_PI*note_freq*elapsed_time);
			sine = sin(2.0*M_PI*note_freq*elapsed_time);
			sum += 200.0*(note_velocity)*(E)*sine;
		}


	sample = sum;
	return sample;
}

