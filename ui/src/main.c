#include "config.h"
#include "game-widget.h"
#include "grid-widget.h"
#include "raylib.h"
#include "snake-widget.h"
#include "stdio.h"
#include "tile-widget.h"
#include "time.h"

static Game* game;
static GameWidget* widget;

static void createGame(void);
static void drawRestartMessage(void);
static void deleteGame();

void main(void)
{
    InitWindow(WIDTH, WIDTH, "C-nake");
    SetTargetFPS(60);

    createGame();

    const Color color = { 46, 46, 46, 255 };

    unsigned dt = 0;

    while (!WindowShouldClose()) {
        if (gameIsFinished(game) && IsKeyPressed(KEY_R)) {
            deleteGame();
            createGame();
        }

        handleMovementKeys(widget);

        if (dt >= 8) {
            updateGameWidget(widget);

            dt = 0;
        }

        dt++;

        ClearBackground(color);
        BeginDrawing();

        drawGameWidget(widget);

        if (gameIsFinished(game))
            drawRestartMessage();

        EndDrawing();
    }

    deleteGame();

    CloseWindow();
}

static void createGame(void)
{
    const GameParams params = { COLS, ROWS, time(NULL) };
    game = allocateGame(params);
    widget = allocateGameWidget(game);
}

static void drawRestartMessage(void)
{
    const int fontSize = 30;
    const char* str = "Press R to restart.";
    const int textWidth = MeasureText(str, fontSize);
    const int x = WIDTH / 2 - textWidth / 2;
    const int y = WIDTH / 2 + textWidth / 2;

    DrawText(str, x, y, fontSize, WHITE);
}

static void deleteGame()
{
    freeGame(game);
    freeGameWidget(widget);
}