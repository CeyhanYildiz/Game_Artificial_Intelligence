#pragma once

// Include the MazeElement header for the base class
#include "MazeElement.h"

// Derived Class -> Checkpoint
class Checkpoint : public MazeElement {
public:
	// Get information about the maze element
	string getDescription() const override {
		return "Checkpoint";  // Description of the 'Checkpoint' maze element
	}

	// Get the symbol representing the maze element
	char getSymbol() const override {
		return 'C';  // Symbol representing the 'Checkpoint' maze element
	}

private:
	// Additional private members or functions, if needed
};
