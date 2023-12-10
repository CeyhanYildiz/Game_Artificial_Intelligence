// Class
#include "Maze.h"

// namespace
using namespace std;

int main() {

    int count = 1;
    while (count)
    {
        // Make game
        Maze game(150, "MazeBot " + to_string(count));
        count++;
        // Make AI
            //Here

        // Solve
        game.run();  // game.run(); = Its a loop FIX!
    }


    return 0;
}