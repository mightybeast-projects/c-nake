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
    GridWidget* widget = safeMalloc(sizeof(struct GridWidget));

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
    freeGrid(widget->grid);
    free(widget);
}

void drawGridWidget(const GridWidget* const widget)
{
    const unsigned width = gridWidth(widget->grid);
    const unsigned height = gridHeight(widget->grid);

    for (int i = 0; i < width; i++)
        for (int j = 0; j < height; j++)
            drawTileWidget(widget->tilesWidgets[i][j]);
}

static TileWidget*** allocateTilesWidgets(Grid* const grid)
{
    const unsigned width = gridWidth(grid);
    const unsigned height = gridHeight(grid);

    TileWidget*** const tilesWidgets = safeMalloc(sizeof(TileWidget**) * width);

    const float margin = 2;
    const float size = (WIDTH - (width - 1) * margin - margin * 2) / width;

    for (int i = 0; i < width; i++) {
        tilesWidgets[i] = safeMalloc(sizeof(TileWidget*) * height);

        for (int j = 0; j < height; j++) {
            float x = i * (size + margin) + margin;
            float y = j * (size + margin) + margin;
            Rectangle rect = { x, y, size, size };
            Tile* tile = gridTiles(grid)[i][j];

            tilesWidgets[i][j] = allocateTileWidget(tile, rect);
        }
    }

    return tilesWidgets;
}