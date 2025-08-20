#include "grid.h"
#include "safe-memory.h"

struct Grid
{
};

Grid* allocateGrid(void)
{
    Grid* grid = safeMalloc(sizeof(struct Grid));

    return grid;
}

void freeGrid(Grid* const grid)
{
    free(grid);
}
