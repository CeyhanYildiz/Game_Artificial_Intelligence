#include "Maze.h"

// Sfml
#include <SFML/Graphics.hpp> // Window app

using namespace sf;


Maze::Maze(int Make_Height, int Make_Width, int Make_Cell) : Height(Make_Height), Width(Make_Width), Cell_Size(Make_Cell),

    window(sf::VideoMode(Make_Height, Make_Width), "MazeBot"),
    Cell(Vector2f(Make_Cell, Make_Cell))  // HIER 
{
    Cell.setFillColor(Color(140,180,255)); // HIER 
}

Maze::~Maze()
{
}

void Maze::run() {
    while (window.isOpen()) {
        handleEvents();
        update();
        render();
    }
}

int Maze::getHeight() const
{
	return Height;
}

int Maze::getWidth() const
{
	return Width;
}

void Maze::handleEvents() {
    Event event;
    while (window.pollEvent(event)) {
        if (event.type == Event::Closed)
            window.close();
    }
}

void Maze::update() {
    // Add any game logic or update code here
    for (int i = 0; i < Height; i++)
    {
        for (int j = 0; j < Width; j++) 
        {
            Cell.setPosition(((Cell_Size + 5) * i), ((Cell_Size + 5) * j));
            window.draw(Cell);
        }
    }
}

void Maze::render() {
    window.clear();
    update();
    window.display();
}



