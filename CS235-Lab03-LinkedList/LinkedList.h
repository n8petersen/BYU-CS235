#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include <sstream>
#include <string>
#include "LinkedListInterface.h"
using std::string;
using std::ostream;

/** Linked List Class Template **/
/*  Note that since this is a template, not an object, class is entirely implemented */
/*  within the header file, and no .cpp file is provided.*/
template<typename T>
class LinkedList : public LinkedListInterface<T>
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
		if (listSize != 0) { n->next->prev = n; }
		head = n;
		listSize++;
		if (listSize == 1) tail = n;
	}

	/** Remove Node at beginning of linked list */
	virtual void pop_front()
	{
		Node* tmp = head;
		head = head->next;
		if (listSize != 1) { head->prev = NULL; }
		delete tmp;
		--listSize;
	}

	/** Return reference to value of Node at beginning of linked list */
	virtual T& front(void)
	{
		return head->data;
	}

	/** Return true if linked list size == 0 */
	virtual bool empty(void) const 
	{
		bool empty = (listSize == 0) ? true : false;
		return empty;
	}

	/** Remove all Nodes with value from linked list */
	/*  First while loop checks if first item is equal to given value, and if so deletes item. */
	/*  Second while loop checks if other items are equal to given value, and if so deletes then. */
	virtual void remove(const T& value)
	{
		if (listSize != 0)
		{
			Node* del;
			while (head != NULL && head->data == value)
			{
				Node* tmp = head;
				head = head->next;
				if (listSize != 1) { head->prev = NULL; }
				delete tmp;
				--listSize;
			}

			Node* tmp = head;
			while (tmp !=NULL && tmp->next != NULL)
			{
				if (tmp->next->data == value)
				{
					del = tmp->next;
					if (del->next == NULL) { tail = tmp; }
					tmp->next = tmp->next->next;
					if (tmp->next != NULL) { tmp->next->prev = tmp; }
					delete del;
					--listSize;

				}
				else { tmp = tmp->next; }
			}
		}
	}

	/** Remove all Nodes from linked list */
	virtual void clear(void)
	{
		if (listSize == 0) {}
		else
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
	/** Reverse Nodes in linked list */
	virtual void reverse(void) 
	{
		Node* current = head;
		Node* prev = NULL, * next = NULL;
		tail = head;

		while (current != NULL) {
			next = current->next;
			current->next = prev;
			current->prev = next;
			prev = current;
			current = next;
		}
		head = prev;
	}

	/** Return the number of nodes in the linked list */
	virtual size_t size(void) const
	{
		return listSize;
	}

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
	
	/** BONUS ** Insert Node(value) at end of linked list */
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

	/** BONUS ** Remove Node at end of linked list */
	virtual void pop_back(void) 
	{
		Node* tmp = tail;
		tail = tail->prev;
		if (listSize != 1) { tail->next = NULL; }
		delete tmp;
		--listSize;
	}

	/** BONUS ** Return reference to value of Node at end of linked list */
	virtual T& back(void)
	{
		return tail->data;
	}

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
};
#endif