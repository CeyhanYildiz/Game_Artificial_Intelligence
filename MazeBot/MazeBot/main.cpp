// Game
#include "Gamethread.h"

int main() {
	// Make Game
	GameManager gameManager(1);

	// Run Game's
	gameManager.startGames();

	return 0;
}
//#include <SFML/Graphics.hpp>
//#include <iostream>
//
//int main() {
//    // Create a window
//    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Pixel Info Example");
//
//    while (window.isOpen()) {
//        sf::Event event;
//        while (window.pollEvent(event)) {
//            if (event.type == sf::Event::Closed)
//                window.close();
//        }
//
//        // Get the mouse position in screen coordinates
//        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
//
//        // Map the screen coordinates to world coordinates
//        sf::Vector2f worldPosition = window.mapPixelToCoords(mousePosition);
//
//        // Display information about the pixel under the mouse
//        std::cout << "Mouse Position (Screen): " << mousePosition.x << ", " << mousePosition.y << std::endl;
//        std::cout << "Mouse Position (World): " << worldPosition.x << ", " << worldPosition.y << std::endl;
//
//        // Note: You can use the worldPosition to retrieve color information if you have objects drawn on the screen.
//
//        window.clear();
//        // Draw your objects here
//        window.display();
//    }
//
//    return 0;
//}