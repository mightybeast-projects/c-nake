#include "snake.h"
#include "grid.h"
#include "safe-memory.h"

struct Snake
{
    unsigned length;
    Grid* grid;
    Tile** body;
    Direction direction;
};

static bool directionsAreOpposite(Direction a, Direction b);

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
    if (directionsAreOpposite(snake->direction, direction))
        return;

    snake->direction = direction;
}

void move(Snake* const snake)
{
    Tile*** const tiles = gridTiles(snake->grid);

    for (int i = snake->length - 1; i > 0; i--)
        snake->body[i] = snake->body[i - 1];

    Tile* const head = snakeHead(snake);
    const unsigned headI = tileI(head);
    const unsigned headJ = tileJ(head);

    Tile* nextHeadTile;

    if (snake->direction == DOWN)
        nextHeadTile = tiles[headI][headJ + 1];
    if (snake->direction == RIGHT)
        nextHeadTile = tiles[headI + 1][headJ];
    if (snake->direction == UP)
        nextHeadTile = tiles[headI][headJ - 1];
    if (snake->direction == LEFT)
        nextHeadTile = tiles[headI - 1][headJ];

    snake->body[0] = nextHeadTile;
}

bool snakeContainsTile(const Snake* const snake, const Tile* const tile)
{
    for (int i = 0; i < snake->length; i++)
        if (snake->body[i] == tile)
            return true;

    return false;
}

static bool directionsAreOpposite(Direction a, Direction b)
{
    return (a == DOWN && b == UP) || (a == UP && b == DOWN)
        || (a == RIGHT && b == LEFT) || (a == LEFT && b == RIGHT);
}