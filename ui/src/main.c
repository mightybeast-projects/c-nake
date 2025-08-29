#include "config.h"
#include "game-widget.h"
#include "grid-widget.h"
#include "raylib.h"
#include "snake-widget.h"
#include "stdio.h"
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

    unsigned dt = 0;

    while (!WindowShouldClose()) {
        handleMovementKeys(widget);

        if (dt >= 8) {
            updateGameWidget(widget);
            printGame(game);

            dt = 0;
        }

        dt++;

        ClearBackground(color);
        BeginDrawing();

        drawGameWidget(widget);

        EndDrawing();
    }

    CloseWindow();

    freeGameWidget(widget);
    freeGame(game);
}