// Copyright 2024 <Thomas Boyajian>

#include <fstream>
#include <cstddef>
#include "Universe.hpp"
#include "CelestialBody.hpp"

namespace NB {

// Default constructor for Universe
Universe::Universe() : radius_(0) {
    setBackground("image.jpg");  // Image for background extra credit
}

Universe::Universe(const std::string& filename) {
    if (!loadFromFile(filename)) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
    }
    setBackground("image.jpg");  // Set background in constructor
}

size_t Universe::size()     const { return bodies_.size(); }
double Universe::radius()   const { return radius_; }
const CelestialBody& Universe::operator[](size_t i) const { return bodies_[i]; }

// This will be used for part b
void Universe::step(double dt) { }

void Universe::draw(sf::RenderTarget& window, sf::RenderStates states) const {
    sf::Vector2u windowSize = window.getSize();
    float scale = std::min(windowSize.x, windowSize.y) / (2.0f * radius_);
    // Above calculates the scale for the window size needed for each simulation

    window.draw(backgroundSprite_, states);  // Draws the background
    for (const auto& body : bodies_) {
        sf::Vector2f scaledPos = sf::Vector2f(  // Calculates scaled position
          (body.position().x * scale) + windowSize.x / 2.0f,
          (-body.position().y * scale) + windowSize.y / 2.0f);
          // Flips the y-axis

    sf::Sprite bodySprite = body.getSprite();  // Get body sprite
    bodySprite.setPosition(scaledPos);  // Set scale position
    window.draw(bodySprite, states);  // Draw body
    }
    /*for(size_t i = 0; i < bodies_.size(); i++){
        window.draw(bodies_[i], states);
    }*/
}

// Read universe data from an input stream
std::istream& Universe::read(std::istream& is) {
    size_t n;
    is >> n >> radius_;
    bodies_.resize(n);

    for (size_t i = 0; i < n; i++) {
        is >> bodies_[i];
    }

    return is;
}

// Write universe data to an output stream
std::ostream& Universe::write(std::ostream& os) const {
    os << bodies_.size() << " " << radius_ << std::endl;
    for (size_t i = 0; i < bodies_.size(); i++) {
        os << bodies_[i] << std::endl;
    }
    return os;
}

// Load universe data from a file
bool Universe::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        return false;
    }

    file >> *this;
    return true;
}

// Needed for setting the background image
void Universe::setBackground(const std::string& filename) {
    if (!backgroundTexture_.loadFromFile(filename)) {
        std::cerr << ("Error: Could not load background texture: " + filename);
    }
    backgroundSprite_.setTexture(backgroundTexture_);
    backgroundSprite_.setScale(
        sf::Vector2f(800.0f / backgroundTexture_.getSize().x,
         800.0f / backgroundTexture_.getSize().y));
}

// Overload >> operator to read universe data
std::istream& operator>>(std::istream& is, Universe& uni) {
    return uni.read(is);
}

// Overload << operator to write universe data
std::ostream& operator<<(std::ostream& os, const Universe& uni) {
    return uni.write(os);
}

}  // namespace NB
