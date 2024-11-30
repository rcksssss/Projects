// Copyright 2024 <Thomas Boyajian>

#include <iostream>
#include "Universe.hpp"
#include "CelestialBody.hpp"
#include <SFML/Graphics.hpp>

int main() {
    // Create universe obj to hold celestial bodies
    NB::Universe universe;

    // Read universe data
    std::cin >> universe;

    sf::RenderWindow window(sf::VideoMode(800, 800),
     "Ps3a: [N-Body Simulation]");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();  // Clear before drawing

        window.draw(universe);  // Draw the universe

        window.display();  // Display the drawing
    }

    return EXIT_SUCCESS;
}
