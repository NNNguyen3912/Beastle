#include "Light_pillar.h"

LightPillar::LightPillar(float x, float y, sf::Texture* texture)
    : animation(texture, 91, 145, 0.1f), finished(false) {
    sprite.setTexture(*texture);
    sprite.setOrigin(91.0f / 2.0f, 145.0f); 
    sprite.setPosition(x, y);

    for (int i = 0; i < 14; ++i) {
        animation.addFrame(i * 91, 0);
    }
}

void LightPillar::update(float deltaTime) {
    animation.update(deltaTime);
    animation.applyToSprite(sprite);

    if (animation.getCurrentFrame() == animation.getFrameCount() - 1) {
        finished = true;
    }
}

void LightPillar::draw(sf::RenderWindow& window) const {
    window.draw(sprite);
}

sf::FloatRect LightPillar::getBounds() const {
    return sprite.getGlobalBounds();
}

sf::FloatRect LightPillar::getCollisionBounds() const {
    sf::FloatRect bounds = sprite.getGlobalBounds();
    float shrinkFactor = 0.4f; 
    float newWidth = bounds.width * shrinkFactor;
    float newHeight = bounds.height * shrinkFactor;
    float offsetX = (bounds.width - newWidth) / 2.0f;
    float offsetY = (bounds.height - newHeight) / 2.0f;
    return sf::FloatRect(bounds.left + offsetX, bounds.top + offsetY, newWidth, newHeight);
}


bool LightPillar::isFinished() const {
    return finished;
}

bool LightPillar::canCollide() const {
    return animation.getCurrentFrame() >= 6;
}