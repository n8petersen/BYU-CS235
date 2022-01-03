#ifndef VECTOR_H
#define VECTOR_H

#include "Deque.h"

template <typename T>
class Vector
{
private:
	Deque<T> vector_;

public:
	Vector() {}
	~Vector() {}

	void push_back(const T data) { vector_.push_back(data); }

	void pop_back(void) { vector_.pop_back(); }

	T& back(void) { return vector_.back(); }

	size_t size(void) { return vector_.size(); }

	T& at(size_t index) { return vector_.at(index); }

	bool empty(void) const { return vector_.empty(); }

	int find(T& value) { return vector_.find(value); }


	std::string toString(void) const { return vector_.toString(); }

	friend std::ostream& operator<<(std::ostream& os, Vector& rtn) { return os << rtn.toString(); }
};

#endif //VECTOR_H