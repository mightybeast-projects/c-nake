#pragma once

#include "grid.h"
#include "snake.h"

typedef struct Game Game;

Game* allocateGame(const unsigned cols, const unsigned rows);
void freeGame(Game* const game);

bool gameIsFinished(const Game* const game);
Grid* gameGrid(const Game* const game);
Snake* gameSnake(const Game* const game);

Tile* foodTile(const Game* const game);
void placeRandomFood(const Game* const game, const unsigned seed);

void moveSnake(const Game* const game);

void printGame(const Game* const game);