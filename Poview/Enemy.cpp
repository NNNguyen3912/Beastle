#include "Enemy.h"

Enemy::Enemy(float x, float y, sf::Texture* texture, float speed)
    : speed(speed), facingRight(true),
    walkLeftAnim(texture, 49, 50, 0.2f),
    walkRightAnim(texture, 49, 50, 0.2f) {
    shape.setTexture(*texture);
    shape.setOrigin(24.5f, 25.0f);
    shape.setPosition(x, y);

    walkLeftAnim.addFrame(0, 0);
    walkLeftAnim.addFrame(49, 0);

    walkRightAnim.addFrame(0, 50);
    walkRightAnim.addFrame(49, 50);

    currentAnim = &walkRightAnim;
}

void Enemy::draw(sf::RenderWindow& window) const {
    window.draw(shape);
}

void Enemy::update(float deltaTime, const sf::Vector2f& targetPos) {
    sf::Vector2f enemyPos = getPosition();
    sf::Vector2f direction = targetPos - enemyPos;
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length > 0) {
        direction /= length;
        shape.move(direction * speed * deltaTime);

        facingRight = (direction.x >= 0);
        currentAnim = facingRight ? &walkRightAnim : &walkLeftAnim;
        currentAnim->update(deltaTime);
        currentAnim->applyToSprite(shape);
    }
}

sf::FloatRect Enemy::getBounds() const {
    return shape.getGlobalBounds();
}

sf::FloatRect Enemy::getCollisionBounds() const {
    sf::FloatRect bounds = shape.getGlobalBounds();
    float shrinkFactor = 0.2f;
    float newWidth = bounds.width * shrinkFactor;
    float newHeight = bounds.height * shrinkFactor;
    float offsetX = (bounds.width - newWidth) / 2.0f;
    float offsetY = (bounds.height - newHeight) / 2.0f;
    return sf::FloatRect(bounds.left + offsetX, bounds.top + offsetY, newWidth, newHeight);
}

sf::Vector2f Enemy::getPosition() const {
    return shape.getPosition();
}