#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include "Animation.h"

class Player {
public:
    Player(float x, float y, sf::Texture* texture);
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);
    sf::Vector2f getPosition() const;
    sf::FloatRect getBounds() const;
    sf::FloatRect getCollisionBounds() const;
    void setAttacking(bool attacking, bool facingRight);
    float getDirection() const;

private:
    sf::Sprite sprite;
    float speed;
    bool isMoving;
    bool isAttacking;
    bool facingRight;
    float direction;

    Animation walkLeftAnim;
    Animation walkRightAnim;
    Animation attackLeftAnim;
    Animation attackRightAnim;
    Animation* currentAnim;
};

#endif