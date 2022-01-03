#ifndef BST_H
#define BST_H
#include <sstream>
#include "BSTInterface.h"
using namespace std;

// NOTE: This is a template class, therefore there is no .cpp file provided
//		 Functions longer than 10 lines are defined below, outside of the class
template <typename T>
class BST : public BSTInterface<T>
{
private:
	struct Node
	{
		T data_;
		Node* left_;
		Node* right_;
		Node(const T& d) : data_(d), left_(NULL), right_(NULL) { }
	};
	Node* root_;

	size_t tree_size = 0;

	/** Inserts a new node **/
	bool insert(Node*& node, const T& data);

	/** Deletes the tree **/
	void deleteTree(Node*& node);

	/** Copies the tree **/
	void copyNodes(Node* node)
	{
		if (node == NULL) 
		{
			return;
		}
		insert(this->root_, node->data_);
		copyNodes(node->left_);
		copyNodes(node->right_);
	} 

	/** Finds if a node is in the tree **/
	bool search(Node* node, const T& data) const;

	/** Gets the predecessor node, and delete it from tree **/
	/*  (Only to be used by the remove helper function) */
	/*  !! Since this is a Node struct type, it cannot be defined outside the class. !! */
	Node* predecessor(Node* node)
	{
		Node* current = node;
		Node* parent = current;		// first sets parent node to current node
		current = current->left_;	// then sets the current node to the left node to start

		/* loop down to find the rightmost leaf */
		while (current && current->right_ != NULL) 
		{
			parent = current;			// set parent to current node
			current = current->right_;	// set current node to right child node
		}
		if (parent == node)			// after while-loop completes
		{							// if parent node is the given node, delete the left node
			parent->left_ = NULL;
		}
		else						// otherwise delete the right node
		{
			parent->right_ = NULL;
		}

		return current;		// return the current node (the predecessor node)
	}

	/** Removes given node, and adjust tree as needed **/
	bool remove(Node* parent, Node* node, const T& data);

	/** Outputs nodes at a given level **/
	bool outLevel(Node* root, int level, stringstream& out) const;


public:
	BST() : root_(NULL) {}
	~BST() { clearTree(); }


	/* Deep Copy Constructor */
	BST(const BST& bst) : root_(NULL) 
	{
		this->copyNodes(bst.root_);
	}

	/* Deep Assignment Operator */
	BST& operator=(const BST& rhs)
	{
		BST<T> the_copy(rhs);
		swap(this->root_, the_copy.root_);
		return *this;
	}


	/** Return true if node added to BST, else false **/
	bool addNode(const T& data) 
	{
		return insert(root_, data); 
	}

	/** Return true if node removed from BST, else false **/
	bool removeNode(const T& data) 
	{ 
		return remove(NULL, root_, data);
	}

	/** Return true if BST cleared of all nodes, else false **/
	bool clearTree();

	/** Finds if value is in tree, returns true or false **/
	bool find(const T& data) const
	{ 
		return search(root_, data);
	}

	/** Returns number of nodes in tree **/
	size_t sizeTree() const
	{
		return tree_size; 
	}

	/** Return a level order traversal of a BST as a string **/
	string toString() const;

	/** Insertion operator to call tree's toString **/
	friend ostream& operator<< (ostream& os, BST<T>& bst)
	{
		if (bst.root_ == NULL) 
		{
			return os << "empty"; 
		}
		else 
		{ 
			return os << bst.toString();
		}
	} 



	/**  Nested Class Iterator - of Class BST  **/
	class Iterator
	{
	private:
		Node* nptr;
		Node* root;
		bool found = false;
	public:
		Iterator(Node* np, Node* rt) : nptr(np), root(rt) {}
		~Iterator() {}

		bool operator!= (const Iterator& rhs) const	// != operator for iterators
		{
			return this->nptr != rhs.nptr;
		}

		bool operator== (const Iterator& other) const	// == operator for iterators
		{
			return this->nptr == other.nptr;
		}

		Iterator& operator++ ()	// ++ operator for iterators
		{
			found = false;
			T data = nptr->data_;
			nptr = NULL;
			findNode(root, data);
			return *this;
		}

		T& operator*() const	// * operator for iterators
		{
			if (nptr == NULL)
			{
				throw string("Invalid dereference!!");
			}
			return nptr->data_;
		}

		virtual string toString() const
		{
			std::ostringstream os;
			os << nptr->data_;
			
			return os.str();
		}

		/**  Outputs the toString function using << operator */
		friend ostream& operator<<(ostream& os, Iterator iter)
		{
			return os << iter.toString();
		}

		/** 'Getter' for nptr private data member */
		Node* getNode() const
		{
			return nptr;
		}

		bool findNode(Node* node, const T& data)
		{
			if (node == NULL) // If node is nonexistant, return false
			{
				return false;
			}
			if (node->data_ == data) // if node with data is found, return true
			{
				found = true;
				
				return findNode(node->right_, data);
			}
			if (node->data_ < data) // If node's data is less than given data, search right
			{
				
				return findNode(node->right_, data);
			}
			bool temp = findNode(node->left_, data);
			if (found)
			{
				nptr = node;
				found = false;
			}
			return temp; 
		}

