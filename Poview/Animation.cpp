#include "Animation.h"

Animation::Animation(sf::Texture* texture, int frameWidth, int frameHeight, float frameTime)
    : texture(texture), frameWidth(frameWidth), frameHeight(frameHeight), frameTime(frameTime), currentTime(0.0f), currentFrame(0) {
}

void Animation::addFrame(int x, int y) {
    frames.emplace_back(x, y, frameWidth, frameHeight);
}

void Animation::update(float deltaTime) {
    currentTime += deltaTime;
    if (currentTime >= frameTime) {
        currentTime -= frameTime;
        currentFrame = (currentFrame + 1) % frames.size();
    }
}

void Animation::applyToSprite(sf::Sprite& sprite) const {
    sprite.setTextureRect(frames[currentFrame]);
}

void Animation::reset() {
    currentFrame = 0;
    currentTime = 0.0f;
}

size_t Animation::getCurrentFrame() const {
    return currentFrame;
}

size_t Animation::getFrameCount() const {
    return frames.size();
}

sf::Texture* Animation::getTexture() const {
    return texture;
}