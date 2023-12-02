#pragma once
#include <vector> // Dynamic Array
#include "MazeElement.h"

using namespace std;

class Maze
{
public:
	
	Maze(int Make_Height, int Make_Width); // Constructor 
	~Maze(); // Destructor
	int getHeight();
	int	getWidth();
private:
	
	int Height; 
	int Width;

};

