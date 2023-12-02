#include "Maze.h"

// Sfml
#include <SFML/Graphics.hpp> // Window app

using namespace sf;

Maze::Maze(int Make_Height, int Make_Width) : Height(Make_Height), Width(Make_Width)
{
}

Maze::~Maze()
{
}

int Maze::getHeight()
{
	return Height;
}

int Maze::getWidth()
{
	return Width;
}


