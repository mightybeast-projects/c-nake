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

Grid* allocateGrid(const unsigned cols, const unsigned rows)
{
    Grid* grid = safeMalloc(sizeof(struct Grid));

    grid->width = cols;
    grid->height = rows;
    grid->tiles = allocateTiles(cols, rows);

    return grid;
}

void freeGrid(Grid* const grid)
{
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

void placeFood(const Grid* const grid, const unsigned seed)
{
    const unsigned width = gridWidth(grid);
    const unsigned height = gridHeight(grid);

    MTState state;

    initializeMTRandom(&state, seed);
    const int rIndex = nextMTRandom(&state) % (width * height);

    for (int i = 0; i < width; i++)
        for (int j = 0; j < height; j++)
            if (rIndex == height * i + j)
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