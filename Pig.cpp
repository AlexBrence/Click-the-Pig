//
// Created by alex on 24. 10. 21.
//

#include <iostream>
#include "Pig.h"


/* PRIVATE FUNCTIONS */
void Pig::initTexture() {
    if (!texture.loadFromFile("/home/alex/Documents/Letnik02/RPO/tasks/task02/Click-the-Pig/Textures/pig.png")) {
        std::cout << "[ERROR::PIG::CONSTRUCTOR] Could not load texture from a file!\n";
    }
}

void Pig::initSprite() {
    sprite.setTexture(texture);

    sprite.setScale(0.7f, 0.7f);


    spriteSize = sprite.getGlobalBounds();
    sprite.setOrigin(spriteSize.width / 2.f, spriteSize.height / 2.f);
}

/* CONSTRUCTOR */
Pig::Pig() {
    initTexture();
    initSprite();
}

/* FUNCTIONS */

// Get
//sf::Vector2<unsigned int> Pig::getSize() const {
//    return texture.getSize();
//}
//
//sf::Vector2<float> Pig::getPosition() const {
//    return sprite.getPosition();
//}

sf::Sprite Pig::getSprite() const {
    return sprite;
}

sf::Texture Pig::getTexture() const {
    return texture;
};

// Set
void Pig::setPosition(const float x, const float y) {
    sprite.setPosition(x, y);
}

// Other
void Pig::move() {
    sprite.move(0.f, fallingSpeed);
}

void Pig::update() {
}

void Pig::render(sf::RenderTarget &target) {
    target.draw(sprite);
}



