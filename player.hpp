#pragma once

#include "global.hpp" 
#include "Configs.hpp" 

class System;         // پیش‌اعلام برای جلوگیری از وابستگی متقابل

class Player {
private:
    Vector2f pos;
    Sprite sprite;
    Texture texture;
    float speedX;
    SheepConfigs sheepConfig;

public:
    Player(int x, int y, float speed, const SheepConfigs& config);
    ~Player();
    void render(sf::RenderWindow& window);
    void update();
    bool move(float boundaryX); 
};