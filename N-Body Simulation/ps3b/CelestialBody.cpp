// Copyright 2024 <Thomas Boyajian>

#include "CelestialBody.hpp"

namespace NB {

CelestialBody::CelestialBody()
: position_(sf::Vector2f(0, 0)), velocity_(sf::Vector2f(0, 0)),
mass_(0), fileName_("") {}

// Constructor for ps3b
CelestialBody::CelestialBody(const sf::Vector2f& position,
const sf::Vector2f& velocity, float mass, const std::string& filename)
: position_(position), velocity_(velocity), mass_(mass), fileName_(filename) {
    if (!texture_.loadFromFile("nbody/" + filename)) {
        std::cerr << "Error loading texture: " << filename << std::endl;
    }

    // Set up the sprite with the loaded texture
    sprite_.setTexture(texture_);
    sprite_.setOrigin(texture_.getSize().x / 2.0f, texture_.getSize().y / 2.0f);
    setPosition(position);
}

// Getter functions which return private member variables
sf::Vector2f CelestialBody::getPosition()  const { return position_; }
sf::Vector2f CelestialBody::getVelocity()  const { return velocity_; }
float CelestialBody::getMass()             const { return mass_; }
// Getter for sprite

// Setter for position
void CelestialBody::setPosition(const sf::Vector2f& pos) {
    position_ = pos;
    sprite_.setPosition(pos);  // Update sprite position as well
}

// Setter for velocity
void CelestialBody::setVelocity(const sf::Vector2f& velocity) {
    velocity_ = velocity;
}

// update position based on velocity and time step
void CelestialBody::updatePosition(double dt) {
    position_ += velocity_ * static_cast<float>(dt);
    sprite_.setPosition(position_);  // Update sprite position as well
}

// update velocity based on acceleration and time step
void CelestialBody::updateVelocity(const sf::Vector2f& acceleration, double dt) {
    velocity_ += acceleration * static_cast<float>(dt);
}

// Draw function
void CelestialBody::draw(
sf::RenderTarget& window,
sf::RenderStates states
) const {
    window.draw(sprite_, states);
}

// Reads celestialbody data from an input stream
// Updated read method: now handles all member variables
std::istream& CelestialBody::read(std::istream& is) {
    is >> position_.x >> position_.y >> velocity_.x >> velocity_.y;
    is >> mass_ >> fileName_;

    if (!texture_.loadFromFile("nbody/" + fileName_)) {
        std::cerr << "Error: Could not load texture from file: " <<
        fileName_ << std::endl;
    }

    // Set up sprite with the loaded texture
    sprite_.setTexture(texture_);
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