		void begin()
		{
			if (nptr != NULL)
			{
				while (nptr->left_ != NULL)
				{
					nptr = nptr->left_;
				}
			}
		}
	};

	// BONUS Iterator Commands
	/** Return left-most node **/
	Iterator begin(void)
	{
		Iterator find(root_, root_);

		find.begin();

		return find;
	}

	/** Returns something not on the BST (NULL) **/
	Iterator end(void)
	{
		return Iterator(NULL, root_);
	}
};


/* Functions that were more than 10 lines - Defined outside of class */
template<typename T>
bool BST<T>::insert(Node*& node, const T& data)
{
	if (node == NULL) // If there is no node at location, insert node there
	{
		node = new Node(data);
		tree_size++;
		return true;
	}
	if (data == node->data_) // If node with that data is found, don't insert new node
	{
		return false;
	}
	if (data < node->data_) // If data is less than the node's data, insert left
	{
		return insert(node->left_, data);
	}
	return insert(node->right_, data); // Otherwise insert right
}

template<typename T>
void BST<T>::deleteTree(Node*& node)
{
	if (node == NULL)
	{
		return;
	}
	deleteTree(node->left_);
	deleteTree(node->right_);
	tree_size--;
	delete(node);
	node = NULL;
	return;
}

template<typename T>
bool BST<T>::search(Node* node, const T& data) const
{
	if (node == NULL) // If node is nonexistant, return false
	{
		return false;
	}
	if (node->data_ == data) // if node with data is found, return true
	{
		return true;
	}
	if (node->data_ < data) // If node's data is less than given data, search right
	{
		return search(node->right_, data);
	}
	return search(node->left_, data); // Otherwise search left
}

template<typename T>
bool BST<T>::remove(Node* parent, Node* node, const T& data)
{
	// base case
	if (node == NULL) // If node is nonexistent, return false
	{
		return false;
	}

	if (data < node->data_) // If given data is less than node's data, remove left
	{
		return remove(node, node->left_, data);
	}

	if (data > node->data_) // if given data is greater than node's data, remove right
	{
		return remove(node, node->right_, data);
	}


	// node has no child
	if (node->left_ == NULL && node->right_ == NULL) // If node has no left/right (has no children)
	{
		// only node in tree
		if (parent == NULL) // If node has no parent (only node in tree)
		{
			root_ = NULL; // Delete the root
		}

		// Cleans up parents link to node
		else if (parent->left_ == node) // If node is the left child
		{
			parent->left_ = NULL;
		}
		else							// If node is the right child
		{
			parent->right_ = NULL;
		}
		tree_size--;
		delete(node);
		return true;
	}


	// node with only one child on the right
	else if (node->left_ == NULL)			// If left node is blank, must be right node
	{
		if (parent->left_ == node)
		{
			parent->left_ = node->right_;
		}
		else // (parent->right_ == node)	
		{
			parent->right_ = node->right_;
		}
		tree_size--;
		delete(node);
		return true;
	}

	// node with only one child on the left
	else if (node->right_ == NULL)			// If right node is blank, must be left node
	{
		if (parent->left_ == node)
		{
			parent->left_ = node->left_;
		}
		else // (parent->right_ == node)
		{
			parent->right_ = node->left_;
		}
		tree_size--;
		delete(node);
		return true;
	}

	// node with two children:
	else
	{
		Node* temp = predecessor(node);	// Get the predecessor, return and delete it

		node->data_ = temp->data_;		// Copy the predecessor's content to node
		tree_size--;
		delete(temp);

		return true;
	}
}

template<typename T>
bool BST<T>::outLevel(Node* root, int level, stringstream& out) const
{
	if (root == NULL)
	{
		return false;
	}
	if (level == 1)
	{
		out << " " << root->data_;
		if ((root->left_ != NULL) || (root->right_ != NULL))
		{
			return true;
		}
		return false;
	}
	if ((level == 2) && !root->left_ && root->right_)
	{
		out << " _";
	}
	bool left = outLevel(root->left_, level - 1, out);
	bool right = outLevel(root->right_, level - 1, out);
	if ((level == 2) && root->left_ && !root->right_)
	{
		out << " _";
	}
	return left || right;
}


template<typename T>
bool BST<T>::clearTree()
{
	deleteTree(root_);
	if (tree_size == 0) // Double checks the list is empty
	{
		return true;
	}
	else
	{
		return false;
	}
}

template<typename T>
string BST<T>::toString() const
{
	stringstream out;
	if (root_ != NULL) // If root isn't blank/tree isn't empty
	{
		int level = 0;
		do
		{
			out << endl << "  " << ++level << ":";	// Ouput the level incremented
		} while (outLevel(root_, level, out));		// Output the given level 
	}
	return out.str();	// Return stringstream 
}

#endif // BST_H