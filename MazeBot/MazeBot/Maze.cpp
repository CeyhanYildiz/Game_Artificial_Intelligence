// Game
#include "Maze.h"
#include "Path.h"
#include "Wall.h"
#include "OutOfBounds.h"
// Sfml
#include <SFML/Graphics.hpp> // Window app

//C++
#include <random>
#include "Start.h"
#include "End.h"
#include <iostream>
#include<windows.h>
#include <unordered_map>


using namespace sf;

// Make Maze
Maze::Maze(int size) : sizeMaze(size) , 
    window(sf::VideoMode(680, 680), "MazeBot"),
    Cell(Vector2f(43, 43)) { // 5 Sweet spot
    TrueSize = sizeMaze * 3;
    maze.resize(TrueSize + 1, vector<MazeElement*>(TrueSize + 1));
    for (int y = 0; y < TrueSize + 1; y++) {
        for (int x = 0; x < TrueSize + 1; x++) {
            if (x == 0 || x == TrueSize || y == 0 || y == TrueSize) { maze[x][y] = new OutOfBounds(); } // Edge of the maze
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
    
}

// Destruckt Maze
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
            
        }
        // Loading time or AKA wasting time
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
    
    printMaze();

}
void Maze::render() {
    window.clear();
    update();
    window.display();
}

void Maze::run() {

    Binary_Tree_Algorithm();

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
    unordered_map<char, Color> symbolToColor = {
        {'P', sf::Color(200, 200, 200)},
        {'W', sf::Color(110, 110, 110)},
        {'C', sf::Color(0, 0, 200)},
        {'S', sf::Color(0, 200, 0)},
        {'E', sf::Color(200, 0, 0)},
        {'w', sf::Color(255, 127, 80)},
        {'X', sf::Color(110, 110, 110)}
    };

    char symbol = element.getSymbol();
    Color fillColor = symbolToColor.count(symbol) ? symbolToColor[symbol] : Color(255, 255, 255);

    Cell.setFillColor(fillColor);
    window.draw(Cell);
    Cell.setOutlineThickness(0.f);
}