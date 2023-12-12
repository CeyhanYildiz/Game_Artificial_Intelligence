#pragma once

// C++ Standard Library
#include <iostream>
#include <thread>
#include <vector>

// Game
#include "Maze.h"

using namespace std;

class GameManager {
public:
    explicit GameManager(int numGames) : numberOfGames(numGames) {}

    void startGames() {
        // Reserve space to avoid frequent reallocations
        games.reserve(numberOfGames);

        // Start and run game threads
        for (int i = 1; i <= numberOfGames; ++i) {
            games.emplace_back(i);
            gameThreads.emplace_back(&GameThread::run, &games.back());
            // Optional: Introduce a delay between starting threads if needed
            this_thread::sleep_for(chrono::seconds(1));
        }

        // Join all the game threads after the loop
        for (auto& thread : gameThreads) {
            thread.join();
        }
    }


private:
    class GameThread {
    public:
        explicit GameThread(int id) : threadId(id) {}

        void run() const {
            // Maze object creation and any additional setup
            Maze game(10, 29, "MazeBot " + to_string(threadId));

            // Use threadId to differentiate between threads if needed
            cout << "Thread " << threadId << " started.\n";

            game.run();
        }

    private:
        int threadId;
    };

    int numberOfGames;
    vector<thread> gameThreads;
    vector<GameThread> games;
};
