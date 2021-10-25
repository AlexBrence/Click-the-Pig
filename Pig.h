//
// Created by alex on 24. 10. 21.
//

#ifndef CLICK_THE_PIG_PIG_H
#define CLICK_THE_PIG_PIG_H


#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Pig {
private:
    /* VARIABLES */

    // Constants
    const float fallingSpeed = 2.f;

    // Sprite
    sf::Sprite sprite;
    sf::Texture texture;
    sf::FloatRect spriteSize;


    /* PRIVATE FUNCTIONS */
    void initTexture();
    void initSprite();

public:
    /* CONSTRUCTOR */
    Pig();

    /* FUNCTIONS */

    // Get
//    sf::Vector2<unsigned int> getSize() const;
//    sf::Vector2<float> getPosition() const;
    sf::Sprite getSprite() const;
    sf::Texture getTexture() const;

    // Set
    void setPosition(const float x, const float y);

    // Other
    void move();
    void update();
    void render(sf::RenderTarget& target);
};


#endif //CLICK_THE_PIG_PIG_H
