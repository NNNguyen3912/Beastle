#include "Boss_skill.h"
#include <cmath>
#include <iostream>

const float PI = 3.14159265359f;
const float DEG_TO_RAD = PI / 180.0f;

Boss_skill::Bullet::Bullet(float x, float y, sf::Texture* texture, float angle)
    : angle(angle), radius(0.0f), active(true) {
    sprite.setTexture(*texture);
    sprite.setOrigin(25, 25); // Kích thước 50x50, tâm ở giữa
    sprite.setPosition(x, y);
}

Boss_skill::Boss_skill(sf::Texture* bulletTexture)
    : bulletTexture(bulletTexture), skillTimer(0.0f) {
}

sf::FloatRect Boss_skill::Bullet::getCollisionBounds() const {
    sf::FloatRect bounds = sprite.getGlobalBounds();
    float shrinkFactor = 0.4f; // Thu nhỏ vùng va chạm xuống 60% kích thước ban đầu
    float newWidth = bounds.width * shrinkFactor;
    float newHeight = bounds.height * shrinkFactor;
    float offsetX = (bounds.width - newWidth) / 2.0f;
    float offsetY = (bounds.height - newHeight) / 2.0f;
    return sf::FloatRect(bounds.left + offsetX, bounds.top + offsetY, newWidth, newHeight);
}

void Boss_skill::update(float deltaTime, const sf::Vector2f& bossPos, const sf::Vector2f& playerPos) {
    skillTimer += deltaTime;

    // Kiểm tra thời gian để bắn
    if (skillTimer >= skillInterval) {
        skillTimer = 0.0f;

        // Bắn 10 viên đạn theo dạng hình tròn
        for (int i = 0; i < 10; ++i) { // Thay đổi từ 6 thành 10
            float angle = i * 36.0f; // 360° / 10 = 36° mỗi viên đạn
            bullets.emplace_back(bossPos.x, bossPos.y, bulletTexture, angle);
        }
    }

    // Cập nhật vị trí các viên đạn
    for (size_t i = 0; i < bullets.size(); ++i) {
        if (bullets[i].active) {
            // Tăng bán kính (mở rộng vòng tròn)
            bullets[i].radius += expandSpeed * deltaTime;

            // Tính vị trí mới dựa trên góc và bán kính
            float xOffset = bullets[i].radius * std::cos(bullets[i].angle * DEG_TO_RAD);
            float yOffset = bullets[i].radius * std::sin(bullets[i].angle * DEG_TO_RAD);
            bullets[i].sprite.setPosition(bossPos.x + xOffset, bossPos.y + yOffset);

            // Xóa viên đạn nếu ra khỏi màn hình
            sf::Vector2f bulletPos = bullets[i].sprite.getPosition();
            if (bulletPos.x < 0 || bulletPos.x > 800 || bulletPos.y < 0 || bulletPos.y > 600) {
                bullets.erase(bullets.begin() + i);
                --i;
            }
        }
    }
}

void Boss_skill::draw(sf::RenderWindow& window) const {
    for (const auto& bullet : bullets) {
        if (bullet.active) {
            window.draw(bullet.sprite);
        }
    }
}

bool Boss_skill::checkCollision(const sf::FloatRect& playerBounds, bool& gameOver) const {
    for (const auto& bullet : bullets) {
        if (bullet.active && bullet.getCollisionBounds().intersects(playerBounds)) { // Dùng getCollisionBounds thay vì getGlobalBounds
            gameOver = true;
            std::cout << "Game Over! Boss Skill hit Player!" << std::endl;
            return true;
        }
    }
    return false;
}