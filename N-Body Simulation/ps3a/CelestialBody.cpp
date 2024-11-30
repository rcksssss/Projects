// Copyright 2024 <Thomas Boyajian>

#include "CelestialBody.hpp"

namespace NB {

// Default constructor
CelestialBody::CelestialBody()
: position_(sf::Vector2f(0, 0)), velocity_(sf::Vector2f(0, 0)),
mass_(0), fileName_("") { }

// Getter functions which return private member variables
sf::Vector2f CelestialBody::position()  const { return position_; }
sf::Vector2f CelestialBody::velocity()  const { return velocity_; }
float CelestialBody::mass()             const { return mass_; }
sf::Sprite CelestialBody::getSprite()   const { return sprite_; }
// Getter for sprite

// Draw function
void CelestialBody::draw(
sf::RenderTarget& window,
sf::RenderStates states
) const {
    window.draw(sprite_, states);
}

// Reads celestialbody data from an input stream
std::istream& CelestialBody::read(std::istream& is) {
    is >> position_.x >> position_.y >> velocity_.x >> velocity_.y;
    is >> mass_ >> fileName_;

    std::string fileName = "nbody/" + fileName_;

    if (!texture_.loadFromFile(fileName)) {
        if (!texture_.loadFromFile(fileName)) {
            std::cerr << "Error: Could not load texture from file: "
                      << fileName_ << " or " << fileName << std::endl;
        }
    }

    sprite_.setTexture(texture_);
    // Set the origin of the sprite to its center
    sprite_.setOrigin(texture_.getSize().x / 2.0f, texture_.getSize().y / 2.0f);
    sprite_.setPosition(position_);
    return is;
}

// Add a constant because our CelestialBody uni is a constant in the
// << operator.
std::ostream& CelestialBody::write(std::ostream& os) const {
    os << position_.x << " " << position_.y << " " << velocity_.x << " ";
    os << velocity_.y << " " << mass_ << " " << fileName_;
    return os;
}

std::istream& operator>>(std::istream& is, CelestialBody& uni) {
    return uni.read(is);
}

std::ostream& operator<<(std::ostream& os, const CelestialBody& uni) {
    return uni.write(os);
}

};  // namespace NB
