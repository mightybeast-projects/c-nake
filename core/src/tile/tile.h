#pragma once

#include "stdbool.h"

typedef struct Tile Tile;

Tile* allocateTile(const unsigned i, const unsigned j);
void freeTile(Tile* const tile);

unsigned tileI(const Tile* const tile);
unsigned tileJ(const Tile* const tile);

bool tileHasFood(const Tile* const tile);
void setTileFood(Tile* const tile, bool value);