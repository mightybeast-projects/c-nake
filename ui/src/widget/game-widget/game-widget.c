#include "game-widget.h"
#include "grid-widget.h"
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
    freeGame(widget->game);
    free(widget);
}

void drawGameWidget(GameWidget* const widget)
{
    drawGridWidget(widget->gridWidget);
    drawSnakeWidget(widget->snakeWidget);
}