#ifndef AVL_H
#define AVL_H
#include <sstream>
#include <algorithm>
#include "AVLInterface.h"
using namespace std;

template<typename T>
class AVL : public AVLInterface<T>
{
private:
	struct Node
	{
		T data;
		Node* left;
		Node* right;
		enum balance_type { LEFT_HEAVY = -1, BALANCED = 0, RIGHT_HEAVY = +1 };
		int balance;

		Node(const T& d) : data(d), left(NULL), right(NULL), balance(BALANCED) { }
	};

	Node* root;
	size_t tree_size;
	bool increase;
	bool decrease;

	/** Inserts a new node **/
	bool insert(Node*& node, const T& data);

	/** Deletes the tree **/
	void deleteTree(Node*& node);

	/** Finds if a node is in the tree **/
	bool search(Node* node, const T& data) const;

	/** Removes given node, and adjust tree as needed **/
	bool remove(Node* parent, Node* node, const T& data);

	/** Outputs nodes at a given level **/
	bool outLevel(Node* root, int level, stringstream& out) const;

	/** Gets the predecessor node, and delete it from tree **/
	/*  (Only to be used by the remove helper function) */
	/*  !! Since this is a Node struct type, it cannot be defined outside the class. !! */
	Node* predecessor(Node* node)
	{
		Node* current = node;
		Node* parent = current;		// first sets parent node to current node
		current = current->left;	// then sets the current node to the left node to start

		/* loop down to find the rightmost leaf */
		while (current && current->right != NULL)
		{
			parent = current;			// set parent to current node
			current = current->right;	// set current node to right child node
		}
		if (parent == node)			// after while-loop completes
		{							// if parent node is the given node, delete the left node
			parent->left = NULL;
		}
		else						// otherwise delete the right node
		{
			parent->right = NULL;
		}

		return current;		// return the current node (the predecessor node)
	}

	// AVL-Tree Functions

	void rebalance_left(Node*& node);
	void rebalance_right(Node*& node);

	Node* rotate_left(Node*& node) {
		Node* temp = node->right;
		node->right = temp->left;
		temp->left = node;
		node = temp;
		return node;
	}

	Node* rotate_right(Node*& node) {
		Node* temp = node->left;
		node->left = temp->right;
		temp->right = node;
		node = temp;
		return node;
	}

public:
	AVL() : root(NULL), tree_size(0), increase(false), decrease(false) {}
	~AVL() { clearTree();  }

	/** Return true if node added to AVL, else false */
	bool addNode(const T& data) { return insert(root, data); }

	/** Return true if node removed from AVL, else false */
	bool removeNode(const T& data) { return remove(NULL, root, data); }

	/** Return true if AVL cleared of all nodes, else false */
	bool clearTree()
	{
		deleteTree(root);
		if (tree_size == 0) { return true; }
		else { return false; }
	}

	bool find(const T& data) const { return search(root, data); }

	/** Return number of elements in AVL tree */
	size_t sizeTree() { return tree_size; }

	/** Return a level order traversal of a AVL as a string */
	std::string toString() const;

	friend ostream& operator<< (ostream& os, AVL<T>& avl)
	{
		if (avl.root == NULL) { return os << "empty"; }
		else { return os << avl.toString(); }
	}
};


/* Functions that were more than 10 lines - Defined outside of class */
template<typename T>
bool AVL<T>::insert(Node*& node, const T& data)
{
	if (node == NULL) // If there is no node at location, insert node there
	{
		node = new Node(data);
		increase = true;
		tree_size++;
		//cout << *this << endl;
		return true;
	}

	if (data < node->data) // If data is less than the node's data, insert left
	{
		bool return_value = insert(node->left, data);

		if (increase)
		{
			switch (node->balance)
			{
			case Node::BALANCED:
				// local root is now left heavy
				node->balance = Node::LEFT_HEAVY;
				break;

			case Node::RIGHT_HEAVY:
				// local root is now right heavy
				node->balance = Node::BALANCED;
				// Overall height of local root remains the same
				increase = false;
				break;

			case Node::LEFT_HEAVY:
				// local root is now critically unbalanced
				rebalance_left(node);
				increase = false;
				break;
			} // End Switch
		} // End if (increase)
		return return_value;
	} // End if (data < node->data)

	if (data > node->data) // If data is greater than the node's data, insert right
	{
		bool return_value = insert(node->right, data);

		if (increase)
		{
			switch (node->balance)
			{
			case Node::BALANCED:
				// local root is now left heavy
				node->balance = Node::RIGHT_HEAVY;
				break;

			case Node::LEFT_HEAVY:
				// local root is now right heavy
				node->balance = Node::BALANCED;
				// Overall height of local root remains the same
				increase = false;
				break;

			case Node::RIGHT_HEAVY:
				// local root is now critically unbalanced
				rebalance_right(node);
				increase = false;
				break;
			} // End Switch
		} // End if (increase)
		return return_value;

	} // End if (data < node->data)
	
	else
	{
		increase = false;
		return false;
	}
}

