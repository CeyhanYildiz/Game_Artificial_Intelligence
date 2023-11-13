#include <iostream>

#include <vector>
#include <string>
#include <fstream>
#include <cstdlib> // Required for rand() and srand()
#include <ctime>   // Required for time()

using namespace std;

ofstream file("output.txt", ios::app);



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
        // Pure virtual functions that must be implemented by derived classes
        virtual string getDescription() const = 0; // Returns a string description of the element
        virtual char getSymbol() const = 0;       // Returns a character symbol representing the element

        virtual ~MazeElement() {} // Virtual destructor to allow proper cleanup of derived types
};

// Derived class representing a wall in the maze
class Wall : public MazeElement 
{
    public:
        string getDescription() const override 
        {
            return "Wall"; // Description of the Wall element
        }
        char getSymbol() const override 
        { 
            return 'W';    // Character symbol for Wall
        }
};

// Derived class representing a path in the maze
class Path : public MazeElement 
{
    public:
        string getDescription() const override 
        {
            return "Path"; // Description of the Path element
        }
        char getSymbol() const override 
        { 
            return 'P';    // Character symbol for Path
        }
};

// Derived class representing a checkpoint in the maze
class Checkpoint : public MazeElement 
{
    public:
        string getDescription() const override 
        {
            return "Checkpoint"; // Description of the Checkpoint element
        }
        char getSymbol() const override 
        { 
            return 'C';          // Character symbol for Checkpoint
        }
};

// Derived class representing the start position in the maze
class Start : public MazeElement 
{
    public:
        string getDescription() const override 
        {
            return "Start"; // Description of the Start element
        }
        char getSymbol() const override 
        { 
            return 'S';     // Character symbol for Start
        }
};

// Derived class representing a wrong path in the maze
class WrongPath : public MazeElement 
{
    public:
        string getDescription() const override 
        {
            return "Wrong path"; // Description of the Wrong Path element
        }
        char getSymbol() const override 
        { 
            return 'w';          // Character symbol for Wrong Path
        }
};

class End : public MazeElement 
{
    public:
        string getDescription() const override 
        {
            return "End"; // Description of the Wrong Path element
        }
        char getSymbol() const override 
        { 
            return 'E';          // Character symbol for Wrong Path
        }
};

class OutOfBounds : public MazeElement {
    public:
        string getDescription() const override {
            return "Out of Bounds";
        }
        char getSymbol() const override { 
            return 'X';
        }
};

void printBlockSymbol(const MazeElement& element);

class Maze {
    public:

        Maze(int size) : sizeMaze(size) 
        {
            maze.resize((sizeMaze * 3) + 1, vector<MazeElement*>((sizeMaze * 3) + 1));
            for (int x = 0; x < (sizeMaze * 3) + 1; x++) 
            {
                for (int y = 0; y < (sizeMaze * 3) + 1; y++) 
                {
                    // Set the first and last rows and columns as OutOfBounds
                    if (x == 0 || x == sizeMaze * 3 || y == 0 || y == sizeMaze * 3) 
                    {
                        maze[x][y] = new OutOfBounds();
                    } 
                    else if (y % 3 == 0 || x % 3 == 0) 
                    {
                        maze[x][y] = new Wall();
                    } 
                    else 
                    {
                        maze[x][y] = new Path();
                    }
                }
            }
            vector<pair<int, int>> endPositions = { {(size * 3) + 1 - 2, (size * 3) + 1 - 2}, {(size * 3) + 1 - 2, (size * 3) + 1 - 3}, {(size * 3) + 1 - 3, (size * 3) + 1 - 2}, {(size * 3) + 1 - 3, (size * 3) + 1 - 3} };
            for (const auto& pos : endPositions)
            {
                setMazeElement(pos.first, pos.second, new End());
            }
            vector<pair<int, int>> startPositions = {{1, 1}, {1, 2}, {2, 1}, {2, 2}};
            for (const auto& pos : startPositions) 
            {
                setMazeElement(pos.first, pos.second, new Start());
            }
            for (int shift = 0; shift < sizeMaze; shift++)
            {
                setMazeElement( shift*(((sizeMaze*3)+1/size)/sizeMaze) , 1 , new Path()); 
                setMazeElement( shift*(((sizeMaze*3)+1/size)/sizeMaze) , 2 , new Path());
                setMazeElement( 1 , shift*(((sizeMaze*3)+1/size)/sizeMaze) , new Path());
                setMazeElement( 2 , shift*(((sizeMaze*3)+1/size)/sizeMaze) , new Path()); 
            }

        /// ALGORITME 
           for (int Y = 0; Y < sizeMaze; Y++)
            {
                for (int  X = 0; X < sizeMaze; X++)
                {
                    int randomNumber = rand() % 2 + 1;
                    if (randomNumber == 2)
                    {
                        //Up
                        setMazeElement( X*(3)+1 , 3*Y , new Path()); 
                        setMazeElement( X*(3)+2 , 3*Y , new Path()); 
                    }
                    else
                    {
                        //Left
                        setMazeElement(  X*3 ,  Y*(3)+1 , new Path()); 
                        setMazeElement(  X*3 ,  Y*(3)+2 , new Path()); 
                    }
                    
                }
            }
            
 
            //cout << "Maze has been successfully initialized" << endl<<endl; // Works
        }

        ~Maze() 
        {       
            for (int x = 0; x < (sizeMaze * 3) + 1; x++) 
            {
                for (int y = 0; y < (sizeMaze * 3) + 1; y++) 
                {
                    delete maze[x][y];
                }
            }
            //cout << "Maze is successfully deleted" << endl; // Works
        }
        MazeElement* getMazeElement(int x, int y) const 
        {
            if (x >= 0 && x < maze.size() && y >= 0 && y < maze[0].size()) 
            {
                return maze[x][y];
            } else 
            {
                return nullptr; // or handle the error as appropriate
            }
        }
        void printMaze() const {
            file << endl;
            for (int x = 0; x < (sizeMaze * 3) + 1; x++) 
            {
                for (int y = 0; y < (sizeMaze * 3) + 1; y++) 
                {
                    printBlockSymbol(*maze[x][y]);
                }
                 file << endl;
                cout << endl;
            }
            file << endl;
        }
        void setMazeElement(int y, int x, MazeElement* newElement) 
        {
            if (x >= 0 && x < maze.size() && y >= 0 && y < maze[x].size()) 
            {
                // Check if the current element is OutOfBounds
                if (dynamic_cast<OutOfBounds*>(maze[x][y]) == nullptr && dynamic_cast<Start*>(maze[x][y]) == nullptr) 
                {
                    delete maze[x][y]; // Delete the old element
                    maze[x][y] = newElement; // Set the new element
                }
            } 
        }

    private:
        int sizeMaze;
        vector<vector<MazeElement*>> maze;
};




int main() {
    
    srand(time(0)); 
    int size = 5;
    Maze myMaze(size);
    myMaze.printMaze();
    
    return 0;
}

void printBlockSymbol(const MazeElement& element) 
{
    switch (element.getSymbol()) 
    {
        case 'P': cout << "⬜" ; file << "⬜";
        break;
        case 'W': cout << "⬛";  file << "⬛";
        break;
        case 'C': cout << "🟦";  file << "🟦";
        break;
        case 'S': cout << "🟩";  file << "🟩";
        break;
        case 'E': cout << "🟥";  file << "🟥";
        break;
        case 'w': cout << "🟨";  file << "🟨";
        break;
        case 'X': cout << "⬛";  file << "⬛";
        break;
        default:
            cout << "Invalid value\n";
    }
}