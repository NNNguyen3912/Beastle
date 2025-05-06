#include "Target.h"

Target::Target(float x, float y, sf::Texture& texture) : moving(false) {
    sprite.setTexture(texture);
    sprite.setOrigin(25, 25); // Kích thước 50x50, tâm ở 25,25
    sprite.setPosition(x, y);
    velocity = sf::Vector2f(0.0f, 0.0f);
}

void Target::draw(sf::RenderWindow& window) const {
    window.draw(sprite);
}

void Target::update(float deltaTime) {
    if (moving) {
        sprite.move(velocity * deltaTime);

        sf::Vector2f pos = sprite.getPosition();
        float halfSize = 25.0f;
        if (pos.x - halfSize < 0) {
            sprite.setPosition(halfSize, pos.y);
            velocity.x = -velocity.x * 0.9f;
        }
        else if (pos.x + halfSize > 800) {
            sprite.setPosition(800 - halfSize, pos.y);
            velocity.x = -velocity.x * 0.9f;
        }
        if (pos.y - halfSize < 0) {
            sprite.setPosition(pos.x, halfSize);
            velocity.y = -velocity.y * 0.9f;
        }
        else if (pos.y + halfSize > 600) {
            sprite.setPosition(pos.x, 600 - halfSize);
            velocity.y = -velocity.y * 0.9f;
        }

        velocity *= friction;
        if (std::abs(velocity.x) < stopThreshold && std::abs(velocity.y) < stopThreshold) {
            moving = false;
        }
    }
}

void Target::move(sf::Vector2f velocity) {
    this->velocity = velocity;
    moving = true;
}

void Target::setPosition(float x, float y) {
    sprite.setPosition(x, y);
}

sf::FloatRect Target::getBounds() const {
    return sprite.getGlobalBounds();
}

sf::Vector2f Target::getPosition() const {
    return sprite.getPosition();
}

bool Target::isMoving() const {
    return moving;
}

void Target::setVelocity(sf::Vector2f velocity) {
    this->velocity = velocity;
    moving = true;
}