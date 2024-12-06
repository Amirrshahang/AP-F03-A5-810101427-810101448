#include "player.hpp"
#include "Configs.hpp"


const int v = 15;

Player::Player(int x, int y, float speed) : pos(x, y), speedX(speed) {
   pos = Vector2f(x, y);
    if (!texture.loadFromFile(PICS_PATH + "player1.png")) {
        throw runtime_error("Failed to load player image!");
    }
    sprite.setTexture(texture);
    sprite.setPosition(pos);
    sprite.setScale(0.35f, 0.35f);
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

