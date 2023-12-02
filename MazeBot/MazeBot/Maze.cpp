// Game
#include "Maze.h"
#include "Path.h"
#include "Wall.h"
#include "OutOfBounds.h"
// Sfml
#include <SFML/Graphics.hpp> // Window app

//C++
#include <random>

using namespace sf;


Maze::Maze(int Make_Height, int Make_Width, int Make_Cell_X, int Make_Cell_Y) : 
    Height(Make_Height), 
    Width(Make_Width), 
    Cell_Size_X(Make_Cell_X), 
    Cell_Size_Y(Make_Cell_Y),

    window(sf::VideoMode(Make_Height, Make_Width), "MazeBot"),
    Cell(Vector2f(20, 20))
{
    maze.resize(((Cell_Size_X * 3) + 1), vector<MazeElement*>(((Cell_Size_X * 3) + 1))); // CAN GO WRONG change X and Y
    for (int x = 0; x < ((Cell_Size_X * 3) + 1) + 1; x++) {
        for (int y = 0; y < ((Cell_Size_X * 3) + 1) + 1; y++) {
            if (x == 0 || x == ((Cell_Size_X * 3) + 1) || y == 0 || y == ((Cell_Size_X * 3) + 1)) 
            { 
                maze[x][y] = new OutOfBounds(); // Edge of the maze
            } 
            else if (y % 3 == 0 || x % 3 == 0) 
            { 
                maze[x][y] = new Wall(); // Wall
            } 
            else { 
                maze[x][y] = new Path(); // Cell Path 
            } 
        }
    }
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
    
        // Simple Display Maze Befor Random
        for (int i = 0; i < ((Cell_Size_X * 3) + 1); i++)
        {
            for (int j = 0; j < ((Cell_Size_Y * 3) + 1); j++)
            {
                if (i % 3 == 0 || j % 3 == 0)
                {
                    Cell.setFillColor(Color(255, 180, 50));
                }
                else if ((i == 1 || i == 2) && (j == 1 || j == 2))
                {
                    Cell.setFillColor(Color(0, 255, 0));
                }
                else if ((i == 91 || i == 92) && (j == 46 || j == 47))
                {
                    Cell.setFillColor(Color(255, 0, 0));
                }
                else
                {
                    Cell.setFillColor(Color(140, 180, 255));
                }
                Cell.setPosition((15 + 0) * i, (15 + 0) * j);
                window.draw(Cell);
            }
        }    

        random_device rd; 
        mt19937 gen(rd()); 
        uniform_int_distribution<> distribution(0, 1); 

}

void Maze::render() {
    window.clear();
    update();
    window.display();
}



