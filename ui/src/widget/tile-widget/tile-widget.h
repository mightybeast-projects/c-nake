#include "raylib.h"
#include "tile.h"

typedef struct TileWidget TileWidget;

TileWidget* allocateTileWidget(Tile* const tile);
void freeTileWidget(TileWidget* const widget);

void setTileWidgetTile(TileWidget* const widget, Tile* const tile);

void calculateTileWidgetRect(TileWidget* const widget);

void drawTileWidget(const TileWidget* const widget, const Color color);