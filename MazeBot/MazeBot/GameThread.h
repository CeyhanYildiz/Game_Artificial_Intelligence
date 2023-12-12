#pragma once

#include <iostream>
// Class
#include <thread>

// Game
#include "Maze.h"

class GameManager {
public:
	explicit GameManager(int numGames);

	void startGames();

private:
	class GameThread {
	public:
		explicit GameThread(int id);

		void run() const;

	private:
		int threadId;
	};

	friend class GameThread;  // Declare GameThread as a friend class

	int numberOfGames;

	vector<thread> gameThreads;
	vector<GameThread> games;
};
