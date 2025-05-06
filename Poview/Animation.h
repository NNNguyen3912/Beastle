#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <SFML/Graphics.hpp>
#include <vector>

class Animation {
public:
    Animation(sf::Texture* texture, int frameWidth, int frameHeight, float frameTime);
    void addFrame(int x, int y);
    void update(float deltaTime);
    void applyToSprite(sf::Sprite& sprite) const;
    void reset();
    size_t getCurrentFrame() const; // Thêm phương thức lấy frame hiện tại
    size_t getFrameCount() const;   // Thêm phương thức lấy số lượng frame
    sf::Texture* getTexture() const;

private:
    sf::Texture* texture;
    std::vector<sf::IntRect> frames;
    int frameWidth;
    int frameHeight;
    float frameTime;
    float currentTime;
    size_t currentFrame;
};

#endif