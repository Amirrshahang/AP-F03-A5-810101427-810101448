
#pragma once

#include "playerBase.hpp"

class Player1 : public PlayerBase {
public:
    Player1(int x, int y, float speed, const SheepConfigs& config);
    ~Player1() override = default;
    bool isOutOfBoundary(float boundaryX) const override;
    int& getCurrentLine() override;
    bool move(float boundaryX) override;
    int getStrength() const override;
    FloatRect getGlobalBounds() const override;
    int getDamage();

};
