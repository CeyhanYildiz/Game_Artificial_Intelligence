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
#include "GameThread.h"

// Name Space
using namespace sf;

// Maze constructor
Maze::Maze(int size, int Cell_Size, string name) :
	sizeMaze(size),
	Cell_Size(Cell_Size),
	window(sf::VideoMode(899, 899), name),
	Cell(Vector2f(Cell_Size, Cell_Size)),
	Player(Vector2f(Cell_Size / 2, Cell_Size / 2))
{
	// Player setup
	Player.setFillColor(Color::Magenta);

	// Constructor for the Maze class with initialization list.

	// Calculations
	TrueSize = sizeMaze * 3;
	int quarter = TrueSize + 1;
	int q1 = quarter - 2;
	int q2 = quarter - 3;
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
	addElements({ {1, 1}, {1, 2}, {2, 1} }, new Start());

	// Replace existing element at (2, 2) with a copied Start element
	delete maze[2][2];
	maze[2][2] = new Start(*dynamic_cast<Start*>(maze[2][1]));

	// Adding End
	addElements({ {q1, q1}, {q1, q2}, {q2, q1} }, new End());

	// Replace existing element at (q2, q2) with a copied End element
	delete maze[q2][q2];
	maze[q2][q2] = new End(*dynamic_cast<End*>(maze[q2][q1]));

	// Grid to Maze using Binary Tree Algorithm
	Binary_Tree_Algorithm();

	// Move the player to the starting position
	Player.move(Cell_Size * 2, Cell_Size * 2);
}

// Destructor for the Maze class, responsible for freeing allocated memory.
Maze::~Maze() {
	// Loop through each cell in the maze and delete the allocated MazeElement objects.
	for (int x = 0; x < TrueSize + 1; x++) {
		for (int y = 0; y < TrueSize + 1; y++) {
			delete maze[x][y];
		}
	}
}

// Function to construct the initial maze structure with walls, paths, and boundaries.
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

	// Loop through each cell in the maze
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

// Function to implement the Binary Tree Algorithm for maze generation.
// The algorithm uses randomization to remove either the West or North wall for each cell.
void Maze::Binary_Tree_Algorithm() {
	// Create a random number generator using Mersenne Twister algorithm
	mt19937 rng(time(NULL));

	// Distribute random numbers between 1 and 2
	uniform_int_distribution<int> dist(1, 2);

	// Loop through each cell in the maze
	for (int col = 0; col < sizeMaze; col++) {
		for (int row = 0; row < sizeMaze; row++) {
			// Generate a random number (1 or 2)
			int randomNumber = dist(rng);

			// Calculate common positions
			int posX = col * 3;
			int posY = row * 3;

			// Removing either the West wall or the North wall
			if (randomNumber == 2) {
				// Check and remove the appropriate wall based on adjacent cell status
				if (getMazeElementSymbol(posX + 1, posY) == 'X') {
					removeLeftWall(posX, posY);
				}
				else {
					removeUpWall(posX, posY);
				}
			}
			else {
				// Check and remove the appropriate wall based on adjacent cell status
				if (getMazeElementSymbol(posX, posY + 1) == 'X') {
					removeUpWall(posX, posY);
				}
				else {
					removeLeftWall(posX, posY);
				}
			}
		}
	}
}

void Maze::run() {
	// Run the maze visualization loop.
	// Handles window events, clears the window, prints the maze, and displays the window.
	while (window.isOpen()) {
		// if window is still open
		handleWindowEvents();

		// Reads the location of the mouse ( magenta Box )
		Vector2<float> playerPosition = Player.getPosition();

		// Ensure you are using the correct indices based on the returned type
		int x = static_cast<int>(playerPosition.x);
		int y = static_cast<int>(playerPosition.y);

		// Makes sure it does not bug out if the mouse is not on the window
		handleOutOfBounds(x, y);

		// Exit the loop after reaching the end
		if (isAtEnd(x, y)) {
			handleEndReached();
			break;  // Exit the loop after reaching the end
		}

		// Player ( BOX ) moves to mouse input
		handlePlayerMovement();

		// Print maze
		printMaze();
		// Print Player
		window.draw(Player);

		// Display the maze + player
		window.display();
	}
}

// Function to handle window events using a polling mechanism.
// It checks for and responds to window closure events, closing the window if detected.
void Maze::handleWindowEvents() {
	Event event;

	// Poll for events until the event queue is empty
	while (window.pollEvent(event)) {
		// Check if the event is a window closure
		if (event.type == Event::Closed)
			window.close();
	}
}

