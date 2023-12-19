// Game
#include "GameThread.h"

// GameManager constructor
GameManager::GameManager(int numGames) : numberOfGames(numGames) {}

// Function to start and run multiple game threads
void GameManager::startGames() {
	// Reserve space to avoid frequent reallocations
	games.reserve(numberOfGames);

	// Start and run game threads
	for (int i = 1; i <= numberOfGames; ++i) {
		// Create a new Game object and corresponding thread
		games.emplace_back(i);
		gameThreads.emplace_back(&GameThread::run, &games.back());

		// Optional: Introduce a delay between starting threads if needed
		this_thread::sleep_for(chrono::seconds(2));
	}

	// Join all the game threads after the loop
	for (auto& thread : gameThreads) {
		thread.join();
	}
}

// GameThread constructor
GameManager::GameThread::GameThread(int id) : threadId(id) {}

// Function to run a game thread
void GameManager::GameThread::run() const {
	// Maze object creation and any additional setup
	Maze game(10, 29, "MazeBot " + to_string(threadId));

	// Use threadId to differentiate between threads if needed
	cout << "Thread " << threadId << " started.\n";

	// Run the game
	game.run();
}