#pragma once
#include "MazeElement.h"

using namespace std;

class Checkpoint : public MazeElement {
public:
    string getDescription() const override { return "Checkpoint"; } // Description of the Checkpoint element
    char getSymbol() const override { return 'C'; }                     // Character symbol for Checkpoint

private:
};
