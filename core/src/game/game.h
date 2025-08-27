#pragma once

#include "grid.h"
#include "snake.h"

typedef struct GameParams
{
    unsigned cols;
    unsigned rows;
    unsigned seed;
} GameParams;

typedef struct Game Game;

Game* allocateGame(const GameParams params);
void freeGame(Game* const game);

bool gameIsFinished(const Game* const game);
Grid* gameGrid(const Game* const game);
Snake* gameSnake(const Game* const game);

Tile* foodTile(const Game* const game);

void updateGame(Game* const game);

void printGame(const Game* const game);