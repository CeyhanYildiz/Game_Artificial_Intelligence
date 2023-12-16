#pragma once

// Class
#include "MazeElement.h"

// Base Class -> End
class End : public MazeElement {
public:

	End() {
		isVisited();  // Assuming isVisited is a member function in MazeElement
	}

	// Copy constructor
	End(const End& other) : MazeElement(other) {
		// Assuming isVisited is a member function in MazeElement
		other.isVisited();
	}

	// Get info
	string getDescription() const override { return "End"; }
	char getSymbol() const override { return 'E'; }

private:
};
