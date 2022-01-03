#include <iostream>
#include <sstream>
#include <fstream>

#include "Maze.h"


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


	// Gets dimensions of the maze
	int depth = 0, height = 0, width = 0;
	std::string line;
	getline(in, line);
	std::istringstream iss(line);
	iss >> height >> width >> depth;
	
	Maze maze(depth, height, width); // Create instance of Maze

	// Sets up the maze based off the input file
	// NOTE: depth -> i, height -> j, width -> k
	for (int i = 0; i < depth; i++)
	{
		for (int j = 0; j < height; j++)
		{
			std::string setInt;
			getline(in, line); // Grabs the next row of the maze
			if (line == "") getline(in, line); // If the line is blank, grab the next line

			for (int k = 0; k < width; k++)
			{
				setInt = line.substr(0, 1); // Parses the row
				if (line.size() != 1) line = line.substr(2, line.size()); // Only substring when not last item
				maze.setValue(j, k, i, std::stoi(setInt)); // Inputs the fetched value into the maze array
			}
		}
	}

	maze.find_maze_path();

	out << maze;

	return 0;
}
