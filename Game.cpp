//
// Created by alex on 23. 10. 21.
//

#include <iostream>
#include <sstream>
#include "Game.h"

/* PRIVATE FUNCTIONS */
void Game::initWindow() {
    window = std::make_shared<sf::RenderWindow>(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT),
                                                "Click the Pig",
                                                sf::Style::Close);
    window->setPosition(sf::Vector2<int>(500, 300));
    window->setFramerateLimit(60);
}

void Game::initFonts() {
    if (!font.loadFromFile("/home/alex/Documents/Letnik02/RPO/tasks/task02/Click-the-Pig/Fonts/IndieFlower-Regular.ttf")) {
        std::cout << "[ERROR::GAME::CONSTRUCTOR] Failed to load the font!\n";
    }
}

void Game::initText() {
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    text.setString("NONE");
}

void Game::initSound() {
    if (!soundBuffer.loadFromFile("/home/alex/Documents/Letnik02/RPO/tasks/task02/Click-the-Pig/Sounds/pig01.ogg")) {
        std::cout << "[ERROR::GAME::CONSTRUCTOR] Failed to load the sound!\n";
    }
    sound.setBuffer(soundBuffer);
}



/* CONSTRUCTOR */
Game::Game()
    : points(0), health(20), piggySpawnTimer(piggySpawnTimerMax), mouseHeld(false), endGame(false) {

    initWindow();
    initFonts();
    initText();
    initSound();
    spawnPig();
    std::cout << "out\n";
}


/* FUNCTIONS */

// Get
bool Game::running() const {
    return window->isOpen();
}

bool Game::getEndGame() const {
    return endGame;
}


void Game::spawnPig() {
    std::shared_ptr<Pig> pig = std::make_shared<Pig>();

    pig->setPosition(
            static_cast<float>(rand() % static_cast<int>(window->getSize().x - pig->getTexture().getSize().x)),
            0.f
    );

    pigs.push_back(pig);
}



// Update
void Game::pollEvents() {
    while (window->pollEvent(event)) {

        switch (event.type) {
            case sf::Event::Closed:
                window->close();
                break;

            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Escape) {
                    window->close();
                }
                break;
        }
    }
}

void Game::updateMousePosition() {
    /**
     * Gets and sets mouse position relative to the window
     */
    mousePositionWindow = sf::Mouse::getPosition(*window);
    mousePositionView = window->mapPixelToCoords(mousePositionWindow);
}


void Game::updateText() {
    /**
     * Updates the points and health
     */

    std::stringstream ss;

    if (endGame) {
        ss << "GAME OVER\n"
           << "Points: " << points;

        text.setFillColor(sf::Color::Red);
        text.setCharacterSize(50);
        text.setPosition(WIN_WIDTH / 3, WIN_HEIGHT / 3);
    }
    else {
        ss << "Points: " << points
           << "\nHealth: " << health
           << "\n";
    }
    text.setString(ss.str());

}

void Game::updatePigs() {

    // Updates the spawn timer and spawns pigs
    if (pigs.size() < maxPiggys) {
        if (piggySpawnTimer >= piggySpawnTimerMax) {
            spawnPig();
            piggySpawnTimer = 0.f;
        }
        else {
            piggySpawnTimer += 1.f;
        }
    }

    // Moving and updating pigs
    for (int i = 0; i < pigs.size(); i++) {
        pigs[i]->move();

        if (pigs[i]->getSprite().getPosition().y > window->getSize().y) {
            pigs.erase(pigs.begin() + i);
            health--;
            std::cout << "Size: " << pigs.size() << "\n";
        }


    }
    // Check if clicked upon
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

        if (!mouseHeld) {
            mouseHeld = true;

            for (int i = 0; i < pigs.size(); i++) {
                if (pigs[i]->getSprite().getGlobalBounds().contains(mousePositionView)) {
                    sound.play();
                    points += 1;
                    std::cout << "Points: " << points << "\n";
                    pigs.erase(pigs.begin() + i);
                }
            }
        }
    }
    else {
        mouseHeld = false;
    }
}


void Game::update() {
    /**
     * Updates the game and components of it
     */

    pollEvents();

    if (!endGame) {
        updateMousePosition();
        updateText();
        updatePigs();
    }

    if (health <= 0) {
        updateText();
        endGame = true;
    }
}


// Render
void Game::renderText(sf::RenderTarget &target) {
    /**
     * Draws the text in the window
     */

    target.draw(text);
}


void Game::render() {
    /**
     * Clears old frames and draws new objects
     */

    window->clear();

    for (auto& p : pigs) {
        p->render(*window);
    }

    renderText(*window);

    window->display();
}

