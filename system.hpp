
#pragma once
#include <chrono>
#include "global.hpp"
#include "player1.hpp"
#include "player2.hpp"
#include <vector>

enum State {
    IN_GAME,
    WHITE_SHEEP_VICTORY_SCREEN,
    BLACK_SHEEP_VICTORY_SCREEN,
    EXIT
};


class System {
private:
    Font font; 
    State state;
    Text healthText1;
    Text healthText2;
    RenderWindow window;
    Texture backgroundTexture;
    Sprite backgroundSprite;
    CircleShape healthCircle1;
    CircleShape healthCircle2;
    Music backgroundMusic;

    //queue<Player1*> players1;
    //vector<Player2*> players2;
    //int power[4][2];
    //int collision[4][2];
    //int coordinate[4][2];
    //int line;

    int currentLine1;
    int currentLine2;

    int playerHealth1;
    int playerHealth2;
    bool isFirstSpawn1;
    bool isFirstSpawn2;

    vector<PlayerBase*> linePlayers1[LINECOUNT]; 
    vector<PlayerBase*> linePlayers2[LINECOUNT]; 

    vector<ConvexShape*> lines1;
    vector<ConvexShape*> lines2;
    vector<CircleShape> sheepCircles1;
    vector<CircleShape> sheepCircles2;
    Clock clock;
    CircleShape healthCircle;
    Text healthText;
    chrono::steady_clock::time_point lastSpawnTime1;
    chrono::steady_clock::time_point lastSpawnTime2;
    deque<SheepConfigs> sheepQueue1;
    deque<SheepConfigs> sheepQueue2;
    void reverseDirection(); 
    void initializeLines1();
    void initializeLines2();
    void highlightLine1();
    void highlightLine2();
    void updateHealthDisplay1(); 
    void updateHealthDisplay2();
    void updateSheepCircles1();
    void updateSheepCircles2();
    void initializeMusic();
    void highlightLine();
    void handle_events();
    void handle_key(Keyboard::Key key);
    void checkCollisions(int lineIndex);
    void handleTeamCollisions(vector<PlayerBase*>& linePlayers);
    void checkCollisionsRecursive(vector<PlayerBase*>& team1, vector<PlayerBase*>& team2, int& linePower);
    int calculateLineStrength(const vector<PlayerBase*>& linePlayers);
    void updatePlayers(vector<PlayerBase*> linePlayers[], int& playerHealth, float boundaryX, bool isPlayer1);

public:
    System(int width, int height);
    ~System();

    void run();
    void render();
};
