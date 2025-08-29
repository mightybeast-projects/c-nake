#include "game-widget.h"
#include "grid-widget.h"
#include "raylib.h"
#include "safe-memory.h"
#include "snake-widget.h"

struct GameWidget
{
    Game* game;
    GridWidget* gridWidget;
    SnakeWidget* snakeWidget;
};

GameWidget* allocateGameWidget(Game* const game)
{
    GameWidget* const widget = safeMalloc(sizeof(struct GameWidget));

    widget->game = game;
    widget->gridWidget = allocateGridWidget(gameGrid(game));
    widget->snakeWidget = allocateSnakeWidget(gameSnake(game));

    return widget;
}

void freeGameWidget(GameWidget* const widget)
{
    free(widget);
}

void handleMovementKeys(GameWidget* const widget)
{
    Snake* const snake = gameSnake(widget->game);

    if (IsKeyDown(KEY_W))
        changeSnakeDirection(snake, UP);
    if (IsKeyDown(KEY_S))
        changeSnakeDirection(snake, DOWN);
    if (IsKeyDown(KEY_A))
        changeSnakeDirection(snake, LEFT);
    if (IsKeyDown(KEY_D))
        changeSnakeDirection(snake, RIGHT);
}

void updateGameWidget(GameWidget* const widget)
{
    updateGame(widget->game);

    updateSnakeWidget(widget->snakeWidget);
}

void drawGameWidget(GameWidget* const widget)
{
    drawGridWidget(widget->gridWidget);
    drawSnakeWidget(widget->snakeWidget);
}