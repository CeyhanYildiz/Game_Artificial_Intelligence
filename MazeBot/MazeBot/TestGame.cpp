#include "TestGame.h"


Game::Game() : window(sf::VideoMode(200, 200), "SFML works!"), shape(100.f) {
    shape.setFillColor(sf::Color::Green);
}

void Game::run() {
    while (window.isOpen()) {
        handleEvents();
        update();
        render();
    }
}

void Game::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
    }
}

void Game::update() {
    // Add any game logic or update code here
}

void Game::render() {
    window.clear();
    window.draw(shape);
    window.display();
}
