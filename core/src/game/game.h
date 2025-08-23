#pragma once

#include "grid.h"

typedef struct Game Game;

Game* allocateGame();
void freeGame(Game* const game);

Grid* gameGrid(const Game* const game);
Snake* gameSnake(const Game* const game);

void placeFood(const Game* const game, const unsigned seed);

void printGame(const Game* const game);