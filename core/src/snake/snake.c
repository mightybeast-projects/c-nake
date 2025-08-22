#include "grid.h"
#include "safe-memory.h"
#include "snake.h"

struct Snake
{
    unsigned length;
    Grid* grid;
    Tile** body;
    Direction direction;
};

Snake* allocateSnake(Grid* const grid)
{
    Snake* snake = safeMalloc(sizeof(struct Snake));

    snake->grid = grid;
    snake->body = safeMalloc(sizeof(Tile*) * gridWidth(grid) * gridHeight(grid));
    snake->length = 2;
    snake->direction = DOWN;

    snake->body[0] = gridTiles(grid)[0][1];
    snake->body[1] = gridTiles(grid)[0][0];

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

Tile* snakeHead(const Snake* const snake)
{
    return snake->body[0];
}

Tile* snakeTail(const Snake* const snake)
{
    return snake->body[snake->length - 1];
}

unsigned snakeLength(const Snake* const snake)
{
    return snake->length;
}

Direction snakeDirection(const Snake* const snake)
{
    return snake->direction;
}

void changeDirection(Snake* const snake, const Direction direction)
{
    snake->direction = direction;
}