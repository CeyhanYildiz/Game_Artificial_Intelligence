#pragma once

// Include the MazeElement header for the base class
#include "MazeElement.h"

// Derived Class -> End
class End : public MazeElement {
public:
	// Default constructor
	End() {
	}

	// Copy constructor
	End(const End& other) : MazeElement(other) {
	}

	// Get information about the maze element
	string getDescription() const override {
		return "End";  // Description of the 'End' maze element
	}

	// Get the symbol representing the maze element
	char getSymbol() const override {
		return 'E';  // Symbol representing the 'End' maze element
	}

private:
	// Additional private members or functions, if needed
};
