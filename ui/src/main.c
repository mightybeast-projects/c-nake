#include "config.h"
#include "game-widget.h"
#include "grid-widget.h"
#include "raylib.h"
#include "tile-widget.h"
#include "time.h"

void main(void)
{
    Grid* const grid = allocateGrid(COLS, ROWS);
    GridWidget* const widget = allocateGridWidget(grid);

    InitWindow(WIDTH, WIDTH, "C-nake");
    SetTargetFPS(60);

    Color color = { 46, 46, 46, 255 };

    while (!WindowShouldClose()) {
        ClearBackground(color);
        BeginDrawing();

        drawGridWidget(widget);

        EndDrawing();
    }

    CloseWindow();

    freeGridWidget(widget);
}