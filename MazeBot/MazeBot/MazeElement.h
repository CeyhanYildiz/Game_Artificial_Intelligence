#pragma once

// C++
#include <string>

using namespace std;

class MazeElement
{
public:
    virtual string getDescription() const = 0;  // Returns a string description of the element
    virtual char getSymbol() const = 0;               // Returns a character symbol representing the element
    virtual ~MazeElement() {}                        // Virtual destructor to allow proper cleanup of derived types

    // Getter and Setter for Visited
    bool isVisited() const { return Visited; }
    void setVisited(bool value) { Visited = value; }
private:
	bool Visited;

};