template<typename T>
void AVL<T>::rebalance_left(Node*& node)
{
	Node* left_child = node->left;

	// See whether left-right-heavy
	if (left_child->balance == Node::RIGHT_HEAVY)
	{
		Node* left_right_child = left_child->right;

		// Adjust the balances to be the new values after rotations are 
		// performed
		if (left_right_child != NULL && left_right_child->balance == Node::LEFT_HEAVY)
		{
			left_child->balance = Node::BALANCED;
			left_right_child->balance = Node::BALANCED;
			node->balance = Node::RIGHT_HEAVY;
		}

		else if (left_right_child != NULL && left_right_child->balance == Node::BALANCED)
		{
			left_child->balance = Node::BALANCED;
			left_right_child->balance = Node::BALANCED;
			node->balance = Node::BALANCED;
		}

		else 
		{
			left_child->balance = Node::LEFT_HEAVY;
			if (left_right_child != NULL) left_right_child->balance = Node::BALANCED;
			node->balance = Node::BALANCED;
		}
		// Perform left rotation
		node->left = rotate_left(node->left);
	}
	else 
	{ 
		// Left-Left case
		 /* In this case the left child (the new root) and the
		 local root (new right child) will both be balanced
		 after the rotation.
		 */
		left_child->balance = Node::BALANCED;
		node->balance = Node::BALANCED;
	}
	// Finally rotate right
	node = rotate_right(node);
}

template<typename T>
void AVL<T>::rebalance_right(Node*& node)
{
	Node* right_child = node->right;

	// See whether right-left-heavy
	if (right_child->balance == Node::LEFT_HEAVY)
	{
		Node* right_left_child = right_child->left;

		// Adjust the balances to be the new values after rotations are 
		// performed
		if (right_left_child != NULL && right_left_child->balance == Node::RIGHT_HEAVY)
		{
			right_child->balance = Node::BALANCED;
			right_left_child->balance = Node::BALANCED;
			node->balance = Node::LEFT_HEAVY;
		}

		else if (right_left_child != NULL && right_left_child->balance == Node::BALANCED)
		{
			right_child->balance = Node::BALANCED;
			right_left_child->balance = Node::BALANCED;
			node->balance = Node::BALANCED;
		}

		else 
		{
			right_child->balance = Node::RIGHT_HEAVY;
			if (right_left_child != NULL) right_left_child->balance = Node::BALANCED;
			node->balance = Node::BALANCED;
		}
		// Perform right rotation
		node->right = rotate_right(node->right);
	}
	else
	{
		// Left-Left case
		 /* In this case the right child (the new root) and the
		 local root (new right child) will both be balanced
		 after the rotation.
		 */
		right_child->balance = Node::BALANCED;
		node->balance = Node::BALANCED;
	}
	// Finally rotate left
	node = rotate_left(node);
}

