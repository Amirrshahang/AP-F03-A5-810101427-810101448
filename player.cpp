#include "player.hpp"
#include "Configs.hpp"


const int v = 15;

Player::Player(int x, int y, float speed, const SheepConfigs& config) 
    : pos(x, y), speedX(speed), sheepConfig(config) {
    if (!texture.loadFromFile(config.texturePath)) { // بارگذاری تصویر خاص گوسفند
        throw std::runtime_error("Failed to load player image: " + config.texturePath);
    }
    sprite.setTexture(texture);
    sprite.setPosition(pos);
    sprite.setScale(0.35f, 0.35f); // تنظیم اندازه بازیکن
}


Player::~Player() {}



void Player::render(RenderWindow &window) {
    window.draw(sprite);
}

bool Player::move(float boundaryX) {
    pos.x += speedX; 
    sprite.setPosition(pos);

    if (pos.x > boundaryX) {
        return true; 
    }
    return false;
}


void Player::update() {
    sprite.setPosition(pos);
}