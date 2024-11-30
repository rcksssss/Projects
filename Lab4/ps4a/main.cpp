// Copyright 2024 <Thomas Boyajian>

#include <fstream>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Sokoban.hpp"

int main(int argc, char* argv[]) {
    // Check command line arguments
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <level_file>\n";
        return 1;
    }
try {
        // Create game instance
        SB::Sokoban game;

        // Load level from file
        std::ifstream levelFile(argv[1]);
        if (!levelFile) {
            std::cerr << "Error: Could not open level file: " << argv[1] << "\n";
            return 1;
        }
        levelFile >> game;

        // Debug output - print the loaded level to console
        std::cout << "Loaded level:\n" << game;

        // Create window sized to the level
        sf::RenderWindow window(
            sf::VideoMode(game.width() * SB::Sokoban::TILE_SIZE,
                         game.height() * SB::Sokoban::TILE_SIZE),
            "Sokoban - Part A");

        // Main game loop
        while (window.isOpen()) {
            // Handle events
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
            }

            // Clear, draw, display
            window.clear(sf::Color::Black);
            window.draw(game);
            window.display();
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

return 0;
}
