#include "game.h"
#include "mersenne-twister.h"
#include "safe-memory.h"
#include "stdio.h"

struct Game
{
    unsigned seed;
    bool isFinished;
    Grid* grid;
    Snake* snake;
};

static void placeRandomFood(const Game* const game, const unsigned seed);
static Tile* chooseRandomTile(const Game* game, MTState* const state);
static void printTile(const Tile* const tile, const Snake* const snake);

Game* allocateGame(const unsigned cols, const unsigned rows, const unsigned seed)
{
    Game* const game = safeMalloc(sizeof(struct Game));

    game->seed = seed;
    game->isFinished = false;
    game->grid = allocateGrid(cols, rows);
    game->snake = allocateSnake(game->grid);

    placeRandomFood(game, seed);

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

void updateGame(Game* const game)
{
    if (game->isFinished)
        return;

    const Snake* const snake = game->snake;

    moveSnake(snake);

    const unsigned width = gridWidth(game->grid);
    const unsigned height = gridHeight(game->grid);

    if (snakeEatsItself(snake) || snakeLength(snake) == width * height) {
        game->isFinished = true;

        return;
    }

    if (!game->isFinished && !foodTile(game))
        placeRandomFood(game, game->seed);
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