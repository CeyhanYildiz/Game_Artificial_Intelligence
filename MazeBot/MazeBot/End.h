#pragma once

// Class
#include "MazeElement.h"

// Base Class -> End 
class End : public MazeElement {
public:
    //Get info
        string getDescription() const override { return "End"; } 
        char getSymbol() const override { return 'E'; }               

private:
};

