#ifndef MAZE_H
#define MAZE_H

#include "MazeInterface.h"
#include <sstream>
//#include <string>

class Maze :
    public MazeInterface
{
private:
	int mazeHeight, mazeWidth, mazeDepth;
	bool mazeComplete = false; // Boolean that is set to true once the maze is solved
	

public:
	Maze(int depth, int height, int width);
	~Maze();

	enum CellType { open, blocked, visited, exit, left, right, up, down, outLayer, inLayer };
	int*** maze;

	/* Sets a specific value in the maze 3D-array */
	void setValue(int height, int width, int layer, int value)
	{
		maze[layer][height][width] = value;
	}

	//int getValue(int height, int width, int layer) { return maze[layer][height][width]; }

	/* Starter function to kick off the recursion. */
	bool find_maze_path()
	{
		mazeComplete = false; // Sets the maze to incomplete
		setValue(mazeHeight - 1, mazeWidth - 1, mazeDepth - 1, exit); // Sets the bottom right value to exit
		return findPath(0, 0, 0);  // Starts recursive function to solve the maze
	}
	
	/* Recursive function to find the exit of the maze */
	bool findPath(int height, int width, int layer);

	/* Outputs the maze in 2D layers, along with the solution */
	std::string toString() const;

	friend std::ostream& operator<<(std::ostream& os, Maze& rtn) { return os << rtn.toString(); }
};

#endif //MAZE_H