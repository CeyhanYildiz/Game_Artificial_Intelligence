#pragma once

#include "MazeElement.h"

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

	// Get info
	string getDescription() const override {
		return "Start";
	}

	char getSymbol() const override {
		return 'S';
	}
};
