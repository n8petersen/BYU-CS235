#ifndef SET_H
#define SET_H

#include <sstream>
#include "SetInterface.h"
#include "BST.h"

using namespace std;

//NOTE:		This is essentially a wrapper class of the BST.
//			It get's all it's functionalty from the BST.

template <typename T>
class Set : public SetInterface<T>
{
private:
	BST<string> bst;

public:
	Set()  {}
	~Set() { bst.clearTree();  }

	/** Inserts item into the set, if the container doesn't
		already contain an element with an equivalent value. */
	virtual bool insert(const T& item)
	{
		return bst.addNode(item);
	}

	/** Removes all items from the set. */
	virtual void clear()
	{
		bst.clearTree();
	}

	/** @return: the number of elements contained by the Set. */
	virtual size_t size() const
	{
		return bst.sizeTree();
	}

	/** @return: return 1 if contains element equivalent to item, else 0. */
	virtual size_t count(const T& item)
	{
		return (bst.find(item) ? 1 : 0);
	}

	/** @return: string representation of items in Set. */
	virtual std::string toString() const
	{
		return bst.toString();
	}

	/** friend << operator **/
	friend ostream& operator<< (ostream& os, Set set)
	{
		return os << set.toString();
	}

};

#endif //SET_H