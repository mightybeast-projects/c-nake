#include "grid.h"
#include "mersenne-twister.h"
#include "safe-memory.h"

struct Grid
{
    unsigned width;
    unsigned height;
    Tile*** tiles;
};

static Tile*** allocateTiles(const unsigned cols, const unsigned rows);
static void freeTiles(Grid* const grid);

static unsigned getRandomFoodIndex(
    const Grid* const grid,
    const Snake* const snake,
    const unsigned seed);

static unsigned getNextRandomIndex(
    const Grid* const grid,
    const Snake* const snake,
    MTState* const state);

Grid* allocateGrid(const unsigned cols, const unsigned rows)
{
    bool zeroSize = (int)cols == 0 || (int)rows == 0;
    bool lessThanThreeRows = rows < 3;

    if (zeroSize || lessThanThreeRows)
        return NULL;

    Grid* grid = safeMalloc(sizeof(struct Grid));

    grid->width = cols;
    grid->height = rows;
    grid->tiles = allocateTiles(cols, rows);

    return grid;
}

void freeGrid(Grid* const grid)
{
    if (!grid)
        return;

    freeTiles(grid);
    free(grid);
}

unsigned gridWidth(const Grid* const grid)
{
    return grid->width;
}

unsigned gridHeight(const Grid* const grid)
{
    return grid->height;
}

Tile*** gridTiles(const Grid* const grid)
{
    return grid->tiles;
}

void placeFood(const Grid* const grid, const Snake* const snake, const unsigned seed)
{
    const unsigned index = getRandomFoodIndex(grid, snake, seed);
    const unsigned width = gridWidth(grid);
    const unsigned height = gridHeight(grid);

    for (int i = 0; i < width; i++)
        for (int j = 0; j < height; j++)
            if (index == height * i + j)
                setTileFood(gridTiles(grid)[i][j], true);
}

static Tile*** allocateTiles(const unsigned cols, const unsigned rows)
{
    Tile*** tiles = safeMalloc(sizeof(Tile**) * cols);

    for (int i = 0; i < cols; i++) {
        tiles[i] = safeMalloc(sizeof(Tile*) * rows);

        for (int j = 0; j < rows; j++)
            tiles[i][j] = allocateTile(i, j);
    }

    return tiles;
}

static void freeTiles(Grid* const grid)
{
    for (int i = 0; i < gridWidth(grid); i++) {
        for (int j = 0; j < gridHeight(grid); j++)
            freeTile(grid->tiles[i][j]);

        free(grid->tiles[i]);
    }

    free(grid->tiles);
}

static unsigned getRandomFoodIndex(
    const Grid* const grid,
    const Snake* const snake,
    const unsigned seed)
{
    MTState* state = safeMalloc(sizeof(struct MTState));

    initializeMTRandom(state, seed);

    const unsigned index = getNextRandomIndex(grid, snake, state);

    free(state);

    return index;
}

static unsigned getNextRandomIndex(
    const Grid* const grid,
    const Snake* const snake,
    MTState* const state)
{
    const unsigned width = gridWidth(grid);
    const unsigned height = gridHeight(grid);
    const unsigned index = nextMTRandom(state) % (width * height);

    for (int i = 0; i < snakeLength(snake); i++) {
        Tile* bodyTile = snakeBody(snake)[i];

        if (height * tileI(bodyTile) + tileJ(bodyTile) == index)
            return getNextRandomIndex(grid, snake, state);
    }

    return index;
}