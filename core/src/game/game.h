#pragma once

#include "grid.h"

typedef struct Game Game;

Game* allocateGame();
void freeGame(Game* const game);

Grid* gameGrid(const Game* const game);
Snake* gameSnake(const Game* const game);