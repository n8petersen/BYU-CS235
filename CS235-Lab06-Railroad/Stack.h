#ifndef STACK_H
#define STACK_H

#include "Deque.h"

template <typename T>
class Stack
{
private:
	Deque<T> stack_;

public:
	Stack() {}
	~Stack() {}

	void push(const T data) { stack_.push_back(data); }

	void pop(void) { stack_.pop_back(); }

	T& top(void) { return stack_.back(); }

	size_t size(void) { return stack_.size(); }

	T& at(size_t index) { return stack_.at(index); }

	bool empty(void) const { return stack_.empty(); }

	int find(T& value) { return stack_.find(value); }


	std::string toString(void) const { return stack_.toString(); }

	friend std::ostream& operator<<(std::ostream& os, Stack& rtn) { return os << rtn.toString(); }
};

#endif //STACK_H