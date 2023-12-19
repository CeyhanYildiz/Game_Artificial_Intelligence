#pragma once

// Include the MazeElement header for the base class
#include "MazeElement.h"

// Derived Class -> OutOfBounds
class OutOfBounds : public MazeElement {
public:
	// Get information about the maze element
	string getDescription() const override {
		return "Out of Bounds";  // Description of the 'Out of Bounds' maze element
	}

	// Get the symbol representing the maze element
	char getSymbol() const override {
		return 'X';  // Symbol representing the 'Out of Bounds' maze element
	}

private:
	// Additional private members or functions, if needed
};
