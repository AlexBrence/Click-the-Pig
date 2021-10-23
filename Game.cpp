//
// Created by alex on 23. 10. 21.
//

#include <iostream>
#include <sstream>
#include "Game.h"

Game::Game()
    : points(0), health(20), piggySpawnTimer(piggySpawnTimerMax), mouseHeld(false), endGame(false) {

    // Window init
    window = std::make_shared<sf::RenderWindow>(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT),
                                                "Click the Pig",
                                                sf::Style::Close);
    window->setPosition(sf::Vector2<int>(500, 300));
    window->setFramerateLimit(60);

    // Fonts init
    if (!font.loadFromFile("/home/alex/Documents/Letnik02/RPO/tasks/task02/Click-the-Pig/Fonts/IndieFlower-Regular.ttf")) {
        std::cout << "ERROR GAME::CONSTRUCTOR: Failed to load the font!\n";
    }

    // Text init
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    text.setString("NONE");
}


/* FUNCTIONS */

// Get
bool Game::running() const {
    return window->isOpen();
}

bool Game::getEndGame() const {
    return endGame;
}


// Update
void Game::pollEvents() {
    while (window->pollEvent(event)) {

        switch (event.type) {
            case sf::Event::Closed:
                window->close();
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
        ss << "GAME OVER";
        text.setString(ss.str());
        text.setFillColor(sf::Color::Red);
        text.setCharacterSize(50);
        text.setPosition(WIN_WIDTH / 3, WIN_HEIGHT / 3);
    }
    else {
        ss << "Points: " << points
           << "\nHealth: " << health
           << "\n";
        text.setString(ss.str());
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

    renderText(*window);

    window->display();
}



































