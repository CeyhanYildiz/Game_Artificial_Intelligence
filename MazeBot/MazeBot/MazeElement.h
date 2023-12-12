#pragma once

// C++
#include <string>

// namespace
using namespace std;

// Base Class
class MazeElement
{
public:
	// Construct & Destructor
	MazeElement() { Visited = false; };
	virtual ~MazeElement() {}

	// Get info
	virtual string getDescription() const = 0;
	virtual char getSymbol() const = 0;
	bool isVisited() const { return Visited; }

	// Set info
	void setVisited() { Visited = true; }

private:
	//Variable
	bool Visited;   // True if cell is Visited

	//unsigned char NorthWall; // True if hase Wall North(UP)
	//unsigned char EastWall;  // Right
	//unsigned char SouthWall; // Down
	//unsigned char WestWall;  // Left
	// this 'space'
};
