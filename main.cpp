#include <iostream>
#include "Game.h"

int main() {

    // Init srand
    srand(static_cast<unsigned>(time(nullptr)));

    // Init game
    Game game;

    // Game loop
    while (game.running()) {
        game.update();

        game.render();
    }

    return 0;
}
