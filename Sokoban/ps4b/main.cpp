// Copyright 2024 <Thomas Boyajian>

#include <fstream>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Sokoban.hpp"

int main(int argc, char* argv[]) {
    // Check for level file argument
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <level_file>\n";
        return 1;
    }

    try {
        // Initialize game and level
        SB::Sokoban game;
        std::ifstream levelFile(argv[1]);
        if (!levelFile) {
            std::cerr << "Error: Could not open level file: " << argv[1] << "\n";
            return 1;
        }
        levelFile >> game;

        // Create game window
        sf::RenderWindow window(
            sf::VideoMode(game.width() * SB::Sokoban::TILE_SIZE,
                         game.height() * SB::Sokoban::TILE_SIZE),
            "Sokoban");

        // Game loop
        while (window.isOpen()) {
            // Process inputs
            sf::Event event;
            while (window.pollEvent(event)) {
                switch (event.type) {
                    case sf::Event::Closed:
                        window.close();
                        break;

                    case sf::Event::KeyPressed:
                        // Handle game controls
                        switch (event.key.code) {
                            case sf::Keyboard::W:
                            case sf::Keyboard::Up:
                                game.movePlayer(SB::Direction::Up);
                                break;

                            case sf::Keyboard::S:
                            case sf::Keyboard::Down:
                                game.movePlayer(SB::Direction::Down);
                                break;

                            case sf::Keyboard::A:
                            case sf::Keyboard::Left:
                                game.movePlayer(SB::Direction::Left);
                                break;

                            case sf::Keyboard::D:
                            case sf::Keyboard::Right:
                                game.movePlayer(SB::Direction::Right);
                                break;

                            case sf::Keyboard::R:  // Reset level
                                game.reset();
                                break;

                            case sf::Keyboard::Z:  // Undo move
                                game.undo();
                                break;

                            default:
                                break;
                        }
                        break;

                    default:
                        break;
                }
            }

            // Update display
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
