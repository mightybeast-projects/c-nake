#include "raylib.h"
#include "tile.h"

typedef struct TileWidget TileWidget;

TileWidget* allocateTileWidget(Tile* const tile, const Rectangle rect);
void freeTileWidget(TileWidget* const widget);

void drawTileWidget(const TileWidget* const widget, const Color color);