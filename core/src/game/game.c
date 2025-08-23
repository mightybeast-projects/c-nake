#include "game.h"
#include "mersenne-twister.h"
#include "safe-memory.h"
#include "stdio.h"

struct Game
{
    Grid* grid;
    Snake* snake;
};

static Tile* chooseRandomTile(const Game* game, MTState* const state);
static void printTile(const Tile* const tile, const Snake* const snake);

Game* allocateGame(const unsigned cols, const unsigned rows)
{
    Game* game = safeMalloc(sizeof(struct Game));

    game->grid = allocateGrid(cols, rows);
    game->snake = allocateSnake(game->grid);

    return game;
}

void freeGame(Game* const game)
{
    freeSnake(game->snake);
    freeGrid(game->grid);
    free(game);
}

Grid* gameGrid(const Game* const game)
{
    return game->grid;
}

Snake* gameSnake(const Game* const game)
{
    return game->snake;
}

void placeRandomFood(const Game* const game, const unsigned seed)
{
    MTState* state = safeMalloc(sizeof(struct MTState));

    initializeMTRandom(state, seed);

    Tile* const tile = chooseRandomTile(game, state);

    setTileFood(tile, true);

    free(state);
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

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++)
            printTile(tiles[j][i], snake);

        printf("\n");
    }
}

static void printTile(const Tile* const tile, const Snake* const snake)
{
    const char* directionChars[4] = { "↑", "↓", "←", "→" };

    if (tileHasFood(tile))
        printf("x ");
    else if (tile == snakeHead(snake))
        printf("%s ", directionChars[snakeDirection(snake)]);
    else if (tile == snakeTail(snake))
        printf("* ");
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