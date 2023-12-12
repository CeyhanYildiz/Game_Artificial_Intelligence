// SFML
#include <SFML/Graphics.hpp> // Window app

// C++
#include <random>
#include <iostream>
#include <windows.h>
#include <map>

// Game
#include "Maze.h"
#include "Path.h"
#include "Wall.h"
#include "OutOfBounds.h"
#include "Start.h"
#include "End.h"
#include "Checkpoint.h"
#include "WrongPath.h"

// Name Space
using namespace sf;

// Make Maze
Maze::Maze(int size, int Cell_Size, string name) :
	sizeMaze(size),
	Cell_Size(Cell_Size),
	window(sf::VideoMode(902, 902), name),
	Cell(Vector2f(Cell_Size, Cell_Size))
{
	// Constructor for the Maze class with initialization list.

	// Calculations
	TrueSize = sizeMaze * 3;
	int quarter = TrueSize + 1;
	int q2 = quarter - 2;
	int q3 = quarter - 3;
	MazeCellSize = sizeMaze * sizeMaze;
	TrueMazeSize = (TrueSize + 1) * (TrueSize + 1);

	// Vector
	maze.resize(TrueSize + 1, vector<MazeElement*>(TrueSize + 1));

	// Making Grid
	ConstructMaze();

	// Lambda function to add Start or End elements
	auto addElements = [this](const vector<pair<int, int>>& positions, MazeElement* element) {
		for (const auto& pos : positions) {
			setMazeElement(pos.first, pos.second, element);
		}
		};

	// Adding Start
	addElements({ {1, 1}, {1, 2}, {2, 1}, {2, 2} }, new Start());

	// Adding End
	addElements({ {q2, q2}, {q2, q3}, {q3, q2}, {q3, q3} }, new End());

	// Grid to Maze
	Binary_Tree_Algorithm();
}

// Destructor Maze
Maze::~Maze() {
	// Destructor for the Maze class, responsible for freeing allocated memory.

	for (int x = 0; x < TrueSize + 1; x++) {
		for (int y = 0; y < TrueSize + 1; y++) { delete maze[x][y]; }
	}
}

void Maze::ConstructMaze() {
	/* Constructing a Vector
	* Creating the following pattern:
	*   O | O | O | O | O | O | O
	*   O | P | P | W | P | P | O
	*   O | P | P | W | P | P | O
	*   O | W | W | W | W | W | O
	*   O | P | P | W | P | P | O
	*   O | P | P | W | P | P | O
	*   O | O | O | O | O | O | O
	*/

	for (int y = 0; y < TrueSize + 1; y++) {
		for (int x = 0; x < TrueSize + 1; x++) {
			// Assigning 'OutOfBounds' to the maze boundaries
			if (x == 0 || x == TrueSize || y == 0 || y == TrueSize) {
				maze[x][y] = new OutOfBounds();
			}
			// Placing 'Wall' on specified coordinates within the maze
			else if (y % 3 == 0 || x % 3 == 0) {
				maze[x][y] = new Wall();
			}
			// Designating 'Path' to the cells within the maze
			else {
				maze[x][y] = new Path();
			}
		}
	}
}

void Maze::Binary_Tree_Algorithm() {
	// Implement the Binary Tree Algorithm to generate a maze.
	// Utilizes randomization to remove either the West or North wall for each cell.

	mt19937 rng(time(NULL)); // Create a random number generator, Mersenne primes
	uniform_int_distribution<int> dist(1, 2); // Distribute between 1 and 2
	for (int col = 0; col < sizeMaze; col++) {
		for (int row = 0; row < sizeMaze; row++) {
			int randomNumber = dist(rng); // Generate a random number (1 or 2)

			// Calculate common positions
			int posX = col * 3;
			int posY = row * 3;

			// Removing either the West wall or the North wall
			if (randomNumber == 2) {
				if (getMazeElementSymbol(posX + 1, posY) == 'X') { removeLeftWall(posX, posY); }
				else { removeUpWall(posX, posY); }
			}
			else {
				if (getMazeElementSymbol(posX, posY + 1) == 'X') { removeUpWall(posX, posY); }
				else { removeLeftWall(posX, posY); }
			}
		}
	}
}

void Maze::run() {
	// Run the maze visualization loop.
	// Handles window events, clears the window, prints the maze, and displays the window.

	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
		}
		window.clear();
		printMaze();
		window.display();
	}
}

// Edit MazeElements
void Maze::setMazeElement(int y, int x, MazeElement* newElement) {
	// Set the maze element at coordinates (y, x) to the specified new element.
	// Ensures valid indices within the maze boundaries and avoids modifying OutOfBounds, Start, or End elements.

	if (x >= 0 && x < maze.size() && y >= 0 && y < maze[x].size()) {
		// Check if the current element is OutOfBounds or Start
		if (dynamic_cast<OutOfBounds*>(maze[x][y]) == nullptr &&
			dynamic_cast<Start*>(maze[x][y]) == nullptr &&
			dynamic_cast<End*>(maze[x][y]) == nullptr) {
			delete maze[x][y]; // Delete the old element
			maze[x][y] = newElement; // Set the new element
		}
	}
}

