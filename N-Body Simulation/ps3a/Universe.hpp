// Copyright 2024 <Thomas Boyajian>

#pragma once

#include <cstddef>
#include <vector>
#include <string>
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

    const CelestialBody& operator[](size_t i) const;  // Optional

    void step(double dt);
    // Implemented in part b, behavior for part a is undefined
 protected:
    void draw(sf::RenderTarget& window,
    sf::RenderStates states) const override;
    // From sf::Drawable
 private:
    // Fields and helper functions go here
    bool loadFromFile(const std::string& filename);
    std::vector<CelestialBody> bodies_;
    double radius_;
    sf::Texture backgroundTexture_;  // For background extra credit
    sf::Sprite backgroundSprite_;  // For background extra credit
    void setBackground(const std::string& filename);
};

std::istream& operator>>(std::istream& is, Universe& uni);
std::ostream& operator<<(std::ostream& os, const Universe& uni);
}  // namespace NB
