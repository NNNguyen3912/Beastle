#ifndef WEAPON_HPP
#define WEAPON_HPP

#include <SFML/Graphics.hpp>

class Weapon {
public:
    Weapon(float x, float y, sf::Texture& texture);
    void draw(sf::RenderWindow& window) const;
    void setActive(bool active);
    bool isActive() const;
    void setPosition(float x, float y);
	void setRotation(float angle);
    sf::Vector2f getPosition() const;
    sf::FloatRect getBounds() const;

private:
    sf::Sprite bullet;
    bool active;
};

#endif