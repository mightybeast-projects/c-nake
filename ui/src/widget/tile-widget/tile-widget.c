#include "tile-widget.h"
#include "config.h"
#include "safe-memory.h"

struct TileWidget
{
    Rectangle rect;
    Tile* tile;
};

TileWidget* allocateTileWidget(Tile* const tile)
{
    TileWidget* const widget = safeMalloc(sizeof(struct TileWidget));

    widget->tile = tile;

    calculateTileWidgetRect(widget);

    return widget;
}

void freeTileWidget(TileWidget* const widget)
{
    freeTile(widget->tile);
    free(widget);
}

void setTileWidgetTile(TileWidget* const widget, Tile* const tile)
{
    widget->tile = tile;
}

void calculateTileWidgetRect(TileWidget* const widget)
{
    const float margin = 5;
    const float size = (WIDTH - (COLS - 1) * margin - margin * 2) / COLS;
    const float x = tileI(widget->tile) * (size + margin) + margin;
    const float y = tileJ(widget->tile) * (size + margin) + margin;
    const Rectangle rect = { x, y, size, size };

    widget->rect = rect;
}

void drawTileWidget(const TileWidget* const widget, const Color color)
{
    if (!widget->tile)
        return;

    DrawRectangleRounded(widget->rect, 0.1, 10, color);
}