// Function to handle the scenario when the player's position goes out of bounds.
// If the player's position exceeds the defined maze boundaries, it sets Startgame to false,
// provides feedback to the user, resets the player's position, and prompts them to try again.
void Maze::handleOutOfBounds(int x, int y) {
	// Check if the player's position is outside the defined maze boundaries
	if (x <= 27 || y <= 27 || x >= 857 || y >= 857) {
		// Set Startgame to false to indicate the need to restart
		Startgame = false;

		// Inform the user about hitting the OutOfBounds wall and provide instructions
		cout << "Hit OutOfBounds Wall, try again" << endl;
		cout << "Move your Mouse to Start (Green Box)" << endl;
		cout << "Wait on my Call" << endl;

		// Introduce a delay for 2000 milliseconds (2 seconds)
		Sleep(2000);

		// Reset the player's position to the starting point
		Player.setPosition(Cell_Size * 2, Cell_Size * 2);

		// Provide feedback that the user is good to go
		cout << "Ok Good to go" << endl;
	}
}

// Function to check if the player's position is at the designated end point of the maze.
// Returns true if the player's position is within the specified end region, otherwise returns false.
bool Maze::isAtEnd(int x, int y) {
	// Check if the player's position is within the specified end region
	if (x >= 810 && y >= 810 && x <= 860 && y <= 860) {
		// Return true if the player is at the end
		return true;
	}
	else {
		// Return false if the player is not at the end
		return false;
	}
}

// Function to handle the scenario when the player reaches the end of the maze.
// Provides congratulatory messages, captures a screenshot of the completed maze,
// closes the current window, introduces a delay, and proceeds to the next maze.
void Maze::handleEndReached() {
	// Congratulate the player for completing the maze
	cout << endl << "Good Job! One more maze to solve." << endl;

	// Create a texture, print the maze, draw the player, and display the window
	texture.create(window.getSize().x, window.getSize().y);
	printMaze();
	window.draw(Player);
	window.display();

	// Update the texture and save a screenshot of the completed maze
	texture.update(window);
	screenshot = texture.copyToImage();
	screenshot.saveToFile("DONE.png");

	// Close the current window
	window.close();

	// Introduce a delay for 2000 milliseconds (2 seconds)
	Sleep(2000);

	// Create a new GameManager instance and start the next maze
	GameManager gameManager(1);
	gameManager.startGames();
}

// Function to handle player movement based on mouse input.
void Maze::handlePlayerMovement() {
	// Get the mouse position in screen coordinates
	Vector2i mousePosition = Mouse::getPosition(window);

	// Map the screen coordinates to world coordinates
	Vector2f worldPosition = window.mapPixelToCoords(mousePosition);

	// Create a texture, print the maze, draw the player, and display the window
	texture.create(window.getSize().x, window.getSize().y);
	printMaze();
	window.draw(Player);
	window.display();

	// Update the texture and save a screenshot of the current state
	texture.update(window);
	screenshot = texture.copyToImage();
	screenshot.saveToFile("DONE.png");

	// Load the screenshot image to track pixel colors
	Image track;
	if (!track.loadFromFile("DONE.png")) {
		// Handle image loading failure
		cout << "ERROR Image" << endl;
	}

	// Get the color of the pixel at the current mouse position
	Color color = track.getPixel(mousePosition.x + 10, mousePosition.y + 10);

	// Check if the mouse is in the start region
	if (mousePosition.x >= 27 && mousePosition.y >= 27 && mousePosition.x <= 80 && mousePosition.y <= 80) {
		Startgame = true;
	}

	// Check for left mouse button press and ensure the game has started
	if (Mouse::isButtonPressed(Mouse::Left) && Startgame) {
		// Left click detected

		// Check if the color is black (assuming black is represented as RGB(0, 0, 0))
		if (color.r == 0 && color.g == 0 && color.b == 0) {
			// Handle collision with a wall
			Startgame = false;
			cout << "Hit Wall, try again" << endl;
			cout << "Move your Mouse to Start (Green Box)" << endl;

			// Introduce a delay for 2000 milliseconds (2 seconds)
			Sleep(2000);

			// Check if the color at the new position is the start position (Green Box)
			if (color.r == 50 && color.g == 255 && color.b == 50) {
				// Reset the player position to the start
				Player.setPosition(Cell_Size * 2, Cell_Size * 2);
				cout << "Ok Good to go" << endl;
			}

			cout << "Wait on my Call" << endl;
		}

		// Set the player position to the current mouse position
		Player.setPosition(mousePosition.x, mousePosition.y);
	}
	else {
		// If the left mouse button is not pressed or the game has not started, reset the player position
		Startgame = false;
		Player.setPosition(Cell_Size * 2, Cell_Size * 2);
	}
}

