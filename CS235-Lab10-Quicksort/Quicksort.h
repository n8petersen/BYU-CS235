#ifndef QUICKSORT_H
#define QUICKSORT_H

#include <algorithm> 

#include "QSInterface.h"

template<typename T>
class Quicksort : public QSInterface<T>
{
private:
	size_t qs_capacity;
	int qs_numItems;
	T* qsArray;

	size_t comparisons;
	size_t exchanges;

	void reallocate();

public:
	Quicksort()
	{
		qs_capacity = 0;
		qs_numItems = 0;
		qsArray = new T[0];
		
		comparisons = 0;
		exchanges = 0;
	}

	~Quicksort()
	{
		delete[] qsArray;
	}

	bool checkConditions(int left, int right);
	bool checkConditions(int left, int right, int pivot);

	void resetCounters()
	{
		comparisons = exchanges = 0;
	}

	void setSize(size_t arraySize);


	/** Add an element to the QuickSort array. Dynamically grow array as needed. */
	virtual bool addElement(T element);


	/** Sort the elements of a QuickSort subarray using median and partition functions. */
	virtual bool sort(size_t left, size_t right);


	/** Sort all elements of the QuickSort array using median and partition functions. */
	virtual bool sortAll()
	{		
		sort(0, qs_numItems); // Kicks of recursive sort function using the very left and very right indeces.
		return true;
	}


	/** Removes all items from the QuickSort array. */
	virtual bool clear()
	{
		qs_numItems = 0; // Doesn't actually clear up the array, but allows things to be inserted
		return true;	 // overtop of the old values
	}


	/** Return size of the QuickSort array. */
	virtual size_t capacity() const
	{
		return qs_capacity;
	}


	/** Return number of elements in the QuickSort array. */
	virtual size_t size() const
	{
		return qs_numItems;
	}


	/**	Calculates the median index, and then sorts the first, middle, and last 
		numbers in the array based on their data-value  */
	virtual int medianOfThree(size_t left, size_t right);


	/** Partitions a subarray around a given pivot value */
	virtual int partition(size_t left, size_t right, size_t pivotIndex);


	/** Returns the comparisons and exhanges for the Stats command */
	std::string stats() const
	{
		std::stringstream outStats;
		outStats << comparisons << "," << exchanges;

		return outStats.str();
	}


	/** @return: comma delimited string representation of the array. */
	virtual std::string toString() const;


	friend std::ostream& operator<<(std::ostream& os, Quicksort& qst) 
	{ 
		return os << qst.toString(); 
	}

};


// FUNCTION DEFINITIONS
//======================

template<typename T>
void Quicksort<T>::setSize(size_t arraySize)
{
	delete[] qsArray;
	qsArray = new T[arraySize];

	for (int i = 0; i < arraySize; ++i) // Initializes the entire array to 0
	{									// (fix for a valgrind error I was getting
		qsArray[i] = 0;					// for accessing unitialized values).
	}

	qs_capacity = arraySize;
	qs_numItems = 0;
}


template<typename T>
bool Quicksort<T>::addElement(T element)
{
	int oldNumItems = qs_numItems;
	if (qs_numItems == qs_capacity && qs_capacity != 0) reallocate(); // Reallocates if needed

	qsArray[qs_numItems] = element; // Insert at the next open slot
	qs_numItems++;					// Increments numItems to 'increase' the size of array

	if (qs_numItems == oldNumItems + 1)	// Checks if the numItems incremented, and returns if it did or not
	{
		return true;
	}
	else
	{
		return false;
	}
}


template<typename T>
bool Quicksort<T>::sort(size_t left, size_t right)
{
	if (!checkConditions(static_cast<int>(left), static_cast<int>(right)))
	{
		return false;
	}

	if (left - right > 1) // Checks if there are contents to be sorted
	{
		size_t pivot = partition(left, right, medianOfThree(left, right)); // Gets the pivot to sort on
		sort(left, pivot); // Sorts left subarray
		sort(pivot + 1, right); // Sorts right subarray
	}

	return true;
}


template<typename T>
int Quicksort<T>::medianOfThree(size_t left, size_t right)
{
	size_t middle = (left + right) / 2; // Gets middle index

	if (qsArray[middle] < qsArray[left]) // Checks if middle is less than left, swaps if so
	{
		std::swap(qsArray[left], qsArray[middle]);
	}

	if (qsArray[right - 1] < qsArray[middle]) // Checks if middle is greater than right, swaps if so
	{
		std::swap(qsArray[middle], qsArray[right - 1]);

		if (qsArray[middle] < qsArray[left]) // Checks if swap made middle less than right, and swaps if so
		{
			std::swap(qsArray[middle], qsArray[left]);
		}
	}

	return static_cast<int>(middle); // Returns middle index
}


template<typename T>
int Quicksort<T>::partition(size_t left, size_t right, size_t pivotIndex)
{
	size_t up = left + 1;
	size_t down = right - 1;

	std::swap(qsArray[left], qsArray[pivotIndex]); // Swaps the left and pivot (usually middle) values
	pivotIndex = left; // Moves pivotIndex to left, where we just put it

	do
	{
		while (qsArray[up] <= qsArray[pivotIndex] && up < right - 1)
		{						// increments up when *up is less than *pivot,
			++up;				// and up isn't at the end
		}
		
		while (qsArray[down] > qsArray[pivotIndex] && down > left)
		{						// decrements down when *down is greater than *pivot,
			--down;				// and down isn't at the end
		}

		if (up < down && qsArray[up] > qsArray[down])
		{
			std::swap(qsArray[up], qsArray[down]);	// swaps *up and *down so that the values 
		}											// end up on the right side of the pivot

	} while (up < down);

	std::swap(qsArray[left], qsArray[down]);	// puts the pivot back into the middle 
	pivotIndex = down;							// of the array where it belongs

	return static_cast<int>(pivotIndex);
}


template<typename T>
std::string Quicksort<T>::toString() const
{
	std::stringstream out;

	for (int i = 0; i < qs_numItems; ++i)
	{
		out << qsArray[i];

		if (i < qs_numItems - 1) // when not at last element, put a comma
		{
			out << ",";
		}
	}

	return out.str();
}


template<typename T>
void Quicksort<T>::reallocate() // Reallocate Definition
{
	T* new_data = new T[2 * qs_capacity];

	for (int i = 0; i < 2 * qs_capacity; ++i)	// Initializes the entire array to 0
	{											// (fix for a valgrind error I was getting
		new_data[i] = 0;						// for accessing unitialized values).
	}

	for (size_t i = 0; i < qs_numItems; ++i)
	{
		new_data[i] = qsArray[i];
	}
	
	std::swap(qsArray, new_data);
	qs_capacity = 2 * qs_capacity;

	delete[] new_data;
}


template<typename T>
bool Quicksort<T>::checkConditions(int left, int right)
{
	if (right <= left			// Checks that the given inputs are within the bounds
		|| qs_numItems == 0
		|| right > qs_numItems
		|| left > qs_numItems
		|| right < 0
		|| left < 0)
	{
		return false;
	}

	else
	{
		return true;
	}
}


template<typename T>
bool Quicksort<T>::checkConditions(int left, int right, int pivot)
{
	if (right <= left			// Checks that the given inputs are within the bounds
		|| pivot <= left
		|| right <= pivot
		|| qs_numItems == 0
		|| right > qs_numItems
		|| left > qs_numItems
		|| pivot > qs_numItems
		|| right < 0
		|| left < 0
		|| pivot < 0)
	{
		return false;
	}

	else
	{
		return true;
	}
}

#endif //QUICKSORT_H