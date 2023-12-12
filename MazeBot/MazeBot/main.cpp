// Game
#include "Gamethread.h"

int main() {
    GameManager gameManager(30); // FIX bug if more than a few it does not print properly
    gameManager.startGames();

    return 0;
}
