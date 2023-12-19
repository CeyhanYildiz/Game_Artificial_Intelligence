#pragma once

// Include the MazeElement header for the base class
#include "MazeElement.h"

// Derived Class -> WrongPath
class WrongPath : public MazeElement {
public:
	// Get information about the maze element
	string getDescription() const override {
		return "Wrong path";  // Description of the 'WrongPath' maze element
	}

	// Get the symbol representing the maze element
	char getSymbol() const override {
		return 'w';  // Symbol representing the 'WrongPath' maze element
	}

private:
	// Additional private members or functions, if needed
};
