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

	// Construct & Destructor
	Maze(int size);
	~Maze();

	// Start Game
	void run();

	// Get info
	int getHeight() const { return Height; };
	int	getWidth() const { return Width; };
	//Gets Symbool
	char getMazeElementSymbol(int x, int y);
	// Gets Description
	string getMazeElementDescription(int x, int y);

private:

	// Called 1 time
	void Binary_Tree_Algorithm();

	// Only Run can call
	void printMaze();
	void printMazeElement(int x, int y);
	void handleEvents();
	void update();
	void render();
	void printBlockSymbol(const MazeElement& element);

	// Game API window
	RenderWindow window;

	// For printing API
	RectangleShape Cell;

	// Info Maze
	int Height;
	int Width;

	// Maze Size
	int sizeMaze;
	// How much Cells are in the maze
	int MazeCellSize;
	// True maze size ' array '
	int TrueMazeSize;
	// Calculation x * 3
	int TrueSize;
	// Kind a dubbel linklist
	vector<vector<MazeElement*>> maze;

	// Admin level Edit Maze 
	void removeLeftWall(int x, int y);
	void removeUpWall(int x, int y);
	void setMazeElement(int y, int x, MazeElement* newElement);

protected:

	// User level Edit Maze
	void setMazeElement_Visited(int y, int x);
	void setMazeElement_WrongTurn(int y, int x);
};

