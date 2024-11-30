// Copyright 2024 <Thomas Boyajian>

#pragma once

#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>

namespace NB {
class CelestialBody: public sf::Drawable {
 public:
    CelestialBody();
    CelestialBody(const sf::Vector2f& position, const sf::Vector2f& velocity,
    float mass, const std::string& filename);  // Required
    // Updated constructor for ps3b

    std::istream& read(std::istream& is);
    std::ostream& write(std::ostream& os) const;

    sf::Vector2f getPosition() const;  // Optional
    sf::Vector2f getVelocity() const;  // Optional
    float getMass() const;  // Optional
    sf::Sprite getSprite() const { return sprite_; }  // Needed to get the sprite

    // New setters for ps3b, allows updating position and velo
    void setPosition(const sf::Vector2f& pos);
    void setVelocity(const sf::Vector2f& velocity);

    // new methods for ps3b, updateds position and velo for simulation
    void updatePosition(double dt);
    void updateVelocity(const sf::Vector2f& acceleration, double dt);

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
