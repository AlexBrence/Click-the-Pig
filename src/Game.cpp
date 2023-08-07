#include "Game.h"

#include <iostream>
#include <sstream>

/* PRIVATE FUNCTIONS */
void Game::initWindow() 
{
  m_window = std::make_shared<sf::RenderWindow>(sf::VideoMode(m_WIN_WIDTH, m_WIN_HEIGHT),
      "Click the Pig",
      sf::Style::Close);
  m_window->setPosition(sf::Vector2<int>(500, 300));
  m_window->setFramerateLimit(60);
}

void Game::initFonts() 
{
  if (!m_font.loadFromFile("/home/alex/Programming/cpp/Click-the-Pig/Fonts/IndieFlower-Regular.ttf")) {
    printf("[ERROR %s::%s] Failed to load the font!\n", __FILE__, __FUNCTION__);
  }
}

void Game::initText() 
{
  m_text.setFont(m_font);
  m_text.setCharacterSize(24);
  m_text.setFillColor(sf::Color::White);
  m_text.setString("NONE");
}

void Game::initSound() 
{
  if (!m_soundBuffer.loadFromFile("/home/alex/Programming/cpp/Click-the-Pig/Sounds/pig01.ogg")) 
  {
    printf("[ERROR %s::%s] Failed to load the sound!\n", __FILE__, __FUNCTION__);
  }
  m_sound.setBuffer(m_soundBuffer);
}


/* CONSTRUCTOR */
Game::Game()
{
    initWindow();
    initFonts();
    initText();
    initSound();
    spawnPig();
}

/* FUNCTIONS */
// Get
bool Game::running() const 
{
  return m_window->isOpen();
}

bool Game::getEndGame() const 
{
  return m_endGame;
}

void Game::spawnPig() 
{
  std::shared_ptr<Pig> pig = std::make_shared<Pig>();

  pig->setPosition(
      static_cast<float>(rand() % static_cast<int>(m_window->getSize().x - pig->getTexture().getSize().x)),
      0.0f
  );
  m_pigs.push_back(pig);
}

// Update
void Game::pollEvents() 
{
  while (m_window->pollEvent(m_event)) 
  {
    switch (m_event.type) 
    {
      case sf::Event::Closed:
        m_window->close();
        break;
      case sf::Event::KeyPressed:
        if (m_event.key.code == sf::Keyboard::Escape) 
        {
          m_window->close();
        }
        break;
      default:
        break;
    }
  }
}

void Game::updateMousePosition() 
{
  m_mousePositionWindow = sf::Mouse::getPosition(*m_window);
  m_mousePositionView = m_window->mapPixelToCoords(m_mousePositionWindow);
}

void Game::updateText() 
{
  std::stringstream ss;
  if (m_endGame) 
  {
    ss << "GAME OVER\n"
       << "Points: " << m_points;

    m_text.setFillColor(sf::Color::Red);
    m_text.setCharacterSize(50);
    m_text.setPosition(static_cast<int32_t>(m_WIN_WIDTH / 3), static_cast<int32_t>(m_WIN_HEIGHT / 3));
  }
  else 
  {
    ss << "Points: " << m_points << "\n"
       << "Health: " << m_health << "\n";
  }
  m_text.setString(ss.str());
}

void Game::updatePigs() 
{
  if (m_pigs.size() < m_maxPiggies) 
  {
    if (m_piggySpawnTimer >= m_piggySpawnTimerMax) 
    {
      spawnPig();
      m_piggySpawnTimer = 0.0f;
    }
    else {
      m_piggySpawnTimer += 1.0f;
    }
  }

  // Moving and updating m_pigs
  for (int i = 0; i < m_pigs.size(); i++) 
  {
    m_pigs[i]->move();

    if (m_pigs[i]->getSprite().getPosition().y > m_window->getSize().y) 
    {
      m_pigs.erase(m_pigs.begin() + i);
      m_health--;
      std::cout << "Size: " << m_pigs.size() << "\n";
    }
  }

  // Check if clicked upon
  if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) 
  {
    if (!m_mouseHeld) 
    {
      m_mouseHeld = true;

      for (int i = 0; i < m_pigs.size(); i++) 
      {
        if (m_pigs[i]->getSprite().getGlobalBounds().contains(m_mousePositionView)) 
        {
          m_sound.play();
          m_points += 1;
          std::cout << "m_points: " << m_points << "\n";
          m_pigs.erase(m_pigs.begin() + i);
        }
      }
    }
  }
  else 
  {
    m_mouseHeld = false;
  }
}

void Game::update() 
{
  pollEvents();

  if (!m_endGame) 
  {
    updateMousePosition();
    updateText();
    updatePigs();
  }

  if (m_health <= 0) 
  {
    updateText();
    m_endGame = true;
  }
}

// Render
void Game::renderText(sf::RenderTarget &target) 
{
  target.draw(m_text);
}

void Game::render() {
  m_window->clear();

  for (const auto& p : m_pigs) {
    p->render(*m_window);
  }
  renderText(*m_window);
  m_window->display();
}
