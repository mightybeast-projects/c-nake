#pragma once

typedef struct Tile Tile;

Tile* allocateTile(unsigned i, unsigned j);
void freeTile(Tile* const tile);

unsigned tileI(const Tile* const tile);
unsigned tileJ(const Tile* const tile);