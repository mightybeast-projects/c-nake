#include "safe-memory.h"
#include "snake.h"

struct Snake
{
    Grid* grid;
    Tile** body;
};

Snake* allocateSnake(Grid* const grid)
{
    Snake* snake = safeMalloc(sizeof(struct Snake));

    snake->grid = grid;
    snake->body = safeMalloc(sizeof(Tile*) * gridWidth(grid) * gridHeight(grid));

    snake->body[0] = gridTiles(grid)[0][0];
    snake->body[1] = gridTiles(grid)[0][1];

    return snake;
}

void freeSnake(Snake* const snake)
{
    free(snake->body);
    free(snake);
}

Grid* snakeGrid(const Snake* const snake)
{
    return snake->grid;
}

Tile** snakeBody(const Snake* const snake)
{
    return snake->body;
}
