#include "message_queue.hpp"

MessageQueue::MessageQueue()
{

}

MessageQueue::~MessageQueue()
{


}

int MessageQueue::front()
{
	//would I need to lock?
	//unique_lock<mutex> lock(the_mutex);
	return the_queue.front();
	//lock.unlock();
	//the_condition_variable.notify_one();
}

void MessageQueue::push(int const& message)
{
	std::unique_lock<std::mutex> lock(the_mutex);
	the_queue.push(message);
	lock.unlock();
	the_condition_variable.notify_one();
}

bool MessageQueue::empty() const
{
	std::lock_guard<std::mutex> lock(the_mutex);
	return the_queue.empty();
}

bool MessageQueue::try_pop(int& popped_value)
{
	std::lock_guard<std::mutex> lock(the_mutex);
	if (the_queue.empty())
	{
		return false;
	}

	popped_value = the_queue.front();
	the_queue.pop();
	return true;
}

void MessageQueue::wait_and_pop(int& popped_value)
{
	std::unique_lock<std::mutex> lock(the_mutex);
	while (the_queue.empty())
	{
		the_condition_variable.wait(lock);
	}

	popped_value = the_queue.front();
	the_queue.pop();
}