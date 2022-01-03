#ifndef QUEUE_H
#define QUEUE_H

#include "Deque.h"

template <typename T>
class Queue
{
private:
	Deque<T> queue_;

public:
	Queue() {}
	~Queue() {}

	void push(const T data) { queue_.push_back(data); }

	void pop(void) { queue_.pop_front(); }

	T& top(void) { return queue_.front();  }

	size_t size(void) { return queue_.size(); }

	T& at(size_t index) { return queue_.at(index); }

	bool empty(void) const { return queue_.empty(); }

	int find(T& value) { return queue_.find(value); }


	std::string toString(void) const { return queue_.toString(); }

	friend std::ostream& operator<<(std::ostream& os, Queue& rtn) { return os << rtn.toString(); }
};

#endif //QUEUE_H