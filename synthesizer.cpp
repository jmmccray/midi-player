#include "synthesizer.hpp"
#include <iostream>
#include <fstream>
#include <QAudioDeviceInfo>
#include <QAudioInput>
// TODO
Synthesizer::Synthesizer()
{	

}

Synthesizer::~Synthesizer()
{

}

void Synthesizer::getMIDIFile(string MIDIFilePath)
{
	//Got code from main.cpp Project 1
	//Sets listOfTracks_ to by later synthesize in Play State
	ifstream inputFilePath;
	inputFilePath.open(MIDIFilePath, ifstream::in);
	listOfTracks_ = readMIDIFromFile(MIDIFilePath);
	if (listOfTracks_.empty())
		cout << "List of Tracks is EMPTY" << endl;
	else
		instrument_ = new DefaultInstrument(*listOfTracks_.begin());
		//instrument_(*listOfTracks_.begin()));
		//cout << "List of Tracks is FULL" << endl;	
}

void Synthesizer::synthesize(MessageQueue* queue, SharedDoubleBuffer* buffer)
{
	messageQueue_ = queue;
	doubleBuffer_ = buffer;
	bool running = true;
	double sample = 0.0;
	QList<int> rates;
	int sampleRate;	
	int j = 0;
	int i = 0;

	QAudioDeviceInfo info(QAudioDeviceInfo::defaultOutputDevice());
	rates = info.supportedSampleRates();
	sampleRate = rates.at(0);
	for (int i = 1; i < rates.size(); ++i)
	{
		if (rates.at(i) < sampleRate)
			sampleRate = rates.at(i);
	}

	while (running == true)
	{
		if (!messageQueue_->empty())
		{
			messageQueue_->wait_and_pop(IDNumber_); //Sets IDNumber to message in queue
			//STATES
			switch (IDNumber_)
			{
				case Default:
				{
					cout << "Entered Default State" << endl;					
					break;
				}
				case Play:
				{
					cout << "Entered Play State...." << endl;
					//if ( instrument_->halted() == false && IDNumber_ != Pause && IDNumber_ != Stop)
						 while (instrument_->halted() == false)
						{
							sample = instrument_->sample((double) i / sampleRate); //original 8000
							//cout << "Sample Value: " << sample << endl;
							doubleBuffer_->writeToBuffer(sample);
							//messageQueue_->push(Play);
							//j++; 
							i++;
						}
						 i = 0;
							//messageQueue_->push(Play);
						
					break;
				}
				case Pause:
				{
					cout << "Entered Pause State" << endl;
					break;
				}
				case Stop:
				{
					doubleBuffer_->clearBuffers();
					messageQueue_->push(Default);
					cout << "Entered Stop State" << endl;
					break;
				}
				case Mute:
				{
					cout << "Entered Mute State" << endl;
					break;
				}
				default: break;
				case Kill:
				{
					cout << "Killing " << endl;
					running = false;
					break;
				}
			}
		}
		else
		{
			//Debugging
			/*for (int i = 0; i < 100000; i++)
			{
				for (int j = 0; j < 10000; j++)
				{

				}
			}*/
			//cout << "Waiting...";
		}
	}

}
