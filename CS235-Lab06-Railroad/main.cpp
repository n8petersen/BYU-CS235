#include <iostream>
#include <sstream>
#include <fstream>

#include "Station.h"

#ifdef _MSC_VER // Memory leak check
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK
#endif

int main(int argc, char* argv[])
{
	// Enable memory leak check
	VS_MEM_CHECK

	/* Read input / output files */
	std::ifstream in(argv[1]);
	std::ofstream out(argv[2]);
	if (argc < 3) // Checks if file names were set
	{
		std::cerr << "Please provide name of input and output files";
		return 1;
	}
	if (!in)
	{
		std::cerr << "Unable to open " << argv[1] << " for input";
		return 2;
	}
	else
	{
		std::cout << argv[1] << " opened successfully.\n";
	}
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


	std::string line;
	Station<Car> station;
	
	// Process inputs
	while (getline(in, line))
	{
		std::string command = "", object = "", dataString = "";
		int dataInt = -1;
		try
		{
			if (line.size() == 0) continue;
			out << line << " ";
			std::istringstream iss(line);

			// Breaks up '<command>:<object> <data>'
			iss >> command >> dataString;
			if (dataString != "") dataInt = std::stoi(dataString); // If not blank, Converts dataString to dataInt
			object = command.substr(command.find(':') + 1, command.find(' ' - 1));
			command = command.substr(0, command.find(':'));

			if (command == "Add")
			{
				if (object == "station")	// Add new car to turntable
				{	
					Car car(dataInt);
					out << station.addCar(car);	
				}

				else if (object == "queue")		// Move car from turntable to queue
				{
					out << station.addQueue();
				}

				else if (object == "stack")		// Move car from turntable to stack
				{
					out << station.addStack();
				}
			}

			else if (command == "Remove")
			{
				if (object == "station")	// Move car from turntable to vector
				{
					out << station.removeCar();
				}

				else if (object == "queue")		// Move car from queue to turntable
				{
					out << station.removeQueue();
				}

				else if (object == "stack")		// Move car from stack to turntable
				{
					out << station.removeStack();
				}
			}

			else if (command == "Top")
			{
				if (object == "station")	// Display car on the turtable
				{
					out << station.topCar();
				}

				else if (object == "queue")		// Display car at head of queue
				{
					out << station.topQueue();
				}

				else if (object == "stack")		// Display car at head of stack
				{
					out << station.topStack();
				}
			}

			else if (command == "Size")
			{
				if (object == "queue")		// Output number of cars in queue
				{
					out << station.sizeQueue();
				}

				else if (object == "stack")		// Output number of cars in stack
				{
					out << station.sizeStack();
				}
				else if (object == "train")		// Output number of cars in stack
				{
					out << station.sizeTrain();
				}
			}

			else if (command == "Queue")
			{
				out << station.printQueue();
			}

			else if (command == "Stack")
			{
				out << station.printStack();
			}

			else if (command == "Train") // Output all train cars on vector
			{
				out << station;
			}

			else if (command == "Find")		// Find location of car 
			{
				Car car(dataInt);
				out << station.find(car);
			}

			else
			{
				throw std::string("Unexpected command!");
			}
		}

		catch (std::string& error) { out << error; }

		out << std::endl;
	}
	

	return 0;
}