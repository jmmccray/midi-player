// Define your shared double buffer here
#ifndef SHARED_DOUBLE_BUFFER_HPP
#define SHARED_DOUBLE_BUFFER_HPP

// define class MIDIPlayer here
#include <QWidget>
#include <streambuf>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <iostream>
using namespace std;

// TODO 
class SharedDoubleBuffer
{

public:
	//Read from Synthesizer- Public
	SharedDoubleBuffer(int maxSize = 700000);
	void writeToBuffer(double samples);
	double readFromBuffer();
	int getWriteBufferSize();
	int getReadBufferSize();
	void clearBuffers();
	
		
private:
	int maxSize_ = 70000;	
	queue<double> writeBuffer;
	queue<double> readBuffer;
	mutex mux_;
	condition_variable condition_;
	int debug = true;
		
};
#endif

