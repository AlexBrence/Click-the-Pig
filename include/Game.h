#pragma once

#include <memory>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/Window/VideoMode.hpp>
#include "Pig.h"

class Game {
public:
  /* CONSTRUCTORS, DESTRUCTORS */
  Game();
  virtual ~Game() = default;

  /* FUNCTIONS */
  // Get
  bool running() const;
  bool getEndGame() const;

  void spawnPig();

  // Update
  void pollEvents();

  /**
   * Gets and sets mouse position relative to the window
   */
  void updateMousePosition();

  /**
   * Updates the points and health
   */
  void updateText();

  /**
   * Updates the spawn timer and spawns pigs
   */
  void updatePigs();

  /**
   * Updates the game and components of it
   */
  void update();

  // Render
  /**
   * Draws the text in the window
   */
  void renderText(sf::RenderTarget& target);

  /**
   * Clears old frames and draws new objects
   */
  void render();
private:
  /* VARIABLES */

  // Constants
  const uint32_t m_WIN_WIDTH          = 800;
  const uint32_t m_WIN_HEIGHT         = 600;
  const float    m_piggySpawnTimerMax = 20.0f;
  const uint8_t  m_maxPiggies          = 5;

  // Pig
  std::vector<std::shared_ptr<Pig>> m_pigs;

  // m_window
  std::shared_ptr<sf::RenderWindow> m_window = nullptr;
  sf::Event m_event{};

  // Mouse pos
  sf::Vector2<int32_t> m_mousePositionWindow;
  sf::Vector2<float>   m_mousePositionView;

  // font, text, sound
  sf::Font        m_font;
  sf::Text        m_text;
  sf::SoundBuffer m_soundBuffer;
  sf::Sound       m_sound;

  // Gameplay vars
  uint32_t m_points           = 0;
  int32_t  m_health           = 5;
  float    m_piggySpawnTimer  = m_piggySpawnTimerMax;
  bool     m_mouseHeld        = false;
  bool     m_endGame          = false;

  // Private functions
  void initWindow();
  void initFonts();
  void initText();
  void initSound();
};
