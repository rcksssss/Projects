// Copyright 2024 <Thomas Boyajian>

#include "Sokoban.hpp"
#include <stdexcept>
#include <algorithm>
#include <string>
#include <fstream>

namespace SB {

// Basic initialization
Sokoban::Sokoban() {
    loadResources();
}

// Load a specific level file
Sokoban::Sokoban(const std::string& filename) : Sokoban() {
    std::ifstream file(filename);
    if (file) {
        file >> *this;
    } else {
        throw std::runtime_error("Could not open file: " + filename);
    }
}

// Load all game resources (images, sounds, fonts)
void Sokoban::loadResources() {
    const std::string texturePath = "sokoban/";

    // All game textures
    if (!m_wallTexture.loadFromFile(texturePath + "block_06.png") ||
        !m_floorTexture.loadFromFile(texturePath + "ground_01.png") ||
        !m_boxTexture.loadFromFile(texturePath + "crate_03.png") ||
        !m_storageTexture.loadFromFile(texturePath + "ground_04.png") ||
        !m_playerTexture.loadFromFile(texturePath + "player_05.png")) {
        throw std::runtime_error("Failed to load one or more textures");
    }

    if (!m_font.loadFromFile("LiberationMono-Regular.ttf")) {
        throw std::runtime_error("Failed to load victory font");
    }

    if (!m_victorySoundBuffer.loadFromFile("victory.wav")) {
        throw std::runtime_error("Failed to load victory sound");
    }
    m_victorySound.setBuffer(m_victorySoundBuffer);

    setupVictoryDisplay();
}

// Setup the victory message display
void Sokoban::setupVictoryDisplay() {
    m_victoryText.setFont(m_font);
    m_victoryText.setString("You Win!");
    m_victoryText.setCharacterSize(48);
    m_victoryText.setFillColor(sf::Color::Black);

    sf::FloatRect textBounds = m_victoryText.getLocalBounds();
    m_victoryText.setOrigin(textBounds.width / 2, textBounds.height / 2);
    float centerX = m_width * TILE_SIZE / 2.0f;
    float centerY = m_height * TILE_SIZE / 2.0f;
    m_victoryText.setPosition(centerX, centerY);
}

// Simple getters
unsigned int Sokoban::height() const { return m_height; }
unsigned int Sokoban::width() const { return m_width; }
unsigned int Sokoban::pixelHeight() const { return m_height * TILE_SIZE; }
unsigned int Sokoban::pixelWidth() const { return m_width * TILE_SIZE; }
sf::Vector2u Sokoban::playerLoc() const { return m_playerPos; }
bool Sokoban::isWon() const { return m_won; }

// Game board state checkers
bool Sokoban::canMoveTo(unsigned int x, unsigned int y) const {
    char cell = m_grid[y][x];
    return cell == '.' || cell == 'a';
}

bool Sokoban::isStorage(unsigned int x, unsigned int y) const {
    char cell = m_grid[y][x];
    return cell == 'a' || cell == '1' || cell == '+';
}

bool Sokoban::isBox(unsigned int x, unsigned int y) const {
    char cell = m_grid[y][x];
    return cell == 'A' || cell == '1';
}

// Core game mechanics
void Sokoban::moveBox(unsigned int fromX, unsigned int fromY,
unsigned int toX, unsigned int toY) {
    bool fromStorage = isStorage(fromX, fromY);
    bool toStorage = isStorage(toX, toY);

    m_grid[fromY][fromX] = fromStorage ? 'a' : '.';
    m_grid[toY][toX] = toStorage ? '1' : 'A';
}

void Sokoban::movePlayer(Direction dir) {
    if (m_won) return;

    // Calculate new position based on direction
    int dx = 0, dy = 0;
    switch (dir) {
        case Direction::Up: dy = -1; break;
        case Direction::Down: dy = 1; break;
        case Direction::Left: dx = -1; break;
        case Direction::Right: dx = 1; break;
    }

    unsigned int newX = m_playerPos.x + dx;
    unsigned int newY = m_playerPos.y + dy;

    if (newX >= m_width || newY >= m_height) return;

    // Check if move is valid and save state if it is
    bool willMove = false;
    if (canMoveTo(newX, newY)) {
        willMove = true;
    } else if (isBox(newX, newY)) {
        unsigned int boxNewX = newX + dx;
        unsigned int boxNewY = newY + dy;
        if (boxNewX < m_width && boxNewY < m_height && canMoveTo(boxNewX, boxNewY)) {
            willMove = true;
        }
    }

    if (willMove) {
        saveState();
    }

    // Execute the move
    if (canMoveTo(newX, newY)) {
        char currentCell = m_grid[m_playerPos.y][m_playerPos.x];
        m_grid[m_playerPos.y][m_playerPos.x] = (currentCell == '+') ? 'a' : '.';
        m_grid[newY][newX] = (isStorage(newX, newY)) ? '+' : '@';
        m_playerPos = {newX, newY};
    } else if (isBox(newX, newY)) {
        unsigned int boxNewX = newX + dx;
        unsigned int boxNewY = newY + dy;

        if (boxNewX < m_width && boxNewY < m_height && canMoveTo(boxNewX, boxNewY)) {
            moveBox(newX, newY, boxNewX, boxNewY);
            char currentCell = m_grid[m_playerPos.y][m_playerPos.x];
            m_grid[m_playerPos.y][m_playerPos.x] = (currentCell == '+') ? 'a' : '.';
            m_grid[newY][newX] = (isStorage(newX, newY)) ? '+' : '@';
            m_playerPos = {newX, newY};
            updateWinState();
        }
    }
}

// Win condition checking
void Sokoban::updateWinState() {
    bool previousWon = m_won;

    // Count all boxes, storage spots, and boxes on storage
    int totalBoxesOnStorage = 0;
    int totalStorageSpots = 0;
    int totalBoxes = 0;

    for (unsigned int y = 0; y < m_height; ++y) {
        for (unsigned int x = 0; x < m_width; ++x) {
            char cell = m_grid[y][x];
            if (cell == '1') {  // Box on storage
                totalBoxesOnStorage++;
            }
            if (cell == 'a' || cell == '1' || cell == '+') {  // Storage spot
                totalStorageSpots++;
            }
            if (cell == 'A' || cell == '1') {  // Box
                totalBoxes++;
            }
        }
    }

    m_won = (totalBoxesOnStorage == totalStorageSpots) &&
            (totalBoxesOnStorage > 0);

    if (m_won && !previousWon && !m_victorySoundPlayed) {
        m_victorySound.play();
        m_victorySoundPlayed = true;
    }
}

// Undo/Reset functionality
void Sokoban::saveState() {
    m_undoStack.emplace_back(m_grid, m_playerPos, m_won);
}

void Sokoban::undo() {
    if (m_undoStack.empty()) return;

    const GameState& prevState = m_undoStack.back();
    m_grid = prevState.grid;
    m_playerPos = prevState.playerPos;
    m_won = prevState.won;
    m_victorySoundPlayed = m_won;
    m_undoStack.pop_back();
}

void Sokoban::reset() {
    m_grid = m_initialGrid;
    m_playerPos = m_initialPlayerPos;
    m_won = false;
    m_victorySoundPlayed = false;
    m_undoStack.clear();
}

// Graphics rendering
void Sokoban::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    sf::Sprite sprite;

