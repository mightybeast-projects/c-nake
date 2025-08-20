#include "safe-memory.h"
#include "tile.h"

struct Tile
{
};

Tile* allocateTile()
{
    Tile* tile = safeMalloc(sizeof(struct Tile));

    return tile;
}

void freeTile(Tile* const tile)
{
    free(tile);
}
