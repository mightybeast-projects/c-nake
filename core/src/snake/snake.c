#include "safe-memory.h"
#include "snake.h"

struct Snake
{
    Grid* grid;
};

Snake* allocateSnake(Grid* const grid)
{
    Snake* snake = safeMalloc(sizeof(struct Snake));

    snake->grid = grid;

    return snake;
}

void freeSnake(Snake* const snake)
{
    free(snake);
}

Grid* snakeGrid(const Snake* const snake)
{
    return snake->grid;
}
