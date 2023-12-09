#pragma once

// Class
#include "MazeElement.h"


class Start : public MazeElement {
public:
    string getDescription() const override { return "Start"; } // Description of the Start element
    char getSymbol() const override { return 'S'; }                // Character symbol for Start

private:
};

