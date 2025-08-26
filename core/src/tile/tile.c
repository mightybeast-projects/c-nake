#include "tile.h"
#include "safe-memory.h"

struct Tile
{
    unsigned i;
    unsigned j;
    bool hasFood;
};

Tile* allocateTile(const unsigned i, const unsigned j)
{
    if ((int)i < 0 || (int)j < 0)
        return NULL;

    Tile* const tile = safeMalloc(sizeof(struct Tile));

    tile->i = i;
    tile->j = j;
    tile->hasFood = false;

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

bool tileHasFood(const Tile* const tile)
{
    return tile->hasFood;
}

void setTileFood(Tile* const tile, bool value)
{
    tile->hasFood = value;
}