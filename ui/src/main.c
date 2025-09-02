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
static unsigned dt = 0;

static void createGame(void);
static void updateGameFrame(void);
static void checkForRestart(void);
static void advanceGame(void);
static void drawRestartMessage(void);
static void deleteGame(void);

void main(void)
{
    createGame();

    InitWindow(WIDTH, WIDTH, "C-nake");
    SetTargetFPS(60);

    while (!WindowShouldClose())
        updateGameFrame();

    CloseWindow();

    deleteGame();
}

static void createGame(void)
{
    const GameParams params = { COLS, ROWS, time(NULL) };

    game = allocateGame(params);
    widget = allocateGameWidget(game);
}

static void updateGameFrame(void)
{
    checkForRestart();
    handleMovementKeys(widget);
    advanceGame();

    const Color color = { 46, 46, 46, 255 };
    ClearBackground(color);

    BeginDrawing();

    drawGameWidget(widget);

    if (gameIsFinished(game))
        drawRestartMessage();

    EndDrawing();
}

static void checkForRestart(void)
{
    if (gameIsFinished(game) && IsKeyPressed(KEY_R)) {
        deleteGame();
        createGame();
    }
}

static void advanceGame(void)
{
    if (dt >= 8) {
        updateGameWidget(widget);

        dt = 0;
    }

    dt++;
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