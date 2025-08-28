#include "config.h"
#include "game-widget.h"
#include "raylib.h"
#include "tile-widget.h"
#include "time.h"

static Game* game;

void main(void)
{
    const GameParams params = { COLS, ROWS, time(NULL) };
    game = allocateGame(params);

    GameWidget* const widget = allocateGameWidget(game);

    Tile* const tile = gridTiles(gameGrid(game))[0][0];
    const Rectangle rect = { 0, 0, 20, 20 };

    TileWidget* const tileWidget = allocateTileWidget(tile, rect);

    InitWindow(WIDTH, WIDTH, "C-nake");
    SetTargetFPS(60);

    Color color = { 46, 46, 46, 255 };

    while (!WindowShouldClose()) {
        ClearBackground(color);
        BeginDrawing();

        drawTileWidget(tileWidget);

        EndDrawing();
    }

    CloseWindow();

    freeGameWidget(widget);
}