#include "grid.h"

typedef struct GridWidget GridWidget;

GridWidget* allocateGridWidget(Grid* const grid);
void freeGridWidget(GridWidget* const widget);

void drawGridWidget(const GridWidget* const widget);