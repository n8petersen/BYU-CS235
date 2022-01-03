#ifndef DEQUE_H
#define DEQUE_H
#include <algorithm>

#include "DequeInterface.h"

template<typename T>
class Deque
	: public DequeInterface<T>
{
private:
	size_t capacity;
	size_t num_items;
	size_t front_index;
	size_t rear_index;
	T* data;

	void reallocate(); // Definition located on bottom beneath class 
	
public:
	Deque(void) :
		capacity(DEFAULT_CAPACITY), //DEFAULT_CAPACITY defined in Interface as 4
		num_items(0),
		front_index(0),
		rear_index(0),
		data(new T[DEFAULT_CAPACITY]) {}

	~Deque() { delete[] data; }
	

	/** Inserts item at front of deque */
	void push_front(const T& value) 
	{
		if (num_items == capacity) reallocate(); // Reallocates if needed

		for (size_t i = num_items; i > 0; --i) { data[i] = data[i - 1]; } // Moves everything in array forward one pos
		data[0] = value;
		num_items++;
		if (num_items > 1) rear_index++; // Increases the rear_index if it's not the only item
	}

	/** Inserts item at rear of deque */
	void push_back(const T& value)
	{
		if (num_items == capacity) reallocate();// Reallocates if needed

		data[num_items] = value;
		num_items++;
		if (num_items > 1) { rear_index++; } // Increases  rear_index if it's not the only item
	}

	/** Removes the front item of the deque */
	void pop_front()
	{
		if (num_items > 0)
		{
			for (size_t i = 0; i < num_items; ++i) { data[i] = data[i + 1]; } // Moves everything in array back one pos
			data[rear_index] = NULL;
			num_items--;
			if (rear_index != 0) { rear_index--; } // Increases  rear_index if it's not the only item
		}
	}

	/** Removes the rear item of the deque */
	void pop_back() 
	{
		if (num_items > 0)
		{
			data[rear_index] = NULL;
			num_items--;
			if (rear_index != 0) { rear_index--; } // Increases  rear_index if it's not the only item
		}
	}

	/** Returns the front item of the deque (Do not remove) */
	T& front() { return data[front_index]; }

	/** Returns the rear item of the deque (Do not remove) */
	T& back() { return data[rear_index]; }

	/** Returns the number of items in the deque */
	size_t size() { return num_items; }

	/** Returns true if deque is empty */
	bool empty() const 
	{
		if (num_items == 0)
			return true;
		else
			return false;
	}

	/** Returns item in deque at index (0 based) */
	T& at(size_t index) { return data[index]; }

	/** Returns the index of the value, if it is not found it will return -1 **/
	int find(T& value)
	{
		for (int i = 0; i < num_items; ++i)
		{
			if (data[i] == value)
			{
				return i;
			}
		}
		return -1;
	}

	/** Returns the deque items */
	std::string toString(void) const 
	{
		std::stringstream out;
		for (size_t i = 0; i < num_items; ++i) { out << data[i] << " "; }
		return out.str();
	}

	friend std::ostream& operator<<(std::ostream& os, Deque& rtn) { return os << rtn.toString(); }

};

template<typename T>
void Deque<T>::reallocate() // Reallocate Definition
{
	T* new_data = new T[2 * capacity];
	for (size_t i = 0; i < num_items; ++i)
	{
		new_data[i] = data[front_index];
		front_index = (front_index + 1) % capacity;
	}
	front_index = 0;
	rear_index = num_items - 1;
	capacity = 2 * capacity;
	std::swap(data, new_data);
	delete[] new_data;
}


#endif //DEQUE_H