#include "system.hpp"

System::System(int width, int height) {
    window.create(VideoMode(width + 20, height), "SHEEP FIGHT", Style::Close);
    window.setFramerateLimit(FRAME_RATE);
    state = IN_GAME;


    if (!backgroundTexture.loadFromFile(PICS_PATH + "background.png")) {
        throw runtime_error("Failed to load background image!");
    }
    backgroundSprite.setTexture(backgroundTexture);

    if (!font.loadFromFile(FONTS_PATH + "KaiseiDecol-Medium.ttf")) {
        throw runtime_error("Failed to load font!");
    }


    float spacing = 20;

    currentLine1 = 0; 
    currentLine2 = 0;

    playerHealth1 = INITIAL_HEALTH;
    playerHealth2= INITIAL_HEALTH;

    lastSpawnTime1 = chrono::steady_clock::now();
    lastSpawnTime2 = chrono::steady_clock::now();

    isFirstSpawn1 = true;
    isFirstSpawn2 = true;

    initializeLines1();
    initializeLines2();

    float radius = 25;
    healthCircle1.setRadius(radius);  
    healthCircle1.setFillColor(Color::Green); 
    healthCircle1.setOutlineThickness(1); 
    healthCircle1.setOutlineColor(Color::Black); 
    healthCircle1.setPosition(30, 327); 

    healthText1.setFont(font);
    healthText1.setCharacterSize(24);
    healthText1.setFillColor(Color::Black);
    healthText1.setPosition(34, 337);
    
    healthCircle2.setRadius(radius);  
    healthCircle2.setFillColor(Color::Green); 
    healthCircle2.setOutlineThickness(1); 
    healthCircle2.setOutlineColor(Color::Black); 
    healthCircle2.setPosition(1137, 327); 

    healthText2.setFont(font);
    healthText2.setCharacterSize(24);
    healthText2.setFillColor(Color::Black);
    healthText2.setPosition(1141, 337);

    updateHealthDisplay1();
    updateHealthDisplay2();



    for (int i = 0; i < 3; ++i) {
        CircleShape circle(radius);
        circle.setFillColor(Color::Transparent);
        circle.setOutlineThickness(2);
        circle.setOutlineColor(Color::Transparent);
        circle.setPosition(230 + i * (radius * 2 + spacing), 33);
        sheepCircles1.push_back(circle);
    }
    for (int i = 0; i < 3; ++i) {
        CircleShape circle(radius);
        circle.setFillColor(Color::Transparent);
        circle.setOutlineThickness(2);
        circle.setOutlineColor(Color::Transparent);
        circle.setPosition(960 - i * (radius * 2 + spacing), 33);
        sheepCircles2.push_back(circle);
    }

    

    for (const auto& sheep : SHEEP_CONFIGS1) {
        sheepQueue1.push_back(sheep); 
    }
    for (const auto& sheep : SHEEP_CONFIGS2) {
        sheepQueue2.push_back(sheep); 
    }

    updateSheepCircles1(); 
    updateSheepCircles2();

}


System::~System() {
    for (int i = 0; i < LINECOUNT; ++i) {
        for (PlayerBase* player : linePlayers1[i]) {
            delete player;
        }
        linePlayers1[i].clear();

        for (PlayerBase* player : linePlayers2[i]) {
            delete player;
        }
        linePlayers2[i].clear();
    }

    for (ConvexShape* line : lines1) {
        delete line;
    }
    lines1.clear();

    for (ConvexShape* line : lines2) {
        delete line;
    }
    lines2.clear();
}



void System::initializeLines1() {
    float startX = 160;

    for (int i = 0; i < LINECOUNT; i++) {
        ConvexShape* triangle = new ConvexShape(3);
        triangle->setPoint(0, Vector2f(startX, OFFSET + i * (LINEHEIGHT + SPACING)));
        triangle->setPoint(1, Vector2f(startX + 20, OFFSET + i * (LINEHEIGHT + SPACING) + LINEHEIGHT / 2)); 
        triangle->setPoint(2, Vector2f(startX, OFFSET + i * (LINEHEIGHT + SPACING) + LINEHEIGHT)); 
        if (i == currentLine1) {
            triangle->setFillColor(Color(255, 255, 255, 100)); 
        } else {
            triangle->setFillColor(Color::Transparent);
        }
        lines1.push_back(triangle);
    }
}

void System::initializeLines2() {
    float startX = 1092;

    for (int i = 0; i < LINECOUNT; i++) {
        ConvexShape* triangle = new ConvexShape(3);
        triangle->setPoint(0, Vector2f(startX, OFFSET + i * (LINEHEIGHT + SPACING)));
        triangle->setPoint(1, Vector2f(startX - 20, OFFSET + i * (LINEHEIGHT + SPACING) + LINEHEIGHT / 2)); 
        triangle->setPoint(2, Vector2f(startX, OFFSET + i * (LINEHEIGHT + SPACING) + LINEHEIGHT)); 
        if (i == currentLine2) {
            triangle->setFillColor(Color(255, 255, 255, 100)); 
        } else {
            triangle->setFillColor(Color::Transparent);
        }
        lines2.push_back(triangle);
    }
}

