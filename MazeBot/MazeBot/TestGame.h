#pragma once
#include <SFML/Graphics.hpp>

class Game {
public:
    Game();
    void run();

private:
    void handleEvents();
    void update();
    void render();

private:
    sf::RenderWindow window;
    sf::CircleShape shape;
};
