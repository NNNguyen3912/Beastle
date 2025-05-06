#ifndef LIGHT_PILLAR_HPP
#define LIGHT_PILLAR_HPP

#include <SFML/Graphics.hpp>
#include "Animation.h"

class LightPillar {
public:
    LightPillar(float x, float y, sf::Texture* texture);
    void update(float deltaTime);
    void draw(sf::RenderWindow& window) const;
    sf::FloatRect getBounds() const;
    bool isFinished() const;
    bool canCollide() const; 
    sf::FloatRect getCollisionBounds() const;

private:
    sf::Sprite sprite;
    Animation animation;
    bool finished;
};

#endif