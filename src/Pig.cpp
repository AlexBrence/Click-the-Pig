#include "Pig.h"
#include <iostream>


/* PRIVATE FUNCTIONS */
void Pig::initTexture() 
{
  if (!m_texture.loadFromFile("/home/alex/Programming/cpp/Click-the-Pig/Textures/pig.png")) 
  {
    printf("[ERROR %s::%s] Could not load texture from a file!\n", __FILE__, __FUNCTION__);
  }
}

void Pig::initSprite() 
{
  sprite.setTexture(m_texture);
  sprite.setScale(0.7f, 0.7f);

  spriteSize = sprite.getGlobalBounds();
  sprite.setOrigin(spriteSize.width / 2.0f, spriteSize.height / 2.0f);
}

/* CONSTRUCTOR */
Pig::Pig() 
{
  initTexture();
  initSprite();
}

/* FUNCTIONS */

// Get
sf::Vector2<unsigned int> Pig::getSize() const 
{
  return m_texture.getSize();
}

sf::Vector2<float> Pig::getPosition() const 
{
  return sprite.getPosition();
}

sf::Sprite Pig::getSprite() const 
{
  return sprite;
}

sf::Texture Pig::getTexture() const 
{
  return m_texture;
};

// Set
void Pig::setPosition(const float x, const float y) 
{
  sprite.setPosition(x, y);
}

// Other
void Pig::move() 
{
  sprite.move(0.0f, fallingSpeed);
}

void Pig::update() 
{ }

void Pig::render(sf::RenderTarget &target) 
{
  target.draw(sprite);
}



