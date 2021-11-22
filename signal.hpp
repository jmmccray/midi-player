//SIGNAL HPP
#ifndef SIGNAL_HPP
#define SIGNAL_HPP

#include <cstdint>
#include <cstddef>
#include <vector>

using namespace std;


/** \A brief Signal holds equally spaced samples of type double.
*/
class Signal
{
public:

	/** Construct a Signal given a sampling rate is samples-per-second (Hz). The default rate is
	* 44.1 kHz.
	* \param sampleRate the sampling rate in Hz
	*/
	//Signal(unsigned int sampleRate = 80000);
	Signal(unsigned int sampleRate = 44100);

	/** return the sampling rate in Hz.*/
	unsigned int getSampleRate();

	/** Normalize the Signal to fit into a 16 bit integer
	* when quantized.
	*/
	void normalize();

	/** Add a sample to the signal.
	* \param value the double sample value to add.
	*/
	void push_back(double value);

	/** Return the number of samples in the signal. */
	std::size_t size();

	/** Return the sample at given index.
	* \param index the index of the sample to return.
	*/
	double operator[](std::size_t index);


private:
	// TODO
	unsigned int sample_rate_;
	vector<double> sample_list_;
	vector<int16_t> normalized_list_; //Need to change to regular int16_t
	bool normalized_ = false; //Holds whether sample has been normalized
};


#endif