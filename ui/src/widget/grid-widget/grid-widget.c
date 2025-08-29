#include "grid-widget.h"
#include "config.h"
#include "safe-memory.h"
#include "tile-widget.h"

struct GridWidget
{
    TileWidget*** tilesWidgets;
    Grid* grid;
};

static TileWidget*** allocateTilesWidgets(Grid* const grid);

GridWidget* allocateGridWidget(Grid* const grid)
{
    GridWidget* const widget = safeMalloc(sizeof(struct GridWidget));

    widget->grid = grid;
    widget->tilesWidgets = allocateTilesWidgets(grid);

    return widget;
}

void freeGridWidget(GridWidget* const widget)
{
    TileWidget*** const tilesWidgets = widget->tilesWidgets;

    for (int i = 0; i < gridWidth(widget->grid); i++) {
        for (int j = 0; j < gridHeight(widget->grid); j++)
            freeTileWidget(tilesWidgets[i][j]);

        free(tilesWidgets[i]);
    }

    free(tilesWidgets);
    free(widget);
}

void drawGridWidget(const GridWidget* const widget)
{
    for (int i = 0; i < gridWidth(widget->grid); i++) {
        for (int j = 0; j < gridHeight(widget->grid); j++) {
            Tile* const tile = gridTiles(widget->grid)[i][j];
            TileWidget* const tileWidget = widget->tilesWidgets[i][j];

            if (tileHasFood(tile))
                drawTileWidget(tileWidget, RED);
            else
                drawTileWidget(tileWidget, (Color) { 75, 75, 75, 255 });
        }
    }
}

static TileWidget*** allocateTilesWidgets(Grid* const grid)
{
    const unsigned width = gridWidth(grid);
    const unsigned height = gridHeight(grid);

    TileWidget*** const tilesWidgets = safeMalloc(sizeof(TileWidget**) * width);

    for (int i = 0; i < width; i++) {
        tilesWidgets[i] = safeMalloc(sizeof(TileWidget*) * height);

        for (int j = 0; j < height; j++)
            tilesWidgets[i][j] = allocateTileWidget(gridTiles(grid)[i][j]);
    }

    return tilesWidgets;
}