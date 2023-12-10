#pragma once

// Class
#include "MazeElement.h"

// Base Class -> Wall
class Wall : public MazeElement {
public:
    // Get info
        string getDescription() const override { return "Wall"; }
        char getSymbol() const override { return 'W'; }

private:

};

