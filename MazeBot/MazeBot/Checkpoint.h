#pragma once

// Class
#include "MazeElement.h"

// Base Class -> Checkpoint 
class Checkpoint : public MazeElement {
public:
    //Get info
    string getDescription() const override { return "Checkpoint"; } // Description of the Checkpoint element
    char getSymbol() const override { return 'C'; }                     // Character symbol for Checkpoint

private:
};
