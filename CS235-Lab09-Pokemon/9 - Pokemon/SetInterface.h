//**** YOU MAY NOT MODIFY THIS DOCUMENT ****/
#ifndef SET_INTERFACE_H
#define SET_INTERFACE_H
#include <string>

template<typename T>
class SetInterface
{
public:
	SetInterface() {}
	virtual ~SetInterface() {}

	/** Inserts item into the set, if the container doesn't
		already contain an element with an equivalent value. */
	virtual bool insert(const T& item) = 0;

	/** Removes all items from the set. */
	virtual void clear() = 0;

	/** @return: the number of elements contained by the Set. */
	virtual size_t size() const = 0;

	/** @return: return 1 if contains element equivalent to item, else 0. */
	virtual size_t count(const T& item) = 0;

	/** @return: string representation of items in Set. */
	virtual std::string toString() const = 0;
};
#endif // SET_INTERFACE_H
