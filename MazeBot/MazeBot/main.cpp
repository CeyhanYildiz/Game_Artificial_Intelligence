// Sfml
#include <SFML/Graphics.hpp> // Window app

// C++
#include <iostream> //Standard Input/Output Streams
#include <vector> // Dynamic Array
#include <string> //String Class 

#include <ctime>   // Time Functions 
#include <random> // Include for modern random number generation

// Cell Element
#include "Checkpoint.h"
#include "End.h" 
#include "MazeElement.h"    
#include "OutOfBounds.h"
#include "Path.h"
#include "Start.h"
#include "Wall.h"   
#include "WrongPath.h"      

// Main Game
#include "Maze.h"

// shortCuts
using namespace sf;
using namespace std;

int main()
{
    Maze maze(1440, 740);
    RenderWindow window(VideoMode(maze.getHeight(), maze.getWidth()), "MazeBot");

    while (window.isOpen())
    {
        Event event; 
        while (window.pollEvent(event)) 
        {
            if (event.type == Event::Closed) 
                window.close(); 
        }

        window.clear(); 
        // Maze Start

        int CELL_SIZE = 20; // Cell Size
        int COLUMNS = 1440 / CELL_SIZE; // X
        int ROWS = 740 / CELL_SIZE; // Y
        RectangleShape Cell(Vector2f(CELL_SIZE - 5, CELL_SIZE - 5));
        Cell.setFillColor(Color(146, 182, 255));
        for (int a = 0; a < COLUMNS; a++)
        {
            for (int b = 0; b < ROWS; b++)
            {
                Cell.setPosition(CELL_SIZE * a, CELL_SIZE * b);
                window.draw(Cell);
            }
        }
        // Maze End
        window.display();
    }
    return 0;
}