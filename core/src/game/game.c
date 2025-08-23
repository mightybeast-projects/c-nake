#include "game.h"
#include "mersenne-twister.h"
#include "safe-memory.h"
#include "stdio.h"

struct Game
{
    Grid* grid;
    Snake* snake;
};

static unsigned getRandomFoodIndex(const Game* game, const unsigned seed);
static unsigned getNextRandomIndex(const Game* game, MTState* const state);

Game* allocateGame()
{
    Game* game = safeMalloc(sizeof(struct Game));

    game->grid = allocateGrid(10, 10);
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

void placeFood(const Game* const game, const unsigned seed)
{
    Grid* const grid = game->grid;

    const unsigned index = getRandomFoodIndex(game, seed);
    const unsigned width = gridWidth(grid);
    const unsigned height = gridHeight(grid);

    for (int i = 0; i < width; i++)
        for (int j = 0; j < height; j++)
            if (index == height * i + j)
                setTileFood(gridTiles(grid)[i][j], true);
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
            if (snakeContainsTile(snake, tiles[j][i]))
                printf("# ");
            else
                printf(". ");

        printf("\n");
    }
}

static unsigned getRandomFoodIndex(const Game* const game, const unsigned seed)
{
    MTState* state = safeMalloc(sizeof(struct MTState));

    initializeMTRandom(state, seed);

    const unsigned index = getNextRandomIndex(game, state);

    free(state);

    return index;
}

static unsigned getNextRandomIndex(const Game* game, MTState* const state)
{
    Grid* const grid = game->grid;
    Snake* const snake = game->snake;

    const unsigned width = gridWidth(grid);
    const unsigned height = gridHeight(grid);
    const unsigned index = nextMTRandom(state) % (width * height);

    for (int i = 0; i < snakeLength(snake); i++) {
        Tile* bodyTile = snakeBody(snake)[i];

        if (height * tileI(bodyTile) + tileJ(bodyTile) == index)
            return getNextRandomIndex(game, state);
    }

    return index;
}