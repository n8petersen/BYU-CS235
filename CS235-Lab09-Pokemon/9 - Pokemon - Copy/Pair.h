#ifndef PAIR_H
#define PAIR_H

#include <typeinfo>

using namespace std;

template<typename T1, typename T2>
struct Pair
{
	T1 first;
	T2 second;
	// Construct a pair from two values.
	Pair(const T1& x, const T2& y) : first(x), second(y) {}

	// Construct a default pair.
	Pair() : first(T1()), second(T2()) {}

	// Construct a default pair.
	Pair(const T1& x) : first(x), second(T2()) {}

	// Construct an assignable pair
	template<typename Other_T1, typename Other_T2>
	Pair(const pair<Other_T1, Other_T2>& other)
	{
		first = other.first;
		second = other.second;
	}

	/* Checks if the second element is empty */ 
	bool isEmpty()
	{
		if (second.size() == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};

#endif // PAIR_H