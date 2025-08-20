#pragma once

typedef struct Grid Grid;

Grid* allocateGrid(void);
void freeGrid(Grid* const grid);