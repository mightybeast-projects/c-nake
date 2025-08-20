#pragma once

typedef struct Grid Grid;

Grid* allocateGrid(unsigned cols, unsigned rows);
void freeGrid(Grid* const grid);

unsigned gridWidth(const Grid* const grid);
unsigned gridHeight(const Grid* const grid);