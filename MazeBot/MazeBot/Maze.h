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
	
	Maze(int Make_Height, int Make_Width, int Make_Cell_X, int Make_Cell_Y); // Constructor 
	~Maze(); // Destructor

	void run();

	int getHeight() const;
	int	getWidth() const;
private:
	
	void handleEvents();
	void update();
	void render();

	RenderWindow window; // Game API

	RectangleShape Cell;
	 
	int Height; 
	int Width;
	int Cell_Size_X;
	int Cell_Size_Y;

	// Kinda dubbel linklist
	vector<vector<MazeElement*>> maze;
};

