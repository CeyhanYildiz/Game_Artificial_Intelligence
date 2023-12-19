#pragma once

#include <iostream>
#include <thread>

// Include the Maze header for GameThread's usage
#include "Maze.h"

class GameManager {
public:
	// Constructor
	explicit GameManager(const int numGames);

	// Function to start the game threads
	void startGames();

private:
	// Nested class representing a game thread
	class GameThread {
	public:
		// Constructor
		explicit GameThread(const int id);

		// Function to run the game thread
		void run() const;

	private:
		int threadId;  // Unique identifier for the game thread
	};

	friend class GameThread;  // Declare GameThread as a friend class

	int numberOfGames;  // Number of games to manage

	vector<thread> gameThreads;  // Vector to store game threads
	vector<GameThread> games;    // Vector to store GameThread instances
};
