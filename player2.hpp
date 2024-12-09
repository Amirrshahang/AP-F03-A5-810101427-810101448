
#pragma once
#include "playerBase.hpp"

class Player2 : public PlayerBase {
private:
    int currentLine; 

public:
    Player2(int x, int y, float speed , const SheepConfigs& config);
    ~Player2() override = default;
    int& getCurrentLine() override;
    bool move(float boundaryX) override;
    bool isOutOfBoundary(float boundaryX) const override;
    int getStrength() const override;
    FloatRect getGlobalBounds() const override;
    int getDamage();

};
