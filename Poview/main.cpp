#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <cstdlib>
#include <vector>
#include "Player.h"
#include "Enemy.h"
#include "Weapon.h"
#include "Target.h"
#include "Boss.h"
#include "Score.h"
#include "Menu.h"

const float PI = 3.14159265359f;
const float DEG_TO_RAD = PI / 180.0f;

int main() {
    sf::RenderWindow window(sf::VideoMode(1024, 720), "Beastle");
    window.setFramerateLimit(120);

    std::srand(static_cast<unsigned>(std::time(nullptr)));

    Score score;

    sf::Font font;
    if (!font.loadFromFile("font/Creepster-Regular.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
        return 1;
    }

    sf::Texture startBackgroundTexture;
    if (!startBackgroundTexture.loadFromFile("images/Menu_start.png")) {
        std::cerr << "Failed to load start background texture!" << std::endl;
        return 1;
    }

    sf::Texture gameOverBackgroundTexture;
    if (!gameOverBackgroundTexture.loadFromFile("images/Menu_end.png")) {
        std::cerr << "Failed to load game over background texture!" << std::endl;
        return 1;
    }

    Menu menu(&font, &startBackgroundTexture, &gameOverBackgroundTexture);

    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(10, 10);

    sf::Texture playerTexture;
    if (!playerTexture.loadFromFile("images/player4.png")) {
        std::cerr << "Failed to load player texture!" << std::endl;
        return 1;
    }

    sf::Texture enemyTexture;
    if (!enemyTexture.loadFromFile("images/enemy.png")) {
        std::cerr << "Failed to load enemy texture!" << std::endl;
        return 1;
    }

    sf::Texture bossMoveTexture;
    if (!bossMoveTexture.loadFromFile("images/boss_move.png")) {
        std::cerr << "Failed to load boss move texture!" << std::endl;
        return 1;
    }

    sf::Texture bossAttackTexture;
    if (!bossAttackTexture.loadFromFile("images/boss_attack.png")) {
        std::cerr << "Failed to load boss attack texture!" << std::endl;
        return 1;
    }

    sf::Texture bossSkillTexture;
    if (!bossSkillTexture.loadFromFile("images/boss_bullet.png")) {
        std::cerr << "Failed to load boss skill texture!" << std::endl;
        return 1;
    }

    sf::Texture lightPillarTexture;
    if (!lightPillarTexture.loadFromFile("images/boss_skill.png")) {
        std::cerr << "Failed to load light pillar texture!" << std::endl;
        return 1;
    }

    sf::Texture targetTexture;
    if (!targetTexture.loadFromFile("images/target.png")) {
        std::cerr << "Failed to load target texture!" << std::endl;
        return 1;
    }

    sf::Texture weaponTexture;
    if (!weaponTexture.loadFromFile("images/weapon.png")) {
        std::cerr << "Failed to load weapon texture!" << std::endl;
        return 1;
    }

    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("images/background.png")) {
        std::cerr << "Failed to load background texture!" << std::endl;
        return 1;
    }
    sf::Sprite background(backgroundTexture);

    Player player(400.0f, 300.0f, &playerTexture);
    Weapon bullet(0.0f, 0.0f, weaponTexture);
    Target target(500.0f, 300.0f, targetTexture);
    std::vector<Enemy> enemies;
    Boss boss(200.0f, 200.0f, &bossMoveTexture, &bossAttackTexture, &bossSkillTexture, &lightPillarTexture, 20.0f);

    enemies.emplace_back(static_cast<float>(rand() % 761 + 20), static_cast<float>(rand() % 561 + 20), &enemyTexture, 20.0f);

    bool isBulletVisible = false;
    float bulletTime = 0.0f, bulletAngle = 0.0f, bulletBaseAngle = 0.0f;
    float spawnTimer = 0.0f;
    const float spawnInterval = 2.0f;
    bool gameOver = false;
    Menu::GameState gameState = Menu::GameState::StartScreen;

    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            menu.handleInput(event, gameState);

            if (gameState == Menu::GameState::Playing && !gameOver && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::J && !isBulletVisible) {
                isBulletVisible = true;
                bulletTime = 0.0f;
                bulletAngle = 90.0f;
                bullet.setActive(true);
                bulletBaseAngle = player.getDirection();
                bool facingRight = (bulletBaseAngle <= 90.0f || bulletBaseAngle >= 270.0f);
                player.setAttacking(true, facingRight);
            }
        }

        if (gameState == Menu::GameState::Playing && !gameOver) {
            float deltaTime = clock.restart().asSeconds();

            player.update(deltaTime);
            target.update(deltaTime);

            sf::Vector2f playerPos = player.getPosition();
            for (auto& enemy : enemies) {
                enemy.update(deltaTime, playerPos);
            }

            boss.update(deltaTime, playerPos);
            boss.checkCollision(player.getCollisionBounds(), gameOver);
            if (gameOver) {
                gameState = Menu::GameState::GameOver;
            }

            if (isBulletVisible) {
                bulletTime += deltaTime;
                if (bulletTime <= 0.5f) {
                    float t = bulletTime / 0.5f;
                    bulletAngle = 90.0f - (180.0f * t);
                }
                else {
                    isBulletVisible = false;
                    bullet.setActive(false);
                    player.setAttacking(false, player.getDirection() <= 90.0f || player.getDirection() >= 270.0f);
                }

                float offsetAngle = bulletBaseAngle + bulletAngle;
                float distance = 50.0f;
                float xOffset = distance * std::cos(offsetAngle * DEG_TO_RAD);
                float yOffset = -distance * std::sin(offsetAngle * DEG_TO_RAD);
                bullet.setPosition(player.getPosition().x + xOffset, player.getPosition().y + yOffset);
            }

            if (isBulletVisible && !target.isMoving() && bullet.getBounds().intersects(target.getBounds())) {
                sf::Vector2f collisionDirection = target.getPosition() - bullet.getPosition();
                float length = std::sqrt(collisionDirection.x * collisionDirection.x + collisionDirection.y * collisionDirection.y);
                if (length != 0) collisionDirection /= length;
                target.setVelocity(collisionDirection * 5000.0f);
                bullet.setActive(false);
                isBulletVisible = false;
                player.setAttacking(false, player.getDirection() <= 90.0f || player.getDirection() >= 270.0f);
            }

            for (size_t i = 0; i < enemies.size(); ++i) {
                if (target.getBounds().intersects(enemies[i].getBounds())) {
                    enemies.erase(enemies.begin() + i);
                    spawnTimer = 0.0f;
                    --i;
                    score.increase(100);
                }
            }

            if (player.getCollisionBounds().intersects(boss.getCollisionBounds())) {
                gameOver = true;
                gameState = Menu::GameState::GameOver;
                std::cout << "Game Over! Boss hit Player!" << std::endl;
            }

            for (const auto& enemy : enemies) {
                if (player.getCollisionBounds().intersects(enemy.getCollisionBounds())) {
                    gameOver = true;
                    gameState = Menu::GameState::GameOver;
                    std::cout << "Game Over! Enemy hit Player!" << std::endl;
                    break;
                }
            }

            spawnTimer += deltaTime;
            if (spawnTimer >= spawnInterval && enemies.size() < 5) {
                for (int i = 0; i < 3; ++i) {
                    enemies.emplace_back(static_cast<float>(rand() % 761 + 20), static_cast<float>(rand() % 561 + 20), &enemyTexture, 20.0f);
                }
                spawnTimer = 0.0f;
            }
        }

        window.clear();
        if (gameState == Menu::GameState::Playing) {
            window.draw(background);
            player.draw(window);
            target.draw(window);
            for (const auto& enemy : enemies) {
                enemy.draw(window);
            }
            boss.draw(window);
            if (isBulletVisible) bullet.draw(window);
            scoreText.setString("Score: " + std::to_string(score.getPoints()));
            window.draw(scoreText);
        }
        menu.draw(window, gameState, score);
        window.display();
    }

    return 0;
}