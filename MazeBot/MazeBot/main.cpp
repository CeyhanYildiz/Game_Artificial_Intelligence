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
#include "TestGame.h"

// shortCuts
using namespace sf;
using namespace std;

int main() {
    Maze game(1440,740,20);
    game.run();  // WHILE LOOP !!

    return 0;
}