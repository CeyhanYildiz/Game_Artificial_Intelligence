#pragma once

// Class
#include "MazeElement.h"

// Base Class -> Checkpoint 
class Checkpoint : public MazeElement {
public:
    // Get info
        string getDescription() const override { return "Checkpoint"; }
        char getSymbol() const override { return 'C'; } 

private:
};
