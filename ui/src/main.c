#include "config.h"
#include "game-widget.h"
#include "grid-widget.h"
#include "raylib.h"
#include "snake-widget.h"
#include "tile-widget.h"
#include "time.h"

void main(void)
{
    const GameParams params = { COLS, ROWS, 1 };
    Game* const game = allocateGame(params);

    GameWidget* const widget = allocateGameWidget(game);

    InitWindow(WIDTH, WIDTH, "C-nake");
    SetTargetFPS(60);

    Color color = { 46, 46, 46, 255 };

    while (!WindowShouldClose()) {
        ClearBackground(color);
        BeginDrawing();

        drawGameWidget(widget);

        EndDrawing();
    }

    CloseWindow();

    freeGame(game);
    freeGameWidget(widget);
}