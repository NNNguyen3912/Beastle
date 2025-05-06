#include <SFML/Graphics.hpp>
#include "Menu.h"
#include <iostream>

Menu::Menu(sf::Font* font, sf::Texture* startBackgroundTexture, sf::Texture* gameOverBackgroundTexture)
    : font(font) {
    startBackground.setTexture(*startBackgroundTexture);
    startBackground.setPosition(0, 0);

    gameOverBackground.setTexture(*gameOverBackgroundTexture);
    gameOverBackground.setPosition(0, 0);

    scoreText.setFont(*font);
    scoreText.setCharacterSize(30);
    scoreText.setFillColor(sf::Color::Red);
    scoreText.setPosition(1024 / 2.0f - 50, 720 / 2.0f + 50);
}

void Menu::handleInput(sf::Event& event, GameState& state) {
    if (event.type == sf::Event::KeyPressed) {
        if (state == GameState::StartScreen && event.key.code == sf::Keyboard::J) {
            state = GameState::Playing;
        }
    }
}

void Menu::draw(sf::RenderWindow& window, const GameState& state, const Score& score) const {
    if (state == GameState::StartScreen) {
        window.draw(startBackground);
        window.draw(startText);
    }
    else if (state == GameState::GameOver) {
        window.draw(gameOverBackground);
        window.draw(gameOverText);
        scoreText.setString("Score: " + std::to_string(score.getPoints()));
        window.draw(scoreText);
    }
}