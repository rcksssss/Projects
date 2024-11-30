// Copyright 2024 <Thomas Boyajian>

#include <iostream>
#include <string>
#include "Universe.hpp"
#include "CelestialBody.hpp"
#include <SFML/Graphics.hpp>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <T> <dt>" << std::endl;
        return 1;
    }

    double T = std::stod(argv[1]);  // Total simulation time
    double dt = std::stod(argv[2]);  // Time step

    // Create universe object to hold celestial bodies
    NB::Universe universe;

    // Read universe data from stdin
    std::cin >> universe;

    sf::RenderWindow window(sf::VideoMode(800, 800), "N-Body Simulation");

    // For tracking simulation time
    double elapsed = 0.0;

    while (window.isOpen() && elapsed < T) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Perform simulation step
        universe.step(dt);
        elapsed += dt;

        window.clear();
        window.draw(universe);
        window.display();
    }

    // Output final state of the universe
    std::cout << universe;

    return 0;
}
