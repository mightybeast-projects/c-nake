#include "game.h"
#include "mersenne-twister.h"
#include "safe-memory.h"
#include "stdio.h"
#include "time.h"

struct Game
{
    bool isFinished;
    Grid* grid;
    Snake* snake;
};

static Tile* chooseRandomTile(const Game* game, MTState* const state);
static void printTile(const Tile* const tile, const Snake* const snake);

Game* allocateGame(const unsigned cols, const unsigned rows)
{
    Game* const game = safeMalloc(sizeof(struct Game));

    game->grid = allocateGrid(cols, rows);
    game->snake = allocateSnake(game->grid);
    game->isFinished = false;

    return game;
}

void freeGame(Game* const game)
{
    freeSnake(game->snake);
    freeGrid(game->grid);
    free(game);
}

bool gameIsFinished(const Game* const game)
{
    return game->isFinished;
}

Grid* gameGrid(const Game* const game)
{
    return game->grid;
}

Snake* gameSnake(const Game* const game)
{
    return game->snake;
}

Tile* foodTile(const Game* const game)
{
    Tile*** const tiles = gridTiles(game->grid);
    const unsigned width = gridWidth(game->grid);
    const unsigned height = gridHeight(game->grid);

    for (int i = 0; i < width; i++)
        for (int j = 0; j < height; j++)
            if (tileHasFood(tiles[i][j]))
                return tiles[i][j];

    return NULL;
}

void placeRandomFood(const Game* const game, const unsigned seed)
{
    MTState* state = safeMalloc(sizeof(struct MTState));

    initializeMTRandom(state, seed);

    Tile* const tile = chooseRandomTile(game, state);

    setTileFood(tile, true);

    free(state);
}

void moveSnake(Game* const game)
{
    if (game->isFinished)
        return;

    Snake* const snake = game->snake;

    const int vectors[4][2] = { { 0, -1 }, { 0, 1 }, { -1, 0 }, { 1, 0 } };
    const int* vector = vectors[snakeDirection(snake)];

    Grid* const grid = game->grid;
    const int width = gridWidth(grid);
    const int height = gridHeight(grid);

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

    Tile*** const tiles = gridTiles(game->grid);
    Tile* const tile = tiles[tileI][tileJ];

    if (tileHasFood(tile))
        growSnake(snake);

    Tile** const sbody = snakeBody(snake);
    const unsigned length = snakeLength(snake);

    for (int i = length - 1; i > 0; i--)
        sbody[i] = sbody[i - 1];

    if (snakeContainsTile(snake, tile)) {
        game->isFinished = true;
        return;
    }

    sbody[0] = tile;

    if (snakeLength(snake) == width * height)
        game->isFinished = true;

    if (tileHasFood(tile) && !game->isFinished) {
        setTileFood(tile, false);
        placeRandomFood(game, time(NULL));
    }
}

void printGame(const Game* const game)
{
    const Grid* const grid = game->grid;
    const Snake* const snake = game->snake;

    Tile*** const tiles = gridTiles(grid);
    const unsigned width = gridWidth(grid);
    const unsigned height = gridHeight(grid);

    Tile** const body = snakeBody(snake);
    const unsigned length = snakeLength(snake);

    printf("\n");

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++)
            printTile(tiles[j][i], snake);

        printf("\n");
    }

    printf("\n");
}

static void printTile(const Tile* const tile, const Snake* const snake)
{
    const char* directionChars[4] = { "↑", "↓", "←", "→" };

    if (tile == snakeHead(snake))
        printf("%s ", directionChars[snakeDirection(snake)]);
    else if (tile == snakeTail(snake))
        printf("* ");
    else if (tileHasFood(tile))
        printf("x ");
    else if (snakeContainsTile(snake, tile))
        printf("# ");
    else
        printf(". ");
}

static Tile* chooseRandomTile(const Game* game, MTState* const state)
{
    Grid* const grid = game->grid;

    const unsigned i = nextMTRandom(state) % gridWidth(grid);
    const unsigned j = nextMTRandom(state) % gridHeight(grid);

    Tile* const tile = gridTiles(grid)[i][j];

    if (snakeContainsTile(game->snake, tile))
        return chooseRandomTile(game, state);

    return tile;
}