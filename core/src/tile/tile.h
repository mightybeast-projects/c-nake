#pragma once

typedef struct Tile Tile;

Tile* allocateTile();
void freeTile(Tile* const tile);