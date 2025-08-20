#include "grid.h"
#include "safe-memory.h"

struct Grid
{
    unsigned width;
    unsigned height;
};

Grid* allocateGrid(unsigned cols, unsigned rows)
{
    Grid* grid = safeMalloc(sizeof(struct Grid));

    grid->width = cols;
    grid->height = rows;

    return grid;
}

void freeGrid(Grid* const grid)
{
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
