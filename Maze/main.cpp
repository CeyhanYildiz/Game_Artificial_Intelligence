#include <iostream> //Standard Input/Output Streams
#include <vector> // Dynamic Array
#include <string> //String Class 
#include <fstream> //File Stream
#include <ctime>   // Time Functions 
#include <random> // Include for modern random number generation
//#include <windows.h>
//#include <stdlib.h> // system(clear)
//#include <cstdlib> // General Purpose Functions
using namespace std;

ofstream file("output.txt", ios::app); // GLOBAL!!!!!

// Base class
class MazeElement {
    public:
        // Pure virtual functions that must be implemented by derived classes
        virtual string getDescription() const = 0;  // Returns a string description of the element
        virtual char getSymbol() const = 0;         // Returns a character symbol representing the element
        virtual ~MazeElement() {}                   // Virtual destructor to allow proper cleanup of derived types
};

// Derived class representing a wall in the maze
class Wall : public MazeElement {
    public:
        string getDescription() const override      {       return "Wall";          } // Description of the Wall element 
        char getSymbol() const override             {       return 'W';             }// Character symbol for Wall
};

// Derived class representing a path in the maze
class Path : public MazeElement {
    public:
        string getDescription() const override      {       return "Path";          } // Description of the Path element
        char getSymbol() const override             {       return 'P';             } // Character symbol for Path
};

// Derived class representing a checkpoint in the maze
class Checkpoint : public MazeElement {
    public:
        string getDescription() const override      {       return "Checkpoint";    } // Description of the Checkpoint element
        char getSymbol() const override             {       return 'C';             } // Character symbol for Checkpoint
};

// Derived class representing the start position in the maze
class Start : public MazeElement {
    public:
        string getDescription() const override      {       return "Start";         } // Description of the Start element
        char getSymbol() const override             {       return 'S';             } // Character symbol for Start
};

// Derived class representing a wrong path in the maze
class WrongPath : public MazeElement {
    public:
        string getDescription() const override      {       return "Wrong path";    } // Description of the Wrong Path element
        char getSymbol() const override             {       return 'w';             } // Character symbol for Wrong Path
};

// Derived class representing the end position in the maze
class End : public MazeElement {
    public:
        string getDescription() const override      {       return "End";           } // Description of the End element
        char getSymbol() const override             {       return 'E';             } // Character symbol for End
};

//Derived class representing the OutOfBounds position in the maze
class OutOfBounds : public MazeElement { 
    public:
        string getDescription() const override      {       return "Out of Bounds"; } // Description of the Out of Bounds element
        char getSymbol() const override             {       return 'X';             } // Character symbol for Out of Bounds
};





void printBlockSymbol(const MazeElement& element); //GLOBAL!!!!!
void printBlockSymbol_CMD(const MazeElement& element); // GLOBAL!!!!!

class Maze {
    public:
        // Makes a Grid for maze
        Maze(int size) : sizeMaze(size) {
            int TrueSize = sizeMaze * 3;
            maze.resize((sizeMaze * 3) + 1, vector<MazeElement*>((sizeMaze * 3) + 1));
            for (int x = 0; x < (sizeMaze * 3) + 1; x++) {
                for (int y = 0; y < (sizeMaze * 3) + 1; y++) {
                    if (x == 0 || x == TrueSize || y == 0 || y == TrueSize) {       maze[x][y] = new OutOfBounds(); } // Edge of the maze
                    else if (y % 3 == 0 || x % 3 == 0)                      {       maze[x][y] = new Wall();        } // Wall
                    else                                                    {       maze[x][y] = new Path();        } // Cell Path 
                }
            }
            // The exit positions for the maze
            // These positions are calculated to be near the bottom-right corner of the maze
            int quarter = TrueSize + 1;
            int q2 = quarter - 2; 
            int q3 = quarter - 3;
            vector<pair<int, int>> endPositions = { {q2, q2}, {q2, q3}, {q3, q2}, {q3, q3} };          
            for (const auto& pos : endPositions)                            {  setMazeElement(pos.first, pos.second, new End());   } // Add End   
            vector<pair<int, int>> startPositions = { {1, 1}, {1, 2}, {2, 1}, {2, 2} };
            for (const auto& pos : startPositions)                          { setMazeElement(pos.first, pos.second, new Start());  } // Add Start
            //cout << "Maze has been successfully initialized" << endl<<endl; // Works
            MazeCellSize = sizeMaze * sizeMaze;
            TrueMazeSize = (sizeMaze * 3 + 1)*(sizeMaze * 3 + 1);
        }
        // Delets Maze
        ~Maze() {       
            for (int x = 0; x < (sizeMaze * 3) + 1; x++) {
                for (int y = 0; y < (sizeMaze * 3) + 1; y++)                {       delete maze[x][y];              }
            }
            //cout << "Maze is successfully deleted" << endl; // Works
        }

