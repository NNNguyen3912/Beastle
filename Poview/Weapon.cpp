#include "Weapon.h"

Weapon::Weapon(float x, float y, sf::Texture& texture) {
    bullet.setTexture(texture);
    bullet.setOrigin(50, 50); // Tâm sprite: 100/2 = 50
    bullet.setPosition(x, y);
    active = false;
}

void Weapon::draw(sf::RenderWindow& window) const {
    if (active)
        window.draw(bullet);
}

void Weapon::setActive(bool active) {
    this->active = active;
}

bool Weapon::isActive() const {
    return active;
}

void Weapon::setPosition(float x, float y) {
    bullet.setPosition(x, y);
}

void Weapon::setRotation(float angle) {
    bullet.setRotation(angle);
}

sf::Vector2f Weapon::getPosition() const {
    return bullet.getPosition();
}

sf::FloatRect Weapon::getBounds() const {
    return bullet.getGlobalBounds();
}