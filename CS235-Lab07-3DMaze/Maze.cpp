#include "Maze.h"
#include <iostream>

// CONSTRUCTORS/DECONSTRUCTORS
// ============

/* Create Maze 3D-Array */
Maze::Maze(int depth, int height, int width) 
{
	mazeDepth = depth;
	mazeHeight = height;
	mazeWidth = width;

	maze = new int** [depth];
	for (int i = 0; i < depth; ++i)
	{
		maze[i] = new int* [height];
		for (int j = 0; j < height; ++j)
		{
			maze[i][j] = new int[width];
		}
	}
}

/* Deallocate Maze Array */
Maze::~Maze() 
{
	for (int i = 0; i < mazeDepth; i++)
	{
		for (int j = 0; j < mazeHeight; j++)
		{
			delete[] maze[i][j];
		}
		delete[] maze[i];
	}
	delete[] maze;
}


// FUNCTIONS
// ==========

/* findPath - Recursive function that determines if the maze is solvable,
	and if so will modify the array to map out the solution */
bool Maze::findPath(int height, int width, int layer)
{
	if (height < 0 || height > mazeHeight - 1 || layer < 0 || layer > mazeDepth - 1 || width < 0 || width > mazeWidth - 1)
	{
		return false;
	}

	if (maze[layer][height][width] == exit)
	{
		mazeComplete = true;
		return true;
	}

	if (maze[layer][height][width] != open)
	{
		return false;
	}

	maze[layer][height][width] = visited;

	if (findPath(height, width - 1, layer)) // LEFT
	{
		if (mazeComplete) 
			maze[layer][height][width] = left;
		return true;
	}
	else if (findPath(height, width + 1, layer)) // RIGHT
	{
		if (mazeComplete) 
			maze[layer][height][width] = right;
		return true;
	}
	else if (findPath(height - 1, width, layer)) // UP
	{
		if (mazeComplete) 
			maze[layer][height][width] = up;
		return true;
	}
	else if (findPath(height + 1, width, layer)) // DOWN
	{
		if (mazeComplete) 
			maze[layer][height][width] = down;
		return true;
	}
	else if (findPath(height, width, layer - 1)) // OUT
	{
		if (mazeComplete) 
			maze[layer][height][width] = outLayer;
		return true;
	}
	else if (findPath(height, width, layer + 1)) // IN
	{
		if (mazeComplete) 
			maze[layer][height][width] = inLayer;
		return true;
	}
	else
	{
		return false;
	}
}

/* toString - Outputs the maze in 2D layers, along with the solution */
std::string Maze::toString() const
{
	std::stringstream out;

	// Print the maze with X and _ format
	out << "Solve Maze:" << std::endl;
	for (int i = 0; i < mazeDepth; ++i)
	{
		out << "Layer " << i + 1 << std::endl;

		for (int j = 0; j < mazeHeight; ++j)
		{
			for (int k = 0; k < mazeWidth; ++k)
			{
				char output;
				if (maze[i][j][k] == 1) output = 'X';
				else output = '_';
				out << " " << output;
			}
			out << std::endl;
		}
	}


	// Prints the maze solution
	if (!mazeComplete) out << std::endl << "No Solution Exists!";
	else
	{
		out << std::endl << "Solution:" << std::endl;
		for (int i = 0; i < mazeDepth; ++i)
		{
			out << "Layer " << i + 1 << std::endl;

			for (int j = 0; j < mazeHeight; ++j)
			{
				for (int k = 0; k < mazeWidth; ++k)
				{
					std::string output = "";
				
					if (maze[i][j][k] == open) output = '_';
					else if (maze[i][j][k] == blocked) output = 'X';
					else if (maze[i][j][k] == visited) output = '*';
					else if (maze[i][j][k] == exit) output = 'E';
					else if (maze[i][j][k] == left) output = 'L';
					else if (maze[i][j][k] == right) output = 'R';
					else if (maze[i][j][k] == up) output = 'U';
					else if (maze[i][j][k] == down) output = 'D';
					else if (maze[i][j][k] == outLayer) output = 'O';
					else if (maze[i][j][k] == inLayer) output = 'I';
					else output = "?";

					out << " " << output;
				}
				out << std::endl;
			}
		}
	}


	return out.str();
}
