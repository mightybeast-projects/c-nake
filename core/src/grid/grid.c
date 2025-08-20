#include "grid.h"
#include "safe-memory.h"

struct Grid
{
    unsigned width;
    unsigned height;
    Tile*** tiles;
};

Grid* allocateGrid(unsigned cols, unsigned rows)
{
    Grid* grid = safeMalloc(sizeof(struct Grid));

    grid->width = cols;
    grid->height = rows;

    grid->tiles = safeMalloc(sizeof(Tile**) * cols);

    for (int i = 0; i < cols; i++) {
        grid->tiles[i] = safeMalloc(sizeof(Tile*) * rows);

        for (int j = 0; j < rows; j++)
            grid->tiles[i][j] = allocateTile(i, j);
    }

    return grid;
}

void freeGrid(Grid* const grid)
{
    for (int i = 0; i < gridWidth(grid); i++) {
        for (int j = 0; j < gridHeight(grid); j++)
            freeTile(grid->tiles[i][j]);

        free(grid->tiles[i]);
    }

    free(grid->tiles);
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