void Maze::setMazeElement_Visited(int y, int x) {
	// Set the maze element at coordinates (y, x) as visited.
	// Ensures valid indices within the maze boundaries before updating.
	// If the element at the specified location is a Path, it is replaced with a Checkpoint.

	if (x >= 0 && x < maze.size() && y >= 0 && y < maze[x].size()) {
		if (dynamic_cast<Path*>(maze[x][y]) != nullptr)
		{
			delete maze[x][y];
			maze[x][y] = new Checkpoint();
		}
	}
}

void Maze::setMazeElement_WrongTurn(int y, int x) {
	if (x >= 0 && x < maze.size() && y >= 0 && y < maze[x].size()) {
		if (dynamic_cast<WrongPath*>(maze[x][y]) != nullptr)
		{
			delete maze[x][y];
			maze[x][y] = new WrongPath();
		}
	}
}

void Maze::removeLeftWall(int x, int y) {
	// Remove the left wall at coordinates (x, y) and create paths in the adjacent cells.
	setMazeElement(x, y + 1, new Path());
	setMazeElement(x, y + 2, new Path());
}
void Maze::removeUpWall(int x, int y) {
	// Remove the up wall at coordinates (x, y) and create paths in the adjacent cells.
	setMazeElement(x + 1, y, new Path());
	setMazeElement(x + 2, y, new Path());
}

// Get info
char Maze::getMazeElementSymbol(int x, int y) {
	// Get the symbol of the maze element at coordinates (x, y).
	return maze[y][x]->getSymbol();
}

string Maze::getMazeElementDescription(int x, int y) {
	// Get the description of the maze element at coordinates (x, y).
	return maze[y][x]->getDescription();
}

// Print
void Maze::printMaze() {
	// Print the maze by iterating through each cell and rendering its symbol.
	for (int y = 0; y < TrueSize + 1; y++) {
		for (int x = 0; x < TrueSize + 1; x++) {
			fading = mapping(x + y, 0, TrueSize * 2, 1, 255);

			Cell.setPosition((Cell_Size * x), (Cell_Size * y)); // 5 sweet spot
			printBlockSymbol(*maze[x][y]);
		}
	}
}
void Maze::printMazeElement(int x, int y) {
	// Print the symbol of the maze element at coordinates (x, y).

	if (x >= 0 && x < maze.size() && y >= 0 && y < maze[x].size())
	{
		printBlockSymbol(*maze[x][y]);
	}
	else
	{
		// Handle out-of-bounds case (e.g., print an error message or log)
		cout << "Error: Attempted to print out-of-bounds element at coordinates (" << x << ", " << y << ")" << endl;
	}
}

void Maze::printBlockSymbol(const MazeElement& element) {
	// Print the symbol of the provided maze element using a colored rectangle.

	// Mapping of symbols to colors
	map<char, Color> symbolToColor = {
		{'P', Color(125, 0, 125)},
		{'W', Color(0, 0, 0)},
		{'C', Color(60, 60, 225)},
		{'S', Color(50, 255, 50)},
		{'E', Color(200, 0, 75)},
		{'w', Color(255, 68, 51)},
		{'X', Color(0, 0, 0)}
	};

	// Get the symbol of the maze element
	char symbol = element.getSymbol();

	// Check if the symbol is present in the map
	if (symbolToColor.count(symbol)) {
		// Retrieve the color for the symbol
		Color fillColor = symbolToColor[symbol];

		// Adjust alpha for specific symbol ('P' in this case)
		if (fillColor.a > 0 && symbol == 'P') {
			fillColor.g -= fading; // Adjust the rate at which the alpha decreases
		}

		// Set the fill color of the cell and draw it
		Cell.setFillColor(fillColor);
		window.draw(Cell);

		// Reset outline thickness (in case it was modified elsewhere)
		Cell.setOutlineThickness(0.f);
	}
	else {
		// Handle the case where the symbol is not found (e.g., log an error)
		cout << "Error: Symbol '" << symbol << "' not found in symbolToColor map." << endl;
	}
}

int Maze::mapping(int input, int fromLow, int fromHigh, int toLow, int toHigh) {
	// Ensure valid input and output ranges
	if (fromLow >= fromHigh || toLow >= toHigh) {
		return input;
	}
	// Calculate the percentage of the input within the input range
	float percentage = static_cast<float>(input - fromLow) / (fromHigh - fromLow);

	// Map the percentage to the output range and convert to integer
	int result = toLow + static_cast<int>(percentage * (toHigh - toLow));

	// Ensure the result is within the specified output range
	result = min(max(result, toLow), toHigh);

	// Return the mapped result
	return result;
}