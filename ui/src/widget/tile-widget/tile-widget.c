#include "tile-widget.h"
#include "safe-memory.h"

struct TileWidget
{
    Rectangle rect;
    Tile* tile;
};

TileWidget* allocateTileWidget(Tile* const tile, const Rectangle rect)
{
    TileWidget* const widget = safeMalloc(sizeof(struct TileWidget));

    widget->tile = tile;
    widget->rect = rect;

    return widget;
}

void freeTileWidget(TileWidget* const widget)
{
    freeTile(widget->tile);
    free(widget);
}

void drawTileWidget(const TileWidget* const widget)
{
    Color color = { 75, 75, 75, 255 };

    DrawRectangleRounded(widget->rect, 0.1, 10, color);
}