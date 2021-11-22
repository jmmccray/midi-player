// Define your message queue here
#ifndef MESSAGE_QUEUE_HPP
#define MESSAGE_QUEUE_HPP

// TODO 
#include<QWidget>
#include <queue>
#include <mutex>
#include <condition_variable>

using namespace std;

class MessageQueue
{
public:


	struct Message
	{
		int ID;
	};
	//Constructor and Destructor?
	MessageQueue();
	~MessageQueue();
	void push(int const& message);
	int front();
	bool empty() const;
	bool try_pop(int& popped_value);
	void wait_and_pop(int& popped_value);

private:
	queue<int> the_queue;
	mutable std::mutex the_mutex;
	condition_variable the_condition_variable;

};
#endif