void System::updateHealthDisplay1() {
    healthText1.setString(to_string(playerHealth1));
}

void System::updateHealthDisplay2() {
    healthText2.setString(to_string(playerHealth2));
}

void System::updateSheepCircles1() {
    for (size_t i = 0; i < sheepCircles1.size(); ++i) {
        if (i < sheepQueue1.size()) {
            Texture texture;
            if (!texture.loadFromFile(sheepQueue1[i].texturePath)) {
                cerr << "Failed to load sheep texture: " << sheepQueue1[i].texturePath << endl;
                continue;
            }
            Sprite sprite(texture);
            sprite.setScale(
                sheepCircles1[i].getGlobalBounds().width / texture.getSize().x,
                sheepCircles1[i].getGlobalBounds().height / texture.getSize().y
            );
            sprite.setPosition(sheepCircles1[i].getPosition());
            window.draw(sprite);
        }
    }
}

void System::updateSheepCircles2() {
    for (size_t i = 0; i < sheepCircles2.size(); ++i) {
        if (i < sheepQueue2.size()) {
            Texture texture;
            if (!texture.loadFromFile(sheepQueue2[i].texturePath)) {
                cerr << "Failed to load sheep texture: " << sheepQueue2[i].texturePath << endl;
                continue;
            }
            Sprite sprite(texture);
            sprite.setScale(
                sheepCircles2[i].getGlobalBounds().width / texture.getSize().x,
                sheepCircles2[i].getGlobalBounds().height / texture.getSize().y
            );
            sprite.setPosition(sheepCircles2[i].getPosition());
            window.draw(sprite);
        }
    }
}

void System::highlightLine1() {
    for (int i = 0; i < lines1.size(); i++) {
        if (i == currentLine1) {
            lines1[i]->setFillColor(Color(255, 255, 255, 100)); 
        } else {
            lines1[i]->setFillColor(Color::Transparent); 
        }
    }
}

void System::highlightLine2() {
    for (int i = 0; i < lines2.size(); i++) {
        if (i == currentLine2) {
            lines2[i]->setFillColor(Color(255, 255, 255, 100)); 
        } else {
            lines2[i]->setFillColor(Color::Transparent); 
        }
    }
}

void System::updatePlayers(vector<PlayerBase*> linePlayers[], int& playerHealth, float boundaryX, bool isPlayer1) {
    for (int i = 0; i < LINECOUNT; ++i) {
        auto& playersInLine = linePlayers[i];
        for (auto it = playersInLine.begin(); it != playersInLine.end();) {
            if ((*it)->move(boundaryX)) {
                playerHealth -= (*it)->getDamage();
                if (playerHealth <= 0) {
                    playerHealth = 0;
                    state = EXIT;
                }

                if (isPlayer1) {
                    updateHealthDisplay2();
                } else {
                    updateHealthDisplay1();
                }

                delete *it;
                it = playersInLine.erase(it);
            } else {
                ++it;
            }
        }
    }
}


void System::run() {
    while (window.isOpen()&& state != EXIT) {
        handle_events();
        updatePlayers(linePlayers1, playerHealth2, 1030, true);
        updatePlayers(linePlayers2, playerHealth1, 130, false);

         for (int i = 0; i < LINECOUNT; ++i) {
             checkCollisions(i);
         }

        render();
    }
    exit(0);
}

void System::handle_events() {
    Event event;
    while (window.pollEvent(event)) {
        switch (event.type) {
        case Event::Closed:
            window.close();
            state = EXIT;
            break;
        case Event::KeyPressed:
            if (event.key.code == Keyboard::Escape) {
                window.close(); 
                state = EXIT;   
            } else {
                handle_key(event.key.code); 
            }
            break;
        default:
            break;
        }
    }
}

void handleTeamCollisions(vector<PlayerBase*>& linePlayers) {
    for (auto it = linePlayers.begin(); it != linePlayers.end(); ++it) {
        auto next = it + 1;
        if (next != linePlayers.end() && (*it)->isStopped()) {
            if ((*it)->getGlobalBounds().intersects((*next)->getGlobalBounds())) {
                (*next)->stop();
            }
        }
    }
}

 void System::checkCollisions(int lineIndex) {
     auto& players1InLine = linePlayers1[lineIndex];
     auto& players2InLine = linePlayers2[lineIndex];

    for (auto it1 = players1InLine.begin(); it1 != players1InLine.end(); ++it1) {
        for (auto it2 = players2InLine.begin(); it2 != players2InLine.end(); ++it2) {
            if ((*it1)->getGlobalBounds().intersects((*it2)->getGlobalBounds())) { 
                if ((*it1)->getStrength() > (*it2)->getStrength()) {
                    
                    (*it2)->speedHandling((*it1)->getSpeed());

                }else if ((*it1)->getStrength() < (*it2)->getStrength()) {

                    (*it1)->speedHandling((*it2)->getSpeed());

                }else {
                     (*it1)->stop();
                     (*it2)->stop();
                }
            }
        }
    }

    handleTeamCollisions(linePlayers1[lineIndex]); 
    handleTeamCollisions(linePlayers2[lineIndex]); 

}



