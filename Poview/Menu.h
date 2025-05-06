#ifndef MENU_HPP
#define MENU_HPP

#include <SFML/Graphics.hpp>
#include "Score.h"

class Menu {
public:
    enum class GameState { StartScreen, Playing, GameOver };

    Menu(sf::Font* font, sf::Texture* startBackgroundTexture, sf::Texture* gameOverBackgroundTexture);
    void handleInput(sf::Event& event, GameState& state);
    void draw(sf::RenderWindow& window, const GameState& state, const Score& score) const;

private:
    sf::Font* font;
    sf::Text startText;
    sf::Text gameOverText;
    mutable sf::Text scoreText;
    sf::Sprite startBackground;
    sf::Sprite gameOverBackground;
};

#endif