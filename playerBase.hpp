#pragma once

#include "global.hpp"
#include "Configs.hpp"

class PlayerBase {
protected:
    Vector2f pos;
    float speedX;
    const SheepConfigs& sheepConfig;
    Texture texture;
    Sprite sprite;
    vector<ConvexShape*> lines;
    int currentLine = 0; 
    bool isFirstSpawn = true; 
    virtual int& getCurrentLine() = 0; 

public:
    PlayerBase(int x, int y, const SheepConfigs& config);
    virtual ~PlayerBase(); 
    virtual void reverseDirection();
    virtual int getStrength() const;
    virtual FloatRect getGlobalBounds() const = 0;
    virtual int getDamage();
    virtual bool isOutOfBoundary(float boundaryX) const = 0;
    virtual void render(RenderWindow& window);
    virtual bool move(float boundaryX);
    int getSpeed() const;
    void speedHandling(int updateSpeed);
    void stop();
    bool isStopped() const;


   
};
