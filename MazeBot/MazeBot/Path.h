#pragma once
#include "MazeElement.h"

using namespace std;

class Path : public MazeElement {
public:
    string getDescription() const override { return "Path"; } // Description of the Path element
    char getSymbol() const override { return 'P'; }                // Character symbol for Path

private:

};

