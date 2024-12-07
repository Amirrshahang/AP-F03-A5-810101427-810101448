#include "system.hpp"

System::System(int width, int height) {
    window.create(VideoMode(width + 20, height), "SHEEP FIGHT", Style::Close);
    window.setFramerateLimit(FRAME_RATE);
    state = IN_GAME;

    if (!backgroundTexture.loadFromFile(PICS_PATH + "background.png")) {
        return;
    }
    backgroundSprite.setTexture(backgroundTexture);
    lastSpawnTime = chrono::steady_clock::now();

    lineCount = 4;
    currentLine = 0; 
    initializeLines();
    isFirstSpawn = true;

    playerHealth = INITIAL_HEALTH;

    if (!font.loadFromFile(FONTS_PATH + "KaiseiDecol-Medium.ttf")) {
        throw runtime_error("Failed to load font!");
    }
    float radius = 25;

    healthCircle.setRadius(radius);  
    healthCircle.setFillColor(Color::Green); 
    healthCircle.setOutlineThickness(1); 
    healthCircle.setOutlineColor(sf::Color::Black); 
    healthCircle.setPosition(1137, 327); 

    healthText.setFont(font);
    healthText.setCharacterSize(24);
    healthText.setFillColor(sf::Color::Black);
    healthText.setPosition(1141, 337);
    


    updateHealthDisplay();

    float spacing = 20;
    float startX = 230; 

    for (int i = 0; i < 3; ++i) {
        CircleShape circle(radius);
        circle.setFillColor(Color::Transparent);
        circle.setOutlineThickness(2);
        circle.setOutlineColor(Color::Transparent);
        circle.setPosition(startX + i * (radius * 2 + spacing), 33);
        sheepCircles.push_back(circle);
    }

    for (const auto& sheep : SHEEP_CONFIGS) {
        sheepQueue.push_back(sheep); 
    }

    updateSheepCircles(); 

}

System::~System() {
    for (Player* player : players) {
        delete player;
    }
    for (sf::ConvexShape* line : lines) {
        delete line; 
    }

}

void System::initializeLines() {
    float startX = 160;
    float endX = 645;
    float lineWidth = endX - startX; 

    for (int i = 0; i < lineCount; i++) {
        ConvexShape* triangle = new ConvexShape(3);
        triangle->setPoint(0, Vector2f(startX, OFFSET + i * (LINEHEIGHT + SPACING)));
        triangle->setPoint(1, Vector2f(startX + 20, OFFSET + i * (LINEHEIGHT + SPACING) + LINEHEIGHT / 2)); 
        triangle->setPoint(2, Vector2f(startX, OFFSET + i * (LINEHEIGHT + SPACING) + LINEHEIGHT)); 
        if (i == currentLine) {
            triangle->setFillColor(Color(255, 255, 255, 100)); 
        } else {
            triangle->setFillColor(Color::Transparent);
        }
        lines.push_back(triangle);
    }
}


void System::highlightLine() {
    for (int i = 0; i < lines.size(); i++) {
        if (i == currentLine) {
            lines[i]->setFillColor(Color(255, 255, 255, 100)); 
        } else {
            lines[i]->setFillColor(Color::Transparent); 
        }
    }
}


void System::run() {
    while (window.isOpen() && state != EXIT) {
        handle_events();
        updatePlayers();
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

void System::updateSheepCircles() {
    for (size_t i = 0; i < sheepCircles.size(); ++i) {
        if (i < sheepQueue.size()) {
            Texture texture;
            if (!texture.loadFromFile(sheepQueue[i].texturePath)) {
                cerr << "Failed to load sheep texture: " << sheepQueue[i].texturePath << std::endl;
                continue;
            }
            Sprite sprite(texture);
            sprite.setScale(
                sheepCircles[i].getGlobalBounds().width / texture.getSize().x,
                sheepCircles[i].getGlobalBounds().height / texture.getSize().y
            );
            sprite.setPosition(sheepCircles[i].getPosition());
            window.draw(sprite);
        }
    }
}



void System::handle_key(Keyboard::Key key) {
    if (state == IN_GAME) {
        switch (key) {
            case Keyboard::Up:
                if (currentLine >= 0) {
                    currentLine--;
                    highlightLine();
                }
                if(currentLine < 0){
                    currentLine = lineCount - 1;
                    highlightLine();
                }
                break;

            case Keyboard::Down:
                if (currentLine <= lineCount - 1) {
                    currentLine++;
                    highlightLine();
                }
                if(currentLine > lineCount - 1){
                    currentLine = 0;
                    highlightLine();
                }
                break;

            case Keyboard::Enter: {
                auto now = std::chrono::steady_clock::now(); 
                auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastSpawnTime).count();

                if (isFirstSpawn || elapsed >= COOLDOWN_MS) { 
                    float X = 160;
                    float Y = OFFSET / 2 + currentLine * (LINEHEIGHT + SPACING) + 2 * LINEHEIGHT / 3;
                    if (!sheepQueue.empty()) {
                        const SheepConfigs& selectedSheep = sheepQueue.front(); 
                        Player* newPlayer = new Player(X, Y, CONSTANT_SPEED, selectedSheep);
                        players.push_back(newPlayer);

                        sheepQueue.pop_front(); 
                        if (!SHEEP_CONFIGS.empty()) {
                            sheepQueue.push_back(SHEEP_CONFIGS[rand() % SHEEP_CONFIGS.size()]);
                        }

                        updateSheepCircles(); 
                    }

                    lastSpawnTime = now; 
                    isFirstSpawn = false; 
                }
                break;
            }
            default:
                break;
        }
    }
}

void System::updateHealthDisplay() {
    healthText.setString(to_string(playerHealth));
}


void System::updatePlayers() {
    for (auto it = players.begin(); it != players.end();) {
        if ((*it)->move(1050)) {
            playerHealth -= (*it)->getDamage();
            if (playerHealth <= 0) {
                playerHealth = 0;
                state = EXIT ;
            }
            updateHealthDisplay();
            delete *it;
            it = players.erase(it);



        } else {
            ++it; 
        }
    }
}


void System::render() {
    window.clear();

    window.draw(backgroundSprite);

    for (auto& line : lines) {
        window.draw(*line);
    }
    for (auto& player : players) {
        player->render(window);
    }

    for (auto& circle : sheepCircles) {
        window.draw(circle);
    }

    updateSheepCircles();

    window.draw(healthCircle);
    window.draw(healthText);
    window.display();
}






