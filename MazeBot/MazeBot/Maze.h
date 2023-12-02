#pragma once
#include <SFML/Graphics.hpp>

#include <vector> // Dynamic Array

#include "MazeElement.h"

using namespace std;
using namespace sf;

class Maze
{
public:
	
	Maze(int Make_Height, int Make_Width, int Make_Cell); // Constructor 
	~Maze(); // Destructor

	void run();

	int getHeight() const;
	int	getWidth() const;
private:
	
	void handleEvents();
	void update();
	void render();

	RenderWindow window; // Game API

	RectangleShape Cell; // HIER 
	 
	int Height; 
	int Width;
	int Cell_Size;

};

