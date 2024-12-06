#pragma once

#include "global.hpp"

class MainMenu {
private:
    Font font;
    Text startText;
    Texture backgroundTexture;
    Sprite backgroundSprite;
    RectangleShape button;

public:
    MainMenu(int width, int height, RenderWindow& window);
    bool run(RenderWindow& window);
    void render(RenderWindow& window);
    void handleEvents(RenderWindow& window, bool& startGame);
};
