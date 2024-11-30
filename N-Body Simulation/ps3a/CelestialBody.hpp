// Copyright 2024 <Thomas Boyajian>

#pragma once

#include <iostream>
#include <memory>

#include <SFML/Graphics.hpp>

namespace NB {
class CelestialBody: public sf::Drawable {
 public:
    CelestialBody();  // Required

    std::istream& read(std::istream& is);
    std::ostream& write(std::ostream& os) const;

    sf::Vector2f position() const;  // Optional
    sf::Vector2f velocity() const;  // Optional
    float mass() const;  // Optional
    sf::Sprite getSprite() const;  // Needed to get the sprite

 protected:
    void draw(sf::RenderTarget& window, sf::RenderStates states) const override;
     // From sf::Drawable

 private:
    // Fields and helper methods go here
    // Variables following the getters from above.
    sf::Vector2f position_;
    sf::Vector2f velocity_;
    float mass_;

    // Add extra internal variables
    std::string fileName_;
    sf::Texture texture_;
    sf::Sprite sprite_;
};

std::istream& operator>>(std::istream& is, CelestialBody& uni);
std::ostream& operator<<(std::ostream& os, const CelestialBody& uni);
}  // namespace NB
