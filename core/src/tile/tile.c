#include "safe-memory.h"
#include "tile.h"

struct Tile
{
    unsigned i;
    unsigned j;
};

Tile* allocateTile(unsigned i, unsigned j)
{
    Tile* tile = safeMalloc(sizeof(struct Tile));

    tile->i = i;
    tile->j = j;

    return tile;
}

void freeTile(Tile* const tile)
{
    free(tile);
}

unsigned tileI(const Tile* const tile)
{
    return tile->i;
}

unsigned tileJ(const Tile* const tile)
{
    return tile->j;
}
