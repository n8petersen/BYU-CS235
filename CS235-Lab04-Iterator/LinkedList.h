#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include <sstream>
#include <string>
using std::string;
using std::ostream;

/** Linked List Class Template **/
/*  Note that since this is a template, class is entirely implemented */
/*  within the header file, and no .cpp file is provided.*/
template<typename T>
class LinkedList
{
private:
	struct Node
	{
		T data;
		Node* next;
		Node* prev;

		Node(const T& d) : data(d), next(NULL), prev(NULL){}
		Node(const T& d, Node* n) : data(d), next(n), prev(n){}
		~Node() = default;
	};
	Node* head;
	Node* tail;
	size_t listSize = 0;

public:
	LinkedList() : head(NULL), tail(NULL), listSize(0) {}
	~LinkedList() { clear(); }

	/** Insert Node(value) at beginning of linked list */
	virtual void push_front(const T& value)
	{
		Node* n = new Node(value);
		n->next = head;
		n->prev = NULL;
		if (listSize != 0)
		{
			n->next->prev = n;
		}
		head = n;
		listSize++;
		if (listSize == 1) {
			tail = n;
		}
	}

	/** Remove Node at beginning of linked list */
	virtual void pop_front()
	{
		Node* tmp = head;
		head = head->next;
		if (listSize != 1)
		{
			head->prev = NULL;
		}
		delete tmp;
		--listSize;
	}

	/** Returns reference to value of Node at beginning of linked list */
	virtual T& front(void)
	{
		return head->data;
	}

	/** Returns true if linked list size == 0 */
	virtual bool empty(void) const 
	{
		bool empty = (listSize == 0) ? true : false;
		return empty;
	}

	/** Removes all Nodes with value from linked list */
	/*  First while loop handles special case where first item is being removed */
	/*  Second while loop handles all other cases being removed */
	virtual void remove(const T& value)
	{
		if (listSize != 0)
		{
			Node* del;
			while (head != NULL && head->data == value)
			{
				Node* tmp = head;
				head = head->next;
				if (listSize != 1)
				{
					head->prev = NULL;
				}
				delete tmp;
				--listSize;
			}

			Node* tmp = head;
			while (tmp !=NULL && tmp->next != NULL)
			{
				if (tmp->next->data == value)
				{
					del = tmp->next;
					if (del->next == NULL)
					{
						tail = tmp;
					}
					tmp->next = tmp->next->next;
					if (tmp->next != NULL)
					{
						tmp->next->prev = tmp;
					}
					delete del;
					--listSize;

				}
				else
				{
					tmp = tmp->next; 
				}
			}
		}
	}

	/** Removes all Nodes from linked list */
	/*  Only clears when list is populated.If empty does nothing. */
	virtual void clear(void)
	{ 
		if (listSize != 0)	
		{
			while (listSize != 0)
			{
				Node* tmp = head;
				head = head->next;
				T v = tmp->data;
				delete tmp;
				listSize--;
			}
			tail = NULL;
		}
	}

	/** Reverses Nodes in linked list */
	virtual void reverse(void) 
	{
		Node* current = head;
		Node* prev = NULL, * next = NULL;
		tail = head;

		while (current != NULL) 
		{
			next = current->next;
			current->next = prev;
			current->prev = next;
			prev = current;
			current = next;
		}
		head = prev;
	}

	/** Returns the number of nodes in the linked list */
	virtual size_t size(void) const
	{
		return listSize;
	}
	
	/** Inserts Node(value) at end of linked list */
	/*  If statement handles special case where list is empty*/
	/*  Else handles all other cases */
	virtual void push_back(const T& value) 
	{
		Node* n = new Node(value);
		listSize++;
		if (head == NULL)
		{
			head = n;
		}
		else
		{
			tail->next = n;
			n->prev = tail;
		}
		tail = n;
	}

	/** Remove Node at end of linked list */
	/*  If list has more than one item, it sets the tail's next item to NULL */
	virtual void pop_back(void) 
	{
		Node* tmp = tail;
		tail = tail->prev;
		if (listSize != 1)
		{
			tail->next = NULL;
		}
		delete tmp;
		--listSize;
	}

	/** Return reference to value of Node at end of linked list */
	virtual T& back(void)
	{
		return tail->data;
	}

	/** Pushes data from old list to a new list */
	/*  Reverses new list so nodes are in correct order */
	void copyList(LinkedList& newList)
	{
		Node* node_ptr = head;
		while (node_ptr != NULL)
		{
			newList.push_front(node_ptr->data);	
			node_ptr = node_ptr->next;
		}
		newList.reverse();	
	}

	/**  Runs through list, prints node data and checks if it is last. If it is not last, it prints a space after */
	virtual string toString() const
	{
		std::ostringstream os;
		Node* node_ptr = head;
		while (node_ptr != NULL)
		{
			os << node_ptr->data << (node_ptr->next != NULL ? " " : "");
			node_ptr = node_ptr->next;
		}
		return os.str();
	}
	
	// Outputs the toString function using << operator
	friend ostream& operator<<(ostream& os, LinkedList& ll)
	{ 
		if (ll.listSize == 0)
		{
			return os << "Empty!";
		}
		else
		{
			return os << ll.toString();
		}
	}


