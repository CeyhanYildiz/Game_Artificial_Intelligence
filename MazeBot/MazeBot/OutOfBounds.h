#pragma once

// Class
#include "MazeElement.h"

using namespace std;

class OutOfBounds : public MazeElement {

public:
    string getDescription() const override { return "Out of Bounds"; } // Description of the Out of Bounds element
    char getSymbol() const override { return 'X'; }                         // Character symbol for Out of Bounds

private:
};
