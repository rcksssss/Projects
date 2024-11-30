// Copyright 2024 <Thomas Boyajian>
#include <iostream>
#include <string>
#include "EDistance.hpp"
#include <SFML/System.hpp>

int main() {
    std::string s1, s2;

    // Read input strings
    std::getline(std::cin, s1);
    std::getline(std::cin, s2);

    // Remove any carriage returns that might be present
    if (!s1.empty() && s1.back() == '\r') s1.pop_back();
    if (!s2.empty() && s2.back() == '\r') s2.pop_back();

    // Start timer
    sf::Clock clock;

    try {
        // Create EDistance object and compute alignment
        EDistance ed(s1, s2);
        int distance = ed.optDistance();
        std::string alignmentStr = ed.alignment();

        // Get elapsed time
        sf::Time t = clock.getElapsedTime();

        // Output results
        std::cout << "Edit distance = " << distance << std::endl;
        std::cout << alignmentStr;
        std::cout << "Execution time is " << t.asSeconds() << " seconds" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
