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

static Tile** allocateBody(const Grid* const grid);
static Tile* getNextSnakeMoveTile(const Snake* const snake);
static bool directionsAreOpposite(const Direction a, const Direction b);

Snake* allocateSnake(Grid* const grid)
{
    Snake* const snake = safeMalloc(sizeof(struct Snake));

    snake->grid = grid;
    snake->body = allocateBody(grid);
    snake->length = 2;
    snake->direction = DOWN;

    return snake;
}

void freeSnake(Snake* const snake)
{
    free(snake->body);
    free(snake);
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

Grid* snakeGrid(const Snake* const snake)
{
    return snake->grid;
}

void changeSnakeDirection(Snake* const snake, const Direction direction)
{
    if (directionsAreOpposite(snake->direction, direction))
        return;

    snake->direction = direction;
}

void moveSnake(Snake* const snake)
{
    Tile* tile = getNextSnakeMoveTile(snake);

    if (tileHasFood(tile)) {
        setTileFood(tile, false);
        snake->length++;
    }

    for (int i = snake->length - 1; i > 0; i--)
        snake->body[i] = snake->body[i - 1];

    snake->body[0] = tile;
}

bool snakeContainsTile(const Snake* const snake, const Tile* const tile)
{
    for (int i = 0; i < snake->length; i++)
        if (snake->body[i] == tile)
            return true;

    return false;
}

bool snakeEatsItself(const Snake* const snake)
{
    for (int i = snake->length - 1; i > 0; i--)
        if (snake->body[i] == snake->body[0])
            return true;

    return false;
}

static Tile** allocateBody(const Grid* const grid)
{
    const unsigned width = gridWidth(grid);
    const unsigned height = gridHeight(grid);

    Tile** const body = safeMalloc(sizeof(Tile*) * width * height);

    for (int i = 0; i < width * height; i++)
        body[i] = NULL;

    body[0] = gridTiles(grid)[0][1];
    body[1] = gridTiles(grid)[0][0];

    return body;
}

static Tile* getNextSnakeMoveTile(const Snake* const snake)
{
    const Grid* const grid = snake->grid;
    const int width = gridWidth(grid);
    const int height = gridHeight(grid);

    const int vectors[4][2] = { { 0, -1 }, { 0, 1 }, { -1, 0 }, { 1, 0 } };
    const int* vector = vectors[snakeDirection(snake)];

    Tile* const head = snakeHead(snake);
    const int headI = tileI(head);
    const int headJ = tileJ(head);

    int tileI = headI + vector[0];
    int tileJ = headJ + vector[1];

    if (tileJ > height - 1)
        tileJ = 0;
    if (tileJ < 0)
        tileJ = height - 1;
    if (tileI > width - 1)
        tileI = 0;
    if (tileI < 0)
        tileI = width - 1;

    Tile*** const tiles = gridTiles(grid);

    return tiles[tileI][tileJ];
}

static bool directionsAreOpposite(const Direction a, const Direction b)
{
    return (a == DOWN && b == UP) || (a == UP && b == DOWN)
        || (a == RIGHT && b == LEFT) || (a == LEFT && b == RIGHT);
}