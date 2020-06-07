#include "Game.h"

int main(int argc, char *argv[]) {
  Game *game = new Game(argc, argv);
  game->runMainLoop();
  delete game;
  exit(0);
}
