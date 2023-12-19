#pragma once

// Include the MazeElement header for the base class
#include "MazeElement.h"

// Derived Class -> Wall
class Wall : public MazeElement {
public:
	// Get information about the maze element
	string getDescription() const override {
		return "Wall";  // Description of the 'Wall' maze element
	}

	// Get the symbol representing the maze element
	char getSymbol() const override {
		return 'W';  // Symbol representing the 'Wall' maze element
	}

private:
	// Additional private members or functions, if needed
};
