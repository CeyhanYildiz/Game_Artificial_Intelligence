#pragma once
#include "MazeElement.h"

using namespace std;

class Wall : public MazeElement {
public:
    string getDescription() const override { return "Wall"; } // Description of the Wall element
    char getSymbol() const override { return 'W'; }                // Character symbol for Wall

private:

};

