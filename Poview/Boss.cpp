#include "Boss.h"
#include <cstdlib>
#include <iostream>

Boss::Boss(float x, float y, sf::Texture* moveTexture, sf::Texture* attackTexture, sf::Texture* bulletTexture, sf::Texture* lightPillarTexture, float speed)
    : speed(speed), facingRight(true), attacking(false), attackTimer(0.0f),
    moveRightAnim(moveTexture, 95, 100, 0.2f),
    moveLeftAnim(moveTexture, 95, 100, 0.2f),
    attackRightAnim(attackTexture, 95, 100, 0.2f),
    attackLeftAnim(attackTexture, 95, 100, 0.2f),
    skill(bulletTexture),
    skill2Timer(0.0f), usingSkill2(false), attackCount(0), attackDurationTimer(0.0f), pillarTimer(0.0f),
    lightPillarTexture(lightPillarTexture) {
    shape.setTexture(*moveTexture);
    shape.setOrigin(285.0f / 2.0f, 200.0f / 2.0f);
    shape.setPosition(x, y);

    moveRightAnim.addFrame(0, 0);
    moveRightAnim.addFrame(95, 0);
    moveRightAnim.addFrame(190, 0);

    moveLeftAnim.addFrame(0, 100);
    moveLeftAnim.addFrame(95, 100);
    moveLeftAnim.addFrame(190, 100);

    attackRightAnim.addFrame(0, 0);
    attackRightAnim.addFrame(95, 0);
    attackRightAnim.addFrame(190, 0);

    attackLeftAnim.addFrame(0, 100);
    attackLeftAnim.addFrame(95, 100);
    attackLeftAnim.addFrame(190, 100);

    currentAnim = &moveRightAnim;
}

void Boss::update(float deltaTime, const sf::Vector2f& targetPos) {
    sf::Vector2f bossPos = getPosition();
    sf::Vector2f direction = targetPos - bossPos;
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    skill2Timer += deltaTime;

    if (skill2Timer >= 10.0f && !usingSkill2) {
        usingSkill2 = true;
        attackCount = 0;
        attackDurationTimer = 0.0f;
        pillarTimer = 0.0f;
        pillars.clear();
        std::cout << "Skill 2 activated!" << std::endl;
    }

    if (length > 0) {
        direction /= length;

        if (!usingSkill2) {
            shape.move(direction * speed * deltaTime);
            facingRight = (direction.x >= 0);
            attackTimer += deltaTime;

            if (attackTimer >= attackInterval) {
                attacking = true;
                attackTimer = 0.0f;
            }
        }
        else {
            attacking = true;
            attackDurationTimer += deltaTime;

            pillarTimer += deltaTime;
            if (pillarTimer >= pillarInterval && pillars.size() < 20) {
                pillarTimer = 0.0f;
                float x = static_cast<float>(rand() % 1024);
                float y = static_cast<float>(rand() % 720);
                pillars.emplace_back(x, y, lightPillarTexture);
                std::cout << "Created Light Pillar at (" << x << ", " << y << "), total pillars: " << pillars.size() << std::endl;
            }

            if (attackDurationTimer >= attackDuration) {
                attackCount++;
                attackDurationTimer = 0.0f;
                std::cout << "Attack " << attackCount << " of 5 completed" << std::endl;
            }

            if (attackCount >= 5) {
                usingSkill2 = false;
                skill2Timer = 0.0f;
                std::cout << "Skill 2 ended!" << std::endl;
            }
        }

        if (attacking) {
            currentAnim = facingRight ? &attackRightAnim : &attackLeftAnim;
            shape.setTexture(*attackRightAnim.getTexture());
        }
        else {
            currentAnim = facingRight ? &moveRightAnim : &moveLeftAnim;
            shape.setTexture(*moveRightAnim.getTexture());
        }

        currentAnim->update(deltaTime);
        currentAnim->applyToSprite(shape);

        if (attacking && (currentAnim == &attackRightAnim || currentAnim == &attackLeftAnim) &&
            currentAnim->getCurrentFrame() == currentAnim->getFrameCount() - 1) {
            attacking = false;
        }

        skill.update(deltaTime, bossPos, targetPos);
    }

    for (size_t i = 0; i < pillars.size(); ++i) {
        pillars[i].update(deltaTime);
        if (pillars[i].isFinished()) {
            pillars.erase(pillars.begin() + i);
            --i;
        }
    }
}

void Boss::draw(sf::RenderWindow& window) const {
    window.draw(shape);
    skill.draw(window);
    for (const auto& pillar : pillars) {
        pillar.draw(window);
    }
}

sf::FloatRect Boss::getBounds() const {
    return shape.getGlobalBounds();
}

sf::FloatRect Boss::getCollisionBounds() const {
    sf::FloatRect bounds = shape.getGlobalBounds();
    float shrinkFactor = 0.2f;
    float newWidth = bounds.width * shrinkFactor;
    float newHeight = bounds.height * shrinkFactor;
    float offsetX = (bounds.width - newWidth) / 2.0f;
    float offsetY = (bounds.height - newHeight) / 2.0f;
    return sf::FloatRect(bounds.left + offsetX, bounds.top + offsetY, newWidth, newHeight);
}

sf::Vector2f Boss::getPosition() const {
    return shape.getPosition();
}

bool Boss::isAttacking() const {
    return attacking;
}

void Boss::setAttacking(bool attacking) {
    this->attacking = attacking;
}

bool Boss::checkCollision(const sf::FloatRect& playerBounds, bool& gameOver) const {
    if (skill.checkCollision(playerBounds, gameOver)) {
        return true;
    }

    for (const auto& pillar : pillars) {
        if (pillar.canCollide() && pillar.getCollisionBounds().intersects(playerBounds)) { // Dùng getCollisionBounds
            gameOver = true;
            std::cout << "Game Over! Light Pillar hit Player!" << std::endl;
            return true;
        }
    }
    return false;
}