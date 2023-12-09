#pragma once

// Class
#include "MazeElement.h"


class Wall : public MazeElement {
public:
    string getDescription() const override { return "Wall"; } // Description of the Wall element
    char getSymbol() const override { return 'W'; }                // Character symbol for Wall

private:

};

