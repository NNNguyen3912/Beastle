#ifndef TARGET_HPP
#define TARGET_HPP

#include <SFML/Graphics.hpp>

class Target {
public:
    Target(float x, float y, sf::Texture& texture);
    void draw(sf::RenderWindow& window) const;
    void update(float deltaTime);
    void move(sf::Vector2f velocity);
    void setPosition(float x, float y);
    sf::FloatRect getBounds() const;
    sf::Vector2f getPosition() const;
    bool isMoving() const;
    void setVelocity(sf::Vector2f velocity);

private:
    sf::Sprite sprite;
    sf::Vector2f velocity;
    bool moving;
    const float friction = 0.95f;
    const float stopThreshold = 10.0f;
};

#endif