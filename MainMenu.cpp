#include "MainMenu.hpp"

MainMenu::MainMenu(int width, int height, RenderWindow& window) {

    if (!backgroundTexture.loadFromFile(PICS_PATH + "menu.png")) {
        throw runtime_error("Failed to load background image!");
    }
    
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(
        float(window.getSize().x) / backgroundTexture.getSize().x,
        float(window.getSize().y) / backgroundTexture.getSize().y
    );

    // تنظیم دکمه استارت
    button.setSize(Vector2f(350, 70)); // اندازه دکمه
    button.setFillColor(Color::Transparent); // دکمه شفاف (روی تصویر قرار دارد)
    button.setOutlineThickness(2);
    button.setOutlineColor(Color::Transparent);

    // موقعیت دکمه روی تصویر
    button.setPosition(
        (width / 2) - 180, // مرکز تصویر
        (height / 2) + 230 // پایین‌تر از مرکز
    );
}

void MainMenu::render(RenderWindow& window) {
    // رسم پس‌زمینه و دکمه
    window.clear(Color::Black);
    window.draw(backgroundSprite);
    window.draw(button);
    window.display();
}

void MainMenu::handleEvents(RenderWindow& window, bool& startGame) {
    Event event;
    while (window.pollEvent(event)) {
        if (event.type == Event::Closed) {
            window.close(); // بستن پنجره
        }
        if (event.type == Event::MouseButtonPressed) {
            Vector2i mousePos = Mouse::getPosition(window);
            if (button.getGlobalBounds().contains(static_cast<Vector2f>(mousePos))) {
                startGame = true; // شروع بازی
            }
        }
    }
}

bool MainMenu::run(RenderWindow& window) {
    bool startGame = false;
    while (window.isOpen() && !startGame) {
        handleEvents(window, startGame);
        render(window);
    }

    if (startGame) {
        window.clear(); // پاک کردن محتوا
        window.display();
    }

    return startGame;
}
