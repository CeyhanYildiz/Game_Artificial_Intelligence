// Game
#include "GameThread.h"

GameManager::GameManager(int numGames) : numberOfGames(numGames) {}

void GameManager::startGames() {
	// Reserve space to avoid frequent reallocations
	games.reserve(numberOfGames);

	// Start and run game threads
	for (int i = 1; i <= numberOfGames; ++i) {
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

GameManager::GameThread::GameThread(int id) : threadId(id) {}

void GameManager::GameThread::run() const {
	// Maze object creation and any additional setup
	Maze game(10, 29, "MazeBot " + to_string(threadId));

	// Use threadId to differentiate between threads if needed
	cout << "Thread " << threadId << " started.\n";

	game.run();
}