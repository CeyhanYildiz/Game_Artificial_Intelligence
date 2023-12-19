#pragma once

// C++ standard library includes
#include <string>

// Namespace declaration
using namespace std;

// Base Class -> MazeElement
class MazeElement {
public:
	// Constructor and Destructor
	MazeElement() {
		Visited = false;  // Initialize the Visited variable to false
	}
	virtual ~MazeElement() {}  // Virtual destructor for polymorphism

	// Get information about the maze element (to be implemented by derived classes)
	virtual string getDescription() const = 0;

	// Get the symbol representing the maze element (to be implemented by derived classes)
	virtual char getSymbol() const = 0;

	// Check if the cell is visited
	bool isVisited() const {
		return Visited;  // Return the value of the Visited variable
	}

	// Set the cell as visited
	void setVisited() {
		Visited = true;  // Set the Visited variable to true
	}

private:
	// Variable
	bool Visited;  // True if the cell is visited
};
