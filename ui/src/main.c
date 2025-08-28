#include "config.h"
#include "game-widget.h"
#include "grid-widget.h"
#include "raylib.h"
#include "snake-widget.h"
#include "tile-widget.h"
#include "time.h"

void main(void)
{
    Grid* const grid = allocateGrid(COLS, ROWS);
    Snake* const snake = allocateSnake(grid);

    GridWidget* const gridWidget = allocateGridWidget(grid);
    SnakeWidget* const snakeWidget = allocateSnakeWidget(snake);

    InitWindow(WIDTH, WIDTH, "C-nake");
    SetTargetFPS(60);

    Color color = { 46, 46, 46, 255 };

    while (!WindowShouldClose()) {
        ClearBackground(color);
        BeginDrawing();

        drawGridWidget(gridWidget);
        drawSnakeWidget(snakeWidget);

        EndDrawing();
    }

    CloseWindow();

    freeGridWidget(gridWidget);
    freeSnakeWidget(snakeWidget);
}