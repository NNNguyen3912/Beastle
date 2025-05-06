#include "Player.h"
#include <cmath>

Player::Player(float x, float y, sf::Texture* texture)
    : speed(200.0f), isMoving(false), isAttacking(false), facingRight(true), direction(0.0f),
    walkLeftAnim(texture, 62, 50, 0.2f),
    walkRightAnim(texture, 62, 50, 0.2f),
    attackLeftAnim(texture, 62, 50, 0.2f),
    attackRightAnim(texture, 62, 50, 0.2f) {
    sprite.setTexture(*texture);
    sprite.setPosition(x, y);
    sprite.setOrigin(31, 25);

    walkLeftAnim.addFrame(0, 0);
    walkLeftAnim.addFrame(62, 0);

    walkRightAnim.addFrame(0, 50);
    walkRightAnim.addFrame(62, 50);

    attackLeftAnim.addFrame(124, 0);
    attackLeftAnim.addFrame(186, 0);

    attackRightAnim.addFrame(124, 50);
    attackRightAnim.addFrame(186, 50);

    currentAnim = &walkRightAnim;
}

void Player::update(float deltaTime) {
    sf::Vector2f movement(0.0f, 0.0f);
    isMoving = false;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        movement.y = -speed * deltaTime;
        isMoving = true;
        direction = 90.0f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        movement.y = speed * deltaTime;
        isMoving = true;
        direction = 270.0f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        movement.x = -speed * deltaTime;
        isMoving = true;
        facingRight = false;
        direction = 180.0f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        movement.x = speed * deltaTime;
        isMoving = true;
        facingRight = true;
        direction = 0.0f;
    }

    if (movement.x != 0 && movement.y != 0) {
        if (movement.x > 0 && movement.y < 0) direction = 45.0f;
        if (movement.x < 0 && movement.y < 0) direction = 135.0f;
        if (movement.x < 0 && movement.y > 0) direction = 225.0f;
        if (movement.x > 0 && movement.y > 0) direction = 315.0f;
        movement /= std::sqrt(2.0f);
    }

    sprite.move(movement);

    if (isAttacking) {
        currentAnim = facingRight ? &attackRightAnim : &attackLeftAnim;
    }
    else if (isMoving) {
        currentAnim = facingRight ? &walkRightAnim : &walkLeftAnim;
    }
    else {
        currentAnim = facingRight ? &walkRightAnim : &walkLeftAnim;
        currentAnim->reset();
    }

    currentAnim->update(deltaTime);
    currentAnim->applyToSprite(sprite);
}

void Player::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

sf::Vector2f Player::getPosition() const {
    return sprite.getPosition();
}

sf::FloatRect Player::getBounds() const {
    return sprite.getGlobalBounds();
}

sf::FloatRect Player::getCollisionBounds() const {
    sf::FloatRect bounds = sprite.getGlobalBounds();
    float shrinkFactor = 0.2f; 
    float newWidth = bounds.width * shrinkFactor;
    float newHeight = bounds.height * shrinkFactor;
    float offsetX = (bounds.width - newWidth) / 2.0f;
    float offsetY = (bounds.height - newHeight) / 2.0f;
    return sf::FloatRect(bounds.left + offsetX, bounds.top + offsetY, newWidth, newHeight);
}

void Player::setAttacking(bool attacking, bool facingRight) {
    isAttacking = attacking;
    this->facingRight = facingRight;
    if (isAttacking) {
        currentAnim = facingRight ? &attackRightAnim : &attackLeftAnim;
        currentAnim->reset();
    }
}

float Player::getDirection() const {
    return direction;
}