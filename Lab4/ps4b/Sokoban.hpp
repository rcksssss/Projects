// Copyright 2024 <Thomas Boyajian>
#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

namespace SB {

// Player can move in these 4 directions
enum class Direction {
    Up, Down, Left, Right
};

// Main game class that handles everything in Sokoban
class Sokoban : public sf::Drawable {
 public:
    static const int TILE_SIZE = 64;  // Size of each game tile in pixels

    // Constructors to start the game
    Sokoban();
    explicit Sokoban(const std::string& filename);

    // Functions to get info about the game board
    unsigned int pixelHeight() const;
    unsigned int pixelWidth() const;
    unsigned int height() const;
    unsigned int width() const;
    sf::Vector2u playerLoc() const;
    bool isWon() const;

    // Game controls
    void movePlayer(Direction dir);
    void reset();
    void undo();

 protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

 private:
    // Basic game board info
    unsigned int m_width{0};
    unsigned int m_height{0};
    std::vector<std::vector<char>> m_grid;
    std::vector<std::vector<char>> m_initialGrid;
    sf::Vector2u m_playerPos{0, 0};
    sf::Vector2u m_initialPlayerPos{0, 0};
    bool m_won{false};

    // Graphics resources
    sf::Texture m_wallTexture;
    sf::Texture m_floorTexture;
    sf::Texture m_boxTexture;
    sf::Texture m_storageTexture;
    sf::Texture m_playerTexture;

    // Victory screen elements
    sf::Font m_font;
    sf::Text m_victoryText;
    sf::SoundBuffer m_victorySoundBuffer;
    sf::Sound m_victorySound;
    bool m_victorySoundPlayed{false};

    // Undo system
    struct GameState {
        std::vector<std::vector<char>> grid;
        sf::Vector2u playerPos;
        bool won;

        GameState(const std::vector<std::vector<char>>& g,
                 const sf::Vector2u& p,
                 bool w)
            : grid(g), playerPos(p), won(w) {}
    };
    std::vector<GameState> m_undoStack;

    // Helper functions for game logic
    bool canMoveTo(unsigned int x, unsigned int y) const;
    bool isStorage(unsigned int x, unsigned int y) const;
    bool isBox(unsigned int x, unsigned int y) const;
    void updateWinState();
    void moveBox(unsigned int fromX, unsigned int fromY,
                unsigned int toX, unsigned int toY);
    void loadResources();
    void setupVictoryDisplay();
    void saveState();

    // Level loading/saving
    friend std::istream& operator>>(std::istream& in, Sokoban& s);
    friend std::ostream& operator<<(std::ostream& out, const Sokoban& s);
};

std::ostream& operator<<(std::ostream& out, const Sokoban& s);
std::istream& operator>>(std::istream& in, Sokoban& s);

}  // namespace SB
