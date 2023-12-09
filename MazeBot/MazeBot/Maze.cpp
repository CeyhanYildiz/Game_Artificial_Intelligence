// Game
#include "Maze.h"
#include "Path.h"
#include "Wall.h"
#include "OutOfBounds.h"
#include "Start.h"
#include "End.h"
#include "Checkpoint.h"
#include "WrongPath.h"

// SFML
#include <SFML/Graphics.hpp> // Window app

// C++
#include <random>
#include <iostream>
#include <windows.h>
#include <map>


// Name Space
using namespace sf;

// Make Maze
Maze::Maze(int size ,string name) : sizeMaze(size),
window(sf::VideoMode(680, 680), name),
Cell(Vector2f(43, 43)) { // 5 Sweet spot
    TrueSize = sizeMaze * 3;
    maze.resize(TrueSize + 1, vector<MazeElement*>(TrueSize + 1));
    for (int y = 0; y < TrueSize + 1; y++) {
        for (int x = 0; x < TrueSize + 1; x++) {
            if (x == 0 || x == TrueSize || y == 0 || y == TrueSize) 
            { 
                maze[x][y] = new OutOfBounds(); // Edge of the maze
            } 
            else if (y % 3 == 0 || x % 3 == 0) { maze[x][y] = new Wall(); } // Wall
            else { maze[x][y] = new Path(); } // Cell Path 
        }
    }
    // The exit positions for the maze
    // These positions are calculated to be near the bottom-right corner of the maze
    int quarter = TrueSize + 1;
    int q2 = quarter - 2;
    int q3 = quarter - 3;
    vector<pair<int, int>> endPositions = { {q2, q2}, {q2, q3}, {q3, q2}, {q3, q3} };
    for (const auto& pos : endPositions) { setMazeElement(pos.first, pos.second, new End()); } // Add End   
    vector<pair<int, int>> startPositions = { {1, 1}, {1, 2}, {2, 1}, {2, 2} };
    for (const auto& pos : startPositions) { setMazeElement(pos.first, pos.second, new Start()); } // Add Start
    //cout << "Maze has been successfully initialized" << endl<<endl; // Works
    MazeCellSize = sizeMaze * sizeMaze;
    TrueMazeSize = (TrueSize + 1) * (TrueSize + 1);

    Binary_Tree_Algorithm();
}

// Destructor Maze
Maze::~Maze()
{
    for (int x = 0; x < TrueSize + 1; x++) {
        for (int y = 0; y < TrueSize + 1; y++) { delete maze[x][y]; }
    }
}

void Maze::Binary_Tree_Algorithm()
{
    mt19937 rng(time(NULL)); // Create a random number generator, Mersenne primes
    uniform_int_distribution<int> dist(1, 2); // Distribute between 1 and 2
    for (int col = 0; col < sizeMaze; col++) {
        for (int row = 0; row < sizeMaze; row++) {
            int randomNumber = dist(rng); // Generate a random number (1 or 2)
            // Calculate common positions
            int posX = col * 3;
            int posY = row * 3;
            if (randomNumber == 2) {
                // Decision to remove left or up wall based on boundary conditions
                if (getMazeElementSymbol(posX + 1, posY) == 'X') { removeLeftWall(posX, posY); }
                else { removeUpWall(posX, posY); }
            }
            else {
                // Similar decision as above
                if (getMazeElementSymbol(posX, posY + 1) == 'X') { removeUpWall(posX, posY); }
                else { removeLeftWall(posX, posY); }
            }
            // Loading time or AKA wasting time
            //handleEvents();
            //update();
            //render();
            //Sleep(1000);
        }
    }
}

void Maze::handleEvents() {
    Event event;
    while (window.pollEvent(event)) {
        if (event.type == Event::Closed)
            window.close();
    }
}
void Maze::update() {

    printMaze();

}
void Maze::render() {
    window.clear();
    update();
    window.display();
}

void Maze::run() {

    while (window.isOpen()) {
        handleEvents();
        update();
        render();

    }
}


// Edit MazeElements
void Maze::setMazeElement(int y, int x, MazeElement* newElement)
{
    if (x >= 0 && x < maze.size() && y >= 0 && y < maze[x].size()) {
        // Check if the current element is OutOfBounds or Start
        if (dynamic_cast<OutOfBounds*>(maze[x][y]) == nullptr &&
            dynamic_cast<Start*>(maze[x][y]) == nullptr &&
            dynamic_cast<End*>(maze[x][y]) == nullptr) {
            delete maze[x][y]; // Delete the old element
            maze[x][y] = newElement;
        } // Set the new element
    }
}

void Maze::setMazeElement_Visited(int y, int x)
{
    if (x >= 0 && x < maze.size() && y >= 0 && y < maze[x].size()) {

        if (dynamic_cast<Path*>(maze[x][y]) != nullptr)
        {
            delete maze[x][y];
            maze[x][y] = new Checkpoint();
        }
    }
}

void Maze::setMazeElement_WrongTurn(int y, int x)
{
    if (x >= 0 && x < maze.size() && y >= 0 && y < maze[x].size()) {

        if (dynamic_cast<WrongPath*>(maze[x][y]) != nullptr)
        {
            delete maze[x][y];
            maze[x][y] = new WrongPath();
        }
    }
}

void Maze::removeLeftWall(int x, int y)
{
    setMazeElement(x, y + 1, new Path());
    setMazeElement(x, y + 2, new Path());
}
void Maze::removeUpWall(int x, int y)
{
    setMazeElement(x + 1, y, new Path());
    setMazeElement(x + 2, y, new Path());
}

// Get info
char Maze::getMazeElementSymbol(int x, int y)
{
    return maze[y][x]->getSymbol();
}

string Maze::getMazeElementDescription(int x, int y)
{
    return maze[y][x]->getDescription();
}

// Print
void Maze::printMaze()
{
    for (int y = 0; y < TrueSize + 1; y++) {
        for (int x = 0; x < TrueSize + 1; x++) {

            Cell.setPosition((43 * x), (43 * y)); // 5 sweet spot
            printBlockSymbol(*maze[x][y]);
        }
    }
}
void Maze::printMazeElement(int x, int y)
{

    if (x >= 0 && x < maze.size() && y >= 0 && y < maze[x].size())
    {
        printBlockSymbol(*maze[x][y]);
    }
    else
    {
    }
}

void Maze::printBlockSymbol(const MazeElement& element)
{
    map<char, Color> symbolToColor = {
        {'P', Color(200, 200, 200)},
        {'W', Color(110, 110, 110)},
        {'C', Color(0, 0, 200)},
        {'S', Color(0, 200, 0)},
        {'E', Color(200, 0, 0)},
        {'w', Color(255, 127, 80)},
        {'X', Color(110, 110, 110)}
    };

    char symbol = element.getSymbol();
    Color fillColor = symbolToColor.count(symbol) ? symbolToColor[symbol] : Color(255, 255, 255);

    Cell.setFillColor(fillColor);
    window.draw(Cell);
    Cell.setOutlineThickness(0.f);
}

