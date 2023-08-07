#include <iostream>

#include "Game.h"

int main() 
{
  // Init game
  Game game;

  // Game loop
  while (game.running()) 
  {
    game.update();
    game.render();
  }

  return 0;
}
