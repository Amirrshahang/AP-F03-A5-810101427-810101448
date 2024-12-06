#include "system.hpp"

System::System(int width, int height) {
    window.create(VideoMode(width + 20, height), "SHEEP FIGHT", Style::Close);
    window.setFramerateLimit(FRAME_RATE);
    state = IN_GAME;

    if (!backgroundTexture.loadFromFile(PICS_PATH + "bg8.png")) {
        return;
    }
    backgroundSprite.setTexture(backgroundTexture);

    lineCount = 5;
    currentLine = 2; 
    initializeLines();

}

System::~System() {
    for (Player* player : players) {
        delete player;
    }
    for (RectangleShape* line : lines) {
        delete line;
    }
}

void System::initializeLines() {    

    for (int i = 0; i < lineCount; i++) {
        if(i == lineCount-1){
            RectangleShape* line = new RectangleShape(Vector2f(window.getSize().x, LINEHEIGHT));
            line->setPosition(0, OFFSET + i * (LINEHEIGHT + SPACING-2));
            line->setFillColor(Color::Transparent); 
            lines.push_back(line);

        }
        else{
            RectangleShape* line = new RectangleShape(Vector2f(window.getSize().x, LINEHEIGHT));
            line->setPosition(0, OFFSET + i * (LINEHEIGHT + SPACING));
            line->setFillColor(Color::Transparent); 
            lines.push_back(line);

        }   
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
                window.close(); // بستن پنجره
                state = EXIT;   // تغییر حالت بازی به خروج
            } else {
                handle_key(event.key.code); // مدیریت سایر کلیدها
            }
            break;
        default:
            break;
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
                    currentLine =4;
                    highlightLine();
                }
                break;

            case Keyboard::Down:
                if (currentLine <= lineCount - 1) {
                    currentLine++;
                    highlightLine();
                }
                if(currentLine > 4){
                    currentLine = 0;
                    highlightLine();
                }
                break;

            case Keyboard::Enter: {
            
                float X = 150;
                float Y = OFFSET/2 + currentLine * (LINEHEIGHT + SPACING) + LINEHEIGHT / 2;
                Player* newPlayer = new Player(X,Y,2.0f);
                players.push_back(newPlayer);

                break;
            }

            default:
                break;
        }
    }
}

void System::updatePlayers() {
    for (auto it = players.begin(); it != players.end();) {
        if ((*it)->move(1050)) { 
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


    window.display();
}
