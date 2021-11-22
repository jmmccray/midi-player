#include "wav.hpp"
// TODO
#include <iostream>
#include <fstream>
#include <math.h>

/** \fn Write a signal to a WAV file. Returns true on success, false on failure.
* The signal should be quantized into a 16 bit integer using rounding to nearest.
* \param sound the signal to write.
* \param filename the filename to write to.
*/
bool write_wav(Signal & sound, const std::string &filename)
{
	sound.normalize();
	ofstream outstream;
	size_t NumSamples = sound.size();
	//Field 1
	const int8_t ChunkID[4] = { 'R','I','F','F' };
	//Field 3
	const int8_t Format[4] = { 'W','A','V', 'E' };
	//Field 4
	char Subchunk1ID[4] = { 'f','m','t', ' ' };
	//Field 5
	int32_t SubChunk1Size = 16;
	//Field 6
	int16_t AudioFormat = 1;
	//Field 7
	int16_t NumChannels = 1;
	//Field 8
	int32_t SampleRate = 44100;
	//Field 11
	int16_t BitsPerSample = 16;
	//Field 9
	int32_t ByteRate = SampleRate * NumChannels * BitsPerSample / 8;
	//Field 10
	int16_t BlockAlign = NumChannels * BitsPerSample / 8;
	//Field 12
	const int8_t SubChunk2ID[4] = { 'd', 'a', 't', 'a' };
	//Field 13
	int32_t SubChunk2Size = (int32_t)NumSamples * 2;
	//Field 2
	int32_t ChunkSize = 4 + (8 + SubChunk1Size) + (8 + SubChunk2Size);


	//Writes 14 fields
	outstream.open(filename, std::ios::binary); //should already open file
	outstream.write(reinterpret_cast<const fstream::char_type*>(&ChunkID), sizeof ChunkID);
	outstream.write(reinterpret_cast<fstream::char_type*>(&ChunkSize), sizeof ChunkSize);
	outstream.write(reinterpret_cast<const fstream::char_type*>(&Format), sizeof Format);
	outstream.write(reinterpret_cast<fstream::char_type*>(&Subchunk1ID), sizeof Subchunk1ID);
	outstream.write(reinterpret_cast<fstream::char_type*>(&SubChunk1Size), sizeof SubChunk1Size);
	outstream.write(reinterpret_cast<fstream::char_type*>(&AudioFormat), sizeof AudioFormat);
	outstream.write(reinterpret_cast<fstream::char_type*>(&NumChannels), sizeof NumChannels);
	outstream.write(reinterpret_cast<fstream::char_type*>(&SampleRate), sizeof SampleRate);
	outstream.write(reinterpret_cast<fstream::char_type*>(&ByteRate), sizeof ByteRate);
	outstream.write(reinterpret_cast<fstream::char_type*>(&BlockAlign), sizeof BlockAlign);
	outstream.write(reinterpret_cast<fstream::char_type*>(&BitsPerSample), sizeof BitsPerSample);
	outstream.write(reinterpret_cast<const fstream::char_type*>(&SubChunk2ID), sizeof SubChunk2ID);
	outstream.write(reinterpret_cast<fstream::char_type*>(&SubChunk2Size), sizeof SubChunk2Size);
	
	int16_t data;
	cout << "Size of Sample: " << sound.size() << endl;
	for (size_t i = 0; i < sound.size(); i++)
	{
		data = sound[i]; //data removes decimal #'s. Ex. xxxx.xx --> xxxx
		outstream.write(reinterpret_cast<fstream::char_type*> (&data), sizeof(data));
		//cout << "Write Normalized: " << data << endl;
		//cout << "Regular: " << non_norm_signal[i] << endl;
		//cout << "Write (S): " << sound[i] << endl;
	}

	return true;
}