// Copyright 2024 <Thomas Boyajian>

#pragma once

#include <cstddef>
#include <vector>
#include <string>
#include <memory>
#include <SFML/Graphics.hpp>
#include "CelestialBody.hpp"

namespace NB {
class Universe: public sf::Drawable {
 public:
    explicit Universe();  // Required
    explicit Universe(const std::string& filename);  // Optional

    std::istream& read(std::istream& is);
    std::ostream& write(std::ostream& os) const;

    size_t size() const;  // Optional
    double radius() const;  // Optional

    std::vector<std::unique_ptr<CelestialBody>> bodies_;

    const CelestialBody& operator[](size_t i) const;  // Optional

    void step(double dt);
    double getElapsedTime() const;  // Need this for elapsed time
    // Implemented in part b, behavior for part a is undefined
 protected:
    void draw(sf::RenderTarget& window,
    sf::RenderStates states) const override;
    // From sf::Drawable
 private:
    // current simulation time
    double t_ = 0.0;
    sf::Font font_;  // font for displaying text
    sf::Text timeText_;  // text obj for displaying time

    // Fields and helper functions go here
    bool loadFromFile(const std::string& filename);
    void setBackground(const std::string& filename);

    // calculates force between two bodies
    sf::Vector2f calculateForce(const CelestialBody& body1,
    const CelestialBody& body2) const;

    double elapsedTime_;  // track elapsed time
    double radius_;
    sf::Texture backgroundTexture_;  // For background extra credit
    sf::Sprite backgroundSprite_;  // For background extra credit

    // gravitational constant
    static constexpr double G = 6.67430e-11;
};

std::istream& operator>>(std::istream& is, Universe& uni);
std::ostream& operator<<(std::ostream& os, const Universe& uni);
}  // namespace NB