    // Draw the game board
    for (unsigned int y = 0; y < m_height; ++y) {
        for (unsigned int x = 0; x < m_width; ++x) {
            float pixelX = x * TILE_SIZE;
            float pixelY = y * TILE_SIZE;

            // Base floor
            sprite.setTexture(m_floorTexture);
            sprite.setPosition(pixelX, pixelY);
            target.draw(sprite, states);

            // Game elements
            switch (m_grid[y][x]) {
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
                    sprite.setPosition(pixelX, pixelY);
                    target.draw(sprite, states);
                    break;

                case '@':  // Player
                case '+':  // Player on storage
                    if (m_grid[y][x] == '+') {
                        sprite.setTexture(m_storageTexture);
                        sprite.setPosition(pixelX, pixelY);
                        target.draw(sprite, states);
                    }
                    sprite.setTexture(m_playerTexture);
                    sprite.setPosition(pixelX, pixelY);
                    target.draw(sprite, states);
                    break;
            }
        }
    }

    if (m_won) {
        target.draw(m_victoryText, states);
    }
}

// Level file handling
std::istream& operator>>(std::istream& in, Sokoban& s) {
    unsigned int height, width;
    in >> height >> width;
    in.ignore();

    s.m_height = height;
    s.m_width = width;
    s.m_grid.resize(height, std::vector<char>(width, '.'));

    for (unsigned int y = 0; y < height; ++y) {
        std::string line;
        std::getline(in, line);

        for (unsigned int x = 0; x < width && x < line.length(); ++x) {
            s.m_grid[y][x] = line[x];
            if (line[x] == '@' || line[x] == '+') {
                s.m_playerPos = {x, y};
                s.m_initialPlayerPos = {x, y};
            }
        }
    }

    s.m_initialGrid = s.m_grid;
    s.setupVictoryDisplay();
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
