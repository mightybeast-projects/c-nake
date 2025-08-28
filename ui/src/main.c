#include "config.h"
#include "game-widget.h"
#include "raylib.h"
#include "time.h"

static Game* game;

void main(void)
{
    const GameParams params = { COLS, ROWS, time(NULL) };
    game = allocateGame(params);

    GameWidget* const widget = allocateGameWidget(game);

    InitWindow(WIDTH, WIDTH, "C-nake");
    SetTargetFPS(60);

    Color color = { 46, 46, 46, 255 };

    while (!WindowShouldClose()) {
        ClearBackground(color);
        BeginDrawing();

        EndDrawing();
    }

    CloseWindow();

    freeGameWidget(widget);
}