        // Prints chossing Cords
        void printMazeElement(int x, int y) const {
            if (x >= 0 && x < maze.size() && y >= 0 && y < maze[x].size())  {       printBlockSymbol(*maze[x][y]); cout << endl;    } 
            else                                                            {       cout << "Invalid coordinates" << endl;          }}
        // Gets Symbool
        char getMazeElementSymbol(int x, int y) const                       {       return maze[y][x]->getSymbol();                 }
        // Gets Description
        string getMazeElementDescription(int x, int y) const                {       return maze[y][x]->getDescription();            }
        
        // Prints Maze
        void printMaze() const {
            file << endl;
            for (int x = 0; x < (sizeMaze * 3) + 1; x++) {
                for (int y = 0; y < (sizeMaze * 3) + 1; y++)                {       printBlockSymbol(*maze[x][y]);                  } 
                file << endl;
                cout << endl;
            }
            file << endl;
        }
        void printMaze_CMD() const {
            file << endl;
            for (int x = 0; x < (sizeMaze * 3) + 1; x++) {
                for (int y = 0; y < (sizeMaze * 3) + 1; y++)                {       printBlockSymbol_CMD(*maze[x][y]);              }
                file << endl;
                cout << endl;
            }
            file << endl;
        } 
        // Implements : The Binary Tree Algorithm to generate the maze layout.
        // Randomly removes either the top wall or the left wall of each cell.
        void Binary_Tree_Algorithm() {
            mt19937 rng(time(NULL)); // Create a random number generator, Mersenne primes
            uniform_int_distribution<int> dist(1, 2); // Distribute between 1 and 2
            for (int row = 0; row < sizeMaze; row++) {
                for (int col = 0; col < sizeMaze; col++) {
                    int randomNumber = dist(rng); // Generate a random number (1 or 2)
                    // Calculate common positions
                    int posX = col * 3;
                    int posY = row * 3;
                    if (randomNumber == 2) {
                        // Decision to remove left or up wall based on boundary conditions
                        if (getMazeElementSymbol(posX + 1, posY)== 'X')     {       removeLeftWall(posX, posY);     } 
                        else                                                {       removeUpWall(posX, posY);       }
                    } else {
                        // Similar decision as above
                        if (getMazeElementSymbol(posX, posY + 1)== 'X')     {       removeUpWall(posX, posY);       } 
                        else                                                {       removeLeftWall(posX, posY);     }
                    }
                }
            }
        }
        int getSizeMaze()                                                   {       return sizeMaze;                }
        int getMazeCellSize()                                               {       return MazeCellSize;            }
        int getTrueMazeSize()                                               {       return TrueMazeSize;            }

    private:
        // Maze Size
        int sizeMaze;
        // How much Cells are in the maze
        int MazeCellSize;
        // True maze size 'arrey'
        int TrueMazeSize;
        // Kinda dubbel linklist
        vector<vector<MazeElement*>> maze;
        // Set Maze Element
        void setMazeElement(int y, int x, MazeElement* newElement) {
            if (x >= 0 && x < maze.size() && y >= 0 && y < maze[x].size()) {
                // Check if the current element is OutOfBounds or Start
                if (dynamic_cast<OutOfBounds*>(maze[x][y]) == nullptr &&
                    dynamic_cast<Start*>(maze[x][y]) == nullptr &&
                    dynamic_cast<End*>(maze[x][y]) == nullptr) {      
                    delete maze[x][y]; // Delete the old element
                    maze[x][y] = newElement;    } // Set the new element
            } 
        }
        // Removes the left wall at the specified position
        void removeLeftWall(int x, int y) {
            setMazeElement(x, y + 1, new Path());
            setMazeElement(x, y + 2, new Path());
        }
        // Removes the up wall at the specified position
        void removeUpWall(int x, int y) {
            setMazeElement(x + 1, y, new Path());
            setMazeElement(x + 2, y, new Path());
        }
};

int main() 
{  
    Maze myMaze(5);
    myMaze.printMaze(); // TEST DELET WHEN DONE 
    myMaze.Binary_Tree_Algorithm();
    myMaze.printMaze();
    
    cout << "myMaze.getSizeMaze()     " << myMaze.getSizeMaze() << endl << "myMaze.getMazeCellSize() " << myMaze.getMazeCellSize() << endl << "myMaze.getTrueMazeSize() " << myMaze.getTrueMazeSize() << endl;
    return 0;
}


// GLOBAL FIX IT !!!!
void printBlockSymbol(const MazeElement& element) {
    switch (element.getSymbol()) {
        case 'P': cout << "⬜"; file << "⬜";
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
        case 'X': cout << "⬛";;  file << "⬛";
            break;
        default:  cout << "Invalid value\n";
            break;
    }
}
void printBlockSymbol_CMD(const MazeElement& element) {
    switch (element.getSymbol()) {
        case 'P': cout << " "; file << "⬜";
            break;
        case 'W': cout << " ";  file << "⬛";
            break;
        case 'C': cout << " ";  file << "🟦";
            break;
        case 'S': cout << " ";  file << "🟩";
            break;
        case 'E': cout << " ";  file << "🟥";
            break;
        case 'w': cout << " ";  file << "🟨";
            break;
        case 'X': cout << ".";;  file << "⬛";
            break;
        default:  cout << "Invalid value\n";
            break;
    }
}