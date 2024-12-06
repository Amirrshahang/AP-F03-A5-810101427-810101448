#pragma once

#include "global.hpp" // در صورت نیاز
class System;         // پیش‌اعلام برای جلوگیری از وابستگی متقابل

class Player {
private:
    Vector2f pos;
    Sprite sprite;
    Texture texture;
    float speedX;

public:
    Player(int x, int y, float speed = 2.0f);
    ~Player();
    void render(sf::RenderWindow& window);
    void update();
    bool move(float boundaryX); 
};
