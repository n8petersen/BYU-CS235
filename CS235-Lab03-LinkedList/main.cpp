#include <iostream>
#include <fstream>
#include "LinkedList.h"

using namespace std;

#ifdef _MSC_VER // Memory leak check
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK
#endif

inline const char* const BoolToString(bool b)
{
	return b ? "true" : "false";
}

int main(int argc, char* argv[])
{
	VS_MEM_CHECK               // Enable memory leak check

	ifstream in; // Reading Input file
	in.open(argv[1]);
	if (in.is_open())
	{
		cout << "Input File opened successfully.\n";
	}
	else
	{
		cout << "ERROR: Input file could not open.\n";
		return 1;
	}

	ofstream out; // Writing Output File
	out.open(argv[2]);
	if (out.is_open())
	{
		cout << "Output File opened successfully.\n";
	}
	else
	{
		cout << "ERROR: Output file could not open.\n";
		return 1;
	}

	LinkedList<string> myList;
	LinkedList<string> copyList;

	for (string line; getline(in, line);)
	{
		string item1, item2;
		if (line.size() == 0) continue;
		out << line << " ";
		istringstream iss(line);
		iss >> item1;


		if (item1 == "Insert") // Inserts item or items at the head of the linked list.
		{
			while (iss >> item2)
			{
				myList.push_front(item2);
			}
		}


		else if (item1 == "Delete") // Deletes the first item in the linked list. Outputs "OK" if successful. Throws an error "Empty!" if linked list is empty.
		{
			try
			{
				if (myList.size() == 0) { throw string("Empty!"); }
				else
				{
					myList.pop_front();
					out << "OK";
				}
			}
			catch (string& s) { out << s; }


		}


		else if (item1 == "First") // Outputs the first item in the linked list. Throws an error "Empty!" if linked list is empty.
		{
			try
			{
				if (myList.size() == 0)
				{
					throw string("Empty!");
				}
				else
				{
					out << myList.front();
				}
			}
			catch (string& s) { out << s; }

		}


		else if (item1 == "Empty") // Outputs true if linked list empty, else false.
		{
			out << BoolToString(myList.empty());

		}


		else if (item1 == "Remove") // Removes all like items from the linked list.
		{
			while (iss >> item2)
			{
				myList.remove(item2);
			}
		}


		else if (item1 == "Clear") // Deletes all items in the linked list. Outputs "OK" if successful.
		{
			if (myList.size() == 0) {}
			else
			{
				myList.clear();
				out << "OK";
			}
		}


		else if (item1 == "Reverse") // Reverses the items in the linked list. Output "OK" if successful. Throws an error "Empty!" if linked list is empty.
		{
			try
			{
				if (myList.size() == 0) { throw string("Empty!"); }
				else
				{
					myList.reverse();
					out << "OK";
				}
			}
			catch (string& s) { out << s; }
			
		}


		else if (item1 == "Size") // Outputs the number of items in the linked list.
		{
			out << myList.size();
		}


		else if (item1 == "PrintList") // Output the contents of the linked list, space separated. Outputs "Empty!" if list is empty.
		{
			try
			{
				if (myList.size() == 0)
				{
					throw string("Empty!");
				}
				else
				{
					out << myList;
				}
			}
			catch (string& s) { out << s; }
		}


		else if (item1 == "Append") // Inserts item or items at the end of the doubly linked list.
		{
			while (iss >> item2)
			{
				myList.push_back(item2);
			}
		}


		else if (item1 == "Drop") // Deletes the last item in the doubly linked list. Throws an error "Empty!" if linked list is empty.
		{
			try
			{
				if (myList.size() == 0) { throw string("Empty!"); }
				else
				{
					myList.pop_back();
					out << "OK";
				}
			}
			catch (string& s) { out << s; }
			
		}


		else if (item1 == "Last") // Outputs the last list item in the doubly linked list. Throws an error "Empty!" if linked list is empty.
		{
			try
			{
				if (myList.size() == 0)
				{
					throw string("Empty!");
				}
				else
				{
					out << myList.back();
				}
			}
			catch (string& s) { out << s; }
		}


		else if (item1 == "Copy") // Makes a deep copy of the current List.
		{
			myList.copyList(copyList);
			out << "OK";
		}

		else if (item1 == "PrintCopy") // Outputs the contents of the linked list copy. Outputs "Empty!" if list is empty.
		{
			try
			{
				if (copyList.size() == 0)
				{
					throw string("Empty!");
				}
				else
				{
					out << copyList;
				}
			}
			catch (string& s) { out << s; }
		}

		out << endl;
	}
	return 0;
}