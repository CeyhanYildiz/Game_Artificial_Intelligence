#include <iostream>

#include <vector>
#include <string>

using namespace std;

/* Idee for a maze

 Samy :
⬛⬛⬛⬛⬛⬛⬛
⬛🟦🟦🟦🟦🟦⬛
⬛🟦⬛⬛⬛🟩⬛
⬛🟦🟦🟦⬛⬛⬛
⬛⬜⬛🟦🟦🟥⬛
⬛⬛⬛⬛⬛⬛⬛

⬜ = Path
⬛ = Wall

Ceyhan:


⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛        ⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛
⬛🟩🟩⬛⬜⬜⬛⬜⬜⬛⬜⬜⬛        ⬛🟩🟩🟦🟦🟦🟨🟨🟨🟨🟨🟨⬛
⬛🟩🟩⬛⬜⬜⬛⬜⬜⬛⬜⬜⬛        ⬛🟩🟩🟦🟦🟦🟨🟨🟨🟨🟨🟨⬛
⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛        ⬛⬛⬛⬛🟦🟦⬛⬛⬛⬛⬛⬛⬛
⬛⬜⬜⬛⬜⬜⬛⬜⬜⬛⬜⬜⬛        ⬛🟨🟨🟨🟦🟦🟦🟦🟦🟦🟦🟦⬛
⬛⬜⬜⬛⬜⬜⬛⬜⬜⬛⬜⬜⬛        ⬛🟨🟨🟨🟦🟦🟦🟦🟦🟦🟦🟦⬛
⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛        ⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛🟦🟦⬛
⬛⬜⬜⬛⬜⬜⬛⬜⬜⬛⬜⬜⬛        ⬛🟨🟨🟨🟨🟨🟨🟦🟦🟦🟦🟦⬛
⬛⬜⬜⬛⬜⬜⬛⬜⬜⬛⬜⬜⬛        ⬛🟨🟨🟨🟨🟨🟨🟦🟦🟦🟦🟦⬛
⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛        ⬛🟨🟨⬛⬛⬛⬛🟦🟦⬛⬛⬛⬛
⬛⬜⬜⬛⬜⬜⬛⬜⬜⬛🟥🟥⬛        ⬛🟨🟨⬛⬜⬜⬜🟦🟦🟦🟥🟥⬛
⬛⬜⬜⬛⬜⬜⬛⬜⬜⬛🟥🟥⬛        ⬛🟨🟨⬛⬜⬜⬜🟦🟦🟦🟥🟥⬛
⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛        ⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛

⬜ = Path         = P
⬛ = Wall         = W
🟦 = Correct Path = C
🟩 = Start        = S 
🟥 = End          = E
🟨 = Wrong Path   = w
*/

// Base class
class MazeElement {
public:
    virtual char getSymbol() const = 0;  // Pure virtual function
    virtual ~MazeElement() {}  // Virtual destructor
};

// Derived classes
class Wall : public MazeElement {
public:
    char getSymbol() const override { return 'W'; }
};

class Path : public MazeElement {
public:
    char getSymbol() const override { return 'P'; }
};

class Checkpoint : public MazeElement {
public:
    char getSymbol() const override { return 'C'; }
};



void printBlockSymbol(const MazeElement& element) {
    switch (element.getSymbol()) {
        case 'P': cout << "⬜"; break;
        case 'W': cout << "⬛"; break;
        case 'C': cout << "🟦"; break;
        case 'S': cout << "🟩"; break;
        case 'E': cout << "🟥"; break;
        case 'w': cout << "🟨"; break;
        // ... handle other cases
        default:
            cout << "Invalid value\n";
    }
}


int main() {
    const int sizeMaze =  4 ;
    const int count = (sizeMaze*3)+1;
    const int CellSize_2x2 = 3;

    // Using a raw pointer array for the maze
    MazeElement*** Maze = new MazeElement**[count];

    for (int x = 0; x < count; x++) {
        Maze[x] = new MazeElement*[count];
        for (int y = 0; y < count; y++) {
            if (y % CellSize_2x2 == 0 || x % CellSize_2x2 == 0) {
                Maze[x][y] = new Wall();
            } else {
                Maze[x][y] = new Path();
            }
        }
    }

    // Printing the maze
    for (int x = 0; x < count; x++) {
        for (int y = 0; y < count; y++) {
            printBlockSymbol(*Maze[x][y]);
        }
        cout << endl;
    }

    // Properly deallocating memory
    for (int x = 0; x < count; x++) {
        for (int y = 0; y < count; y++) {
            delete Maze[x][y];
        }
        delete[] Maze[x];
    }
    delete[] Maze;

    return 0;
}