template<typename T>
bool AVL<T>::remove(Node* parent, Node* node, const T& data)
{
	// base case
	if (node == NULL) // If node is nonexistent, return false
	{
		return false;
	}

	if (data < node->data) // If given data is less than node's data, remove left
	{
		bool return_value = remove(node, node->left, data);

		if (decrease && return_value)
		{
			switch (node->balance)
			{
			case Node::BALANCED:
				node->balance = Node::RIGHT_HEAVY;
				decrease = false;
				break;

			case Node::LEFT_HEAVY:
				node->balance = Node::BALANCED;
				//decrease = false;
				break;

			case Node::RIGHT_HEAVY:
				rebalance_right(node);
				//decrease = false;
				break;
			} // End Switch
		} // End if (increase)

		//cout << "remove: " << data << * this << endl;
		return return_value;

	}

	if (data > node->data) // if given data is greater than node's data, remove right
	{
		bool return_value  = remove(node, node->right, data);

		if (decrease && return_value)
		{
			switch (node->balance)
			{
			case Node::BALANCED:
				node->balance = Node::LEFT_HEAVY;
				decrease = false;
				break;

			case Node::RIGHT_HEAVY:
				node->balance = Node::BALANCED;
				//decrease = false;
				break;

			case Node::LEFT_HEAVY:
				rebalance_left(node);
				//decrease = false;
				break;
			} // End Switch
		} // End if (increase)

		//if (return_value) cout << endl << "remove: " << data << *this << endl;
		return return_value;
	}


	// node has no child
	if (node->left == NULL && node->right == NULL) // If node has no left/right (has no children)
	{
		// only node in tree
		if (parent == NULL) // If node has no parent (only node in tree)
		{
			root = NULL; // Delete the root
		}

		// Cleans up parents link to node
		else if (parent->left == node) // If node is the left child
		{
			parent->left = NULL;
		}
		else							// If node is the right child
		{
			parent->right = NULL;
		}
		tree_size--;
		delete(node);
		decrease = true;
		//cout << endl << "remove: " << data << *this << endl;
		return true;
	}


	// node with only one child on the right
	else if (node->left == NULL && node->right != NULL)			// If left node is blank, must be right node
	{
		if (parent == NULL) // if parent is null, we are dealing with the root node.
		{
			Node* temp = node;
			node = node->right;

			tree_size--;
			delete(temp);
			root = node;
			decrease = true;
			//cout << endl << "remove: " << data << *this << endl;
			return true;
		}
		else if (parent->left == node)
		{
			parent->left = node->right;
		}
		else // (parent->right == node)	
		{
			parent->right = node->right;
		}
		tree_size--;
		delete(node);
		decrease = true;

		//cout << endl << "remove: " << data << *this << endl;
		return true;
	}

	// node with only one child on the left
	else if (node->right == NULL && node->left != NULL)			// If right node is blank, must be left node
	{
		if (parent == NULL) // if parent is null, we are dealing with the root node.
		{
			Node* temp = node;
			node = node->left;
			
			tree_size--;
			delete(temp);
			root = node;
			decrease = true;


			//cout << *this << endl;
			return true;
		}
		else if (parent->left == node)
		{
			parent->left = node->left;
		}
		else // (parent->right == node)
		{
			parent->right = node->left;
		}
		tree_size--;
		delete(node);
		decrease = true;

		//cout << endl << "remove: " << data << *this << endl;
		return true;
	}

	// node with two children:
	else
	{
		Node* temp = predecessor(node);	// Get the predecessor, return and delete it

		node->data = temp->data;		// Copy the predecessor's content to node
		tree_size--;
		delete(temp);
		decrease = true;

		if (decrease)
		{
			switch (node->balance)
			{
			case Node::BALANCED:
				node->balance = Node::RIGHT_HEAVY;
				decrease = false;
				break;

			case Node::LEFT_HEAVY:
				node->balance = Node::BALANCED;
				//decrease = false;
				break;

			case Node::RIGHT_HEAVY:
				rebalance_right(node);
				//decrease = false;
				break;
			} // End Switch
		} // End if (increase)

		//cout << endl << "remove: " << data << *this << endl;
		return true;
	}
}

template<typename T>
void AVL<T>::deleteTree(Node*& node)
{
	if (node == NULL)
	{
		return;
	}
	deleteTree(node->left);
	deleteTree(node->right);
	tree_size--;
	delete(node);
	node = NULL;
	return;
}

template<typename T>
bool AVL<T>::search(Node* node, const T& data) const
{
	if (node == NULL) // If node is nonexistant, return false
	{
		return false;
	}
	if (node->data == data) // if node with data is found, return true
	{
		return true;
	}
	if (node->data < data) // If node's data is less than given data, search right
	{
		return search(node->right, data);
	}
	return search(node->left, data); // Otherwise search left
}

template<typename T>
bool AVL<T>::outLevel(Node* root, int level, stringstream& out) const
{
	if (root == NULL)
	{
		return false;
	}
	if (level == 1)
	{
		out << " " << root->data;
		if ((root->left != NULL) || (root->right != NULL))
		{
			return true;
		}
		return false;
	}
	if ((level == 2) && !root->left && root->right)
	{
		out << " _";
	}
	bool left = outLevel(root->left, level - 1, out);
	bool right = outLevel(root->right, level - 1, out);
	if ((level == 2) && root->left && !root->right)
	{
		out << " _";
	}
	return left || right;
}


template<typename T>
std::string AVL<T>::toString() const
{
	stringstream out;
	if (root != NULL) // If root isn't blank/tree isn't empty
	{
		int level = 0;
		do
		{
			out << endl << "  " << ++level << ":";	// Ouput the level incremented
		} while (outLevel(root, level, out));		// Output the given level 
	}
	return out.str();	// Return stringstream 
}

#endif //AVL_H