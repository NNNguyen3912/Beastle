#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <SFML/Graphics.hpp>
#include "Animation.h"

class Enemy {
public:
    Enemy(float x, float y, sf::Texture* texture, float speed = 150.0f);
    void draw(sf::RenderWindow& window) const;
    void update(float deltaTime, const sf::Vector2f& targetPos);
    sf::FloatRect getBounds() const;
    sf::FloatRect getCollisionBounds() const;
    sf::Vector2f getPosition() const;

private:
    sf::Sprite shape;
    float speed;
    bool facingRight;

    Animation walkLeftAnim;
    Animation walkRightAnim;
    Animation* currentAnim;
};

#endif