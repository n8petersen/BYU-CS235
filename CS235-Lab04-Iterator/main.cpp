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

	if (argc < 3) // Checks if file names were set
	{
		cerr << "Please provide name of input and output files";
		return 1;
	}
	ifstream in(argv[1]); // Reading input file
	if (!in)
	{
		cerr << "Unable to open " << argv[1] << " for input";
		return 2;
	}
	else
	{
		cout << argv[1] << " opened successfully.\n";
	}
	ofstream out(argv[2]); // Reading output file
	if (!out)
	{
		in.close();
		cerr << "Unable to open " << argv[2] << " for output";
		return 3;
	}
	else
	{
		cout << argv[2] << " opened successfully.\n";
	}

	LinkedList<string> myList;
	LinkedList<string> copyList;
	

	for (string line; getline(in, line);) // Reads line from input file into string variable 'line'
	{
		out << endl;

		string command, value; // creates string variables 'command' and 'value'
		if (line.size() == 0) continue; // If the line is empty, goes to next line.
		out << line << " "; // Outputs the input line
		istringstream iss(line); // Parses first part of line into the iss
		iss >> command; // puts iss into string variable 'command'


		/** Linked List Commands - Lab 3  */
		/*   Checks if input command is valid, and processes valid commands */
		if (command == "Insert") // Inserts item or items at the head of the linked list.
		{
			while (iss >> value)
			{
				myList.push_front(value);
			}
		}


		else if (command == "Delete") // Deletes the first item in the linked list. Outputs "OK" if successful. Throws an error "Empty!" if linked list is empty.
		{
			try
			{
				if (myList.size() == 0)
				{
					throw string("Empty!");
				}
				else
				{
					myList.pop_front();
					out << "OK";
				}
			}
			catch (string& s)
			{ 
				out << s;
			}


		}


		else if (command == "First") // Outputs the first item in the linked list. Throws an error "Empty!" if linked list is empty.
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
			catch (string& s) 
			{ 
				out << s;
			}

		}


		else if (command == "Empty") // Outputs true if linked list empty, else false.
		{
			out << BoolToString(myList.empty());

		}


		else if (command == "Remove") // Removes all like items from the linked list.
		{
			while (iss >> value)
			{
				myList.remove(value);
			}
		}


		else if (command == "Clear") // Deletes all items in the linked list. Outputs "OK" if successful.
		{
			if (myList.size() != 0)
			{
				myList.clear();
				out << "OK";
			}
		}


		else if (command == "Reverse") // Reverses the items in the linked list. Output "OK" if successful. Throws an error "Empty!" if linked list is empty.
		{
			try
			{
				if (myList.size() == 0)
				{
					throw string("Empty!"); 
				}
				else
				{
					myList.reverse();
					out << "OK";
				}
			}
			catch (string& s)
			{
				out << s; 
			}
			
		}


		else if (command == "Size") // Outputs the number of items in the linked list.
		{
			out << myList.size();
		}


		else if (command == "PrintList") // Output the contents of the linked list, space separated. Outputs "Empty!" if list is empty.
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
			catch (string& s) 
			{ 
				out << s;
			}
		}


		else if (command == "Append") // Inserts item or items at the end of the doubly linked list.
		{
			while (iss >> value)
			{
				myList.push_back(value);
			}
		}


		else if (command == "Drop") // Deletes the last item in the doubly linked list. Throws an error "Empty!" if linked list is empty.
		{
			try
			{
				if (myList.size() == 0)
				{
					throw string("Empty!"); 
				}
				else
				{
					myList.pop_back();
					out << "OK";
				}
			}
			catch (string& s) 
			{
				out << s;
			}
			
		}


		else if (command == "Last") // Outputs the last list item in the doubly linked list. Throws an error "Empty!" if linked list is empty.
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
			catch (string& s)
			{ 
				out << s; 
			}
		}


		else if (command == "Copy") // Makes a deep copy of the current List.
		{
			try
			{
				if (myList.size() == 0)
				{
					throw string("Empty!");
				}
				else
				{
					if (copyList.size() != 0) 
					{
						copyList.clear();
					}
					myList.copyList(copyList);
					out << "OK";
				}
			}
			catch (string& s) 
			{
				out << s; 
			}
			
		}


		else if (command == "PrintCopy") // Outputs the contents of the linked list copy. Outputs "Empty!" if list is empty.
		{
			out << copyList;
		}



		/*  Iterator Commands - Lab 4  */

		else if (command == "Iterate") // Output the contents of the linked list, one element per line, enclosed in brackets [].
		{
			try
			{
				if (myList.size() == 0)
				{
					throw string("Empty!");
				}
				else
				{
					LinkedList<string>::Iterator iter = myList.begin();
					while (iter != myList.end())				// Prints all contents of iterators on their own line in [brackets]
					{											//  i.e		[1]
						out << endl << " [" << *iter << "]";	//			[2]
						++iter;									//			[3] ...
					}
				}
			}
			catch (string& s) 
			{ 
				out << s; 
			}
		}


		else if (command == "Find") // Finds the first occurence of an item in the linked list
		{
			iss >> value;
			if (myList.size() != 0)
			{
				LinkedList<string>::Iterator position = myList.find(myList.begin(), myList.end(), value);

				if (position == NULL) 
				{
					out << "Not Found";	// If didn't find value in list (position returns NULL), outputs "Not Found"
				}	
				else 
				{ 
					out << "OK";
				}							// Otherwise outputs "OK"			(other similar if statements in following commands)
			}
		}

		else if (command == "InsertBefore") // Inserts items in the linked list before the iterator
		{
			string find_val;
			iss >> value >> find_val;
			
			LinkedList<string>::Iterator position = myList.find(myList.begin(), myList.end(), find_val);
			myList.insert(position, value);

			if (position == NULL)
			{
				out << "Not Found"; 
			}
			else 
			{ 
				out << "OK"; 
			}
		}


		else if (command == "InsertAfter") // Inserts items in the linked list after the iterator
		{
			string find_val;
			iss >> value >> find_val;

			LinkedList<string>::Iterator position = myList.find(myList.begin(), myList.end(), find_val);
			myList.insert_after(position, value);

			if (position == NULL) 
			{
				out << "Not Found";
			}
			else 
			{
				out << "OK"; 
			}
	}


		else if (command == "Erase") // Deletes the first occurrance of item in the linked list.
		{
			string find_val;
			iss >> value >> find_val;

			LinkedList<string>::Iterator position = myList.find(myList.begin(), myList.end(), value);

			if (position == NULL) 
			{
				out << "Not Found";
			}
			else 
			{ 
				myList.erase(position);
				out << "OK";
			}
		}



		else if (command == "Replace") // Replaces all matching items in the linked list with new value
		{
			string value2;
			iss >> value >> value2;

			int count = myList.replace(myList.begin(), myList.end(), value, value2);
			if (count > 0)	// Only outputs "OK" if it made any changes
			{
				out << "OK";
			}
		}
	}
	return 0;
};