#ifndef BOSS_SKILL_HPP
#define BOSS_SKILL_HPP

#include <SFML/Graphics.hpp>
#include <vector>

class Boss_skill {
public:
    Boss_skill(sf::Texture* bulletTexture);
    void update(float deltaTime, const sf::Vector2f& bossPos, const sf::Vector2f& playerPos);
    void draw(sf::RenderWindow& window) const;
    bool checkCollision(const sf::FloatRect& playerBounds, bool& gameOver) const;

private:
    struct Bullet {
        sf::Sprite sprite;
        float angle;       
        float radius;     
        bool active;
        sf::FloatRect getCollisionBounds() const;
        
        Bullet(float x, float y, sf::Texture* texture, float angle);
    };

    sf::Texture* bulletTexture;
    std::vector<Bullet> bullets;
    float skillTimer;
    const float skillInterval = 6.0f; 
    const float expandSpeed = 200.0f;   
    const float initialRadius = 50.0f; 
};

#endif