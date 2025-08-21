#pragma once

#include "tile.h"

typedef struct Grid Grid;

Grid* allocateGrid(const unsigned cols, const unsigned rows);
void freeGrid(Grid* const grid);

unsigned gridWidth(const Grid* const grid);
unsigned gridHeight(const Grid* const grid);

Tile*** gridTiles(const Grid* const grid);

void placeFood(const Grid* const grid, const unsigned seed);