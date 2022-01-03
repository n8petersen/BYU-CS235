#include <iostream>
#include <fstream>
#include <sstream>

#include "BST.h"

using namespace std;

#ifdef _MSC_VER // Memory leak check
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK
#endif

int main(int argc, char* argv[])
{
	VS_MEM_CHECK               // Enable memory leak check

	if (argc < 3) // Checks if file names were set
	{
		std::cerr << "Please provide name of input and output files";
		return 1;
	}
	std::ifstream in(argv[1]); // Reading input file
	if (!in)
	{
		std::cerr << "Unable to open " << argv[1] << " for input";
		return 2;
	}
	else
	{
		std::cout << argv[1] << " opened successfully.\n";
	}
	std::ofstream out(argv[2]); // Reading output file
	if (!out)
	{
		in.close();
		std::cerr << "Unable to open " << argv[2] << " for output";
		return 3;
	}
	else
	{
		std::cout << argv[2] << " opened successfully.\n";
	}

	
	//\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\//
	//						Main program begins here    
	//\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\//

	string line;

	BST<int> bstInt;
	BST<int> bstIntCopy;
	BST<string> bstString;
	BST<string> bstStringCopy;
	enum TreeType { none, integerTree, stringTree };
	int currentTree = none;

	while (getline(in, line))
	{
		string command, value;

		if (line.size() == 0) continue; // If the line is empty, goes to next line.
		out << line << " "; // Outputs the input line
		istringstream iss(line);
		iss >> command >> value; // breaks up line into command and value


		try
		{
			if (command == "INT")
			{
				currentTree = integerTree;
				out << "OK";
			}
			else if (command == "STRING")
			{
				currentTree = stringTree;
				out << "OK";
			}


			/* Int Tree Commands */
			else if (currentTree == integerTree) // Checks if the current tree is Int or String
			{
				if (command == "add")
				{
					if (bstInt.addNode(stoi(value))) 
					{
						out << "OK"; 
					}
					else 
					{
						out << "Error"; 
					}
				}


				else if (command == "remove")
				{
					if (bstInt.removeNode(stoi(value))) 
					{
						out << "OK"; 
					}
					else 
					{
						out << "Error"; 
					}
				}


				else if (command == "clear")
				{
					if (bstInt.clearTree()) 
					{
						out << "OK"; 
					}
					else 
					{
						out << "Error"; 
					}
				}


				else if (command == "size")
				{
					out << bstInt.sizeTree();
				}


				else if (command == "print")
				{
					out << bstInt;
				}


				else if (command == "find")
				{
					if (bstInt.find(stoi(value))) 
					{
						out << "found"; 
					}
					else 
					{
						out << "not found";
					}
				}


				else if (command == "copy")
				{
					if (bstInt.sizeTree() != 0)
					{
						bstIntCopy = bstInt; // Uses Deep Assignment Operator
						out << "OK"; 
					}
					else 
					{
						out << "Error"; 
					}
				}


				else if (command == "printcopy")
				{
					out << bstIntCopy;
				}


				else if (command == "tree")
				{
					BST<int>::Iterator iter = bstInt.begin();
					BST<int>::Iterator end_iter = bstInt.end();
					if (iter == end_iter)
					{
						out << "empty";
					}
					for (; iter != end_iter; ++iter)
					{
						out << " " << *iter;
					}
				}


				else 
				{
					throw string("Error"); // If unknown INT command is entered throw "Error:
				}
			}



			/* String Tree Commands */
			else if (currentTree == stringTree)
			{
				if (command == "add")
				{
					if (bstString.addNode(value)) 
					{
						out << "OK"; 
					}
					else 
					{
						out << "Error"; 
					}
				}


				else if (command == "remove")
				{
					if (bstString.removeNode(value)) 
					{
						out << "OK"; 
					}
					else 
					{
						out << "Error";
					}
				}


				else if (command == "clear")
				{
					if (bstString.clearTree()) 
					{
						out << "OK"; 
					}
					else 
					{
						out << "Error"; 
					}
				}


				else if (command == "size")
				{
					out << bstString.sizeTree();
				}


				else if (command == "print")
				{
					out << bstString;
				}


				else if (command == "find")
				{
					if (bstString.find(value)) 
					{
						out << "found"; 
					}
					else 
					{
						out << "not found";
					}
				}


				else if (command == "copy")
				{
					if (bstString.sizeTree() != 0)
					{
						bstStringCopy = bstString; // Uses Deep Assignment Operator
						out << "OK";
					}
					else 
					{
						out << "Error";
					}
				}


				else if (command == "printcopy")
				{
					out << bstStringCopy;
				}


				else if (command == "tree")
				{
					BST<string>::Iterator iter = bstString.begin();
					BST<string>::Iterator end_iter = bstString.end();
					if (iter == end_iter)
					{
						out << "empty";
					}
					for (; iter != end_iter; ++iter)
					{
						out << " " << *iter;
					}

				}
				else 
				{
					throw string("Error");// If unknown STRING command is entered throw "Error:
				}
			}

			else 
			{ 
				throw string("Error"); // If unknown command is entered throw "Error:
			}
			
		}
		catch (std::string& error) 
		{
			out << error; 
		}

		out << endl; // Ends line to start next line
	}
}