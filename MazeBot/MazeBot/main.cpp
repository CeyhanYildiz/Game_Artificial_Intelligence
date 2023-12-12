// Game
#include "Gamethread.h"

int main() {
    GameManager gameManager(1); 
    // More than 2 bug : Thread 1885405251 started.
    // Thread 2 started.

    gameManager.startGames();

    return 0;
}
