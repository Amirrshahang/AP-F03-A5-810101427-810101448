#pragma once

#include <chrono>
#include "global.hpp"
#include "player.hpp"
#include <vector>

enum State {
    IN_GAME,
    PAUSE_MENU,
    MAIN_MENU,
    LEVEL_SELECT,
    VICTORY_SCREEN,
    GAMEOVER_SCREEN,
    CREDITS,
    EXIT
};

class System {
public:
    System(int width, int height);
    void run();
    ~System();
    RenderWindow window;

private:
    State state;
    Player* player;
    Texture backgroundTexture;
    Sprite backgroundSprite;
    chrono::steady_clock::time_point lastSpawnTime;
    vector<RectangleShape*> lines;
    vector<Player*> players; 
    Font font;                    

    int currentLine;
    int lineCount;
    void highlightLine();  
    void render();
    void handle_events();
    void initializeLines();
    void updatePlayers();
    void handle_key(Keyboard::Key key);
};
