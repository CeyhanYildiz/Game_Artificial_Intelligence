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
class MazeElement 
{
    public:
        virtual char getSymbol() const = 0;  // Pure virtual function
        virtual ~MazeElement() {}  // Virtual destructor
};

// Derived classes
class Wall : public MazeElement 
{
    public:
        char getSymbol() const override { return 'W'; }
};

class Path : public MazeElement 
{
    public:
        char getSymbol() const override { return 'P'; }
};

class Checkpoint : public MazeElement 
{
    public:
        char getSymbol() const override { return 'C'; }
};



void printBlockSymbol(const MazeElement& element);


int main() 
{
    const int sizeMaze = 4; // sizeMaze x sizeMaze 

    // Using std::vector for the maze
    vector<vector<MazeElement*>> Maze((sizeMaze * 3) + 1, vector<MazeElement*>((sizeMaze * 3) + 1));

    for (int x = 0; x < (sizeMaze * 3) + 1; x++) 
    {
        for (int y = 0; y < (sizeMaze * 3) + 1; y++) 
        {
            if (y % 3 == 0 || x % 3 == 0) 
            {
                Maze[x][y] = new Wall();
            } else 
            {
                Maze[x][y] = new Path();
            }
        }
    }

    // Printing the maze
    for (int x = 0; x < (sizeMaze * 3) + 1; x++) 
    {
        for (int y = 0; y < (sizeMaze * 3) + 1; y++) 
        {
            printBlockSymbol(*Maze[x][y]);
        }
        cout << endl;
    }

    // Deallocating memory
    for (int x = 0; x < (sizeMaze * 3) + 1; x++) 
    {
        for (int y = 0; y < (sizeMaze * 3) + 1; y++) 
        {
            delete Maze[x][y];
        }
    }
    return 0;
}

void printBlockSymbol(const MazeElement& element) 
{
    switch (element.getSymbol()) 
    {
        case 'P': cout << "⬜"; break;
        case 'W': cout << "⬛"; break;
        case 'C': cout << "🟦"; break;
        case 'S': cout << "🟩"; break;
        case 'E': cout << "🟥"; break;
        case 'w': cout << "🟨"; break;
        default:
            cout << "Invalid value\n";
    }
}