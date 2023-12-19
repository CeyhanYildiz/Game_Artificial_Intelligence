#pragma once

// Include the MazeElement header for the base class
#include "MazeElement.h"

// Derived Class -> Start
class Start : public MazeElement {
public:
	// Default constructor
	Start() {
		isVisited();  // Assuming isVisited is a member function in MazeElement
	}

	// Copy constructor
	Start(const Start& other) : MazeElement(other) {
		// Assuming isVisited is a member function in MazeElement
		other.isVisited();
	}

	// Get information about the maze element
	string getDescription() const override {
		return "Start";  // Description of the 'Start' maze element
	}

	// Get the symbol representing the maze element
	char getSymbol() const override {
		return 'S';  // Symbol representing the 'Start' maze element
	}
};
