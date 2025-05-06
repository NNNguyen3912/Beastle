#ifndef BOSS_HPP
#define BOSS_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "Animation.h"
#include "Boss_skill.h"
#include "Light_pillar.h"

class Boss {
public:
    Boss(float x, float y, sf::Texture* moveTexture, sf::Texture* attackTexture, sf::Texture* bulletTexture, sf::Texture* lightPillarTexture, float speed = 100.0f);
    void update(float deltaTime, const sf::Vector2f& targetPos);
    void draw(sf::RenderWindow& window) const;
    sf::FloatRect getBounds() const;
    sf::FloatRect getCollisionBounds() const;
    sf::Vector2f getPosition() const;
    bool isAttacking() const;
    void setAttacking(bool attacking);
    bool checkCollision(const sf::FloatRect& playerBounds, bool& gameOver) const;
	
    //sf::Texture* getTexture() const { return moveRightAnim.getTexture(); } // Trả về texture hiện tại (move texture)
    //sf::Texture* getMoveTexture() const { return moveRightAnim.getTexture(); }
    //sf::Texture* getAttackTexture() const { return attackRightAnim.getTexture(); }
    //sf::Texture* getSkillTexture() const { return skill.getTexture(); }
    //sf::Texture* getLightPillarTexture() const { return lightPillarTexture; }
private:
    sf::Sprite shape;
    float speed;
    bool facingRight;
    bool attacking;
    float attackTimer;
    const float attackInterval = 6.0f;

    Animation moveRightAnim;
    Animation moveLeftAnim;
    Animation attackRightAnim;
    Animation attackLeftAnim;
    Animation* currentAnim;

    Boss_skill skill;

    float skill2Timer;
    bool usingSkill2;
    int attackCount;
    float attackDurationTimer; 
    const float attackDuration = 0.6f; 
    float pillarTimer;
    const float pillarInterval = 0.15f;
    std::vector<LightPillar> pillars;
    sf::Texture* lightPillarTexture;
};

#endif