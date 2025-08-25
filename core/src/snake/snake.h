#pragma once

#include "grid.h"
#include "tile.h"

typedef enum
{
    UP,
    DOWN,
    LEFT,
    RIGHT
} Direction;

typedef struct Snake Snake;

Snake* allocateSnake(Grid* const grid);
void freeSnake(Snake* const snake);

Grid* snakeGrid(const Snake* const snake);
Tile** snakeBody(const Snake* const snake);
Tile* snakeHead(const Snake* const snake);
Tile* snakeTail(const Snake* const snake);
unsigned snakeLength(const Snake* const snake);
Direction snakeDirection(const Snake* const snake);

void changeDirection(Snake* const snake, const Direction direction);

bool move(Snake* const snake);

bool snakeContainsTile(const Snake* const snake, const Tile* const tile);