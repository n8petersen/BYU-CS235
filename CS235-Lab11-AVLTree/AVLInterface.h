//**** YOU MAY NOT MODIFY THIS DOCUMENT ****/
#ifndef AVL_INTERFACE_H
#define AVL_INTERFACE_H
#include <string>

/** A binary tree node with data, left and right child pointers */
template<typename T>
class AVLInterface
{
public:
	AVLInterface(void) {}
	virtual ~AVLInterface(void) {}

	/** Return true if node added to AVL, else false */
	virtual bool addNode(const T&) = 0;

	/** Return true if node removed from AVL, else false */
	virtual bool removeNode(const T&) = 0;

	/** Return true if AVL cleared of all nodes, else false */
	virtual bool clearTree(void) = 0;

	/** Return number of elements in AVL tree */
	virtual size_t sizeTree(void) = 0;

	/** Return a level order traversal of a AVL as a string */
	virtual std::string toString(void) const = 0;
};
#endif	// AVL_INTERFACE_H
