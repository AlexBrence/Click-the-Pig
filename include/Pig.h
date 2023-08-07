#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Pig 
{
public:
  /* CONSTRUCTOR */
  Pig();

  /* FUNCTIONS */
  // Get
  sf::Vector2<unsigned int> getSize()     const;
  sf::Vector2<float>        getPosition() const;
  sf::Sprite                getSprite()   const;
  sf::Texture               getTexture() const;

  // Set
  void setPosition(const float x, const float y);

  // Other
  void move();
  void update();
  void render(sf::RenderTarget& target);

private:
  /* VARIABLES */

  // Constants
  const float fallingSpeed = 4.0f;

  // Sprite
  sf::Sprite    sprite;
  sf::Texture   m_texture;
  sf::FloatRect spriteSize;

  /* PRIVATE FUNCTIONS */
  void initTexture();
  void initSprite();
};