// Function to set the maze element at specified coordinates to the given new element.
// Ensures valid indices within the maze boundaries and avoids modifying OutOfBounds, Start, or End elements.
void Maze::setMazeElement(int y, int x, MazeElement* newElement) {
	// Check if the coordinates (x, y) are within the bounds of the maze
	if (x >= 0 && x < maze.size() && y >= 0 && y < maze[x].size()) {
		// Check if the current element is neither OutOfBounds, Start, nor End
		if (dynamic_cast<OutOfBounds*>(maze[x][y]) == nullptr &&
			dynamic_cast<Start*>(maze[x][y]) == nullptr &&
			dynamic_cast<End*>(maze[x][y]) == nullptr) {
			// Delete the old element at the specified coordinates
			delete maze[x][y];
			// Set the new element at the specified coordinates
			maze[x][y] = newElement;
		}
	}
}

// Function to mark the maze element at specified coordinates as visited.
// Ensures valid indices within the maze boundaries before updating.
// If the element at the specified location is a Path, it is replaced with a Checkpoint.
void Maze::setMazeElement_Visited(int y, int x) {
	// Check if the coordinates (x, y) are within the bounds of the maze
	if (x >= 0 && x < maze.size() && y >= 0 && y < maze[x].size()) {
		// Check if the current element is a Path
		if (dynamic_cast<Path*>(maze[x][y]) != nullptr) {
			// Delete the old Path element and replace it with a Checkpoint
			delete maze[x][y];
			maze[x][y] = new Checkpoint();
		}
	}
}

// Function to mark the maze element at specified coordinates as a wrong turn.
// Ensures valid indices within the maze boundaries before updating.
// If the element at the specified location is a WrongPath, it is replaced with a new WrongPath element.
void Maze::setMazeElement_WrongTurn(int y, int x) {
	// Check if the coordinates (x, y) are within the bounds of the maze
	if (x >= 0 && x < maze.size() && y >= 0 && y < maze[x].size()) {
		// Check if the current element is a WrongPath
		if (dynamic_cast<WrongPath*>(maze[x][y]) != nullptr) {
			// Delete the old WrongPath element and replace it with a new WrongPath
			delete maze[x][y];
			maze[x][y] = new WrongPath();
		}
	}
}

// Function to remove the left wall at coordinates (x, y) and create paths in the adjacent cells.
void Maze::removeLeftWall(int x, int y) {
	// Create paths in the adjacent cells to the left of the specified coordinates
	setMazeElement(x, y + 1, new Path());
	setMazeElement(x, y + 2, new Path());
}

// Function to remove the up wall at coordinates (x, y) and create paths in the adjacent cells.
void Maze::removeUpWall(int x, int y) {
	// Create paths in the adjacent cells above the specified coordinates
	setMazeElement(x + 1, y, new Path());
	setMazeElement(x + 2, y, new Path());
}

// Function to get the symbol of the maze element at coordinates (x, y).
char Maze::getMazeElementSymbol(int x, int y) {
	// Return the symbol of the maze element at the specified coordinates
	return maze[y][x]->getSymbol();
}

// Function to get the description of the maze element at coordinates (x, y).
string Maze::getMazeElementDescription(int x, int y) {
	// Return the description of the maze element at the specified coordinates
	return maze[y][x]->getDescription();
}

// Function to print the maze by iterating through each cell and rendering its symbol.
void Maze::printMaze() {
	// Iterate through each cell in the maze
	for (int y = 0; y < TrueSize + 1; y++) {
		for (int x = 0; x < TrueSize + 1; x++) {
			// Calculate fading effect based on cell position
			fading = mapping(x + y, 0, TrueSize * 2, 1, 255);

			// Set the position of the Cell object based on the current coordinates
			Cell.setPosition((Cell_Size * x), (Cell_Size * y));

			// Print the symbol of the maze element at the current coordinates
			printBlockSymbol(*maze[x][y]);
		}
	}
}

// Function to print the symbol of the maze element at coordinates (x, y).
void Maze::printMazeElement(int x, int y) {
	// Check if the coordinates (x, y) are within the bounds of the maze
	if (x >= 0 && x < maze.size() && y >= 0 && y < maze[x].size()) {
		// Print the symbol of the maze element at the specified coordinates
		printBlockSymbol(*maze[x][y]);
	}
	else {
		// Handle out-of-bounds case (e.g., print an error message or log)
		cout << "Error: Attempted to print out-of-bounds element at coordinates (" << x << ", " << y << ")" << endl;
	}
}

// Function to print the symbol of the provided maze element using a colored rectangle.
void Maze::printBlockSymbol(const MazeElement& element) {
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

		// Adjust alpha for a specific symbol ('P' in this case)
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

// Function to map a value from one range to another.
// Ensures valid input and output ranges, calculates the percentage of the input within the input range,
// maps the percentage to the output range, and converts the result to an integer.
int Maze::mapping(int input, int fromLow, int fromHigh, int toLow, int toHigh) {
	// Ensure valid input and output ranges
	if (fromLow >= fromHigh || toLow >= toHigh) {
		// Return the input if ranges are invalid
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