void System::handle_key(Keyboard::Key key) {
    if (state == IN_GAME) {
        switch (key) {
            case Keyboard::Up:
                if (currentLine1 >= 0) {
                    currentLine1--;
                    highlightLine1();
                }
                if(currentLine1 < 0){
                    currentLine1 = LINECOUNT - 1;
                    highlightLine1();
                }
                break;
            case Keyboard::Down:
               if (currentLine1 <= LINECOUNT - 1) {
                    currentLine1++;
                    highlightLine1();
                }
                if(currentLine1 > LINECOUNT - 1){
                    currentLine1 = 0;
                    highlightLine1();
                }
                break;

            case Keyboard::W:
                if (currentLine2 >= 0) {
                    currentLine2--;
                    highlightLine2();
                }
                if(currentLine2 < 0){
                    currentLine2 = LINECOUNT - 1;
                    highlightLine2();
                }
                break;
            case Keyboard::S:
               if (currentLine2 <= LINECOUNT - 1) {
                    currentLine2++;
                    highlightLine2();
                }
                if (currentLine2 > LINECOUNT-1) {
                    currentLine2 = 0;
                    highlightLine2();
                }
                break;
            case Keyboard::Enter: {
                auto now = chrono::steady_clock::now(); 
                auto elapsed = chrono::duration_cast<chrono::milliseconds>(now - lastSpawnTime1).count();

                if (isFirstSpawn1 || elapsed >= COOLDOWN_MS) { 
                    float X = 140;
                    float Y = OFFSET / 2 + currentLine1 * (LINEHEIGHT + SPACING) + 2 * LINEHEIGHT / 3;
                    if (!sheepQueue1.empty()) {
                        const SheepConfigs& selectedSheep1 = sheepQueue1.front(); 
                        Player1* newPlayer = new Player1(X, Y, CONSTANT_SPEED, selectedSheep1);
                        linePlayers1[currentLine1].push_back(newPlayer);

                        sheepQueue1.pop_front(); 
                        if (!SHEEP_CONFIGS1.empty()) {
                            sheepQueue1.push_back(SHEEP_CONFIGS1[rand() % SHEEP_CONFIGS1.size()]);
                        }

                        updateSheepCircles1(); 
                    }

                    lastSpawnTime1 = now; 
                    isFirstSpawn1 = false; 
                }
                break;
            }

            case Keyboard::Space: {
                auto now = chrono::steady_clock::now();
                auto elapsed = chrono::duration_cast<chrono::milliseconds>(now - lastSpawnTime2).count();

                if (isFirstSpawn2 || elapsed >= COOLDOWN_MS) { 
                    float X = 1025;
                    float Y = OFFSET / 2 + currentLine2 * (LINEHEIGHT + SPACING) + 2 * LINEHEIGHT / 3;
                    if (!sheepQueue2.empty()) {
                        const SheepConfigs& selectedSheep2 = sheepQueue2.front(); 
                        Player2* newPlayer = new Player2(X, Y, CONSTANT_SPEED, selectedSheep2);
                        linePlayers2[currentLine2].push_back(newPlayer);

                        sheepQueue2.pop_front(); 
                        if (!SHEEP_CONFIGS2.empty()) {
                            sheepQueue2.push_back(SHEEP_CONFIGS2[rand() % SHEEP_CONFIGS2.size()]);
                        }
                        updateSheepCircles2(); 
                    }

                    lastSpawnTime2 = now; 
                    isFirstSpawn2 = false; 
                }
                break;
            }
            default:
                break;
        }
    }
}
void System::render() {
    window.clear();
    window.draw(backgroundSprite);

    for (auto& line : lines1) {
        window.draw(*line);
    }
    for (auto& line : lines2) {
        window.draw(*line);
    }

    for (int i = 0; i < LINECOUNT; ++i) {
        for (auto& player : linePlayers1[i]) {
            player->render(window);
        }
    }

    for (int i = 0; i < LINECOUNT; ++i) {
        for (auto& player : linePlayers2[i]) {
            player->render(window);
        }
    }

    for (auto& circle : sheepCircles1) {
        window.draw(circle);
    }
    for (auto& circle : sheepCircles2) {
        window.draw(circle);
    }

    updateSheepCircles1();
    updateSheepCircles2();

    window.draw(healthCircle1);
    window.draw(healthText1);

    window.draw(healthCircle2);
    window.draw(healthText2);

    window.display();
}
