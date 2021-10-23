//
// Created by alex on 23. 10. 21.
//

#ifndef CLICK_THE_PIG_GAME_H
#define CLICK_THE_PIG_GAME_H


#include <memory>
#include <vector>

// Precompiled headers
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/Window/VideoMode.hpp>

class Game {
private:
    /* VARIABLES */

    // Constants
    const int WIN_WIDTH = 800;
    const int WIN_HEIGHT = 600;
    const float piggySpawnTimerMax = 20.f;
    const int maxPiggys = 5;

    // Window
    std::shared_ptr<sf::RenderWindow> window = nullptr;
    sf::Event event;

    // Mouse pos
    sf::Vector2<int> mousePositionWindow;
    sf::Vector2<float> mousePositionView;

    // Font and Text
    sf::Font font;
    sf::Text text;

    // Gameplay vars
    int points;
    int health;
    float piggySpawnTimer;
    bool mouseHeld;
    bool endGame;


public:
    /* CONSTRUCTORS, DESTRUCTORS */
    Game();
    virtual ~Game() = default;

    /* FUNCTIONS */

    // Get
    bool running() const;
    bool getEndGame() const;

    // Update
    void pollEvents();
    void updateMousePosition();
    void updateText();
    void update();

    // Render
    void renderText(sf::RenderTarget& target);
    void render();

};


#endif //CLICK_THE_PIG_GAME_H
