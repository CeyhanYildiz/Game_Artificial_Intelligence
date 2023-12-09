#pragma once

// Class
#include "MazeElement.h"

class Path : public MazeElement {
public:
    string getDescription() const override { return "Path"; } // Description of the Path element
    char getSymbol() const override { return 'P'; }                // Character symbol for Path

private:

};

