#pragma once

#include "grid.h"

typedef struct Snake Snake;

Snake* allocateSnake(Grid* const grid);
void freeSnake(Snake* const snake);

Grid* snakeGrid(const Snake* const snake);

Tile** snakeBody(const Snake* const snake);