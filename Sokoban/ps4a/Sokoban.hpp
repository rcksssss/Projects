// Copyright 2024 <Thomas Boyajian>

#pragma once

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

namespace SB {
enum class Direction {
    Up, Down, Left, Right
};

class Sokoban : public sf::Drawable {
 public:
    static const int TILE_SIZE = 64;

    Sokoban();
    explicit Sokoban(const std::string&);  // Optional

    unsigned int pixelHeight() const;  // Optional
    unsigned int pixelWidth() const;  // Optional

    unsigned int height() const;
    unsigned int width() const;

    sf::Vector2u playerLoc() const;

    bool isWon() const;  // used for part b

    void movePlayer(Direction dir);
    void reset();

    void undo();  // Optional XC
    void redo();  // Optional XC

 protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

 private:
    // Dimensions
    unsigned int m_width{0};
    unsigned int m_height{0};

    // Player position
    sf::Vector2u m_playerPos{0, 0};

    // Level data
    std::vector<std::vector<char>> m_grid;

    // Textures
    sf::Texture m_wallTexture;
    sf::Texture m_floorTexture;
    sf::Texture m_boxTexture;
    sf::Texture m_storageTexture;
    sf::Texture m_playerTexture;

    friend std::istream& operator>>(std::istream& in, Sokoban& s);
    friend std::ostream& operator<<(std::ostream& out, const Sokoban& s);
};

std::ostream& operator<<(std::ostream& out, const Sokoban& s);
std::istream& operator>>(std::istream& in, Sokoban& s);
}  // namespace SB
