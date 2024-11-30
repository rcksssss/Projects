// Copyright 2024 <Thomas Boyajian>

#include "Sokoban.hpp"
#include <stdexcept>
#include <string>
#include <fstream>

namespace SB {

Sokoban::Sokoban() {
    // Load textures
    const std::string texturePath = "sokoban/";

    if (!m_wallTexture.loadFromFile(texturePath + "block_06.png") ||
        !m_floorTexture.loadFromFile(texturePath + "ground_01.png") ||
        !m_boxTexture.loadFromFile(texturePath + "crate_03.png") ||
        !m_storageTexture.loadFromFile(texturePath + "ground_04.png") ||
        !m_playerTexture.loadFromFile(texturePath + "player_05.png")) {
        throw std::runtime_error("Failed to load one or more textures");
    }
}

Sokoban::Sokoban(const std::string& filename) : Sokoban() {
    std::ifstream file(filename);
    if (file) {
        file >> *this;
    } else {
        throw std::runtime_error("Could not open file: " + filename);
    }
}

unsigned int Sokoban::height() const {
    return m_height;
}

unsigned int Sokoban::width() const {
    return m_width;
}

unsigned int Sokoban::pixelHeight() const {
    return m_height * TILE_SIZE;
}

unsigned int Sokoban::pixelWidth() const {
    return m_width * TILE_SIZE;
}

sf::Vector2u Sokoban::playerLoc() const {
    return m_playerPos;
}

bool Sokoban::isWon() const {
    return false;  // Part B implementation
}

void Sokoban::movePlayer(Direction) {
    // Part B implementation
}

void Sokoban::reset() {
    // Part B implementation
}

void Sokoban::undo() {
    // Optional XC implementation
}

void Sokoban::redo() {
    // Optional XC implementation
}

void Sokoban::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    sf::Sprite sprite;

    // Draw the game board
    for (unsigned int y = 0; y < m_height; ++y) {
        for (unsigned int x = 0; x < m_width; ++x) {
            char cell = m_grid[y][x];
            float pixelX = x * TILE_SIZE;
            float pixelY = y * TILE_SIZE;

            // Draw floor for all cells
            sprite.setTexture(m_floorTexture);
            sprite.setPosition(pixelX, pixelY);
            target.draw(sprite, states);

            // Draw other elements based on cell type
            switch (cell) {
                case '#':  // Wall
                    sprite.setTexture(m_wallTexture);
                    sprite.setPosition(pixelX, pixelY);
                    target.draw(sprite, states);
                    break;
                case 'A':  // Box
                    sprite.setTexture(m_boxTexture);
                    sprite.setPosition(pixelX, pixelY);
                    target.draw(sprite, states);
                    break;
                case 'a':  // Storage
                    sprite.setTexture(m_storageTexture);
                    sprite.setPosition(pixelX, pixelY);
                    target.draw(sprite, states);
                    break;
                case '1':  // Box on storage
                    sprite.setTexture(m_storageTexture);
                    sprite.setPosition(pixelX, pixelY);
                    target.draw(sprite, states);
                    sprite.setTexture(m_boxTexture);
                    target.draw(sprite, states);
                    break;
                case '@':  // Player
                    sprite.setTexture(m_playerTexture);
                    sprite.setPosition(pixelX, pixelY);
                    target.draw(sprite, states);
                    break;
            }
        }
    }
}

std::istream& operator>>(std::istream& in, Sokoban& s) {
    // Read dimensions
    unsigned int height, width;
    in >> height >> width;
    in.ignore();  // Skip newline

    // Set dimensions
    s.m_height = height;
    s.m_width = width;

    // Resize and read grid
    s.m_grid.resize(height, std::vector<char>(width, '.'));

    // Read the grid data
    for (unsigned int y = 0; y < height; ++y) {
        std::string line;
        std::getline(in, line);

        for (unsigned int x = 0; x < width && x < line.length(); ++x) {
            s.m_grid[y][x] = line[x];
            if (line[x] == '@') {
                s.m_playerPos = {x, y};
            }
        }
    }

    return in;
}

std::ostream& operator<<(std::ostream& out, const Sokoban& s) {
    out << s.height() << " " << s.width() << "\n";

    for (const auto& row : s.m_grid) {
        for (char cell : row) {
            out << cell;
        }
        out << "\n";
    }

    return out;
}

}  // namespace SB
