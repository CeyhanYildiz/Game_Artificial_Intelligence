#pragma once

// Class
#include "MazeElement.h"

using namespace std;

class End : public MazeElement {
public:
    string getDescription() const override { return "End"; } // Description of the End element
    char getSymbol() const override { return 'E'; }               // Character symbol for End

private:
};

