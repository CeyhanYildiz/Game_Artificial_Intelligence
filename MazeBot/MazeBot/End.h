#pragma once

// Class
#include "MazeElement.h"

// Base Class -> End
class End : public MazeElement {
public:

	End() {
	}

	// Copy constructor
	End(const End& other) : MazeElement(other) {
	}

	// Get info
	string getDescription() const override { return "End"; }
	char getSymbol() const override { return 'E'; }

private:
};
