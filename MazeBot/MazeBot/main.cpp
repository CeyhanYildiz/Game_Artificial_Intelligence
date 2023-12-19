// Game
#include "Gamethread.h"

int main() {
	// Create GameManager instance with a specified ID (1 in this case)
	GameManager gameManager(1);

	// Start the game(s) using the GameManager
	gameManager.startGames();

	// Exit the program with a success status
	return 0;
}