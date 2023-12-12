#pragma once

// Class
#include "MazeElement.h"

// Base Class -> Path
class Path : public MazeElement {
public:
	// Get info
	string getDescription() const override { return "Path"; }
	char getSymbol() const override { return 'P'; }

private:
};
