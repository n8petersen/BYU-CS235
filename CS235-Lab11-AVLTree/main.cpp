#include <iostream>
#include <fstream>
#include "AVL.h"

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

	// MAIN PROGRAM STARTS HERE \/\/\/\/\/\/\/\/\/\/\/\/\//

	string line;

	AVL<int> avlInt;
	AVL<string> avlString;
	enum TreeType { none, integerTree, stringTree };
	int currentTree = none;

	while (getline(in, line))
	{
		std::string command;

		try
		{
			string command;

			if (line.size() == 0) continue; // If the line is empty, goes to next line.
			out << line; // Outputs the input line
			istringstream iss(line);
			iss >> command; // breaks up line into command and value


			if (command == "INT")
			{
				currentTree = integerTree;
				out << " true";
			}
			else if (command == "STRING")
			{
				currentTree = stringTree;
				out << " true";
			}


			/* INT Tree Commands */
			else if (currentTree == integerTree) // Checks if the current tree is Int or String
			{
				int value;
				iss >> value;
				if (command == "add")
				{
					if (avlInt.addNode(value))
					{
						out << " true";
					}
					else
					{
						out << " false";
					}
				}

				else if (command == "remove")
				{
					if (avlInt.removeNode(value))
					{
						out << " true";
					}
					else
					{
						out << " false";
					}
				}

				else if (command == "clear")
				{
					if (avlInt.clearTree())
					{
						out << " true";
					}
					else
					{
						out << " false";
					}
				}

				else if (command == "size")
				{
					out << avlInt.sizeTree();
				}

				else if (command == "print")
				{
					out << ":" << avlInt;
				}

				else if (command == "find")
				{
					if (avlInt.find(value))
					{
						out << "found";
					}
					else
					{
						out << "not found";
					}
				}

				else
				{
					throw string("Error");// If unknown INT command is entered throw "Error:
				}
			}


			/* STRING Tree Commands */
			else if (currentTree == stringTree)
			{
				string value;
				iss >> value;
				if (command == "add")
				{
					if (avlString.addNode(value))
					{
						out << " true";
					}
					else
					{
						out << " false";
					}
				}

				else if (command == "remove")
				{
					if (avlString.removeNode(value))
					{
						out << " true";
					}
					else
					{
						out << " false";
					}
				}

				else if (command == "clear")
				{
					if (avlString.clearTree())
					{
						out << " true";
					}
					else
					{
						out << " false";
					}
				}

				else if (command == "size")
				{
					out << avlString.sizeTree();
				}

				else if (command == "print")
				{
					out << ":" << avlString;
				}

				else if (command == "find")
				{
					if (avlString.find(value))
					{
						out << "found";
					}
					else
					{
						out << "not found";
					}
				}

				else
				{
					throw string("Error");// If unknown INT command is entered throw "Error:
				}
			}


			else
			{
				throw string("Error"); // If unknown command is entered throw "Error:
			}


			out << endl;
		}

		catch (std::string& error)
		{
			out << error << endl;
		}
	}

	return 0;
}