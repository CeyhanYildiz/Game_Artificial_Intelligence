#pragma once

// SFML
#include <SFML/Graphics.hpp>

//C++

// BaseClass
#include "MazeElement.h"

using namespace std;
using namespace sf;

class Maze
{
public:
	
	Maze(int size); // Constructor 
	~Maze(); // Destructor

	void run();

	int getHeight() const;
	int	getWidth() const;

	// Gets Symbool
	char getMazeElementSymbol(int x, int y);
	// Gets Description
	string getMazeElementDescription(int x, int y);

	void Binary_Tree_Algorithm();

	void printMazeElement(int x, int y);

	void printMaze();

private:
	
	void handleEvents();
	void update();
	void render();

	RenderWindow window; // Game API

	RectangleShape Cell;
	 
	int Height; 
	int Width;

	// Maze Size
	int sizeMaze;
	// How much Cells are in the maze
	int MazeCellSize;
	// True maze size 'arrey'
	int TrueMazeSize;
	// Caculation x * 3
	int TrueSize;
	// Kinda dubbel linklist
	vector<vector<MazeElement*>> maze;

	// Removes the left wall at the specified position
	void removeLeftWall(int x, int y);

	// Removes the up wall at the specified position
	void removeUpWall(int x, int y);

	void setMazeElement(int y, int x, MazeElement* newElement);

	void printBlockSymbol(const MazeElement& element);

};

