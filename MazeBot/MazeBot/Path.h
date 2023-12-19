#pragma once

// Class
#include "MazeElement.h"

// Base Class -> Path
class Path : public MazeElement {
public:
	// Get info
	string getDescription() const override { return "Path"; }
	char getSymbol() const override { return 'P'; }

	// Set Wall Type (only one of Up_Down or Left_Right can be set, not both)
	void setWallType(unsigned char upDown, unsigned char leftRight) {
		if (upDown != 0 && leftRight == 0) {
			Up_Down = upDown;
		}
		else if (upDown == 0 && leftRight != 0) {
			Left_Right = leftRight;
		}
		else {
			// Handle the case where both or neither are set (you may throw an exception or handle it differently)
			// For simplicity, I'm printing a message to the console
			cout << "Error: Set either Up_Down or Left_Right, not both or neither." << endl;
		}
	}

	// Getter functions
	unsigned char getUp_Down() const { return Up_Down; }
	unsigned char getLeft_Right() const { return Left_Right; }

private:

	//Wall Type
	unsigned char Up_Down;
	unsigned char Left_Right;
};
