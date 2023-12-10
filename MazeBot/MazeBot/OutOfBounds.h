#pragma once

// Class
#include "MazeElement.h"

// Base Class -> OutOfBounds
class OutOfBounds : public MazeElement {
public:
    // Get info
        string getDescription() const override { return "Out of Bounds"; }
        char getSymbol() const override { return 'X'; }

private:
};
