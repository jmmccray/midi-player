#include "shared_double_buffer.hpp"
#include <iostream>
// Implement your shared double buffer here

SharedDoubleBuffer::SharedDoubleBuffer(int maxSize)
{
	maxSize_ = maxSize;
}

void SharedDoubleBuffer::writeToBuffer(double sample)
{
	//Non-blocking
	//cout << "Entering Write Buffer..." << endl; //Passes
	//Where to use condition
	unique_lock<mutex> lock(mux_);
	//WAITS until a buffer is empty
		while (writeBuffer.size() == maxSize_)
		{
			condition_.wait(lock);
		}

		if(writeBuffer.size() < maxSize_)
		{
			//cout << "Write Sample: " << sample << endl; //works
			writeBuffer.push(sample);
		}
		condition_.notify_all();
}

double SharedDoubleBuffer::readFromBuffer()
{
	//Block: in case the writer has not finished writing.
	//
	//cout << "Entered Read Buffer..." << endl;
	double sample = 0.0;	
	
	//cout << "Read Buffer Size: " << readBuffer.size();
		 if(!readBuffer.empty())
		{
			
			sample = readBuffer.front();
			debug = false;
			//cout << "Read Sample: " << sample << endl; //Debuging
			readBuffer.pop();
			return sample;
		}
		
			mux_.lock();
			swap(writeBuffer, readBuffer);			
			 if (readBuffer.empty() && !debug)
			{
				//cout << "Read Buffer Is Empty" << endl;
				
			}			
			mux_.unlock();
			
			condition_.notify_all();
			if (!readBuffer.empty())
			{

				sample = readBuffer.front();
				readBuffer.pop();
			}
			return sample;		
}

int SharedDoubleBuffer::getWriteBufferSize()
{
	mux_.lock();
	return writeBuffer.size();
	mux_.unlock();
}

int SharedDoubleBuffer::getReadBufferSize()
{
	mux_.lock();
	return readBuffer.size();
	mux_.unlock();
}

void SharedDoubleBuffer::clearBuffers()
{
	unique_lock<mutex> lock(mux_);
	while (!readBuffer.empty())
	{
		readBuffer.pop();
	}	
	while (!writeBuffer.empty())
	{
		writeBuffer.pop();
	}
	condition_.notify_all();
}