	/**  Nested Class Iterator - of Class LinkedList  **/
	class Iterator
	{
	private:
		Node* nptr;
	public:
		Iterator(Node* np) : nptr(np) {}
		~Iterator() {}

		bool operator!=(const Iterator& rhs) const	// != operator for iterators
		{
			return this->nptr != rhs.nptr;
		}

		bool operator==(const Iterator& other) const	// == operator for iterators
		{
			return this->nptr == other.nptr;
		}

		Iterator& operator++()	// ++ operator for iterators
		{
			nptr = nptr->next;
			return *this;
		}
		
		Iterator& operator--() // -- operator for iterators
		{
			nptr = nptr->prev; return *this;
		}

		T& operator*() const	// * operator for iterators
		{
			if (nptr == NULL)
			{
				throw string("Invalid dereference!!");
			}
			return nptr->data;
		}
		

		/**  Runs through list, prints node data and checks if it is last. If it is not last, it prints a space after */
		virtual string toString() const
		{
			std::ostringstream os;
			os << nptr->data << (nptr->next != NULL ? " " : "");

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
	};


	/** Returns iterator pointing to the first value in linked list */
	Iterator begin(void)
	{	
		return Iterator(this->head);
	}

	/** Returns iterator pointing to NULL*/
	Iterator end(void)
	{
		return Iterator(NULL);
	}

	/** Returns iterator containing found value in linked list. If not found, returns Iterator of NULL*/
	Iterator find(Iterator first, Iterator last, const T& value)
	{	
		LinkedList<string>::Iterator iter = first;
		while (iter != last)
		{
			if (*iter != value)
			{
				++iter;
			}
			else
			{
				return iter;
			}
		}
		return LinkedList<T>::Iterator(NULL);
	}

	/** Inserts value in list before given iterator **/
	/*  If iter is not the given position, continues through list*/
	/*  Creates a new node. If it is the first item in the list, it sets the head to new node. */
	/*  Sets the appropriate prev and next in doubly linked list */
	/* Returns iterator pointing to inserted value in linked list*/
	Iterator insert(Iterator position, const T& value)
	{	
		LinkedList<string>::Iterator iter = begin();
		while (iter != end())
		{
			if (iter != position)
			{
				++iter;
			}
			else
			{
				Node* nptr = position.getNode();
				Node* n = new Node(value);
				listSize++;

				if (nptr->prev == NULL)
				{
					n->prev = NULL;
					head = n;
				}
				else
				{
					n->prev = nptr->prev;
					n->prev->next = n;
				}
				n->next = nptr;
				nptr->prev = n;
				
				return iter;
			}
		}

		return LinkedList<T>::Iterator(NULL); 
	}

	/** Inserts value in list after given iterator **/
	/*  If iter is not the given position, continues through list*/
	/*  Creates a new node. If it is the last item in the list, it sets the tail to new node. */
	/*  Sets the appropriate prev and next in doubly linked list */
	/* Returns iterator pointing to inserted value in linked list*/
	Iterator insert_after(Iterator position, const T& value)
	{
		LinkedList<string>::Iterator iter = begin();
		while (iter != end())
		{
			if (iter != position)
			{
				++iter;
			}
			else
			{
				Node* nptr = position.getNode();
				Node* n = new Node(value);
				listSize++;

				if (nptr->next == NULL)
				{
					n->next = NULL;
					tail = n;
				}
				else
				{
					n->next = nptr->next;
					n->next->prev = n;
				}
				n->prev = nptr;
				nptr->next = n;

				return iter;
			}
		}

		return LinkedList<T>::Iterator(NULL);
	}

	/** Erases first value that iterator contains */
	/*  If iter is not the given position, continues through list*/
	/*  When position is found, sets appropriate links in doubly linked list */
	/*  Special cases included to handle when the first object (head) or last object (tail) are removed */
	/*  Removes object from linked list */
	/* Returns iterator pointing to next item after deleted node linked list */
	Iterator erase(Iterator position)
	{	
		LinkedList<string>::Iterator iter = begin();
		while (iter != end())
		{
			if (iter == position)
			{
				Node* nptr = position.getNode();
				Node* del;

				if (iter == head)
				{
					nptr->next->prev = NULL;
					del = head;
					head = head->next;

				}
				else if (nptr->next == NULL)
				{
					nptr->prev->next = NULL;
					del = tail;
					tail = tail->prev;
				}
				else
				{
					nptr->next->prev = nptr->next->prev->prev;
					nptr->prev->next = nptr->prev->next->next;
					del = nptr;
				}

				delete del;
				--listSize;

				LinkedList<string>::Iterator returnIter = (nptr->next == NULL) ? NULL : ++iter;
				return returnIter;
			}
			else
			{
				++iter;
			}
		}
		return LinkedList<T>::Iterator(NULL);
	}

	/** Replace found old_value(s) with new_value */
	/*  Counts how many replacements are made. */
	/*  In main, if this count > 0, it will print OK. Otherwise it will print nothing. */
	int replace(Iterator first, Iterator last, const T& old_value, const T& new_value)
	{	
		LinkedList<string>::Iterator iter = first;
		int count = 0;
		while (iter != last)
		{
			Node* nptr = iter.getNode();
			if (*iter == old_value)
			{
				nptr->data = new_value;
				++count;
			}
			++iter;
		}
		return count;
	}
};
#endif