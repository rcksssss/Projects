// Copyright 2024 <Thomas Boyajian>

#include <fstream>
#include <cstddef>
#include <cmath>
#include "Universe.hpp"
#include "CelestialBody.hpp"

namespace NB {

// Default constructor
Universe::Universe() : elapsedTime_(0), radius_(0) {
    setBackground("image.jpg");
    // Image for background extra credit
    if (!font_.loadFromFile("LiberationMono-Regular.ttf")) {
        std::cerr << "Error loading font" << std::endl;
    }  // above is checking if the font is loaded or not
    timeText_.setFont(font_);
    timeText_.setCharacterSize(20);  // char size of font
    timeText_.setFillColor(sf::Color::White);  // font color
    timeText_.setPosition(10, 10);  // font position
}

Universe::Universe(const std::string& filename) {
    if (!loadFromFile(filename)) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
    }
    setBackground("image.jpg");  // Set background in constructor
}

size_t Universe::size() const { return bodies_.size(); }
double Universe::radius() const { return radius_; }
const CelestialBody& Universe::operator[](size_t i) const { return *(bodies_[i]); }

void Universe::step(double dt) {
    std::vector<sf::Vector2f> forces(bodies_.size(), sf::Vector2f(0, 0));

    // Calculate forces
    for (size_t i = 0; i < bodies_.size(); ++i) {
        for (size_t j = i + 1; j < bodies_.size(); ++j) {
            sf::Vector2f force = calculateForce(*bodies_[i], *bodies_[j]);
            forces[i] += force;
            forces[j] -= force;  // Equal and opposite force
        }
    }

    // Update velocities and positions
    for (size_t i = 0; i < bodies_.size(); ++i) {
        sf::Vector2f acceleration = forces[i] / bodies_[i]->getMass();

        // Update velocity
        sf::Vector2f newVelocity = bodies_[i]->getVelocity()
         + acceleration * static_cast<float>(dt);
        bodies_[i]->setVelocity(newVelocity);

        // Update position
        sf::Vector2f newPosition = bodies_[i]->getPosition()
         + newVelocity * static_cast<float>(dt);
        bodies_[i]->setPosition(newPosition);
    }

    // Update simulation time
    elapsedTime_ += dt;
    timeText_.setString("Elapsed Time: " + std::to_string(elapsedTime_) + " s");
}

// getter for elapsed time
double Universe::getElapsedTime()  const {
    return elapsedTime_;
}

void Universe::draw(sf::RenderTarget& window, sf::RenderStates states) const {
    sf::Vector2u windowSize = window.getSize();
    float scale = std::min(windowSize.x, windowSize.y) / (2.0f * radius_);

    // Draw background
    window.draw(backgroundSprite_, states);

    // Draw celestial bodies
    for (const auto& body : bodies_) {
        sf::Vector2f scaledPos(
            (body->getPosition().x * scale) + windowSize.x / 2.0f,
            (windowSize.y / 2.0f) - (body->getPosition().y * scale));
            // Flip y-axis

        sf::Sprite bodySprite = body->getSprite();
        bodySprite.setPosition(scaledPos);
        window.draw(bodySprite, states);
    }

    // draw elapsed time
    window.draw(timeText_, states);
}
/*void Universe::draw(sf::RenderTarget& window, sf::RenderStates states) const {
    sf::Vector2u windowSize = window.getSize();
    float scale = std::min(windowSize.x, windowSize.y) / (2.0f * radius_);

    // Draw background
    window.draw(backgroundSprite_, states);

    // Draw celestial bodies
    for (const auto& body : bodies_) {
        sf::Vector2f scaledPos(
            (body->getPosition().x * scale) + windowSize.x / 2.0f,
            (windowSize.y / 2.0f) - (body->getPosition().y * scale)  // Flip y-axis
        );

        // Draw a circle for each body
        sf::CircleShape shape(10.0f);  // 10 pixel radius, adjust as needed
        shape.setFillColor(sf::Color::White);
        shape.setOrigin(10.0f, 10.0f);  // Center the circle
        shape.setPosition(scaledPos);

        window.draw(shape, states);
    }
}*/

sf::Vector2f Universe::calculateForce(const CelestialBody& body1,
const CelestialBody& body2) const {
    const double G = 6.67430e-11;  // gravitational constant
    sf::Vector2f delta = body2.getPosition() - body1.getPosition();
    double distance = std::sqrt(delta.x * delta.x + delta.y * delta.y);

    // Avoid division by zero
    if (distance == 0) {
        return sf::Vector2f(0, 0);
    }

    double forceMagnitude = G * body1.getMass() * body2.getMass() / (distance * distance);
    return sf::Vector2f(
        static_cast<float>(forceMagnitude * delta.x / distance),
        static_cast<float>(forceMagnitude * delta.y / distance));
}

std::istream& Universe::read(std::istream& is) {
    size_t n;
    is >> n >> radius_;
    bodies_.clear();

    for (size_t i = 0; i < n; i++) {
        sf::Vector2f position, velocity;
        float mass;
        std::string filename;
        is >> position.x >> position.y >> velocity.x >> velocity.y >> mass >> filename;

        auto body = std::make_unique<CelestialBody>(position, velocity, mass, filename);
        bodies_.push_back(std::move(body));
    }

    return is;
}

std::ostream& Universe::write(std::ostream& os) const {
    os << bodies_.size() << " " << radius_ << std::endl;
    for (const auto& body : bodies_) {
        os << *body << std::endl;
    }
    return os;
}

bool Universe::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        return false;
    }

    file >> *this;
    return true;
}

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
