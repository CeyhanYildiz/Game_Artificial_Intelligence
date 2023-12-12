#pragma once

// Class
#include "MazeElement.h"

// Base Class -> WrongPath
class WrongPath : public MazeElement {
public:
	// Get info
	string getDescription() const override { return "Wrong path"; }
	char getSymbol() const override { return 'w'; }

private:
};