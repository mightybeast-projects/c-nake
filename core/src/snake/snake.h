#pragma once

#include "tile.h"

typedef enum
{
    UP,
    DOWN,
    LEFT,
    RIGHT
} Direction;

typedef struct Grid Grid;
typedef struct Snake Snake;

Snake* allocateSnake(Grid* const grid);
void freeSnake(Snake* const snake);

Grid* snakeGrid(const Snake* const snake);
Tile** snakeBody(const Snake* const snake);
Tile* snakeHead(const Snake* const snake);
Tile* snakeTail(const Snake* const snake);
unsigned snakeLength(const Snake* const snake);
Direction snakeDirection(const Snake* const snake);