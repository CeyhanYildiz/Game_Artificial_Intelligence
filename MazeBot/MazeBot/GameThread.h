#pragma once

// C++
#include <iostream>
#include <thread>

// Game
#include "Maze.h"

using namespace std;


class GameManager {
public:
    GameManager(int numGames) : numberOfGames(numGames) {}

    void startGames() {
        for (int i = 1; i <= numberOfGames; ++i) {
            games.emplace_back(i);
            gameThreads.emplace_back(&GameThread::run, &games.back());
            //this_thread::sleep_for(chrono::seconds(4));
        }

        // Join all the game threads after the loop
        for (auto& thread : gameThreads) {
            thread.join();
        }
    }

private:
    class GameThread {
    public:
        GameThread(int id) : threadId(id) {}

        void run() {
            // Maze object creation and any additional setup
            Maze game(10, 29, "MazeBot " + to_string(threadId));

            // You can use threadId to differentiate between threads if needed
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

