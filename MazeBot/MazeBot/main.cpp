// C++
#include <iostream>
#include <thread>
#include <vector>

// Game
#include "Maze.h"

using namespace std;

int main() {
    const int numberOfGames = 5;
    vector<thread> gameThreads;

    for (int i = 1; i <= numberOfGames; ++i) {
        // Create a thread to make the gam
        gameThreads.emplace_back([i]() {
            // Maze object creation and any additional setup
            Maze game(10, 29, "MazeBot " + to_string(i));

            // You can use i to differentiate between threads if needed
            cout << "Thread " << i << " started.\n";

            game.run();
            });
        //this_thread::sleep_for(chrono::seconds(1));
    }

    // Join all the game threads after the loop
    for (auto& thread : gameThreads) {
        thread.join();
    }

    return 0;
}
