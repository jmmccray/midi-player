//SIGNAL.CPP
#include "signal.hpp"
#include <iostream>
#include <math.h>
// TODO

/** Construct a Signal given a sampling rate is samples-per-second (Hz). The default rate is
* 44.1 kHz.
* \param sampleRate the sampling rate in Hz
*/
Signal::Signal(unsigned int sampleRate)
{
	sample_rate_ = sampleRate;
}

/** return the sampling rate in Hz.*/
unsigned int Signal::getSampleRate()
{
	return sample_rate_; //Units: Hz
}

/** Normalize the Signal to fit into a 16 bit integer
* when quantized.
*/
void Signal::normalize()
{

	
	 for (unsigned int i = 0; i < sample_list_.size(); i++)
	{
		//Scaling, do not need in project 2 (Milestone 1)
		if (sample_list_.at(i) > 32768.0)
			 sample_list_.at(i) = 32768.0;
		 else if (sample_list_.at(i) < -32768.0)
			 sample_list_.at(i) = -32768.0;
		normalized_list_.push_back((int16_t) round(sample_list_.at(i)));
	}

	 normalized_ = true;
	//For Debugging
	/* for (int i = 0; i < sample_list_.size(); i++)
	{
		cout << "Normalized Value: " << normalized_list_.at(i) << endl;
		cout << "Regular Value: " << sample_list_.at(i) << endl;
	}*/
}

/** Add a sample to the signal.
* \param value the double sample value to add.
*/
void Signal::push_back(double value)
{
	sample_list_.push_back(value);
}

/** Return the number of samples in the signal. */
std::size_t Signal::size()
{
	return sample_list_.size();
}

/** Return the sample at given index.
* \param index the index of the sample to return.
*/
double Signal::operator[] (std::size_t index)
{
	if (normalized_)
		return normalized_list_.at(index); //Remember, need to normalize
	else
		return sample_list_.at(index);
}