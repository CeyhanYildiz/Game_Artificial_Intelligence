#pragma once

// Class
#include "MazeElement.h"

// Base Class -> Start
class Start : public MazeElement {
public:
    // Get info
        string getDescription() const override { return "Start"; } 
        char getSymbol() const override { return 'S'; }

private:
};

