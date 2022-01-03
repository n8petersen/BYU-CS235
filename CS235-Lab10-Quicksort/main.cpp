#include <iostream>
#include <fstream>
#include <sstream>

#include "Quicksort.h"

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

	Quicksort<int> quicksort;

	std::string line;
	while (getline(in, line))
	{
		std::string command;

		try
		{
			if (line.size() == 0) continue;
			std::istringstream iss(line);
			iss >> command;
			out << command << " ";


			if (command == "QuickSort")
			{
				size_t value = 0;
				iss >> value;
				quicksort.setSize(value);
				out << value << " OK";
			}
			

			else if (command == "AddToArray")
			{
				string adding;
				int value = 0;
				while (iss >> value)
				{
					if (!quicksort.addElement(value))
					{
						throw string("Error");
						break;
					}
					adding = adding + to_string(value) + ",";
				}
				adding = adding.substr(0, adding.length() - 1);
				
				out << " " << adding << " OK";
			}


			else if (command == "Capacity")
			{
				out << quicksort.capacity();
			}


			else if (command == "Clear")
			{
				quicksort.clear();
				out << "OK";
			}


			else if (command == "Size")
			{
				out << quicksort.size();
			}


			else if (command == "Sort")
			{
				size_t left = 0, right = 0;
				iss >> left >> right;

				quicksort.resetCounters();
				if (quicksort.sort(left, right))
				{
					out << left << "," << right << " OK";
				}
				else
				{
					throw string("Error");
				}
			}


			else if (command == "SortAll")
			{
				quicksort.resetCounters();
				if (quicksort.sortAll())
				{
					out << "OK";
				}
				else
				{
					throw string("Error");
				}
			}


			else if (command == "MedianOfThree")
			{
				int left = 0, right = 0;
				iss >> left >> right;

				out << left << "," << right << " = ";

				if (!quicksort.checkConditions(left, right))
				{
					out << "-1";
				}

				else
				{
					out << quicksort.medianOfThree(left, right);
				}
			}


			else if (command == "Partition")
			{
				int left = 0, right = 0, pivot = 0;
				iss >> left >> right >> pivot;

				out << left << "," << right << "," << pivot << " = ";
				if (!quicksort.checkConditions(left, right, pivot))
				{
					out << "-1";
				}

				else
				{
					out << quicksort.partition(left, right, pivot);
				}
			}


			else if (command == "PrintArray")
			{
				if (quicksort.size() == 0)
				{
					out << "Empty";
				}
				else
				{
					out << quicksort;
				}
			}


			else if (command == "Stats")
			{
				out << quicksort.stats();
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